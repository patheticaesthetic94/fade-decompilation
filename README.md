# Fade for Android and the web

Buildable Android port of Fade 1.09, with English game text and original or HD assets.

## Play in your browser

[Play Original or HD](https://patheticaesthetic94.github.io/fade-decompilation/).
Click or tap to play; saves are kept in your browser and shared between editions.
HD includes 4× artwork, outline fonts, and enhanced sounds. Its download is about
411 MiB; Original is about 12 MiB. See [browser build and Pages instructions](port/WEB.md).

## Downloads

[Android releases](https://github.com/patheticaesthetic94/fade-decompilation/releases/latest) provide two signed APKs:

- **Original:** original graphics, bitmap fonts, and sounds.
- **HD:** 838 images at 4× resolution, outline fonts, and 109 enhanced sounds.

Both use native adaptive launcher icons on Android 8+ and circular fallback icons on Android 7. Both require Android 7.0+ and support arm64-v8a and x86_64. They share the app ID and signing key: install one over the other to switch editions and preserve saves. Uninstalling or clearing app data removes saves.

## Build

Install Python 3, JDK 17+, Android SDK platform 35, NDK `29.0.14206865`, and Android CMake `3.22.1` or newer. Set `ANDROID_HOME` to the SDK path; the macOS default is `~/Library/Android/sdk`. The first build downloads SDL2 2.32.10, Gradle 8.11.1, and Android build dependencies. No third-party Python packages or decompiler installation are needed.

```sh
tools/android_build.sh       # original debug APK
tools/android_build.sh --hd  # HD debug APK
```

Output: `port/android/app/build/outputs/apk/debug/app-debug.apk`.

For signed releases, supply your own private keystore and password file:

```sh
export FADE_RELEASE_KEYSTORE=/absolute/path/to/fade-release.jks
export FADE_RELEASE_PASSWORD_FILE=/absolute/path/to/password.txt
export FADE_RELEASE_KEY_ALIAS=fade-release
tools/android_release.sh
```

The key and keystore use the same password. Outputs: `build/releases/fade-android-original.apk` and `build/releases/fade-android-hd.apk`. Use the same signing key for future updates.

## Required inputs

- `decomp/`: recovered game source and types used by the source generator.
- `port/`: native runtime, fixups, Android project, app icon, fonts, and third-party headers/notices.
- `extracted/`: original encoded resources and executable data image required at runtime.
- `hd-assets/`, `hd-audio/`: HD resources and manifests used during staging.
- `tools/`: source generation, compiler correction, asset staging, and build scripts.

Generated code, build outputs, caches, machine settings, and signing keys stay outside Git. Fade resources belong to their original creators; font licenses and third-party notices are retained.
