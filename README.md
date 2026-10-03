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

- [Play on the web](https://patheticaesthetic94.github.io/fade-decompilation/) - The game runs inside a recreated Pocket PC on your desk. Choose **Classic** or **Remastered** on its screen, and use its direction pad and buttons or your keyboard. Saves are kept in your browser and shared between editions, but can also be exported.

- [Android release](https://github.com/patheticaesthetic94/fade-decompilation/releases/latest) - One APK holds both editions and the web player's interface: the same Pocket PC Home (**Classic** or **Remastered**, language flags, screen filter, save backup/restore), Walkthrough, Help, dock and device view, around the native game. Requires Android 7.0+ and supports arm64-v8a and x86_64. It installs over earlier Original or HD releases and keeps their saves. Uninstalling or clearing app data removes saves.

- **Pocket PC screen filter** (web and Android) - Recreates a 2001 3.8" transflective screen: the 240 × 320 pixel grid with RGB stripes, 65,536 colours, raised blacks and a narrow gamut, an uneven front light and slow pixel response. It can be switched on or off while playing.

## HD Remaster (Optional)

Whilst the game can be enjoyed in it's original resolution using all of it's original assets, you could also choose to play with HD remastered assets:

- All backgrounds, scenes, inventory items and UI elements have been AI upscaled using the High Fidelity model. 

- All sound effects have been processed to be made clearer and higher resolution using AudioSR.

- A brand new text rendering engine has been put in place to render text natively without relying on pre-baked bitmap images doing the work. This allows fonts to be altered if needed by the individual.



## Features

- **Completely decompiled** source code to preserve this game into the future by allowing anyone to recompile the game for any device in the future.

- **Native** and pre-built for web and Android devices. This is not emulation or a virtual machine. This is the game running on device as though it was made for it.

- **French text** (web) from the original French release, grafted onto the fixed 1.09 scripts. Pick the French flag beside **Language** on the web player's Home menu; saves work in both languages. See [port/LANGUAGES.md](port/LANGUAGES.md).

- **Removed loading** from the beginning of the game which on an emulator or real device could take minutes.

## Build

Install Python 3, JDK 17+, Android SDK platform 35, NDK `29.0.14206865`, and Android CMake `3.22.1` or newer. Set `ANDROID_HOME` to the SDK path; the macOS default is `~/Library/Android/sdk`. The first build downloads SDL2 2.32.10, Gradle 8.11.1, and Android build dependencies. Staging needs Pillow (`pip install pillow`) to re-encode Remastered artwork as JPEG, as the web build does; no decompiler installation is needed.

```sh
tools/android_build.sh       # debug APK with Classic and Remastered (FADE_HD_JPEG=0: lossless PNG artwork)
```

Output: `port/android/app/build/outputs/apk/debug/app-debug.apk`.

To build the web player, see [port/WEB.md](port/WEB.md).

For signed releases, supply your own private keystore and password file:

```sh
export FADE_RELEASE_KEYSTORE=/absolute/path/to/fade-release.jks
export FADE_RELEASE_PASSWORD_FILE=/absolute/path/to/password.txt
export FADE_RELEASE_KEY_ALIAS=fade-release
tools/android_release.sh
```

The key and keystore use the same password. Output: `build/releases/fade-android.apk`. Use the same signing key for future updates.

## Required inputs

- `decomp/`: recovered game source and types used by the source generator.
- `port/`: native runtime, fixups, Android project, app icon, fonts, and third-party headers/notices.
- `extracted/`: original encoded resources and executable data image required at runtime.
- `lang/fr/Data/`: French game text that replaces `extracted/Data` when `FADE_LANG=fr`.
- `hd-assets/`, `hd-audio/`: Remastered resources and manifests, verified and staged by `tools/stage_assets.py`.
- `tools/`: source generation, compiler correction, asset staging, and build scripts.

Generated code, build outputs, caches, machine settings, and signing keys stay outside Git. Fade resources belong to their original creators; font licenses and third-party notices are retained.
