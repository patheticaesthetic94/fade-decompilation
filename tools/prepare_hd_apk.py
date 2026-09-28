#!/usr/bin/env python3
"""Stage the selected 4x pack and rasterize OFL replacement fonts for the APK.

Glyphs use shared font baselines and retain the legacy advance grid.
Run after android_build.sh has staged the legacy data into build/android-assets.
"""
import hashlib
import json
import os
from pathlib import Path
import shutil
from PIL import Image, ImageDraw, ImageFont

ROOT = Path(__file__).resolve().parent.parent
FONT_REVISION = '23e54b51ddffbc7713c583748e3bd86f62b1fa4a'
CHARS = ('ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890'
         'çâàéêèôùû !"-\'?;,.:()')


def cells(im):
    w, h = im.size
    y = 0
    out = []
    while y < h:
        if im.getpixel((0, y)) == (255, 0, 255):
            y += 1
            continue
        x = 0
        row = []
        while x < w:
            if im.getpixel((x, y)) == (255, 0, 255):
                x += 1
                continue
            start = x
            while x < w and im.getpixel((x, y)) != (255, 0, 255):
                x += 1
            bottom = y
            while bottom < h and im.getpixel((start, bottom)) != (255, 0, 255):
                bottom += 1
            row.append((start, y, x-start, bottom-y))
        out.extend(row)
        y += row[0][3] if row else 1
    if len(out) != len(CHARS):
        raise ValueError(f'Expected {len(CHARS)} glyphs, found {len(out)}')
    return out


def mangle(path):
    p = Path(path)
    stem = p.stem.upper().replace('É', '1')
    stem = stem[:1] + ''.join(chr((ord(c)-65+4) % 26+65) if 'A' <= c <= 'Z' else c
                             for c in stem[1:])
    extension = '.IFV' if p.suffix.lower() == '.wav' else '.IF' + p.suffix[1].upper()
    return str(p.with_name(stem + extension))


def fonts(stage):
    sources = ROOT / 'port/resources/fonts'
    dest = stage / 'hd/fonts'
    dest.mkdir(parents=True, exist_ok=True)
    for p in sources.iterdir():
        if p.is_file():
            shutil.copy2(p, dest / p.name)
    records = {}
    for source in sorted((ROOT / 'assets/Fonts').glob('*.bmp')):
        im = Image.open(source).convert('RGB')
        popup = 'POPUPS' in source.name
        face = 'Arimo.ttf' if popup else 'ComicNeue-Bold.ttf'
        font = ImageFont.truetype(str(sources / face), 26 if popup else 34)
        baseline = 32 if popup else 35
        color = ((255, 140, 0) if 'ORANGE' in source.name else
                 (255, 255, 0) if 'JAUNE' in source.name else
                 (0, 128, 255) if 'BLEU' in source.name else
                 (0, 0, 0) if 'NOIR' in source.name else (255, 255, 255))
        background = (255, 255, 255) if 'NOIR' in source.name else (0, 0, 0)
        # Keep the game's original advances and separator grid. Only the ink is
        # replaced; changing sheet widths confuses the legacy glyph index map.
        sheet = Image.new('RGB', im.size, (255, 0, 255))
        atlas = Image.new('RGBA', (1024, 1024))  # 16x16 slots, 64x64 each
        metrics = {}
        for char, (x, y, w, h) in zip(CHARS, cells(im)):
            glyph = Image.new('RGBA', (w*4, h*4))
            box = font.getbbox(char, anchor='ls')
            ink_width = max(1, box[2]-box[0])
            ink_height = max(1, box[3]-box[1])
            ink = Image.new('RGBA', (ink_width, ink_height))
            ImageDraw.Draw(ink).text((-box[0], -box[1]), char, font=font,
                                     fill=color+(255,), anchor='ls')
            # Slightly fill letter cells without widening punctuation marks.
            expanded_width = min(glyph.width, max(1, round(ink.width*1.04))) \
                if char.isalnum() else ink.width
            if expanded_width != ink.width:
                ink = ink.resize((expanded_width, ink.height), Image.Resampling.LANCZOS)
            if ink.width > glyph.width:
                ink = ink.resize((glyph.width, ink.height), Image.Resampling.LANCZOS)
            ink_x = min(glyph.width-ink.width, max(0, box[0]))
            glyph.alpha_composite(ink, (ink_x,
                                        max(0, min(glyph.height-ink.height,
                                                   baseline+box[1]))))
            code = ord(char)
            atlas.paste(glyph, ((code % 16)*64, (code // 16)*64))
            if char == "'":
                atlas.paste(glyph, ((0x92 % 16)*64, (0x92 // 16)*64))
            low = Image.new('RGBA', glyph.size, background+(255,))
            low.alpha_composite(glyph)
            sheet.paste(low.convert('RGB').resize((w, h), Image.Resampling.LANCZOS), (x, y))
            metrics[str(code)] = [w, h]
        atlas.save(dest / (source.name + '.png'))
        # Original loader XORs the first ten bytes of each sheet.
        tmp = dest / 'sheet.bmp'
        sheet.save(tmp)
        data = tmp.read_bytes()
        (stage / 'fade' / mangle('Fonts/' + source.name)).write_bytes(
            bytes(b ^ 0x4d for b in data[:10]) + data[10:])
        tmp.unlink()
        records[source.name] = {'face': face, 'metrics': metrics}
    (dest / 'provenance.json').write_text(json.dumps({
        'repository': 'https://github.com/google/fonts', 'revision': FONT_REVISION,
        'files': {p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in sources.iterdir()
                  if p.is_file()}, 'glyphs': records}, indent=2)+'\n')


def main():
    stage = ROOT / 'build/android-assets'
    pack = Path(os.environ.get('FADE_HD_PACK', ROOT / 'hd-assets'))
    if not pack.is_absolute():
        pack = ROOT / pack
    manifest = json.loads((pack / 'manifest.json').read_text())
    if manifest['scale'] != 4:
        raise ValueError('HD renderer requires a 4x pack')
    lines = []
    for name, asset in sorted(manifest['assets'].items()):
        if asset['method'] == 'skip':
            continue
        if asset['status'] != 'complete':
            raise ValueError(f'Incomplete asset: {name}')
        rel = asset['output']
        source = pack / rel
        if hashlib.sha256(source.read_bytes()).hexdigest() != asset['output_sha256']:
            raise ValueError(f'HD hash mismatch: {name}')
        target = stage / 'hd' / rel
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source, target)
        # Match MangleAssetPath, including accented names and callers using .ifj.
        lines.append(mangle(name).lower()+'\t'+rel)
    (stage / 'hd/files.txt').write_text('\n'.join(sorted(lines))+'\n')
    if os.environ.get("FADE_RUNTIME_FONTS") != "1":
        fonts(stage)
    print(f'HD APK resources: {len(lines)} images; ' +
          ('runtime outline fonts' if os.environ.get('FADE_RUNTIME_FONTS') == '1' else 'six glyph atlases'))


if __name__ == '__main__':
    main()
