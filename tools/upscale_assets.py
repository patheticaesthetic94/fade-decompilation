#!/usr/bin/env python3
"""Prepare an HD PNG pack with local Real-ESRGAN ncnn inference.

Requires Pillow and, for AI jobs, a local realesrgan-ncnn-vulkan executable
and its models directory. Never downloads models or modifies source assets.
See port/HD.md for policy, commands and engine integration requirements.
"""
import argparse
from collections import Counter
import fnmatch
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
EXTENSIONS = {'.jpg', '.jpeg', '.bmp', '.gif', '.png'}
METHODS = {'ai', 'lanczos', 'nearest', 'skip'}


def digest(path):
    h = hashlib.sha256()
    with path.open('rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            h.update(block)
    return h.hexdigest()


def atomic_json(path, value):
    temporary = path.with_suffix('.json.tmp')
    temporary.write_text(json.dumps(value, indent=2) + '\n')
    temporary.replace(path)


def default_method(relative):
    folder = relative.parts[0].lower()
    if folder == 'fonts':
        return 'skip'
    # Masks encode exact colours rather than artwork. Sprite artwork can use
    # AI: the HD renderer retains key coverage from the original RGB565 image.
    if 'mask' in relative.name.lower():
        return 'nearest'
    if folder in {'images', 'zoom', 'inventaire', 'menu', 'ui', 'sprites'}:
        return 'ai'
    return 'lanczos'


def load_rules(path):
    rules = json.loads(path.read_text()) if path else []
    if not isinstance(rules, list):
        raise ValueError('rules must be a JSON list')
    for rule in rules:
        if not isinstance(rule, dict) or set(rule) - {'glob', 'method', 'key_rgb'}:
            raise ValueError('rules accept glob, method and optional key_rgb only')
        if not isinstance(rule.get('glob'), str) or rule.get('method') not in METHODS:
            raise ValueError('each rule needs a glob and a supported method')
        key = rule.get('key_rgb')
        if key is not None and (not isinstance(key, list) or len(key) != 3 or
                                any(type(c) is not int or not 0 <= c <= 255 for c in key)):
            raise ValueError('key_rgb must contain three integers in 0..255')
    return rules


def inventory(source, rules, includes, limit, resample_only):
    jobs = []
    for path in sorted(source.rglob('*')):
        if not path.is_file() or path.suffix.lower() not in EXTENSIONS:
            continue
        relative = path.relative_to(source)
        name = relative.as_posix()
        if includes and not any(fnmatch.fnmatchcase(name, pat) for pat in includes):
            continue
        method, key = default_method(relative), None
        for rule in rules:
            if fnmatch.fnmatchcase(name, rule['glob']):
                method, key = rule['method'], rule.get('key_rgb')
        if relative.parts[0].lower() == 'fonts' and method != 'skip':
            raise ValueError('font sheets must be replaced with outline fonts, not upscaled')
        if resample_only and method == 'ai':
            method = 'lanczos'
        with Image.open(path) as im:
            size, frames = list(im.size), getattr(im, 'n_frames', 1)
        if frames > 1:
            raise ValueError(f'{name}: animated images need a frame-aware pipeline')
        jobs.append({'source': name, 'source_sha256': digest(path),
                     'original_size': size, 'method': method, 'key_rgb': key,
                     'output': name + '.png' if method != 'skip' else None})
        if limit and len(jobs) >= limit:
            break
    return jobs


def runner_settings(args):
    if args.backend == 'torch':
        from upscale_torch import choose_device
        if not args.checkpoint or not args.network_source:
            raise ValueError('torch requires --checkpoint and --network-source')
        if args.tile and args.tile % 8:
            raise ValueError('torch tile size must be a multiple of 8')
        checkpoint, source = args.checkpoint.resolve(), args.network_source.resolve()
        return {'backend': 'torch', 'architecture': args.architecture,
                'checkpoint': str(checkpoint), 'checkpoint_sha256': digest(checkpoint),
                'network_source': str(source), 'network_sha256': digest(source),
                'adapter_sha256': digest(Path(__file__).with_name('upscale_torch.py')),
                'device': choose_device(args.device), 'tile': args.tile}
    binary = shutil.which(str(args.binary))
    if binary is None:
        raise ValueError('local upscaler not found; use --binary /path/to/realesrgan-ncnn-vulkan')
    binary = Path(binary).resolve()
    models = args.models.resolve() if args.models else binary.parent / 'models'
    model_files = [models / (args.model + suffix) for suffix in ('.param', '.bin')]
    if not all(p.is_file() for p in model_files):
        raise ValueError(f'model files missing in {models}; use --models /path/to/models')
    return {'backend': 'ncnn', 'binary': str(binary), 'binary_sha256': digest(binary),
            'models': str(models), 'model': args.model,
            'model_sha256': {p.name: digest(p) for p in model_files},
            'tile': args.tile, 'gpu': args.gpu}


def process(job, source, output, scale, runner, timeout, torch_runner=None, ncnn_ready=None):
    path = source / job['source']
    destination = output / job['output']
    destination.parent.mkdir(parents=True, exist_ok=True)
    size = tuple(n * scale for n in job['original_size'])
    with Image.open(path) as im:
        original = im.convert('RGBA')
    if job['key_rgb'] is not None:
        key = tuple(job['key_rgb'])
        # Explicit keys only: black can also be legitimate opaque artwork.
        original.putdata([(r, g, b, 0 if (r, g, b) == key else a)
                          for r, g, b, a in original.getdata()])
    alpha = original.getchannel('A')
    with tempfile.TemporaryDirectory(prefix='fade-upscale-') as temporary:
        temp = Path(temporary)
        if job['method'] == 'ai':
            if torch_runner is not None:
                image = torch_runner.enhance(original)
            elif ncnn_ready is not None:
                with Image.open(ncnn_ready) as im:
                    image = im.convert('RGBA')
            else:
                image = run_ncnn(original, temp, scale, runner, timeout)
            if image.size != size:
                raise ValueError(f'upscaler returned {image.size}, expected {size}')
            # Do not let the network invent mask values or transparency.
            image.putalpha(alpha.resize(size, Image.Resampling.NEAREST))
        else:
            resampling = (Image.Resampling.NEAREST if job['method'] == 'nearest'
                          else Image.Resampling.LANCZOS)
            image = original.resize(size, resampling)
            if job['key_rgb'] is not None:
                image.putalpha(alpha.resize(size, Image.Resampling.NEAREST))
        image.save(temp / 'final.png')
        with Image.open(temp / 'final.png') as check:
            check.load()
            if check.size != size:
                raise ValueError('output dimensions failed validation')
        staged = destination.with_suffix('.png.tmp')
        shutil.copyfile(temp / 'final.png', staged)
        staged.replace(destination)
    return {'status': 'complete', 'output_size': list(size),
            'output_sha256': digest(destination), 'output_bytes': destination.stat().st_size}


def run_ncnn(original, temp, scale, runner, timeout):
    original.convert('RGB').save(temp / 'input.png')
    command = [runner['binary'], '-i', str(temp / 'input.png'),
               '-o', str(temp / 'output.png'), '-m', runner['models'],
               '-n', runner['model'], '-s', str(scale),
               '-t', str(runner['tile']), '-j', '1:1:1', '-f', 'png']
    if runner['gpu'] is not None:
        command += ['-g', str(runner['gpu'])]
    result = subprocess.run(command, capture_output=True, text=True, timeout=timeout)
    if result.returncode:
        raise RuntimeError(f'upscaler exited {result.returncode}: {result.stderr[-3000:]}')
    with Image.open(temp / 'output.png') as im:
        image = im.convert('RGBA')
    return image


def job_settings(job, scale, runner):
    settings = {'schema': 1, **job, 'scale': scale,
                'runner': runner if job['method'] == 'ai' else None}
    fingerprint = hashlib.sha256(json.dumps(settings, sort_keys=True).encode()).hexdigest()
    return settings, fingerprint


class NcnnBatch:
    """Reuse the model across small groups while preserving per-asset validation."""
    def __init__(self, jobs, source, output, records, scale, runner, timeout, size):
        self.source, self.scale, self.runner = source, scale, runner
        self.timeout, self.size = timeout, size
        self.pending, self.ready, self.workspace = [], {}, None
        for job in jobs:
            if job['method'] != 'ai':
                continue
            _, fingerprint = job_settings(job, scale, runner)
            old = records.get(job['source'], {})
            path = output / job['output']
            if (old.get('fingerprint') == fingerprint and old.get('status') == 'complete'
                    and path.is_file() and digest(path) == old.get('output_sha256')):
                continue
            self.pending.append(job)

    def get(self, job):
        name = job['source']
        if name not in self.ready:
            if self.workspace:
                self.workspace.cleanup()
            self.workspace = tempfile.TemporaryDirectory(prefix='fade-upscale-batch-')
            temp = Path(self.workspace.name)
            inputs, outputs = temp / 'inputs', temp / 'outputs'
            inputs.mkdir(); outputs.mkdir()
            group, self.pending = self.pending[:self.size], self.pending[self.size:]
            self.ready = {}
            for index, entry in enumerate(group):
                with Image.open(self.source / entry['source']) as im:
                    im.convert('RGB').save(inputs / f'{index:04d}.png')
                self.ready[entry['source']] = outputs / f'{index:04d}.png'
            runner = self.runner
            command = [runner['binary'], '-i', str(inputs), '-o', str(outputs),
                       '-m', runner['models'], '-n', runner['model'], '-s', str(self.scale),
                       '-t', str(runner['tile']), '-j', '1:1:1', '-f', 'png']
            if runner['gpu'] is not None:
                command += ['-g', str(runner['gpu'])]
            print(f'Running local inference batch of {len(group)} images', flush=True)
            try:
                result = subprocess.run(command, capture_output=True, text=True,
                                        timeout=self.timeout * len(group))
                if result.returncode or not all(p.is_file() for p in self.ready.values()):
                    raise RuntimeError(f'batch exited {result.returncode}: {result.stderr[-2000:]}')
            except (OSError, RuntimeError, subprocess.SubprocessError) as error:
                # Recover per-image, retaining each asset's normal failure report.
                print(f'Batch failed; retrying individually: {error}', file=sys.stderr, flush=True)
                self.ready = {entry['source']: None for entry in group}
        return self.ready[name]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source', type=Path, default=ROOT / 'assets')
    parser.add_argument('--output', type=Path, default=ROOT / 'build/hd-assets')
    parser.add_argument('--inventory', action='store_true', help='inspect without producing files or running AI')
    parser.add_argument('--resample-only', action='store_true', help='use Lanczos instead of AI for pipeline checks')
    parser.add_argument('--scale', type=int, choices=[4], default=4, help='4x general-purpose model')
    local_binary = ROOT / 'build/third_party/realesrgan-ncnn-vulkan-20220424/realesrgan-ncnn-vulkan'
    parser.add_argument('--binary', default=str(local_binary) if local_binary.is_file()
                        else 'realesrgan-ncnn-vulkan')
    parser.add_argument('--backend', choices=['ncnn', 'torch'], default='ncnn')
    parser.add_argument('--architecture', choices=['swinir-l', 'swinir-m', 'realesrnet'], default='swinir-l')
    parser.add_argument('--checkpoint', type=Path)
    parser.add_argument('--network-source', type=Path, help='local official network_swinir.py or rrdbnet_arch.py')
    parser.add_argument('--device', choices=['auto', 'mps', 'cpu'], default='auto')
    parser.add_argument('--models', type=Path)
    parser.add_argument('--model', choices=['realesrgan-x4plus', 'realesrnet-x4plus',
                                         'realesrgan-x4plus-anime', 'high-fidelity-4x'],
                        default='realesrgan-x4plus')
    parser.add_argument('--tile', type=int, default=128)
    parser.add_argument('--batch-size', type=int, default=16, help='ncnn images per model load; 1 disables batching')
    parser.add_argument('--gpu', type=int)
    parser.add_argument('--timeout', type=int, default=600, help='seconds per ncnn asset; torch runs in-process')
    parser.add_argument('--rules', type=Path, help='JSON overrides; last matching rule wins')
    parser.add_argument('--include', action='append', default=[], help='relative glob; repeat to select samples')
    parser.add_argument('--limit', type=int, default=0, help='maximum selected assets; 0 means all')
    args = parser.parse_args()
    source, output = args.source.resolve(), args.output.resolve()
    if not source.is_dir():
        parser.error(f'source directory not found: {source}')
    if source == output or source in output.parents or output in source.parents:
        parser.error('source and output trees must be separate and must not contain each other')
    if args.limit < 0 or args.timeout <= 0 or args.batch_size < 1 or (args.tile != 0 and args.tile < 32):
        parser.error('limit must be nonnegative, timeout positive, tile 0 or at least 32')
    try:
        jobs = inventory(source, load_rules(args.rules), args.include, args.limit, args.resample_only)
        if not jobs:
            raise ValueError('no images matched')
        counts = Counter(job['method'] for job in jobs)
        pixels = sum(w * h * args.scale ** 2 for job in jobs if job['method'] != 'skip'
                     for w, h in [job['original_size']])
        print(f'{len(jobs)} assets: {dict(counts)}; uncompressed RGBA output {pixels * 4 / 2**20:.1f} MiB', flush=True)
        if args.inventory:
            return 0
        runner = runner_settings(args) if counts['ai'] else None
        torch_runner = None
        if runner and runner['backend'] == 'torch':
            from upscale_torch import TorchUpscaler
            print(f'Loading {args.architecture} on {runner["device"]}', flush=True)
            torch_runner = TorchUpscaler(runner)
        output.mkdir(parents=True, exist_ok=True)
        manifest_path = output / 'manifest.json'
        previous = json.loads(manifest_path.read_text()) if manifest_path.exists() else {}
        records = previous.get('assets', {})
        manifest = {'schema': 1, 'source_root': str(source), 'scale': args.scale,
                    'renderer_integrated': False, 'assets': records}
        batches = (NcnnBatch(jobs, source, output, records, args.scale, runner,
                             args.timeout, args.batch_size)
                   if runner and runner['backend'] == 'ncnn' and args.batch_size > 1 else None)
        failures = 0
        for index, job in enumerate(jobs, 1):
            name = job['source']
            settings, fingerprint = job_settings(job, args.scale, runner)
            record = records.get(name, {})
            if job['method'] == 'skip':
                records[name] = {**settings, 'fingerprint': fingerprint, 'status': 'skipped',
                                 'reason': 'font sheet: use an outline-font replacement'}
            else:
                destination = output / job['output']
                if (record.get('fingerprint') == fingerprint and record.get('status') == 'complete'
                        and destination.is_file() and digest(destination) == record.get('output_sha256')):
                    print(f'[{index}/{len(jobs)}] cached {name}', flush=True)
                    continue
                print(f'[{index}/{len(jobs)}] {job["method"]} {name}', flush=True)
                try:
                    ready = batches.get(job) if batches and job['method'] == 'ai' else None
                    result = process(job, source, output, args.scale, runner, args.timeout, torch_runner, ready)
                    records[name] = {**settings, 'fingerprint': fingerprint, **result}
                except (OSError, ValueError, RuntimeError, subprocess.SubprocessError) as error:
                    failures += 1
                    records[name] = {**settings, 'fingerprint': fingerprint,
                                     'status': 'failed', 'error': str(error)}
                    print(f'FAILED {name}: {error}', file=sys.stderr, flush=True)
            atomic_json(manifest_path, manifest)
        print(f'Manifest: {manifest_path}; failures: {failures}', flush=True)
        return 1 if failures else 0
    except (OSError, ValueError, RuntimeError, ImportError) as error:
        parser.error(str(error))


if __name__ == '__main__':
    sys.exit(main())
