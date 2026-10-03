// test/internal/test_definition_labels.cpp — 定義テーブルのラベル参照テスト
//
// 4つのテーブルは id 0 を「定義済みの空文字列」として持つ。AVR と非AVRは
// 同じ値を返さなければならない: 存在する長さ0の view — nullopt ではない。
// AVR 側の `if (n == 0) return std::nullopt;` は「欠落」と「空」を混同して
// いたため、このテストはその回帰を検出する（pgm-stub ビルドで意味を持つ）。
//
// あわせて、非AVR のラベル実体を `const char*` 化した表が内容を失っていない
// ことを、各 strategy（array / binary_search / 手書き）で1件ずつ確認する。

#define ARDUINO 0
#include "../src/definition/_index.h"
#include "../test_helpers.h"
#include "doctest.h"

#include <cstring>
#include <string_view>

using namespace azaraC;

// 空ラベルは「存在する」— 欠落ではない

#if (AZARAC_ENABLE_DCX_CAMF)
TEST_CASE("Definition lookup: empty label is present, not absent") {
    // array strategy (BASE=0) — 行0 が空文字列
    auto intl = def::qzss_dcx_camf_a11_international_library_lookup(0);
    REQUIRE(intl.has_value());
    CHECK(intl->size() == 0);

    // binary_search — 表に id 0 が空文字列として存在する
    auto instr = def::qzss_dcx_camf_c10_instruction_library_for_second_ellipse_lookup(0);
    REQUIRE(instr.has_value());
    CHECK(instr->size() == 0);

#if (AZARAC_LANG_JA)
    auto ja = def::qzss_dcx_camf_a11_japanese_library_ja_lookup(0);
    REQUIRE(ja.has_value());
    CHECK(ja->size() == 0);
#endif
#if (AZARAC_LANG_EN)
    // azarashi 0.17 gave the English library a word for code 0 ("No
    // instruction"), so only the presence holds here, not emptiness.
    auto en = def::qzss_dcx_camf_a11_japanese_library_en_lookup(0);
    REQUIRE(en.has_value());
#endif

    // 欠落は欠落のまま（範囲チェック／検索外れであって len ヒューリスティックではない）
    auto oob = def::qzss_dcx_camf_c10_instruction_library_for_second_ellipse_lookup(250);
    CHECK_FALSE(oob.has_value());
    auto oob_arr = def::qzss_dcx_camf_a11_international_library_lookup(250);
    CHECK_FALSE(oob_arr.has_value());
}
#endif // AZARAC_ENABLE_DCX_CAMF

// const char* 化した表が内容を保っている（行・長さの取り違え検出）

#if (AZARAC_ENABLE_DCX_CAMF)
TEST_CASE("Definition lookup: label content survives const char* storage") {
    // binary_search（行は {id, const char*} の組）
    auto avoid = def::qzss_dcx_camf_c10_instruction_library_for_second_ellipse_lookup(8);
    REQUIRE(avoid.has_value());
    CHECK(*avoid == std::string_view("Avoid driving."));

    // array（BASE からの添字で引く）
    auto hokkaido = def::qzss_dcx_camf_a11_international_library_lookup(1);
    REQUIRE(hokkaido.has_value());
    CHECK(hokkaido->size() == 112u);
    CHECK(std::strncmp(hokkaido->data(), "You are in the danger zone", 26) == 0);

    // 手書きヘッダ（a3_provider_identifier：country=10, provider=1 → key 161）
    auto agency = def::qzss_dcx_camf_a3_provider_identifier_lookup(10, 1);
    REQUIRE(agency.has_value());
    CHECK(*agency == std::string_view("National Emergency Management Agency"));
}
#endif // AZARAC_ENABLE_DCX_CAMF

// 英語索引 — azarashi 0.17 が追加した _en 表を、3 戦略すべてで引く
//
// 索引そのものが正しいこと（strategy ごとの境界と欠落）と、値が英語である
// ことを確かめる。期待値は実ヘッダから実測したもの。

#if (AZARAC_LANG_EN)

// 表によって戻り値が 2 通りある（undefined を持つ表は optional、持たない表は
// const char*）。テストは両方を受ける。2 通りであること自体は既知の非対称で、
// ここで検証したい対象ではない。
static bool present(std::optional<std::string_view> v) { return v.has_value(); }
static bool present(const char* v) { return v != nullptr; }

// AVR のルックアップは共有スクラッチバッファを指す view を返す。保持するなら
// コピーが要る（次のルックアップが上書きする）。
static std::string label(std::optional<std::string_view> v) {
    return v ? std::string(v->data(), v->size()) : std::string();
}
static std::string label(const char* v) { return v ? std::string(v) : std::string(); }

