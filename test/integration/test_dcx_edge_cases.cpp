// DCX (MT=44) デコーダ異常系・境界値テスト方針: テストは通すためのものではなく誤った実装を落とすもの（誤実装混入時に失敗するケースを網羅）

#include "../test_helpers.h"
#include "../src/internal/DcxHelper.h"
#include "doctest.h"

using namespace azaraC;

#if (AZARAC_ENABLE_DCX_CAMF)

// DCX 分類（Null / Outside / A3）の表駆動テスト

namespace {

static Message decodeEdge(uint8_t sdmt, uint16_t sdm, uint8_t a1, uint16_t a2,
                          uint8_t a3, uint8_t a4, uint16_t ex1, uint8_t vn) {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);      // PAB=A
    setBits(bits, 8, 6, 44);        // MT=44
    setBits(bits, 14, 1, sdmt);
    setBits(bits, 15, 9, sdm);
    setBits(bits, 24, 2, a1);
    setBits(bits, 26, 9, a2);
    setBits(bits, 35, 5, a3);
    setBits(bits, 40, 7, a4);
    setBits(bits, 146, 16, ex1);
    setBits(bits, 214, 6, vn);
    setBits(bits, 226, 24, crc24qRef(bits, 226));

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    dec.decode(frame, msg, 0);
    return msg;
}

} // namespace

TEST_CASE("DCX Edge: NullMessage classification") {
    // A1=0, A2=111(Japan), A3=0 が前提。CAMF/拡張が非ゼロなら Unknown（A3=0 は not used）。
    struct Case {
        uint16_t sdm;
        uint8_t a4;
        uint16_t ex1;
        uint8_t vn;
        bool is_null;
        Mt44ServiceKind kind;
    };
    const Case cases[] = {
        {0,     0, 1101, 1, false, Mt44ServiceKind::Unknown},
        {0,     0, 0,    0, true,  Mt44ServiceKind::NullMessage},
        {0x1FF, 5, 0,    1, false, Mt44ServiceKind::Unknown},
    };
    for (const Case& c : cases) {
        INFO("is_null=", c.is_null);
        Message msg = decodeEdge(0, c.sdm, 0, 111, 0, c.a4, c.ex1, c.vn);
        REQUIRE(msg.valid);
        const Mt44Data* mt44 = msg.getMt44();
        REQUIRE(mt44 != nullptr);
        CHECK(mt44->is_null_message == c.is_null);
        CHECK(mt44->service_kind == c.kind);
    }
}

TEST_CASE("DCX Edge: OutsideJapan classification") {
    struct Case { uint8_t a1; uint16_t a2; uint8_t a3; uint8_t a4; };
    const Case cases[] = {
        {1, 0,   5, 5},
        {1, 110, 1, 0},
    };
    for (const Case& c : cases) {
        INFO("a2=", c.a2);
        Message msg = decodeEdge(0, 0, c.a1, c.a2, c.a3, c.a4, 0, 1);
        REQUIRE(msg.valid);
        const Mt44Data* mt44 = msg.getMt44();
        REQUIRE(mt44 != nullptr);
        CHECK(mt44->service_kind == Mt44ServiceKind::OutsideJapan);
        CHECK(mt44->ex_kind == ExtendedKind::OutsideJapan);
    }
}

TEST_CASE("DCX Edge: Japan provider classification (JAlert/LocalGovernment/Unknown)") {
    struct Case { uint16_t sdm; uint8_t a4; uint8_t a3; Mt44ServiceKind kind; };
    const Case cases[] = {
        {0x1FF, 5, 0,  Mt44ServiceKind::Unknown},
        {0x1FF, 5, 2,  Mt44ServiceKind::JAlert},
        {0x1FF, 5, 3,  Mt44ServiceKind::JAlert},
        {0x1FF, 5, 4,  Mt44ServiceKind::LocalGovernment},
        {0x1FF, 5, 5,  Mt44ServiceKind::Unknown},
        {0x1FF, 5, 31, Mt44ServiceKind::Unknown},
    };
    for (const Case& c : cases) {
        INFO("a3=", static_cast<int>(c.a3));
        Message msg = decodeEdge(0, c.sdm, 1, 111, c.a3, c.a4, 0, 1);
        REQUIRE(msg.valid);
        const Mt44Data* mt44 = msg.getMt44();
        REQUIRE(mt44 != nullptr);
        CHECK(mt44->service_kind == c.kind);
    }
}

// B1-B4 と has_main_ellipse の分離テスト

TEST_CASE("DCX Edge: B4 (A17=3) without main ellipse") {
    // B4 は A12-A16（主楕円）の有無と独立にデコードされる
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);
    setBits(bits, 14, 1, 0);
    setBits(bits, 15, 9, 0x1FF);
    setBits(bits, 24, 2, 1);
    setBits(bits, 26, 9, 111);
    setBits(bits, 35, 5, 1);
    setBits(bits, 40, 7, 36);     // a4=36 (Earthquake)
    // A12-A16 がすべてゼロ → 主楕円なし
    setBits(bits, 129, 2, 3);     // A17=3 (B4)
    // 地震データの A18: D1=0x05, D2=0x03, D3=0x00, D4=0x00
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
    // A17=3 の B4 処理は has_main_ellipse ブロックの外（DecoderDcx.cpp:259-267）
    CHECK(mt44->mt44_decoded.main_ellipse_present == false);
    // → main_ellipse 不在でも b4_present=true になることを確認
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

