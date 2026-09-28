# Runtime font engine investigation

Implemented on branch `font-rendering`, 2026-09-28. The optional runtime mode
opens the bundled Comic Neue Bold and Arimo TrueType files and uses natural
fractional advances, pair kerning, font baselines and line spacing. Wrapping,
drawing, paging, dialogue selection and inventory continuation lines share one
native layout. Recovered gameplay and script code continue to use logical
240×320 coordinates.

Build from the root:

```sh
tools/android_build.sh --runtime-fonts
FADE_HD_PACK=build/hd-upscayl-high-fidelity tools/android_build.sh --hd --runtime-fonts
python3 tools/tests/text.py
python3 tools/tests/hd.py
```

The outputs are `build/fade-android-runtime-fonts.apk` (original-resolution
artwork) and `build/fade-android-runtime-fonts-hd.apk` (selected 4× image pack).
Both contain arm64-v8a and x86_64 libraries. Installing with `adb install -r`
preserves existing saves. Runtime mode is independent of the image pack;
ordinary builds and `--hd` without `--runtime-fonts` keep their previous paths.

### Implementation

- `port/src/text.c` owns paragraph text, full integer line/page positions and a
  bounded 512-entry glyph-mask cache in native memory. `port/fixups/text.c`
  adapts the recovered APIs; `port/patches.txt` removes byte truncation from
  dialogue line indices. Generated source remains reproducible through mkport.
- The backend is pinned **stb_truetype 1.26**, revision and SHA-256 recorded in
  `port/third_party/stb_truetype.PROVENANCE`. This keeps the English game's
  runtime self-contained. It implements natural advances and pair kerning;
  it does not provide complex-script shaping. Only the trusted bundled fonts
  are loaded. This differs from the SDL2_ttf architecture proposed below.
- Comic Neue Bold uses a 9 logical pixel EM size; Arimo uses 7. Their font
  metrics produce 11- and 9-pixel line steps. Six colour roles share metrics
  within each family, so highlights keep line breaks stable.
- UTF-16 decoding supports surrogate pairs, normalizes surviving CP1252 curly
  apostrophes and maps invalid/unsupported glyphs to replacement ink. The
  layout splits overlong words at codepoint boundaries and handles CR/LF.
- Paragraph identities map every dialogue continuation line to its choice;
  titles and spacer lines are unselectable. Inventory continuation lines map
  to the visible item ordinal expected by the recovered inventory caller;
  highlights apply to the entire item's paragraph.
- Text masks blend into the existing native layer buffers at 4× with clipping,
  bearings and one family baseline. RGB565 mirrors/snapshots stay synchronized
  for effects and saves. Saved backgrounds retain antialias coverage.
- Typewriter drawing reveals fixed positions from the complete run, restores
  the background to prevent repeated alpha buildup and keeps 30 ms timing.
  A skip completes the line and subsequent page lines immediately.
- Popup and save/load labels use natural runs clipped inside their existing UI
  bounds. Loading progress uses the same backend. Labels overflowing fixed
  bounds clip; glyphs are never horizontally fitted into legacy bitmap cells.
- Staging includes both TTFs, their full OFL notices and hash provenance. It
  omits all six original font sheets and generated font atlases in runtime mode.

### Verification and limits

Both ABI builds pass; actual runtime execution is checked on the arm64 Android
35 emulator. `tools/tests/text.py` links the APK's native library and verifies
natural measurement (`My diary`: 33.786 logical pixels versus 43 legacy cells),
encoding, explicit newlines, long-word splitting, 601-line navigation, reflow,
wrapped choice IDs, stable colour highlights, alpha composition, saved
backgrounds, clipping, typewriter skip, inventory IDs and state reset/reuse.
The existing HD renderer regression also passes with the new library.

Interactive evidence under `build/probes/runtime-*` includes opening text,
scene transitions, dialogue paging and selecting a choice by its continuation
line. The HD build also displays save-slot labels and the Load popup, and
restores the existing bedroom save (scene 3). Physical-device testing, later
campaign/diary coverage and x86_64 runtime
remain unverified. Rasterization is at fixed 4× logical resolution, not exact
physical display resolution; the existing presentation scales that result.

The rest of this document preserves the original investigation and architecture
proposal for context and future extensions.