static bool isAsciiLabel(std::string_view s) {
    if (s.empty()) return false;
    for (char c : s) {
        const bool ok = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
                        (c >= '0' && c <= '9') ||
                        c == ' ' || c == '.' || c == '-' || c == '/' ||
                        c == '(' || c == ')' || c == '\'' || c == ',' || c == '~';
        if (!ok) return false;
    }
    return true;
}

TEST_CASE("Definition lookup EN: array strategy indexes by BASE") {
    // AVR のルックアップは共有スクラッチバッファを返す。2 つ目の呼び出しが
    // 1 つ目の view を上書きするため、値を保持する場合は都度コピーする。
#if (AZARAC_ENABLE_SEISMIC || AZARAC_ENABLE_DCX_CAMF)
    const std::string first(def::qzss_dcr_jma_prefecture_en_lookup(1)->data(),
                            def::qzss_dcr_jma_prefecture_en_lookup(1)->size());
    CHECK(first == "Hokkaido Prefecture");                            // BASE

    const std::string last(def::qzss_dcr_jma_prefecture_en_lookup(47)->data(),
                           def::qzss_dcr_jma_prefecture_en_lookup(47)->size());
    CHECK(last == "Okinawa Prefecture");                              // BASE + SIZE - 1

    CHECK_FALSE(def::qzss_dcr_jma_prefecture_en_lookup(48).has_value());
#endif // SEISMIC || DCX_CAMF

#if (AZARAC_ENABLE_TYPHOON)
    // BASE=0 の array（境界が 0 側にある）
    auto zero = def::qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_en_lookup(0);
    REQUIRE(zero.has_value());
    CHECK(std::string(zero->data(), zero->size()) == "0 hours ahead");
    CHECK(def::qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_en_lookup(127).has_value());
    CHECK_FALSE(def::qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_en_lookup(128).has_value());

    // 添字のズレ検出: 隣り合う行が入れ替わっていないこと（都度コピーして比較）
    const std::string n1(def::qzss_dcr_jma_typhoon_number_en_lookup(1)->data(),
                         def::qzss_dcr_jma_typhoon_number_en_lookup(1)->size());
    const std::string n2(def::qzss_dcr_jma_typhoon_number_en_lookup(2)->data(),
                         def::qzss_dcr_jma_typhoon_number_en_lookup(2)->size());
    CHECK(n1 == "No. 1");
    CHECK(n2 == "No. 2");
    CHECK_FALSE(def::qzss_dcr_jma_typhoon_number_en_lookup(100).has_value());
#endif // TYPHOON
}

TEST_CASE("Definition lookup EN: sparse table skips the gaps") {
    // disaster_category は 7 と 13 を定義しない（仕様上未使用）。
    // この表は undefined を持たないため const char* を返す（nullptr = 欠落）。
    const char* dc5 = def::qzss_dcr_jma_disaster_category_en_lookup(5);
    REQUIRE(dc5 != nullptr);
    CHECK(label(dc5) == "Tsunami");

    const char* dc6 = def::qzss_dcr_jma_disaster_category_en_lookup(6);
    REQUIRE(dc6 != nullptr);
    CHECK(label(dc6) == "Northwest Pacific Tsunami");

    // 歯抜けの先も正しい（binary_search が 1 つずれていない）
    const char* dc14 = def::qzss_dcr_jma_disaster_category_en_lookup(14);
    REQUIRE(dc14 != nullptr);
    CHECK(label(dc14) == "Marine");

    CHECK(def::qzss_dcr_jma_disaster_category_en_lookup(7) == nullptr);
    CHECK(def::qzss_dcr_jma_disaster_category_en_lookup(13) == nullptr);

#if (AZARAC_ENABLE_VOLCANO || AZARAC_ENABLE_ASH_FALL)
    // 大きな疎キー（火山名）
    auto aso = def::qzss_dcr_jma_volcano_name_en_lookup(503);
    REQUIRE(aso.has_value());
    CHECK(*aso == std::string_view("Asosan"));
#endif // VOLCANO || ASH_FALL

#if (AZARAC_ENABLE_EEW)
    // 数値コードから作られる表（マグニチュード 72 = 7.2）
    auto mag = def::qzss_dcr_jma_eew_magnitude_en_lookup(72);
    REQUIRE(mag.has_value());
    CHECK(*mag == std::string_view("7.2"));
#endif // EEW
}

