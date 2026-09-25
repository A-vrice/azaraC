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

// ═══════════════════════════════════════════════════════════════════════════════
// 空ラベルは「存在する」— 欠落ではない
// ═══════════════════════════════════════════════════════════════════════════════

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
    auto en = def::qzss_dcx_camf_a11_japanese_library_en_lookup(0);
    REQUIRE(en.has_value());
    CHECK(en->size() == 0);
#endif

    // 欠落は欠落のまま（範囲チェック／検索外れであって len ヒューリスティックではない）
    auto oob = def::qzss_dcx_camf_c10_instruction_library_for_second_ellipse_lookup(250);
    CHECK_FALSE(oob.has_value());
    auto oob_arr = def::qzss_dcx_camf_a11_international_library_lookup(250);
    CHECK_FALSE(oob_arr.has_value());
}
#endif // AZARAC_ENABLE_DCX_CAMF

// ═══════════════════════════════════════════════════════════════════════════════
// const char* 化した表が内容を保っている（行・長さの取り違え検出）
// ═══════════════════════════════════════════════════════════════════════════════

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
