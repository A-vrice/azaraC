#!/usr/bin/env bash
# autoresearch.sh — AVR definition-table footprint benchmark.
#
# Goal (issue #35): the generated target-area string pools repeat parent region names, so one pool costs ~63 KB on the English side alone.
# On AVR that is not just expensive, it is unbuildable: avr-gcc rejects any single object above 32,767 bytes ("size of variable is too large"; verified — 32,767 compiles, 32,768 does not), which is why the AVR preset in azaraC_config.h leaves DCX/CAMF (and the volcano/ash-fall families) off entirely.
#
# Primary metric   AVR_TABLE_BYTES — every byte the enabled configuration asks the
#                  AVR linker for: the string literals of the definition tables (the
#                  pools plus the `switch` tables' per-case literals) and the entry
#                  arrays, measured from `avr-gcc -E` output. Stage 3 cross-checks it
#                  against avr-gcc's own object sizes, which keeps struct layout honest.
# Reported         AVR_STRING_BYTES (the issue's "63 KB pool" number),
#                  AVR_ENTRY_BYTES/ROWS/ROW_BYTES, AVR_LARGEST_LITERAL, the four
#                  large pools, UNO_*/MEGA_* sizes of two real linked images,
#                  AVR_TABLES_IN_RAM, MEGA_DCX_TABLES, MEGA_FAR_OPS, AVR_COMPILE_OK,
#                  AVR_TABLE_CROSSCHECK, FLASH_BUF_OK, MEGA_NEAR_SYM_ADDR/MEGA_CORE_PGM_ADDR
#                  (the near-Flash tables read through a 16-bit pointer must stay in the window).
#
# Gates (non-zero exit)
#   labels    every id of every table must render byte-identical labels in all three
#             modes (AVR far Flash, AVR 16-bit progmem, host) against the golden
#             hashes in test/bench/avr/labels.golden.
#   buffer    AZARAC_FLASH_BUF_SIZE (src/azaraC_config.h) must hold the longest label
#             of every enabled category: internal/FlashString.h clamps the copy at
#             size - 1, so a category missing from the size chain would truncate its
#             labels silently (check_flash_buf.py sweeps all combinations, both
#             languages, both presets).
#   build     every TU must compile for ATmega2560 with all categories enabled *once*
#             no single pool is over the per-object limit. While a pool is oversized
#             the failure is the expected baseline, reported but not gated — that is
#             the bug this metric fixes.
#   crosscheck the primary metric must equal what avr-gcc reports for the symbols it placed.
#   uno       the default AVR configuration must still compile and link.
#   mega      the DCX/CAMF configuration (opted in, as on a 256 KB part) must still compile
#             and link, enable the DCX/CAMF tables, keep every table in Flash and use far
#             Flash reads (elpm/RAMPZ) — without them the tables above 64 KB would garble.
#             The tables read through the *near* 16-bit pointer (CRC24Q, radius, B4 layout)
#             must stay below 0xFFFF, or those reads return garbage in silence.
#   ram       SRAM must not grow (UNO_RAM_BYTES and MEGA_RAM_BYTES <= baseline) and no table
#             may live in RAM instead of Flash: shrinking Flash by spending SRAM is a loss, and
#             the AVR path can only join labels in the shared 800 B buffer it already owns.
#   mega-lto  the same DCX/CAMF configuration under the Arduino recipe (-flto, the build a Mega
#             sketch really gets) must link and fit the ATmega2560's SRAM.
#   path      every linked image must still hold the decode path, the serializer and the
#             definition tables: if LTO ever drops them, the flash numbers stop meaning
#             "what a sketch pays".
#
# Deterministic: fixed toolchain flags, locked inputs, no network, no clock; requires avr-gcc/avr-size/avr-nm and g++ on PATH.
# The Uno image links with the Arduino AVR core's `-flto -fuse-linker-plugin` (AVR_LTO). The Mega image links LTO-free in stage 5 and with the Arduino recipe in stage 5b; stage 5b's image is gated (it must link and fit the part's SRAM).
#
# `bash test/bench/avr/autoresearch.sh --bless-labels` re-records the golden label hashes — only after confirming the label change was intended.

set -uo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR/../../.."

