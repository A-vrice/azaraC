// test/core/test_core.cpp — コア機能テスト
// CRC-24Q, 時間変換, 緯度経度, 重複除去の統合テスト
// test_crc.cpp, test_time.cpp, test_latlon.cpp, test_dedup.cpp を統合

#include "../test_helpers.h"
#include "doctest.h"

using namespace azaraC;

// ── CRC-24Q テスト (from test_crc.cpp) ─────────────────────────────────────

TEST_CASE("CRC-24Q vs reference") {
    uint8_t buf[29] = {};
    uint32_t a = TestDecoder::calcCRC(buf, 226);
    uint32_t b = crc24qRef(buf, 226);
    CHECK(a == b);

    for (auto& v : buf) v = 0xA5;
    a = TestDecoder::calcCRC(buf, 226);
    b = crc24qRef(buf, 226);
    CHECK(a == b);
}

TEST_CASE("CRC-24Q: diverse random patterns") {
    uint8_t buf[29];
    for (int pat = 0; pat < 50; ++pat) {
        INFO("Pattern ", pat);
        // Fill with deterministic pseudo-random data
        uint8_t seed = (uint8_t)(pat * 37 + 13);
        for (int i = 0; i < 29; ++i) {
            buf[i] = (uint8_t)(seed * (i + 1) ^ 0xA5);
            seed = (uint8_t)(seed * 7 + 3);
        }
        uint32_t a = TestDecoder::calcCRC(buf, 226);
        uint32_t b = crc24qRef(buf, 226);
        CHECK(a == b);
    }
}

TEST_CASE("CRC-24Q: alternating bits") {
    uint8_t buf[29] = {};
    for (int i = 0; i < 29; ++i) buf[i] = 0x55;
    CHECK(TestDecoder::calcCRC(buf, 226) == crc24qRef(buf, 226));

    for (int i = 0; i < 29; ++i) buf[i] = 0xAA;
    CHECK(TestDecoder::calcCRC(buf, 226) == crc24qRef(buf, 226));
}

TEST_CASE("CRC-24Q: single bit set sweep") {
    uint8_t buf[29] = {};
    // Test first 10 bit positions
    for (int b = 0; b < 10; ++b) {
        INFO("Bit position ", b);
        memset(buf, 0, 29);
        buf[b / 8] = (uint8_t)(0x80u >> (b % 8));
        CHECK(TestDecoder::calcCRC(buf, 226) == crc24qRef(buf, 226));
    }
    // Test last 10 bit positions
    for (int b = 216; b < 226; ++b) {
        INFO("Bit position ", b);
        memset(buf, 0, 29);
        buf[b / 8] = (uint8_t)(0x80u >> (b % 8));
        CHECK(TestDecoder::calcCRC(buf, 226) == crc24qRef(buf, 226));
    }
}

TEST_CASE("CRC-24Q: bit_len=0") {
    uint8_t buf[1] = {0xFF};
    CHECK(TestDecoder::calcCRC(buf, 0) == 0);
}

TEST_CASE("CRC-24Q: bit_len=1") {
    uint8_t buf[1] = {0x00};
    CHECK(TestDecoder::calcCRC(buf, 1) == crc24qRef(buf, 1));
    buf[0] = 0x80;
    CHECK(TestDecoder::calcCRC(buf, 1) == crc24qRef(buf, 1));
}

TEST_CASE("CRC-24Q: known-answer check value (72-bit)") {
    // CRC-24Q standard check value for ASCII "123456789"
    // From RevEng CRC catalogue: poly=0x1864CFB init=0 refin=0 refout=0 xorout=0
    // This implementation matches the catalogue, confirmed by independent LFSR bit-wise implementation.
    uint8_t buf[9] = {'1','2','3','4','5','6','7','8','9'};
    CHECK(TestDecoder::calcCRC(buf, 72) == 0xCDE703);
}

