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

static bool has(const std::string& s, const std::string& sub) {
    return s.find(sub) != std::string::npos;
}

// ラベルはビルド時に選んだ言語で出力される。これらのテストが検証するのはコード→ラベルの対応（S1-lookup 回帰）なので、言語ごとの期待値を持たせてどの構成でも意味を保つ。
#if AZARAC_LANG_JA
#  define LBL(ja, en) ja
#elif AZARAC_LANG_EN
#  define LBL(ja, en) en
#else
#  define LBL(ja, en) ""
#endif

static bool hasLabel(const std::string& s, const char* key, const char* value) {
    return s.find(std::string("\"") + key + "\":\"" + value + "\"") != std::string::npos;
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

static void initMt43(Message& m, uint8_t disaster_category) {
    m.msg_type = 43;
    m.payload_type = MsgPayloadType::Mt43;
    m.initPayload<Mt43Data>();
    Mt43Data* mt43 = m.getMt43();
    if (mt43) {
        mt43->disaster_category = disaster_category;
    }
}

#if (AZARAC_ENABLE_DCX_CAMF)
static void initMt44(Message& m) {
    m.msg_type = 44;
    m.payload_type = MsgPayloadType::Mt44;
    m.initPayload<Mt44Data>();
}
#endif // AZARAC_ENABLE_DCX_CAMF

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

// MT=44 DCX JSON 出力テスト

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
    CHECK(hasField(s, "\"dcx_type\":\"L_ALERT\""));
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
    CHECK(hasField(s, "\"dcx_type\":\"J_ALERT\""));
    CHECK(hasField(s, "\"a2_country\":111"));
    CHECK(hasField(s, "\"a3_provider\":2"));
    CHECK(hasField(s, "\"ex8_area_type\":0"));
    CHECK(has(s, "\"jalert_target\":{"));
    CHECK(has(s, std::string("\"prefectures\":[{\"position\":47,\"label\":\"")
                             + LBL("沖縄県", "Okinawa Prefecture") + "\""));
    CHECK(hasField(s, "\"position\":46"));
    CHECK(hasField(s, "\"position\":45"));
    CHECK(s.find("prefecture_mode") == std::string::npos);
    CHECK(s.find("prefecture_positions") == std::string::npos);
    CHECK(s.find("prefecture_labels") == std::string::npos);
    // Regression: ex_vn must be preceded by a comma after the array close (was "]\"ex_vn\"" — invalid JSON). See bugfix: JAlert JSON missing comma.
    CHECK(s.find("],\"ex_vn\"") != std::string::npos);
    CHECK(s.find("]\"ex_vn\"") == std::string::npos);
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
    CHECK(hasField(s, "\"dcx_type\":\"LOCAL_GOV\""));
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
    CHECK(hasField(s, "\"dcx_type\":\"OUTSIDE_JAPAN\""));
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
    CHECK(hasField(s, "\"dcx_type\":\"NULL\""));
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
    CHECK(hasField(s, "\"dcx_type\":\"UNKNOWN\""));
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

// MT=43 DCR JSON 出力テスト

TEST_CASE("JSON v2: svid is the raw PRN, no svid_label") {
    // フレーマは svid を PRN（128–191）に正規化して入れる。v2 はそれをそのまま出し、ラベルは付けない（読み手は PRN から自分で引く）。
    Message m{};
    initMt43As(m, 1);

    for (uint8_t svid : {uint8_t{184}, uint8_t{186}, uint8_t{247}, uint8_t{119}}) {
        m.svid = svid;
        StringPrint sp;
        internal::JsonSerializer::serialize(m, sp);
        const auto& s = sp.str();
        INFO("svid=", (int)svid);
        CHECK(hasField(s, std::string("\"svid\":") + std::to_string(svid)));
        CHECK(s.find("svid_label") == std::string::npos);
    }
}

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
    CHECK(hasLabel(s, "disaster_category_label", LBL("緊急地震速報", "Earthquake Early Warning")));
    // S1-lookup regression: seismic_intensity_lower/upper_limit の疎キーテーブル
    CHECK(hasLabel(s, "intensity_lower_label", LBL("震度4", "Seismic intensity of 4")));
    CHECK(hasLabel(s, "intensity_upper_label", LBL("震度5弱", "Seismic intensity of 5-lower")));
    // S1-lookup regression: eew_forecast_region の疎キーテーブル (code 1 → 北海道道央)
    CHECK(has(s, std::string("\"code\":1,\"label\":\"") + LBL("北海道道央", "Central Area of Hokkaido (Do'o)") + "\""));
    CHECK(has(s,"\"data\":{"));
    CHECK(hasField(s,"\"depth\":60"));
    CHECK(hasField(s,"\"magnitude\":65"));
    CHECK(hasLabel(s, "depth_label", LBL("60km", "60 km")));
    CHECK(hasLabel(s, "magnitude_label", LBL("6.5", "6.5")));
    CHECK(has(s,"\"regions\":["));
}
#endif // AZARAC_ENABLE_EEW

