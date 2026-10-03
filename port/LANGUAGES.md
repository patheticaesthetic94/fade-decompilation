# French language option

`lang/fr/Data/` holds the six `Data/*.Fad` files with French text. Everything else (the
exe, fonts, art and sounds) is shared with the English 1.09 release.

## Source

The French release is "Fade released version 1.04" (`Fade.ARM.CAB`). Compared with English 1.09:

- **All language lives in the six `Data/*.Fad` files.** `Fade.exe` has no translated
  strings: the engine's own words (`Save`, `Load`, `EMPTY`, `SLOT`, ...) are English in both
  releases, and object verbs are dispatched on the first tag letter only (`_Ut` "Utiliser"
  and `_Us` "Use" are both `U`). The menu art was already English in the French release.
- Record counts are identical (448 scenes, 145 objects, 7 book pages). Text is CP1252.
  `Font_Load` maps `à â ç è é ê ô ù û ’`, so the bitmap fonts draw French. A few rare
  characters (`ï`, `« »`, `°`, `…`) have no bitmap glyph, as in the original; the
  Remastered outline fonts draw them.
- **36 scene scripts were fixed after 1.04**: hotspot coordinates, added `_Wa` waits,
  `ON`→`ON/OFF` dialogue flags, actions added, moved or removed. Shipping the 1.04 scripts
  unchanged would bring those bugs back.
- The only differing images are the credits, where 1.09 adds the US translators, and 19
  images renamed to drop accents. 1.09's are kept.

## How the files were built

Each 1.09 English record keeps its structure, and only its text fields are replaced with
the aligned French ones. Numbers, tags, `ON`/`OFF` flags, type letters and media names
are byte-identical to 1.09, with the same field counts. Restructured records are aligned
by action verb, using a French-to-English label dictionary learned from the records that
match. 22 fields with no unambiguous 1.04 counterpart were set by hand, mostly with 1.04
wording from the same or a sibling hotspot; five short strings are new translations. The
`Index*.Fad` offset tables are rebuilt.

Result: 15,852 text fields in French, none left in English. Because the structure is
unchanged, **save files are interchangeable between languages**, and 1.04 saves use the same
format.

## Runtime selection

`port/src/files.c` reads `FADE_LANG`. For a two-letter code other than `en`, every asset
lookup tries `lang/<code>/<path>` first, then `<path>`. `tools/stage_assets.py` stages
`lang/` into `fade/lang/` and lists it in `files.txt`. The web player sets `FADE_LANG=fr`
from its Home menu checkbox or `?lang=fr`. The Android launcher does not offer the
language yet; the files are packaged, so it only needs to set the variable.

## Verification

- `tools/tests/web.cjs`: in Classic (`?lang=`) and Remastered (Home checkbox), French loads
  the override pack and English does not. New Game shows the French narration, and the
  English and French screenshots differ.
- Manual browser checks: the scene 2 dialogue menu is French and advances when a choice
  is picked. Accents render in both editions. A French 1.04 save (Astrolab, scene 304)
  loads without errors.
- Not verified: the full French campaign, and whether every French string fits its text box.
  1.04 used the same layout, so overflow is unlikely.
