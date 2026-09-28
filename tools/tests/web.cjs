// Browser regression: real menus, gameplay, save/reload, and cross-edition saves.
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
    async function launch(mode) {
      await page.goto(`${base}play.html?version=${mode}`);
      await page.click('#start');
      await page.waitForFunction(() => typeof game !== 'undefined' && game?.HEAPU8?.[0x474b1] === 1,
        null, { timeout: 120000 });
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
    await launch('normal');
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
    await launch('normal');
    assert.deepEqual(await saves(), saved, 'Saves restored automatically after reload');
    await launch('hd');
    assert.deepEqual(await saves(), saved, 'HD restores the same saved games');
    await page.screenshot({ path: `${output}/hd-menu.png` });
    await tap(120, 55);
    await tap(120, 32);
    await chooseFirstPopupItem();
    await page.waitForTimeout(2000);
    assert.equal(await page.evaluate(() => game.HEAPU8[0x48688]), 1, 'HD loads the Original save');
    await page.screenshot({ path: `${output}/hd-loaded-scene.png` });
    assert.deepEqual(errors, [], 'No runtime errors during gameplay or save loading');
    console.log('PASS: Original/HD menus, gameplay, actual save, reload persistence, cross-edition loading');
  } finally {
    await browser.close();
  }
})().catch(err => { console.error(err); process.exitCode = 1; });