// OutsideJapan 拡張フィールドの検証

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
    CHECK(mt44->ex.ex_outside.vn == 1);
}

// A5 severity 境界値テスト

TEST_CASE("DCX Edge: A5 boundary values with L-Alert") {
    struct Case { uint8_t a5; };
    const Case cases[] = {{0}, {3}};
    for (const Case& c : cases) {
        INFO("a5=", static_cast<int>(c.a5));
        uint8_t bits[32] = {};
        setBits(bits, 0, 8, 0x53);
        setBits(bits, 8, 6, 44);
        setBits(bits, 14, 1, 0);
        setBits(bits, 15, 9, 0x1FF);
        setBits(bits, 24, 2, 1);
        setBits(bits, 26, 9, 111);
        setBits(bits, 35, 5, 1);       // a3=1 (L-Alert)
        setBits(bits, 40, 7, 10);
        setBits(bits, 47, 2, c.a5);
        setBits(bits, 214, 6, 1);
        setBits(bits, 226, 24, crc24qRef(bits, 226));

        Frame frame{};
        memcpy(frame.bits, bits, 32);
        frame.svid = 193;
        Decoder dec;
        Message msg{};
        REQUIRE(dec.decode(frame, msg, 0));

        const Mt44Data* mt44 = msg.getMt44();
        REQUIRE(mt44 != nullptr);
        CHECK(mt44->camf.a5 == c.a5);
        CHECK(mt44->service_kind == Mt44ServiceKind::LAlert);
    }
}

// SDMT/SDM 境界値テスト

TEST_CASE("DCX Edge: SDMT=1, SDM boundaries") {
    struct Case { uint16_t sdm; };
    const Case cases[] = {{0}, {511}};
    for (const Case& c : cases) {
        INFO("sdm=", c.sdm);
        uint8_t bits[32] = {};
        setBits(bits, 0, 8, 0x53);
        setBits(bits, 8, 6, 44);
        setBits(bits, 14, 1, 1);       // SDMT=1 (all)
        setBits(bits, 15, 9, c.sdm);
        setBits(bits, 24, 2, 1);
        setBits(bits, 26, 9, 111);
        setBits(bits, 35, 5, 1);
        setBits(bits, 40, 7, 10);
        setBits(bits, 214, 6, 1);
        setBits(bits, 226, 24, crc24qRef(bits, 226));

        Frame frame{};
        memcpy(frame.bits, bits, 32);
        frame.svid = 193;
        Decoder dec;
        Message msg{};
        REQUIRE(dec.decode(frame, msg, 0));

        const Mt44Data* mt44 = msg.getMt44();
        REQUIRE(mt44 != nullptr);
        CHECK(mt44->sd.sdmt == 1);
        CHECK(mt44->sd.sdm == c.sdm);
        CHECK(mt44->service_kind == Mt44ServiceKind::LAlert);
    }
}

// DCX 廃番メッセージ（有効なバージョンの確認）

TEST_CASE("DCX Edge: Vn boundaries are stored as-is") {
    struct Case { uint8_t vn; };
    const Case cases[] = {{0}, {63}};
    for (const Case& c : cases) {
        INFO("vn=", static_cast<int>(c.vn));
        uint8_t bits[32] = {};
        setBits(bits, 0, 8, 0x53);
        setBits(bits, 8, 6, 44);
        setBits(bits, 14, 1, 0);
        setBits(bits, 15, 9, 0);
        setBits(bits, 24, 2, 1);
        setBits(bits, 26, 9, 111);
        setBits(bits, 35, 5, 1);
        setBits(bits, 40, 7, 10);
        setBits(bits, 214, 6, c.vn);
        setBits(bits, 226, 24, crc24qRef(bits, 226));

        Frame frame{};
        memcpy(frame.bits, bits, 32);
        frame.svid = 193;
        Decoder dec;
        Message msg{};
        REQUIRE(dec.decode(frame, msg, 0));

        const Mt44Data* mt44 = msg.getMt44();
        REQUIRE(mt44 != nullptr);
        CHECK(mt44->ex.ex_lalert_local.vn == c.vn);
    }
}

