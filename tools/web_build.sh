#!/bin/sh
# Run after sourcing emsdk_env.sh. Outputs build/web (one engine, Classic + Remastered data) for Pages or a local server.
set -eu
cd "$(dirname "$0")/.."
command -v emcc >/dev/null || { echo 'Source emsdk_env.sh (Emscripten 4.0.15) first.' >&2; exit 1; }
ASSETS=${FADE_WEB_ASSETS:-build/web-assets}
if [ ! -f "$ASSETS/fade/files.txt" ] || [ ! -f "$ASSETS/hd/files.txt" ]; then
  # JPEG keeps the Remastered download near 90 MB instead of 400 MB; Android keeps lossless PNGs.
  python3 tools/stage_assets.py --output "$ASSETS" --hd-jpeg 92
fi
python3 tools/mkport.py
rm -rf build/web
mkdir -p build/web build/web-objects
cp -R web/. build/web/
for src in port/gen/game.c port/gen/funcs.c port/fixups/*.c port/src/*.c; do
  obj="build/web-objects/$(basename "$(dirname "$src")")-$(basename "$src" .c).o"
  emcc -c "$src" -o "$obj" -Iport/include -Iport/src -Iport/gen -Iport/third_party \
    -std=gnu11 -O2 -w -fsigned-char -fno-strict-aliasing -fwrapv \
    -Wno-error=int-conversion -Wno-error=incompatible-pointer-types \
    -Wno-error=incompatible-function-pointer-types -sUSE_SDL=2
done
# Game data is not preloaded: the player downloads the classic parts, plus the remastered parts when chosen.
emcc build/web-objects/*.o -o build/web/fade.js -O2 --profiling-funcs -sUSE_SDL=2 \
  -sASYNCIFY=1 -sEMULATE_FUNCTION_POINTER_CASTS=1 -sASYNCIFY_STACK_SIZE=16777216 -sSTACK_SIZE=16777216 \
  -sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=268435456 -sMAXIMUM_MEMORY=2147483648 \
  -sGLOBAL_BASE=4194304 -sMODULARIZE=1 -sEXPORT_NAME=createFade \
  -sFORCE_FILESYSTEM=1 -sEXPORTED_RUNTIME_METHODS='["FS","IDBFS","callMain","HEAPU8","ENV"]' \
  -sEXPORTED_FUNCTIONS='["_main","_port_set_lcd"]' \
  -sINVOKE_RUN=0 -sEXIT_RUNTIME=1 -sENVIRONMENT=web -lidbfs.js -lm
# Version the page's code so browsers never pair a new release with a cached engine or player.
BUILD=$(cat build/web/fade.js build/web/fade.wasm build/web/player.js build/web/site.css | shasum | cut -c1-12)
perl -pi -e "s/\?v=dev/?v=$BUILD/g" build/web/index.html build/web/player.js
python3 tools/pack_web_data.py "$ASSETS" build/web/data
python3 tools/validate_web.py build/web
