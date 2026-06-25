// test/framer/test_framer.cpp — フレーマーテスト
// UBX/NMEA フレーマーの統合テスト

#define ARDUINO 0
#include "../test_helpers.h"
#include "doctest.h"
#include <cstring>

using namespace azaraC;

// ── UBX Tests ──────────────────────────────────────────────────────────────

TEST_CASE("UBX Framer Basic") {
    // svId=2 (u-blox) -> PRN184 (QZS-2 L1S)
    uint8_t bits[32] = {0x53, 0xAB};
    auto pkt = makeUbxSfrbx(2, bits);

    UbxFramer framer;
    Frame out;
    bool found = false;
    for (auto b : pkt) {
        if (framer.feed(b, out)) { found = true; break; }
    }

    REQUIRE(found);
    CHECK(out.svid == 184);  // svId=2 -> PRN184
    CHECK(out.bits[0] == 0x53);
}

TEST_CASE("UBX Checksum Error") {
    uint8_t bits[32] = {0};
    auto pkt = makeUbxSfrbx(2, bits);
    pkt[10] ^= 0xFF; // Corrupt header/payload

    UbxFramer framer;
    Frame out;
    bool found = false;
    for (auto b : pkt) {
        if (framer.feed(b, out)) found = true;
    }
    CHECK_FALSE(found);
}

TEST_CASE("UBX Garbage Recovery") {
    // svId=3 (u-blox) -> PRN185 (QZS-4 L1S)
    uint8_t bits[32] = {0x9A};
    auto pkt = makeUbxSfrbx(3, bits);

    UbxFramer framer;
    Frame out;
    // Feed garbage
    for (int i = 0; i < 100; ++i) framer.feed(0xAA, out);

    // Feed valid
    bool found = false;
    for (auto b : pkt) {
        if (framer.feed(b, out)) { found = true; break; }
    }
    REQUIRE(found);
    CHECK(out.svid == 185);  // svId=3 -> PRN185
}

TEST_CASE("UBX: SFRBX basic decode") {
    uint8_t nav_bits[32] = {0x53, 0xAB};
    auto pkt = makeUbxSfrbx(2, nav_bits);

    UbxFramer framer;
    Frame ubx_frame;
    bool found = false;
    for (auto b : pkt) {
        if (framer.feed(b, ubx_frame)) { found = true; break; }
    }
    REQUIRE(found);
    CHECK(ubx_frame.svid == 184);
    CHECK(ubx_frame.bits[0] == 0x53);
}

TEST_CASE("UBX: SFRBX round-trip with NMEA") {
    // svId=7 (u-blox) -> PRN189 (QZS-3 L1S)
    uint8_t nav_bits[32] = {};
    nav_bits[0] = 0x53;
    nav_bits[1] = 0x2F;

    auto pkt = makeUbxSfrbx(7, nav_bits);

    UbxFramer framer;
    Frame ubx_frame;
    bool found = false;
    for (auto b : pkt) {
        if (framer.feed(b, ubx_frame)) { found = true; break; }
    }
    REQUIRE(found);
    CHECK(ubx_frame.svid == 189);  // svId=7 -> PRN189
}

TEST_CASE("UBX: SFRBX with different svid") {
    // svId=4 (u-blox) -> PRN186 (QZS-1R L1S)
    uint8_t nav_bits[32] = {0x9A, 0xCD};
    auto pkt = makeUbxSfrbx(4, nav_bits);

    UbxFramer framer;
    Frame ubx_frame;
    bool found = false;
    for (auto b : pkt) {
        if (framer.feed(b, ubx_frame)) { found = true; break; }
    }
    REQUIRE(found);
    CHECK(ubx_frame.svid == 186);  // svId=4 -> PRN186
}

TEST_CASE("UBX: Checksum error rejection") {
    uint8_t nav_bits[32] = {0x53, 0xAB};
    auto pkt = makeUbxSfrbx(2, nav_bits);

    // Corrupt the checksum
    pkt[pkt.size() - 1] ^= 0xFF;

    UbxFramer framer;
    Frame ubx_frame;
    bool found = false;
    for (auto b : pkt) {
        if (framer.feed(b, ubx_frame)) { found = true; break; }
    }
    CHECK_FALSE(found);
}

