#!/usr/bin/env python3
"""ミューテーションテスト（C++ / doctest 向けの軽量ハーネス）。

mizchi/mutator は TS/JS の AST を書き換えて Vitest/Jest/Playwright を回すツールで、
このリポジトリ（C++17 + doctest）には適用できない。ここでは同じ考え方
（実装を 1 箇所だけ壊し、テストが落ちるかを見る）を、既存の
`make -C test` と g++ だけで実装する。

使い方（リポジトリルートから）:
    python test/scripts/mutation_test.py --list        # 変異の総数を数えるだけ
    python test/scripts/mutation_test.py               # 既定 60 個を実行
    python test/scripts/mutation_test.py --budget 200  # 多めに実行

判定:
    killed    テストが落ちた（テストが変異を検出した）
    survived  テストが通った（テストの隙間）
    invalid   ビルドが通らない変異（スコアから除外）
    no_code_change  その構成では無効化された行への変異で、オブジェクトが変わらない（スコアから除外）

変異はコメント・文字列リテラル・プリプロセッサ行の外側にだけ適用する。
1 回の実行で 1 箇所だけ書き換え、必ず元のバイト列へ戻す（異常終了時も finally /
SIGINT で復元する）。
"""

import argparse
import fnmatch
import hashlib
import json
import random
import re
import signal
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TEST_DIR = ROOT / "test"


class HarnessError(RuntimeError):
    """変異ではなくハーネス（ビルド／実行環境）側の異常。"""

# test/Makefile の LIB_SRCS と同じ並び（ヘッダは対象外: 変更すると依存 .o が
# 大量に再ビルドされ 1 変異あたりのコストが跳ね上がるため）。
LIB_SRCS = [
    "src/Parser.cpp",
    "src/decoder/Decoder.cpp",
    "src/decoder/DecoderDcx.cpp",
    "src/decoder/DecoderQzqsm.cpp",
    "src/framer/UbxFramer.cpp",
    "src/framer/NmeaFramer.cpp",
    "src/json/JsonWriter.cpp",
    "src/json/JsonSerializer.cpp",
    "src/json/JsonSerializerDcx.cpp",
    "src/json/JsonSerializerQzqsm.cpp",
    "src/internal/DcxHelper.cpp",
    "src/internal/Dedup.cpp",
]

# 1 パスで重複なく拾うための複合パターン。多文字演算子を先に置く。
COMBINED = re.compile(
    r"""
      (?P<shl><<)
    | (?P<shr>>>)
    | (?P<le><=)
    | (?P<ge>>=)
    | (?P<eq>==)
    | (?P<ne>!=)
    | (?P<and>&&)
    | (?P<or>\|\|)
    | (?P<arrow>->)
    | (?P<inc>\+\+)
    | (?P<dec>--)
    | (?P<plus_eq>\+=)
    | (?P<minus_eq>-=)
    # 注意: re.VERBOSE ではパターン内の空白が無視される。`(?<= )` は「空白 1 個の後ろ」ではなく
    # 空の後読み（常に真）にコンパイルされ、テンプレート引数の `<...>` や単項 +/- まで拾ってしまう。
    # 空白は文字クラス `[ ]` に入れて有意にする。
    | (?P<lt>(?<=[ ])<(?=[ ]))
    | (?P<gt>(?<=[ ])>(?=[ ]))
    | (?P<plus>(?<=[ ])\+(?=[ ]))
    | (?P<minus>(?<=[ ])-(?=[ ]))
    | (?P<neg>!(?!=))
    | (?P<true>\btrue\b)
    | (?P<false>\bfalse\b)
    | (?P<num>(?<![\w.])[01][uUlL]*(?![\w.]))
    """,
    re.VERBOSE,
)

# 変異させない（今回のスコア対象外の）グループ
SKIP_GROUPS = {"shl", "shr", "arrow", "inc", "dec", "plus_eq", "minus_eq"}

SIMPLE_REPL = {
    "le": "<",
    "ge": ">",
    "eq": "!=",
    "ne": "==",
    "and": "||",
    "or": "&&",
    "lt": "<=",
    "gt": ">=",
    "plus": "-",
    "minus": "+",
    "neg": "",
    "true": "false",
    "false": "true",
}


