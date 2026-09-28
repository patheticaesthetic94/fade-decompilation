#!/bin/sh
# Decompile extracted/Fade.exe with Ghidra headless into decomp/game.c (game code) and decomp/lib.c (thunks, CRT, MFC)
# Usage: tools/decompile.sh [project_dir]   (project dir defaults to build/ghidra)
set -e
cd "$(dirname "$0")/.."
PROJ=${1:-build/ghidra}
LIB=29d40   # first non-game address: CRT time/tz code, then MFC-for-CE
GS="64168 2c0ab8"   # g_gameState extent: pool words inside it are GameState field offsets, not pointers
mkdir -p "$PROJ" decomp
# Stage exports so an interrupted run cannot leave mixed or truncated generated files.
OUT=$(mktemp -d "$PWD/build/decomp.XXXXXX")
LOG="$PWD/build/decomp.log"
if
"$(brew --prefix ghidra)/libexec/support/analyzeHeadless" "$PROJ" fade \
  -import extracted/Fade.exe -overwrite -scriptPath tools/ghidra \
  -preScript ApplyImports.java -postScript ApplySymbols.java -postScript TypePools.java $LIB $GS \
  -postScript AutoAccessors.java $LIB -postScript CommitSigs.java $LIB -postScript TypeThis.java $LIB -postScript DecompileAll.java "$OUT" $LIB -postScript ExportHeader.java "$OUT" > "$LOG" 2>&1
then
  grep -E 'unresolved|renamed|ERROR|REPORT' "$LOG" || true
else
  cat "$LOG" >&2
  exit 1
fi
if ! grep -q 'REPORT ExportHeader:' "$LOG" || grep -q 'ERROR' "$LOG"; then
  echo "Decompilation failed; see $LOG (exports retained in $OUT)" >&2
  exit 1
fi
for f in game.c lib.c fade_types.h; do
  test -s "$OUT/$f"
done
for f in game.c lib.c fade_types.h; do
  mv "$OUT/$f" "decomp/$f"
done
rmdir "$OUT"
