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

import csv
import json
import os
import re
import subprocess
import sys

from _common import (  # type: ignore[import-not-found]
    BASE,
    DC_MAP,
    DECODE_BIN,
    IT_MAP,
    RC_MAP,
    REALDATA,
    make_qzqsm,
)

OUT_CPP = os.path.join(BASE, 'test', 'integration', 'test_realdata.cpp')

# カテゴリ無効ビルド（make macro）では該当 dc の電文が DisabledAtCompileTime になりデコードできない。生成物側にも #if ガードを出さないと、手で足したガードが再生成で消える。
DISABLED_DC_MACROS = [
    (1, 'AZARAC_ENABLE_EEW'),
    (2, 'AZARAC_ENABLE_HYPOCENTER'),
    (3, 'AZARAC_ENABLE_SEISMIC'),
    (4, 'AZARAC_ENABLE_NANKAI'),
    (5, 'AZARAC_ENABLE_TSUNAMI'),
    (6, 'AZARAC_ENABLE_NW_PAC_TSUNAMI'),
    (8, 'AZARAC_ENABLE_VOLCANO'),
    (9, 'AZARAC_ENABLE_ASH_FALL'),
    (10, 'AZARAC_ENABLE_WEATHER'),
    (11, 'AZARAC_ENABLE_FLOOD'),
    (12, 'AZARAC_ENABLE_TYPHOON'),
    (14, 'AZARAC_ENABLE_MARINE'),
]

# decode_to_json CLI 統合

def _entry0(fields: dict, nmea: str) -> dict:
    """entry[0] を返す。entry が無いフィクスチャは生成を失敗させる
    （entries[0] を assert する側が範囲外を読む前に気付けるようにする）。"""
    entries = fields.get('entries') or []
    if not entries:
        raise SystemExit(f"collector returned no entries for {nmea}")
    return entries[0]


def _emit_disabled_guard(w, cases_var: str) -> None:
    """カテゴリ無効ビルドで該当 dc を skip するガードを生成する。

    make macro は各 AZARAC_ENABLE_* を個別に 0 にして run する。無効カテゴリの
    電文は Decoder が DisabledAtCompileTime で拒否するため、ガードが無いと
    フルスイート以外（make macro）が落ちる。
    """
    w('        // Skip disabled-category cases (preprocessor-guarded, eliminated at compile time when enabled)')
    w(f'        {{ uint8_t _dc = {cases_var}[i].expected_dc;')
    for dc, macro in DISABLED_DC_MACROS:
        w('#if !' + macro)
        w(f'          if (_dc == {dc}) continue;')
        w('#endif')
    w('        (void)_dc;')
    w('        }')


def decode_batch(nmea_list: list, raw: bool = False) -> list:
    """decode_to_json CLI を使って NMEA 文をデコード

    Args:
        raw: True で --raw（dedup 無効）。data.txt は同一情報の重複を含むため、
             既定の Parser 経路だと出力件数が入力件数より減り、インデックスが
             ずれる（重複除去は「同じ情報を 2 度通知しない」機能なので当然）。

    Returns:
        list of dicts: 各NMEA文のデコード結果 (JSONパース済み)

    失敗時は SystemExit で落とす。None を返してフィールド検査を黙って削ると、
    デコードが壊れても生成物が「検査の少ない緑」になる。
    """
    if not os.path.exists(DECODE_BIN):
        raise SystemExit(f"decode_to_json not found: run `make -C test decode` first ({DECODE_BIN})")

    input_text = '\n'.join(nmea_list) + '\n'
    cmd = [DECODE_BIN] + (['--raw'] if raw else [])
    try:
        proc = subprocess.run(
            cmd,
            input=input_text,
            capture_output=True,
            text=True,
            encoding='utf-8',
            errors='replace',
            timeout=120,
            check=False,
        )
    except subprocess.TimeoutExpired as e:
        raise SystemExit(f"decode_to_json timeout: {e}")
    if proc.returncode != 0:
        raise SystemExit(f"decode_to_json failed (rc={proc.returncode}): {proc.stderr[:500]}")
    try:
        results = json.loads(proc.stdout)
    except json.JSONDecodeError as e:
        raise SystemExit(f"decode_to_json returned invalid JSON: {e}")
    if len(results) != len(nmea_list):
        raise SystemExit(
            f"decode_to_json returned {len(results)} results for {len(nmea_list)} inputs")

    for nmea, r in zip(nmea_list, results):
        if r is None:
            raise SystemExit(f"decode failed for: {nmea}")
    return results


# 1. qzqsm_history.md のパース

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


# 2. qzqsm_20240101-0107_noto.csv のパース

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


# 3. data.txt のパース

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


# C++ フィールド値検証コード生成 (decode_to_json の結果から)

