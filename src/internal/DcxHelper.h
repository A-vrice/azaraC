#pragma once
// DCX MT44 decode helpers
// Based on IS-QZSS-DCX-004 / EWSS CAMF v1.2

#include "MtCommonTypes.h"

namespace azaraC {
namespace internal {

// A12: Latitude = -90 + (180/(2^16-1)) * code, microdegrees
int32_t decodeLatitude16(uint16_t code);

// A13: Longitude = -180 + (360/(2^17-1)) * code, microdegrees
int32_t decodeLongitude17(uint32_t code);

// EX3: same formula as A12 but 17-bit, microdegrees
int32_t decodeLatitude17(uint32_t code);

// EX4: Longitude = 45 + (180/(2^17-1)) * code, microdegrees
int32_t decodeLongitude17_45_225(uint32_t code);

// A14/A15/EX5/EX6: log table IS-QZSS-DCX-003 Table 4.2-17, meters (×1,000 from km)
int32_t decodeRadiusCode(uint8_t code);

// A16: Azimuth = -90 + (180/2^6) * code, dexadegrees (×100,000)
int32_t decodeAzimuth6(uint8_t code);

// EX7: Azimuth = -90 + (180/2^7) * code, dexadegrees (×100,000)
int32_t decodeAzimuth7(uint8_t code);

// J-Alert EX9 decoding

// EX8=0: EX9 = [47-bit prefecture][17-bit reserved]; prefecture = ex9[63:17].
// Bit 0 (LSB) = Hokkaido (JIS 1) … bit 46 (MSB) = Okinawa (JIS 47).
// Fills out_positions (≥47 bytes); returns count written.
uint8_t decodePrefectureBitmask(uint64_t ex9, uint8_t* out_positions);

// EX8=1: four 16-bit codes; fills out_codes (≥4 elements); returns count written.
uint8_t decodeCityCodeList(uint64_t ex9, uint16_t* out_codes);

// B1 (A17=00) - Improved Resolution of Main Ellipse (EWSS CAMF v1.1 §3.7.1)

// Decode B1 refinement from A18 (15-bit field)
// C1 = a18[14:12] (3b), C2 = a18[11:9] (3b), C3 = a18[8:6] (3b),
// C4 = a18[5:3] (3b), Reserved = a18[2:0] (3b)
struct B1Refinement {
    uint8_t c1; // latitude refinement (0-7)
    uint8_t c2; // longitude refinement (0-7)
    uint8_t c3; // semi-major axis refinement (0-7), §3.7.1.3
    uint8_t c4; // semi-minor axis refinement (0-7), §3.7.1.4
};

B1Refinement decodeB1Refinement(uint16_t a18);

// delta = C1 × 180/(8×65535), microdegrees
int32_t b1RefinedLatitudeOffset(uint8_t c1);

// delta = C2 × 360/(8×131071), microdegrees
int32_t b1RefinedLongitudeOffset(uint8_t c2);

// refined = base_radius_m - (delta_m*code + 4)/8 （四捨五入）
// delta_m = radius(code) - radius(code-1); original_radius_code: A14 (semi-major) / A15 (semi-minor)
int32_t b1RefinedRadiusM(uint8_t code, int32_t base_radius_m, uint8_t original_radius_code);

// B2 (A17=01) - Position of the Centre of the Hazard (EWSS CAMF v1.1 §3.7.2)

struct B2HazardCenter {
    uint8_t c5;              // 7 bits - delta latitude raw
    uint8_t c6;              // 7 bits - delta longitude raw
    int32_t delta_lat_microdeg;   // Delta latitude in microdegrees (×1,000,000, range -10..+10)
    int32_t delta_lon_microdeg;   // Delta longitude in microdegrees
};

B2HazardCenter decodeB2HazardCenter(uint8_t c5, uint8_t c6);


// B4 (A17=11) - Quantitative and Detailed Information (EWSS CAMF v1.1 §3.7.4)

struct B4DetailedInfo {
    bool     present = false;
    uint8_t  a4_code = 0;           // Hazard category/type (raw)
    static constexpr uint8_t D_COUNT = 36;
    // Presence flags and values for D1..D36 (0-indexed arrays)
    bool     d_present[D_COUNT] = {};
    uint8_t  d_values[D_COUNT] = {};
};

void decodeB4DetailedInfo(uint16_t a18, uint8_t a4_code, B4DetailedInfo& out);

} // namespace internal
} // namespace azaraC
