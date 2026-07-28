// test/integration/test_dcx_edge_cases.cpp
// DCX (MT=44) デコーダ異常系・境界値テスト
// 「テストは通すためのものではなく誤った実装を落とすもの」に基づき、
// 誤った実装が混入した場合に確実に失敗するテストケースを網羅する。

#include "../test_helpers.h"
#include "../src/internal/DcxHelper.h"
#include "doctest.h"

using namespace azaraC;

#if (AZARAC_ENABLE_DCX_CAMF)

// ═══════════════════════════════════════════════════════════════════════════════
// DCX NullMessage 境界値テスト
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("DCX Edge: NullMessage with A1-A18 zero but extended non-zero") {
    // A1-A18 がすべてゼロでも、拡張フィールドが非ゼロなら NullMessage ではない
    // IS-QZSS-DCX-003 §4.3: extended message fields (bits 146..219) must also be 0
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);     // PAB=A
    setBits(bits, 8, 6, 44);       // MT=44
    setBits(bits, 14, 1, 0);       // SDMT
    setBits(bits, 15, 9, 0);       // SDM
    setBits(bits, 26, 9, 111);     // A2=111 (Japan) — NullMessage チェック条件を満たす
    // A1-A18 are all zero (bits 24..145 except A2 not set)
    // Extended field EX1 at bit 146 is non-zero → NullMessage チェック失敗
    setBits(bits, 146, 16, 1101);
    setBits(bits, 214, 6, 1);      // vn=1

    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    REQUIRE(dec.decode(frame, msg, 0));

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    // NullMessage になってはいけない
    CHECK(mt44->is_null_message == false);
    // A1=0, A2=111(Japan), A3=0 → JAlert に分類される
    CHECK(mt44->service_kind == Mt44ServiceKind::JAlert);
}

TEST_CASE("DCX Edge: NullMessage with correct conditions") {
    // A1=0, A2=111(Japan), A3=0 かつ全 CAMF/拡張フィールド 0 → NullMessage
    // IS-QZSS-DCX-003 §4.3: A2 は Japan(111) である必要があり、
    // A1=0, A3=0 かつ残りの全フィールドが 0 でなければならない
    // vn フィールド (bit 214) は拡張フィールド (bit 210..219) に含まれるため、0 必須
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);     // PAB
    setBits(bits, 8, 6, 44);       // MT=44
    setBits(bits, 14, 1, 0);       // SDMT=0
    setBits(bits, 15, 9, 0);       // SDM=0
    setBits(bits, 24, 2, 0);       // A1=0 (bit 24-25, MSB first → first bit of 2)
    setBits(bits, 26, 9, 111);     // A2=111 (Japan) ← NullMessage 検出に必須
    // A3-A18 = 0 (未設定)
    // 拡張フィールド = 0 (未設定, vn 含む)

    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    REQUIRE(dec.decode(frame, msg, 0));

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->is_null_message == true);
    CHECK(mt44->service_kind == Mt44ServiceKind::NullMessage);
}

TEST_CASE("DCX Edge: A2=111, A3=0 だが CAMF 非ゼロ → JAlert, not Null") {
    // A2=111(Japan), A3=0 だが A4 などが非ゼロ → Null ではない JAlert
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);
    setBits(bits, 14, 1, 0);
    setBits(bits, 15, 9, 0x1FF);
    setBits(bits, 24, 2, 0);     // a1=0 (Null check requires a1=0)
    setBits(bits, 26, 9, 111);   // a2=111 (Japan)
    setBits(bits, 35, 5, 0);     // a3=0 (FDMA → JAlert)
    setBits(bits, 40, 7, 5);     // a4=5 (non-zero → not Null)
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    REQUIRE(dec.decode(frame, msg, 0));

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->is_null_message == false);
    CHECK(mt44->service_kind == Mt44ServiceKind::JAlert);
}

// ═══════════════════════════════════════════════════════════════════════════════
// A2 国コードの境界値テスト
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("DCX Edge: A2=0 (unknown country) → OutsideJapan") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);
    setBits(bits, 14, 1, 0);
    setBits(bits, 15, 9, 0);
    setBits(bits, 24, 2, 1);
    setBits(bits, 26, 9, 0);      // a2=0 (unknown country)
    setBits(bits, 35, 5, 5);
    setBits(bits, 40, 7, 5);
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    REQUIRE(dec.decode(frame, msg, 0));

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->service_kind == Mt44ServiceKind::OutsideJapan);
    CHECK(mt44->ex_kind == ExtendedKind::OutsideJapan);
}

