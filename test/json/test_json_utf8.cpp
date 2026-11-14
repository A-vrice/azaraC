// writeStrUtf8（南海トラフ集約テキストの UTF-8 検証＋U+FFFD 置換）の回帰テスト。
// オラクルは Python errors="replace"（ maximal subpart 規則）と独立なコードポイント検証器。
// 本番のバイトパターン判定とは別アルゴリズムで出力の妥当性を検査する。

#define ARDUINO 0
#include "../src/azaraC.h"
#include "../src/internal/PrintShim.h"
#include "../src/json/JsonWriter.h"
#include "../test_helpers.h"
#include "JsonCheck.h"
#include "doctest.h"
#include <cstdint>
#include <string>

using namespace azaraC;

#if AZARAC_ENABLE_NANKAI

namespace {

// 独立な UTF-8 妥当性検証（コードポイント復号＋overlong/サロゲート/範囲検査）。
bool isValidUtf8(const std::string& s) {
    const uint8_t* p = reinterpret_cast<const uint8_t*>(s.data());
    const size_t n = s.size();
    size_t i = 0;
    while (i < n) {
        const uint8_t b = p[i];
        if (b < 0x80) { ++i; continue; }
        uint32_t cp; int extra;
        if      (b >= 0xC2 && b <= 0xDF) { cp = b & 0x1Fu; extra = 1; }
        else if (b >= 0xE0 && b <= 0xEF) { cp = b & 0x0Fu; extra = 2; }
        else if (b >= 0xF0 && b <= 0xF4) { cp = b & 0x07u; extra = 3; }
        else return false;
        if (i + static_cast<size_t>(extra) >= n) return false;
        for (int k = 1; k <= extra; ++k) {
            const uint8_t c = p[i + k];
            if ((c & 0xC0) != 0x80) return false;
            cp = (cp << 6) | (c & 0x3Fu);
        }
        if (extra == 1 && cp < 0x80) return false;
        if (extra == 2 && cp < 0x800) return false;
        if (extra == 3 && cp < 0x10000) return false;
        if (cp >= 0xD800 && cp <= 0xDFFF) return false;
        if (cp > 0x10FFFF) return false;
        i += static_cast<size_t>(extra) + 1;
    }
    return true;
}

// writeStrUtf8 の出力から外側の引用符を除いた本体を返す。
std::string body(const std::string& input) {
    StringPrint sp;
    internal::writeStrUtf8(sp, input);
    const std::string& s = sp.str();
    REQUIRE(s.size() >= 2);
    REQUIRE(s.front() == '"');
    REQUIRE(s.back() == '"');
    return s.substr(1, s.size() - 2);
}

std::string bytes(const std::vector<uint8_t>& v) {
    return std::string(reinterpret_cast<const char*>(v.data()), v.size());
}

} // namespace

TEST_CASE("UTF-8: replacement matches Python errors=replace (maximal subpart)") {
    struct Case { std::vector<uint8_t> in, out; };
    // Python: b.decode('utf-8','replace').encode('utf-8') で生成（JSON エスケープ対象を含まない入力）。
    const Case cases[] = {
        {{0xFF}, {0xEF,0xBF,0xBD}},
        {{0x80}, {0xEF,0xBF,0xBD}},
        {{0xC0,0x80}, {0xEF,0xBF,0xBD,0xEF,0xBF,0xBD}},
        {{0xC3,0xFF,0xA9}, {0xEF,0xBF,0xBD,0xEF,0xBF,0xBD,0xEF,0xBF,0xBD}},
        {{0xE3,0x81,0xFF}, {0xEF,0xBF,0xBD,0xEF,0xBF,0xBD}},
        {{0xF0,0x9F,0x92}, {0xEF,0xBF,0xBD}},
        {{0xED,0xA0,0x80}, {0xEF,0xBF,0xBD,0xEF,0xBF,0xBD,0xEF,0xBF,0xBD}},
        {{0xF4,0x90,0x80,0x80}, {0xEF,0xBF,0xBD,0xEF,0xBF,0xBD,0xEF,0xBF,0xBD,0xEF,0xBF,0xBD}},
        {{0xE0,0x80,0x80}, {0xEF,0xBF,0xBD,0xEF,0xBF,0xBD,0xEF,0xBF,0xBD}},
        {{0xC3,0xA9}, {0xC3,0xA9}},                         // valid é
        {{0xE3,0x81,0x82}, {0xE3,0x81,0x82}},               // valid あ
        {{0xF0,0x9F,0x92,0xA9}, {0xF0,0x9F,0x92,0xA9}},     // valid 💩
        {{0x41,0xFF,0x42}, {0x41,0xEF,0xBF,0xBD,0x42}},
        {{0xE3,0x81}, {0xEF,0xBF,0xBD}},                    // truncated valid prefix
    };
    for (const auto& c : cases) {
        CAPTURE(c.in.size());
        CHECK(body(bytes(c.in)) == bytes(c.out));
    }
}

