#!/bin/sh
# Build the Android APK with both editions (the launcher picks Classic or Remastered): tools/android_build.sh [Gradle tasks...]
set -eu
cd "$(dirname "$0")/.."
SDL=SDL2-2.32.10
export ANDROID_HOME=${ANDROID_HOME:-$HOME/Library/Android/sdk}
mkdir -p build/third_party
if [ ! -d "build/third_party/$SDL" ]; then
  curl -sfL "https://github.com/libsdl-org/SDL/releases/download/release-2.32.10/$SDL.tar.gz" -o build/third_party/sdl.tar.gz
  tar xzf build/third_party/sdl.tar.gz -C build/third_party
  rm build/third_party/sdl.tar.gz
fi
python3 tools/mkport.py
python3 tools/stage_assets.py --output build/android-assets
printf 'sdk.dir=%s\n' "$ANDROID_HOME" > port/android/local.properties
[ "$#" -gt 0 ] || set -- assembleDebug
cd port/android
./gradlew -q "$@"
