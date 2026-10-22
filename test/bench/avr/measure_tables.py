#!/usr/bin/env python3
"""生成定義テーブルの AVR flash コスト（autoresearch.sh stage 1）。

入力: 全カテゴリ・両言語を有効にした ATmega2560 向け `avr-gcc -E` の出力
（"tables.i"）。分岐を選ぶのは *本物の* AVR プリプロセッサなので、テキストには
AVR ビルドがコンパイルするテーブルがそのまま入る — AZARAC_ENABLE_* /
AZARAC_LANG_* ガードのモデルを二重に持たなくてよい。

ここで数えるもの（AVR ではすべて Flash に載る）:

  AVR_STRING_BYTES   `[] = "..."` の全初期化子: 文字列プール本体と、
                     `switch` 方式テーブルの case ごとのリテラル。
                     GCC は len バイトのリテラルに len+1 バイトを置く（暗黙の
                     終端 NUL）。
  AVR_ENTRY_BYTES    各 `..._TABLE[]` 配列を rows x sizeof(ヘッダ自身の
                     `..._Entry`) として、AVR-GCC の自然アラインメントどおりに
                     並べたサイズ。

  AVR_TABLE_BYTES    上記の合計 — 主要指標。

両項は、同じシンボルについて avr-gcc が報告するサイズと突き合わせる
(crosscheck_tables.py)。

出力の各行は `METRIC <name>=<value>` 行。
"""

import re
import sys

# プリプロセス出力は宣言を `# 12 "file.h"` マーカーで分割し、__attribute__((__progmem__)) を独立した行へ持ち上げる。意味があるのは宣言本体だけなので、まずそれを取り除く。
# Flash が 64 KiB を超えると AZARAC_PROGMEM はインラインの `__attribute__((__section__(".text.azaraC.<n>")))` に展開される — 同じ属性で括弧が 1 段深いだけ — ので、パターンは両方を受ける（テキストは解析するだけでコンパイルしない）。
MARKER = re.compile(r'^# \d+ "[^"]*"(?: \d+)*$', re.M)
ATTR = re.compile(r'__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)')
LITERAL_START = re.compile(r'\[\]\s*=\s*"')
ENTRY_STRUCT = re.compile(r'struct\s+(\w+_Entry)\s*\{([^}]*)\}\s*;')
TABLE = re.compile(r'(\w+_TABLE)\[\]\s*=\s*\{(.*?)\n\s*\};', re.S)
ROW = re.compile(r'\{\s*[0-9][0-9a-fA-FxXuUlL]*(?:\s*,\s*[0-9][0-9a-fA-FxXuUlL]*)*\s*\}')
NAME = re.compile(r'(\w+)\s*$')

# AVR-GCC はこれらのフィールドにバイト境界のアラインメントを与える（avr-gcc 7.3.0 で実測: `{uint8_t id; uint16_t offset; uint16_t len;}` のエントリは 5 バイトで、2 バイト境界なら 6 バイトになるところ。alignof(uint64_t) は 1）。よってエントリはフィールドの単純合計。
# 未知のフィールドはレイアウトモデルを見直すべき合図で、推測してはいけない。いずれにせよ crosscheck_tables.py が結果を avr-gcc と照合する。
SCALARS = {'uint8_t': 1, 'int8_t': 1, 'char': 1, 'bool': 1,
           'uint16_t': 2, 'int16_t': 2, 'uint32_t': 4, 'int32_t': 4,
           'uint64_t': 8, 'int64_t': 8,
           'const char*': 2, 'char*': 2}

# issue が個別に追跡するプール (issue #35)。報告のみ。
TRACKED = (
    'QZSS_DCX_EX1_TARGET_AREA_CODE_EN_POOL',
    'QZSS_DCX_EX1_TARGET_AREA_CODE_JA_POOL',
    'QZSS_DCR_JMA_LOCAL_GOVERNMENT_EN_POOL',
    'QZSS_DCR_JMA_LOCAL_GOVERNMENT_POOL',
)


