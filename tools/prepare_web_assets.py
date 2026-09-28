#!/usr/bin/env python3
"""Stage independent Original/HD browser packs and a Pages release bundle."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import tarfile

def mangle(path):
    p = Path(path)
    stem = p.stem.upper().replace('É', '1')
    stem = stem[:1] + ''.join(chr((ord(c)-65+4) % 26+65) if 'A' <= c <= 'Z' else c for c in stem[1:])
    extension = '.IFV' if p.suffix.lower() == '.wav' else '.IF' + p.suffix[1].upper()
    return str(p.with_name(stem + extension))

ROOT = Path(__file__).resolve().parents[1]


def prepare(output, hd_pack, audio_pack):
    source = ROOT / 'extracted'
    # Never let a misconfigured output remove the checkout or source packs.
    for protected in (ROOT, source, hd_pack, audio_pack):
        if protected and (output == protected or output in protected.parents):
            raise ValueError(f'Output would overwrite source data: {output}')
    if not (source / 'Fade.exe').is_file():
        raise ValueError('Missing extracted/Fade.exe. Run tools/extract_cab.py first.')
    if output.exists():
        shutil.rmtree(output)
    for mode in ('normal', 'hd'):
        stage = output / mode
        fade = stage / 'fade'
        for p in sorted(source.rglob('*')):
            if not p.is_file() or p.name.startswith('_cab_header') or p.name == 'gamma.exe':
                continue
            target = fade / p.relative_to(source)
            target.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(p, target)
        if mode == 'hd':
            manifest = json.loads((hd_pack / 'manifest.json').read_text())
            if manifest['scale'] != 4:
                raise ValueError('HD pack must be 4x')
            lines = []
            for name, asset in sorted(manifest['assets'].items()):
                if asset['method'] == 'skip':
                    continue
                if asset['status'] != 'complete':
                    raise ValueError(f'Incomplete HD image: {name}')
                rel = Path(asset['output'])
                if rel.is_absolute() or '..' in rel.parts:
                    raise ValueError(f'Invalid HD path: {rel}')
                image = hd_pack / rel
                if hashlib.sha256(image.read_bytes()).hexdigest() != asset['output_sha256']:
                    raise ValueError(f'HD hash mismatch: {name}')
                target = stage / 'hd' / rel
                target.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(image, target)
                lines.append(mangle(name).lower() + '\t' + rel.as_posix())
            (stage / 'hd/files.txt').write_text('\n'.join(sorted(lines)) + '\n')
            shutil.copytree(ROOT / 'port/resources/fonts', stage / 'fonts')
            (stage / 'fonts/runtime.txt').write_text('Web HD runtime outline fonts; scale 4\n')
            shutil.rmtree(fade / 'Fonts', ignore_errors=True)
            if audio_pack:
                audio = json.loads((audio_pack / 'manifest.json').read_text())['assets']
                expected = {mangle('Sounds/' + name) for name in audio}
                original = {p.relative_to(source).as_posix() for p in (source / 'Sounds').rglob('*') if p.is_file()}
                if not audio or expected != original:
                    raise ValueError('Enhanced sound pack must cover all original sounds')
                for name, record in sorted(audio.items()):
                    sound = audio_pack / 'Sounds' / name
                    rel = mangle('Sounds/' + name)
                    if (record['status'] != 'complete' or
                        hashlib.sha256((source / rel).read_bytes()).hexdigest() != record['source_sha256'] or
                        hashlib.sha256(sound.read_bytes()).hexdigest() != record['output_sha256']):
                        raise ValueError(f'Enhanced sound hash mismatch: {name}')
                    shutil.copy2(sound, fade / rel)
        (fade / 'files.txt').write_text(''.join(
            p.relative_to(fade).as_posix() + '\n' for p in sorted(fade.rglob('*'))
            if p.is_file() and p.name != 'files.txt'))
        print(f'{mode}: {sum(p.stat().st_size for p in stage.rglob("*") if p.is_file()) / 2**20:.1f} MiB')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--hd-pack', type=Path, default=Path(os.environ.get(
        'FADE_HD_PACK', ROOT / ('hd-assets' if (ROOT / 'hd-assets').exists() else 'build/hd-upscayl-high-fidelity-compressed'))))
    parser.add_argument('--audio-pack', type=Path, default=Path(os.environ.get(
        'FADE_AUDIO_PACK', ROOT / ('hd-audio' if (ROOT / 'hd-audio').exists() else 'build/remastered-audio-flashsr'))))
    parser.add_argument('--original-audio', action='store_true', help='Use original sounds in HD too')
    parser.add_argument('--output', type=Path, default=ROOT / 'build/web-assets')
    parser.add_argument('--bundle', type=Path, help='Also write a gzip tar for the web-assets GitHub release')
    args = parser.parse_args()
    prepare(args.output.resolve(), args.hd_pack.resolve(), None if args.original_audio else args.audio_pack.resolve())
    if args.bundle:
        args.bundle.parent.mkdir(parents=True, exist_ok=True)
        with tarfile.open(args.bundle, 'w:gz') as archive:
            for mode in ('normal', 'hd'):
                archive.add(args.output / mode, arcname=mode)
        print(f'Release bundle: {args.bundle}')


if __name__ == '__main__':
    main()
