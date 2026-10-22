#!/usr/bin/env python3
"""主要指標を avr-gcc 自身と突き合わせる（autoresearch.sh stage 3）。

stdin: stage 3 がビルドしたオブジェクトに対する `avr-nm --print-size --radix=d -C` の出力。
argv[1]: measure_tables.py が書く `NAME BYTES` の詳細ファイル。

avr-gcc が実際に配置した各 `*_POOL` / `*_TABLE` シンボルは、measure_tables.py が
プリプロセス済みソースから解析した値と完全に一致すること。でなければ指標は
コンパイラが格納するもの以外を測っている。これがエントリ構造体のレイアウトモデルを
正しく保つ: 圧縮エンコーディングで構造体が変われば、モデルと avr-gcc が食い違い、
誤った数値を黙って報告せずに実行が失敗する。

網羅性は構造上部分的: テーブルはそれを参照する翻訳単位に住み、コンパイルできない
大きさのものはどのオブジェクトにもない — なので件数を報告する（ハーネスは検査した
ものだけをゲートする）。
azaraC 自身の手書きテーブル（HAND_WRITTEN_TABLES）は `_TABLE` 接尾辞を共有し、
autoresearch.sh の RAM ゲートに見えるようにしている。ここでは解析せず、件数から除外する。
"""

import sys

SUFFIXES = ('_POOL', '_TABLE')

# azaraC 自身の小さな Flash テーブル（internal/DcxHelper.cpp）は、生成定義テーブルと
# 同じ命名規約に従って「RAM にない」ゲートに拾われるようにしているが、measure_tables.py は
# 解析しない: 生成物ではなく手書きだから。これらの配置は MEGA_NEAR_SYM_ADDR でゲートする。
HAND_WRITTEN_TABLES = {'RADIUS_TABLE', 'B4_LAYOUT_TABLE'}


def main(pools_path: str) -> int:
    declared = {}
    with open(pools_path, encoding='utf-8') as fh:
        for line in fh:
            parts = line.split()
            if len(parts) == 2:
                declared[parts[0]] = int(parts[1])

    placed = {}
    for line in sys.stdin:
        parts = line.split()
        if len(parts) < 4 or len(parts[2]) != 1 or not parts[2].isalpha():
            continue
        # 無名名前空間の demangle 名は空白を含むので、名前は型フィールドより後ろ全部であり、
        # parts[3] だけではない。
        name = ' '.join(parts[3:]).rsplit('::', 1)[-1]
        if name in HAND_WRITTEN_TABLES:
            continue
        if name.endswith(SUFFIXES):
            placed[name] = max(placed.get(name, 0), int(parts[1]))

    matched = 0
    for name, size in sorted(placed.items()):
        want = declared.get(name)
        if want is None:
            print(f'autoresearch: {name} placed but not parsed', file=sys.stderr)
            continue
        if want == size:
            matched += 1
        else:
            print(f'autoresearch: {name}: avr-gcc placed {size} B, parsed {want} B', file=sys.stderr)
    pools = sum(s for n, s in placed.items() if n.endswith('_POOL'))
    tables = sum(s for n, s in placed.items() if n.endswith('_TABLE'))
    print(f'METRIC AVR_TABLE_CROSSCHECK={matched}/{len(placed)}')
    print(f'METRIC AVR_POOL_BYTES_NM={pools}')
    print(f'METRIC AVR_ENTRY_BYTES_NM={tables}')
    return 0


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print(__doc__, file=sys.stderr)
        raise SystemExit(2)
    raise SystemExit(main(sys.argv[1]))
