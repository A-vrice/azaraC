// test/json/test_json.cpp - JsonSerializer の出力検証
#define ARDUINO 0
#include "../src/azaraC.h"
#include "../src/internal/PrintShim.h"
#include "../src/json/JsonWriter.h"
#include "../test_helpers.h"
#include "doctest.h"
#include <cstring>
#include <limits>
#include <string>

using namespace azaraC;

static bool has(const std::string& s, const char* sub) {
    return s.find(sub) != std::string::npos;
}

// JSON文字列中で "key":value が正しい境界で存在することを検証
// value の直後が , } または文字列終端であることを確認
static bool hasField(const std::string& s, const std::string& key_val) {
    auto pos = s.find(key_val);
    if (pos == std::string::npos) return false;
    size_t end = pos + key_val.size();
    // value の直後が JSON の区切り文字または文字列終端
    return end >= s.size() || s[end] == ',' || s[end] == '}' || s[end] == '\n' || s[end] == ' ';
}

// Helper to create Mt43Data with safe initialization
static void initMt43(Message& m, uint8_t disaster_category) {
    m.msg_type = 43;
    m.payload_type = MsgPayloadType::Mt43;
    m.initPayload<Mt43Data>();
    Mt43Data* mt43 = m.getMt43();
    if (mt43) {
        mt43->disaster_category = disaster_category;
    }
}

// Helper to create Mt44Data with safe initialization
static void initMt44(Message& m) {
    m.msg_type = 44;
    m.payload_type = MsgPayloadType::Mt44;
    m.initPayload<Mt44Data>();
}

// Helper: init Mt43 with specific sub-type (avoids repetitive initAs pattern)
static void initMt43As(Message& m, uint8_t dc) {
    initMt43(m, dc);
    Mt43Data* mt43 = m.getMt43();
    if (!mt43) return;
    switch (dc) {
        case 1: mt43->initAs<EewData>(); break;
        case 2: mt43->initAs<HypocenterData>(); break;
        case 3: mt43->initAs<SeismicData>(); break;
#if (AZARAC_ENABLE_NANKAI)
        case 4: mt43->initAs<NankaiData>(); break;
#endif
        case 5: mt43->initAs<TsunamiData>(); break;
        case 6: mt43->initAs<NwPacTsunamiData>(); break;
        case 8: mt43->initAs<VolcanoData>(); break;
        case 9: mt43->initAs<AshFallData>(); break;
        case 10: mt43->initAs<WeatherData>(); break;
        case 11: mt43->initAs<FloodData>(); break;
        case 12: mt43->initAs<TyphoonData>(); break;
        case 14: mt43->initAs<MarineData>(); break;
        default: break;
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
// MT=44 DCX JSON 出力テスト
// ═══════════════════════════════════════════════════════════════════════════════

#if (AZARAC_ENABLE_DCX_CAMF)
TEST_CASE("JSON Serialization: MT=44 DCX L-Alert") {
    Message m{};
    m.svid = 193; m.crc24 = 0xABCDEF;
    initMt44(m);
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);

    mt44->service_kind = Mt44ServiceKind::LAlert;
    mt44->is_null_message = false;
    mt44->ex_kind = ExtendedKind::LAlertOrLocal;
    mt44->camf.a1 = 1; mt44->camf.a2 = 111; mt44->camf.a3 = 1;
    mt44->camf.a4 = 10; mt44->camf.a5 = 3; mt44->camf.a8 = 4;
    mt44->camf.a11 = 1;
    mt44->ex_lalert_local.ex1 = 1100;
    mt44->ex_lalert_local.vn = 1;
    mt44->sd.sdmt = 0; mt44->sd.sdm = 0x1FF;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"msg_type\":44"));
    CHECK(hasField(s, "\"dcx_type\":1"));
    CHECK(hasField(s, "\"dcx_type_label\":\"L_ALERT\""));
    CHECK(hasField(s, "\"a2_country\":111"));
    CHECK(hasField(s, "\"a3_provider\":1"));
    CHECK(hasField(s, "\"ex1_target_area\":1100"));
    CHECK(hasField(s, "\"sd_sdmt\":0"));
    CHECK(hasField(s, "\"sd_sdm\":511"));
}

TEST_CASE("JSON Serialization: MT=44 DCX J-Alert") {
    Message m{};
    m.svid = 193; m.crc24 = 0xABCDEF;
    initMt44(m);
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);

    mt44->service_kind = Mt44ServiceKind::JAlert;
    mt44->is_null_message = false;
    mt44->ex_kind = ExtendedKind::JAlert;
    mt44->camf.a1 = 1; mt44->camf.a2 = 111; mt44->camf.a3 = 2;
    mt44->camf.a4 = 5; mt44->camf.a5 = 3;
    mt44->ex_jalert.ex8 = 0;
    mt44->ex_jalert.ex9 = 7;
    mt44->ex_jalert.vn = 1;
    mt44->mt44_decoded.jalert_prefecture_mode = true;
    mt44->mt44_decoded.prefecture_count = 3;
    mt44->mt44_decoded.prefecture_positions[0] = 47;
    mt44->mt44_decoded.prefecture_positions[1] = 46;
    mt44->mt44_decoded.prefecture_positions[2] = 45;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"msg_type\":44"));
    CHECK(hasField(s, "\"dcx_type\":2"));
    CHECK(hasField(s, "\"dcx_type_label\":\"J_ALERT\""));
    CHECK(hasField(s, "\"a2_country\":111"));
    CHECK(hasField(s, "\"a3_provider\":2"));
    CHECK(hasField(s, "\"ex8_area_type\":0"));
    CHECK(has(s, "\"jalert_target\":{"));
    CHECK(hasField(s, "\"prefecture_mode\":1"));
    CHECK(hasField(s, "\"prefecture_positions\":[47,46,45]"));
}

