"""nankai_vectors.json の決まったフィールドの SHA-256 を管理する。

params.timestamp は azarashi の生成時刻で毎回変わるため対象外。
C++ フィクスチャとテストが参照する nmea / type / params（timestamp 以外）を
キー順・区切りを正規化してハッシュする。

使い方:
    python test/scripts/hash_nankai_vectors.py --check   # CI（既定）
    python test/scripts/hash_nankai_vectors.py --update  # JSON を意図的に更新したとき
"""
import argparse
import hashlib
import json
import os
import sys

DATA_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "data")
JSON_PATH = os.path.join(DATA_DIR, "nankai_vectors.json")
DIGEST_PATH = os.path.join(DATA_DIR, "nankai_vectors.sha256")


def deterministic_projection(doc):
    """timestamp を除いた、フィクスチャが依存するフィールドだけを残す。"""
    rows = []
    for row in doc:
        params = {k: v for k, v in (row.get("params") or {}).items() if k != "timestamp"}
        rows.append({"nmea": row.get("nmea"), "type": row.get("type"), "params": params})
    return rows


def compute_digest(doc):
    canonical = json.dumps(deterministic_projection(doc), ensure_ascii=False,
                           sort_keys=True, separators=(",", ":"))
    return hashlib.sha256(canonical.encode("utf-8")).hexdigest()


def write_digest():
    """生成器から呼ぶ: 現在の JSON に合わせて .sha256 を更新する。"""
    with open(JSON_PATH, encoding="utf-8") as f:
        doc = json.load(f)
    with open(DIGEST_PATH, "w", encoding="utf-8", newline="\n") as f:
        f.write(compute_digest(doc) + "\n")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    group = parser.add_mutually_exclusive_group()
    group.add_argument("--check", action="store_true", help="committed digest と一致するか検証する（既定）")
    group.add_argument("--update", action="store_true", help="committed digest を現在の JSON で更新する")
    args = parser.parse_args()

    with open(JSON_PATH, encoding="utf-8") as f:
        doc = json.load(f)
    actual = compute_digest(doc)

    if args.update:
        with open(DIGEST_PATH, "w", encoding="utf-8", newline="\n") as f:
            f.write(actual + "\n")
        print(f"updated {DIGEST_PATH}: {actual}")
        return 0

    if not os.path.exists(DIGEST_PATH):
        print(f"missing {DIGEST_PATH}; run with --update", file=sys.stderr)
        return 1
    with open(DIGEST_PATH, encoding="utf-8") as f:
        expected = f.read().strip()
    if actual != expected:
        print("nankai_vectors.json deterministic digest mismatch:", file=sys.stderr)
        print(f"  expected {expected}", file=sys.stderr)
        print(f"  actual   {actual}", file=sys.stderr)
        return 1
    print(f"nankai_vectors.json digest OK: {actual}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
