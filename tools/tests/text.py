#!/usr/bin/env python3
"""Build and run the actual runtime text regression test on an adb arm64 emulator.

Requires a runtime-font APK build first. ANDROID_HOME and ANDROID_SERIAL are respected.
Only writes test files under /data/local/tmp/fade-text-test; app saves are untouched.
"""
import os
from pathlib import Path
import shutil
import subprocess

ROOT = Path(__file__).resolve().parents[2]


def run(*args):
    subprocess.run(args, cwd=ROOT, check=True)


def main():
    sdk = Path(os.environ.get('ANDROID_HOME', str(Path.home() / 'Library/Android/sdk')))
    compilers = list((sdk / 'ndk/29.0.14206865/toolchains/llvm/prebuilt').glob('*/bin/aarch64-linux-android24-clang'))
    libraries = list((ROOT / 'port/android/app/build/intermediates/cxx' / os.environ.get('FADE_TEST_BUILD_TYPE', 'Debug')).glob('*/obj/arm64-v8a/libmain.so'))
    if len(compilers) != 1 or len(libraries) != 1:
        raise SystemExit('Build the selected APK first; expected one pinned NDK and one arm64 output')
    output = ROOT / 'build/text-test'
    output.mkdir(parents=True, exist_ok=True)
    shutil.copy2(ROOT / 'extracted/Fade.exe', output / 'Fade.exe')
    shutil.copytree(ROOT / 'build/android-assets/fonts', output / 'fonts', dirs_exist_ok=True)
    libdir = libraries[0].parent
    run(str(compilers[0]), '-std=gnu11', '-fms-extensions', '-Wl,--export-dynamic',
        '-Iport/include', '-Ibuild/third_party/SDL2-2.32.10/include',
        'tools/tests/text.c', '-L'+str(libdir), '-lmain', '-lSDL2', '-lm', '-o', str(output / 'test'))
    for name in ['libmain.so', 'libSDL2.so']:
        shutil.copy2(libdir / name, output / name)
    run('adb', 'push', str(output)+'/.', '/data/local/tmp/fade-text-test')
    run('adb', 'shell', 'cd /data/local/tmp/fade-text-test && LD_LIBRARY_PATH=. ./test')


if __name__ == '__main__':
    main()
