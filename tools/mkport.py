#!/usr/bin/env python3
"""decomp/game.c + decomp/fade_types.h -> port/gen/{game.c,fade_types.h,protos.h}.

Mechanical C source transforms so Ghidra's output compiles against port/include/prelude.h.
A function re-written by hand in port/fixups/*.c (marked by a '// <addr> <Name>' header there) is left out of game.c.
Usage: python3 tools/mkport.py
"""
import os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GEN = os.path.join(ROOT, 'port', 'gen')
PATCHES = os.path.join(ROOT, 'port', 'patches.txt')
FIX = os.path.join(ROOT, 'port', 'fixups')

COMMON = [
    (r'\bwchar_t\b', 'wchar16'),
    (r'\bulong\b', 'uint'),
    (r'\blong\b', 'int'),
    (r'\b(_?)div_t\b', r'\1gdiv_t'),   # not the libc typedef
]
GAME = [
    (r'(?<![>.\w])free\(', 'game_free('),
    (r'\bdiv\(', 'div32('),
    (r'\btime\(', 'time32('),
    (r'\bwcscmp\(', 'wcscmp16('),
    (r'\brand\(', 'rand15('),
    (r'\bsrand\(', 'srand15('),
    (r'^ *atexit\(&LAB_\w+\);\n', ''),   # static destructors: never run
]
HEADER = [
    (r'^(struct|union) (\w+);$', r'typedef \1 \2 \2;'),
    (r'\bstatic_assert\b', '_Static_assert'),
]
KEYWORDS = {'return', 'case', 'else', 'do', 'goto', 'sizeof', 'code'}
# a type name followed by pointer stars, in a declarator (`T *name`) or a cast (`(T **)`)
PTR = re.compile(r'\b([A-Za-z_]\w*)( ?)(\*+)(?=[A-Za-z_)])')
PARTIAL = re.compile(r'((?:\b\w+)(?:\.\w+|->\w+|\[\w+\])*)\._(\d+)_(\d+)_')


def ptr32(m):
    """Every pointer is 32-bit (`T *_P32`), except native function pointers."""
    if m[1] in KEYWORDS:
        return m[0]
    return m[1] + ' ' + ' '.join(['*_P32'] * len(m[3])) + ' '


def partial(m):
    x, off, n = m[1], int(m[2]), int(m[3])
    return f'PART3({x},{off})' if n == 3 else f'PART({x},{off},uint{8 * n}_t)'


def p32_header(s):
    while True:   # innermost P32<...> first
        t = re.sub(r'P32<([^<>]*)>', r'\1 *_P32', s)
        if t == s:
            return s
        s = t


def sub(s, rules):
    for a, b in rules:
        s = re.sub(a, b, s, flags=re.M)
    return s


FRAME_VAR = re.compile(r'^  (?!return\b)([A-Za-z_][^;=()]*?)\b((?:local|[A-Za-z]*Stack)_([0-9a-f]+))((?: ?\[\w+\])*);$')


def stack_frame(text):
    """Put every local that Ghidra names by its stack offset (local_38, auStack_3c, CStack_c, ...) into one
    per-function byte array at its original offset below the entry SP. The original code relies on that
    layout: structs split into several locals (GetObjectW filling a BITMAP), by-value struct copies built
    in place, &stack0x... references. Register-only temporaries (iVar1, ...) stay ordinary locals."""
    head, sep, rest = text.partition('\n{\n')
    if not sep:
        return text
    parts = re.split(r'(\n[ \t]*\n)', rest, maxsplit=1)
    if len(parts) < 3 or not re.match(r'^  \S', parts[0]):
        return text
    decls, sep2, code = parts
    vars_, keep = [], []
    for line in decls.split('\n'):
        m = FRAME_VAR.match(line)
        if m:
            vars_.append((m[1].strip(), m[2], int(m[3], 16), m[4].replace(' ', '')))
        else:
            keep.append(line)
    if not vars_:
        return text
    size = (max(o for _, _, o, _ in vars_) + 15) & ~7
    defs = [f'  undefined1 __frame[{size:#x}] __attribute__((aligned(8)));   /* original stack frame */']
    for ty, name, off, dims in vars_:
        at = f'__frame + {size - off:#x}'
        defs.append(f'#define {name} (*({ty} (*){dims})({at}))' if dims else f'#define {name} (*({ty} *)({at}))')

    def ref(m):   # &stack0xffffffe0: entry-SP relative address inside this frame
        off = 0x100000000 - int(m[1], 16)
        return f'(__frame + {size - off:#x})' if off <= size else m[0]
    code = re.sub(r'&stack0x(f[0-9a-f]{7})\b', ref, code)
    body_end = code.rstrip().rfind('\n}')
    undefs = ''.join(f'#undef {name}\n' for _, name, _, _ in vars_)
    code = code[:body_end + 1] + undefs + code[body_end + 1:]
    return head + sep + '\n'.join(keep + defs) + sep2 + code


