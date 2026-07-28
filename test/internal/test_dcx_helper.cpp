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
    // Latitude = -90 + (180 / 65535) * code
    CHECK(decodeLatitude16(0) == doctest::Approx(-90.0));
    CHECK(decodeLatitude16(65535) == doctest::Approx(90.0));
    // Midpoint: code=32767 → approximately -90 + 180*32767/65535 ≈ -0.0009°
    double mid = -90.0 + (180.0 / 65535.0) * 32767.0;
    CHECK(decodeLatitude16(32767) == doctest::Approx(mid).epsilon(0.00001));
    // Quarter points
    CHECK(decodeLatitude16(16384) == doctest::Approx(-45.0).epsilon(0.001));
    CHECK(decodeLatitude16(49151) == doctest::Approx(45.0).epsilon(0.001));
}

TEST_CASE("decodeLongitude17: boundary and known values") {
    // Longitude = -180 + (360 / 131071) * code
    CHECK(decodeLongitude17(0) == doctest::Approx(-180.0));
    CHECK(decodeLongitude17(131071) == doctest::Approx(180.0));
    // Midpoint
    double mid = -180.0 + (360.0 / 131071.0) * 65535.0;
    CHECK(decodeLongitude17(65535) == doctest::Approx(mid).epsilon(0.00001));
}

TEST_CASE("decodeRadiusCode: boundary and OOB") {
    // IS-QZSS-DCX-003 Table 4.2-17, validated against specification values
    CHECK(decodeRadiusCode(0) == doctest::Approx(0.216));
    CHECK(decodeRadiusCode(1) == doctest::Approx(0.292));
    CHECK(decodeRadiusCode(31) == doctest::Approx(2500.0));
    // Out-of-bounds (≥32) → 0.0
    CHECK(decodeRadiusCode(32) == doctest::Approx(0.0));
    CHECK(decodeRadiusCode(255) == doctest::Approx(0.0));
    // Verify monotonicity: each entry must be larger than the previous
    for (uint8_t i = 1; i < 32; ++i) {
        CAPTURE(i);
        CHECK(decodeRadiusCode(i) > decodeRadiusCode(i - 1));
    }
}

TEST_CASE("decodeAzimuth6: boundary and known values") {
    // Azimuth = -90 + (180 / 64) * code
    CHECK(decodeAzimuth6(0) == doctest::Approx(-90.0));
    CHECK(decodeAzimuth6(32) == doctest::Approx(0.0));
    CHECK(decodeAzimuth6(63) == doctest::Approx(87.1875));
    // Quarter points
    CHECK(decodeAzimuth6(16) == doctest::Approx(-45.0));
    CHECK(decodeAzimuth6(48) == doctest::Approx(45.0));
}

TEST_CASE("decodeAzimuth7: boundary and known values") {
    // Azimuth = -90 + (180 / 128) * code
    CHECK(decodeAzimuth7(0) == doctest::Approx(-90.0));
    CHECK(decodeAzimuth7(64) == doctest::Approx(0.0));
    CHECK(decodeAzimuth7(127) == doctest::Approx(88.59375));
    CHECK(decodeAzimuth7(32) == doctest::Approx(-45.0));
    CHECK(decodeAzimuth7(96) == doctest::Approx(45.0));
}
