#!/usr/bin/env python3
"""ゲート: 共有ラベルバッファが、ビルドが返し得る最長ラベルを保持できること。

`AZARAC_FLASH_BUF_SIZE` は src/azaraC_config.h で有効なカテゴリから選ばれるが、ラベルは *独立した* ガードマクロ（src/definition/*.h）で有効になるテーブルにある。
最長ラベルがそのバッファより大きいカテゴリを有効にすると、`azarac_pgm_view` はコピーを `AZARAC_FLASH_BUF_SIZE - 1` で打ち切り（internal/FlashString.h）、ラベルは黙って切り詰められる。
切れ目は UTF-8 の途中に落ちるので、JSON 出力はエラーではなく壊れたラベルを載せる。
AVR プリセットでは起きない（SEISMIC/TSUNAMI のラベルは最大 45 B）が、`-D` で有効にした他のカテゴリでは起きる。
`-D` が文書化された設定方法だからだ。

カテゴリフラグの全組み合わせ・両言語・出荷する 2 プリセット（Uno/atmega328p と Mega/atmega2560）について次を検査する:

    AZARAC_FLASH_BUF_SIZE - 1  >=  有効な全テーブルの最長ラベル

テーブルは生成ヘッダから取る（各ガードブロックの非圧縮 host 分岐が、AVR 側が再現するラベル集合）。
単一リテラルだけでなく、NUL 区切りプール内の各ラベルと、プール内ラベルに親（+ 祖父）プールを連結した後の長さも検査する。
サイズ連鎖は azaraC_config.h の `#if`/`#elif` 連鎖から読む。
いくつかの設定は実 AVR プリプロセッサと突き合わせ、連鎖パーサがマクロからずれないようにする。

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
POOL = re.compile(r'static const char AZARAC_PROGMEM (\w+)\[\]\s*[^=]*=\s*"((?:[^"\\]|\\.)*)";')
CHILD_TABLE = re.compile(r'static const \w+_Entry\s+(\w+)_TABLE\[\]\s*[^=]*=\s*\{(.*?)\};', re.S)
PARENT_TABLE = re.compile(r'static const \w+_PARENT_Entry\s+(\w+)_PARENT_TABLE\[\]\s*[^=]*=\s*\{(.*?)\};', re.S)
GRAND_TABLE = re.compile(r'static const \w+_GRAND_Entry\s+(\w+)_GRAND_TABLE\[\]\s*[^=]*=\s*\{(.*?)\};', re.S)
ENTRY_STRUCT = re.compile(r'struct (\w+_Entry)\s*\{([^}]*)\};')


def table_fields(text):
    """構造体宣言から {構造体名: [フィールド名, ...]} を作る。

    行の要素の意味はフィールド名で決まる（戦略ごとに `{offset, parent}` だったり `{id, parent, offset}` だったりする）ので、宣言から名前を取る。
    """
    return {name: re.findall(r'\b(\w+)\s*;', body)
            for name, body in ENTRY_STRUCT.findall(text)}


def table_rows(body):
    """`{0u, 255u},` 形式の行を整数リストにする。"""
    return [[int(x.strip().rstrip("u")) for x in row.split(",") if x.strip()]
            for row in re.findall(r'\{([^}]*)\}', body)]


def offset_lengths(data):
    """NUL 区切りプールの {開始オフセット: バイト長}。"""
    out = {}
    start = 0
    for i, b in enumerate(data):
        if b == 0:
            if i > start:
                out[start] = i - start
            start = i + 1
    if start < len(data):
        out[start] = len(data) - start
    return out


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

    `frames` は開いている `#if` ごとに 1 つのカテゴリ frozenset を持つ。
    ガードはフレーム内でカテゴリを OR でまとめ（`(A || B) && (LANG_JA)`）、フレーム同士を AND で繋ぐので、OR の組は分けたままにする。
    まとめてしまうと OR 組の全カテゴリを要求し、どれか 1 つで有効になるテーブルを取りこぼす。

    ラベルは 3 形態あるので全部見る: 単一リテラル（switch 戦略）、NUL 区切りプール内の各ラベル（binary_search 戦略の葉）。
    プール内ラベル＋親（＋祖父）プールの連結後（`azarac_pgm_join_z` / `join3` が返す長さ）。
    プールを丸ごと飛ばすと後者 2 つを見落とす。

    ラベルごとに 1 エントリ持つと設定のたびに再走査になるが、効き得るのは条件ごとの最長だけであり条件も少ないので、ここで畳み込む。
    """
    out = {}
    # listdir でなく os.walk: 手書きテーブルは definition/manual/ にあり、同じ共有バッファ経由でラベルを返すので、これらも走査対象にする。
    paths = []
    for root, _dirs, files in os.walk(DEFS):
        paths.extend(os.path.join(root, f) for f in files if f.endswith(".h"))
    for path in sorted(paths):
        name = os.path.relpath(path, DEFS).replace(os.sep, "/")
        blocks = {}
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
            key = (tuple(frozenset(c) for c, _ in stack),
                   tuple(l for _, l in stack if l))
            blocks.setdefault(key, []).append(line)

        for key, lines in blocks.items():
            text = "".join(lines)

            def put(n):
                if n > out.get(key, (0, ""))[0]:
                    out[key] = (n, name)

            # 単一リテラル（プール以外）
            for line in lines:
                for body in LITERAL.findall(line):
                    if "\\0" in body:
                        continue  # NUL 区切りのプールであり、単一ラベルではない
                    data = unescape(body)
                    if data:
                        put(len(data))

            # プール内の各ラベル
            pools = {}
            for m in POOL.finditer(text):
                data = unescape(m.group(2))
                if data is None:
                    continue
                pools[m.group(1)] = offset_lengths(data)
                for length in pools[m.group(1)].values():
                    put(length)

            # 分割ラベルの連結後（子 + 親 + 祖父）
            fields = table_fields(text)
            parents = {n: (table_rows(b), fields.get(n + "_PARENT_Entry", ["offset", "grand"]))
                       for n, b in PARENT_TABLE.findall(text)}
            grands = {n: (table_rows(b), fields.get(n + "_GRAND_Entry", ["offset"]))
                      for n, b in GRAND_TABLE.findall(text)}
            for base, body in CHILD_TABLE.findall(text):
                if base.endswith("_PARENT") or base.endswith("_GRAND"):
                    continue  # 親・祖父テーブル自体は下から参照されるだけ
                child = pools.get(base + "_POOL")
                parent = pools.get(base + "_PARENT_POOL")
                grand = pools.get(base + "_GRAND_POOL")
                if not child:
                    continue
                child_fields = fields.get(base + "_Entry", ["id", "offset"])
                for row in table_rows(body):
                    entry = dict(zip(child_fields, row))
                    off = entry.get("offset")
                    if off not in child:
                        continue
                    length = child[off]
                    pi = entry.get("parent", 255)
                    if pi != 255 and parent and base in parents:
                        prows, pfields = parents[base]
                        if pi < len(prows):
                            p = dict(zip(pfields, prows[pi]))
                            poff = p.get("offset")
                            if poff in parent:
                                length += parent[poff]
                                gi = p.get("grand", 255)
                                if gi != 255 and grand and base in grands:
                                    grows, gfields = grands[base]
                                    if gi < len(grows):
                                        goff = dict(zip(gfields, grows[gi])).get("offset")
                                        if goff in grand:
                                            length += grand[goff]
                    put(length)
    return out


def parse_ladder():
    """AZARAC_FLASH_BUF_SIZE の連鎖から [(categories, language|None, size)] を返す。

    連鎖は自前のもの（機械的に大小比較でき、カテゴリ群ごとに 1 分岐）なので、素直な置換で足りる。
    正しさは `crosscheck_ladder` が avr-gcc と突き合わせて示す。
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
