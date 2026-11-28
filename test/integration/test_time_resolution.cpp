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

TEST_CASE("Time: resolveTime DHM picks the nearest day past the u32 epoch") {
    // report_unix = 0xFFFFFFFF = 2106-02-07 06:28:15 UTC。最寄りは翌日 2/8 00:00（u32 超過）で、前月 1/8 ではない。
    TimeFields t = TestDecoder::testResolveTime(0, 8, 0, 0, 0xFFFFFFFFu);
    CHECK(t.month == 2);
    CHECK(t.day == 8);
    CHECK(t.unix_time == 0);
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
    // 不正な day=32
    TimeFields t1 = TestDecoder::testResolveTime(0, 32, 0, 0, now);
    CHECK(t1.unix_time == 0);
    CHECK(t1.day == 0);

    // 不正な month=13
    TimeFields t2 = TestDecoder::testResolveTime(13, 1, 0, 0, now);
    CHECK(t2.unix_time == 0);
    CHECK(t2.day == 0);

    // 不正な hour=24
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

// u32 epoch 飽和（F5）: 2106 年超は unix_time だけ 0、暦フィールドは保持

TEST_CASE("Time: resolveTime saturates unix_time beyond u32 epoch") {
    TimeFields t = TestDecoder::testResolveTime(6, 15, 12, 30, 0xFFFFFFFFu - 3600u);
    CHECK(t.unix_time == 0);
    CHECK(t.month == 6);
    CHECK(t.day == 15);
    CHECK(t.hour == 12);
    CHECK(t.minute == 30);
}

TEST_CASE("Time: resolveArrivalTime saturates unix_time beyond u32 epoch") {
    TimeFields t = TestDecoder::testResolveArrivalTime(0x0800u, 0xFFFFFFFFu - 3600u);
    CHECK(t.unix_time == 0);
    CHECK(t.hour == 0);
    CHECK(t.minute == 0);
}

// 津波到着時刻解決 E2E テスト

#if (AZARAC_ENABLE_TSUNAMI)
TEST_CASE("Time: Tsunami arrival_time unix resolved with valid report_unix") {
    // report_unix = 2024-01-01 10:40:00 UTC
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
    REQUIRE(tsunami->count == 5);

    // 生の到着時刻 (2024-01-01) から独立に計算した UTC。
    CHECK(mt43->event_time.unix_time == 1704093720u);   // 07:22
    struct Arrival { uint16_t raw; uint32_t unix; };
    const Arrival expected[] = {
        {488u,  1704094800u},   // 07:40
        {498u,  1704095400u},   // 07:50
        {512u,  1704096000u},   // 08:00
        {512u,  1704096000u},   // 08:00
        {2047u, 0u},            // 到着済み/不明
    };
    for (uint8_t i = 0; i < tsunami->count; ++i) {
        INFO("tsunami entry ", i);
        CHECK(tsunami->entries[i].arrival_time_raw == expected[i].raw);
        CHECK(tsunami->entries[i].arrival_time.unix_time == expected[i].unix);
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
    // DCX a6=0（今週）、a7=2（月曜 00:01）。IS-QZSS-DCX-004 §4.2.3.6 Table 4.2-9（A6=0 は今週、A6=1 は翌週）/ §4.2.3.7 Table 4.2-10（週は月曜 00:00 UTC に始まる）/ EWSS CAMF v1.2 §3.3。report_unix = 2024-05-20 00:00:00 UTC (Monday = 週の起点)
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
    uint32_t report_unix = 1716163200u;   // 2024-05-20 00:00:00 UTC (Monday)
    bool ok = dec.decode(frame, msg, report_unix);
    REQUIRE(ok);

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->onset_time.unix_time != 0);
    CHECK(mt44->onset_time.unix_time == report_unix + 60);
    CHECK(mt44->onset_time.minute == 1);
    CHECK(mt44->onset_time.hour == 0);
}

TEST_CASE("Time: DCX onset_time saturates unix_time beyond u32 epoch") {
    // 上の解決テストと同じフレームで a6=1（翌週）にする。report_unix = 0xFFFFFFFF（2106-02-07 日曜）の翌週月曜 00:01 は u32 を超える。
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
    setBits(bits, 49, 1, 1);     // a6=1 → 翌週
    setBits(bits, 50, 14, 2);    // a7=2 → 翌週月曜 00:01 UTC
    setBits(bits, 214, 6, 1);
    setBits(bits, 226, 24, crc24qRef(bits, 226));

    Frame frame{};
    memcpy(frame.bits, bits, 32);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    REQUIRE(dec.decode(frame, msg, 0xFFFFFFFFu));

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->onset_time.unix_time == 0);
    CHECK(mt44->onset_time.hour == 0);
    CHECK(mt44->onset_time.minute == 1);
}