TEST_CASE("CRC-24Q: known-answer 226-bit messages") {
    // Values computed by independent bit-wise LFSR CRC-24Q (Python) and
    // cross-verified against azarashi and crc24qRef byte-wise implementation.
    // Both implementations agree.
    {
        INFO("all-zero 226-bit");
        uint8_t buf[29] = {};
        CHECK(TestDecoder::calcCRC(buf, 226) == 0x000000);
    }
    {
        INFO("0x55 226-bit");
        uint8_t buf[29];
        memset(buf, 0x55, 29);
        CHECK(TestDecoder::calcCRC(buf, 226) == 0x9AB74F);
    }
    {
        INFO("0xAA 226-bit");
        uint8_t buf[29];
        memset(buf, 0xAA, 29);
        CHECK(TestDecoder::calcCRC(buf, 226) == 0xB32265);
    }
    {
        INFO("0xA5 226-bit");
        uint8_t buf[29];
        memset(buf, 0xA5, 29);
        CHECK(TestDecoder::calcCRC(buf, 226) == 0xE54EC3);
    }
}

TEST_CASE("getBits extraction") {
    uint8_t buf[2] = {0xAB, 0xCD};

    CHECK(TestDecoder::extractBits(buf, 0,  8) == 0xAB);
    CHECK(TestDecoder::extractBits(buf, 8,  8) == 0xCD);
    CHECK(TestDecoder::extractBits(buf, 0,  4) == 0xA);
    CHECK(TestDecoder::extractBits(buf, 4,  4) == 0xB);
    CHECK(TestDecoder::extractBits(buf, 0,  1) == 1);
    CHECK(TestDecoder::extractBits(buf, 7,  1) == 1);
    CHECK(TestDecoder::extractBits(buf, 8,  1) == 1);
    CHECK(TestDecoder::extractBits(buf, 0, 16) == 0xABCD);
}

// ── Out-of-Bounds 検出テスト ──────────────────────────────────────────────

TEST_CASE("getBits: OOB detected at boundary") {
    uint8_t buf[32] = {};
    TestDecoder::clearOob();
    uint32_t val = TestDecoder::extractBits(buf, 256, 1);
    CHECK(TestDecoder::checkOob() == true);
    CHECK(val == 0);
}

TEST_CASE("getBits: OOB detected well past boundary") {
    uint8_t buf[32] = {};
    TestDecoder::clearOob();
    uint32_t val = TestDecoder::extractBits(buf, 300, 8);
    CHECK(TestDecoder::checkOob() == true);
    CHECK(val == 0);
}

TEST_CASE("getBits: No OOB at last valid position") {
    uint8_t buf[32] = {};
    TestDecoder::clearOob();
    TestDecoder::extractBits(buf, 248, 8);
    CHECK(TestDecoder::checkOob() == false);
    // 248+8=256, boundary exact, no OOB
}

TEST_CASE("getBits: No OOB at mid-frame") {
    uint8_t buf[32] = {};
    TestDecoder::clearOob();
    TestDecoder::extractBits(buf, 100, 16);
    CHECK(TestDecoder::checkOob() == false);
}

TEST_CASE("getBits64: OOB detected") {
    uint8_t buf[32] = {};
    TestDecoder::clearOob();
    uint64_t val = TestDecoder::extractBits64(buf, 250, 16);
    CHECK(TestDecoder::checkOob() == true);
    CHECK(val == 0);
}

// ── setBits セルフテスト ─────────────────────────────────────────────────

TEST_CASE("setBits: roundtrip with getBits") {
    uint8_t buf[8] = {};
    setBits(buf, 10, 8, 0xAB);
    CHECK(TestDecoder::extractBits(buf, 10, 8) == 0xAB);
}

TEST_CASE("setBits: zero-length write no-op") {
    uint8_t buf[4] = {};
    setBits(buf, 10, 0, 0xFF);
    // Buffer should remain unchanged (all zeros)
    CHECK(TestDecoder::extractBits(buf, 0, 32) == 0);
}

TEST_CASE("setBits: overwrite then read") {
    uint8_t buf[8] = {};
    setBits(buf, 0, 4, 0xA);
    setBits(buf, 0, 4, 0x5);
    CHECK(TestDecoder::extractBits(buf, 0, 4) == 0x5);
}

TEST_CASE("setBits: multi-byte span") {
    uint8_t buf[16] = {};
    setBits(buf, 60, 16, 0xABCD);
    CHECK(TestDecoder::extractBits(buf, 60, 16) == 0xABCD);
}

TEST_CASE("setBits: boundary at byte edge") {
    uint8_t buf[8] = {};
    setBits(buf, 0, 32, 0xDEADBEEF);
    CHECK(TestDecoder::extractBits(buf, 0, 32) == 0xDEADBEEF);
}

// ── readNotifications テスト ──────────────────────────────────────────────