def replacement_for(group: str, matched: str):
    if group in SKIP_GROUPS:
        return None
    if group == "num":
        body = matched.rstrip("uUlL")
        suffix = matched[len(body):]
        return ("1" if body == "0" else "0") + suffix
    return SIMPLE_REPL.get(group)


def shadow_line(line: str, state: str):
    """コメント・文字列・文字リテラルを空白に置き換えた同じ長さの行を返す。"""
    out = list(line)
    i = 0
    n = len(line)
    while i < n:
        ch = line[i]
        if state == "normal":
            if ch == "/" and i + 1 < n and line[i + 1] == "/":
                for j in range(i, n):
                    if out[j] not in "\r\n":
                        out[j] = " "
                break
            if ch == "/" and i + 1 < n and line[i + 1] == "*":
                state = "block"
                out[i] = " "
                if i + 1 < n:
                    out[i + 1] = " "
                i += 2
                continue
            if ch == '"':
                state = "string"
                out[i] = " "
                i += 1
                continue
            if ch == "'":
                state = "char"
                out[i] = " "
                i += 1
                continue
            i += 1
        elif state == "block":
            out[i] = " "
            if ch == "*" and i + 1 < n and line[i + 1] == "/":
                out[i + 1] = " "
                state = "normal"
                i += 2
                continue
            i += 1
        else:  # string / char
            out[i] = " "
            if ch == "\\":
                if i + 1 < n:
                    out[i + 1] = " "
                    i += 2
                    continue
                i += 1
                continue
            if (state == "string" and ch == '"') or (state == "char" and ch == "'"):
                state = "normal"
            i += 1
    # 行末で閉じていない文字列は次の行へ持ち越さない（行継続は稀で、
    # 持ち越すとファイル残り全体がマスクされて変異が消えるため）。
    if state in ("string", "char"):
        state = "normal"
    return "".join(out), state


def shadow_text(text: str) -> str:
    """行をまたぐコメント／文字列の状態を保ったまま、全体をマスクする。"""
    state = "normal"
    out = []
    for line in text.splitlines(keepends=True):
        shadow, state = shadow_line(line, state)
        out.append(shadow)
    return "".join(out)


CAST_START = re.compile(r"\b(?:reinterpret|static|const|dynamic)_cast\s*<")
STATIC_ASSERT_START = re.compile(r"\bstatic_assert\s*\(")


def mask_span(chars, start: int, end: int) -> None:
    """[start, end) を空白にする（改行は残す: 行番号と桁位置を保存するため）。"""
    for i in range(start, min(end, len(chars))):
        if chars[i] not in "\r\n":
            chars[i] = " "


def mask_non_code_regions(shadow: str) -> str:
    """コードでない領域を空白化して、比較演算子の誤認を防ぐ。

    - `reinterpret_cast<const uint8_t*>` の閉じ `>` は比較演算子ではない
      （`>` -> `>=` の変異がコンパイルエラーになるだけだった）。
    - `static_assert(...)` はコンパイル時のアサーション（テスト側の表明）なので、
      変異させると「コンパイルエラー」にしかならず、テストの検出力を測れない。
    """
    chars = list(shadow)
    # static_assert(...): 括弧の対応を数えて引数全体を潰す。
    for m in STATIC_ASSERT_START.finditer(shadow):
        depth = 0
        i = m.end() - 1
        while i < len(shadow):
            ch = shadow[i]
            if ch == "(":
                depth += 1
            elif ch == ")":
                depth -= 1
                if depth == 0:
                    break
            i += 1
        mask_span(chars, m.start(), i + 1)
    # *_cast<...>: 山括弧の対応を数える（`A<B<C>>` のネストにも耐える）。
    for m in CAST_START.finditer(shadow):
        depth = 0
        lt = m.end() - 1
        i = lt
        closed = False
        while i < len(shadow):
            ch = shadow[i]
            if ch == "<":
                depth += 1
            elif ch == ">":
                depth -= 1
                if depth == 0:
                    closed = True
                    break
            i += 1
        if closed:
            mask_span(chars, lt, i + 1)
    return "".join(chars)


