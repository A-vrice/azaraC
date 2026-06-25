// test/core/test_boundary_values.cpp — 境界値テスト
// 緯度経度、日付、時間の境界値テスト

#include "../test_helpers.h"
#include "doctest.h"
#include <cmath>

using namespace azaraC;

// =============================================================================
// 緯度経度境界値テスト
// =============================================================================

TEST_CASE("Boundary: Latitude 90°N") {
    uint8_t buf[32] = {};
    // lat_ns=0, lat_deg=90, lat_min=59, lat_sec=59
    setBits(buf, 0, 1, 0);       // lat_ns = 0 (North)
    setBits(buf, 1, 7, 90);      // lat_deg = 90
    setBits(buf, 8, 6, 59);      // lat_min = 59
    setBits(buf, 14, 6, 59);     // lat_sec = 59

    LatLon ll = TestDecoder::testExtractLatLon(buf, 0);
    CHECK(ll.lat_ns == 0);
    CHECK(ll.lat_deg == 90);
    CHECK(ll.lat_min == 59);
    CHECK(ll.lat_sec == 59);
}

TEST_CASE("Boundary: Latitude 90°S") {
    uint8_t buf[32] = {};
    // lat_ns=1, lat_deg=90, lat_min=59, lat_sec=59
    setBits(buf, 0, 1, 1);       // lat_ns = 1 (South)
    setBits(buf, 1, 7, 90);      // lat_deg = 90
    setBits(buf, 8, 6, 59);      // lat_min = 59
    setBits(buf, 14, 6, 59);     // lat_sec = 59

    LatLon ll = TestDecoder::testExtractLatLon(buf, 0);
    CHECK(ll.lat_ns == 1);
    CHECK(ll.lat_deg == 90);
    CHECK(ll.lat_min == 59);
    CHECK(ll.lat_sec == 59);
}

TEST_CASE("Boundary: Longitude 180°E") {
    uint8_t buf[32] = {};
    // lon_ew=0, lon_deg=180, lon_min=59, lon_sec=59
    setBits(buf, 20, 1, 0);      // lon_ew = 0 (East)
    setBits(buf, 21, 8, 180);    // lon_deg = 180
    setBits(buf, 29, 6, 59);     // lon_min = 59
    setBits(buf, 35, 6, 59);     // lon_sec = 59

    LatLon ll = TestDecoder::testExtractLatLon(buf, 0);
    CHECK(ll.lon_ew == 0);
    CHECK(ll.lon_deg == 180);
    CHECK(ll.lon_min == 59);
    CHECK(ll.lon_sec == 59);
}

TEST_CASE("Boundary: Longitude 180°W") {
    uint8_t buf[32] = {};
    // lon_ew=1, lon_deg=180, lon_min=59, lon_sec=59
    setBits(buf, 20, 1, 1);      // lon_ew = 1 (West)
    setBits(buf, 21, 8, 180);    // lon_deg = 180
    setBits(buf, 29, 6, 59);     // lon_min = 59
    setBits(buf, 35, 6, 59);     // lon_sec = 59

    LatLon ll = TestDecoder::testExtractLatLon(buf, 0);
    CHECK(ll.lon_ew == 1);
    CHECK(ll.lon_deg == 180);
    CHECK(ll.lon_min == 59);
    CHECK(ll.lon_sec == 59);
}

// =============================================================================
// 日付境界値テスト
// =============================================================================

TEST_CASE("Boundary: Hour=23, Minute=59") {
    uint32_t now = 1704067200u; // 2024-01-01 00:00:00 UTC
    uint8_t bits[32] = {};

    // day=15, hour=23, minute=59
    setBits(bits, 0, 5, 15);     // day = 15
    setBits(bits, 5, 5, 23);     // hour = 23
    setBits(bits, 10, 6, 59);    // minute = 59

    TimeFields t = TestDecoder::testResolveTime(0, 15, 23, 59, now);
    CHECK(t.day == 15);
    CHECK(t.hour == 23);
    CHECK(t.minute == 59);
}

TEST_CASE("Boundary: Month=0, Day=0 (invalid)") {
    uint32_t now = 1704067200u;
    TimeFields t = TestDecoder::testResolveTime(0, 0, 0, 0, now);
    CHECK(t.day == 0);
    CHECK(t.hour == 0);
    CHECK(t.minute == 0);
    CHECK(t.unix_time == 0);
}

TEST_CASE("Boundary: Month=13 (invalid)") {
    uint32_t now = 1704067200u;
    TimeFields t = TestDecoder::testResolveTime(13, 1, 0, 0, now);
    CHECK(t.day == 0);
    CHECK(t.unix_time == 0);
}

TEST_CASE("Boundary: Hour=24 (invalid)") {
    uint32_t now = 1704067200u;
    TimeFields t = TestDecoder::testResolveTime(1, 1, 24, 0, now);
    CHECK(t.day == 0);
    CHECK(t.unix_time == 0);
}

