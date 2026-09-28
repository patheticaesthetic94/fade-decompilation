# Audio enhancement and lossless image compression

The 2026-09-28 preparation run generated **109 FlashSR sound effects** and
compressed **1,718 PNGs across 10 HD directories**, saving **171.68 MiB** with
identical decoded pixels. Original inputs remain intact. The preparation
produced separate audio and image packs. The subsequent APK build described
below bundles the complete FlashSR audio and compressed Upscayl High Fidelity
artwork.

The durable [results snapshot](media-results-2026-09-28.json) records model
revisions, checkpoint hashes, settings, validation results and exact byte
counts. Detailed per-file manifests, logs and listening pages are in `build/`,
which is ignored by Git and can be regenerated using the commands below.

## Tools and installation

| Tool | Purpose |
| --- | --- |
| [`setup_media_models.sh`](../tools/setup_media_models.sh) | Create the local environment, fetch pinned model sources and download checkpoints |
| [`remaster_sounds.py`](../tools/remaster_sounds.py) | Decode, enhance, validate and resume a sound-effect batch; generate the listening page |
| [`remaster_flashsr.py`](../tools/remaster_flashsr.py) | Adapt the official FlashSR implementation for local CPU/Metal inference |
| [`compress_hd_images.py`](../tools/compress_hd_images.py) | Optimize PNG copies, verify exact pixels and update pack manifests |

Install the local tools with `sh tools/setup_media_models.sh`. This uses
`build/media-venv`, pinned model sources and FlashSR checkpoints under
`build/model-cache`. Use `sh tools/setup_media_models.sh audiosr` to install
the optional 6.18 GB AudioSR checkpoint. Python 3.8–3.11 and FFmpeg are required.
The environment reuses available system packages but installs any needed
versions inside the virtual environment; system packages are not modified.

Run all commands from the project root. Git and FFmpeg must be on `PATH`.
Some Python versions require a Rust toolchain to build pyoxipng from source;
the installed optimizer here was built using the existing Cargo toolchain.
Installation downloads code and weights; batch inference uses local files.

```sh
sh tools/setup_media_models.sh                  # FlashSR weights
sh tools/setup_media_models.sh audiosr          # optional AudioSR weights
# Select a compatible interpreter if python3 is newer than 3.11:
MEDIA_PYTHON=/path/to/python3.11 sh tools/setup_media_models.sh
```

The tested environment used Python 3.8.10, torch/torchaudio 2.1.1,
torchvision 0.16.1, NumPy 1.23.5, librosa 0.9.2, transformers 4.30.2,
torchlibrosa 0.1.0, timm 0.9.12, huggingface_hub 0.19.4 and pyoxipng 9.1.1.
The scripts keep package/model caches, Numba cache and Matplotlib configuration
under `build/`. The installer reuses available system packages and places
additional packages inside the virtual environment.

## Pinned model provenance

