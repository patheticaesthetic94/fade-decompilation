#!/bin/sh
# Regenerate port/gen from decomp/ and syntax-check it; errors go to build/port.err
cd "$(dirname "$0")/.."
python3 tools/mkport.py || exit 1
clang -x c -std=gnu11 -fms-extensions -fsigned-char -fsyntax-only -ferror-limit=0 -w -Wno-error=int-conversion -Wno-error=incompatible-function-pointer-types -Wno-error=incompatible-pointer-types -Iport/include -Ibuild/third_party/SDL2-2.32.10/include port/gen/game.c $(ls port/fixups/*.c 2>/dev/null) 2> build/port.err
status=$?
echo "errors: $(grep -c 'error:' build/port.err)"
exit "$status"
