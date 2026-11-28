// シリアライザ出力が JSON として妥当か`_label_en` の併記は各ラベルサイトを 2 ペアで書き、`last` の受け渡しを誤ると `"a":1"b":2` のカンマ欠落や二重カンマを生む。既存テストの has() 部分一致では検出できないので、全カテゴリを 1 通ずつシリアライズし、 1. 構造が閉じている（括弧・引用符・カンマ）
//   2. 同じオブジェクト内でキーが重複していない
// を検証する（重複は数量フィールドに `_label` を足した際などに起こる）。

#define ARDUINO 0
#include "../src/azaraC.h"
#include "../src/internal/PrintShim.h"
#include "../src/json/JsonWriter.h"
#include "../test_helpers.h"
#include "JsonCheck.h"
#include "doctest.h"
#include <cstring>
#include <string>
#include <vector>

using namespace azaraC;

namespace {

// 全カテゴリを 1 通ずつ。initMt43As は test_json.cpp と同じ初期化。
std::vector<uint8_t> allCategories() {
    return {
#if (AZARAC_ENABLE_EEW)
        1,
#endif
#if (AZARAC_ENABLE_HYPOCENTER)
        2,
#endif
#if (AZARAC_ENABLE_SEISMIC)
        3,
#endif
#if (AZARAC_ENABLE_NANKAI)
        4,
#endif
#if (AZARAC_ENABLE_TSUNAMI)
        5,
#endif
#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)
        6,
#endif
#if (AZARAC_ENABLE_VOLCANO)
        8,
#endif
#if (AZARAC_ENABLE_ASH_FALL)
        9,
#endif
#if (AZARAC_ENABLE_WEATHER)
        10,
#endif
#if (AZARAC_ENABLE_FLOOD)
        11,
#endif
#if (AZARAC_ENABLE_TYPHOON)
        12,
#endif
#if (AZARAC_ENABLE_MARINE)
        14,
#endif
    };
}

void initMt43As(Message& m, uint8_t dc) {
    m.msg_type = 43;
    m.initPayload<Mt43Data>();
    Mt43Data* mt43 = m.getMt43();
    if (!mt43) return;
    mt43->disaster_category = dc;
    switch (dc) {
#if (AZARAC_ENABLE_EEW)
        case 1: mt43->initAs<EewData>(); break;
#endif
#if (AZARAC_ENABLE_HYPOCENTER)
        case 2: mt43->initAs<HypocenterData>(); break;
#endif
#if (AZARAC_ENABLE_SEISMIC)
        case 3: mt43->initAs<SeismicData>(); break;
#endif // AZARAC_ENABLE_SEISMIC
#if (AZARAC_ENABLE_NANKAI)
        case 4: mt43->initAs<NankaiData>(); break;
#endif
#if (AZARAC_ENABLE_TSUNAMI)
        case 5: mt43->initAs<TsunamiData>(); break;
#endif // AZARAC_ENABLE_TSUNAMI
#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)
        case 6: mt43->initAs<NwPacTsunamiData>(); break;
#endif // AZARAC_ENABLE_NW_PAC_TSUNAMI
#if (AZARAC_ENABLE_VOLCANO)
        case 8: mt43->initAs<VolcanoData>(); break;
#endif // AZARAC_ENABLE_VOLCANO
#if (AZARAC_ENABLE_ASH_FALL)
        case 9: mt43->initAs<AshFallData>(); break;
#endif // AZARAC_ENABLE_ASH_FALL
#if (AZARAC_ENABLE_WEATHER)
        case 10: mt43->initAs<WeatherData>(); break;
#endif // AZARAC_ENABLE_WEATHER
#if (AZARAC_ENABLE_FLOOD)
        case 11: mt43->initAs<FloodData>(); break;
#endif // AZARAC_ENABLE_FLOOD
#if (AZARAC_ENABLE_TYPHOON)
        case 12: mt43->initAs<TyphoonData>(); break;
#endif // AZARAC_ENABLE_TYPHOON
#if (AZARAC_ENABLE_MARINE)
        case 14: mt43->initAs<MarineData>(); break;
#endif // AZARAC_ENABLE_MARINE
        default: break;
    }
}

void checkWellFormed(const std::string& json, const char* what) {
    JsonCheck jc(json);
    // run() は状態を進めるので 1 回だけ呼ぶ（2 回呼ぶと必ず失敗する）。
    const bool ok = jc.run();
    if (!ok) {
        MESSAGE("JSON malformed [", what, "]: ", jc.error());
        MESSAGE("json=", json.substr(0, 400));
    }
    CHECK(ok);
}

} // namespace

