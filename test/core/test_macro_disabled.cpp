// test/core/test_macro_disabled.cpp
// AZARAC_ENABLE_* 無効化時にデコーダが正しくエラーを返すことのランタイムテスト。
// 各テストは #if !(AZARAC_ENABLE_XXX) ガードで囲み、マクロ有効時は TEST_CASE ごと消える（恒常 PASS する空テストを残さない）。無効化ビルドでコンパイルして検証する（全 13 マクロ一括は make macro）。

#include "../test_helpers.h"
#include "doctest.h"

using namespace azaraC;


// DCR の災害カテゴリ（1-14）メッセージを生成し、マクロ無効化時の拒否を検証する。
// [[maybe_unused]]: デフォルトビルド（全マクロ有効）では参照されないため
[[maybe_unused]] static void testDisabledDcrCategory(uint8_t disaster_category) {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);       // Preamble
    setBits(bits, 8, 6, 43);         // msg_type = 43 (DCR)
    setBits(bits, 14, 3, 1);         // report_classification
    setBits(bits, 17, 4, disaster_category);  // disaster_category
    setBits(bits, 214, 6, 1);        // version = 1
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    bool ok = dec.decode(frame, msg, 0);

    CHECK_FALSE(ok);
    CHECK_FALSE(msg.valid);
    CHECK(msg.msg_type == 43);
    CHECK(msg.unsupported_reason == UnsupportedReason::DisabledAtCompileTime);
    // 拒否時はペイロードを Empty のまま（メタデータ未設定）
    CHECK(msg.payload_type == MsgPayloadType::Empty);
}

// DCX (MT=44) メッセージを生成し、マクロ無効化時の拒否を検証する。
// [[maybe_unused]]: デフォルトビルド（全マクロ有効）では参照されないため
[[maybe_unused]] static void testDisabledDcx() {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);       // Preamble
    setBits(bits, 8, 6, 44);         // msg_type = 44 (DCX)
    setBits(bits, 24, 2, 1);         // A1 = 1
    setBits(bits, 26, 9, 111);       // A2 = 111 (Japan)
    setBits(bits, 35, 5, 1);         // A3 = 1
    setBits(bits, 40, 7, 10);        // A4 = 10
    setBits(bits, 214, 6, 1);        // vn = 1
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    bool ok = dec.decode(frame, msg, 0);

    CHECK_FALSE(ok);
    CHECK_FALSE(msg.valid);
    CHECK(msg.msg_type == 44);
    CHECK(msg.unsupported_reason == UnsupportedReason::DisabledAtCompileTime);
    // 拒否時はペイロードを Empty のまま
    CHECK(msg.payload_type == MsgPayloadType::Empty);
}

// DCR カテゴリの無効化テスト（13 個中 12 個）。

#if !(AZARAC_ENABLE_EEW)
TEST_CASE("Macro: Disabled EEW (dc=1) rejected") {
    testDisabledDcrCategory(1);
}
#endif

#if !(AZARAC_ENABLE_HYPOCENTER)
TEST_CASE("Macro: Disabled Hypocenter (dc=2) rejected") {
    testDisabledDcrCategory(2);
}
#endif

#if !(AZARAC_ENABLE_SEISMIC)
TEST_CASE("Macro: Disabled Seismic (dc=3) rejected") {
    testDisabledDcrCategory(3);
}
#endif

#if !(AZARAC_ENABLE_NANKAI)
TEST_CASE("Macro: Disabled Nankai (dc=4) rejected") {
    testDisabledDcrCategory(4);
}
#endif

#if !(AZARAC_ENABLE_TSUNAMI)
TEST_CASE("Macro: Disabled Tsunami (dc=5) rejected") {
    testDisabledDcrCategory(5);
}
#endif

#if !(AZARAC_ENABLE_NW_PAC_TSUNAMI)
TEST_CASE("Macro: Disabled NW Pacific Tsunami (dc=6) rejected") {
    testDisabledDcrCategory(6);
}
#endif

#if !(AZARAC_ENABLE_VOLCANO)
TEST_CASE("Macro: Disabled Volcano (dc=8) rejected") {
    testDisabledDcrCategory(8);
}
#endif

#if !(AZARAC_ENABLE_ASH_FALL)
TEST_CASE("Macro: Disabled Ash Fall (dc=9) rejected") {
    testDisabledDcrCategory(9);
}
#endif

#if !(AZARAC_ENABLE_WEATHER)
TEST_CASE("Macro: Disabled Weather (dc=10) rejected") {
    testDisabledDcrCategory(10);
}
#endif

#if !(AZARAC_ENABLE_FLOOD)
TEST_CASE("Macro: Disabled Flood (dc=11) rejected") {
    testDisabledDcrCategory(11);
}
#endif

#if !(AZARAC_ENABLE_TYPHOON)
TEST_CASE("Macro: Disabled Typhoon (dc=12) rejected") {
    testDisabledDcrCategory(12);
}
#endif

#if !(AZARAC_ENABLE_MARINE)
TEST_CASE("Macro: Disabled Marine (dc=14) rejected") {
    testDisabledDcrCategory(14);
}
#endif

// DCX CAMF マクロ無効化テスト

#if !(AZARAC_ENABLE_DCX_CAMF)
TEST_CASE("Macro: Disabled DCX CAMF (MT=44) rejected") {
    testDisabledDcx();
}
#endif

// マクロの有無に依存しない共通動作確認。

TEST_CASE("Macro: Disabled all macros - invalid preamble still rejected") {
    uint8_t bits[32] = {};
    // 不正プリアンブル（bits[0] = 0x00）
    setBits(bits, 8, 6, 43);         // msg_type = 43
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    bool ok = dec.decode(frame, msg, 0);
    CHECK_FALSE(ok);  // 不正プリアンブルで弾かれる
    CHECK_FALSE(msg.valid);
    // unsupported_reason は None のまま（CRCチェック通過前にリジェクト）
    CHECK(msg.unsupported_reason == UnsupportedReason::None);
}

TEST_CASE("Macro: Disabled all macros - CRC mismatch returns false") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);       // 有効プリアンブル
    setBits(bits, 8, 6, 43);         // msg_type = 43
    setBits(bits, 214, 6, 1);        // version
    // CRC を設定しない → CRC ミスマッチ

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    bool ok = dec.decode(frame, msg, 0);
    CHECK_FALSE(ok);  // CRC 不一致で弾かれる
    CHECK_FALSE(msg.valid);
    CHECK(msg.unsupported_reason == UnsupportedReason::None);
}

TEST_CASE("Macro: Disabled all macros - unknown MT returns false") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);       // 有効プリアンブル
    setBits(bits, 8, 6, 0);          // msg_type = 0 (unknown)
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    bool ok = dec.decode(frame, msg, 0);
    CHECK_FALSE(ok);
    CHECK_FALSE(msg.valid);
    CHECK(msg.unsupported_reason == UnsupportedReason::UnknownCategory);
}