## What the earlier atlas HD build does

`tools/prepare_hd_apk.py` rasterizes Comic Neue Bold and Arimo into six PNG
atlases. It reads every legacy bitmap cell, preserves its advance, and stretches
or compresses the replacement ink to fit. `Font_Load` still extracts legacy
glyphs, and `hd_font` attaches the corresponding PNG pixels to those allocations.
The game draws one glyph at a time using those cell widths.

Consequently, changing the TTF does not give the game that font's natural
spacing. The runtime does not open the bundled TTF files. Modernizing only
`Glyph_BlitToLayer` cannot solve wrapping or recover kerning between letters.

Outline fonts will still become pixels for display. Runtime rasterization and
caching are compatible with this proposal: the important difference is that
layout comes from the font and text run, rather than authored bitmap cells.

## Confirmed integration points

Addresses below identify recovered functions in `decomp/game.c` and
`tools/ghidra/symbols.txt`. Durable replacements belong in `port/fixups/` and
`port/src/`; generated sources must not be edited.

| Area | Existing functions | Required behavior |
| --- | --- | --- |
| Font loading | `Font_Load` (0x1d958), `FontGlyphs_Ctor/Dtor` | Associate each legacy font identity with a native face/style; stop reading sheets in the new mode. |
| Measurement | `Font_TextWidth` (0x1e3cc), `Font_MaxGlyphWidth` (0x1d600), `Text_CountLines` (0x1e440) | Measure complete runs using the font; share the wrapping implementation. Despite its name, `Font_MaxGlyphWidth` actually returns the maximum **height**. |
| Content and wrapping | `TextList_SetText`, `AppendText`, `WrapText` (0x1d260), `Clear`, `Reset`, `SetFont`, `SetRect` | Own source text, paragraph metadata and reflow; handle explicit newlines and words wider than the panel. |
| Drawing | `Text_DrawLine` (0x1cbc0), `TextList_Draw` (0x1cda8) | Draw complete font runs at their shared baselines, with clipping to the panel. |
| Animated drawing | `Text_TypeLine` (0x1cc40), `TextList_DrawTyped` (0x1cf38) | Reveal a prelaid-out line without moving its already visible letters; retain 30 ms timing and skip behavior. |
| Paging and taps | `CalcLinesPerPage`, `PageUp/Down`, `LineUp/Down`, `AtEnd`, `HitTest`, `LineAt` | Use layout line boxes and the current visible range for both arrows and touch. |
| Dialogue | `TextList_SetDialogMenu/Menu2`, `SetDialogTitle/Reply`, `Game_DialogChoiceAtLine` (0x26f94) | Attach topic/choice identities to laid-out lines; resolve taps directly to those identities. |
| Inventory | `Game_SetInventoryText` (0x26ec4), `TextList_SetLineTag` (0x1c65c), inventory tap handling | Preserve object identity across wrapping; highlight all lines belonging to the selected object. |
| Action popups | `PopupMenu_DrawText` (0x1e9a0), item drawing/rectangles | Use the popup face and fit text inside the existing item artwork; update rectangles together if item geometry changes. |
| Save/load labels | `Menu_DrawText` (0x1fe60), `SaveMenu_DrawSlotText` | Render runs at the existing slot anchors, clipped to the available label area. |
| Loading percentage | `DrawLoadingProgress` (0x130d8) | Replace its separate per-glyph loop too; it writes both layer 1 and the direct framebuffer. |

The searched glyph call sites cover text lists, popups, save/load labels and
loading progress. Images containing lettering need separate asset work; a font
engine cannot reconstruct strings from menu/background artwork.

## Findings that affect correctness

**Dialogue must use one authoritative layout.** `Game_DialogChoiceAtLine`
currently recreates the title and each active choice and calls `Text_CountLines`
with hard-coded bounds 0x15..0xd6. Display construction uses individual title,
normal and highlighted font identities. Replacing drawing while leaving that
independent calculation can select the wrong reply. Record `choice_id` when
building the menu and assign it to every continuation line. Title and spacer
lines have no selectable identity. Preserve the visible source anchor when a
highlight rebuilds the list; changing only colour must never change line breaks.

