#!/usr/bin/env bash
# autoresearch.sh — AVR 定義テーブルのフットプリント計測。
#
# 目的 (issue #35): 生成される target-area 文字列プールが親リージョン名を重複して持つため、プール 1 つで英語側だけで約 63 KB かかる。
# AVR ではそれが高コストなだけでなくビルド不能になる: avr-gcc は 32,767 バイトを超える単一オブジェクトを拒否する（"size of variable is too large"。32,767 は通り 32,768 は通らないことを確認済み）。azaraC_config.h の AVR プリセットが DCX/CAMF（および volcano/ash-fall 系）を完全に外しているのはこのため。
#
# 主要指標 AVR_TABLE_BYTES — 有効な設定が AVR リンカに要求する全バイト数:
#                定義テーブルの文字列リテラル（プールと `switch` テーブルの
#                case ごとのリテラル）とエントリ配列を `avr-gcc -E` の出力から
#                計測する。stage 3 が avr-gcc 自身のオブジェクトサイズと突き合わせる
#                ので、構造体レイアウトも正しく保たれる。
# 報告値        AVR_STRING_BYTES（issue の「63 KB プール」の数値）、
#                AVR_ENTRY_BYTES/ROWS/ROW_BYTES、AVR_LARGEST_LITERAL、4 つの
#                大きなプール、実リンクした 2 イメージの UNO_*/MEGA_* サイズ、
#                AVR_TABLES_IN_RAM、MEGA_DCX_TABLES、MEGA_FAR_OPS、AVR_COMPILE_OK、
#                AVR_TABLE_CROSSCHECK、FLASH_BUF_OK、MEGA_NEAR_SYM_ADDR/MEGA_CORE_PGM_ADDR
#                （16 ビットポインタで読む near-Flash テーブルは窓内に収まること）。
#
# ゲート (違反時は非ゼロ終了)
#   labels    各テーブルの全 id が 3 つのモード（AVR far Flash、AVR 16-bit progmem、host）で
#             バイト単位に同一のラベルを返すこと（比較先は test/bench/avr/labels.golden のハッシュ）。
#   buffer    AZARAC_FLASH_BUF_SIZE (src/azaraC_config.h) が有効な全カテゴリの最長ラベルを
#             保持できること: internal/FlashString.h は size - 1 でコピーを打ち切るため、
#             サイズ連鎖から漏れたカテゴリはラベルを黙って切り詰める
#             （check_flash_buf.py が両言語・両プリセットの全組み合わせを走査する）。
#   build     全カテゴリ有効の全 TU が ATmega2560 向けにコンパイルできること *ただし*
#             単一プールがオブジェクト上限を超えていないとき。プールが過大な間の失敗は
#             想定内のベースラインで、報告のみ（ゲートしない）— それがこの指標が直すバグ。
#   crosscheck 主要指標が、avr-gcc が実際に配置したシンボルのサイズと一致すること。
#   uno       既定の AVR 設定がコンパイル・リンクできること。
#   mega      DCX/CAMF 設定（256 KB 品と同じく有効化したもの）がコンパイル・リンクでき、
#             DCX/CAMF テーブルを有効にし、全テーブルを Flash に置き、far Flash 読み出し
#             (elpm/RAMPZ) を使うこと — なければ 64 KB 超のテーブルが壊れる。
#             *near* 16 ビットポインタで読むテーブル（CRC24Q、radius、B4 レイアウト）は
#             0xFFFF 未満に収まること。超えると黙ってゴミを返す。
#   ram       SRAM が増えないこと（UNO_RAM_BYTES と MEGA_RAM_BYTES <= ベースライン）、
#             かつテーブルが Flash ではなく RAM に住まないこと: SRAM を食って Flash を
#             減らすのは損失で、AVR 経路は既に持つ共有 800 B バッファでしかラベルを連結できない。
#   mega-lto  同じ DCX/CAMF 設定を Arduino のレシピ（-flto。Mega スケッチが実際に受けるビルド）
#             でリンクでき、ATmega2560 の SRAM に収まること。
#   path      リンクした各イメージが decode 経路・シリアライザ・定義テーブルを保持していること:
#             LTO がそれらを落とすと flash の数値は「スケッチが払う額」を意味しなくなる。
#
# 決定的: ツールチェーンフラグ固定、入力固定、ネットワーク・時計なし。avr-gcc/avr-size/avr-nm と g++ が PATH に必要。
# Uno イメージは Arduino AVR コアの `-flto -fuse-linker-plugin`（AVR_LTO）でリンクする。Mega イメージは stage 5 で LTO なし、stage 5b で Arduino レシピでリンクし、stage 5b のイメージはゲート対象（リンクでき、品の SRAM に収まること）。
#
# `bash test/bench/avr/autoresearch.sh --bless-labels` は golden のラベルハッシュを再記録する — ラベル変更が意図どおりだと確認した後のみ。

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