BENCH="test/bench/avr"
OUT="$BENCH/out"
MCU=atmega2560
UNO_MCU=atmega328p

AVR_CC="${AVR_CC:-avr-gcc}"
AVR_SIZE="${AVR_SIZE:-avr-size}"
AVR_NM="${AVR_NM:-avr-nm}"
AVR_OBJDUMP="${AVR_OBJDUMP:-avr-objdump}"
HOST_CXX="${HOST_CXX:-g++}"
PYTHON="${PYTHON:-python}"
command -v "$PYTHON" >/dev/null 2>&1 || PYTHON=python3

# Recipe for the Arduino-core stand-in (see $BENCH/shim/Arduino.h): ARDUINO=1 makes azaraC.h include <Print.h> and TimeFields.h use millis(), as in a real AVR build.
AVR_BUILD=(-mmcu="$MCU" -Os -std=gnu++17 -fno-exceptions
           -ffunction-sections -fdata-sections -Werror=overflow
           -I src -I "$BENCH/shim" -DARDUINO=1)

# The Arduino AVR core compiles and links with `-flto -fuse-linker-plugin` (platform.txt), so stage 4's Uno image — the configuration a sketch actually ships — uses them too.
# Stage 3 keeps its own LTO-free recipe on purpose: an LTO object carries no sizes for symbols, which would leave nothing for the avr-gcc crosscheck to compare against.
# Stage 5 stays LTO-free for a different reason; see the note there.
AVR_LTO=(-flto -fuse-linker-plugin)

# Worst case for the tables: every category, both languages.
CATS=(-DAZARAC_LANG_JA=1 -DAZARAC_LANG_EN=1
      -DAZARAC_ENABLE_EEW=1 -DAZARAC_ENABLE_HYPOCENTER=1 -DAZARAC_ENABLE_SEISMIC=1
      -DAZARAC_ENABLE_NANKAI=1 -DAZARAC_ENABLE_TSUNAMI=1 -DAZARAC_ENABLE_NW_PAC_TSUNAMI=1
      -DAZARAC_ENABLE_VOLCANO=1 -DAZARAC_ENABLE_ASH_FALL=1 -DAZARAC_ENABLE_WEATHER=1
      -DAZARAC_ENABLE_FLOOD=1 -DAZARAC_ENABLE_TYPHOON=1 -DAZARAC_ENABLE_MARINE=1
      -DAZARAC_ENABLE_DCX_CAMF=1)

# avr-gcc per-object ceiling: 2**15 is the compiler's limit.
MAX_OBJECT_BYTES=32768

# The AVR path trades Flash for RAM only within the SRAM it already owns (the shared 800 B label buffer in internal/FlashString.h); growing SRAM to shrink Flash is a loss, so the linked Uno image's RAM is gated.
# Measured 702 B (data 626 + bss 76) at the pre-compression baseline, 640 B before the JSON keys moved to Flash, 204 B once they did (data 88 + bss 116), 146 B now (data 30 + bss 116): the keys and the helper tables left .data (avr-libc's script copies .rodata into SRAM) and the 40 B of new bss is the shared key buffer (AZARAC_KEY_BUF_SIZE), for +730 B of Flash (13,546 → 14,276).
# The last 58 B are the fixed strings that left .data: "QZQSM," (7) from NmeaFramer plus the JSON values arrival_estimated (18), no_information (15) and unrecognized_code (18), which now go through AZARAC_KEY; .data is down to the allocator's globals and the two framer vtables, for +194 B of Flash (14,276 → 14,470). ("null" cost nothing even before: the seven call sites measured byte-identical.)
# The probe's opaque sink (the write() that keeps the serialize path in the image) adds 132 B on top: 14,602 B.
MAX_UNO_RAM_BYTES=146

# The same ceiling for stage 5's DCX/CAMF image: measured 3,714 B (data 2,902 + bss 812) of the Mega's 8,192 B — the keys alone were ~1.8 KB of it — and 1,086 B once they moved (data 234 + bss 852) for +1,712 B of Flash (144,806 → 146,518), so the tables may cost Flash but never SRAM.
# The +40 B of bss is the shared key buffer the Flash keys are copied through.
# 896 B now (data 44 + bss 852): the DCX value literals (invalid_mt44, NULL/L_ALERT/J_ALERT/LOCAL_GOV/OUTSIDE_JAPAN/UNKNOWN, unsupported_*) left .data the same way, for +154 B of Flash (146,518 → 146,672). The probe's opaque sink adds 20 B: 146,692 B.
# The ceiling keeps no slack: 896 B is the current measurement, so any SRAM regression fails here (growing SRAM to shrink Flash is the failure this exists for).
MAX_MEGA_RAM_BYTES=896

