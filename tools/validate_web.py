#!/usr/bin/env python3
"""Check a deployable Pages site: page files, the engine, both data packs and total size."""
import json
from pathlib import Path
import sys

site = Path(sys.argv[1] if len(sys.argv) > 1 else 'build/web')
for name in ('index.html', 'play.html', 'site.css', 'player.js', 'today.jpg', 'fade-icon.png',
             'walkthrough.html', 'walkthrough.md', 'fade.js', 'fade.wasm', 'data/packs.json'):
    assert (site / name).is_file() and (site / name).stat().st_size > 0, f'Missing {name}'
assert (site / '.nojekyll').is_file(), 'Missing .nojekyll'
assert (site / 'fade.wasm').read_bytes()[:4] == b'\0asm'
packs = json.loads((site / 'data/packs.json').read_text())
for name in ('classic', 'remastered'):
    pack = packs[name]
    for part in pack['parts']:
        assert (site / 'data' / part['file']).stat().st_size == part['bytes'], f'{part["file"]} size mismatch'
    assert sum(p['size'] for p in pack['parts']) == pack['size'], f'{name} parts do not cover the pack'
    assert all(0 <= off and off + n <= pack['size'] for _, off, n in pack['files'])
paths = {p for _, pack in packs.items() for p, *_ in pack['files']}
for required in ('fade/Fade.exe', 'fade/files.txt', 'hd/files.txt', 'fonts/runtime.txt'):
    assert required in paths, f'Missing packed {required}'
assert not any(p.is_symlink() for p in site.rglob('*')), 'Pages artifact cannot contain symlinks'
size = sum(p.stat().st_size for p in site.rglob('*') if p.is_file())
assert size < 1_000_000_000, f'Pages site exceeds 1 GB: {size}'
print(f'PASS: Classic + Remastered Pages site, {size / 2**20:.1f} MiB')
