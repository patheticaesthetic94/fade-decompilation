#!/usr/bin/env python3
"""Stage the combined Classic + Remastered game data used by the APK and the web build.

Layout (paths are what the runtime opens):
  fade/      original encoded resources, bitmap fonts and sounds (Classic, and shared by both)
  hd/        verified 4x artwork plus hd/files.txt (encoded name -> PNG)
  fonts/     outline fonts, licences and runtime.txt for the native text engine
  hdaudio/   verified 48 kHz sounds under the original encoded names
The launcher picks an edition at startup (FADE_EDITION); Classic ignores hd/, fonts/ and hdaudio/.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import wave

ROOT = Path(__file__).resolve().parent.parent


def mangle(path):
    """The exe's MangleAssetPath, including accented names."""
    p = Path(path)
    stem = p.stem.upper().replace('É', '1')
    stem = stem[:1] + ''.join(chr((ord(c)-65+4) % 26+65) if 'A' <= c <= 'Z' else c for c in stem[1:])
    extension = '.IFV' if p.suffix.lower() == '.wav' else '.IF' + p.suffix[1].upper()
    return str(p.with_name(stem + extension))


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def stage_original(stage, source):
    fade = stage / 'fade'
    names = []
    for p in sorted(source.rglob('*')):
        if not p.is_file() or p.name.startswith('_cab_header') or p.name in ('gamma.exe', '.DS_Store'):
            continue
        rel = p.relative_to(source).as_posix()
        target = fade / rel
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(p, target)
        names.append(rel)
    (fade / 'files.txt').write_text(''.join(n + '\n' for n in names))
    return len(names)


def to_jpeg(png, quality):
    """Re-encode an HD image for download size. The runtime takes alpha from the original's colour key,
    so only RGB matters; 4:4:4 JPEG at q92 averages about 45 dB PSNR at under a fifth of the PNG size."""
    from io import BytesIO
    from PIL import Image
    out = BytesIO()
    # No optimize=True: stb_image 2.30 rejects Pillow's optimised Huffman tables ("bad huffman code").
    Image.open(png).convert('RGB').save(out, 'JPEG', quality=quality, subsampling=0)
    return out.getvalue()


def stage_hd(stage, pack, jpeg_quality=None):
    manifest = json.loads((pack / 'manifest.json').read_text())
    if manifest['scale'] != 4:
        raise ValueError('HD renderer requires a 4x pack')
    lines = []
    for name, asset in sorted(manifest['assets'].items()):
        if asset['method'] == 'skip':
            continue
        if asset['status'] != 'complete':
            raise ValueError(f'Incomplete HD image: {name}')
        rel = Path(asset['output'])
        if rel.is_absolute() or '..' in rel.parts:
            raise ValueError(f'Invalid HD path: {rel}')
        image = pack / rel
        if digest(image) != asset['output_sha256']:
            raise ValueError(f'HD hash mismatch: {name}')
        if jpeg_quality:
            rel = rel.with_suffix('.jpg')
        target = stage / 'hd' / rel
        target.parent.mkdir(parents=True, exist_ok=True)
        if jpeg_quality:
            target.write_bytes(to_jpeg(image, jpeg_quality))
        else:
            shutil.copy2(image, target)
        lines.append(mangle(name).lower() + '\t' + rel.as_posix())
    (stage / 'hd/files.txt').write_text('\n'.join(sorted(lines)) + '\n')
    return len(lines)


def stage_fonts(stage):
    source = ROOT / 'port/resources/fonts'
    dest = stage / 'fonts'
    dest.mkdir(parents=True, exist_ok=True)
    hashes = {}
    for p in sorted(source.iterdir()):
        if p.is_file():
            shutil.copy2(p, dest / p.name)
            hashes[p.name] = digest(p)
    (dest / 'runtime.txt').write_text('stb_truetype 1.26; Comic Neue Bold 9em; Arimo 7em; scale 4\n')
    (dest / 'provenance.json').write_text(json.dumps({
        'repository': 'https://github.com/google/fonts',
        'revision': '23e54b51ddffbc7713c583748e3bd86f62b1fa4a',
        'files_sha256': hashes,
    }, indent=2) + '\n')


def stage_audio(stage, pack, source):
    manifest = json.loads((pack / 'manifest.json').read_text())
    expected = set(manifest['assets'])
    originals = {p.relative_to(source).as_posix() for p in (source / 'Sounds').rglob('*') if p.is_file()}
    if not expected or {mangle('Sounds/' + n) for n in expected} != originals:
        raise ValueError('Remastered audio must cover the complete original sound inventory')
    for name in sorted(expected):
        record = manifest['assets'][name]
        rel = mangle('Sounds/' + name)
        output = pack / 'Sounds' / name
        if record['status'] != 'complete' or digest(source / rel) != record['source_sha256']:
            raise ValueError(f'Incomplete or stale audio source: {name}')
        if digest(output) != record['output_sha256']:
            raise ValueError(f'Remastered audio hash mismatch: {name}')
        with wave.open(str(output), 'rb') as wav:
            if (wav.getframerate() != 48000 or wav.getsampwidth() != 2 or wav.getcomptype() != 'NONE' or
                    wav.getnchannels() != record['channels'] or wav.getnframes() != record['output_frames']):
                raise ValueError(f'Invalid remastered WAV format or duration: {name}')
        target = stage / 'hdaudio' / rel
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(output, target)
    return len(expected)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--output', type=Path, default=ROOT / 'build/android-assets')
    parser.add_argument('--hd-pack', type=Path, default=Path(os.environ.get('FADE_HD_PACK', ROOT / 'hd-assets')))
    parser.add_argument('--audio-pack', type=Path, default=Path(os.environ.get('FADE_AUDIO_PACK', ROOT / 'hd-audio')))
    parser.add_argument('--hd-jpeg', type=int, metavar='QUALITY',
                        help='Re-encode HD images as JPEG (smaller web download; needs Pillow)')
    args = parser.parse_args()
    output = args.output.resolve()
    hd_pack = (ROOT / args.hd_pack).resolve()
    audio_pack = (ROOT / args.audio_pack).resolve()
    source = ROOT / 'extracted'
    # Never let a misconfigured output remove the checkout or source packs.
    for protected in (ROOT, source, hd_pack, audio_pack):
        if output == protected or output in protected.parents:
            raise ValueError(f'Output would overwrite source data: {output}')
    if not (source / 'Fade.exe').is_file():
        raise ValueError('Missing extracted/Fade.exe')
    if output.exists():
        shutil.rmtree(output)
    files = stage_original(output, source)
    images = stage_hd(output, hd_pack, args.hd_jpeg)
    stage_fonts(output)
    sounds = stage_audio(output, audio_pack, source)
    size = sum(p.stat().st_size for p in output.rglob('*') if p.is_file()) / 2**20
    print(f'Staged {output}: {files} original files, {images} HD images, {sounds} remastered sounds, {size:.1f} MiB')


if __name__ == '__main__':
    main()
