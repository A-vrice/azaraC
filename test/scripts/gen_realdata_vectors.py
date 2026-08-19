#!/usr/bin/env python3
"""gen_realdata_vectors.py — realdata/ から C++ テストベクタを生成する

生成先: test/integration/test_realdata.cpp

データソース:
  1. realdata/qzqsm_history.md  — 過去配信データ（$QZQSM文 + 期待値）
  2. realdata/qzqsm_20240101-0107_noto.csv — 能登半島地震 246件（hex + メタデータ）
  3. realdata/data.txt — DCX/DCR 生 hex 64行

decode_to_json CLI を用いて各NMEA文をデコードし、
主要フィールドの期待値をC++ テストコードに埋め込む。
"""

import re
import csv
import os
import sys
import json
import subprocess
import platform

BASE = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
REALDATA = os.path.join(BASE, 'realdata')
OUT_CPP = os.path.join(BASE, 'test', 'integration', 'test_realdata.cpp')
DECODE_BIN = os.path.join(BASE, 'test', 'decode_to_json.exe' if platform.system() == 'Windows' else 'decode_to_json')

# ── 災害カテゴリ名 → コード ──────────────────────────────────────────────
DC_MAP = {
    '緊急地震速報': 1,
    '震源': 2,
    '震度': 3,
    '南海トラフ地震': 4,
    '津波': 5,
    '北西太平洋津波': 6,
    '火山': 8,
    '降灰': 9,
    '気象': 10,
    '洪水': 11,
    '台風': 12,
    '海上': 14,
}

# ── 情報種別名 → コード ──────────────────────────────────────────────────
IT_MAP = {
    '発表': 0,
    '訂正': 1,
    '取消': 2,
}

# ── 報告分類名 → コード ──────────────────────────────────────────────────
RC_MAP = {
    '最優先': 1,
    '優先': 2,
    '通常': 3,
    '訓練/試験': 7,
}


def nmea_checksum(body: str) -> str:
    """NMEA チェックサム計算"""
    cs = 0
    for ch in body:
        cs ^= ord(ch)
    return f"*{cs:02X}"


def make_qzqsm(svid: int, hex_payload: str) -> str:
    """$QZQSM NMEA 文を構築（チェックサム付き）"""
    body = f"QZQSM,{svid},{hex_payload}"
    return f"${body}{nmea_checksum(body)}"


# ═══════════════════════════════════════════════════════════════════════════
# decode_to_json CLI 統合
# ═══════════════════════════════════════════════════════════════════════════

def decode_batch(nmea_list: list) -> list:
    """decode_to_json CLI を使って NMEA 文をデコード

    Returns:
        list of dicts: 各NMEA文のデコード結果 (JSONパース済み)
        デコード失敗時は None を返す
    """
    if not os.path.exists(DECODE_BIN):
        print(f"WARNING: decode_to_json not found at {DECODE_BIN}", file=sys.stderr)
        print("         Field-level checks will be skipped.", file=sys.stderr)
        return [None] * len(nmea_list)

    input_text = '\n'.join(nmea_list) + '\n'
    try:
        proc = subprocess.run(
            [DECODE_BIN],
            input=input_text,
            capture_output=True,
            text=True,
            encoding='utf-8',
            errors='replace',
            timeout=120,
        )
        if proc.returncode != 0:
            print(f"WARNING: decode_to_json failed (rc={proc.returncode}): {proc.stderr[:200]}", file=sys.stderr)
            return [None] * len(nmea_list)

        results = json.loads(proc.stdout)
        if len(results) != len(nmea_list):
            print(f"WARNING: decode_to_json returned {len(results)} results for {len(nmea_list)} inputs", file=sys.stderr)
            while len(results) < len(nmea_list):
                results.append(None)
        return results
    except subprocess.TimeoutExpired as e:
        print(f"WARNING: decode_to_json timeout: {e}", file=sys.stderr)
        return [None] * len(nmea_list)
    except json.JSONDecodeError as e:
        print(f"WARNING: decode_to_json JSON error: {e}", file=sys.stderr)
        return [None] * len(nmea_list)
    except Exception as e:
        print(f"WARNING: decode_to_json unexpected error: {e}", file=sys.stderr)
        return [None] * len(nmea_list)


# ═══════════════════════════════════════════════════════════════════════════
# 1. qzqsm_history.md のパース
# ═══════════════════════════════════════════════════════════════════════════

