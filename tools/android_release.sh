#!/bin/sh
# Build the signed release APK (Classic and Remastered in one app). Signing credentials stay outside Git.
set -eu
cd "$(dirname "$0")/.."
: "${FADE_RELEASE_KEYSTORE:?Set FADE_RELEASE_KEYSTORE to your private keystore}"
: "${FADE_RELEASE_PASSWORD_FILE:?Set FADE_RELEASE_PASSWORD_FILE to a private password file}"
mkdir -p build/releases
tools/android_build.sh clean assembleRelease
cp port/android/app/build/outputs/apk/release/app-release.apk build/releases/fade-android.apk
ls -la build/releases/fade-android.apk
