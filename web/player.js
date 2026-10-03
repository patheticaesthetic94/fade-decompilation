'use strict';
// Fade web player: in-screen edition launcher, data download/cache, LCD filter and hardware buttons.
const $ = selector => document.querySelector(selector);
const params = new URLSearchParams(location.search);
const device = $('#device');
const canvas = $('#canvas');
const today = $('#today');
const loading = $('#loading');
const status = $('#status');
const detail = $('#detail');
const bar = $('.bar');
const barFill = $('#bar-fill');
const retry = $('#retry');
const lcdLaunch = $('#lcd-launch');
const lcdToggle = $('#lcd-toggle');
const backup = $('#backup');
const guide = $('#guide');
const help = $('#help');
let game = null;
let packs = null;
let running = false;
let failed = false;

const store = {
  get(key) { try { return localStorage.getItem(key); } catch { return null; } },
  set(key, value) { try { localStorage.setItem(key, value); } catch { /* storage unavailable */ } },
};
const mib = bytes => `${(bytes / 2 ** 20).toFixed(bytes < 100 * 2 ** 20 ? 1 : 0)} MB`;

// ---- Pocket PC clock and date ------------------------------------------------------------
function tick() {
  const now = new Date();
  const time = now.toLocaleTimeString([], { hour: 'numeric', minute: '2-digit' });
  for (const clock of document.querySelectorAll('.clock')) clock.textContent = time;
  $('#today-date').textContent = now.toLocaleDateString([], { weekday: 'long', month: 'long', day: 'numeric', year: 'numeric' });
}
tick();
setInterval(tick, 15000);

// ---- screen filter -----------------------------------------------------------------------
let lcd = params.has('lcd') ? params.get('lcd') === '1' : store.get('fade-lcd') === '1';
function setLcd(on) {
  lcd = on;
  store.set('fade-lcd', on ? '1' : '0');
  lcdLaunch.checked = on;
  lcdToggle.setAttribute('aria-pressed', String(on));
  device.classList.toggle('lcd', on);
  if (running && game) game._port_set_lcd(on ? 1 : 0);
}
setLcd(lcd);
lcdLaunch.onchange = () => setLcd(lcdLaunch.checked);
lcdToggle.onclick = () => setLcd(!lcd);

// ---- walkthrough and help ----------------------------------------------------------------
function showGuide(show) {
  guide.hidden = !show;
  document.body.classList.toggle('guide-open', show);
  for (const b of document.querySelectorAll('[data-open="guide"]')) b.setAttribute('aria-expanded', String(show));
  if (show) {
    const frame = $('#guide-frame');
    // Keep the same iframe mounted when closing so the reading position is retained.
    if (!frame.hasAttribute('src')) frame.src = frame.dataset.src;
    $('#guide-close').focus();
  }
  window.dispatchEvent(new Event('resize'));
}
for (const b of document.querySelectorAll('[data-open]')) {
  b.onclick = () => b.dataset.open === 'guide' ? showGuide(guide.hidden) : help.showModal();
}
$('#guide-close').onclick = () => showGuide(false);

// Fullscreen hides the device and scales the game to the display. Without the Fullscreen API
// (iPhone Safari), the same layout fills the browser window instead.
const fsButton = $('#fullscreen');
function setFullscreen(on) {
  document.body.classList.toggle('fs', on);
  fsButton.setAttribute('aria-pressed', String(on));
  fsButton.querySelector('span').textContent = on ? 'Exit fullscreen' : 'Fullscreen';
  window.dispatchEvent(new Event('resize'));
}
fsButton.onclick = () => {
  const on = !document.body.classList.contains('fs');
  if (!on && document.fullscreenElement) document.exitFullscreen().catch(() => {});
  else if (on && document.documentElement.requestFullscreen) {
    document.documentElement.requestFullscreen({ navigationUI: 'hide' }).catch(() => setFullscreen(true));
  }
  if (!document.documentElement.requestFullscreen || !on) setFullscreen(on);
};
document.addEventListener('fullscreenchange', () => setFullscreen(Boolean(document.fullscreenElement)));
// Reveal the dock briefly when the pointer moves in fullscreen.
let idle;
window.addEventListener('pointermove', () => {
  if (!document.body.classList.contains('fs')) return;
  document.body.classList.add('pointer-active');
  clearTimeout(idle);
  idle = setTimeout(() => document.body.classList.remove('pointer-active'), 2000);
});
$('#power').onclick = () => {
  if (!running || confirm('Return to the edition choice? Unsaved progress will be lost.')) location.href = location.pathname;
};