def compute_sites(text: str):
    lines = text.splitlines(keepends=True)
    shadow_lines = mask_non_code_regions(shadow_text(text)).splitlines(keepends=True)
    sites = []
    for idx, line in enumerate(lines):
        shadow = shadow_lines[idx] if idx < len(shadow_lines) else line
        if line.lstrip().startswith("#"):
            continue  # プリプロセッサ行（#include / #if / #define）は対象外
        for m in COMBINED.finditer(shadow):
            group = m.lastgroup
            repl = replacement_for(group, m.group(0))
            if repl is None or repl == m.group(0):
                continue
            sites.append(
                {
                    "line": idx + 1,
                    "col": m.start(),
                    "length": m.end() - m.start(),
                    "from": m.group(0),
                    "to": repl,
                    "operator": group,
                    "context": line.rstrip("\r\n").strip(),
                }
            )
    return lines, sites


BACKUP_SUFFIX = ".mutation_backup"


def backup_path(path: Path) -> Path:
    return path.with_name(path.name + BACKUP_SUFFIX)


def recover_stale_backup(path: Path) -> bool:
    """前回が強制終了されて残ったバックアップを復元する。"""
    bp = backup_path(path)
    if not bp.exists():
        return False
    write_text(path, read_text(bp))
    bp.unlink()
    return True


def read_text(path: Path) -> str:
    with open(path, "r", encoding="utf-8", newline="") as f:
        return f.read()


def write_text(path: Path, text: str) -> None:
    with open(path, "w", encoding="utf-8", newline="") as f:
        f.write(text)


def apply_site(lines, site):
    mutated = list(lines)
    line = mutated[site["line"] - 1]
    start, end = site["col"], site["col"] + site["length"]
    mutated[site["line"] - 1] = line[:start] + site["to"] + line[end:]
    return "".join(mutated)


def run(cmd, timeout, cwd):
    started = time.time()
    try:
        proc = subprocess.run(
            cmd,
            cwd=str(cwd),
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            timeout=timeout,
        )
        return proc.returncode, proc.stdout.decode("utf-8", "replace"), time.time() - started
    except subprocess.TimeoutExpired as exc:
        out = (exc.output or b"").decode("utf-8", "replace")
        return None, out, time.time() - started


def find_test_binary() -> Path:
    for name in ("run_tests.exe", "run_tests"):
        candidate = TEST_DIR / name
        if candidate.exists():
            return candidate
    raise SystemExit("テストバイナリが見つかりません。先に `make -C test all` を実行してください。")


def object_path_for(rel: str) -> Path:
    """test/Makefile は LIB_OBJS を notdir で test/ 直下に置く。"""
    return TEST_DIR / (Path(rel).stem + ".o")


def invalidate_object(rel: str) -> None:
    """変異を確実にコンパイルさせる。

    MinGW の make はタイムスタンプを秒精度で比較することがあり、直前に書いた
    ソースを「新しい」と判定しない場合がある。その場合テストは変異前のバイナリで
    走り、検出漏れ（false SURVIVED）として記録されてしまう。"""
    obj = object_path_for(rel)
    if obj.exists():
        obj.unlink()


def build(timeout, static_link):
    cmd = ["make", "-C", "test", "AZARAC_LOCK_HELD=1"]
    if static_link:
        # MinGW の動的リンクは 0xC0000139 (ENTRYPOINT_NOT_FOUND) で起動しないことがある。
        # test/Makefile の STATIC=1 がその既定の回避策。
        cmd.append("STATIC=1")
    cmd.append("all")
    return run(cmd, timeout, ROOT)


def run_tests(timeout):
    binary = find_test_binary()
    return run([str(binary)], timeout, TEST_DIR)


def suite_ran(output: str) -> bool:
    """テスト本体が実際に動いたか。起動失敗（DLL 不整合など）を「検出」と誤認しないため。"""
    return "[doctest]" in output