TEST_CASE("readNotifications: 3 codes") {
    uint8_t buf[8] = {};
    setBits(buf, 0, 9, 100);
    setBits(buf, 9, 9, 200);
    setBits(buf, 18, 9, 300);
    uint16_t out[3] = {};
    uint8_t cnt = TestDecoder::testReadNotifications(buf, 0, out);
    CHECK(cnt == 3);
    CHECK(out[0] == 100);
    CHECK(out[1] == 200);
    CHECK(out[2] == 300);
}

TEST_CASE("readNotifications: 0 terminates") {
    uint8_t buf[8] = {};
    setBits(buf, 0, 9, 100);
    setBits(buf, 9, 9, 0);   // zero terminates
    setBits(buf, 18, 9, 300);
    uint16_t out[3] = {};
    uint8_t cnt = TestDecoder::testReadNotifications(buf, 0, out);
    CHECK(cnt == 1);
    CHECK(out[0] == 100);
}

TEST_CASE("readNotifications: all zeros") {
    uint8_t buf[8] = {};
    uint16_t out[3] = {};
    uint8_t cnt = TestDecoder::testReadNotifications(buf, 0, out);
    CHECK(cnt == 0);
}

TEST_CASE("readNotifications: single code") {
    uint8_t buf[8] = {};
    setBits(buf, 0, 9, 50);
    uint16_t out[3] = {};
    uint8_t cnt = TestDecoder::testReadNotifications(buf, 0, out);
    CHECK(cnt == 1);
    CHECK(out[0] == 50);
}

TEST_CASE("invalid preamble rejected") {
    uint8_t buf[32] = {};
    Frame f; f.svid = 193; memcpy(f.bits, buf, 32);
    Decoder dec;
    Message msg{};
    bool ok = dec.decode(f, msg);
    CHECK(ok == false);
}

#if (AZARAC_ENABLE_DCX_CAMF)

TEST_CASE("MT=44 field extraction on synthetic frame") {
    uint8_t buf[32] = {};

    setBits(buf, 0,  8, 0x53);
    setBits(buf, 8,  6, 44);
    setBits(buf, 24, 2, 1);
    setBits(buf, 26, 9, 111);
    setBits(buf, 35, 5, 2);

    uint32_t crc = crc24qRef(buf, 226);
    setBits(buf, 226, 24, crc);

    Frame f; f.svid = 193; memcpy(f.bits, buf, 32);
    Decoder dec;
    Message msg{};
    bool ok = dec.decode(f, msg);
    REQUIRE(ok);
    CHECK(msg.msg_type == 44);
    CHECK(msg.payload_type == MsgPayloadType::Mt44);
    
    // Use safe accessor for Mt44Data
    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->service_kind == Mt44ServiceKind::JAlert);
    CHECK(mt44->camf.a1 == 1);
    CHECK(mt44->camf.a2 == 111);
    CHECK(mt44->camf.a3 == 2);
}
#endif

// ── 時間変換テスト (from test_time.cpp) ────────────────────────────────────

TEST_CASE("daysFromCivil と civilFromDays の相互変換") {
    struct TestCase {
        uint32_t year, month, day;
    };
    TestCase cases[] = {
        {2024, 1, 1},
        {2024, 12, 31},
        {2023, 2, 28},
        {2024, 2, 29},
        {2000, 1, 1},
        {1970, 1, 1},
    };

    for (auto& tc : cases) {
        uint32_t days = daysFromCivil(tc.year, tc.month, tc.day);
        uint32_t y, m, d;
        civilFromDays(days, y, m, d);

        CAPTURE(tc.year);
        CAPTURE(tc.month);
        CAPTURE(tc.day);
        CHECK(y == tc.year);
        CHECK(m == tc.month);
        CHECK(d == tc.day);
    }
}

TEST_CASE("resolveTime: 基本的な日付変換") {
    uint32_t now = 1704067200u;
    TimeFields t = TestDecoder::testResolveTime(1, 1, 0, 0, now);
    CHECK(t.day == 1);
    CHECK(t.hour == 0);
    CHECK(t.minute == 0);
    CHECK(t.unix_time == 1704067200u);
}