def parse_history(filepath: str) -> list:
    """qzqsm_history.md をパースしてテストベクタを抽出"""
    results = []
    current_dc_name = None
    current_dc_code = None

    with open(filepath, encoding='utf-8') as f:
        for line in f:
            line = line.strip()

            # dc= 行からカテゴリ名を取得
            m = re.match(r'^##\s+dc=(\d+)\s+(.+)', line)
            if m:
                dc_num = int(m.group(1))
                dc_name = m.group(2).strip()
                current_dc_name = dc_name
                current_dc_code = dc_num
                continue

            # $QZQSM 行を抽出
            m = re.match(r'^`(\$QZQSM,\d+,[0-9A-Fa-f]+\*[0-9A-Fa-f]{2})`', line)
            if m:
                nmea = m.group(1)
                if current_dc_code is not None:
                    results.append({
                        'nmea': nmea,
                        'expected_dc': current_dc_code,
                        'dc_name': current_dc_name,
                        'source': 'history',
                    })

    return results


# ═══════════════════════════════════════════════════════════════════════════
# 2. qzqsm_20240101-0107_noto.csv のパース
# ═══════════════════════════════════════════════════════════════════════════

def parse_noto_csv(filepath: str) -> list:
    """能登半島地震 CSV をパースしてテストベクタを抽出"""
    results = []

    with open(filepath, encoding='utf-8') as f:
        reader = csv.DictReader(f)
        for row in reader:
            hex_payload = row['message'].strip()
            dc_name = row['disaster_category'].strip()
            it_name = row['information_type'].strip()
            rc_name = row['report_classification'].strip()

            dc_code = DC_MAP.get(dc_name)
            it_code = IT_MAP.get(it_name)
            rc_code = RC_MAP.get(rc_name)

            if dc_code is None:
                print(f"WARNING: unknown disaster_category '{dc_name}'", file=sys.stderr)
                continue

            nmea = make_qzqsm(57, hex_payload)

            results.append({
                'nmea': nmea,
                'hex': hex_payload,
                'expected_dc': dc_code,
                'expected_it': it_code,
                'expected_rc': rc_code,
                'dc_name': dc_name,
                'it_name': it_name,
                'rc_name': rc_name,
                'source': 'noto',
            })

    return results


# ═══════════════════════════════════════════════════════════════════════════
# 3. data.txt のパース
# ═══════════════════════════════════════════════════════════════════════════

def parse_data_txt(filepath: str) -> list:
    """data.txt をパースしてテストベクタを抽出"""
    results = []

    with open(filepath, encoding='utf-8') as f:
        for i, line in enumerate(f, 1):
            hex_payload = line.strip()
            if not hex_payload:
                continue

            nmea = make_qzqsm(57, hex_payload)

            results.append({
                'nmea': nmea,
                'hex': hex_payload,
                'line': i,
                'source': 'data_txt',
            })

    return results


# ═══════════════════════════════════════════════════════════════════════════
# C++ フィールド値検証コード生成 (decode_to_json の結果から)
# ═══════════════════════════════════════════════════════════════════════════

def _collect_eew_fields(decoded: dict) -> dict:
    """EEW フィールドを収集"""
    d = decoded.get('detail', {}) if decoded else {}
    return {
        'depth': d.get('depth', 0),
        'magnitude': d.get('magnitude', 0),
        'epicenter': d.get('epicenter', 0),
        'intensity_lower': d.get('intensity_lower', 0),
        'intensity_upper': d.get('intensity_upper', 0),
        'long_period_lower': d.get('long_period_lower', 0),
        'long_period_upper': d.get('long_period_upper', 0),
    }


def _collect_hypo_fields(decoded: dict) -> dict:
    """Hypocenter フィールドを収集"""
    d = decoded.get('detail', {}) if decoded else {}
    return {
        'depth': d.get('depth', 0),
        'magnitude': d.get('magnitude', 0),
        'epicenter': d.get('epicenter', 0),
    }


def _collect_seismic_fields(decoded: dict) -> dict:
    """Seismic フィールドを収集"""
    d = decoded.get('detail', {}) if decoded else {}
    entries = d.get('entries', [])
    return {
        'count': len(entries),
        'entries': [{'intensity_code': e.get('intensity', 0),
                      'prefecture_code': e.get('prefecture', 0)}
                     for e in entries[:1]],
    }


