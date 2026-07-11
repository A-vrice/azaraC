# test/Makefile — ホストビルド

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I../src -I. -DARDUINO=0 -DAZARAC_LANG_JA=1 -DAZARAC_LANG_EN=1 -DAZARAC_NANKAI_MAX_PAGES=63 -DAZARAC_NANKAI_AGGREGATED_TEXT_SIZE=1135 -g -MMD -MP

# --- Static Analysis and Coverage ---
# 過剰に厳格な警告オプション（-Wshadow, -Wconversion, -Wsign-conversion）は、
# ビット演算を多用する組み込み向けコードにおいて修正コストが高すぎるため削除する。
ANALYSIS_CXXFLAGS = $(CXXFLAGS) -Wpedantic -Wnull-dereference -Wdouble-promotion -Wformat=2 -Werror
COVERAGE_FLAGS    = -O0 -fprofile-arcs -ftest-coverage

# MinGW-w64 bin path (override on command line if needed, e.g. make MINGW64_BIN=C:\mingw64\bin)
MINGW64_BIN ?= D:\apps\mingw64\bin

# OS detection
ifeq ($(OS),Windows_NT)
  TEST_BIN   = run_tests.exe
  RUN_PREFIX =
  RM         = cmd /c "del /F /Q"
  ifneq ($(MINGW64_BIN),)
    export PATH := $(PATH);$(MINGW64_BIN)
  endif
  # メモリ割り当て増加: 256MBスタック + 512MBヒープ
  LDFLAGS = -Wl,--stack,268435456 -Wl,--heap,536870912
else
  TEST_BIN   = run_tests
  RUN_PREFIX = ./
  RM         = rm -f
  LDFLAGS =
endif

# Test sources (機能別ディレクトリ)
TEST_SRCS = \
	test_main.cpp \
	core/test_core.cpp \
	core/test_boundary_values.cpp \
	core/test_message_struct.cpp \
	framer/test_framer.cpp \
	framer/test_ublox_azarashi.cpp \
	json/test_json.cpp \
	json/test_json_dcx_b1b4.cpp \
	integration/test_parser.cpp \
	integration/test_parser_integration.cpp \
	integration/test_nankai.cpp \
	integration/test_nankai_e2e.cpp \
	integration/test_error_handling.cpp \
	integration/test_azarashi.cpp \
	integration/test_azarashi_dcr.cpp \
	integration/test_azarashi_dcx.cpp \
	integration/test_realdata.cpp

# Library sources (src/ 配下の実装ファイル)
LIB_SRCS = \
	../src/Parser.cpp \
	../src/decoder/Decoder.cpp \
	../src/decoder/DecoderDcx.cpp \
	../src/decoder/DecoderQzqsm.cpp \
	../src/framer/UbxFramer.cpp \
	../src/framer/NmeaFramer.cpp \
	../src/json/JsonWriter.cpp \
	../src/json/JsonSerializer.cpp \
	../src/json/JsonSerializerDcx.cpp \
	../src/json/JsonSerializerQzqsm.cpp \
	../src/internal/DcxHelper.cpp \
	../src/internal/Dedup.cpp

# Object files - サブディレクトリの.oはそのまま保持、ライブラリはカレントに
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
LIB_OBJS = $(notdir $(LIB_SRCS:.cpp=.o))
OBJS = $(TEST_OBJS) $(LIB_OBJS)

# VPATH for library sources
VPATH = ../src:../src/decoder:../src/framer:../src/json:../src/internal

.PHONY: all clean run fuzz decode compare-realdata check check-xml check-strict-compile coverage memprof

all: $(TEST_BIN)

