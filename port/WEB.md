# Browser port and GitHub Pages

The web player compiles the recovered game and SDL2 platform layer into one
WebAssembly engine. The page shows a recreated Pocket PC; its screen first shows
a Today-style launcher where the player picks an edition:

- **Classic**: original 240 × 320 artwork, bitmap fonts and sounds (about 8 MB to download).
- **Remastered**: the 4× artwork, Comic Neue / Arimo outline fonts and the verified
  48 kHz sound pack (about 90 MB more, downloaded only when chosen).

The engine reads `FADE_EDITION=classic|remastered` before loading media.

## Downloads

- For the web, `tools/stage_assets.py --hd-jpeg 92` re-encodes the 4× artwork as
  4:4:4 JPEG. That is 70 MB instead of 379 MB of PNG, at about 45 dB mean PSNR. The
  runtime takes alpha from the original's colour key, so only RGB is stored. Pillow's
  `optimize` is off because stb_image 2.30 rejects its Huffman tables. Android keeps
  the lossless PNGs.
- `tools/pack_web_data.py` cuts each pack into parts of at most 8 MiB, named by
  content hash. It gzips a part when that saves at least 10% (most of Classic). The
  player downloads four parts at a time and inflates them with `DecompressionStream`.
- Each part is stored in Cache Storage as it arrives, so an interrupted download
  resumes. The player asks for persistent storage. Later visits start without the
  network, and the launcher then reads "Stored on this device". Parts that are no
  longer listed in `packs.json` are deleted.

## Fullscreen

The Fullscreen button puts the device away and scales the 3:4 game to fill the
display, keeping its shape on a black background. A dock offers Home, Walkthrough, screen filter, Help and exit. On desktop it sits at the top right and appears when the pointer moves. On phones and touch screens it is always shown, centred along the bottom and clear of the status bar, and the game is fitted above it.
Browsers without the Fullscreen API (iPhone Safari) get the same layout inside the
browser window.

## Local build

Install and activate Emscripten **4.0.15**, then source its `emsdk_env.sh`.
Python 3 and the tracked `decomp/` sources are required; Ghidra and the Android
SDK are unnecessary. Emscripten downloads its pinned SDL2 port on first use.

```sh
python3 -m pip install pillow   # for --hd-jpeg
python3 tools/stage_assets.py --output build/web-assets --hd-jpeg 92
source build/emsdk/emsdk_env.sh
tools/web_build.sh
python3 -m http.server 8000 --directory build/web
```

Open `http://localhost:8000`. Serve over HTTP; opening the HTML file directly will
not load WebAssembly or data. `tools/stage_assets.py` is shared with the Android
build. It stages `extracted/`, `hd-assets/` and `hd-audio/`, and validates every
Remastered image and sound against its manifest hash. Use `--hd-pack` or
`--audio-pack` (or `FADE_HD_PACK` / `FADE_AUDIO_PACK`) to select other complete
packs. `tools/pack_web_data.py` splits the stage into the two downloads plus
`data/packs.json` (parts and file offsets) and extracts the launcher wallpaper.
Set `FADE_WEB_ASSETS` to build from a different staged directory.

URL options: `?edition=classic` or `?edition=remastered` starts an edition directly,
`?lcd=1` / `?lcd=0` sets the screen filter, and `&trace` logs engine details to the
browser console. Older `play.html?version=…` links redirect to the matching edition.

## Publish on GitHub Pages

