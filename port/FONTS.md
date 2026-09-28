# Font replacement investigation

For the implemented runtime mode using natural advances, kerning, wrapping
and line metrics, see [TEXT_ENGINE.md](TEXT_ENGINE.md). Build it with
`tools/android_build.sh --runtime-fonts` or combine it with `--hd`. The earlier
atlas HD approach below remains available and preserves bitmap cell advances.

Investigated and implemented 2026-09-28. The optional HD APK replaces the fonts.
The supplied bitmap fonts have **unverified licensing**, rather than confirmed
free-use rights. The HD build uses Comic Neue Bold for game text
and Arimo Regular for popups, rendered through native 4× buffers.

## Implemented HD replacement

`tools/prepare_hd_apk.py` rasterizes Comic Neue Bold and Arimo Regular at 4× into
six antialiased glyph atlases. Every glyph in a font role shares one baseline,
while the game's original glyph advances and cell separators remain intact. The
font sizes are fitted to those cells to limit horizontal compression. Letters
receive a small width adjustment; punctuation keeps its original side bearing. The native
renderer keeps text with the game layers, including copy, clear, saved backgrounds,
composition and direct animated drawing.

Replacement BMP sheets retain only the original separator geometry and cell metrics;
all ink is newly rasterized. They replace the obfuscated font sheets during APK
staging, so the HD APK does not contain the original font sheet ink. Original
inputs under `assets/` and `extracted/` remain unchanged.

Maintained resources are under `port/resources/fonts/`. Both families and their
matching OFL notices were obtained from `google/fonts` revision
`23e54b51ddffbc7713c583748e3bd86f62b1fa4a`. The APK includes the font files,
full licences and a provenance manifest with SHA-256 hashes. Rasterization uses
Pillow/FreeType during preparation and adds no Android font dependency.

Build with `tools/android_build.sh --hd`. The emulator displays Comic Neue text
in opening scenes, dialogue and save labels, and Arimo in the Load popup.
The native regression test checks antialias coverage through keyed composition
and opaque popup presentation. Broader visual checks across the full
campaign and physical devices remain necessary.

## Existing fonts and provenance

The runtime loads six obfuscated BMP sheets from `extracted/Fonts/`. Decoded
inspection copies are in `assets/Fonts/`:

| Decoded sheet | Image size | Glyph cell width | Glyph cell height | Appearance |
| --- | --- | --- | --- | --- |
| FONT TEXTE BLANCHE.bmp | 314×45 | 3–9 px | 11–12 px | White handwritten text |
| FONT TEXTE JAUNE.bmp | 314×45 | 3–9 px | 11–12 px | Yellow handwritten text |
| FONT TEXTE BLEU.bmp | 314×45 | 3–9 px | 11–12 px | Blue handwritten text |
| FONT TEXTE NOIR.bmp | 314×63 | 3–9 px | 11–12 px | Black handwritten text |
| FONT POPUPS BLANCHE.bmp | 314×40 | 2–9 px | 10 px | White compact sans serif |
| FONT POPUPS ORANGE.bmp | 314×40 | 2–9 px | 10 px | Orange compact sans serif |

Dimensions were measured with Pillow using the magenta separators and the row
order consumed by `Font_Load`. There are 83 extracted cells per sheet; the
apostrophe cell is also assigned to byte 0x92. Colour variants have some differing
cell widths, so a replacement should preserve each table's metrics individually.

Visual inspection suggests a Comic Sans-like face for text and an Arial-like
face for popups. These are **visual inferences**, not verified font identities:
there are no TTF/OTF files or family metadata accompanying these sheets. No font
licence or attribution was found in the supplied application/resource files.
Public searches did not establish a licence for these particular sheets either.
Their presence in the original installer does not establish permission to reuse
them in a redistributed port; the original publisher's font permissions remain
unknown.

