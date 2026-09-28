#!/usr/bin/env python3
"""Audit selected walkthrough claims against recovered Fade scripts.

This is a small inventory/branch interpreter, not a game emulator. Scene flags,
dialogue, timing, menus and input are deliberately outside its scope.
"""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]


def records(name):
    return (ROOT / 'assets/Data' / name).read_text(encoding='latin1').split('[#')[1:]


SCENES = records('Data.Fad.txt')
ITEMS = records('DataObjets.Fad.txt')


def scripts(record):
    # _Ac# is also an item-menu field; only _Ac_ begins a script.
    return [s.split('_FA')[0] for s in re.split(r'_Ac(?=_)', record)[1:]]


def run(record, start, inventory):
    blocks = scripts(record)
    visited, transitions = [], []
    current = start
    for _ in range(100):
        visited.append(current)
        following = None
        for op, value in re.findall(r'_(Pr|Ef|If|Al)#([^_]*)', blocks[current]):
            value = value.rstrip('#')
            if op == 'Pr':
                inventory.add(int(value))
            elif op == 'Ef':
                inventory.discard(int(value))
            elif op == 'Al':
                transitions.append(int(value))
            else:
                required, yes, no = value.split('##')
                following = int(yes if set(map(int, required.split(','))) <= inventory else no)
        # Script_Run executes all operations, then Script_RunList follows If.
        if following is None:
            return visited, transitions
        current = following
    raise AssertionError('Unexpected script loop')


def scene(number):
    return SCENES[number - 1]


def check():
    assert len(SCENES) == 448 and len(ITEMS) == 145
    inventory = set()
    for action in (2, 3, 4, 6):  # Gemini, Cancer, Leo, Libra
        run(scene(163), action, inventory)
    assert run(scene(163), 12, inventory)[1] == [164]
    inventory = set()
    run(scene(163), 0, inventory)  # a wrong symbol
    for action in (2, 3, 4, 6):
        run(scene(163), action, inventory)
    assert run(scene(163), 12, inventory)[1] == []
    assert not inventory  # failed submission resets the puzzle
    print('PASS: zodiac sequence and reset')

    inventory = {111}
    for digit in (2, 3, 1, 9):
        run(scene(260), digit, inventory)
    assert 19 in run(scene(260), 11, inventory)[0]
    inventory = set()
    for digit in (9, 1, 3, 2):
        run(scene(260), digit, inventory)
    assert 19 not in run(scene(260), 11, inventory)[0]
    print('PASS: keypad 2319 and rejected wrong code')

    inventory = set()
    visited = []
    for action in (4, 6, 7, 13):  # Isis west; submit; Mnemosis NE; submit
        visited += run(scene(319), action, inventory)[0]
    assert 22 in visited  # opens female statue
    assert '_Ps#319,5,2##1#' in scripts(scene(319))[22]
    inventory = set()
    visited = []
    for action in (0, 6, 7, 13):
        visited += run(scene(319), action, inventory)[0]
    assert 22 not in visited
    print('PASS: temple selections and rejected wrong symbol')

    evidence = {33, 34, 35, 36, 37, 71, 141}
    assert run(scene(90), 1, set(evidence))[1] == [91]
    for missing in evidence:
        assert run(scene(90), 1, evidence - {missing})[1] == []
    assert run(scene(90), 1, evidence | {38})[1] == []
    print('PASS: police evidence and undeveloped-film gates')

    assert run(scene(392), 0, {66, 67, 68})[1] == [394]
    for missing in (66, 67, 68):
        assert run(scene(392), 0, {66, 67, 68} - {missing})[1] == []
    endings = [n for n, record in enumerate(SCENES, 1) if '_Fj' in record]
    assert endings == [447]
    print('PASS: final observation gate and ending opcode')

    assert '_Pz#3,3,2,3##1#' in scripts(scene(8))[5]
    assert '_Pz#213,0,0,5##1#' in scripts(ITEMS[104])[1]
    print('PASS: phone unlocks bedroom photo; candles unlock tobacco')

    inventory = {79}
    run(ITEMS[78], 1, inventory)
    assert 79 not in inventory
    restores = [n for n, record in enumerate(SCENES, 1)
                if re.search(r'_Pr#79#', record)]
    assert restores == [215]
    assert '_Pi#79,3##1#' in scripts(scene(237))[2]
    print('KNOWN SOURCE ISSUE: club outfit removes briefcase needed for window escape')
    print('Audit complete; full gameplay and port behavior remain untested.')


if __name__ == '__main__':
    check()