TEST_CASE("JSON Serialization: MT=44 DCX Local Government") {
    Message m{};
    m.svid = 193; m.crc24 = 0xABCDEF;
    initMt44(m);
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);

    mt44->service_kind = Mt44ServiceKind::LocalGovernment;
    mt44->is_null_message = false;
    mt44->ex_kind = ExtendedKind::LAlertOrLocal;
    mt44->camf.a1 = 1; mt44->camf.a2 = 111; mt44->camf.a3 = 4;
    mt44->camf.a4 = 10; mt44->camf.a5 = 3;
    mt44->ex_lalert_local.ex1 = 1100;
    mt44->ex_lalert_local.ex2 = 1;
    mt44->ex_lalert_local.ex3 = 91522;
    mt44->ex_lalert_local.ex4 = 68950;
    mt44->ex_lalert_local.ex5 = 10;
    mt44->ex_lalert_local.ex6 = 8;
    mt44->ex_lalert_local.ex7 = 96;
    mt44->ex_lalert_local.vn = 1;
    mt44->mt44_decoded.additional_area.present = true;
    mt44->mt44_decoded.additional_area.head_to_area = true;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"msg_type\":44"));
    CHECK(hasField(s, "\"dcx_type\":3"));
    CHECK(hasField(s, "\"dcx_type_label\":\"LOCAL_GOV\""));
    CHECK(hasField(s, "\"a3_provider\":4"));
    CHECK(hasField(s, "\"ex1_target_area\":1100"));
    CHECK(has(s, "\"additional_area\":{"));
    CHECK(hasField(s, "\"head_to_area\":1"));
}

TEST_CASE("JSON Serialization: MT=44 DCX Outside Japan") {
    Message m{};
    m.svid = 193; m.crc24 = 0xABCDEF;
    initMt44(m);
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);

    mt44->service_kind = Mt44ServiceKind::OutsideJapan;
    mt44->is_null_message = false;
    mt44->ex_kind = ExtendedKind::OutsideJapan;
    mt44->camf.a1 = 1; mt44->camf.a2 = 32; mt44->camf.a3 = 1;
    mt44->ex_outside.vn = 5;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"msg_type\":44"));
    CHECK(hasField(s, "\"dcx_type\":4"));
    CHECK(hasField(s, "\"dcx_type_label\":\"OUTSIDE_JAPAN\""));
    CHECK(hasField(s, "\"a2_country\":32"));
}

TEST_CASE("JSON Serialization: MT=44 DCX Null Message") {
    Message m{};
    m.svid = 193; m.crc24 = 0xABCDEF;
    initMt44(m);
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);

    mt44->service_kind = Mt44ServiceKind::NullMessage;
    mt44->is_null_message = true;
    mt44->ex_kind = ExtendedKind::None;
    mt44->camf.a2 = 111; mt44->camf.a3 = 0;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"msg_type\":44"));
    CHECK(hasField(s, "\"dcx_type\":0"));
    CHECK(hasField(s, "\"dcx_type_label\":\"NULL\""));
}

TEST_CASE("JSON Serialization: MT=44 DCX Unknown") {
    Message m{};
    m.svid = 193; m.crc24 = 0xABCDEF;
    initMt44(m);
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);

    mt44->service_kind = Mt44ServiceKind::Unknown;
    mt44->is_null_message = false;
    mt44->ex_kind = ExtendedKind::None;
    mt44->camf.a2 = 111; mt44->camf.a3 = 5;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"msg_type\":44"));
    CHECK(hasField(s, "\"dcx_type\":5"));
    CHECK(hasField(s, "\"dcx_type_label\":\"UNKNOWN\""));
}

TEST_CASE("JSON Serialization: MT=44 DCX main ellipse") {
    Message m{};
    m.svid = 193; m.crc24 = 0xABCDEF;
    initMt44(m);
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);

    mt44->service_kind = Mt44ServiceKind::LAlert;
    mt44->camf.a1 = 1; mt44->camf.a2 = 111;
    mt44->camf.a3 = 1; mt44->camf.a4 = 1;
    mt44->camf.a5 = 3; mt44->camf.a8 = 4;
    mt44->mt44_decoded.main_ellipse_present = true;
    mt44->mt44_decoded.main_ellipse.lat_microdeg = 35600000;  // 35.6° in microdegrees
    mt44->mt44_decoded.main_ellipse.lon_microdeg = 139600000; // 139.6° in microdegrees

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s,"\"svid\":193"));
    CHECK(hasField(s,"\"msg_type\":44"));
    CHECK(hasField(s,"\"a2_country\":111"));
    CHECK(has(s,"\"main_ellipse\":{"));
    CHECK(hasField(s,"\"lat_deg\":35.600000"));
    CHECK(hasField(s,"\"lon_deg\":139.600000"));
}
#endif // AZARAC_ENABLE_DCX_CAMF

