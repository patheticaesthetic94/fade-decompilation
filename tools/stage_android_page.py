#!/usr/bin/env python3
"""Stage the web player's page for the Android app: build/android-assets/web/.

The app shows web/index.html, site.css, player.js and the walkthroughs in a WebView around the native
game (port/android, Assets.java), so it needs the page but not the WebAssembly engine or data packs.
today.jpg (the Home wallpaper) is the menu artwork, decoded as tools/pack_web_data.py does for the site.
Run after tools/stage_assets.py, which provides fade/.
"""
from pathlib import Path
import shutil
import sys

ROOT = Path(__file__).resolve().parent.parent
PAGE = ['index.html', 'site.css', 'player.js', 'fade-icon.png', 'walkthrough.html', 'walkthrough.fr.html']


def main():
    stage = Path(sys.argv[1]) if len(sys.argv) > 1 else ROOT / 'build/android-assets'
    out = stage / 'web'
    shutil.rmtree(out, ignore_errors=True)
    out.mkdir(parents=True)
    for name in PAGE:
        shutil.copy2(ROOT / 'web' / name, out / name)
    # Images keep a plain JPEG after their first 10 bytes, which are XORed with 0x4D.
    art = bytearray((stage / 'fade/Menu/MIRY FEGOKVSYRH.IFJ').read_bytes())
    art[:10] = bytes(b ^ 0x4d for b in art[:10])
    (out / 'today.jpg').write_bytes(art)
    print(f'Player page staged: {len(PAGE) + 1} files -> {out}')


if __name__ == '__main__':
    main()