TEST_CASE("Time: DCX onset_time A7 boundary (16-bit overflow guard)") {
    // A7 は 1..10080（週頭からの分）。16 bit の unsigned int では (a7-1)*60 が 65535 を超えた時点で週内の別時刻へ折り返す（a7=1094 が最初の外れ値、a7=10080 が上限）。ここでは境界の意味（週頭 + (a7-1) 分）を固定する。
    struct Case { uint16_t a6, a7; uint32_t offset_s; uint8_t hour, minute; };
    const Case cases[] = {
        {0, 1094,  65580u, 18, 13},   // 16 bit で最初に折り返す値
        {1, 10080, 604740u, 23, 59},  // A7 の上限 = 翌週の日曜 23:59
    };

    // 2024-05-20 は月曜 00:00 UTC（週の起点）
    const uint32_t report_unix = 1716163200u;   // 2024-05-20 00:00:00 UTC (Monday)

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

    CHECK(mt43->event_time.unix_time == 1704092760u);   // 2024-01-01 07:06 UTC
}
#endif // AZARAC_ENABLE_EEW

// 暦に存在しない日付の未解決化（C4）。
// 仕様 Table 4.1.2-5 等の day 範囲は月別日数。2/30・4/31・平年 2/29 を黙って別月日へ
// 正規化せず、unix_time=0（生フィールド保持）に倒すことを固定する。

TEST_CASE("Time: MDHM calendar-invalid dates are unresolved (raw fields kept)") {
    const uint32_t base = daysFromCivil(2024, 2, 15) * 86400u;   // 閏年 2 月
    struct Case { uint8_t month, day; };
    const Case invalid[] = {{2, 30}, {4, 31}, {6, 31}, {9, 31}, {11, 31}};
    for (const Case& c : invalid) {
        CAPTURE(c.month);
        CAPTURE(c.day);
        TimeFields t = TestDecoder::testResolveTime(c.month, c.day, 12, 0, base);
        CHECK(t.unix_time == 0);
        CHECK(t.month == c.month);   // 生フィールドは保持
        CHECK(t.day == c.day);
        CHECK(t.hour == 12);
    }
    // 平年 2/29 も未解決（最寄り閏年へ飛ばさない）。
    const uint32_t common = daysFromCivil(2023, 2, 26) * 86400u;
    TimeFields t = TestDecoder::testResolveTime(2, 29, 0, 0, common);
    CHECK(t.unix_time == 0);
    CHECK(t.month == 2);
    CHECK(t.day == 29);
}

TEST_CASE("Time: MDHM leap 2/29 resolves, common 2/29 does not") {
    const uint32_t leap = daysFromCivil(2024, 2, 15) * 86400u;
    TimeFields t = TestDecoder::testResolveTime(2, 29, 0, 0, leap);
    CHECK(t.unix_time == daysFromCivil(2024, 2, 29) * 86400u);
    CHECK(t.month == 2);
    CHECK(t.day == 29);
}

TEST_CASE("Time: MDHM calendar-invalid across year boundary stays unresolved") {
    // 12 月基準で 2/30 → 旧実装は翌年 3/2 へ正規化していた（+76 日の未来）。未解決を固定。
    const uint32_t base = daysFromCivil(2024, 12, 15) * 86400u;
    TimeFields t = TestDecoder::testResolveTime(2, 30, 0, 0, base);
    CHECK(t.unix_time == 0);
    CHECK(t.month == 2);
    CHECK(t.day == 30);
}

TEST_CASE("Time: DHM stale never fabricates a future date (base Mar 1, day 31)") {
    // 旧実装は Feb 31 を 3/2 へ正規化して未来日付を返していた。直近の有効な過去（1/31）に落とす。
    const uint32_t base = daysFromCivil(2024, 3, 1) * 86400u;
    TimeFields t = TestDecoder::testResolveTime(0, 31, 0, 0, base);
    CHECK(t.unix_time != 0);
    CHECK(t.unix_time <= base);
    CHECK(t.unix_time == daysFromCivil(2024, 1, 31) * 86400u);
    CHECK(t.day == 31);
}