TEST_CASE("resolveTime: 異なる日付の変換") {
    uint32_t days = daysFromCivil(2024, 6, 15);
    uint32_t expected_unix = days * 86400u + 12u * 3600u + 30u * 60u;
    uint32_t now = days * 86400u;

    TimeFields t = TestDecoder::testResolveTime(6, 15, 12, 30, now);
    CHECK(t.day == 15);
    CHECK(t.hour == 12);
    CHECK(t.minute == 30);
    CHECK(t.unix_time == expected_unix);
}

TEST_CASE("resolveTime: 月のラップアラウンド") {
    uint32_t now = daysFromCivil(2024, 1, 15) * 86400u;
    TimeFields t = TestDecoder::testResolveTime(12, 31, 0, 0, now);
    uint32_t expected = daysFromCivil(2023, 12, 31) * 86400u;
    CHECK(t.unix_time == expected);
}

TEST_CASE("resolveTime: 日のラップアラウンド（DHMのみ）") {
    uint32_t now = daysFromCivil(2024, 1, 15) * 86400u;
    TimeFields t = TestDecoder::testResolveTime(0, 20, 0, 0, now);
    CHECK(t.day == 20);
}

TEST_CASE("resolveTime: DHM形式のテスト") {
    uint8_t day = 15, hour = 10, minute = 30;
    uint32_t now = daysFromCivil(2024, 1, 15) * 86400u;
    TimeFields t = TestDecoder::testResolveTime(0, day, hour, minute, now);

    CHECK(t.day == day);
    CHECK(t.hour == hour);
    CHECK(t.minute == minute);
}

TEST_CASE("resolveTime: 日付のラップアラウンド（月末→月初）") {
    uint32_t now = daysFromCivil(2024, 1, 1) * 86400u;
    TimeFields t = TestDecoder::testResolveTime(0, 31, 0, 0, now);
    uint32_t expected = daysFromCivil(2023, 12, 31) * 86400u;
    CHECK(t.unix_time == expected);
}

TEST_CASE("resolveTime: 日付のラップアラウンド（月初→月末）") {
    uint32_t now = daysFromCivil(2024, 1, 31) * 86400u;
    TimeFields t = TestDecoder::testResolveTime(0, 1, 0, 0, now);
    uint32_t expected = daysFromCivil(2024, 2, 1) * 86400u;
    CHECK(t.unix_time == expected);
}

TEST_CASE("resolveTime: MDHM形式（月指定あり）") {
    uint32_t now = daysFromCivil(2024, 6, 15) * 86400u;
    TimeFields t = TestDecoder::testResolveTime(6, 15, 12, 0, now);
    CHECK(t.day == 15);
    CHECK(t.hour == 12);
    CHECK(t.minute == 0);
    uint32_t expected = daysFromCivil(2024, 6, 15) * 86400u + 12 * 3600u;
    CHECK(t.unix_time == expected);
}

TEST_CASE("resolveTime: 月のラップアラウンド（MDHM）") {
    uint32_t now = daysFromCivil(2024, 1, 15) * 86400u;
    TimeFields t = TestDecoder::testResolveTime(12, 15, 0, 0, now);
    uint32_t expected = daysFromCivil(2023, 12, 15) * 86400u;
    CHECK(t.unix_time == expected);
}

TEST_CASE("resolveTime: 無効な入力の処理") {
    TimeFields t1 = TestDecoder::testResolveTime(0, 0, 0, 0, 1704067200u);
    CHECK(t1.day == 0);
    CHECK(t1.hour == 0);
    CHECK(t1.minute == 0);
    CHECK(t1.unix_time == 0);

    TimeFields t2 = TestDecoder::testResolveTime(0, 32, 0, 0, 1704067200u);
    CHECK(t2.day == 0);
    CHECK(t2.hour == 0);
    CHECK(t2.minute == 0);
    CHECK(t2.unix_time == 0);

    TimeFields t3 = TestDecoder::testResolveTime(13, 1, 0, 0, 1704067200u);
    CHECK(t3.day == 0);
    CHECK(t3.hour == 0);
    CHECK(t3.minute == 0);
    CHECK(t3.unix_time == 0);

    TimeFields t4 = TestDecoder::testResolveTime(1, 1, 24, 0, 1704067200u);
    CHECK(t4.day == 0);
    CHECK(t4.hour == 0);
    CHECK(t4.minute == 0);
    CHECK(t4.unix_time == 0);
}

// ── DHM extraction テスト ────────────────────────────────────────────────

