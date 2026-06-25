// test/integration/test_error_handling.cpp — エラーハンドリング詳細テスト

#include <string>
#include "doctest.h"
#include "../src/Parser.h"
#include "../test_helpers.h"

using namespace azaraC;

TEST_CASE("Error: NMEA 65 char payload rejected") {
    char nmea[256];
    strcpy(nmea, "$QZQSM,55,");
    for (int i = 0; i < 65; i++) {
        sprintf(nmea + strlen(nmea), "%X", i % 16);
    }
    uint8_t xsum = 0;
    for (size_t i = 1; i < strlen(nmea); i++) {
        xsum ^= (uint8_t)nmea[i];
    }
    sprintf(nmea + strlen(nmea), "*%02X\r\n", xsum);

    Message msg{};
    bool ok = decodeNmea(nmea, msg);
    CHECK_FALSE(ok);
}

TEST_CASE("Error: Invalid CRC leaves msg invalid") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 17, 4, 1);
    setBits(bits, 214, 6, 1);
    setBits(bits, 226, 24, 0xDEADBEE);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    bool result = dec.decode(frame, msg, 0);
    CHECK_FALSE(result);
    CHECK_FALSE(msg.valid);
}

TEST_CASE("Error: Invalid preamble leaves msg invalid") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x00);
    setBits(bits, 8, 6, 43);
    setBits(bits, 17, 4, 1);
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    bool result = dec.decode(frame, msg, 0);
    CHECK_FALSE(result);
    CHECK_FALSE(msg.valid);
}

TEST_CASE("Error: Invalid MT leaves msg invalid") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 99);
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    bool result = dec.decode(frame, msg, 0);
    CHECK_FALSE(result);
    CHECK_FALSE(msg.valid);
}

TEST_CASE("Error: Invalid disaster category leaves msg invalid") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 17, 4, 7);
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    bool result = dec.decode(frame, msg, 0);
    CHECK_FALSE(result);
    CHECK_FALSE(msg.valid);
}

TEST_CASE("Error: Invalid NMEA checksum rejected") {
    const char* nmea = "$QZQSM,58,9AAF899C80000324000039000548C5E2C000000003DFF8001C000012FE4B0FC*00";
    Message msg{};
    bool ok = decodeNmea(nmea, msg);
    CHECK_FALSE(ok);
}

TEST_CASE("Error: Short NMEA payload rejected") {
    const char* nmea = "$QZQSM,58,9AAF*7F";
    NmeaFramer framer;
    Frame frame;
    bool found = false;
    for (int i = 0; nmea[i]; i++) {
        if (framer.feed((uint8_t)nmea[i], frame)) {
            found = true;
            break;
        }
    }
    CHECK_FALSE(found);
}

TEST_CASE("Error: Version 0 rejected") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 17, 4, 1);
    setBits(bits, 214, 6, 0);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    CHECK_FALSE(dec.decode(frame, msg, 0));
}

TEST_CASE("Error: Version 2 rejected") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 17, 4, 1);
    setBits(bits, 214, 6, 2);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    CHECK_FALSE(dec.decode(frame, msg, 0));
}

TEST_CASE("Error: Version 1 accepted") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 17, 4, 1);
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    CHECK(dec.decode(frame, msg, 0));
}
