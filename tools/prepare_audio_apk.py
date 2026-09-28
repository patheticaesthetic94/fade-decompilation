#!/usr/bin/env python3
"""Replace staged legacy sounds with a complete, verified remastered WAV pack."""
import hashlib
import json
import os
from pathlib import Path
import shutil
import wave

from prepare_hd_apk import mangle

ROOT = Path(__file__).resolve().parent.parent


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    stage = ROOT / 'build/android-assets'
    pack = Path(os.environ.get('FADE_AUDIO_PACK', 'hd-audio'))
    if not pack.is_absolute():
        pack = ROOT / pack
    manifest = json.loads((pack / 'manifest.json').read_text())
    sources = ROOT / 'extracted/Sounds'
    expected = set(manifest['assets'])
    encoded = {mangle('Sounds/' + name) for name in expected}
    originals = {p.relative_to(ROOT / 'extracted').as_posix()
                 for p in sources.rglob('*') if p.is_file()}
    if not expected or encoded != originals:
        raise ValueError('Remastered audio manifest must cover the complete original inventory')
    generated = {p.relative_to(pack / 'Sounds').as_posix()
                 for p in (pack / 'Sounds').rglob('*.wav')}
    if generated != expected:
        raise ValueError('Remastered audio files must cover the complete source inventory')
    index = {line.lower() for line in (stage / 'fade/files.txt').read_text().splitlines()}
    replacements = []
    # Validate the entire pack before replacing any staged sound.
    for name in sorted(expected):
        record = manifest['assets'][name]
        source = ROOT / 'extracted' / mangle('Sounds/' + name)
        output = pack / 'Sounds' / name
        target_rel = mangle('Sounds/' + name)
        target = stage / 'fade' / target_rel
        if target_rel.lower() not in index or not target.is_file():
            raise ValueError(f'Missing legacy sound destination: {name}')
        if record['status'] != 'complete' or digest(source) != record['source_sha256']:
            raise ValueError(f'Incomplete or stale audio source: {name}')
        if digest(output) != record['output_sha256']:
            raise ValueError(f'Remastered audio hash mismatch: {name}')
        with wave.open(str(output), 'rb') as wav:
            if (wav.getframerate() != 48000 or wav.getsampwidth() != 2 or
                    wav.getcomptype() != 'NONE' or
                    wav.getnchannels() != record['channels'] or
                    wav.getnframes() != record['output_frames'] or
                    wav.getnframes() != round(record['source_frames'] * 48000 / record['source_rate'])):
                raise ValueError(f'Invalid remastered WAV format or duration: {name}')
        replacements.append((output, target))
    for output, target in replacements:
        shutil.copy2(output, target)
    dest = stage / 'audio'
    dest.mkdir(exist_ok=True)
    (dest / 'provenance.json').write_text(json.dumps({
        'pack': os.path.relpath(pack, ROOT),
        'manifest_sha256': digest(pack / 'manifest.json'),
        'settings': manifest['settings'],
        'assets': {name: {'output_sha256': manifest['assets'][name]['output_sha256'],
                          'packaged_path': 'fade/' + mangle('Sounds/' + name)}
                   for name in sorted(expected)},
    }, indent=2) + '\n')
    print(f'Remastered APK audio: {len(replacements)} verified 48 kHz PCM16 effects')


if __name__ == '__main__':
    main()