TEST_CASE("extractDHM: basic extraction") {
    uint8_t buf[4] = {};
    // day=15 (0b01111), hour=10 (0b01010), min=30 (0b011110)
    uint32_t now = daysFromCivil(2024, 1, 15) * 86400u;
    setBits(buf, 0, 5, 15);
    setBits(buf, 5, 5, 10);
    setBits(buf, 10, 6, 30);
    TimeFields t = TestDecoder::testExtractDHM(buf, 0, now);
    CHECK(t.day == 15);
    CHECK(t.hour == 10);
    CHECK(t.minute == 30);
    CHECK(t.unix_time != 0);
}

TEST_CASE("extractDHM: max values") {
    uint8_t buf[4] = {};
    // day=31 (5bit max), hour=23 (5bit), min=59 (6bit)
    uint32_t now = daysFromCivil(2024, 1, 31) * 86400u;
    setBits(buf, 0, 5, 31);
    setBits(buf, 5, 5, 23);
    setBits(buf, 10, 6, 59);
    TimeFields t = TestDecoder::testExtractDHM(buf, 0, now);
    CHECK(t.day == 31);
    CHECK(t.hour == 23);
    CHECK(t.minute == 59);
}

TEST_CASE("extractDHM: zero values") {
    uint8_t buf[4] = {};
    // day=0 → resolveTime rejects day<1 → all cleared
    uint32_t now = daysFromCivil(2024, 1, 15) * 86400u;
    TimeFields t = TestDecoder::testExtractDHM(buf, 0, now);
    CHECK(t.day == 0);
    CHECK(t.hour == 0);
    CHECK(t.minute == 0);
    CHECK(t.unix_time == 0);
}

TEST_CASE("extractDHM: report_unix=0") {
    uint8_t buf[4] = {};
    setBits(buf, 0, 5, 15);
    setBits(buf, 5, 5, 10);
    setBits(buf, 10, 6, 30);
    TimeFields t = TestDecoder::testExtractDHM(buf, 0, 0u);
    // DHM resolved but unix_time stays 0
    CHECK(t.day == 15);
    CHECK(t.hour == 10);
    CHECK(t.minute == 30);
    CHECK(t.unix_time == 0);
}

// ── resolveArrivalTime テスト ─────────────────────────────────────────────

TEST_CASE("resolveArrivalTime: raw=0 returns zeros") {
    TimeFields t = TestDecoder::testResolveArrivalTime(0, 1704067200u);
    CHECK(t.day == 0);
    CHECK(t.hour == 0);
    CHECK(t.minute == 0);
    CHECK(t.unix_time == 0);
}

TEST_CASE("resolveArrivalTime: hour>23 rejected") {
    // (31<<6)|0 = hour=31
    TimeFields t = TestDecoder::testResolveArrivalTime((31u << 6) | 0u, 1704067200u);
    CHECK(t.day == 0);
    CHECK(t.hour == 0);
    CHECK(t.minute == 0);
    CHECK(t.unix_time == 0);
}

TEST_CASE("resolveArrivalTime: min>59 rejected") {
    // (0<<6)|63 = min=63
    TimeFields t = TestDecoder::testResolveArrivalTime((0u << 6) | 63u, 1704067200u);
    CHECK(t.day == 0);
    CHECK(t.hour == 0);
    CHECK(t.minute == 0);
    CHECK(t.unix_time == 0);
}

TEST_CASE("resolveArrivalTime: normal day_offset=0") {
    uint32_t base = daysFromCivil(2024, 1, 1) * 86400u;
    // (0<<11)|(7<<6)|40 = day_offset=0, hour=7, min=40
    uint16_t raw = (0u << 11) | (7u << 6) | 40u;
    TimeFields t = TestDecoder::testResolveArrivalTime(raw, base);
    CHECK(t.day == 1);
    CHECK(t.hour == 7);
    CHECK(t.minute == 40);
    // unix: base day + 7*3600 + 40*60
    uint32_t expected = daysFromCivil(2024, 1, 1) * 86400u + 7u * 3600u + 40u * 60u;
    CHECK(t.unix_time == expected);
}

TEST_CASE("resolveArrivalTime: day_offset=1 (next day)") {
    uint32_t base = daysFromCivil(2024, 1, 1) * 86400u;
    // (1<<11)|(0<<6)|0 = day_offset=1, hour=0, min=0
    uint16_t raw = (1u << 11) | (0u << 6) | 0u;
    TimeFields t = TestDecoder::testResolveArrivalTime(raw, base);
    CHECK(t.day == 2);
    CHECK(t.hour == 0);
    CHECK(t.minute == 0);
    uint32_t expected = daysFromCivil(2024, 1, 2) * 86400u;
    CHECK(t.unix_time == expected);
}

