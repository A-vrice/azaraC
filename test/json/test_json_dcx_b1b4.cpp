// test/json/test_json_dcx_b1b4.cpp — DCX B1-B4 JSON出力テスト

#define ARDUINO 0
#include "../src/azaraC.h"
#include "../src/internal/PrintShim.h"
#include "../test_helpers.h"
#include "doctest.h"
#include <cstring>
#include <string>

using namespace azaraC;

#if (AZARAC_ENABLE_DCX_CAMF)

static bool has(const std::string& s, const char* sub) {
    return s.find(sub) != std::string::npos;
}

static bool has(const std::string& s, const std::string& sub) {
    return s.find(sub) != std::string::npos;
}

// ラベルはビルド時に選んだ言語で出力される（test_json.cpp と同じ規則）。
#if AZARAC_LANG_JA
#  define LBL(ja, en) ja
#elif AZARAC_LANG_EN
#  define LBL(ja, en) en
#else
#  define LBL(ja, en) ""
#endif

// "key":value の直後が JSON の区切りであることを確認（部分一致の誤検出を防ぐ）
static bool hasField(const std::string& s, const std::string& key_val) {
    auto pos = s.find(key_val);
    if (pos == std::string::npos) return false;
    size_t end = pos + key_val.size();
    return end >= s.size() || s[end] == ',' || s[end] == '}' || s[end] == ']' || s[end] == '\n' || s[end] == ' ';
}

static void initMt44(Message& m) {
    m.msg_type = 44;
    m.payload_type = MsgPayloadType::Mt44;
    m.initPayload<Mt44Data>();
}

TEST_CASE("JSON DCX B1: refinement fields") {
    Message m{};
    m.svid = 193;
    m.crc24 = 0xABCDEF;
    initMt44(m);
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);
    
    mt44->service_kind = Mt44ServiceKind::LAlert;
    mt44->is_null_message = false;
    mt44->ex_kind = ExtendedKind::LAlertOrLocal;
    mt44->camf.a1 = 1;
    mt44->camf.a2 = 111;
    mt44->camf.a3 = 1;
    mt44->camf.b1_present = true;
    mt44->mt44_decoded.main_ellipse_present = true;
    mt44->mt44_decoded.main_ellipse.lat_microdeg = 35600000;      // 35.6° in microdegrees
    mt44->mt44_decoded.main_ellipse.lon_microdeg = 139600000;     // 139.6° in microdegrees
    mt44->mt44_decoded.main_ellipse.b1_lat_offset_microdeg = 2400; // 0.0024° in microdegrees
    mt44->mt44_decoded.main_ellipse.b1_lon_offset_microdeg = 2400; // 0.0024° in microdegrees
    mt44->mt44_decoded.main_ellipse.b1_refined_semi_major_m = 215125;  // 215.125 km in meters
    mt44->mt44_decoded.main_ellipse.b1_refined_semi_minor_m = 215125;  // 215.125 km in meters

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(has(s, "\"b1_refinement\":{"));
    CHECK(hasField(s, "\"c1_lat_offset_deg\":0.002400"));
    CHECK(hasField(s, "\"c2_lon_offset_deg\":0.002400"));
    CHECK(hasField(s, "\"c3_refined_semi_major_km\":215.125"));
    CHECK(hasField(s, "\"c4_refined_semi_minor_km\":215.125"));
}

TEST_CASE("JSON DCX B2: hazard center fields") {
    Message m{};
    m.svid = 193;
    m.crc24 = 0xABCDEF;
    initMt44(m);
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);
    
    mt44->service_kind = Mt44ServiceKind::LAlert;
    mt44->is_null_message = false;
    mt44->ex_kind = ExtendedKind::LAlertOrLocal;
    mt44->camf.a1 = 1;
    mt44->camf.a2 = 111;
    mt44->camf.a3 = 1;
    mt44->camf.b2_present = true;
    mt44->camf.b2_c5 = 63;
    mt44->camf.b2_c6 = 63;
    mt44->mt44_decoded.main_ellipse_present = true;
    mt44->mt44_decoded.main_ellipse.lat_microdeg = 35600000; // 35.6° in microdegrees
    mt44->mt44_decoded.main_ellipse.lon_microdeg = 139600000; // 139.6° in microdegrees
    mt44->mt44_decoded.b2_hazard_center_present = true;
    mt44->mt44_decoded.b2_hazard_lat_microdeg = 35600000;
    mt44->mt44_decoded.b2_hazard_lon_microdeg = 139600000;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(has(s, "\"hazard_center\":{"));
    CHECK(has(s, "\"c5_raw\":63"));
    CHECK(has(s, "\"c6_raw\":63"));
}

