# HD asset preparation and model comparison

The local pipeline is implemented in `tools/upscale_assets.py`. It prepares
lossless 4× PNG packs without changing the original assets. The optional Android
HD build now uses these packs through native high-resolution backing buffers.

## Lossless compression of generated packs

`tools/compress_hd_images.py` creates sibling `*-compressed` copies and verifies
exact decoded RGBA equality, including hidden RGB under transparency. It
updates manifest hashes/sizes so the copied packs pass the existing validator.
The 2026-09-28 batch covered 1,718 PNGs in 10 directories and saved 171.68 MiB.
The current `hd-assets` pack fell from 440.82 to 359.85 MiB; the Upscayl High
Fidelity pack fell from 465.21 to 377.80 MiB. Both compressed full packs passed
validation. These PNG totals describe the later complete packs, separately
from the earlier generation/APK measurements below.

```sh
build/media-venv/bin/python tools/compress_hd_images.py --all
python3 tools/validate_hd_assets.py --pack build/hd-assets-compressed
python3 tools/validate_hd_assets.py --pack build/hd-upscayl-high-fidelity-compressed
# Build using either copy when ready; this rebuild was not run for compression:
FADE_HD_PACK=build/hd-upscayl-high-fidelity-compressed tools/android_build.sh --hd --runtime-fonts
```

See [MEDIA.md](MEDIA.md) for installation, per-pack savings, sound enhancement,
validation evidence and integration limits. Exact counts, model hashes and
byte totals are retained in [media-results-2026-09-28.json](media-results-2026-09-28.json).

## Playable HD build

```sh
tools/android_build.sh --hd
adb install -r build/fade-android-hd.apk
python3 tools/tests/hd.py
```

The development APK is `build/fade-android-hd.apk` (about 442 MiB), with both
arm64-v8a and x86_64 libraries. It uses the same application ID and debug signing
key as the existing build, so installing over it retains saves. A normal build
without `--hd` continues to stage the original asset pack.

`tools/prepare_hd_apk.py` verifies the selected pack hashes and stages 838 PNGs,
an index, six 4× font atlases, replacement legacy font sheets, pinned outline
fonts and their OFL notices. Original font ink is absent from the staged sheets.
Comic Neue Bold supplies game text; Arimo supplies popup text. See [FONTS.md](FONTS.md).

`port/src/hd.c` keeps native ARGB backing stores outside the low-address game
arena. `port/fixups/hd.c` mirrors layer fills, composition, image blits, keyed
sprites, masks, clipping, row/stride operations, downscaled save previews,
saved backgrounds and direct drawing. Presentation uploads a 960×1280 texture;
SDL still uses a 240×320 logical size for input and letterboxing. The original
RGB565 buffers remain populated for scripts, effects and save files.

Legacy fades and shadows still calculate logical geometry and colour changes;
the renderer applies those changes to native detail. Their intermediate colours
approximate the original RGB565 operations. Unregistered buffers, including
screenshots read from existing saves, use enlarged logical pixels. Native text
coverage is retained through layer composition, including logically transparent cells.

Both ABIs build and the arm64 renderer regression test passes for native detail,
keyed composition, saved backgrounds, rows, source stride, clipping, masks,
pointer reuse, antialiased text, opaque popup presentation and in-place shadows.
The emulator runs the menu, opening scenes and dialogue with replacement assets,
and the final APK loads an existing scene-3 save, opens inventory and displays
the corrected Load and bedroom object popups. Screenshots/logs are under
`build/probes/hd-*.{png,log}`. Early gameplay measured about 148 MiB total PSS
on the arm64 emulator; this is one observation, not a peak-memory guarantee.
Later campaign scenes, endings, exhaustive effect fidelity, x86_64 execution
and physical-device HD performance still need testing.

## Selected model

The user selected **Real-ESRGAN x4plus** after reviewing the comparison. It is
the default AI model, using the installed ncnn macOS bundle automatically when
available. The selected full-pack output is `build/hd-assets/`.

```sh
python3 tools/upscale_assets.py --output build/hd-assets
python3 tools/validate_hd_assets.py --pack build/hd-assets
```

This processes all 844 entries using the policy below: 837 AI images, one
nearest-neighbour mask and six skipped font sheets. Model comparisons
remain available as review artifacts; the selected pipeline uses Real-ESRGAN.

The full selected pack has been generated and validated: **838 PNGs, zero
failures**, about **424 MiB** on disk. `build/hd-assets/validation.json` records
the complete 844-entry inventory, exact 4× dimensions, decoding and source/output
hash checks with no errors. The original assets are unchanged. The pack is
integrated into the optional HD APK build described above.

## Models tested on 2026-09-28

