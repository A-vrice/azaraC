// test/test_helpers.h — 複数のテストファイルで共有するヘルパー関数・クラス

#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#define ARDUINO 0
#include "../src/azaraC.h"
#include "../src/decoder/Decoder.h"
#include "../src/framer/NmeaFramer.h"
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <random>
#include <string>
#include <vector>

using namespace azaraC;
using namespace azaraC::internal;

// ビット操作ヘルパー

inline void setBits(uint8_t* buf, uint16_t start, uint8_t len, uint32_t value) {
    if (len == 0) return;
    for (int i = static_cast<int>(len) - 1; i >= 0; --i) {
        uint16_t pos = start + (len - 1 - i);
        if ((value >> i) & 1) buf[pos >> 3] |=  (1 << (7 - (pos & 7)));
        else                  buf[pos >> 3] &= ~(1 << (7 - (pos & 7)));
    }
}

// UBX SFRBX パケット生成

inline std::vector<uint8_t> makeUbxSfrbx(uint8_t svId, const uint8_t* nav_bits) {
    std::vector<uint8_t> out;
    out.push_back(0xB5); out.push_back(0x62); // SYNC
    out.push_back(0x02); out.push_back(0x13); // CLASS/ID (RXM-SFRBX)

    uint16_t len = 8 + 8 * 4; // header(8) + 8 words(32)
    out.push_back(len & 0xFF);
    out.push_back(len >> 8);

    // Header
    out.push_back(5);    // gnssId (QZSS)
    out.push_back(svId); // svId
    out.push_back(0);    // sigId (L1S)
    out.push_back(0);    // freqId
    out.push_back(8);    // numWords
    out.push_back(0);    // chn
    out.push_back(1);    // version
    out.push_back(0);    // reserved

    // Payload (8 words)
    for (int w = 0; w < 8; ++w) {
        uint32_t val = 0;
        for (int b = 0; b < 32; ++b) {
            int bit_idx = w * 32 + b;
            if (bit_idx < 250) {
                if (nav_bits[bit_idx / 8] & (0x80u >> (bit_idx % 8))) {
                    val |= (1u << (31 - b));
                }
            }
        }
        out.push_back(val & 0xFF);
        out.push_back((val >> 8) & 0xFF);
        out.push_back((val >> 16) & 0xFF);
        out.push_back(val >> 24);
    }

    // Checksum
    uint8_t cka = 0, ckb = 0;
    for (size_t i = 2; i < out.size(); ++i) {
        cka += out[i];
        ckb += cka;
    }
    out.push_back(cka);
    out.push_back(ckb);

    return out;
}

// NMEA QZQSM 文生成
// 第1引数は PRN（QZS の 183-191）でも生の Satellite ID（下位 6bit、53-63）でもよい: 電文に載るのは下位 7bit の2桁10進だけなので `& 0x7F` に落として書く（FRAME 側は `| 0x80` で PRN に戻す）。2桁で書ける 0..99 が上限（100 以上は3桁になり、受信側が仕様どおり拒否する）。
inline std::string makeNmeaQzqsm(uint8_t svid, const uint8_t* nav_bits) {
    assert((svid & 0x7F) <= 99);
    char buf[256];
    snprintf(buf, sizeof(buf), "QZQSM,%02u,", static_cast<unsigned>(svid & 0x7F));
    std::string s = "$";
    s += buf;
    // Output 31 full bytes (62 hex chars)
    for (int i = 0; i < 31; ++i) {
        char hex[3];
        snprintf(hex, sizeof(hex), "%02X", nav_bits[i]);
        s += hex;
    }
    // Output 1 nibble (1 hex char) for the remaining 2 bits
    char hex[2];
    snprintf(hex, sizeof(hex), "%01X", (nav_bits[31] >> 4) & 0xF);
    s += hex;

    uint8_t xsum = 0;
    for (size_t i = 1; i < s.size(); ++i) {
        xsum ^= (uint8_t)s[i];
    }

    char tail[6];
    snprintf(tail, sizeof(tail), "*%02X\r\n", xsum);
    s += tail;
    return s;
}

// CRC-24Q リファレンス実装

inline uint32_t crc24qRef(const uint8_t* d, int total_bits) {
    uint32_t crc = 0;
    int bytes = (total_bits + 7) / 8;
    for (int i = 0; i < bytes; i++) {
        uint8_t b = d[i];
        int bits_to_process = 8;
        if (i == bytes - 1 && (total_bits & 7)) {
            b &= 0xFFu << (8 - (total_bits & 7));
            bits_to_process = total_bits & 7;
        }
        crc ^= (uint32_t)b << 16;
        for (int j = 0; j < bits_to_process; j++) {
            crc <<= 1;
            if (crc & 0x1000000) crc ^= 0x1864CFB;
        }
    }
    return crc & 0xFFFFFF;
}

// NMEAデコードヘルパー

