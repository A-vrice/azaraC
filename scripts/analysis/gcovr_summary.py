#!/usr/bin/env python3
r"""
gcovr_summary.py — gcovr の JSON 出力をパースし、ファイル別・全体のカバレッジを
Markdown サマリーとして出力します。GitHub Actions の $GITHUB_STEP_SUMMARY 用に使用します。

Usage:
    # gcovr の JSON レポートを生成
    gcovr . --filter=../src/ --exclude='.*test_.*\.cpp' --json-pretty -o coverage_report.json

    # サマリーを生成
    python scripts/gcovr_summary.py --input coverage_report.json

    # CI では >> $GITHUB_STEP_SUMMARY にリダイレクトして使用
    python scripts/gcovr_summary.py -i coverage_report.json >> $GITHUB_STEP_SUMMARY
"""

import argparse
import json
import sys
from pathlib import Path


# ── メイン処理 ────────────────────────────────────────────────────────────────

def parse_gcovr_json(json_path: Path) -> dict:
    """gcovr JSON を読み込み、ファイル別のカバレッジ情報を返す。"""
    try:
        with open(json_path, "r", encoding="utf-8") as f:
            data = json.load(f)
    except json.JSONDecodeError as e:
        print(f"[gcovr_summary] ERROR: Failed to parse JSON: {e}", file=sys.stderr)
        print(f"  file: {json_path}", file=sys.stderr)
        return {"total_lines": 0, "total_exec": 0, "per_file": []}

    files: list[dict] = data.get("files", [])
    if not files:
        return {"total_lines": 0, "total_exec": 0, "per_file": []}

    per_file: list[dict] = []
    grand_total_lines = 0
    grand_total_exec = 0

    for file_info in files:
        file_path = file_info.get("file", "(unknown)")
        lines = file_info.get("lines", [])

        total_lines = 0  # 実行可能行数
        executed_lines = 0  # 実行された行数

        for line_data in lines:
            count = line_data.get("count", None)
            # count が数値以外（"-" や null）は実行可能行ではない
            if count is None or count == "-":
                continue
            try:
                count_int = int(count)
            except (ValueError, TypeError):
                continue

            total_lines += 1
            if count_int > 0:
                executed_lines += 1

        if total_lines > 0:
            coverage = (executed_lines / total_lines) * 100.0
        else:
            coverage = 100.0  # 実行可能行がない場合は 100% 扱い

        per_file.append({
            "file": file_path,
            "total_lines": total_lines,
            "executed_lines": executed_lines,
            "coverage": coverage,
        })

        grand_total_lines += total_lines
        grand_total_exec += executed_lines

    if grand_total_lines > 0:
        total_coverage = (grand_total_exec / grand_total_lines) * 100.0
    else:
        total_coverage = 100.0  # per_file と同様、実行可能行が 0 なら 100% 扱い

    return {
        "total_lines": grand_total_lines,
        "total_exec": grand_total_exec,
        "total_coverage": total_coverage,
        "per_file": per_file,
    }


def _coverage_emoji(coverage_pct: float) -> str:
    """カバレッジ率に応じた絵文字を返す。"""
    if coverage_pct >= 80:
        return "🟢"
    elif coverage_pct >= 50:
        return "🟡"
    else:
        return "🔴"


def _short_path(file_path: str) -> str:
    """冗長な前パス（/home/runner/work/... 等）を削り src/... 形式で表示する。"""
    marker = "src/"
    idx = file_path.rfind(marker)
    if idx != -1:
        return file_path[idx:]
    return file_path


def generate_markdown(stats: dict) -> str:
    """カバレッジ統計から Markdown サマリーを生成。"""
    lines: list[str] = []
    lines.append("### 📊 Coverage Report (gcovr)")
    lines.append("")

    per_file = stats.get("per_file", [])
    total_lines_count = stats.get("total_lines", 0)
    total_exec_count = stats.get("total_exec", 0)
    total_coverage = stats.get("total_coverage", 0.0)

    if not per_file:
        lines.append("⚠️ No coverage data available.")
        lines.append("")
        return "\n".join(lines)

    # ── ファイル別カバレッジテーブル ──
    lines.append("| File | Lines | Executed | Coverage |")
    lines.append("|------|-------|----------|----------|")
    for entry in per_file:
        file_display = f"`{_short_path(entry['file'])}`"
        emoji = _coverage_emoji(entry["coverage"])
        lines.append(
            f"| {file_display} "
            f"| {entry['total_lines']} "
            f"| {entry['executed_lines']} "
            f"| {emoji} {entry['coverage']:.1f}% |"
        )

    # ── 全体サマリー ──
    emoji_total = _coverage_emoji(total_coverage)
    lines.append(
        f"| **Total** "
        f"| **{total_lines_count}** "
        f"| **{total_exec_count}** "
        f"| **{emoji_total} {total_coverage:.1f}%** |"
    )
    lines.append("")

    # ── コメント ──
    if total_coverage >= 80:
        lines.append(f"{emoji_total} Overall coverage: **{total_coverage:.1f}%** — Excellent!")
    elif total_coverage >= 50:
        lines.append(f"{emoji_total} Overall coverage: **{total_coverage:.1f}%** — Good, but there is room for improvement.")
    else:
        lines.append(f"{emoji_total} Overall coverage: **{total_coverage:.1f}%** — Needs improvement. Consider adding more tests.")
    lines.append("")

    return "\n".join(lines)


def main() -> int:
    parser = argparse.ArgumentParser(
        description="gcovr JSON → Markdown カバレッジサマリー変換"
    )
    parser.add_argument(
        "--input", "-i",
        type=str,
        required=True,
        help="gcovr の JSON レポートファイルへのパス（必須）"
    )
    args = parser.parse_args()

    json_path = Path(args.input)
    if not json_path.is_absolute():
        json_path = Path.cwd() / json_path

    if not json_path.exists():
        print(f"[gcovr_summary] ERROR: Input JSON file not found: {json_path}",
              file=sys.stderr)
        # エラーでも空の結果を返して CI が止まらないようにする
        stats = {"total_lines": 0, "total_exec": 0, "total_coverage": 0.0, "per_file": []}
    else:
        stats = parse_gcovr_json(json_path)

    markdown = generate_markdown(stats)
    print(markdown)
    return 0


if __name__ == "__main__":
    sys.exit(main())