TEST_CASE("resolveArrivalTime: base_unix < 2000 returns unresolved") {
    // 946684799 = 1999-12-31 23:59:59
    uint16_t raw = (0u << 11) | (12u << 6) | 30u;
    TimeFields t = TestDecoder::testResolveArrivalTime(raw, 946684799u);
    CHECK(t.hour == 12);
    CHECK(t.minute == 30);
    CHECK(t.unix_time == 0);
    CHECK(t.day == 0);
}

TEST_CASE("Unix時間の計算検証") {
    TimeFields t = TestDecoder::testResolveTime(1, 1, 0, 0, 1704067200u);
    CHECK(t.unix_time == 1704067200u);
}

TEST_CASE("resolveTime: now_unix=0 (未同期シナリオ)") {
    TimeFields t = TestDecoder::testResolveTime(0, 15, 10, 30, 0u);
    CHECK(t.day == 15);
    CHECK(t.hour == 10);
    CHECK(t.minute == 30);
    CHECK(t.unix_time == 0);
}

TEST_CASE("resolveTime: now_unix < 2000年 (閾値テスト)") {
    TimeFields t = TestDecoder::testResolveTime(0, 20, 12, 0, 946684799u);
    CHECK(t.day == 20);
    CHECK(t.hour == 12);
    CHECK(t.minute == 0);
    CHECK(t.unix_time == 0);

    TimeFields t2 = TestDecoder::testResolveTime(1, 1, 0, 0, 946684800u);
    CHECK(t2.unix_time == 946684800u);
}

TEST_CASE("daysFromCivil と civilFromDays の網羅的ストレステスト (1970-2100)") {
    uint32_t start_days = daysFromCivil(1970, 1, 1);
    uint32_t end_days = daysFromCivil(2100, 12, 31);

    for (uint32_t days = start_days; days <= end_days; ++days) {
        uint32_t y = 0, m = 0, d = 0;
        civilFromDays(days, y, m, d);
        uint32_t reconstructed = daysFromCivil(y, m, d);

        if (reconstructed != days) {
            CAPTURE(days);
            CAPTURE(y);
            CAPTURE(m);
            CAPTURE(d);
            CAPTURE(reconstructed);
            FAIL("日付のラウンドトリップ変換が一致しません");
        }
    }
}

// ── 緯度経度テスト (from test_latlon.cpp) ──────────────────────────────────

TEST_CASE("extractLatLon: 基本的な緯度経度抽出") {
    uint8_t buf[32] = {};

    setBits(buf, 0, 1, 0);
    setBits(buf, 1, 7, 35);
    setBits(buf, 8, 6, 30);
    setBits(buf, 14, 6, 45);

    setBits(buf, 20, 1, 0);
    setBits(buf, 21, 8, 139);
    setBits(buf, 29, 6, 45);
    setBits(buf, 35, 6, 30);

    LatLon ll = TestDecoder::testExtractLatLon(buf, 0);

    CHECK(ll.lat_ns == 0);
    CHECK(ll.lat_deg == 35);
    CHECK(ll.lat_min == 30);
    CHECK(ll.lat_sec == 45);
    CHECK(ll.lon_ew == 0);
    CHECK(ll.lon_deg == 139);
    CHECK(ll.lon_min == 45);
    CHECK(ll.lon_sec == 30);
}

TEST_CASE("extractLatLon: 南緯と西経") {
    uint8_t buf[32] = {};

    setBits(buf, 0, 1, 1);
    setBits(buf, 1, 7, 33);
    setBits(buf, 8, 6, 0);
    setBits(buf, 14, 6, 0);

    setBits(buf, 20, 1, 1);
    setBits(buf, 21, 8, 151);
    setBits(buf, 29, 6, 0);
    setBits(buf, 35, 6, 0);

    LatLon ll = TestDecoder::testExtractLatLon(buf, 0);

    CHECK(ll.lat_ns == 1);
    CHECK(ll.lat_deg == 33);
    CHECK(ll.lon_ew == 1);
    CHECK(ll.lon_deg == 151);
}

