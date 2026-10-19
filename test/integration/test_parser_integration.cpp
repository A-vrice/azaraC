// test/integration/test_parser_integration.cpp — Parser統合テスト
// NOTE: Most tests use EEW (dc=1); guarded by AZARAC_ENABLE_EEW

#include <string>
#include "doctest.h"
#include "../src/Parser.h"
#include "../test_helpers.h"

using namespace azaraC;

// Non-category-specific tests (always compiled)

#if (AZARAC_ENABLE_NANKAI)
TEST_CASE("Parser getNankaiBuffer returns nullptr for unknown key") {
    Parser parser;

    azaraC::internal::NankaiPageKey key = {1};
    const azaraC::internal::NankaiPageBuffer* buf = parser.getNankaiBuffer(key);
    CHECK(buf == nullptr);
}
#endif

// EEW-dependent tests (dc=1)

#if (AZARAC_ENABLE_EEW)

TEST_CASE("Parser AUTO mode: NMEA message decoded") {
    Parser parser;
    Message msg;

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 1);
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);
    std::string nmea = makeNmeaQzqsm(58, bits);

    bool output = false;
    for (size_t i = 0; i < nmea.length(); i++) {
        if (parser.feed(nmea[i], msg, 0)) {
            output = true;
            break;
        }
    }

    CHECK(output);
    CHECK(msg.valid);
    CHECK(msg.payload_type == MsgPayloadType::Mt43);
}

TEST_CASE("Parser AUTO mode: UBX message decoded") {
    Parser parser;
    Message msg;

    uint8_t nav_bits[32] = {};
    setBits(nav_bits, 0, 8, 0x53);
    setBits(nav_bits, 8, 6, 43);
    setBits(nav_bits, 17, 4, 1);
    setBits(nav_bits, 214, 6, 1);
    uint32_t crc = crc24qRef(nav_bits, 226);
    setBits(nav_bits, 226, 24, crc);
    auto ubx = makeUbxSfrbx(193, nav_bits);

    bool output = false;
    for (auto b : ubx) {
        if (parser.feed(b, msg, 0)) {
            output = true;
            break;
        }
    }

    CHECK(output);
    CHECK(msg.valid);
}

TEST_CASE("Parser EEW duplicate suppression") {
    Parser parser;
    Message msg;

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 1);
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);
    std::string nmea = makeNmeaQzqsm(58, bits);

    bool output1 = false;
    for (size_t i = 0; i < nmea.length(); i++) {
        if (parser.feed(nmea[i], msg, 0)) {
            output1 = true;
            break;
        }
    }
    CHECK(output1);
    CHECK(msg.valid);

    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    CHECK(mt43->disaster_category == 1);

    bool output2 = false;
    for (size_t i = 0; i < nmea.length(); i++) {
        if (parser.feed(nmea[i], msg, 0)) {
            output2 = true;
            break;
        }
    }
    CHECK_FALSE(output2);
}

TEST_CASE("Parser reset clears state") {
    Parser parser;
    Message msg;

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 1);
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);
    std::string nmea = makeNmeaQzqsm(58, bits);

    bool output1 = false;
    for (size_t i = 0; i < nmea.length(); i++) {
        if (parser.feed(nmea[i], msg, 0)) {
            output1 = true;
            break;
        }
    }
    CHECK(output1);

    parser.reset();

    bool output2 = false;
    for (size_t i = 0; i < nmea.length(); i++) {
        if (parser.feed(nmea[i], msg, 0)) {
            output2 = true;
            break;
        }
    }
    CHECK(output2);
}

