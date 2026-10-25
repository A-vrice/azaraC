// test/core/test_time_equivalence.cpp
// Decoder::civil_from_days / days_from_civil の高速版 (u16 演算 + 400 年ブロック引き算) が
// 旧実装 (Hinnant era 法・u32 除算) と実用域で完全一致することを全日スイープで検証する。
// resolveTime の境界意味 (month==0 の 3 候補探索・stale 処理・2/29 正規化) は
// test/integration/test_time_resolution.cpp が担う。ここは純粋な日付変換の等価性のみ。

#include "../test_helpers.h"
#include "doctest.h"

#include <cstdint>
#include <string>

using namespace azaraC;

// 旧実装 (Decoder.cpp の *_ref と同一・リファレンスオラクル)
static void civilRef(uint32_t days_since_1970, uint32_t& y, uint32_t& m, uint32_t& d) {
    uint32_t z = days_since_1970 + 719468u;
    uint32_t era = z / 146097u;
    uint32_t doe = z - era * 146097u;
    uint32_t yoe = (doe - doe / 1460u + doe / 36524u - doe / 146096u) / 365u;
    y = yoe + era * 400u;
    uint32_t doy = doe - (365u * yoe + yoe / 4u - yoe / 100u);
    uint32_t mp = (5u * doy + 2u) / 153u;
    d = doy - (153u * mp + 2u) / 5u + 1u;
    m = mp + (mp < 10u ? 3u : -9u);
    y += (m <= 2u);
}

static uint32_t daysRef(uint32_t y, uint32_t m, uint32_t d) {
    y -= (m <= 2u);
    uint32_t era = y / 400u;
    uint32_t yoe = y - era * 400u;
    uint32_t doy = (153u * (m + (m > 2u ? (uint32_t)-3u : 9u)) + 2u) / 5u + d - 1u;
    uint32_t doe = yoe * 365u + yoe / 4u - yoe / 100u + doy;
    return era * 146097u + doe - 719468u;
}

static std::string ymdStr(uint32_t y, uint32_t m, uint32_t d) {
    return std::to_string(y) + "-" + std::to_string(m) + "-" + std::to_string(d);
}

// 1970-01-01 .. 2400-12-31 の全日で civil_from_days を旧実装と比較し、往復も検証する。
// u32 unix 秒の上限 (2106 年) と平年の世紀境界 (2100 年) を含む。
TEST_CASE("Time equivalence: civil_from_days full sweep 1970..2400") {
    const uint32_t end_days = daysRef(2400, 12, 31);
    uint32_t bad = UINT32_MAX;
    for (uint32_t days = 0; days <= end_days; ++days) {
        uint32_t y1, m1, d1, y2, m2, d2;
        civilFromDays(days, y1, m1, d1);
        civilRef(days, y2, m2, d2);
        if (y1 != y2 || m1 != m2 || d1 != d2 || daysFromCivil(y1, m1, d1) != days) {
            bad = days;
            if (y1 != y2 || m1 != m2 || d1 != d2) {
                const std::string msg = "civil_from_days mismatch at day " + std::to_string(days)
                    + ": got " + ymdStr(y1, m1, d1) + " want " + ymdStr(y2, m2, d2);
                FAIL(msg);
            } else {
                const std::string msg = "days_from_civil roundtrip mismatch at day " + std::to_string(days);
                FAIL(msg);
            }
        }
    }
    CHECK(bad == UINT32_MAX);
}

// days_from_civil 単体: 全 (年 1970..2400 × 月 1..12 × 日 1..31)。日が月長を超える入力も
// 旧実装と同じ正規化 (例: 2/30 → 3/2 相当の日数) になることを検証する。
TEST_CASE("Time equivalence: days_from_civil full domain sweep") {
    uint32_t bad_y = 0, bad_m = 0, bad_d = 0;
    for (uint32_t y = 1970; y <= 2400; ++y) {
        for (uint32_t m = 1; m <= 12; ++m) {
            for (uint32_t d = 1; d <= 31; ++d) {
                if (daysFromCivil(y, m, d) != daysRef(y, m, d)) {
                    bad_y = y; bad_m = m; bad_d = d;
                }
            }
        }
    }
    if (bad_y) {
        const std::string msg = "days_from_civil mismatch at " + ymdStr(bad_y, bad_m, bad_d);
        FAIL(msg);
    }
    CHECK(bad_y == 0);
}

// 実用域の外 (year > 9999 / days > 9999-12-31) もオラクルと完全一致すること。
TEST_CASE("Time equivalence: out-of-range inputs fall back to reference") {
    const uint32_t beyond[][3] = {
        {10000, 1, 1}, {12345, 6, 15}, {99999, 12, 31}, {58, 7, 1},
    };
    for (const auto& ymd : beyond) {
        CHECK(daysFromCivil(ymd[0], ymd[1], ymd[2]) == daysRef(ymd[0], ymd[1], ymd[2]));
    }
    for (uint32_t days = 2932896u; days < 2932896u + 800u; ++days) {
        uint32_t y1, m1, d1, y2, m2, d2;
        civilFromDays(days, y1, m1, d1);
        civilRef(days, y2, m2, d2);
        CHECK(y1 == y2);
        CHECK(m1 == m2);
        CHECK(d1 == d2);
    }
}
