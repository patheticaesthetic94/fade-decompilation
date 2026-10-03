'use strict';
// Fade web player: in-screen edition launcher, data download/cache, LCD filter and hardware buttons.
const $ = selector => document.querySelector(selector);
const params = new URLSearchParams(location.search);
const BUILD = '?v=dev';   // replaced by tools/web_build.sh, so a release never pairs with a cached engine
const device = $('#device');
const canvas = $('#canvas');
const today = $('#today');
const loading = $('#loading');
const status = $('#status');
const detail = $('#detail');
const bar = $('.bar');
const barFill = $('#bar-fill');
const retry = $('#retry');
const backup = $('#backup');
const notifyBox = $('#notify');
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
  for (const box of document.querySelectorAll('.lcd-check')) box.checked = on;
  for (const b of document.querySelectorAll('.lcd-toggle, #power')) b.setAttribute('aria-pressed', String(on));
  device.classList.toggle('lcd', on);
  if (running && game) game._port_set_lcd(on ? 1 : 0);
}
setLcd(lcd);
for (const box of document.querySelectorAll('.lcd-check')) box.onchange = () => setLcd(box.checked);
// The power button on top of the device, and the fullscreen dock, switch the filter.
for (const b of document.querySelectorAll('.lcd-toggle, #power')) b.onclick = () => setLcd(!lcd);

// ---- game text language: ?lang=fr|en, otherwise the last choice in this browser ----------------
// The flags behave like a Pocket PC toolbar's toggle buttons: the current language stays pressed.
let lang = (params.get('lang') || store.get('fade-lang')) === 'fr' ? 'fr' : 'en';
const flags = document.querySelectorAll('.flag');
function setLang(code) {
  lang = code;
  for (const flag of flags) flag.setAttribute('aria-checked', String(flag.dataset.lang === code));
}
setLang(lang);
for (const flag of flags) {
  flag.onclick = () => { setLang(flag.dataset.lang); store.set('fade-lang', lang); };
  flag.onkeydown = event => {
    if (!['ArrowLeft', 'ArrowRight'].includes(event.key)) return;
    const other = [...flags].find(f => f !== flag);
    other.focus();
    other.click();
    event.preventDefault();
  };
}

// ---- walkthrough and help: Pocket PC screens drawn over the game --------------------------
const overlays = { guide: $('#walk'), help: $('#helpscreen') };
const walkDoc = $('#walk-doc');
const walkMenu = $('#walk-menu');
const walkContents = $('#walk-contents');
let overlay = null;          // name of the open screen
let guideLoaded = null;

function loadGuide() {
  guideLoaded ??= fetch('walkthrough.html').then(r => {
    if (!r.ok) throw new Error();
    return r.text();
  }).then(html => {
    const main = new DOMParser().parseFromString(html, 'text/html').querySelector('main');
    walkDoc.replaceChildren(...[...main.childNodes].map(node => document.importNode(node, true)));
    // Chapter menu from the guide's sections.
    walkMenu.replaceChildren(...[...walkDoc.querySelectorAll('h2')].map(h => {
      const item = document.createElement('li');
      const button = document.createElement('button');
      button.type = 'button';
      button.setAttribute('role', 'menuitem');
      button.textContent = h.textContent;
      button.onclick = () => { showMenu(false); scrollDocTo(h); };
      item.append(button);
      return item;
    }));
  }).catch(() => {
    guideLoaded = null;
    walkDoc.innerHTML = '<p class="doc-loading">The walkthrough could not be loaded. <a href="walkthrough.html" target="_blank" rel="noopener">Open it in a new tab</a>.</p>';
  });
}
function scrollDocTo(target) {
  walkDoc.scrollTop = target.getBoundingClientRect().top - walkDoc.getBoundingClientRect().top + walkDoc.scrollTop
    - parseFloat(getComputedStyle(walkDoc).paddingTop);
  walkDoc.focus({ preventScroll: true });
}
// Links inside the guide jump within its own scroller.
walkDoc.addEventListener('click', event => {
  const link = event.target.closest('a[href^="#"]');
  if (!link) return;
  const target = walkDoc.querySelector(CSS.escape ? `#${CSS.escape(link.hash.slice(1))}` : link.hash);
  if (target) { event.preventDefault(); scrollDocTo(target); }
});
function showMenu(show) {
  walkMenu.hidden = !show;
  walkContents.setAttribute('aria-expanded', String(show));
  if (show) walkMenu.querySelector('button')?.focus();
}
walkContents.onclick = () => showMenu(walkMenu.hidden);
$('#walk-top').onclick = () => { walkDoc.scrollTop = 0; };