**Inventory also couples item indices to line indices.**
`Game_SetInventoryText` changes one line's font based on the selected object.
Natural wrapping can make one object name occupy multiple lines. The new adapter
must build item-aware paragraphs from the inventory objects and adapt selection,
rather than infer object identity from a wrapped line number.

**Narrow arithmetic cannot own the new layout.** `Glyph.w/h`,
`TextList.top/page/count`, and the result of `Text_CountLines` are bytes.
`Font_TextWidth` accumulates and returns a `char`; some draw loops use a signed
char index. Keep widths and counts in native int/float storage. Compatibility
fields must have an explicit bounded mapping, and all consumers of potentially
larger line indices must move to that storage. Merely storing new widths in
`Glyph.w` still loses fractional advances and context-dependent placement.

**CString ownership is significant.** The recovered methods destroy their
by-value CString arguments. Replacements must copy text before returning and
honour that callee-destroyed convention. Preserve the corrected signatures in
`port/patches.txt`, especially `TextList_CalcLinesPerPage` and
`TextList_SetDialogReply`. Native fonts, caches and layouts must stay outside
the game's `_P32` structures; only genuine game allocations belong in its low
address arena. Purge side-table entries on reset/destruction and pointer reuse.

**The scripts are not UTF-8.** A scan of the XOR-decoded original data found:

| Input | Bytes >= 0x80 |
| --- | --- |
| `Data.Fad` | 0x91 × 8, 0x92 × 9, 0xe0 × 1, 0xe7 × 2, 0xe8 × 12, 0xe9 × 106 |
| `Book.Fad` | 0xe8 × 1 |
| `DataObjets.Fad` | 0xe8 × 1, 0xe9 × 9 |

These are whole-file counts, including script fields, not exclusively visible
prose. `port/src/crt.c` already converts ANSI CString input as Windows-1252,
mapping 0x91/0x92 to U+2018/U+2019. Other paths append characters directly;
the font adapter should accept proper UTF-16 and normalize surviving legacy
0x91/0x92 values at its boundary. Convert to UTF-8 once for the font backend,
preserving a source-offset map. Never index a 255-entry glyph table with U+2019.
Define replacement behavior for invalid UTF-16 and unsupported glyphs.

## Recommended architecture

Use a small game-specific layout service backed by **SDL2_ttf**, with its
FreeType dependency pinned and built for both Android ABIs. The existing
project uses SDL2, so select the SDL2-compatible library branch/release rather
than migrating the platform to SDL3 as part of text work. Keep the already
bundled Comic Neue Bold and Arimo faces; the six legacy identities become two
families and six colour styles with shared metrics within each family.

