#!/usr/bin/env python3
"""compare_with_azarashi.py — azarashi vs AzaraC 出力比較スクリプト

realdata/ の実際のQZSSメッセージを入力とし、azarashi (リファレンス実装) と
AzaraC のデコード結果を比較する。

比較は「_raw サフィックスの数値フィールド」を中心に行う。
ラベル文字列は言語・フォーマット差異が多いため、数値の一致を主眼とする。

使い方:
    python test/scripts/compare_with_azarashi.py
    python test/scripts/compare_with_azarashi.py --verbose
    python test/scripts/compare_with_azarashi.py --source history
    python test/scripts/compare_with_azarashi.py --source noto
    python test/scripts/compare_with_azarashi.py --source data_txt
"""

import csv
import json
import os
import re
import subprocess
import sys
import argparse
import urllib.request

try:
    import azarashi
except ImportError:
    print("ERROR: azarashi package not found. Install with: pip install azarashi", file=sys.stderr)
    sys.exit(1)

# ── パス設定 ──────────────────────────────────────────────────────────────
BASE = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
REALDATA = os.path.join(BASE, 'realdata')
_exe = '.exe' if os.name == 'nt' else ''
AZARAC_BIN = os.path.join(BASE, 'test', f'decode_to_json{_exe}')
PYTHON = os.environ.get('PYTHON', sys.executable)

# ── NMEA生成ヘルパー ──────────────────────────────────────────────────────

def nmea_checksum(body: str) -> str:
    cs = 0
    for ch in body:
        cs ^= ord(ch)
    return f"*{cs:02X}"


def make_qzqsm(svid: int, hex_payload: str) -> str:
    body = f"QZQSM,{svid},{hex_payload}"
    return f"${body}{nmea_checksum(body)}"


# ── realdata パーサ ───────────────────────────────────────────────────────

DC_MAP = {
    '緊急地震速報': 1, '震源': 2, '震度': 3, '南海トラフ地震': 4,
    '津波': 5, '北西太平洋津波': 6, '火山': 8, '降灰': 9,
    '気象': 10, '洪水': 11, '台風': 12, '海上': 14,
}

IT_MAP = {'発表': 0, '訂正': 1, '取消': 2}
RC_MAP = {'最優先': 1, '優先': 2, '通常': 3, '訓練/試験': 7}


def parse_history(filepath: str) -> list[dict]:
    results = []
    current_dc = None
    with open(filepath, encoding='utf-8') as f:
        for line in f:
            line = line.strip()
            m = re.match(r'^##\s+dc=(\d+)\s+(.+)', line)
            if m:
                current_dc = int(m.group(1))
                continue
            m = re.match(r'^`(\$QZQSM,\d+,[0-9A-Fa-f]+\*[0-9A-Fa-f]{2})`', line)
            if m and current_dc is not None:
                results.append({'nmea': m.group(1), 'source': 'history'})
    return results


def parse_noto_csv(filepath: str) -> list[dict]:
    results = []
    with open(filepath, encoding='utf-8') as f:
        reader = csv.DictReader(f)
        for row in reader:
            hex_payload = row['message'].strip()
            nmea = make_qzqsm(57, hex_payload)
            results.append({'nmea': nmea, 'source': 'noto'})
    return results


def parse_data_txt(filepath: str) -> list[dict]:
    results = []
    with open(filepath, encoding='utf-8') as f:
        for line in f:
            hex_payload = line.strip()
            if hex_payload:
                nmea = make_qzqsm(57, hex_payload)
                results.append({'nmea': nmea, 'source': 'data_txt'})
    return results


