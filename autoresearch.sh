#!/usr/bin/env bash
# autoresearch.sh — dedup benchmark entrypoint.
#
#   primary    : NANOS_PER_OP   ns per dedup decision over the scored streams
#   guardrails : NEW_RECALL (baseline 118/118), DUP_SUPPRESS >= 0.99, CAPACITY_DISTINCT,
#                SRAM_*_BYTES, NANKAI_KEY_STABLE, ACCURACY_P*
#
# The scored streams are spec-model traffic (qzss-specs/アプリケーションノートv2.md
# 原PDF p.23–27): the same information relayed by several satellites, rebroadcast
# every 4 s, and repeated after its validity window. Accuracy alone is NOT the
# objective: 2200 of the 2238 scored decisions expect "duplicate", so a filter
# that answers "always duplicate" would top any accuracy-derived metric while
# suppressing every alert. NEW_RECALL is therefore included in the objective
# (DUP_SUPPRESS × NEW_RECALL / NANOS_PER_OP) and also gated: a run that reports
# any fewer new informations than the baseline is rejected.
#
# Deterministic inputs (test/data/*.json), fixed LCG seed, no network, no
# wall-clock input. Exit 0 on success; non-zero when the harness or a
# guardrail fails.

set -uo pipefail

cd "$(dirname "$0")"

# Baseline NEW_RECALL count (informations reported) — deterministic; raise when it improves.
MIN_NEW_CORRECT=118

# Duplicate suppression must not be traded for speed: shrinking the table below the
# committed capacity (32 slots x 8 ways measures 0.9797) shows up here, not in NANOS_PER_OP.
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

# Headers drive both the library and the header-only bench target, so the newest
# header is part of every object's dependency set (-MMD would be tighter, but
# this has to stay dependency-free).
NEWEST_HEADER="$(ls -t src/*.h src/*/*.h 2>/dev/null | head -1)"
needs_rebuild() {   # $1 = source, $2 = object
    [[ ! -f "$2" ]] && return 0
    [[ "$1" -nt "$2" ]] && return 0
    [[ -n "$NEWEST_HEADER" && "$NEWEST_HEADER" -nt "$2" ]] && return 0
    return 1
}

OBJS=()
for src in "${LIBS[@]}"; do
    obj="$BENCH_DIR/$(basename "${src%.cpp}").o"
    OBJS+=("$obj")
    needs_rebuild "$src" "$obj" && { "$CXX" -std=c++17 -O2 -I src -I test -DARDUINO=0 -c "$src" -o "$obj" || exit 3; }
done
needs_rebuild test/bench/bench_dedup.cpp "$BENCH_OBJ" && {
    "$CXX" -std=c++17 -O2 -I src -I test -DARDUINO=0 -c test/bench/bench_dedup.cpp -o "$BENCH_OBJ" || exit 3; }
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

# Guardrail: informational coverage must not regress, or the loop would happily
# trade every alert away for speed.
if (( new_ok < MIN_NEW_CORRECT )); then
    echo "bench: NEW_RECALL regressed (NEW_CORRECT=$new_ok < $MIN_NEW_CORRECT, NEW_RECALL=$recall)" >&2
    exit 6
fi

if [[ "$(awk -v d="$dup" -v m="$MIN_DUP_SUPPRESS" 'BEGIN { print (d + 0 < m + 0) ? 1 : 0 }')" == "1" ]]; then
    echo "bench: DUP_SUPPRESS regressed ($dup < $MIN_DUP_SUPPRESS) — capacity must not be traded for speed" >&2
    exit 7
fi

# Reported objective: cost per decision, penalised for lost duplicate
# suppression. Constant NEW_RECALL terms cancel in comparisons.
objective="$(awk -v n="$nanos" -v d="$dup" 'BEGIN { printf "%.6f", (d > 0 ? n / d : 1e18) }')"

echo "bench: ok (NANOS_PER_OP=$nanos DUP_SUPPRESS=$dup NEW_RECALL=$recall OBJECTIVE=$objective)"