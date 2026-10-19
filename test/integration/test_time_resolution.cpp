// test/integration/test_time_resolution.cpp
// report_unix を渡し、resolveTime / event_time の unix_time 解決を検証する統合テスト。

#include "../test_helpers.h"
#include "doctest.h"

using namespace azaraC;

// resolveTime 単体テスト（report_unix あり）

TEST_CASE("Time: resolveTime with valid report_unix (2024-06-15)") {
    // report_unix = 2024-06-15 12:00:00 UTC
    uint32_t now = 1718452800u;
    TimeFields t = TestDecoder::testResolveTime(6, 15, 12, 30, now);
    CHECK(t.month == 6);
    CHECK(t.day == 15);
    CHECK(t.hour == 12);
    CHECK(t.minute == 30);
    CHECK(t.unix_time != 0);
    CHECK(t.unix_time == now + 30 * 60);
}

TEST_CASE("Time: resolveTime with year boundary crossing") {
    // report_unix = 2024-01-01 00:00:00 UTC
    uint32_t now = 1704067200u;
    // 12月15日 → 2023-12-15 のラップアラウンド
    TimeFields t = TestDecoder::testResolveTime(12, 15, 0, 0, now);
    CHECK(t.unix_time == daysFromCivil(2023, 12, 15) * 86400u);
}

TEST_CASE("Time: resolveTime DHM month-end event (base Jan 31, day 15)") {
    // extractDHM は過去イベント専用。base 2024-01-31 で day=15 の最寄り Feb 15 はマージン(3日)超 → stale → 過去の直近 Jan 15。旧 ±15 は Feb 15 と誤判定。
    uint32_t now = daysFromCivil(2024, 1, 31) * 86400u;
    TimeFields t = TestDecoder::testResolveTime(0, 15, 0, 0, now);
    CHECK(t.month == 1);
    CHECK(t.day == 15);
    CHECK(t.unix_time == daysFromCivil(2024, 1, 15) * 86400u);
}

TEST_CASE("Time: resolveTime DHM same-day event (base Jan 31, day 31)") {
    uint32_t now = daysFromCivil(2024, 1, 31) * 86400u;
    TimeFields t = TestDecoder::testResolveTime(0, 31, 0, 0, now);
    CHECK(t.month == 1);
    CHECK(t.day == 31);
    CHECK(t.unix_time == daysFromCivil(2024, 1, 31) * 86400u);
}

TEST_CASE("Time: resolveTime DHM future-in-month steps back (base Mar 1, day 15)") {
    // base 2024-03-01。day=15 の最寄り Mar 15 (14日後) はマージン(3日)超 → stale → 過去の直近 Feb 15。
    uint32_t now = daysFromCivil(2024, 3, 1) * 86400u;
    TimeFields t = TestDecoder::testResolveTime(0, 15, 0, 0, now);
    CHECK(t.month == 2);
    CHECK(t.day == 15);
    CHECK(t.unix_time == daysFromCivil(2024, 2, 15) * 86400u);
}

TEST_CASE("Time: resolveTime DHM mid-month (base Mar 15, day 15)") {
    uint32_t now = daysFromCivil(2024, 3, 15) * 86400u;
    TimeFields t = TestDecoder::testResolveTime(0, 15, 0, 0, now);
    CHECK(t.month == 3);
    CHECK(t.day == 15);
    CHECK(t.unix_time == daysFromCivil(2024, 3, 15) * 86400u);
}

TEST_CASE("Time: resolveTime DHM day/month boundary (report 1/31 23:00, day 1 02:00)") {
    // 報告 1/31 23:00、イベント 2/1 02:00（未来側 3 時間）はマージン内 → Feb 1 に解決。pure past-bias は Jan 1 と誤る。
    uint32_t now = daysFromCivil(2024, 1, 31) * 86400u + 23 * 3600u;
    TimeFields t = TestDecoder::testResolveTime(0, 1, 2, 0, now);
    CHECK(t.month == 2);
    CHECK(t.day == 1);
    CHECK(t.unix_time == daysFromCivil(2024, 2, 1) * 86400u + 2 * 3600u);
}

TEST_CASE("Time: resolveTime with month wrap-around (MDHM)") {
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
    CHECK(t.unix_time == 0);
}

TEST_CASE("Time: resolveTime report_unix < 2000-01-01 returns unix_time=0") {
    TimeFields t = TestDecoder::testResolveTime(6, 15, 12, 0, 946684799u);
    CHECK(t.unix_time == 0);  // below 2000-01-01
}

// 津波到着時刻解決 E2E テスト

#if (AZARAC_ENABLE_TSUNAMI)
TEST_CASE("Time: Tsunami arrival_time unix resolved with valid report_unix") {
    // report_unix = 2024-01-01 12:00:00 UTC
    const char* nmea = "$QZQSM,57,9AACA884EB0001E4F47B31E833C07C8D6920035C8800E087FF355011DDFED1C*09";
    Message msg{};
    REQUIRE(decodeNmea(nmea, msg, 1704105600u));
    CHECK(msg.msg_type == 43);
    CHECK(msg.payload_type == MsgPayloadType::Mt43);

    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    CHECK(mt43->disaster_category == 5);

    const TsunamiData* tsunami = mt43->getTsunami();
    REQUIRE(tsunami != nullptr);

    CHECK(mt43->event_time.unix_time != 0);

    // arrival_time は基地局の event_time から計算
    for (uint8_t i = 0; i < tsunami->count; ++i) {
        INFO("tsunami entry ", i);
        // 到達済み (hour=31, min=63) のエントリをスキップ
        if (tsunami->entries[i].arrival_time.hour <= 23 &&
            tsunami->entries[i].arrival_time.minute <= 59 &&
            tsunami->entries[i].arrival_time_raw != 2047) {
            CHECK(tsunami->entries[i].arrival_time.unix_time != 0);
        }
    }
}

