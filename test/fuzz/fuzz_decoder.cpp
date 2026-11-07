// ファジーテスト: ランダム入力に対するデコーダの堅牢性テストビルド・実行: `make fuzz`（FUZZ_ITERATIONS でイテレーション数を指定可）。
// ライブラリ構成（ソース一覧・フラグ）は test/Makefile が唯一の正。
//
// シード: 既定は random_device。FUZZ_SEED で固定すると全テストが決定的になる（クラッシュ時の再現に使う。失敗時の出力に再現コマンドも出る）。

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <cerrno>
#include <climits>
#include <random>
#include <vector>
#include <string>
#include <chrono>

#if defined(_WIN32)
#include <windows.h>
#include <psapi.h>
#endif

#define ARDUINO 0
#include "azaraC.h"
#include "decoder/Decoder.h"
#include "framer/NmeaFramer.h"
#include "framer/UbxFramer.h"
#include "json/JsonSerializer.h"
#include "internal/PrintShim.h"
#include "test_helpers.h"

using namespace azaraC;
using namespace azaraC::internal;

// テスト名を記録するための最大例外数
#define MAX_EXCEPTION_LOG 100

// MemoryTracker: RAIIパターンによるメモリ使用量自動計測
#if defined(__linux__)
#include <fstream>
#include <sstream>
#elif defined(__APPLE__)
#include <mach/mach.h>
#endif

class MemoryTracker {
public:
    MemoryTracker() {
        start_kb_ = get_current_memory_kb();
        peak_kb_ = start_kb_;
        printf("Memory at start: %zu KB\n\n", start_kb_);
    }

    ~MemoryTracker() {
        end_kb_ = get_current_memory_kb();
        print_report();
    }

    void checkpoint() {
        size_t current = get_current_memory_kb();
        if (current > peak_kb_) {
            peak_kb_ = current;
        }
    }

private:
    size_t start_kb_ = 0;
    size_t end_kb_ = 0;
    size_t peak_kb_ = 0;

    static size_t get_current_memory_kb() {
#if defined(__linux__)
        std::ifstream status("/proc/self/status");
        std::string line;
        while (std::getline(status, line)) {
            if (line.size() >= 6 && line.substr(0, 6) == "VmRSS:") {
                std::istringstream iss(line);
                std::string label;
                size_t value;
                std::string unit;
                iss >> label >> value >> unit;
                return value;
            }
        }
        return 0;
#elif defined(__APPLE__)
        mach_task_basic_info info;
        mach_msg_type_number_t size = MACH_TASK_BASIC_INFO_COUNT;
        if (task_info(mach_task_self(), MACH_TASK_BASIC_INFO, (task_info_t)&info, &size) == KERN_SUCCESS) {
            return info.resident_size / 1024;
        }
        return 0;
#elif defined(_WIN32)
        PROCESS_MEMORY_COUNTERS pmc;
        if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
            return pmc.WorkingSetSize / 1024;
        }
        return 0;
#else
        return 0;
#endif
    }

    void print_report() const {
        printf("\n--- Memory Usage ---\n");
        if (start_kb_ > 0) {
            printf("Start: %zu KB\n", start_kb_);
            printf("End:   %zu KB\n", end_kb_);
            printf("Peak:  %zu KB\n", peak_kb_);
            printf("Delta: %lld KB\n", (long long)end_kb_ - (long long)start_kb_);
        } else {
            printf("Memory measurement not available on this platform\n");
        }
    }
};

struct ExceptionInfo {
    const char* test_name;
    uint64_t iteration;
};

struct FuzzStats {
    uint64_t total_iterations = 0;
    uint64_t valid_frames = 0;
    uint64_t invalid_crc = 0;
    uint64_t invalid_preamble = 0;
    uint64_t framer_rejected = 0;
    uint64_t decode_success = 0;
    uint64_t decode_fail = 0;
    uint64_t mt43_count = 0;
    uint64_t mt44_count = 0;
    uint64_t exceptions = 0;
    uint64_t warnings = 0;
    uint64_t nmea_frames = 0;
    uint64_t ubx_frames = 0;
    uint64_t serialized = 0;

    // テストごとの例外記録
    ExceptionInfo exception_log[MAX_EXCEPTION_LOG];
    int exception_log_count = 0;

    void log_exception(const char* test_name, uint64_t iter) {
        if (exception_log_count < MAX_EXCEPTION_LOG) {
            exception_log[exception_log_count++] = {test_name, iter};
        }
        exceptions++;
    }

    void log_warning(const char* test_name, uint64_t iter) {
        if (exception_log_count < MAX_EXCEPTION_LOG) {
            exception_log[exception_log_count++] = {test_name, iter};
        }
        warnings++;
    }

