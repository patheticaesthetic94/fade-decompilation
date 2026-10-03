#!/bin/sh
# Build the Android APK: the web player's page (Home, Walkthrough, Help, device) around the native game,
# with both editions (Home picks Classic or Remastered): tools/android_build.sh [Gradle tasks...]
# Remastered uses the web's JPEG q92 artwork (FADE_HD_JPEG=0 keeps the lossless PNGs, a ~400 MB APK).
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
if [ "${FADE_HD_JPEG:-92}" = 0 ]; then python3 tools/stage_assets.py --output build/android-assets
else python3 tools/stage_assets.py --output build/android-assets --hd-jpeg "${FADE_HD_JPEG:-92}"; fi
python3 tools/stage_android_page.py build/android-assets
printf 'sdk.dir=%s\n' "$ANDROID_HOME" > port/android/local.properties
[ "$#" -gt 0 ] || set -- assembleDebug
cd port/android
./gradlew -q "$@"
