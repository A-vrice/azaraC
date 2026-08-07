# test/Makefile — ホストビルド

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I../src -I. -DARDUINO=0 -DAZARAC_LANG_JA=1 -DAZARAC_LANG_EN=1 -DAZARAC_NANKAI_MAX_PAGES=63 -MMD -MP

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
  RM         = rm -f
  ifneq ($(wildcard $(MINGW64_BIN)/g++.exe),)
    export PATH := $(MINGW64_BIN);$(PATH)
  endif
  # /dev/null fallback — Windows では NUL
  DEVNULL = NUL
  # メモリ割り当て増加: 256MBスタック + 512MBヒープ (MinGW)
  LDFLAGS = -Wl,--stack,268435456 -Wl,--heap,536870912
else
  TEST_BIN   = run_tests
  RUN_PREFIX = ./
  RM         = rm -f
  LDFLAGS =
  # /dev/null fallback — Linux/macOS では /dev/null
  DEVNULL = /dev/null
endif

# Optimization profile: make RELEASE=1 for -Os (smaller code, no debug symbols)
ifdef RELEASE
  CXXFLAGS += -Os -fdata-sections -ffunction-sections
  LDFLAGS += -Wl,--gc-sections
else
  CXXFLAGS += -g
endif

# Test sources (機能別ディレクトリ)
TEST_SRCS = \
	test_main.cpp \
	core/test_core.cpp \
	core/test_boundary_values.cpp \
	core/test_message_struct.cpp \
	core/test_macro_disabled.cpp \
	framer/test_framer.cpp \
	framer/test_ublox_azarashi.cpp \
	framer/test_ublox_multignss.cpp \
	internal/test_dcx_helper_b4.cpp \
	internal/test_dcx_helper.cpp \
	internal/test_avr_std_shim.cpp \
	json/test_json.cpp \
	json/test_json_dcx_b1b4.cpp \
	integration/test_parser.cpp \
	integration/test_parser_integration.cpp \
	integration/test_nankai.cpp \
	integration/test_nankai_e2e.cpp \
	integration/test_error_handling.cpp \
	integration/test_time_resolution.cpp \
	integration/test_dcx_edge_cases.cpp \
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

.PHONY: all clean run fuzz decode compare-realdata check check-xml check-strict-compile coverage memprof pgm-stub

all: $(TEST_BIN)

# Rule to build the test binary
$(TEST_BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_EXTRA) $^ -o $@ $(LDFLAGS)

# Pattern rules for test sources (サブディレクトリ対応)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_EXTRA) -c $< -o $@

run: all
	$(RUN_PREFIX)$(TEST_BIN)

# Fuzz target — FUZZ_ITERATIONS をargv[1]として渡す (argv[1] > getenv > default)
FUZZ_BIN = fuzz_decoder
FUZZ_SRCS = fuzz/fuzz_decoder.cpp
FUZZ_OBJS = $(FUZZ_SRCS:.cpp=.o)
FUZZ_ITERATIONS ?= 10000

fuzz: $(FUZZ_BIN)
	$(RUN_PREFIX)$(FUZZ_BIN) $(FUZZ_ITERATIONS)

$(FUZZ_BIN): $(FUZZ_OBJS) $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_EXTRA) $^ -o $@ $(LDFLAGS)

# Decode-to-JSON CLI tool (for azarashi comparison)
DECODE_BIN = decode_to_json
DECODE_SRCS = tools/decode_to_json.cpp
DECODE_OBJS = $(DECODE_SRCS:.cpp=.o)

decode: $(DECODE_BIN)

$(DECODE_BIN): $(DECODE_OBJS) $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_EXTRA) $^ -o $@ $(LDFLAGS)

# Compare with azarashi (requires: pip install azarashi)
PYTHON ?= python
COMPARE_ARGS ?=
compare-realdata: $(DECODE_BIN)
	$(PYTHON) scripts/compare_with_azarashi.py $(COMPARE_ARGS)

