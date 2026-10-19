// DCX MT44 decode helpers
// Based on IS-QZSS-DCX-004 / EWSS CAMF v1.2
#include "DcxHelper.h"
#include "../azaraC_config.h"   // AZARAC_PROGMEM_NEAR / AZARAC_PGM_READ_*

namespace azaraC {
namespace internal {

// Latitude/Longitude decoding

int32_t decodeLatitude16(uint16_t code) {
    // -90,000,000 + 180,000,000 * code / 65535, rounded
    return static_cast<int32_t>(
        -90000000LL + (180000000LL * code + 32767) / 65535
    );
}

int32_t decodeLongitude17(uint32_t code) {
    // -180,000,000 + 360,000,000 * code / 131071, rounded
    return static_cast<int32_t>(
        -180000000LL + (360000000LL * code + 65535) / 131071
    );
}

int32_t decodeLatitude17(uint32_t code) {
    return static_cast<int32_t>(
        -90000000LL + (180000000LL * code + 65535) / 131071
    );
}

int32_t decodeLongitude17_45_225(uint32_t code) {
    return static_cast<int32_t>(
        45000000LL + (180000000LL * code + 65535) / 131071
    );
}

// Radius decoding (5-bit code): IS-QZSS-DCX-003 Table 4.2-17 / 4.2-18 Radius[m] = 10^(log10(216.20) + a * (log10(2500000) - log10(216.20)) / 31)
// Flash に置く: avr-libc のリンカスクリプトは .rodata を .data（SRAM）へ含めるので、属性の無い const 配列はそのまま SRAM を食う（実測 128 B）。
static const int32_t RADIUS_TABLE[32] AZARAC_PROGMEM_NEAR = {
        216,
        292,
        395,
        535,
        723,
        978,
        1322,
        1788,
        2418,
        3269,
        4421,
        5979,
        8085,
        10933,
        14784,
        19992,
        27035,
        36559,
        49439,
        66855,
        90407,
        122255,
        165324,
        223564,
        302322,
        408824,
        552846,
        747603,
        1010970,
        1367116,
        1848727,
        2500000
};

int32_t decodeRadiusCode(uint8_t code) {
    if (code < 32) {
        return static_cast<int32_t>(AZARAC_PGM_READ_DWORD(&RADIUS_TABLE[code]));
    }
    return 0;
}

// Azimuth decoding

int32_t decodeAzimuth6(uint8_t code) {
    // -9,000,000 + 18,000,000 * code / 64 (×100,000 scale)
    return static_cast<int32_t>(
        -9000000LL + (18000000LL * code + 32) / 64
    );
}

int32_t decodeAzimuth7(uint8_t code) {
    // -9,000,000 + 18,000,000 * code / 128 (×100,000 scale)
    return static_cast<int32_t>(
        -9000000LL + (18000000LL * code + 64) / 128
    );
}

// J-Alert EX9 decoding

uint8_t decodePrefectureBitmask(uint64_t ex9, uint8_t* out_positions) {
    uint8_t count = 0;

    // EX8=0: prefecture = ex9[63:17] (stream bits 147..193); ex9[16:0] (bits 194..210) reserved.

    uint64_t pref = ex9 >> 17;

    for (uint8_t i = 0; i < 47; ++i) {
        if (pref & (1ULL << i)) {
            // i+1 = JIS code
            out_positions[count++] = i + 1;
        }
    }

    return count;
}

uint8_t decodeCityCodeList(uint64_t ex9, uint16_t* out_codes) {
    uint8_t count = 0;

    // EX8=1: four 16-bit codes, LSB-first.

    for (uint8_t i = 0; i < 4; ++i) {
        uint16_t code = static_cast<uint16_t>((ex9 >> (i * 16)) & 0xFFFF);
        if (code != 0) {
            out_codes[count++] = code;
        }
    }

    return count;
}

// B1 (A17=00) - Improved Resolution of Main Ellipse (EWSS CAMF v1.2 §3.7.1) A18 is MSB-first (a18[14] = spec bit 131): C1..C4 = spec 131-133/134-136/137-139/140-142 → a18[14:12]/[11:9]/[8:6]/[5:3] (3b each); a18[2:0] reserved.

B1Refinement decodeB1Refinement(uint16_t a18) {
    B1Refinement b1;
    b1.c1 = (a18 >> 12) & 0x07;
    b1.c2 = (a18 >> 9)  & 0x07;
    b1.c3 = (a18 >> 6)  & 0x07;
    b1.c4 = (a18 >> 3)  & 0x07;
    return b1;
}

int32_t b1RefinedLatitudeOffset(uint8_t c1) {
    // C1 × 180,000,000 / (8 × 65535), microdegrees
    return static_cast<int32_t>(
        (static_cast<int64_t>(c1) * 180000000LL + 262140) / 524280
    );
}

int32_t b1RefinedLongitudeOffset(uint8_t c2) {
    // C2 × 360,000,000 / (8 × 131071), microdegrees
    return static_cast<int32_t>(
        (static_cast<int64_t>(c2) * 360000000LL + 524284) / 1048568
    );
}

int32_t b1RefinedRadiusM(uint8_t code, int32_t base_radius_m, uint8_t original_radius_code) {
    // refined = base - (delta * code + 4) / 8  （四捨五入）
    int32_t delta_m;
    if (original_radius_code == 0) {
        delta_m = decodeRadiusCode(0);
    } else {
        delta_m = decodeRadiusCode(original_radius_code) - decodeRadiusCode(original_radius_code - 1);
    }
    return base_radius_m - (delta_m * code + 4) / 8;
}

// B2 (A17=01) - Position of the Centre of the Hazard (EWSS CAMF v1.2 §3.7.2)

B2HazardCenter decodeB2HazardCenter(uint8_t c5, uint8_t c6) {
    B2HazardCenter r{};
    r.c5 = c5;
    r.c6 = c6;
    // delta = -10 + 20 * code / 128 (microdegrees); code 64..127 rounds up (+1) so code 127 gives exactly +10,000,000.
    // Matches the EWSS-CAMF v1.2 §3.7.2 C5/C6 table for all visible entries (e.g. 0 → -10°, 127 → +10°).
    if (c5 <= 63) r.delta_lat_microdeg = -10000000 + 156250 * c5;
    else          r.delta_lat_microdeg = -10000000 + 156250 * (c5 + 1);
    if (c6 <= 63) r.delta_lon_microdeg = -10000000 + 156250 * c6;
    else          r.delta_lon_microdeg = -10000000 + 156250 * (c6 + 1);
    return r;
}


// B4 field layout: A4 hazard code → up to 4 D-field specs, ordered MSB→LSB within A18[15:0] per EWSS CAMF v1.2 §3.7.4 (d_idx=0xFF terminates).

namespace {

struct DFieldSpec {
    uint8_t d_idx;   // 0..35 = D1..D36; 0xFF = terminator
    uint8_t shift;   // bit shift within A18[15:0]
    uint8_t bits;    // bit width (1..8)
};

struct HazardB4Layout {
    uint8_t a4_code;
    DFieldSpec fields[4];
};

// Flash に置く（avr-libc のリンカスクリプトは .rodata を .data に含めるため、属性の無い const 配列は SRAM を食う — 実測 45 行 = 585 B）。
// 行はパディング無しの 13 B であることが前提で、下の読み出しがバイト単位でオフセットを組む。
static_assert(sizeof(DFieldSpec) == 3, "DFieldSpec must stay padding-free");
static_assert(sizeof(HazardB4Layout) == 13, "HazardB4Layout must stay padding-free");

// Sorted by a4_code; linear scan over ~45 entries is fast enough.
static const HazardB4Layout B4_LAYOUT_TABLE[] AZARAC_PROGMEM_NEAR = {
    {4  , {{31,13,2}, {32,11,2}, {255,0,0}, {255,0,0}}},
    {5  , {{30,11,4}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {6  , {{33,13,2}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {9  , {{29,11,4}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {10 , {{29,11,4}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {11 , {{29,11,4}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {15 , {{27,12,3}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {16 , {{23,12,3}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {18 , {{23,12,3}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {19 , {{26,11,4}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {21 , {{23,12,3}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {23 , {{24,11,4}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {27 , {{22,12,3}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {30 , {{22,12,3}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {32 , {{19,12,3}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {33 , {{18,12,3}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {36 , {{0,11,4}, {1,8,3}, {2,4,4}, {3,0,4}}},
    {37 , {{20,12,3}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {43 , {{4,12,3}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {44 , {{4,12,3}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {47 , {{7,11,4}, {4,8,3}, {255,0,0}, {255,0,0}}},
    {51 , {{25,10,5}, {34,4,6}, {255,0,0}, {255,0,0}}},
    {53 , {{25,10,5}, {34,4,6}, {255,0,0}, {255,0,0}}},
    {55 , {{28,10,5}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {56 , {{28,10,5}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {57 , {{28,10,5}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {58 , {{28,10,5}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {60 , {{28,10,5}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {63 , {{5,11,4}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {64 , {{7,11,4}, {8,8,3}, {15,5,3}, {10,2,3}}},
    {65 , {{17,13,2}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {68 , {{14,13,2}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {69 , {{16,12,3}, {12,8,4}, {255,0,0}, {255,0,0}}},
    {70 , {{11,11,4}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {71 , {{5,11,4}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {72 , {{15,12,3}, {255,0,0}, {255,0,0}, {255,0,0}}},
    {74 , {{8,12,3}, {12,8,4}, {255,0,0}, {255,0,0}}},
    {75 , {{12,11,4}, {7,7,4}, {255,0,0}, {255,0,0}}},
    {76 , {{13,10,5}, {12,6,4}, {255,0,0}, {255,0,0}}},
    {77 , {{7,11,4}, {8,8,3}, {9,5,3}, {15,2,3}}},
    {79 , {{7,11,4}, {8,8,3}, {10,5,3}, {255,0,0}}},
    {80 , {{6,12,3}, {7,8,4}, {8,5,3}, {255,0,0}}},
    {81 , {{7,11,4}, {5,7,4}, {255,0,0}, {255,0,0}}},
    {82 , {{35,12,3}, {7,8,4}, {8,5,3}, {255,0,0}}},
    {103, {{21,12,3}, {255,0,0}, {255,0,0}, {255,0,0}}},
};

} // anonymous namespace

void decodeB4DetailedInfo(uint16_t a18, uint8_t a4_code, B4DetailedInfo& out) {
    out = B4DetailedInfo{};
    out.present = true;
    out.a4_code = a4_code;

    // 表は Flash にある: 行全体を RAM へ写さず、必要なバイトだけ AZARAC_PGM_READ_BYTE で読む（host では通常のロード）。
    const uint8_t* rows = reinterpret_cast<const uint8_t*>(B4_LAYOUT_TABLE);
    constexpr uint8_t ROW_BYTES = sizeof(HazardB4Layout);
    for (uint8_t i = 0; i < sizeof(B4_LAYOUT_TABLE) / sizeof(B4_LAYOUT_TABLE[0]); ++i) {
        if (AZARAC_PGM_READ_BYTE(rows + i * ROW_BYTES) != a4_code) continue;
        for (uint8_t j = 0; j < 4; ++j) {
            const uint8_t* f = rows + i * ROW_BYTES + 1 + j * sizeof(DFieldSpec);
            const uint8_t d_idx = AZARAC_PGM_READ_BYTE(f);
            if (d_idx == 0xFF) break;
            const uint8_t shift = AZARAC_PGM_READ_BYTE(f + 1);
            const uint8_t bits  = AZARAC_PGM_READ_BYTE(f + 2);
            out.d_values[d_idx] = static_cast<uint8_t>((a18 >> shift) & ((1u << bits) - 1u));
            out.d_present[d_idx] = true;
        }
        return;
    }
}

} // namespace internal
} // namespace azaraC
