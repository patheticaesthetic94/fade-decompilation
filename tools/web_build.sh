#!/bin/sh
# Run after sourcing emsdk_env.sh. Outputs build/web for Pages or a local server.
set -eu
cd "$(dirname "$0")/.."
command -v emcc >/dev/null || { echo 'Source emsdk_env.sh (Emscripten 4.0.15) first.' >&2; exit 1; }
ASSETS=${FADE_WEB_ASSETS:-build/web-assets}
if [ ! -f "$ASSETS/normal/fade/files.txt" ] || [ ! -f "$ASSETS/hd/hd/files.txt" ]; then
  python3 tools/prepare_web_assets.py --output "$ASSETS"
fi
python3 tools/mkport.py
mkdir -p build/web build/web-objects
cp web/* web/.nojekyll build/web/
# Compile once; both variants share the engine and select media at runtime.
for src in port/gen/game.c port/gen/funcs.c port/fixups/*.c port/src/*.c; do
  obj="build/web-objects/$(basename "$(dirname "$src")")-$(basename "$src" .c).o"
  emcc -c "$src" -o "$obj" -Iport/include -Iport/src -Iport/gen -Iport/third_party \
    -std=gnu11 -O2 -w -fsigned-char -fno-strict-aliasing -fwrapv \
    -Wno-error=int-conversion -Wno-error=incompatible-pointer-types \
    -Wno-error=incompatible-function-pointer-types -sUSE_SDL=2
done
for mode in normal hd; do
  mkdir -p "build/web/$mode"
  emcc build/web-objects/*.o -o "build/web/$mode/fade.js" -O2 --profiling-funcs -sUSE_SDL=2 \
    -sASYNCIFY=1 -sEMULATE_FUNCTION_POINTER_CASTS=1 -sASYNCIFY_STACK_SIZE=16777216 -sSTACK_SIZE=16777216 \
    -sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=268435456 -sMAXIMUM_MEMORY=2147483648 \
    -sGLOBAL_BASE=4194304 -sMODULARIZE=1 -sEXPORT_NAME=createFade \
    -sFORCE_FILESYSTEM=1 -sEXPORTED_RUNTIME_METHODS='["FS","IDBFS","callMain","HEAPU8","ENV"]' \
    -sINVOKE_RUN=0 -sEXIT_RUNTIME=1 -sENVIRONMENT=web -lidbfs.js \
    --preload-file "$ASSETS/$mode@/" -lm
done
python3 tools/validate_web.py build/web