TEST_CASE("UTF-8: output is always valid UTF-8 (all 1-byte and 2-byte inputs)") {
    for (int a = 0; a < 256; ++a) {
        const std::string in(1, static_cast<char>(a));
        CHECK(isValidUtf8(body(in)));
    }
    for (int a = 0; a < 256; ++a) {
        for (int b = 0; b < 256; ++b) {
            const char buf[2] = {static_cast<char>(a), static_cast<char>(b)};
            CHECK(isValidUtf8(body(std::string(buf, 2))));
        }
    }
}

TEST_CASE("UTF-8: valid sequences pass through unchanged") {
    const char* valid[] = {
        "Hello, world!",
        "\xC3\xA9",                     // é
        "\xE3\x81\x82\xE3\x81\x84",     // あい
        "\xF0\x9F\x92\xA9",             // 💩
        "mix \xE3\x81\x82 ASCII \xC3\xA9",
    };
    for (const char* s : valid) {
        const std::string in(s);
        CHECK(isValidUtf8(in));
        CHECK(body(in) == in);
    }
}

TEST_CASE("UTF-8: JSON escaping still applies alongside replacement") {
    // " \ と改行＋不正バイト 0xFF。エスケープと U+FFFD が両立し、JSON として妥当。
    const std::string in = "\"\\\n\xFF";
    const std::string out = body(in);
    CHECK(out.find("\\\"") != std::string::npos);
    CHECK(out.find("\\\\") != std::string::npos);
    CHECK(out.find("\\n") != std::string::npos);
    CHECK(out.find("\xEF\xBF\xBD") != std::string::npos);
    CHECK(isValidUtf8(out));
    const std::string obj = "{\"text_utf8\":\"" + out + "\"}";
    JsonCheck jc(obj);
    CHECK(jc.run());
}

TEST_CASE("UTF-8: Nankai aggregated text with invalid bytes serializes to valid JSON") {
    Message m{};
    m.msg_type = 43;
    m.initPayload<Mt43Data>();
    Mt43Data* mt43 = m.getMt43();
    REQUIRE(mt43 != nullptr);
    mt43->disaster_category = 4;
    mt43->initAs<NankaiData>();
    NankaiData* nankai = mt43->getNankai();
    REQUIRE(nankai != nullptr);

    // 衛星由来を模した生バイト: 正常な日本語＋不正シーケンス＋制御文字。
    const char raw[] = "\xE3\x81\x82\xFF\xE3\x81\xC3\xA9\x01";
    nankai->is_aggregated = true;
    nankai->aggregated_text_ptr = raw;
    nankai->aggregated_len = static_cast<uint8_t>(sizeof(raw) - 1);
    nankai->page = 1;
    nankai->total_page = 1;

    StringPrint sp;
    internal::JsonSerializer::serialize(m, sp);
    const std::string& json = sp.str();
    JsonCheck jc(json);
    const bool ok = jc.run();
    if (!ok) MESSAGE("json=", json.substr(0, 400), " err=", jc.error());
    CHECK(ok);

    // text_utf8 の値を取り出して UTF-8 妥当性を検査する。
    const std::string key = "\"text_utf8\":\"";
    const size_t start = json.find(key);
    REQUIRE(start != std::string::npos);
    size_t vbegin = start + key.size();
    std::string value;
    for (size_t i = vbegin; i < json.size(); ++i) {
        const char c = json[i];
        if (c == '\\') { value += c; if (i + 1 < json.size()) value += json[++i]; continue; }
        if (c == '"') break;
        value += c;
    }
    CHECK(isValidUtf8(value));
    CHECK(value.find("\xEF\xBF\xBD") != std::string::npos);   // 0xFF と切断シーケンスが置換された
}

#endif // AZARAC_ENABLE_NANKAI