# Arduino コア代替（$BENCH/shim/Arduino.h）用のレシピ: ARDUINO=1 で azaraC.h は <Print.h> を include し、TimeFields.h は実 AVR ビルド同様 millis() を使う。
AVR_BUILD=(-mmcu="$MCU" -Os -std=gnu++17 -fno-exceptions
           -ffunction-sections -fdata-sections -Werror=overflow
           -I src -I "$BENCH/shim" -DARDUINO=1)

# Arduino AVR コアは `-flto -fuse-linker-plugin` でコンパイル・リンクする（platform.txt）ので、stage 4 の Uno イメージ — スケッチが実際に配布される設定 — もこれを使う。
# stage 3 は意図的に LTO なしのレシピを使う: LTO オブジェクトはシンボルのサイズを持たず、avr-gcc との突き合わせに何も残らないため。
# stage 5 も別の理由で LTO なしのまま。その箇所の注記を参照。
AVR_LTO=(-flto -fuse-linker-plugin)

# テーブルの最悪ケース: 全カテゴリ・両言語。
CATS=(-DAZARAC_LANG_JA=1 -DAZARAC_LANG_EN=1
      -DAZARAC_ENABLE_EEW=1 -DAZARAC_ENABLE_HYPOCENTER=1 -DAZARAC_ENABLE_SEISMIC=1
      -DAZARAC_ENABLE_NANKAI=1 -DAZARAC_ENABLE_TSUNAMI=1 -DAZARAC_ENABLE_NW_PAC_TSUNAMI=1
      -DAZARAC_ENABLE_VOLCANO=1 -DAZARAC_ENABLE_ASH_FALL=1 -DAZARAC_ENABLE_WEATHER=1
      -DAZARAC_ENABLE_FLOOD=1 -DAZARAC_ENABLE_TYPHOON=1 -DAZARAC_ENABLE_MARINE=1
      -DAZARAC_ENABLE_DCX_CAMF=1)

# avr-gcc のオブジェクト上限: 2**15 がコンパイラの限界。
MAX_OBJECT_BYTES=32768

# AVR 経路が RAM と引き換えに使える Flash は、既に持っている SRAM（internal/FlashString.h の共有 800 B ラベルバッファ）の範囲だけ。SRAM を増やして Flash を減らすのは損失なので、リンクした Uno イメージの RAM はゲートする。
# 圧縮前のベースラインで 702 B（data 626 + bss 76）、JSON キーを Flash へ移す前が 640 B、移した後が 204 B（data 88 + bss 116）、payload のアラインメント修正前が 146 B、現在 142 B（data 30 + bss 112）: キーと補助テーブルが .data を出た（avr-libc のリンカスクリプトは .rodata を SRAM にコピーする）ためで、bss の 36 B は共有キーバッファ（AZARAC_KEY_BUF_SIZE）。Flash は +730 B（13,546 → 14,276）。
# 残り 58 B は .data を出た固定文字列: NmeaFramer の "QZQSM,"（7）と、AZARAC_KEY 経由になった JSON 値 arrival_estimated（18）、no_information（15）、unrecognized_code（18）。.data に残るのはアロケータのグローバルと 2 つのフレーマ vtable だけで、Flash は +194 B（14,276 → 14,470）。（"null" は以前からコストゼロ: 7 か所の呼び出しはバイト単位で同一だった。）
# プローブの不透明シンク（serialize 経路をイメージに残す write()）がさらに 132 B を足す: d55cb12 時点で 14,602 B、HEAD で 14,622 B（その間の parser/UBX 修正分）、現在 14,702 B。
# 最後の 80 B の Flash が 4 B の SRAM を買う: AVR では alignas(8) が純粋なパディングだった（avr-gcc の __alignof__(unsigned long long) は 1）ので、payload のストレージは alignas(uint64_t) にした — sizeof(Mt43Data) 88 → 80 B、sizeof(Message) 104 → 89 B（スケッチが自前で持つグローバル Message も同じだけ縮む）。host は 8 バイト境界とレイアウトを維持する。JSON キーバッファは 40 → 36 B（最長キーは 35 B）。差分はテーブルではなくレイアウト: AVR_TABLE_BYTES は不変。
MAX_UNO_RAM_BYTES=142