TEST_CASE("Time: Tsunami arrival_time unix=0 with report_unix=0") {
    const char* nmea = "$QZQSM,57,9AACA884EB0001E4F47B31E833C07C8D6920035C8800E087FF355011DDFED1C*09";
    Message msg{};
    REQUIRE(decodeNmea(nmea, msg, 0));
    CHECK(msg.msg_type == 43);
    CHECK(msg.payload_type == MsgPayloadType::Mt43);

    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    CHECK(mt43->disaster_category == 5);

    const TsunamiData* tsunami = mt43->getTsunami();
    REQUIRE(tsunami != nullptr);

    // report_unix=0 では unix_time は未解決（DHM フィールドは設定される）
    CHECK(tsunami->entries[0].arrival_time.hour == 7);
    CHECK(tsunami->entries[0].arrival_time.minute == 40);
    CHECK(tsunami->entries[0].arrival_time.unix_time == 0);
}
#endif // AZARAC_ENABLE_TSUNAMI

#if (AZARAC_ENABLE_DCX_CAMF)
// DCX onset_time 解決 E2E テスト

TEST_CASE("Time: DCX onset_time resolved with valid report_unix") {
    // DCX a6=0 (current week), a7=2 (Monday 00:01)
    // IS-QZSS-DCX-004 §4.2.3.6, Table 4.2-9: A6=0 → current week, A6=1 → next week
    // EWSS CAMF v1.1 §3.3: Week starts Monday 00:00 UTC
    // report_unix = 2024-05-20 00:00:00 UTC (Monday = 週の起点)
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
    // a6=0 の週の起点 (Monday 00:00) と report_unix が同日 → onset_time = report_unix + 60
    uint32_t report_unix = static_cast<uint32_t>(daysFromCivil(2024, 5, 20) * 86400u);
    bool ok = dec.decode(frame, msg, report_unix);
    REQUIRE(ok);

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->onset_time.unix_time != 0);
    CHECK(mt44->onset_time.unix_time == report_unix + 60);
    CHECK(mt44->onset_time.minute == 1);
    CHECK(mt44->onset_time.hour == 0);
}

TEST_CASE("Time: DCX onset_time A7 boundary (16-bit overflow guard)") {
    // A7 は 1..10080（週頭からの分）。16 bit の unsigned int では (a7-1)*60 が 65535 を超えた時点で
    // 週内の別時刻へ折り返す（a7=1094 が最初の外れ値、a7=10080 が上限）。ここでは境界の意味
    // （週頭 + (a7-1) 分）を固定する。
    struct Case { uint16_t a6, a7; uint32_t offset_s; uint8_t hour, minute; };
    const Case cases[] = {
        {0, 1094,  65580u, 18, 13},   // 16 bit で最初に折り返す値
        {1, 10080, 604740u, 23, 59},  // A7 の上限 = 翌週の日曜 23:59
    };

    // 2024-05-20 は月曜 00:00 UTC（週の起点）
    const uint32_t report_unix = static_cast<uint32_t>(daysFromCivil(2024, 5, 20) * 86400u);

    for (const Case& c : cases) {
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
        setBits(bits, 49, 1, c.a6);
        setBits(bits, 50, 14, c.a7);
        setBits(bits, 214, 6, 1);
        setBits(bits, 226, 24, crc24qRef(bits, 226));

        Frame frame{};
        memcpy(frame.bits, bits, 32);
        frame.svid = 193;
        Decoder dec;
        Message msg{};
        REQUIRE(dec.decode(frame, msg, report_unix));

        const Mt44Data* mt44 = msg.getMt44();
        REQUIRE(mt44 != nullptr);
        // a6=1 は翌週の月曜が起点
        const uint32_t week_start = report_unix + (c.a6 ? 7u * 86400u : 0u);
        CHECK(mt44->onset_time.unix_time == week_start + c.offset_s);
        CHECK(mt44->onset_time.hour == c.hour);
        CHECK(mt44->onset_time.minute == c.minute);
    }
}

TEST_CASE("Time: DCX onset_time NOT resolved with report_unix=0") {
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
    bool ok = dec.decode(frame, msg, 0);
    REQUIRE(ok);

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->onset_time.unix_time == 0);
}
#endif

// 実データ EEW と Hypocenter の event_time 検証

#if (AZARAC_ENABLE_EEW)
TEST_CASE("Time: EEW event_time resolved with real report_unix") {
    Message msg{};
    const char* nmea = "$QZQSM,57,9AAC8884E3009324000009C60539619DC0000100000000010000001065F294C*08";
    REQUIRE(decodeNmea(nmea, msg, 1704067200u));  // 2024-01-01 00:00:00 UTC
    CHECK(msg.msg_type == 43);

    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    CHECK(mt43->disaster_category == 1);

    CHECK(mt43->event_time.unix_time != 0);
}
#endif // AZARAC_ENABLE_EEW
