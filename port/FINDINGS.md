# Android port findings — 2026-09-28

The port now builds for arm64-v8a and x86_64. On the arm64 Android 35 emulator,
English opening gameplay, object interactions and persistent save/load work.
After a physical-device startup failure was fixed, the user reported: “the port
seems to work okay so far.” This confirms preliminary device operation; it does
not establish full campaign, audio or lifecycle coverage. The phone model and
Android version were not supplied.

[README.md](README.md) contains build commands and controls. [../CLAUDE.md](../CLAUDE.md)
contains the resource formats, decompiler workflow and port architecture.

## Architecture and source ownership

Fade 1.09 is the original 2001 Pocket PC ARM game. `app/Setup.exe` remains the
read-only distribution input. `extracted/` holds the original executable and
encoded game files; `assets/` holds converted resources for inspection. French
asset names are developer filenames; the scripts and player-facing text in this
distribution are English.

Ghidra emits `decomp/game.c`, `decomp/lib.c` and `decomp/fade_types.h`.
`tools/mkport.py` converts the recovered game source into `port/gen/`, using
`port/patches.txt` and `port/fixups/` for necessary corrections. SDL2 and
`port/src/` replace the Pocket PC APIs. Do not hand-edit generated files:
durable symbols, structs and signatures belong in `tools/ghidra/symbols.txt`.

The original image is mapped at 0x10000 so recovered global addresses remain
valid. Game pointers use clang `__ptr32 __uptr`; heap memory and the game
thread's stack must stay low. Pointer-to-signed-int conversions further motivate
keeping both below 2 GB. The existing intermediate-LLVM compiler launcher
fixes narrow-store miscompilation through `__ptr32` on AArch64. Original stack
frame layout and signed-char semantics must also be preserved.

## Missing menu buttons

Initial behavior: the title animated, but the menu displayed only Quit.

Original ARM instructions in `Menu_AddButton` (0x1f35c, particularly
0x1f370–0x1f3ac) establish trailing state and id arguments. Ghidra omitted them
from the signature and dropped their stores. The button record needs state at
0x2b, savedState at 0x2c and id at 0x30, within a 0x34-byte `MenuButton`.

The durable fix adds these fields and types parameter 12 as `char` and parameter
13 as `int` in `symbols.txt`, then regenerates the sources. `Menu_AddButton`
now stores state, savedState and id; callers supply the original values. The
recovered ids are New Game=1, Continue=2, Load=3, Save=4, Quit=5 and Credits=6.
Full menu rendering and early-game availability were checked in the emulator.
Credits content itself was not exercised.

Evidence: `build/menu-before.png`, `build/menu-after.png` and
`build/probes/final-menu.png`.

## Quit and startup registry handling

Quit sends WM_CLOSE (0x10). The old `DefWindowProcW` stub ignored it.
`port/src/win32.c` now posts WM_DESTROY (2), allowing the original cleanup and
PostQuitMessage path to finish. The emulator log records `WinMain returned 0`
and the activity closes. Evidence: `build/probes/final-quit.log` and `.png`.

Recovered startup queries the registry Install_Dir, then checks RegCloseKey's
result rather than the failed query's result. The previous runtime returned
ERROR_FILE_NOT_FOUND without initializing the directory buffer. A zero-filled
arena happened to produce a bare backslash prefix, masking this dependency.

`port/src/files.c` now supplies the UTF-16 REG_SZ `\Program Files\fade`, including
its terminator, with size-query and short-buffer handling. Existing path
translation strips that prefix and resolves case-insensitive APK asset names.
Final-build logs confirm the canonical prefix is used. Empty-path file-open
attempts still appear for optional empty filenames; their presence alone does
not indicate an asset-loading failure.

## Physical-device memory failure and fix

The reported dialog was:

```text
arena: cannot map 0x8000000 bytes at 0x400000 (got 0x7804378000)
```

The old allocator requested a 128 MB heap at 0x400000 using an mmap address hint,
then required an exact result. The phone returned a high address. The report
proves that the fixed-address assumption failed; no phone memory-map dump was
available to establish which mapping or device policy caused it.

`port/src/lowmem.h` now searches for free ranges below 0x80000000, starting at
0x400000 and stepping by 16 MB. Heap (128 MB) and stack (16 MB) are reserved
independently. Linux reservations use MAP_FIXED_NOREPLACE, which avoids replacing
existing mappings. Return addresses are checked even on older kernels that
ignore the flag, and unwanted mappings are released. Failure diagnostics
include the region and system error. The original image still requires its
fixed address; it is not relocated by this change.

`main.c` now checks pthread attribute initialization, explicit stack assignment
and thread creation, and destroys the attributes after creation. A failed stack
assignment cannot silently put game locals on a high default stack.

`tools/tests/lowmem.c` reserves the entire old heap/stack range, writes sentinel
bytes, attempts a conflicting reservation, then reserves and writes a relocated
heap and stack. It checks the low-address limit, non-overlap and preservation
of the original sentinels. Compiled with the pinned NDK and run on the arm64
emulator, it reported:

```text
PASS: occupied=0x400000 heap=0x9400000 stack=0x11400000; existing mappings preserved
```

The rebuilt app also booted and loaded the existing scene-3 save in the emulator.
Evidence: `build/probes/lowmem-loaded.png` and `.log`. The replacement supplied
to the user is `build/fade-android-memory-fix.apk` (18,342,037 bytes), copied from
the debug APK. The user subsequently confirmed preliminary operation on the
phone. Future builds update the standard Gradle output, not that named copy.

## Gameplay and save findings

The apparent opening-scene stall was the original script waiting for text
paging, not a runtime deadlock. Native stack inspection traced it to Script_Run
opcode 0x19. Tapping the down arrow near game coordinates (225,276) advances
pages and eventually the scene. Dialogue options also scroll with the arrows;
additional replies can be below the visible lines.