# stage 5 の DCX/CAMF イメージも同じ上限: Mega の 8,192 B のうち実測 3,714 B（data 2,902 + bss 812）— その大半がキー約 1.8 KB だった — が、キーを移して 1,086 B（data 234 + bss 852）、Flash は +1,712 B（144,806 → 146,518）。テーブルは Flash を消費してよく、SRAM は決して使わない。
# bss の 36 B は Flash のキーをコピーして通す共有キーバッファ。
# payload アラインメント修正前が 896 B、現在 892 B（data 44 + bss 848）: DCX の値リテラル（invalid_mt44、NULL/L_ALERT/J_ALERT/LOCAL_GOV/OUTSIDE_JAPAN/UNKNOWN、unsupported_*）も同様に .data を出て、Flash は +154 B（146,518 → 146,672）。プローブの不透明シンクが 18 B を足す: d55cb12 時点で 146,690 B、HEAD で 146,700 B、現在 146,550 B。
# キーバッファはここでも 36 B で、payload のストレージは alignas(uint64_t): AVR ではそれはアラインメントにならない（avr-gcc の __alignof__(unsigned long long) は 1）ので、純粋なパディングを削っただけ。host は 8 バイト境界を維持する。
# この上限に余裕はない: 892 B が現在の実測値なので、SRAM が回帰すればここで落ちる（SRAM を増やして Flash を減らすのが、これが存在する理由の失敗）。
MAX_MEGA_RAM_BYTES=892

# 品の SRAM。スケッチが実際に受けるイメージ（stage 5b、Arduino レシピ）向け: LTO
# ビルドがリンクでき ATmega2560 に収まらなければ、その設定は出荷できない。
ATMEGA2560_SRAM_BYTES=8192

mkdir -p "$OUT"

# stage 1
# AVR プリプロセッサから見た有効なテーブル。
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
# 共有ラベルバッファは有効な全カテゴリの最長ラベルを保持できること: internal/FlashString.h は AZARAC_FLASH_BUF_SIZE - 1 でコピーを打ち切るため、サイズ連鎖から漏れたカテゴリはラベルを黙って（UTF-8 の途中で）切り詰める。
# 全カテゴリの組み合わせ・両言語・両プリセットで走査する。サイズ連鎖は azaraC_config.h から読み、AVR プリプロセッサと突き合わせる。
buf_status=0
"$PYTHON" "$BENCH/check_flash_buf.py" --avr-gcc "$AVR_CC" || buf_status=$?
echo "METRIC FLASH_BUF_OK=$(( buf_status == 0 ? 1 : 0 ))"

# stage 2
# ラベルの等価性: AVR 分岐（PROGMEM 文字列ビュー）と host 分岐が、ベースラインで返していたラベルを返し続けること。
"$PYTHON" "$BENCH/gen_label_dump.py" "$OUT/dump_labels.cpp" || exit 4
GOLDEN="$BENCH/labels.golden"

run_dump() {   # $1 = バイナリ; "<hash> <calls> <labels>" を出力
    "$1" | sed -n 's/^LABELHASH \([0-9a-f]*\) calls=\([0-9]*\) labels=\([0-9]*\)$/\1 \2 \3/p'
}
build_dump() {  # $1 = ラベル、残りは追加フラグ
    local label="$1"; shift
    "$HOST_CXX" -std=c++17 -O1 -I src -DARDUINO=0 "$@" "${CATS[@]}" \
        "$OUT/dump_labels.cpp" -o "$OUT/dump_$label" || return 1
}

build_dump avr -I test/stub -D__AVR__ -DAZARAC_AVR_STUB \
    || { echo "autoresearch: AVR label dump did not build" >&2; exit 4; }