// _label_en は _label と別言語のラベルを併記する。両言語 ON のときだけ出る。
// AZARAC_LANG_EN 単独でガードすると JA=0/EN=1 でも走り、その構成では _label が EN になるため JA 前提の期待値が成立しない。
#if (AZARAC_ENABLE_EEW) && (AZARAC_LANG_JA) && (AZARAC_LANG_EN)
TEST_CASE("JSON Serialization: label_en is emitted when both languages are on") {
    Message m{};
    initMt43As(m, 1);                    // EEW
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);
    EewData* eew = mt43->getEew();
    REQUIRE(eew != nullptr);
    eew->depth = 60;
    eew->magnitude = 65;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    // _label は JA、_label_en は EN（併記）
    CHECK(hasLabel(s, "depth_label", "60km"));
    CHECK(hasLabel(s, "depth_label_en", "60 km"));
    CHECK(hasLabel(s, "magnitude_label", "6.5"));
    CHECK(hasLabel(s, "magnitude_label_en", "6.5"));
}
#endif // AZARAC_ENABLE_EEW && AZARAC_LANG_JA && AZARAC_LANG_EN

// 数量コードの境界値とセンチネルがラベルとして可視化されること。
// 501/101 は「境界超過」、511/127 は「不明」で、生コード値だけでは利用者が判別できない。
#if (AZARAC_ENABLE_EEW)
// 両言語とも無効な構成では LBL が "" を返し、hasLabel(..., "") が常に真になる（空振り通過）。その構成ではラベル自体が出力されないため検証対象が無く、テストごとコンパイルしない。
#if (AZARAC_LANG_JA) || (AZARAC_LANG_EN)
TEST_CASE("JSON Serialization: quantity labels expose bounds and sentinels") {
    Message m{};
    initMt43As(m, 1);                    // EEW
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);
    EewData* eew = mt43->getEew();
    REQUIRE(eew != nullptr);

    eew->depth = 501;      // 500km より深い（境界）
    eew->magnitude = 101;  // 10.0 より大きい（境界）
    StringPrint sp1;
    internal::JsonSerializer::serialize(m, sp1);
    CHECK(hasLabel(sp1.str(), "depth_label", LBL("500kmより深い", "Deeper than 500 km")));
    CHECK(hasLabel(sp1.str(), "magnitude_label", LBL("10.0より大きい", "Over 10.0")));
    // ラベルが空振りしていないことを生コード側でも押さえる
    CHECK(hasField(sp1.str(), "\"depth\":501"));
    CHECK(hasField(sp1.str(), "\"magnitude\":101"));

    eew->depth = 511;      // 不明（センチネル）
    eew->magnitude = 127;  // 不明（センチネル）
    StringPrint sp2;
    internal::JsonSerializer::serialize(m, sp2);
    CHECK(hasLabel(sp2.str(), "depth_label", LBL("不明", "Unknown")));
    CHECK(hasLabel(sp2.str(), "magnitude_label", LBL("不明", "Unknown")));
    CHECK(hasField(sp2.str(), "\"depth\":511"));
    CHECK(hasField(sp2.str(), "\"magnitude\":127"));

#if (AZARAC_LANG_JA) && (AZARAC_LANG_EN)
    // 併記される英語ラベルも境界/センチネルを反映すること
    eew->depth = 501;
    eew->magnitude = 127;
    StringPrint sp3;
    internal::JsonSerializer::serialize(m, sp3);
    CHECK(hasLabel(sp3.str(), "depth_label_en", "Deeper than 500 km"));
    CHECK(hasLabel(sp3.str(), "magnitude_label_en", "Unknown"));
#endif
}
#endif // (AZARAC_LANG_JA) || (AZARAC_LANG_EN)
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
    CHECK(hasLabel(s, "disaster_category_label", LBL("震度", "Seismic Intensity")));
    CHECK(has(s,"\"entries\":["));
    CHECK(hasField(s,"\"intensity\":4"));
    CHECK(hasLabel(s, "intensity_label", LBL("5強", "5-upper")));
    CHECK(hasField(s,"\"prefecture\":13"));
    CHECK(hasLabel(s, "prefecture_label", LBL("東京都", "Tokyo Metropolis")));
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
    CHECK(hasLabel(s, "disaster_category_label", LBL("震源", "Hypocenter")));
    CHECK(has(s, "\"data\":{"));
    CHECK(hasField(s, "\"depth\":40"));
    CHECK(hasField(s, "\"magnitude\":64"));
    CHECK(hasLabel(s, "depth_label", LBL("40km", "40 km")));
    CHECK(hasLabel(s, "magnitude_label", LBL("6.4", "6.4")));
    CHECK(hasField(s, "\"epicenter\":791"));
    CHECK(hasLabel(s, "epicenter_label", LBL("日向灘", "Hyuganada Sea")));
    CHECK(has(s, "\"notifications\":["));
    CHECK(has(s, std::string("\"code\":201,\"label\":\"") + LBL("強い揺れに警戒してください。", "Watch out for strong tremors.") + "\""));
}

