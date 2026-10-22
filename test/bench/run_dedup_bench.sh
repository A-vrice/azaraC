#!/usr/bin/env bash
# test/bench/run_dedup_bench.sh — dedup ベンチマークの入口（`make -C test bench-dedup`）。
#
#   primary    : NANOS_PER_OP   scored ストリームの 1 判定あたりの ns
#   gates      : NEW_RECALL (NEW_CORRECT >= 118), DUP_SUPPRESS >= 0.99,
#                NANKAI_KEY_STABLE == 1, PREAMBLE_KEY_STABLE == 1  (違反で非ゼロ終了)
#   reported   : CAPACITY_DISTINCT, SRAM_*_BYTES, ACCURACY_P*, CORPUS_*（表示のみで
#                ゲートしない — 動いたら diff で読む）
#
# scored ストリームは仕様モデルのトラフィック（qzss-specs/アプリケーションノートv2.md
# 原PDF p.23–27）: 同じ情報が複数衛星で中継され、4 秒ごとに再放送され、有効窓の後に
# 繰り返される。ACCURACY 単独は目的ではない: 2238 判定のうち 2200 が "duplicate" を
# 期待するので、「常に重複」と答えるフィルタは全警報を抑止しながら精度由来の指標を
# 制覇してしまう。そこで NEW_RECALL を目的関数に含め
# (DUP_SUPPRESS × NEW_RECALL / NANOS_PER_OP)、ゲートにもする: ベースラインより
# 新規情報の通知が少ない実行は棄却する。
#
# 決定的な入力（test/data/*.json）、固定 LCG シード、ネットワークなし、
# 実時計入力なし。成功時 exit 0、ハーネスやガードレールが失敗すると非ゼロ。

set -uo pipefail

# 下のパスはリポジトリ相対なので、スクリプトが test/bench/ にあり呼び出し側が
# cd していなくても、リポジトリルートから実行する。
cd "$(dirname "$0")/../.."

# ベースラインの NEW_RECALL 数（通知した情報数）— 決定的。改善したら上げる。
MIN_NEW_CORRECT=118

# 速度と引き換えに重複抑止を落としてはならない: テーブルをコミット済み容量より
# 小さくすると（32 スロット x 8 ウェイは 0.9797）NANOS_PER_OP ではなくここに出る。
MIN_DUP_SUPPRESS=0.99

CXX="${CXX:-g++}"
BENCH_DIR="test/bench"
BENCH_BIN="$BENCH_DIR/bench_dedup"
BENCH_OBJ="$BENCH_DIR/bench_dedup.o"

mkdir -p "$BENCH_DIR"

LIBS=(src/Parser.cpp src/decoder/Decoder.cpp src/decoder/DecoderDcx.cpp
      src/decoder/DecoderQzqsm.cpp src/framer/UbxFramer.cpp src/framer/NmeaFramer.cpp
      src/json/JsonWriter.cpp src/json/JsonSerializer.cpp src/json/JsonSerializerDcx.cpp
      src/json/JsonSerializerQzqsm.cpp src/internal/DcxHelper.cpp src/internal/Dedup.cpp)

# ヘッダはライブラリとヘッダオンリーのベンチ対象の両方を駆動するので、最新の
# ヘッダ（src か test — bench_dedup.cpp は test_helpers.h を include する）を
# 全オブジェクトの依存に含める（-MMD の方が厳密だが、依存なしのままにしておく必要がある）。
NEWEST_HEADER="$(ls -t src/*.h src/*/*.h test/*.h test/*/*.h 2>/dev/null | head -1)"
needs_rebuild() {   # $1 = ソース、$2 = オブジェクト
    [[ ! -f "$2" ]] && return 0
    [[ "$1" -nt "$2" ]] && return 0
    [[ -n "$NEWEST_HEADER" && "$NEWEST_HEADER" -nt "$2" ]] && return 0
    # コンパイラもビルド状態の一部: CXX の切り替えでオブジェクトを無効化しないと、
    # CXX=clang++ で再実行しても g++ 製オブジェクトを再リンクするだけになる。
    [[ "$(cat "${2%.o}.cxxid" 2>/dev/null)" != "$CXX" ]] && return 0
    return 1
}

OBJS=()
for src in "${LIBS[@]}"; do
    obj="$BENCH_DIR/$(basename "${src%.cpp}").o"
    OBJS+=("$obj")
    needs_rebuild "$src" "$obj" && {
        "$CXX" -std=c++17 -O2 -I src -I test -DARDUINO=0 -c "$src" -o "$obj" || exit 3
        printf '%s' "$CXX" > "${obj%.o}.cxxid"
    }