# 同じテーブルを別のアドレッシングモードで: Flash 64 KiB 以下の品（Uno）は 16 ビット progmem ポインタを使い、それより大きい品は far アクセサを使う。
# スタブは既定で大型品を模すので、このビルドでは FLASHEND を固定する。
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
        echo "# Definition-label のハッシュ: <hash> <lookups> <labels>。再記録は"
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
    # AVR_SHORT は 16 ビット progmem ポインタを使う。AVR の golden と比較する。
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
# 単一プールがオブジェクト上限を超えていない状態で、全 TU が実ターゲット向けにコンパイルできること。上限を超えている間はビルド自体がゲートで、超えた状態の失敗は想定内のベースライン。
rm -rf "$OUT/obj"
mkdir -p "$OUT/obj"
build_failed=0
for src in src/*.cpp src/*/*.cpp; do
    obj="$OUT/obj/$(echo "$src" | tr '/' '_').o"
    "$AVR_CC" "${AVR_BUILD[@]}" "${CATS[@]}" -c "$src" -o "$obj" || build_failed=1
done
build_ok=$((1 - build_failed))
echo "METRIC AVR_COMPILE_OK=$build_ok"

# 主要指標は、avr-gcc が実際に配置したシンボルのサイズと一致して初めて信用できる。
if [[ -f "$OUT/pools.txt" ]]; then
    cross="$("$AVR_NM" --print-size --radix=d -C "$OUT"/obj/*.o 2>/dev/null | tr -d '\r' \
        | "$PYTHON" "$BENCH/crosscheck_tables.py" "$OUT/pools.txt")"
    echo "$cross"
    cross_checked="$(printf '%s\n' "$cross" | sed -n 's/.*CROSSCHECK=[0-9]*\/\([0-9]*\).*/\1/p')"
    cross_matched="$(printf '%s\n' "$cross" | sed -n 's/.*CROSSCHECK=\([0-9]*\)\/.*/\1/p')"
fi

# stage 4
# ライブラリが AVR 向けに実際に出荷する設定（プリセット: seismic と tsunami のみ、日本語ラベル）。ビルド可能で小さいままであること。
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
    # .data/.bss にある定義テーブルはもう Flash にない: すべて PROGMEM であること。
    tables_in_ram="$("$AVR_NM" -C "$OUT/uno.elf" 2>/dev/null \
        | awk '$2 ~ /^[dDbB]$/ && $NF ~ /(_POOL|_TABLE)$/ { n++ } END { print n + 0 }')"
fi
echo "METRIC UNO_COMPILE_OK=$uno_ok"
[[ -n "${uno_flash:-}" ]] && echo "METRIC UNO_FLASH_BYTES=$uno_flash"
[[ -n "${uno_ram:-}" ]] && echo "METRIC UNO_RAM_BYTES=$uno_ram"
[[ -n "${tables_in_ram:-}" ]] && echo "METRIC AVR_TABLES_IN_RAM=$tables_in_ram"