def parse_l1s_archive(filepath: str) -> list[dict]:
    """QZSSのL1SアーカイブバイナリファイルをパースしてNMEAセンテンスを抽出"""
    if not os.path.exists(filepath):
        os.makedirs(os.path.dirname(filepath), exist_ok=True)
        file_id = os.path.basename(filepath)
        url = f"https://sys.qzss.go.jp/dod/api/get/l1s?id={file_id}"
        print(f"Downloading L1S archive {file_id} from QZSS API...")
        try:
            urllib.request.urlretrieve(url, filepath)
            print(f"Saved to {filepath}")
        except Exception as e:
            print(f"ERROR: Failed to download L1S archive: {e}", file=sys.stderr)
            sys.exit(1)

    results = []
    with open(filepath, "rb") as f:
        while True:
            record = f.read(38)
            if len(record) < 38:
                break

            prn = record[0]
            l1s_msg = record[5:37]  # 32 bytes (256 bits)
            mt = l1s_msg[1] >> 2    # Message Type (6 bits)

            # デコード対象は DCR (MT43) および DCX (MT44) のみ
            if mt not in (43, 44):
                continue

            svid = prn - 128 if prn >= 128 else prn
            # 63文字の16進数（252ビット）のペイロードを作成
            hex_payload = l1s_msg.hex()[:-1].upper()
            nmea = make_qzqsm(svid, hex_payload)
            results.append({'nmea': nmea, 'source': 'l1s'})
    return results


# ── azarashi でデコード ───────────────────────────────────────────────────

def json_serial(obj):
    if isinstance(obj, bytes):
        return obj.hex()
    if hasattr(obj, '__dict__'):
        return {k: json_serial(v) for k, v in obj.__dict__.items()}
    try:
        return str(obj)
    except:
        return repr(obj)


def decode_with_azarashi(nmea: str) -> dict:
    try:
        r = azarashi.decode(nmea.strip())
        return r.get_params()
    except Exception as e:
        return {"_error": str(e)}


# ── AzaraC でデコード ─────────────────────────────────────────────────────

def decode_with_azarac(nmeas: list[str], raw: bool = False) -> list[dict]:
    """AzaraC CLI ツールを呼び出してデコード"""
    if not os.path.exists(AZARAC_BIN):
        print(f"ERROR: AzaraC binary not found: {AZARAC_BIN}", file=sys.stderr)
        print("Build it first with: cd test && make decode", file=sys.stderr)
        sys.exit(1)

    input_text = "\n".join(nmeas) + "\n"
    cmd = [AZARAC_BIN]
    if raw:
        cmd.append("--raw")
    try:
        result = subprocess.run(
            cmd,
            input=input_text,
            capture_output=True,
            text=True,
            timeout=30,
            encoding='utf-8',
            errors='replace'
        )
        if result.returncode != 0:
            print(f"WARNING: AzaraC binary returned code {result.returncode}", file=sys.stderr)
            print(f"stderr: {result.stderr}", file=sys.stderr)
            return [{"_error": f"azarac_exit_{result.returncode}"} for _ in nmeas]

        return json.loads(result.stdout)
    except subprocess.TimeoutExpired:
        return [{"_error": "timeout"} for _ in nmeas]
    except json.JSONDecodeError as e:
        print(f"ERROR: Failed to parse AzaraC JSON output: {e}", file=sys.stderr)
        return [{"_error": "json_parse_failed"} for _ in nmeas]


# ── フラット化 & 正規化 ───────────────────────────────────────────────────

def flatten_dict(d: dict, prefix: str = "") -> dict:
    """ネストされたdictをフラット化 (キーは '.' 区切り)"""
    result = {}
    for k, v in d.items():
        key = f"{prefix}.{k}" if prefix else k
        if isinstance(v, dict):
            result.update(flatten_dict(v, key))
        elif isinstance(v, list):
            # リストはインデックス付きでフラット化
            for i, item in enumerate(v):
                if isinstance(item, dict):
                    result.update(flatten_dict(item, f"{key}[{i}]"))
                else:
                    result[f"{key}[{i}]"] = item
        else:
            result[key] = v
    return result


