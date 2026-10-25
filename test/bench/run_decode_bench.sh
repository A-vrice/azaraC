#!/usr/bin/env bash
# test/bench/run_decode_bench.sh — decode ベンチマークの入口（`make -C test bench-decode`）。
#
#   primary    : DECODE_CYCLES_<GROUP>   グループ別・1 文あたりサイクル（rdtsc、文内 min-of-15
#                                     のグループ中央値）。フレーミング＋デコード込み。
#   gates      : CRASH_GROUP == 0, DECODE_OUTPUTS > 0, DECODE_GROUPS >= 8,
#                MT43_SEISMIC / MT44 の両グループが存在すること（違反で非ゼロ終了）。
#                サイクル値そのものはゲートしない（回帰追跡は METRIC の diff で行う）。
#
# 決定的な入力（test/data/*.json）、固定 report_unix、ネットワークなし、実時計入力なし。

set -uo pipefail

cd "$(dirname "$0")/../.."

CXX="${CXX:-g++}"
BENCH_DIR="test/bench"
BENCH_BIN="$BENCH_DIR/bench_decode"
BENCH_OBJ="$BENCH_DIR/bench_decode.o"

mkdir -p "$BENCH_DIR"

LIBS=(src/Parser.cpp src/decoder/Decoder.cpp src/decoder/DecoderDcx.cpp
      src/decoder/DecoderQzqsm.cpp src/framer/UbxFramer.cpp src/framer/NmeaFramer.cpp
      src/json/JsonWriter.cpp src/json/JsonSerializer.cpp src/json/JsonSerializerDcx.cpp
      src/json/JsonSerializerQzqsm.cpp src/internal/DcxHelper.cpp src/internal/Dedup.cpp)

NEWEST_HEADER="$(ls -t src/*.h src/*/*.h test/*.h test/*/*.h 2>/dev/null | head -1)"
needs_rebuild() {   # $1 = ソース、$2 = オブジェクト
    [[ ! -f "$2" ]] && return 0
    [[ "$1" -nt "$2" ]] && return 0
    [[ -n "$NEWEST_HEADER" && "$NEWEST_HEADER" -nt "$2" ]] && return 0
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
needs_rebuild test/bench/bench_decode.cpp "$BENCH_OBJ" && {
    "$CXX" -std=c++17 -O2 -I src -I test -DARDUINO=0 -c test/bench/bench_decode.cpp -o "$BENCH_OBJ" || exit 3
    printf '%s' "$CXX" > "${BENCH_OBJ%.o}.cxxid"; }
"$CXX" -std=c++17 -O2 "$BENCH_OBJ" "${OBJS[@]}" -o "$BENCH_BIN" || exit 3

OUT="$(./"$BENCH_BIN" 2>&1)"
STATUS=$?
printf '%s\n' "$OUT"
[[ $STATUS -ne 0 ]] && exit $STATUS

metric() { printf '%s\n' "$OUT" | sed -n "s/^METRIC $1=\([-0-9.eE+]*\)\$/\1/p" | tail -1; }

crash="$(metric CRASH_GROUP)"
[[ "${crash:-1}" == "0" ]] || { echo "bench: incomplete run (CRASH_GROUP=${crash:-missing})" >&2; exit 4; }

outputs="$(metric DECODE_OUTPUTS)"
groups="$(metric DECODE_GROUPS)"
if [[ -z "$outputs" || "$outputs" -le 0 ]]; then
    echo "bench: no decodes emitted (DECODE_OUTPUTS=${outputs:-missing}) — decode path broken?" >&2
    exit 5
fi
if [[ -z "$groups" || "$groups" -lt 8 ]]; then
    echo "bench: too few groups (DECODE_GROUPS=${groups:-missing}) — fixture or scan broken" >&2
    exit 6
fi
for name in DECODE_CYCLES_MT43_SEISMIC DECODE_CYCLES_MT44; do
    [[ -n "$(metric "$name")" ]] || { echo "bench: required metric $name missing" >&2; exit 7; }
done

echo "bench: ok (DECODE_OUTPUTS=$outputs DECODE_GROUPS=$groups)"
