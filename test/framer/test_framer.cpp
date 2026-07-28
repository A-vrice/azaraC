// test/framer/test_framer.cpp — フレーマーテスト
// UBX/NMEA フレーマーの統合テスト

#define ARDUINO 0
#include "../test_helpers.h"
#include "doctest.h"
#include <cstring>

using namespace azaraC;

// ── UBX Tests ──────────────────────────────────────────────────────────────

TEST_CASE("UBX Framer: basic decode with multiple svIds") {
    // svId -> PRN mapping: 2->184, 3->185, 7->189
    struct SvidCase { uint8_t svid; uint8_t expected_prn; uint8_t bits0; };
    SvidCase cases[] = {
        {2, 184, 0x53},  // svId=2 -> PRN184 (QZS-2 L1S)
        {3, 185, 0x9A},  // svId=3 -> PRN185 (QZS-4 L1S)
        {7, 189, 0x53},  // svId=7 -> PRN189 (QZS-3 L1S)
    };
    for (auto& tc : cases) {
        uint8_t bits[32] = {tc.bits0, 0xAB};
        auto pkt = makeUbxSfrbx(tc.svid, bits);

        UbxFramer framer;
        Frame out;
        bool found = false;
        for (auto b : pkt) {
            if (framer.feed(b, out)) { found = true; break; }
        }

        INFO("svId=", (int)tc.svid);
        REQUIRE(found);
        CHECK(out.svid == tc.expected_prn);
        CHECK(out.bits[0] == tc.bits0);
    }
}

TEST_CASE("UBX Checksum Error: corrupted payload and checksum") {
    // Method 1: Corrupt a header/payload byte
    {
        uint8_t bits[32] = {0};
        auto pkt = makeUbxSfrbx(2, bits);
        pkt[10] ^= 0xFF;

        UbxFramer framer;
        Frame out;
        bool found = false;
        for (auto b : pkt) {
            if (framer.feed(b, out)) found = true;
        }
        CHECK_FALSE(found);
    }
    // Method 2: Corrupt the last checksum byte
    {
        uint8_t bits[32] = {0x53, 0xAB};
        auto pkt = makeUbxSfrbx(2, bits);
        pkt[pkt.size() - 1] ^= 0xFF;

        UbxFramer framer;
        Frame out;
        bool found = false;
        for (auto b : pkt) {
            if (framer.feed(b, out)) found = true;
        }
        CHECK_FALSE(found);
    }
}

