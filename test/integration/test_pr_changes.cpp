// test/integration/test_pr_changes.cpp
// Tests corresponding to functionality added/changed in the PR:
//   - Python azarashi package deleted, replaced by C++ azaraC library
//   - NmeaFramer (replaces NmeaQzssDcrDecoder + HexQzssDcrDecoder)
//   - Decoder CRC/preamble/routing (replaces QzssDcrDecoder)
//   - JMA outer frame (replaces QzssDcrDecoderJma): version, RC, DC, time, IT
//   - Ash fall decoder (replaces QzssDcrDecoderJmaAshFall)
//   - Parser class (replaces decode() / decode_stream() API)

#include "../test_helpers.h"
#include "doctest.h"

using namespace azaraC;
using namespace azaraC::internal;

// ═══════════════════════════════════════════════════════════════════════════════
// Helper: build a minimal valid MT=43 frame and return CRC-stamped bits
// ═══════════════════════════════════════════════════════════════════════════════

static void buildMt43Frame(uint8_t* bits, uint8_t disaster_category = 1,
                            uint8_t rc = 1, uint8_t it = 0, uint8_t version = 1) {
    memset(bits, 0, 32);
    setBits(bits, 0,   8, 0x53);             // preamble
    setBits(bits, 8,   6, 43);               // msg_type = 43
    setBits(bits, 14,  3, rc);               // report_classification
    setBits(bits, 17,  4, disaster_category);// disaster_category
    setBits(bits, 21,  4, 1);               // report_time month = 1
    setBits(bits, 25,  5, 1);               // report_time day = 1
    setBits(bits, 30,  5, 0);               // report_time hour = 0
    setBits(bits, 35,  6, 0);               // report_time minute = 0
    setBits(bits, 41,  2, it);              // information_type
    setBits(bits, 214, 6, version);         // version
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);
}

// ═══════════════════════════════════════════════════════════════════════════════
// NmeaFramer edge cases
// (corresponds to deleted NmeaQzssDcrDecoder: prefix check, svid, hex validation)
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("NmeaFramer: non-QZQSM prefix rejected ($GPGGA)") {
    // Feed a $GPGGA sentence — should not produce a frame
    const char* gga = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47\r\n";
    NmeaFramer framer;
    Frame out{};
    bool found = false;
    for (const char* p = gga; *p; ++p) {
        if (framer.feed(static_cast<uint8_t>(*p), out)) { found = true; break; }
    }
    CHECK_FALSE(found);
}

TEST_CASE("NmeaFramer: $ mid-sentence resets state, subsequent valid sentence accepted") {
    uint8_t bits[32] = {};
    bits[0] = 0x53;
    auto valid = makeNmeaQzqsm(55, bits);

    NmeaFramer framer;
    Frame out{};

    // Start feeding a partial sentence then inject a $ to reset
    const char* partial = "$QZQSM,55,AABBCC";
    for (const char* p = partial; *p; ++p) framer.feed(static_cast<uint8_t>(*p), out);

    // Now inject $ (should reset state)
    framer.feed('$', out);

    // Feed the valid sentence from the beginning (without the leading $, since $ was just fed)
    // The valid sentence from makeNmeaQzqsm starts with '$', feeding it:
    bool found = false;
    for (char c : valid) {
        if (framer.feed(static_cast<uint8_t>(c), out)) { found = true; break; }
    }
    REQUIRE(found);
    CHECK(out.svid == 55);
}

TEST_CASE("NmeaFramer: invalid hex character in payload rejected") {
    // Build a valid-looking NMEA with 'G' (invalid hex) in payload
    // "QZQSM,55," + 62 valid hex chars + 1 'G'
    std::string sentence = "QZQSM,55,";
    for (int i = 0; i < 62; ++i) sentence += "A";
    sentence += "G";  // 63rd char is invalid hex

    uint8_t xsum = 0;
    for (char c : sentence) xsum ^= static_cast<uint8_t>(c);
    char tail[8];
    sprintf(tail, "*%02X\r\n", xsum);
    std::string full = "$" + sentence + tail;

    NmeaFramer framer;
    Frame out{};
    bool found = false;
    for (char c : full) {
        if (framer.feed(static_cast<uint8_t>(c), out)) { found = true; break; }
    }
    CHECK_FALSE(found);
}