If they originated from Windows fonts, converting them to bitmap glyphs is not
by itself permission to bundle them in a game. Microsoft's [font redistribution
FAQ](https://learn.microsoft.com/en-us/typography/fonts/font-faq) distinguishes
static images of complete text from individually addressable bitmap fonts and
requires additional rights for the latter. This does not prove that the original
publisher lacked those rights.

## Free alternatives

| Role | First candidate | Alternative | Assessment |
| --- | --- | --- | --- |
| Dialogue, descriptions, inventory and other handwritten text | Comic Neue Bold | Comic Neue Regular | Preserves the informal handwritten character; weight and size need in-game comparison. No exact metric match is assumed. |
| Popup actions and selections | Arimo Regular | Liberation Sans Regular, version 2 or newer | Familiar sans serif. Arial metric compatibility is useful, but does not guarantee compatibility with the custom bitmap cells. |

[Comic Neue](https://github.com/google/fonts/tree/main/ofl/comicneue) supplies
static TrueType files, including Bold and Regular, under [OFL 1.1](https://github.com/google/fonts/blob/main/ofl/comicneue/OFL.txt).
[Arimo's upstream project](https://github.com/googlefonts/Arimo) documents Arial
metric compatibility and provides its [OFL 1.1 licence](https://github.com/googlefonts/Arimo/blob/main/OFL.txt).
[Liberation Fonts](https://github.com/liberationfonts/liberation-fonts) also provides
outline fonts and an [OFL 1.1 licence](https://github.com/liberationfonts/liberation-fonts/blob/main/LICENSE).
Use an identified release/commit and its matching licence, rather than an
unattributed download or an older Liberation package with different terms.

These outline fonts can be rasterized at the device's required size; there is no
fixed bitmap resolution. One text face and one popup face can produce all six
colour roles at render time.

The [official OFL FAQ](https://openfontlicense.org/ofl-faq/) permits bundling with
free or commercial games. Include each font's copyright, licence notice and
full licence text in the APK. The application itself need not adopt the OFL.
If distributing converted bitmap fonts or modified font files, preserve the OFL
and check the selected package's Reserved Font Names requirements.

## Why a sheet swap is insufficient for high resolution

`port/src/main.c` creates a **240×320 RGB565 texture**, copies `port_fb` into it
in `port_present`, then scales it with SDL's linear filtering. `Font_Load`
(0x1d958) extracts individual bitmaps into `Glyph` structures; `Glyph_BlitToLayer`
(0x1e53c) and `Glyph_DrawDirect` (0x1e5ec) copy them into game layers or the
framebuffer. Text is already rasterized before display scaling.

A free-font BMP generated at the existing cell sizes would resolve the font
provenance issue for the replacement and could improve legibility, but it would
still enlarge roughly 10–12 pixel-high glyphs. A larger sheet would alter glyph
sizes used for wrapping and layout, rather than automatically produce sharper
text within the same UI. Raising the whole framebuffer resolution would also
require changes throughout the engine's fixed coordinates and layer buffers.

## Original implementation proposal (historical)

Keep the game's 240×320 layout and input coordinates, while drawing replacement
glyphs into a separate display-resolution text layer through SDL. SDL2_ttf is a
reasonable renderer: its [blended rendering API](https://wiki.libsdl.org/SDL2_ttf/TTF_RenderUTF8_Blended)
produces antialiased ARGB surfaces. It is an additional dependency; this port
currently links SDL2 only. Cache glyph textures and regenerate them when the
display scale changes.

1. Bundle pinned font files and their notices from a new maintained resource
   directory. Extend APK staging in `tools/android_build.sh`, which currently
   copies `extracted/`, rather than editing regenerated `assets/` files.
2. Replace font loading through `port/fixups/` and store each original logical
   glyph width/height as explicit metrics. Keep native SDL/font objects outside
   the game's 32-bit-pointer structures. Preserving per-glyph advances and line
   heights initially avoids changing wrapping, pagination and popup selection
   rectangles. Fit replacement glyphs to those cells and assess distortion.
3. Intercept both layer glyph drawing and direct glyph drawing. Render to native
   display resolution using the same logical positions and clipping. Suppress
   the old glyph pixels, while reproducing their background treatment: text
   fonts are loaded unkeyed and popup fonts keyed in `LoadGameResources`.
4. Track text with the relevant game layers and their composition, copy, clear,
   restore and fade operations. A simple persistent overlay would otherwise
   leave stale text when panels or popups disappear, or place it above objects
   that should obscure it. Account for `port_present` throttling as well.
5. Preserve the character-by-character path in `Text_TypeLine` (0x1cc40).
   The legacy mapping includes accented French letters and byte 0x92 as an
   apostrophe, even in the English data. Convert these explicitly to Unicode;
   do not interpret the existing bytes as UTF-8.

The existing `tools/mkport.py` recognises function replacements in `port/fixups/`
by their address/name headers. Durable implementation belongs there and in
`port/src/`, with build dependency changes in `port/CMakeLists.txt`; direct
edits to `decomp/` or `port/gen/` would be overwritten.

## Validation needed before adopting replacements

Compare original and replacement rendering at small, fractional and large display
scales. Exercise long descriptions, dialogue choices and highlights, animated
text and skip, inventory, diary pages, object popups, save/load slot labels and
credits. Check wrapping, clipping, accents, punctuation and popup tap targets.
Close and reopen panels; change scenes; run fades; resize or resume the app to
check for stale text and incorrect layering. Validate on both configured ABIs
and a physical Android device.

The original investigation inspected the font sheets, loader, drawing paths,
framebuffer presentation, APK resource staging and upstream licence sources.
The HD implementation above now replaces those fonts and renders them at 4×.
This font replacement is separate from the original game's other assets.
