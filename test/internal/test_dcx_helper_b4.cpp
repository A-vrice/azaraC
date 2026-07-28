// test/internal/test_dcx_helper_b4.cpp — DcxHelper B4 全ハザードタイプテスト
// decodeB4DetailedInfo の各 a4_code 分岐を網羅し、正しいビット展開を検証する

#define ARDUINO 0
#include "../src/internal/DcxHelper.h"
#include "../test_helpers.h"
#include "doctest.h"
#include <cmath>

using namespace azaraC::internal;

// ---------------------------------------------------------------------------
// ヘルパー: B4 result のアサーション
// ---------------------------------------------------------------------------

static void check_no_present(const B4DetailedInfo& r) {
    for (uint8_t i = 0; i < B4DetailedInfo::D_COUNT; ++i) {
        CHECK(!r.d_present[i]);
    }
}

static void check_value(const B4DetailedInfo& r, uint8_t idx, uint8_t expected) {
    CHECK(r.d_present[idx]);
    CHECK(r.d_values[idx] == expected);
}

static void check_not_present(const B4DetailedInfo& r, uint8_t idx) {
    CHECK(!r.d_present[idx]);
}

// ---------------------------------------------------------------------------
// 各 a4_code の分岐テスト
// ---------------------------------------------------------------------------

TEST_CASE("B4: Earthquake (a4=36) - D1/D2/D3/D4") {
    // a18[14:11]=D1(4b), a18[10:8]=D2(3b), a18[7:4]=D3(4b), a18[3:0]=D4(4b)
    // D1=0x0A, D2=0x05, D3=0x0C, D4=0x03
    uint16_t a18 = (0x0A << 11) | (0x05 << 8) | (0x0C << 4) | 0x03;
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 36, r);
    REQUIRE(r.present);
    CHECK(r.a4_code == 36);
    check_value(r, 0, 0x0A); // D1
    check_value(r, 1, 0x05); // D2
    check_value(r, 2, 0x0C); // D3
    check_value(r, 3, 0x03); // D4
    // 他の D_present は false
    check_not_present(r, 4);
    check_not_present(r, 5);
}

TEST_CASE("B4: Tsunami (a4=43) - D5") {
    // D5[131:133] → a18[14:12] → shift=12, mask=0x07
    // D5 = 0x06
    uint16_t a18 = (0x06 << 12);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 43, r);
    REQUIRE(r.present);
    check_value(r, 4, 0x06); // D5
    check_not_present(r, 0);
    check_not_present(r, 5);
}

TEST_CASE("B4: Tidal wave (a4=44) - D5") {
    uint16_t a18 = (0x03 << 12);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 44, r);
    REQUIRE(r.present);
    check_value(r, 4, 0x03); // D5
}

TEST_CASE("B4: Cold wave (a4=63) - D6") {
    // D6[131:134] → a18[14:11] → shift=11, mask=0x0F
    uint16_t a18 = (0x0B << 11);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 63, r);
    REQUIRE(r.present);
    check_value(r, 5, 0x0B); // D6
    check_not_present(r, 4);
}

TEST_CASE("B4: Heat wave (a4=71) - D6") {
    uint16_t a18 = (0x07 << 11);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 71, r);
    REQUIRE(r.present);
    check_value(r, 5, 0x07); // D6
}

TEST_CASE("B4: Hurricane (a4=80) - D7/D8/D9") {
    // D7[131:133]→a18[14:12] shift=12 mask=0x07
    // D8[134:137]→a18[11:8]  shift=8  mask=0x0F
    // D9[138:140]→a18[7:5]   shift=5  mask=0x07
    uint16_t a18 = (0x05 << 12) | (0x09 << 8) | (0x06 << 5);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 80, r);
    REQUIRE(r.present);
    check_value(r, 6, 0x05); // D7
    check_value(r, 7, 0x09); // D8
    check_value(r, 8, 0x06); // D9
}