TEST_CASE("Definition lookup EN: switch strategy returns nullopt outside the cases") {
#if (AZARAC_ENABLE_MARINE)
    auto lifted = def::qzss_dcr_jma_marine_warning_code_en_lookup(0);
    REQUIRE(lifted.has_value());
    CHECK(*lifted == std::string_view("Marine Warning Lifted"));

    auto wind = def::qzss_dcr_jma_marine_warning_code_en_lookup(20);
    REQUIRE(wind.has_value());
    CHECK(*wind == std::string_view("Wind Warning"));

    auto other = def::qzss_dcr_jma_marine_warning_code_en_lookup(31);
    REQUIRE(other.has_value());
    CHECK(*other == std::string_view("Other Marine Warning"));

    // 19 は JA 表にも EN 表にも無い — 空文字列ではなく欠落
    CHECK_FALSE(def::qzss_dcr_jma_marine_warning_code_en_lookup(19).has_value());
#endif // MARINE

    // 0 番は「発表」であって「未定義」ではない
    auto issue = def::qzss_dcr_jma_information_type_en_lookup(0);
    REQUIRE(issue.has_value());
    CHECK(*issue == std::string_view("Issue"));
    CHECK_FALSE(def::qzss_dcr_jma_information_type_en_lookup(3).has_value());

    auto train = def::qzss_dcr_jma_report_classification_en_lookup(7);
    REQUIRE(train.has_value());
    CHECK(*train == std::string_view("Training/Test"));
}

TEST_CASE("Definition lookup EN: every label is English") {
    // 日本語のまま残っていないこと（生成元の取り違え検出）。
    // AVR は共有バッファを返すため、1 件ずつ引いて即座に判定する。
    CHECK(isAsciiLabel(label(def::qzss_dcr_jma_disaster_category_en_lookup(1))));
    CHECK(isAsciiLabel(label(def::qzss_dcr_jma_disaster_category_en_lookup(5))));
#if (AZARAC_ENABLE_SEISMIC || AZARAC_ENABLE_DCX_CAMF)
    CHECK(isAsciiLabel(label(def::qzss_dcr_jma_prefecture_en_lookup(13))));
#endif // SEISMIC || DCX_CAMF
#if (AZARAC_ENABLE_TSUNAMI)
    CHECK(isAsciiLabel(label(def::qzss_dcr_jma_tsunami_height_en_lookup(3))));
    CHECK(isAsciiLabel(label(def::qzss_dcr_jma_tsunami_height_en_lookup(15))));
#endif // TSUNAMI
#if (AZARAC_ENABLE_MARINE)
    CHECK(isAsciiLabel(label(def::qzss_dcr_jma_marine_warning_code_en_lookup(20))));
#endif // MARINE
#if (AZARAC_ENABLE_SEISMIC)
    CHECK(isAsciiLabel(label(def::qzss_dcr_jma_seismic_intensity_en_lookup(4))));
#endif // SEISMIC
#if (AZARAC_ENABLE_EEW || AZARAC_ENABLE_HYPOCENTER || AZARAC_ENABLE_NW_PAC_TSUNAMI)
    CHECK(isAsciiLabel(label(def::qzss_dcr_jma_depth_of_hypocenter_en_lookup(10))));
#endif
#if (AZARAC_ENABLE_VOLCANO || AZARAC_ENABLE_ASH_FALL)
    CHECK(isAsciiLabel(label(def::qzss_dcr_jma_volcano_name_en_lookup(503))));
#endif // VOLCANO || ASH_FALL
#if (AZARAC_ENABLE_EEW)
    CHECK(isAsciiLabel(label(def::qzss_dcr_jma_eew_forecast_region_en_lookup(1))));
#endif // EEW
#if (AZARAC_ENABLE_ASH_FALL)
    CHECK(isAsciiLabel(label(def::qzss_dcr_jma_ash_fall_warning_type_en_lookup(1))));
#endif // ASH_FALL
#if (AZARAC_ENABLE_WEATHER)
    CHECK(isAsciiLabel(label(def::qzss_dcr_jma_weather_forecast_region_en_lookup(11000))));
#endif // WEATHER
#if (AZARAC_ENABLE_TYPHOON)
    CHECK(isAsciiLabel(label(def::qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_en_lookup(24))));
#endif // TYPHOON
}

#endif // AZARAC_LANG_EN

// JA と EN は同じコード集合を引く（索引の一致）
//
// 片方だけにコードがあると、言語を切り替えただけでラベルが消える。

#if (AZARAC_LANG_JA) && (AZARAC_LANG_EN)

// 表によって戻り値が 2 通りある（undefined を持つ表は optional、持たない表は
// const char*）。どちらも「引けたか」に落とす（present は上で定義済み）。
template <typename JF, typename EF>
static void expectSameKeySet(JF ja, EF en, uint16_t hi, const char* name) {
    for (uint16_t k = 0; k <= hi; ++k) {
        const auto id = static_cast<uint8_t>(k);
        CHECK_MESSAGE(present(ja(id)) == present(en(id)),
                      name, " id=", static_cast<int>(id));
    }
}

