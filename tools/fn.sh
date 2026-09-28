#!/bin/sh
# Print decompiled bodies from decomp/game.c by address: tools/fn.sh 1d260 20ea8 ...
for a in "$@"; do
  a=$(printf '%08x' 0x$a)
  awk -v a="$a" '/^\/\/ [0-9a-f]{8} /{p=($2==a)} p' "$(dirname "$0")/../decomp/game.c" | grep -v '^\s*$'
done
