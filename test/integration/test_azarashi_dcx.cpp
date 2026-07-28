// test/integration/test_azarashi_dcx.cpp
// MT=44 DCX の azarashi 比較テスト（データ駆動）
// azarashi v0.16.1 のデコード結果と照合

#include "../test_helpers.h"
#include "doctest.h"
#include <cstring>
#include <string>

using namespace azaraC;

#if (AZARAC_ENABLE_DCX_CAMF)

// ═══════════════════════════════════════════════════════════════════════════════
// DCX NULL Message — test_dcx
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("DCX: Null Message") {
    Message msg{};
    const char* nmea = "$QZQSM,55,53B0840DE0000000000000000000000000000000000000000000000012ACBD4*0E";
    REQUIRE(decodeNmea(nmea, msg));
    CHECK(msg.msg_type == 44);
    CHECK(msg.payload_type == MsgPayloadType::Mt44);

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->service_kind == Mt44ServiceKind::NullMessage);
    CHECK(mt44->is_null_message == true);
}

// ═══════════════════════════════════════════════════════════════════════════════
// DCX Outside Japan — test_dcx (Fiji, Tsunami)
// azarashi: a2=71(Fiji), a4=44(GEO/Tsunami), a5=3(Extreme), vn=16
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("DCX: Outside Japan - Fiji Tsunami") {
    Message msg{};
    const char* nmea = "$QZQSM,56,9AB08408E0598969E00066AFFE8E6F70091200000000000000000100CD1A410*0C";
    REQUIRE(decodeNmea(nmea, msg));
    CHECK(msg.msg_type == 44);
    CHECK(msg.payload_type == MsgPayloadType::Mt44);

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->service_kind == Mt44ServiceKind::OutsideJapan);
    CHECK(mt44->camf.a2 == 71);   // Fiji
    CHECK(mt44->camf.a3 == 0);    // Undefined Provider
    CHECK(mt44->camf.a5 == 3);    // Extreme severity
    CHECK(mt44->ex_outside.vn == 16); // version 16
}

// ═══════════════════════════════════════════════════════════════════════════════
// DCX L-Alert — test_dcx
// azarashi: a2=111(Japan), a3=1(Foundation for MultiMedia Communications),
//           a4=1(CBRNE/Air strike), a5=0(Unknown), ex1=1101(札幌市中央区), vn=1
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("DCX: L-Alert - CBRNE Air Strike") {
    Message msg{};
    const char* nmea = "$QZQSM,55,9AB0840DE10208ADE0000000000000000000011340000000000000132F0D238*04";
    REQUIRE(decodeNmea(nmea, msg));
    CHECK(msg.msg_type == 44);
    CHECK(msg.payload_type == MsgPayloadType::Mt44);

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->service_kind == Mt44ServiceKind::LAlert);
    CHECK(mt44->camf.a2 == 111);  // Japan
    CHECK(mt44->camf.a3 == 1);    // Foundation for MultiMedia Communications
    CHECK(mt44->ex_lalert_local.ex1 == 1101); // Chuo-ku, Sapporo-shi
    CHECK(mt44->ex_lalert_local.vn == 1);
}

// ═══════════════════════════════════════════════════════════════════════════════
// DCX J-Alert — test_dcx
// azarashi: a2=111(Japan), a3=3(Related Ministries),
//           a4=8(CBRNE/Missile attack), a5=3(Extreme), vn=1
//           ex9: 全47都道府県
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("DCX: J-Alert - Missile Attack") {
    Message msg{};
    const char* nmea = "$QZQSM,55,53B0840DE31188FC208600000000000000001FFFFFFFFFFFC00000120738628*00";
    REQUIRE(decodeNmea(nmea, msg));
    CHECK(msg.msg_type == 44);
    CHECK(msg.payload_type == MsgPayloadType::Mt44);

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->service_kind == Mt44ServiceKind::JAlert);
    CHECK(mt44->camf.a2 == 111);  // Japan
    CHECK(mt44->camf.a3 == 3);    // Related Ministries (FDMA -> J-Alert)
    CHECK(mt44->camf.a5 == 3);    // Extreme severity
    CHECK(mt44->ex_jalert.vn == 1);

    // ex9: 全47都道府県が指定されていることを検証
    CHECK(mt44->mt44_decoded.jalert_prefecture_mode == true);
    CHECK(mt44->mt44_decoded.prefecture_count == 47);
    for (int i = 0; i < 47; ++i) {
        CAPTURE(i);
        CHECK(mt44->mt44_decoded.prefecture_positions[i] == i + 1);
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
// DCX Local Government a3 boundary (4..31 range) — test_dcx
// Locks in the LocalGovernment service kind for the expanded a3 range.
// a2=111(Japan), a3=4(min) / a3=31(max). Non-JAlert path verified.
// ═══════════════════════════════════════════════════════════════════════════════

namespace {
Message decodeDcxHelper(uint8_t* bits) {
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);
    TestDecoder decoder;
    Message msg{};
    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    decoder.decode(frame, msg, 0);
    return msg;
}
} // namespace

