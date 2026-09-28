#!/bin/sh
# Build the Android APK: tools/android_build.sh [--hd] [--runtime-fonts] [--remastered-audio] [assembleDebug|installDebug|...]
# Needs: Android SDK (ANDROID_HOME or ~/Library/Android/sdk) with NDK 29 and CMake, JDK 17+, network on first run.
set -e
HD=0
RUNTIME_FONTS=0
REMASTERED_AUDIO=0
while [ "$#" -gt 0 ]; do
  case "$1" in
    --hd) HD=1; shift ;;
    --runtime-fonts) RUNTIME_FONTS=1; shift ;;
    --remastered-audio) REMASTERED_AUDIO=1; shift ;;
    *) break ;;
  esac
done
cd "$(dirname "$0")/.."
SDL=SDL2-2.32.10
export ANDROID_HOME=${ANDROID_HOME:-$HOME/Library/Android/sdk}
mkdir -p build/third_party
[ -d build/third_party/$SDL ] || { curl -sfL https://github.com/libsdl-org/SDL/releases/download/release-2.32.10/$SDL.tar.gz | tar xz -C build/third_party; }
python3 tools/mkport.py
# game data -> APK assets/fade/ (+ files.txt index for case-insensitive lookup)
rm -rf build/android-assets && mkdir -p build/android-assets/fade
(cd extracted && find . -type f ! -name '_cab_header*' ! -name gamma.exe ! -name '.DS_Store' | sed 's|^\./||' | sort > ../build/android-assets/fade/files.txt
 tar cf - -T ../build/android-assets/fade/files.txt) | tar xf - -C build/android-assets/fade
if [ "$HD" = 1 ]; then FADE_RUNTIME_FONTS=$RUNTIME_FONTS python3 tools/prepare_hd_apk.py; fi
if [ "$RUNTIME_FONTS" = 1 ]; then python3 tools/prepare_runtime_fonts.py; fi
if [ "$REMASTERED_AUDIO" = 1 ]; then python3 tools/prepare_audio_apk.py; fi
# gradle wrapper from the SDL template, pinned to a Gradle that AGP 8.7 supports
A=port/android
[ -f $A/gradlew ] || { cp build/third_party/$SDL/android-project/gradlew $A/; mkdir -p $A/gradle/wrapper;
  cp build/third_party/$SDL/android-project/gradle/wrapper/gradle-wrapper.jar $A/gradle/wrapper/;
  printf 'distributionUrl=https\\://services.gradle.org/distributions/gradle-8.11.1-bin.zip\n' > $A/gradle/wrapper/gradle-wrapper.properties; }
echo "sdk.dir=$ANDROID_HOME" > $A/local.properties
[ "$#" -gt 0 ] || set -- assembleDebug
cd $A && ./gradlew -q "$@"
if [ -f app/build/outputs/apk/debug/app-debug.apk ]; then
  if [ "$RUNTIME_FONTS" = 1 ]; then
    if [ "$HD" = 1 ]; then
      FONT_APK_OUTPUT=${FADE_RUNTIME_FONTS_APK_OUTPUT:-../../build/fade-android-runtime-fonts-hd.apk}
    else
      FONT_APK_OUTPUT=${FADE_RUNTIME_FONTS_APK_OUTPUT:-../../build/fade-android-runtime-fonts.apk}
    fi
    cp app/build/outputs/apk/debug/app-debug.apk "$FONT_APK_OUTPUT"
  elif [ "$HD" = 1 ]; then
    cp app/build/outputs/apk/debug/app-debug.apk "${FADE_HD_APK_OUTPUT:-../../build/fade-android-hd.apk}"
  fi
fi
ls -la app/build/outputs/apk/*/*.apk 2>/dev/null || true
