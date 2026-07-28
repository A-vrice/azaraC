// test/integration/test_error_handling.cpp  Eエラーハンドリング詳細チE��チE
#include <string>
#include "doctest.h"
#include "../src/Parser.h"
#include "../test_helpers.h"

using namespace azaraC;

TEST_CASE("Error: NMEA 65 char payload rejected") {
    char nmea[256];
    strcpy(nmea, "$QZQSM,55,");
    size_t offset = strlen(nmea);
    for (int i = 0; i < 65; i++) {
        REQUIRE(offset < sizeof(nmea));
        REQUIRE(snprintf(nmea + offset, sizeof(nmea) - offset, "%X", i % 16) == 1);
        offset += 1;  // known fixed width per iteration
    }
    uint8_t xsum = 0;
    for (size_t i = 1; i < offset; i++) {
        xsum ^= (uint8_t)nmea[i];
    }
    REQUIRE(offset < sizeof(nmea) - 5);
    REQUIRE(snprintf(nmea + offset, sizeof(nmea) - offset, "*%02X\r\n", xsum) == 5);

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

#if (AZARAC_ENABLE_EEW)
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
#endif // AZARAC_ENABLE_EEW

// ══════════════════════════════════════════════════════════════════════════════╁E// チE��ーダエチE��ケースチE��チE(decoder_edge_cases.md)
// ══════════════════════════════════════════════════════════════════════════════╁E
// Helper: build a valid MT=43 frame with custom disaster_category
static void buildMt43Frame(uint8_t category, uint8_t* bits) {
    memset(bits, 0, 32);
    setBits(bits, 0, 8, 0x53);       // Preamble
    setBits(bits, 8, 6, 43);         // msg_type
    setBits(bits, 14, 3, 1);         // report_classification = 1 (訓練)
    setBits(bits, 17, 4, category);  // disaster_category
    setBits(bits, 214, 6, 1);        // version = 1
}

TEST_CASE("Decoder: disaster_category=7 (unassigned) rejected") {
    uint8_t bits[32];
    buildMt43Frame(7, bits);
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

TEST_CASE("Decoder: disaster_category=13 (reserved) rejected") {
    uint8_t bits[32];
    buildMt43Frame(13, bits);
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

#if (AZARAC_ENABLE_EEW)
TEST_CASE("Decoder: report_classification all values 0-7") {
    for (uint8_t rc = 0; rc <= 7; ++rc) {
        uint8_t bits[32] = {};
        setBits(bits, 0, 8, 0x53);
        setBits(bits, 8, 6, 43);
        setBits(bits, 14, 3, rc);
        setBits(bits, 17, 4, 1);         // disaster_category = 1 (EEW)
        setBits(bits, 214, 6, 1);
        uint32_t crc = crc24qRef(bits, 226);
        setBits(bits, 226, 24, crc);

        Frame frame{};
        memcpy(frame.bits, bits, 32);
        frame.svid = 193;
        Decoder dec;
        Message msg{};
        bool result = dec.decode(frame, msg, 1704067200u);
        INFO("report_classification=", rc);
        CHECK(result);
        CHECK(msg.valid);
    }
}
TEST_CASE("Decoder: information_type all values 0-3") {
    for (uint8_t it = 0; it <= 3; ++it) {
        uint8_t bits[32] = {};
        setBits(bits, 0, 8, 0x53);
        setBits(bits, 8, 6, 43);
        setBits(bits, 14, 3, 1);
        setBits(bits, 17, 4, 1);         // disaster_category = 1 (EEW)
        setBits(bits, 41, 2, it);        // information_type
        setBits(bits, 214, 6, 1);
        uint32_t crc = crc24qRef(bits, 226);
        setBits(bits, 226, 24, crc);

        Frame frame{};
        memcpy(frame.bits, bits, 32);
        frame.svid = 193;
        Decoder dec;
        Message msg{};
        bool result = dec.decode(frame, msg, 1704067200u);
        INFO("information_type=", it);
        CHECK(result);
        CHECK(msg.valid);
    }
}
#endif // AZARAC_ENABLE_EEW

#if (AZARAC_ENABLE_DCX_CAMF)
TEST_CASE("Decoder: MT=44 A12=0 with EX1!=0 target_area_code present") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);         // MT=44
    setBits(bits, 24, 2, 1);         // a1=1 (Alert)
    setBits(bits, 26, 9, 111);       // a2=111 (Japan)
    setBits(bits, 35, 5, 1);         // a3=1 (Foundation for MultiMedia Communications) - 5 bits
    setBits(bits, 40, 7, 10);        // a4=10 - 7 bits
    setBits(bits, 47, 2, 3);         // a5=3 - 2 bits
    // A12-A16 (main ellipse) = 0
    // EX1 at bit 146 (16 bits) = 1100 (札幌市中央区)
    setBits(bits, 146, 16, 1100);
    setBits(bits, 214, 6, 1);        // version
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    bool result = dec.decode(frame, msg, 0);
    REQUIRE(result);
    CHECK(msg.valid);

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->mt44_decoded.target_area_code_present == true);
    CHECK(mt44->mt44_decoded.target_area_code == 1100);
}

