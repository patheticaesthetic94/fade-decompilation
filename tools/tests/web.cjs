// Browser regression: in-screen launcher, real menus, gameplay, save/reload, cross-edition saves,
// French text, the live screen filter and the device's hardware buttons.
// NODE_PATH=build/web-test/node_modules node tools/tests/web.cjs
const assert = require('node:assert/strict');
const fs = require('node:fs');
const { chromium } = require('playwright');
const base = process.env.FADE_WEB_TEST_URL || 'http://127.0.0.1:8000/';
const output = 'build/web-test';
fs.mkdirSync(output, { recursive: true });
(async () => {
  const browser = await chromium.launch({
    headless: true,
    ...(process.env.FADE_BROWSER_PATH ? { executablePath: process.env.FADE_BROWSER_PATH } : {}),
  });
  try {
    const context = await browser.newContext({ viewport: { width: 1000, height: 1100 } });
    const page = await context.newPage();
    const errors = [];
    page.on('pageerror', err => errors.push(err.message));
    const logs = [];
    page.on('console', m => logs.push(m.text()));
    async function launch(mode, query = '') {
      logs.length = 0;
      await page.goto(`${base}?lcd=0${query}`);
      await page.click(`.edition[data-edition="${mode}"]`);
      await page.waitForFunction(() => window.game?.HEAPU8?.[0x474b1] === 1, null, { timeout: 180000 });
      assert.deepEqual(errors, [], 'Browser runtime errors');
    }
    async function tap(x, y) {
      const box = await page.locator('#canvas').boundingBox();
      await page.mouse.click(box.x + box.width * x / 240, box.y + box.height * y / 320, {delay: 100});
      await page.waitForTimeout(1000);
    }
    async function chooseFirstPopupItem() {
      // Coordinates come from the visible menu's recovered ItemRect, allowing
      // Original and HD to use their different font metrics.
      await page.waitForFunction(() => game.HEAPU8[0x47530] > 0);
      const point = await page.evaluate(() => {
        const view = new DataView(game.HEAPU8.buffer);
        return {
          x: view.getInt32(0x4753c, true) + view.getInt32(0x47544, true) / 2,
          y: view.getInt32(0x47540, true) + view.getInt32(0x47548, true) / 2,
        };
      });
      await tap(point.x, point.y);
    }
    const saves = () => page.evaluate(() => {
      const result = {};
      for (const name of game.FS.readdir('/saves/save')) {
        if (name !== '.' && name !== '..') result[name] = Array.from(game.FS.readFile('/saves/save/' + name));
      }
      return result;
    });
    await launch('classic');
    await page.screenshot({ path: `${output}/original-menu.png` });
    await tap(120, 20);
    assert.equal(await page.evaluate(() => game.HEAPU8[0x48688]), 1, 'New Game enters gameplay');
    await page.screenshot({ path: `${output}/original-scene.png` });
    // The original introduction requires paging with the lower-right arrow.
    // Options is deliberately ignored until the current narration is finished.
    for (let i = 0; i < 40 && !(await page.evaluate(() => game.HEAPU8[0x474b1])); i++) {
      await tap(225, 276);
      await tap(35, 200);
    }
    assert.equal(await page.evaluate(() => game.HEAPU8[0x474b1]), 1, 'Options opens main menu');
    await tap(120, 90);
    await page.screenshot({ path: `${output}/save-menu.png` });
    await tap(120, 32);
    await chooseFirstPopupItem();
    await page.waitForTimeout(2000);
    const saved = await saves();
    assert(Object.keys(saved).length > 0, 'Game Save writes a real save file');
    await page.waitForTimeout(1000); // Let IDBFS autoPersist settle without a manual sync.
    await launch('classic');
    assert.deepEqual(await saves(), saved, 'Saves restored automatically after reload');
    await launch('remastered');
    assert.deepEqual(await saves(), saved, 'HD restores the same saved games');
    await page.screenshot({ path: `${output}/hd-menu.png` });
    await tap(120, 55);
    await tap(120, 32);
    await chooseFirstPopupItem();
    await page.waitForTimeout(2000);
    assert.equal(await page.evaluate(() => game.HEAPU8[0x48688]), 1, 'HD loads the Original save');
    await page.screenshot({ path: `${output}/hd-loaded-scene.png` });
    // The screen filter switches on and off while playing.
    const frame = () => page.locator('#canvas').screenshot();
    const plain = await frame();
    await page.click('#power');
    await page.waitForTimeout(800);
    assert(!plain.equals(await frame()), 'Screen filter changes the rendered panel');
    await page.screenshot({ path: `${output}/hd-filter.png` });
    await page.click('#power');
    // French: same engine and scripts with text from lang/fr, chosen by ?lang= or the Home menu's flags.
    const sceneText = () => page.locator('#canvas').screenshot();
    for (const mode of ['classic', 'remastered']) {
      const shots = {};
      for (const lang of ['en', 'fr']) {
        if (mode === 'remastered') {
          await page.goto(`${base}?lcd=0`);
          await page.click(`.flag[data-lang="${lang}"]`);
          await launch(mode);
        } else {
          await launch(mode, `&lang=${lang}`);
        }
        assert.equal(logs.some(line => line.includes('overrides lang/fr/')), lang === 'fr', `${mode} ${lang} text`);
        await tap(120, 20);
        assert.equal(await page.evaluate(() => game.HEAPU8[0x48688]), 1, `${mode} ${lang} New Game`);
        await page.waitForTimeout(1500);
        shots[lang] = await sceneText();
        fs.writeFileSync(`${output}/${mode}-scene-${lang}.png`, shots[lang]);
      }
      assert(!shots.fr.equals(shots.en), `${mode} French narration differs from English`);
    }
    // The flags switch the device, Help and walkthrough at once.
    await page.goto(`${base}?lcd=0`);
    await page.click('.flag[data-lang="fr"]');
    assert.equal(await page.textContent('.today-title'), 'Choisissez une édition', 'French device text');
    assert.equal(await page.getAttribute('html', 'lang'), 'fr', 'French page language');
    await page.click('#today [data-open="help"]');
    assert(await page.isVisible('#help-doc h2:text("Jouer")'), 'French Help');
    await page.click('#helpscreen [data-open="guide"]');
    await page.waitForFunction(() => document.querySelector('#walk-doc h1')?.textContent === 'Fade : la solution pas à pas');
    assert(await page.locator('#walk-menu button').count() >= 10, 'French walkthrough chapters');
    await page.screenshot({ path: `${output}/french-walkthrough.png` });
    await page.click('#walk .ok');
    await page.screenshot({ path: `${output}/french-launcher.png` });
    await page.click('.flag[data-lang="en"]');
    assert.equal(await page.textContent('.today-title'), 'Choose an edition', 'English device text');
    await page.click('#today [data-open="guide"]');
    await page.waitForFunction(() => document.querySelector('#walk-doc h1')?.textContent === 'Fade: a step-by-step walkthrough');
    await page.click('#walk .ok');
    assert.equal(await page.getAttribute('.flag[data-lang="en"]', 'aria-checked'), 'true', 'English flag pressed again');
    await page.screenshot({ path: `${output}/launcher.png` });
    // The device's direction pad sends the game's arrow keys.
    const keys = [];
    page.on('console', m => { if (m.text().includes('key down')) keys.push(m.text()); });
    await page.goto(`${base}?edition=classic&trace=1`);
    await page.waitForFunction(() => window.game?.HEAPU8?.[0x474b1] === 1, null, { timeout: 180000 });
    const pad = page.locator('.dpad .down');
    await pad.dispatchEvent('pointerdown', { pointerId: 1 });
    await page.waitForTimeout(200);
    await pad.dispatchEvent('pointerup', { pointerId: 1 });
    await page.waitForTimeout(500);
    assert(keys.some(k => k.includes('vk 0x28')), 'Direction pad reaches the game as VK_DOWN');
    // The walkthrough opens on the device's screen with a chapter menu; the d-pad scrolls it.
    await page.click('.keys [data-action="guide"]');
    await page.waitForFunction(() => document.querySelectorAll('#walk-menu button').length >= 10);
    const screen = await page.locator('#screen').boundingBox();
    const walk = await page.locator('#walk').boundingBox();
    assert(Math.abs(walk.x - screen.x) < 2 && Math.abs(walk.width - screen.width) < 2, 'Walkthrough fills the device screen');
    await pad.dispatchEvent('pointerdown', { pointerId: 1 });
    await pad.dispatchEvent('pointerup', { pointerId: 1 });
    assert(await page.evaluate(() => document.querySelector('#walk-doc').scrollTop) > 0, 'Direction pad scrolls the walkthrough');
    await page.click('#walk .ok');
    // Fullscreen puts the device away and fits the 3:4 game to the display.
    // Home asks in a Pocket PC balloon, not a browser dialog; No keeps playing.
    page.on('dialog', d => { errors.push(`browser dialog: ${d.message()}`); d.dismiss(); });
    await page.click('.keys [data-action="home"]');
    await page.waitForSelector('#notify:not([hidden])');
    await page.click('#notify-actions button:last-child');
    assert(await page.isHidden('#notify') && await page.isVisible('#canvas'), 'No keeps the game running');
    await page.click('.keys [data-action="fullscreen"]');
    await page.waitForTimeout(800);
    const box = await page.locator('#canvas').boundingBox();
    const view = page.viewportSize();
    assert(Math.abs(Math.min(view.width / 240, view.height / 320) * 320 - box.height) < 2, 'Fullscreen game fills the display');
    assert(box.y >= 0 && box.y + box.height <= view.height + 1, 'Fullscreen game is entirely on screen');
    assert(!(await page.locator('.keys').isVisible()), 'Fullscreen hides the device');
    await page.screenshot({ path: `${output}/fullscreen.png` });
    await page.click('.dock [data-action="fullscreen"]');
    // Home then Yes returns to the edition menu. Both editions' parts were stored, so a repeat
    // visit needs no download, and the menu offers a backup of the saved games.
    await page.click('.keys [data-action="home"]');
    await page.click('#notify-actions button:first-child');
    await page.waitForURL(url => !url.search);
    await page.waitForFunction(() => document.querySelector('#size-remastered').textContent === 'Stored on this device');
    await page.waitForFunction(() => !document.querySelector('#backup').disabled);
    const [download] = await Promise.all([page.waitForEvent('download'), page.click('#backup')]);
    const backup = JSON.parse(fs.readFileSync(await download.path(), 'utf8'));
    assert.deepEqual(Object.keys(backup.files).filter(n => n.startsWith('save/')).sort(), Object.keys(saved).map(n => `save/${n}`).sort(),
      'Edition menu backs up the stored saves');
    // Restore: wipe this browser's saves, load the backup back, and the game sees the same files.
    await page.evaluate(() => new Promise(r => { const q = indexedDB.deleteDatabase('/saves'); q.onsuccess = q.onerror = q.onblocked = r; }));
    await page.reload();
    await page.waitForFunction(() => document.querySelector('#saves-count').textContent === 'No saved games yet');
    await page.setInputFiles('#restore-file', await download.path());
    await page.waitForSelector('#notify:not([hidden])');
    await page.click('#notify-actions button:first-child');
    await page.waitForFunction(() => document.querySelector('#notify-text').textContent.startsWith('Restored'));
    await page.click('#notify-actions button');
    await launch('classic');
    assert.deepEqual(await saves(), saved, 'Restored backup is the game\'s saves');
    assert.deepEqual(errors, [], 'No runtime errors or browser dialogs');
    assert.deepEqual(errors, [], 'No runtime errors during gameplay or save loading');
    console.log('PASS: launcher, Classic/Remastered menus, French text, gameplay, actual save, reload persistence, cross-edition loading, screen filter, hardware buttons, in-screen walkthrough, Home balloon, fullscreen, stored downloads, save backup and restore from the edition menu');
  } finally {
    await browser.close();
  }
})().catch(err => { console.error(err); process.exitCode = 1; });