// ═══════════════════════════════════════════════════════════════════════════════
// MT=43 DCR JSON 出力テスト
// ═══════════════════════════════════════════════════════════════════════════════

#if (AZARAC_ENABLE_EEW)
TEST_CASE("JSON Serialization: MT=43 EEW") {
    Message m{};
    initMt43As(m, 1);
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);

    EewData* eew = mt43->getEew();
    REQUIRE(eew != nullptr);

    eew->depth = 60; eew->magnitude = 65; eew->epicenter = 42;
    eew->intensity_lower = 5; eew->intensity_upper = 6;
    eew->region_count = 2;
    eew->regions[0] = 1; eew->regions[1] = 12;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s,"\"disaster_category\":1"));
    // S1-lookup regression: disaster_category は疎キー(binary_search)テーブル
    CHECK(hasField(s,"\"disaster_category_label\":\"緊急地震速報\""));
    // S1-lookup regression: seismic_intensity_lower/upper_limit の疎キーテーブル
    CHECK(hasField(s,"\"intensity_lower_label\":\"震度4\""));
    CHECK(hasField(s,"\"intensity_upper_label\":\"震度5弱\""));
    // S1-lookup regression: eew_forecast_region の疎キーテーブル (code 1 → 北海道道央)
    CHECK(hasField(s,"\"code\":1,\"label\":\"北海道道央\""));
    CHECK(has(s,"\"detail\":{"));
    CHECK(hasField(s,"\"depth\":60"));
    CHECK(hasField(s,"\"magnitude\":65"));
    CHECK(has(s,"\"regions\":["));
}
#endif // AZARAC_ENABLE_EEW

#if (AZARAC_ENABLE_SEISMIC)
TEST_CASE("JSON Serialization: MT=43 Seismic Intensity") {
    Message m{};
    initMt43As(m, 3);
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);

    SeismicData* seis = mt43->getSeismic();
    REQUIRE(seis != nullptr);

    seis->count = 2;
    seis->entries[0] = {4, 13};
    seis->entries[1] = {5, 14};

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s,"\"disaster_category\":3"));
    CHECK(hasField(s,"\"disaster_category_label\":\"震度\""));
    CHECK(has(s,"\"entries\":["));
    CHECK(hasField(s,"\"intensity\":4"));
    CHECK(hasField(s,"\"intensity_label\":\"5強\""));
    CHECK(hasField(s,"\"prefecture\":13"));
    CHECK(hasField(s,"\"prefecture_label\":\"東京都\""));
}
#endif // AZARAC_ENABLE_SEISMIC

#if (AZARAC_ENABLE_HYPOCENTER)
TEST_CASE("JSON Serialization: MT=43 Hypocenter") {
    Message m{};
    initMt43As(m, 2);
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);

    HypocenterData* hypo = mt43->getHypocenter();
    REQUIRE(hypo != nullptr);

    hypo->depth = 40;
    hypo->magnitude = 64;
    hypo->epicenter = 791;
    hypo->notification_count = 1;
    hypo->notification[0] = 201;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"disaster_category\":2"));
    CHECK(hasField(s, "\"disaster_category_label\":\"震源\""));
    CHECK(has(s, "\"detail\":{"));
    CHECK(hasField(s, "\"depth\":40"));
    CHECK(hasField(s, "\"magnitude\":64"));
    CHECK(hasField(s, "\"epicenter\":791"));
    CHECK(hasField(s, "\"epicenter_label\":\"日向灘\""));
    CHECK(has(s, "\"notifications\":["));
    CHECK(hasField(s, "\"code\":201,\"label\":\"強い揺れに警戒してください。\""));
}
#endif // AZARAC_ENABLE_HYPOCENTER

#if (AZARAC_ENABLE_TSUNAMI)
TEST_CASE("JSON Serialization: MT=43 Tsunami") {
    Message m{};
    initMt43As(m, 5);
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);

    TsunamiData* tsunami = mt43->getTsunami();
    REQUIRE(tsunami != nullptr);

    tsunami->warning_code = 3;
    tsunami->count = 2;
    tsunami->entries[0].region_code = 65;
    tsunami->entries[0].height_code = 4;
    tsunami->entries[1].region_code = 66;
    tsunami->entries[1].height_code = 2;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"disaster_category\":5"));
    CHECK(hasField(s, "\"disaster_category_label\":\"津波\""));
    CHECK(has(s, "\"detail\":{"));
    CHECK(hasField(s, "\"warning_code\":3"));
    CHECK(hasField(s, "\"warning_code_label\":\"津波警報\""));
    CHECK(has(s, "\"entries\":["));
    CHECK(hasField(s, "\"region\":65"));
    CHECK(hasField(s, "\"height\":4"));
    CHECK(hasField(s, "\"height_label\":\"5m\""));
}
#endif // AZARAC_ENABLE_TSUNAMI