TEST_CASE("Decoder: MT=44 EX8=1 (city code list mode)") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);         // MT=44
    setBits(bits, 24, 2, 2);         // a1=2 (Update)
    setBits(bits, 26, 9, 111);       // a2=111 (Japan)
    setBits(bits, 35, 5, 2);         // a3=2 (Fire and Disaster Management Agency) - 5 bits
    setBits(bits, 40, 7, 5);         // a4=5 - 7 bits
    setBits(bits, 47, 2, 3);         // a5=3 - 2 bits
    // EX8 at bit 146 (1 bit) = 1 (city code list mode)
    setBits(bits, 146, 1, 1);
    // EX9 at bit 147 (64 bits) = 4 city codes (each 16 bits)
    // ex9 = (ex9_hi << 32) | ex9_lo
    // ex9_hi = bits 147..178, ex9_lo = bits 179..210
    // Code 1 = ex9[0:15] = ex9_lo[0:15] = bits 179..194
    // Code 2 = ex9[16:31] = ex9_lo[16:31] = bits 195..210
    // Code 3 = ex9[32:47] = ex9_hi[0:15] = bits 147..162
    // Code 4 = ex9[48:63] = ex9_hi[16:31] = bits 163..178
    setBits(bits, 179, 16, 1100);    // city 1 (ex9[0:15])
    setBits(bits, 195, 16, 1101);    // city 2 (ex9[16:31])
    setBits(bits, 147, 16, 1102);    // city 3 (ex9[32:47])
    setBits(bits, 163, 16, 1103);    // city 4 (ex9[48:63])
    setBits(bits, 214, 6, 1);        // version
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    bool result = dec.decode(frame, msg, 0);
    REQUIRE(result);

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->mt44_decoded.jalert_prefecture_mode == false);
    CHECK(mt44->mt44_decoded.city_code_count == 4);
    // Verify all 4 codes are decoded in the exact ex9 bit layout order
    // produced by decodeCityCodeList (ex9[0:15], ex9[16:31], ex9[32:47],
    // ex9[48:63]). With the fixture below this yields [1101, 1100, 1103, 1102].
    CHECK(mt44->mt44_decoded.city_codes[0] == 1101);
    CHECK(mt44->mt44_decoded.city_codes[1] == 1100);
    CHECK(mt44->mt44_decoded.city_codes[2] == 1103);
    CHECK(mt44->mt44_decoded.city_codes[3] == 1102);
}

TEST_CASE("Decoder: MT=44 Outside Japan ex11_raw JSON output") {
    // Use a synthetic Outside Japan message
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);         // MT=44
    setBits(bits, 24, 2, 3);         // a1=3 (All Clear)
    setBits(bits, 26, 9, 71);        // a2=71 (Fiji) - triggers OutsideJapan branch (a2 != 111)
    setBits(bits, 35, 5, 2);         // a3=2 (Fiji Meteorological Service)
    setBits(bits, 40, 7, 5);         // a4=5 - 7 bits
    setBits(bits, 47, 2, 3);         // a5=3 - 2 bits
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    bool result = dec.decode(frame, msg, 0);
    REQUIRE(result);

    // Verify JSON output contains ex11_raw
    StringPrint sp;
    internal::JsonSerializer::serialize(msg, sp);
    const auto& s = sp.str();
    CHECK(s.find("\"ex11_raw\":") != std::string::npos);
}