#if (AZARAC_LANG_JA) || (AZARAC_LANG_EN)
TEST_CASE("JSON Serialization: hypocenter quantity labels expose bounds and sentinels") {
    Message m{};
    initMt43As(m, 2);
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);
    HypocenterData* hypo = mt43->getHypocenter();
    REQUIRE(hypo != nullptr);
    hypo->epicenter = 791;   // 既存テストと同じ値。epicenter_label を非空に保つ

    // depth は EEW と同じ depth_of_hypocenter テーブル。実ガードは (EEW || HYPOCENTER || NW_PAC_TSUNAMI) なので、EEW=0 構成でも
    // Hypocenter 側で境界とセンチネルを検証できる。
    hypo->depth = 501;       // 500km より深い
    hypo->magnitude = 126;   // 不明(8.0より大きい) — Hypocenter 専用の境界マーカー
    StringPrint sp1;
    internal::JsonSerializer::serialize(m, sp1);
    CHECK(hasField(sp1.str(), "\"depth\":501"));
    CHECK(hasLabel(sp1.str(), "depth_label", LBL("500kmより深い", "Deeper than 500 km")));
    CHECK(hasField(sp1.str(), "\"magnitude\":126"));
    CHECK(hasLabel(sp1.str(), "magnitude_label", LBL("不明(8.0より大きい)", "Unknown (Over 8.0)")));

    hypo->depth = 511;       // 不明
    hypo->magnitude = 127;   // 不明
    StringPrint sp2;
    internal::JsonSerializer::serialize(m, sp2);
    CHECK(hasField(sp2.str(), "\"depth\":511"));
    CHECK(hasLabel(sp2.str(), "depth_label", LBL("不明", "Unknown")));
    CHECK(hasField(sp2.str(), "\"magnitude\":127"));
    CHECK(hasLabel(sp2.str(), "magnitude_label", LBL("不明", "Unknown")));
}
#endif // (AZARAC_LANG_JA) || (AZARAC_LANG_EN)
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
    CHECK(hasLabel(s, "disaster_category_label", LBL("津波", "Tsunami")));
    CHECK(has(s, "\"data\":{"));
    CHECK(hasField(s, "\"warning_code\":3"));
    CHECK(hasLabel(s, "warning_code_label", LBL("津波警報", "Tsunami Warning")));
    CHECK(has(s, "\"entries\":["));
    CHECK(hasField(s, "\"region\":65"));
    CHECK(hasField(s, "\"height\":4"));
    CHECK(hasLabel(s, "height_label", LBL("5m", "5 m")));
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
    CHECK(hasLabel(s, "disaster_category_label", LBL("南海トラフ地震", "Nankai Trough Earthquake")));
    CHECK(has(s, "\"data\":{"));
    CHECK(hasField(s, "\"info_code\":1"));
    CHECK(hasField(s, "\"info_code_label\":\"調査中A（監視領域内でマグニチュード6.8以上の地震が発生したことにより、臨時に「南海トラフ沿いの地震に関する評価検討会」を開催）\""));
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
    CHECK(hasLabel(s, "disaster_category_label", LBL("北西太平洋津波", "Northwest Pacific Tsunami")));
    CHECK(has(s, "\"data\":{"));
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
    vol->ambiguity = 5;   // 近似時刻（日）— 表に存在するコードで引く
    vol->lg_count = 1;
    vol->local_govs[0] = 4600000;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"disaster_category\":8"));
    // S1-lookup regression: dc=8 は火山（修正前は array 戦略で降灰にズレていた）
    CHECK(hasLabel(s, "disaster_category_label", LBL("火山", "Volcano")));
    CHECK(has(s, "\"data\":{"));
    // 言語非依存表（JA 兄弟なし）なので _label_en は出ず、常に同じ英語ラベル
    CHECK(hasField(s, "\"ambiguity\":5"));
    CHECK(hasField(s, "\"ambiguity_label\":\"Approximate time (day)\""));
    CHECK_FALSE(has(s, "ambiguity_label_en"));
    CHECK(hasField(s, "\"warning_code\":52"));
    CHECK(hasLabel(s, "warning_code_label", LBL("噴火", "Volcanic eruptions")));
    CHECK(hasField(s, "\"volcano_name\":503"));
    CHECK(hasLabel(s, "volcano_name_label", LBL("阿蘇山", "Asosan")));
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
    CHECK(hasLabel(s, "disaster_category_label", LBL("降灰", "Ash Fall")));
    CHECK(has(s, "\"data\":{"));
    CHECK(hasField(s, "\"warning_type\":1"));
    CHECK(hasLabel(s, "warning_type_label", LBL("速報", "Preliminary")));
    CHECK(hasField(s, "\"volcano_name\":503"));
    CHECK(hasLabel(s, "volcano_name_label", LBL("阿蘇山", "Asosan")));
    CHECK(has(s, "\"entries\":["));
    CHECK(hasField(s, "\"arrival_time_code\":3"));
    CHECK(hasLabel(s, "arrival_time_label", LBL("3時間", "3 hours")));
    CHECK(s.find("arrival_hour") == std::string::npos);
    CHECK(has(s, std::string("\"warning_code\":2,\"warning_code_label\":\"") + LBL("やや多量の降灰", "Moderate ash fall") + "\""));
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
    CHECK(hasLabel(s, "disaster_category_label", LBL("気象", "Weather")));
    CHECK(has(s, "\"data\":{"));
    CHECK(hasField(s, "\"warning_state\":1"));
    CHECK(hasLabel(s, "warning_state_label", LBL("発表", "Announcement")));
    CHECK(has(s, "\"entries\":["));
    CHECK(hasField(s, "\"sub_category\":2"));
    CHECK(hasLabel(s, "sub_category_label", LBL("大雨特別警報", "Heavy Rain Emergency Warning")));
    CHECK(hasField(s, "\"region\":11000"));
    CHECK(hasLabel(s, "region_label", LBL("宗谷地方", "Soya Region")));
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
    CHECK(hasLabel(s, "disaster_category_label", LBL("洪水", "Flood")));
    CHECK(has(s, "\"data\":{"));
    CHECK(has(s, "\"entries\":["));
    CHECK(hasField(s, "\"warning_level\":3"));
    CHECK(hasLabel(s, "warning_level_label", LBL("氾濫危険情報", "Information on potential flood hazards")));
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
    typh->elapsed = 24;
    typh->coords.lat_ns = 0;
    typh->coords.lat_deg = 25;
    typh->coords.lon_ew = 0;
    typh->coords.lon_deg = 130;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"disaster_category\":12"));
    CHECK(hasLabel(s, "disaster_category_label", LBL("台風", "Typhoon")));
    CHECK(has(s, "\"data\":{"));
    CHECK(hasField(s, "\"number\":21"));
    CHECK(hasLabel(s, "number_label", LBL("21号", "No. 21")));
    CHECK(hasField(s, "\"scale\":3"));
    CHECK(hasField(s, "\"intensity\":2"));
    CHECK(hasLabel(s, "intensity_label", LBL("非常に強い", "Very Strong")));
    CHECK(hasField(s, "\"pressure\":980"));
    CHECK(hasLabel(s, "pressure_label", LBL("980hPa", "980 hPa")));
    CHECK(hasField(s, "\"max_wind\":35"));
    CHECK(hasLabel(s, "max_wind_label", LBL("35m/s", "35 m/s")));
    CHECK(hasField(s, "\"max_gust\":50"));
    CHECK(hasLabel(s, "max_gust_label", LBL("50m/s", "50 m/s")));
    CHECK(hasField(s, "\"elapsed\":24"));
    CHECK(hasLabel(s, "elapsed_label", LBL("24時間後", "24 hours ahead")));