# --- Static Analysis ---
# 静的解析 (時間をかけた厳格なチェック)
check:
	@echo "Running cppcheck..."
	cppcheck --enable=warning,performance,portability --check-level=exhaustive --inline-suppr --suppress=missingIncludeSystem --suppress=*:doctest.h --error-exitcode=1 --std=c++17 -I../src -I. -DAZARAC_NANKAI_MAX_PAGES=63 ../src .
	@echo "Compiling library with strict warnings..."
	$(CXX) $(ANALYSIS_CXXFLAGS) -c $(LIB_SRCS)

# cppcheck の XML レポートをファイルに保存（サマリー生成用）
check-xml:
	@echo "Running cppcheck (XML output)..."
	cppcheck --enable=warning,performance,portability --check-level=exhaustive --inline-suppr --suppress=missingIncludeSystem --suppress=*:doctest.h --xml --xml-version=2 --output-file=cppcheck_report.xml --std=c++17 -I../src -I. -DAZARAC_NANKAI_MAX_PAGES=63 ../src . 2> cppcheck_stderr.log || true
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

# --- AZARAC_ENABLE_* Macro Tests ---
# 全マクロ無効化でもコンパイルが通ることを検証する
MACRO_OFF_FLAGS = \
	-DAZARAC_ENABLE_EEW=0 -DAZARAC_ENABLE_HYPOCENTER=0 \
	-DAZARAC_ENABLE_SEISMIC=0 -DAZARAC_ENABLE_NANKAI=0 \
	-DAZARAC_ENABLE_TSUNAMI=0 -DAZARAC_ENABLE_NW_PAC_TSUNAMI=0 \
	-DAZARAC_ENABLE_VOLCANO=0 -DAZARAC_ENABLE_ASH_FALL=0 \
	-DAZARAC_ENABLE_WEATHER=0 -DAZARAC_ENABLE_FLOOD=0 \
	-DAZARAC_ENABLE_TYPHOON=0 -DAZARAC_ENABLE_MARINE=0 \
	-DAZARAC_ENABLE_DCX_CAMF=0

.PHONY: test-macro-compile test-macro-sizes

test-macro-compile:
	@echo "=== Compiling with ALL AZARAC_ENABLE_* macros disabled ==="
	@mkdir -p $(MACRO_TMP)
	@for f in $(LIB_SRCS); do bn=$$(basename $$f); $(CXX) $(CXXFLAGS) $(MACRO_OFF_FLAGS) -c $$f -o $(MACRO_TMP)/$$bn.o; done
	@rm -rf $(MACRO_TMP)
	@echo "===== SUCCESS: all macros disabled compilation passed ====="

MACRO_TMP = .macro_tmp
QZQSM_SRC = ../src/decoder/DecoderQzqsm.cpp
DCX_SRC   = ../src/decoder/DecoderDcx.cpp
JSON_SRC  = ../src/json/JsonSerializerQzqsm.cpp
JSON_DCX_SRC = ../src/json/JsonSerializerDcx.cpp