# stage 5
# 大容量フラッシュのイメージ: DCX/CAMF を明示的に有効化した 256 KB 品（プリセットはもうチップ名で有効化しないので、Mega ユーザーがするようにこの stage で定義する）。
# テーブルが 64 KB 超に置かれるため、この stage は実デバイス上で far アドレッシングを証明できる。
#
# stage 4 と違いここでは ${AVR_LTO[@]} を付けない: この stage は下のゲートが比較する数値（MAX_MEGA_RAM_BYTES、near シンボルの窓、far 読み出し）を記録するので、素のレシピのままにする。stage 5b が同じプリセットを Arduino レシピでリンクして結果を報告し、両者の差はゲートではなく警告。
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
    # プリセットは 256 KB 品で実際に DCX/CAMF テーブルを有効にしていること。
    mega_tables="$("$AVR_NM" -C "$OUT/mega.elf" 2>/dev/null \
        | awk '$3 ~ /QZSS_DCX_/ && $3 ~ /(_POOL|_TABLE)$/ { n++ } END { print n + 0 }')"
    # far Flash アドレッシングが使われていること: RAMPZ/elpm がなければ 64 KB 超のテーブル（全カテゴリビルドで 195 シンボル中 138）は読めない。
    mega_far_ops="$("$AVR_OBJDUMP" -d "$OUT/mega.elf" 2>/dev/null \
        | grep -c -e 'elpm' -e 'out.*0x3b')"
    # .text 先頭の `*(.progmem.*)` クラスタが、大きなイメージで 0xFFFF を越える唯一の場所で、16 ビット Flash ポインタで読むテーブルはすべてそこに住む: CRC24Q のニブル（crc24q の pgm_read_byte）と radius/B4 テーブル（AZARAC_PROGMEM_NEAR）。どれか 1 つでも窓を越えると黙ってゴミをデコードする — CRC が違えば全フレームを無言で捨てる — ので、その中の最大アドレスをゲートする。
    # avr-nm はファイル全体で 1 つの幅にアドレスを揃える（ここでは 8 桁の 16 進）ので、下の文字列比較は数値比較になる。$NF なのは、無名名前空間の demangle 名が余分なフィールドを持つため。
    near_sym_addr="$("$AVR_NM" -C "$OUT/mega.elf" 2>/dev/null \
        | awk 'NF >= 3 && $NF ~ /(CRC24Q_T4B[0-2]|RADIUS_TABLE|B4_LAYOUT_TABLE)$/ && $1 > m { m = $1 } END { print m }')"

    # コアが我々のテーブルに対して払うもの。core.a は最後にリンクされるので、コア自身の PROGMEM（digital_pin_to_port_PGM …）は progmem クラスタの全入力セクションより後 — 我々の後 — に置かれる。
    # 0xFFFF を越えるとコアの 16 ビット `pgm_read_byte(&digital_pin_to_port_PGM[pin])` は届かず、pinMode/digitalWrite が誤ったポートを読む。64 KiB 超の Flash を持つ品で AZARAC_PROGMEM がテーブルを .text.azaraC.* クラスタへ移すのはこのため。
    # test/bench/avr/core_progmem.c を参照。
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
# スケッチが実際にビルドされるレシピでの同じプリセット: Arduino AVR
# コアは `-flto`（${AVR_LTO[@]}）でコンパイル・リンクする。これがボードの見る
# 数値なので、下でイメージ自体をゲートする（リンクでき ATmega2560 の SRAM に収まること）。
# LTO なしの stage 5 の値も追従すること — ジェネレータは switch 方式の
# リテラルを名前空間スコープに持ち上げて LTO でも Flash に残すので、差が
# 出るのはそれらが .data に落ちたとき。
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

# プローブは decode + serialize 経路 — そしてそれが読む定義テーブル — を
# リンク済みイメージに残すために存在する。これがそれが残ったことの確認で、
# LTO が落とすと上の flash 数値は「スケッチが払う額」を意味しなくなる。
# avr-nm は Windows で CRLF を出すので、パターンは行末に固定しない。
image_has_path() {  # $1 = elf
    "$AVR_NM" -C "$1" 2>/dev/null | awk '
        /Decoder::decode/ { d++ }
        /JsonSerializer/ { s++ }
        /_POOL|_TABLE/ { t++ }
        END { exit !(d > 0 && s > 0 && t > 0) }'
}

# ゲート
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

# stage 5b のイメージは Mega スケッチが実際に受け取るもの（コアが -flto を付ける）なので、
# ゲートする: リンクでき、品に収まること。LTO なしの値との差はゲートせず警告に留める
# — 生成リテラルがすべて LTO を生き残る間は一致し（ジェネレータが switch 方式の
# リテラルを名前空間スコープに出すのはまさにそのため）、差自体がツールチェーン依存だから。
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

# プローブはリンク済みの各イメージで decode + serialize 経路と定義テーブルを
# 保持し続けなければならない。でなければ上の flash 数値はスケッチが決して走らせないイメージを測っている。
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
    # テーブルは低アドレスの progmem クラスタに置いてはいけない: コア自身の PROGMEM を、コアが読む 16 ビット窓の外へ押し出してしまう。
    if [[ -z "${mega_core_pgm:-}" ]]; then
        echo "autoresearch: the core PROGMEM stand-in did not link — placement is unverified" >&2
        status=13
    elif (( 0x$mega_core_pgm > 0xFFFF )); then
        echo "autoresearch: the core's PROGMEM landed at 0x$mega_core_pgm, past the 16-bit progmem window — pinMode/digitalWrite would read the wrong port" >&2
        status=13
    fi
    # 同じ窓を我々の側でも: AZARAC_PROGMEM_NEAR の各テーブルは 16 ビットの `pgm_read_*` で読む。
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
