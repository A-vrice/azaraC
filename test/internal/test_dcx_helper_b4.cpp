// DcxHelper B4 全ハザードタイプの単体テスト（decodeB4DetailedInfo の a4_code 分岐ごとのビット展開）。
// 45 コードを表で回し、各コードで「レイアウトに含まれる D フィールドだけが present」かつ「値が仕様どおり」であることを全 36 スロットについて検証する。

#define ARDUINO 0
#include "../src/internal/DcxHelper.h"
#include "../test_helpers.h"
#include "doctest.h"

using namespace azaraC::internal;

namespace {

struct B4Field {
    uint8_t idx;
    uint8_t value;
};

struct B4Row {
    uint8_t a4;
    uint16_t a18;
    uint8_t count;
    B4Field fields[4];
};

// 既存のコード別テスト（shift/mask と期待値）をそのまま表にしたもの。
// 期待値を実装の B4_LAYOUT_TABLE から生成しない（循環参照を避ける）。
static const B4Row kRows[] = {
    {  4, 0x4800, 2, {{31,0x02}, {32,0x01}}},
    {  5, 0x4800, 1, {{30,0x09}}},
    {  6, 0x6000, 1, {{33,0x03}}},
    {  9, 0x4000, 1, {{29,0x08}}},
    { 10, 0x2000, 1, {{29,0x04}}},
    { 11, 0x7800, 1, {{29,0x0F}}},
    { 15, 0x2000, 1, {{27,0x02}}},
    { 16, 0x3000, 1, {{23,0x03}}},
    { 18, 0x5000, 1, {{23,0x05}}},
    { 19, 0x3800, 1, {{26,0x07}}},
    { 21, 0x2000, 1, {{23,0x02}}},
    { 23, 0x7800, 1, {{24,0x0F}}},
    { 27, 0x4000, 1, {{22,0x04}}},
    { 30, 0x1000, 1, {{22,0x01}}},
    { 32, 0x2000, 1, {{19,0x02}}},
    { 33, 0x7000, 1, {{18,0x07}}},
    { 36, 0x55C3, 4, {{0,0x0A}, {1,0x05}, {2,0x0C}, {3,0x03}}},
    { 37, 0x1000, 1, {{20,0x01}}},
    { 43, 0x6000, 1, {{4,0x06}}},
    { 44, 0x3000, 1, {{4,0x03}}},
    { 47, 0x4700, 2, {{7,0x08}, {4,0x07}}},
    { 51, 0x4150, 2, {{25,0x10}, {34,0x15}}},
    { 53, 0x7AB0, 2, {{25,0x1E}, {34,0x2B}}},
    { 55, 0x0C00, 1, {{28,0x03}}},
    { 56, 0x2800, 1, {{28,0x0A}}},
    { 57, 0x5400, 1, {{28,0x15}}},
    { 58, 0x7C00, 1, {{28,0x1F}}},
    { 60, 0x3C00, 1, {{28,0x0F}}},
    { 63, 0x5800, 1, {{5,0x0B}}},
    { 64, 0x7C58, 4, {{7,0x0F}, {8,0x04}, {15,0x02}, {10,0x06}}},
    { 65, 0x2000, 1, {{17,0x01}}},
    { 68, 0x4000, 1, {{14,0x02}}},
    { 69, 0x3A00, 2, {{16,0x03}, {12,0x0A}}},
    { 70, 0x6800, 1, {{11,0x0D}}},
    { 71, 0x3800, 1, {{5,0x07}}},
    { 72, 0x5000, 1, {{15,0x05}}},
    { 74, 0x3B00, 2, {{8,0x03}, {12,0x0B}}},
    { 75, 0x3E80, 2, {{12,0x07}, {7,0x0D}}},
    { 76, 0x6B00, 2, {{13,0x1A}, {12,0x0C}}},
    { 77, 0x7568, 4, {{7,0x0E}, {8,0x05}, {9,0x03}, {15,0x02}}},
    { 79, 0x6680, 3, {{7,0x0C}, {8,0x06}, {10,0x04}}},
    { 80, 0x59C0, 3, {{6,0x05}, {7,0x09}, {8,0x06}}},
    { 81, 0x4B00, 2, {{7,0x09}, {5,0x06}}},
    { 82, 0x4A40, 3, {{35,0x04}, {7,0x0A}, {8,0x02}}},
    {103, 0x6000, 1, {{21,0x06}}},
};

static void expectB4(const B4Row& row) {
    B4DetailedInfo r;
    decodeB4DetailedInfo(row.a18, row.a4, r);

    INFO("a4=", static_cast<int>(row.a4), " a18=", static_cast<unsigned>(row.a18));
    REQUIRE(r.present);
    CHECK(r.a4_code == row.a4);

    bool present[B4DetailedInfo::D_COUNT] = {};
    uint8_t value[B4DetailedInfo::D_COUNT] = {};
    for (uint8_t i = 0; i < row.count; ++i) {
        present[row.fields[i].idx] = true;
        value[row.fields[i].idx] = row.fields[i].value;
    }
    for (uint8_t i = 0; i < B4DetailedInfo::D_COUNT; ++i) {
        CAPTURE(i);
        CHECK(r.d_present[i] == present[i]);
        if (present[i]) CHECK(r.d_values[i] == value[i]);
    }
}

} // namespace

TEST_CASE("B4: all a4 layouts match spec fields (45 codes)") {
    for (const B4Row& row : kRows) {
        expectB4(row);
    }
}

TEST_CASE("B4: boundary a18=0 keeps the layout present with value 0") {
    expectB4(B4Row{36, 0x0000, 4, {{0,0}, {1,0}, {2,0}, {3,0}}});
}

TEST_CASE("B4: boundary a18=0x7FFF uses the maximum field values") {
    expectB4(B4Row{36, 0x7FFF, 4, {{0,0x0F}, {1,0x07}, {2,0x0F}, {3,0x0F}}});
}

TEST_CASE("B4: unknown a4_code is present but has no D fields") {
    expectB4(B4Row{99, 0x3FFF, 0, {}});
    expectB4(B4Row{255, 0x0000, 0, {}});
}