TEST_CASE("B4: Typhoon (a4=82) - D36/D8/D9") {
    // D36[131:133]→a18[14:12] shift=12 mask=0x07
    // D8[134:137]→a18[11:8]   shift=8  mask=0x0F
    // D9[138:140]→a18[7:5]    shift=5  mask=0x07
    uint16_t a18 = (0x04 << 12) | (0x0A << 8) | (0x02 << 5);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 82, r);
    REQUIRE(r.present);
    check_value(r, 35, 0x04); // D36
    check_value(r, 7,  0x0A); // D8
    check_value(r, 8,  0x02); // D9
    check_not_present(r, 6);
}

TEST_CASE("B4: Tornado (a4=79) - D8/D9/D11") {
    // D8[131:134]→a18[14:11] shift=11 mask=0x0F
    // D9[135:137]→a18[10:8]  shift=8  mask=0x07
    // D11[138:140]→a18[7:5]  shift=5  mask=0x07
    uint16_t a18 = (0x0C << 11) | (0x06 << 8) | (0x04 << 5);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 79, r);
    REQUIRE(r.present);
    check_value(r, 7,  0x0C); // D8
    check_value(r, 8,  0x06); // D9
    check_value(r, 10, 0x04); // D11
}

TEST_CASE("B4: Storm/Thunderstorm (a4=77) - D8/D9/D10/D16") {
    // D8[131:134]→a18[14:11] shift=11 mask=0x0F
    // D9[135:137]→a18[10:8]  shift=8  mask=0x07
    // D10[138:140]→a18[7:5]  shift=5  mask=0x07
    // D16[141:143]→a18[4:2]  shift=2  mask=0x07
    uint16_t a18 = (0x0E << 11) | (0x05 << 8) | (0x03 << 5) | (0x02 << 2);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 77, r);
    REQUIRE(r.present);
    check_value(r, 7,  0x0E); // D8
    check_value(r, 8,  0x05); // D9
    check_value(r, 9,  0x03); // D10
    check_value(r, 15, 0x02); // D16
}

TEST_CASE("B4: Hail (a4=70) - D12") {
    // D12[131:134]→a18[14:11] shift=11 mask=0x0F
    uint16_t a18 = (0x0D << 11);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 70, r);
    REQUIRE(r.present);
    check_value(r, 11, 0x0D); // D12
}

TEST_CASE("B4: Rainfall (a4=74) - D9/D13") {
    // D9[131:133]→a18[14:12] shift=12 mask=0x07
    // D13[134:137]→a18[11:8] shift=8  mask=0x0F
    uint16_t a18 = (0x03 << 12) | (0x0B << 8);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 74, r);
    REQUIRE(r.present);
    check_value(r, 8,  0x03); // D9
    check_value(r, 12, 0x0B); // D13
}

TEST_CASE("B4: Snowfall (a4=76) - D14/D13") {
    // D14[131:135]→a18[14:10] shift=10 mask=0x1F
    // D13[136:139]→a18[9:6]   shift=6  mask=0x0F
    uint16_t a18 = (0x1A << 10) | (0x0C << 6);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 76, r);
    REQUIRE(r.present);
    check_value(r, 13, 0x1A); // D14
    check_value(r, 12, 0x0C); // D13
}

TEST_CASE("B4: Flood (a4=68) - D15") {
    // D15[131:132]→a18[14:13] shift=13 mask=0x03
    uint16_t a18 = (0x02 << 13);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 68, r);
    REQUIRE(r.present);
    check_value(r, 14, 0x02); // D15
}

TEST_CASE("B4: Lightning (a4=72) - D16") {
    // D16[131:133]→a18[14:12] shift=12 mask=0x07
    uint16_t a18 = (0x05 << 12);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 72, r);
    REQUIRE(r.present);
    check_value(r, 15, 0x05); // D16
}