// NMEA part uses EEW (dc=1), UBX part uses DCX (MT=44); needs both macros.
#if (AZARAC_ENABLE_DCX_CAMF)
TEST_CASE("Parser handles mixed NMEA and UBX messages") {
    Parser parser;
    Message msg;

    uint8_t bits1[32] = {};
    setBits(bits1, 0, 8, 0x53);
    setBits(bits1, 8, 6, 43);
    setBits(bits1, 14, 3, 1);
    setBits(bits1, 17, 4, 1);
    setBits(bits1, 214, 6, 1);
    uint32_t crc1 = crc24qRef(bits1, 226);
    setBits(bits1, 226, 24, crc1);
    std::string nmea1 = makeNmeaQzqsm(58, bits1);

    bool output1 = false;
    for (size_t i = 0; i < nmea1.length(); i++) {
        if (parser.feed(nmea1[i], msg, 0)) {
            output1 = true;
            break;
        }
    }
    CHECK(output1);
    CHECK(msg.payload_type == MsgPayloadType::Mt43);

    uint8_t nav_bits[32] = {};
    setBits(nav_bits, 0, 8, 0x53);
    setBits(nav_bits, 8, 6, 44);
    setBits(nav_bits, 24, 2, 1);
    setBits(nav_bits, 26, 9, 111);
    setBits(nav_bits, 214, 6, 1);
    uint32_t crc2 = crc24qRef(nav_bits, 226);
    setBits(nav_bits, 226, 24, crc2);
    auto ubx = makeUbxSfrbx(193, nav_bits);

    bool output2 = false;
    for (auto b : ubx) {
        if (parser.feed(b, msg, 0)) {
            output2 = true;
            break;
        }
    }
    CHECK(output2);
    CHECK(msg.payload_type == MsgPayloadType::Mt44);
}
#endif // AZARAC_ENABLE_DCX_CAMF


TEST_CASE("Parser: long garbage between valid frames recovers") {
    azaraC::Parser parser;
    azaraC::Message msg;

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 1);
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);
    std::string nmea = makeNmeaQzqsm(58, bits);

    std::string garbage;
    for (int i = 0; i < 1000; ++i) {
        garbage += static_cast<char>(0x41 + (i % 26));
    }
    std::string stream = garbage + nmea;

    bool output = false;
    for (size_t i = 0; i < stream.length(); ++i) {
        if (parser.feed(stream[i], msg, 0)) {
            output = true;
            break;
        }
    }
    CHECK(output);
    CHECK(msg.valid);
    CHECK(msg.payload_type == azaraC::MsgPayloadType::Mt43);
}

TEST_CASE("Parser: rapid consecutive resets still decode") {
    azaraC::Parser parser;
    azaraC::Message msg;

    const std::string partial = "$QZQSM,58,9AAF";
    for (int r = 0; r < 10; ++r) {
        for (char c : partial) {
            parser.feed(static_cast<uint8_t>(c), msg, 0);
        }
        parser.reset();
    }

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 1);
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);
    std::string nmea = makeNmeaQzqsm(58, bits);

    bool output = false;
    for (size_t i = 0; i < nmea.length(); ++i) {
        if (parser.feed(nmea[i], msg, 0)) {
            output = true;
            break;
        }
    }
    CHECK(output);
    CHECK(msg.valid);
}

TEST_CASE("Parser: mode switch NMEA to UBX after partial frame") {
    azaraC::Parser parser;
    azaraC::Message msg;

    std::string nmea_partial = "$QZQSM,58,9AAF";
    uint8_t nav_bits[32] = {};
    setBits(nav_bits, 0, 8, 0x53);
    setBits(nav_bits, 8, 6, 43);
    setBits(nav_bits, 17, 4, 1);
    setBits(nav_bits, 214, 6, 1);
    uint32_t crc = crc24qRef(nav_bits, 226);
    setBits(nav_bits, 226, 24, crc);
    auto ubx = makeUbxSfrbx(193, nav_bits);

    for (char c : nmea_partial) {
        parser.feed((uint8_t)c, msg, 0);
    }

    bool ubx_found = false;
    for (auto b : ubx) {
        if (parser.feed(b, msg, 0)) {
            ubx_found = true;
            break;
        }
    }
    CHECK(ubx_found);
    CHECK(msg.valid);
    CHECK(msg.payload_type == azaraC::MsgPayloadType::Mt43);
}

TEST_CASE("Parser: stale NMEA partial data doesn't leak") {
    azaraC::Parser parser;
    azaraC::Message msg;

    std::string stale_prefix = "$GPGGA,1234";
    for (char c : stale_prefix) {
        parser.feed((uint8_t)c, msg, 0);
    }

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 1);
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);
    std::string nmea = makeNmeaQzqsm(58, bits);

    bool output = false;
    for (size_t i = 0; i < nmea.length(); ++i) {
        if (parser.feed(nmea[i], msg, 0)) {
            output = true;
            break;
        }
    }
    CHECK(output);
    CHECK(msg.valid);
    const azaraC::Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    CHECK(mt43->disaster_category == 1);
}