# ---- Macro size impact measurement (Unix/Linux only; requires sh + size) ----
ifneq ($(OS),Windows_NT)
test-macro-sizes:
	@echo "=== AZARAC_ENABLE_* Macro Size Impact ==="
	@echo ""
	@echo "Building baseline (all macros ON)..."
	@mkdir -p $(MACRO_TMP)
	$(CXX) $(CXXFLAGS) -c $(QZQSM_SRC) -o $(MACRO_TMP)/bl_qzqsm.o
	$(CXX) $(CXXFLAGS) -c $(DCX_SRC) -o $(MACRO_TMP)/bl_dcx.o
	$(CXX) $(CXXFLAGS) -c $(JSON_SRC) -o $(MACRO_TMP)/bl_json.o
	$(CXX) $(CXXFLAGS) -c $(JSON_DCX_SRC) -o $(MACRO_TMP)/bl_json_dcx.o
	@echo ""
	@echo "=== Size report (.text bytes; host g++ -O0, relative comparison) ==="
	@echo "| Macro disabled | DecoderQzqsm | DecoderDcx | JsonSerQzqsm | JsonSerDcx |"
	@echo "|---------------|-------------|------------|-------------|-----------|"
	@BL_QZQSM=`size $(MACRO_TMP)/bl_qzqsm.o 2>/dev/null | tail -1 | awk '{print $$1}'`; \
	BL_DCX=`size $(MACRO_TMP)/bl_dcx.o 2>/dev/null | tail -1 | awk '{print $$1}'`; \
	BL_JSON=`size $(MACRO_TMP)/bl_json.o 2>/dev/null | tail -1 | awk '{print $$1}'`; \
	BL_JSON_DCX=`size $(MACRO_TMP)/bl_json_dcx.o 2>/dev/null | tail -1 | awk '{print $$1}'`; \
	printf "| %-14s | %-11s | %-10s | %-11s | %-9s |\n" "BASELINE (all ON)" "$$BL_QZQSM" "$$BL_DCX" "$$BL_JSON" "$$BL_JSON_DCX"; \
	set -e; \
	for m in EEW HYPOCENTER SEISMIC NANKAI TSUNAMI NW_PAC_TSUNAMI VOLCANO ASH_FALL WEATHER FLOOD TYPHOON MARINE; do \
		$(CXX) $(CXXFLAGS) -DAZARAC_ENABLE_$$m=0 -c $(QZQSM_SRC) -o $(MACRO_TMP)/$$m.o; \
		qz=`size $(MACRO_TMP)/$$m.o 2>/dev/null | tail -1 | awk '{print $$1}'`; \
		diff_qz=$$((BL_QZQSM - qz)); \
		$(CXX) $(CXXFLAGS) -DAZARAC_ENABLE_$$m=0 -c $(JSON_SRC) -o $(MACRO_TMP)/j$$m.o; \
		js=`size $(MACRO_TMP)/j$$m.o 2>/dev/null | tail -1 | awk '{print $$1}'`; \
		diff_js=$$((BL_JSON - js)); \
		printf "| %-14s | %-5s(-%4s) | %-10s | %-5s(-%5s) | %-9s |\n" "ENABLE_$${m}=0" "$$qz" "$$diff_qz" "---" "$$js" "$$diff_js" "---"; \
	done; \
	$(CXX) $(CXXFLAGS) -DAZARAC_ENABLE_DCX_CAMF=0 -c $(DCX_SRC) -o $(MACRO_TMP)/dcx_off.o; \
	$(CXX) $(CXXFLAGS) -DAZARAC_ENABLE_DCX_CAMF=0 -c $(JSON_DCX_SRC) -o $(MACRO_TMP)/json_dcx_off.o; \
	dcx=`size $(MACRO_TMP)/dcx_off.o 2>/dev/null | tail -1 | awk '{print $$1}'`; \
	json_dcx=`size $(MACRO_TMP)/json_dcx_off.o 2>/dev/null | tail -1 | awk '{print $$1}'`; \
	diff_dcx=$$((BL_DCX - dcx)); \
	diff_json_dcx=$$((BL_JSON_DCX - json_dcx)); \
	printf "| %-14s | %-11s | %-5s(-%4s) | %-11s | %-5s(-%4s) |\n" "ENABLE_DCX_CAMF=0" "---" "$$dcx" "$$diff_dcx" "---" "$$json_dcx" "$$diff_json_dcx"
	@echo "|---------------|-------------|------------|-------------|-----------|"
	@echo "===== Measurement complete ====="
	@rm -rf $(MACRO_TMP)
