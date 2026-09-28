#!/usr/bin/env python3
"""Check a deployable Pages site, including both wasm/data outputs and size."""
from pathlib import Path
import sys

site = Path(sys.argv[1] if len(sys.argv) > 1 else 'build/web')
for name in ('index.html', 'play.html', 'site.css', 'player.js', 'walkthrough.html', 'walkthrough.md', '.nojekyll'):
    assert (site / name).is_file(), f'Missing {name}'
for mode in ('normal', 'hd'):
    for suffix in ('js', 'wasm', 'data'):
        path = site / mode / ('fade.' + suffix)
        assert path.is_file() and path.stat().st_size > 0, f'Missing {path}'
    assert (site / mode / 'fade.wasm').read_bytes()[:4] == b'\0asm'
assert not any(p.is_symlink() for p in site.rglob('*')), 'Pages artifact cannot contain symlinks'
size = sum(p.stat().st_size for p in site.rglob('*') if p.is_file())
assert size < 1_000_000_000, f'Pages site exceeds 1 GB: {size}'
print(f'PASS: Original and HD Pages site, {size / 2**20:.1f} MiB')