Emulator coverage includes scene 1's bedroom introduction, Anne in scene 2,
scrolling and choosing a reply, and transition to daytime bedroom scene 3.
Inventory shows My Diary. The bedroom plant popup and its English Examine
description work. Diary contents, item use and later puzzles remain untested.

Saving scene 3 to slot 1 produced `build/save1.fad`, 1,134,011 bytes. Its packed
header decodes with `<HBBIBBBI` as scene, month, day, elapsed days, hour, minute,
second and checksum. The captured values were `(3,9,28,0,0,10,43,1669)`.
The checksum matched:

```text
scene + 2 * (month + 2 * (day + 2 * (hour + 2 * (minute + 2 * second))))
```

After force-stop/relaunch, Load displayed the bedroom thumbnail and saved time,
then restored scene 3. Loading was repeated after installing the memory fix.
Saves live in private `files/save/`; reinstalling with `adb install -r` preserved
the slot. Clearing app data or uninstalling removes it. The local captured save
is diagnostic evidence, not an APK asset.

Evidence includes `build/scene1.png`, `build/scene2.png`,
`build/dialogue-third.png`, `build/reply.png`, and `build/probes/` captures for
`scene3`, `inventory`, `object-menu`, `examine`, `save-slots`, `save-confirm`,
`saved`, `load-confirm` and `loaded`, with associated logs where captured.

## Build and diagnostic reliability

`tools/decompile.sh` previously hid headless-tool failures behind a filtered
pipeline. It now stages all three exports, checks completion and errors, and
replaces generated files only after successful export. Failed runs retain
diagnostics in `build/decomp.log`. A complete regeneration was verified with
438 game functions and 96 types. On this Mac Ghidra worked with the Homebrew
OpenJDK 25 JAVA_HOME documented in the README.

`tools/portcheck.sh` now propagates clang's failure status. Syntax checks reported
zero errors; they check generated game code and fixups, while Android builds
compile the platform runtime. Debug APK builds succeeded for both configured
ABIs using SDK 35, NDK 29.0.14206865 and SDL2 2.32.10.

`tools/android_probe.py` taps in logical 240x320 coordinates, maps them into the
centered portrait display, and records a screenshot and app-PID-filtered logs.
It captures the PID before tapping so Quit logs remain collectable. It neither
builds nor starts the app and does not clear data. Startup animation and nested
game message loops can delay handling; inspect the captured screen before
assuming a tap sequence completed. Some exploratory captures show intermediate
states, such as `lowmem-menu` during animation and `lowmem-load` at the popup.

Optional touch tracing records message type, coordinates, menu/game state and
scene. Unrelated emulator process crashes appeared in unfiltered system logs;
they are not evidence of a Fade crash. No Fade native crash was observed in the
tested gameplay paths.

## Menu Quit and reopen (2026-09-28)

Reproduced the reported error on the arm64 Android 35 emulator. Menu Quit
returned from WinMain with status 0 and finished SDLActivity, but Android kept
PID 11757 alive. Reopening ran SDL_main in that same process, reserved another
heap, then failed mapping the PE image at 0x10000 with `File exists`. The first
session's image, heap, stack and native static state were still resident.

The app now uses `org.fadeport.fade.FadeActivity`, an SDLActivity subclass.
Its onDestroy calls SDL's cleanup first (including joining the native thread),
then ends the process. This preserves the runtime's assumption of one game
session per process without overwriting occupied mappings or trying to restart
partially reset native state. The Gradle source set includes the app's Java
directory, and the manifest and launch helper use the new activity.

`python3 tools/tests/restart.py` passed three menu Quit/reopen cycles: PIDs
12357 → 12484 → 12563 → 12643. Each Quit returned from WinMain normally and
ended the process; each reopen rendered the menu without a fatal error.
Home/resume retained PID 12357. The existing slot-1 save's SHA-256 stayed
`16a427ce44706d6242751521b02489e2bbf76bd4cc95da773978d3b01ef54f1a` through
the APK update and all cycles. Evidence is under `build/restart-test/`.

The replacement is `build/fade-android-quit-reopen-fix.apk` (436,749,800 bytes),
built for arm64-v8a and x86_64. Media validation passed for all 109 enhanced
sounds, 838 compressed HD images, runtime fonts and both native ABIs; the report
is `build/quit-reopen-media-validation.json`. The physical-device Quit/reopen
path and x86_64 execution remain untested.

## Remaining validation

- Local media preparation completed separately from the APK: FlashSR produced
  all 109 sound effects at 48 kHz PCM16; independent inventory/hash/duration/
  channel/clipping checks passed, and all 109 were reused on a second run.
  Lossless compression covered 1,718 PNGs across 10 directories, saving
  171.68 MiB with exact RGBA equality. Both compressed full HD packs passed
  validation with 838 files each. See [MEDIA.md](MEDIA.md) and the durable
  [results snapshot](media-results-2026-09-28.json). Listening approval, audible
  Android playback of the enhanced pack and APK integration remain open.
- Full campaign, later scene links, close-up/zoom views, diary reading, item
  combinations, puzzle state, all save slots, overwrite/delete and endings.
- Audible playback: emulator testing used audio disabled; API calls alone do
  not verify sound output.
- Android background/resume, interruption handling and system Back behavior.
- Detailed phone coverage, including device/OS information; x86_64 execution
  has not been tested even though it builds.
- Compatibility across kernel versions and page sizes. Low-memory candidates
  are aligned for 4 KB and 16 KB pages, but 16 KB device testing is not recorded.

Compatibility stubs remain in the runtime. Treat the current state as working
early gameplay with preliminary phone confirmation, not full-game certification.
