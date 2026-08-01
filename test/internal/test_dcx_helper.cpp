// test/internal/test_dcx_helper.cpp — DcxHelper 境界値単体テスト
// decodeLatitude16, decodeLongitude17, decodeRadiusCode, decodeAzimuth6/7 の
// 境界値および既知値を検証する。

#define ARDUINO 0
#include "../src/internal/DcxHelper.h"
#include "../test_helpers.h"
#include "doctest.h"
#include <cmath>

using namespace azaraC::internal;

TEST_CASE("decodeLatitude16: boundary and known values") {
    // Returns microdegrees (×1,000,000)
    CHECK(decodeLatitude16(0) == -90000000);
    CHECK(decodeLatitude16(65535) == 90000000);
    CHECK(decodeLatitude16(32767) == -1373);
    CHECK(decodeLatitude16(16384) == -44999313);
    CHECK(decodeLatitude16(49151) == 44999313);
}

TEST_CASE("decodeLongitude17: boundary and known values") {
    // Returns microdegrees (×1,000,000)
    CHECK(decodeLongitude17(0) == -180000000);
    CHECK(decodeLongitude17(131071) == 180000000);
    CHECK(decodeLongitude17(65535) == -1373);
}

TEST_CASE("decodeRadiusCode: boundary and OOB") {
    // Returns meters
    CHECK(decodeRadiusCode(0) == 216);
    CHECK(decodeRadiusCode(1) == 292);
    CHECK(decodeRadiusCode(31) == 2500000);
    // Out-of-bounds (≥32) → 0
    CHECK(decodeRadiusCode(32) == 0);
    CHECK(decodeRadiusCode(255) == 0);
    // Verify monotonicity: each entry must be larger than the previous
    for (uint8_t i = 1; i < 32; ++i) {
        CAPTURE(i);
        CHECK(decodeRadiusCode(i) > decodeRadiusCode(i - 1));
    }
}

TEST_CASE("decodeAzimuth6: boundary and known values") {
    // Returns dexadegrees (×100,000)
    CHECK(decodeAzimuth6(0) == -9000000);
    CHECK(decodeAzimuth6(32) == 0);
    CHECK(decodeAzimuth6(63) == 8718750);
    CHECK(decodeAzimuth6(16) == -4500000);
    CHECK(decodeAzimuth6(48) == 4500000);
}

TEST_CASE("decodeAzimuth7: boundary and known values") {
    // Returns dexadegrees (×100,000)
    CHECK(decodeAzimuth7(0) == -9000000);
    CHECK(decodeAzimuth7(64) == 0);
    CHECK(decodeAzimuth7(127) == 8859375);
    CHECK(decodeAzimuth7(32) == -4500000);
    CHECK(decodeAzimuth7(96) == 4500000);
}