// 各カテゴリを代表値付きで埋め、1 通ずつ JSON 妥当性を検査する（数量はセンチネルを入れてラベル分岐も通す）。
TEST_CASE("JSON well-formedness: every MT43 category") {
    for (uint8_t dc : allCategories()) {
        Message m{};
        m.svid = 186;
        initMt43As(m, dc);
        Mt43Data* mt43 = m.getMt43();
        REQUIRE(mt43 != nullptr);
        mt43->report_classification = 1;
        mt43->information_type = 0;
        mt43->version = 1;

        // 数量の境界・センチネル（表外はラベル空、501/511 は境界ラベル）
        switch (dc) {
#if (AZARAC_ENABLE_EEW)
            case 1: {
                EewData* e = mt43->getEew();
                if (e) { e->depth = 511; e->magnitude = 127; e->epicenter = 791; }
                break;
            }
#endif
#if (AZARAC_ENABLE_HYPOCENTER)
            case 2: {
                HypocenterData* h = mt43->getHypocenter();
                if (h) { h->depth = 501; h->magnitude = 101; }
                break;
            }
#endif
#if (AZARAC_ENABLE_TYPHOON)
            case 12: {
                TyphoonData* t = mt43->getTyphoon();
                if (t) { t->number = 21; t->pressure = 980; t->max_wind = 35; t->max_gust = 0; }
                break;
            }
#endif
#if (AZARAC_ENABLE_VOLCANO)
            case 8: {
                VolcanoData* v = mt43->getVolcano();
                if (v) { v->ambiguity = 7; v->warning_code = 52; v->volcano_name = 503; }
                break;
            }
#endif
            default: break;
        }

        StringPrint sp;
        internal::JsonSerializer::serialize(m, sp);
        checkWellFormed(sp.str(), "MT43");
    }
}

// 未対応カテゴリ（switch の default）は `"note":"unsupported_category"` を last=true で書く。
// last を落とすと `{"note":"unsupported_category",}` の末尾カンマになり JSON として不正になる。
// 既存の has() 部分一致テスト（test_json.cpp）はこの壊れ方を検出できない。
TEST_CASE("JSON well-formedness: unsupported MT43 category") {
    Message m{};
    m.svid = 186;
    m.msg_type = 43;
    m.initPayload<Mt43Data>();
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);
    mt43->report_classification = 1;
    mt43->information_type = 0;
    mt43->version = 1;
    mt43->disaster_category = 99;   // どのカテゴリにも一致しない

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const std::string& s = sp.str();
    CHECK(s.find("\"note\":\"unsupported_category\"") != std::string::npos);
    checkWellFormed(s, "MT43 unsupported category");
}

#if (AZARAC_ENABLE_WEATHER)
// 繰返しエントリ（entries[]）はラベルを 2〜3 本並べるため、`last` の受け渡し誤りが
// カンマ欠落として現れる。wellformed テストの既定 WeatherData は count=0 で
// ループ本体を一度も通らないので、ここで 2 件（表内・表外）を明示的に入れる。
TEST_CASE("JSON well-formedness: MT43 weather entries") {
    Message m{};
    m.svid = 186;
    m.msg_type = 43;
    m.initPayload<Mt43Data>();
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);
    mt43->report_classification = 1;
    mt43->information_type = 0;
    mt43->version = 1;
    mt43->disaster_category = 10;
    mt43->initAs<WeatherData>();
    WeatherData* wx = mt43->getWeather();
    REQUIRE(wx != nullptr);
    wx->warning_state = 1;
    wx->count = 2;
    wx->entries[0].sub_category = 1;      // 表内（ラベルあり）
    wx->entries[0].region_code = 47101;
    wx->entries[1].sub_category = 99;     // 表外（ラベル null）
    wx->entries[1].region_code = 1301;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const std::string& s = sp.str();
#if AZARAC_LANG_JA && AZARAC_LANG_EN
    // `_label_en` の併記は両言語 ON のときだけ（単一言語ビルドでは AZARAC_LABEL が 1 本になる）。
    CHECK(s.find("\"sub_category_label_en\"") != std::string::npos);
#endif
    checkWellFormed(s, "MT43 weather");
}
#endif // AZARAC_ENABLE_WEATHER

#if (AZARAC_ENABLE_NANKAI)
// 集約テキストは is_aggregated=true のときだけ有効。
// 条件が `&&` でなく `||` だと、不整合状態（is_aggregated=false / aggregated_len>0）で
// 未初期化の aggregated_text_ptr を text_utf8 に書いてしまう。防御を固定する。
TEST_CASE("JSON well-formedness: Nankai inconsistent aggregate state") {
    Message m{};
    m.svid = 186;
    m.msg_type = 43;
    m.initPayload<Mt43Data>();
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);
    mt43->disaster_category = 4;
    mt43->initAs<NankaiData>();
    NankaiData* nk = mt43->getNankai();
    REQUIRE(nk != nullptr);
    static const char stale[] = "STALE";
    nk->is_aggregated = false;          // 未完成なのにテキスト長だけ非 0（不整合）
    nk->aggregated_len = 5;
    nk->aggregated_text_ptr = stale;
    nk->page = 1;
    nk->total_page = 2;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const std::string& s = sp.str();
    CHECK(s.find("\"text_utf8\"") == std::string::npos);
    checkWellFormed(s, "MT43 nankai inconsistent");
}
#endif // AZARAC_ENABLE_NANKAI