def normalize_value(v):
    """値を正規化: None → None, 数値文字列→数値, 真偽→bool"""
    if v is None:
        return None
    if isinstance(v, bool):
        return v
    if isinstance(v, (int, float)):
        return v
    if isinstance(v, str):
        # 数値文字列を数値に変換
        try:
            if '.' in v:
                return float(v)
            return int(v)
        except (ValueError, TypeError):
            pass
        # 真偽文字列
        if v.lower() in ('true', 'false'):
            return v.lower() == 'true'
    return v


# ── キー対応表 (azarashi → AzaraC) ───────────────────────────────────────

# azarashi のキー名 → AzaraC のキー名 (パス)
KEY_MAPPING = {
    # 共通ヘッダ
    "satellite_id": "svid",
    "satellite_prn": None,  # AzaraC は svid_label に含む
    "message_type": None,  # "DCR"/"DCX" → 43/44
    "report_classification_no": "report_classification",
    "disaster_category_no": "disaster_category",
    "information_type_no": "information_type",
    "report_time": "report_time",  # フォーマット差異あり

    # EEW
    "depth_of_hypocenter_raw": "detail.depth",
    "magnitude_raw": "detail.magnitude",
    "seismic_epicenter_raw": "detail.epicenter",
    "seismic_intensity_lower_limit_raw": "detail.intensity_lower",
    "seismic_intensity_upper_limit_raw": "detail.intensity_upper",
    "notifications_on_disaster_prevention_raw": "detail.notifications",
    "eew_forecast_regions_raw": "detail.regions",
    "occurrence_time_of_earthquake": "detail.quake_time",

    # 無視するキー (メタデータ・デバッグ用)
    "_ignore": [
        "sentence", "raw", "timestamp", "message", "nmea", "message_header",
        "preamble", "version", "assumptive",
        "report_classification", "report_classification_en",
        "disaster_category", "disaster_category_en",
        "information_type", "information_type_en",
        "long_period_ground_motion_lower_limit",
        "long_period_ground_motion_upper_limit",
        "depth_of_hypocenter", "magnitude",
        "seismic_epicenter", "seismic_intensity_lower_limit",
        "seismic_intensity_upper_limit",
        "notifications_on_disaster_prevention",
        "eew_forecast_regions",
    ]
}


def build_comparison(azarashi_flat: dict, azarac_flat: dict) -> list[dict]:
    """azarashi と AzaraC のフラット化結果を比較し、差分リストを返す"""
    differences = []

    # 無視するキーセット
    ignore_keys = set(KEY_MAPPING["_ignore"])

    # azarashi の _raw キーを探して AzaraC の対応キーと比較
    for az_key, az_val in azarashi_flat.items():
        # 無視キーをスキップ
        if az_key in ignore_keys:
            continue
        # _raw で終わるキーは対応する AzaraC キーと比較
        if az_key.endswith("_raw"):
            base_name = az_key[:-4]  # "_raw" を除去
            # マッピングを確認
            if base_name in KEY_MAPPING:
                azarac_key = KEY_MAPPING[base_name]
                if azarac_key is None:
                    continue
                azarac_val = azarac_flat.get(azarac_key)
                # 比較
                if not values_equal(az_val, azarac_val, azarac_flat, azarac_key):
                    differences.append({
                        "field": f"azarashi.{az_key} vs azarac.{azarac_key}",
                        "azarashi": az_val,
                        "azarac": azarac_val,
                    })

    return differences


def values_equal(az_val, ac_val, ac_flat: dict, ac_key: str) -> bool:
    """値を比較 (型の違いを吸収)"""
    # None チェック
    if az_val is None and ac_val is None:
        return True
    if az_val is None or ac_val is None:
        # azarashi の null は AzaraC の 0 と同等の場合がある
        if az_val is None and ac_val == 0:
            return True
        return False

    # リスト比較
    if isinstance(az_val, list) and isinstance(ac_val, list):
        if len(az_val) != len(ac_val):
            return False
        for a, b in zip(az_val, ac_val):
            if isinstance(a, (int, float)) and isinstance(b, (int, float)):
                if a != b:
                    return False
            elif str(a) != str(b):
                return False
        return True

    # 数値比較
    az_norm = normalize_value(az_val)
    ac_norm = normalize_value(ac_val)
    if isinstance(az_norm, (int, float)) and isinstance(ac_norm, (int, float)):
        return az_norm == ac_norm

    # 文字列比較
    return str(az_val) == str(ac_val)


