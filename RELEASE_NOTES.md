# Fade 1.09 — Android release 1

Two signed Android release builds from the same source snapshot:

| File | Edition | Bytes |
| --- | --- | ---: |
| `fade-android-original.apk` | Original graphics, bitmap fonts, and sounds | 16,459,524 |
| `fade-android-hd.apk` | 838 4× images, runtime fonts, and 109 enhanced effects | 434,621,773 |

Requires Android 7.0 or newer; includes arm64-v8a and x86_64. Both editions share an app ID and signing certificate, so installing one over the other preserves saves. These APKs have a new release certificate and cannot replace debug-signed development builds in place.

Original and HD assets are included in the repository and in `fade-original-assets.zip` and `fade-hd-assets.zip`. The original archive contains the installer, encoded install tree, and decoded resources; the HD archive contains artwork, enhanced audio, fonts, and provenance. Walkthroughs are provided in Markdown and printable HTML.

## Checks performed on 2026-09-28

- Both APKs built using `assembleRelease`, contain both native architectures, pass APK signature verification and 16 KiB ZIP alignment, and are not marked debuggable.
- Both signing certificate SHA-256 digests match.
- All 960 packaged original install files match the source bytes; the original APK has no HD, runtime-font, or enhanced-audio overlays.
- All 838 HD images match their manifest hashes and encoded filename index; all 109 enhanced sounds match their hashes, rates, channels, and durations.
- The full HD source pack passes inventory, image dimension, source hash, and output hash validation.
- HD renderer and runtime text harnesses pass against the release native libraries on the arm64 Android 35 emulator. The harnesses leave the installed app and saves untouched.
- Recovered source regeneration and syntax checks report zero errors.
- The walkthrough script audit passes its puzzle-condition checks and identifies the known briefcase/outfit source-game issue documented in the guide.

Checksums, asset reports, package details, signature verification output, and the release regression report accompany the downloads. Full campaign completion, x86_64 execution, and subjective listening review remain unverified. The port still contains compatibility stubs.