TEST_CASE("NmeaFramer: svid > 255 is rejected") {
    // Sentence with svid=300 (3 digits > 255)
    std::string sentence = "QZQSM,300,";
    for (int i = 0; i < 63; ++i) sentence += "0";

    uint8_t xsum = 0;
    for (char c : sentence) xsum ^= static_cast<uint8_t>(c);
    char tail[8];
    sprintf(tail, "*%02X\r\n", xsum);
    std::string full = "$" + sentence + tail;

    NmeaFramer framer;
    Frame out{};
    bool found = false;
    for (char c : full) {
        if (framer.feed(static_cast<uint8_t>(c), out)) { found = true; break; }
    }
    CHECK_FALSE(found);
}

TEST_CASE("NmeaFramer: lowercase hex in payload accepted") {
    // Use lowercase hex — hexVal() should handle a-f
    uint8_t bits[32] = {};
    bits[0] = 0xAB;
    bits[1] = 0xCD;

    // Build NMEA manually with lowercase hex
    std::string sentence = "QZQSM,55,";
    for (int i = 0; i < 31; ++i) {
        char buf[3];
        sprintf(buf, "%02x", bits[i]);  // lowercase
        sentence += buf;
    }
    // Add 1 nibble (lowercase)
    char nibble[2];
    sprintf(nibble, "%01x", (bits[31] >> 4) & 0xF);
    sentence += nibble;

    uint8_t xsum = 0;
    for (char c : sentence) xsum ^= static_cast<uint8_t>(c);
    char tail[8];
    sprintf(tail, "*%02X\r\n", xsum);
    std::string full = "$" + sentence + tail;

    NmeaFramer framer;
    Frame out{};
    bool found = false;
    for (char c : full) {
        if (framer.feed(static_cast<uint8_t>(c), out)) { found = true; break; }
    }
    REQUIRE(found);
    CHECK(out.svid == 55);
    CHECK(out.bits[0] == 0xAB);
    CHECK(out.bits[1] == 0xCD);
}

TEST_CASE("NmeaFramer: exactly 63 hex chars accepted (regression)") {
    // This is the normal case — 63 chars = 250 bits (31 full bytes + 1 nibble)
    uint8_t bits[32] = {};
    bits[0] = 0x53;
    auto pkt = makeNmeaQzqsm(193, bits);

    NmeaFramer framer;
    Frame out{};
    bool found = false;
    for (char c : pkt) {
        if (framer.feed(static_cast<uint8_t>(c), out)) { found = true; break; }
    }
    REQUIRE(found);
    CHECK(out.svid == 193);
    CHECK(out.bits[0] == 0x53);
}

TEST_CASE("NmeaFramer: missing comma after svid rejected") {
    // No comma between svid and payload
    std::string sentence = "QZQSM,55";
    for (int i = 0; i < 63; ++i) sentence += "0";  // no comma

    uint8_t xsum = 0;
    for (char c : sentence) xsum ^= static_cast<uint8_t>(c);
    char tail[8];
    sprintf(tail, "*%02X\r\n", xsum);
    std::string full = "$" + sentence + tail;

    NmeaFramer framer;
    Frame out{};
    bool found = false;
    for (char c : full) {
        if (framer.feed(static_cast<uint8_t>(c), out)) { found = true; break; }
    }
    CHECK_FALSE(found);
}

TEST_CASE("NmeaFramer: non-numeric svid rejected") {
    std::string sentence = "QZQSM,5X,";
    for (int i = 0; i < 63; ++i) sentence += "0";

    uint8_t xsum = 0;
    for (char c : sentence) xsum ^= static_cast<uint8_t>(c);
    char tail[8];
    sprintf(tail, "*%02X\r\n", xsum);
    std::string full = "$" + sentence + tail;

    NmeaFramer framer;
    Frame out{};
    bool found = false;
    for (char c : full) {
        if (framer.feed(static_cast<uint8_t>(c), out)) { found = true; break; }
    }
    CHECK_FALSE(found);
}

