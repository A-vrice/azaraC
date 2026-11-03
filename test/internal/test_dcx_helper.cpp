// DcxHelper 各デコーダの境界値・既知値の単体テスト。

#define ARDUINO 0
#include "../src/internal/DcxHelper.h"
#include "../test_helpers.h"
#include "doctest.h"
#include <cmath>

using namespace azaraC::internal;

TEST_CASE("decodeLatitude16: boundary and known values") {
    // 単位はマイクロ度（×1,000,000）
    CHECK(decodeLatitude16(0) == -90000000);
    CHECK(decodeLatitude16(65535) == 90000000);
    CHECK(decodeLatitude16(32767) == -1373);
    CHECK(decodeLatitude16(16384) == -44999313);
    CHECK(decodeLatitude16(49151) == 44999313);
}

TEST_CASE("decodeLongitude17: boundary and known values") {
    // 単位はマイクロ度（×1,000,000）
    CHECK(decodeLongitude17(0) == -180000000);
    CHECK(decodeLongitude17(131071) == 180000000);
    CHECK(decodeLongitude17(65535) == -1373);
}

TEST_CASE("decodeRadiusCode: all 32 spec values") {
    // IS-QZSS-DCX-004 Table 4.2-17 (Ellipse Semi-Major Axis) の全 32 値。
    // 実装表をそのまま写さず、仕様表の値を独立した期待値として固定する。
    static const int32_t expected[32] = {
        216,     292,     395,     535,     723,     978,     1322,    1788,
        2418,    3269,    4421,    5979,    8085,    10933,   14784,   19992,
        27035,   36559,   49439,   66855,   90407,   122255,  165324,  223564,
        302322,  408824,  552846,  747603,  1010970, 1367116, 1848727, 2500000
    };
    for (uint8_t i = 0; i < 32; ++i) {
        CAPTURE(i);
        CHECK(decodeRadiusCode(i) == expected[i]);
    }
    // 範囲外（≥32）は 0
    CHECK(decodeRadiusCode(32) == 0);
    CHECK(decodeRadiusCode(255) == 0);
}

TEST_CASE("decodeAzimuth6: boundary and known values") {
    // 単位は 100,000 分度（×100,000）
    CHECK(decodeAzimuth6(0) == -9000000);
    CHECK(decodeAzimuth6(32) == 0);
    CHECK(decodeAzimuth6(63) == 8718750);
    CHECK(decodeAzimuth6(16) == -4500000);
    CHECK(decodeAzimuth6(48) == 4500000);
}

TEST_CASE("decodeAzimuth7: boundary and known values") {
    // 単位は 100,000 分度（×100,000）
    CHECK(decodeAzimuth7(0) == -9000000);
    CHECK(decodeAzimuth7(64) == 0);
    CHECK(decodeAzimuth7(127) == 8859375);
    CHECK(decodeAzimuth7(32) == -4500000);
    CHECK(decodeAzimuth7(96) == 4500000);
}

TEST_CASE("decodeLatitude17: boundary and known values") {
    // EX3: A12 と同じ式、17 ビット、マイクロ度
    CHECK(decodeLatitude17(0) == -90000000);
    CHECK(decodeLatitude17(131071) == 90000000);
    CHECK(decodeLatitude17(32767) == -45001030);
    CHECK(decodeLatitude17(65535) == -687);
    CHECK(decodeLatitude17(65536) == 687);
}

TEST_CASE("decodeLongitude17_45_225: boundary and known values") {
    // EX4: 45 + (180/(2^17-1)) * code、マイクロ度（45..225 度）
    CHECK(decodeLongitude17_45_225(0) == 45000000);
    CHECK(decodeLongitude17_45_225(131071) == 225000000);
    CHECK(decodeLongitude17_45_225(65535) == 134999313);
}

TEST_CASE("decodeB2HazardCenter: C5/C6 table and >63 rounding branch") {
    // EWSS CAMF v1.2 §3.7.2: delta = -10 + 20*code/128 度。code <=63 は code をそのまま使い、code >63 は +1 の丸め分岐に入る。
    CHECK(decodeB2HazardCenter(0, 0).delta_lat_microdeg == -10000000);
    CHECK(decodeB2HazardCenter(0, 0).delta_lon_microdeg == -10000000);
    CHECK(decodeB2HazardCenter(43, 16).delta_lat_microdeg == -3281250);
    CHECK(decodeB2HazardCenter(63, 63).delta_lat_microdeg == -156250);
    CHECK(decodeB2HazardCenter(64, 64).delta_lat_microdeg == 156250);
    CHECK(decodeB2HazardCenter(127, 127).delta_lon_microdeg == 10000000);

    // c5 と c6 は独立
    B2HazardCenter b2 = decodeB2HazardCenter(86, 107);
    CHECK(b2.c5 == 86);
    CHECK(b2.c6 == 107);
    CHECK(b2.delta_lat_microdeg == 3593750);
    CHECK(b2.delta_lon_microdeg == 6875000);
}

TEST_CASE("decodeCityCodeList: layout, zero skip and order") {
    // EX8=1: 16 bit コード 4 個を ex9[0:15],[16:31],[32:47],[48:63] に置く
    uint16_t codes[4] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
    uint64_t ex9 = ((uint64_t)0x1234) | ((uint64_t)0x5678 << 16) |
                   ((uint64_t)0x9ABC << 32) | ((uint64_t)0xDEF0 << 48);
    uint8_t n = decodeCityCodeList(ex9, codes);
    CHECK(n == 4);
    CHECK(codes[0] == 0x1234);
    CHECK(codes[1] == 0x5678);
    CHECK(codes[2] == 0x9ABC);
    CHECK(codes[3] == 0xDEF0);

    // ゼロのコードは飛ばし、残りは相対順序を保つ。
    codes[0] = codes[1] = codes[2] = codes[3] = 0xFFFF;
    uint64_t ex9_zero = ((uint64_t)0x0000) | ((uint64_t)0x0007 << 16) |
                        ((uint64_t)0x0000 << 32) | ((uint64_t)0x0009 << 48);
    n = decodeCityCodeList(ex9_zero, codes);
    CHECK(n == 2);
    CHECK(codes[0] == 0x0007);
    CHECK(codes[1] == 0x0009);

    // すべてゼロならコードなし。
    CHECK(decodeCityCodeList(0, codes) == 0);
}
