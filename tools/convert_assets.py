#!/usr/bin/env python3
"""Convert extracted/ game assets into standard files under assets/ with readable names.

Obfuscation (confirmed in Fade.exe, see decomp/game.c XOR 0x4d / 0x77 loops):
- Names: uppercased; every A-Z after the first character is shifted +4 (wrapping).
  Extension ".jpg" -> ".IFJ", ".bmp" -> ".IFB", ".wav" -> ".IFV", ".gif" -> ".IFG".
- .IFJ/.IFB/.IFG: first 10 bytes XOR 0x4D, rest is a plain JPEG/BMP/GIF. .IFV: plain WAV.
- Data/*.Fad (except Index*.Fad): every byte XOR 0x77 -> text (English, cp1252).
Usage: tools/convert_assets.py [extracted] [assets]
"""
import os, sys

EXT = {"IFJ": "jpg", "IFB": "bmp", "IFV": "wav", "IFG": "gif"}

def decode_name(stem):
    return stem[:1] + "".join(
        chr((ord(c) - 65 - 4) % 26 + 65) if "A" <= c <= "Z" else c for c in stem[1:])

def main():
    src = sys.argv[1] if len(sys.argv) > 1 else "extracted"
    dst = sys.argv[2] if len(sys.argv) > 2 else "assets"
    n = 0
    for root, _, files in os.walk(src):
        rel = os.path.relpath(root, src)
        for f in files:
            stem, _, ext = f.rpartition(".")
            data = open(os.path.join(root, f), "rb").read()
            if ext.upper() in EXT:
                name = decode_name(stem) + "." + EXT[ext.upper()]
                if ext.upper() != "IFV":
                    data = bytes(b ^ 0x4D for b in data[:10]) + data[10:]
            elif ext == "Fad" and not stem.startswith("Index"):
                name, data = f + ".txt", bytes(b ^ 0x77 for b in data)
            else:
                continue
            out = os.path.join(dst, rel, name)
            os.makedirs(os.path.dirname(out), exist_ok=True)
            open(out, "wb").write(data)
            n += 1
    print("wrote %d files to %s" % (n, dst))

if __name__ == "__main__":
    main()