TEST_CASE("B4: Wind chill/Frost (a4=81) - D8/D6") {
    // D8[131:134]→a18[14:11] shift=11 mask=0x0F
    // D6[135:138]→a18[10:7]  shift=7  mask=0x0F
    uint16_t a18 = (0x09 << 11) | (0x06 << 7);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 81, r);
    REQUIRE(r.present);
    check_value(r, 7, 0x09); // D8
    check_value(r, 5, 0x06); // D6
}

TEST_CASE("B4: Derecho (a4=64) - D8/D9/D16/D11") {
    // D8[131:134]→a18[14:11] shift=11 mask=0x0F
    // D9[135:137]→a18[10:8]  shift=8  mask=0x07
    // D16[138:140]→a18[7:5]  shift=5  mask=0x07
    // D11[141:143]→a18[4:2]  shift=2  mask=0x07
    uint16_t a18 = (0x0F << 11) | (0x04 << 8) | (0x02 << 5) | (0x06 << 2);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 64, r);
    REQUIRE(r.present);
    check_value(r, 7,  0x0F); // D8
    check_value(r, 8,  0x04); // D9
    check_value(r, 15, 0x02); // D16
    check_value(r, 10, 0x06); // D11
}

TEST_CASE("B4: Fog (a4=69) - D17/D13") {
    // D17[131:133]→a18[14:12] shift=12 mask=0x07
    // D13[134:137]→a18[11:8]  shift=8  mask=0x0F
    uint16_t a18 = (0x03 << 12) | (0x0A << 8);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 69, r);
    REQUIRE(r.present);
    check_value(r, 16, 0x03); // D17
    check_value(r, 12, 0x0A); // D13
}

TEST_CASE("B4: Snow storm/Blizzard (a4=75) - D13/D8") {
    // D13[131:134]→a18[14:11] shift=11 mask=0x0F
    // D8[135:138]→a18[10:7]   shift=7  mask=0x0F
    uint16_t a18 = (0x07 << 11) | (0x0D << 7);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 75, r);
    REQUIRE(r.present);
    check_value(r, 12, 0x07); // D13
    check_value(r, 7,  0x0D); // D8
}

TEST_CASE("B4: Drought (a4=65) - D18") {
    // D18[131:132]→a18[14:13] shift=13 mask=0x03
    uint16_t a18 = (0x01 << 13);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 65, r);
    REQUIRE(r.present);
    check_value(r, 17, 0x01); // D18
}

TEST_CASE("B4: Avalanche (a4=33) - D19") {
    // D19[131:133]→a18[14:12] shift=12 mask=0x07
    uint16_t a18 = (0x07 << 12);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 33, r);
    REQUIRE(r.present);
    check_value(r, 18, 0x07); // D19
}

TEST_CASE("B4: Ash fall (a4=32) - D20") {
    // D20[131:133]→a18[14:12] shift=12 mask=0x07
    uint16_t a18 = (0x02 << 12);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 32, r);
    REQUIRE(r.present);
    check_value(r, 19, 0x02); // D20
}

TEST_CASE("B4: Wind/wave/storm surge (a4=47) - D8/D5") {
    // D8[131:134]→a18[14:11] shift=11 mask=0x0F
    // D5[135:137]→a18[10:8]  shift=8  mask=0x07
    uint16_t a18 = (0x08 << 11) | (0x07 << 8);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 47, r);
    REQUIRE(r.present);
    check_value(r, 7, 0x08); // D8
    check_value(r, 4, 0x07); // D5
}

TEST_CASE("B4: Geomagnetic (a4=37) - D21") {
    // D21[131:133]→a18[14:12] shift=12 mask=0x07
    uint16_t a18 = (0x01 << 12);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 37, r);
    REQUIRE(r.present);
    check_value(r, 20, 0x01); // D21
}

TEST_CASE("B4: Terrorism (a4=103) - D22") {
    // D22[131:133]→a18[14:12] shift=12 mask=0x07
    uint16_t a18 = (0x06 << 12);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 103, r);
    REQUIRE(r.present);
    check_value(r, 21, 0x06); // D22
}

