#!/usr/bin/env python3
"""Verify a complete generated HD pack against its source assets and manifest."""
import argparse
from collections import Counter
from datetime import datetime, timezone
import json
from pathlib import Path

from PIL import Image

from upscale_assets import EXTENSIONS, atomic_json, digest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source', type=Path, default=Path('assets'))
    parser.add_argument('--pack', type=Path, default=Path('hd-assets'))
    args = parser.parse_args()
    manifest = json.loads((args.pack / 'manifest.json').read_text())
    records = manifest['assets']
    expected = {p.relative_to(args.source).as_posix() for p in args.source.rglob('*')
                if p.is_file() and p.suffix.lower() in EXTENSIONS}
    errors, files, total_bytes, total_pixels = [], 0, 0, 0
    for name in sorted(expected):
        record = records.get(name)
        if record is None:
            errors.append(f'{name}: missing manifest entry')
            continue
        try:
            source = args.source / name
            if digest(source) != record['source_sha256']:
                raise ValueError('source hash differs')
            with Image.open(source) as image:
                if list(image.size) != record['original_size']:
                    raise ValueError('source dimensions differ')
            if record['method'] == 'skip':
                if record['status'] != 'skipped' or record['output'] is not None:
                    raise ValueError('invalid skipped entry')
                continue
            if record['status'] != 'complete':
                raise ValueError(f'job status is {record["status"]}')
            path = args.pack / record['output']
            if digest(path) != record['output_sha256']:
                raise ValueError('output hash differs')
            with Image.open(path) as image:
                image.load()
                expected_size = [n * manifest['scale'] for n in record['original_size']]
                if image.format != 'PNG' or list(image.size) != expected_size:
                    raise ValueError('output format or dimensions differ')
                total_pixels += image.width * image.height
            total_bytes += path.stat().st_size
            files += 1
        except (OSError, ValueError, KeyError) as error:
            errors.append(f'{name}: {error}')
    stale = sorted(set(records) - expected)
    errors.extend(f'{name}: source absent from current inventory' for name in stale)
    report = {'validated_at': datetime.now(timezone.utc).isoformat(),
              'valid': not errors, 'scale': manifest['scale'],
              'source_entries': len(expected), 'generated_files': files,
              'methods': dict(Counter(r['method'] for r in records.values())),
              'statuses': dict(Counter(r['status'] for r in records.values())),
              'png_bytes': total_bytes, 'decoded_rgba_bytes': total_pixels * 4,
              'renderer_integrated': manifest.get('renderer_integrated', False),
              'errors': errors}
    atomic_json(args.pack / 'validation.json', report)
    print(json.dumps(report, indent=2))
    return 0 if not errors else 1


if __name__ == '__main__':
    raise SystemExit(main())