else
# Windows fallback: just compile and show raw size output
test-macro-sizes:
	@echo "=== AZARAC_ENABLE_* Macro Size Impact (Windows, raw sizes) ==="
	@if not exist $(MACRO_TMP) mkdir $(MACRO_TMP)
	$(CXX) $(CXXFLAGS) -c $(QZQSM_SRC) -o $(MACRO_TMP)/bl_qzqsm.o
	$(CXX) $(CXXFLAGS) -c $(DCX_SRC) -o $(MACRO_TMP)/bl_dcx.o
	$(CXX) $(CXXFLAGS) -c $(JSON_SRC) -o $(MACRO_TMP)/bl_json.o
	$(CXX) $(CXXFLAGS) -c $(JSON_DCX_SRC) -o $(MACRO_TMP)/bl_json_dcx.o
	@echo "Baseline (all ON):"
	-@size $(MACRO_TMP)/bl_qzqsm.o
	-@size $(MACRO_TMP)/bl_dcx.o
	-@size $(MACRO_TMP)/bl_json.o
	-@size $(MACRO_TMP)/bl_json_dcx.o
	@echo "Individual macros disabled (compiling & sizing):"
	-@for %%m in (EEW HYPOCENTER SEISMIC NANKAI TSUNAMI NW_PAC_TSUNAMI VOLCANO ASH_FALL WEATHER FLOOD TYPHOON MARINE) do @( \
		$(CXX) $(CXXFLAGS) -DAZARAC_ENABLE_%%m=0 -c $(QZQSM_SRC) -o $(MACRO_TMP)/%%m.o 2>nul & \
		echo DecoderQzqsm with %%%%m=0: & \
		size $(MACRO_TMP)/%%m.o )
	-@$(CXX) $(CXXFLAGS) -DAZARAC_ENABLE_DCX_CAMF=0 -c $(DCX_SRC) -o $(MACRO_TMP)/dcx_off.o 2>nul
	-@echo DecoderDcx with DCX_CAMF=0: & size $(MACRO_TMP)/dcx_off.o
	-@$(CXX) $(CXXFLAGS) -DAZARAC_ENABLE_DCX_CAMF=0 -c $(JSON_DCX_SRC) -o $(MACRO_TMP)/json_dcx_off.o 2>nul
	-@echo JsonSerializerDcx with DCX_CAMF=0: & size $(MACRO_TMP)/json_dcx_off.o
	@echo "===== Measurement complete ====="
	@-rmdir /s /q $(MACRO_TMP) 2>nul
endif

# ---- Macro disable runtime tests (compile + run for each disabled macro) ----
# 各マクロを個別に無効化してビルド・実行し、無効化されたデコーダが
# 正しくエラー（unsupported_reason = DisabledAtCompileTime）を返すことを検証する。
# 全 13 マクロを個別にテストする（カバレッジ優先）。

MACRO_NAMES = EEW HYPOCENTER SEISMIC NANKAI TSUNAMI NW_PAC_TSUNAMI VOLCANO ASH_FALL WEATHER FLOOD TYPHOON MARINE DCX_CAMF

.PHONY: macro

# Individual macro disabled test: clean → rebuild with macro=0 → run
# 各マクロの無効化ビルドは独立して行う（clean → build → run）
ifeq ($(OS),Windows_NT)
macro:
	@echo === AZARAC_ENABLE_* Macro Runtime Tests ===
	@echo Testing all $(words $(MACRO_NAMES)) macros individually...
	@$(MAKE) _macro-test-one M=EEW
	@$(MAKE) _macro-test-one M=HYPOCENTER
	@$(MAKE) _macro-test-one M=SEISMIC
	@$(MAKE) _macro-test-one M=NANKAI
	@$(MAKE) _macro-test-one M=TSUNAMI
	@$(MAKE) _macro-test-one M=NW_PAC_TSUNAMI
	@$(MAKE) _macro-test-one M=VOLCANO
	@$(MAKE) _macro-test-one M=ASH_FALL
	@$(MAKE) _macro-test-one M=WEATHER
	@$(MAKE) _macro-test-one M=FLOOD
	@$(MAKE) _macro-test-one M=TYPHOON
	@$(MAKE) _macro-test-one M=MARINE
	@$(MAKE) _macro-test-one M=DCX_CAMF
	@echo ===== All macro runtime tests passed =====

