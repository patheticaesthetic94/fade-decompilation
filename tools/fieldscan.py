#!/usr/bin/env python3
"""List this-pointer (param_1) field accesses in decomp/game.c for functions whose name matches a regex.
Usage: tools/fieldscan.py 'Screen_|GetScreen'   ->  offset  types  count  functions"""
import re, sys, collections
src = open(__import__('os').path.join(__import__('os').path.dirname(__import__('os').path.abspath(__file__)), '..', 'decomp', 'game.c')).read()
pat = re.compile(sys.argv[1])
p = sys.argv[2] if len(sys.argv) > 2 else 'param_1'
acc = re.compile(r'(?:\*\((\w+(?: \w+)?) \*\*?\)\(?)?' + p + r'(?: \+ (0x[0-9a-f]+|\d+))?\)?(\[)?')
fields = collections.defaultdict(lambda: [set(), 0, set()])
for m in re.finditer(r'^// ([0-9a-f]{8}) (\S+)\n(.*?)(?=^// [0-9a-f]{8} |\Z)', src, re.S | re.M):
    if not pat.search(m.group(2)): continue
    for a in acc.finditer(m.group(3)):
        off = int(a.group(2), 0) if a.group(2) else 0
        if not a.group(1) and not a.group(2): continue
        f = fields[off]; f[0].add(a.group(1) or '&'); f[1] += 1; f[2].add(m.group(2))
for off in sorted(fields):
    t, n, fn = fields[off]
    print(f'{off:#6x} {"/".join(sorted(t)):28} {n:3} {" ".join(sorted(fn))[:110]}')
