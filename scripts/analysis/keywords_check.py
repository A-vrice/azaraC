#!/usr/bin/env python3
"""keywords_check.py — keywords.txt が公開 API を網羅しているか双方向検証する。

KEYWORD1: 公開ヘッダの struct/class/union/enum class 定義名と双方向差分。
LITERAL1: azaraC_config.h のユーザー設定 AZARAC_* マクロと双方向差分。
KEYWORD2（メソッド）は機械検証の対象外（keywords.txt の手動リストで管理）。
使い方: python scripts/analysis/keywords_check.py （リポジトリルートから）
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
HEADERS = [
    "src/Parser.h", "src/Message.h", "src/Mt43Data.h", "src/Mt44Data.h",
    "src/internal/MtCommonTypes.h", "src/framer/IFramer.h", "src/framer/Frame.h",
    "src/internal/NankaiPageBuffer.h",
]
# 定義のみ拾う（同一行に { が必須）。前方宣言 struct ParserTestHook; は除外される。
# スキャン対象ヘッダは全て開き括弧が同一行にあることを確認済み。
TYPE_RE = re.compile(r"^[ \t]*(?:struct|class|union|enum[ \t]+class)[ \t]+([A-Za-z_]\w*)[^\n]*\{", re.MULTILINE)
MACRO_RE = re.compile(
    r"^#define[ \t]+(AZARAC_(?:ENABLE_[A-Z_0-9]+|LANG_[A-Z]+|NANKAI_[A-Z_]+|"
    r"DEDUP_[A-Z_0-9]+|NMEA_[A-Z_]+|AVR_LARGE_FLASH|FLASH_BUF_SIZE))[ \t]", re.MULTILINE)


def main():
    kw = {}
    for line in (ROOT / "keywords.txt").read_text(encoding="utf-8").splitlines():
        parts = line.split("\t")
        if len(parts) >= 2 and parts[0] and not parts[0].startswith("#"):
            kw.setdefault(parts[1].strip(), set()).add(parts[0].strip())
    types = set()
    for h in HEADERS:
        types.update(TYPE_RE.findall((ROOT / h).read_text(encoding="utf-8")))
    macros = set(MACRO_RE.findall((ROOT / "src/azaraC_config.h").read_text(encoding="utf-8")))
    k1 = kw.get("KEYWORD1", set())
    l1 = {n for n in kw.get("LITERAL1", set()) if n.startswith("AZARAC_")}
    errors = []
    for name in sorted(types - k1):
        errors.append(f"missing KEYWORD1: {name}")
    for name in sorted(k1 - types):
        errors.append(f"stale KEYWORD1 (not in public headers): {name}")
    for name in sorted(macros - l1):
        errors.append(f"missing LITERAL1: {name}")
    for name in sorted(l1 - macros):
        errors.append(f"stale LITERAL1 (not a user macro): {name}")
    if errors:
        print("\n".join(errors), file=sys.stderr)
        return 1
    print(f"keywords OK: {len(types)} types, {len(macros)} macros")
    return 0


if __name__ == "__main__":
    sys.exit(main())