Three common samples were processed locally on the Mac GPU: `Images/PART1
SALON.jpg`, `Images/PART3 CHAMBRELOUISON.jpg` and `Zoom/DEBOUCHE CHIOTTE ZOOM.jpg`.
The first two are room scenes; the last is a small close-up detail. All outputs
have exactly four times the source width and height.

| Pack directory under build/ | Model | Observed tradeoff |
| --- | --- | --- |
| hd-samples | Real-ESRGAN x4plus, ncnn | Sharper baseline, with reconstructed fine texture |
| hd-realesrnet-samples | RealESRNet x4plus, PyTorch | Softer, less aggressive texture reconstruction |
| hd-swinir-samples | SwinIR-L real-SR PSNR, PyTorch | Also noticeably soft; not a clear visual improvement on these samples |
| hd-swinir-gan-samples | SwinIR-L real-SR GAN, PyTorch | Strongest alternative for further visual review; different reconstruction of curtains, surfaces and small details |

These are visual observations, not measured high-resolution reconstruction
accuracy. The original high-resolution artwork is unavailable. Neither a larger
model nor the name "PSNR" establishes accuracy on this game's compressed artwork.
Sharper models can invent detail; fidelity-oriented models can erase texture.

The [Real-ESRGAN model zoo](https://github.com/xinntao/Real-ESRGAN/blob/master/docs/model_zoo.md)
identifies RealESRNet as the MSE-loss model and notes its smoothing effects.
[SwinIR's official repository](https://github.com/JingyunLiang/SwinIR) supplies
real-world super-resolution checkpoints and architecture settings. Both SwinIR
checkpoints used here are the large x4 real-SR versions from the official
[v0.0 release](https://github.com/JingyunLiang/SwinIR/releases/tag/v0.0).

Open `build/hd-comparison/index.html` in a browser for an offline wipe slider
with all four model outputs, original nearest-neighbour enlargement and Lanczos.
The controls switch scene, either model, and native output pixel display size.

## Reproduce comparisons

Run from the project root. Pillow is required for every backend. The PyTorch
backend also requires NumPy and torch; SwinIR requires timm. The tested local
environment has torch 2.1.1 and torchvision 0.16.1. No package installation or
system-wide settings were changed.

```sh
python3 tools/upscale_assets.py --inventory

python3 tools/upscale_assets.py --backend torch --architecture swinir-l \
  --checkpoint build/third_party/swinir/SwinIR-L-x4-GAN.pth \
  --network-source build/third_party/swinir/network_swinir.py \
  --device mps --tile 0 \
  --include 'Images/PART1 SALON.jpg' \
  --include 'Images/PART3 CHAMBRELOUISON.jpg' \
  --include 'Zoom/DEBOUCHE CHIOTTE ZOOM.jpg' \
  --output build/hd-swinir-gan-samples

python3 tools/compare_upscales.py \
  --variant 'Real-ESRGAN=build/hd-samples' \
  --variant 'RealESRNet (fidelity)=build/hd-realesrnet-samples' \
  --variant 'SwinIR-L PSNR (fidelity)=build/hd-swinir-samples' \
  --variant 'SwinIR-L GAN (sharper)=build/hd-swinir-gan-samples'
```

Use the PSNR checkpoint in the same SwinIR command to reproduce that pack. For
RealESRNet, use `--architecture realesrnet`, its checkpoint under
`build/third_party/realesrnet/RealESRNet_x4plus.pth`, and its official architecture
file `build/third_party/realesrnet/rrdbnet_arch.py`.

`--device cpu` runs without GPU access. `--device auto` selects MPS when available,
otherwise CPU. The session sandbox hides Metal; GPU comparisons required running
with GPU access. The script does not silently change devices after an inference
failure. `--tile 0` processes each image as a whole, as used for the PyTorch
comparisons; smaller multiple-of-eight tiles with 32-pixel context padding can
reduce memory use, but must be checked for seams. `--timeout` applies to the ncnn
subprocess only, not to PyTorch's in-process inference.

Each pack's manifest records source, checkpoint, architecture and adapter hashes,
device, processing method, original/output dimensions and output hash. Successful
matching files are reused on subsequent runs. Failed jobs are recorded, the batch
continues and the script returns nonzero. Architecture/checkpoint files are local
inputs; the processing script never downloads anything.

The ncnn backend groups 16 pending images per model load by default. Its output
was checked against the approved per-image samples and matched pixel for pixel.
Use `--batch-size 1` for per-image execution. A failed batch retries its images
individually. Completed outputs retain the same resume fingerprints across batch
sizes. The validator checks the full source inventory, source/output hashes,
PNG decoding and exact dimensions, then writes `validation.json` into the pack.

Downloaded architecture revisions and licences are retained under
`build/third_party/`: SwinIR commit
`6545850fbf8df298df73d81f3e8cba638787c8bd`, BasicSR commit
`8d56e3a045f9fb3e1d8872f92ee4a4f07f886b0a`. The RealESRNet adapter supplies
inference-only BasicSR helpers and loads all checkpoint parameters strictly.
Checkpoint loading uses `weights_only=True`. The original Real-ESRGAN macOS
bundle came from official release v0.2.5.0, file
`realesrgan-ncnn-vulkan-20220424-macos.zip`, SHA-256
`e0ad05580abfeb25f8d8fb55aaf7bedf552c375b5b4d9bd3c8d59764d2cc333a`.

## Full-pack policy

The inventory contains 844 images: 837 scene, zoom, inventory, menu, UI and sprite
images use AI upscaling, one mask uses nearest-neighbour scaling, and six
bitmap font sheets are skipped for outline-font replacement (see
[FONTS.md](FONTS.md)). There are currently no multi-frame GIFs; future animated
inputs are rejected rather than silently reduced to one frame.

All 132 sprites use the pack's AI model. Earlier packs included these sprites
as nearest-neighbour enlargements, which retained their original pixelation.
The HD renderer derives sprite key coverage from the original RGB565 pixels
in `hd_register`, so AI changes to RGB artwork do not change which logical
pixels are transparent. Keep actual mask images on nearest-neighbour scaling.

To update sprites in the existing Upscayl High Fidelity pack and package it
with runtime outline fonts:

```sh
python3 tools/upscale_assets.py --include 'Sprites/*' \
  --output build/hd-upscayl-high-fidelity \
  --binary /Applications/Upscayl.app/Contents/Resources/bin/upscayl-bin \
  --models /Applications/Upscayl.app/Contents/Resources/models \
  --model high-fidelity-4x
python3 tools/validate_hd_assets.py --pack build/hd-upscayl-high-fidelity
FADE_HD_PACK=build/hd-upscayl-high-fidelity tools/android_build.sh --hd --runtime-fonts
```

JSON rules can override individual assets using a relative `glob`, `method`
(`ai`, `lanczos`, `nearest` or `skip`) and optional explicit `key_rgb` triplet.
The last matching rule wins. Transparency is enlarged independently with nearest
neighbour when AI or an explicit colour key is used. Colour keys need review:
black is also opaque artwork, and the original runtime's RGB565 key comparisons
are not equivalent to indiscriminately making all source black pixels transparent.
Using AI on keyed RGB artwork can introduce edge halos; review it before enabling
such overrides. Bitmap font processing cannot be enabled through rules.

To run the selected model over the default full inventory, remove `--include`
and use a separate pack directory. The resulting pack represents about 1.42 GiB of decoded RGBA
pixels in total; that is not its PNG disk size or a required simultaneous memory
allocation. Images should be loaded on demand.

## Rendering constraints

JPEG sprites contain rectangular patches of the room behind the object. AI
upscaling the room and each patch independently can produce visible box edges.
The HD renderer now blends the outer two logical pixels (eight native pixels)
of `sprites/*.ifj` into the destination using a smooth coverage ramp; tiny
patches use a narrower band. The centre remains fully detailed. BMP cutouts
and explicitly masked blits retain their original coverage. Original RGB565
writes, gameplay geometry and saves are preserved. This softens seams; it
does not correct colour or texture differences throughout an entire patch,
and artwork touching its outer edge also receives the blend.

`build/fade-android-sprite-seams.apk` includes this renderer with the compressed
Upscayl High Fidelity images, runtime outline fonts and FlashSR audio. Both
ABIs build; arm64 renderer and font regressions pass, including patch edges,
clipping, sharp centres, BMP coverage and saving/restoring a blended patch
without blending it twice. Its media audit verifies all 838 images and 109
sounds with zero errors. A three-example compositing preview is retained at
`build/sprite-seams-comparison.png`. The replacement APK starts and loads the
existing bedroom save on the arm64 emulator; captures are under
`build/probes/sprite-seams-*`. Full campaign and physical-device visual review
remain outstanding.

```sh
FADE_HD_PACK=build/hd-upscayl-high-fidelity-compressed \
FADE_RUNTIME_FONTS_APK_OUTPUT=../../build/fade-android-sprite-seams.apk \
tools/android_build.sh --hd --runtime-fonts --remastered-audio
```

A 4× portrait canvas is 960×1280; a typical 240×180 scene becomes 960×720.
Logical gameplay coordinates remain at 240×320 to preserve scene hotspots,
scripts, button hitboxes and saves. HD artwork is associated with the original
image allocation while the game continues to receive original dimensions.

The recovered engine still operates on fixed RGB565 pixel buffers. Returning
larger dimensions would change layout and invalidate buffer/stride assumptions.
The HD renderer mirrors those operations in separate native buffers and enables
PNG decoding in stb_image. Images load on demand and their native stores are
released with the corresponding logical allocation.

The upscaling scripts remain asset preparation tools; renderer integration lives
in maintained port source and fixups rather than the generated decompilation.