#if (AZARAC_ENABLE_NANKAI)
TEST_CASE("JSON Serialization: MT=43 Nankai Trough") {
    Message m{};
    initMt43As(m, 4);
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);

    NankaiData* nankai = mt43->getNankai();
    REQUIRE(nankai != nullptr);

    nankai->info_code = 1;
    nankai->page = 2;
    nankai->total_page = 3;
    nankai->text[0] = 'T';
    nankai->text[1] = 'e';
    nankai->text[2] = 's';
    nankai->text[3] = 't';

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"disaster_category\":4"));
    CHECK(hasField(s, "\"disaster_category_label\":\"南海トラフ地震\""));
    CHECK(has(s, "\"detail\":{"));
    CHECK(hasField(s, "\"info_code\":1"));
    CHECK(has(s, "\"info_code_label\":\"調査中A"));
    CHECK(hasField(s, "\"page\":2"));
    CHECK(hasField(s, "\"total_page\":3"));
}
#endif // AZARAC_ENABLE_NANKAI

#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)
TEST_CASE("JSON Serialization: MT=43 NW Pacific Tsunami") {
    Message m{};
    initMt43As(m, 6);
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);

    NwPacTsunamiData* nw_pac = mt43->getNwPac();
    REQUIRE(nw_pac != nullptr);

    nw_pac->potential = 2;
    nw_pac->count = 1;
    nw_pac->entries[0].region_code = 1;
    nw_pac->entries[0].height_code = 3;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"disaster_category\":6"));
    CHECK(hasField(s, "\"disaster_category_label\":\"北西太平洋津波\""));
    CHECK(has(s, "\"detail\":{"));
    CHECK(hasField(s, "\"potential\":2"));
    CHECK(hasField(s, "\"potential_label\":\"There is a Possibility of a Destructive Regional Tsunami\""));
    CHECK(has(s, "\"entries\":["));
    CHECK(hasField(s, "\"height_label\":\"3m~5m\""));
    // S1-lookup regression: coastal_region_en の疎キーテーブル (code 1 → Ust-Kamchatsk)
    CHECK(hasField(s, "\"region\":1,\"region_label\":\"Ust-Kamchatsk (East Coasts of Kamchatka Peninsula)\""));
}
#endif // AZARAC_ENABLE_NW_PAC_TSUNAMI

#if (AZARAC_ENABLE_VOLCANO)
TEST_CASE("JSON Serialization: MT=43 Volcano") {
    Message m{};
    initMt43As(m, 8);
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);

    VolcanoData* vol = mt43->getVolcano();
    REQUIRE(vol != nullptr);

    vol->warning_code = 52;
    vol->volcano_name = 503;
    vol->ambiguity = 0;
    vol->lg_count = 1;
    vol->local_govs[0] = 4600000;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"disaster_category\":8"));
    // S1-lookup regression: dc=8 は火山（修正前は array 戦略で降灰にズレていた）
    CHECK(hasField(s, "\"disaster_category_label\":\"火山\""));
    CHECK(has(s, "\"detail\":{"));
    CHECK(hasField(s, "\"warning_code\":52"));
    CHECK(hasField(s, "\"warning_code_label\":\"噴火\""));
    CHECK(hasField(s, "\"volcano_name\":503"));
    CHECK(hasField(s, "\"volcano_name_label\":\"阿蘇山\""));
    CHECK(has(s, "\"local_govs\":["));
}
#endif // AZARAC_ENABLE_VOLCANO

#if (AZARAC_ENABLE_ASH_FALL)
TEST_CASE("JSON Serialization: MT=43 Ash Fall") {
    Message m{};
    initMt43As(m, 9);
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);

    AshFallData* ash = mt43->getAshFall();
    REQUIRE(ash != nullptr);

    ash->warning_type = 1;
    ash->volcano_name = 503;
    ash->count = 2;
    ash->entries_time[0] = 3;
    ash->entries_code[0] = 2;
    ash->entries_lg[0] = 1100000;
    ash->entries_time[1] = 6;
    ash->entries_code[1] = 5;
    ash->entries_lg[1] = 1200000;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"disaster_category\":9"));
    CHECK(hasField(s, "\"disaster_category_label\":\"降灰\""));
    CHECK(has(s, "\"detail\":{"));
    CHECK(hasField(s, "\"warning_type\":1"));
    CHECK(hasField(s, "\"warning_type_label\":\"速報\""));
    CHECK(hasField(s, "\"volcano_name\":503"));
    CHECK(hasField(s, "\"volcano_name_label\":\"阿蘇山\""));
    CHECK(has(s, "\"entries\":["));
    CHECK(hasField(s, "\"warning_code\":2,\"warning_code_label\":\"やや多量の降灰\""));
}
#endif // AZARAC_ENABLE_ASH_FALL

