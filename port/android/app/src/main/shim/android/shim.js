'use strict';
// Android shell for the web player (loaded before player.js; see Assets.java). The page is the web
// player's own index.html, site.css and player.js; this adapts it to the native game:
//   Home (HomeActivity):   choosing an edition starts the native game (GameActivity); saved games
//                          are the native files instead of IndexedDB.
//   Game (?native=<edition>, GameActivity): the page shows its "running" state over the native
//                          surface, cuts a hole where the screen is and reports that rectangle.
// player.js's top-level bindings (running, game, overlay, notifyBox, ...) are shared script globals.
(() => {
  const bridge = window.FadeAndroid;
  const NATIVE = new URLSearchParams(location.search).get('native');

  // The app is always full screen. Without the Fullscreen API, player.js toggles its Fullscreen
  // layout itself (its iPhone path), so the dock's Exit fullscreen button shows the Pocket PC device.
  Object.defineProperty(Element.prototype, 'requestFullscreen', { value: undefined, configurable: true });

  // Back up: a download link to a blob is handed to Android's "save as" picker.
  const click = HTMLAnchorElement.prototype.click;
  HTMLAnchorElement.prototype.click = function () {
    if (bridge && this.download && this.href.startsWith('blob:')) {
      fetch(this.href).then(r => r.text()).then(text => bridge.saveFile(this.download, text));
      return;
    }
    return click.call(this);
  };

  // Android's Back button: close a balloon or screen first; during a game, ask before returning Home
  // (the Home button); on Home, leave the app.
  window.fadeAndroidBack = () => {
    try {
      if (!notifyBox.hidden) { dismiss(); return true; }
      if (!walkMenu.hidden) { showMenu(false); return true; }
      if (overlay) { closeOverlay(); return true; }
      if (NATIVE) { actions.home(); return true; }
    } catch { /* page not ready */ }
    return false;
  };

  // Saved games cross the bridge as {path: base64}; the page uses {path: byte array}.
  const decode = json => Object.fromEntries(Object.entries(JSON.parse(json))
    .map(([name, b64]) => [name, Array.from(atob(b64), c => c.charCodeAt(0))]));
  const encode = files => JSON.stringify(Object.fromEntries(Object.entries(files).map(([name, bytes]) => {
    let s = '';
    for (let i = 0; i < bytes.length; i += 0x8000) s += String.fromCharCode.apply(null, Array.from(bytes.slice(i, i + 0x8000)));
    return [name, btoa(s)];
  })));
  const fullscreen = () => document.body.classList.contains('fs');

  // Deferred player.js has run by now.
  document.addEventListener('DOMContentLoaded', () => (NATIVE ? gameMode() : homeMode()));

  function homeMode() {
    // Both editions are in the APK.
    window.loadIndex = async () => { sizes = [0, 0]; showSizes(); };
    loadIndex();
    window.start = edition => bridge.play(edition, lang, lcd, fullscreen());
    // Saves: the native game's files. Games saved by the earlier WebView-only APK (IndexedDB in this
    // same WebView profile) are copied over once, when there are no native saves yet.
    const browserSaves = readStoredSaves;
    window.readStoredSaves = async () => decode(bridge.readSaves());
    window.writeStoredSaves = async files => { if (!bridge.replaceSaves(encode(files))) throw new Error('restore'); };
    (async () => {
      if (!Object.keys(await readStoredSaves()).length) {
        const old = await browserSaves();
        if (Object.keys(old).length) bridge.replaceSaves(encode(old));
      }
      showSaves();
    })();
  }

  function gameMode() {
    const edition = NATIVE === 'remastered' ? 'remastered' : 'classic';
    const name = lang === 'fr' ? FR[edition] : edition === 'remastered' ? 'Remastered' : 'Classic';
    // The engine is native: the filter switch and device/dock keys go to it through the bridge.
    running = true;
    game = { _port_set_lcd: on => bridge.setLcd(Boolean(on)) };
    window.sendKey = (type, key) => bridge.key(type === 'keydown', key);
    window.showSaves = async () => {};
    actions.home = window.goHome = () => {
      closeOverlay();
      notify(t('leave'), [[t('yes'), () => bridge.home(lcd, fullscreen())], [t('no'), null]]);
    };
    document.title = `Fade · ${name}`;
    showLoading(t('starting', name));
    bar.hidden = false;
    bar.classList.add('indeterminate');
    detail.textContent = '';
    window.fadeNativeReady = () => {
      if (failed || loading.hidden) return;
      loading.hidden = true;
      device.dataset.state = 'on';
    };
    if (bridge.isStarted()) fadeNativeReady();

    // The native surface lies under this page. Everything is painted as usual except the screen
    // rectangle, which an even-odd clip leaves transparent (a balloon over it stays painted). While
    // the loading screen, Walkthrough or Help covers the screen, nothing is cut out.
    // html's own (transparent) image stops body's background from moving to the unclippable canvas.
    const style = document.createElement('style');
    style.textContent = 'html { background-image: linear-gradient(transparent, transparent); }';
    document.head.append(style);
    const screenEl = document.querySelector('#screen');
    const stage = document.querySelector('#stage');
    let lastClip = null, lastRect = '';
    const box = r => `M${r.left} ${r.top}h${r.width}v${r.height}h${-r.width}Z`;
    (function frame() {
      const r = screenEl.getBoundingClientRect();
      const covered = !loading.hidden || overlay !== null || failed;
      let clip = 'none';
      if (!covered) {
        let path = `M0 0H${innerWidth}V${innerHeight}H0Z ${box(r)}`;
        if (!notifyBox.hidden) {
          // The balloon, and its tail (site.css .notify::before: 12u wide, 10u tall, 26u from the right).
          const n = notifyBox.getBoundingClientRect(), u = r.width / 240, tip = n.right - 32 * u;
          path += ` ${box(n)} M${tip} ${n.top - 10 * u}L${tip + 6 * u} ${n.top}H${tip - 6 * u}Z`;
        }
        clip = `path(evenodd, '${path}')`;
      }
      if (clip !== lastClip) {
        document.body.style.clipPath = stage.style.clipPath = clip;
        lastClip = clip;
      }
      const blocking = covered || !notifyBox.hidden;
      const rect = [r.left, r.top, r.width, r.height, devicePixelRatio, blocking].join();
      if (rect !== lastRect) {
        lastRect = rect;
        bridge.setScreen(r.left, r.top, r.width, r.height, devicePixelRatio, blocking);
      }
      requestAnimationFrame(frame);
    })();
  }
})();