function openOverlay(name) {
  if (overlay === name) return closeOverlay();
  closeOverlay();
  overlay = name;
  overlays[name].hidden = false;
  if (name === 'guide') loadGuide();
  for (const b of document.querySelectorAll('.dock [data-open]')) b.setAttribute('aria-pressed', String(b.dataset.open === name));
  overlays[name].querySelector('.doc').focus({ preventScroll: true });
}
function closeOverlay() {
  if (!overlay) return;
  showMenu(false);
  overlays[overlay].hidden = true;   // the scroll position survives: the screen stays mounted
  overlay = null;
  for (const b of document.querySelectorAll('.dock [data-open]')) b.setAttribute('aria-pressed', 'false');
  if (running) canvas.focus();
}
for (const b of document.querySelectorAll('[data-open]')) b.addEventListener('click', () => openOverlay(b.dataset.open));

// ---- Pocket PC notification balloon --------------------------------------------------------
let notifyClose = null;
function notify(text, actions) {
  $('#notify-text').textContent = text;
  const row = $('#notify-actions');
  row.replaceChildren(...actions.map(([label, run]) => {
    const button = document.createElement('button');
    button.type = 'button';
    button.className = 'ppc-button';
    button.textContent = label;
    button.onclick = () => { dismiss(); run?.(); };
    return button;
  }));
  const previous = document.activeElement;
  notifyClose = () => previous?.focus?.({ preventScroll: true });
  notifyBox.hidden = false;
  row.lastElementChild.focus();   // the safe choice
}
function dismiss() {
  if (notifyBox.hidden) return;
  notifyBox.hidden = true;
  notifyClose?.();
}
function notifyKey(key) {
  const buttons = [...notifyBox.querySelectorAll('button')];
  const at = buttons.indexOf(document.activeElement);
  if (key === 'ArrowLeft' || key === 'ArrowUp') buttons[Math.max(0, at - 1)].focus();
  else if (key === 'ArrowRight' || key === 'ArrowDown') buttons[Math.min(buttons.length - 1, at + 1)].focus();
  else if (key === 'Enter') (buttons[at] || buttons.at(-1)).click();
  else if (key === 'Escape') dismiss();
}

// ---- device buttons: Home, Walkthrough, Fullscreen, Help -----------------------------------
function goHome() {
  closeOverlay();
  if (!running) {
    if (game || failed || params.has('edition') || params.has('version')) location.href = location.pathname;
    return;
  }
  notify('Return to the edition menu? Anything since your last save will be lost.',
    [['Yes', () => { location.href = location.pathname; }], ['No', null]]);
}
const actions = {
  home: goHome,
  guide: () => openOverlay('guide'),
  help: () => openOverlay('help'),
  fullscreen: () => toggleFullscreen(),
};
for (const b of document.querySelectorAll('[data-action]')) b.addEventListener('click', () => actions[b.dataset.action]());
for (const b of document.querySelectorAll('[data-close]')) b.onclick = closeOverlay;

