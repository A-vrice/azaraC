// test/integration/test_parser_integration.cpp — Parser統合テスト

#include <string>
#include "doctest.h"
#include "../src/Parser.h"
#include "../test_helpers.h"

using namespace azaraC;

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

TEST_CASE("Parser getNankaiBuffer returns nullptr for unknown key") {
    Parser parser;

    azaraC::internal::NankaiPageKey key = {1, 1234567890};
    const azaraC::internal::NankaiPageBuffer* buf = parser.getNankaiBuffer(key);
    CHECK(buf == nullptr);
}

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