TEST_CASE("Definition lookup: JA and EN cover the same codes") {
    expectSameKeySet(def::qzss_dcr_jma_disaster_category_lookup,
                     def::qzss_dcr_jma_disaster_category_en_lookup, 20, "disaster_category");
    expectSameKeySet(def::qzss_dcr_jma_prefecture_lookup,
                     def::qzss_dcr_jma_prefecture_en_lookup, 47, "prefecture");
    expectSameKeySet(def::qzss_dcr_jma_tsunami_height_lookup,
                     def::qzss_dcr_jma_tsunami_height_en_lookup, 20, "tsunami_height");
    expectSameKeySet(def::qzss_dcr_jma_marine_warning_code_lookup,
                     def::qzss_dcr_jma_marine_warning_code_en_lookup, 40, "marine_warning_code");
    expectSameKeySet(def::qzss_dcr_jma_report_classification_lookup,
                     def::qzss_dcr_jma_report_classification_en_lookup, 10, "report_classification");
    expectSameKeySet(def::qzss_dcr_jma_information_type_lookup,
                     def::qzss_dcr_jma_information_type_en_lookup, 5, "information_type");
    expectSameKeySet(def::qzss_dcr_jma_seismic_intensity_lower_limit_lookup,
                     def::qzss_dcr_jma_seismic_intensity_lower_limit_en_lookup, 20, "seis_lower");
    expectSameKeySet(def::qzss_dcr_jma_seismic_intensity_upper_limit_lookup,
                     def::qzss_dcr_jma_seismic_intensity_upper_limit_en_lookup, 20, "seis_upper");
    // id 0 は長周期地震動では「未使用」— JA/EN とも欠落で揃う
    CHECK_FALSE(present(def::qzss_dcr_jma_long_period_ground_motion_lower_limit_lookup(0)));
    CHECK_FALSE(present(def::qzss_dcr_jma_long_period_ground_motion_lower_limit_en_lookup(0)));
    expectSameKeySet(def::qzss_dcr_jma_long_period_ground_motion_lower_limit_lookup,
                     def::qzss_dcr_jma_long_period_ground_motion_lower_limit_en_lookup, 10, "lpgm_lower");
    expectSameKeySet(def::qzss_dcr_jma_long_period_ground_motion_upper_limit_lookup,
                     def::qzss_dcr_jma_long_period_ground_motion_upper_limit_en_lookup, 10, "lpgm_upper");
}

#endif // AZARAC_LANG_JA && AZARAC_LANG_EN

// 日本語版を持たない _en 表は言語非依存（AZARAC_LANG_EN に依存しない）
//
// これらは仕様自体が英語で、日本語版が存在しないため表の唯一の供給元になる。
// AZARAC_LANG_EN でガードすると、ライブラリ既定（JA=1 / EN=0）で nullopt
// スタブになり、北西太平洋津波のラベルが全滅する。ガードを外した状態を固定
// するため、このテストは AZARAC_LANG_EN でガードしない（両構成で走る）。
// 期待値は実ヘッダから実測。

#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)
TEST_CASE("Definition lookup: lone _en tables resolve regardless of AZARAC_LANG_EN") {
    auto potential = def::qzss_dcr_jma_tsunamigenic_potential_en_lookup(2);
    REQUIRE(potential.has_value());
    CHECK(*potential == std::string_view("There is a Possibility of a Destructive Regional Tsunami"));

    auto height = def::qzss_dcr_jma_northwest_pacific_tsunami_height_en_lookup(3);
    REQUIRE(height.has_value());
    CHECK(*height == std::string_view("3m~5m"));

    // binary_search 戦略（隣接行の取り違え検出）
    auto region = def::qzss_dcr_jma_coastal_region_en_lookup(1);
    REQUIRE(region.has_value());
    CHECK(*region == std::string_view("Ust-Kamchatsk (East Coasts of Kamchatka Peninsula)"));

    // 表外は欠落のまま
    CHECK_FALSE(def::qzss_dcr_jma_tsunamigenic_potential_en_lookup(5).has_value());
    CHECK_FALSE(def::qzss_dcr_jma_coastal_region_en_lookup(0).has_value());
}
#endif // AZARAC_ENABLE_NW_PAC_TSUNAMI

#if (AZARAC_ENABLE_VOLCANO || AZARAC_ENABLE_ASH_FALL)
TEST_CASE("Definition lookup: ambiguity_of_activity_time is language-independent") {
    auto none = def::qzss_dcr_jma_ambiguity_of_activity_time_en_lookup(0);
    REQUIRE(none.has_value());
    CHECK(*none == std::string_view("No ambiguity"));

    auto day = def::qzss_dcr_jma_ambiguity_of_activity_time_en_lookup(5);
    REQUIRE(day.has_value());
    CHECK(*day == std::string_view("Approximate time (day)"));

    CHECK_FALSE(def::qzss_dcr_jma_ambiguity_of_activity_time_en_lookup(8).has_value());
}
#endif // AZARAC_ENABLE_VOLCANO || AZARAC_ENABLE_ASH_FALL