The repository is [patheticaesthetic94/fade-decompilation](https://github.com/patheticaesthetic94/fade-decompilation).
Its `extracted/`, `hd-assets/`, `hd-audio/` and fonts are tracked, so CI stages
both editions directly from the repository.

In **Settings → Pages → Build and deployment → Source**, choose **GitHub Actions**.
Run **Build and deploy browser games** from Actions (or push to `main`). The
workflow stages and validates media, installs pinned Emscripten, builds the player,
runs the browser regression, checks the site is below Pages' 1 GB limit and
deploys `build/web`. All paths are relative, so repository subpaths and custom
domains both work. The site is https://patheticaesthetic94.github.io/fade-decompilation/.

## The device and its controls

The Pocket PC is drawn in CSS. It is zoomed so that the top of the case (speaker grille and
LED) and its bottom curve fall outside the window, while the screen, direction pad and buttons stay in
view. One game pixel is `--u`. Clicking or tapping the screen uses the original game
coordinates. The direction pad sends the arrow keys and Enter, and the keyboard
works too. The game itself only reads up and down, which scroll the text panel and
step through dialogue. Left and right only feed its hidden cheat sequences, and it
ignores the action, A/B/C and Start buttons. The four front
buttons are:

- **Home** returns to the edition menu. While a game is loaded it first asks in a
  Pocket PC notification balloon, because unsaved progress will be lost.
- **Walkthrough**.
- **Fullscreen** hides the device and scales the game to the display. A small dock
  then offers the same actions, plus the filter.
- **Help**.

The switch on the right edge turns the screen filter on and off, and so does a
checkbox in Help. The edition menu shows how many games are saved and downloads a
JSON backup. Without a running game it reads IDBFS's IndexedDB store
(`/saves`, `FILE_DATA`) directly.

The walkthrough and help open on the device's own screen, over the launcher or the
running game. They use the same Pocket PC look: a title bar with an **ok** button, a
scrolling document and a command bar. The walkthrough's **Contents** menu lists its
chapters. `walkthrough.html` is fetched on first open, and its `<main>` content is
restyled. While either screen is open, the keyboard and direction pad scroll it
instead of reaching the game. The action button, Enter or Escape close it.

## Pocket PC screen filter

`port/src/lcd.c` simulates a 2001 3.8" 240 × 320 transflective TFT (about 105 ppi)
on both web and Android. Each frame is reduced to the panel's grid (Remastered
averages each 4 × 4 block), quantised to RGB565, desaturated to about 78%, mapped
to a raised black level and a cool, dim white point, shaded by a front light that
enters from the top edge, and blended with the previous frame (about 35 ms
response). It is then drawn at 4× with vertical RGB stripes and the black matrix
between cells. On the web `port_set_lcd()` switches it while playing; on Android it
is a launcher option.

## Saves

Use the game's Save command. `/saves` is restored from IndexedDB before WinMain
starts; IDBFS automatically persists closed/written saves and registry settings.
Both editions use the same store. Allow a moment after saving for the browser to
finish persisting changes. Clearing browser site data deletes saves; private
browsing may restrict persistence. The edition menu downloads a JSON backup of all save files. Audio may require a tap on the screen because browsers gate audio behind
user gestures.

## Implementation

Wasm32 naturally matches the recovered ILP32 types. `--global-base=4194304`
reserves the lower 4 MiB of linear memory for the original PE image at `0x10000`.
The heap uses ordinary wasm allocations, and the game runs on the browser thread
with a 16 MiB stack. Asyncify preserves WinMain's blocking message loop, timers,
animations and synchronous sound waits across browser event turns. No pthreads,
SharedArrayBuffer, service worker or custom cross-origin headers are required.
Downloaded packs are mounted into MEMFS without copying (`FS.createDataFile` owns
slices of the reassembled pack buffer).

`tools/validate_web.py` checks page files, the wasm header, both packs against
`packs.json` and total deployment size. The workflow also runs `tools/tests/web.cjs`
in Chromium: the launcher, both editions' menus, gameplay, real game saves,
restoration after reload, loading a Classic save in Remastered, switching the
filter while playing, the direction pad reaching the game, the in-screen walkthrough, the Home balloon, fullscreen sizing,
stored downloads on a repeat visit and the edition menu's save backup. Run it locally with:

```sh
npm install --prefix build/web-test playwright@1.63.0
build/web-test/node_modules/.bin/playwright install chromium
NODE_PATH=build/web-test/node_modules node tools/tests/web.cjs
```

The local HTTP server must be running. Set `FADE_BROWSER_PATH` to use an
installed Chromium executable or `FADE_WEB_TEST_URL` to test another site.
Full campaign completion and browsers other than the tested Chromium version
remain unverified.