#if (AZARAC_LANG_JA) || (AZARAC_LANG_EN)
    // max_gust 0 は「突風なし/不明」のセンチネル。生コード 0 では意味が取れない
    typh->max_gust = 0;
    StringPrint sp0;
    internal::JsonSerializer::serialize(m, sp0);
    CHECK(hasField(sp0.str(), "\"max_gust\":0"));
    CHECK(hasLabel(sp0.str(), "max_gust_label", LBL("不明", "Unknown")));
#endif
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
    CHECK(hasLabel(s, "disaster_category_label", LBL("海上", "Marine")));
    CHECK(has(s, "\"data\":{"));
    CHECK(has(s, "\"entries\":["));
    CHECK(hasField(s, "\"warning_code\":19"));
    CHECK(hasField(s, "\"region\":100"));
    // 疎キー negative: marine warning code 19 は未定義→null, 20 → 海上風警報
    CHECK(hasField(s, "\"warning_code\":19,\"warning_code_label\":null"));
    CHECK(has(s, std::string("\"warning_code\":20,\"warning_code_label\":\"") + LBL("海上風警報", "Wind Warning") + "\""));
}
#endif // AZARAC_ENABLE_MARINE

// JSON 構造検証
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
        // Missing-comma guard: a closing bracket/brace must not be immediately followed by a key's opening quote (would be "]\"key\"" / "}\"key\"").
        // Regression for the JAlert prefecture_labels/city_labels comma bug.
        for (size_t i = 1; i < s.size(); ++i) {
            if ((s[i-1] == ']' || s[i-1] == '}') && s[i] == '"') {
                const std::string msg = "missing comma after closing bracket at idx "
                                        + std::to_string(i) + " json=" + s;
                FAIL(msg.c_str());
            }
        }
        // Double-comma guard: a field separator must not be doubled (",,").
        // Catches a field emitted with a trailing comma before a closing brace that is itself followed by another comma.
        for (size_t i = 1; i < s.size(); ++i) {
            if (s[i-1] == ',' && s[i] == ',') {
                const std::string msg = "double comma at idx "
                                        + std::to_string(i) + " json=" + s;
                FAIL(msg.c_str());
            }
        }
        // Trailing-comma guard: a comma must not precede a closing brace/bracket (",}" / ",]"). JSON forbids trailing commas in objects/arrays. Catches a field emitted with last=false immediately before its closing brace.
        for (size_t i = 1; i < s.size(); ++i) {
            if (s[i-1] == ',' && (s[i] == '}' || s[i] == ']')) {
                const std::string msg = "trailing comma before closing at idx "
                                        + std::to_string(i) + " json=" + s;
                FAIL(msg.c_str());
            }
        }
    };

    SUBCASE("Disaster Categories 1-14") {
        // dc=7 は未割り当てのため除外
        for (uint8_t dc : {1,2,3,4,5,6,8,9,10,11,12,14}) {
            Message m{}; initMt43(m, dc);
            test_balanced(m);
        }
    }
#if (AZARAC_ENABLE_DCX_CAMF)
    SUBCASE("MT=44") {
        Message m{}; initMt44(m);
        test_balanced(m);
    }
#endif
#if (AZARAC_ENABLE_DCX_CAMF)
    SUBCASE("MT=44 JAlert prefecture mode") {
        Message m{}; initMt44(m);
        Mt44Data* mt44 = m.getMt44();
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
        test_balanced(m);
    }
    SUBCASE("MT=44 JAlert city mode") {
        Message m{}; initMt44(m);
        Mt44Data* mt44 = m.getMt44();
        mt44->service_kind = Mt44ServiceKind::JAlert;
        mt44->is_null_message = false;
        mt44->ex_kind = ExtendedKind::JAlert;
        mt44->camf.a1 = 1; mt44->camf.a2 = 111; mt44->camf.a3 = 1;
        mt44->camf.a4 = 10; mt44->camf.a5 = 3;
        mt44->ex_jalert.ex8 = 1;
        mt44->ex_jalert.ex9 = 7;
        mt44->ex_jalert.vn = 1;
        mt44->mt44_decoded.jalert_prefecture_mode = false;
        mt44->mt44_decoded.city_code_count = 3;
        mt44->mt44_decoded.city_codes[0] = 1101;
        mt44->mt44_decoded.city_codes[1] = 1102;
        mt44->mt44_decoded.city_codes[2] = 47101;
        test_balanced(m);
    }
