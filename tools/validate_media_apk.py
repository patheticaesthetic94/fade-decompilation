#!/usr/bin/env python3
"""Audit the APK's enhanced audio, compressed artwork, indices and native ABIs."""
import argparse
import hashlib
import io
import json
from pathlib import Path
import wave
import zipfile

from prepare_hd_apk import mangle


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--apk', type=Path, default=Path('build/fade-android-enhanced-media.apk'))
    parser.add_argument('--audio-pack', type=Path, default=Path('hd-audio'))
    parser.add_argument('--hd-pack', type=Path, default=Path('hd-assets'))
    parser.add_argument('--report', type=Path, default=Path('build/enhanced-media-apk-validation.json'))
    args = parser.parse_args()
    audio = json.loads((args.audio_pack / 'manifest.json').read_text())
    images = json.loads((args.hd_pack / 'manifest.json').read_text())
    errors, sounds, artwork = [], 0, 0
    with zipfile.ZipFile(args.apk) as apk:
        if apk.testzip() is not None:
            errors.append('APK ZIP integrity failure')
        files = set(apk.namelist())
        legacy_index = set(apk.read('assets/fade/files.txt').decode().lower().splitlines())
        hd_index = dict(line.split('\t') for line in apk.read('assets/hd/files.txt').decode().splitlines())
        for name, record in audio['assets'].items():
            try:
                path = mangle('Sounds/' + name)
                if path.lower() not in legacy_index:
                    raise ValueError('missing sound index entry')
                data = apk.read('assets/fade/' + path)
                if hashlib.sha256(data).hexdigest() != record['output_sha256']:
                    raise ValueError('enhanced audio hash mismatch')
                with wave.open(io.BytesIO(data), 'rb') as wav:
                    if (wav.getframerate() != 48000 or wav.getsampwidth() != 2 or
                            wav.getnchannels() != record['channels'] or
                            wav.getnframes() != record['output_frames']):
                        raise ValueError('enhanced WAV format mismatch')
                sounds += 1
            except (KeyError, ValueError, wave.Error) as error:
                errors.append(f'{name}: {error}')
        for name, record in images['assets'].items():
            if record['method'] == 'skip':
                continue
            try:
                if hd_index.get(mangle(name).lower()) != record['output']:
                    raise ValueError('HD filename index mismatch')
                data = apk.read('assets/hd/' + record['output'])
                if hashlib.sha256(data).hexdigest() != record['output_sha256']:
                    raise ValueError('compressed artwork hash mismatch')
                artwork += 1
            except (KeyError, ValueError) as error:
                errors.append(f'{name}: {error}')
        abis = sorted({name.split('/')[1] for name in files if name.startswith('lib/')})
        for abi in ['arm64-v8a', 'x86_64']:
            for library in ['libmain.so', 'libSDL2.so']:
                if f'lib/{abi}/{library}' not in files:
                    errors.append(f'Missing native library: {abi}/{library}')
        if 'assets/fonts/runtime.txt' not in files:
            errors.append('Missing runtime outline fonts')
        if any(name.startswith(('assets/fade/Fonts/', 'assets/hd/fonts/')) for name in files):
            errors.append('Unexpected bitmap font sheets')
        if 'assets/audio/provenance.json' not in files:
            errors.append('Missing audio provenance')
    report = {'valid': not errors, 'apk': str(args.apk),
              'size_bytes': args.apk.stat().st_size,
              'sha256': hashlib.sha256(args.apk.read_bytes()).hexdigest(),
              'audio_pack': str(args.audio_pack), 'hd_pack': str(args.hd_pack),
              'enhanced_sounds': sounds, 'audio_rate': 48000,
              'compressed_hd_images': artwork, 'abis': abis,
              'runtime_fonts': True, 'errors': errors}
    args.report.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
    return 0 if not errors else 1


if __name__ == '__main__':
    raise SystemExit(main())