// ---- hardware buttons send the keys the game reads ---------------------------------------
const keyCodes = { ArrowUp: 38, ArrowDown: 40, ArrowLeft: 37, ArrowRight: 39, Enter: 13, Escape: 27, z: 90, x: 88, c: 67 };
const keyNames = { z: 'KeyZ', x: 'KeyX', c: 'KeyC' };
function sendKey(type, key) {
  const event = new KeyboardEvent(type, { key, code: keyNames[key] || key, bubbles: true, cancelable: true });
  for (const prop of ['keyCode', 'which']) Object.defineProperty(event, prop, { get: () => keyCodes[key] });
  document.dispatchEvent(event);
}
for (const button of document.querySelectorAll('[data-key]')) {
  const key = button.dataset.key;
  const pad = button.closest('.dpad');
  let down = false;
  const press = event => {
    event.preventDefault();
    if (down) return;
    down = true;
    button.setPointerCapture?.(event.pointerId);
    button.classList.add('pressed');
    if (pad && !button.classList.contains('action')) pad.dataset.tilt = button.className;
    if (running) sendKey('keydown', key);
  };
  const release = () => {
    if (!down) return;
    down = false;
    button.classList.remove('pressed');
    if (pad) delete pad.dataset.tilt;
    if (running) sendKey('keyup', key);
  };
  button.addEventListener('pointerdown', press);
  button.addEventListener('pointerup', release);
  button.addEventListener('pointercancel', release);
  button.addEventListener('lostpointercapture', release);
  button.addEventListener('contextmenu', event => event.preventDefault());
}
canvas.addEventListener('contextmenu', event => event.preventDefault());
window.addEventListener('keydown', event => {
  if (running && ['ArrowUp', 'ArrowDown', 'ArrowLeft', 'ArrowRight', ' '].includes(event.key)) event.preventDefault();
});

// ---- data packs --------------------------------------------------------------------------
// Each pack is split into content-hashed parts (tools/pack_web_data.py). Parts download a few at a
// time and are kept in Cache Storage, so a repeat visit (or a retry after an interruption) only
// fetches what is missing.
const PARALLEL = 4;
const openCache = () => (window.caches ? caches.open('fade-data').catch(() => null) : Promise.resolve(null));
const partUrl = part => new URL(`data/${part.file}`, location.href).href;

async function loadIndex() {
  const response = await fetch('data/packs.json', { cache: 'no-cache' });
  if (!response.ok) throw new Error('The game files could not be found.');
  packs = await response.json();
  const cache = await openCache();
  const current = new Set([...packs.classic.parts, ...packs.remastered.parts].map(partUrl));
  const stored = new Set();
  if (cache) {
    for (const request of await cache.keys()) {
      if (current.has(request.url)) stored.add(request.url);
      else cache.delete(request);   // parts of an older release
    }
  }
  const missing = list => list.filter(pack => pack.parts.some(part => !stored.has(partUrl(part))))
    .reduce((sum, pack) => sum + pack.bytes, 0);
  const label = bytes => bytes ? `${mib(bytes)} download` : 'Stored on this device';
  $('#size-classic').textContent = label(missing([packs.classic]));
  $('#size-remastered').textContent = label(missing([packs.classic, packs.remastered]));
}

async function readBody(response, expected, progress) {
  const bytes = new Uint8Array(expected);
  const reader = response.body.getReader();
  let received = 0;
  for (;;) {
    const { done, value } = await reader.read();
    if (done) break;
    if (received + value.length > expected) throw new Error('The downloaded game files are damaged. Try again.');
    bytes.set(value, received);
    received += value.length;
    progress(value.length);
  }
  if (received !== expected) throw new Error('The download was interrupted. Try again.');
  return bytes;
}

// Fetches one part (from the cache when stored) and writes it, inflated, into the pack buffer.
async function fetchPart(cache, part, target, offset, progress) {
  const url = partUrl(part);
  let body = null;
  const cached = cache && await cache.match(url).catch(() => null);
  if (cached) {
    body = new Uint8Array(await cached.arrayBuffer());
    if (body.length === part.bytes) progress(part.bytes);
    else body = null;
  }
  if (!body) {
    const response = await fetch(url).catch(() => null);
    if (!response || !response.ok || !response.body) throw new Error('The game files could not be downloaded. Check your connection and try again.');
    body = await readBody(response, part.bytes, progress);
    if (cache) cache.put(url, new Response(body, { headers: { 'Content-Type': 'application/octet-stream' } })).catch(() => {});
  }
  let raw = body;
  if (part.gzip) {
    if (!window.DecompressionStream) throw new Error('This browser is too old to unpack the game files.');
    raw = new Uint8Array(await new Response(new Blob([body]).stream().pipeThrough(new DecompressionStream('gzip'))).arrayBuffer());
  }
  if (raw.length !== part.size) throw new Error('The downloaded game files are damaged. Try again.');
  target.set(raw, offset);
}

async function fetchPacks(list, progress) {
  const cache = await openCache();
  // Ask the browser not to evict the stored game when space runs low.
  navigator.storage?.persist?.().catch(() => {});
  const jobs = [];
  const buffers = list.map(pack => {
    const bytes = new Uint8Array(pack.size);
    let offset = 0;
    for (const part of pack.parts) {
      jobs.push([part, bytes, offset]);
      offset += part.size;
    }
    return bytes;
  });
  let next = 0;
  const worker = async () => {
    while (next < jobs.length) {
      const [part, bytes, offset] = jobs[next++];
      await fetchPart(cache, part, bytes, offset, progress);
    }
  };
  await Promise.all(Array.from({ length: PARALLEL }, worker));
  return buffers;
}