# The part's SRAM, for the image a sketch really gets (stage 5b, the Arduino recipe): the LTO
# build must link and fit the ATmega2560, or the configuration is not shippable at all.
ATMEGA2560_SRAM_BYTES=8192

mkdir -p "$OUT"

# stage 1
# The enabled tables, as the AVR preprocessor sees them.
"$AVR_CC" -E -x c++ -std=gnu++17 -mmcu="$MCU" -DARDUINO=1 \
    -I src -I "$BENCH/shim" "${CATS[@]}" "$BENCH/tables.cpp" -o "$OUT/tables.i" \
    || { echo "autoresearch: preprocessing failed" >&2; exit 3; }
"$PYTHON" "$BENCH/measure_tables.py" "$OUT/tables.i" "$OUT/pools.txt" | tee "$OUT/metrics.txt" \
    || { echo "autoresearch: measure_tables.py failed" >&2; exit 3; }

metric() { sed -n "s/^METRIC $1=\([-0-9.eE+]*\)\$/\1/p" "$OUT/metrics.txt" | tail -1; }

table_bytes="$(metric AVR_TABLE_BYTES)"
string_bytes="$(metric AVR_STRING_BYTES)"
entry_bytes="$(metric AVR_ENTRY_BYTES)"
entry_rows="$(metric AVR_ENTRY_ROWS)"
largest="$(metric AVR_LARGEST_LITERAL)"
[[ -n "$table_bytes" && -n "$string_bytes" && -n "$entry_bytes" && -n "$largest" ]] \
    || { echo "autoresearch: metrics missing" >&2; exit 3; }

# stage 1b
# The shared label buffer must hold the longest label of every enabled category: internal/FlashString.h clamps the copy at AZARAC_FLASH_BUF_SIZE - 1, so a category the size chain misses would truncate its labels silently (mid-UTF-8).
# Swept over every category combination, both languages, both presets; the size chain is read from azaraC_config.h and cross-checked against the AVR preprocessor.
buf_status=0
"$PYTHON" "$BENCH/check_flash_buf.py" --avr-gcc "$AVR_CC" || buf_status=$?
echo "METRIC FLASH_BUF_OK=$(( buf_status == 0 ? 1 : 0 ))"

# stage 2
# Label equivalence: the AVR branch (PROGMEM string views) and the host branch must keep rendering the labels they rendered at the baseline.
"$PYTHON" "$BENCH/gen_label_dump.py" "$OUT/dump_labels.cpp" || exit 4
GOLDEN="$BENCH/labels.golden"

run_dump() {   # $1 = binary; prints "<hash> <calls> <labels>"
    "$1" | sed -n 's/^LABELHASH \([0-9a-f]*\) calls=\([0-9]*\) labels=\([0-9]*\)$/\1 \2 \3/p'
}
build_dump() {  # $1 = label, rest = extra flags
    local label="$1"; shift
    "$HOST_CXX" -std=c++17 -O1 -I src -DARDUINO=0 "$@" "${CATS[@]}" \
        "$OUT/dump_labels.cpp" -o "$OUT/dump_$label" || return 1
}

build_dump avr -I test/stub -D__AVR__ -DAZARAC_AVR_STUB \
    || { echo "autoresearch: AVR label dump did not build" >&2; exit 4; }
# The same tables through the other addressing mode: parts with <= 64 KiB of Flash (the Uno) use 16-bit progmem pointers, larger ones the far accessors.
# The stub stands in for a large part by default, so pin FLASHEND down for this build.
build_dump avr_short -I test/stub -D__AVR__ -DAZARAC_AVR_STUB -DFLASHEND=0x7FFF \
    || { echo "autoresearch: short-Flash AVR label dump did not build" >&2; exit 4; }