def load_patches():
    """port/patches.txt: '@ Func' then '- old' / '+ new' literal pairs (a '-' with no '+' deletes the line)."""
    pats, fn, lines = {}, None, open(PATCHES).read().split('\n') if os.path.exists(PATCHES) else []
    for i, l in enumerate(lines):
        if l.startswith('@ '):
            fn = l[2:].strip(); pats.setdefault(fn, [])
        elif l.startswith('- '):
            new = lines[i + 1][2:] if i + 1 < len(lines) and lines[i + 1].startswith('+ ') else None
            pats[fn].append((l[2:], new))
    return pats


def apply_patches(src, pats):
    def fix(m):
        name, text = m[2], m[0]
        for old, new in pats.get(name, []):
            if old not in text:
                sys.exit(f'mkport: patch for {name} no longer matches: {old!r}')
            if new is None:
                text = re.sub(r'^[ \t]*' + re.escape(old) + r'[ \t]*\n', '', text, flags=re.M)
            else:
                text = text.replace(old, new)
        return text
    return re.sub(r'^// ([0-9a-f]{8}) (\S+)\n.*?(?=^// [0-9a-f]{8} |\Z)', fix, src, flags=re.S | re.M)


def split(src):
    """-> [(addr, name, signature, full_text)]"""
    out = []
    parts = re.split(r'^(// [0-9a-f]{8} \S+)\n', src, flags=re.M)
    for hdr, body in zip(parts[1::2], parts[2::2]):
        _, addr, name = hdr.split()
        sig = body.split('\n{', 1)[0].strip()
        out.append((addr, name, ' '.join(sig.split()), hdr + '\n' + body))
    return out


def main():
    os.makedirs(GEN, exist_ok=True)
    fixups = {m for f in sorted(os.listdir(FIX)) if f.endswith('.c')
              for m in re.findall(r'^// [0-9a-f]{8} (\w+)$', open(os.path.join(FIX, f)).read(), re.M)}
    wrappers = {m for f in sorted(os.listdir(FIX)) if f.endswith('.c')
                for m in re.findall(r'^// HD_WRAP (\w+)$', open(os.path.join(FIX, f)).read(), re.M)}
    types = p32_header(sub(sub(open(os.path.join(ROOT, 'decomp', 'fade_types.h')).read(), COMMON), HEADER))
    open(os.path.join(GEN, 'fade_types.h'), 'w').write(types)

    src = apply_patches(open(os.path.join(ROOT, 'decomp', 'game.c')).read(), load_patches())
    src = sub(sub(src, COMMON), GAME)
    src = re.sub(r'/\* WARNING:[^*]*\*/', '', src)
    funcs = split(PARTIAL.sub(partial, PTR.sub(ptr32, src)))
    protos, body, skipped = [], [], set()
    for addr, name, sig, text in funcs:
        if re.search(r'^  ' + name + r'\(\);$', text, re.M):
            skipped.add(name)
            continue   # import thunk: provided by port/src
        protos.append(sig + ';' + ('  // fixup' if name in fixups else ''))
        if name in wrappers:
            pattern = r'\b' + re.escape(name) + r'(?=\s*\()'
            protos.append(re.sub(pattern, 'legacy_' + name, sig, count=1) + ';')
            text = re.sub(pattern, 'legacy_' + name, text, count=1)
            body.append(stack_frame(text))
        if name not in fixups:
            body.append(stack_frame(text))
    # guest code address -> native function, for code pointers found in the image (static-init table)
    table = [(a, n) for a, n, _, _ in funcs if n not in skipped]
    open(os.path.join(GEN, 'funcs.c'), 'w').write(
        '// Generated by tools/mkport.py -- do not edit.\n#include "fade.h"\n#include "../src/port.h"\n'
        'const GameFunc game_funcs[] = {\n' + ''.join(f'  {{0x{a}, (void (*)(void)){n}}},\n' for a, n in table)
        + '};\nconst int game_nfuncs = ' + str(len(table)) + ';\n')
    open(os.path.join(GEN, 'protos.h'), 'w').write(
        '// Generated by tools/mkport.py -- do not edit.\n#pragma once\n' + '\n'.join(protos) + '\n')
    open(os.path.join(GEN, 'game.c'), 'w').write(
        '// Generated by tools/mkport.py from decomp/game.c -- do not edit.\n#include "fade.h"\n\n' + ''.join(body))
    print(f'mkport: {len(funcs)} functions, {len(fixups)} fixups')


if __name__ == '__main__':
    main()