# ── メイン ────────────────────────────────────────────────────────────────

def main():
    parser = argparse.ArgumentParser(description="Compare azarashi vs AzaraC output")
    parser.add_argument("--source", choices=["history", "noto", "data_txt", "l1s", "all"],
                        default="all", help="Which realdata source to test")
    parser.add_argument("--verbose", "-v", action="store_true", help="Show all differences")
    parser.add_argument("--max-diff", type=int, default=10, help="Max differences to show per case")
    args = parser.parse_args()

    # 数据読み込み
    cases = []
    if args.source in ("history", "all"):
        cases.extend(parse_history(os.path.join(REALDATA, 'qzqsm_history.md')))
    if args.source in ("noto", "all"):
        cases.extend(parse_noto_csv(os.path.join(REALDATA, 'qzqsm_20240101-0107_noto.csv')))
    if args.source in ("data_txt", "all"):
        cases.extend(parse_data_txt(os.path.join(REALDATA, 'data.txt')))
    if args.source in ("l1s", "all"):
        cases.extend(parse_l1s_archive(os.path.join(REALDATA, 'Q002_20240101.l1s')))

    print(f"Testing {len(cases)} messages from realdata/ ...")

    # AzaraC で一括デコード
    nmeas = [c['nmea'] for c in cases]
    # この比較は入力ごとに1件の出力を必要とするためParser処理を迂回する
    azarac_results = decode_with_azarac(nmeas, raw=True)
    if len(azarac_results) != len(cases):
        print(
            f"ERROR: AzaraC returned {len(azarac_results)} results for {len(cases)} inputs",
            file=sys.stderr,
        )
        sys.exit(1)

    # メッセージごとに比較
    total = 0
    passed = 0
    failed_cases = []

    for i, (case, azarac_msg) in enumerate(zip(cases, azarac_results)):
        nmea = case['nmea']

        # azarashi でデコード
        azarashi_params = decode_with_azarashi(nmea)

        # エラーチェック
        if "_error" in azarashi_params:
            print(f"  [{i}] SKIP (azarashi error: {azarashi_params['_error']})")
            continue
        if "_error" in azarac_msg:
            print(f"  [{i}] SKIP (AzaraC error: {azarac_msg['_error']})")
            failed_cases.append((i, nmea, "azarac_error", azarac_msg['_error']))
            continue

        total += 1

        # フラット化
        azarashi_flat = flatten_dict(azarashi_params)
        azarac_flat = flatten_dict(azarac_msg)

        # 比較
        diffs = build_comparison(azarashi_flat, azarac_flat)

        if not diffs:
            passed += 1
        else:
            failed_cases.append((i, nmea, diffs, None))
            if args.verbose:
                print(f"  [{i}] DIFF ({len(diffs)} differences)")
                for d in diffs[:args.max_diff]:
                    print(f"    {d['field']}: azarashi={d['azarashi']} vs azarac={d['azarac']}")

    # レポート
    print(f"\n{'='*60}")
    print(f"Results: {passed}/{total} passed, {len(failed_cases)} with differences")
    print(f"{'='*60}")

    if failed_cases:
        print(f"\nFailed cases (showing first 5):")
        for idx, (i, nmea, diffs, err) in enumerate(failed_cases[:5]):
            if err:
                print(f"  [{i}] ERROR: {err}")
            else:
                print(f"  [{i}] {len(diffs)} diffs: {nmea[:60]}...")
                for d in diffs[:3]:
                    print(f"    {d['field']}: azarashi={d['azarashi']} vs azarac={d['azarac']}")

    # 終了コード
    sys.exit(0 if len(failed_cases) == 0 else 1)


if __name__ == '__main__':
    main()