TEST_CASE("JSON DCX B3: secondary ellipse fields") {
    Message m{};
    m.svid = 193;
    m.crc24 = 0xABCDEF;
    initMt44(m);
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);
    
    mt44->service_kind = Mt44ServiceKind::LAlert;
    mt44->is_null_message = false;
    mt44->ex_kind = ExtendedKind::LAlertOrLocal;
    mt44->camf.a1 = 1;
    mt44->camf.a2 = 111;
    mt44->camf.a3 = 1;
    mt44->camf.b3_present = true;
    mt44->camf.b3_c7 = 3;
    mt44->camf.b3_c8 = 7;
    mt44->camf.b3_c9 = 31;
    mt44->camf.b3_c10 = 0;
    mt44->mt44_decoded.main_ellipse_present = true;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(has(s, "\"secondary_ellipse\":{"));
    CHECK(has(s, "\"c7_shift\":3"));
    CHECK(has(s, "\"c8_homothetic\":7"));
    CHECK(has(s, "\"c9_bearing\":31"));
    CHECK(has(s, "\"c10_guidance\":0"));
}

TEST_CASE("JSON DCX B4: detailed info fields") {
    Message m{};
    m.svid = 193;
    m.crc24 = 0xABCDEF;
    initMt44(m);
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);
    
    mt44->service_kind = Mt44ServiceKind::LAlert;
    mt44->is_null_message = false;
    mt44->ex_kind = ExtendedKind::LAlertOrLocal;
    mt44->camf.a1 = 1;
    mt44->camf.a2 = 111;
    mt44->camf.a3 = 1;
    mt44->camf.a4 = 36;  // Earthquake
    mt44->camf.a17 = 3;  // B4
    mt44->camf.a18 = 0x7F59;  // D1=15 (bits 14:11), D2=7 (bits 10:8), D3=5 (bits 7:4), D4=9 (bits 3:0)
    mt44->camf.b4_present = true;
    mt44->mt44_decoded.main_ellipse_present = true;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(has(s, "\"detailed_info\":{"));
    CHECK(has(s, "\"a4_hazard\":36"));
    CHECK_FALSE(has(s, "a4_code"));
    CHECK(has(s, "\"d1_magnitude\":15"));
    CHECK(has(s, "\"d2_seismic_coeff\":7"));
    CHECK(has(s, "\"d3_azimuth\":5,\"d3_azimuth_label\":\"112.5°\""));
    CHECK(has(s, "\"d4_vector_length\":9,\"d4_vector_length_label\":\"30\""));
}

// Build a B4 message with the given hazard code and A18 bit-field, return its JSON.
static std::string b4Json(uint8_t a4, uint16_t a18) {
    Message m{};
    m.svid = 193;
    m.crc24 = 0xABCDEF;
    initMt44(m);
    Mt44Data* mt44 = m.getMt44();
    mt44->service_kind = Mt44ServiceKind::LAlert;
    mt44->ex_kind = ExtendedKind::LAlertOrLocal;
    mt44->camf.a1 = 1;
    mt44->camf.a2 = 111;
    mt44->camf.a3 = 1;
    mt44->camf.a4 = a4;
    mt44->camf.a17 = 3;
    mt44->camf.a18 = a18;
    mt44->camf.b4_present = true;
    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    return sp.str();
}