    void print() const {
        printf("\n=== Fuzz Test Statistics ===\n");
        printf("Total iterations:    %llu\n", (unsigned long long)total_iterations);
        printf("Valid frames:        %llu (%.2f%%)\n",
               (unsigned long long)valid_frames,
               total_iterations > 0 ? 100.0 * valid_frames / total_iterations : 0);
        printf("  NMEA frames:       %llu\n", (unsigned long long)nmea_frames);
        printf("  UBX frames:        %llu\n", (unsigned long long)ubx_frames);
        printf("Invalid CRC:         %llu\n", (unsigned long long)invalid_crc);
        printf("Invalid preamble:    %llu\n", (unsigned long long)invalid_preamble);
        printf("Framer rejects:      %llu\n", (unsigned long long)framer_rejected);
        printf("Decode success:      %llu\n", (unsigned long long)decode_success);
        printf("  MT=43:             %llu\n", (unsigned long long)mt43_count);
        printf("  MT=44:             %llu\n", (unsigned long long)mt44_count);
        printf("Decode fail:         %llu\n", (unsigned long long)decode_fail);
        printf("Serialized:          %llu\n", (unsigned long long)serialized);
        printf("Exceptions caught:   %llu\n", (unsigned long long)exceptions);
        printf("Warnings:            %llu\n", (unsigned long long)warnings);

        if (exception_log_count > 0) {
            printf("\n--- Exception Details (first %d) ---\n", exception_log_count);
            for (int i = 0; i < exception_log_count; i++) {
                printf("  [%s] iteration %llu\n",
                       exception_log[i].test_name,
                       (unsigned long long)exception_log[i].iteration);
            }
        }
        printf("===========================\n");
    }
};


static void set_valid_preamble(uint8_t* bits, std::mt19937& rng) {
    std::uniform_int_distribution<int> dist(0, 2);
    uint8_t preambles[] = {0x53, 0x9A, 0xC6};
    bits[0] = preambles[dist(rng)];
}

static void set_valid_msg_type(uint8_t* bits, std::mt19937& rng) {
    std::uniform_int_distribution<int> dist(0, 1);
    uint8_t types[] = {43, 44};
    uint8_t mt = types[dist(rng)];
    // MTはビット8-13に設定
    for (int i = 0; i < 6; i++) {
        if ((mt >> (5 - i)) & 1) {
            bits[(8 + i) / 8] |= (0x80 >> ((8 + i) % 8));
        } else {
            bits[(8 + i) / 8] &= ~(0x80 >> ((8 + i) % 8));
        }
    }
}

static void set_valid_crc(uint8_t* bits) {
    uint32_t crc = crc24qRef(bits, 226);
    // CRCはビット226-249に設定
    for (int i = 0; i < 24; i++) {
        if ((crc >> (23 - i)) & 1) {
            bits[(226 + i) / 8] |= (0x80 >> ((226 + i) % 8));
        } else {
            bits[(226 + i) / 8] &= ~(0x80 >> ((226 + i) % 8));
        }
    }
}

// テスト1: 完全ランダムデータ
static void test_random_raw_data(FuzzStats& stats, std::mt19937& rng, int iterations) {
    printf("Test 1: Random raw data (%d iterations)...\n", iterations);

    for (int i = 0; i < iterations; i++) {
        try {
            uint8_t bits[32];
            generate_random_nav_bits(bits, sizeof(bits), rng);

            Frame frame;
            frame.svid = 193;
            memcpy(frame.bits, bits, 32);

            Decoder decoder;
            Message msg;
            decoder.decode(frame, msg, 0);

            stats.total_iterations++;
        } catch (...) {
            stats.log_exception("test_random_raw_data", i);
        }
    }
    printf("  Completed.\n");
}

// テスト2: 有効なプリアンブル + ランダムデータ
static void test_valid_preamble(FuzzStats& stats, std::mt19937& rng, int iterations) {
    printf("Test 2: Valid preamble + random data (%d iterations)...\n", iterations);

    for (int i = 0; i < iterations; i++) {
        try {
            uint8_t bits[32];
            generate_random_nav_bits(bits, sizeof(bits), rng);
            set_valid_preamble(bits, rng);

            Frame frame;
            frame.svid = 193;
            memcpy(frame.bits, bits, 32);

            Decoder decoder;
            Message msg;
            decoder.decode(frame, msg, 0);

            stats.total_iterations++;

        } catch (...) {
            stats.log_exception("test_valid_preamble", i);
        }
    }
    printf("  Completed.\n");
}

// テスト3: 有効なプリアンブル + 有効なMSG_TYPE + ランダムデータ
static void test_valid_preamble_and_type(FuzzStats& stats, std::mt19937& rng, int iterations) {
    printf("Test 3: Valid preamble + valid msg_type + random data (%d iterations)...\n", iterations);

    for (int i = 0; i < iterations; i++) {
        try {
            uint8_t bits[32];
            generate_random_nav_bits(bits, sizeof(bits), rng);
            set_valid_preamble(bits, rng);
            set_valid_msg_type(bits, rng);

            Frame frame;
            frame.svid = 193;
            memcpy(frame.bits, bits, 32);

            Decoder decoder;
            Message msg;
            decoder.decode(frame, msg, 0);

            stats.total_iterations++;
        } catch (...) {
            stats.log_exception("test_valid_preamble_and_type", i);
        }
    }
    printf("  Completed.\n");
}

// テスト4: 有効なフレーム（CRC正しい）- MT=43
static void test_valid_frames_mt43(FuzzStats& stats, std::mt19937& rng, int iterations) {
    printf("Test 4a: Valid frames MT=43 with correct CRC (%d iterations)...\n", iterations);

    for (int i = 0; i < iterations; i++) {
        try {
            uint8_t bits[32];
            generate_random_nav_bits(bits, sizeof(bits), rng);
            set_valid_preamble(bits, rng);
            for (int j = 0; j < 6; j++) {
                if ((43 >> (5 - j)) & 1) {
                    bits[(8 + j) / 8] |= (0x80 >> ((8 + j) % 8));
                } else {
                    bits[(8 + j) / 8] &= ~(0x80 >> ((8 + j) % 8));
                }
            }
            set_valid_crc(bits);

            Frame frame;
            frame.svid = 193;
            memcpy(frame.bits, bits, 32);

            Decoder decoder;
            Message msg;
            bool result = decoder.decode(frame, msg, 1704067200u);

            stats.total_iterations++;

            if (result) {
                stats.valid_frames++;
                stats.decode_success++;
                stats.mt43_count++;
            } else {
                stats.decode_fail++;
            }
        } catch (...) {
            stats.log_exception("test_valid_frames_mt43", i);
        }
    }
    printf("  Completed.\n");
}

