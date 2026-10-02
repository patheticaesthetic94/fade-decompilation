#!/usr/bin/env python3
"""Pack staged game data (tools/stage_assets.py) into the web player's two downloads.

classic.data:     fade/ (needed by both editions)
remastered.data:  hd/, fonts/, hdaudio/ (fetched only when Remastered is chosen)
Each NAME.data is the files concatenated; packs.json lists [path, offset, size] per file and
a content hash, which the player uses to version its offline cache.
Also writes today.jpg, the menu artwork used as the launcher's wallpaper.
"""
import hashlib
import json
from pathlib import Path
import sys

PACKS = {'classic': ['fade'], 'remastered': ['hd', 'fonts', 'hdaudio']}


def main():
    stage, out = Path(sys.argv[1]), Path(sys.argv[2])
    out.mkdir(parents=True, exist_ok=True)
    index = {}
    for name, roots in PACKS.items():
        files, offset, sha = [], 0, hashlib.sha256()
        with open(out / f'{name}.data', 'wb') as data:
            for root in roots:
                for p in sorted((stage / root).rglob('*')):
                    if not p.is_file():
                        continue
                    blob = p.read_bytes()
                    rel = p.relative_to(stage).as_posix()
                    data.write(blob)
                    sha.update(rel.encode() + b'\0' + blob)
                    files.append([rel, offset, len(blob)])
                    offset += len(blob)
        if not files:
            raise SystemExit(f'No staged files for {name} in {stage}')
        index[name] = {'data': f'{name}.data', 'size': offset, 'hash': sha.hexdigest()[:16], 'files': files}
        print(f'{name}: {len(files)} files, {offset / 2**20:.1f} MiB')
    (out / 'packs.json').write_text(json.dumps(index, separators=(',', ':')))
    # Images keep a plain JPEG after their first 10 bytes, which are XORed with 0x4D.
    art = bytearray((stage / 'fade/Menu/MIRY FEGOKVSYRH.IFJ').read_bytes())
    art[:10] = bytes(b ^ 0x4d for b in art[:10])
    (out.parent / 'today.jpg').write_bytes(art)


if __name__ == '__main__':
    main()
