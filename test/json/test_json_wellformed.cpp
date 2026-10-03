// test/json/test_json_wellformed.cpp — シリアライザ出力が JSON として妥当か
//
// `_label_en` の併記は各ラベルサイトを 2 つのペアで書くため、`last` の受け渡しを
// 誤ると `"a":1"b":2` のような**カンマ欠落**や、逆に二重カンマを生む。既存テストは
// `has()` による部分文字列検査なので、この種の構文崩れを検出できない。
//
// ここでは全カテゴリを 1 通ずつシリアライズし、
//   1. JSON として構造が閉じている（括弧・引用符・カンマ）
//   2. 同じオブジェクト内でキーが重複していない
// を検証する。キー重複は、数量フィールドに `_label` を足した際などに起こり得る。

#define ARDUINO 0
#include "../src/azaraC.h"
#include "../src/internal/PrintShim.h"
#include "../src/json/JsonWriter.h"
#include "../test_helpers.h"
#include "doctest.h"
#include <cstring>
#include <string>
#include <vector>

using namespace azaraC;

namespace {

// 最小の JSON 妥当性検査。値は深追いせず、構造（括弧・引用符・カンマ）と
// 各オブジェクト内のキー重複だけを見る。空白は書かない前提なので厳密でよい。
class JsonCheck {
public:
    JsonCheck(const std::string& s) : s_(s) {}

    // 妥当なら true。不正なら error() に理由が入る。
    bool run() {
        if (!parseValue()) { fail("value"); return false; }
        if (i_ != s_.size()) { fail("trailing"); return false; }
        return true;
    }

    const std::string& error() const { return err_; }

private:
    const std::string& s_;
    size_t i_ = 0;
    std::string err_;
    std::vector<std::string> keys_;   // 現在のオブジェクトのキー集合

    void fail(const char* what) {
        if (err_.empty())
            err_ = std::string(what) + " at offset " + std::to_string(i_);
    }
    bool eof() const { return i_ >= s_.size(); }
    char peek() const { return eof() ? '\0' : s_[i_]; }

    bool parseString() {
        if (peek() != '"') { fail("string open"); return false; }
        ++i_;
        while (!eof()) {
            char c = s_[i_];
            if (c == '\\') { i_ += 2; continue; }   // エスケープは 2 文字消費
            if (c == '"') { ++i_; return true; }
            ++i_;
        }
        fail("string unterminated");
        return false;
    }

    bool parseNumber() {
        size_t start = i_;
        if (peek() == '-') ++i_;
        while (!eof() && (isdigit(static_cast<unsigned char>(peek())) || peek() == '.' ||
                          peek() == 'e' || peek() == 'E' || peek() == '+' || peek() == '-'))
            ++i_;
        if (i_ == start) { fail("number"); return false; }
        return true;
    }

    bool parseLiteral(const char* lit) {
        size_t n = strlen(lit);
        if (s_.compare(i_, n, lit) != 0) { fail(lit); return false; }
        i_ += n;
        return true;
    }

    bool parseObject() {
        if (peek() != '{') { fail("object open"); return false; }
        ++i_;
        auto saved = keys_;
        keys_.clear();
        if (peek() == '}') { ++i_; keys_ = saved; return true; }
        for (;;) {
            size_t keyPos = i_;
            if (!parseString()) return false;
            std::string key = s_.substr(keyPos, i_ - keyPos);
            // 同一オブジェクト内のキー重複を検出する
            for (const auto& k : keys_) {
                if (k == key) {
                    err_ = "duplicate key " + key + " at offset " + std::to_string(keyPos);
                    return false;
                }
            }
            keys_.push_back(key);
            if (peek() != ':') { fail("colon"); return false; }
            ++i_;
            if (!parseValue()) return false;
            if (peek() == ',') { ++i_; continue; }
            if (peek() == '}') { ++i_; keys_ = saved; return true; }
            fail("object sep");
            return false;
        }
    }

    bool parseArray() {
        if (peek() != '[') { fail("array open"); return false; }
        ++i_;
        auto saved = keys_;
        keys_.clear();
        if (peek() == ']') { ++i_; keys_ = saved; return true; }
        for (;;) {
            if (!parseValue()) return false;
            if (peek() == ',') { ++i_; continue; }
            if (peek() == ']') { ++i_; keys_ = saved; return true; }
            fail("array sep");
            return false;
        }
    }

    bool parseValue() {
        switch (peek()) {
            case '"': return parseString();
            case '{': return parseObject();
            case '[': return parseArray();
            case 't': return parseLiteral("true");
            case 'f': return parseLiteral("false");
            case 'n': return parseLiteral("null");
            default:  return parseNumber();
        }
    }
};

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
    m.payload_type = MsgPayloadType::Mt43;
    m.initPayload<Mt43Data>();
    Mt43Data* mt43 = m.getMt43();
    if (!mt43) return;
    mt43->disaster_category = dc;
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

// 各カテゴリを代表値付きで埋め、1 通ずつ JSON 妥当性を検査する。
// 数量フィールドは境界値（センチネル）を入れてラベルの分岐も通す。
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

#if (AZARAC_ENABLE_DCX_CAMF)
TEST_CASE("JSON well-formedness: MT44 DCX") {
    Message m{};
    m.svid = 193;
    m.crc24 = 0xABCDEF;
    m.msg_type = 44;
    m.payload_type = MsgPayloadType::Mt44;
    m.initPayload<Mt44Data>();
    Mt44Data* mt44 = m.getMt44();
    REQUIRE(mt44 != nullptr);
    mt44->service_kind = Mt44ServiceKind::LAlert;
    mt44->is_null_message = false;
    mt44->ex_kind = ExtendedKind::LAlertOrLocal;
    mt44->camf.a1 = 1; mt44->camf.a2 = 111; mt44->camf.a3 = 1;
    mt44->camf.a4 = 10; mt44->camf.a5 = 3; mt44->camf.a8 = 4;
    mt44->camf.a9 = 1; mt44->camf.a11 = 1;   // 日本語ライブラリ（AZARAC_LOOKUP_LANG 経路）
    mt44->ex_lalert_local.ex1 = 1100;
    mt44->ex_lalert_local.vn = 1;
    mt44->sd.sdmt = 0; mt44->sd.sdm = 0x1FF;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    checkWellFormed(sp.str(), "MT44");
}
#endif // AZARAC_ENABLE_DCX_CAMF

// 不正な JSON を検出できること（検査器自体の回帰）。
// これが無いと「常に true を返す検査器」で上のテストが無意味になる。
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
        JsonCheck jc(s);
        bool ok = jc.run();
        if (strcmp(s, "{\"a\":1}") == 0) {
            CHECK(ok);               // 妥当なものは通る
        } else {
            CHECK_FALSE(ok);         // 不正なものは落ちる
        }
    }
}
