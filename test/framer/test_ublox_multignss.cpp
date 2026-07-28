// test/framer/test_ublox_multignss.cpp
// UBX SFRBX マルチGNSS混在テスト
// gnssId フィルタリング（QZSS=5 のみ許可）の正しさを検証

#include "../test_helpers.h"
#include "doctest.h"
#include <cstring>
#include <vector>

using namespace azaraC;

// ── ヘルパー: 任意の gnssId で SFRBX パケットを生成 ─────────────────────────

static std::vector<uint8_t> makeUbxSfrbxGnssId(uint8_t gnssId, uint8_t svId, const uint8_t* nav_bits) {
    auto pkt = makeUbxSfrbx(static_cast<uint8_t>(svId + 182), nav_bits);
    // gnssId フィールドはペイロード先頭バイト（offset 6 from sync）
    // UBX header(6) + SFRBX payload hdr(8) の構造:
    // [B5][62][02][13][len_lo][len_hi][gnssId][svId][sigId][freqId][numWords][chn][ver][reserved]
    // gnssId は index 6 (=全体の7バイト目)
    pkt[6] = gnssId;
    // Checksum は変更されたバイトに対して再計算
    uint8_t cka = 0, ckb = 0;
    for (size_t i = 2; i < pkt.size() - 2; ++i) {
        cka += pkt[i];
        ckb += cka;
    }
    pkt[pkt.size() - 2] = cka;
    pkt[pkt.size() - 1] = ckb;
    return pkt;
}

// ── テストケース ──────────────────────────────────────────────────────────────

TEST_CASE("UBX: GPS (gnssId=0) ignored") {
    uint8_t bits[32] = {0x53};
    auto pkt = makeUbxSfrbxGnssId(0, 2, bits);  // GPS (gnssId=0)

    UbxFramer framer;
    Frame out;
    bool found = false;
    for (auto b : pkt) {
        if (framer.feed(b, out)) { found = true; break; }
    }
    CHECK_FALSE(found);  // GPS は無視される
}

TEST_CASE("UBX: GLONASS (gnssId=6) ignored") {
    uint8_t bits[32] = {0x53};
    auto pkt = makeUbxSfrbxGnssId(6, 2, bits);  // GLONASS (gnssId=6)

    UbxFramer framer;
    Frame out;
    bool found = false;
    for (auto b : pkt) {
        if (framer.feed(b, out)) { found = true; break; }
    }
    CHECK_FALSE(found);  // GLONASS は無視される
}

TEST_CASE("UBX: Galileo (gnssId=2) ignored") {
    uint8_t bits[32] = {0x53};
    auto pkt = makeUbxSfrbxGnssId(2, 2, bits);  // Galileo (gnssId=2)

    UbxFramer framer;
    Frame out;
    bool found = false;
    for (auto b : pkt) {
        if (framer.feed(b, out)) { found = true; break; }
    }
    CHECK_FALSE(found);  // Galileo は無視される
}

TEST_CASE("UBX: BeiDou (gnssId=3) ignored") {
    uint8_t bits[32] = {0x53};
    auto pkt = makeUbxSfrbxGnssId(3, 2, bits);  // BeiDou (gnssId=3)

    UbxFramer framer;
    Frame out;
    bool found = false;
    for (auto b : pkt) {
        if (framer.feed(b, out)) { found = true; break; }
    }
    CHECK_FALSE(found);  // BeiDou は無視される
}

TEST_CASE("UBX: Invalid gnssId (7) ignored") {
    uint8_t bits[32] = {0x53};
    auto pkt = makeUbxSfrbxGnssId(7, 2, bits);  // 未定義 gnssId=7

    UbxFramer framer;
    Frame out;
    bool found = false;
    for (auto b : pkt) {
        if (framer.feed(b, out)) { found = true; break; }
    }
    CHECK_FALSE(found);  // 未定義も無視される
}

TEST_CASE("UBX: QZSS after 100 GPS frames") {
    // 100 個の GPS SFRBX 後、QZSS SFRBX を正しくデコード
    UbxFramer framer;
    Frame out;
    uint8_t bits[32] = {0x53};

    // 100 個の GPS フレーム
    for (int i = 0; i < 100; ++i) {
        auto gps = makeUbxSfrbxGnssId(0, 2, bits);
        for (auto b : gps) {
            CHECK_FALSE(framer.feed(b, out));  // GPS は常に無視
        }
    }

    // 最後に QZSS
    auto qzss = makeUbxSfrbxGnssId(5, 2, bits);  // QZSS (gnssId=5), svId=2 → PRN184
    bool found = false;
    for (auto b : qzss) {
        if (framer.feed(b, out)) { found = true; break; }
    }
    REQUIRE(found);
    CHECK(out.svid == 184);  // svId=2 → PRN184
    CHECK(out.source == FrameSource::UBX);
}

TEST_CASE("UBX: Mixed gnssId stream preserves QZSS") {
    // GPS → QZSS → GLONASS → QZSS の混在で両方の QZSS フレームを取得
    struct TestFrame { uint8_t gnssId; bool expect; uint8_t expected_svid; };
    TestFrame frames[] = {
        {0, false, 0},    // GPS → 無視
        {5, true, 184},   // QZSS svId=2 → PRN184
        {6, false, 0},    // GLONASS → 無視
        {5, true, 185},   // QZSS svId=3 → PRN185
    };

    UbxFramer framer;
    uint8_t bits1[32] = {0x53};
    uint8_t bits2[32] = {0x9A};

    int qzss_index = 0;
    for (auto& f : frames) {
        const uint8_t* nav_bits = (f.gnssId == 5 && f.expected_svid == 185) ? bits2 : bits1;
        uint8_t svid = (f.expected_svid > 0) ? static_cast<uint8_t>(f.expected_svid - 182) : 2;
        auto pkt = makeUbxSfrbxGnssId(f.gnssId, svid, nav_bits);

        Frame out;
        bool found = false;
        for (auto b : pkt) {
            if (framer.feed(b, out)) { found = true; break; }
        }

        if (f.expect) {
            REQUIRE(found);
            CHECK(out.svid == f.expected_svid);
            CHECK(out.source == FrameSource::UBX);
            ++qzss_index;
        } else {
            CHECK_FALSE(found);
        }
    }
}

TEST_CASE("UBX: QZSS with valid payload survives non-QZSS contamination") {
    // 非QZSSメッセージがフレーマー内部状態を破壊しないことを検証
    UbxFramer framer;
    Frame out;
    uint8_t bits[32] = {0x53, 0x2F};

    // 先に GPS をいくつか流す
    for (int i = 0; i < 5; ++i) {
        auto gps = makeUbxSfrbxGnssId(0, 2, bits);
        for (auto b : gps) {
            framer.feed(b, out);  // 戻り値は無視
        }
    }

    // QZSS
    auto qzss = makeUbxSfrbxGnssId(5, 2, bits);
    bool found = false;
    for (auto b : qzss) {
        if (framer.feed(b, out)) { found = true; break; }
    }
    REQUIRE(found);
    CHECK(out.svid == 184);
    // ペイロードが正しいこと
    CHECK(out.bits[0] == 0x53);
    CHECK(out.bits[1] == 0x2F);
}