// 手順③ の照合対象は MT～VN（bit 8..219 = 212 bit。
// 付属フローチャートも「MT～Vnの212bit」と明記）。
// プリアンブル（bit 0..7）は A(0x53)→B(0x9A)→C(0xC6)、Reserved（bit 220..225）は 16 値で巡回するため、どちらも含めず 1 情報 1 通知に固定する。
TEST_CASE("Parser: プリアンブル/Reserved が違っても同一 MT～VN は 1 回だけ通知される") {
    Parser parser;
    Message msg;

    // minute: MT～VN 内の唯一の内容マーカー（bit 35..40）。preamble/reserved は MT～VN 外で identity を変えない。
    auto feedFrame = [&](uint8_t preamble, uint8_t minute, uint8_t reserved) -> int {
        uint8_t bits[32] = {};
        setBits(bits, 0, 8, preamble);
        setBits(bits, 8, 6, 43);
        setBits(bits, 14, 3, 1);      // report_classification
        setBits(bits, 17, 4, 1);      // disaster_category = 1 (EEW)
        setBits(bits, 35, 6, minute); // report_time minute
        setBits(bits, 214, 6, 1);     // version (Vn = bit 214..219)
        setBits(bits, 220, 6, reserved);
        setBits(bits, 226, 24, crc24qRef(bits, 226));
        const std::string nmea = makeNmeaQzqsm(58, bits);
        int emitted = 0;
        for (size_t i = 0; i < nmea.size(); ++i) {
            if (parser.feed(static_cast<uint8_t>(nmea[i]), msg, 0)) ++emitted;
        }
        return emitted;
    };

    CHECK(feedFrame(0x53, 0, 0) == 1);   // 新規情報
    CHECK(feedFrame(0x9A, 0, 0) == 0);   // プリアンブルだけ違う → 重複
    CHECK(feedFrame(0xC6, 0, 0) == 0);   // 同様
    CHECK(feedFrame(0x53, 0, 5) == 0);   // Reserved(220..225) だけ違う → 重複
    CHECK(feedFrame(0x53, 0, 15) == 0);  // 同様（218 bit 鍵なら別情報になる）
    CHECK(feedFrame(0x53, 1, 0) == 1);   // MT～VN が変われば別情報
}
#endif // AZARAC_ENABLE_EEW

#if (AZARAC_ENABLE_DCX_CAMF)
// QZS 事務局回答: 照合範囲「MT および CAMF〜EM」に SDMT（bit 14）・SDM（bit 15..23）を含めず、SD だけが違う同一内容は 1 回だけ通知する。
TEST_CASE("Parser: MT44 は SDMT/SDM が違っても同一内容を 1 回だけ通知する") {
    Parser parser;
    Message msg;

    // MT=44 の L-Alert（A2=Japan, A3=FMMC）。SDMT/SDM と A8 以外は固定。
    auto feed = [&](uint8_t sdmt, uint16_t sdm, uint8_t a8) -> int {
        uint8_t bits[32] = {};
        setBits(bits, 0, 8, 0x53);
        setBits(bits, 8, 6, 44);
        setBits(bits, 14, 1, sdmt);
        setBits(bits, 15, 9, sdm);
        setBits(bits, 24, 2, 1);       // A1=Alert
        setBits(bits, 26, 9, 111);     // A2=Japan
        setBits(bits, 35, 5, 1);       // A3=FMMC (L-Alert)
        setBits(bits, 40, 7, 1);       // A4=Rainfall（NullMessage 判定を避ける）
        setBits(bits, 64, 2, a8);      // A8=Hazard Duration
        setBits(bits, 226, 24, crc24qRef(bits, 226));
        const std::string nmea = makeNmeaQzqsm(58, bits);
        int emitted = 0;
        for (size_t i = 0; i < nmea.size(); ++i) {
            if (parser.feed(static_cast<uint8_t>(nmea[i]), msg, 0)) ++emitted;
        }
        return emitted;
    };

    CHECK(feed(0, 0x000, 1) == 1);   // 新規情報
    CHECK(feed(1, 0x1FF, 1) == 0);   // SD だけ違う → 重複（Step 1 前は 1 になる）
    CHECK(feed(0, 0x1FF, 2) == 1);   // A8 が違う → 別情報
}
#endif // AZARAC_ENABLE_DCX_CAMF
