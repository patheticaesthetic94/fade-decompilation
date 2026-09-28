#!/bin/sh
# One line per game function (addr name size | callees | strings) -> build/funcindex.txt.
# Runs against the existing Ghidra project (after tools/decompile.sh), read-only, ~15s.
set -e
cd "$(dirname "$0")/.."
"$(brew --prefix ghidra)/libexec/support/analyzeHeadless" build/ghidra fade -process Fade.exe -noanalysis -readOnly \
  -scriptPath tools/ghidra -postScript FuncIndex.java "$PWD/build/funcindex.txt" 29d40 2>&1 | grep -E 'ERROR' || true
echo "build/funcindex.txt: $(awk '$2 ~ /^FUN_/' build/funcindex.txt | wc -l | tr -d " ") unnamed of $(wc -l < build/funcindex.txt)"
