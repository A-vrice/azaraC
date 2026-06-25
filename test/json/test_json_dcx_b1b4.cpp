// test/json/test_json_dcx_b1b4.cpp — DCX B1-B4 JSON出力テスト

#define ARDUINO 0
#include "../src/azaraC.h"
#include "../src/internal/PrintShim.h"
#include "../test_helpers.h"
#include "doctest.h"
#include <cstring>
#include <string>

using namespace azaraC;

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
    mt44->mt44_decoded.main_ellipse.lat_deg = 35.6;
    mt44->mt44_decoded.main_ellipse.lon_deg = 139.6;
    mt44->mt44_decoded.main_ellipse.b1_lat_offset_deg = 0.0024;
    mt44->mt44_decoded.main_ellipse.b1_lon_offset_deg = 0.0024;
    mt44->mt44_decoded.main_ellipse.b1_major_factor = 0.875;
    mt44->mt44_decoded.main_ellipse.b1_minor_factor = 0.875;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(has(s, "\"b1_refinement\":{"));
    CHECK(has(s, "\"c1_lat_offset_deg\":"));
    CHECK(has(s, "\"c2_lon_offset_deg\":"));
    CHECK(has(s, "\"c3_major_factor\":"));
    CHECK(has(s, "\"c4_minor_factor\":"));
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
    mt44->mt44_decoded.main_ellipse.lat_deg = 35.6;
    mt44->mt44_decoded.main_ellipse.lon_deg = 139.6;

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
    mt44->camf.b4_present = true;
    mt44->camf.b4_d1_present = true;
    mt44->camf.b4_d1 = 15;
    mt44->camf.b4_d2_present = true;
    mt44->camf.b4_d2 = 7;
    mt44->mt44_decoded.main_ellipse_present = true;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(has(s, "\"detailed_info\":{"));
    CHECK(has(s, "\"a4_code\":36"));
    CHECK(has(s, "\"d1_magnitude\":{\"raw\":15"));
    CHECK(has(s, "\"d2_seismic_coeff\":{\"raw\":7"));
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
    mt44->mt44_decoded.main_ellipse.lat_deg = 35.6;
    mt44->mt44_decoded.main_ellipse.lon_deg = 139.6;
    mt44->mt44_decoded.main_ellipse.semi_major_km = 100.0;
    mt44->mt44_decoded.main_ellipse.semi_minor_km = 50.0;
    mt44->mt44_decoded.main_ellipse.azimuth_deg = 45.0;

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
    mt44->mt44_decoded.additional_area.ellipse.lat_deg = 35.0;
    mt44->mt44_decoded.additional_area.ellipse.lon_deg = 140.0;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(has(s, "\"additional_area\":{"));
    CHECK(has(s, "\"head_to_area\":1"));
}
