#!/usr/bin/env python3
"""Build and run the actual HD renderer regression test on an adb arm64 emulator.

Requires an HD APK build first. ANDROID_HOME and ANDROID_SERIAL are respected.
Only writes test files under /data/local/tmp/fade-hd-test; app saves are untouched.
"""
import os
from pathlib import Path
import shutil
import subprocess
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]


def run(*args):
    subprocess.run(args, cwd=ROOT, check=True)


def main():
    sdk = Path(os.environ.get('ANDROID_HOME', str(Path.home() / 'Library/Android/sdk')))
    compilers = list((sdk / 'ndk/29.0.14206865/toolchains/llvm/prebuilt').glob('*/bin/aarch64-linux-android24-clang'))
    libraries = list((ROOT / 'port/android/app/build/intermediates/cxx' / os.environ.get('FADE_TEST_BUILD_TYPE', 'Debug')).glob('*/obj/arm64-v8a/libmain.so'))
    if len(compilers) != 1 or len(libraries) != 1:
        raise SystemExit('Build the selected APK first; expected one pinned NDK and one arm64 output')
    output = ROOT / 'build/hd-test'
    (output / 'hd').mkdir(parents=True, exist_ok=True)
    shutil.copy2(ROOT / 'extracted/Fade.exe', output / 'Fade.exe')
    (output / 'hd/files.txt').write_text(
        'fixture.bmp\tfixture.png\n'
        'menu/cvihmxw1.ifj\tfixture.png\n'
        'menu/cvihmxw2.ifj\tfixture.png\n'
        'sprites/cutout.ifb\tpatch.png\n'
        'sprites/patch.ifj\tpatch.png\n'
        'zoom/zssq v1zimp.ifj\tfixture.png\n')
    im = Image.new('RGB', (8, 8))
    for y in range(8):
        for x in range(8):
            im.putpixel((x, y), (0, 0, 0) if x < 4 and y < 4 else
                        (200+x*5, 0, 0) if y < 4 else
                        (0, 255, 0) if x < 4 else (0, 0, 255))
    im.save(output / 'hd/fixture.png')
    Image.new('RGB', (32, 32), (255, 0, 0)).save(output / 'hd/patch.png')
    (output / 'hd/fonts').mkdir(exist_ok=True)
    atlas = Image.new('RGBA', (1024, 1024))
    atlas.putpixel((65 % 16 * 64 + 1, 65 // 16 * 64 + 1), (255, 255, 255, 128))
    atlas.save(output / 'hd/fonts/FONT POPUPS BLANCHE.bmp.png')
    libdir = libraries[0].parent
    run(str(compilers[0]), '-std=gnu11', '-fms-extensions', '-Wl,--export-dynamic',
        '-Iport/include', '-Ibuild/third_party/SDL2-2.32.10/include',
        'tools/tests/hd.c', '-L'+str(libdir), '-lmain', '-lSDL2', '-o', str(output / 'test'))
    for name in ['libmain.so', 'libSDL2.so']:
        shutil.copy2(libdir / name, output / name)
    run('adb', 'push', str(output)+'/.', '/data/local/tmp/fade-hd-test')
    run('adb', 'shell', 'cd /data/local/tmp/fade-hd-test && LD_LIBRARY_PATH=. ./test')


if __name__ == '__main__':
    main()