TEST_CASE("B4: Forest fire (a4=27) - D23") {
    // D23[131:133]→a18[14:12] shift=12 mask=0x07
    uint16_t a18 = (0x04 << 12);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 27, r);
    REQUIRE(r.present);
    check_value(r, 22, 0x04); // D23
}

TEST_CASE("B4: Risk of fire (a4=30) - D23") {
    uint16_t a18 = (0x01 << 12);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 30, r);
    REQUIRE(r.present);
    check_value(r, 22, 0x01); // D23
}

TEST_CASE("B4: Contaminated water (a4=16) - D24") {
    // D24[131:133]→a18[14:12] shift=12 mask=0x07
    uint16_t a18 = (0x03 << 12);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 16, r);
    REQUIRE(r.present);
    check_value(r, 23, 0x03); // D24
}

TEST_CASE("B4: Marine pollution (a4=18) - D24") {
    uint16_t a18 = (0x05 << 12);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 18, r);
    REQUIRE(r.present);
    check_value(r, 23, 0x05); // D24
}

TEST_CASE("B4: River pollution (a4=21) - D24") {
    uint16_t a18 = (0x02 << 12);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 21, r);
    REQUIRE(r.present);
    check_value(r, 23, 0x02); // D24
}

TEST_CASE("B4: UV radiation (a4=23) - D25") {
    // D25[131:134]→a18[14:11] shift=11 mask=0x0F
    uint16_t a18 = (0x0F << 11);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 23, r);
    REQUIRE(r.present);
    check_value(r, 24, 0x0F); // D25
}

TEST_CASE("B4: Risk of infection (a4=53) - D26/D35") {
    // D26[131:135]→a18[14:10] shift=10 mask=0x1F
    // D35[136:141]→a18[9:4]   shift=4  mask=0x3F
    uint16_t a18 = (0x1E << 10) | (0x2B << 4);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 53, r);
    REQUIRE(r.present);
    check_value(r, 25, 0x1E); // D26
    check_value(r, 34, 0x2B); // D35
}

TEST_CASE("B4: Pandemic (a4=51) - D26/D35") {
    uint16_t a18 = (0x10 << 10) | (0x15 << 4);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 51, r);
    REQUIRE(r.present);
    check_value(r, 25, 0x10); // D26
    check_value(r, 34, 0x15); // D35
}

TEST_CASE("B4: Noise pollution (a4=19) - D27") {
    // D27[131:134]→a18[14:11] shift=11 mask=0x0F
    uint16_t a18 = (0x07 << 11);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 19, r);
    REQUIRE(r.present);
    check_value(r, 26, 0x07); // D27
}

TEST_CASE("B4: Air pollution (a4=15) - D28") {
    // D28[131:133]→a18[14:12] shift=12 mask=0x07
    uint16_t a18 = (0x02 << 12);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 15, r);
    REQUIRE(r.present);
    check_value(r, 27, 0x02); // D28
}

TEST_CASE("B4: Gas supply outage (a4=56) - D29") {
    // D29[131:135]→a18[14:10] shift=10 mask=0x1F
    uint16_t a18 = (0x0A << 10);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 56, r);
    REQUIRE(r.present);
    check_value(r, 28, 0x0A); // D29
}

TEST_CASE("B4: IT outage (a4=57) - D29") {
    uint16_t a18 = (0x15 << 10);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 57, r);
    REQUIRE(r.present);
    check_value(r, 28, 0x15); // D29
}

TEST_CASE("B4: Power outage (a4=58) - D29") {
    uint16_t a18 = (0x1F << 10);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 58, r);
    REQUIRE(r.present);
    check_value(r, 28, 0x1F); // D29
}

TEST_CASE("B4: Emergency number outage (a4=55) - D29") {
    uint16_t a18 = (0x03 << 10);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 55, r);
    REQUIRE(r.present);
    check_value(r, 28, 0x03); // D29
}

