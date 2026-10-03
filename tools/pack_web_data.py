#!/usr/bin/env python3
"""Pack staged game data (tools/stage_assets.py) into the web player's two downloads.

classic:     fade/ (needed by both editions)
remastered:  hd/, fonts/, hdaudio/ (fetched only when Remastered is chosen)
Each pack is its files concatenated, then cut into parts of at most 8 MiB so the player can
download several at once and cache them one by one (an interrupted download resumes). A part is
gzipped when that saves at least 10%; the player inflates it with DecompressionStream. Part names
carry their content hash, so they never change once published. packs.json lists the parts and
[path, offset, size] for every file.
Also writes today.jpg, the menu artwork used as the launcher's wallpaper.
"""
import gzip
import hashlib
import json
from pathlib import Path
import sys

PACKS = {'classic': ['fade'], 'remastered': ['hd', 'fonts', 'hdaudio']}
PART = 8 << 20


def main():
    stage, out = Path(sys.argv[1]), Path(sys.argv[2])
    out.mkdir(parents=True, exist_ok=True)
    for old in out.glob('*.bin'):
        old.unlink()
    index = {}
    for name, roots in PACKS.items():
        files, blob = [], bytearray()
        for root in roots:
            for p in sorted((stage / root).rglob('*')):
                if p.is_file():
                    files.append([p.relative_to(stage).as_posix(), len(blob), p.stat().st_size])
                    blob += p.read_bytes()
        if not files:
            raise SystemExit(f'No staged files for {name} in {stage}')
        parts = []
        for start in range(0, len(blob), PART):
            raw = bytes(blob[start:start + PART])
            packed = gzip.compress(raw, 9, mtime=0)
            gz = len(packed) <= len(raw) * 0.9
            body = packed if gz else raw
            digest = hashlib.sha256(body).hexdigest()[:16]
            file = f'{name}-{len(parts):02d}-{digest}.bin'
            (out / file).write_bytes(body)
            parts.append({'file': file, 'size': len(raw), 'bytes': len(body), 'gzip': gz})
        transfer = sum(p['bytes'] for p in parts)
        index[name] = {'size': len(blob), 'bytes': transfer, 'parts': parts, 'files': files}
        print(f'{name}: {len(files)} files, {len(blob) / 2**20:.1f} MiB in {len(parts)} parts, '
              f'{transfer / 2**20:.1f} MiB to download')
    (out / 'packs.json').write_text(json.dumps(index, separators=(',', ':')))
    # Images keep a plain JPEG after their first 10 bytes, which are XORed with 0x4D.
    art = bytearray((stage / 'fade/Menu/MIRY FEGOKVSYRH.IFJ').read_bytes())
    art[:10] = bytes(b ^ 0x4d for b in art[:10])
    (out.parent / 'today.jpg').write_bytes(art)


if __name__ == '__main__':
    main()
