#!/usr/bin/env python3
"""_common.py — test/scripts 共通ヘルパ（DC_MAP / NMEA / JSON serialize / パス）"""
import os
import sys
from datetime import datetime

# ── パス ──────────────────────────────────────────────────────────────
BASE = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
REALDATA = os.path.join(BASE, "realdata")
DECODE_BIN = os.path.join(BASE, "test", f"decode_to_json{_exe}")
AZARAC_BIN = DECODE_BIN  # alias for compare_with_azarashi.py
PYTHON = os.environ.get("PYTHON", sys.executable)

# ── 災害カテゴリ / 情報種別 / 報告分類 ────────────────────────────────
DC_MAP = {
    "緊急地震速報": 1, "震源": 2, "震度": 3, "南海トラフ地震": 4,
    "津波": 5, "北西太平洋津波": 6, "火山": 8, "降灰": 9,
    "気象": 10, "洪水": 11, "台風": 12, "海上": 14,
}
IT_MAP = {"発表": 0, "訂正": 1, "取消": 2}
RC_MAP = {"最優先": 1, "優先": 2, "通常": 3, "訓練/試験": 7}

# ── NMEA ──────────────────────────────────────────────────────────────
def nmea_checksum(body: str) -> str:
    cs = 0
    for ch in body:
        cs ^= ord(ch)
    return f"*{cs:02X}"


def make_qzqsm(svid: int, hex_payload: str) -> str:
    body = f"QZQSM,{svid},{hex_payload}"
    return f"${body}{nmea_checksum(body)}"


# ── JSON serialize ──────────────────────────────────────────────────
def json_serial(obj):
    """azarashi オブジェクト等を JSON 文字列化（robust: __str__/__repr__ 例外も吸収）"""
    if isinstance(obj, datetime):
        return obj.isoformat()
    if isinstance(obj, bytes):
        return obj.hex()
    if isinstance(obj, set):
        return list(obj)
    if hasattr(obj, "__dict__"):
        return {k: json_serial(v) for k, v in obj.__dict__.items()}
    try:
        return str(obj)
    except Exception:  # noqa: BLE001
        try:
            return repr(obj)
        except Exception:  # noqa: BLE001
            return f"<{type(obj).__name__}>"