done
needs_rebuild test/bench/bench_dedup.cpp "$BENCH_OBJ" && {
    "$CXX" -std=c++17 -O2 -I src -I test -DARDUINO=0 -c test/bench/bench_dedup.cpp -o "$BENCH_OBJ" || exit 3
    printf '%s' "$CXX" > "${BENCH_OBJ%.o}.cxxid"; }
"$CXX" -std=c++17 -O2 "$BENCH_OBJ" "${OBJS[@]}" -o "$BENCH_BIN" || exit 3

OUT="$(./"$BENCH_BIN" 2>&1)"
STATUS=$?
printf '%s\n' "$OUT"
[[ $STATUS -ne 0 ]] && exit $STATUS

metric() { printf '%s\n' "$OUT" | sed -n "s/^METRIC $1=\([-0-9.eE+]*\)\$/\1/p" | tail -1; }

crash="$(metric CRASH_GROUP)"
[[ "${crash:-1}" == "0" ]] || { echo "bench: incomplete run (CRASH_GROUP=${crash:-missing})" >&2; exit 4; }

nanos="$(metric NANOS_PER_OP)"
dup="$(metric DUP_SUPPRESS)"
recall="$(metric NEW_RECALL)"
new_ok="$(metric NEW_CORRECT)"
scored="$(metric DECISIONS_SCORED)"
[[ -n "$nanos" && -n "$dup" && -n "$recall" && -n "$new_ok" && -n "$scored" ]] \
    || { echo "bench: metrics missing" >&2; exit 5; }

# ガードレール: 通知の網羅性が回帰してはいけない。でないとループは速度と引き換えに
# 全警報を喜んで捨てる。
if (( new_ok < MIN_NEW_CORRECT )); then
    echo "bench: NEW_RECALL regressed (NEW_CORRECT=$new_ok < $MIN_NEW_CORRECT, NEW_RECALL=$recall)" >&2
    exit 6
fi

if [[ "$(awk -v d="$dup" -v m="$MIN_DUP_SUPPRESS" 'BEGIN { print (d + 0 < m + 0) ? 1 : 0 }')" == "1" ]]; then
    echo "bench: DUP_SUPPRESS regressed ($dup < $MIN_DUP_SUPPRESS) — capacity must not be traded for speed" >&2
    exit 7
fi

# ガードレール: 2 つの挙動同一性チェックは "stable"（1）を報告すること。鍵が
# 250-bit フレーム全体に広がり直した場合（PREAMBLE_KEY_STABLE: プリアンブルは
# A→B→C と巡回するので、広がった鍵は 1 情報を 3 回通知する）や、南海トラフ事象を
# 完成ページで識別してしまった場合（NANKAI_KEY_STABLE）を捕まえる唯一の手段。
# どちらのバグでも NEW_RECALL と DUP_SUPPRESS は緑のままなので、このゲートがないと
# 回帰が黙って出荷される。
# 1 以外の値には大きく異なる 2 つの原因があり、メッセージも分ける:
#   0        — 鍵が誤り（同一性をデバッグ、手順③: MT～VN）
#   missing  — 指標が出力されていない（ベンチがその検査を実行していない）
#   -1       — フィクスチャが使用不能（例: nankai_vectors.json が 27 ページを失った）
#              — test/data/*.json をデバッグする。ハッシュではない
for name in NANKAI_KEY_STABLE PREAMBLE_KEY_STABLE; do
    got="$(metric "$name")"
    case "${got:-missing}" in
    1) ;;
    0)
        echo "bench: $name regressed (0) — the identity key no longer matches the spec (手順③: MT～VN)" >&2
        exit 8
        ;;
    *)
        echo "bench: $name unusable (${got:-missing}) — fixture problem, not a key regression; check test/data/*.json" >&2
        exit 9
        ;;
    esac
done

# 報告する目的関数: 1 判定あたりのコストに、失った重複抑止のペナルティを掛けたもの。
# NEW_RECALL の定数項は比較で打ち消える。
objective="$(awk -v n="$nanos" -v d="$dup" 'BEGIN { printf "%.6f", (d > 0 ? n / d : 1e18) }')"

echo "bench: ok (NANOS_PER_OP=$nanos DUP_SUPPRESS=$dup NEW_RECALL=$recall OBJECTIVE=$objective)"