TEST_CASE("JSON DCX B4: multi-field layouts emit the correct raw values") {
    // Each A18 is assembled from the layout's (shift, width) so a wrong mapping
    // (shift/width/field) changes the emitted raw value.
    // a4=64: D8(11,4) D9(8,3) D16(5,3) D11(2,3)
    {
        const std::string s = b4Json(64, (15u << 11) | (7u << 8) | (5u << 5) | (3u << 2));
        CHECK(has(s, "\"d8_wind_speed\":15"));
        CHECK(has(s, "\"d9_rainfall\":7"));
        CHECK(has(s, "\"d16_lightning\":5"));
        CHECK(has(s, "\"d11_tornado_prob\":3"));
        // Fields outside this layout must not be emitted (no cross-layout bleed).
        CHECK_FALSE(has(s, "\"d1_magnitude\""));
        CHECK_FALSE(has(s, "\"d26_cases_per_100k\""));
    }
    // a4=77: D8(11,4) D9(8,3) D10(5,3) D16(2,3)
    {
        const std::string s = b4Json(77, (9u << 11) | (4u << 8) | (2u << 5) | (1u << 2));
        CHECK(has(s, "\"d8_wind_speed\":9"));
        CHECK(has(s, "\"d9_rainfall\":4"));
        CHECK(has(s, "\"d10_damage\":2"));
        CHECK(has(s, "\"d16_lightning\":1"));
    }
    // a4=80: D7(12,3) D8(8,4) D9(5,3)
    {
        const std::string s = b4Json(80, (7u << 12) | (15u << 8) | (6u << 5));
        CHECK(has(s, "\"d7_hurricane_cat\":7"));
        CHECK(has(s, "\"d8_wind_speed\":15"));
        CHECK(has(s, "\"d9_rainfall\":6"));
    }
    // a4=82: D36(12,3) D8(8,4) D9(5,3) — verifies D36 value, not just its presence.
    {
        const std::string s = b4Json(82, (5u << 12) | (10u << 8) | (3u << 5));
        CHECK(has(s, "\"d36_typhoon_cat\":5"));
        CHECK(has(s, "\"d8_wind_speed\":10"));
        CHECK(has(s, "\"d9_rainfall\":3"));
    }
    // a4=51: D26(10,5) D35(4,6) — 6-bit width field
    {
        const std::string s = b4Json(51, (20u << 10) | (33u << 4));
        CHECK(has(s, "\"d26_cases_per_100k\":20"));
        CHECK(has(s, "\"d35_infection_type\":33"));
    }
    // a4=47: D8(11,4) D5(8,3)
    {
        const std::string s = b4Json(47, (12u << 11) | (6u << 8));
        CHECK(has(s, "\"d8_wind_speed\":12"));
        CHECK(has(s, "\"d5_wave_height\":6"));
    }
}

TEST_CASE("JSON DCX B4: unknown a4 has no D-field layout") {
    const std::string s = b4Json(1, 0x7FFF);  // a4=1 has no D-field layout
    CHECK(has(s, "\"a4_hazard\":1"));
    CHECK(has(s, "\"detailed_info\":{}"));
    CHECK_FALSE(has(s, "a4_code"));
    CHECK_FALSE(has(s, "\"d1_magnitude\""));
    CHECK_FALSE(has(s, "\"d8_wind_speed\""));
}

TEST_CASE("JSON DCX main ellipse fields") {
    Message m{};
    m.svid = 193;
    m.crc24 = 0xABCDEF;
    initMt44(m);
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);
    
    mt44->service_kind = Mt44ServiceKind::LAlert;
    mt44->is_null_message = false;
    mt44->ex_kind = ExtendedKind::LAlertOrLocal;
    mt44->camf.a1 = 1;
    mt44->camf.a2 = 111;
    mt44->camf.a3 = 1;
    mt44->mt44_decoded.main_ellipse_present = true;
    mt44->mt44_decoded.main_ellipse.lat_microdeg = 35600000;   // 35.6°
    mt44->mt44_decoded.main_ellipse.lon_microdeg = 139600000;  // 139.6°
    mt44->mt44_decoded.main_ellipse.semi_major_m = 100000;  // 100 km
    mt44->mt44_decoded.main_ellipse.semi_minor_m = 50000;   // 50 km
    mt44->mt44_decoded.main_ellipse.azimuth_decideg = 4500000;    // 45°

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();
    CHECK(has(s, "\"main_ellipse\":{"));
    CHECK(has(s, "\"lat_deg\":35.600"));
    CHECK(has(s, "\"lon_deg\":139.600"));
    CHECK(has(s, "\"semi_major_km\":100.000"));
    CHECK(has(s, "\"semi_minor_km\":50.000"));
    CHECK(has(s, "\"azimuth_deg\":45.000"));
}