TEST_CASE("DCX Edge: onset_time on non-Monday, a7==0, and report_unix==2000-01-01") {
    auto decodeWith = [](uint16_t a7, uint32_t report_unix) -> TimeFields {
        uint8_t bits[32] = {};
        setBits(bits, 0, 8, 0x53);
        setBits(bits, 8, 6, 44);
        setBits(bits, 14, 1, 0);
        setBits(bits, 15, 9, 0);
        setBits(bits, 24, 2, 1);
        setBits(bits, 26, 9, 111); // Japan
        setBits(bits, 35, 5, 1);   // L-Alert
        setBits(bits, 40, 7, 10);
        setBits(bits, 49, 1, 0);   // a6 = 0 (this week)
        setBits(bits, 50, 14, a7); // a7
        setBits(bits, 226, 24, crc24qRef(bits, 226));

        Frame frame{};
        for (size_t i = 0; i < 32; ++i) frame.bits[i] = bits[i];
        frame.svid = 193;
        Decoder dec;
        Message msg{};
        REQUIRE(dec.decode(frame, msg, report_unix));
        return msg.getMt44()->onset_time;
    };

    // 2024-06-06 (Thu, dow=3): 今週月曜は 2024-06-03
    const uint32_t thu = daysFromCivil(2024, 6, 6) * 86400u + 12u * 3600u;
    TimeFields mon = decodeWith(1, thu);
    CHECK(mon.unix_time == daysFromCivil(2024, 6, 3) * 86400u);
    CHECK(mon.month == 6);
    CHECK(mon.day == 3);
    CHECK(mon.hour == 0);
    CHECK(mon.minute == 0);

    // a7 == 1441 → 火曜 2024-06-04 00:00
    TimeFields tue = decodeWith(1441, thu);
    CHECK(tue.unix_time == daysFromCivil(2024, 6, 4) * 86400u);
    CHECK(tue.month == 6);
    CHECK(tue.day == 4);

    // a7 == 0 → onset_time は未設定 (unix_time == 0)
    TimeFields none = decodeWith(0, thu);
    CHECK(none.unix_time == 0);

    // report_unix == 946684800 (2000-01-01, Sat, dow=5) ちょうどは有効扱い → 月曜 1999-12-27
    TimeFields epoch2000 = decodeWith(1, 946684800u);
    CHECK(epoch2000.unix_time == daysFromCivil(1999, 12, 27) * 86400u);
    CHECK(epoch2000.month == 12);
    CHECK(epoch2000.day == 27);
}

TEST_CASE("DCX Edge: LocalGovernment additional_area present iff any of ex2..ex7 is non-zero") {
    auto decodeLocal = [](uint8_t ex2, uint32_t ex3, uint32_t ex4, uint8_t ex5, uint8_t ex6, uint8_t ex7) -> bool {
        uint8_t bits[32] = {};
        setBits(bits, 0, 8, 0x53);
        setBits(bits, 8, 6, 44);
        setBits(bits, 24, 2, 1);
        setBits(bits, 26, 9, 111); // Japan
        setBits(bits, 35, 5, 4);   // LocalGovernment (a3=4)
        setBits(bits, 40, 7, 10);
        // EX2(1)@162, EX3(17)@163, EX4(17)@180, EX5(5)@197, EX6(5)@202, EX7(7)@207
        setBits(bits, 162, 1, ex2);
        setBits(bits, 163, 17, ex3);
        setBits(bits, 180, 17, ex4);
        setBits(bits, 197, 5, ex5);
        setBits(bits, 202, 5, ex6);
        setBits(bits, 207, 7, ex7);
        setBits(bits, 226, 24, crc24qRef(bits, 226));

        Frame frame{};
        for (size_t i = 0; i < 32; ++i) frame.bits[i] = bits[i];
        frame.svid = 193;
        Decoder dec;
        Message msg{};
        REQUIRE(dec.decode(frame, msg, 0));
        const Mt44Data* mt44 = msg.getMt44();
        REQUIRE(mt44 != nullptr);
        REQUIRE(mt44->service_kind == Mt44ServiceKind::LocalGovernment);
        return mt44->mt44_decoded.additional_area.present;
    };

    CHECK_FALSE(decodeLocal(0, 0, 0, 0, 0, 0));
    CHECK(decodeLocal(1, 0, 0, 0, 0, 0));
    CHECK(decodeLocal(0, 1, 0, 0, 0, 0));
    CHECK(decodeLocal(0, 0, 1, 0, 0, 0));
    CHECK(decodeLocal(0, 0, 0, 1, 0, 0));
    CHECK(decodeLocal(0, 0, 0, 0, 1, 0));
    CHECK(decodeLocal(0, 0, 0, 0, 0, 1));
}

TEST_CASE("DCX Edge: OutsideJapan decodes all 8 bytes of ex11_raw") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);
    setBits(bits, 24, 2, 1);
    setBits(bits, 26, 9, 100); // OutsideJapan (a2 != 111)
    for (int i = 0; i < 8; ++i) {
        setBits(bits, static_cast<uint16_t>(146 + i * 8), 8, static_cast<uint32_t>(0x11 + i * 0x11));
    }
    setBits(bits, 226, 24, crc24qRef(bits, 226));

    Frame frame{};
    for (size_t i = 0; i < 32; ++i) frame.bits[i] = bits[i];
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    REQUIRE(dec.decode(frame, msg, 0));
    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    REQUIRE(mt44->service_kind == Mt44ServiceKind::OutsideJapan);
    for (int i = 0; i < 8; ++i) {
        CHECK(mt44->ex.ex_outside.ex11_raw[i] == static_cast<uint8_t>(0x11 + i * 0x11));
    }
}
#endif
