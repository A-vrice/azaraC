#!/usr/bin/env python3
"""Gate: the shared label buffer must hold the longest label a build can return.

`AZARAC_FLASH_BUF_SIZE` is selected from the enabled categories in
src/azaraC_config.h, but the labels live in tables that are enabled by
*independent* guard macros (src/definition/*.h). When a category whose longest
label is bigger than the buffer it selects is turned on, `azarac_pgm_view` clamps
the copy at `AZARAC_FLASH_BUF_SIZE - 1` (internal/FlashString.h) and the label is
silently truncated — the cut lands mid-UTF-8, so JSON output carries a mangled
label instead of an error. The AVR presets never hit it (SEISMIC/TSUNAMI labels
are 45 B at most) but any other category enabled with `-D` does, which is the
documented way to configure this library.

What this checks, for every combination of category flags, both languages and
both shipped presets (Uno/atmega328p and Mega/atmega2560):

    AZARAC_FLASH_BUF_SIZE - 1  >=  longest label of every enabled table

The tables come from the generated headers (the uncompressed host branch of each
guard block is the label set the AVR side reproduces), the ladder from the
`#if`/`#elif` chain in azaraC_config.h. A handful of configurations are
cross-checked against the real AVR preprocessor so the ladder parser cannot
drift from the macro.

Run: python test/bench/avr/check_flash_buf.py [--avr-gcc avr-gcc] [--quiet]
Exit: 0 = every configuration fits, 1 = at least one truncates, 2 = usage/setup.
"""

import argparse
import itertools
import os
import re
import subprocess
import sys

CATEGORIES = (
    "EEW", "HYPOCENTER", "SEISMIC", "NANKAI", "TSUNAMI", "NW_PAC_TSUNAMI",
    "VOLCANO", "ASH_FALL", "WEATHER", "FLOOD", "TYPHOON", "MARINE", "DCX_CAMF",
)
# Flags a user may set; the ones the AVR preset fixes are handled separately.
TUNABLE = [c for c in CATEGORIES if c not in ("SEISMIC", "TSUNAMI")]

# test/bench/avr/check_flash_buf.py -> repository root
REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
DEFS = os.path.join(REPO, "src", "definition")
CONFIG_H = os.path.join(REPO, "src", "azaraC_config.h")

LITERAL = re.compile(r'"((?:[^"\\]|\\.)*)"')
GUARD = re.compile(r'#\s*if\s+(.*)')


def unescape(text):
    """Bytes of a C string literal's body (UTF-8 stays byte-for-byte)."""
    try:
        return text.encode("utf-8").decode("unicode_escape").encode("latin-1")
    except (UnicodeDecodeError, UnicodeEncodeError):
        return None


def parse_condition(expr):
    """(categories, language) for a generated guard: '(A || B) && (AZARAC_LANG_JA)'."""
    cats = frozenset(re.findall(r'AZARAC_ENABLE_(\w+)', expr))
    lang = None
    if "AZARAC_LANG_EN" in expr:
        lang = "EN"
    elif "AZARAC_LANG_JA" in expr:
        lang = "JA"
    return cats, lang


def scan_tables():
    """Longest label per guard condition: {(frames, languages): (bytes, file)}.

    `frames` holds one frozenset of categories per open `#if`. A guard groups
    categories with OR inside a frame (`(A || B) && (LANG_JA)`) and ANDs the
    frames, so the groups stay separate: merging them would demand every
    category of an OR group and skip the tables a one-of-them build selects.

    One entry per label would be re-scanned for every configuration; only the
    longest per condition can matter, and the conditions are few, so they are
    folded here instead.
    """
    out = {}
    for name in sorted(os.listdir(DEFS)):
        if not name.endswith(".h"):
            continue
        stack = []  # [(categories, language)], one entry per open #if
        for line in open(os.path.join(DEFS, name), encoding="utf-8"):
            stripped = line.lstrip()
            if stripped.startswith("#if"):
                stack.append(parse_condition(stripped))
                continue
            if stripped.startswith("#endif"):
                if stack:
                    stack.pop()
                continue
            if stripped.startswith("#"):
                continue  # #include "..." is not a label
            if '"' not in line:
                continue
            frames = tuple(frozenset(c) for c, _ in stack)
            langs = tuple(l for _, l in stack if l)
            for body in LITERAL.findall(line):
                if "\\0" in body:
                    continue  # a NUL-separated pool, not one label
                data = unescape(body)
                if not data:
                    continue
                key = (frames, langs)
                if len(data) > out.get(key, (0, ""))[0]:
                    out[key] = (len(data), name)
    return out


def parse_ladder():
    """[(categories, language|None, size)] from the AZARAC_FLASH_BUF_SIZE chain.

    The chain is ours (machine-sized, one branch per category group), so a plain
    substitution is enough; `crosscheck_ladder` proves it against avr-gcc.
    """
    text = open(CONFIG_H, encoding="utf-8").read()
    chain = re.search(r'#ifndef AZARAC_FLASH_BUF_SIZE\n(.*?)\n#endif', text, re.S)
    if not chain:
        raise SystemExit("check_flash_buf: AZARAC_FLASH_BUF_SIZE chain not found")
    out = []
    for line in chain.group(1).splitlines():
        m = re.match(r'\s*#\s*(if|elif|else)\s*(.*)', line)
        if m:
            kind, expr = m.group(1), m.group(2)
            cats, lang = parse_condition(expr) if kind != "else" else (frozenset(), None)
            out.append((cats, lang, kind, expr.strip()))
            continue
        m = re.match(r'\s*#\s*define\s+AZARAC_FLASH_BUF_SIZE\s+(\d+)', line)
        if m and out:
            cats, lang, kind, expr = out[-1]
            out[-1] = (cats, lang, int(m.group(1)))
    return [b for b in out if len(b) == 3]


