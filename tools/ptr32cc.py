#!/usr/bin/env python3
"""Compiler launcher for the port (CMake C_COMPILER_LAUNCHER): compile a C file via LLVM IR with
tools/ptr32fix.py in between, so __ptr32 loads/stores get correct code on AArch64.

Invoked as: ptr32cc.py <clang> <flags...> -o <obj> -c <src>
"""
import os, subprocess, sys

HERE = os.path.dirname(os.path.abspath(__file__))
args = sys.argv[1:]
cc, flags = args[0], args[1:]
if '-c' not in flags:   # link or probe: pass through
    sys.exit(subprocess.call(args))
src = flags[flags.index('-c') + 1]
obj = flags[flags.index('-o') + 1]
ll, fixed = obj + '.ll', obj + '.fixed.ll'

front = []
i = 0
while i < len(flags):
    f = flags[i]
    if f in ('-c', '-o'):
        i += 2; continue
    front.append(f); i += 1
r = subprocess.call([cc] + front + ['-S', '-emit-llvm', '-Xclang', '-disable-llvm-passes', '-c', src, '-o', ll])
if r:
    sys.exit(r)
subprocess.check_call([sys.executable, os.path.join(HERE, 'ptr32fix.py'), ll, fixed])

back = []
i = 0
while i < len(front):
    f = front[i]
    if f in ('-MT', '-MF', '-MQ'):
        i += 2; continue
    if f in ('-MD', '-MMD') or f == src or f.startswith(('-I', '-D', '-std=', '-W')):
        i += 1; continue
    back.append(f); i += 1
sys.exit(subprocess.call([cc] + back + ['-Wno-override-module', '-c', fixed, '-o', obj]))
