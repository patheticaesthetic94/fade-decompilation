# Browser port and GitHub Pages

The Original and HD editions compile the recovered game and SDL2 platform layer
into WebAssembly. The landing page lets players choose an edition; only that
edition's data is downloaded. Original retains the bitmap artwork and fonts.
HD uses the selected 4× pack with Comic Neue / Arimo outline fonts and the
verified enhanced sound pack. Original uses the legacy sounds.

## Local build

Install and activate Emscripten **4.0.15**, then source its `emsdk_env.sh`.
Python 3 and the tracked `decomp/` sources are required; Ghidra and the Android
SDK are unnecessary. Emscripten downloads its pinned SDL2 port on first use.

```sh
python3 tools/prepare_web_assets.py
source build/emsdk/emsdk_env.sh
tools/web_build.sh
python3 -m http.server 8000 --directory build/web
```

Open `http://localhost:8000`. Serve over HTTP; opening the HTML file directly
will not load WebAssembly/data. The default HD pack is `hd-assets/` when present, otherwise
`build/hd-upscayl-high-fidelity-compressed`; pass `--hd-pack PATH` or set
`FADE_HD_PACK` to select another complete 4× manifest. Preparation reads
`extracted/` and validates every HD image's SHA-256 before staging it. Outputs
live under `build/web-assets`, and do not modify Android's staged resources.
Enhanced sounds default to `hd-audio/`, or the local
`build/remastered-audio-flashsr` pack. Use `--audio-pack PATH` to override, or
`--original-audio` for legacy sound in both editions. An optional prepared bundle
can be extracted there instead. Set `FADE_WEB_ASSETS`
to build from a different prepared directory.

## Publish on GitHub Pages

The repository is [patheticaesthetic94/fade-decompilation](https://github.com/patheticaesthetic94/fade-decompilation).
Its `extracted/`, `hd-assets/`, `hd-audio/` and fonts are tracked, so CI prepares
both editions directly from the repository. No release bundle is required.

In **Settings → Pages → Build and deployment → Source**, choose **GitHub Actions**.
Run **Build and deploy browser games** from Actions (or push to `main`). The
workflow prepares and validates media, installs pinned Emscripten, builds both
editions, checks the site is below Pages' 1 GB limit and deploys `build/web`.
All paths are relative, so repository subpaths and custom domains both work.

The expected site URL is https://patheticaesthetic94.github.io/fade-decompilation/.
The workflow's deployment output confirms the actual live URL.

## Walkthrough while playing

The player toolbar's **Walkthrough** button opens the full guide alongside the
canvas on desktop, or below it on smaller screens. Its independently scrolling
panel keeps its position when closed and reopened. The panel remains available
in fullscreen, and **Open guide in a new tab** offers a separate reading window.
The guide includes chapter links, puzzle solutions, checkpoints and story spoilers.

## Controls and saves

Click/tap uses the original game coordinates. Arrow keys and Enter/Z, X, C map
to the Pocket PC hardware buttons. Fullscreen is optional.
Use the game's Save command. `/saves` is restored from IndexedDB before WinMain
starts; IDBFS automatically persists closed/written saves and registry settings.
Original and HD use the same store on the same origin. Allow a moment after
saving for the browser to finish persisting changes. Clearing browser site
data deletes it; private browsing may restrict persistence. The player can
also download a JSON backup of all save files. Audio may require tapping the
canvas after a download because browsers gate audio behind user gestures.

## Implementation

Wasm32 naturally matches the recovered ILP32 types. `--global-base=4194304`
reserves the lower 4 MiB of linear memory for the original PE image at `0x10000`.
The heap uses ordinary wasm allocations, and the game runs on the browser thread
with a 16 MiB stack. Asyncify preserves WinMain's blocking message loop, timers,
animations and synchronous sound waits across browser event turns. No pthreads,
SharedArrayBuffer, service worker or custom cross-origin headers are required.
The same engine is linked with a separate preload package for each edition.

`tools/validate_web.py` checks outputs, wasm headers, and total deployment size.
The workflow also runs `tools/tests/web.cjs` in Chromium to exercise menus,
gameplay, real game saves, automatic restoration after reload, and loading an
Original save in HD. Run it locally with:

```sh
npm install --prefix build/web-test playwright@1.63.0
build/web-test/node_modules/.bin/playwright install chromium
NODE_PATH=build/web-test/node_modules node tools/tests/web.cjs
```

The local HTTP server must be running. Set `FADE_BROWSER_PATH` to use an
installed Chromium executable or `FADE_WEB_TEST_URL` to test another site.
Append `&trace` to the player URL for detailed engine logs in the browser console.
Full campaign completion and browsers other than the tested Chromium version
remain unverified.