#if (AZARAC_ENABLE_WEATHER)
TEST_CASE("JSON Serialization: MT=43 Weather") {
    Message m{};
    initMt43As(m, 10);
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);

    WeatherData* wx = mt43->getWeather();
    REQUIRE(wx != nullptr);

    wx->warning_state = 1;
    wx->count = 3;
    wx->entries[0].sub_category = 2;
    wx->entries[0].region_code = 11000;
    wx->entries[1].sub_category = 3;
    wx->entries[1].region_code = 12000;
    wx->entries[2].sub_category = 7;
    wx->entries[2].region_code = 13000;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"disaster_category\":10"));
    CHECK(hasField(s, "\"disaster_category_label\":\"気象\""));
    CHECK(has(s, "\"detail\":{"));
    CHECK(hasField(s, "\"warning_state\":1"));
    CHECK(hasField(s, "\"warning_state_label\":\"発表\""));
    CHECK(has(s, "\"entries\":["));
    CHECK(hasField(s, "\"sub_category\":2"));
    CHECK(hasField(s, "\"sub_category_label\":\"大雨特別警報\""));
    CHECK(hasField(s, "\"region\":11000"));
    CHECK(hasField(s, "\"region_label\":\"宗谷地方\""));
}
#endif // AZARAC_ENABLE_WEATHER

#if (AZARAC_ENABLE_FLOOD)
TEST_CASE("JSON Serialization: MT=43 Flood") {
    Message m{};
    initMt43As(m, 11);
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);

    FloodData* flood = mt43->getFlood();
    REQUIRE(flood != nullptr);

    flood->count = 2;
    flood->entries[0].warning_level = 3;
    flood->entries[0].region_code = 1234567ULL;
    flood->entries[1].warning_level = 4;
    flood->entries[1].region_code = 890ULL;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"disaster_category\":11"));
    CHECK(hasField(s, "\"disaster_category_label\":\"洪水\""));
    CHECK(has(s, "\"detail\":{"));
    CHECK(has(s, "\"entries\":["));
    CHECK(hasField(s, "\"warning_level\":3"));
    CHECK(hasField(s, "\"warning_level_label\":\"氾濫危険情報\""));
}
#endif // AZARAC_ENABLE_FLOOD

#if (AZARAC_ENABLE_TYPHOON)
TEST_CASE("JSON Serialization: MT=43 Typhoon") {
    Message m{};
    initMt43As(m, 12);
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);

    TyphoonData* typh = mt43->getTyphoon();
    REQUIRE(typh != nullptr);

    typh->number = 21;
    typh->scale = 3;
    typh->intensity = 2;
    typh->pressure = 980;
    typh->max_wind = 35;
    typh->max_gust = 50;
    typh->coords.lat_ns = 0;
    typh->coords.lat_deg = 25;
    typh->coords.lon_ew = 0;
    typh->coords.lon_deg = 130;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"disaster_category\":12"));
    CHECK(hasField(s, "\"disaster_category_label\":\"台風\""));
    CHECK(has(s, "\"detail\":{"));
    CHECK(hasField(s, "\"number\":21"));
    CHECK(hasField(s, "\"scale\":3"));
    CHECK(hasField(s, "\"intensity\":2"));
    CHECK(hasField(s, "\"intensity_label\":\"非常に強い\""));
    CHECK(hasField(s, "\"pressure\":980"));
    CHECK(hasField(s, "\"max_wind\":35"));
    CHECK(hasField(s, "\"max_gust\":50"));
}
#endif // AZARAC_ENABLE_TYPHOON

#if (AZARAC_ENABLE_MARINE)
TEST_CASE("JSON Serialization: MT=43 Marine") {
    Message m{};
    initMt43As(m, 14);
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);

    MarineData* marine = mt43->getMarine();
    REQUIRE(marine != nullptr);

    marine->count = 2;
    marine->entries[0].warning_code = 19;
    marine->entries[0].region_code = 100;
    marine->entries[1].warning_code = 20;
    marine->entries[1].region_code = 200;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"disaster_category\":14"));
    // S1-lookup regression: dc=14 は海上（修正前は array 戦略で out-of-bounds→空）
    CHECK(hasField(s, "\"disaster_category_label\":\"海上\""));
    CHECK(has(s, "\"detail\":{"));
    CHECK(has(s, "\"entries\":["));
    CHECK(hasField(s, "\"warning_code\":19"));
    CHECK(hasField(s, "\"region\":100"));
    // 疎キー negative: marine warning code 19 は未定義→空、20 → 海上風警報
    CHECK(hasField(s, "\"warning_code\":20,\"warning_code_label\":\"海上風警報\""));
}
#endif // AZARAC_ENABLE_MARINE