// テスト4b: 有効なフレーム（CRC正しい）- MT=44 (DCX)
static void test_valid_frames_mt44(FuzzStats& stats, std::mt19937& rng, int iterations) {
    printf("Test 4b: Valid frames MT=44 (DCX) with correct CRC (%d iterations)...\n", iterations);

    for (int i = 0; i < iterations; i++) {
        try {
            uint8_t bits[32];
            generate_random_nav_bits(bits, sizeof(bits), rng);
            set_valid_preamble(bits, rng);
            for (int j = 0; j < 6; j++) {
                if ((44 >> (5 - j)) & 1) {
                    bits[(8 + j) / 8] |= (0x80 >> ((8 + j) % 8));
                } else {
                    bits[(8 + j) / 8] &= ~(0x80 >> ((8 + j) % 8));
                }
            }
            set_valid_crc(bits);

            Frame frame;
            frame.svid = 193;
            memcpy(frame.bits, bits, 32);

            Decoder decoder;
            Message msg;
            bool result = decoder.decode(frame, msg, 1704067200u);

            stats.total_iterations++;

            if (result) {
                stats.valid_frames++;
                stats.decode_success++;
                stats.mt44_count++;
            } else {
                stats.decode_fail++;
            }
        } catch (...) {
            stats.log_exception("test_valid_frames_mt44", i);
        }
    }
    printf("  Completed.\n");
}

// テスト5: NMEAフレーマーへのランダム入力
static void test_nmea_framer(FuzzStats& stats, std::mt19937& rng, int iterations) {
    printf("Test 5: NMEA framer with random data (%d iterations)...\n", iterations);

    for (int i = 0; i < iterations; i++) {
        try {
            uint8_t bits[32];
            generate_random_nav_bits(bits, sizeof(bits), rng);
            set_valid_preamble(bits, rng);
            set_valid_msg_type(bits, rng);
            set_valid_crc(bits);

            std::string nmea = makeNmeaQzqsm(63, bits);

            NmeaFramer framer;
            Frame frame;
            bool found = false;

            for (char c : nmea) {
                if (framer.feed((uint8_t)c, frame)) {
                    found = true;
                    break;
                }
            }

            stats.total_iterations++;

            if (found) {
                stats.nmea_frames++;
                Decoder decoder;
                Message msg;
                decoder.decode(frame, msg, 1704067200u);
            }
        } catch (...) {
            stats.log_exception("test_nmea_framer", i);
        }
    }
    printf("  Completed.\n");
}

// テスト6: UBXフレーマーへのランダム入力
static void test_ubx_framer(FuzzStats& stats, std::mt19937& rng, int iterations) {
    printf("Test 6: UBX framer with random data (%d iterations)...\n", iterations);

    for (int i = 0; i < iterations; i++) {
        try {
            uint8_t bits[32];
            generate_random_nav_bits(bits, sizeof(bits), rng);
            set_valid_preamble(bits, rng);
            set_valid_msg_type(bits, rng);
            set_valid_crc(bits);

            auto ubx = makeUbxSfrbx(193, bits);

            UbxFramer framer;
            Frame frame;
            bool found = false;

            for (auto b : ubx) {
                if (framer.feed(b, frame)) {
                    found = true;
                    break;
                }
            }

            stats.total_iterations++;

            if (found) {
                stats.ubx_frames++;
                Decoder decoder;
                Message msg;
                decoder.decode(frame, msg, 1704067200u);
            }
        } catch (...) {
            stats.log_exception("test_ubx_framer", i);
        }
    }
    printf("  Completed.\n");
}

