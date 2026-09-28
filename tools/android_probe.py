#!/usr/bin/env python3
"""Tap in Fade's 240x320 coordinates and save a screenshot plus app-only logs.

Requires an installed, running debug APK in portrait fullscreen. Does not build,
reset app data or start an emulator. Example:
  python3 tools/android_probe.py --tap 225 276 --name next-page
ANDROID_SERIAL is respected by adb. Results go to build/probes/.
"""
import argparse
from pathlib import Path
import re
import struct
import subprocess
import time


def adb(*args):
    return subprocess.check_output(['adb', *args])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--tap', nargs=2, type=int, action='append', default=[])
    parser.add_argument('--delay', type=float, default=1.0,
                        help='seconds between taps and before capture')
    parser.add_argument('--name', default='probe')
    args = parser.parse_args()
    if not re.fullmatch(r'[A-Za-z0-9_-]+', args.name):
        parser.error('--name must be a simple filename')
    if not 0 <= args.delay <= 30:
        parser.error('--delay must be between 0 and 30 seconds')
    for x, y in args.tap:
        if not (0 <= x < 240 and 0 <= y < 320):
            parser.error('--tap must be within the 240x320 game screen')

    process = subprocess.run(['adb', 'shell', 'pidof', 'org.fadeport.fade'],
                             stdout=subprocess.PIPE, check=False)
    pid = process.stdout.decode().strip()
    if not pid:
        raise SystemExit('Fade is not running')
    shot = adb('exec-out', 'screencap', '-p')
    width, height = struct.unpack_from('>II', shot, 16)
    scale = min(width / 240, height / 320)
    left, top = (width - 240 * scale) / 2, (height - 320 * scale) / 2
    for x, y in args.tap:
        adb('shell', 'input', 'tap', str(round(left + x * scale)),
            str(round(top + y * scale)))
        time.sleep(args.delay)
    if not args.tap:
        time.sleep(args.delay)
    out = Path(__file__).resolve().parent.parent / 'build' / 'probes'
    out.mkdir(parents=True, exist_ok=True)
    (out / f'{args.name}.png').write_bytes(adb('exec-out', 'screencap', '-p'))
    logs = adb('logcat', '-d', f'--pid={pid}', '-s', 'SDL/APP', 'libc').decode()
    (out / f'{args.name}.log').write_text(logs)
    events = [line for line in logs.splitlines()
              if 'tap ' in line or 'fatal:' in line or 'Fatal signal' in line]
    for line in events[-12:]:
        print(line)
    print(f'Screenshot and logs: {out / args.name}')


if __name__ == '__main__':
    main()