// ═══════════════════════════════════════════════════════════════════════════════
// JSON 構造検証
// ═══════════════════════════════════════════════════════════════════════════════
TEST_CASE("JSON Serialization: Balanced braces/brackets") {
    auto test_balanced = [](const Message& m) {
        StringPrint sp;
        internal::JsonSerializer::serialize(m, sp);
        const auto& s = sp.str();
        int brace = 0, bracket = 0; bool in_str = false; char prev = 0;
        for (char c : s) {
            if (c == '"' && prev != '\\') in_str = !in_str;
            if (!in_str) {
                if (c=='{') brace++;
                if (c=='}') brace--;
                if (c=='[') bracket++;
                if (c==']') bracket--;
            }
            prev = c;
        }
        CHECK_MESSAGE((brace == 0 && bracket == 0), "json=", s.c_str());
    };

    SUBCASE("Disaster Categories 1-14") {
        // dc=7 は未割り当てのため除外
        for (uint8_t dc : {1,2,3,4,5,6,8,9,10,11,12,14}) {
            Message m{}; initMt43(m, dc);
            test_balanced(m);
        }
    }
    SUBCASE("MT=44") {
        Message m{}; initMt44(m);
        test_balanced(m);
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
// JSON エスケープ文字テスト (json_serialization.md #1)
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("JSON Serialization: Escape characters in writeStr") {
    // Test that writeStr properly escapes special JSON characters
    SUBCASE("Double quote") {
        StringPrint sp;
        internal::writeStr(sp, std::string_view("test\"value"));
        const auto& s = sp.str();
        CHECK(s == "\"test\\\"value\"");
    }
    SUBCASE("Backslash") {
        StringPrint sp;
        internal::writeStr(sp, std::string_view("back\\slash"));
        const auto& s = sp.str();
        CHECK(s == "\"back\\\\slash\"");
    }
    SUBCASE("Newline") {
        StringPrint sp;
        internal::writeStr(sp, std::string_view("line1\nline2"));
        const auto& s = sp.str();
        CHECK(s == "\"line1\\nline2\"");
    }
    SUBCASE("Carriage return") {
        StringPrint sp;
        internal::writeStr(sp, std::string_view("cr\rhere"));
        const auto& s = sp.str();
        CHECK(s == "\"cr\\rhere\"");
    }
    SUBCASE("Tab") {
        StringPrint sp;
        internal::writeStr(sp, std::string_view("tab\there"));
        const auto& s = sp.str();
        CHECK(s == "\"tab\\there\"");
    }
    SUBCASE("Backspace") {
        StringPrint sp;
        internal::writeStr(sp, std::string_view("bs\bhere"));
        const auto& s = sp.str();
        CHECK(s == "\"bs\\bhere\"");
    }
    SUBCASE("Form feed") {
        StringPrint sp;
        internal::writeStr(sp, std::string_view("ff\fhere"));
        const auto& s = sp.str();
        CHECK(s == "\"ff\\fhere\"");
    }
    SUBCASE("Control character (0x01)") {
        StringPrint sp;
        std::string ctrl = std::string("ctrl") + '\x01' + "here";
        internal::writeStr(sp, std::string_view(ctrl));
        const auto& s = sp.str();
        CHECK(s == "\"ctrl\\u0001here\"");
    }
    SUBCASE("UTF-8 bytes pass through") {
        StringPrint sp;
        // Japanese UTF-8: こんにちは
        internal::writeStr(sp, std::string_view("\xE3\x81\x93\xE3\x82\x93\xE3\x81\xAB\xE3\x81\xA1\xE3\x81\xAF"));
        const auto& s = sp.str();
        CHECK(s == "\"\xE3\x81\x93\xE3\x82\x93\xE3\x81\xAB\xE3\x81\xA1\xE3\x81\xAF\"");
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
// MT=43 report_time JSON 出力テスト (json_serialization.md #2)
// ═══════════════════════════════════════════════════════════════════════════════

#if (AZARAC_ENABLE_EEW)
TEST_CASE("JSON Serialization: MT=43 report_time output") {
    Message m{};
    m.msg_type = 43;
    m.payload_type = MsgPayloadType::Mt43;
    m.initPayload<Mt43Data>();
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);
    mt43->disaster_category = 1;

    // Set event_time fields
    mt43->event_time.month = 1;
    mt43->event_time.day = 1;
    mt43->event_time.hour = 0;
    mt43->event_time.minute = 0;
    mt43->event_time.unix_time = 1704067200;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(has(s, "\"report_time\":"));
    CHECK(hasField(s, "\"month\":1"));
    CHECK(hasField(s, "\"day\":1"));
    CHECK(hasField(s, "\"hour\":0"));
    CHECK(hasField(s, "\"min\":0"));
    CHECK(hasField(s, "\"unix\":1704067200"));
}
#endif // AZARAC_ENABLE_EEW

// ═══════════════════════════════════════════════════════════════════════════════
// MT=44 onset_time JSON 出力テスト (json_serialization.md #3)
// ═══════════════════════════════════════════════════════════════════════════════

#if (AZARAC_ENABLE_DCX_CAMF)
TEST_CASE("JSON Serialization: MT=44 onset_time output") {
    Message m{};
    m.svid = 193; m.crc24 = 0xABCDEF;
    initMt44(m);
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);

    mt44->service_kind = Mt44ServiceKind::LAlert;
    mt44->is_null_message = false;
    mt44->ex_kind = ExtendedKind::LAlertOrLocal;
    mt44->camf.a1 = 1; mt44->camf.a2 = 111; mt44->camf.a3 = 1;
    mt44->camf.a4 = 10; mt44->camf.a5 = 3; mt44->camf.a8 = 4;
    mt44->camf.a6 = 0; mt44->camf.a7 = 1;
    mt44->ex_lalert_local.ex1 = 1100;
    mt44->ex_lalert_local.vn = 1;
    mt44->sd.sdmt = 0; mt44->sd.sdm = 0x1FF;

    // Set onset_time fields
    mt44->onset_time.month = 3;
    mt44->onset_time.day = 15;
    mt44->onset_time.hour = 14;
    mt44->onset_time.minute = 30;
    mt44->onset_time.unix_time = 1710508200;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(has(s, "\"onset_time\":"));
    CHECK(hasField(s, "\"month\":3"));
    CHECK(hasField(s, "\"day\":15"));
    CHECK(hasField(s, "\"hour\":14"));
    CHECK(hasField(s, "\"min\":30"));
    CHECK(hasField(s, "\"unix\":1710508200"));
}
#endif // AZARAC_ENABLE_DCX_CAMF

// ═══════════════════════════════════════════════════════════════════════════════
// MT=44 sd_sdmt=1 テスト (json_serialization.md #4)
// ═══════════════════════════════════════════════════════════════════════════════

#if (AZARAC_ENABLE_DCX_CAMF)
TEST_CASE("JSON Serialization: MT=44 sd_sdmt=1 output") {
    Message m{};
    m.svid = 193; m.crc24 = 0xABCDEF;
    initMt44(m);
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);

    mt44->service_kind = Mt44ServiceKind::LAlert;
    mt44->is_null_message = false;
    mt44->ex_kind = ExtendedKind::LAlertOrLocal;
    mt44->camf.a1 = 1; mt44->camf.a2 = 111; mt44->camf.a3 = 1;
    mt44->camf.a4 = 10; mt44->camf.a5 = 3; mt44->camf.a8 = 4;
    mt44->ex_lalert_local.ex1 = 1100;
    mt44->ex_lalert_local.vn = 1;
    mt44->sd.sdmt = 1;  // ← sdmt=1
    mt44->sd.sdm = 0x1FF;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"sd_sdmt\":1"));
}
#endif // AZARAC_ENABLE_DCX_CAMF