build_dump host || { echo "autoresearch: host label dump did not build" >&2; exit 4; }

avr_labels="$(run_dump "$OUT/dump_avr")"
avr_short_labels="$(run_dump "$OUT/dump_avr_short")"
host_labels="$(run_dump "$OUT/dump_host")"
[[ -n "$avr_labels" && -n "$avr_short_labels" && -n "$host_labels" ]] \
    || { echo "autoresearch: label dump produced no hash" >&2; exit 4; }

if [[ "${1:-}" == "--bless-labels" ]]; then
    {
        echo "# Definition-label hashes: <hash> <lookups> <labels>. Re-record with"
        echo "#   bash autoresearch.sh --bless-labels"
        echo "AVR $avr_labels"
        echo "HOST $host_labels"
    } > "$GOLDEN"
    echo "autoresearch: blessed $GOLDEN"
fi

label_status=0
if [[ ! -f "$GOLDEN" ]]; then
    echo "autoresearch: $GOLDEN missing — run 'bash autoresearch.sh --bless-labels'" >&2
    label_status=1
else
    # AVR_SHORT uses 16-bit progmem pointers; it is compared against the AVR golden.
    for path in AVR AVR_SHORT HOST; do
        want="$(sed -n "s/^${path%%_SHORT} //p" "$GOLDEN")"
        case "$path" in
            AVR)       have="$avr_labels"; bin="$OUT/dump_avr" ;;
            AVR_SHORT) have="$avr_short_labels"; bin="$OUT/dump_avr_short" ;;
            HOST)      have="$host_labels"; bin="$OUT/dump_host" ;;
        esac
        if [[ "$want" != "$have" ]]; then
            echo "autoresearch: $path labels changed: golden='$want' now='$have'" >&2
            "$bin" dump > "$OUT/labels_$path.txt" 2>/dev/null
            echo "autoresearch: full dump written to $OUT/labels_$path.txt" >&2
            label_status=1
        fi
    done
    echo "METRIC LABELS_AVR_CALLS=$(printf '%s' "$avr_labels" | cut -d' ' -f2)"
    echo "METRIC LABELS_AVR_STRINGS=$(printf '%s' "$avr_labels" | cut -d' ' -f3)"
    echo "METRIC LABELS_AVR_SHORT_MATCH=$([[ "$avr_short_labels" == "$avr_labels" ]] && echo 1 || echo 0)"
fi

# stage 3
# Every TU must compile for the real target once no pool exceeds the per-object ceiling; below it the build is the gate, above it failure is the expected baseline.
rm -rf "$OUT/obj"
mkdir -p "$OUT/obj"
build_failed=0
for src in src/*.cpp src/*/*.cpp; do
    obj="$OUT/obj/$(echo "$src" | tr '/' '_').o"
    "$AVR_CC" "${AVR_BUILD[@]}" "${CATS[@]}" -c "$src" -o "$obj" || build_failed=1
done
build_ok=$((1 - build_failed))
echo "METRIC AVR_COMPILE_OK=$build_ok"

# The primary metric is only honest if it agrees with the sizes avr-gcc reports for the symbols it actually placed.
if [[ -f "$OUT/pools.txt" ]]; then
    cross="$("$AVR_NM" --print-size --radix=d -C "$OUT"/obj/*.o 2>/dev/null | tr -d '\r' \
        | "$PYTHON" "$BENCH/crosscheck_tables.py" "$OUT/pools.txt")"
    echo "$cross"
    cross_checked="$(printf '%s\n' "$cross" | sed -n 's/.*CROSSCHECK=[0-9]*\/\([0-9]*\).*/\1/p')"
    cross_matched="$(printf '%s\n' "$cross" | sed -n 's/.*CROSSCHECK=\([0-9]*\)\/.*/\1/p')"
fi

# stage 4
# The configuration the library actually ships for AVR (preset: seismic and tsunami only, Japanese labels); it must stay buildable and small.
uno_ok=0
uno_flash=""
uno_build=(-mmcu="$UNO_MCU" -Os -std=gnu++17 -fno-exceptions "${AVR_LTO[@]}"
           -ffunction-sections -fdata-sections -Wl,--gc-sections -Werror=overflow
           -I src -I "$BENCH/shim" -DARDUINO=1)