#endif // AZARAC_ENABLE_DCX_CAMF
#if (AZARAC_ENABLE_DCX_CAMF)
    SUBCASE("MT=44 JAlert real vector (47 prefectures)") {
        // 実データ: J-Alert Missile Attack, 全47都道府県 (test_azarashi_dcx.cpp と同一ベクタ) decodeNmea は DCX デコードを呼ぶため AZARAC_ENABLE_DCX_CAMF 依存。
        // ガードしないと macro-off (DCX_CAMF=0) で decodeNmea が false になり CI が落ちる。
        Message msg{};
        REQUIRE(decodeNmea(
            "$QZQSM,55,53B0840DE31188FC208600000000000000001FFFFFFFFFFFC00000120738628*00",
            msg));
        CHECK(msg.msg_type == 44);
        CHECK(msg.payload_type == MsgPayloadType::Mt44);
        const Mt44Data* mt44 = msg.getMt44();
        REQUIRE(mt44 != nullptr);
        CHECK(mt44->service_kind == Mt44ServiceKind::JAlert);
        // 実データ経路でシリアライザが有効JSONを出すこと（カンマ/ブラケット整合）
        test_balanced(msg);
    }
#endif // AZARAC_ENABLE_DCX_CAMF
}

// JSON エスケープ文字テスト (json_serialization.md #1)

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

// MT=43 report_time JSON 出力テスト (json_serialization.md #2)

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

// MT=44 onset_time JSON 出力テスト (json_serialization.md #3)

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

// MT=44 sd_sdmt=1 テスト (json_serialization.md #4)

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

// MT=44 a6=0 / a8=0 / a9=0 / a10=0 / a11=0 テスト (json_serialization.md #5)

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

// a11=0 は「定義済みの空ラベル」であって欠落ではない。AVR と非AVRは同じ結果でなければならない: 空の JSON 文字列であって null ではない。
// v2 の 3 値規則では `""` = 表に当たったがラベルが空、`null` = 表に無い / 表が無い。区別するのは test/internal/test_definition_labels.cpp の lookup レベルの検査。ここは JSON 出力での回帰ガード。
TEST_CASE("JSON Serialization: a11 empty label is present, not absent") {
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
    mt44->camf.a6 = 1; mt44->camf.a7 = 1; mt44->camf.a8 = 1;
    mt44->camf.a9 = 1;   // Country/region library (A2=111) -> a11_japanese_library_ja / _en
    mt44->camf.a10 = 1;
    mt44->camf.a11 = 0;  // JA: "指示なし" / EN: "No instruction" (azarashi 0.17.1)
    mt44->ex_lalert_local.ex1 = 1100;
    mt44->ex_lalert_local.vn = 1;
    mt44->sd.sdmt = 0; mt44->sd.sdm = 0x1FF;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    // 定義済みのラベルは "null" にならない（欠落と空文字列の区別）
    CHECK(hasField(s, std::string("\"a11_guidance_label\":\"") + LBL("指示なし", "No instruction") + "\""));
    CHECK(s.find("\"a11_guidance_label\":null") == std::string::npos);
    // 日本の表は 10bit を鍵にした結合表なので List B は無い
    CHECK(hasField(s, "\"a11_guidance_list_b_label\":null"));
}

// IS-QZSS-DCX-004 §4.2.3.9 Table 4.2-12 / EWSS CAMF v1.1 §3.5.3, §11: A9=0 は
// International library。A11 は List A 5bit (a11 >> 5) と List B 5bit (a11 & 0x1F) の2コードで、それぞれ別の表を引く。
TEST_CASE("JSON Serialization: A9=0 uses the international library") {
    auto jsonFor = [](uint16_t a11) {
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
        mt44->camf.a6 = 1; mt44->camf.a7 = 1; mt44->camf.a8 = 1;
        mt44->camf.a9 = 0;   // International library
        mt44->camf.a10 = 1;
        mt44->camf.a11 = a11;
        mt44->ex_lalert_local.ex1 = 1100;
        mt44->ex_lalert_local.vn = 1;
        mt44->sd.sdmt = 0; mt44->sd.sdm = 0x1FF;

        StringPrint sp;
        internal::JsonSerializer::serialize(m, sp);
        return sp.str();
    };

    const char* const listA1 =
        "You are in the danger zone, leave the area immediately. "
        "Listen to radio or media for directions and information.";
    const char* const listB1 =
        "Check with the weather services and local authorities for additional information";

    // a11=1 → List A=0 / List B=1。国際表のコード 0 は List A / List B とも定義済みの空ラベル（null ではない）。
    {
        const std::string s = jsonFor(1);
        CHECK(hasField(s, "\"a11_guidance_label\":\"\""));
        CHECK(hasField(s, std::string("\"a11_guidance_list_b_label\":\"") + listB1 + "\""));
        CHECK_FALSE(has(s, "a11_guidance_label_en"));
        CHECK_FALSE(has(s, "a11_guidance_list_b_label_en"));
    }
    // a11=33 → List A=1 / List B=1。List B を List A として出していないことを同一 JSON の 2 値で検出する。
    {
        const std::string s = jsonFor(33);
        CHECK(hasField(s, std::string("\"a11_guidance_label\":\"") + listA1 + "\""));
        CHECK(hasField(s, std::string("\"a11_guidance_list_b_label\":\"") + listB1 + "\""));
    }
    // a11=61 → List A=1 / List B=29（List B の 29/30 は欠落 = 定義なし）
    {
        const std::string s = jsonFor(61);
        CHECK(hasField(s, std::string("\"a11_guidance_label\":\"") + listA1 + "\""));
        CHECK(hasField(s, "\"a11_guidance_list_b_label\":null"));
    }
}