// ═══════════════════════════════════════════════════════════════════════════════
// MT=44 a6=0 / a8=0 / a9=0 / a10=0 / a11=0 テスト (json_serialization.md #5)
// ═══════════════════════════════════════════════════════════════════════════════

#if (AZARAC_ENABLE_DCX_CAMF)
TEST_CASE("JSON Serialization: MT=44 zero-value fields output") {
    Message m{};
    m.svid = 193; m.crc24 = 0xABCDEF;
    initMt44(m);
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);

    mt44->service_kind = Mt44ServiceKind::LAlert;
    mt44->is_null_message = false;
    mt44->ex_kind = ExtendedKind::LAlertOrLocal;
    mt44->camf.a1 = 1; mt44->camf.a2 = 111; mt44->camf.a3 = 1;
    mt44->camf.a4 = 10; mt44->camf.a5 = 3;
    mt44->camf.a6 = 0;   // ← 0
    mt44->camf.a7 = 1;
    mt44->camf.a8 = 0;   // ← 0
    mt44->camf.a9 = 0;   // ← 0
    mt44->camf.a10 = 0;  // ← 0
    mt44->camf.a11 = 0;  // ← 0
    mt44->ex_lalert_local.ex1 = 1100;
    mt44->ex_lalert_local.vn = 1;
    mt44->sd.sdmt = 0; mt44->sd.sdm = 0x1FF;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"a6_onset_week\":0"));
    CHECK(hasField(s, "\"a8_duration\":0"));
    CHECK(hasField(s, "\"a9_type_of_library\":0"));
    CHECK(hasField(s, "\"a10_library_version\":0"));
    CHECK(hasField(s, "\"a11_guidance\":0"));
}
#endif // AZARAC_ENABLE_DCX_CAMF

// ═══════════════════════════════════════════════════════════════════════════════
// MT=43 event_time 未解決 (report_unix=0) テスト (json_serialization.md #6)
// ═══════════════════════════════════════════════════════════════════════════════

#if (AZARAC_ENABLE_EEW)
TEST_CASE("JSON Serialization: MT=43 unix_time=0 output") {
    Message m{};
    m.msg_type = 43;
    m.payload_type = MsgPayloadType::Mt43;
    m.initPayload<Mt43Data>();
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);
    mt43->disaster_category = 1;

    // event_time with unix_time=0 (not resolved)
    mt43->event_time.month = 0;
    mt43->event_time.day = 0;
    mt43->event_time.hour = 0;
    mt43->event_time.minute = 0;
    mt43->event_time.unix_time = 0;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"unix\":0"));
}
#endif // AZARAC_ENABLE_EEW