def _collect_tsunami_fields(decoded: dict) -> dict:
    """Tsunami フィールドを収集"""
    d = decoded.get('detail', {}) if decoded else {}
    entries = d.get('entries', [])
    return {
        'warning_code': d.get('warning_code', 0),
        'count': len(entries),
        'entries': [{'region_code': e.get('region', 0),
                      'height_code': e.get('height', 0)}
                     for e in entries[:5]],
    }


def _collect_nwpac_fields(decoded: dict) -> dict:
    """NW Pacific Tsunami フィールドを収集"""
    d = decoded.get('detail', {}) if decoded else {}
    return {
        'potential': d.get('potential', 0),
        'count': len(d.get('entries', [])),
    }


def _collect_volcano_fields(decoded: dict) -> dict:
    """Volcano フィールドを収集"""
    d = decoded.get('detail', {}) if decoded else {}
    return {
        'volcano_name': d.get('volcano_name', 0),
        'warning_code': d.get('warning_code', 0),
    }


def _collect_ashfall_fields(decoded: dict) -> dict:
    """Ash Fall フィールドを収集"""
    d = decoded.get('detail', {}) if decoded else {}
    return {
        'volcano_name': d.get('volcano_name', 0),
        'warning_type': d.get('warning_type', 0),
    }


def _collect_weather_fields(decoded: dict) -> dict:
    """Weather フィールドを収集"""
    d = decoded.get('detail', {}) if decoded else {}
    return {
        'warning_state': d.get('warning_state', 0),
        'count': len(d.get('entries', [])),
    }


def _collect_flood_fields(decoded: dict) -> dict:
    """Flood フィールドを収集"""
    d = decoded.get('detail', {}) if decoded else {}
    return {
        'count': len(d.get('entries', [])),
    }


def _collect_typhoon_fields(decoded: dict) -> dict:
    """Typhoon フィールドを収集"""
    d = decoded.get('detail', {}) if decoded else {}
    return {
        'pressure': d.get('pressure', 0),
        'max_wind': d.get('max_wind', 0),
        'max_gust': d.get('max_gust', 0),
    }


def _collect_marine_fields(decoded: dict) -> dict:
    """Marine フィールドを収集"""
    d = decoded.get('detail', {}) if decoded else {}
    entries = d.get('entries', [])
    return {
        'count': len(entries),
        'entries': [{'warning_code': e.get('warning_code', 0),
                      'region_code': e.get('region', 0)}
                     for e in entries[:1]],
    }


# dc → (type_name, getter, collector)
DC_INFO = {
    1:  ('EewData', 'getEew', 'eew', _collect_eew_fields),
    2:  ('HypocenterData', 'getHypocenter', 'hypo', _collect_hypo_fields),
    3:  ('SeismicData', 'getSeismic', 'seis', _collect_seismic_fields),
    5:  ('TsunamiData', 'getTsunami', 'tsunami', _collect_tsunami_fields),
    6:  ('NwPacTsunamiData', 'getNwPac', 'nw_pac', _collect_nwpac_fields),
    8:  ('VolcanoData', 'getVolcano', 'vol', _collect_volcano_fields),
    9:  ('AshFallData', 'getAshFall', 'ash', _collect_ashfall_fields),
    10: ('WeatherData', 'getWeather', 'weather', _collect_weather_fields),
    11: ('FloodData', 'getFlood', 'flood', _collect_flood_fields),
    12: ('TyphoonData', 'getTyphoon', 'typh', _collect_typhoon_fields),
    14: ('MarineData', 'getMarine', 'marine', _collect_marine_fields),
}


# ═══════════════════════════════════════════════════════════════════════════
# C++ テストファイル生成
# ═══════════════════════════════════════════════════════════════════════════

