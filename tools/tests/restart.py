#!/usr/bin/env python3
"""Verify menu Quit/reopen and Home/resume on an installed Fade debug APK.

Requires adb and a portrait emulator/device; ANDROID_SERIAL is respected.
Starts at the main menu, exits three times, and leaves the app at the menu.
Does not install, force-stop, clear app data or change saves. Screenshots and
logs are recorded under build/restart-test.
"""
from pathlib import Path
import struct
import subprocess
import time

PACKAGE = 'org.fadeport.fade'
COMPONENT = PACKAGE + '/org.fadeport.fade.FadeActivity'
OUTPUT = Path(__file__).resolve().parents[2] / 'build/restart-test'


def adb(*args, check=True):
    return subprocess.run(['adb', *args], check=check, stdout=subprocess.PIPE,
                          stderr=subprocess.PIPE).stdout


def pid():
    return adb('shell', 'pidof', PACKAGE, check=False).decode().strip()


def saves():
    return adb('shell', f"run-as {PACKAGE} sh -c "
               "'if [ -d files/save ]; then find files/save -type f "
               "-exec sha256sum {} \\; | sort; fi'")


def launch(name):
    adb('shell', 'am', 'start', '-W', '-n', COMPONENT)
    time.sleep(4)  # Allow resource loading and menu rendering to finish.
    current = pid()
    assert current, 'Game process exited during launch'
    logs = adb('logcat', '-d', '--pid=' + current, '-s', 'SDL/APP')
    (OUTPUT / (name + '.log')).write_bytes(logs)
    assert b'fatal:' not in logs and b'Fatal signal' not in logs, logs.decode()
    shot = adb('exec-out', 'screencap', '-p')
    (OUTPUT / (name + '.png')).write_bytes(shot)
    return current, shot


def main():
    OUTPUT.mkdir(parents=True, exist_ok=True)
    original_saves = saves()
    current, shot = launch('initial')
    adb('shell', 'input', 'keyevent', 'KEYCODE_HOME')
    time.sleep(1)
    assert pid() == current, 'Home ended the game process'
    resumed, shot = launch('resumed')
    assert resumed == current, 'Returning from Home restarted the game'

    for cycle in range(1, 4):
        width, height = struct.unpack_from('>II', shot, 16)
        scale = min(width / 240, height / 320)
        # Quit occupies x=94..149, y=148..172 in the original main menu.
        x = round((width - 240 * scale) / 2 + 120 * scale)
        y = round((height - 320 * scale) / 2 + 160 * scale)
        adb('shell', 'input', 'tap', str(x), str(y))
        deadline = time.monotonic() + 10
        while pid() and time.monotonic() < deadline:
            time.sleep(0.2)
        logs = adb('logcat', '-d', '--pid=' + current, '-s', 'SDL/APP')
        (OUTPUT / f'quit-{cycle}.log').write_bytes(logs)
        assert b'WinMain returned 0' in logs, 'Menu Quit did not complete'
        assert not pid(), 'Quit left the game process and arena alive'
        reopened, shot = launch(f'reopened-{cycle}')
        assert reopened != current, 'Reopen reused the old process'
        assert saves() == original_saves, 'Saved games changed during restart'
        print(f'Cycle {cycle}: Quit ended PID {current}; reopened as {reopened}')
        current = reopened
    print('PASS: three Quit/reopen cycles, Home/resume, and save preservation')


if __name__ == '__main__':
    main()