// ═══════════════════════════════════════════════════════════════════════════════
// Nankai 集約後 text_utf8 出力テスト (integration_e2e.md #2)
// ═══════════════════════════════════════════════════════════════════════════════

#if (AZARAC_ENABLE_NANKAI)
TEST_CASE("JSON Serialization: Nankai aggregated text_utf8 output") {
    Message m{};
    initMt43As(m, 4);  // Nankai
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);

    NankaiData* nankai = mt43->getNankai();
    REQUIRE(nankai != nullptr);

    // Simulate aggregated state (multi-page complete)
    nankai->is_aggregated = true;
    const char* aggregated = "南海トラフ地震に関する情報";
    nankai->aggregated_len = strlen(aggregated);
    nankai->aggregated_text_ptr = aggregated;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    // Should output text_utf8, not text_hex
    CHECK(s.find("\"text_utf8\":") != std::string::npos);
    CHECK(s.find("\"text_hex\"") == std::string::npos);
    CHECK(has(s, aggregated));
}
#endif // AZARAC_ENABLE_NANKAI

#if (AZARAC_ENABLE_NANKAI)
TEST_CASE("JSON Serialization: Nankai incomplete text_hex output") {
    Message m{};
    initMt43As(m, 4);  // Nankai
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);

    NankaiData* nankai = mt43->getNankai();
    REQUIRE(nankai != nullptr);

    // Not aggregated (default state)
    nankai->is_aggregated = false;
    nankai->page = 3;
    nankai->total_page = 27;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    // Should output text_hex, not text_utf8
    CHECK(s.find("\"text_hex\":") != std::string::npos);
    CHECK(s.find("\"text_utf8\"") == std::string::npos);
    CHECK(hasField(s, "\"page\":3"));
    CHECK(hasField(s, "\"total_page\":27"));
}
#endif // AZARAC_ENABLE_NANKAI

// ═══════════════════════════════════════════════════════════════════════════════
// JsonWriter 個別関数テスト
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("wf_u64 出力") {
    StringPrint sp;

    // 最小値: 0
    internal::wf_u64(sp, "zero", 0ULL, true);
    CHECK(sp.str() == "\"zero\":0");

    // 最大値
    sp = StringPrint{};
    internal::wf_u64(sp, "max", 18446744073709551615ULL, false);
    CHECK(sp.str() == "\"max\":18446744073709551615,");

    // 中間値: last=true でカンマなし
    sp = StringPrint{};
    internal::wf_u64(sp, "val", 12345678901234ULL, true);
    CHECK(sp.str() == "\"val\":12345678901234");

    // last=false でカンマあり
    sp = StringPrint{};
    internal::wf_u64(sp, "a", 1ULL, false);
    CHECK(sp.str() == "\"a\":1,");
}

// ═══════════════════════════════════════════════════════════════════════════════
// writeDouble エッジケーステスト
// ═══════════════════════════════════════════════════════════════════════════════
TEST_CASE("writeDouble: 通常の正の値") {
    StringPrint sp;
    internal::writeDouble(sp, 3.14159, 2);
    CHECK(sp.str() == "3.14");
}

TEST_CASE("writeDouble: 通常の負の値") {
    StringPrint sp;
    internal::writeDouble(sp, -3.14159, 2);
    CHECK(sp.str() == "-3.14");
}

TEST_CASE("writeDouble: ゼロ") {
    StringPrint sp;
    internal::writeDouble(sp, 0.0, 3);
    CHECK(sp.str() == "0.000");
}

TEST_CASE("writeDouble: 負の微小値がゼロに丸められる (符号抑制)") {
    StringPrint sp;
    internal::writeDouble(sp, -0.0000001, 6);
    CHECK(sp.str() == "0.000000");
}

TEST_CASE("writeDouble: 負の微小値がゼロに丸められる (precision=3)") {
    StringPrint sp;
    internal::writeDouble(sp, -0.0004, 3);
    CHECK(sp.str() == "0.000");
}

TEST_CASE("writeDouble: 符号抑制のしきい値超えで符号あり") {
    StringPrint sp;
    internal::writeDouble(sp, -0.000001, 6);
    CHECK(sp.str() == "-0.000001");
}

TEST_CASE("writeDouble: NaNはnull") {
    StringPrint sp;
    double nan = std::numeric_limits<double>::quiet_NaN();
    internal::writeDouble(sp, nan, 3);
    CHECK(sp.str() == "null");
}

TEST_CASE("writeDouble: 無限大はnull") {
    StringPrint sp;
    double inf = std::numeric_limits<double>::infinity();
    internal::writeDouble(sp, inf, 3);
    CHECK(sp.str() == "null");
}

TEST_CASE("writeDouble: 負の無限大はnull") {
    StringPrint sp;
    double ninf = -std::numeric_limits<double>::infinity();
    internal::writeDouble(sp, ninf, 3);
    CHECK(sp.str() == "null");
}