// While a screen is open, the game does not see the keyboard; keys scroll or close the screen.
function overlayKey(key) {
  const doc = overlays[overlay].querySelector('.doc');
  const step = doc.clientHeight;
  if (key === 'ArrowUp') doc.scrollBy({ top: -step / 6 });
  else if (key === 'ArrowDown') doc.scrollBy({ top: step / 6 });
  else if (key === 'ArrowLeft') doc.scrollBy({ top: -step * 0.9 });
  else if (key === 'ArrowRight') doc.scrollBy({ top: step * 0.9 });
  else if (key === 'Enter' || key === 'Escape') closeOverlay();
}
// Registered before the engine's listener, so SDL never sees keys meant for a screen or balloon.
window.addEventListener('keydown', event => {
  if (!event.isTrusted) return;
  if (!notifyBox.hidden) {
    event.stopImmediatePropagation();
    if (event.key.startsWith('Arrow') || event.key === 'Escape') { event.preventDefault(); notifyKey(event.key); }
    return;
  }
  if (!overlay) return;
  event.stopImmediatePropagation();
  if (event.key === 'Escape') { event.preventDefault(); walkMenu.hidden ? closeOverlay() : showMenu(false); }
}, true);
window.addEventListener('keyup', event => {
  if (event.isTrusted && (overlay || !notifyBox.hidden)) event.stopImmediatePropagation();
}, true);

