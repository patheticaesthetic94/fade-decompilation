#!/usr/bin/env python3
"""Create a separate 48 kHz sound pack using AudioSR or one-step FlashSR.

Uses local checkpoint/source files only. FFmpeg decodes legacy compressed WAVs.
Keeps original low-frequency content; adds model-generated upper frequencies.
Outputs preserve clip length/channels, match RMS level and avoid clipping.
"""
import argparse
import hashlib
import html
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
from urllib.parse import quote

import numpy as np
import soundfile as sf
from scipy.signal import butter, resample_poly, sosfilt

ROOT = Path(__file__).resolve().parents[1]
RATE = 48000


def digest(path):
    h = hashlib.sha256()
    with path.open('rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            h.update(block)
    return h.hexdigest()


def save_json(path, data):
    staged = path.with_suffix('.json.tmp')
    staged.write_text(json.dumps(data, indent=2) + '\n')
    staged.replace(path)


def decode(path, temporary):
    decoded = temporary / 'decoded.wav'
    subprocess.run(['ffmpeg', '-v', 'error', '-nostdin', '-y', '-i', str(path),
                    '-c:a', 'pcm_f32le', str(decoded)], check=True, capture_output=True)
    samples, rate = sf.read(decoded, dtype='float32', always_2d=True)
    if not samples.size or not np.isfinite(samples).all():
        raise ValueError('empty or non-finite source')
    return samples, rate


def rms(samples):
    return float(np.sqrt(np.mean(np.square(samples, dtype=np.float64))))


def load_model(pipeline, checkpoint, device):
    import gc
    import torch
    # Upstream loads a second 6 GB copy of the checkpoint into RAM. Mapping
    # weights and assigning tensors lets the OS page them during GPU transfer.
    print(f'Loading local AudioSR weights on {device}', flush=True)
    state = torch.load(str(checkpoint), map_location='cpu', mmap=True, weights_only=True)
    config = pipeline.default_audioldm_config('basic')
    config['model']['params']['device'] = device
    model = pipeline.LatentDiffusion(**config['model']['params'])
    missing, unexpected = model.load_state_dict(state['state_dict'], strict=False, assign=True)
    # Training-only buffers may be absent. Reject missing learned parameters.
    parameters = set(dict(model.named_parameters()))
    if parameters.intersection(missing):
        raise ValueError(f'checkpoint missing parameters: {parameters.intersection(missing)}')
    del state
    gc.collect()
    model.eval().to(device)
    print('AudioSR ready', flush=True)
    return model


def enhance(samples, rate, model, super_resolution, args, temp):
    import math
    divisor = math.gcd(rate, RATE)
    original = resample_poly(samples, RATE // divisor, rate // divisor, axis=0)
    length = round(len(samples) * RATE / rate)
    original = original[:length]
    generated = np.zeros_like(original)
    chunk, overlap = round(5.12 * RATE), round(0.32 * RATE)
    weights = np.zeros(length, dtype=np.float32)
    for start in range(0, length, chunk - overlap):
        stop = min(start + chunk, length)
        window = np.ones(stop - start, dtype=np.float32)
        fade = min(overlap, len(window))
        if start:
            window[:fade] *= np.linspace(0, 1, fade, dtype=np.float32)
        if stop < length:
            window[-fade:] *= np.linspace(1, 0, fade, dtype=np.float32)
        for channel in range(samples.shape[1]):
            segment = original[start:stop, channel]
            if rms(segment) < 1e-7:
                restored = segment
            else:
                # Supply 48 kHz audio so the upstream frontend can estimate its
                # true spectral cutoff. Padding stays inside model inference.
                sf.write(temp / 'chunk.wav', segment, RATE, subtype='FLOAT')
                restored = np.asarray(super_resolution(
                    model, str(temp / 'chunk.wav'), seed=args.seed,
                    ddim_steps=args.steps, guidance_scale=3.5)).reshape(-1)
                if len(restored) < len(segment) or not np.isfinite(restored).all():
                    raise ValueError('model returned invalid samples')
                restored = restored[:len(segment)]
                restored = restored * (rms(segment) / max(rms(restored), 1e-8))
            generated[start:stop, channel] += restored * window
        weights[start:stop] += window
        if stop == length:
            break
    generated /= np.maximum(weights[:, None], 1e-8)
    # Protect ambience, impacts and mechanical noises from speech-style
    # denoising or wholesale regeneration. Only use the upper-band residual.
    cutoff = min(rate * 0.45, 20000)
    highpass = butter(6, cutoff, btype='highpass', fs=RATE, output='sos')
    result = original + args.strength * sosfilt(highpass, generated - original, axis=0)
    result *= rms(original) / max(rms(result), 1e-8)
    peak = float(np.max(np.abs(result)))
    if peak > 0.98:
        result *= 0.98 / peak
    return result.astype(np.float32)


def listening_page(output, records, model_name):
    rows = []
    for name, record in sorted(records.items()):
        if record.get('status') != 'complete':
            continue
        # Decoded preview handles the two formats browsers cannot play.
        before = quote('originals/' + name)
        after = quote('Sounds/' + name)
        rows.append(f'<tr><td>{html.escape(name)}</td>'
                    f'<td><audio controls preload="none" src="{before}"></audio></td>'
                    f'<td><audio controls preload="none" src="{after}"></audio></td></tr>')
    (output / 'index.html').write_text(
        '<!doctype html><meta charset="utf-8"><title>Fade sound comparison</title>'
        '<style>body{font:16px system-ui;margin:24px;background:#171b22;color:#eee}'
        'td,th{padding:8px;text-align:left}audio{width:280px}</style>'
        f'<h1>Fade sound comparison</h1><p>Original decoded audio and {html.escape(model_name)} '
        'upper-frequency enhancement. Listen before selecting a replacement pack.</p>'
        '<table><tr><th>Effect</th><th>Original</th><th>Enhanced</th></tr>'
        + ''.join(rows) + '</table>')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source', type=Path, default=ROOT / 'assets/Sounds')
    parser.add_argument('--output', type=Path)
    parser.add_argument('--checkpoint', type=Path, required=True,
                        help='AudioSR checkpoint file or FlashSR weights directory')
    parser.add_argument('--backend', choices=['audiosr', 'flashsr'], default='audiosr')
    parser.add_argument('--model-source', type=Path)
    parser.add_argument('--device', choices=['auto', 'cpu', 'mps', 'cuda'], default='auto')
    parser.add_argument('--steps', type=int, default=50)
    parser.add_argument('--strength', type=float, default=0.5)
    parser.add_argument('--seed', type=int, default=42)
    parser.add_argument('--limit', type=int, default=0)
    args = parser.parse_args()
    args.model_source = args.model_source or ROOT / 'build/third_party' / args.backend
    args.output = args.output or ROOT / ('build/remastered-audio' if args.backend == 'audiosr'
                                       else 'build/remastered-audio-flashsr')
    source, output = args.source.resolve(), args.output.resolve()
    if source == output or source in output.parents or output in source.parents:
        parser.error('source and output trees must be separate')
    checkpoint_ready = (args.checkpoint.is_file() if args.backend == 'audiosr' else
                        all((args.checkpoint / name).is_file() for name in
                            ['student_ldm.pth', 'sr_vocoder.pth', 'vae.pth']))
    if (not checkpoint_ready or not 1 <= args.steps <= 1000 or
            not 0 <= args.strength <= 1 or args.limit < 0):
        parser.error('require local checkpoint, steps 1..1000, strength 0..1, limit >= 0')
    os.environ.setdefault('NUMBA_CACHE_DIR', str(ROOT / 'build/numba-cache'))
    os.environ.setdefault('MPLCONFIGDIR', str(ROOT / 'build/matplotlib-cache'))
    os.environ.setdefault('HF_HUB_OFFLINE', '1')
    sys.path.insert(0, str(args.model_source.resolve()))
    import torch
    if args.backend == 'audiosr':
        import audiosr.pipeline as pipeline
    else:
        import remaster_flashsr as adapter
    torch.set_num_threads(min(8, torch.get_num_threads()))
    device = args.device
    if device == 'auto':
        device = ('cuda' if torch.cuda.is_available() else
                  'mps' if torch.backends.mps.is_available() else 'cpu')
    model_name = 'AudioSR basic' if args.backend == 'audiosr' else 'FlashSR one-step'
    checkpoint_hash = (digest(args.checkpoint) if args.backend == 'audiosr' else
                       {p: digest(args.checkpoint / p) for p in
                        ['student_ldm.pth', 'sr_vocoder.pth', 'vae.pth']})
    pipeline_path = args.model_source / ('audiosr/pipeline.py' if args.backend == 'audiosr'
                                       else 'FlashSR/FlashSR.py')
    settings = {'model': model_name, 'checkpoint_sha256': checkpoint_hash,
                'pipeline_sha256': digest(pipeline_path),
                'script_sha256': digest(Path(__file__)), 'device': device,
                'steps': args.steps if args.backend == 'audiosr' else 1,
                'adapter_sha256': digest(Path(__file__).with_name('remaster_flashsr.py'))
                    if args.backend == 'flashsr' else None,
                'strength': args.strength, 'seed': args.seed,
                'output_rate': RATE}
    output.mkdir(parents=True, exist_ok=True)
    for folder in ['Sounds', 'originals']:
        (output / folder).mkdir(exist_ok=True)
    manifest_path = output / 'manifest.json'
    previous = json.loads(manifest_path.read_text()) if manifest_path.exists() else {}
    records = previous.get('assets', {})
    manifest = {'settings': settings, 'source': str(source), 'assets': records}
    files = sorted(source.rglob('*.wav'))
    if args.limit:
        files = files[:args.limit]
    if not files:
        parser.error('no WAV files found')
    model, failures = None, 0
    for index, path in enumerate(files, 1):
        name = path.relative_to(source).as_posix()
        fingerprint = hashlib.sha256(json.dumps(
            {'source': digest(path), **settings}, sort_keys=True).encode()).hexdigest()
        destination, preview = output / 'Sounds' / name, output / 'originals' / name
        record = records.get(name, {})
        if (record.get('fingerprint') == fingerprint and record.get('status') == 'complete'
                and destination.exists() and digest(destination) == record['output_sha256']
                and preview.exists() and digest(preview) == record['preview_sha256']):
            print(f'[{index}/{len(files)}] cached {name}', flush=True)
            continue
        print(f'[{index}/{len(files)}] enhance {name}', flush=True)
        try:
            if model is None:
                model = (load_model(pipeline, args.checkpoint, device) if args.backend == 'audiosr'
                         else adapter.load(args.checkpoint, args.model_source, device))
            with tempfile.TemporaryDirectory(prefix='fade-audiosr-') as temporary:
                temp = Path(temporary)
                samples, rate = decode(path, temp)
                infer = pipeline.super_resolution if args.backend == 'audiosr' else adapter.infer
                restored = enhance(samples, rate, model, infer, args, temp)
                destination.parent.mkdir(parents=True, exist_ok=True)
                preview.parent.mkdir(parents=True, exist_ok=True)
                staged = destination.with_suffix('.wav.tmp')
                sf.write(staged, restored, RATE, subtype='PCM_16', format='WAV')
                check, check_rate = sf.read(staged, always_2d=True)
                if (check.shape != restored.shape or check_rate != RATE or
                        not np.isfinite(check).all() or np.max(np.abs(check)) >= 1):
                    raise ValueError('output validation failed')
                staged.replace(destination)
                sf.write(preview, samples, rate, subtype='PCM_16')
                records[name] = {'status': 'complete', 'fingerprint': fingerprint,
                                 'source_sha256': digest(path), 'source_rate': rate,
                                 'source_frames': len(samples), 'channels': samples.shape[1],
                                 'output_frames': len(check), 'output_rate': RATE,
                                 'duration_seconds': len(check) / RATE,
                                 'original_rms': rms(samples), 'output_rms': rms(check),
                                 'output_peak': float(np.max(np.abs(check))),
                                 'output_sha256': digest(destination),
                                 'preview_sha256': digest(preview)}
        except Exception as error:
            import traceback
            traceback.print_exc()
            records[name] = {'status': 'failed', 'fingerprint': fingerprint, 'error': str(error)}
            failures += 1
            if model is None:
                save_json(manifest_path, manifest)
                return 1
        save_json(manifest_path, manifest)
        listening_page(output, records, model_name)
    manifest['summary'] = {'requested': len(files), 'failures': failures,
                           'complete': sum(r.get('status') == 'complete' for r in records.values())}
    save_json(manifest_path, manifest)
    print(json.dumps(manifest['summary']), flush=True)
    return 1 if failures else 0


if __name__ == '__main__':
    sys.exit(main())
