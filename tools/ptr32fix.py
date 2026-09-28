#!/usr/bin/env python3
"""Work around clang's AArch64 __ptr32 codegen: rewrite frontend LLVM IR so that no load, store or memory
intrinsic goes through an addrspace(270/271/272) pointer.

clang (AArch64, at least up to 21) lowers `store i8/i16` through a __ptr32 pointer as a 32-bit `str`, which
clobbers the neighbouring bytes, and cannot lower llvm.memcpy on those address spaces at all. Casting the
pointer to a generic one first (addrspacecast = zero-extend for __uptr) gives correct code; the 32-bit
pointer representation in memory and 32-bit pointer arithmetic are unchanged.

Usage: ptr32fix.py in.ll out.ll   (in.ll from `clang -S -emit-llvm -Xclang -disable-llvm-passes`)
"""
import re, sys

AS = r'addrspace\((27[012])\)'
STORE = re.compile(r'^(\s*)store (volatile )?(.*), ptr ' + AS + r' (.*?), align (\d+)(.*)$')
LOAD = re.compile(r'^(\s*)(%[\w.]+) = load (volatile )?(.*?), ptr ' + AS + r' (.*?), align (\d+)(.*)$')
MEMCALL = re.compile(r'@llvm\.(memcpy|memmove|memset)(\.inline)?\.(p\d+)(?:\.(p\d+))?\.(i\d+)\(')
OPERAND = re.compile(r'ptr ' + AS + r' (noalias |nonnull |noundef |align \d+ |dereferenceable\(\d+\) )*(%[\w.]+|@[\w.]+)')

n = 0


def cast(indent, space, val, out):
    global n
    n += 1
    tmp = f'%__p32_{n}'
    out.append(f'{indent}{tmp} = addrspacecast ptr addrspace({space}) {val} to ptr')
    return tmp


def fix(lines):
    out, decls = [], set()
    for l in lines:
        m = STORE.match(l)
        if m:
            ind, vol, tv, sp, ptr, al, rest = m.groups()
            t = cast(ind, sp, ptr, out)
            out.append(f'{ind}store {vol or ""}{tv}, ptr {t}, align {al}{rest}')
            continue
        m = LOAD.match(l)
        if m:
            ind, dst, vol, ty, sp, ptr, al, rest = m.groups()
            t = cast(ind, sp, ptr, out)
            out.append(f'{ind}{dst} = load {vol or ""}{ty}, ptr {t}, align {al}{rest}')
            continue
        m = MEMCALL.search(l)
        if m and re.search(AS, l) and not l.startswith('declare'):
            ind = re.match(r'\s*', l).group()

            def op(mo):
                return 'ptr ' + (mo.group(2) or '') + cast(ind, mo.group(1), mo.group(3), out)
            l = OPERAND.sub(op, l)
            name = f'llvm.{m[1]}{m[2] or ""}.p0' + ('.p0' if m[4] else '') + f'.{m[5]}'
            l = l[:m.start()] + '@' + name + '(' + l[m.end():]
            decls.add((m[1], m[2] or '', bool(m[4]), m[5]))
        out.append(l)
    for kind, inl, two, it in decls:
        name = f'llvm.{kind}{inl}.p0' + ('.p0' if two else '') + f'.{it}'
        if not any(x.startswith('declare') and '@' + name + '(' in x for x in out):
            args = 'ptr, ptr, ' if two else 'ptr, i8, '
            out.append(f'declare void @{name}({args}{it}, i1 immarg)')
    return out


src = open(sys.argv[1]).read().split('\n')
open(sys.argv[2], 'w').write('\n'.join(fix(src)))