TEST_CASE("DCX Edge: A2=110 (Japan-1) → OutsideJapan") {
    // A2=110 は Japan ではない
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);
    setBits(bits, 14, 1, 0);
    setBits(bits, 15, 9, 0);
    setBits(bits, 24, 2, 1);
    setBits(bits, 26, 9, 110);    // a2=110 (≠ 111 → not Japan)
    setBits(bits, 35, 5, 1);
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    REQUIRE(dec.decode(frame, msg, 0));

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->service_kind == Mt44ServiceKind::OutsideJapan);
}

// ═══════════════════════════════════════════════════════════════════════════════
// A3 プロバイダの境界値テスト
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("DCX Edge: A3=0 (FDMA) with Japan → JAlert") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);
    setBits(bits, 14, 1, 0);
    setBits(bits, 15, 9, 0x1FF);
    setBits(bits, 24, 2, 1);
    setBits(bits, 26, 9, 111);    // a2=111 (Japan)
    setBits(bits, 35, 5, 0);      // a3=0 (FDMA → JAlert)
    setBits(bits, 40, 7, 5);
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    REQUIRE(dec.decode(frame, msg, 0));

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->service_kind == Mt44ServiceKind::JAlert);
}

TEST_CASE("DCX Edge: A2=111, A3=5 → LocalGovernment") {
    // A3=5 は LocalGovernment 範囲（4-31）
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);
    setBits(bits, 14, 1, 0);
    setBits(bits, 15, 9, 0);
    setBits(bits, 24, 2, 1);
    setBits(bits, 26, 9, 111);
    setBits(bits, 35, 5, 5);      // a3=5 (LocalGovernment range)
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    REQUIRE(dec.decode(frame, msg, 0));

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->service_kind == Mt44ServiceKind::LocalGovernment);
}

TEST_CASE("DCX Edge: A3=31 (max) with Japan → LocalGovernment") {
    // A3=31 は LocalGovernment 範囲の最大値
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);
    setBits(bits, 14, 1, 0);
    setBits(bits, 15, 9, 0);
    setBits(bits, 24, 2, 1);
    setBits(bits, 26, 9, 111);
    setBits(bits, 35, 5, 31);     // a3=31 (max)
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    REQUIRE(dec.decode(frame, msg, 0));

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->service_kind == Mt44ServiceKind::LocalGovernment);
}

// ═══════════════════════════════════════════════════════════════════════════════
// B1-B4 と has_main_ellipse の分離テスト
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("DCX Edge: B4 (A17=3) without main ellipse") {
    // B4 は A12-A16（主楕円）の有無とは独立してデコードされる（DecoderDcx.cpp:259-267）
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);
    setBits(bits, 14, 1, 0);
    setBits(bits, 15, 9, 0x1FF);
    setBits(bits, 24, 2, 1);
    setBits(bits, 26, 9, 111);
    setBits(bits, 35, 5, 1);
    setBits(bits, 40, 7, 36);     // a4=36 (Earthquake)
    // A12-A16 all zero → no main ellipse
    setBits(bits, 129, 2, 3);     // A17=3 (B4)
    // A18 with earthquake data: D1=0x05, D2=0x03, D3=0x00, D4=0x00
    setBits(bits, 131, 15, (5 << 11) | (3 << 8));
    setBits(bits, 146, 16, 1100); // EX1
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    REQUIRE(dec.decode(frame, msg, 0));

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    // main_ellipse は存在しない
    CHECK(mt44->mt44_decoded.main_ellipse_present == false);
    // B4 は A17=3 なので independent check が必要
    // 実際には A17=3 の B4 処理は has_main_ellipse ブロックの外にある（259-267行）
    // そのため has_main_ellipse=false でも b4_present=true になる
    // → このテストでバグがないことを確認
    CHECK(mt44->camf.b4_present == true);
}

TEST_CASE("DCX Edge: A17=0 (B1) with all-zero codes → b1_present=false") {
    // B1 コードがすべて 0 の場合、b1_present=false（改善がないことを示す）
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);
    setBits(bits, 14, 1, 0);
    setBits(bits, 15, 9, 0x1FF);
    setBits(bits, 24, 2, 1);
    setBits(bits, 26, 9, 111);
    setBits(bits, 35, 5, 1);
    setBits(bits, 40, 7, 10);
    setBits(bits, 80, 16, 32768); // A12 non-zero → main ellipse present
    setBits(bits, 129, 2, 0);     // A17=0 (B1)
    setBits(bits, 131, 15, 0);    // A18=0 → all B1 codes are 0
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    REQUIRE(dec.decode(frame, msg, 0));

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->camf.b1_present == false);
    CHECK(mt44->mt44_decoded.main_ellipse_present == true);
}

