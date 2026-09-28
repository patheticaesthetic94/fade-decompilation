#!/bin/sh
# Build original or HD Android APK: tools/android_build.sh [--hd] [Gradle tasks...]
set -eu
cd "$(dirname "$0")/.."
HD=0
if [ "${1:-}" = --hd ]; then HD=1; shift; fi
SDL=SDL2-2.32.10
export ANDROID_HOME=${ANDROID_HOME:-$HOME/Library/Android/sdk}
mkdir -p build/third_party
if [ ! -d "build/third_party/$SDL" ]; then
  curl -sfL "https://github.com/libsdl-org/SDL/releases/download/release-2.32.10/$SDL.tar.gz" -o build/third_party/sdl.tar.gz
  tar xzf build/third_party/sdl.tar.gz -C build/third_party
  rm build/third_party/sdl.tar.gz
fi
python3 tools/mkport.py
rm -rf build/android-assets
mkdir -p build/android-assets/fade
(cd extracted && find . -type f ! -name '.DS_Store' | sed 's|^\./||' | sort > ../build/android-assets/fade/files.txt
 tar cf - -T ../build/android-assets/fade/files.txt) | tar xf - -C build/android-assets/fade
if [ "$HD" = 1 ]; then
  python3 tools/prepare_hd_apk.py
  python3 tools/prepare_runtime_fonts.py
  python3 tools/prepare_audio_apk.py
fi
printf 'sdk.dir=%s\n' "$ANDROID_HOME" > port/android/local.properties
[ "$#" -gt 0 ] || set -- assembleDebug
cd port/android
./gradlew -q "$@"
