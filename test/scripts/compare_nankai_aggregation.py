#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""compare_nankai_aggregation.py — テストのnankai_page_dataとazarashi出力を比較

nankai_vectors.jsonのtext_information（azarashi出力）をページ順に連結し、
test_nankai_e2e.cppのnankai_page_dataと比較する。
また、実際のNMEAメッセージをAzaraCのdecode_to_jsonツールに通し、
集約結果がazarashiと一致するかを検証する。
"""

import json
import os
import subprocess
import sys
import io

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
sys.stderr = io.TextIOWrapper(sys.stderr.buffer, encoding='utf-8', errors='replace')

BASE = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
VECTORS = os.path.join(BASE, 'test', 'data', 'nankai_vectors.json')
_exe = '.exe' if os.name == 'nt' else ''
AZARAC_BIN = os.path.join(BASE, 'test', f'decode_to_json{_exe}')
PYTHON = os.environ.get('PYTHON', sys.executable)

# NANKAI_PAGE_DATA: C++ 側 test_nankai_e2e.cpp の nankai_page_data[27][18] 固定フィクスチャ。
# この配列は azarashi 出力と照合済みであり、比較の参照側（expected）として使用する。
# 比較対象の azarashi_pages は nankai_vectors.json から独立して読み込まれるため、
# 両者は別ソースとなり、ドリフト検出が可能である。
#
# ページ構成（C++ のコメントより）:
#   page 1, 8-26 : azarashi text_information と完全一致
#   page 2-7     : 合成フィラー（nankai_vectors.json に実データ未収録）
#   page 27      : 合成値（同上）
NANKAI_PAGE_DATA = [
    bytes([0xE5,0x8D,0x97,0xE6,0xB5,0xB7,0xE3,0x83,0x88,0xE3,0x83,0xA9,0xE3,0x83,0x95,0xE6,0xB2,0xBF]),  # page 1
    bytes([0xE3,0x81,0x8A,0xE3,0x81,0x86,0xE3,0x81,0x8B,0xE3,0x82,0x93,0xE3,0x82,0x80,0xE3,0x82,0x8A]),  # page 2
    bytes([0xE3,0x81,0x8A,0xE3,0x81,0x86,0xE3,0x81,0x8B,0xE3,0x82,0x93,0xE3,0x82,0x80,0xE3,0x82,0x8A]),  # page 3
    bytes([0xE3,0x81,0x8A,0xE3,0x81,0x86,0xE3,0x81,0x8B,0xE3,0x82,0x93,0xE3,0x82,0x80,0xE3,0x82,0x8A]),  # page 4
    bytes([0xE3,0x81,0x8A,0xE3,0x81,0x86,0xE3,0x81,0x8B,0xE3,0x82,0x93,0xE3,0x82,0x80,0xE3,0x82,0x8A]),  # page 5
    bytes([0xE3,0x81,0x8A,0xE3,0x81,0x86,0xE3,0x81,0x8B,0xE3,0x82,0x93,0xE3,0x82,0x80,0xE3,0x82,0x8A]),  # page 6
    bytes([0xE3,0x81,0x8A,0xE3,0x81,0x86,0xE3,0x81,0x8B,0xE3,0x82,0x93,0xE3,0x82,0x80,0xE3,0x82,0x8A]),  # page 7
    bytes([0xE3,0x82,0x8C,0xE3,0x81,0xBE,0xE3,0x81,0x99,0xE3,0x80,0x82,0xE3,0x81,0x93,0xE3,0x81,0xAE]),  # page 8
    bytes([0xE9,0x80,0x9A,0xE5,0xB8,0xB8,0xE3,0x81,0xA8,0xE3,0x81,0xAF,0xE7,0x95,0xB0,0xE3,0x81,0xAA]),  # page 9
    bytes([0xE3,0x82,0x8B,0xE3,0x82,0x86,0xE3,0x81,0xA3,0xE3,0x81,0x8F,0xE3,0x82,0x8A,0xE3,0x81,0x99]),  # page 10
    bytes([0xE3,0x81,0xB9,0xE3,0x82,0x8A,0xE3,0x81,0xAE,0xE7,0x99,0xBA,0xE7,0x94,0x9F,0xE3,0x81,0xAB]),  # page 11
    bytes([0xE3,0x82,0x88,0xE3,0x82,0x8A,0xE3,0x80,0x81,0xE5,0x8D,0x97,0xE6,0xB5,0xB7,0xE3,0x83,0x88]),  # page 12
    bytes([0xE3,0x83,0xA9,0xE3,0x83,0x95,0xE5,0x9C,0xB0,0xE9,0x9C,0x87,0xE3,0x81,0xAE,0xE6,0x83,0xB3]),  # page 13
    bytes([0xE5,0xAE,0x9A,0xE9,0x9C,0x87,0xE6,0xBA,0x90,0xE5,0x9F,0x9F,0xE3,0x81,0xA7,0xE3,0x81,0xAF]),  # page 14
    bytes([0xE3,0x80,0x81,0xE5,0xA4,0xA7,0xE8,0xA6,0x8F,0xE6,0xA8,0xA1,0xE5,0x9C,0xB0,0xE9,0x9C,0x87]),  # page 15
    bytes([0xE3,0x81,0xAE,0xE7,0x99,0xBA,0xE7,0x94,0x9F,0xE5,0x8F,0xAF,0xE8,0x83,0xBD,0xE6,0x80,0xA7]),  # page 16
    bytes([0xE3,0x81,0x8C,0xE5,0xB9,0xB3,0xE5,0xB8,0xB8,0xE6,0x99,0x82,0xE3,0x81,0xAB,0xE6,0xAF,0x94]),  # page 17
    bytes([0xE3,0x81,0xB9,0xE3,0x81,0xA6,0xE7,0x9B,0xB8,0xE5,0xAF,0xBE,0xE7,0x9A,0x84,0xE3,0x81,0xAB]),  # page 18
    bytes([0xE9,0xAB,0x98,0xE3,0x81,0xBE,0xE3,0x81,0xA3,0xE3,0x81,0xA6,0xE3,0x81,0x84,0xE3,0x82,0x8B]),  # page 19
    bytes([0xE3,0x81,0xA8,0xE8,0x80,0x83,0xE3,0x81,0x88,0xE3,0x82,0x89,0xE3,0x82,0x8C,0xE3,0x81,0xBE]),  # page 20
    bytes([0xE3,0x81,0x99,0xE3,0x80,0x82,0xE4,0xBB,0x8A,0xE5,0xBE,0x8C,0xE3,0x81,0xAE,0xE6,0x94,0xBF]),  # page 21
    bytes([0xE5,0xBA,0x9C,0xE3,0x82,0x84,0xE8,0x87,0xAA,0xE6,0xB2,0xBB,0xE4,0xBD,0x93,0xE3,0x81,0xAA]),  # page 22
    bytes([0xE3,0x81,0xA9,0xE3,0x81,0x8B,0xE3,0x82,0x89,0xE3,0x81,0xAE,0xE5,0x91,0xBC,0xE3,0x81,0xB3]),  # page 23
    bytes([0xE3,0x81,0x8B,0xE3,0x81,0x91,0xE7,0xAD,0x89,0xE3,0x81,0xAB,0xE5,0xBF,0x9C,0xE3,0x81,0x98]),  # page 24
    bytes([0xE3,0x81,0x9F,0xE9,0x98,0xB2,0xE7,0x81,0xBD,0xE5,0xAF,0xBE,0xE5,0xBF,0x9C,0xE3,0x82,0x92]),  # page 25
    bytes([0xE3,0x81,0xA8,0xE3,0x81,0xA3,0xE3,0x81,0xA6,0xE3,0x81,0x8F,0xE3,0x81,0xA0,0xE3,0x81,0x95]),  # page 26
    bytes([0xE5,0x8D,0x97,0xE6,0xB5,0xB7,0xE3,0x83,0x88,0xE3,0x83,0xA9,0xE3,0x83,0x95,0xE5,0x9C,0xB0]),  # page 27
]


# ═══════════════════════════════════════════════════════════════════════════════
# CRC-24Q  (generator 0x1864CFB, GPS/QZSS standard)
# Bit ordering: MSB-first (matches C++ Decoder::crc24q)
# ═══════════════════════════════════════════════════════════════════════════════
CRC24Q_POLY = 0x1864CFB

def crc24q(data: bytes, bit_len: int) -> int:
    """CRC-24Q computation. data: byte array, bit_len: number of bits to process."""
    crc = 0
    num_bytes = (bit_len + 7) // 8
    for i in range(num_bytes):
        byte = data[i]
        bits_to_process = 8
        if i == num_bytes - 1 and (bit_len & 7):
            byte &= 0xFF << (8 - (bit_len & 7))
            bits_to_process = bit_len & 7
        crc ^= (byte << 16) & 0xFFFFFF
        for _ in range(bits_to_process):
            crc <<= 1
            if crc & 0x1000000:
                crc ^= CRC24Q_POLY
    return crc & 0xFFFFFF


def set_bits_msb(buf: bytearray, start: int, length: int, value: int):
    """Set 'length' bits at 'start' to 'value' (MSB-first bit ordering).
    Matches C++ setBits() from test_helpers.h."""
    if length == 0:
        return
    for i in range(length - 1, -1, -1):
        pos = start + (length - 1 - i)
        byte_idx = pos >> 3
        bit_idx = 7 - (pos & 7)
        if (value >> i) & 1:
            buf[byte_idx] |= (1 << bit_idx)
        else:
            buf[byte_idx] &= ~(1 << bit_idx)


def get_bits_msb(buf, start: int, length: int) -> int:
    """Read 'length' bits at 'start' (MSB-first bit ordering).
    Matches C++ Decoder::getBits()."""
    val = 0
    for i in range(length):
        pos = start + i
        byte_idx = pos >> 3
        bit_idx = 7 - (pos & 7)
        val = (val << 1) | ((buf[byte_idx] >> bit_idx) & 1)
    return val


def nmea_checksum(body: str) -> str:
    """NMEA XOR checksum."""
    cs = 0
    for ch in body:
        cs ^= ord(ch)
    return f"*{cs:02X}"


def make_qzqsm_nmea(svid: int, hex_payload: str) -> str:
    """Build $QZQSM NMEA sentence."""
    body = f"QZQSM,{svid},{hex_payload}"
    return f"${body}{nmea_checksum(body)}"


def generate_filler_nmea(template_nmea: str, page_num: int, text_bytes: bytes,
                          total_pages: int = 27, svid: int = 58) -> str:
    """Generate a valid NMEA string for a filler Nankai page.

    Takes an existing NMEA entry as a template, replaces the page number
    and text bytes using proper bit-level operations, then recomputes CRC-24Q.
    All field positions match Decoder::decodeNankai() and buildNankaiPage().
    """
    # Extract hex payload from template NMEA: $QZQSM,<svid>,<hex>*<cksum>
    parts = template_nmea.split(',')
    hex_part = parts[2].split('*')[0].upper()

    # Decode hex to 32 bytes (63-64 hex chars → up to 32 bytes)
    hex_len = len(hex_part)
    buf = bytearray(32)
    full_bytes = hex_len // 2
    if full_bytes > 32:
        full_bytes = 32
    for i in range(full_bytes):
        buf[i] = int(hex_part[i*2:i*2+2], 16)
    # Handle trailing nibble (63 hex chars → 31 bytes + 1 nibble)
    if hex_len & 1 and full_bytes < 32:
        buf[full_bytes] = int(hex_part[full_bytes*2], 16) << 4

    # Bit layout per Decoder::decodeNankai / buildNankaiPage:
    #   bits   0-7:   preamble (8b)
    #   bits   8-13:  msg_type (6b)
    #   bits  14-16:  report_classification (3b)
    #   bits  17-20:  disaster_category (4b)
    #   bits  21-24:  report_time month (4b)
    #   bits  25-29:  report_time day (5b)
    #   bits  30-34:  report_time hour (5b)
    #   bits  35-40:  report_time minute (6b)
    #   bits  41-42:  information_type (2b)
    #   bits  53-56:  info_code (4b)
    #   bits  57-200: text (18×8=144b) ← REPLACE
    #   bits 201-206: page_num (6b)     ← REPLACE
    #   bits 207-212: total_page (6b)   ← REPLACE
    #   bits 226-249: CRC-24Q (24b)     ← RECOMPUTE

    # Overwrite text (bits 57-200): 18 bytes, MSB-first per byte
    for j in range(18):
        byte_val = text_bytes[j] if j < len(text_bytes) else 0
        set_bits_msb(buf, 57 + j * 8, 8, byte_val)

    # Overwrite page_num (bits 201-206, 6 bits)
    set_bits_msb(buf, 201, 6, page_num)

    # Overwrite total_pages (bits 207-212, 6 bits)
    set_bits_msb(buf, 207, 6, total_pages)

    # Compute CRC-24Q on bits 0-225 (226 bits)
    crc = crc24q(bytes(buf), 226)

    # Store CRC at bits 226-249 (24 bits)
    set_bits_msb(buf, 226, 24, crc)

    # Re-encode to hex (63 chars for 250 bits: 31 full bytes + 1 nibble)
    hex_out = buf[:31].hex().upper() + hex(buf[31] >> 4)[2:].upper()

    return make_qzqsm_nmea(svid, hex_out)


def main():
    # 1. nankai_vectors.json から azarashi出力を読み込み
    with open(VECTORS, encoding='utf-8') as f:
        vectors = json.load(f)

    # ページ番号 → text_information のマップ
    azarashi_pages = {}
    template_nmea = None  # for filler generation
    for v in vectors:
        p = v['params']
        page_num = p['page_number']
        text_hex = p['text_information']
        azarashi_pages[page_num] = bytes.fromhex(text_hex)
        if template_nmea is None:
            template_nmea = p['nmea']

    print(f"azarashi nankai_vectors.json: {len(azarashi_pages)} pages found")
    print(f"  pages: {sorted(azarashi_pages.keys())}")
    print()

    # 2. テストのnankai_page_dataとazarashi出力をページごとに比較
    print("=== Page-by-page comparison: test nankai_page_data vs azarashi ===")
    mismatches = 0
    matches = 0
    missing_in_json = 0
    for i in range(27):
        page_num = i + 1
        test_data = NANKAI_PAGE_DATA[i]
        if page_num in azarashi_pages:
            aza_data = azarashi_pages[page_num]
            if test_data == aza_data:
                print(f"  page {page_num:2d}: MATCH   {test_data.hex()}")
                matches += 1
            else:
                print(f"  page {page_num:2d}: MISMATCH")
                print(f"    test:     {test_data.hex()}")
                print(f"    azarashi: {aza_data.hex()}")
                mismatches += 1
        else:
            print(f"  page {page_num:2d}: NOT IN JSON  test={test_data.hex()}")
            missing_in_json += 1

    print(f"\n  Summary: {matches} matches, {mismatches} mismatches, {missing_in_json} not in JSON")
    print()

    # 3. azarashi出力をページ順に連結した集約テキスト
    azarashi_aggregated = b''
    for p in range(1, 28):
        if p in azarashi_pages:
            azarashi_aggregated += azarashi_pages[p]

    # 4. テストのnankai_page_dataを連結した集約テキスト
    test_aggregated = b''.join(NANKAI_PAGE_DATA)

    print("=== Aggregated body comparison ===")
    print(f"  test_aggregated length:     {len(test_aggregated)} bytes")
    print(f"  azarashi_aggregated length: {len(azarashi_aggregated)} bytes (only {len(azarashi_pages)} pages)")
    print()

    # 5. azarashiが持っているページ分だけ比較
    # azarashiのページ順で、テストの対応ページと比較
    print("=== Comparing only pages present in azarashi JSON ===")
    partial_mismatches = 0
    partial_matches = 0
    for p in sorted(azarashi_pages.keys()):
        test_data = NANKAI_PAGE_DATA[p - 1]
        aza_data = azarashi_pages[p]
        if test_data == aza_data:
            partial_matches += 1
        else:
            partial_mismatches += 1
            print(f"  page {p}: MISMATCH")
            print(f"    test:     {test_data.hex()}")
            print(f"    azarashi: {aza_data.hex()}")

    print(f"  Partial summary: {partial_matches} matches, {partial_mismatches} mismatches")
    print()

    # 6. AzaraC decode_to_json で実際のNMEAをデコードし集約本文を検証
    #    decode_to_json は Parser を使用するよう改修済み（集約対応）。
    #    nankai_vectors.json には 20/27 ページしかないため、
    #    不足ページ（2-7, 27）の NMEA を合成して全27ページを入力する。
    if os.path.exists(AZARAC_BIN):
        print("=== AzaraC decode_to_json: aggregation verification ===")
        print(f"  nankai_vectors.json provides {len(vectors)} NMEA messages (pages {sorted(azarashi_pages.keys())})")
        print("  Generating filler NMEA for missing pages (2-7, 27)...")

        # Collect all 27 NMEA lines
        all_nmeas = []
        for page_num in range(1, 28):
            # Find existing NMEA for this page in vectors
            found = None
            for v in vectors:
                if v['params']['page_number'] == page_num:
                    found = v['params']['nmea']
                    break
            if found:
                all_nmeas.append(found)
            else:
                # Generate filler NMEA for missing page
                filler_text = NANKAI_PAGE_DATA[page_num - 1]
                filler_nmea = generate_filler_nmea(
                    template_nmea, page_num, filler_text)
                all_nmeas.append(filler_nmea)
                print(f"    generated filler for page {page_num}: text={filler_text.hex()}")

        print(f"  Total NMEA lines (including fillers): {len(all_nmeas)}")
        input_text = "\n".join(all_nmeas) + "\n"

        try:
            result = subprocess.run(
                [AZARAC_BIN],
                input=input_text,
                capture_output=True,
                text=True,
                timeout=30,
                encoding='utf-8',
                errors='replace'
            )
            if result.returncode == 0:
                azaC_results = json.loads(result.stdout)
                print(f"  AzaraC decoded {len(azaC_results)} message(s)")

                if len(azaC_results) == 0:
                    print("  WARNING: No aggregated output — check if all 27 pages reached the Parser.")
                    print("  (Aggregation requires all pages with matching event_time + info_code.)")
                else:
                    # Find the aggregated message (text_utf8 is in detail for aggregated Nankai)
                    aggregated_found = False
                    for i, r in enumerate(azaC_results):
                        detail = r.get('detail', {})
                        text_utf8 = detail.get('text_utf8', None)
                        if text_utf8 is not None:
                            aggregated_found = True
                            aggregated_bytes = text_utf8.encode('utf-8')
                            expected_bytes = test_aggregated
                            # Compare aggregated text with expected concatenation of all 27 pages
                            if aggregated_bytes == expected_bytes:
                                print(f"  msg {i}: AGGREGATED text_utf8 MATCH ({len(aggregated_bytes)} bytes)")
                            else:
                                print(f"  msg {i}: AGGREGATED text_utf8 MISMATCH")
                                print(f"    AzaraC aggregated length: {len(aggregated_bytes)}")
                                print(f"    Expected length:          {len(expected_bytes)}")
                                # Show hex diff
                                min_len = min(len(aggregated_bytes), len(expected_bytes))
                                first_diff = None
                                for j in range(min_len):
                                    if aggregated_bytes[j] != expected_bytes[j]:
                                        first_diff = j
                                        break
                                if first_diff is not None:
                                    print(f"    First diff at byte {first_diff}")
                                    print(f"      AzaraC:   {aggregated_bytes[max(0,first_diff-5):first_diff+20].hex()}")
                                    print(f"      Expected: {expected_bytes[max(0,first_diff-5):first_diff+20].hex()}")
                                elif len(aggregated_bytes) != len(expected_bytes):
                                    extra = aggregated_bytes[min_len:].hex() if len(aggregated_bytes) > min_len else expected_bytes[min_len:].hex()
                                    print(f"    Extra bytes: {extra}")
                            break

                    if not aggregated_found:
                        print("  No aggregated message (with text_utf8) in output.")
                        print("  All messages have text_hex only — aggregation did not complete.")
                        # Show per-message summary
                        for i, r in enumerate(azaC_results):
                            detail = r.get('detail', {})
                            page = detail.get('page', r.get('page', '?'))
                            total = detail.get('total_page', r.get('total_page', '?'))
                            has_hex = 'text_hex' in detail or 'text_hex' in r
                            has_utf8 = 'text_utf8' in detail or 'text_utf8' in r
                            print(f"    msg {i}: page={page}/{total} text_hex={'present' if has_hex else 'absent'} text_utf8={'present' if has_utf8 else 'absent'}")
            else:
                print(f"  AzaraC returned code {result.returncode}")
                if result.stderr:
                    print(f"  stderr: {result.stderr[:500]}")
        except json.JSONDecodeError as e:
            print(f"  JSON parse error: {e}")
            print(f"  Raw stdout (first 500 chars): {result.stdout[:500] if 'result' in dir() else 'N/A'}")
        except Exception as e:
            print(f"  ERROR: {e}")
    else:
        print(f"  AzaraC binary not found: {AZARAC_BIN}")
        print("  Build with: cd test && make decode")

    print()
    print("=== Conclusion ===")
    if mismatches == 0 and partial_mismatches == 0:
        print("  All pages present in both sources MATCH.")
    else:
        print(f"  {mismatches} full mismatches, {partial_mismatches} partial mismatches found.")
        print("  The test nankai_page_data does NOT fully match azarashi output.")
        print("  This means the test's expected_body may not reflect real-world data.")


if __name__ == '__main__':
    main()