// テスト7: 境界値テスト
static void test_boundary_values(FuzzStats& stats, std::mt19937& rng) {
    printf("Test 7: Boundary values...\n");

    {
        try {
            uint8_t bits[32] = {0};
            Frame frame;
            frame.svid = 193;
            memcpy(frame.bits, bits, 32);

            Decoder decoder;
            Message msg;
            decoder.decode(frame, msg, 0);
            stats.total_iterations++;
        } catch (...) {
            stats.log_exception("test_boundary_all_zeros", 0);
        }
    }

    {
        try {
            uint8_t bits[32];
            memset(bits, 0xFF, sizeof(bits));
            Frame frame;
            frame.svid = 193;
            memcpy(frame.bits, bits, 32);

            Decoder decoder;
            Message msg;
            decoder.decode(frame, msg, 0);
            stats.total_iterations++;
        } catch (...) {
            stats.log_exception("test_boundary_all_ones", 0);
        }
    }

    uint8_t boundary_preambles[] = {0x00, 0x52, 0x53, 0x54, 0x99, 0x9A, 0x9B, 0xC5, 0xC6, 0xC7, 0xFF};
    for (uint8_t preamble : boundary_preambles) {
        try {
            uint8_t bits[32] = {0};
            bits[0] = preamble;
            Frame frame;
            frame.svid = 193;
            memcpy(frame.bits, bits, 32);

            Decoder decoder;
            Message msg;
            decoder.decode(frame, msg, 0);
            stats.total_iterations++;
        } catch (...) {
            stats.log_exception("test_boundary_preamble", preamble);
        }
    }

    for (uint8_t mt = 0; mt < 64; mt++) {
        if (mt == 43 || mt == 44) continue; // 有効なタイプはスキップ

        try {
            uint8_t bits[32] = {0};
            bits[0] = 0x53; // 有効なプリアンブル
            // MTを設定 (ビット8-13)
            for (int i = 0; i < 6; i++) {
                if ((mt >> (5 - i)) & 1) {
                    bits[(8 + i) / 8] |= (0x80 >> ((8 + i) % 8));
                }
            }

            Frame frame;
            frame.svid = 193;
            memcpy(frame.bits, bits, 32);

            Decoder decoder;
            Message msg;
            decoder.decode(frame, msg, 0);
            stats.total_iterations++;
        } catch (...) {
            stats.log_exception("test_boundary_invalid_mt", mt);
        }
    }

    // テストケース: SVID境界値 (QZSS有効範囲: 193-202)
    uint8_t boundary_svids[] = {0, 1, 192, 193, 194, 200, 201, 202, 203, 254, 255};
    for (uint8_t svid : boundary_svids) {
        try {
            uint8_t bits[32] = {0};
            bits[0] = 0x53;
            set_valid_msg_type(bits, rng);
            set_valid_crc(bits);

            Frame frame;
            frame.svid = svid;
            memcpy(frame.bits, bits, 32);

            Decoder decoder;
            Message msg;
            decoder.decode(frame, msg, 1704067200u);
            stats.total_iterations++;
        } catch (...) {
            stats.log_exception("test_boundary_svid", svid);
        }
    }

    uint32_t boundary_times[] = {
        0,                    // 未初期化
        1,                    // 最小値
        946684800u - 1,       // 2000-01-01 00:00:00 UTC - 1秒
        946684800u,           // 2000-01-01 00:00:00 UTC
        946684800u + 1,       // 2000-01-01 00:00:00 UTC + 1秒
        1704067200u,          // 2024-01-01 00:00:00 UTC
        1704067200u - 86400u, // 閏年境界前
        1704067200u + 86400u, // 閏年境界後
        4102444800u - 1,      // 2100-01-01 00:00:00 UTC - 1秒 (閏年でない年)
        0xFFFFFFFFu           // 最大値
    };
    for (uint32_t report_unix : boundary_times) {
        try {
            uint8_t bits[32] = {0};
            bits[0] = 0x53;
            set_valid_msg_type(bits, rng);
            set_valid_crc(bits);

            Frame frame;
            frame.svid = 193;
            memcpy(frame.bits, bits, 32);

            Decoder decoder;
            Message msg;
            decoder.decode(frame, msg, report_unix);
            stats.total_iterations++;
        } catch (...) {
            stats.log_exception("test_boundary_report_unix", report_unix);
        }
    }

    printf("  Completed.\n");
}

