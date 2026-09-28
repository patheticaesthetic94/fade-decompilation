'use strict';
const version = new URLSearchParams(location.search).get('version') === 'hd' ? 'hd' : 'normal';
const canvas = document.querySelector('#canvas');
const status = document.querySelector('#status');
const overlay = document.querySelector('#overlay');
const start = document.querySelector('#start');
const progress = document.querySelector('#progress');
const fullscreen = document.querySelector('#fullscreen');
const backup = document.querySelector('#backup');
const player = document.querySelector('.player');
const walkthroughToggle = document.querySelector('#walkthrough-toggle');
const walkthroughPanel = document.querySelector('#walkthrough-panel');
const walkthroughGuide = document.querySelector('#walkthrough-guide');
function showWalkthrough(show) {
  walkthroughPanel.hidden = !show;
  player.classList.toggle('walkthrough-open', show);
  walkthroughToggle.setAttribute('aria-expanded', String(show));
  if (show) {
    // Keep the same iframe mounted when closing so reading position is retained.
    if (!walkthroughGuide.hasAttribute('src')) walkthroughGuide.src = walkthroughGuide.dataset.src;
    document.querySelector('#walkthrough-close').focus();
  } else {
    (game && overlay.hidden ? canvas : walkthroughToggle).focus();
  }
}
walkthroughToggle.onclick = () => showWalkthrough(walkthroughPanel.hidden);
document.querySelector('#walkthrough-close').onclick = () => showWalkthrough(false);
let game;
let failed = false;
document.querySelector('#edition').textContent = `Fade · ${version === 'hd' ? 'HD' : 'Original'}`;
document.title = `Fade · ${version === 'hd' ? 'HD' : 'Original'}`;
function error(message) {
  failed = true;
  overlay.hidden = false;
  status.textContent = message;
  progress.hidden = true;
  start.textContent = 'Reload and retry';
  start.disabled = false;
  start.onclick = () => location.reload();
}
function loadScript(src) {
  return new Promise((resolve, reject) => {
    const script = document.createElement('script');
    script.src = src;
    script.onload = resolve;
    script.onerror = () => reject(new Error('The game files could not be downloaded. Check your connection and try again.'));
    document.head.append(script);
  });
}
start.onclick = async () => {
  start.disabled = true;
  progress.hidden = false;
  status.textContent = version === 'hd' ? 'Downloading HD. This edition is a large download…' : 'Downloading Original…';
  try {
    if (!window.WebAssembly) throw new Error('This browser does not support WebAssembly.');
    await loadScript(`${version}/fade.js`);
    game = await window.createFade({
      canvas,
      noInitialRun: true,
      locateFile: path => `${version}/${path}`,
      setStatus: text => { if (text && !failed) status.textContent = text; },
      monitorRunDependencies: left => {
        progress.removeAttribute('value');
        if (left && !failed) status.textContent = 'Loading game data…';
      },
      preRun: [module => {
        if (new URLSearchParams(location.search).has('trace')) module.ENV.FADE_TRACE = '1';
        const FS = module.FS;
        FS.mkdir('/saves');
        FS.mount(module.IDBFS, { autoPersist: true }, '/saves');
        module.addRunDependency('restore-saves');
        FS.syncfs(true, err => {
          if (err) document.querySelector('#storage').textContent = 'Browser storage is unavailable. Download a save backup before leaving.';
          module.removeRunDependency('restore-saves');
        });
      }],
      onAbort: message => error(`The game stopped: ${message}`),
      onExit: () => {
        overlay.hidden = false;
        status.textContent = 'Game closed. Your saved games are kept in this browser.';
        start.disabled = false;
        start.textContent = 'Play again';
        start.onclick = () => location.reload();
      },
      print: text => console.info(text),
      printErr: text => console.error(text),
    });
    if (failed) return;
    overlay.hidden = true;
    progress.hidden = true;
    fullscreen.disabled = !player.requestFullscreen;
    backup.disabled = false;
    canvas.focus();
    game.callMain([]);
  } catch (err) { error(err.message || String(err)); }
};
fullscreen.onclick = () => player.requestFullscreen().catch(err => {
  document.querySelector('#storage').textContent = `Fullscreen unavailable: ${err.message}`;
});
canvas.addEventListener('contextmenu', event => event.preventDefault());
canvas.addEventListener('keydown', event => {
  if (['ArrowUp', 'ArrowDown', 'ArrowLeft', 'ArrowRight', ' '].includes(event.key)) event.preventDefault();
});
backup.onclick = () => {
  if (!game) return;
  const files = {};
  function collect(path) {
    for (const name of game.FS.readdir(path)) {
      if (name === '.' || name === '..') continue;
      const full = `${path}/${name}`;
      if (game.FS.isDir(game.FS.stat(full).mode)) collect(full);
      else files[full.slice('/saves/'.length)] = Array.from(game.FS.readFile(full));
    }
  }
  collect('/saves');
  const url = URL.createObjectURL(new Blob([JSON.stringify({format: 'fade-saves-v1', files})], {type: 'application/json'}));
  const link = document.createElement('a');
  link.href = url;
  link.download = 'fade-saves.json';
  link.click();
  setTimeout(() => URL.revokeObjectURL(url), 1000);
};

window.addEventListener('error', event => {
  if (event.error && start.disabled) error(`The game stopped: ${event.error.message}`);
});
