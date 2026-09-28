#!/usr/bin/env python3
"""Stage the verified 4x artwork pack for the HD edition."""
import hashlib
import json
import os
from pathlib import Path
import shutil

ROOT = Path(__file__).resolve().parent.parent


def mangle(path):
    p = Path(path)
    stem = p.stem.upper().replace('É', '1')
    stem = stem[:1] + ''.join(chr((ord(c)-65+4) % 26+65) if 'A' <= c <= 'Z' else c
                             for c in stem[1:])
    extension = '.IFV' if p.suffix.lower() == '.wav' else '.IF' + p.suffix[1].upper()
    return str(p.with_name(stem + extension))



def main():
    stage = ROOT / 'build/android-assets'
    pack = Path(os.environ.get('FADE_HD_PACK', ROOT / 'hd-assets'))
    if not pack.is_absolute():
        pack = ROOT / pack
    manifest = json.loads((pack / 'manifest.json').read_text())
    if manifest['scale'] != 4:
        raise ValueError('HD renderer requires a 4x pack')
    lines = []
    for name, asset in sorted(manifest['assets'].items()):
        if asset['method'] == 'skip':
            continue
        if asset['status'] != 'complete':
            raise ValueError(f'Incomplete asset: {name}')
        rel = asset['output']
        source = pack / rel
        if hashlib.sha256(source.read_bytes()).hexdigest() != asset['output_sha256']:
            raise ValueError(f'HD hash mismatch: {name}')
        target = stage / 'hd' / rel
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source, target)
        # Match MangleAssetPath, including accented names and callers using .ifj.
        lines.append(mangle(name).lower()+'\t'+rel)
    (stage / 'hd/files.txt').write_text('\n'.join(sorted(lines))+'\n')
    print(f'HD APK resources: {len(lines)} images; runtime outline fonts')


if __name__ == '__main__':
    main()
