#!/usr/bin/env python3
"""
cppcheck_summary.py — cppcheck の XML 出力をパースし、重要度別に集計した
Markdown サマリーを GitHub Actions の $GITHUB_STEP_SUMMARY 用に出力します。

Usage:
    # 従来通り cppcheck を実行してサマリー生成
    python scripts/analysis/cppcheck_summary.py

    # 既存の XML レポートファイルを読み込んでサマリー生成（CI用）
    python scripts/analysis/cppcheck_summary.py --input-xml path/to/cppcheck_report.xml

    # チェックレベルを指定（--input-xml 未指定時のみ有効）
    python scripts/analysis/cppcheck_summary.py --check-level normal

    # CI では >> $GITHUB_STEP_SUMMARY にリダイレクトして使用
    python scripts/analysis/cppcheck_summary.py -i cppcheck_report.xml >> $GITHUB_STEP_SUMMARY
"""

import argparse
import subprocess
import sys
import xml.etree.ElementTree as ET
from collections import OrderedDict
from pathlib import Path

# ── 設定 ──────────────────────────────────────────────────────────────────────

# 重要度 → ラベル / 絵文字 マッピング（表示順を制御するため OrderedDict を使用）
SEVERITY_ORDER = OrderedDict([
    ("error",       ("error",       "🚨")),
    ("warning",     ("warning",     "⚠ ")),
    ("style",       ("style",       "💡")),
    ("performance", ("performance", "⚡")),
    ("portability", ("portability", "🔧")),
    ("information", ("information", "ℹ ")),
])

# cppcheck の実行パラメータ（Makefile の check ターゲットと同一）
CPPCHECK_BASE_ARGS = [
    "cppcheck",
    "--enable=warning,performance,portability",
    "--inline-suppr",
    "--suppress=missingIncludeSystem",
    "--suppress=*:test/doctest.h",
    "--std=c++17",
    "--xml",
    "-Isrc",
    "-Itest",
    "-DAZARAC_NANKAI_MAX_PAGES=63",
    "-DAZARAC_NANKAI_AGGREGATED_TEXT_SIZE=1135",
    "src",
    "test",
]

REPO_ROOT = Path(__file__).resolve().parent.parent  # リポジトリルート


# ── メイン処理 ────────────────────────────────────────────────────────────────

def run_cppcheck(check_level: str = "exhaustive") -> str:
    """cppcheck を XML モードで実行し、標準出力を文字列として返す。"""
    cmd = CPPCHECK_BASE_ARGS[:1]  # ["cppcheck"]
    cmd += ["--check-level=" + check_level]
    cmd += CPPCHECK_BASE_ARGS[1:]  # 残りの引数

    result = subprocess.run(
        cmd,
        capture_output=True,
        text=True,
        cwd=REPO_ROOT,
    )
    # cppcheck は issue があると exit code 1 になるが、XML は stdout に出力される
    xml_output = result.stdout.strip()
    if not xml_output:
        print("[cppcheck_summary] WARNING: cppcheck produced no XML output.",
              file=sys.stderr)
        print(f"  cwd={REPO_ROOT}  stderr={result.stderr[:200] if result.stderr else '(empty)'}",
              file=sys.stderr)
    return xml_output


def parse_cppcheck_xml(xml_str: str) -> dict:
    """
    cppcheck の XML 出力をパースし、severity ごとに issue のリストを返す。
    → { severity: [ { "file", "line", "message", "id" }, ... ], ... }
    """
    issues: dict[str, list[dict]] = {sev: [] for sev in SEVERITY_ORDER}

    if not xml_str:
        return issues

    try:
        root = ET.fromstring(xml_str)
    except ET.ParseError as e:
        print(f"[cppcheck_summary] ERROR: Failed to parse XML: {e}", file=sys.stderr)
        print(f"  XML (first 500 chars): {xml_str[:500]}", file=sys.stderr)
        return issues

    for error_elem in root.findall(".//error"):
        severity = error_elem.get("severity", "unknown")
        msg = error_elem.get("msg", "(no message)")
        error_id = error_elem.get("id", "(no id)")

        # <location> 要素を取得（複数ある場合は最初のもの）
        location_elem = error_elem.find("location")
        if location_elem is not None:
            file_path = location_elem.get("file", "(unknown)")
            line = location_elem.get("line", "0")
        else:
            file_path = "(unknown)"
            line = "0"

        # Skip issues from third-party test framework (doctest.h)
        if "doctest.h" in file_path:
            continue

        issue = {
            "file": file_path,
            "line": line,
            "message": msg,
            "id": error_id,
        }

        issues.setdefault(severity, []).append(issue)

    return issues


