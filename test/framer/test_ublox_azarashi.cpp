// test/framer/test_ublox_azarashi.cpp
// UBX SFRBX の azarashi 比較テスト
// azarashi v0.16.1 のデコード結果と照合

#define ARDUINO 0
#include "../test_helpers.h"
#include "doctest.h"
#include <cstring>
#include <vector>

using namespace azaraC;

// ═══════════════════════════════════════════════════════════════════════════════
// UBX SFRBX 5パターン — test_ublox (azarashi)
// azarashi でデコードした結果: NMEA ラウンドトリップ + フィールド検証
// ═══════════════════════════════════════════════════════════════════════════════

// UBX SFRBXパケットを作成し、フレーマーでデコードするヘルパー
static bool feedUbxPacket(UbxFramer& framer, Frame& frame, uint8_t svId, const uint8_t* nav_bits) {
    auto pkt = makeUbxSfrbx(svId, nav_bits);
    for (auto b : pkt) {
        if (framer.feed(b, frame)) return true;
    }
    return false;
}

// ナビビットからプリアンブルとMTを抽出するヘルパー（デバッグ用）
[[maybe_unused]] static uint8_t getPreamble(const uint8_t* bits) {
    return TestDecoder::extractBits(bits, 0, 8);
}
[[maybe_unused]] static uint8_t getMT(const uint8_t* bits) {
    return TestDecoder::extractBits(bits, 8, 6);
}

TEST_CASE("UBX: SFRBX sv56 pattern1 - Marine (round-trip with NMEA)") {
    // azarashi ublox_sv56_p1: svid=2, Marine, Regular, 8 regions
    // UBXヘッダー: gnssId=5(QZSS), svId=2, sigId=0, freqId=0, numWords=8, chn=0, version=1
    // 注: このデータは有効なCRC-24Qチェックサムを持つ
    std::vector<uint8_t> ubx_data = {
        0xB5, 0x62, 0x02, 0x13, 0x2C, 0x00,
        0x05, 0x02, 0x01, 0x00, 0x09, 0x40, 0x02, 0x00,
        0xC5, 0xF1, 0xAD, 0x9A, 0x04, 0x05, 0x80, 0x11,
        0x54, 0x8D, 0xA0, 0x60, 0x3F, 0x82, 0xD2, 0x11,
        0x0F, 0xAA, 0x7D, 0x50, 0x28, 0x0C, 0x43, 0xC9,
        0x10, 0x00, 0x50, 0x7D, 0x31, 0x79, 0xF0, 0x28,
        0x73, 0x18, 0x10, 0xB2, 0x62, 0x2F
    };

    UbxFramer framer;
    Frame frame;
    bool found = false;
    for (auto b : ubx_data) {
        if (framer.feed(b, frame)) { found = true; break; }
    }
    REQUIRE(found);
    CHECK(frame.svid == 184);  // svId=2 -> PRN184 (ublox_qzss_svid_prn_map)

    // NMEA に変換してデコード
    std::string nmea = makeNmeaQzqsm(frame.svid, frame.bits);
    Message msg{};
    REQUIRE(decodeNmea(nmea.c_str(), msg));
    CHECK(msg.msg_type == 43);
    CHECK(msg.payload_type == MsgPayloadType::Mt43);

    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    CHECK(mt43->disaster_category == 14); // Marine
}

TEST_CASE("UBX: svid to PRN mapping") {
    // azarashi ublox_sv55-61: svid -> PRN mapping verification
    // UBXフレーマーが正しくsvidをPRNに変換することを検証
    struct SvidCase { uint8_t svid; uint8_t expected_prn; };
    SvidCase cases[] = {{1, 183}, {2, 184}, {3, 185}, {4, 186}};
    for (auto& tc : cases) {
        uint8_t nav_bits[32] = {};  // ダミーデータ（svid変換のみテスト）
        UbxFramer framer;
        Frame frame;
        bool found = feedUbxPacket(framer, frame, tc.svid, nav_bits);
        REQUIRE(found);
        CHECK(frame.svid == tc.expected_prn);
        CHECK(frame.source == FrameSource::UBX);
    }
}
