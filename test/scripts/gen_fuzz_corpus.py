#!/usr/bin/env python3
"""gen_fuzz_corpus.py — コミット済みベクタ JSON から libFuzzer のシードコーパスを生成する。

入力: test/data/{dcr,dcx,nankai}_vectors.json（nmea 文字列と params.message = 250bit フレームの 64 桁 hex）
出力: test/fuzz/corpus/{nmea_,raw_,ubx_}<sha256(content)[:16]>

冪等: 既存の nmea_/raw_/ubx_ 接頭辞ファイルを削除してから書き出すので、再実行でツリーが一致する。
使い方: python test/scripts/gen_fuzz_corpus.py （リポジトリルートから）
"""
import hashlib
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
DATA = ROOT / "test" / "data"
OUT = ROOT / "test" / "fuzz" / "corpus"
VECTORS = ["dcr_vectors.json", "dcx_vectors.json", "nankai_vectors.json"]


def ubx_packet(raw: bytes, svid: int) -> bytes:
    """250bit フレームから有効な UBX-RXM-SFRBX パケットを合成する（src/framer/UbxFramer.cpp の parse の逆変換）。"""
    # SFRBX ヘッダ: gnssId(5=QZSS) svId sigId(0=L1S) freqId numWords(8) chn version(1) reserved
    header = bytes([5, svid & 0xFF, 0, 0, 8, 0, 1, 0])
    # parse は各ワードをバイトスワップして out.bits へ入れるので、逆に反転して目的のフレームにする。
    words = b"".join(raw[i:i + 4][::-1] for i in range(0, 32, 4))
    payload = header + words
    body = bytes([0x02, 0x13, len(payload) & 0xFF, (len(payload) >> 8) & 0xFF]) + payload
    ck_a = ck_b = 0
    for b in body:
        ck_a = (ck_a + b) & 0xFF
        ck_b = (ck_b + ck_a) & 0xFF
    return b"\xB5\x62" + body + bytes([ck_a, ck_b])


def main():
    OUT.mkdir(parents=True, exist_ok=True)
    for old in OUT.iterdir():
        if old.is_file() and old.name.split("_")[0] in ("nmea", "raw", "ubx"):
            old.unlink()

    counts = {"nmea": 0, "raw": 0, "ubx": 0}
    for name in VECTORS:
        for entry in json.loads((DATA / name).read_text(encoding="utf-8")):
            nmea = entry.get("nmea")
            if nmea:
                content = (nmea + "\r\n").encode("ascii")
                (OUT / f"nmea_{hashlib.sha256(content).hexdigest()[:16]}").write_bytes(content)
                counts["nmea"] += 1

            params = entry.get("params") or {}
            hexmsg = params.get("message")
            if not hexmsg:
                continue
            raw = bytes.fromhex(hexmsg)
            if len(raw) != 32:
                continue
            (OUT / f"raw_{hashlib.sha256(raw).hexdigest()[:16]}").write_bytes(raw)
            counts["raw"] += 1

            svid = params.get("satellite_id", 58)
            packet = ubx_packet(raw, svid)
            (OUT / f"ubx_{hashlib.sha256(packet).hexdigest()[:16]}").write_bytes(packet)
            counts["ubx"] += 1

    total = sum(counts.values())
    print(f"corpus: {total} files ({counts['nmea']} nmea, {counts['raw']} raw, {counts['ubx']} ubx) -> {OUT}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