TEST_CASE("NmeaFramer: checksum mismatch rejected") {
    uint8_t bits[32] = {};
    auto pkt = makeNmeaQzqsm(55, bits);
    // Corrupt the checksum digit (second-to-last before \r\n)
    pkt[pkt.size() - 4] ^= 0x01;  // flip a bit in checksum hex

    NmeaFramer framer;
    Frame out{};
    bool found = false;
    for (char c : pkt) {
        if (framer.feed(static_cast<uint8_t>(c), out)) { found = true; break; }
    }
    CHECK_FALSE(found);
}

// ═══════════════════════════════════════════════════════════════════════════════
// Decoder validation
// (corresponds to deleted QzssDcrDecoder: preamble, CRC, message type routing)
// (corresponds to deleted QzssDcrDecoderJma: version check, RC, DC, IT)
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("Decoder: CRC mismatch with valid preamble rejected") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);  // valid preamble
    setBits(bits, 8, 6, 43);    // valid msg_type
    setBits(bits, 214, 6, 1);   // valid version
    setBits(bits, 17, 4, 1);    // EEW category
    // Do NOT set correct CRC — leave as zeros (wrong CRC)
    // The CRC field at bit 226 is 0, which is almost certainly wrong

    Frame f; f.svid = 193; memcpy(f.bits, bits, 32);
    Decoder dec;
    Message msg{};
    bool ok = dec.decode(f, msg);
    CHECK_FALSE(ok);
}

TEST_CASE("Decoder: invalid preamble (0x52) rejected") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x52);  // 0x52 is NOT a valid preamble
    setBits(bits, 8, 6, 43);
    setBits(bits, 214, 6, 1);
    setBits(bits, 17, 4, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame f; f.svid = 193; memcpy(f.bits, bits, 32);
    Decoder dec;
    Message msg{};
    bool ok = dec.decode(f, msg);
    CHECK_FALSE(ok);
}

TEST_CASE("Decoder: MT=43 version != 1 rejected") {
    // version=0 at bits [214..219]
    uint8_t bits[32] = {};
    setBits(bits, 0,   8, 0x53);
    setBits(bits, 8,   6, 43);
    setBits(bits, 17,  4, 1);    // EEW
    setBits(bits, 214, 6, 0);    // version=0 (unsupported)
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame f; f.svid = 193; memcpy(f.bits, bits, 32);
    Decoder dec;
    Message msg{};
    bool ok = dec.decode(f, msg);
    CHECK_FALSE(ok);
}

TEST_CASE("Decoder: MT=43 version=2 rejected") {
    uint8_t bits[32] = {};
    setBits(bits, 0,   8, 0x53);
    setBits(bits, 8,   6, 43);
    setBits(bits, 17,  4, 1);
    setBits(bits, 214, 6, 2);    // version=2 (unsupported)
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame f; f.svid = 193; memcpy(f.bits, bits, 32);
    Decoder dec;
    Message msg{};
    bool ok = dec.decode(f, msg);
    CHECK_FALSE(ok);
}

TEST_CASE("Decoder: MT=43 unknown disaster category rejected") {
    // Category 7 is not defined in IS-QZSS-DCR-016
    uint8_t bits[32] = {};
    setBits(bits, 0,   8, 0x53);
    setBits(bits, 8,   6, 43);
    setBits(bits, 14,  3, 1);
    setBits(bits, 17,  4, 7);    // category 7 = undefined
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame f; f.svid = 193; memcpy(f.bits, bits, 32);
    Decoder dec;
    Message msg{};
    bool ok = dec.decode(f, msg);
    CHECK_FALSE(ok);
}

TEST_CASE("Decoder: MT=43 category 13 (undefined) rejected") {
    uint8_t bits[32] = {};
    setBits(bits, 0,   8, 0x53);
    setBits(bits, 8,   6, 43);
    setBits(bits, 17,  4, 13);   // 13 = not in spec
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame f; f.svid = 193; memcpy(f.bits, bits, 32);
    Decoder dec;
    Message msg{};
    bool ok = dec.decode(f, msg);
    CHECK_FALSE(ok);
}