TEST_CASE("JSON Serialization: A9=0 code 0 is an empty international label") {
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
    mt44->camf.a6 = 1; mt44->camf.a7 = 1; mt44->camf.a8 = 1;
    mt44->camf.a9 = 0;
    mt44->camf.a10 = 1;
    mt44->camf.a11 = 0;
    mt44->ex_lalert_local.ex1 = 1100;
    mt44->ex_lalert_local.vn = 1;
    mt44->sd.sdmt = 0; mt44->sd.sdm = 0x1FF;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    CHECK(hasField(s, "\"a11_guidance_label\":\"\""));
    CHECK(hasField(s, "\"a11_guidance_list_b_label\":\"\""));
    CHECK(s.find("\"a11_guidance_label\":null") == std::string::npos);
}

// A9=1 は国/地域 library だが、表を持っているのは日本のみ（A2=111）。
TEST_CASE("JSON Serialization: A9=1 outside Japan has no country library") {
    Message m{};
    m.svid = 193; m.crc24 = 0xABCDEF;
    initMt44(m);
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);

    mt44->service_kind = Mt44ServiceKind::OutsideJapan;
    mt44->is_null_message = false;
    mt44->ex_kind = ExtendedKind::OutsideJapan;
    mt44->camf.a1 = 1; mt44->camf.a2 = 71; mt44->camf.a3 = 1;
    mt44->camf.a4 = 10; mt44->camf.a5 = 3;
    mt44->camf.a6 = 1; mt44->camf.a7 = 1; mt44->camf.a8 = 1;
    mt44->camf.a9 = 1;   // Country/region library
    mt44->camf.a10 = 1;
    // 1 は International library では「You are in the danger zone…」。A2≠111 で表を引いていないこと（空になること）を区別できるよう、範囲内のコードを使う。
    mt44->camf.a11 = 1;
    mt44->ex_lalert_local.ex1 = 1100;
    mt44->ex_lalert_local.vn = 1;
    mt44->sd.sdmt = 0; mt44->sd.sdm = 0x1FF;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const auto& s = sp.str();

    // 表が無い（A9=1 かつ A2≠111）ので v2 はラベル無し（null）
    CHECK(hasField(s, "\"a11_guidance_label\":null"));
    CHECK(hasField(s, "\"a11_guidance_list_b_label\":null"));
    CHECK_FALSE(has(s, "You are in the danger zone"));
}

// 実データ (J-Alert, a2=111 / a9=1 / a10=0 / a11=136) で国/地域 library の日本語ラベルが出る。
TEST_CASE("JSON Serialization: real J-Alert resolves the A11 country library label") {
    Message msg{};
    REQUIRE(decodeNmea(
        "$QZQSM,55,53B0840DE3E208FD208800000000000000001FFFFFFFFFFFC0000011BFAF780*79", msg));
    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->camf.a2 == 111);
    CHECK(mt44->camf.a9 == 1);
    CHECK(mt44->camf.a11 == 136);

    StringPrint sp;
    internal::JsonSerializer::serialize(msg, sp);
    const auto& s = sp.str();
    CHECK(hasLabel(s, "a11_guidance_label",
                   LBL("これは、Jアラートのテストです。",
                       "This is a test message for J-Alert.")));
    CHECK(hasField(s, "\"a11_guidance_list_b_label\":null"));
#if (AZARAC_LANG_JA) && (AZARAC_LANG_EN)
    CHECK(hasLabel(s, "a11_guidance_label_en", "This is a test message for J-Alert."));
#endif
}
#endif // AZARAC_ENABLE_DCX_CAMF

// MT=43 event_time 未解決 (report_unix=0) テスト (json_serialization.md #6)

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

    CHECK(hasField(s, "\"unix\":null"));
}
#endif // AZARAC_ENABLE_EEW

// Nankai 集約後 text_utf8 出力テスト (integration_e2e.md #2)

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

// JsonWriter 個別関数テスト

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

// writeDouble エッジケーステスト
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

// v2 スキーマ (schema_version: 2)

TEST_CASE("writeOptStr: nullopt は null、空文字列は \"\"") {
    StringPrint sp;
    internal::writeOptStr(sp, std::nullopt);
    CHECK(sp.str() == "null");

    StringPrint sp2;
    internal::writeOptStr(sp2, std::optional<std::string_view>(std::string_view{"", 0}));
    CHECK(sp2.str() == "\"\"");
}

