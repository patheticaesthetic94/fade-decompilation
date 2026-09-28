#!/usr/bin/env python3
"""Disassemble game functions from extracted/Fade.exe: tools/armdis.py <name|hexaddr> ...

Function bounds come from the '// <addr> <name>' headers in decomp/game.c and decomp/lib.c; call targets and
literal-pool words are labelled with those names and with symbols.txt globals.
"""
import os, re, struct, sys
import capstone, pefile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
pe = pefile.PE(os.path.join(ROOT, 'extracted', 'Fade.exe'), fast_load=True)
BASE = pe.OPTIONAL_HEADER.ImageBase
img = pe.get_memory_mapped_image()

names, starts = {}, []
for f in ('game.c', 'lib.c'):
    for m in re.finditer(r'^// ([0-9a-f]{8}) (\S+)$', open(os.path.join(ROOT, 'decomp', f)).read(), re.M):
        a = int(m[1], 16); names[a] = m[2]; starts.append(a)
for l in open(os.path.join(ROOT, 'tools', 'ghidra', 'symbols.txt')):
    m = re.match(r'([0-9a-f]{5,8}) (\w+)', l)
    if m: names.setdefault(int(m[1], 16), m[2])
starts.sort()
byname = {v: k for k, v in names.items()}

md = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_ARM)


def word(a):
    return struct.unpack_from('<I', img, a - BASE)[0]


def dis(start):
    end = next((s for s in starts if s > start), start + 0x400)
    pool = set()
    for i in md.disasm(bytes(img[start - BASE:end - BASE]), start):
        if i.address in pool:
            w = word(i.address)
            print(f'{i.address:06x}  .word {w:#x}  {names.get(w, "")}')
            continue
        note = ''
        m = re.search(r'\[pc, #(-?0x[0-9a-f]+|-?\d+)\]', i.op_str)
        if m and i.mnemonic.startswith('ldr'):
            la = i.address + 8 + int(m[1], 0); pool.add(la)
            w = word(la); note = f'; ={w:#x} {names.get(w, "")}'
        m = re.match(r'#(0x[0-9a-f]+)$', i.op_str)
        if i.mnemonic.startswith('b') and m:
            note = '; ' + names.get(int(m[1], 16), '')
        print(f'{i.address:06x}  {i.mnemonic:8} {i.op_str} {note}'.rstrip())


for arg in sys.argv[1:]:
    a = byname.get(arg) or int(arg, 16)
    print(f'== {a:08x} {names.get(a, "")}')
    dis(a)
