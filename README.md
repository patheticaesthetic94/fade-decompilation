# Fade decompilation

Recovered source, original assets, HD assets, and an Android port of **Fade 1.09** (Fade Team, 2001), the Pocket PC point-and-click adventure. Game text is English; resource names retain the original French names.

## Android downloads

Get the APK you want from [Releases](https://github.com/patheticaesthetic94/fade-decompilation/releases/tag/v1.09-android.1):

| Edition | Download | Assets |
| --- | --- | --- |
| Original | [fade-android-original.apk](https://github.com/patheticaesthetic94/fade-decompilation/releases/download/v1.09-android.1/fade-android-original.apk) | Original graphics, bitmap fonts, and sounds |
| HD | [fade-android-hd.apk](https://github.com/patheticaesthetic94/fade-decompilation/releases/download/v1.09-android.1/fade-android-hd.apk) | 838 images at 4× resolution, Comic Neue / Arimo runtime fonts, and 109 enhanced 48 kHz sounds |

Both are signed **release builds** supporting Android 7.0+ (API 24), arm64-v8a and x86_64. Open the APK and allow installation from your downloading app when Android prompts.

Both editions share the application ID `org.fadeport.fade`, signing certificate, and save format. Install one over the other to switch editions while retaining saves; they occupy one installed app. These releases use a dedicated signing key, so Android cannot install them over earlier debug-signed APKs. Preserve existing saves before removing a debug build. Uninstalling or clearing app data deletes saves.

The release also includes original/HD asset archives, both walkthrough formats, validation reports, and `SHA256SUMS.txt`.

## Walkthrough and controls

Read the [step-by-step walkthrough](WALKTHROUGH.md) or download [the printable HTML version](WALKTHROUGH.html). It covers the story and endings and contains spoilers. Puzzle conditions were checked against recovered scripts and engine code; the whole route has not been played through on Android.

Tap an object and choose an action. The red chest opens inventory, the green book opens the diary, and the bottom-left emblem opens the menu. Use the up/down arrows beside text to page through narration and dialogue choices. The opening waits for the down arrow. Save and Load use three slots; saves live in the app's private `files/save/` directory.

## Included files

| Path | Contents |
| --- | --- |
| `decomp/` | Recovered game C, library C, and type definitions |
| `port/` | SDL2 compatibility layer, durable fixes, headers, Android app, runtime fonts, and research documents |
| `tools/` | Extraction, Ghidra recovery, asset preparation, build, and validation tools |
| `app/Setup.exe` | Original installer |
| `extracted/` | Original encoded install tree and executable data image required at runtime |
| `assets/` | Original resources with readable filenames and standard formats |
| `hd-assets/` | Complete compressed Upscayl High Fidelity artwork pack and provenance |
| `hd-audio/` | Complete enhanced sounds, manifest, and validation record |

Original and HD assets are in Git and in separate release archives. Build directories, model weights, caches, personal saves, machine settings, and signing credentials are excluded. Generated `port/gen/` is recreated from the recovered sources and durable fixes.

## Build from source

Requirements: Python 3, JDK 17+, Android SDK platform 35, NDK `29.0.14206865`, and Android CMake `3.22.1` or newer. Set `ANDROID_HOME` to your SDK; the macOS default is `~/Library/Android/sdk`. SDL2 `2.32.10`, Gradle `8.11.1`, and Android dependencies download on the first build. Ghidra is only needed to regenerate recovered source.

```sh
python3 -m venv build/venv
. build/venv/bin/activate
pip install -r requirements.txt

tools/android_build.sh                         # original debug APK
tools/android_build.sh --hd --runtime-fonts --remastered-audio  # HD debug APK
```

Debug output: `port/android/app/build/outputs/apk/debug/app-debug.apk`. Override bundled packs with `FADE_HD_PACK` and `FADE_AUDIO_PACK` if desired.

To build both signed releases, supply a private keystore and password file outside the repository:

```sh
export FADE_RELEASE_KEYSTORE=/absolute/path/to/private/fade-release.jks
export FADE_RELEASE_PASSWORD_FILE=/absolute/path/to/private/password.txt
export FADE_RELEASE_KEY_ALIAS=fade-release
tools/android_release.sh
```

The password file contains only the keystore password; the key uses the same password. Outputs are `build/releases/fade-android-original.apk` and `build/releases/fade-android-hd.apk`. APKs rebuilt with another key cannot replace published APKs in place.

Repeat extraction with `python3 tools/extract_cab.py` (requires `7z`) and `python3 tools/convert_assets.py`. Normal builds use the supplied `extracted/` and `decomp/` inputs.

## Validation and status

Release checks verify APK signatures, both native ABIs, ZIP integrity, original asset hashes, all 838 HD artwork hashes and filename mappings, all 109 enhanced sound hashes and WAV formats, and runtime font packaging. Reports and checksums accompany the release.

```sh
python3 tools/validate_hd_assets.py --pack hd-assets
python3 tools/validate_media_apk.py --apk build/releases/fade-android-hd.apk \
  --report build/releases/hd-validation.json
python3 tools/walkthrough_audit.py
tools/portcheck.sh
```

Earlier development checks covered opening gameplay, inventory, close-ups, save/load, credits, HD rendering, text layout, memory relocation, and quit/reopen on an arm64 Android 35 emulator. A user reported early gameplay working on a physical device. Full campaign completion, x86_64 execution, and subjective listening review remain open. Compatibility stubs remain; this is a work-in-progress port.

See [findings](port/FINDINGS.md), [HD rendering](port/HD.md), [text layout](port/TEXT_ENGINE.md), and [media preparation](port/MEDIA.md). These research documents retain historical experiment paths and refer to local `build/` evidence excluded from this publication. Published packs are `hd-assets/` and `hd-audio/`.

## Credits and notices

Fade and its original resources belong to their original creators. Recovered code and derived artwork/audio do not establish new ownership of the game. No blanket open-source license is asserted for game resources or recovered code.

SDL2 is fetched from its upstream distribution. Font OFL notices and bundled `stb` notices/provenance are retained. HD manifests record image and sound pipeline provenance; model weights are excluded.