TEST_CASE("Decoder: MT=44 A17/A18 specific settings output") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);         // MT=44
    setBits(bits, 24, 2, 1);         // a1=1 (Alert)
    setBits(bits, 26, 9, 111);       // a2=111 (Japan)
    setBits(bits, 35, 5, 1);         // a3=1 (Foundation for MultiMedia Communications)
    setBits(bits, 40, 7, 10);        // a4=10
    setBits(bits, 47, 2, 3);         // a5=3
    // A17 at bit 129 (2 bits) = 2
    setBits(bits, 129, 2, 2);
    // A18 at bit 131 (15 bits) = 0x1234
    setBits(bits, 131, 15, 0x1234);
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    bool result = dec.decode(frame, msg, 0);
    REQUIRE(result);

    // Verify JSON output contains a17/a18
    StringPrint sp;
    internal::JsonSerializer::serialize(msg, sp);
    const auto& s = sp.str();
    CHECK(s.find("\"a17_type_of_specific_settings\":") != std::string::npos);
    CHECK(s.find("\"a18_specific_settings\":") != std::string::npos);
}

TEST_CASE("Decoder: MT=44 D36 typhoon category output") {
    // D36 (typhoon category) is decoded from A18[14:12] (top 3 bits of A18)
    // A18 starts at bit 131, so A18[14:12] = bits 131..133
    // DcxHelper.cpp: r.d36 = (a18 >> 12) & 0x07;
    for (uint8_t d36_val = 0; d36_val <= 7; ++d36_val) {
        uint8_t bits[32] = {};
        setBits(bits, 0, 8, 0x53);
        setBits(bits, 8, 6, 44);         // MT=44
        setBits(bits, 24, 2, 1);         // a1=1 (Alert)
        setBits(bits, 26, 9, 111);       // a2=111 (Japan)
        setBits(bits, 35, 5, 1);         // a3=1
        setBits(bits, 40, 7, 82);        // a4=82 (Typhoon)
        setBits(bits, 47, 2, 3);         // a5=3
        setBits(bits, 129, 2, 3);        // A17=3 (B4 detailed info)
        // A18 at bit 131: d36 at a18[14:12] = spec bits 131..133
        setBits(bits, 131, 3, d36_val);
        // d8 at a18[11:8] = spec bits 134..137, d9 at a18[7:5] = spec bits 138..140
        setBits(bits, 134, 4, 5);        // d8=5
        setBits(bits, 138, 3, 2);        // d9=2
        setBits(bits, 214, 6, 1);        // version
        uint32_t crc = crc24qRef(bits, 226);
        setBits(bits, 226, 24, crc);

        Frame frame{};
        memcpy(frame.bits, bits, 32);
        frame.svid = 193;
        Decoder dec;
        Message msg{};
        bool result = dec.decode(frame, msg, 0);
        INFO("d36_val=", d36_val);
        REQUIRE(result);
        CHECK(msg.valid);

        const Mt44Data* mt44 = msg.getMt44();
        REQUIRE(mt44 != nullptr);

        // Verify JSON output contains d36_typhoon_cat field (with embedded label)
        StringPrint sp;
        internal::JsonSerializer::serialize(msg, sp);
        const auto& s = sp.str();
        auto pos = s.find("\"d36_typhoon_cat\":");
        CHECK(pos != std::string::npos);
        // Find closing '}' of the d36_typhoon_cat nested object to bound search
        auto close_brace = s.find('}', pos);
        CHECK(close_brace != std::string::npos);
        auto label_pos = s.find("\"label\":", pos);
        CHECK(label_pos != std::string::npos);
        CHECK(label_pos <= close_brace);
    }
}
#endif