TEST_CASE("extractLatLon: 境界値テスト") {
    uint8_t buf[32] = {};

    setBits(buf, 0, 1, 0);
    setBits(buf, 1, 7, 90);
    setBits(buf, 8, 6, 59);
    setBits(buf, 14, 6, 59);

    setBits(buf, 20, 1, 0);
    setBits(buf, 21, 8, 180);
    setBits(buf, 29, 6, 59);
    setBits(buf, 35, 6, 59);

    LatLon ll = TestDecoder::testExtractLatLon(buf, 0);

    CHECK(ll.lat_deg == 90);
    CHECK(ll.lat_min == 59);
    CHECK(ll.lat_sec == 59);
    CHECK(ll.lon_deg == 180);
    CHECK(ll.lon_min == 59);
    CHECK(ll.lon_sec == 59);
}

// ── 重複除去テスト (from test_dedup.cpp) ───────────────────────────────────

TEST_CASE("DedupFilter: 新規メッセージは重複しない") {
    DedupFilter filter;
    DedupKey key{193, 43, 0xABCDEF};
    CHECK_FALSE(filter.isDuplicate(key));
}

TEST_CASE("DedupFilter: 同じキーは重複と判定される") {
    DedupFilter filter;
    DedupKey key{193, 43, 0xABCDEF};
    CHECK_FALSE(filter.isDuplicate(key));
    CHECK(filter.isDuplicate(key));
}

TEST_CASE("DedupFilter: 異なるsvidは重複しない") {
    DedupFilter filter;
    DedupKey key1{193, 43, 0xABCDEF};
    DedupKey key2{194, 43, 0xABCDEF};
    CHECK_FALSE(filter.isDuplicate(key1));
    CHECK_FALSE(filter.isDuplicate(key2));
}

TEST_CASE("DedupFilter: 異なるmsg_typeは重複しない") {
    DedupFilter filter;
    DedupKey key1{193, 43, 0xABCDEF};
    DedupKey key2{193, 44, 0xABCDEF};
    CHECK_FALSE(filter.isDuplicate(key1));
    CHECK_FALSE(filter.isDuplicate(key2));
}

TEST_CASE("DedupFilter: 異なるcrc24は重複しない") {
    DedupFilter filter;
    DedupKey key1{193, 43, 0xABCDEF};
    DedupKey key2{193, 43, 0x123456};
    CHECK_FALSE(filter.isDuplicate(key1));
    CHECK_FALSE(filter.isDuplicate(key2));
}

TEST_CASE("DedupFilter: 複数メッセージの管理") {
    DedupFilter filter;
    DedupKey key1{193, 43, 0xAAAAAA};
    DedupKey key2{193, 43, 0xBBBBBB};
    DedupKey key3{193, 43, 0xCCCCCC};

    CHECK_FALSE(filter.isDuplicate(key1));
    CHECK_FALSE(filter.isDuplicate(key2));
    CHECK_FALSE(filter.isDuplicate(key3));

    CHECK(filter.isDuplicate(key1));
    CHECK(filter.isDuplicate(key2));
    CHECK(filter.isDuplicate(key3));
}

TEST_CASE("DedupFilter: reset後に新規として扱われる") {
    DedupFilter filter;
    DedupKey key{193, 43, 0xABCDEF};
    CHECK_FALSE(filter.isDuplicate(key));
    CHECK(filter.isDuplicate(key));

    filter.reset();
    CHECK_FALSE(filter.isDuplicate(key));
}

TEST_CASE("DedupFilter: リングバッファのラップアラウンド") {
    DedupFilter filter;
    DedupKey keys[33];
    for (int i = 0; i < 33; i++) {
        keys[i] = {193, 43, (uint32_t)(0x100000 + i)};
    }

    for (int i = 0; i < 32; i++) {
        CHECK_FALSE(filter.isDuplicate(keys[i]));
    }

    CHECK_FALSE(filter.isDuplicate(keys[32]));
    CHECK_FALSE(filter.isDuplicate(keys[0]));
    CHECK(filter.isDuplicate(keys[32]));
}

TEST_CASE("DedupFilter: 同一CRCでもsvidが異なれば別メッセージ") {
    DedupFilter filter;
    DedupKey key1{55, 43, 0xABCDEF};
    DedupKey key2{56, 43, 0xABCDEF};
    DedupKey key3{57, 43, 0xABCDEF};

    CHECK_FALSE(filter.isDuplicate(key1));
    CHECK_FALSE(filter.isDuplicate(key2));
    CHECK_FALSE(filter.isDuplicate(key3));
}

