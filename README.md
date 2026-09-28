<p align="center">
  <img src="web/fade-icon.png" alt="Fade Decompiled" width="120">
</p>

<h1 align="center">Fade Decompiled</h1>

<p align="center">
  Complete decompilation and native Android and Web port of the game Fade (version 1.09) originally and only released for PocketPC. Developed by Fade Team in 2001, this game was previously unable to be played by any modern device without running a virtual machine and legacy software.
</p>

<p align="center">
  <a href="https://patheticaesthetic94.github.io/fade-decompilation/"><b>▶ Play in your browser</b></a>
   · 
  <a href="https://github.com/patheticaesthetic94/fade-decompilation/releases"><b>⬇ Download the latest Android release</b></a>
   · 
  <a href="https://www.reddit.com/r/1112byAghartaStudio/"><b>💬 Join the 1112 Reddit</b></a>
</p> 

## Quick start

- [Play the Original or HD on web](https://patheticaesthetic94.github.io/fade-decompilation/) - A port of the game for modern browsers which runs the original and HD versions of the game. Saves are kept in your browser and shared between editions, but can also be exported.

- [Android releases](https://github.com/patheticaesthetic94/fade-decompilation/releases/latest) - Download either the original version of the game or the HD version of the game as separate APK files. Both require Android 7.0+ and support arm64-v8a and x86_64. They share the app ID and signing key: install one over the other to switch editions and preserve saves. Uninstalling or clearing app data removes saves.

## HD Remaster (Optional)

Whilst the game can be enjoyed in it's original resolution using all of it's original assets, you could also choose to play with HD remastered assets:

- All backgrounds, scenes, inventory items and UI elements have been AI upscaled using the High Fidelity model. 

- All sound effects have been processed to be made clearer and higher resolution using AudioSR.

- A brand new text rendering engine has been put in place to render text natively without relying on pre-baked bitmap images doing the work. This allows fonts to be altered if needed by the individual.



## Features

- **Completely decompiled** source code to preserve this game into the future by allowing anyone to recompile the game for any device in the future.

- **Native** and pre-built for web and Android devices. This is not emulation or a virtual machine. This is the game running on device as though it was made for it.

- **Removed loading** from the beginning of the game which on an emulator or real device could take minutes.

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