function showLoading(message) {
  today.hidden = true;
  loading.hidden = false;
  retry.hidden = true;
  status.textContent = message;
  device.dataset.state = 'loading';
}
function fail(message) {
  failed = true;
  running = false;
  canvas.hidden = true;
  showLoading(message);
  device.dataset.state = 'off';
  bar.hidden = true;
  detail.textContent = '';
  retry.hidden = false;
  retry.textContent = 'Back to editions';
  retry.onclick = () => { location.href = location.pathname; };
}

function loadScript(src) {
  return new Promise((resolve, reject) => {
    const script = document.createElement('script');
    script.src = src;
    script.onload = resolve;
    script.onerror = () => reject(new Error('The game could not be downloaded. Check your connection and try again.'));
    document.head.append(script);
  });
}

async function start(edition) {
  if (running) return;
  running = true;
  const remastered = edition === 'remastered';
  const name = remastered ? 'Remastered' : 'Classic';
  document.title = `Fade · ${name}`;
  showLoading(`Loading ${name}…`);
  bar.hidden = false;
  bar.classList.remove('indeterminate');
  try {
    if (!window.WebAssembly) throw new Error('This browser does not support WebAssembly.');
    if (!packs) await loadIndex();
    const wanted = remastered ? [packs.classic, packs.remastered] : [packs.classic];
    const total = wanted.reduce((sum, p) => sum + p.bytes, 0);
    let received = 0;
    const engine = loadScript('fade.js');
    const buffers = await fetchPacks(wanted, n => {
      received += n;
      barFill.style.width = `${(received / total) * 100}%`;
      detail.textContent = `${mib(received)} of ${mib(total)}`;
    });
    await engine;
    status.textContent = `Starting ${name}…`;
    detail.textContent = '';
    bar.classList.add('indeterminate');
    game = await window.createFade({
      canvas,
      noInitialRun: true,
      locateFile: path => path,
      preRun: [module => {
        const FS = module.FS;
        // Files are owned by the downloaded buffers, so nothing is copied.
        buffers.forEach((bytes, i) => {
          for (const [path, offset, size] of wanted[i].files) {
            const slash = path.lastIndexOf('/');
            FS.mkdirTree('/' + path.slice(0, slash));
            FS.createDataFile('/' + path.slice(0, slash), path.slice(slash + 1), bytes.subarray(offset, offset + size), true, false, true);
          }
        });
        module.ENV.FADE_EDITION = edition;
        module.ENV.FADE_LCD = lcd ? '1' : '0';
        if (params.has('trace')) module.ENV.FADE_TRACE = '1';
        FS.mkdir('/saves');
        FS.mount(module.IDBFS, { autoPersist: true }, '/saves');
        module.addRunDependency('restore-saves');
        FS.syncfs(true, err => {
          if (err) detail.textContent = 'Browser storage is unavailable. Download a save backup before leaving.';
          module.removeRunDependency('restore-saves');
        });
      }],
      onAbort: message => fail(`The game stopped: ${message}`),
      onExit: () => {
        running = false;
        canvas.hidden = true;
        showLoading('Game closed. Your saved games are kept in this browser.');
        device.dataset.state = 'off';
        bar.hidden = true;
        retry.hidden = false;
        retry.textContent = 'Back to editions';
        retry.onclick = () => { location.href = location.pathname; };
      },
      print: text => console.info(text),
      printErr: text => console.error(text),
    });
    if (failed) return;
    window.game = game;
    loading.hidden = true;
    canvas.hidden = false;
    device.dataset.state = 'on';
    backup.disabled = false;
    canvas.focus();
    game.callMain([]);
  } catch (err) {
    fail(err.message || String(err));
  }
}

for (const button of document.querySelectorAll('.edition')) button.onclick = () => start(button.dataset.edition);
loadIndex().catch(() => { /* reported when an edition is chosen */ });
// play.html?version=hd (older links) and ?edition=classic|remastered start directly.
const requested = params.get('edition') || { hd: 'remastered', normal: 'classic' }[params.get('version')];
if (requested === 'classic' || requested === 'remastered') start(requested);

backup.onclick = () => {
  if (!game) return;
  const files = {};
  (function collect(path) {
    for (const name of game.FS.readdir(path)) {
      if (name === '.' || name === '..') continue;
      const full = `${path}/${name}`;
      if (game.FS.isDir(game.FS.stat(full).mode)) collect(full);
      else files[full.slice('/saves/'.length)] = Array.from(game.FS.readFile(full));
    }
  })('/saves');
  const url = URL.createObjectURL(new Blob([JSON.stringify({ format: 'fade-saves-v1', files })], { type: 'application/json' }));
  const link = document.createElement('a');
  link.href = url;
  link.download = 'fade-saves.json';
  link.click();
  setTimeout(() => URL.revokeObjectURL(url), 1000);
};

window.addEventListener('error', event => {
  if (running && event.error) fail(`The game stopped: ${event.error.message}`);
});
