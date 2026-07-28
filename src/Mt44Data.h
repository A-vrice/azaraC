#pragma once
// azaraC - src/Mt44Data.h
// MT=44 (DCX/CAMF) data structures
// Bit offsets derived from azarashi (IS-QZSS-DCX-004)

#include <cstdint>

#include "internal/MtCommonTypes.h"

namespace azaraC {

// ---- MT=44 DCX type ----------------------------------------------------

enum class Mt44ServiceKind : uint8_t {
    NullMessage,
    LAlert,
    JAlert,
    LocalGovernment,
    OutsideJapan,
    Unknown
};

enum class ExtendedKind : uint8_t {
    None,
    LAlertOrLocal,
    JAlert,
    OutsideJapan
};

struct Mt44Sd {
    uint8_t  sdmt;   // 1 bit
    uint16_t sdm;    // 9 bits
};

struct Mt44CamfRaw {
    uint8_t  a1  = 0;    // 2
    uint16_t a2  = 0;    // 9
    uint8_t  a3  = 0;    // 5
    uint8_t  a4  = 0;    // 7
    uint8_t  a5  = 0;    // 2
    uint8_t  a6  = 0;    // 1
    uint16_t a7  = 0;    // 14
    uint8_t  a8  = 0;    // 2
    uint8_t  a9  = 0;    // 1
    uint8_t  a10 = 0;    // 3
    uint16_t a11 = 0;    // 10
    uint16_t a12 = 0;    // 16 (unsigned, latitude code)
    uint32_t a13 = 0;    // 17 (unsigned, longitude code)
    uint8_t  a14 = 0;    // 5
    uint8_t  a15 = 0;    // 5
    uint8_t  a16 = 0;    // 6
    uint8_t  a17 = 0;    // 2
    uint16_t a18 = 0;    // 15

    // B1 (A17=00) - Improved Resolution of Main Ellipse (EWSS CAMF v1.1 §3.7.1)
    bool     b1_present = false;
    uint8_t  b1_c1 = 0;
    uint8_t  b1_c2 = 0;
    uint8_t  b1_c3 = 0;
    uint8_t  b1_c4 = 0;

    // B2 (A17=01) - Position of the Centre of the Hazard (EWSS CAMF v1.1 §3.7.2)
    bool     b2_present = false;
    uint8_t  b2_c5 = 0;
    uint8_t  b2_c6 = 0;

    // B3 (A17=10) - Secondary Ellipse Definition (EWSS CAMF v1.1 §3.7.3)
    bool     b3_present = false;
    uint8_t  b3_c7 = 0;
    uint8_t  b3_c8 = 0;
    uint8_t  b3_c9 = 0;
    uint8_t  b3_c10 = 0;

    // B4 (A17=11) - Quantitative and Detailed Information (EWSS CAMF v1.1 §3.7.4)
    // D1..D36 represented as arrays for compact storage and loop-based JSON serialization.
    static constexpr uint8_t B4_D_COUNT = 36;
    bool     b4_present = false;
};

struct Mt44ExLAlertOrLocal {
    uint16_t ex1;
    uint8_t  ex2;
    uint32_t ex3;
    uint32_t ex4;
    uint8_t  ex5;
    uint8_t  ex6;
    uint8_t  ex7;
    uint8_t  vn;
};

struct Mt44ExJAlert {
    uint8_t  ex8;
    uint64_t ex9;
    uint8_t  ex10;
    uint8_t  vn;
};

struct Mt44ExOutside {
    uint8_t ex11_raw[9];
    uint8_t vn;
};

// ---- MT=44 Decoded structures (IS-QZSS-DCX-004) --------------------------

struct DecodedEllipse {
#ifdef AZARAC_DCX_USE_FLOAT
    float lat_deg;
    float lon_deg;
    float semi_major_km;
    float semi_minor_km;
    float azimuth_deg;
    float b1_lat_offset_deg;
    float b1_lon_offset_deg;
    float b1_refined_semi_major_km;
    float b1_refined_semi_minor_km;
#else
    double lat_deg;
    double lon_deg;
    double semi_major_km;
    double semi_minor_km;
    double azimuth_deg;
    double b1_lat_offset_deg;
    double b1_lon_offset_deg;
    double b1_refined_semi_major_km;
    double b1_refined_semi_minor_km;
#endif
};

struct DecodedAdditionalArea {
    bool present;
    bool head_to_area;
    DecodedEllipse ellipse;
};

struct Mt44AlertIdentity {
    uint16_t a2;
    uint8_t  a3;
    uint8_t  a4;
    uint16_t ex1;

    bool operator==(const Mt44AlertIdentity& o) const {
        return a2 == o.a2 && a3 == o.a3 && a4 == o.a4 && ex1 == o.ex1;
    }
};

struct Mt44Decoded {
    Mt44ServiceKind service_kind;
    bool is_null_message;
    bool main_ellipse_present;
    DecodedEllipse main_ellipse;
    bool b2_hazard_center_present = false;
    double b2_hazard_lat_deg = 0.0;
    double b2_hazard_lon_deg = 0.0;
    bool target_area_code_present;
    uint16_t target_area_code;
    bool jalert_prefecture_mode;
    uint8_t prefecture_positions[47];
    uint8_t prefecture_count;
    uint16_t city_codes[4];
    uint8_t city_code_count;
    DecodedAdditionalArea additional_area;
    Mt44AlertIdentity alert_identity;
};

// ---- MT=44 Data (DCX / CAMF) -------------------------------------------

struct Mt44Data {
    Mt44ServiceKind service_kind = {};
    bool            is_null_message = false;
    Mt44Sd          sd = {};
    Mt44CamfRaw     camf = {};
    TimeFields      onset_time = {};
    ExtendedKind        ex_kind = {};
    Mt44ExLAlertOrLocal ex_lalert_local = {};
    Mt44ExJAlert        ex_jalert = {};
    Mt44ExOutside       ex_outside = {};
    Mt44Decoded      mt44_decoded = {};
};

} // namespace azaraC