TEST_CASE("B4: Telephone line outage (a4=60) - D29") {
    uint16_t a18 = (0x0F << 10);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 60, r);
    REQUIRE(r.present);
    check_value(r, 28, 0x0F); // D29
}

TEST_CASE("B4: Radiological hazard (a4=9) - D30") {
    // D30[131:134]→a18[14:11] shift=11 mask=0x0F
    uint16_t a18 = (0x08 << 11);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 9, r);
    REQUIRE(r.present);
    check_value(r, 29, 0x08); // D30
}

TEST_CASE("B4: Nuclear hazard (a4=10) - D30") {
    uint16_t a18 = (0x04 << 11);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 10, r);
    REQUIRE(r.present);
    check_value(r, 29, 0x04); // D30
}

TEST_CASE("B4: Nuclear power station accident (a4=11) - D30") {
    uint16_t a18 = (0x0F << 11);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 11, r);
    REQUIRE(r.present);
    check_value(r, 29, 0x0F); // D30
}

TEST_CASE("B4: Chemical hazard (a4=5) - D31") {
    // D31[131:134]→a18[14:11] shift=11 mask=0x0F
    uint16_t a18 = (0x09 << 11);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 5, r);
    REQUIRE(r.present);
    check_value(r, 30, 0x09); // D31
}

TEST_CASE("B4: Biological hazard (a4=4) - D32/D33") {
    // D32[131:132]→a18[14:13] shift=13 mask=0x03
    // D33[133:134]→a18[12:11] shift=11 mask=0x03
    uint16_t a18 = (0x02 << 13) | (0x01 << 11);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 4, r);
    REQUIRE(r.present);
    check_value(r, 31, 0x02); // D32
    check_value(r, 32, 0x01); // D33
}

TEST_CASE("B4: Explosive hazard (a4=6) - D34") {
    // D34[131:132]→a18[14:13] shift=13 mask=0x03
    uint16_t a18 = (0x03 << 13);
    B4DetailedInfo r;
    decodeB4DetailedInfo(a18, 6, r);
    REQUIRE(r.present);
    check_value(r, 33, 0x03); // D34
}

// ---------------------------------------------------------------------------
// 境界値・異常系テスト
// ---------------------------------------------------------------------------

TEST_CASE("B4: 境界値 - a18=0 は全 D が 0") {
    B4DetailedInfo r;
    decodeB4DetailedInfo(0x0000, 36, r);
    REQUIRE(r.present);
    CHECK(r.d_values[0] == 0);
    CHECK(r.d_values[1] == 0);
    CHECK(r.d_values[2] == 0);
    CHECK(r.d_values[3] == 0);
}

TEST_CASE("B4: 境界値 - a18=0x7FFF (全ビット 1)") {
    B4DetailedInfo r;
    decodeB4DetailedInfo(0x7FFF, 36, r);
    REQUIRE(r.present);
    // D1=0x0F, D2=0x07, D3=0x0F, D4=0x0F
    CHECK(r.d_values[0] == 0x0F);
    CHECK(r.d_values[1] == 0x07);
    CHECK(r.d_values[2] == 0x0F);
    CHECK(r.d_values[3] == 0x0F);
}

TEST_CASE("B4: unknown a4_code は present=true だが d_present=false") {
    // default ケースに落ちる
    B4DetailedInfo r;
    decodeB4DetailedInfo(0x3FFF, 99, r);
    CHECK(r.present);
    CHECK(r.a4_code == 99);
    // どの D_present も false
    for (uint8_t i = 0; i < B4DetailedInfo::D_COUNT; ++i) {
        CHECK(!r.d_present[i]);
    }
}

TEST_CASE("B4: default でも a4_code は保持される") {
    B4DetailedInfo r;
    decodeB4DetailedInfo(0x0000, 255, r);
    CHECK(r.present);
    CHECK(r.a4_code == 255);
    check_no_present(r);
}
