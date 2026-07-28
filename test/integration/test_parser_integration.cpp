// test/integration/test_parser_integration.cpp — Parser統合テスト
// NOTE: Most tests use EEW (disaster_category=1) and are guarded by AZARAC_ENABLE_EEW

#include <string>
#include "doctest.h"
#include "../src/Parser.h"
#include "../test_helpers.h"

using namespace azaraC;

// =============================================================================
// Non-category-specific tests (always compiled)
// =============================================================================

#if (AZARAC_ENABLE_NANKAI)
TEST_CASE("Parser getNankaiBuffer returns nullptr for unknown key") {
    Parser parser;

    azaraC::internal::NankaiPageKey key = {1234567890, 1};
    const azaraC::internal::NankaiPageBuffer* buf = parser.getNankaiBuffer(key);
    CHECK(buf == nullptr);
}
#endif

// =============================================================================
// EEW-dependent tests (dc=1)
// =============================================================================

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

// Parser handles mixed NMEA and UBX messages: NMEA part uses EEW (dc=1),
// UBX part uses DCX (MT=44). Guarded by both macros.
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

// ── Parser 再入安全性テスト ─────────────────────────────────────────────────────

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

    // 1000 バイトのランダムデータ挿入後、QZQSM が正常にデコードされる
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

    // 未完了フレームを保持した状態で繰り返しリセット
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

    // NMEA の途中で UBX データが混入 → リセット後 UBX を正しく処理
    std::string nmea_partial = "$QZQSM,58,9AAF";
    uint8_t nav_bits[32] = {};
    setBits(nav_bits, 0, 8, 0x53);
    setBits(nav_bits, 8, 6, 43);
    setBits(nav_bits, 17, 4, 1);
    setBits(nav_bits, 214, 6, 1);
    uint32_t crc = crc24qRef(nav_bits, 226);
    setBits(nav_bits, 226, 24, crc);
    auto ubx = makeUbxSfrbx(193, nav_bits);

    // 部分 NMEA を feed
    for (char c : nmea_partial) {
        parser.feed((uint8_t)c, msg, 0);
    }

    // UBX データを feed（この時点で内部フレーマーが NMEA→UBX に切り替わるはず）
    bool ubx_found = false;
    for (auto b : ubx) {
        if (parser.feed(b, msg, 0)) {
            ubx_found = true;
            break;
        }
    }
    // UBX データは正しくデコードされるべき
    CHECK(ubx_found);
    CHECK(msg.valid);
    CHECK(msg.payload_type == azaraC::MsgPayloadType::Mt43);
}

TEST_CASE("Parser: stale NMEA partial data doesn't leak") {
    azaraC::Parser parser;
    azaraC::Message msg;

    // 不正 NMEA 開始（非 QZQSM のスタブ）
    std::string stale_prefix = "$GPGGA,1234";
    for (char c : stale_prefix) {
        parser.feed((uint8_t)c, msg, 0);
    }

    // その後、有効な QZQSM を流す — 前の部分データが悪影響しない
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
    // 正しい disaster_category が取れていること（古いデータが混入していない）
    const azaraC::Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    CHECK(mt43->disaster_category == 1);
}

#endif // AZARAC_ENABLE_EEW