TEST_CASE("Boundary: Minute=60 (invalid)") {
    uint32_t now = 1704067200u;
    TimeFields t = TestDecoder::testResolveTime(1, 1, 0, 60, now);
    CHECK(t.day == 0);
    CHECK(t.unix_time == 0);
}

// =============================================================================
// 深度・大きさ境界値テスト
// =============================================================================

TEST_CASE("Boundary: Depth 501+ (special value)") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 17, 4, 2);     // Hypocenter
    setBits(bits, 96, 9, 501);   // depth = 501
    setBits(bits, 214, 6, 1);

    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Message msg{};
    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 55;
    Decoder dec;
    REQUIRE(dec.decode(frame, msg, 0));
    
    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    const HypocenterData* hypo = mt43->getHypocenter();
    REQUIRE(hypo != nullptr);
    CHECK(hypo->depth == 501);
}

TEST_CASE("Boundary: Depth 511 (unknown)") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 17, 4, 2);
    setBits(bits, 96, 9, 511);   // depth = 511 (unknown)
    setBits(bits, 214, 6, 1);

    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Message msg{};
    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 55;
    Decoder dec;
    REQUIRE(dec.decode(frame, msg, 0));
    
    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    const HypocenterData* hypo = mt43->getHypocenter();
    REQUIRE(hypo != nullptr);
    CHECK(hypo->depth == 511);
}

TEST_CASE("Boundary: Magnitude 126") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 17, 4, 2);
    setBits(bits, 105, 7, 126);  // magnitude = 126
    setBits(bits, 214, 6, 1);

    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Message msg{};
    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 55;
    Decoder dec;
    REQUIRE(dec.decode(frame, msg, 0));
    
    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    const HypocenterData* hypo = mt43->getHypocenter();
    REQUIRE(hypo != nullptr);
    CHECK(hypo->magnitude == 126);
}

TEST_CASE("Boundary: Magnitude 127 (unknown)") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 17, 4, 2);
    setBits(bits, 105, 7, 127);  // magnitude = 127 (unknown)
    setBits(bits, 214, 6, 1);

    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Message msg{};
    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 55;
    Decoder dec;
    REQUIRE(dec.decode(frame, msg, 0));
    
    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    const HypocenterData* hypo = mt43->getHypocenter();
    REQUIRE(hypo != nullptr);
    CHECK(hypo->magnitude == 127);
}

// =============================================================================
// EEW 長周期地震動階級境界値テスト
// =============================================================================

TEST_CASE("Boundary: Long period ground motion lower=3, upper=3") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 17, 4, 1);     // EEW
    setBits(bits, 47, 3, 3);     // long_period_lower = 3
    setBits(bits, 50, 3, 3);     // long_period_upper = 3
    setBits(bits, 214, 6, 1);

    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Message msg{};
    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 55;
    Decoder dec;
    REQUIRE(dec.decode(frame, msg, 0));
    
    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    const EewData* eew = mt43->getEew();
    REQUIRE(eew != nullptr);
    CHECK(eew->long_period_lower == 3);
    CHECK(eew->long_period_upper == 3);
}

// =============================================================================
// 通知コード境界値テスト
// =============================================================================

TEST_CASE("Boundary: EEW notification count=3") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 17, 4, 1);     // EEW
    // 3 notification codes: 100, 200, 300
    setBits(bits, 53, 9, 100);
    setBits(bits, 62, 9, 200);
    setBits(bits, 71, 9, 300);
    setBits(bits, 214, 6, 1);

    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Message msg{};
    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 55;
    Decoder dec;
    REQUIRE(dec.decode(frame, msg, 0));
    
    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    const EewData* eew = mt43->getEew();
    REQUIRE(eew != nullptr);
    CHECK(eew->notification_count == 3);
    CHECK(eew->notification[0] == 100);
    CHECK(eew->notification[1] == 200);
    CHECK(eew->notification[2] == 300);
}

// =============================================================================
// 閏年テスト
// =============================================================================

TEST_CASE("Boundary: Leap year Feb 29") {
    uint32_t now = 1709164800u; // 2024-03-01 00:00:00 UTC (2024 is leap year)
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 17, 4, 1);     // EEW
    setBits(bits, 21, 4, 2);     // month = 2
    setBits(bits, 25, 5, 29);    // day = 29
    setBits(bits, 214, 6, 1);

    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Message msg{};
    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 55;
    Decoder dec;
    REQUIRE(dec.decode(frame, msg, now));
    
    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    CHECK(mt43->event_time.day == 29);
}

// =============================================================================
// 年末テスト
// =============================================================================

TEST_CASE("Boundary: Year end Dec 31") {
    uint32_t now = 1735686000u; // 2024-12-31 00:00:00 UTC
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 17, 4, 1);
    setBits(bits, 21, 4, 12);    // month = 12
    setBits(bits, 25, 5, 31);    // day = 31
    setBits(bits, 214, 6, 1);

    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Message msg{};
    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 55;
    Decoder dec;
    REQUIRE(dec.decode(frame, msg, now));
    
    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    CHECK(mt43->event_time.day == 31);
}