def _escape_md_table(text: str) -> str:
    """Markdown テーブルセル内で | や改行がレイアウトを壊さないようエスケープする。"""
    return text.replace("|", "\\|").replace("\n", " ").replace("\r", "")


def generate_markdown(issues: dict) -> str:
    """issues から Markdown サマリー文字列を生成。"""
    lines: list[str] = []
    lines.append("### 🔍 Cppcheck Static Analysis Results")
    lines.append("")

    total_count = sum(len(v) for v in issues.values())

    # 表示順: SEVERITY_ORDER に定義された既知の重要度、その後に未知の重要度を続ける
    display_order = list(SEVERITY_ORDER.keys())
    for key in issues:
        if key not in display_order:
            display_order.append(key)

    # ── 件数テーブル ──
    lines.append("| Severity | Count |")
    lines.append("|----------|-------|")
    for sev_key in display_order:
        if sev_key in SEVERITY_ORDER:
            sev_label, emoji = SEVERITY_ORDER[sev_key]
        else:
            sev_label, emoji = sev_key, "❓"
        count = len(issues.get(sev_key, []))
        lines.append(f"| {emoji} {sev_label} | {count} |")
    lines.append(f"| **Total** | **{total_count}** |")
    lines.append("")

    # ── 詳細 (件数 > 0 の重要度のみ折りたたみ表示) ──
    if total_count == 0:
        lines.append("✅ No issues detected.")
        lines.append("")
    else:
        for sev_key in display_order:
            sev_issues = issues.get(sev_key, [])
            if not sev_issues:
                continue
            count = len(sev_issues)
            if sev_key in SEVERITY_ORDER:
                sev_label, emoji = SEVERITY_ORDER[sev_key]
            else:
                sev_label, emoji = sev_key, "❓"
            lines.append("<details>")
            lines.append(f"<summary>{emoji} {sev_label} ({count})</summary>")
            lines.append("")
            lines.append("| File | Line | Message |")
            lines.append("|------|------|---------|")
            for iss in sev_issues:
                # ファイルパスをリポジトリルートからの相対パスとして表示
                # | や改行を含むメッセージでもテーブルが崩れないようエスケープ
                file_display = f"`{_escape_md_table(iss['file'])}`"
                lines.append(f"| {file_display} | {iss['line']} | {_escape_md_table(iss['message'])} |")
            lines.append("")
            lines.append("</details>")
            lines.append("")

        if total_count > 0:
            lines.append(f"**{total_count} issue(s)** found across {sum(1 for v in issues.values() if v)} severity level(s).")
            lines.append("")

    return "\n".join(lines)


def main() -> int:
    parser = argparse.ArgumentParser(
        description="cppcheck XML → Markdown サマリー変換"
    )
    parser.add_argument(
        "--input-xml", "-i",
        type=str,
        default=None,
        help="既存の cppcheck XML レポートファイルへのパス。指定しない場合は cppcheck を実行する。"
    )
    parser.add_argument(
        "--check-level",
        type=str,
        default="exhaustive",
        choices=["exhaustive", "normal", "simple"],
        help="cppcheck のチェックレベル（--input-xml 未指定時のみ有効。デフォルト: exhaustive）"
    )
    args = parser.parse_args()

    if args.input_xml:
        xml_path = Path(args.input_xml)
        if not xml_path.is_absolute():
            # 相対パスはカレントディレクトリ基準で解決
            xml_path = Path.cwd() / xml_path
        if not xml_path.exists():
            print(f"[cppcheck_summary] ERROR: Input XML file not found: {xml_path}",
                  file=sys.stderr)
            # エラーでも空の結果を返して CI が止まらないようにする
            issues = {sev: [] for sev in SEVERITY_ORDER}
        else:
            with open(xml_path, "r", encoding="utf-8") as f:
                xml_str = f.read()
            issues = parse_cppcheck_xml(xml_str)
    else:
        # 後方互換性: 引数なしの場合は従来通り cppcheck を実行
        xml_str = run_cppcheck(check_level=args.check_level)
        issues = parse_cppcheck_xml(xml_str)

    markdown = generate_markdown(issues)
    print(markdown)
    return 0


if __name__ == "__main__":
    sys.exit(main())