# Rule to build the test binary
$(TEST_BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Pattern rules for test sources (サブディレクトリ対応)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	$(RUN_PREFIX)$(TEST_BIN)

# Fuzz target
FUZZ_BIN = fuzz_decoder
FUZZ_SRCS = fuzz/fuzz_decoder.cpp
FUZZ_OBJS = $(FUZZ_SRCS:.cpp=.o)

fuzz: $(FUZZ_BIN)
	$(RUN_PREFIX)$(FUZZ_BIN)

$(FUZZ_BIN): $(FUZZ_OBJS) $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Decode-to-JSON CLI tool (for azarashi comparison)
DECODE_BIN = decode_to_json
DECODE_SRCS = tools/decode_to_json.cpp
DECODE_OBJS = $(DECODE_SRCS:.cpp=.o)

decode: $(DECODE_BIN)

$(DECODE_BIN): $(DECODE_OBJS) $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compare with azarashi (requires: pip install azarashi)
PYTHON ?= python
COMPARE_ARGS ?=
compare-realdata: $(DECODE_BIN)
	$(PYTHON) scripts/compare_with_azarashi.py $(COMPARE_ARGS)

# --- Static Analysis ---
# 静的解析 (時間をかけた厳格なチェック)
check:
	@echo "Running cppcheck..."
	cppcheck --enable=warning,performance,portability --check-level=exhaustive --inline-suppr --suppress=missingIncludeSystem --error-exitcode=1 --std=c++17 -I../src -I. ../src test
	@echo "Compiling library with strict warnings..."
	$(CXX) $(ANALYSIS_CXXFLAGS) -c $(LIB_SRCS)

# cppcheck の XML レポートをファイルに保存（サマリー生成用）
check-xml:
	@echo "Running cppcheck (XML output)..."
	cppcheck --enable=warning,performance,portability --check-level=exhaustive --inline-suppr --suppress=missingIncludeSystem --xml --xml-version=2 --output-file=cppcheck_report.xml --std=c++17 -I../src -I. ../src test 2> cppcheck_stderr.log || true
	@echo "cppcheck XML report saved to cppcheck_report.xml"

# 厳格コンパイルチェックのみ（check から cppcheck を除いた部分）
check-strict-compile:
	@echo "Compiling library with strict warnings..."
	$(CXX) $(ANALYSIS_CXXFLAGS) -c $(LIB_SRCS)

# --- Coverage ---
# カバレッジ測定
coverage:
	@$(MAKE) clean
	@echo "Building with coverage instrumentation..."
	$(MAKE) CXXFLAGS="$(CXXFLAGS) $(COVERAGE_FLAGS)" $(TEST_BIN)
	@echo "Running tests with coverage..."
	$(RUN_PREFIX)$(TEST_BIN)
	@echo "----------------------------------------"
	gcovr . --filter=../src/ --exclude='.*test_.*\.cpp' --txt

# --- Memory Profiling ---
# メモリプロファイリング (Valgrind Massifによるヒープ検証)
ifeq ($(OS),Windows_NT)
memprof:
	@echo "memprof: Valgrind is not available on Windows. Run on Linux or WSL."
else
memprof: $(TEST_BIN)
	valgrind --tool=massif --pages-as-heap=yes --massif-out-file=massif.out $(RUN_PREFIX)$(TEST_BIN)
	ms_print massif.out | head -n 30
endif

# Include dependency files
-include $(TEST_OBJS:.o=.d) $(LIB_OBJS:.o=.d) $(FUZZ_OBJS:.o=.d) $(DECODE_OBJS:.o=.d)

clean:
	-$(RM) *.o *.exe *.d *.gcno *.gcda massif.out cppcheck_report.xml cppcheck_stderr.log coverage_report.json
	-$(RM) core/*.o core/*.d core/*.gcno core/*.gcda
	-$(RM) decoder/*.o decoder/*.d decoder/*.gcno decoder/*.gcda
	-$(RM) framer/*.o framer/*.d framer/*.gcno framer/*.gcda
	-$(RM) json/*.o json/*.d json/*.gcno json/*.gcda
	-$(RM) integration/*.o integration/*.d integration/*.gcno integration/*.gcda
	-$(RM) fuzz/*.o fuzz/*.d fuzz/*.gcno fuzz/*.gcda
	-$(RM) tools/*.o tools/*.d tools/*.gcno tools/*.gcda
	-$(RM) scripts/*.o scripts/*.d scripts/*.gcno scripts/*.gcda