TEST_CASE("UBX Garbage Recovery: multiple svIds after garbage") {
    struct SvidCase { uint8_t svid; uint8_t expected_prn; };
    SvidCase cases[] = {
        {2, 184},  // svId=2 -> PRN184
        {3, 185},  // svId=3 -> PRN185
        {4, 186},  // svId=4 -> PRN186
    };
    for (auto& tc : cases) {
        uint8_t bits[32] = {0x9A};
        auto pkt = makeUbxSfrbx(tc.svid, bits);

        UbxFramer framer;
        Frame out;
        // Feed garbage
        for (int i = 0; i < 100; ++i) framer.feed(0xAA, out);

        // Feed valid
        bool found = false;
        for (auto b : pkt) {
            if (framer.feed(b, out)) { found = true; break; }
        }
        INFO("svId=", (int)tc.svid);
        REQUIRE(found);
        CHECK(out.svid == tc.expected_prn);
    }
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

// ── UBX SFRBX 境界値テスト ────────────────────────────────────────────────────

TEST_CASE("UBX: SFRBX length must be 40") {
    // Build a packet with length=8 (header only, no words) so checksum is
    // consistent but parse() rejects it because _len < 8 + numWords*4.
    // This ensures the frame fails specifically due to length mismatch,
    // not a checksum error.
    std::vector<uint8_t> pkt;
    pkt.push_back(0xB5); pkt.push_back(0x62); // SYNC
    pkt.push_back(0x02); pkt.push_back(0x13); // CLASS/ID (RXM-SFRBX)
    pkt.push_back(0x08); pkt.push_back(0x00); // length = 8 (should be 40)
    // SFRBX header: gnssId=5(QZSS), svId=2, sigId=0, freqId=0, numWords=8, chn=0, ver=1, reserved=0
    pkt.push_back(5); pkt.push_back(2); pkt.push_back(0); pkt.push_back(0);
    pkt.push_back(8); pkt.push_back(0); pkt.push_back(1); pkt.push_back(0);
    // UBX checksum over bytes [2..end)
    uint8_t cka = 0, ckb = 0;
    for (size_t i = 2; i < pkt.size(); ++i) { cka += pkt[i]; ckb += cka; }
    pkt.push_back(cka);
    pkt.push_back(ckb);

    UbxFramer framer;
    Frame out;
    bool found = false;
    for (auto b : pkt) {
        if (framer.feed(b, out)) { found = true; break; }
    }
    CHECK_FALSE(found);
}

TEST_CASE("UBX: Two consecutive frames decoded") {
    uint8_t bits1[32] = {0x53};
    uint8_t bits2[32] = {0x9A};
    auto pkt1 = makeUbxSfrbx(2, bits1);
    auto pkt2 = makeUbxSfrbx(3, bits2);

    std::vector<uint8_t> combined;
    combined.insert(combined.end(), pkt1.begin(), pkt1.end());
    combined.insert(combined.end(), pkt2.begin(), pkt2.end());

    UbxFramer framer;
    Frame out;
    int found_count = 0;
    for (auto b : combined) {
        if (framer.feed(b, out)) found_count++;
    }
    CHECK(found_count == 2);
}

// ── NMEA 部分フレーム復帰テスト ────────────────────────────────────────────────

TEST_CASE("NMEA: Partial frame then valid frame recovery") {
    NmeaFramer framer;
    Frame out;
    // Feed a partial frame (truncated)
    std::string partial = "$QZQSM,55,9AAF";
    for (char c : partial) framer.feed((uint8_t)c, out);

    // Now feed a valid frame
    uint8_t bits[32] = {0x53, 0xAD};
    auto validPkt = makeNmeaQzqsm(55, bits);
    bool found = false;
    for (char c : validPkt) {
        if (framer.feed((uint8_t)c, out)) { found = true; break; }
    }
    REQUIRE(found);
    CHECK(out.svid == 183);  // NMEA 55 + 128 = PRN183
}

// ── NMEA チェックサム境界値テスト ──────────────────────────────────────────────

TEST_CASE("NMEA: Checksum *00 rejected (unless coincidentally correct)") {
    uint8_t bits[32] = {};
    auto pkt = makeNmeaQzqsm(56, bits);
    // Overwrite checksum with *00
    pkt[pkt.size() - 4] = '0';
    pkt[pkt.size() - 3] = '0';

    NmeaFramer framer;
    Frame out;
    bool found = false;
    for (char c : pkt) {
        if (framer.feed((uint8_t)c, out)) { found = true; break; }
    }
    CHECK_FALSE(found);
}

TEST_CASE("NMEA: Checksum *FF rejected (unless coincidentally correct)") {
    uint8_t bits[32] = {};
    auto pkt = makeNmeaQzqsm(56, bits);
    // Overwrite checksum with *FF
    pkt[pkt.size() - 4] = 'F';
    pkt[pkt.size() - 3] = 'F';

    NmeaFramer framer;
    Frame out;
    bool found = false;
    for (char c : pkt) {
        if (framer.feed((uint8_t)c, out)) { found = true; break; }
    }
    CHECK_FALSE(found);
}

// ── NMEA マルチセンテンス混在テスト ──────────────────────────────────────────

TEST_CASE("NMEA: QZQSM between garbage lines") {
    // ゴミデータ → QZQSM → ゴミデータ の混在ストリームでも QZQSM が正常にデコードされる
    uint8_t bits[32] = {0x53};
    std::string valid = makeNmeaQzqsm(56, bits);
    std::string stream = "garbage_line_1\r\ngarbage_line_2\r\n" + valid + "\r\ngarbage_line_3\r\n";

    NmeaFramer framer;
    Frame out;
    bool found = false;
    for (char c : stream) {
        if (framer.feed((uint8_t)c, out)) { found = true; break; }
    }
    CHECK(found);
    CHECK(out.svid == 184);  // NMEA 56 + 128 = PRN184
}

TEST_CASE("NMEA: QZQSM survives repeated garbage bursts") {
    // 10 回のゴミデータバースト後に QZQSM が正しくデコードされる
    std::string stream;
    for (int i = 0; i < 10; ++i) {
        stream += "N$GPGARBAGE,123,456,789*00\r\n$XXFOO,bar,baz\r\n";
    }
    uint8_t bits[32] = {0x53};
    stream += makeNmeaQzqsm(55, bits);

    NmeaFramer framer;
    Frame out;
    bool found = false;
    for (char c : stream) {
        if (framer.feed((uint8_t)c, out)) { found = true; break; }
    }
    REQUIRE(found);
    CHECK(out.svid == 183);  // NMEA 55 + 128 = PRN183
}

TEST_CASE("NMEA: Invalid NMEA-like lines don't break subsequent QZQSM") {
    // 不正な NMEA ライクな行（チェックサム一致しない）の後でも QZQSM がデコードできる
    uint8_t bits[32] = {0x53};
    std::string qzqsm = makeNmeaQzqsm(56, bits);
    std::string stream =
        "$XXXXX,123*00\r\n"   // チェックサム不一致（ゴミ）
        "$YYYYY,456*FF\r\n"   // チェックサム不一致（ゴミ）
        + qzqsm;

    NmeaFramer framer;
    Frame out;
    bool found = false;
    for (char c : stream) {
        if (framer.feed((uint8_t)c, out)) { found = true; break; }
    }
    REQUIRE(found);
    CHECK(out.svid == 184);  // NMEA 56 + 128 = PRN184
}