TEST_CASE("Decoder: MT=43 report_classification extracted correctly") {
    uint8_t bits[32] = {};
    buildMt43Frame(bits, 1, 5, 0, 1);  // rc=5

    Frame f; f.svid = 193; memcpy(f.bits, bits, 32);
    Decoder dec;
    Message msg{};
    bool ok = dec.decode(f, msg);
    REQUIRE(ok);
    CHECK(msg.mt43.report_classification == 5);
}

TEST_CASE("Decoder: MT=43 information_type extracted correctly") {
    // information_type at bits [41..42]: test with it=2
    uint8_t bits[32] = {};
    buildMt43Frame(bits, 1, 1, 2, 1);  // it=2

    Frame f; f.svid = 193; memcpy(f.bits, bits, 32);
    Decoder dec;
    Message msg{};
    bool ok = dec.decode(f, msg);
    REQUIRE(ok);
    CHECK(msg.mt43.information_type == 2);
}

TEST_CASE("Decoder: MT=43 all valid disaster categories are accepted") {
    // categories: 1,2,3,4,5,6,8,9,10,11,12,14 (4=Nankai accepted by Decoder directly)
    const uint8_t valid_cats[] = {1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 14};
    for (uint8_t cat : valid_cats) {
        uint8_t bits[32] = {};
        buildMt43Frame(bits, cat);

        Frame f; f.svid = 193; memcpy(f.bits, bits, 32);
        Decoder dec;
        Message msg{};
        bool ok = dec.decode(f, msg);
        CAPTURE(cat);
        CHECK(ok);
        CHECK(msg.mt43.disaster_category == cat);
    }
}

TEST_CASE("Decoder: MT=43 svid is preserved in Message") {
    uint8_t bits[32] = {};
    buildMt43Frame(bits, 1);

    Frame f; f.svid = 57; memcpy(f.bits, bits, 32);
    Decoder dec;
    Message msg{};
    bool ok = dec.decode(f, msg);
    REQUIRE(ok);
    CHECK(msg.svid == 57);
    CHECK(msg.msg_type == 43);
}

TEST_CASE("Decoder: MT=43 report_time fields extracted") {
    uint8_t bits[32] = {};
    memset(bits, 0, 32);
    setBits(bits, 0,   8, 0x53);
    setBits(bits, 8,   6, 43);
    setBits(bits, 14,  3, 1);
    setBits(bits, 17,  4, 1);    // EEW
    setBits(bits, 21,  4, 6);    // month=6
    setBits(bits, 25,  5, 15);   // day=15
    setBits(bits, 30,  5, 12);   // hour=12
    setBits(bits, 35,  6, 30);   // minute=30
    setBits(bits, 41,  2, 0);
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame f; f.svid = 193; memcpy(f.bits, bits, 32);
    Decoder dec;
    Message msg{};
    uint32_t now = 1750000000u;  // some unix time in 2025
    bool ok = dec.decode(f, msg, now);
    REQUIRE(ok);
    CHECK(msg.mt43.event_time.day == 15);
    CHECK(msg.mt43.event_time.hour == 12);
    CHECK(msg.mt43.event_time.minute == 30);
}

// ═══════════════════════════════════════════════════════════════════════════════
// Ash Fall decoder tests
// (corresponds to deleted QzssDcrDecoderJmaAshFall)
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("AshFall: warning_type=1 (速報) decoded") {
    uint8_t bits[32] = {};
    // activity_time: extractDHM at offset 53 (day 5bit+hour 5bit+min 6bit)
    setBits(bits, 53,  5, 10);   // day=10
    setBits(bits, 58,  5, 8);    // hour=8
    setBits(bits, 63,  6, 0);    // min=0
    setBits(bits, 69,  2, 1);    // warning_type=1 (速報)
    setBits(bits, 71, 12, 500);  // volcano_name code=500
    // No entries (all zeros at offset 83+)

    Message msg{};
    TestDecoder::testDecodeAshFall(bits, msg, 1704067200u);

    CHECK(msg.mt43.ash.warning_type == 1);
    CHECK(msg.mt43.ash.volcano_name == 500);
    CHECK(msg.mt43.ash.count == 0);
    CHECK(msg.mt43.ash.activity_time.day == 10);
    CHECK(msg.mt43.ash.activity_time.hour == 8);
}