SDL2_ttf supplies [whole-string measurement](https://wiki.libsdl.org/SDL2_ttf/TTF_SizeUTF8)
and [antialiased ARGB line rendering](https://wiki.libsdl.org/SDL2_ttf/TTF_RenderUTF8_Blended).
Keep game-aware wrapping in the adapter so it can expose source ranges,
selection IDs and page boundaries, rather than using a wrapped surface as the
only result. Measure each candidate line as a run; adding separately measured
words or characters can lose kerning at the joins. Use the same backend,
font settings and size for measurement and rendering.

For broader language support or precise glyph-cluster reveal, add HarfBuzz to
the backend explicitly and verify the enabled build features.
[HarfBuzz](https://harfbuzz.github.io/what-is-harfbuzz.html) provides shaped glyph
IDs and positions; it does not replace paragraph layout or the renderer.
SDL2_ttf run rendering is a reasonable first backend for this English game.
FreeType alone is an alternative for direct glyph positioning, but requires
more renderer/cache code; its
[glyph metrics documentation](https://freetype.org/freetype2/docs/glyphs/glyphs-3.html)
explains why advances and ink bounds are different.

Suggested native objects:

```text
TextStyle   = face + logical size + colour + ascent/descent/line spacing
Paragraph   = source text + style + indent + selectable item/choice identity
LayoutLine  = source range + baseline + bounds + identity + rendered run
TextLayout  = paragraphs + lines + visible source anchor + reveal state
```

The default size and leading are role-level choices, independent of old cells.
Choose them visually for the existing panel areas. Fixed 240×320 logical UI
bounds remain useful: scene hotspots, script coordinates and saves need not
change when text reflows. Use a fixed line step derived from the chosen face
metrics initially; reserve mixed variable-height lines for when required.

Cache line surfaces or shaped runs by text, face, size, render scale and font
settings. Tint reusable alpha masks for colour-only highlights. Set a cache
memory limit and invalidate layout when text, bounds or size changes.
For typewriter animation, lay out the entire line first and reveal at source
character/cluster boundaries. Rendering progressively longer prefixes can
change kerning or ligatures and cause visible letters to jump. A line-surface
backend needs measured reveal boundaries and an explicit ligature policy; a
shaped-run backend can reveal its fixed clusters directly. Preserve the
original skip result across subsequent lines of the page.

## Composition and resolution

For the first implementation, render font runs into the existing **4× native
layer buffers** and maintain downsampled RGB565 copies for legacy effects and
save previews. Add a run-compositing entry point to `port/src/hd.c`, rather than
allocating faux legacy glyphs for each character. Clip using ink bounds as well
as advances, account for bearings and descenders, and update the logical pixel
snapshot consistently so `hd_sync` does not overwrite the new text later.

This reuses the HD renderer's copy/clear, saved-background, shadow/fade and
composition handling. A global text overlay would need its own equivalents
for all those operations and could otherwise leave stale popup text or draw
letters above scene objects. Animated text must update both the target layer
and direct framebuffer, as the original path does.

Runtime fonts at 4× already remove authored bitmap spacing, but presentation
still scales a 960×1280 image. Exact device-resolution rasterization is a
separate extension: `HD_SCALE` is fixed to 4 throughout `hd.c`, and
`port_present` uploads one texture. Supporting arbitrary output scale requires
either generalizing native backing stores, or retaining ordered text commands
with copy/restore/effect state and replaying them at presentation resolution.
Do not claim display-resolution rendering from a change to font loading alone.
Keep logical layout stable across output-scale changes to prevent resize-induced
page jumps; use consistent logical metrics and regenerate raster caches.

## Offline measurements

Pillow/FreeType measurements at the existing preparation sizes demonstrate
that natural advances differ substantially from the preserved cells:

| String and role | Sum of legacy cell widths | Natural outline advance, divided by 4 |
| --- | --- | --- |
| `My diary`, Comic Neue Bold at 34 px | 43 | 32 |
| `Examine`, Arimo at 26 px | 29 | 25 |
| Diary sentence beginning `Using a mirror`, Comic Neue Bold at 34 px | 440 | 313.25 |

The full measurement inputs/results and high-byte scan are in
`build/text-engine-investigation.json`. These are offline advance measurements,
not SDL2_ttf results, final size recommendations, or runtime visual validation.
The investigation environment's Pillow measurements must not be treated as
proof of a particular shaping configuration. Natural spacing will change
pagination; preserving current line breaks is not a goal of the new engine.

## Implementation sequence and acceptance

1. Add the pinned font backend, runtime font resource staging, style registry,
   encoding conversion, measurement and layout module. Give runtime-font mode
   an explicit switch independent of the image pack. Omit generated atlases and
   original font sheets from that mode once every glyph path is replaced.
2. Replace text-list wrapping, drawing, line spacing and navigation together.
   Track paragraphs so resizing or font changes can reflow original text.
   Integrate run compositing, saved backgrounds and direct animated drawing.
3. Replace dialogue and inventory mappings with paragraph identities; adapt
   popup and save/loading-label paths. Preserve popup artwork geometry initially,
   choosing a role size that fits, with a defined overflow policy rather than
   horizontal glyph distortion.
4. Verify both ABI builds and compare emulator/device captures. Extend the
   existing HD regression coverage for alpha composition and effects, and add
   focused layout/selection checks for wrapped choices and inventory items.

Acceptance requires real font advances with no legacy cell fitting, consistent
measurement and rendering, stable colour highlights, correct taps on every
continuation line, explicit-newline/long-word handling, accents and curly quotes,
typewriter/skip behavior, paging through the complete text, and clean panel
close/reopen and scene transitions. Check diary pages, all save labels, popup
actions, small/fractional/large display scales, resume, and existing save previews.
Validate byte-limit boundaries and long lines without signed-index wraparound.

The difficult part is maintaining these layout and interaction contracts. Font
rasterization itself is provided by established libraries. This can remain a
focused text-subsystem replacement alongside the recovered gameplay engine.