.PHONY: _macro-test-one

_macro-test-one:
	@echo Testing AZARAC_ENABLE_$(M)=0...
	@$(MAKE) clean 2>$(DEVNULL)
	@$(MAKE) -B CXXFLAGS="$(CXXFLAGS) -DAZARAC_ENABLE_$(M)=0" run
else
macro:
	@echo "=== AZARAC_ENABLE_* Macro Runtime Tests ==="
	@echo "Testing all $(words $(MACRO_NAMES)) macros individually..."
	@for m in $(MACRO_NAMES); do \
		echo ""; \
		echo "--- Testing AZARAC_ENABLE_$${m}=0 ---"; \
		$(MAKE) clean 2>$(DEVNULL); \
		$(MAKE) CXXFLAGS="$(CXXFLAGS) -DAZARAC_ENABLE_$${m}=0" run || exit 1; \
	done
	@echo "===== All macro runtime tests passed ====="
endif

# Include dependency files
-include $(TEST_OBJS:.o=.d) $(LIB_OBJS:.o=.d) $(FUZZ_OBJS:.o=.d) $(DECODE_OBJS:.o=.d)

clean:
	-@$(RM) *.o *.exe *.d *.gcno *.gcda massif.out cppcheck_report.xml cppcheck_stderr.log coverage_report.json
	-@$(RM) core/*.o core/*.d core/*.gcno core/*.gcda
	-@$(RM) decoder/*.o decoder/*.d decoder/*.gcno decoder/*.gcda
	-@$(RM) framer/*.o framer/*.d framer/*.gcno framer/*.gcda
	-@$(RM) json/*.o json/*.d json/*.gcno json/*.gcda
	-@$(RM) integration/*.o integration/*.d integration/*.gcno integration/*.gcda
	-@$(RM) internal/*.o internal/*.d internal/*.gcno internal/*.gcda
	-@$(RM) fuzz/*.o fuzz/*.d fuzz/*.gcno fuzz/*.gcda
	-@$(RM) tools/*.o tools/*.d tools/*.gcno tools/*.gcda
	-@$(RM) scripts/*.o scripts/*.d scripts/*.gcno scripts/*.gcda

# ---- PROGMEM stub (AVR branch semantics test on host) ----
# Compiles all tests with __AVR__ defined and a stub avr/pgmspace.h so the
# PROGMEM code paths (memcpy_P / pgm_read_dword) exercise on the host.
# AVR presets that conflict with test assumptions (BUFFERS=1, DEDUP_SLOTS=4)
# are neutralized.
pgm-stub:
	$(MAKE) clean
	$(MAKE) CXXFLAGS="-std=c++17 -Wall -Wextra -Istub -I../src -I. -DARDUINO=0 -D__AVR__ -DAZARAC_AVR_STUB -DAZARAC_LANG_JA=1 -DAZARAC_LANG_EN=1 -DAZARAC_NANKAI_MAX_PAGES=63 -DAZARAC_NANKAI_BUFFERS=4 -DAZARAC_DEDUP_SLOTS=8 -DAZARAC_ENABLE_EEW=1 -DAZARAC_ENABLE_HYPOCENTER=1 -DAZARAC_ENABLE_SEISMIC=1 -DAZARAC_ENABLE_NANKAI=1 -DAZARAC_ENABLE_TSUNAMI=1 -DAZARAC_ENABLE_NW_PAC_TSUNAMI=1 -DAZARAC_ENABLE_VOLCANO=1 -DAZARAC_ENABLE_ASH_FALL=1 -DAZARAC_ENABLE_WEATHER=1 -DAZARAC_ENABLE_FLOOD=1 -DAZARAC_ENABLE_TYPHOON=1 -DAZARAC_ENABLE_MARINE=1 -DAZARAC_ENABLE_DCX_CAMF=1 -MMD -MP -g"
	$(RUN_PREFIX)$(TEST_BIN)