def generate_cpp(history: list, noto: list, data_txt: list,
                 history_decoded: list, noto_decoded: list,
                 data_txt_decoded: list) -> str:
    lines = []
    w = lines.append

    w('// test/integration/test_realdata.cpp')
    w('// AUTO-GENERATED by test/scripts/gen_realdata_vectors.py — DO NOT EDIT')
    w('// realdata/ の実際のデータを用いたデコード正確性検証')
    w('')
    w('#include "../test_helpers.h"')
    w('#include "doctest.h"')
    w('#include <cstring>')
    w('#include <string>')
    w('')
    w('using namespace azaraC;')
    w('')

    # ── History テスト ────────────────────────────────────────────────────
    # 構造体定義と期待値配列をファイルスコープに配置（スタックオーバーフロー対策）

    # デコード結果から各dc typeごとの期待値配列を収集
    # 1件でも decode 失敗した dc タイプは field-level check 全体を無効化し、
    # *_expected[] 配列サイズと switch-case ヒット数の不一致による範囲外参照を防止する
    dc_failed = set()       # decodeが1件でも失敗したdc
    for i, h in enumerate(history):
        dc = h['expected_dc']
        if DC_INFO.get(dc) is None:
            continue
        decoded = history_decoded[i] if i < len(history_decoded) else None
        if decoded is None:
            dc_failed.add(dc)

    dc_entries = {}  # dc_code -> list of (entry_index, collected_fields)
    for i, h in enumerate(history):
        dc = h['expected_dc']
        decoded = history_decoded[i] if i < len(history_decoded) else None
        info = DC_INFO.get(dc)
        if info is None or decoded is None:
            continue
        if dc in dc_failed:
            continue
        _, _, _, collector = info
        fields = collector(decoded)
        if dc not in dc_entries:
            dc_entries[dc] = []
        dc_entries[dc].append((i, fields))

    # ファイルスコープの構造体定義と期待値配列を生成
    w('// ═══════════════════════════════════════════════════════════════════════════════')
    w(f'// qzqsm_history.md: {len(history)} 件の過去配信データ')
    w('// デコード成功 + disaster_category 一致 + フィールド値検証')
    w('// ═══════════════════════════════════════════════════════════════════════════════')
    w('')

    # History Case struct and data at file scope
    w('namespace {')
    w('    struct HistoryCase {')
    w('        const char* nmea;')
    w('        uint8_t expected_dc;')
    w('        const char* label;')
    w('    };')
    w('')
    w('    static const HistoryCase history_cases[] = {')

    for h in history:
        nmea_escaped = h['nmea'].replace('"', '\\"')
        label = f"dc={h['expected_dc']} {h['dc_name']}"
        w(f'        {{"{nmea_escaped}", {h["expected_dc"]}, "{label}"}},')

    w('    };')
    w('')

    # 各dc typeの期待値構造体と配列をファイルスコープに生成
    for dc, entries in sorted(dc_entries.items()):
        info = DC_INFO[dc]
        type_name, getter, varname, _ = info
        dc_name_label = history[entries[0][0]]['dc_name'] if entries else f'dc={dc}'

        if dc == 1:  # EEW
            w(f'    // dc={dc} {dc_name_label}: {len(entries)} entries')
            w('    struct EewExpected { uint16_t depth; uint8_t magnitude; uint16_t epicenter; uint8_t intensity_lower; uint8_t intensity_upper; uint8_t long_period_lower; uint8_t long_period_upper; };')
            w('    static const EewExpected eew_expected[] = {')
            for _, f in entries:
                w(f'        {{{f["depth"]}, {f["magnitude"]}, {f["epicenter"]}, {f["intensity_lower"]}, {f["intensity_upper"]}, {f["long_period_lower"]}, {f["long_period_upper"]}}},')
            w('    };')
            w('')

        elif dc == 2:  # Hypocenter
            w(f'    // dc={dc} {dc_name_label}: {len(entries)} entries')
            w('    struct HypoExpected { uint16_t depth; uint8_t magnitude; uint16_t epicenter; };')
            w('    static const HypoExpected hypo_expected[] = {')
            for _, f in entries:
                w(f'        {{{f["depth"]}, {f["magnitude"]}, {f["epicenter"]}}},')
            w('    };')
            w('')

        elif dc == 3:  # Seismic
            w(f'    // dc={dc} {dc_name_label}: {len(entries)} entries')
            w('    struct SeismicExpected { uint8_t count; };')
            w('    static const SeismicExpected seismic_expected[] = {')
            for _, f in entries:
                w(f'        {{{f["count"]}}},')
            w('    };')
            w('')

        elif dc == 5:  # Tsunami
            w(f'    // dc={dc} {dc_name_label}: {len(entries)} entries')
            w('    struct TsunamiExpected { uint8_t warning_code; uint8_t count; };')
            w('    static const TsunamiExpected tsunami_expected[] = {')
            for _, f in entries:
                w(f'        {{{f["warning_code"]}, {f["count"]}}},')
            w('    };')
            w('')

        elif dc == 6:  # NW Pacific
            w(f'    // dc={dc} {dc_name_label}: {len(entries)} entries')
            w('    struct NwPacExpected { uint8_t potential; uint8_t count; };')
            w('    static const NwPacExpected nwpac_expected[] = {')
            for _, f in entries:
                w(f'        {{{f["potential"]}, {f["count"]}}},')
            w('    };')
            w('')

        elif dc == 8:  # Volcano
            w(f'    // dc={dc} {dc_name_label}: {len(entries)} entries')
            w('    struct VolcanoExpected { uint16_t volcano_name; uint8_t warning_code; };')
            w('    static const VolcanoExpected volcano_expected[] = {')
            for _, f in entries:
                w(f'        {{{f["volcano_name"]}, {f["warning_code"]}}},')
            w('    };')
            w('')

        elif dc == 9:  # Ash Fall
            w(f'    // dc={dc} {dc_name_label}: {len(entries)} entries')
            w('    struct AshFallExpected { uint16_t volcano_name; uint8_t warning_type; };')
            w('    static const AshFallExpected ashfall_expected[] = {')
            for _, f in entries:
                w(f'        {{{f["volcano_name"]}, {f["warning_type"]}}},')
            w('    };')
            w('')

        elif dc == 10:  # Weather
            w(f'    // dc={dc} {dc_name_label}: {len(entries)} entries')
            w('    struct WeatherExpected { uint8_t warning_state; uint8_t count; };')
            w('    static const WeatherExpected weather_expected[] = {')
            for _, f in entries:
                w(f'        {{{f["warning_state"]}, {f["count"]}}},')
            w('    };')
            w('')

        elif dc == 11:  # Flood
            w(f'    // dc={dc} {dc_name_label}: {len(entries)} entries')
            w('    struct FloodExpected { uint8_t count; };')
            w('    static const FloodExpected flood_expected[] = {')
            for _, f in entries:
                w(f'        {{{f["count"]}}},')
            w('    };')
            w('')

        elif dc == 12:  # Typhoon
            w(f'    // dc={dc} {dc_name_label}: {len(entries)} entries')
            w('    struct TyphoonExpected { uint16_t pressure; uint8_t max_wind; uint8_t max_gust; };')
            w('    static const TyphoonExpected typhoon_expected[] = {')
            for _, f in entries:
                w(f'        {{{f["pressure"]}, {f["max_wind"]}, {f["max_gust"]}}},')
            w('    };')
            w('')

        elif dc == 14:  # Marine
            w(f'    // dc={dc} {dc_name_label}: {len(entries)} entries')
            w('    struct MarineExpected { uint8_t count; };')
            w('    static const MarineExpected marine_expected[] = {')
            for _, f in entries:
                w(f'        {{{f["count"]}}},')
            w('    };')
            w('')

    w('} // anonymous namespace')
    w('')

    # TEST_CASE 関数（スタック使用量を最小化）
    w('TEST_CASE("Realdata: History - decode and disaster_category") {')

    # インデックスカウンタ
    idx_vars = []
    for dc in sorted(dc_entries.keys()):
        info = DC_INFO[dc]
        _, _, varname, _ = info
        idx_vars.append(f'{varname}_idx')
    if idx_vars:
        w(f'    size_t {" = 0, ".join(idx_vars)} = 0;')
    w('')

    # メインループ
    w(f'    constexpr size_t N = {len(history)};')
    w('    for (size_t i = 0; i < N; ++i) {')
    w('        Message msg{};')
    w('        CAPTURE(i);')
    w('        CAPTURE(history_cases[i].label);')
    w('        CAPTURE(history_cases[i].nmea);')
    w('        REQUIRE(decodeNmea(history_cases[i].nmea, msg));')
    w('        CHECK(msg.msg_type == 43);')
    w('        CHECK(msg.payload_type == MsgPayloadType::Mt43);')
    w('        const Mt43Data* mt43 = msg.getMt43();')
    w('        REQUIRE(mt43 != nullptr);')
    w('        CHECK(mt43->disaster_category == history_cases[i].expected_dc);')
    w('')
    w('        // Field-level verification based on disaster category')
    w('        // (expected values from AzaraC decode_to_json)')
    w('        switch (history_cases[i].expected_dc) {')

    for dc, entries in sorted(dc_entries.items()):
        info = DC_INFO[dc]
        type_name, getter, varname, _ = info
        dc_name_label = entries[0][0]
        idx_var = f'{varname}_idx'

        if dc == 1:  # EEW
            w(f'            case {dc}: {{')
            w(f'                const {type_name}* {varname} = mt43->{getter}();')
            w(f'                REQUIRE({varname} != nullptr);')
            w(f'                CHECK({varname}->depth == eew_expected[{idx_var}].depth);')
            w(f'                CHECK({varname}->magnitude == eew_expected[{idx_var}].magnitude);')
            w(f'                CHECK({varname}->epicenter == eew_expected[{idx_var}].epicenter);')
            w(f'                CHECK({varname}->intensity_lower == eew_expected[{idx_var}].intensity_lower);')
            w(f'                CHECK({varname}->intensity_upper == eew_expected[{idx_var}].intensity_upper);')
            w(f'                CHECK({varname}->long_period_lower == eew_expected[{idx_var}].long_period_lower);')
            w(f'                CHECK({varname}->long_period_upper == eew_expected[{idx_var}].long_period_upper);')
            w(f'                {idx_var}++;')
            w('                break;')
            w('            }')

        elif dc == 2:  # Hypocenter
            w(f'            case {dc}: {{')
            w(f'                const {type_name}* {varname} = mt43->{getter}();')
            w(f'                REQUIRE({varname} != nullptr);')
            w(f'                CHECK({varname}->depth == hypo_expected[{idx_var}].depth);')
            w(f'                CHECK({varname}->magnitude == hypo_expected[{idx_var}].magnitude);')
            w(f'                CHECK({varname}->epicenter == hypo_expected[{idx_var}].epicenter);')
            w(f'                {idx_var}++;')
            w('                break;')
            w('            }')

        elif dc == 3:  # Seismic
            w(f'            case {dc}: {{')
            w(f'                const {type_name}* {varname} = mt43->{getter}();')
            w(f'                REQUIRE({varname} != nullptr);')
            w(f'                CHECK({varname}->count == seismic_expected[{idx_var}].count);')
            w(f'                {idx_var}++;')
            w('                break;')
            w('            }')

        elif dc == 5:  # Tsunami
            w(f'            case {dc}: {{')
            w(f'                const {type_name}* {varname} = mt43->{getter}();')
            w(f'                REQUIRE({varname} != nullptr);')
            w(f'                CHECK({varname}->warning_code == tsunami_expected[{idx_var}].warning_code);')
            w(f'                CHECK({varname}->count == tsunami_expected[{idx_var}].count);')
            w(f'                {idx_var}++;')
            w('                break;')
            w('            }')

        elif dc == 6:  # NW Pacific
            w(f'            case {dc}: {{')
            w(f'                const {type_name}* {varname} = mt43->{getter}();')
            w(f'                REQUIRE({varname} != nullptr);')
            w(f'                CHECK({varname}->potential == nwpac_expected[{idx_var}].potential);')
            w(f'                CHECK({varname}->count == nwpac_expected[{idx_var}].count);')
            w(f'                {idx_var}++;')
            w('                break;')
            w('            }')

        elif dc == 8:  # Volcano
            w(f'            case {dc}: {{')
            w(f'                const {type_name}* {varname} = mt43->{getter}();')
            w(f'                REQUIRE({varname} != nullptr);')
            w(f'                CHECK({varname}->volcano_name == volcano_expected[{idx_var}].volcano_name);')
            w(f'                CHECK({varname}->warning_code == volcano_expected[{idx_var}].warning_code);')
            w(f'                {idx_var}++;')
            w('                break;')
            w('            }')

        elif dc == 9:  # Ash Fall
            w(f'            case {dc}: {{')
            w(f'                const {type_name}* {varname} = mt43->{getter}();')
            w(f'                REQUIRE({varname} != nullptr);')
            w(f'                CHECK({varname}->volcano_name == ashfall_expected[{idx_var}].volcano_name);')
            w(f'                CHECK({varname}->warning_type == ashfall_expected[{idx_var}].warning_type);')
            w(f'                {idx_var}++;')
            w('                break;')
            w('            }')

        elif dc == 10:  # Weather
            w(f'            case {dc}: {{')
            w(f'                const {type_name}* {varname} = mt43->{getter}();')
            w(f'                REQUIRE({varname} != nullptr);')
            w(f'                CHECK({varname}->warning_state == weather_expected[{idx_var}].warning_state);')
            w(f'                CHECK({varname}->count == weather_expected[{idx_var}].count);')
            w(f'                {idx_var}++;')
            w('                break;')
            w('            }')

        elif dc == 11:  # Flood
            w(f'            case {dc}: {{')
            w(f'                const {type_name}* {varname} = mt43->{getter}();')
            w(f'                REQUIRE({varname} != nullptr);')
            w(f'                CHECK({varname}->count == flood_expected[{idx_var}].count);')
            w(f'                {idx_var}++;')
            w('                break;')
            w('            }')

        elif dc == 12:  # Typhoon
            w(f'            case {dc}: {{')
            w(f'                const {type_name}* {varname} = mt43->{getter}();')
            w(f'                REQUIRE({varname} != nullptr);')
            w(f'                CHECK({varname}->pressure == typhoon_expected[{idx_var}].pressure);')
            w(f'                CHECK({varname}->max_wind == typhoon_expected[{idx_var}].max_wind);')
            w(f'                CHECK({varname}->max_gust == typhoon_expected[{idx_var}].max_gust);')
            w(f'                {idx_var}++;')
            w('                break;')
            w('            }')

        elif dc == 14:  # Marine
            w(f'            case {dc}: {{')
            w(f'                const {type_name}* {varname} = mt43->{getter}();')
            w(f'                REQUIRE({varname} != nullptr);')
            w(f'                CHECK({varname}->count == marine_expected[{idx_var}].count);')
            w(f'                {idx_var}++;')
            w('                break;')
            w('            }')

    w('            default: break;')
    w('        }')
    w('    }')
    w('}')
    w('')

    # ── Noto CSV テスト ───────────────────────────────────────────────────
    w('// ═══════════════════════════════════════════════════════════════════════════════')
    w(f'// qzqsm_20240101-0107_noto.csv: {len(noto)} 件（能登半島地震）')
    w('// デコード成功 + disaster_category / information_type / report_classification 検証')
    w('// ═══════════════════════════════════════════════════════════════════════════════')
    w('')
    w('namespace {')
    w('    struct NotoCase {')
    w('        const char* nmea;')
    w('        uint8_t expected_dc;')
    w('        uint8_t expected_it;')
    w('        uint8_t expected_rc;')
    w('        const char* label;')
    w('    };')
    w('')
    w('    static const NotoCase noto_cases[] = {')

    for n in noto:
        nmea_escaped = n['nmea'].replace('"', '\\"')
        label = f"{n['dc_name']} {n['it_name']} {n['rc_name']}"
        w(f'        {{"{nmea_escaped}", {n["expected_dc"]}, {n["expected_it"]}, {n["expected_rc"]}, "{label}"}},')

    w('    };')
    w('} // anonymous namespace')
    w('')
    w('TEST_CASE("Realdata: Noto 2024 - decode and metadata") {')
    w(f'    constexpr size_t N = {len(noto)};')
    w('    for (size_t i = 0; i < N; ++i) {')
    w('        Message msg{};')
    w('        CAPTURE(i);')
    w('        CAPTURE(noto_cases[i].label);')
    w('        CAPTURE(noto_cases[i].nmea);')
    w('        REQUIRE(decodeNmea(noto_cases[i].nmea, msg));')
    w('        CHECK(msg.msg_type == 43);')
    w('        CHECK(msg.payload_type == MsgPayloadType::Mt43);')
    w('        const Mt43Data* mt43 = msg.getMt43();')
    w('        REQUIRE(mt43 != nullptr);')
    w('        CHECK(mt43->disaster_category == noto_cases[i].expected_dc);')
    w('        CHECK(mt43->information_type == noto_cases[i].expected_it);')
    w('        CHECK(mt43->report_classification == noto_cases[i].expected_rc);')
    w('    }')
    w('}')
    w('')

    # ── data.txt テスト ───────────────────────────────────────────────────
    w('// ═══════════════════════════════════════════════════════════════════════════════')
    w(f'// data.txt: {len(data_txt)} 件の DCX/DCR 混在生データ')
    w('// デコード成功 + msg_type + disaster_category/service_kind 検証')
    w('// (expected values from AzaraC decode_to_json)')
    w('// ═══════════════════════════════════════════════════════════════════════════════')
    w('')
    w('namespace {')
    w('    struct DataTxtCase {')
    w('        const char* nmea;')
    w('        int line;')
    w('        uint8_t expected_msg_type;')
    w('    };')
    w('')
    w('    static const DataTxtCase data_txt_cases[] = {')

    for i, d in enumerate(data_txt):
        nmea_escaped = d['nmea'].replace('"', '\\"')
        decoded = data_txt_decoded[i] if i < len(data_txt_decoded) else None
        if decoded is None or 'msg_type' not in decoded:
            raise RuntimeError(f"decode_to_json missing msg_type for data.txt line {d['line']}")
        expected_mt = decoded['msg_type']
        if expected_mt not in (43, 44):
            raise RuntimeError(f"unexpected msg_type {expected_mt} for data.txt line {d['line']}")
        w(f'        {{"{nmea_escaped}", {d["line"]}, {expected_mt}}},')

    w('    };')
    w('} // anonymous namespace')
    w('')
    w('TEST_CASE("Realdata: data.txt - decode success and valid msg_type") {')
    w(f'    constexpr size_t N = {len(data_txt)};')
    w('    for (size_t i = 0; i < N; ++i) {')
    w('        Message msg{};')
    w('        CAPTURE(i);')
    w('        CAPTURE(data_txt_cases[i].line);')
    w('        CAPTURE(data_txt_cases[i].nmea);')
    w('        REQUIRE(decodeNmea(data_txt_cases[i].nmea, msg));')
    w('        CHECK(msg.valid);')
    w('        CHECK(msg.msg_type == data_txt_cases[i].expected_msg_type);')
    w('        CHECK((msg.payload_type == MsgPayloadType::Mt43 || msg.payload_type == MsgPayloadType::Mt44));')
    w('        // Verify payload_type matches msg_type')
    w('        if (msg.msg_type == 43) {')
    w('            CHECK(msg.payload_type == MsgPayloadType::Mt43);')
    w('        } else if (msg.msg_type == 44) {')
    w('            CHECK(msg.payload_type == MsgPayloadType::Mt44);')
    w('        }')
    w('    }')
    w('}')
    w('')

    return '\n'.join(lines)