def literal_bytes(lit: str) -> int:
    """コンパイラが文字列リテラル本体に格納するバイト数（エスケープは展開済み）。"""
    n = 0
    i = 0
    while i < len(lit):
        c = lit[i]
        if c != '\\':
            n += len(c.encode('utf-8', 'surrogateescape'))
            i += 1
            continue
        j = lit[i + 1]
        if j in '01234567':                      # \NNN
            k = i + 1
            while k < len(lit) and k < i + 4 and lit[k] in '01234567':
                k += 1
            n += 1
            i = k
        elif j == 'x':                           # \xNN
            k = i + 2
            while k < len(lit) and lit[k] in '0123456789abcdefABCDEF':
                k += 1
            n += 1
            i = k
        elif j in 'uU':                          # \uNNNN / \UNNNNNNNN
            width = 4 if j == 'u' else 8
            try:
                n += len(chr(int(lit[i + 2:i + 2 + width], 16)).encode('utf-8'))
                i += 2 + width
            except ValueError:
                n += 1
                i += 2
        else:                                    # \n \t \" \\ \'
            n += 1
            i += 2
    return n


def scan_literal(text: str, quote: int):
    """`text[quote] == '"'` から始まる文字列リテラルのバイト数（コンパイラが連結する
    隣接リテラルも含む）と、その直後の位置。"""
    total = 0
    i = quote
    while True:
        j = i + 1
        while True:
            if text[j] == '\\':
                j += 2
                continue
            if text[j] == '"':
                break
            j += 1
        total += literal_bytes(text[i + 1:j])
        j += 1
        k = j
        while k < len(text) and text[k] in ' \t\n':
            k += 1
        if k < len(text) and text[k] == '"':
            i = k
            continue
        return total + 1, j          # +1: 暗黙の終端 NUL


def struct_size(body: str) -> int:
    """AVR-GCC の配置どおりの `{ type field; ... }` エントリ構造体の sizeof。"""
    size = 0
    for decl in body.split(';'):
        decl = decl.strip()
        if not decl:
            continue
        key = ' '.join(decl.split()[:-1]).replace(' *', '*')
        if key not in SCALARS:
            raise SystemExit(f'measure_tables: unsupported entry field {decl!r}')
        size += SCALARS[key]
    return size


def main(path: str, detail_path=None) -> int:
    with open(path, 'r', encoding='utf-8', errors='surrogateescape') as fh:
        text = ATTR.sub('', MARKER.sub('', fh.read()))

    sizes = {name: struct_size(body) for name, body in ENTRY_STRUCT.findall(text)}
    if not sizes:
        raise SystemExit('measure_tables: no entry structs found — wrong input?')

    entries = {}
    pools = {}
    count = 0
    largest = 0
    for m in LITERAL_START.finditer(text):
        head = NAME.search(text[max(0, m.start() - 200):m.start()])
        name = head.group(1) if head else '?'
        size, _ = scan_literal(text, m.end() - 1)
        pools[name] = pools.get(name, 0) + size
        count += 1
        largest = max(largest, size)

    rows = 0
    for m in TABLE.finditer(text):
        name = m.group(1)
        entry = name[:-len('_TABLE')] + '_Entry'
        if entry not in sizes:
            raise SystemExit(f'measure_tables: no struct for {name}')
        n = len(ROW.findall(m.group(2)))
        rows += n
        entries[name] = n * sizes[entry]

    strings = sum(pools.values())
    entry_bytes = sum(entries.values())
    row_bytes = entry_bytes // rows if rows else 0
    print(f'METRIC AVR_TABLE_BYTES={strings + entry_bytes}')
    print(f'METRIC AVR_STRING_BYTES={strings}')
    print(f'METRIC AVR_ENTRY_BYTES={entry_bytes}')
    print(f'METRIC AVR_ENTRY_ROWS={rows}')
    print(f'METRIC AVR_ENTRY_ROW_BYTES={row_bytes}')
    print(f'METRIC AVR_LARGEST_LITERAL={largest}')
    print(f'METRIC AVR_LITERALS={count}')
    print(f'METRIC AVR_TABLES={len(entries)}')
    for pool in TRACKED:
        if pool in pools:
            print(f'METRIC {pool}={pools[pool]}')
    if detail_path:
        # 計測した全シンボル。ハーネスがこのバイト数を avr-gcc 側と比較できるようにする。
        with open(detail_path, 'w', encoding='utf-8', newline='\n') as fh:
            for name in sorted(list(pools) + list(entries)):
                fh.write(f'{name} {pools.get(name, entries.get(name))}\n')
    return 0


if __name__ == '__main__':
    if len(sys.argv) not in (2, 3):
        print(__doc__, file=sys.stderr)
        raise SystemExit(2)
    raise SystemExit(main(*sys.argv[1:]))