TEST_CASE("JSON v2: header and data layout") {
#if (AZARAC_ENABLE_TSUNAMI)
    // MT43: ルートに DCR の報告ヘッダ、本文は data
    {
        Message m{};
        m.svid = 186;
        m.crc24 = 0x00A6C5B8;
        initMt43As(m, 5);
        Mt43Data* mt43 = m.getMt43();
        REQUIRE(mt43 != nullptr);
        mt43->version = 1;

        StringPrint sp;
        internal::JsonSerializer::serialize(m, sp);
        const auto& s = sp.str();

        CHECK(s.rfind("{\"schema_version\":2,\"svid\":186,\"msg_type\":43,\"crc24\":\"0x00A6C5B8\",", 0) == 0);
        CHECK(has(s, "\"data\":{\"warning_code\""));
        // メタ情報は data より前（ルート）にある
        CHECK(s.find("\"version\":1") < s.find("\"data\":{"));
        CHECK(s.find("\"report_time\"") < s.find("\"data\":{"));
        CHECK(s.find("\"detail\"") == std::string::npos);
        CHECK(s.find("svid_label") == std::string::npos);
        CHECK(s.find("msg_type_label") == std::string::npos);
    }
#endif // AZARAC_ENABLE_TSUNAMI
#if (AZARAC_ENABLE_DCX_CAMF)
    // MT44: ルートは svid/msg_type/crc24 と data だけ
    {
        Message m{};
        m.svid = 193;
        m.crc24 = 0x00074DAD;
        initMt44(m);
        Mt44Data* mt44 = m.getMt44();
        REQUIRE(mt44 != nullptr);
        mt44->service_kind = Mt44ServiceKind::JAlert;
        mt44->ex_kind = ExtendedKind::JAlert;
        mt44->ex_jalert.ex8 = 0;
        mt44->ex_jalert.vn = 1;
        mt44->sd.sdmt = 0;
        mt44->sd.sdm = 0;
        mt44->mt44_decoded.jalert_prefecture_mode = true;
        mt44->mt44_decoded.prefecture_count = 1;
        mt44->mt44_decoded.prefecture_positions[0] = 47;

        StringPrint sp;
        internal::JsonSerializer::serialize(m, sp);
        const auto& s = sp.str();

        CHECK(s.rfind("{\"schema_version\":2,\"svid\":193,\"msg_type\":44,\"crc24\":\"0x00074DAD\",\"data\":{\"dcx_type\":\"J_ALERT\",", 0) == 0);
        // data の中身: dcx_type が先頭、sd_sdmt/sd_sdm が最後
        CHECK(s.find("\"sd_sdmt\"") > s.find("\"data\":{"));
        CHECK(s.find("\"sd_sdm\"") > s.find("\"data\":{"));
        CHECK(s.rfind("\"sd_sdmt\":0,\"sd_sdm\":0}") != std::string::npos);
        // ルート直下に dcx_type / sd_sdmt は無い（最初の dcx_type は data の直後）
        const size_t dataPos = s.find("\"data\":{");
        CHECK(dataPos != std::string::npos);
        CHECK(s.compare(dataPos + 8, 11, "\"dcx_type\":") == 0);
        CHECK(s.find("\"dcx_type\"") == dataPos + 8);
        CHECK(has(s, "\"data\":{"));
        CHECK(s.find("dcx_type_label") == std::string::npos);
    }
#endif // AZARAC_ENABLE_DCX_CAMF
}

#if (AZARAC_ENABLE_TSUNAMI) || (AZARAC_ENABLE_NW_PAC_TSUNAMI)
TEST_CASE("JSON v2: arrival sentinel status") {
#if (AZARAC_ENABLE_TSUNAMI)
    auto tsunamiJson = [](uint16_t raw) {
        Message m{};
        m.svid = 186;
        initMt43As(m, 5);
        TsunamiData* t = m.getMt43()->getTsunami();
        t->count = 1;
        t->entries[0].arrival_time_raw = raw;
        t->entries[0].height_code = 4;
        t->entries[0].region_code = 65;
        StringPrint sp;
        internal::JsonSerializer::serialize(m, sp);
        return sp.str();
    };
#endif // AZARAC_ENABLE_TSUNAMI
#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)
    auto nwPacJson = [](uint16_t raw) {
        Message m{};
        m.svid = 186;
        initMt43As(m, 6);
        NwPacTsunamiData* t = m.getMt43()->getNwPac();
        t->count = 1;
        t->entries[0].arrival_time_raw = raw;
        t->entries[0].height_code = 3;
        t->entries[0].region_code = 1;
        StringPrint sp;
        internal::JsonSerializer::serialize(m, sp);
        return sp.str();
    };
#endif // AZARAC_ENABLE_NW_PAC_TSUNAMI

#if (AZARAC_ENABLE_TSUNAMI)
    // cat 5: 31:63 推定
    {
        const std::string s = tsunamiJson(2047);
        CHECK(hasField(s, "\"arrival_time_raw\":2047"));
        CHECK(has(s, "\"arrival_status\":\"arrival_estimated\""));
        CHECK(has(s, "\"arrival_time\":null"));
        CHECK(s.find("arrival_day_offset") == std::string::npos);
    }
    // cat 5: day0/30:62 = 情報なし（範囲外チェックを先に置くと到達不能になる）
    {
        const std::string s = tsunamiJson(1982);
        CHECK(has(s, "\"arrival_status\":\"no_information\""));
        CHECK(has(s, "\"arrival_time\":null"));
    }
    // cat 5: raw=0 は解決不能（デコーダは空を返す）
    {
        const std::string s = tsunamiJson(0);
        CHECK(has(s, "\"arrival_status\":\"unrecognized_code\""));
        CHECK(has(s, "\"arrival_time\":null"));
    }
    // cat 5: 通常時刻（hour 7 min 40）は status 無し、未解決なら unix が null
    {
        Message m{};
        m.svid = 186;
        initMt43As(m, 5);
        TsunamiData* t = m.getMt43()->getTsunami();
        t->count = 1;
        t->entries[0].arrival_time_raw = (7u << 6) | 40u;
        t->entries[0].arrival_time.month = 0;
        t->entries[0].arrival_time.day = 0;
        t->entries[0].arrival_time.hour = 7;
        t->entries[0].arrival_time.minute = 40;
        t->entries[0].arrival_time.unix_time = 0;   // 未解決
        t->entries[0].height_code = 4;
        t->entries[0].region_code = 65;
        StringPrint sp;
        internal::JsonSerializer::serialize(m, sp);
        const std::string s = sp.str();
        CHECK(s.find("\"arrival_status\"") == std::string::npos);
        CHECK(has(s, "\"arrival_time\":{\"month\":0,\"day\":0,\"hour\":7,\"min\":40,\"unix\":null}"));
    }
#endif // AZARAC_ENABLE_TSUNAMI
#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)
    // cat 6: 31:63 は到着済み or 不明
    {
        const std::string s = nwPacJson(2047);
        CHECK(has(s, "\"arrival_status\":\"arrived_or_unknown\""));
        CHECK(has(s, "\"arrival_time\":null"));
    }
    // cat 6: 1982 は no_information ではなく範囲外
    {
        const std::string s = nwPacJson(1982);
        CHECK(has(s, "\"arrival_status\":\"unrecognized_code\""));
    }
#endif // AZARAC_ENABLE_NW_PAC_TSUNAMI
}
#endif // (AZARAC_ENABLE_TSUNAMI) || (AZARAC_ENABLE_NW_PAC_TSUNAMI)

