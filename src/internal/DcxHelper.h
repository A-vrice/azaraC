#pragma once
// DCX MT44 の復号ヘルパ（IS-QZSS-DCX-004 / EWSS CAMF v1.2）

#include "MtCommonTypes.h"

namespace azaraC {
namespace internal {

// A2 フィールドの日本国コード（9 bit: 001101111 = 111）
static constexpr uint16_t DCX_COUNTRY_CODE_JAPAN = 111;

// A12: 緯度 = -90 + (180/(2^16-1)) * code、単位はマイクロ度
int32_t decodeLatitude16(uint16_t code);

// A13: 経度 = -180 + (360/(2^17-1)) * code、単位はマイクロ度
int32_t decodeLongitude17(uint32_t code);

// EX3: A12 と同じ式で 17 bit、単位はマイクロ度
int32_t decodeLatitude17(uint32_t code);

// EX4: 経度 = 45 + (180/(2^17-1)) * code、単位はマイクロ度
int32_t decodeLongitude17_45_225(uint32_t code);

// A14/A15/EX5/EX6: 対数表（IS-QZSS-DCX-003 Table 4.2-17）、単位はメートル（km×1,000）
int32_t decodeRadiusCode(uint8_t code);

// A16: 方位角 = -90 + (180/2^6) * code、単位は 100,000 分度
int32_t decodeAzimuth6(uint8_t code);

// EX7: 方位角 = -90 + (180/2^7) * code、単位は 100,000 分度
int32_t decodeAzimuth7(uint8_t code);

// J-Alert EX9 の復号

// EX8=0: EX9 = [47 bit 都道府県][17 bit Reserved]、都道府県 = ex9[63:17]。
// bit 0 (LSB) = 北海道 (JIS 1) … bit 46 (MSB) = 沖縄 (JIS 47)。
// out_positions（47 バイト以上）を埋め、書いた件数を返す。
uint8_t decodePrefectureBitmask(uint64_t ex9, uint8_t* out_positions);

// EX8=1: 16 bit コードを 4 個。out_codes（4 要素以上）を埋めて書いた件数を返す。
uint8_t decodeCityCodeList(uint64_t ex9, uint16_t* out_codes);

// B1 (A17=00) - Improved Resolution of Main Ellipse (EWSS CAMF v1.2 §3.7.1)

// A18（15 bit フィールド）から B1 の精細化値を復号する。
// C1..C4 = a18[14:12]/[11:9]/[8:6]/[5:3]（各 3b）、a18[2:0] は Reserved（3b）。
struct B1Refinement {
    uint8_t c1; // 緯度の精細化 (0-7)
    uint8_t c2; // 経度の精細化 (0-7)
    uint8_t c3; // 長半径の精細化 (0-7)、§3.7.1.3
    uint8_t c4; // 短半径の精細化 (0-7)、§3.7.1.4
};

B1Refinement decodeB1Refinement(uint16_t a18);

// delta = C1 × 180/(8×65535)、単位はマイクロ度
int32_t b1RefinedLatitudeOffset(uint8_t c1);

// delta = C2 × 360/(8×131071)、単位はマイクロ度
int32_t b1RefinedLongitudeOffset(uint8_t c2);

// refined = base_radius_m - (delta_m*code + 4)/8 （四捨五入） delta_m = radius(code) - radius(code-1)。original_radius_code は A14（長半径）/ A15（短半径）
int32_t b1RefinedRadiusM(uint8_t code, int32_t base_radius_m, uint8_t original_radius_code);

// B2 (A17=01) - Position of the Centre of the Hazard (EWSS CAMF v1.2 §3.7.2)

struct B2HazardCenter {
    uint8_t c5;              // 7 bit — 緯度オフセットの生コード
    uint8_t c6;              // 7 bit — 経度オフセットの生コード
    int32_t delta_lat_microdeg;   // マイクロ度（×1,000,000、範囲 -10..+10）
    int32_t delta_lon_microdeg;   // マイクロ度
};

B2HazardCenter decodeB2HazardCenter(uint8_t c5, uint8_t c6);

// B4 (A17=11) - Quantitative and Detailed Information (EWSS CAMF v1.2 §3.7.4)

struct B4DetailedInfo {
    bool     present = false;
    uint8_t  a4_code = 0;           // ハザードのcategory/type（生コード）
    static constexpr uint8_t D_COUNT = 36;
    // D1..D36 の存在フラグと値（0 始まりの配列）
    bool     d_present[D_COUNT] = {};
    uint8_t  d_values[D_COUNT] = {};
};

void decodeB4DetailedInfo(uint16_t a18, uint8_t a4_code, B4DetailedInfo& out);

} // namespace internal
} // namespace azaraC
