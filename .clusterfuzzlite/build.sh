#!/bin/bash -eu
# ClusterFuzzLite (OSS-Fuzz 互換) のビルド。$SRC / $OUT / $WORK / $CXX / $CXXFLAGS /
# $LIB_FUZZING_ENGINE は builder イメージが渡す。
# $CXXFLAGS などは空白区切りのフラグ列で単語分割が前提（SC2086）。$SRC は
# builder が渡す環境変数で、このスクリプトでは代入しない（SC2153）。
# shellcheck disable=SC2086,SC2153
# ソースと定義は test/Makefile の fuzz-libfuzzer ターゲットと揃えてある
# （-Itest はハーネスが使う test/json/JsonCheck.h のため）。
# 3つのコンパイル時構成を別ターゲットとしてビルドする。バッファ追い出しや
# 受理/拒否の分岐は構成で変わるため、既定構成だけでは届かない経路がある。
# 定義が構成ごとに違うのでオブジェクトは共有できず、構成別のディレクトリに分ける。
#   fuzz_libfuzzer: 既定構成（従来どおり。corpus の継続性のため名前も定義も不変）
#   fuzz_libfuzzer_small: AVR 相当の縮小構成。Nankai バッファ1個・最大4ページ、
#     dedup 64スロットにし、有効カテゴリは震度・南海トラフ・津波のみ
#   fuzz_libfuzzer_strict: 検証を厳格にした構成。dedup 無効、SVID 検証レベル2、
#     NMEA の非0パディングを拒否する
set -eu
cd "$SRC/azaraC"

SRCS="
src/Parser.cpp
src/decoder/Decoder.cpp
src/decoder/DecoderDcx.cpp
src/decoder/DecoderQzqsm.cpp
src/framer/UbxFramer.cpp
src/framer/NmeaFramer.cpp
src/json/JsonWriter.cpp
src/json/JsonSerializer.cpp
src/json/JsonSerializerDcx.cpp
src/json/JsonSerializerQzqsm.cpp
src/internal/DcxHelper.cpp
src/internal/Dedup.cpp
test/fuzz/fuzz_libfuzzer.cpp
"

build_target() {
  target=$1
  shift
  objdir="$WORK/obj-$target"
  mkdir -p "$objdir"
  objs=""
  for f in $SRCS; do
    obj="$objdir/$(basename "$f" .cpp).o"
    $CXX $CXXFLAGS -std=c++17 -Isrc -Itest "$@" -c "$f" -o "$obj"
    objs="$objs $obj"
  done
  $CXX $CXXFLAGS $LIB_FUZZING_ENGINE $objs -o "$OUT/$target"
  zip -j "$OUT/${target}_seed_corpus.zip" test/fuzz/corpus/*
}

BASE_DEFS="-DARDUINO=0 -DAZARAC_TESTING=1"

build_target fuzz_libfuzzer \
  $BASE_DEFS -DAZARAC_LANG_JA=1 -DAZARAC_LANG_EN=1

build_target fuzz_libfuzzer_small \
  $BASE_DEFS -DAZARAC_LANG_JA=1 -DAZARAC_LANG_EN=0 \
  -DAZARAC_ENABLE_EEW=0 -DAZARAC_ENABLE_HYPOCENTER=0 -DAZARAC_ENABLE_SEISMIC=1 \
  -DAZARAC_ENABLE_NANKAI=1 -DAZARAC_ENABLE_TSUNAMI=1 -DAZARAC_ENABLE_NW_PAC_TSUNAMI=0 \
  -DAZARAC_ENABLE_VOLCANO=0 -DAZARAC_ENABLE_ASH_FALL=0 -DAZARAC_ENABLE_WEATHER=0 \
  -DAZARAC_ENABLE_FLOOD=0 -DAZARAC_ENABLE_TYPHOON=0 -DAZARAC_ENABLE_MARINE=0 \
  -DAZARAC_ENABLE_DCX_CAMF=0 -DAZARAC_NANKAI_BUFFERS=1 -DAZARAC_NANKAI_MAX_PAGES=4 \
  -DAZARAC_DEDUP_SLOTS=64

build_target fuzz_libfuzzer_strict \
  $BASE_DEFS -DAZARAC_LANG_JA=0 -DAZARAC_LANG_EN=1 \
  -DAZARAC_ENABLE_DEDUP=0 -DAZARAC_NMEA_STRICT_SVID=2 \
  -DAZARAC_NMEA_REJECT_NONZERO_PADDING=1