inline bool decodeNmea(const char* nmea, Message& msg, uint32_t report_unix = 0) {
    NmeaFramer framer;
    Frame frame;
    bool found = false;
    for (int i = 0; nmea[i]; i++) {
        if (framer.feed((uint8_t)nmea[i], frame)) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    Decoder dec;
    return dec.decode(frame, msg, report_unix);
}

// NmeaFramer のパーサー動作のみをテストする（Decoder を経由せず、チェックサム検証を含む）

inline bool feedNmeaRaw(const char* nmea, Frame& out) {
    NmeaFramer framer;
    for (int i = 0; nmea[i]; i++) {
        if (framer.feed((uint8_t)nmea[i], out)) {
            return true;
        }
    }
    return false;
}

// 指定した16進文字数の $QZQSM 文を生成（チェックサム付き）
inline std::string makeNmeaQzqsmHex(int num_hex_chars) {
    std::string s = "$QZQSM,55,";
    for (int i = 0; i < num_hex_chars; i++) {
        char hex[2];
        snprintf(hex, sizeof(hex), "%X", i % 16);
        s += hex;
    }
    uint8_t xsum = 0;
    for (size_t i = 1; i < s.size(); i++) {
        xsum ^= (uint8_t)s[i];
    }
    char tail[6];
    snprintf(tail, sizeof(tail), "*%02X\r\n", xsum);
    s += tail;
    return s;
}

// テスト用デコーダー（protected関数を公開）

struct TestDecoder : Decoder {
    // One shared instance: the OOB flag and getBits/getBits64 state must persist across calls
    static TestDecoder& inst() {
        static TestDecoder t;
        return t;
    }

    // CRC計算
    static uint32_t calcCRC(const uint8_t* data, uint16_t bit_len) {
        return crc24q(data, bit_len);
    }

    // ビット抽出（getBits は非static、インスタンス経由で呼ぶ）
    static uint32_t extractBits(const uint8_t* b, uint16_t s, uint8_t l) {
        return inst().getBits(b, s, l);
    }

    // OOB (out-of-bounds) flag control for getBits/getBits64 tests
    static void clearOob() {
        inst().oob_ = false;
    }
    static bool checkOob() {
        return inst().oob_;
    }

    // getBits64 is non-static: call through the instance
    static uint64_t extractBits64(const uint8_t* b, uint16_t s, uint8_t l) {
        return inst().getBits64(b, s, l);
    }

    // extractDHM is non-static: call through the instance
    static TimeFields testExtractDHM(const uint8_t* b, uint16_t start, uint32_t report_unix = 0) {
        static TestDecoder t;
        t.oob_ = false;
        return t.extractDHM(b, start, report_unix);
    }

    // readNotifications is non-static: call through the instance
    static uint8_t testReadNotifications(const uint8_t* b, uint16_t start, uint16_t* out) {
        static TestDecoder t;
        return t.readNotifications(b, start, out);
    }

    // サブデコーダー用ラッパー。基底の条件コンパイルに合わせて #if ガードする
#if (AZARAC_ENABLE_EEW)
    static void testDecodeEEW(const uint8_t* bits, Message& out, uint32_t now_unix) {
        TestDecoder t;
        t.decodeEEW(bits, out, now_unix);
    }
#endif

    // protected static in the base class: callable directly
    static TimeFields testResolveArrivalTime(uint16_t raw, uint32_t base_unix) {
        return resolveArrivalTime(raw, base_unix);
    }

    // 時間解決
    static TimeFields testResolveTime(uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint32_t now_unix) {
        return resolveTime(month, day, hour, minute, now_unix);
    }

    // 緯度経度抽出（extractLatLon は非static、インスタンス経由で呼ぶ）
    static LatLon testExtractLatLon(const uint8_t* buf, uint16_t start) {
        return TestDecoder().extractLatLon(buf, start);
    }

    // 日付変換
    static void testCivilFromDays(uint32_t days, uint32_t& y, uint32_t& m, uint32_t& d) {
        civil_from_days(days, y, m, d);
    }

    static uint32_t testDaysFromCivil(uint32_t y, uint32_t m, uint32_t d) {
        return days_from_civil(y, m, d);
    }
};


// ファジーテストヘルパー

inline void generate_random_nav_bits(uint8_t* bits, size_t size, std::mt19937& rng) {
    std::uniform_int_distribution<int> dist(0, 255);
    for (size_t i = 0; i < size; ++i) {
        bits[i] = static_cast<uint8_t>(dist(rng));
    }
}

// 日付計算ヘルパー

inline void civilFromDays(uint32_t days_since_1970, uint32_t& y, uint32_t& m, uint32_t& d) {
    TestDecoder::testCivilFromDays(days_since_1970, y, m, d);
}

inline uint32_t daysFromCivil(uint32_t y, uint32_t m, uint32_t d) {
    return TestDecoder::testDaysFromCivil(y, m, d);
}

#endif // TEST_HELPERS_H
