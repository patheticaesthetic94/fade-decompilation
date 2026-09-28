#!/bin/sh
# Install into build/ only. Requires Python 3.8--3.11 and ffmpeg on PATH.
set -eu
cd "$(dirname "$0")/.."
MEDIA_PYTHON=${MEDIA_PYTHON:-python3}
"$MEDIA_PYTHON" -c 'import sys; assert (3, 8) <= sys.version_info[:2] <= (3, 11), "Use Python 3.8--3.11 (MEDIA_PYTHON=/path/to/python)"'
command -v ffmpeg >/dev/null
mkdir -p build/third_party
backend=${1:-flashsr}
case "$backend" in audiosr|flashsr) ;; *) echo 'Use flashsr or audiosr' >&2; exit 1 ;; esac
revision=d312fbab9f0e94087d9f2802d03cf184353cc805
if [ ! -d build/third_party/audiosr/.git ]; then
    git clone https://github.com/haoheliu/versatile_audio_super_resolution.git build/third_party/audiosr
fi
git -C build/third_party/audiosr checkout "$revision"
"$MEDIA_PYTHON" -m venv --system-site-packages build/media-venv
export PIP_CACHE_DIR="$PWD/build/pip-cache"
build/media-venv/bin/python -m pip install \
    torch==2.1.1 torchaudio==2.1.1 torchvision==0.16.1 numpy==1.23.5 \
    librosa==0.9.2 transformers==4.30.2 torchlibrosa==0.1.0 \
    huggingface_hub==0.19.4 pyoxipng==9.1.1 'Pillow>=10,<11' \
    'scipy<1.12' soundfile tqdm einops pyyaml unidecode phonemizer \
    progressbar ftfy timm==0.9.12 pandas matplotlib psutil
build/media-venv/bin/python -m pip install --no-deps --no-build-isolation build/third_party/audiosr
if [ "$backend" = flashsr ]; then
    if [ ! -d build/third_party/flashsr/.git ]; then
        git clone https://github.com/jakeoneijk/FlashSR_Inference.git build/third_party/flashsr
    fi
    git -C build/third_party/flashsr checkout 2292814a7ef74f61a5479c8d96e653d2f90f369d
fi
HF_HUB_DISABLE_TELEMETRY=1 build/media-venv/bin/python - "$backend" <<'PY'
from pathlib import Path
import sys
from huggingface_hub import hf_hub_download
if sys.argv[1] == 'audiosr':
    p = hf_hub_download('haoheliu/audiosr_basic', 'pytorch_model.bin',
                       revision='74a47f49061a1e788e968cc43ad45c0b6243f37d',
                       cache_dir='build/model-cache', resume_download=True)
    Path('build/audiosr-checkpoint.txt').write_text(str(Path(p).resolve()) + '\n')
    print('Checkpoint:', p)
    # AudioSR constructs an auxiliary CLAP module even for basic inference.
    # It needs these small RoBERTa metadata files, but no RoBERTa weights.
    revision = 'e2da8e2f811d1448a5b465c236feacd80ffbac7b'
    for name in ['config.json', 'tokenizer_config.json', 'vocab.json', 'merges.txt']:
        hf_hub_download('roberta-base', name, revision=revision,
                        cache_dir='build/model-cache')
    ref = Path('build/model-cache/models--roberta-base/refs/main')
    ref.parent.mkdir(parents=True, exist_ok=True)
    ref.write_text(revision)
else:
    dest = Path('build/flashsr-weights')
    dest.mkdir(exist_ok=True)
    revision = '5701dea5f6a45ed964f5cb5b9280b3a1f9b39882'
    for name in ['student_ldm.pth', 'sr_vocoder.pth', 'vae.pth']:
        p = hf_hub_download('jakeoneijk/FlashSR_weights', name, repo_type='dataset',
                           revision=revision, cache_dir='build/model-cache', resume_download=True)
        link = dest / name
        target = Path(p).absolute()
        if link.is_symlink():
            link.unlink()
        elif link.exists():
            raise RuntimeError('Refusing to overwrite local checkpoint: ' + str(link))
        link.symlink_to(target)
        print('Checkpoint:', p)
    (dest / 'revision.txt').write_text(revision + '\n')
PY
echo 'Ready. See port/MEDIA.md for batch commands.'