# 実行ファイルがロードできなかった場合の終了コード（Windows）。
# 0xC0000139 ENTRYPOINT_NOT_FOUND / 0xC0000135 DLL_NOT_FOUND / 0xC000007B BAD_IMAGE
LOAD_ERROR_CODES = {0xC0000139, 0xC0000135, 0xC000007B}


def is_load_error(rc) -> bool:
    return rc is not None and (rc & 0xFFFFFFFF) in LOAD_ERROR_CODES


def exit_note(rc) -> str:
    if rc is None:
        return "timeout"
    return f"exit {rc} (0x{rc & 0xFFFFFFFF:08X})"


def relevant_output(output: str, limit: int = 4):
    """失敗の手がかりになる行だけ抜き出す。"""
    picked = []
    for line in output.splitlines():
        if re.search(r"ERROR|FATAL|error:|test cases:", line):
            picked.append(line.strip())
    if not picked:
        picked = [l.strip() for l in output.splitlines() if l.strip()][-limit:]
    return picked[-limit:]


def main() -> int:
    ap = argparse.ArgumentParser(description="C++ (doctest) ミューテーションテスト")
    ap.add_argument("--budget", type=int, default=60, help="実行する変異の数（既定 60）")
    ap.add_argument("--seed", type=int, default=20261119, help="抽選シード")
    ap.add_argument("--list", action="store_true", help="変異を数えるだけで実行しない")
    ap.add_argument("--build-timeout", type=float, default=180.0)
    ap.add_argument(
        "--test-timeout",
        type=float,
        default=120.0,
        help="1 変異あたりのテスト実行上限（既定 120 秒。ハング変異のコストを抑える）",
    )
    ap.add_argument(
        "--files",
        nargs="*",
        default=None,
        help="対象を絞る（部分文字列または glob。例: --files src/json/JsonWriter.cpp）",
    )
    ap.add_argument("--json", default="test/mutation_report.json", help="レポート出力先")
    ap.add_argument(
        "--link",
        choices=["auto", "static", "dynamic"],
        default="auto",
        help="テストバイナリのリンク方法（auto: Windows では static）",
    )
    ap.add_argument("--quiet", action="store_true")
    args = ap.parse_args()
    for stream in (sys.stdout, sys.stderr):
        try:
            stream.reconfigure(encoding="utf-8")
        except (AttributeError, ValueError):
            pass
    static_link = args.link == "static" or (args.link == "auto" and sys.platform.startswith("win"))

    # 前回の強制終了で残った変異を先に戻す（変異を読む前に必ず行う）。
    for rel in LIB_SRCS:
        path = ROOT / rel
        if path.exists() and recover_stale_backup(path):
            print(f"recovered stale mutant: {rel}", file=sys.stderr)

    selected = [
        rel
        for rel in LIB_SRCS
        if not args.files
        or any(fnmatch.fnmatch(rel, pat) or pat in rel for pat in args.files)
    ]
    if not selected:
        print("--files に一致するソースがありません。", file=sys.stderr)
        return 2

    corpora = {}
    total_sites = 0
    for rel in selected:
        path = ROOT / rel
        if not path.exists():
            print(f"skip (not found): {rel}", file=sys.stderr)
            continue
        lines, sites = compute_sites(read_text(path))
        corpora[rel] = {"lines": lines, "sites": sites}
        total_sites += len(sites)

    if args.list:
        by_op = {}
        print(f"{'file':38} {'mutants':>8}  ops")
        for rel, data in corpora.items():
            ops = {}
            for s in data["sites"]:
                ops[s["operator"]] = ops.get(s["operator"], 0) + 1
                by_op[s["operator"]] = by_op.get(s["operator"], 0) + 1
            summary = " ".join(f"{k}:{v}" for k, v in sorted(ops.items()))
            print(f"{rel:38} {len(data['sites']):8}  {summary}")
        print(f"{'TOTAL':38} {total_sites:8}")
        print("by operator: " + " ".join(f"{k}:{v}" for k, v in sorted(by_op.items())))
        return 0

    if total_sites == 0:
        print("変異箇所が見つかりませんでした。", file=sys.stderr)
        return 2

    # ベースライン（変異なし）が緑でなければスコアに意味がない。
    if not args.quiet:
        print("baseline: building and running the unmutated suite ...")
    for rel in corpora:
        invalidate_object(rel)
    rc, out, elapsed = build(args.build_timeout, static_link)
    if rc != 0:
        print("baseline build failed:\n" + "\n".join(relevant_output(out)), file=sys.stderr)
        return 2
    rc, out, test_elapsed = run_tests(args.test_timeout)
    if rc != 0:
        print("baseline tests failed:\n" + "\n".join(relevant_output(out)), file=sys.stderr)
        return 2
    if not suite_ran(out):
        print(
            "baseline: テストバイナリが起動していません（出力に [doctest] がありません）。"
            "MinGW では `--link static` を試してください。",
            file=sys.stderr,
        )
        return 2
    if not args.quiet:
        print(f"baseline: green ({elapsed + test_elapsed:.1f}s)")

    # 変異がそのビルド構成で実際にコードへ現れたかを判定するための基準。
    # `#if` で無効化された行への変異はオブジェクトが 1 バイトも変わらないため、
    # テストの隙間（survived）ではなく no_code_change として除外する。
    baseline_objects = {}
    for rel in corpora:
        obj = object_path_for(rel)
        if obj.exists():
            baseline_objects[rel] = hashlib.sha256(obj.read_bytes()).hexdigest()

    # ファイルごとにシャッフルし、ファイルを巡回しながら予算まで採用する。
    rng = random.Random(args.seed)
    queues = {rel: rng.sample(data["sites"], len(data["sites"])) for rel, data in corpora.items()}
    order = []
    files = sorted(queues)
    while len(order) < args.budget and any(queues[f] for f in files):
        for rel in files:
            if not queues[rel]:
                continue
            order.append((rel, queues[rel].pop()))
            if len(order) >= args.budget:
                break

    results = []
    interrupted = {"flag": False}
    current = {"path": None, "original": None}

    def restore():
        if current["path"] is not None and current["original"] is not None:
            write_text(current["path"], current["original"])
            backup_path(current["path"]).unlink(missing_ok=True)
            current["path"] = None
            current["original"] = None

    def on_sigint(signum, frame):
        interrupted["flag"] = True
        restore()
        print("\ninterrupted: source restored.", file=sys.stderr)
        sys.exit(130)

    signal.signal(signal.SIGINT, on_sigint)
    for name in ("SIGTERM", "SIGBREAK", "SIGHUP"):
        sig = getattr(signal, name, None)
        if sig is not None:
            try:
                signal.signal(sig, on_sigint)
            except (OSError, ValueError):
                pass
    try:
        for i, (rel, site) in enumerate(order, 1):
            path = ROOT / rel
            original = read_text(path)
            current["path"], current["original"] = path, original
            # 電源断や強制終了でも次回起動時に戻せるよう、元の内容を先に退避する。
            write_text(backup_path(path), original)
            write_text(path, apply_site(corpora[rel]["lines"], site))
            build_sec, test_sec = 0.0, 0.0
            try:
                invalidate_object(rel)
                rc, build_out, build_sec = build(args.build_timeout, static_link)
                if rc is None:
                    status, detail = "invalid", ["build timeout"]
                elif rc != 0:
                    status, detail = "invalid", relevant_output(build_out)
                else:
                    obj = object_path_for(rel)
                    digest = hashlib.sha256(obj.read_bytes()).hexdigest() if obj.exists() else None
                    if digest is not None and digest == baseline_objects.get(rel):
                        # その構成では無効化されている行への変異（テストでは殺せない）。
                        status, detail = "no_code_change", ["mutated object identical to baseline"]
                    else:
                        rc, test_out, test_sec = run_tests(args.test_timeout)
                        detail = relevant_output(test_out)
                        if rc is None:
                            status = "killed"  # ハング = 検出とみなす
                            detail = ["test timeout"]
                        elif is_load_error(rc):
                            # 実行ファイルがロードできない = ハーネス側の問題。検出として数えない。
                            raise HarnessError(
                                f"{rel}:{site['line']}: テストバイナリが起動していません "
                                f"({exit_note(rc)})。--link static を試してください。"
                            )
                        elif rc != 0:
                            # テスト失敗もクラッシュ（例: 0xC0000005）も検出とみなす。
                            status = "killed"
                            detail = (detail + [exit_note(rc)])[-4:]
                        else:
                            status = "survived"
            finally:
                write_text(path, original)
                backup_path(path).unlink(missing_ok=True)
                current["path"], current["original"] = None, None

            entry = {
                "file": rel,
                "line": site["line"],
                "operator": site["operator"],
                "from": site["from"],
                "to": site["to"],
                "context": site["context"],
                "status": status,
                "detail": detail[:4],
                "seconds": round(build_sec + (test_sec or 0.0), 2),
            }
            results.append(entry)
            if not args.quiet:
                mark = {
                    "killed": "KILLED  ",
                    "survived": "SURVIVED",
                    "invalid": "INVALID ",
                    "no_code_change": "NOCODE  ",
                }[status]
                print(
                    f"[{i:3}/{len(order)}] {mark} {rel}:{site['line']}  "
                    f"{site['from']!r} -> {site['to']!r}  ({entry['seconds']:.1f}s)",
                    flush=True,
                )
                if status == "survived":
                    print(f"           {site['context']}", flush=True)
    except HarnessError as exc:
        print(f"\nharness error: {exc}", file=sys.stderr)
        return 2
    finally:
        restore()

    killed = sum(1 for r in results if r["status"] == "killed")
    survived = sum(1 for r in results if r["status"] == "survived")
    invalid = sum(1 for r in results if r["status"] == "invalid")
    no_code_change = sum(1 for r in results if r["status"] == "no_code_change")
    valid = killed + survived
    score = (killed / valid * 100.0) if valid else 0.0

    report = {
        "tool": "test/scripts/mutation_test.py",
        "seed": args.seed,
        "budget": args.budget,
        "files": args.files,
        "total_sites_available": total_sites,
        "executed": len(results),
        "killed": killed,
        "survived": survived,
        "invalid": invalid,
        "no_code_change": no_code_change,
        "mutation_score_percent": round(score, 1),
        "survived_mutants": [r for r in results if r["status"] == "survived"],
        "no_code_change_mutants": [r for r in results if r["status"] == "no_code_change"],
        "results": results,
    }
    out_path = ROOT / args.json
    with open(out_path, "w", encoding="utf-8", newline="\n") as f:
        json.dump(report, f, ensure_ascii=False, indent=2)

    print()
    print(f"executed      : {len(results)} / {total_sites} available mutants")
    print(f"killed        : {killed}")
    print(f"survived      : {survived}")
    print(f"invalid       : {invalid} (compile error, excluded from score)")
    print(f"no_code_change: {no_code_change} (inactive under this build config, excluded from score)")
    print(f"mutation score: {score:.1f}%  (killed / (killed + survived))")
    if survived:
        print("\nsurvived mutants (gaps in the suite):")
        for r in results:
            if r["status"] == "survived":
                print(f"  {r['file']}:{r['line']}  {r['from']!r} -> {r['to']!r}   {r['context']}")
    if no_code_change:
        print("\nno_code_change mutants (the mutated line is inactive in this configuration):")
        for r in results:
            if r["status"] == "no_code_change":
                print(f"  {r['file']}:{r['line']}  {r['from']!r} -> {r['to']!r}   {r['context']}")
    print(f"\nreport: {out_path.relative_to(ROOT)}")

    # 最後に元のソースで作り直し、緑に戻ったことを確認する。
    print("\nrestore check: rebuilding with the original source ...")
    for rel in corpora:
        invalidate_object(rel)
    rc, out, _ = build(args.build_timeout, static_link)
    if rc != 0:
        print("restore build FAILED:\n" + "\n".join(relevant_output(out)), file=sys.stderr)
        return 1
    rc, out, _ = run_tests(args.test_timeout)
    if rc != 0 or not suite_ran(out):
        print("restore tests FAILED:\n" + "\n".join(relevant_output(out)), file=sys.stderr)
        return 1
    print("restore check: green (source tree unchanged, tests pass)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