TEST_CASE("JSON DCX additional area fields") {
    Message m{};
    m.svid = 193;
    m.crc24 = 0xABCDEF;
    initMt44(m);
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);
    
    mt44->service_kind = Mt44ServiceKind::LocalGovernment;
    mt44->is_null_message = false;
    mt44->ex_kind = ExtendedKind::LAlertOrLocal;
    mt44->camf.a1 = 1;
    mt44->camf.a2 = 111;
    mt44->camf.a3 = 4;
    mt44->mt44_decoded.additional_area.present = true;
    mt44->mt44_decoded.additional_area.head_to_area = true;
    mt44->mt44_decoded.additional_area.ellipse.lat_microdeg = 35000000;  // 35.0° in microdegrees
    mt44->mt44_decoded.additional_area.ellipse.lon_microdeg = 140000000; // 140.0° in microdegrees

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(has(s, "\"additional_area\":{"));
    CHECK(has(s, "\"head_to_area\":1"));
}

TEST_CASE("JSON DCX EX1 city codes with labels") {
    Message m{};
    m.svid = 193;
    m.crc24 = 0xABCDEF;
    initMt44(m);
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);
    
    mt44->service_kind = Mt44ServiceKind::JAlert;
    mt44->is_null_message = false;
    mt44->ex_kind = ExtendedKind::JAlert;
    mt44->camf.a1 = 1;
    mt44->camf.a2 = 111;
    mt44->camf.a3 = 1;
    mt44->camf.a4 = 10;
    mt44->camf.a5 = 3;
    mt44->camf.a8 = 4;
    mt44->camf.a11 = 1;
    // City codes mode (EX8=1)
    mt44->ex_jalert.ex8 = 1;
    mt44->ex_jalert.vn = 1;
    // Set a valid known city code (1101 = "Chuo-ku, Sapporo-shi")
    mt44->mt44_decoded.jalert_prefecture_mode = false;
    mt44->mt44_decoded.city_code_count = 1;
    mt44->mt44_decoded.city_codes[0] = 1101;
    mt44->sd.sdmt = 0;
    mt44->sd.sdm = 0x1FF;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    // Check city objects output (label is resolved, not null)
    CHECK(has(s, "\"cities\":[{\"code\":1101,\"label\":\""));
    // At minimum we should NOT see null labels for known codes
    CHECK(s.find("\"cities\":[{\"code\":1101,\"label\":null}]") == std::string::npos);
    CHECK(s.find("city_codes") == std::string::npos);
    CHECK(s.find("city_labels") == std::string::npos);
    // Regression: ex_vn must be preceded by a comma (was "]\"ex_vn\"" — invalid JSON)
    CHECK(s.find("],\"ex_vn\"") != std::string::npos);
    CHECK(s.find("]\"ex_vn\"") == std::string::npos);
}

TEST_CASE("JSON DCX EX1 city codes multiple entries") {
    Message m{};
    m.svid = 193;
    m.crc24 = 0xABCDEF;
    initMt44(m);
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);
    
    mt44->service_kind = Mt44ServiceKind::JAlert;
    mt44->is_null_message = false;
    mt44->ex_kind = ExtendedKind::JAlert;
    mt44->camf.a1 = 1;
    mt44->camf.a2 = 111;
    mt44->camf.a3 = 1;
    mt44->camf.a4 = 10;
    mt44->camf.a5 = 3;
    mt44->camf.a8 = 4;
    mt44->camf.a11 = 1;
    mt44->ex_jalert.ex8 = 1;
    mt44->ex_jalert.vn = 1;
    mt44->mt44_decoded.jalert_prefecture_mode = false;
    mt44->mt44_decoded.city_code_count = 3;
    mt44->mt44_decoded.city_codes[0] = 1101;  // Chuo-ku, Sapporo
    mt44->mt44_decoded.city_codes[1] = 1102;  // Kita-ku, Sapporo
    mt44->mt44_decoded.city_codes[2] = 47201; // Naha-shi, Okinawa
    mt44->sd.sdmt = 0;
    mt44->sd.sdm = 0x1FF;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    // All three codes appear in the cities array
    CHECK(has(s, "\"cities\":[{\"code\":1101,"));
    CHECK(hasField(s, "\"code\":1102"));
    CHECK(hasField(s, "\"code\":47201"));
    // Check no null labels at any position within the cities array
    {
        const auto p = s.find("\"cities\":[");
        const auto q = s.find(']', p + 10);
        const auto arr = s.substr(p, q - p + 1);
        CHECK(arr.find("null") == std::string::npos);
    }
}
#endif