uno_objs=()
rm -rf "$OUT/obj_uno"
mkdir -p "$OUT/obj_uno"
for src in src/*.cpp src/*/*.cpp "$BENCH/probe.cpp"; do
    obj="$OUT/obj_uno/$(echo "$src" | tr '/' '_').o"
    if "$AVR_CC" "${uno_build[@]}" -c "$src" -o "$obj"; then
        uno_objs+=("$obj")
    else
        uno_objs=()
        break
    fi
done
if [[ ${#uno_objs[@]} -gt 0 ]] && "$AVR_CC" "${uno_build[@]}" "${uno_objs[@]}" -o "$OUT/uno.elf"; then
    uno_ok=1
    uno_flash="$("$AVR_SIZE" "$OUT/uno.elf" | awk 'NR == 2 { print $1 + $2 }')"
    uno_ram="$("$AVR_SIZE" "$OUT/uno.elf" | awk 'NR == 2 { print $2 + $3 }')"
    # A definition table in .data/.bss is no longer in Flash: all must be PROGMEM.
    tables_in_ram="$("$AVR_NM" -C "$OUT/uno.elf" 2>/dev/null \
        | awk '$2 ~ /^[dDbB]$/ && $NF ~ /(_POOL|_TABLE)$/ { n++ } END { print n + 0 }')"
fi
echo "METRIC UNO_COMPILE_OK=$uno_ok"
[[ -n "${uno_flash:-}" ]] && echo "METRIC UNO_FLASH_BYTES=$uno_flash"
[[ -n "${uno_ram:-}" ]] && echo "METRIC UNO_RAM_BYTES=$uno_ram"
[[ -n "${tables_in_ram:-}" ]] && echo "METRIC AVR_TABLES_IN_RAM=$tables_in_ram"

# stage 5
# The large-flash image: a 256 KB part with DCX/CAMF opted in (the preset no longer flips it on by chip name, so this stage defines it, as a Mega user would).
# Its tables land above 64 KB, which is what makes this stage able to prove the far addressing on a real device.
#
# No ${AVR_LTO[@]} here, unlike stage 4: this stage records the numbers the gates below compare against (MAX_MEGA_RAM_BYTES, the near-symbol window, the far reads), so it keeps the plain recipe. Stage 5b links the same preset with the Arduino recipe and reports the result; a gap between the two is a warning, not a gate.
mega_ok=0
mega_build=(-mmcu="$MCU" -Os -std=gnu++17 -fno-exceptions
            -ffunction-sections -fdata-sections -Wl,--gc-sections -Werror=overflow
            -DAZARAC_ENABLE_DCX_CAMF=1
            -I src -I "$BENCH/shim" -DARDUINO=1)
mega_objs=()
rm -rf "$OUT/obj_mega"
mkdir -p "$OUT/obj_mega"
for src in src/*.cpp src/*/*.cpp "$BENCH/probe.cpp"; do
    obj="$OUT/obj_mega/$(echo "$src" | tr '/' '_').o"
    if "$AVR_CC" "${mega_build[@]}" -c "$src" -o "$obj"; then
        mega_objs+=("$obj")
    else
        mega_objs=()
        break
    fi
done
if [[ ${#mega_objs[@]} -gt 0 ]] && "$AVR_CC" "${mega_build[@]}" "${mega_objs[@]}" -o "$OUT/mega.elf"; then
    mega_ok=1
    mega_flash="$("$AVR_SIZE" "$OUT/mega.elf" | awk 'NR == 2 { print $1 + $2 }')"
    mega_ram="$("$AVR_SIZE" "$OUT/mega.elf" | awk 'NR == 2 { print $2 + $3 }')"
    mega_tables_in_ram="$("$AVR_NM" -C "$OUT/mega.elf" 2>/dev/null \
        | awk '$2 ~ /^[dDbB]$/ && $NF ~ /(_POOL|_TABLE)$/ { n++ } END { print n + 0 }')"
    # The preset must actually carry the DCX/CAMF tables on a 256 KB part.
    mega_tables="$("$AVR_NM" -C "$OUT/mega.elf" 2>/dev/null \
        | awk '$3 ~ /QZSS_DCX_/ && $3 ~ /(_POOL|_TABLE)$/ { n++ } END { print n + 0 }')"
    # Far Flash addressing must be in use: without RAMPZ/elpm the tables above 64 KB (138 of 195 symbols in the all-category build) would be unreadable.
    mega_far_ops="$("$AVR_OBJDUMP" -d "$OUT/mega.elf" 2>/dev/null \
        | grep -c -e 'elpm' -e 'out.*0x3b')"
    # The `*(.progmem.*)` cluster at the front of .text is the one spot a large image pushes past 0xFFFF, and every table read through a 16-bit Flash pointer lives there: the CRC24Q nibbles (crc24q's pgm_read_byte) and the radius/B4 tables (AZARAC_PROGMEM_NEAR). One of them above the window decodes garbage in silence — a wrong CRC rejects every frame without a word — so the highest address among them is gated.
    # avr-nm pads addresses to one width for the whole file (8 hex digits here), so the string compare below is a numeric one; $NF because a demangled name in an anonymous namespace spans extra fields.
    near_sym_addr="$("$AVR_NM" -C "$OUT/mega.elf" 2>/dev/null \
        | awk 'NF >= 3 && $NF ~ /(CRC24Q_T4B[0-2]|RADIUS_TABLE|B4_LAYOUT_TABLE)$/ && $1 > m { m = $1 } END { print m }')"

    # What the core pays for our tables. core.a is linked last, so its own PROGMEM (digital_pin_to_port_PGM …) lands after every progmem-cluster input section — after ours.
    # Above 0xFFFF the core's 16-bit `pgm_read_byte(&digital_pin_to_port_PGM[pin])` cannot reach it and pinMode/digitalWrite read the wrong port, which is why AZARAC_PROGMEM moves the tables to the .text.azaraC.* cluster on parts with more than 64 KiB of Flash.
    # See test/bench/avr/core_progmem.c.
    core_build=(-mmcu="$MCU" -Os -std=gnu11 -fno-exceptions
                -ffunction-sections -fdata-sections)
    if "$AVR_CC" "${core_build[@]}" -c "$BENCH/core_progmem.c" -o "$OUT/obj_mega_core.o" \
       && "$AVR_CC" "${mega_build[@]}" "${mega_objs[@]}" "$OUT/obj_mega_core.o" \
            -Wl,--undefined=core_probe_read_pin -o "$OUT/mega_core.elf"; then
        mega_core_pgm="$("$AVR_NM" "$OUT/mega_core.elf" 2>/dev/null \
            | awk '$3 == "core_probe_pin_to_port_PGM" { print $1 }')"
    fi
fi
echo "METRIC MEGA_COMPILE_OK=$mega_ok"
[[ -n "${mega_flash:-}" ]] && echo "METRIC MEGA_FLASH_BYTES=$mega_flash"
[[ -n "${mega_ram:-}" ]] && echo "METRIC MEGA_RAM_BYTES=$mega_ram"
[[ -n "${mega_tables:-}" ]] && echo "METRIC MEGA_DCX_TABLES=$mega_tables"
[[ -n "${mega_far_ops:-}" ]] && echo "METRIC MEGA_FAR_OPS=$mega_far_ops"
[[ -n "${near_sym_addr:-}" ]] && echo "METRIC MEGA_NEAR_SYM_ADDR=0x$near_sym_addr"
[[ -n "${mega_core_pgm:-}" ]] && echo "METRIC MEGA_CORE_PGM_ADDR=0x$mega_core_pgm"

# --------------------------------------------------------------- stage 5b ---
# The same preset under the recipe a sketch is actually built with: the Arduino AVR
# core compiles and links with `-flto` (${AVR_LTO[@]}). This is the number the board
# sees, so the image itself is gated below (it must link and fit the ATmega2560's SRAM).
# It must also track the LTO-free stage-5 figure — the generator hoists the
# switch-strategy literals to namespace scope so LTO keeps them in Flash, and a gap
# means they fell back into .data.
mega_lto_ok=0
mega_lto_build=(-mmcu="$MCU" -Os -std=gnu++17 -fno-exceptions "${AVR_LTO[@]}"
                -ffunction-sections -fdata-sections -Wl,--gc-sections -Werror=overflow
                -DAZARAC_ENABLE_DCX_CAMF=1
                -I src -I "$BENCH/shim" -DARDUINO=1)
mega_lto_objs=()
rm -rf "$OUT/obj_mega_lto"
mkdir -p "$OUT/obj_mega_lto"
for src in src/*.cpp src/*/*.cpp "$BENCH/probe.cpp"; do
    obj="$OUT/obj_mega_lto/$(echo "$src" | tr '/' '_').o"
    if "$AVR_CC" "${mega_lto_build[@]}" -c "$src" -o "$obj"; then
        mega_lto_objs+=("$obj")
    else
        mega_lto_objs=()
        break
    fi
done
if [[ ${#mega_lto_objs[@]} -gt 0 ]] \
   && "$AVR_CC" "${mega_lto_build[@]}" "${mega_lto_objs[@]}" -o "$OUT/mega_lto.elf"; then
    mega_lto_ok=1
    mega_lto_flash="$("$AVR_SIZE" "$OUT/mega_lto.elf" | awk 'NR == 2 { print $1 + $2 }')"
    mega_lto_ram="$("$AVR_SIZE" "$OUT/mega_lto.elf" | awk 'NR == 2 { print $2 + $3 }')"
fi
echo "METRIC MEGA_LTO_COMPILE_OK=$mega_lto_ok"
[[ -n "${mega_lto_flash:-}" ]] && echo "METRIC MEGA_LTO_FLASH_BYTES=$mega_lto_flash"
[[ -n "${mega_lto_ram:-}" ]] && echo "METRIC MEGA_LTO_RAM_BYTES=$mega_lto_ram"

# The probe exists to keep the decode + serialize path — and the definition tables it reads —
# in the linked image. This is the check that it stayed there: if LTO ever drops them, the
# flash numbers above stop meaning "what a sketch pays". avr-nm prints CRLF on Windows, so
# the patterns are not anchored to the line end.
image_has_path() {  # $1 = elf
    "$AVR_NM" -C "$1" 2>/dev/null | awk '
        /Decoder::decode/ { d++ }
        /JsonSerializer/ { s++ }
        /_POOL|_TABLE/ { t++ }
        END { exit !(d > 0 && s > 0 && t > 0) }'
}

# gates
status=0

if [[ -n "${cross_checked:-}" ]] && [[ "$cross_checked" != "0" && "$cross_matched" != "$cross_checked" ]]; then
    echo "autoresearch: table sizes disagree with avr-gcc ($cross_matched/$cross_checked) — the metric is wrong" >&2
    status=6
fi

if (( largest < MAX_OBJECT_BYTES )); then
    if (( build_ok == 0 )); then
        echo "autoresearch: largest pool ($largest B) is placeable but the AVR build fails" >&2
        status=7
    fi
else
    echo "autoresearch: largest pool is $largest B (>= $MAX_OBJECT_BYTES) — the AVR build cannot compile until it shrinks" >&2
fi

if (( uno_ok == 0 )); then
    echo "autoresearch: the default AVR configuration no longer builds" >&2
    status=8
fi

if [[ -n "${uno_ram:-}" ]] && (( uno_ram > MAX_UNO_RAM_BYTES )); then
    echo "autoresearch: SRAM grew to $uno_ram B (baseline $MAX_UNO_RAM_BYTES) — smaller Flash does not buy back RAM" >&2
    status=10
fi

if [[ -n "${mega_ram:-}" ]] && (( mega_ram > MAX_MEGA_RAM_BYTES )); then
    echo "autoresearch: Mega SRAM grew to $mega_ram B (baseline $MAX_MEGA_RAM_BYTES) — the DCX/CAMF labels must stay in Flash" >&2
    status=15
fi

# Stage 5b's image is the one a Mega sketch really gets (the core applies -flto), so it is
# gated: it must link, and it must fit the part. The gap to the LTO-free figure is warned
# about rather than gated — it matches while every generated literal survives LTO (the
# generator emits the switch-strategy literals at namespace scope for exactly that reason),
# and the gap itself depends on the toolchain.
if (( mega_lto_ok == 0 )); then
    echo "autoresearch: the DCX/CAMF configuration no longer builds with the Arduino recipe (-flto)" >&2
    status=16
elif [[ -n "${mega_lto_ram:-}" ]] && (( mega_lto_ram > ATMEGA2560_SRAM_BYTES )); then
    echo "autoresearch: the Arduino recipe (-flto) makes the Mega image cost $mega_lto_ram B of SRAM — over the ATmega2560's $ATMEGA2560_SRAM_BYTES B" >&2
    status=16
fi

if [[ -n "${mega_lto_ram:-}" && -n "${mega_ram:-}" ]] \
   && (( mega_lto_ram > mega_ram + 64 )); then
    echo "autoresearch: the Arduino recipe (-flto) makes the Mega image cost $mega_lto_ram B of SRAM against the LTO-free $mega_ram B — generated literals are landing in .data instead of Flash (not gated: the fix is the generator emitting namespace-scope literals)" >&2
fi

# The probe must still keep the decode + serialize path and the definition tables in every
# linked image; otherwise the flash numbers above measure an image a sketch never runs.
for img in "$OUT/uno.elf" "$OUT/mega.elf" "$OUT/mega_lto.elf"; do
    if [[ -f "$img" ]] && ! image_has_path "$img"; then
        echo "autoresearch: $(basename "$img") lost the decode path, the serializer or the definition tables — its flash number no longer reflects a sketch" >&2
        status=17
    fi
done

if [[ -n "${tables_in_ram:-}" ]] && (( tables_in_ram != 0 )); then
    echo "autoresearch: $tables_in_ram definition table(s) landed in RAM instead of Flash" >&2
    status=11
fi

if (( mega_ok == 0 )); then
    echo "autoresearch: the DCX/CAMF AVR configuration no longer builds" >&2
    status=12
else
    [[ -n "${mega_tables_in_ram:-}" ]] && (( mega_tables_in_ram != 0 )) && {
        echo "autoresearch: $mega_tables_in_ram Mega table(s) in RAM instead of Flash" >&2
        status=12
    }
    (( ${mega_tables:-0} == 0 )) && {
        echo "autoresearch: the 256 KB preset stopped enabling the DCX/CAMF tables" >&2
        status=12
    }
    (( ${mega_far_ops:-0} == 0 )) && {
        echo "autoresearch: the Mega image uses no far Flash reads (elpm/RAMPZ) — tables above 64 KB would garble" >&2
        status=12
    }
    # The tables must not sit in the low-progmem cluster: they would push the core's own PROGMEM past the 16-bit window the core reads it through.
    if [[ -z "${mega_core_pgm:-}" ]]; then
        echo "autoresearch: the core PROGMEM stand-in did not link — placement is unverified" >&2
        status=13
    elif (( 0x$mega_core_pgm > 0xFFFF )); then
        echo "autoresearch: the core's PROGMEM landed at 0x$mega_core_pgm, past the 16-bit progmem window — pinMode/digitalWrite would read the wrong port" >&2
        status=13
    fi
    # Same window, our own side: every AZARAC_PROGMEM_NEAR table is read through 16-bit `pgm_read_*`.
    if [[ -z "${near_sym_addr:-}" ]]; then
        echo "autoresearch: none of the near-Flash tables (CRC24Q_T4B0-2, RADIUS_TABLE, B4_LAYOUT_TABLE) are in the Mega link — the symbols were renamed or moved to another section" >&2
        status=13
    elif (( 0x$near_sym_addr > 0xFFFF )); then
        echo "autoresearch: azaraC's near-Flash tables reach 0x$near_sym_addr, past the 16-bit progmem window — pgm_read_byte/pgm_read_dword would read garbage (crc24q would reject every frame)" >&2
        status=13
    fi
fi

if (( label_status != 0 )); then
    status=9
fi

if (( buf_status != 0 )); then
    status=14
fi

if (( status != 0 )); then
    exit "$status"
fi

echo "autoresearch: ok (AVR_TABLE_BYTES=$table_bytes strings=$string_bytes entries=$entry_bytes rows=$entry_rows largest=$largest AVR_COMPILE_OK=$build_ok UNO_FLASH_BYTES=${uno_flash:-n/a} MEGA_FLASH_BYTES=${mega_flash:-n/a})"
exit 0