TEST_CASE("DedupFilter: 大量メッセージの処理") {
    DedupFilter filter;
    for (int i = 0; i < 512; i++) {
        DedupKey key{193, 43, (uint32_t)(0x100000 + i)};
        CHECK_FALSE(filter.isDuplicate(key));
    }

    for (int i = 512 - AZARAC_DEDUP_SLOTS; i < 512; i++) {
        DedupKey key{193, 43, (uint32_t)(0x100000 + i)};
        CHECK(filter.isDuplicate(key));
    }
}

// ── sizeof 回帰ガード ────────────────────────────────────────────────────────
// RAMが制限された組込みターゲットで構造体が肥大化した場合に検出する。

TEST_CASE("Memory: sizeof guards for embedded targets") {
#if defined(__GNUC__) && ARDUINO == 0
    // Message payload_storage_ = max(sizeof(Mt43Data), sizeof(Mt44Data))
    // Current: Mt43Data=128, Mt44Data=376 → Message=392
    CHECK(sizeof(Message) <= 420);
    CHECK(sizeof(Mt43Data) <= 240);
    CHECK(sizeof(Mt44Data) <= 420);
    // Parser = NankaiPageBufferManager (4×1168=4672) + framers, decoder, dedup (~320)
    CHECK(sizeof(Parser) <= 5500);
#else
    // Skip on non-GCC or embedded — sizeof may differ per arch
    INFO("sizeof guard skipped (non-GCC or ARDUINO target)");
#endif
}

// ── ファジースモークテスト ────────────────────────────────────────────────────
// 統合 test スイート内で軽量 fuzz を実行し、クラッシュ・ハングがないことを確認

TEST_CASE("Fuzz smoke: random frames no crash") {
    std::mt19937 rng(42);
    Decoder dec;
    for (int i = 0; i < 1000; ++i) {
        uint8_t bits[32];
        generate_random_nav_bits(bits, sizeof(bits), rng);
        Frame frame;
        frame.svid = 193;
        memcpy(frame.bits, bits, 32);
        Message msg{};
        dec.decode(frame, msg, 0);
    }
}

TEST_CASE("Fuzz smoke: valid preamble + random data") {
    std::mt19937 rng(42);
    Decoder dec;
    for (int i = 0; i < 1000; ++i) {
        uint8_t bits[32];
        generate_random_nav_bits(bits, sizeof(bits), rng);
        // Set valid preamble: {0x53, 0x9A, 0xC6}
        bits[0] = (uint8_t[]){0x53, 0x9A, 0xC6}[rng() % 3];
        Frame frame;
        frame.svid = 193;
        memcpy(frame.bits, bits, 32);
        Message msg{};
        dec.decode(frame, msg, 0);
    }
}

TEST_CASE("Fuzz smoke: valid MT=43 + correct CRC") {
    std::mt19937 rng(42);
    Decoder dec;
    for (int i = 0; i < 1000; ++i) {
        uint8_t bits[32] = {};
        bits[0] = (uint8_t[]){0x53, 0x9A, 0xC6}[rng() % 3];
        // Set MT=43 at bits [8, 14)
        setBits(bits, 8, 6, 43);
        // Fill remaining payload with random
        for (int b = 14; b < 226; ++b) {
            if (rng() & 1) bits[b / 8] |= (0x80 >> (b % 8));
        }
        // Set CRC
        uint32_t crc = crc24qRef(bits, 226);
        setBits(bits, 226, 24, crc);
        Frame frame;
        frame.svid = 193;
        memcpy(frame.bits, bits, 32);
        Message msg{};
        dec.decode(frame, msg, 0);
    }
}

TEST_CASE("Fuzz smoke: corrupted NMEA no crash") {
    std::mt19937 rng(42);
    NmeaFramer framer;
    for (int i = 0; i < 1000; ++i) {
        uint8_t bytes[64];
        for (size_t j = 0; j < sizeof(bytes); ++j) {
            bytes[j] = static_cast<uint8_t>(rng() & 0xFF);
        }
        Frame frame;
        for (size_t j = 0; j < sizeof(bytes); ++j) {
            framer.feed(bytes[j], frame);
        }
        framer.reset();
    }
}
