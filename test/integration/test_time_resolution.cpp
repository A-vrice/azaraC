// test/integration/test_time_resolution.cpp
// report_unix 時刻解決の統合テスト
// decodeNmea ヘルパーに report_unix を渡し、resolveTime が正しく
// unix_time を解決することを検証する。

#include "../test_helpers.h"
#include "doctest.h"

using namespace azaraC;

// ═══════════════════════════════════════════════════════════════════════════════
// resolveTime 単体テスト（report_unix あり）
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("Time: resolveTime with valid report_unix (2024-06-15)") {
    // report_unix = 2024-06-15 12:00:00 UTC
    uint32_t now = 1718452800u;
    TimeFields t = TestDecoder::testResolveTime(6, 15, 12, 30, now);
    CHECK(t.month == 6);
    CHECK(t.day == 15);
    CHECK(t.hour == 12);
    CHECK(t.minute == 30);
    CHECK(t.unix_time != 0);
    // unix_time should be 2024-06-15 12:30:00
    CHECK(t.unix_time == now + 30 * 60);
}

TEST_CASE("Time: resolveTime with year boundary crossing") {
    // report_unix = 2024-01-01 00:00:00 UTC
    uint32_t now = 1704067200u;
    // 12月15日 → 2023-12-15 のラップアラウンド
    TimeFields t = TestDecoder::testResolveTime(12, 15, 0, 0, now);
    CHECK(t.unix_time == daysFromCivil(2023, 12, 15) * 86400u);
}

TEST_CASE("Time: resolveTime with month wrap-around (MDHM)") {
    // report_unix = 2024-05-15 00:00:00 UTC (5月)
    uint32_t now = daysFromCivil(2024, 5, 15) * 86400u;
    // Month=12, day=15 → 12-5=7 > 6 → 前年にラップアラウンド → 2023-12-15
    TimeFields t = TestDecoder::testResolveTime(12, 15, 0, 0, now);
    CHECK(t.month == 12);
    CHECK(t.day == 15);
    CHECK(t.unix_time == daysFromCivil(2023, 12, 15) * 86400u);
}

TEST_CASE("Time: resolveTime with invalid values rejected") {
    uint32_t now = 1704067200u;
    // Invalid day=32
    TimeFields t1 = TestDecoder::testResolveTime(0, 32, 0, 0, now);
    CHECK(t1.unix_time == 0);
    CHECK(t1.day == 0);

    // Invalid month=13
    TimeFields t2 = TestDecoder::testResolveTime(13, 1, 0, 0, now);
    CHECK(t2.unix_time == 0);
    CHECK(t2.day == 0);

    // Invalid hour=24
    TimeFields t3 = TestDecoder::testResolveTime(1, 1, 24, 0, now);
    CHECK(t3.unix_time == 0);
    CHECK(t3.day == 0);
}

TEST_CASE("Time: resolveTime with report_unix=0 returns unix_time=0") {
    TimeFields t = TestDecoder::testResolveTime(6, 15, 12, 0, 0);
    CHECK(t.day == 15);    // DHM fields are still populated
    CHECK(t.hour == 12);
    CHECK(t.minute == 0);
    CHECK(t.unix_time == 0);  // unix_time is unresolved
}

TEST_CASE("Time: resolveTime report_unix < 2000-01-01 returns unix_time=0") {
    TimeFields t = TestDecoder::testResolveTime(6, 15, 12, 0, 946684799u);
    CHECK(t.unix_time == 0);  // below 2000-01-01
}

// ═══════════════════════════════════════════════════════════════════════════════
// 津波到着時刻解決 E2E テスト
// ═══════════════════════════════════════════════════════════════════════════════

#if (AZARAC_ENABLE_TSUNAMI)
TEST_CASE("Time: Tsunami arrival_time unix resolved with valid report_unix") {
    // 津波メッセージに report_unix を指定して decode
    // report_unix = 2024-01-01 12:00:00 UTC
    const char* nmea = "$QZQSM,57,9AACA884EB0001E4F47B31E833C07C8D6920035C8800E087FF355011DDFED1C*09";
    Message msg{};
    REQUIRE(decodeNmea(nmea, msg, 1704105600u));  // report_unix 指定
    CHECK(msg.msg_type == 43);
    CHECK(msg.payload_type == MsgPayloadType::Mt43);

    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    CHECK(mt43->disaster_category == 5);

    const TsunamiData* tsunami = mt43->getTsunami();
    REQUIRE(tsunami != nullptr);

    // event_time.unix_time が解決されていること
    CHECK(mt43->event_time.unix_time != 0);

    // arrival_time.unix_time が解決されていること（基地局の event_time から計算）
    for (uint8_t i = 0; i < tsunami->count; ++i) {
        INFO("tsunami entry ", i);
        // 到達済み (hour=31, min=63) のエントリをスキップ
        if (tsunami->entries[i].arrival_time.hour <= 23 &&
            tsunami->entries[i].arrival_time.minute <= 59 &&
            tsunami->entries[i].arrival_time_raw != 2047) {
            // 到達済みでないエントリは unix_time が解決されている
            CHECK(tsunami->entries[i].arrival_time.unix_time != 0);
        }
    }
}