TEST_CASE("JSON v2: unix is null only when unresolved") {
    Message m{};
    initMt43As(m, 2);
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);

    mt43->event_time.unix_time = 1704067200;
    {
        StringPrint sp;
        internal::JsonSerializer::serialize(m, sp);
        CHECK(hasField(sp.str(), "\"unix\":1704067200"));
    }
    mt43->event_time.unix_time = 0;
    {
        StringPrint sp;
        internal::JsonSerializer::serialize(m, sp);
        CHECK(hasField(sp.str(), "\"unix\":null"));
    }
}

#if (AZARAC_ENABLE_DCX_CAMF)
TEST_CASE("JSON v2: unknown label is null, empty label is a string") {
    auto labelJson = [](uint16_t a11, uint16_t a2, uint8_t a9) {
        Message m{};
        m.svid = 193;
        initMt44(m);
        Mt44Data* mt44 = m.getMt44();
        mt44->service_kind = Mt44ServiceKind::LAlert;
        mt44->ex_kind = ExtendedKind::LAlertOrLocal;
        mt44->camf.a1 = 1; mt44->camf.a2 = a2; mt44->camf.a3 = 1;
        mt44->camf.a4 = 10; mt44->camf.a5 = 3;
        mt44->camf.a9 = a9; mt44->camf.a11 = a11;
        StringPrint sp;
        internal::JsonSerializer::serialize(m, sp);
        return sp.str();
    };

    // A9=0/A11=0: 国際表の定義済み空ラベル
    {
        const std::string s = labelJson(0, 111, 0);
        CHECK(hasField(s, std::string("\"a11_guidance_label\":\"") + LBL("", "") + "\""));
    }
    // A9=0/A11=61: List A=1（定義あり）/ List B=29（欠落 → null）
    {
        const std::string s = labelJson(61, 111, 0);
        CHECK(hasField(s, std::string("\"a11_guidance_label\":\"")
            + "You are in the danger zone, leave the area immediately. "
              "Listen to radio or media for directions and information." + "\""));
        CHECK(hasField(s, "\"a11_guidance_list_b_label\":null"));
    }
    // A9=1/A2=71: 表そのものが無い
    {
        const std::string s = labelJson(1, 71, 1);
        CHECK(hasField(s, "\"a11_guidance_label\":null"));
    }
}
#endif // AZARAC_ENABLE_DCX_CAMF

#if (AZARAC_ENABLE_DCX_CAMF)
TEST_CASE("JSON v2: J-Alert objects") {
    auto jalertJson = [](bool prefectureMode) {
        Message m{};
        m.svid = 193;
        initMt44(m);
        Mt44Data* mt44 = m.getMt44();
        mt44->service_kind = Mt44ServiceKind::JAlert;
        mt44->ex_kind = ExtendedKind::JAlert;
        mt44->camf.a1 = 1; mt44->camf.a2 = 111; mt44->camf.a3 = 2;
        mt44->camf.a4 = 5; mt44->camf.a5 = 3;
        mt44->ex_jalert.ex8 = prefectureMode ? 0 : 1;
        mt44->ex_jalert.vn = 1;
        mt44->mt44_decoded.jalert_prefecture_mode = prefectureMode;
        if (prefectureMode) {
            mt44->mt44_decoded.prefecture_count = 1;
            mt44->mt44_decoded.prefecture_positions[0] = 47;
        } else {
            mt44->mt44_decoded.city_code_count = 1;
            mt44->mt44_decoded.city_codes[0] = 1101;
        }
        StringPrint sp;
        internal::JsonSerializer::serialize(m, sp);
        return sp.str();
    };

    {
        const std::string s = jalertJson(true);
        // position は JIS 都道府県コード（1 始まり）
        CHECK(has(s, std::string("\"prefectures\":[{\"position\":47,\"label\":\"")
                                 + LBL("沖縄県", "Okinawa Prefecture") + "\"}]"));
        CHECK(s.find("prefecture_labels") == std::string::npos);
        CHECK(s.find("prefecture_mode") == std::string::npos);
        CHECK(s.find("cities") == std::string::npos);
    }
    {
        const std::string s = jalertJson(false);
        CHECK(has(s, std::string("\"cities\":[{\"code\":1101,\"label\":\"")
                                 + LBL("札幌市中央区", "Chuo Ward, Sapporo City") + "\"}]"));
        CHECK(s.find("city_codes") == std::string::npos);
        CHECK(s.find("city_labels") == std::string::npos);
        CHECK(s.find("prefectures") == std::string::npos);
    }
}
#endif // AZARAC_ENABLE_DCX_CAMF
