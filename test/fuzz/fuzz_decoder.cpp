// test/fuzz/fuzz_decoder.cpp
// ファジーテスト: ランダム入力に対するデコーダの堅牢性テスト
//
// コンパイル: g++ -std=c++17 -I../include -I. -DARDUINO=0 -DAZARAC_LANG_JA=1 -DAZARAC_LANG_EN=1 -g -o fuzz_decoder fuzz_decoder.cpp ../src/Parser.cpp ../src/decoder/Decoder.cpp ../src/decoder/DecoderDcx.cpp ../src/decoder/DecoderQzqsm.cpp ../src/framer/UbxFramer.cpp ../src/framer/NmeaFramer.cpp ../src/json/JsonWriter.cpp ../src/json/JsonSerializer.cpp ../src/json/JsonSerializerDcx.cpp ../src/json/JsonSerializerQzqsm.cpp ../src/internal/DcxHelper.cpp ../src/internal/Dedup.cpp -Wl,--stack,33554432
//
// 実行: ./fuzz_decoder [イテレーション数]

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>
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
#include "test_helpers.h"

using namespace azaraC;
using namespace azaraC::internal;

// テスト名を記録するための最大例外数
#define MAX_EXCEPTION_LOG 100

// ---------------------------------------------------------------------------
// MemoryTracker: RAIIパターンによるメモリ使用量自動計測
// ---------------------------------------------------------------------------
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

// 例外情報
struct ExceptionInfo {
    const char* test_name;
    uint64_t iteration;
};

// 統計情報
struct FuzzStats {
    uint64_t total_iterations = 0;
    uint64_t valid_frames = 0;
    uint64_t invalid_crc = 0;
    uint64_t invalid_preamble = 0;
    uint64_t decode_success = 0;
    uint64_t decode_fail = 0;
    uint64_t mt43_count = 0;
    uint64_t mt44_count = 0;
    uint64_t exceptions = 0;
    uint64_t nmea_frames = 0;
    uint64_t ubx_frames = 0;

    // テストごとの例外記録
    ExceptionInfo exception_log[MAX_EXCEPTION_LOG];
    int exception_log_count = 0;

    void log_exception(const char* test_name, uint64_t iter) {
        if (exception_log_count < MAX_EXCEPTION_LOG) {
            exception_log[exception_log_count++] = {test_name, iter};
        }
        exceptions++;
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
        printf("Decode success:      %llu\n", (unsigned long long)decode_success);
        printf("  MT=43:             %llu\n", (unsigned long long)mt43_count);
        printf("  MT=44:             %llu\n", (unsigned long long)mt44_count);
        printf("Decode fail:         %llu\n", (unsigned long long)decode_fail);
        printf("Exceptions caught:   %llu\n", (unsigned long long)exceptions);

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


// 有効なプリアンブルを設定
static void set_valid_preamble(uint8_t* bits, std::mt19937& rng) {
    std::uniform_int_distribution<int> dist(0, 2);
    uint8_t preambles[] = {0x53, 0x9A, 0xC6};
    bits[0] = preambles[dist(rng)];
}

// 有効なMSG_TYPEを設定
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

// CRCを計算して設定
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
            // MT=43を強制設定
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
            // MT=44を強制設定
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

            std::string nmea = makeNmeaQzqsm(193, bits);

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

    // テストケース: 全ゼロ
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

    // テストケース: 全1
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

    // テストケース: プリアンブルの境界値
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

    // テストケース: 無効なMSG_TYPE
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

    // テストケース: report_unix境界値
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

            // NMEA経由でテスト
            std::string nmea = makeNmeaQzqsm(193, bits);

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

            // 進捗表示
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

            // ランダムなビットを反転（CRC破損）
            int corrupt_pos = bit_dist(rng);
            bits[corrupt_pos / 8] ^= (0x80 >> (corrupt_pos % 8));

            Frame frame;
            frame.svid = 193;
            memcpy(frame.bits, bits, 32);

            Decoder decoder;
            Message msg;
            decoder.decode(frame, msg, 1704067200u);

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

            std::string nmea = makeNmeaQzqsm(193, bits);

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
                decoder.decode(frame, msg, 1704067200u);
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
                decoder.decode(frame, msg, 1704067200u);
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

            // デコードは失敗するはず（CRC不一致）
            // 注意: CRC失敗時はsvidが設定されずにfalseが返される（正常動作）
            // ここではvalidがfalseであることのみを検証
            if (!result && msg.valid) {
                printf("  WARNING: valid should be false on decode failure at iteration %d\n", i);
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

            std::string nmea = makeNmeaQzqsm(193, bits);

            // Remove the leading '$'
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

            // Should NOT be detected without '$'
            if (found) {
                // Malformed frame was still detected — record as failure and abort
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

            // Corrupt SYNC character
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
                // Malformed frame was still detected — record as failure and abort
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

            // NMEA経由でテスト
            std::string nmea = makeNmeaQzqsm(193, bits);

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

            // 進捗表示
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

int main(int argc, char* argv[]) {
    printf("=== AzaraC Fuzz Testing ===\n");
    printf("Starting fuzz tests...\n\n");

    // 乱数シード
    std::random_device rd;
    std::mt19937 rng(rd());

    // イテレーション数（環境変数 > コマンドライン引数 > デフォルト）
    int iterations = 10000;
    const char* env_iter = std::getenv("FUZZ_ITERATIONS");
    if (env_iter) {
        iterations = std::atoi(env_iter);
    }
    if (argc > 1) {
        iterations = std::atoi(argv[1]);
    }
    printf("Iterations per test: %d\n\n", iterations);

    FuzzStats stats;

    // RAIIによる自動メモリ計測（スコープ終了時にレポート出力）
    MemoryTracker mem_tracker;

    // テスト実行
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

    // 結果表示（メモリレポートはmem_trackerのデストラクタで自動出力）
    stats.print();

    // サマリー
    printf("\n=== Summary ===\n");
    if (stats.exceptions == 0) {
        printf("PASS: No exceptions caught during fuzz testing.\n");
    } else {
        printf("FAIL: %llu exceptions caught during fuzz testing.\n",
               (unsigned long long)stats.exceptions);
    }

    printf("Fuzz testing completed.\n");

    return stats.exceptions > 0 ? 1 : 0;
}
