#!/usr/bin/env python3
"""compare_nankai_aggregation.py — azarashi 出力と AzaraC 集約結果を比較する

test/data/nankai_vectors.json（azarashi 出力）を唯一の情報源とする。
C++ 側のページフィクスチャ test/data/nankai_pages_generated.h は
gen_all_vectors.py の gen_nankai() が同じ JSON から生成するため、
C++ と Python でページデータが二重管理されることはない。

検証内容:
  1. JSON のページ構成（欠落ページがないか）
  2. NUL 打ち切り（compactText 相当）を反映した期待集約本文
  3. test/decode_to_json に 27 電文を通したときの集約本文が期待値と一致するか
"""

import io
import json
import os
import subprocess
import sys

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
sys.stderr = io.TextIOWrapper(sys.stderr.buffer, encoding='utf-8', errors='replace')

BASE = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
VECTORS = os.path.join(BASE, 'test', 'data', 'nankai_vectors.json')
_exe = '.exe' if os.name == 'nt' else ''
AZARAC_BIN = os.path.join(BASE, 'test', f'decode_to_json{_exe}')


def load_pages():
    """Return (pages, nmeas) from nankai_vectors.json, keyed by page number."""
    with open(VECTORS, encoding='utf-8') as f:
        vectors = json.load(f)

    pages = {}
    nmeas = {}
    for v in vectors:
        p = v.get('params')
        if not p or 'page_number' not in p:
            continue
        raw = p['text_information']
        pages[p['page_number']] = raw if isinstance(raw, (bytes, bytearray)) else bytes.fromhex(raw)
        if p.get('nmea'):
            nmeas[p['page_number']] = p['nmea']
    return pages, nmeas


def compact(page_bytes):
    """Page text up to the first NUL (mirrors NankaiPageBuffer::compactText)."""
    return page_bytes.split(b'\x00', 1)[0]


def main():
    pages, nmeas = load_pages()
    if not pages:
        print(f"No pages found in {VECTORS}")
        return 1

    total = max(pages)
    print(f"nankai_vectors.json: {len(pages)} messages, pages {sorted(pages)}")

    missing = [n for n in range(1, total + 1) if n not in pages]
    if missing:
        print(f"  ERROR: missing pages {missing}")
        return 1
    if len(nmeas) != total:
        print(f"  ERROR: missing NMEA for pages {sorted(set(range(1, total + 1)) - set(nmeas))}")
        return 1

    expected = b''.join(compact(pages[n]) for n in range(1, total + 1))
    raw_total = sum(len(pages[n]) for n in range(1, total + 1))
    print(f"  expected aggregated body: {len(expected)} bytes "
          f"(page payload total {raw_total}; final page NUL-padded)")

    if not os.path.exists(AZARAC_BIN):
        print(f"  AzaraC binary not found: {AZARAC_BIN}")
        print("  Build with: make -C test decode")
        return 0

    print("=== AzaraC decode_to_json aggregation verification ===")
    input_text = "\n".join(nmeas[n] for n in range(1, total + 1)) + "\n"
    try:
        # check=False: 失敗時は returncode と stderr を自前で整形して報告する
        # （CalledProcessError にスタックトレースを出させない）。
        result = subprocess.run(
            [AZARAC_BIN], input=input_text, capture_output=True, text=True,
            timeout=30, encoding='utf-8', errors='replace', check=False)
    except Exception as e:  # noqa: BLE001 — 手動ツールのため広く捕捉
        print(f"  ERROR running {AZARAC_BIN}: {e}")
        return 1

    if result.returncode != 0:
        print(f"  AzaraC returned code {result.returncode}")
        if result.stderr:
            print(f"  stderr: {result.stderr[:500]}")
        return 1

    results = json.loads(result.stdout)
    print(f"  AzaraC decoded {len(results)} message(s)")

    aggregated = None
    for r in results:
        detail = r.get('detail', {})
        if 'text_utf8' in detail:
            aggregated = detail['text_utf8'].encode('utf-8')
            break

    if aggregated is None:
        print("  FAIL: no aggregated message (text_utf8) produced")
        return 1

    if aggregated == expected:
        print(f"  PASS: aggregated text_utf8 matches expected ({len(aggregated)} bytes)")
        return 0

    print(f"  FAIL: aggregated length {len(aggregated)} != expected {len(expected)}")
    n = min(len(aggregated), len(expected))
    for i in range(n):
        if aggregated[i] != expected[i]:
            print(f"    first diff at byte {i}")
            print(f"      AzaraC:   {aggregated[max(0, i - 5):i + 20].hex()}")
            print(f"      Expected: {expected[max(0, i - 5):i + 20].hex()}")
            break
    return 1


if __name__ == '__main__':
    sys.exit(main())