| Component | Upstream | Pinned revision |
| --- | --- | --- |
| FlashSR inference source | [jakeoneijk/FlashSR_Inference](https://github.com/jakeoneijk/FlashSR_Inference) | `2292814a7ef74f61a5479c8d96e653d2f90f369d` |
| FlashSR weights | [jakeoneijk/FlashSR_weights](https://huggingface.co/datasets/jakeoneijk/FlashSR_weights) | `5701dea5f6a45ed964f5cb5b9280b3a1f9b39882` |
| AudioSR source | [haoheliu/versatile_audio_super_resolution](https://github.com/haoheliu/versatile_audio_super_resolution) | `d312fbab9f0e94087d9f2802d03cf184353cc805` |
| AudioSR basic weights | [haoheliu/audiosr_basic](https://huggingface.co/haoheliu/audiosr_basic) | `74a47f49061a1e788e968cc43ad45c0b6243f37d` |
| Auxiliary RoBERTa config/tokenizer | [roberta-base](https://huggingface.co/roberta-base) | `e2da8e2f811d1448a5b465c236feacd80ffbac7b` |

FlashSR's three checkpoints are `student_ldm.pth`, `sr_vocoder.pth` and
`vae.pth`. `build/flashsr-weights/` contains links to the downloaded snapshots.
The optional AudioSR checkpoint path is stored in `build/audiosr-checkpoint.txt`.
Full SHA-256 values for all four checkpoints and the inference scripts used
are retained in the results snapshot and generated manifests.

## Sound effects

```sh
PYTORCH_ENABLE_MPS_FALLBACK=1 build/media-venv/bin/python tools/remaster_sounds.py \
  --backend flashsr --checkpoint build/flashsr-weights --device auto
```

The default source is `assets/Sounds`; FlashSR output is `build/remastered-audio-flashsr`.
Open `build/remastered-audio-flashsr/index.html` for original/enhanced playback of each
effect. Original assets are untouched. Select the enhanced pack for a build
with `tools/android_build.sh --remastered-audio`; `FADE_AUDIO_PACK` defaults
to `build/remastered-audio-flashsr`. Staging verifies the complete inventory,
source/output hashes, 48 kHz PCM16 format, channels and duration, then copies
the sounds over the game's encoded `.IFV` paths. The APK includes audio
provenance. The engine requests 48 kHz output and converts to the obtained
device rate when necessary.

[FlashSR](https://github.com/jakeoneijk/FlashSR_Inference) is a one-step diffusion
model for sound effects, music and speech. It avoids the repeated sampling work
of [AudioSR](https://github.com/haoheliu/versatile_audio_super_resolution), which
is also supported:

```sh
TRANSFORMERS_CACHE=build/model-cache PYTORCH_ENABLE_MPS_FALLBACK=1 \
  build/media-venv/bin/python tools/remaster_sounds.py \
  --checkpoint "$(cat build/audiosr-checkpoint.txt)" --device auto
```

AudioSR output is `build/remastered-audio`. Both models' upper frequencies are inferred
details, not recovery of a known original master. Listen for changes to impacts,
ambience, mechanical sounds and looping clips before adopting the pack.
The model does not remove the original 8-bit quantization noise.

The script decodes WAV files through FFmpeg to floating-point PCM and resamples
each channel to 48 kHz using SciPy's polyphase resampler. It processes
5.12-second chunks with 0.32-second overlap and linear crossfades. FlashSR pads
short chunks to its required 245,760 samples; padding is removed before mixing.
Silent chunks bypass generation.

The resampled original is the base signal. A sixth-order Butterworth high-pass
filter selects the difference between the model output and that base, using
`min(0.45 * source_sample_rate, 20000)` Hz as its cutoff. The residual is added
at 50% strength. Chunk levels are matched before crossfading; final RMS is
matched to the resampled original, and gain is reduced if the peak exceeds
0.98. Resampling and this peak protection can change the level relative to the
decoded low-rate source. This is bandwidth enhancement, not general denoising.
Output is 48 kHz PCM16, preserving duration to the nearest output sample and
channel count. `--strength`, `--steps`, `--device` and `--limit` are available.
FlashSR uses its trained single-step sampler; AudioSR defaults to 50 steps.
On this Mac, FlashSR's complex STFT frontend stays on CPU because torch 2.1.1
does not support complex tensors on Metal; real mel features and the learned
networks run on the selected GPU. Set `PYTORCH_ENABLE_MPS_FALLBACK=1` before
running on MPS to permit the upstream weight-normalization operation on CPU.
Model output is validated for sample count, channels, sample rate, finite
values and clipping, not subjective quality.

The installer defaults to FlashSR, while `remaster_sounds.py` defaults to
AudioSR. Pass `--backend flashsr` as shown above
when using the completed full-pack model.

| Option | Default / behavior |
| --- | --- |
| `--checkpoint` | Required: AudioSR file or FlashSR weights directory |
| `--source`, `--output` | `assets/Sounds`; separate output directory selected by backend |
| `--model-source` | `build/third_party/audiosr` or `build/third_party/flashsr` |
| `--device` | `auto`: CUDA, then Metal, then CPU when available |
| `--steps` | 50 for AudioSR; FlashSR uses its trained one-step sampler |
| `--strength` | 0.5; accepted range 0–1 |
| `--seed` | 42 |
| `--limit` | 0 means all files; a positive value processes the first sorted entries |

For a small trial, add `--limit 1 --output build/audio-trial`. CPU execution
uses `--device cpu`. Changing devices changes the resume fingerprint.

The manifest records source/output hashes, settings, durations and levels.
Rerunning skips files only when input, model, script, settings and both generated
file hashes match. Inference uses explicit local files and disables Hugging Face
downloads. AudioSR tensors are memory-mapped and assigned during loading to
reduce duplicate weight allocations. Metal requires GPU access outside the
session sandbox on this Mac.
The optional AudioSR installer also caches its auxiliary RoBERTa configuration
and tokenizer under `build/model-cache`; use the `TRANSFORMERS_CACHE` setting
shown above so inference finds them without a network request.

Failures are recorded in the manifest and return a nonzero exit status. A
per-file failure allows the batch to continue; a model-loading failure stops it.
Audio output is staged and validated before replacing its destination file.
Reruns retry failed or changed entries and verify both enhanced and preview
hashes before reusing a completed entry.

## HD image compression

```sh
build/media-venv/bin/python tools/compress_hd_images.py --all
python3 tools/validate_hd_assets.py --pack build/hd-assets-compressed
```

`--all` processes every `build/hd*` directory containing PNGs, including alternate
model packs and comparison images, into sibling `*-compressed` directories.
For a single pack, use `--source build/hd-assets`; `--output` can specify its copy.
The default optimization level is 2, adjustable from 0 to 6. The optimizer
retains PNG metadata and compares dimensions and every decoded RGBA pixel,
including hidden RGB values under transparent pixels. Each written file is
decoded again for verification. A candidate is kept only if it is smaller.
Files that cannot shrink retain their original bytes.

`--workers` defaults to 2. Source and output directories must be separate and
must not contain one another. Animated PNGs are rejected by this pipeline.
`--all` covers generated `build/hd*` directories, excluding existing
`*-compressed` copies; it does not process the separate Android staging tree.
Image compression reruns the optimizer on each invocation; only the audio
pipeline has per-file inference caching.

Auxiliary files are copied and asset manifest hashes/sizes updated. Existing
source packs remain intact. `compression.json` contains per-image checks and
size savings; `build/hd-compression.json` summarizes an `--all` run. These
copies can be validated and selected wherever the original PNG pack was used.
For an HD Android build, select the copy with
`FADE_HD_PACK=build/hd-assets-compressed tools/android_build.sh --hd`.
This changes PNG encoding only; it does not quantize colors, alter alpha,
resize images or change the renderer. APK savings also depend on ZIP compression.

## Image batch results (2026-09-28)

All 1,718 PNGs in 10 generated HD directories passed exact RGBA comparisons.
Combined PNG size fell from 922.81 MiB to 751.13 MiB, saving 171.68 MiB.
The selected pack's 838 PNGs fell from 440.82 MiB to 359.85 MiB (18.37% smaller).
Both the selected and alternate complete packs pass the existing HD validator.
Original files remain intact; see the JSON reports for individual image savings.

| Original directory under `build/` | PNGs | Before (MiB) | After (MiB) | Reduction |
| --- | ---: | ---: | ---: | ---: |
| `hd-assets` | 838 | 440.82 | 359.85 | 18.37% |
| `hd-batch-check` | 2 | 1.69 | 1.40 | 17.28% |
| `hd-comparison` | 18 | 6.58 | 5.31 | 19.32% |
| `hd-pipeline-check` | 6 | 1.53 | 1.15 | 25.24% |
| `hd-realesrnet-samples` | 3 | 1.00 | 0.77 | 22.18% |
| `hd-samples` | 5 | 3.30 | 2.68 | 18.66% |
| `hd-swinir-gan-samples` | 3 | 1.69 | 1.39 | 17.77% |
| `hd-swinir-samples` | 3 | 0.99 | 0.78 | 21.78% |
| `hd-test` | 2 | <0.01 | <0.01 | 92.25% |
| `hd-upscayl-high-fidelity` | 838 | 465.21 | 377.80 | 18.79% |
| **Total** | **1,718** | **922.81** | **751.13** | **18.60%** |

Each output is the original directory name with `-compressed` appended.
MiB values are rounded; the JSON snapshot retains exact byte counts.

## Sound batch results (2026-09-28)

FlashSR processed all 109 effects with zero failures. The independent
`build/remastered-audio-flashsr/validation.json` report verifies the inventory,
unchanged source hashes, output/preview hashes, exact rounded sample counts,
channels, 48 kHz PCM16 encoding, finite samples and no clipping. It does not
rate perceived quality; the listening page covers every effect for that review.

The inventory contains 109 mono WAVs: 90 unsigned 8-bit PCM files at 8 kHz,
nine at 11.025 kHz, seven at 22.05 kHz, and one signed 16-bit PCM file at 8 kHz.
The remaining two are `PORTIERE.wav` (IMA ADPCM, 11.025 kHz) and
`MEC ETRANGLE.wav` (TrueSpeech, 8 kHz). Both legacy codecs decoded and processed
successfully. Total enhanced duration is 249.482979 seconds.

AudioSR was tested first on the 16 GB Apple Silicon Mac. Its original loader
caused memory pressure, so the adapter uses memory-mapped checkpoint tensors
and `load_state_dict(assign=True)` to reduce duplicate allocations. Its 50-step
trial passed, with sampling taking roughly 30–45 seconds per chunk after
initialization. Eight completed AudioSR effects remain in
`build/remastered-audio/` for comparison; a full AudioSR pack was not generated.

FlashSR was selected to complete the batch using its trained one-step sampler.
The initial Metal trial exposed an unsupported complex-tensor STFT operation;
moving only that frontend to CPU allowed the trial to pass. An early FlashSR
trial sampled in about two seconds, with later warm sampler calls around
half a second. These are sampler observations, not timings for an entire clip
or a quality comparison. The complete FlashSR batch then finished with zero
failures. A second invocation reported **109 cached effects**, zero failures
and no model initialization, verifying resume behavior.

Additional preparation checks passed for hidden RGB values under transparency,
partial alpha, PNG text/DPI metadata, audio chunks of 0.01, 5.12, 5.2 and
10 seconds, both legacy WAV decoders, and offline auxiliary AudioSR tokenizer
loading. The complete output checks cover every file; synthetic chunk checks
exercise boundaries and do not measure audio quality.

## Evidence and remaining review

| Artifact | Contents |
| --- | --- |
| `build/remastered-audio-flashsr/manifest.json` | Model/script hashes, settings and per-effect source/output hashes, durations, channels and levels |
| `build/remastered-audio-flashsr/validation.json` | Independent complete-pack verification; 109 files, no errors |
| `build/remastered-audio-flashsr/index.html` | Original decoded and enhanced playback for all 109 effects |
| `build/audio-flashsr-all.log` | Complete FlashSR processing log |
| `build/audio-flashsr-cache-check.log` | Second run showing all 109 effects reused |
| `build/remastered-audio/index.html` | Eight completed AudioSR comparisons |
| `build/hd-compression.json` | Summary of all 10 compressed directories |
| `build/hd-compression.log` | Image processing progress and size totals |
| `build/hd-assets-compressed/validation.json` | Selected full HD pack verification; 838 files, no errors |
| `build/hd-upscayl-high-fidelity-compressed/validation.json` | Alternate full HD pack verification; 838 files, no errors |
| `build/*-compressed/compression.json` | Per-PNG sizes, hashes and exact RGBA comparison results |

The independent audio report was produced by a separate one-off audit of the
source inventory, manifest and decoded output/preview files. The batch script
itself validates each newly generated output; rerunning it verifies cached
hashes but does not regenerate that independent report.

Listening review of the generated high frequencies, transients, ambience and
loop boundaries remains open. There was no subjective approval of the sound
pack in this session. These outputs are bundled in the APK below; audible device playback remains
unverified. PNG byte savings do not establish an equal
APK reduction because APK ZIP compression also affects the result.


## Updated APK (2026-09-28)

`build/fade-android-enhanced-media.apk` contains 109 enhanced FlashSR sound
effects, 838 losslessly compressed Upscayl High Fidelity images, runtime
Comic Neue / Arimo fonts, and arm64-v8a / x86_64 libraries. The app ID, version
and save format are preserved. Install over the existing app to retain saves.
This build is 436,308,846 bytes (416.10 MiB), compared with 506,231,552 bytes
for the preceding runtime-font HD APK, a reduction of 66.68 MiB.

```sh
FADE_HD_PACK=build/hd-upscayl-high-fidelity-compressed \
  FADE_RUNTIME_FONTS_APK_OUTPUT=../../build/fade-android-enhanced-media.apk \
  tools/android_build.sh --hd --runtime-fonts --remastered-audio
python3 tools/validate_media_apk.py
```

Run `./gradlew clean` in `port/android` before rebuilding when measuring APK
size: incremental packaging can retain unused ZIP space after asset replacement.
The delivered artifact was built cleanly. APK ZIP integrity, all media hashes,
48 kHz WAV headers, both native ABIs, filename indices and APK signature passed.
The validator writes `build/enhanced-media-apk-validation.json`.

The arm64 emulator also passed the existing HD renderer and runtime-font
regressions. A standalone audio harness decoded all 109 WAVs and ran the
actual game's audio callback at 48 kHz, matching every mono-to-stereo output
sample within one PCM16 rounding step; looping and stopping passed. The harness
supplies filesystem and audio-device wrappers because standalone executables
lack Android's Java helpers. This checks conversion and callback behavior,
not audible playback or the real device audio driver. Its source and evidence
are in `build/media-audio-test/` and `build/enhanced-media-audio-test.log`.
Other build/test logs use the `build/enhanced-media-*` prefix.