TEST_CASE("Time: resolveTime invariants sweep (no silent date change, no future beyond margin)") {
    // 実装の年解決ロジックを写さない独立不変条件:
    //  (1) 解決済みなら civil(unix/86400) の (月,日) が入力と一致（日が黙って化けない）。
    //  (2) どの年でも暦外の日付（2/30, 4/31, 6/31, 9/31, 11/31）は常に未解決。
    //  (3) DHM の解決済み unix は base+3日を超えない（未来クランプ）。
    //  (4) 範囲外入力は未解決。
    auto alwaysInvalid = [](uint8_t mo, uint8_t da) {
        if (mo == 2 && da >= 30) return true;
        if ((mo == 4 || mo == 6 || mo == 9 || mo == 11) && da == 31) return true;
        return false;
    };
    uint32_t checked = 0;
    for (uint32_t year = 2023; year <= 2025; ++year) {
        for (uint32_t mo = 1; mo <= 12; ++mo) {
            const uint32_t base = daysFromCivil(year, mo, 1) * 86400u + 12 * 3600u;
            for (uint8_t day = 1; day <= 31; ++day) {
                for (uint8_t month = 0; month <= 12; ++month) {
                    TimeFields t = TestDecoder::testResolveTime(month, day, 12, 0, base);
                    ++checked;
                    if (t.unix_time == 0) continue;
                    uint32_t ry, rm, rd;
                    TestDecoder::testCivilFromDays(t.unix_time / 86400u, ry, rm, rd);
                    CAPTURE(year); CAPTURE(mo); CAPTURE(month); CAPTURE(day);
                    CHECK(rd == day);                       // (1) 日は化けない
                    if (month != 0) CHECK(rm == month);     // (1) MDHM の月は化けない
                    else CHECK(t.unix_time <= base + 3u * 86400u);   // (3) DHM 未来クランプ
                    if (month != 0) CHECK(!alwaysInvalid(month, day));   // (2)
                }
            }
        }
    }
    CHECK(checked > 10000);   // 掃引が実行されたことの自己検証
    // (4) 範囲外
    const uint32_t base = daysFromCivil(2024, 6, 15) * 86400u;
    CHECK(TestDecoder::testResolveTime(0, 0, 12, 0, base).unix_time == 0);
    CHECK(TestDecoder::testResolveTime(0, 32, 12, 0, base).unix_time == 0);
    CHECK(TestDecoder::testResolveTime(13, 1, 12, 0, base).unix_time == 0);
    CHECK(TestDecoder::testResolveTime(1, 1, 24, 0, base).unix_time == 0);
    CHECK(TestDecoder::testResolveTime(1, 1, 12, 60, base).unix_time == 0);
}

TEST_CASE("Time: century leap year boundaries (2000 valid, 2100 invalid)") {
    // 2000 年は 400 の倍数 → 2/29 有効
    const uint32_t base2000 = daysFromCivil(2000, 2, 28) * 86400u;
    TimeFields t2000 = TestDecoder::testResolveTime(2, 29, 12, 0, base2000);
    CHECK(t2000.unix_time == daysFromCivil(2000, 2, 29) * 86400u + 12u * 3600u);

    // 2100 年は 100 の倍数かつ 400 の倍数でない → 2/29 は暦外で未解決
    const uint32_t base2100 = daysFromCivil(2100, 2, 28) * 86400u;
    TimeFields t2100 = TestDecoder::testResolveTime(2, 29, 12, 0, base2100);
    CHECK(t2100.unix_time == 0);
}

TEST_CASE("Time: MDHM diff == ±6 vs ±7 year wrap-around") {
    // base = 2024-06-15 (m=6): month=12 → diff = +6 (同年 2024)
    const uint32_t base6 = daysFromCivil(2024, 6, 15) * 86400u;
    CHECK(TestDecoder::testResolveTime(12, 1, 0, 0, base6).unix_time == daysFromCivil(2024, 12, 1) * 86400u);

    // base = 2024-05-15 (m=5): month=12 → diff = +7 > 6 (前年 2023)
    const uint32_t base5 = daysFromCivil(2024, 5, 15) * 86400u;
    CHECK(TestDecoder::testResolveTime(12, 1, 0, 0, base5).unix_time == daysFromCivil(2023, 12, 1) * 86400u);

    // base = 2024-07-15 (m=7): month=1 → diff = -6 (同年 2024)
    const uint32_t base7 = daysFromCivil(2024, 7, 15) * 86400u;
    CHECK(TestDecoder::testResolveTime(1, 1, 0, 0, base7).unix_time == daysFromCivil(2024, 1, 1) * 86400u);

    // base = 2024-08-15 (m=8): month=1 → diff = -7 < -6 (翌年 2025)
    const uint32_t base8 = daysFromCivil(2024, 8, 15) * 86400u;
    CHECK(TestDecoder::testResolveTime(1, 1, 0, 0, base8).unix_time == daysFromCivil(2025, 1, 1) * 86400u);
}

