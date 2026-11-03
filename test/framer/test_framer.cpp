// UBX/NMEA フレーマーの統合テスト

#define ARDUINO 0
#include "../test_helpers.h"
#include "doctest.h"
#include <cstring>

using namespace azaraC;

// UBX テスト

TEST_CASE("UBX Framer: basic decode with multiple svIds") {
    // svId → PRN 対応: 2→184, 3→185, 7→189
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
    // 方法 1: ヘッダ／ペイロードの 1 バイトを壊す
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
    // 方法 2: チェックサム最終バイトを壊す
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
        // ゴミを入力
        for (int i = 0; i < 100; ++i) framer.feed(0xAA, out);

        // 妥当な電文を入力
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

// NMEA テスト

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

TEST_CASE("NMEA: invalid checksum is rejected") {
    enum class Kind { LastDigit, Zero, FF };
    struct Case { Kind kind; const char* name; };
    const Case cases[] = {
        {Kind::LastDigit, "last digit corrupted"},
        {Kind::Zero,      "*00"},
        {Kind::FF,        "*FF"},
    };
    for (const Case& c : cases) {
        INFO(c.name);
        uint8_t bits[32] = {};
        auto pkt = makeNmeaQzqsm(56, bits);
        switch (c.kind) {
            case Kind::LastDigit: pkt[pkt.size() - 3] = '0'; break;
            case Kind::Zero:      pkt[pkt.size() - 4] = '0'; pkt[pkt.size() - 3] = '0'; break;
            case Kind::FF:        pkt[pkt.size() - 4] = 'F'; pkt[pkt.size() - 3] = 'F'; break;
        }

        NmeaFramer framer;
        Frame out;
        bool found = false;
        for (char ch : pkt) {
            if (framer.feed((uint8_t)ch, out)) { found = true; break; }
        }
        CHECK_FALSE(found);
    }
}

TEST_CASE("NMEA: garbage and partial frames recover") {
    const std::string crlf = std::string(1, static_cast<char>(13)) + static_cast<char>(10);
    std::string bursts;
    for (int i = 0; i < 10; ++i) {
        bursts += "N$GPGARBAGE,123,456,789*00" + crlf + "$XXFOO,bar,baz" + crlf;
    }

    struct Case {
        const char* name;
        std::string prelude;
        uint8_t svid;
        uint8_t bits0;
        uint8_t bits1;
    };
    const Case cases[] = {
        {"partial frame",     "$QZQSM,55,9AAF", 55, 0x53, 0xAD},
        {"partial then junk", "$QZQSM,1" + std::string(50, '?'), 57, 0x12, 0x34},
        {"oversize",          "$" + std::string(300, 'A'), 61, 0x55, 0x00},
        {"between garbage",   std::string("garbage_line_1") + crlf + "garbage_line_2" + crlf, 56, 0x53, 0x00},
        {"repeated bursts",   bursts, 55, 0x53, 0x00},
        {"invalid lines",     std::string("$XXXXX,123*00") + crlf + "$YYYYY,456*FF" + crlf, 56, 0x53, 0x00},
    };
    for (const Case& c : cases) {
        INFO(c.name);
        NmeaFramer framer;
        Frame out;
        for (char ch : c.prelude) framer.feed((uint8_t)ch, out);

        uint8_t bits[32] = {c.bits0, c.bits1};
        const std::string valid = makeNmeaQzqsm(c.svid, bits);
        bool found = false;
        for (char ch : valid) {
            if (framer.feed((uint8_t)ch, out)) { found = true; break; }
        }
        REQUIRE(found);
        CHECK(out.svid == static_cast<uint8_t>(c.svid + 128));
    }
}

// NMEA ペイロード長検証: NmeaFramer のみ（Decoder を経由しない）

TEST_CASE("NMEA: payload length must be 63 or 64 hex chars") {
    // 65 hex は _buf[82] に収まる（overrun は 73 hex 以上）ため、このテストは長さ検証のみ。
    // overrun 時の reset() は、その長さが必ず 63/64 検証で拒否されるため等価変異（監査時に reset() 削除でも全テストが緑のままだったことを確認済み）。
    struct Case { int hex_chars; bool accept; };
    const Case cases[] = {
        {62, false}, {63, true}, {64, true}, {65, false},
    };
    for (const Case& c : cases) {
        INFO("hex_chars=", c.hex_chars);
        Frame out{};
        auto nmea = makeNmeaQzqsmHex(c.hex_chars);
        const bool ok = feedNmeaRaw(nmea.c_str(), out);
        CHECK(ok == c.accept);
        if (c.accept) CHECK(out.svid == 183);  // NMEA 55 + 128 = PRN183
    }
}

// Satellite ID は「PRN を表す 8bit の下位 6bit」(DCR-017/DCX-004 §4.3.1) なので Frame::svid は常に PRN (id | 0x80)。
// 53/54 も実データに現れるためケースに含める。
TEST_CASE("NMEA: Satellite ID は生 ID から PRN に正規化される") {
    struct Case { uint8_t id; uint8_t expected_prn; };
    const Case cases[] = {
        {53, 181},   // QZS-1R 系 (DCX 実データに 5 通)
        {54, 182},   // (DCX 実データに 56 通)
        {55, 183},
        {56, 184},
        {57, 185},
        {58, 186},
        {61, 189},
        {63, 191},   // 6bit の上限
    };
    for (const auto& c : cases) {
        uint8_t bits[32] = {0};
        auto pkt = makeNmeaQzqsm(c.id, bits);
        NmeaFramer framer;
        Frame out{};
        bool found = false;
        for (char ch : pkt) {
            if (framer.feed(static_cast<uint8_t>(ch), out)) { found = true; break; }
        }
        INFO("input id=", (int)c.id);
        REQUIRE(found);
        CHECK(out.svid == c.expected_prn);
    }
}

// 仕様の Satellite ID は PRN 下位 6bit の2桁10進（Table 4.3.1-1）。azarashi も長さ 2 を要求する。
// 1桁/3桁/6bit を超える2桁を通すと `| 0x80` の結果が PRN 契約（181-191）の外に出る（64 → 192, 100 → 228）。
TEST_CASE("NMEA: Satellite ID は 2 桁かつ 6bit に限る") {
    auto sentence = [](const char* id_field) {
        std::string s = std::string("$QZQSM,") + id_field + ",";
        for (int i = 0; i < 31; ++i) {
            char hex[3];
            snprintf(hex, sizeof(hex), "%02X", 0);
            s += hex;
        }
        s += '0';
        uint8_t xsum = 0;
        for (size_t i = 1; i < s.size(); ++i) xsum ^= static_cast<uint8_t>(s[i]);
        char tail[8];
        snprintf(tail, sizeof(tail), "*%02X\r\n", xsum);
        return s + tail;
    };

    struct Case { const char* id_field; bool accepted; uint8_t expected_prn; };
    const Case cases[] = {
        {"5",   false, 0},     // 1 桁
        {"55",  true,  183},   // 2 桁（仕様どおり）
        {"63",  true,  191},   // 6bit の上限
        {"64",  false, 0},     // 6bit 外 → 192
        {"99",  false, 0},     // 6bit 外 → 227
        {"100", false, 0},     // 3 桁 → 228 になり PRN 契約外
    };
    for (const auto& c : cases) {
        NmeaFramer framer;
        Frame out{};
        bool found = false;
        const std::string pkt = sentence(c.id_field);
        for (char ch : pkt) {
            if (framer.feed(static_cast<uint8_t>(ch), out)) { found = true; break; }
        }
        INFO("id field=", c.id_field);
        CHECK(found == c.accepted);
        if (c.accepted) CHECK(out.svid == c.expected_prn);
    }
}

// UBX SFRBX 境界値テスト

TEST_CASE("UBX: SFRBX length must be 40") {
    // length=8（ヘッダのみ、words なし）でチェックサムは整合させ、parse() に _len < 8 + numWords*4 で落とさせる（失敗理由を長さ不一致に限定する）。
    std::vector<uint8_t> pkt;
    pkt.push_back(0xB5); pkt.push_back(0x62); // SYNC
    pkt.push_back(0x02); pkt.push_back(0x13); // CLASS/ID (RXM-SFRBX)
    pkt.push_back(0x08); pkt.push_back(0x00); // length = 8 (should be 40)
    // SFRBX ヘッダ: gnssId=5(QZSS), svId=2, sigId=0, freqId=0, numWords=8, chn=0, ver=1, reserved=0
    pkt.push_back(5); pkt.push_back(2); pkt.push_back(0); pkt.push_back(0);
    pkt.push_back(8); pkt.push_back(0); pkt.push_back(1); pkt.push_back(0);
    // バイト [2..end) の UBX チェックサム
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

namespace {

// UBX-RXM-SFRBX パケットを組み立てる。SFRBX ヘッダのフィールドを直接指定し、長さとチェックサムを整合させたまま 1 フィールドだけ不正にできる。
std::vector<uint8_t> makeSfrbxRaw(uint8_t gnssId, uint8_t sigId, uint8_t numWords) {
    std::vector<uint8_t> pkt;
    pkt.push_back(0xB5); pkt.push_back(0x62);  // SYNC
    pkt.push_back(0x02); pkt.push_back(0x13);  // CLASS/ID (RXM-SFRBX)
    const uint16_t len = static_cast<uint16_t>(8 + numWords * 4);
    pkt.push_back(static_cast<uint8_t>(len & 0xFF));
    pkt.push_back(static_cast<uint8_t>(len >> 8));
    pkt.push_back(gnssId);    // SFRBX header[0]
    pkt.push_back(2);         // svId
    pkt.push_back(sigId);     // sigId
    pkt.push_back(0);         // freqId
    pkt.push_back(numWords);  // numWords
    pkt.push_back(0);         // chn
    pkt.push_back(1);         // version
    pkt.push_back(0);         // reserved
    for (uint8_t w = 0; w < numWords; ++w) {
        pkt.push_back(0); pkt.push_back(0); pkt.push_back(0); pkt.push_back(0);
    }
    uint8_t cka = 0, ckb = 0;
    for (size_t i = 2; i < pkt.size(); ++i) { cka += pkt[i]; ckb += cka; }
    pkt.push_back(cka);
    pkt.push_back(ckb);
    return pkt;
}

bool feedSfrbx(const std::vector<uint8_t>& pkt) {
    UbxFramer framer;
    Frame out;
    for (auto b : pkt) {
        if (framer.feed(b, out)) return true;
    }
    return false;
}

} // namespace

TEST_CASE("UBX: non-QZSS gnssId rejected (length and checksum valid)") {
    CHECK_FALSE(feedSfrbx(makeSfrbxRaw(/*gnssId=*/3, /*sigId=*/0, /*numWords=*/8)));
    // 対照: gnssId=5 なら同じ組み立てで受理される
    CHECK(feedSfrbx(makeSfrbxRaw(/*gnssId=*/5, /*sigId=*/0, /*numWords=*/8)));
}

TEST_CASE("UBX: sigId outside {0,1} rejected") {
    CHECK_FALSE(feedSfrbx(makeSfrbxRaw(/*gnssId=*/5, /*sigId=*/2, /*numWords=*/8)));
    CHECK(feedSfrbx(makeSfrbxRaw(/*gnssId=*/5, /*sigId=*/1, /*numWords=*/8)));
}

TEST_CASE("UBX: numWords outside {8,9} rejected even when length matches") {
    // length は 8 + numWords*4 で整合させ、numWords 検査だけで弾かれることを確認する。
    CHECK_FALSE(feedSfrbx(makeSfrbxRaw(/*gnssId=*/5, /*sigId=*/0, /*numWords=*/1)));
    CHECK_FALSE(feedSfrbx(makeSfrbxRaw(/*gnssId=*/5, /*sigId=*/0, /*numWords=*/10)));
    // 対照: 8 words（仕様どおり）と 9 words（u-blox の実データ。余剰 word は無視）を受理する
    CHECK(feedSfrbx(makeSfrbxRaw(/*gnssId=*/5, /*sigId=*/0, /*numWords=*/8)));
    CHECK(feedSfrbx(makeSfrbxRaw(/*gnssId=*/5, /*sigId=*/0, /*numWords=*/9)));
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

// NMEA 部分フレーム復帰テスト

TEST_CASE("UBX: SYNC2 resync on stray 0xB5") {
    uint8_t bits[32] = {0x53};
    auto pkt = makeUbxSfrbx(2, bits);
    UbxFramer framer;
    Frame out;
    framer.feed(0xB5, out);  // stray sync byte
    int found = 0;
    for (auto b : pkt) {
        if (framer.feed(b, out)) found++;
    }
    CHECK(found == 1);
    CHECK(out.svid == 184);
}