// テスト8: 長時間実行テスト（メモリリーク検出）
static void test_long_running(FuzzStats& stats, std::mt19937& rng, int iterations) {
    printf("Test 8: Long running test (%d iterations)...\n", iterations);

    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < iterations; i++) {
        try {
            uint8_t bits[32];
            generate_random_nav_bits(bits, sizeof(bits), rng);
            set_valid_preamble(bits, rng);
            set_valid_msg_type(bits, rng);
            set_valid_crc(bits);

            std::string nmea = makeNmeaQzqsm(63, bits);

            NmeaFramer framer;
            Frame frame;

            for (char c : nmea) {
                if (framer.feed((uint8_t)c, frame)) {
                    Decoder decoder;
                    Message msg;
                    decoder.decode(frame, msg, 1704067200u);
                    break;
                }
            }

            stats.total_iterations++;

            if (i % 10000 == 0 && i > 0) {
                auto now = std::chrono::steady_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
                printf("  Progress: %d/%d (%llds elapsed)\n", i, iterations, (long long)elapsed);
            }
        } catch (...) {
            stats.log_exception("test_long_running", i);
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    printf("  Completed in %llds.\n", (long long)elapsed);
}

// テスト9: 破損フレームテスト
static void test_corrupted_frames(FuzzStats& stats, std::mt19937& rng, int iterations) {
    printf("Test 9: Corrupted frame test (%d iterations)...\n", iterations);

    std::uniform_int_distribution<int> dist(0, 255);
    std::uniform_int_distribution<int> bit_dist(0, 249);

    for (int i = 0; i < iterations; i++) {
        try {
            uint8_t bits[32];
            generate_random_nav_bits(bits, sizeof(bits), rng);
            set_valid_preamble(bits, rng);
            set_valid_msg_type(bits, rng);
            set_valid_crc(bits);

            // ランダムなビットを反転（CRC破損）。
            // 1/8 はプリアンブル、1/8 はデータ部を確実に壊し、両方の拒否経路が必ず観測されるようにする。
            int corrupt_pos;
            if (i % 8 == 0)      corrupt_pos = (i / 8) % 8;      // bit 0..7（プリアンブル）
            else if (i % 8 == 1) corrupt_pos = 8 + (i % 218);    // bit 8..225（CRC 被覆域）
            else                 corrupt_pos = bit_dist(rng);
            bits[corrupt_pos / 8] ^= (0x80 >> (corrupt_pos % 8));

            Frame frame;
            frame.svid = 193;
            memcpy(frame.bits, bits, 32);

            Decoder decoder;
            Message msg;
            const bool ok = decoder.decode(frame, msg, 1704067200u);

            const uint8_t pre = bits[0];
            const bool pre_ok = (pre == 0x53 || pre == 0x9A || pre == 0xC6);
            if (!pre_ok) stats.invalid_preamble++;
            else         stats.invalid_crc++;

            // 1 bit 反転で CRC-24Q が通ることはない（線形符号）。通ったら実装のバグ。
            if (ok) {
                printf("  FAIL: corrupted frame decoded successfully at iteration %d\n", i);
                stats.log_exception("test_corrupted_frames_unexpected_success", i);
            }

            stats.total_iterations++;
        } catch (...) {
            stats.log_exception("test_corrupted_frames", i);
        }
    }
    printf("  Completed.\n");
}

// テスト10: 破損NMEAフレームテスト
static void test_corrupted_nmea(FuzzStats& stats, std::mt19937& rng, int iterations) {
    printf("Test 10: Corrupted NMEA frame test (%d iterations)...\n", iterations);

    std::uniform_int_distribution<int> dist(0, 255);

    for (int i = 0; i < iterations; i++) {
        try {
            uint8_t bits[32];
            generate_random_nav_bits(bits, sizeof(bits), rng);
            set_valid_preamble(bits, rng);
            set_valid_msg_type(bits, rng);
            set_valid_crc(bits);

            std::string nmea = makeNmeaQzqsm(63, bits);

            // NMEAを破損させる（ランダムな位置の文字を変更）
            if (nmea.size() > 10) {
                std::uniform_int_distribution<size_t> pos_dist(1, nmea.size() - 5);
                size_t pos = pos_dist(rng);
                nmea[pos] = static_cast<char>(dist(rng));
            }

            NmeaFramer framer;
            Frame frame;
            bool found = false;

            for (char c : nmea) {
                if (framer.feed((uint8_t)c, frame)) {
                    found = true;
                    break;
                }
            }

            if (found) {
                Decoder decoder;
                Message msg;
                if (!decoder.decode(frame, msg, 1704067200u)) stats.invalid_crc++;
            } else {
                stats.framer_rejected++;
            }

            stats.total_iterations++;
        } catch (...) {
            stats.log_exception("test_corrupted_nmea", i);
        }
    }
    printf("  Completed.\n");
}

// テスト11: 破損UBXフレームテスト
static void test_corrupted_ubx(FuzzStats& stats, std::mt19937& rng, int iterations) {
    printf("Test 11: Corrupted UBX frame test (%d iterations)...\n", iterations);

    std::uniform_int_distribution<int> dist(0, 255);

    for (int i = 0; i < iterations; i++) {
        try {
            uint8_t bits[32];
            generate_random_nav_bits(bits, sizeof(bits), rng);
            set_valid_preamble(bits, rng);
            set_valid_msg_type(bits, rng);
            set_valid_crc(bits);

            auto ubx = makeUbxSfrbx(193, bits);

            // UBXを破損させる（ランダムな位置のバイトを変更）
            if (ubx.size() > 10) {
                std::uniform_int_distribution<size_t> pos_dist(6, ubx.size() - 3);
                size_t pos = pos_dist(rng);
                ubx[pos] = static_cast<uint8_t>(dist(rng));
            }

            UbxFramer framer;
            Frame frame;
            bool found = false;

            for (auto b : ubx) {
                if (framer.feed(b, frame)) {
                    found = true;
                    break;
                }
            }

            if (found) {
                Decoder decoder;
                Message msg;
                if (!decoder.decode(frame, msg, 1704067200u)) stats.invalid_crc++;
            } else {
                stats.framer_rejected++;
            }

            stats.total_iterations++;
        } catch (...) {
            stats.log_exception("test_corrupted_ubx", i);
        }
    }
    printf("  Completed.\n");
}

// テスト12: デコード失敗時のMessage状態検証
static void test_decode_failure_state(FuzzStats& stats, std::mt19937& rng, int iterations) {
    printf("Test 12: Decode failure state verification (%d iterations)...\n", iterations);

    for (int i = 0; i < iterations; i++) {
        try {
            uint8_t bits[32];
            generate_random_nav_bits(bits, sizeof(bits), rng);
            // 無効なプリアンブル（CRC不一致を誘発）
            bits[0] = 0x00;

            Frame frame;
            frame.svid = 193;
            memcpy(frame.bits, bits, 32);

            Decoder decoder;
            Message msg;
            bool result = decoder.decode(frame, msg, 0);

            // CRC不一致で false。CRC失敗時は svid 未設定のまま false が返る（正常）ため、ここでは valid==false のみ検証する。
            if (!result && msg.valid) {
                stats.log_warning("test_decode_failure_state", i);
                printf("  FAIL: valid should be false on decode failure at iteration %d\n", i);
            }

            stats.total_iterations++;
        } catch (...) {
            stats.log_exception("test_decode_failure_state", i);
        }
    }
    printf("  Completed.\n");
}

// テスト13: NMEA $ 文字消去テスト (fuzz_and_perf.md #2)
static void test_corrupted_nmea_dollar(FuzzStats& stats, std::mt19937& rng, int iterations) {
    printf("Test 13: NMEA $ removal test (%d iterations)...\n", iterations);

    for (int i = 0; i < iterations; i++) {
        try {
            uint8_t bits[32];
            generate_random_nav_bits(bits, sizeof(bits), rng);
            set_valid_preamble(bits, rng);
            set_valid_msg_type(bits, rng);
            set_valid_crc(bits);

            std::string nmea = makeNmeaQzqsm(63, bits);

            if (nmea.size() > 0 && nmea[0] == '$') {
                nmea = nmea.substr(1);
            }

            NmeaFramer framer;
            Frame frame;
            bool found = false;

            for (char c : nmea) {
                if (framer.feed((uint8_t)c, frame)) {
                    found = true;
                    break;
                }
            }

            // '$' が無ければ検出してはならない
            if (found) {
                printf("  FAIL: NMEA frame detected without '$' at iteration %d\n", i);
                stats.log_exception("test_corrupted_nmea_dollar_unexpected_found", i);
                stats.total_iterations++;
                continue;
            }

            stats.total_iterations++;
        } catch (...) {
            stats.log_exception("test_corrupted_nmea_dollar", i);
        }
    }
    printf("  Completed.\n");
}

// テスト14: UBX SYNC 文字破損テスト (fuzz_and_perf.md #3)
static void test_corrupted_ubx_sync(FuzzStats& stats, std::mt19937& rng, int iterations) {
    printf("Test 14: UBX SYNC corruption test (%d iterations)...\n", iterations);

    for (int i = 0; i < iterations; i++) {
        try {
            uint8_t bits[32];
            generate_random_nav_bits(bits, sizeof(bits), rng);
            set_valid_preamble(bits, rng);
            set_valid_msg_type(bits, rng);
            set_valid_crc(bits);

            auto ubx = makeUbxSfrbx(193, bits);

            if (ubx.size() > 0) {
                ubx[0] = 0x00;  // Should be 0xB5
            }

            UbxFramer framer;
            Frame frame;
            bool found = false;

            for (auto b : ubx) {
                if (framer.feed(b, frame)) {
                    found = true;
                    break;
                }
            }

            if (found) {
                printf("  FAIL: UBX frame detected with corrupted SYNC at iteration %d\n", i);
                stats.log_exception("test_corrupted_ubx_sync_unexpected_found", i);
                stats.total_iterations++;
                continue;
            }

            stats.total_iterations++;
        } catch (...) {
            stats.log_exception("test_corrupted_ubx_sync", i);
        }
    }
    printf("  Completed.\n");
}

// テスト15: report_unix=0 + SVID 境界値テスト (fuzz_and_perf.md #4)
static void test_boundary_report_unix_svid(FuzzStats& stats, std::mt19937& rng) {
    printf("Test 15: report_unix=0 + SVID boundary values...\n");

    uint8_t boundary_svids[] = {0, 1, 182, 183, 192, 193, 202, 203, 254, 255};

    for (uint8_t svid : boundary_svids) {
        try {
            uint8_t bits[32] = {0};
            bits[0] = 0x53;
            set_valid_msg_type(bits, rng);
            set_valid_crc(bits);

            Frame frame;
            frame.svid = svid;
            memcpy(frame.bits, bits, 32);

            Decoder decoder;
            Message msg;
            // report_unix=0
            decoder.decode(frame, msg, 0);
            stats.total_iterations++;
        } catch (...) {
            stats.log_exception("test_boundary_report_unix_svid", svid);
        }
    }
    printf("  Completed.\n");
}

// テスト16: 長時間実行メモリ安定性テスト (fuzz_and_perf.md #1)
static void test_memory_stability(FuzzStats& stats, std::mt19937& rng, int iterations) {
    printf("Test 16: Memory stability test (%d iterations)...\n", iterations);

    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < iterations; i++) {
        try {
            uint8_t bits[32];
            generate_random_nav_bits(bits, sizeof(bits), rng);
            set_valid_preamble(bits, rng);
            set_valid_msg_type(bits, rng);
            set_valid_crc(bits);

            std::string nmea = makeNmeaQzqsm(63, bits);

            NmeaFramer framer;
            Frame frame;

            for (char c : nmea) {
                if (framer.feed((uint8_t)c, frame)) {
                    Decoder decoder;
                    Message msg;
                    decoder.decode(frame, msg, 1704067200u);
                    break;
                }
            }

            stats.total_iterations++;

            if (i % 10000 == 0 && i > 0) {
                auto now = std::chrono::steady_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
                printf("  Progress: %d/%d (%llds elapsed)\n", i, iterations, (long long)elapsed);
            }
        } catch (...) {
            stats.log_exception("test_memory_stability", i);
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    printf("  Completed in %llds.\n", (long long)elapsed);
}

// テスト17: デコード成功電文の JSON シリアライズ（監査 P2-3）他のテストは decode まででシリアライザを通さないため、ランダムペイロードが定義テーブル参照（ラベル引き当て）や数値フォーマット経路に与える入力はここでしか検証できない。
// 有効 CRC の MT43/MT44 をデコードし、成功したものをそのまま JsonSerializer へ流す（test_azarashi_dcr.cpp と同じ公開経路）。
static void test_decode_serialize(FuzzStats& stats, std::mt19937& rng, int iterations) {
    printf("Test 17: Decode -> JSON serialize (%d iterations)...\n", iterations);

    for (int i = 0; i < iterations; i++) {
        try {
            uint8_t bits[32];
            generate_random_nav_bits(bits, sizeof(bits), rng);
            set_valid_preamble(bits, rng);
            set_valid_msg_type(bits, rng);
            set_valid_crc(bits);

            Frame frame;
            frame.svid = 193;
            memcpy(frame.bits, bits, 32);

            Decoder decoder;
            Message msg;
            if (decoder.decode(frame, msg, 1704067200u)) {
                StringPrint sp;
                JsonSerializer::serialize(msg, sp);
                const std::string& s = sp.str();
                // 有効電文のシリアライズ結果が空になることはない。空なら破損の兆候。
                if (s.empty()) {
                    printf("  FAIL: serializer produced empty output at iteration %d\n", i);
                    stats.log_exception("test_decode_serialize_empty_output", i);
                } else {
                    stats.serialized++;
                }
            }

            stats.total_iterations++;
        } catch (...) {
            stats.log_exception("test_decode_serialize", i);
        }
    }
    printf("  Completed.\n");
}

// テスト18: Parser の状態遷移（Nankai ページ集約、Rc、dedup、reset）を含む入力。
// 既存の fuzz は Decoder を直接呼ぶため、状態付きのバグを検出できない。
static void test_parser_stateful(FuzzStats& stats, std::mt19937& rng, int iterations) {
    printf("Test 18: Stateful Parser (%d iterations)...\n", iterations);
    Parser parser;
    Message msg;
    std::uniform_int_distribution<int> byte_dist(0, 255);
    std::uniform_int_distribution<int> rc_dist(0, 7);
    std::uniform_int_distribution<int> page_dist(0, 64);
    std::uniform_int_distribution<int> info_dist(0, 15);
    std::uniform_int_distribution<int> it_dist(0, 3);

    for (int i = 0; i < iterations; ++i) {
        try {
            uint8_t bits[32];
            generate_random_nav_bits(bits, sizeof(bits), rng);
            set_valid_preamble(bits, rng);
            setBits(bits, 8, 6, 43);
            setBits(bits, 14, 3, static_cast<uint32_t>(rc_dist(rng)));
            setBits(bits, 17, 4, 4);  // Nankai
            setBits(bits, 21, 4, static_cast<uint32_t>(byte_dist(rng) & 0x0F));
            setBits(bits, 25, 5, static_cast<uint32_t>(byte_dist(rng) & 0x1F));
            setBits(bits, 30, 5, static_cast<uint32_t>(byte_dist(rng) & 0x1F));
            setBits(bits, 35, 6, static_cast<uint32_t>(byte_dist(rng) & 0x3F));
            setBits(bits, 41, 2, static_cast<uint32_t>(it_dist(rng)));
            setBits(bits, 53, 4, static_cast<uint32_t>(info_dist(rng)));
            for (int t = 0; t < 18; ++t) {
                setBits(bits, static_cast<uint16_t>(57 + t * 8), 8,
                        static_cast<uint32_t>(byte_dist(rng)));
            }
            setBits(bits, 201, 6, static_cast<uint32_t>(page_dist(rng)));
            setBits(bits, 207, 6, static_cast<uint32_t>(page_dist(rng)));
            setBits(bits, 214, 6, 1);  // version
            set_valid_crc(bits);

            const std::string nmea = makeNmeaQzqsm(58, bits);
            bool emitted = false;
            for (char c : nmea) {
                if (parser.feed(static_cast<uint8_t>(c), msg, 1704067200u)) {
                    emitted = true;
                    break;
                }
            }
            if (emitted) {
                if (!msg.valid) {
                    stats.log_warning("test_parser_stateful_invalid", i);
                }
                if (msg.payload_type == MsgPayloadType::Mt43) {
                    const Mt43Data* d = msg.getMt43();
                    if (!d) {
                        stats.log_warning("test_parser_stateful_missing_mt43", i);
                    } else if (d->disaster_category == 4) {
                        const NankaiData* n = d->getNankai();
                        if (!n) {
                            stats.log_warning("test_parser_stateful_missing_nankai", i);
                        } else if (n->is_aggregated &&
                                   (!n->aggregated_text_ptr || n->aggregated_len > 63 * 18)) {
                            stats.log_warning("test_parser_stateful_bad_aggregate", i);
                        }
                        if (n && (n->page < 1 || n->total_page < 1 || n->page > n->total_page)) {
                            stats.log_warning("test_parser_stateful_bad_page", i);
                        }
                    }
                }
            }

            // 同じ電文の再送も Parser の状態（ページ重複・dedup）を通す。
            if (i % 17 == 0) {
                for (char c : nmea) {
                    if (parser.feed(static_cast<uint8_t>(c), msg, 1704067200u) && !msg.valid) {
                        stats.log_warning("test_parser_stateful_repeat_invalid", i);
                        break;
                    }
                }
            }
            // 長時間同じ Parser だけを使い続けないよう、時々状態を初期化する。
            if (i % 997 == 0) parser.reset();

            stats.total_iterations++;
        } catch (...) {
            stats.log_exception("test_parser_stateful", i);
        }
    }
    printf("  Completed.\n");
}

int main(int argc, char* argv[]) {
    printf("=== azaraC Fuzz Testing ===\n");
    printf("Starting fuzz tests...\n\n");

    // シード（監査 P2-2）: 既定は random_device。FUZZ_SEED で固定できる。
    // mt19937 の seed は uint32 なので、指定値は 32bit に切り詰めた「実効シード」を印字する — 印字された値で再現するには FUZZ_SEED に同じ値を渡せばよい。
    uint32_t seed = 0;
    const char* env_seed = std::getenv("FUZZ_SEED");
    if (env_seed && *env_seed) {
        char* end = nullptr;
        errno = 0;
        // base 0: 10 進に加え 0x/0b 接頭辞も受け付ける
        const unsigned long long v = std::strtoull(env_seed, &end, 0);
        if (errno != 0 || end == env_seed || *end != '\0') {
            fprintf(stderr, "FUZZ: invalid FUZZ_SEED: '%s' (expected integer)\n", env_seed);
            return 2;
        }
        seed = static_cast<uint32_t>(v);
    } else {
        std::random_device rd;
        seed = rd();
    }
    std::mt19937 rng(seed);
    printf("Seed: %llu\n", (unsigned long long)seed);

    // イテレーション数（環境変数 > コマンドライン引数 > デフォルト）。atoi は不正入力で 0 を返し 0 回の「無検査 PASS」になるため、値域を検証して落とす。
    long long iterations = 10000;
    const char* env_iter = std::getenv("FUZZ_ITERATIONS");
    const char* source = "default";
    if (env_iter) { source = "FUZZ_ITERATIONS"; }
    if (argc > 1) { env_iter = argv[1]; source = "argv[1]"; }
    if (env_iter) {
        char* end = nullptr;
        errno = 0;
        const long long v = std::strtoll(env_iter, &end, 10);
        // 上限 INT_MAX / 5: iterations * 5 を渡すテストがあり、INT_MAX まで許すと int への縮小で負値→0 回ループの「無検査 PASS」に戻る。
        if (errno != 0 || end == env_iter || *end != '\0' || v <= 0 || v > INT_MAX / 5) {
            fprintf(stderr, "FUZZ: invalid %s: '%s' (expected integer in 1..%d)\n",
                    source, env_iter, INT_MAX / 5);
            return 2;
        }
        iterations = v;
    }
    printf("Iterations per test: %lld\n\n", iterations);
    fflush(stdout);

    FuzzStats stats;

    // RAIIによる自動メモリ計測（スコープ終了時にレポート出力）
    MemoryTracker mem_tracker;

    test_random_raw_data(stats, rng, iterations);
    mem_tracker.checkpoint();
    test_valid_preamble(stats, rng, iterations);
    mem_tracker.checkpoint();
    test_valid_preamble_and_type(stats, rng, iterations);
    mem_tracker.checkpoint();
    test_valid_frames_mt43(stats, rng, iterations);
    mem_tracker.checkpoint();
    test_valid_frames_mt44(stats, rng, iterations);
    mem_tracker.checkpoint();
    test_nmea_framer(stats, rng, iterations / 2);
    mem_tracker.checkpoint();
    test_ubx_framer(stats, rng, iterations / 2);
    mem_tracker.checkpoint();
    test_boundary_values(stats, rng);
    mem_tracker.checkpoint();
    test_corrupted_frames(stats, rng, iterations);
    mem_tracker.checkpoint();
    test_corrupted_nmea(stats, rng, iterations / 2);
    mem_tracker.checkpoint();
    test_corrupted_ubx(stats, rng, iterations / 2);
    mem_tracker.checkpoint();
    test_decode_failure_state(stats, rng, iterations / 2);
    mem_tracker.checkpoint();
    test_long_running(stats, rng, iterations * 5);
    mem_tracker.checkpoint();
    test_corrupted_nmea_dollar(stats, rng, iterations / 2);
    mem_tracker.checkpoint();
    test_corrupted_ubx_sync(stats, rng, iterations / 2);
    mem_tracker.checkpoint();
    test_boundary_report_unix_svid(stats, rng);
    mem_tracker.checkpoint();
    test_memory_stability(stats, rng, iterations * 5);
    mem_tracker.checkpoint();
    test_decode_serialize(stats, rng, iterations / 2);
    mem_tracker.checkpoint();
    test_parser_stateful(stats, rng, iterations / 2);
    mem_tracker.checkpoint();

    // メモリレポートは mem_tracker のデストラクタで自動出力
    stats.print();

    printf("\n=== Summary ===\n");
    if (stats.exceptions == 0 && stats.warnings == 0) {
        printf("PASS: No exceptions or invariant warnings during fuzz testing.\n");
    } else {
        printf("FAIL: %llu exceptions and %llu warnings during fuzz testing.\n",
               (unsigned long long)stats.exceptions,
               (unsigned long long)stats.warnings);
        // catch できないクラッシュ（segfault 等）で死んだ場合も、シードを固定して再実行すれば同じ入力列を辿れる。
        printf("Reproduce with: FUZZ_SEED=%llu make -C test fuzz FUZZ_ITERATIONS=%lld\n",
               (unsigned long long)seed, iterations);
    }

    // 破損テストが実際に「拒否」を観測できているか。カウンタが 0 のままなら
    // 入力生成か判定が壊れている（計測が嘘をついている）ので、成功扱いにしない。
    const bool corruption_observed = (stats.invalid_crc > 0 && stats.invalid_preamble > 0);
    if (corruption_observed) {
        printf("Corruption rejections: crc=%llu, preamble=%llu, framer=%llu\n",
               (unsigned long long)stats.invalid_crc,
               (unsigned long long)stats.invalid_preamble,
               (unsigned long long)stats.framer_rejected);
    } else {
        printf("FAIL: corruption counters were not exercised (crc=%llu, preamble=%llu).\n",
               (unsigned long long)stats.invalid_crc,
               (unsigned long long)stats.invalid_preamble);
    }

    printf("Fuzz testing completed.\n");

    return (stats.exceptions > 0 || stats.warnings > 0 || !corruption_observed) ? 1 : 0;
}