// ═══════════════════════════════════════════════════════════════════════════════
// OutsideJapan 拡張フィールドの検証
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("DCX Edge: OutsideJapan with all-zero extended fields") {
    // A2 != 111 で OutsideJapan になる場合、extended fields が空でも問題ない
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);
    setBits(bits, 14, 1, 0);
    setBits(bits, 15, 9, 0);
    setBits(bits, 24, 2, 1);
    setBits(bits, 26, 9, 5);       // a2=5 (Outside Japan)
    setBits(bits, 35, 5, 1);
    // Extended fields all zero (default)
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    REQUIRE(dec.decode(frame, msg, 0));

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->service_kind == Mt44ServiceKind::OutsideJapan);
    CHECK(mt44->ex_outside.vn == 1);
}

// ═══════════════════════════════════════════════════════════════════════════════
// A5 severity 境界値テスト
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("DCX Edge: A5=3 (max) with L-Alert") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);
    setBits(bits, 14, 1, 0);
    setBits(bits, 15, 9, 0x1FF);
    setBits(bits, 24, 2, 1);
    setBits(bits, 26, 9, 111);
    setBits(bits, 35, 5, 1);       // a3=1 (L-Alert)
    setBits(bits, 40, 7, 10);
    setBits(bits, 47, 2, 3);       // a5=3 (Extreme — max value)
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    REQUIRE(dec.decode(frame, msg, 0));

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->camf.a5 == 3);
    CHECK(mt44->service_kind == Mt44ServiceKind::LAlert);
}

TEST_CASE("DCX Edge: A5=0 (Unknown) with L-Alert") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);
    setBits(bits, 14, 1, 0);
    setBits(bits, 15, 9, 0x1FF);
    setBits(bits, 24, 2, 1);
    setBits(bits, 26, 9, 111);
    setBits(bits, 35, 5, 1);
    setBits(bits, 40, 7, 10);
    setBits(bits, 47, 2, 0);       // a5=0 (Unknown — min value)
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    REQUIRE(dec.decode(frame, msg, 0));

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->camf.a5 == 0);
    CHECK(mt44->service_kind == Mt44ServiceKind::LAlert);
}

// ═══════════════════════════════════════════════════════════════════════════════
// SDMT/SDM 境界値テスト
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("DCX Edge: SDMT=1 (all), SDM=0") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);
    setBits(bits, 14, 1, 1);       // SDMT=1 (all)
    setBits(bits, 15, 9, 0);        // SDM=0
    setBits(bits, 24, 2, 1);
    setBits(bits, 26, 9, 111);
    setBits(bits, 35, 5, 1);
    setBits(bits, 40, 7, 10);
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    REQUIRE(dec.decode(frame, msg, 0));

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->sd.sdmt == 1);
    CHECK(mt44->sd.sdm == 0);
    CHECK(mt44->service_kind == Mt44ServiceKind::LAlert);
}

TEST_CASE("DCX Edge: SDMT=1, SDM=511 (max 9-bit)") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);
    setBits(bits, 14, 1, 1);       // SDMT=1
    setBits(bits, 15, 9, 0x1FF);   // SDM=511 (max 9-bit)
    setBits(bits, 24, 2, 1);
    setBits(bits, 26, 9, 111);
    setBits(bits, 35, 5, 1);
    setBits(bits, 40, 7, 10);
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    REQUIRE(dec.decode(frame, msg, 0));

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->sd.sdmt == 1);
    CHECK(mt44->sd.sdm == 511);
}

// ═══════════════════════════════════════════════════════════════════════════════
// DCX 廃番メッセージ（有効なバージョンの確認）
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("DCX Edge: Vn=0 (reserved) decoded") {
    // DCX の Vn フィールドは 0-63 の任意の値を受け入れる（MT=44 は version チェックがない）
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);
    setBits(bits, 14, 1, 0);
    setBits(bits, 15, 9, 0);
    setBits(bits, 24, 2, 1);
    setBits(bits, 26, 9, 111);
    setBits(bits, 35, 5, 1);
    setBits(bits, 40, 7, 10);
    setBits(bits, 214, 6, 0);       // vn=0 (reserved)
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    REQUIRE(dec.decode(frame, msg, 0));

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->ex_lalert_local.vn == 0);  // Vn is stored as-is
}

TEST_CASE("DCX Edge: Vn=63 (max) decoded") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);
    setBits(bits, 14, 1, 0);
    setBits(bits, 15, 9, 0);
    setBits(bits, 24, 2, 1);
    setBits(bits, 26, 9, 111);
    setBits(bits, 35, 5, 1);
    setBits(bits, 40, 7, 10);
    setBits(bits, 214, 6, 63);      // vn=63 (max 6-bit)
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    REQUIRE(dec.decode(frame, msg, 0));

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->ex_lalert_local.vn == 63);
}
#endif
