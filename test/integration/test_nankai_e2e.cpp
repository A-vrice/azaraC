// test/integration/test_nankai_e2e.cpp — 南海トラフ複数ページ集約E2Eテスト

#include <string>
#include "doctest.h"
#include "../src/internal/NankaiPageBuffer.h"
#include "../src/Parser.h"
#include "../test_helpers.h"

using namespace azaraC::internal;

TEST_CASE("Nankai E2E: Parser decodes synthetic Nankai message") {
    azaraC::Parser parser;
    azaraC::Message msg;

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 4);
    setBits(bits, 53, 4, 1);
    setBits(bits, 201, 6, 1);
    setBits(bits, 207, 6, 1);
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
    CHECK(msg.payload_type == azaraC::MsgPayloadType::Mt43);
    
    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    CHECK(mt43->disaster_category == 4);
    
    const NankaiData* nankai = mt43->getNankai();
    REQUIRE(nankai != nullptr);
    CHECK(nankai->page == 1);
    CHECK(nankai->total_page == 1);
}

TEST_CASE("Nankai E2E: Parser duplicate suppression") {
    azaraC::Parser parser;
    azaraC::Message msg;

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 4);
    setBits(bits, 53, 4, 1);
    setBits(bits, 201, 6, 1);
    setBits(bits, 207, 6, 1);
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

    bool output2 = false;
    for (size_t i = 0; i < nmea.length(); i++) {
        if (parser.feed(nmea[i], msg, 0)) {
            output2 = true;
            break;
        }
    }
    CHECK_FALSE(output2);
}

TEST_CASE("Nankai E2E: Parser reset allows re-output") {
    azaraC::Parser parser;
    azaraC::Message msg;

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 4);
    setBits(bits, 53, 4, 1);
    setBits(bits, 201, 6, 1);
    setBits(bits, 207, 6, 1);
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

TEST_CASE("Nankai E2E: Multiple different messages not suppressed") {
    azaraC::Parser parser;
    azaraC::Message msg;

    uint8_t bits1[32] = {};
    setBits(bits1, 0, 8, 0x53);
    setBits(bits1, 8, 6, 43);
    setBits(bits1, 14, 3, 1);
    setBits(bits1, 17, 4, 4);
    setBits(bits1, 53, 4, 1);
    setBits(bits1, 201, 6, 1);
    setBits(bits1, 207, 6, 1);
    setBits(bits1, 214, 6, 1);
    uint32_t crc1 = crc24qRef(bits1, 226);
    setBits(bits1, 226, 24, crc1);
    std::string nmea1 = makeNmeaQzqsm(58, bits1);

    uint8_t bits2[32] = {};
    setBits(bits2, 0, 8, 0x53);
    setBits(bits2, 8, 6, 43);
    setBits(bits2, 14, 3, 1);
    setBits(bits2, 17, 4, 4);
    setBits(bits2, 53, 4, 2);
    setBits(bits2, 201, 6, 1);
    setBits(bits2, 207, 6, 1);
    setBits(bits2, 214, 6, 1);
    uint32_t crc2 = crc24qRef(bits2, 226);
    setBits(bits2, 226, 24, crc2);
    std::string nmea2 = makeNmeaQzqsm(58, bits2);

    bool output1 = false;
    for (size_t i = 0; i < nmea1.length(); i++) {
        if (parser.feed(nmea1[i], msg, 0)) {
            output1 = true;
            break;
        }
    }
    CHECK(output1);

    bool output2 = false;
    for (size_t i = 0; i < nmea2.length(); i++) {
        if (parser.feed(nmea2[i], msg, 0)) {
            output2 = true;
            break;
        }
    }
    CHECK(output2);
}

TEST_CASE("Nankai E2E: Text extraction from single page") {
    azaraC::Parser parser;
    azaraC::Message msg;

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 4);
    setBits(bits, 53, 4, 1);
    const char* text = "Test";
    for (int i = 0; i < 4; i++) {
        setBits(bits, 57 + i * 8, 8, (uint8_t)text[i]);
    }
    setBits(bits, 201, 6, 1);
    setBits(bits, 207, 6, 1);
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
    
    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    
    const NankaiData* nankai = mt43->getNankai();
    REQUIRE(nankai != nullptr);
    CHECK(nankai->text[0] == 'T');
    CHECK(nankai->text[1] == 'e');
    CHECK(nankai->text[2] == 's');
    CHECK(nankai->text[3] == 't');
}

TEST_CASE("Nankai E2E: Oversized page rejected") {
    const char* nmea_oversized = "$QZQSM,58,9AAFA19C918002F1C0C271C0410000000000000000000000000036D81121AA2D0*07";

    Message msg;
    bool ok = decodeNmea(nmea_oversized, msg);
    CHECK_FALSE(ok);
}

TEST_CASE("Nankai E2E: Page tracking with single page") {
    azaraC::Parser parser;
    azaraC::Message msg;

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 4);
    setBits(bits, 53, 4, 5);
    setBits(bits, 201, 6, 1);
    setBits(bits, 207, 6, 1);
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

    REQUIRE(output);
    
    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    
    const NankaiData* nankai = mt43->getNankai();
    REQUIRE(nankai != nullptr);
    CHECK(nankai->page == 1);
    CHECK(nankai->total_page == 1);
    CHECK(nankai->info_code == 5);
}