// Fullscreen hides the device and scales the game to the display. Without the Fullscreen API
// (iPhone Safari), the same layout fills the browser window instead.
function setFullscreen(on) {
  document.body.classList.toggle('fs', on);
  window.dispatchEvent(new Event('resize'));
}
function toggleFullscreen() {
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
  let toGame = false;   // the key-down went to the game, so its key-up must too
  const press = event => {
    event.preventDefault();
    if (down) return;
    down = true;
    button.setPointerCapture?.(event.pointerId);
    button.classList.add('pressed');
    if (pad && !button.classList.contains('action')) pad.dataset.tilt = button.className;
    toGame = !overlay && notifyBox.hidden && running;
    if (toGame) sendKey('keydown', key);
    else if (!notifyBox.hidden) notifyKey(key);
    else if (overlay) overlayKey(key);
  };
  const release = () => {
    if (!down) return;
    down = false;
    button.classList.remove('pressed');
    if (pad) delete pad.dataset.tilt;
    if (toGame) sendKey('keyup', key);
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
    const engine = loadScript('fade.js' + BUILD);
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
      locateFile: path => path + BUILD,
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
        if (lang === 'fr') module.ENV.FADE_LANG = 'fr';
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

// ---- saved games: read from the engine while it runs, otherwise straight from IndexedDB -----
// IDBFS keeps each file under its full path ('/saves/...') in the 'FILE_DATA' store of a database
// named after the mount point.
function readStoredSaves() {
  return new Promise(resolve => {
    let request;
    try { request = indexedDB.open('/saves', 21); } catch { resolve({}); return; }
    request.onupgradeneeded = () => request.transaction.abort();   // nothing saved yet: create nothing
    request.onerror = () => resolve({});
    request.onsuccess = () => {
      const db = request.result;
      const files = {};
      try {
        const cursor = db.transaction('FILE_DATA', 'readonly').objectStore('FILE_DATA').openCursor();
        cursor.onsuccess = () => {
          const c = cursor.result;
          if (!c) { db.close(); resolve(files); return; }
          if (c.value?.contents && String(c.key).startsWith('/saves/')) files[String(c.key).slice('/saves/'.length)] = Array.from(c.value.contents);
          c.continue();
        };
        cursor.onerror = () => { db.close(); resolve(files); };
      } catch { db.close(); resolve({}); }
    };
  });
}
function readRunningSaves() {
  const files = {};
  (function collect(path) {
    for (const name of game.FS.readdir(path)) {
      if (name === '.' || name === '..') continue;
      const full = `${path}/${name}`;
      if (game.FS.isDir(game.FS.stat(full).mode)) collect(full);
      else files[full.slice('/saves/'.length)] = Array.from(game.FS.readFile(full));
    }
  })('/saves');
  return files;
}
const readSaves = () => (game && running ? Promise.resolve(readRunningSaves()) : readStoredSaves());
async function showSaves() {
  const files = await readSaves();
  const count = Object.keys(files).filter(name => name.startsWith('save/')).length;
  $('#saves-count').textContent = count ? `Saved games: ${count}` : 'No saved games yet';
  backup.disabled = !Object.keys(files).length;
}
showSaves();
// Restore: replaces the IDBFS store with a backup's files. The engine reloads /saves from it at startup.
const FILE_MODE = 0o100666, DIR_MODE = 0o40777;
function parseBackup(text) {
  const data = JSON.parse(text);
  if (data?.format !== 'fade-saves-v1' || typeof data.files !== 'object' || !data.files) throw new Error();
  const files = {};
  for (const [name, bytes] of Object.entries(data.files)) {
    if (!/^[^/\\].*$/.test(name) || name.split('/').some(part => !part || part === '.' || part === '..')) throw new Error();
    if (!Array.isArray(bytes) || bytes.length > 4 << 20 || bytes.some(b => !Number.isInteger(b) || b < 0 || b > 255)) throw new Error();
    files[name] = Uint8Array.from(bytes);
  }
  if (!Object.keys(files).length) throw new Error();
  return files;
}
function writeStoredSaves(files) {
  return new Promise((resolve, reject) => {
    const request = indexedDB.open('/saves', 21);
    request.onupgradeneeded = () => {   // first save in this browser: same schema as IDBFS
      const store = request.result.objectStoreNames.contains('FILE_DATA')
        ? request.transaction.objectStore('FILE_DATA') : request.result.createObjectStore('FILE_DATA');
      if (!store.indexNames.contains('timestamp')) store.createIndex('timestamp', 'timestamp', { unique: false });
    };
    request.onerror = () => reject(request.error);
    request.onsuccess = () => {
      const db = request.result;
      const tx = db.transaction('FILE_DATA', 'readwrite');
      const store = tx.objectStore('FILE_DATA');
      const now = new Date();
      store.delete(IDBKeyRange.bound('/saves/', '/saves/\uffff'));
      const dirs = new Set();
      for (const [name, contents] of Object.entries(files)) {
        const parts = name.split('/');
        for (let i = 1; i < parts.length; i++) dirs.add(parts.slice(0, i).join('/'));
        store.put({ timestamp: now, mode: FILE_MODE, contents }, `/saves/${name}`);
      }
      for (const dir of dirs) store.put({ timestamp: now, mode: DIR_MODE }, `/saves/${dir}`);
      tx.oncomplete = () => { db.close(); resolve(); };
      tx.onerror = tx.onabort = () => { db.close(); reject(tx.error); };
    };
  });
}
const restoreFile = $('#restore-file');
$('#restore').onclick = () => { restoreFile.value = ''; restoreFile.click(); };
restoreFile.onchange = async () => {
  const file = restoreFile.files[0];
  if (!file) return;
  let files;
  try { files = parseBackup(await file.text()); } catch {
    notify('That file is not a Fade save backup.', [['OK', null]]);
    return;
  }
  const count = Object.keys(files).filter(name => name.startsWith('save/')).length;
  const games = `${count} saved game${count === 1 ? '' : 's'}`;
  notify(`Replace the saved games in this browser with the ${games} in this backup?`, [
    ['Restore', async () => {
      try {
        await writeStoredSaves(files);
        await showSaves();
        notify(`Restored ${games}.`, [['OK', null]]);
      } catch {
        notify('The backup could not be restored. Browser storage may be unavailable.', [['OK', null]]);
      }
    }],
    ['Cancel', null],
  ]);
};

backup.onclick = async () => {
  const files = await readSaves();
  if (!Object.keys(files).length) return;
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