TEST_CASE("Time: DHM year wrap-around, MARGIN_SEC boundary, and 13-month lookback") {
    // Dec 31 23:00 + Jan 1 01:00 → 翌年 1 月 (cm >= 13)
    const uint32_t dec31 = daysFromCivil(2024, 12, 31) * 86400u + 23u * 3600u;
    TimeFields jan1 = TestDecoder::testResolveTime(0, 1, 1, 0, dec31);
    CHECK(jan1.month == 1);
    CHECK(jan1.unix_time == daysFromCivil(2025, 1, 1) * 86400u + 1u * 3600u);

    // Jan 1 01:00 + Dec 31 23:00 → 前年 12 月 (cm <= 0)
    const uint32_t jan1_base = daysFromCivil(2025, 1, 1) * 86400u + 1u * 3600u;
    TimeFields dec31_ev = TestDecoder::testResolveTime(0, 31, 23, 0, jan1_base);
    CHECK(dec31_ev.month == 12);
    CHECK(dec31_ev.unix_time == daysFromCivil(2024, 12, 31) * 86400u + 23u * 3600u);

    // MARGIN_SEC = 3 日ちょうど: 2024-06-10 12:30 基準で 6/13 12:30 はマージン内 (6月)、6/13 12:31 は超過で前月 (5月)
    const uint32_t june10 = daysFromCivil(2024, 6, 10) * 86400u + 12u * 3600u + 30u * 60u;
    TimeFields within = TestDecoder::testResolveTime(0, 13, 12, 30, june10);
    CHECK(within.month == 6);
    CHECK(within.unix_time == june10 + 3u * 86400u);

    TimeFields beyond = TestDecoder::testResolveTime(0, 13, 12, 31, june10);
    CHECK(beyond.month == 5);
    CHECK(beyond.unix_time == daysFromCivil(2024, 5, 13) * 86400u + 12u * 3600u + 31u * 60u);

    // 13 か月遡りループでの時刻比較 (ts64 <= base_unix と hour/minute の寄与)
    const uint32_t june20 = daysFromCivil(2024, 6, 20) * 86400u + 10u * 3600u + 15u * 60u;
    TimeFields past = TestDecoder::testResolveTime(0, 28, 14, 45, june20);
    CHECK(past.month == 5);
    CHECK(past.unix_time == daysFromCivil(2024, 5, 28) * 86400u + 14u * 3600u + 45u * 60u);
}

TEST_CASE("Time: resolveArrivalTime 23:59 valid and 2000-01-01 base_unix boundary") {
    // hour=23, min=59 は有効な上限値
    const uint16_t raw_2359 = static_cast<uint16_t>((0u << 11) | (23u << 6) | 59u);
    // base_unix == 946684800u (2000-01-01 00:00:00 UTC) ちょうどは有効扱い
    TimeFields t = TestDecoder::testResolveArrivalTime(raw_2359, 946684800u);
    CHECK(t.month == 1);
    CHECK(t.day == 1);
    CHECK(t.hour == 23);
    CHECK(t.minute == 59);
    CHECK(t.unix_time == 946684800u + 23u * 3600u + 59u * 60u);

    // base_unix == 946684799u は基準時刻無効 → month/day/unix_time は 0、hour/minute のみ保持
    TimeFields t_old = TestDecoder::testResolveArrivalTime(raw_2359, 946684799u);
    CHECK(t_old.month == 0);
    CHECK(t_old.day == 0);
    CHECK(t_old.hour == 23);
    CHECK(t_old.minute == 59);
    CHECK(t_old.unix_time == 0);

    // readNotifications: 3 件満杯
    uint8_t nb[32] = {};
    setBits(nb, 0, 9, 101);
    setBits(nb, 9, 9, 202);
    setBits(nb, 18, 9, 303);
    uint16_t notes[3] = {};
    CHECK(TestDecoder::testReadNotifications(nb, 0, notes) == 3);
    CHECK(notes[0] == 101);
    CHECK(notes[1] == 202);
    CHECK(notes[2] == 303);
}
