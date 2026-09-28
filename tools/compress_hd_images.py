#!/usr/bin/env python3
"""Losslessly optimize generated PNG packs into separate, validated copies.

Requires Pillow and pyoxipng. Defaults to build/hd-assets; --all processes
every build/hd* directory containing PNGs. Originals are never overwritten.
"""
import argparse
from concurrent.futures import ThreadPoolExecutor
from io import BytesIO
import json
from pathlib import Path
import shutil

from PIL import Image
import oxipng
from upscale_assets import atomic_json, digest

ROOT = Path(__file__).resolve().parents[1]


def pixels(data):
    with Image.open(BytesIO(data)) as im:
        im.load()
        if getattr(im, 'n_frames', 1) != 1:
            raise ValueError('animated PNG requires a frame-aware optimizer')
        # Include hidden RGB under fully transparent pixels in the comparison.
        return im.size, im.convert('RGBA').tobytes()


def compress(source, destination, level):
    raw = source.read_bytes()
    candidate = oxipng.optimize_from_memory(raw, level=level, optimize_alpha=False)
    if pixels(raw) != pixels(candidate):
        raise ValueError(f'{source}: decoded RGBA pixels changed')
    result = candidate if len(candidate) < len(raw) else raw
    destination.parent.mkdir(parents=True, exist_ok=True)
    temporary = destination.with_suffix('.png.tmp')
    temporary.write_bytes(result)
    if pixels(temporary.read_bytes()) != pixels(raw):
        raise ValueError(f'{destination}: written pixels changed')
    temporary.replace(destination)
    return {'input_bytes': len(raw), 'output_bytes': len(result),
            'input_sha256': digest(source), 'output_sha256': digest(destination),
            'pixels_identical': True}


def pack(source, output, level, workers):
    source, output = source.resolve(), output.resolve()
    if source == output or source in output.parents or output in source.parents:
        raise ValueError('source and output trees must be separate')
    files = sorted(source.rglob('*.png'))
    if not files:
        raise ValueError(f'no PNGs found in {source}')
    output.mkdir(parents=True, exist_ok=True)
    # Copy indexes, font licenses, metrics and manifests alongside the PNGs.
    for path in source.rglob('*'):
        if path.is_file() and path.suffix.lower() != '.png' and path.name not in {
                'validation.json', 'compression.json'}:
            dest = output / path.relative_to(source)
            dest.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(path, dest)
    records = {}
    def job(path):
        relative = path.relative_to(source)
        return relative.as_posix(), compress(path, output / relative, level)
    with ThreadPoolExecutor(max_workers=workers) as pool:
        for index, (name, record) in enumerate(pool.map(job, files), 1):
            records[name] = record
            if index % 100 == 0 or index == len(files):
                print(f'{source.name}: {index}/{len(files)} verified', flush=True)
    manifest_path = output / 'manifest.json'
    if manifest_path.exists():
        manifest = json.loads(manifest_path.read_text())
        for record in manifest.get('assets', {}).values():
            optimized = records.get(record.get('output'))
            if optimized:
                if record.get('output_sha256') != optimized['input_sha256']:
                    raise ValueError('source pack manifest hash mismatch')
                record['output_sha256'] = optimized['output_sha256']
                record['output_bytes'] = optimized['output_bytes']
        atomic_json(manifest_path, manifest)
    before = sum(r['input_bytes'] for r in records.values())
    after = sum(r['output_bytes'] for r in records.values())
    report = {'source': str(source), 'output': str(output), 'optimizer': 'pyoxipng',
              'level': level, 'files': len(files), 'input_bytes': before,
              'output_bytes': after, 'saved_bytes': before - after,
              'saved_percent': round(100 * (before - after) / before, 2),
              'all_pixels_identical': True, 'assets': records}
    atomic_json(output / 'compression.json', report)
    print(f'{source.name}: {before / 2**20:.2f} -> {after / 2**20:.2f} MiB '
          f'({report["saved_percent"]}% smaller)', flush=True)
    return {k: v for k, v in report.items() if k != 'assets'}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source', type=Path, default=ROOT / 'build/hd-assets')
    parser.add_argument('--output', type=Path)
    parser.add_argument('--all', action='store_true')
    parser.add_argument('--level', type=int, choices=range(7), default=2)
    parser.add_argument('--workers', type=int, default=2)
    args = parser.parse_args()
    if args.workers < 1 or (args.all and args.output):
        parser.error('workers must be positive; --all cannot use --output')
    sources = ([p for p in sorted((ROOT / 'build').glob('hd*'))
                if p.is_dir() and not p.name.endswith('-compressed')
                and next(p.rglob('*.png'), None) is not None]
               if args.all else [args.source])
    summaries = [pack(p, args.output or p.with_name(p.name + '-compressed'),
                      args.level, args.workers) for p in sources]
    if args.all:
        atomic_json(ROOT / 'build/hd-compression.json', {'packs': summaries})


if __name__ == '__main__':
    main()