def main():
    print(f"Base dir: {BASE}")
    print(f"Realdata dir: {REALDATA}")

    # パース
    history = parse_history(os.path.join(REALDATA, 'qzqsm_history.md'))
    print(f"History: {len(history)} entries")

    noto = parse_noto_csv(os.path.join(REALDATA, 'qzqsm_20240101-0107_noto.csv'))
    print(f"Noto CSV: {len(noto)} entries")

    data_txt = parse_data_txt(os.path.join(REALDATA, 'data.txt'))
    print(f"data.txt: {len(data_txt)} entries")

    # decode_to_json で期待値を取得
    print("\nDecoding history entries...")
    history_nmeas = [h['nmea'] for h in history]
    history_decoded = decode_batch(history_nmeas)
    for i, (h, d) in enumerate(zip(history, history_decoded)):
        dc = h['expected_dc']
        if d:
            print(f"  [{i}] dc={dc} {h['dc_name']}: decoded OK")
        else:
            print(f"  [{i}] dc={dc} {h['dc_name']}: decode FAILED")

    print("\nDecoding data.txt entries...")
    data_txt_nmeas = [d['nmea'] for d in data_txt]
    data_txt_decoded = decode_batch(data_txt_nmeas)
    mt_counts = {}
    for i, (d, dec) in enumerate(zip(data_txt, data_txt_decoded)):
        if dec:
            mt = dec.get('msg_type', '?')
            mt_counts[mt] = mt_counts.get(mt, 0) + 1
            if i < 5 or i >= len(data_txt) - 2:
                print(f"  [{i}] line={d['line']}: MT={mt}")
        else:
            print(f"  [{i}] line={d['line']}: decode FAILED")
    print(f"  MT distribution: {mt_counts}")

    # Noto CSV は大量なのでデコードをスキップ（メタデータのみで十分）
    noto_decoded = [None] * len(noto)

    # C++ 生成
    cpp = generate_cpp(history, noto, data_txt,
                       history_decoded, noto_decoded, data_txt_decoded)

    os.makedirs(os.path.dirname(OUT_CPP), exist_ok=True)
    with open(OUT_CPP, 'w', encoding='utf-8') as f:
        f.write(cpp)
    print(f"\nGenerated: {OUT_CPP} ({len(cpp)} bytes)")


if __name__ == '__main__':
    main()