TEST_CASE("AshFall: warning_type=2 (詳細) decoded") {
    uint8_t bits[32] = {};
    setBits(bits, 53,  5, 20);
    setBits(bits, 58,  5, 14);
    setBits(bits, 63,  6, 30);
    setBits(bits, 69,  2, 2);    // warning_type=2 (詳細)
    setBits(bits, 71, 12, 100);  // volcano_name=100

    Message msg{};
    TestDecoder::testDecodeAshFall(bits, msg, 1704067200u);

    CHECK(msg.mt43.ash.warning_type == 2);
    CHECK(msg.mt43.ash.volcano_name == 100);
}

TEST_CASE("AshFall: single entry decoded") {
    uint8_t bits[32] = {};
    setBits(bits, 69, 2, 1);     // warning_type=1
    setBits(bits, 71, 12, 200);  // volcano_name

    // Entry 0 at offset 83: time(3)+code(3)+lg(23)=29 bits
    setBits(bits, 83, 3, 5);     // arrival_hour=5
    setBits(bits, 86, 3, 3);     // warning_code=3
    setBits(bits, 89, 23, 12345); // local_gov=12345

    Message msg{};
    TestDecoder::testDecodeAshFall(bits, msg, 1704067200u);

    CHECK(msg.mt43.ash.count == 1);
    CHECK(msg.mt43.ash.entries_time[0] == 5);
    CHECK(msg.mt43.ash.entries_code[0] == 3);
    CHECK(msg.mt43.ash.entries_lg[0] == 12345);
}

TEST_CASE("AshFall: zero entries (all zeros at offset 83)") {
    uint8_t bits[32] = {};
    setBits(bits, 69, 2, 1);
    setBits(bits, 71, 12, 50);
    // Offset 83 is all zeros → no entries

    Message msg{};
    TestDecoder::testDecodeAshFall(bits, msg, 1704067200u);

    CHECK(msg.mt43.ash.count == 0);
}

TEST_CASE("AshFall: multiple entries (up to 4)") {
    uint8_t bits[32] = {};
    setBits(bits, 69, 2, 2);
    setBits(bits, 71, 12, 300);

    // 4 entries, each non-zero at offset 83 + i*29
    for (int i = 0; i < 4; ++i) {
        uint16_t off = 83 + i * 29;
        setBits(bits, off,     3, i + 1);     // arrival_hour
        setBits(bits, off + 3, 3, i + 2);     // warning_code
        setBits(bits, off + 6, 23, 100 + i);  // local_gov (non-zero)
    }

    Message msg{};
    TestDecoder::testDecodeAshFall(bits, msg, 1704067200u);

    CHECK(msg.mt43.ash.count == 4);
    for (int i = 0; i < 4; ++i) {
        CAPTURE(i);
        CHECK(msg.mt43.ash.entries_time[i] == static_cast<uint8_t>(i + 1));
        CHECK(msg.mt43.ash.entries_code[i] == static_cast<uint8_t>(i + 2));
        CHECK(msg.mt43.ash.entries_lg[i] == static_cast<uint32_t>(100 + i));
    }
}

