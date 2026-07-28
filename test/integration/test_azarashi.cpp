// test/integration/test_azarashi.cpp
// DCX (MT=44) の azarashi 比較テストは test_azarashi_dcx.cpp に統合済み
// DCR (MT=43) の azarashi 比較テストは test_azarashi_dcr.cpp に統合済み
// このファイルは無効化済み（#if 0）。重複テストのため。
// Makefile の TEST_SRCS からも削除済み。

#if 0

#include "../test_helpers.h"
#include "doctest.h"

using namespace azaraC;

// 現在は汎用テストのみ。DCX/DCRの個別比較テストは以下のファイルに分割済み:
// - test_azarashi_dcx.cpp (MT=44 DCX)
// - test_azarashi_dcr.cpp (MT=43 DCR)

// ═══════════════════════════════════════════════════════════════════════════════
// azarashi 互換性汎用テスト
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("DCR: MT=43 EEW basic decode matches azarashi semantics") {
    // 能登半島地震の実データ: 緊急地震速報 発表 最優先
    // azarashi でのデコード結果と照合
    const char* nmea = "$QZQSM,57,9AAC8884E3009324000009C60539619DC0000100000000010000001065F294C*08";
    Message msg{};
    REQUIRE(decodeNmea(nmea, msg));
    CHECK(msg.msg_type == 43);
    CHECK(msg.payload_type == MsgPayloadType::Mt43);

    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    CHECK(mt43->disaster_category == 1);
    CHECK(mt43->report_classification == 1);
    CHECK(mt43->information_type == 0);

    const EewData* eew = mt43->getEew();
    REQUIRE(eew != nullptr);
    // azarashi でのデコード結果と一致することを確認
    CHECK(eew->depth == 10);        // 10km
    CHECK(eew->magnitude == 57);    // M5.7
    CHECK(eew->epicenter == 390);   // 石川県能登地方
    CHECK(eew->intensity_lower == 7); // 震度5強
    CHECK(eew->intensity_upper == 7); // 震度5強
    CHECK(eew->long_period_lower == 2); // 長周期地震動階級1
    CHECK(eew->long_period_upper == 2); // 長周期地震動階級1
    CHECK(eew->notification_count == 1);
    CHECK(eew->notification[0] == 201);
    CHECK(eew->region_count == 2);
    CHECK(eew->regions[0] == 22); // 石川
    CHECK(eew->regions[1] == 62); // 北陸
}

TEST_CASE("DCR: MT=43 Tsunami decode with arrival time") {
    // 津波 発表 最優先
    // AzaraC のデコード結果を具体的に検証
    const char* nmea = "$QZQSM,57,9AACA884EB0001E4F47B31E833C07C8D6920035C8800E087FF355011DDFED1C*09";
    Message msg{};
    REQUIRE(decodeNmea(nmea, msg));
    CHECK(msg.msg_type == 43);
    CHECK(msg.payload_type == MsgPayloadType::Mt43);

    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    CHECK(mt43->disaster_category == 5);
    CHECK(mt43->report_classification == 1); // 最優先
    CHECK(mt43->information_type == 0);      // 発表

    const TsunamiData* tsunami = mt43->getTsunami();
    REQUIRE(tsunami != nullptr);
    CHECK(tsunami->warning_code == 3); // 津波警報
    CHECK(tsunami->count == 5);         // 5地域
    // 各エントリの具体的な値を検証（azarashi 0.16.1 のデコード結果と照合）
    // IS-QZSS-DCR-016: entry layout = Ta(12) + Th(4) + Pl(10)
    CHECK(tsunami->entries[0].region_code == 240); // 山形県
    CHECK(tsunami->entries[0].height_code == 3);   // 3m
    CHECK(tsunami->entries[1].region_code == 361); // 石川県加賀
    CHECK(tsunami->entries[1].height_code == 3);   // 3m
    CHECK(tsunami->entries[2].region_code == 370); // 福井県
    CHECK(tsunami->entries[2].height_code == 3);   // 3m
    CHECK(tsunami->entries[3].region_code == 520); // 兵庫県北部
    CHECK(tsunami->entries[3].height_code == 3);   // 3m
    CHECK(tsunami->entries[4].region_code == 340); // 新潟県上中下越
    CHECK(tsunami->entries[4].height_code == 3);   // 3m
    // 到着予想時刻（arrival_time）の検証
    // decodeNmea は report_unix=0 で呼ぶため month/day/unix_time は未解決
    CHECK(tsunami->entries[0].arrival_time_raw == 488); // next=0, hour=7, min=40
    CHECK(tsunami->entries[0].arrival_time.hour == 7);
    CHECK(tsunami->entries[0].arrival_time.minute == 40);
    CHECK(tsunami->entries[1].arrival_time_raw == 498); // next=0, hour=7, min=50
    CHECK(tsunami->entries[1].arrival_time.hour == 7);
    CHECK(tsunami->entries[1].arrival_time.minute == 50);
    CHECK(tsunami->entries[2].arrival_time_raw == 512); // next=0, hour=8, min=0
    CHECK(tsunami->entries[2].arrival_time.hour == 8);
    CHECK(tsunami->entries[2].arrival_time.minute == 0);
    CHECK(tsunami->entries[3].arrival_time_raw == 512); // next=0, hour=8, min=0
    CHECK(tsunami->entries[3].arrival_time.hour == 8);
    CHECK(tsunami->entries[3].arrival_time.minute == 0);
    CHECK(tsunami->entries[4].arrival_time_raw == 2047); // next=0, hour=31, min=63 (到達済み/不明)
    CHECK(tsunami->entries[4].arrival_time.hour == 0);    // hour>23 → 0 クリア
    CHECK(tsunami->entries[4].arrival_time.minute == 0);  // min>59 → 0 クリア
}

TEST_CASE("DCX: MT=44 L-Alert basic decode matches azarashi semantics") {
    // L-Alert - CBRNE Air Strike
    const char* nmea = "$QZQSM,55,9AB0840DE10208ADE0000000000000000000011340000000000000132F0D238*04";
    Message msg{};
    REQUIRE(decodeNmea(nmea, msg));
    CHECK(msg.msg_type == 44);
    CHECK(msg.payload_type == MsgPayloadType::Mt44);

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->service_kind == Mt44ServiceKind::LAlert);
    CHECK(mt44->camf.a2 == 111);
    CHECK(mt44->camf.a3 == 1);
    CHECK(mt44->ex_lalert_local.ex1 == 1101);
}

#endif // #if 0 — テストは test_azarashi_dcr.cpp / test_azarashi_dcx.cpp に移行済み