TEST_CASE("DCX: Local Government a3=4 (boundary min)") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);     // PAB=A
    setBits(bits, 8, 6, 44);       // MT=44
    setBits(bits, 14, 1, 0);       // SDMT
    setBits(bits, 15, 9, 0x1FF);   // SDM
    setBits(bits, 26, 9, 111);     // a2=Japan
    setBits(bits, 35, 5, 4);       // a3=4 (LocalGovernment min)

    Message msg = decodeDcxHelper(bits);
    REQUIRE(msg.valid);
    CHECK(msg.msg_type == 44);
    CHECK(msg.payload_type == MsgPayloadType::Mt44);

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->service_kind == Mt44ServiceKind::LocalGovernment);
    CHECK(mt44->camf.a2 == 111);
    CHECK(mt44->camf.a3 == 4);
    // Verify non-JAlert: prefecture fields NOT populated
    CHECK(mt44->mt44_decoded.jalert_prefecture_mode == false);
    CHECK(mt44->mt44_decoded.prefecture_count == 0);
}

TEST_CASE("DCX: Local Government a3=31 (boundary max)") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);     // PAB=A
    setBits(bits, 8, 6, 44);       // MT=44
    setBits(bits, 14, 1, 0);       // SDMT
    setBits(bits, 15, 9, 0x1FF);   // SDM
    setBits(bits, 26, 9, 111);     // a2=Japan
    setBits(bits, 35, 5, 31);      // a3=31 (LocalGovernment max)

    Message msg = decodeDcxHelper(bits);
    REQUIRE(msg.valid);
    CHECK(msg.msg_type == 44);
    CHECK(msg.payload_type == MsgPayloadType::Mt44);

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->service_kind == Mt44ServiceKind::LocalGovernment);
    CHECK(mt44->camf.a2 == 111);
    CHECK(mt44->camf.a3 == 31);
    // Verify non-JAlert: prefecture fields NOT populated
    CHECK(mt44->mt44_decoded.jalert_prefecture_mode == false);
    CHECK(mt44->mt44_decoded.prefecture_count == 0);
}

// ═══════════════════════════════════════════════════════════════════════════════
// DCX J-Alert a3 ∈ {0,2,3} — Non-null message
// a2=111(Japan), a4=8(Missile attack)で非NullのJ-Alertを確認
// a3=0(FDMA), a3=2(Cabinet Office), a3=3(FDMA) はいずれも JAlert に分岐
//   (IS-QZSS-DCX-003 §4.2.1.2, DecoderDcx.cpp:196)
// NullMessage チェック（全フィールドゼロ）に引っかからないよう a4 を設定
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("DCX: J-Alert a3={0,2,3} (FDMA/Cabinet Office) - Non-null message") {
    const int a3_values[] = {0, 2, 3};
    for (int a3_val : a3_values) {
        INFO("Testing a3=" << a3_val);
        
        uint8_t bits[32] = {};
        setBits(bits, 0, 8, 0x53);     // PAB=A
        setBits(bits, 8, 6, 44);       // MT=44
        setBits(bits, 14, 1, 0);       // SDMT
        setBits(bits, 15, 9, 0x1FF);   // SDM
        setBits(bits, 26, 9, 111);     // a2=Japan
        setBits(bits, 35, 5, a3_val);  // a3 ∈ {0,2,3}
        setBits(bits, 40, 7, 8);       // a4=8 (CBRNE/Missile attack) - ensures non-null

        Message msg = decodeDcxHelper(bits);
        REQUIRE(msg.valid);
        CHECK(msg.msg_type == 44);
        CHECK(msg.payload_type == MsgPayloadType::Mt44);

        const Mt44Data* mt44 = msg.getMt44();
        REQUIRE(mt44 != nullptr);
        CHECK(mt44->service_kind == Mt44ServiceKind::JAlert);
        CHECK(mt44->camf.a2 == 111);
        CHECK(mt44->camf.a3 == a3_val);
        CHECK(mt44->is_null_message == false);
        // Verify J-Alert: ex_jalert path sets jalert_prefecture_mode = true
        CHECK(mt44->mt44_decoded.jalert_prefecture_mode == true);
    }
}
#endif