def _collect_eew_fields(decoded: dict) -> dict:
    """EEW フィールドを収集"""
    d = decoded.get('data', {}) if decoded else {}
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
    d = decoded.get('data', {}) if decoded else {}
    return {
        'depth': d.get('depth', 0),
        'magnitude': d.get('magnitude', 0),
        'epicenter': d.get('epicenter', 0),
    }


def _collect_seismic_fields(decoded: dict) -> dict:
    """Seismic フィールドを収集"""
    d = decoded.get('data', {}) if decoded else {}
    entries = d.get('entries', [])
    return {
        'count': len(entries),
        'entries': [{'intensity_code': e.get('intensity', 0),
                      'prefecture_code': e.get('prefecture', 0)}
                     for e in entries[:1]],
    }


def _collect_tsunami_fields(decoded: dict) -> dict:
    """Tsunami フィールドを収集"""
    d = decoded.get('data', {}) if decoded else {}
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
    d = decoded.get('data', {}) if decoded else {}
    return {
        'potential': d.get('potential', 0),
        'count': len(d.get('entries', [])),
    }


def _collect_volcano_fields(decoded: dict) -> dict:
    """Volcano フィールドを収集"""
    d = decoded.get('data', {}) if decoded else {}
    return {
        'volcano_name': d.get('volcano_name', 0),
        'warning_code': d.get('warning_code', 0),
    }


def _collect_ashfall_fields(decoded: dict) -> dict:
    """Ash Fall フィールドを収集"""
    d = decoded.get('data', {}) if decoded else {}
    return {
        'volcano_name': d.get('volcano_name', 0),
        'warning_type': d.get('warning_type', 0),
    }


def _collect_weather_fields(decoded: dict) -> dict:
    """Weather フィールドを収集"""
    d = decoded.get('data', {}) if decoded else {}
    entries = d.get('entries', [])
    return {
        'warning_state': d.get('warning_state', 0),
        'count': len(entries),
        'entries': [{'sub_category': e.get('sub_category', 0),
                      'region_code': e.get('region', 0)}
                     for e in entries[:1]],
    }


def _collect_flood_fields(decoded: dict) -> dict:
    """Flood フィールドを収集"""
    d = decoded.get('data', {}) if decoded else {}
    return {
        'count': len(d.get('entries', [])),
    }


def _collect_typhoon_fields(decoded: dict) -> dict:
    """Typhoon フィールドを収集"""
    d = decoded.get('data', {}) if decoded else {}
    return {
        'pressure': d.get('pressure', 0),
        'max_wind': d.get('max_wind', 0),
        'max_gust': d.get('max_gust', 0),
    }


def _collect_marine_fields(decoded: dict) -> dict:
    """Marine フィールドを収集"""
    d = decoded.get('data', {}) if decoded else {}
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


