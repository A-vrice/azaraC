#!/usr/bin/env python3
"""ゲート: 共有ラベルバッファが、ビルドが返し得る最長ラベルを保持できること。

`AZARAC_FLASH_BUF_SIZE` は src/azaraC_config.h で有効なカテゴリから選ばれるが、
ラベルは *独立した* ガードマクロ（src/definition/*.h）で有効になるテーブルにある。
最長ラベルがそのバッファより大きいカテゴリを有効にすると、`azarac_pgm_view` は
コピーを `AZARAC_FLASH_BUF_SIZE - 1` で打ち切り（internal/FlashString.h）、ラベルは
黙って切り詰められる — 切れ目は UTF-8 の途中に落ちるので、JSON 出力はエラーではなく
壊れたラベルを載せる。AVR プリセットでは起きない（SEISMIC/TSUNAMI のラベルは最大 45 B）
が、`-D` で有効にした他のカテゴリでは起きる。`-D` が文書化された設定方法だからだ。

カテゴリフラグの全組み合わせ・両言語・出荷する 2 プリセット（Uno/atmega328p と
Mega/atmega2560）について次を検査する:

    AZARAC_FLASH_BUF_SIZE - 1  >=  有効な全テーブルの最長ラベル

テーブルは生成ヘッダから取る（各ガードブロックの非圧縮 host 分岐が、AVR 側が再現する
ラベル集合）。サイズ連鎖は azaraC_config.h の `#if`/`#elif` 連鎖から読む。いくつかの
設定は実 AVR プリプロセッサと突き合わせ、連鎖パーサがマクロからずれないようにする。

実行: python test/bench/avr/check_flash_buf.py [--avr-gcc avr-gcc] [--quiet]
終了: 0 = 全設定が収まる、1 = 少なくとも 1 つが切り詰める、2 = 使用方法/準備の誤り。
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
# ユーザーが設定できるフラグ。AVR プリセットが固定するものは別途扱う。
TUNABLE = [c for c in CATEGORIES if c not in ("SEISMIC", "TSUNAMI")]

# test/bench/avr/check_flash_buf.py -> repository root
REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
DEFS = os.path.join(REPO, "src", "definition")
CONFIG_H = os.path.join(REPO, "src", "azaraC_config.h")

LITERAL = re.compile(r'"((?:[^"\\]|\\.)*)"')
GUARD = re.compile(r'#\s*if\s+(.*)')


def unescape(text):
    """C 文字列リテラル本体のバイト列（UTF-8 はバイト単位でそのまま）。"""
    try:
        return text.encode("utf-8").decode("unicode_escape").encode("latin-1")
    except (UnicodeDecodeError, UnicodeEncodeError):
        return None


def parse_condition(expr):
    """生成ガードの (categories, language)。例: '(A || B) && (AZARAC_LANG_JA)'。"""
    cats = frozenset(re.findall(r'AZARAC_ENABLE_(\w+)', expr))
    lang = None
    if "AZARAC_LANG_EN" in expr:
        lang = "EN"
    elif "AZARAC_LANG_JA" in expr:
        lang = "JA"
    return cats, lang


def scan_tables():
    """ガード条件ごとの最長ラベル: {(frames, languages): (bytes, file)}。

    `frames` は開いている `#if` ごとに 1 つのカテゴリ frozenset を持つ。ガードは
    フレーム内でカテゴリを OR でまとめ（`(A || B) && (LANG_JA)`）、フレーム同士を
    AND で繋ぐので、OR の組は分けたままにする: まとめてしまうと OR 組の全カテゴリを
    要求し、どれか 1 つで有効になるテーブルを取りこぼす。

    ラベルごとに 1 エントリ持つと設定のたびに再走査になるが、効き得るのは条件ごとの
    最長だけであり条件も少ないので、ここで畳み込む。
    """
    out = {}
    # listdir でなく os.walk: 手書きテーブルは definition/manual/ にあり、同じ共有
    # バッファ経由でラベルを返すので、これらも走査対象にする。
    paths = []
    for root, _dirs, files in os.walk(DEFS):
        paths.extend(os.path.join(root, f) for f in files if f.endswith(".h"))
    for path in sorted(paths):
        name = os.path.relpath(path, DEFS).replace(os.sep, "/")
        stack = []  # [(categories, language)]、開いている #if ごとに 1 エントリ
        for line in open(path, encoding="utf-8"):
            stripped = line.lstrip()
            if stripped.startswith("#if"):
                stack.append(parse_condition(stripped))
                continue
            if stripped.startswith("#endif"):
                if stack:
                    stack.pop()
                continue
            if stripped.startswith("#"):
                continue  # #include "..." はラベルではない
            if '"' not in line:
                continue
            frames = tuple(frozenset(c) for c, _ in stack)
            langs = tuple(l for _, l in stack if l)
            for body in LITERAL.findall(line):
                if "\\0" in body:
                    continue  # NUL 区切りのプールであり、単一ラベルではない
                data = unescape(body)
                if not data:
                    continue
                key = (frames, langs)
                if len(data) > out.get(key, (0, ""))[0]:
                    out[key] = (len(data), name)
    return out


def parse_ladder():
    """AZARAC_FLASH_BUF_SIZE の連鎖から [(categories, language|None, size)] を返す。

    連鎖は自前のもの（機械的に大小比較でき、カテゴリ群ごとに 1 分岐）なので、
    素直な置換で足りる。正しさは `crosscheck_ladder` が avr-gcc と突き合わせて示す。
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
    """`flags`（カテゴリ → 0/1 の dict）に対して連鎖が選ぶサイズ。"""
    for cats, lang, size in chain:
        if lang is not None and not flags.get("LANG_" + lang, True):
            continue
        if not cats or any(flags.get(c, 0) for c in cats):
            return size
    raise SystemExit("check_flash_buf: no ladder branch matched")


def needed(tables, flags):
    """その設定が返し得る最長ラベルの (bytes, file)。"""
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
    """いくつかの設定について、解析した連鎖を avr-gcc -dM と比較する。"""
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
    """全プリセット + 全カテゴリの組み合わせ、両言語、出荷する 2 MCU。"""
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