TEST_CASE("AshFall: volcano_name code boundaries") {
    // Test code=0 (minimum)
    {
        uint8_t bits[32] = {};
        setBits(bits, 69, 2, 1);
        setBits(bits, 71, 12, 0);  // code=0
        Message msg{};
        TestDecoder::testDecodeAshFall(bits, msg, 0);
        CHECK(msg.mt43.ash.volcano_name == 0);
    }

    // Test code=4095 (maximum for 12 bits)
    {
        uint8_t bits[32] = {};
        setBits(bits, 69, 2, 1);
        setBits(bits, 71, 12, 4095);  // max 12-bit value
        Message msg{};
        TestDecoder::testDecodeAshFall(bits, msg, 0);
        CHECK(msg.mt43.ash.volcano_name == 4095);
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
// Parser class end-to-end tests
// (corresponds to deleted azarashi.decode() / decode_stream() API)
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("Parser: AUTO mode with valid NMEA returns Message") {
    uint8_t bits[32] = {};
    buildMt43Frame(bits, 1);  // EEW, version=1

    auto nmea = makeNmeaQzqsm(55, bits);

    Parser parser;
    Message msg{};
    bool got = false;
    for (char c : nmea) {
        if (parser.feed(static_cast<uint8_t>(c), msg)) { got = true; break; }
    }
    REQUIRE(got);
    CHECK(msg.valid == true);
    CHECK(msg.msg_type == 43);
    CHECK(msg.svid == 55);
    CHECK(msg.mt43.disaster_category == 1);
}

TEST_CASE("Parser: AUTO mode with valid UBX returns Message") {
    uint8_t bits[32] = {};
    buildMt43Frame(bits, 1);  // EEW

    auto ubx = makeUbxSfrbx(193, bits);

    Parser parser;
    Message msg{};
    bool got = false;
    for (uint8_t b : ubx) {
        if (parser.feed(b, msg)) { got = true; break; }
    }
    REQUIRE(got);
    CHECK(msg.valid == true);
    CHECK(msg.msg_type == 43);
    CHECK(msg.svid == 193);
}

TEST_CASE("Parser: deduplication suppresses same message on second feed") {
    uint8_t bits[32] = {};
    buildMt43Frame(bits, 1);
    auto nmea = makeNmeaQzqsm(55, bits);

    Parser parser;
    Message msg{};

    // First pass: should succeed
    bool first = false;
    for (char c : nmea) {
        if (parser.feed(static_cast<uint8_t>(c), msg)) { first = true; break; }
    }
    REQUIRE(first);

    // Second pass (identical message): should be suppressed by dedup
    bool second = false;
    for (char c : nmea) {
        if (parser.feed(static_cast<uint8_t>(c), msg)) { second = true; break; }
    }
    CHECK_FALSE(second);
}

TEST_CASE("Parser: reset() clears dedup state, same message accepted again") {
    uint8_t bits[32] = {};
    buildMt43Frame(bits, 1);
    auto nmea = makeNmeaQzqsm(55, bits);

    Parser parser;
    Message msg{};

    // First pass
    bool first = false;
    for (char c : nmea) {
        if (parser.feed(static_cast<uint8_t>(c), msg)) { first = true; break; }
    }
    REQUIRE(first);

    // Second pass without reset: suppressed
    bool second = false;
    for (char c : nmea) {
        if (parser.feed(static_cast<uint8_t>(c), msg)) { second = true; break; }
    }
    CHECK_FALSE(second);

    // Reset and try again: should succeed
    parser.reset();
    bool third = false;
    for (char c : nmea) {
        if (parser.feed(static_cast<uint8_t>(c), msg)) { third = true; break; }
    }
    CHECK(third);
}

TEST_CASE("Parser: different svid same content are NOT duplicates") {
    uint8_t bits[32] = {};
    buildMt43Frame(bits, 1);

    auto nmea55 = makeNmeaQzqsm(55, bits);
    auto nmea56 = makeNmeaQzqsm(56, bits);

    Parser parser;
    Message msg{};

    bool got55 = false;
    for (char c : nmea55) {
        if (parser.feed(static_cast<uint8_t>(c), msg)) { got55 = true; break; }
    }
    REQUIRE(got55);
    CHECK(msg.svid == 55);

    // Different svid — dedup key includes svid, so should pass
    bool got56 = false;
    for (char c : nmea56) {
        if (parser.feed(static_cast<uint8_t>(c), msg)) { got56 = true; break; }
    }
    // NOTE: dedup key = {svid, msg_type, crc24} so different svid → not duplicate
    CHECK(got56);
    CHECK(msg.svid == 56);
}

TEST_CASE("Parser: invalid NMEA (CRC mismatch in QZSS frame) is rejected") {
    // Feed garbage NMEA that parses as a frame but fails CRC check
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 214, 6, 1);
    setBits(bits, 17, 4, 1);
    // Intentionally wrong CRC: set all CRC bits to 0
    // crc24qRef would give something non-zero, so leaving as 0 fails CRC check

    auto nmea = makeNmeaQzqsm(55, bits);

    Parser parser;
    Message msg{};
    bool got = false;
    for (char c : nmea) {
        if (parser.feed(static_cast<uint8_t>(c), msg)) { got = true; break; }
    }
    CHECK_FALSE(got);
}

TEST_CASE("Parser: mixed NMEA garbage then valid NMEA succeeds") {
    uint8_t bits[32] = {};
    buildMt43Frame(bits, 1);
    auto nmea = makeNmeaQzqsm(55, bits);

    Parser parser;
    Message msg{};

    // Feed garbage first
    const char* garbage = "JUNK DATA $GPGGA RANDOM BYTES\r\n";
    for (const char* p = garbage; *p; ++p) parser.feed(static_cast<uint8_t>(*p), msg);

    // Then feed valid NMEA
    bool got = false;
    for (char c : nmea) {
        if (parser.feed(static_cast<uint8_t>(c), msg)) { got = true; break; }
    }
    REQUIRE(got);
    CHECK(msg.msg_type == 43);
}

TEST_CASE("Parser: MT=44 message decoded via NMEA") {
    uint8_t bits[32] = {};
    // Build a minimal MT=44 L-Alert frame
    setBits(bits, 0,   8, 0x53);
    setBits(bits, 8,   6, 44);
    setBits(bits, 14,  1, 0);
    setBits(bits, 15,  9, 0x1FF);
    setBits(bits, 24,  2, 1);    // A1
    setBits(bits, 26,  9, 111);  // A2=Japan
    setBits(bits, 35,  5, 1);    // A3=1 → L-Alert
    setBits(bits, 40,  7, 10);   // A4
    setBits(bits, 47,  2, 3);    // A5
    setBits(bits, 214, 6, 1);    // vn=1
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    auto nmea = makeNmeaQzqsm(55, bits);

    Parser parser;
    Message msg{};
    bool got = false;
    for (char c : nmea) {
        if (parser.feed(static_cast<uint8_t>(c), msg)) { got = true; break; }
    }
    REQUIRE(got);
    CHECK(msg.msg_type == 44);
    CHECK(msg.mt44.service_kind == Mt44ServiceKind::LAlert);
}

TEST_CASE("Parser: with custom framer uses that framer exclusively") {
    // Use NmeaFramer as custom framer
    NmeaFramer custom_framer;
    Parser parser(custom_framer);

    uint8_t bits[32] = {};
    buildMt43Frame(bits, 1);
    auto nmea = makeNmeaQzqsm(55, bits);

    Message msg{};
    bool got = false;
    for (char c : nmea) {
        if (parser.feed(static_cast<uint8_t>(c), msg)) { got = true; break; }
    }
    REQUIRE(got);
    CHECK(msg.svid == 55);
    CHECK(msg.msg_type == 43);
}

// ═══════════════════════════════════════════════════════════════════════════════
// Additional boundary and regression tests
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("Decoder: all-zeros frame rejected (invalid preamble)") {
    uint8_t bits[32] = {};
    Frame f; f.svid = 193; memcpy(f.bits, bits, 32);
    Decoder dec;
    Message msg{};
    bool ok = dec.decode(f, msg);
    CHECK_FALSE(ok);
}

TEST_CASE("Decoder: MT=43 EEW with zero regions succeeds") {
    uint8_t bits[32] = {};
    // preamble + EEW frame with no forecast regions set
    setBits(bits, 0,   8, 0x53);
    setBits(bits, 8,   6, 43);
    setBits(bits, 14,  3, 1);
    setBits(bits, 17,  4, 1);    // EEW
    setBits(bits, 21,  4, 1);
    setBits(bits, 25,  5, 1);
    setBits(bits, 30,  5, 0);
    setBits(bits, 35,  6, 0);
    setBits(bits, 41,  2, 0);
    setBits(bits, 214, 6, 1);
    // No region bits set (bits [130..209] are 0)
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame f; f.svid = 193; memcpy(f.bits, bits, 32);
    Decoder dec;
    Message msg{};
    bool ok = dec.decode(f, msg);
    REQUIRE(ok);
    CHECK(msg.mt43.disaster_category == 1);
    CHECK(msg.mt43.eew.region_count == 0);
}

TEST_CASE("Decoder: MT=43 disaster_category field correct range [0..15]") {
    // All 16 possible 4-bit values — only valid ones should decode
    // Valid categories: 1,2,3,4,5,6,8,9,10,11,12,14
    // Invalid: 0,7,13,15
    const bool expected_valid[16] = {
        false,  // 0  - not defined
        true,   // 1  - EEW
        true,   // 2  - Hypocenter
        true,   // 3  - Seismic
        true,   // 4  - Nankai (handled specially via page buffer, but valid frame)
        true,   // 5  - Tsunami
        true,   // 6  - NW Pacific Tsunami
        false,  // 7  - undefined
        true,   // 8  - Volcano
        true,   // 9  - Ash Fall
        true,   // 10 - Weather
        true,   // 11 - Flood
        true,   // 12 - Typhoon
        false,  // 13 - undefined
        true,   // 14 - Marine
        false,  // 15 - undefined
    };

    for (int cat = 0; cat <= 15; ++cat) {
        uint8_t bits[32] = {};
        setBits(bits, 0,   8, 0x53);
        setBits(bits, 8,   6, 43);
        setBits(bits, 14,  3, 1);
        setBits(bits, 17,  4, static_cast<uint8_t>(cat));
        setBits(bits, 21,  4, 1);
        setBits(bits, 25,  5, 1);
        setBits(bits, 30,  5, 0);
        setBits(bits, 35,  6, 0);
        setBits(bits, 214, 6, 1);
        uint32_t crc = crc24qRef(bits, 226);
        setBits(bits, 226, 24, crc);

        Frame f; f.svid = 193; memcpy(f.bits, bits, 32);
        Decoder dec;
        Message msg{};
        bool ok = dec.decode(f, msg);
        CAPTURE(cat);
        CHECK(ok == expected_valid[cat]);
    }
}

TEST_CASE("NmeaFramer: newline mid-sentence resets (\\n inside sentence)") {
    NmeaFramer framer;
    Frame out{};

    // Feed start of a sentence then inject newline
    const char* prefix = "$QZQSM,55,";
    for (const char* p = prefix; *p; ++p) framer.feed(static_cast<uint8_t>(*p), out);
    framer.feed('\n', out);  // should reset

    // Now feed a valid sentence
    uint8_t bits[32] = {};
    bits[0] = 0x53;
    auto pkt = makeNmeaQzqsm(193, bits);
    bool found = false;
    for (char c : pkt) {
        if (framer.feed(static_cast<uint8_t>(c), out)) { found = true; break; }
    }
    REQUIRE(found);
    CHECK(out.svid == 193);
}

TEST_CASE("AshFall: entry termination when 29-bit block is zero") {
    uint8_t bits[32] = {};
    setBits(bits, 69, 2, 1);
    setBits(bits, 71, 12, 42);

    // First entry: non-zero
    setBits(bits, 83, 3, 2);
    setBits(bits, 86, 3, 1);
    setBits(bits, 89, 23, 5000);

    // Second entry: all zeros (29 bits = 0) → terminate
    // (bits 112..140 are already zero)

    Message msg{};
    TestDecoder::testDecodeAshFall(bits, msg, 1704067200u);

    CHECK(msg.mt43.ash.count == 1);
    CHECK(msg.mt43.ash.entries_time[0] == 2);
    CHECK(msg.mt43.ash.entries_code[0] == 1);
    CHECK(msg.mt43.ash.entries_lg[0] == 5000);
}

TEST_CASE("Decoder: MT=43 report_classification boundaries") {
    // report_classification is 3 bits [14..16]: values 0-7 all valid in spec
    for (uint8_t rc = 0; rc <= 7; ++rc) {
        uint8_t bits[32] = {};
        buildMt43Frame(bits, 1, rc, 0, 1);

        Frame f; f.svid = 193; memcpy(f.bits, bits, 32);
        Decoder dec;
        Message msg{};
        bool ok = dec.decode(f, msg);
        CAPTURE(rc);
        CHECK(ok);
        CHECK(msg.mt43.report_classification == rc);
    }
}

TEST_CASE("Decoder: information_type all valid values (0-3)") {
    for (uint8_t it = 0; it <= 3; ++it) {
        uint8_t bits[32] = {};
        buildMt43Frame(bits, 1, 1, it, 1);

        Frame f; f.svid = 193; memcpy(f.bits, bits, 32);
        Decoder dec;
        Message msg{};
        bool ok = dec.decode(f, msg);
        CAPTURE(it);
        CHECK(ok);
        CHECK(msg.mt43.information_type == it);
    }
}
