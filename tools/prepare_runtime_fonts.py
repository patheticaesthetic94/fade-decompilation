#!/usr/bin/env python3
"""Stage trusted outline fonts; omit all legacy font sheets/HD glyph atlases."""
import hashlib
import json
from pathlib import Path
import shutil

ROOT = Path(__file__).resolve().parent.parent


def main():
    stage = ROOT / 'build/android-assets'
    source = ROOT / 'port/resources/fonts'
    dest = stage / 'fonts'
    dest.mkdir(parents=True, exist_ok=True)
    hashes = {}
    for p in sorted(source.iterdir()):
        if p.is_file():
            shutil.copy2(p, dest / p.name)
            hashes[p.name] = hashlib.sha256(p.read_bytes()).hexdigest()
    (dest / 'runtime.txt').write_text('stb_truetype 1.26; Comic Neue Bold 9em; Arimo 7em; scale 4\n')
    (dest / 'provenance.json').write_text(json.dumps({
        'repository': 'https://github.com/google/fonts',
        'revision': '23e54b51ddffbc7713c583748e3bd86f62b1fa4a',
        'files_sha256': hashes,
    }, indent=2) + '\n')
    shutil.rmtree(stage / 'fade/Fonts', ignore_errors=True)
    shutil.rmtree(stage / 'hd/fonts', ignore_errors=True)
    index = stage / 'fade/files.txt'
    index.write_text(''.join(line for line in index.read_text().splitlines(keepends=True)
                             if not line.lower().startswith('fonts/')))
    print('Runtime fonts staged: two trusted outline faces, licences and provenance; no bitmap font sheets')


if __name__ == '__main__':
    main()
