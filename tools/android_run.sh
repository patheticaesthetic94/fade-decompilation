#!/bin/sh
# Build, install and start the Android port, then show its log: tools/android_run.sh [trace] [seconds]
set -e
cd "$(dirname "$0")/.."
tools/android_build.sh assembleDebug >/dev/null
adb install -r port/android/app/build/outputs/apk/debug/app-debug.apk >/dev/null
adb shell setprop debug.fade.trace "$([ "$1" = trace ] && echo 1 || echo 0)"
adb shell am force-stop org.fadeport.fade
adb logcat -c
adb shell am start -n org.fadeport.fade/org.fadeport.fade.FadeActivity >/dev/null
sleep "${2:-6}"
adb logcat -d | grep -E 'SDL/APP|F DEBUG|F libc' | sed -E 's/^.{31}//' | cut -c1-200
adb exec-out screencap -p > build/shot.png
