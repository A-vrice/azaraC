#!/bin/bash -eu
# ClusterFuzzLite (OSS-Fuzz 互換) のビルド。$SRC / $OUT / $WORK / $CXX / $CXXFLAGS /
# $LIB_FUZZING_ENGINE は builder イメージが渡す。
# ソースと定義は test/Makefile の fuzz-libfuzzer ターゲットと揃えてある
# （-Itest はハーネスが使う test/json/JsonCheck.h のため）。
set -eu
cd "$SRC/azaraC"

mkdir -p "$WORK/obj"
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
OBJS=""
for f in $SRCS; do
  obj="$WORK/obj/$(basename "$f" .cpp).o"
  $CXX $CXXFLAGS -std=c++17 -Isrc -Itest \
    -DARDUINO=0 -DAZARAC_TESTING=1 -DAZARAC_LANG_JA=1 -DAZARAC_LANG_EN=1 \
    -c "$f" -o "$obj"
  OBJS="$OBJS $obj"
done

$CXX $CXXFLAGS $LIB_FUZZING_ENGINE $OBJS -o "$OUT/fuzz_libfuzzer"

zip -j "$OUT/fuzz_libfuzzer_seed_corpus.zip" test/fuzz/corpus/*
