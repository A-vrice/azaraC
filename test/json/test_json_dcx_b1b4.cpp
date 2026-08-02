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

// Helper to create Mt44Data with safe initialization
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
    mt44->mt44_decoded.main_ellipse.lat_microdeg = 35.6;
    mt44->mt44_decoded.main_ellipse.lon_microdeg = 139.6;
    mt44->mt44_decoded.main_ellipse.b1_lat_offset_microdeg = 0.0024;
    mt44->mt44_decoded.main_ellipse.b1_lon_offset_microdeg = 0.0024;
    mt44->mt44_decoded.main_ellipse.b1_refined_semi_major_m = 215.125;
    mt44->mt44_decoded.main_ellipse.b1_refined_semi_minor_m = 215.125;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(has(s, "\"b1_refinement\":{"));
    CHECK(has(s, "\"c1_lat_offset_deg\":"));
    CHECK(has(s, "\"c2_lon_offset_deg\":"));
    CHECK(has(s, "\"c3_refined_semi_major_km\":"));
    CHECK(has(s, "\"c4_refined_semi_minor_km\":"));
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
    CHECK(has(s, "\"a4_code\":36"));
    CHECK(has(s, "\"d1_magnitude\":{\"raw\":15"));
    CHECK(has(s, "\"d2_seismic_coeff\":{\"raw\":7"));
    CHECK(has(s, "\"d3_azimuth\":{\"raw\":5,\"label\":\"112.5\"}"));
    CHECK(has(s, "\"d4_vector_length\":{\"raw\":9,\"label\":\"30\"}"));
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
    mt44->mt44_decoded.additional_area.ellipse.lat_microdeg = 35.0;
    mt44->mt44_decoded.additional_area.ellipse.lon_microdeg = 140.0;

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

    // Check city codes output
    CHECK(has(s, "\"city_codes\":[1101]"));
    // Check that city label is resolved (JA/EN depending on build)
    CHECK(has(s, "\"city_labels\":[\""));
    // The label should contain "Sapporo" (EN) or "札幌" (JA)
    // At minimum we should NOT see null labels for known codes
    CHECK(s.find("\"city_labels\":[null]") == std::string::npos);
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
    mt44->mt44_decoded.city_codes[2] = 47101; // Naha-shi, Okinawa
    mt44->sd.sdmt = 0;
    mt44->sd.sdm = 0x1FF;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    // All three codes appear in city_codes array
    CHECK(has(s, "\"city_codes\":[1101,1102,47101]"));
    // city_labels has three entries, all non-null
    CHECK(has(s, "\"city_labels\":[\""));
    // Check no null values at any position within the array
    {
        const auto p = s.find("\"city_labels\":[");
        const auto q = s.find(']', p + 14);
        const auto arr = s.substr(p, q - p + 1);
        CHECK(arr.find("null") == std::string::npos);
    }
}
#endif