# C++ テストファイル生成

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

    # History テスト
    # 構造体定義と期待値配列をファイルスコープに配置（スタックオーバーフロー対策）

    # デコード結果から各dc typeごとの期待値配列を収集
    dc_entries = {}  # dc_code -> list of (history_index, collected_fields)
    for i, h in enumerate(history):
        dc = h['expected_dc']
        decoded = history_decoded[i]
        info = DC_INFO.get(dc)
        if info is None:
            continue
        _, _, _, collector = info
        fields = collector(decoded)
        if dc not in dc_entries:
            dc_entries[dc] = []
        dc_entries[dc].append((i, fields))

    # ファイルスコープの構造体定義と期待値配列を生成
    w(f'// qzqsm_history.md: {len(history)} 件の過去配信データ')
    w('// デコード成功 + disaster_category 一致 + フィールド値検証')
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
            w('    struct SeismicExpected { uint8_t intensity; uint8_t prefecture; uint8_t count; };')
            w('    static const SeismicExpected seismic_expected[] = {')
            for ei, f in entries:
                e0 = _entry0(f, history[ei]['nmea'])
                w(f'        {{{e0.get("intensity_code", 0)}, {e0.get("prefecture_code", 0)}, {f["count"]}}},')
            w('    };')
            w('')

        elif dc == 5:  # Tsunami
            w(f'    // dc={dc} {dc_name_label}: {len(entries)} entries')
            w('    struct TsunamiExpected { uint8_t warning_code; uint8_t height; uint16_t region; uint8_t count; };')
            w('    static const TsunamiExpected tsunami_expected[] = {')
            for ei, f in entries:
                e0 = _entry0(f, history[ei]['nmea'])
                w(f'        {{{f["warning_code"]}, {e0.get("height_code", 0)}, {e0.get("region_code", 0)}, {f["count"]}}},')
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
            w('    struct WeatherExpected { uint8_t warning_state; uint8_t sub_category; uint32_t region; uint8_t count; };')
            w('    static const WeatherExpected weather_expected[] = {')
            for ei, f in entries:
                e0 = _entry0(f, history[ei]['nmea'])
                w(f'        {{{f["warning_state"]}, {e0.get("sub_category", 0)}, {e0.get("region_code", 0)}, {f["count"]}}},')
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
            w('    struct MarineExpected { uint8_t warning_code; uint16_t region; uint8_t count; };')
            w('    static const MarineExpected marine_expected[] = {')
            for ei, f in entries:
                e0 = _entry0(f, history[ei]['nmea'])
                w(f'        {{{e0.get("warning_code", 0)}, {e0.get("region_code", 0)}, {f["count"]}}},')
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
    _emit_disabled_guard(w, 'history_cases')
    w('        REQUIRE(decodeNmea(history_cases[i].nmea, msg));')
    w('        CHECK(msg.msg_type == 43);')
    w('        CHECK(msg.payload_type == MsgPayloadType::Mt43);')
    w('        const Mt43Data* mt43 = msg.getMt43();')
    w('        REQUIRE(mt43 != nullptr);')
    w('        CHECK(mt43->disaster_category == history_cases[i].expected_dc);')
    w('')
    w('        // Field-level verification based on disaster category')
    w('        // (expected values from azaraC decode_to_json)')
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
            w(f'                CHECK({varname}->entries[0].intensity_code == seismic_expected[{idx_var}].intensity);')
            w(f'                CHECK({varname}->entries[0].prefecture_code == seismic_expected[{idx_var}].prefecture);')
            w(f'                CHECK({varname}->count == seismic_expected[{idx_var}].count);')
            w(f'                {idx_var}++;')
            w('                break;')
            w('            }')

        elif dc == 5:  # Tsunami
            w(f'            case {dc}: {{')
            w(f'                const {type_name}* {varname} = mt43->{getter}();')
            w(f'                REQUIRE({varname} != nullptr);')
            w(f'                CHECK({varname}->warning_code == tsunami_expected[{idx_var}].warning_code);')
            w(f'                CHECK({varname}->entries[0].height_code == tsunami_expected[{idx_var}].height);')
            w(f'                CHECK({varname}->entries[0].region_code == tsunami_expected[{idx_var}].region);')
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
            w(f'                CHECK({varname}->entries[0].sub_category == weather_expected[{idx_var}].sub_category);')
            w(f'                CHECK({varname}->entries[0].region_code == weather_expected[{idx_var}].region);')
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
            w(f'                CHECK({varname}->entries[0].warning_code == marine_expected[{idx_var}].warning_code);')
            w(f'                CHECK({varname}->entries[0].region_code == marine_expected[{idx_var}].region);')
            w(f'                CHECK({varname}->count == marine_expected[{idx_var}].count);')
            w(f'                {idx_var}++;')
            w('                break;')
            w('            }')

    w('            default: break;')
    w('        }')
    w('    }')
    w('}')
    w('')

    # Noto CSV テスト
    w(f'// qzqsm_20240101-0107_noto.csv: {len(noto)} 件（能登半島地震）')
    w('// デコード成功 + disaster_category / information_type / report_classification 検証')
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
    _emit_disabled_guard(w, 'noto_cases')
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

    # data.txt テスト
    w(f'// data.txt: {len(data_txt)} 件の DCX/DCR 混在生データ')
    w('// デコード成功 + msg_type + disaster_category/service_kind 検証')
    w('// (expected values from azaraC decode_to_json)')
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
    w('        if (!decodeNmea(data_txt_cases[i].nmea, msg)) {')
    w('            // Skip cases where the category is disabled at compile time')
    w('            if (msg.unsupported_reason == UnsupportedReason::DisabledAtCompileTime) continue;')
    w('            REQUIRE(false);')
    w('        }')
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
        print(f"  [{i}] dc={h['expected_dc']} {h['dc_name']}: decoded OK")

    print("\nDecoding data.txt entries...")
    data_txt_nmeas = [d['nmea'] for d in data_txt]
    data_txt_decoded = decode_batch(data_txt_nmeas, raw=True)
    mt_counts = {}
    for i, (d, dec) in enumerate(zip(data_txt, data_txt_decoded)):
        mt = dec.get('msg_type', '?')
        mt_counts[mt] = mt_counts.get(mt, 0) + 1
        if i < 5 or i >= len(data_txt) - 2:
            print(f"  [{i}] line={d['line']}: MT={mt}")
    print(f"  MT distribution: {mt_counts}")

    # Noto CSV は大量なのでデコードをスキップ（メタデータのみで十分）
    noto_decoded = [None] * len(noto)

    # C++ 生成
    cpp = generate_cpp(history, noto, data_txt,
                       history_decoded, noto_decoded, data_txt_decoded)

    os.makedirs(os.path.dirname(OUT_CPP), exist_ok=True)
    with open(OUT_CPP, 'w', encoding='utf-8', newline='\n') as f:
        f.write(cpp)
    print(f"\nGenerated: {OUT_CPP} ({len(cpp)} bytes)")


if __name__ == '__main__':
    main()
