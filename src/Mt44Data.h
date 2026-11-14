#pragma once
// MT=44 (DCX/CAMF) のデータ構造。ビット位置は IS-QZSS-DCX-004（azarashi の定義表）由来。

#include "internal/MtCommonTypes.h"  // 共通の整数型（cstdint の AVR 分岐もここ）

namespace azaraC {

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
    uint16_t a12 = 0;    // 16 (unsigned、緯度コード)
    uint32_t a13 = 0;    // 17 (unsigned、経度コード)
    uint8_t  a14 = 0;    // 5
    uint8_t  a15 = 0;    // 5
    uint8_t  a16 = 0;    // 6
    uint8_t  a17 = 0;    // 2
    uint16_t a18 = 0;    // 15

    // B1 (A17=00) - Improved Resolution of Main Ellipse (EWSS CAMF v1.2 §3.7.1)
    bool     b1_present = false;

    // B2 (A17=01) - Position of the Centre of the Hazard (EWSS CAMF v1.2 §3.7.2)
    bool     b2_present = false;
    uint8_t  b2_c5 = 0;
    uint8_t  b2_c6 = 0;

    // B3 (A17=10) - Secondary Ellipse Definition (EWSS CAMF v1.2 §3.7.3)
    bool     b3_present = false;
    uint8_t  b3_c7 = 0;
    uint8_t  b3_c8 = 0;
    uint8_t  b3_c9 = 0;
    uint8_t  b3_c10 = 0;

    // B4 (A17=11) - Quantitative and Detailed Information (EWSS CAMF v1.2 §3.7.4)
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

// 復号済み構造 (IS-QZSS-DCX-004)

// 楕円の汎用部。
// 追加楕円は B1 精密化を持たない（EWSS CAMF v1.2 の B1 は主楕円のみ）ので b1_* は DecodedEllipse 側に分離し、DecodedAdditionalArea は 16 B 小さいコア型を使う。
struct DecodedEllipseCore {
    int32_t lat_microdeg;              // microdegrees (×1,000,000)
    int32_t lon_microdeg;              // microdegrees (×1,000,000)
    int32_t semi_major_m;              // meters (×1,000 from km)
    int32_t semi_minor_m;              // meters (×1,000 from km)
    int32_t azimuth_decideg;           // 1e-5 degrees (×100,000)。フィールド名は歴史的経緯（3.0.0 で改名検討）
};

struct DecodedEllipse : DecodedEllipseCore {
    int32_t b1_lat_offset_microdeg;    // microdegrees (×1,000,000)
    int32_t b1_lon_offset_microdeg;    // microdegrees (×1,000,000)
    int32_t b1_refined_semi_major_m;   // meters (×1,000 from km)
    int32_t b1_refined_semi_minor_m;   // meters (×1,000 from km)
};

struct DecodedAdditionalArea {
    bool present;
    bool head_to_area;
    DecodedEllipseCore ellipse;
};

// Mt44Decoded は生コードから導けない派生値だけを持つ。
// service_kind・is_null_message・b2_hazard_center_present・target_area_code はそれぞれ Mt44Data の同名フィールド / camf.b2_present / ex_lalert_local.ex1 と同値なのでミラーにしない。
struct Mt44Decoded {
    bool main_ellipse_present;
    bool jalert_prefecture_mode;
    DecodedEllipse main_ellipse;
    int32_t b2_hazard_lat_microdeg;    // microdegrees (×1,000,000)
    int32_t b2_hazard_lon_microdeg;    // microdegrees (×1,000,000)
    uint8_t prefecture_positions[47];
    uint8_t prefecture_count;
    uint16_t city_codes[4];
    uint8_t city_code_count;
    DecodedAdditionalArea additional_area;
};

struct Mt44Data {
    Mt44ServiceKind service_kind = {};
    bool            is_null_message = false;
    Mt44Sd          sd = {};
    Mt44CamfRaw     camf = {};
    TimeFields      onset_time = {};
    ExtendedKind        ex_kind = {};
    // 拡張部は ex_kind で排他（decoder は active 枝だけ書き、serializer も ex_kind で分岐して active 枝だけ読む）。
    // 3 構造体を並列に持つと AVR で 36 B 常時消費なので union にする（最大枝 15 B）。
    // NSDMI は先頭の raw_ だけ（C++17 では複数の variant メンバに初期化子を持てない）。
    // 非 active 枝は未規定値だが、ex_kind で排他なので読まれない。
    union Mt44Extended {
        // 最大枝はプラットフォームで変わる（AVR は LAlert、ホストは整列で JAlert）。
        // 先頭に最大サイズのバイト列を置き、{} で union 全体がゼロ初期化されるようにする。
        uint8_t             raw_[sizeof(Mt44ExLAlertOrLocal) > sizeof(Mt44ExJAlert)
                                 ? (sizeof(Mt44ExLAlertOrLocal) > sizeof(Mt44ExOutside) ? sizeof(Mt44ExLAlertOrLocal) : sizeof(Mt44ExOutside))
                                 : (sizeof(Mt44ExJAlert) > sizeof(Mt44ExOutside) ? sizeof(Mt44ExJAlert) : sizeof(Mt44ExOutside))]{};
        Mt44ExLAlertOrLocal ex_lalert_local;
        Mt44ExJAlert        ex_jalert;
        Mt44ExOutside       ex_outside;
    };
    Mt44Extended    ex = {};
    Mt44Decoded     mt44_decoded = {};
};

} // namespace azaraC