def picks(chain, flags):
    """Size the ladder selects for `flags` (a dict of category -> 0/1)."""
    for cats, lang, size in chain:
        if lang is not None and not flags.get("LANG_" + lang, True):
            continue
        if not cats or any(flags.get(c, 0) for c in cats):
            return size
    raise SystemExit("check_flash_buf: no ladder branch matched")


def needed(tables, flags):
    """(bytes, file) of the longest label the configuration can return."""
    worst = (0, "")
    for (frames, langs), (size, name) in tables.items():
        if any(l and not flags.get("LANG_" + l, True) for l in langs):
            continue
        if any(frame and not any(flags.get(c, 0) for c in frame) for frame in frames):
            continue
        if size > worst[0]:
            worst = (size, name)
    return worst


def crosscheck_ladder(chain, avr_gcc, configs):
    """Compare the parsed ladder against avr-gcc -dM for a few configurations."""
    bad = 0
    for mcu, flags in configs:
        args = [avr_gcc, "-E", "-dM", "-mmcu=" + mcu, "-I", os.path.join(REPO, "src"), "-x", "c++",
                CONFIG_H]
        for cat in TUNABLE:
            args.append("-DAZARAC_ENABLE_%s=%d" % (cat, flags.get(cat, 0)))
        args.append("-DAZARAC_LANG_JA=%d" % flags.get("LANG_JA", 1))
        args.append("-DAZARAC_LANG_EN=%d" % flags.get("LANG_EN", 0))
        proc = subprocess.run(args, capture_output=True, text=True)
        if proc.returncode != 0:
            print("check_flash_buf: avr-gcc failed:\n" + proc.stderr[-500:], file=sys.stderr)
            return 2
        m = re.search(r'^#define AZARAC_FLASH_BUF_SIZE (\d+)', proc.stdout, re.M)
        if not m:
            print("check_flash_buf: buffer macro missing from the preprocessor output",
                  file=sys.stderr)
            return 2
        real = int(m.group(1))
        parsed = picks(chain, flags)
        if real != parsed:
            print("check_flash_buf: ladder parser says %d, avr-gcc says %d (mcu=%s, %s)"
                  % (parsed, real, mcu, sorted(k for k, v in flags.items() if v)), file=sys.stderr)
            bad += 1
    return 1 if bad else 0


def configurations():
    """Every preset + category combination, both languages, both shipped MCUs."""
    for mcu, large in (("atmega328p", 0), ("atmega2560", 1)):
        for lang_ja, lang_en in ((1, 0), (0, 1), (1, 1)):
            for combo in itertools.product((0, 1), repeat=len(TUNABLE)):
                flags = dict(LANG_JA=lang_ja, LANG_EN=lang_en)
                flags.update(zip(TUNABLE, combo))
                flags.setdefault("SEISMIC", 1)
                flags.setdefault("TSUNAMI", 1)
                if "DCX_CAMF" not in flags:
                    flags["DCX_CAMF"] = large
                yield mcu, flags


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--avr-gcc", default="avr-gcc")
    ap.add_argument("--quiet", action="store_true")
    args = ap.parse_args()

    tables = scan_tables()
    if not tables:
        print("check_flash_buf: no labels found under " + DEFS, file=sys.stderr)
        return 2
    chain = parse_ladder()

    samples = [("atmega328p", {"LANG_JA": 1, "LANG_EN": 0, **{c: 0 for c in TUNABLE}, "DCX_CAMF": 0}),
               ("atmega328p", {"LANG_JA": 1, "LANG_EN": 0, **{c: 0 for c in TUNABLE}, "EEW": 1}),
               ("atmega328p", {"LANG_JA": 1, "LANG_EN": 0, **{c: 0 for c in TUNABLE}, "VOLCANO": 1}),
               ("atmega328p", {"LANG_JA": 1, "LANG_EN": 0, **{c: 1 for c in TUNABLE}}),
               ("atmega2560", {"LANG_JA": 1, "LANG_EN": 0, **{c: 0 for c in TUNABLE}, "DCX_CAMF": 1}),
               ("atmega2560", {"LANG_JA": 0, "LANG_EN": 1, **{c: 0 for c in TUNABLE}, "FLOOD": 1})]
    rc = crosscheck_ladder(chain, args.avr_gcc, samples)
    if rc:
        return rc

    failures = []
    for mcu, flags in configurations():
        size = picks(chain, flags)
        need, who = needed(tables, flags)
        if need > size - 1:
            on = sorted(k for k, v in flags.items() if v and not k.startswith("LANG_"))
            failures.append((size, need, who, mcu, on))

    if not failures:
        if not args.quiet:
            print("check_flash_buf: ok (%d guard conditions, %d ladder branches, "
                  "buffer holds every enabled label)" % (len(tables), len(chain)))
        return 0

    failures.sort(key=lambda f: f[1] - f[0], reverse=True)
    worst = failures[0]
    print("check_flash_buf: %d configuration(s) return a truncated label; worst:" % len(failures))
    for size, need, who, mcu, on in failures[:5]:
        print("  %s  buffer %d < label %d B (%s)  categories: %s"
              % (mcu, size, need, who, ",".join(on)))
    return 1


if __name__ == "__main__":
    sys.exit(main())