TEST_CASE("Time: Tsunami arrival_time unix=0 with report_unix=0") {
    // report_unix=0 の場合、arrival_time.unix_time は解決されない
    const char* nmea = "$QZQSM,57,9AACA884EB0001E4F47B31E833C07C8D6920035C8800E087FF355011DDFED1C*09";
    Message msg{};
    REQUIRE(decodeNmea(nmea, msg, 0));  // report_unix=0
    CHECK(msg.msg_type == 43);
    CHECK(msg.payload_type == MsgPayloadType::Mt43);

    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    CHECK(mt43->disaster_category == 5);

    const TsunamiData* tsunami = mt43->getTsunami();
    REQUIRE(tsunami != nullptr);

    // report_unix=0 では event_time が解決されない
    // event_time.unix_time = 0 または報告時に解決されていない
    CHECK(tsunami->entries[0].arrival_time.hour == 7);  // DHM は解決される
    CHECK(tsunami->entries[0].arrival_time.minute == 40);
    // しかし unix_time は 0
    CHECK(tsunami->entries[0].arrival_time.unix_time == 0);
}
#endif // AZARAC_ENABLE_TSUNAMI

#if (AZARAC_ENABLE_DCX_CAMF)
// ═══════════════════════════════════════════════════════════════════════════════
// DCX onset_time 解決 E2E テスト
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("Time: DCX onset_time resolved with valid report_unix") {
    // DCX メッセージ: a6=0 (current week), a7=2 (Monday 00:01)
    // IS-QZSS-DCX-004 §4.2.3.6, Table 4.2-9: A6=0 → current week, A6=1 → next week
    // EWSS CAMF v1.1 §3.3: Week starts Monday 00:00 UTC
    // report_unix = 2024-05-20 00:00:00 UTC (Monday → current week start)
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);
    setBits(bits, 14, 1, 0);
    setBits(bits, 15, 9, 0x1FF);
    setBits(bits, 24, 2, 1);
    setBits(bits, 26, 9, 111);
    setBits(bits, 35, 5, 1);
    setBits(bits, 40, 7, 10);
    setBits(bits, 47, 2, 3);
    setBits(bits, 49, 1, 0);     // a6=0 → current week (Monday-based)
    setBits(bits, 50, 14, 2);    // a7=2 → Monday 00:01 UTC
    setBits(bits, 214, 6, 1);

    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    // 2024-05-20 00:00:00 UTC (Monday) — Monday-based week starts same day
    // a6=0 (current week) かつ report_unix が週の開始 (Monday 00:00) のため
    // onset_time = report_unix + 60 = Monday 00:01 UTC となる
    uint32_t report_unix = static_cast<uint32_t>(daysFromCivil(2024, 5, 20) * 86400u);
    bool ok = dec.decode(frame, msg, report_unix);
    REQUIRE(ok);

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->onset_time.unix_time != 0);
    CHECK(mt44->onset_time.unix_time == report_unix + 60);
    // a7=2 → Monday 00:01 UTC
    CHECK(mt44->onset_time.minute == 1);
    CHECK(mt44->onset_time.hour == 0);
}

TEST_CASE("Time: DCX onset_time NOT resolved with report_unix=0") {
    // report_unix=0 の場合、DCX の onset_time は解決されない
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 44);
    setBits(bits, 14, 1, 0);
    setBits(bits, 15, 9, 0x1FF);
    setBits(bits, 24, 2, 1);
    setBits(bits, 26, 9, 111);
    setBits(bits, 35, 5, 1);
    setBits(bits, 40, 7, 10);
    setBits(bits, 47, 2, 3);
    setBits(bits, 49, 1, 0);
    setBits(bits, 50, 14, 60);
    setBits(bits, 214, 6, 1);

    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    bool ok = dec.decode(frame, msg, 0);  // report_unix=0
    REQUIRE(ok);

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    // report_unix=0 では onset_time は解決されない
    CHECK(mt44->onset_time.unix_time == 0);
}
#endif

// ═══════════════════════════════════════════════════════════════════════════════
// 実データ EEW と Hypocenter の event_time 検証
// ═══════════════════════════════════════════════════════════════════════════════

#if (AZARAC_ENABLE_EEW)
TEST_CASE("Time: EEW event_time resolved with real report_unix") {
    // 実データに report_unix を指定して event_time が解決されることを確認
    Message msg{};
    const char* nmea = "$QZQSM,57,9AAC8884E3009324000009C60539619DC0000100000000010000001065F294C*08";
    REQUIRE(decodeNmea(nmea, msg, 1704067200u));  // 2024-01-01 00:00:00 UTC
    CHECK(msg.msg_type == 43);

    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    CHECK(mt43->disaster_category == 1);

    // event_time.unix_time が解決されていること
    CHECK(mt43->event_time.unix_time != 0);
}
#endif // AZARAC_ENABLE_EEW
