#!/usr/bin/env python3
"""Extract the Fade Pocket PC CAB from app/Setup.exe and rebuild the install tree.

Usage: tools/extract_cab.py [app/Setup.exe] [extracted]
Needs 7z. Parses the WinCE CAB header (*.000) to map mangled 8.3 member names
(XXXXXXXX.NNN, NNN = file id) back to real names and directories.
"""
import os, shutil, struct, subprocess, sys, tempfile

def parse_header(data):
    assert data[:4] == b"MSCE"
    nstr, ndir, nfile = struct.unpack_from("<HHH", data, 48)
    ostr, odir, ofile = struct.unpack_from("<III", data, 60)
    strings, p = {}, ostr
    for _ in range(nstr):
        sid, ln = struct.unpack_from("<HH", data, p)
        strings[sid] = data[p + 4:p + 4 + ln].split(b"\0")[0].decode("latin-1")
        p += 4 + ln
    dirs, p = {}, odir
    for _ in range(ndir):
        did, ln = struct.unpack_from("<HH", data, p)
        ids = struct.unpack_from("<%dH" % (ln // 2), data, p + 4)
        dirs[did] = [strings[i] for i in ids if i]
        p += 4 + ln
    files, p = {}, ofile
    for _ in range(nfile):
        fid, did, _unk, flags, ln = struct.unpack_from("<HHHIH", data, p)
        name = data[p + 12:p + 12 + ln].split(b"\0")[0].decode("latin-1")
        files[fid] = (dirs[did], name)
        p += 12 + ln
    return files

def main():
    src = sys.argv[1] if len(sys.argv) > 1 else "app/Setup.exe"
    out = sys.argv[2] if len(sys.argv) > 2 else "extracted"
    with tempfile.TemporaryDirectory() as tmp:
        subprocess.run(["7z", "x", "-y", src, "-o" + tmp], check=True, stdout=subprocess.DEVNULL)
        members = os.listdir(tmp)
        hdr = next(m for m in members if m.endswith(".000"))
        files = parse_header(open(os.path.join(tmp, hdr), "rb").read())
        os.makedirs(out, exist_ok=True)
        shutil.copy(os.path.join(tmp, hdr), os.path.join(out, "_cab_header.000"))
        for m in members:
            fid = int(m.rsplit(".", 1)[1])
            if fid == 0:
                continue
            d, name = files[fid]
            # %CE1% = \Program Files; strip the macro root so the tree is relative
            parts = [x for x in d if not x.startswith("%")]
            dst = os.path.join(out, *parts, name)
            os.makedirs(os.path.dirname(dst), exist_ok=True)
            shutil.copy(os.path.join(tmp, m), dst)
        print("extracted %d files to %s" % (len(members) - 1, out))

if __name__ == "__main__":
    main()
