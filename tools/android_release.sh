#!/bin/sh
# Build both signed release editions. Signing credentials stay outside Git.
set -eu
cd "$(dirname "$0")/.."
: "${FADE_RELEASE_KEYSTORE:?Set FADE_RELEASE_KEYSTORE to your private keystore}"
: "${FADE_RELEASE_PASSWORD_FILE:?Set FADE_RELEASE_PASSWORD_FILE to a private password file}"
mkdir -p build/releases
FADE_HD_PACK=hd-assets FADE_AUDIO_PACK=hd-audio tools/android_build.sh clean assembleRelease
cp port/android/app/build/outputs/apk/release/app-release.apk build/releases/fade-android-original.apk
FADE_HD_PACK=hd-assets FADE_AUDIO_PACK=hd-audio tools/android_build.sh --hd clean assembleRelease
cp port/android/app/build/outputs/apk/release/app-release.apk build/releases/fade-android-hd.apk