TEST_CASE("UBX: Garbage recovery") {
    uint8_t nav_bits[32] = {0x9A};
    auto pkt = makeUbxSfrbx(3, nav_bits);

    UbxFramer framer;
    Frame ubx_frame;
    bool found = false;
    for (auto b : pkt) {
        if (framer.feed(b, ubx_frame)) { found = true; break; }
    }
    REQUIRE(found);
    CHECK(ubx_frame.svid == 185);
}

// ── NMEA Tests ──────────────────────────────────────────────────────────────

TEST_CASE("NMEA Framer Basic") {
    // $QZQSM svid=56 -> PRN184 (QZS-2 L1S)
    uint8_t bits[32];
    for(int i=0; i<32; ++i) bits[i] = i;
    auto pkt = makeNmeaQzqsm(56, bits);

    NmeaFramer framer;
    Frame out;
    bool found = false;
    for (char c : pkt) {
        if (framer.feed((uint8_t)c, out)) { found = true; break; }
    }
    REQUIRE(found);
    CHECK(out.svid == 184);  // NMEA 56 + 128 = PRN184
    CHECK(out.bits[1] == 1);
}

TEST_CASE("NMEA Checksum Error") {
    uint8_t bits[32] = {0};
    auto pkt = makeNmeaQzqsm(56, bits);
    pkt[pkt.size() - 3] = '0'; // Corrupt checksum last digit

    NmeaFramer framer;
    Frame out;
    bool found = false;
    for (char c : pkt) {
        if (framer.feed((uint8_t)c, out)) found = true;
    }
    CHECK_FALSE(found);
}

TEST_CASE("NMEA Garbage Recovery") {
    // $QZQSM svid=57 -> PRN185 (QZS-4 L1S)
    uint8_t bits[32] = {0x12, 0x34};
    auto pkt = makeNmeaQzqsm(57, bits);

    NmeaFramer framer;
    Frame out;
    // Feed partial frame then garbage
    std::string partial = "$QZQSM,1";
    for (char c : partial) framer.feed((uint8_t)c, out);
    for (int i = 0; i < 50; ++i) framer.feed('?', out);

    // Feed valid
    bool found = false;
    for (char c : pkt) {
        if (framer.feed((uint8_t)c, out)) { found = true; break; }
    }
    REQUIRE(found);
    CHECK(out.svid == 185);  // NMEA 57 + 128 = PRN185
}

TEST_CASE("NMEA Oversize Recovery") {
    NmeaFramer framer;
    Frame out;
    framer.feed('$', out);
    for (int i = 0; i < 300; ++i) {
        framer.feed('A', out); // Fill buffer beyond capacity
    }
    // Should have reset internally. Try valid one now.
    // $QZQSM svid=61 -> PRN189 (QZS-3 L1S)
    uint8_t bits[32] = {0x55};
    auto pkt = makeNmeaQzqsm(61, bits);
    bool found = false;
    for (char c : pkt) {
        if (framer.feed((uint8_t)c, out)) { found = true; break; }
    }
    REQUIRE(found);
    CHECK(out.svid == 189);  // NMEA 61 + 128 = PRN189
}

// ── NMEA ペイロード長検証 ────────────────────────────────────────────────────
// NmeaFramer のみをテスト（Decoder を経由しない）

TEST_CASE("NMEA: 62文字の拒否") {
    Frame out{};
    auto nmea = makeNmeaQzqsmHex(62);
    CHECK_FALSE(feedNmeaRaw(nmea.c_str(), out));
}

TEST_CASE("NMEA: 63文字の受け入れ") {
    Frame out{};
    auto nmea = makeNmeaQzqsmHex(63);
    CHECK(feedNmeaRaw(nmea.c_str(), out));
    CHECK(out.svid == 183);  // NMEA 55 + 128 = PRN183
}

TEST_CASE("NMEA: 64文字の受け入れ") {
    Frame out{};
    auto nmea = makeNmeaQzqsmHex(64);
    CHECK(feedNmeaRaw(nmea.c_str(), out));
    CHECK(out.svid == 183);  // NMEA 55 + 128 = PRN183
}

TEST_CASE("NMEA: 65文字の拒否") {
    Frame out{};
    auto nmea = makeNmeaQzqsmHex(65);
    CHECK_FALSE(feedNmeaRaw(nmea.c_str(), out));
}
