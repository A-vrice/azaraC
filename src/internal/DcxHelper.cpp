// azaraC - src/internal/DcxHelper.cpp
// DCX MT44 decode helpers
// Based on IS-QZSS-DCX-004 / EWSS CAMF v1.2
#include "DcxHelper.h"

namespace azaraC {
namespace internal {

// ---------------------------------------------------------------------------
// Latitude/Longitude decoding
// ---------------------------------------------------------------------------

dcx_real_t decodeLatitude16(uint16_t code) {
    static constexpr dcx_real_t SCALE = 180.0 / 65535.0;
    return static_cast<dcx_real_t>(-90.0) + SCALE * static_cast<dcx_real_t>(code);
}

dcx_real_t decodeLongitude17(uint32_t code) {
    static constexpr dcx_real_t SCALE = 360.0 / 131071.0;
    return static_cast<dcx_real_t>(-180.0) + SCALE * static_cast<dcx_real_t>(code);
}

dcx_real_t decodeLatitude17(uint32_t code) {
    static constexpr dcx_real_t SCALE = 180.0 / 131071.0;
    return static_cast<dcx_real_t>(-90.0) + SCALE * static_cast<dcx_real_t>(code);
}

dcx_real_t decodeLongitude17_45_225(uint32_t code) {
    static constexpr dcx_real_t SCALE = 180.0 / 131071.0;
    return static_cast<dcx_real_t>(45.0) + SCALE * static_cast<dcx_real_t>(code);
}

// ---------------------------------------------------------------------------
// Radius decoding (5-bit code)
// IS-QZSS-DCX-003 Table 4.2-17 / 4.2-18
// Radius[m] = 10^(log10(MinRadius) + a * (log10(MaxRadius) - log10(MinRadius)) / Max_a)
// MinRadius = 216.20, MaxRadius = 2500000, Max_a = 31
// ---------------------------------------------------------------------------

dcx_real_t decodeRadiusCode(uint8_t code) {
    static constexpr double radius_table[32] = {
        0.216,   // 0
        0.292,   // 1
        0.395,   // 2
        0.535,   // 3
        0.723,   // 4
        0.978,   // 5
        1.322,   // 6
        1.788,   // 7
        2.418,   // 8
        3.269,   // 9
        4.421,   // 10
        5.979,   // 11
        8.085,   // 12
        10.933,  // 13
        14.784,  // 14
        19.992,  // 15
        27.035,  // 16
        36.559,  // 17
        49.439,  // 18
        66.855,  // 19
        90.407,  // 20
        122.255, // 21
        165.324, // 22
        223.564, // 23
        302.322, // 24
        408.824, // 25
        552.846, // 26
        747.603, // 27
        1010.970,// 28
        1367.116,// 29
        1848.727,// 30
        2500.000 // 31
    };

    if (code < 32) {
        return radius_table[code];
    }
    return static_cast<dcx_real_t>(0.0);
}

// ---------------------------------------------------------------------------
// Azimuth decoding
// ---------------------------------------------------------------------------

dcx_real_t decodeAzimuth6(uint8_t code) {
    static constexpr dcx_real_t SCALE = 180.0 / 64.0;
    return static_cast<dcx_real_t>(-90.0) + SCALE * static_cast<dcx_real_t>(code);
}

dcx_real_t decodeAzimuth7(uint8_t code) {
    static constexpr dcx_real_t SCALE = 180.0 / 128.0;
    return static_cast<dcx_real_t>(-90.0) + SCALE * static_cast<dcx_real_t>(code);
}

// ---------------------------------------------------------------------------
// J-Alert EX9 decoding
// ---------------------------------------------------------------------------

uint8_t decodePrefectureBitmask(uint64_t ex9, uint8_t* out_positions) {
    uint8_t count = 0;

    // EX9 bit layout for prefecture (EX8=0):
    // EX9 64-bit field: [47-bit prefecture][17-bit reserved]
    // Stream bit 147 → ex9 bit 63 (MSB of 47-bit field)
    // Stream bit 193 → ex9 bit 17 (LSB of 47-bit field)
    // Stream bits 194..210 → ex9 bits 16..0 (reserved)
    //
    // 47-bit prefecture integer: bit 0 (LSB) = Hokkaido (JIS 1), bit 46 (MSB) = Okinawa (JIS 47)
    // In EX9, this maps to ex9[63:17], so we shift right by 17 to align.

    uint64_t pref = ex9 >> 17;  // Extract 47-bit prefecture field

    for (uint8_t i = 0; i < 47; ++i) {
        if (pref & (1ULL << i)) {
            // i=0 (LSB) = Hokkaido = JIS code 1
            // i=46 (MSB) = Okinawa = JIS code 47
            out_positions[count++] = i + 1;
        }
    }

    return count;
}

uint8_t decodeCityCodeList(uint64_t ex9, uint16_t* out_codes) {
    uint8_t count = 0;

    // EX9 bit layout for cities/towns/villages (EX8=1):
    // Four 16-bit city/town/village codes
    // Code 1: bits [0..15]
    // Code 2: bits [16..31]
    // Code 3: bits [32..47]
    // Code 4: bits [48..63]

    for (uint8_t i = 0; i < 4; ++i) {
        uint16_t code = static_cast<uint16_t>((ex9 >> (i * 16)) & 0xFFFF);
        if (code != 0) {
            out_codes[count++] = code;
        }
    }

    return count;
}

// ---------------------------------------------------------------------------
// B1 (A17=00) - Improved Resolution of Main Ellipse (EWSS CAMF v1.1 §3.7.1)
// ---------------------------------------------------------------------------
// A18 bit layout: bit[14]=MSB (first bit of field = spec bit 131), bit[0]=LSB (last bit = spec bit 145)
// getBits() reads MSB-first, so a18 bit 14 = spec bit 131
// C1: spec bits 131-133 → a18[14:12] → shift=12, mask=0x07
// C2: spec bits 134-136 → a18[11:9]  → shift=9,  mask=0x07
// C3: spec bits 137-139 → a18[8:6]   → shift=6,  mask=0x07
// C4: spec bits 140-142 → a18[5:3]   → shift=3,  mask=0x07
// Reserved: spec bits 143-145 → a18[2:0]

B1Refinement decodeB1Refinement(uint16_t a18) {
    B1Refinement b1;
    b1.c1 = (a18 >> 12) & 0x07;  // spec[131:133] → a18[14:12]
    b1.c2 = (a18 >> 9)  & 0x07;  // spec[134:136] → a18[11:9]
    b1.c3 = (a18 >> 6)  & 0x07;  // spec[137:139] → a18[8:6]
    b1.c4 = (a18 >> 3)  & 0x07;  // spec[140:142] → a18[5:3]
    // a18[2:0] reserved (spec bits 143-145)
    return b1;
}

double b1RefinedLatitudeOffset(uint8_t c1) {
    // C1: 緯度補正 = C1 × 180 / (8 × 65535)
    // Grid interval = 180 / 65535 ≈ 0.002747°
    // Step = interval / 8 ≈ 0.000343°
    static constexpr dcx_real_t SCALE = 180.0 / (8.0 * 65535.0);
    return static_cast<double>(c1) * SCALE;
}

double b1RefinedLongitudeOffset(uint8_t c2) {
    // C2: 経度補正 = C2 × 360 / (8 × 131071)
    // Grid interval = 360 / 131071 ≈ 0.002747°
    // Step = interval / 8 ≈ 0.000343°
    static constexpr dcx_real_t SCALE = 360.0 / (8.0 * 131071.0);
    return static_cast<double>(c2) * SCALE;
}

double b1RefinedRadiusKm(uint8_t code, double base_radius_km, uint8_t original_radius_code) {
    // C3/C4: EWSS CAMF v1.1 §3.7.1.3 / §3.7.1.4
    // refined_length = base_radius - delta * (code / 8.0)
    // where delta = decodeRadiusCode(original_radius_code) - decodeRadiusCode(original_radius_code - 1)
    double delta_km;
    if (original_radius_code == 0) {
        delta_km = decodeRadiusCode(0);
    } else {
        delta_km = decodeRadiusCode(original_radius_code) - decodeRadiusCode(original_radius_code - 1);
    }
    return base_radius_km - delta_km * (static_cast<double>(code) / 8.0);
}

// ---------------------------------------------------------------------------
// B2 (A17=01) - Position of the Centre of the Hazard (EWSS CAMF v1.1 §3.7.2)
// ---------------------------------------------------------------------------

B2HazardCenter decodeB2HazardCenter(uint8_t c5, uint8_t c6) {
    B2HazardCenter r{};
    r.present = true;
    r.c5 = c5;
    r.c6 = c6;
    // delta = -10 + (20/128) * code  (if code <= 63)
    // delta = -10 + (20/128) * (code+1)  (if code >= 64)
    // Step = 20/128 = 0.15625 degrees
    double step = 20.0 / 128.0;
    if (c5 <= 63) r.delta_lat_deg = -10.0 + step * c5;
    else          r.delta_lat_deg = -10.0 + step * (c5 + 1);
    if (c6 <= 63) r.delta_lon_deg = -10.0 + step * c6;
    else          r.delta_lon_deg = -10.0 + step * (c6 + 1);
    return r;
}


// ---------------------------------------------------------------------------
// B4 field layout table
// Each A4 hazard code maps to up to 4 D-field specs (d_idx=0xFF terminates).
// Fields are ordered MSB→LSB within A18[15:0] per EWSS CAMF v1.2 §3.7.4.
// ---------------------------------------------------------------------------

namespace {

struct DFieldSpec {
    uint8_t d_idx;   // 0..35 = D1..D36; 0xFF = terminator
    uint8_t shift;   // bit shift within A18[15:0]
    uint8_t bits;    // bit width (1..8)
};

struct HazardB4Layout {
    uint8_t a4_code;
    DFieldSpec fields[4];  // d_idx=0xFF terminates
};

// Sorted by a4_code; linear scan is fast enough for ~45 entries.
static const HazardB4Layout B4_LAYOUTS[] = {
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

    for (uint8_t i = 0; i < sizeof(B4_LAYOUTS) / sizeof(B4_LAYOUTS[0]); ++i) {
        if (B4_LAYOUTS[i].a4_code == a4_code) {
            for (uint8_t j = 0; j < 4; ++j) {
                const DFieldSpec& f = B4_LAYOUTS[i].fields[j];
                if (f.d_idx == 0xFF) break;
                out.d_values[f.d_idx] = static_cast<uint8_t>((a18 >> f.shift) & ((1u << f.bits) - 1));
                out.d_present[f.d_idx] = true;
            }
            return;
        }
    }
}

} // namespace internal
} // namespace azaraC