#if (AZARAC_ENABLE_DCX_CAMF)
// B4 の詳細情報は present な D フィールドを 1 つのオブジェクトに並べる。
// 先頭フラグ（first_detail_field）を落とすと `"detailed_info":{,"d1...` になるが、
// test_json_dcx_b1b4.cpp の has() 部分一致はこれを検出できない。
TEST_CASE("JSON well-formedness: MT44 B4 detailed info") {
    Message m{};
    m.svid = 193;
    m.crc24 = 0xABCDEF;
    m.msg_type = 44;
    m.initPayload<Mt44Data>();
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);
    mt44->service_kind = Mt44ServiceKind::LAlert;
    mt44->is_null_message = false;
    mt44->ex_kind = ExtendedKind::LAlertOrLocal;
    mt44->camf.a1 = 1;
    mt44->camf.a2 = 111;
    mt44->camf.a3 = 1;
    mt44->camf.a4 = 36;      // Earthquake
    mt44->camf.a17 = 3;      // B4
    mt44->camf.a18 = 0x7F59; // D1=15, D2=7, D3=5, D4=9（4 フィールド present）
    mt44->camf.b4_present = true;
    mt44->mt44_decoded.main_ellipse_present = true;
    mt44->sd.sdmt = 0;
    mt44->sd.sdm = 0x1FF;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const std::string& s = sp.str();
    CHECK(s.find("\"detailed_info\":{") != std::string::npos);
    CHECK(s.find("\"d4_vector_length\"") != std::string::npos);
    checkWellFormed(s, "MT44 B4");
}
#endif // AZARAC_ENABLE_DCX_CAMF

#if (AZARAC_ENABLE_DCX_CAMF)
TEST_CASE("JSON well-formedness: MT44 DCX") {
    Message m{};
    m.svid = 193;
    m.crc24 = 0xABCDEF;
    m.msg_type = 44;
    m.initPayload<Mt44Data>();
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);
    mt44->service_kind = Mt44ServiceKind::LAlert;
    mt44->is_null_message = false;
    mt44->ex_kind = ExtendedKind::LAlertOrLocal;
    mt44->camf.a1 = 1; mt44->camf.a2 = 111; mt44->camf.a3 = 1;
    mt44->camf.a4 = 10; mt44->camf.a5 = 3; mt44->camf.a8 = 4;
    mt44->camf.a9 = 1; mt44->camf.a11 = 1;   // 日本語ライブラリ（AZARAC_LOOKUP_LANG 経路）
    mt44->ex.ex_lalert_local.ex1 = 1100;
    mt44->ex.ex_lalert_local.vn = 1;
    mt44->sd.sdmt = 0; mt44->sd.sdm = 0x1FF;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    checkWellFormed(sp.str(), "MT44");
}
#endif // AZARAC_ENABLE_DCX_CAMF

// 検査器自体の検証: 不正な JSON を検出できること（無いと「常に true を返す検査器」で上のテストが無意味になる）。
TEST_CASE("JSON well-formedness: the checker rejects malformed input") {
    const char* bad[] = {
        "{\"a\":1\"b\":2}",          // カンマ欠落（AZARAC_LABEL の last 誤りと同じ形）
        "{\"a\":1,}",                // 末尾カンマ
        "{\"a\":1",                  // 閉じ括弧なし
        "{\"a\":\"x}",               // 引用符なし
        "{\"a\":1,\"a\":2}",         // キー重複
        "{\"a\":[1,2}",              // 配列の閉じ誤り
        "{\"a\":1}",                 // （これは妥当 — 除外）
    };
    for (const char* s : bad) {
        // JsonCheck は const std::string& を保持する。
        // const char* からの一時 std::string を直接渡すとメンバ参照の束縛先が全式の終わりで破壊される（dangling reference。LTO のヒープレイアウト変化で顕在化）ので、ここで寿命を作る。
        const std::string input(s);
        JsonCheck jc(input);
        bool ok = jc.run();
        if (strcmp(s, "{\"a\":1}") == 0) {
            CHECK(ok);               // 妥当なものは通る
        } else {
            CHECK_FALSE(ok);         // 不正なものは落ちる
        }
    }
}
