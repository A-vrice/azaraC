// Parser の内部時刻を使う Nankai/dedup の回帰テスト。
// ParserTestHook は AZARAC_TESTING=1 のときだけ Parser の friend になる。

#include "doctest.h"
#include "test_helpers.h"

#if defined(AZARAC_TESTING) && AZARAC_TESTING && AZARAC_ENABLE_NANKAI
namespace azaraC {
namespace internal {
struct ParserTestHook {
    static bool postDecode(Parser& parser, const Message& decoded, Message& out,
                           uint32_t identity, uint64_t now_ms) {
        return parser.postDecodeAt(decoded, out, identity, now_ms);
    }
};
} // namespace internal
} // namespace azaraC

namespace {

using azaraC::Message;
using azaraC::Mt43Data;
using azaraC::NankaiData;
using azaraC::internal::ParserTestHook;

Message makeNankai(uint8_t info_code, uint8_t page, uint8_t total,
                   uint8_t report_classification, const char* text, uint8_t text_len,
                   uint8_t rt_month = 6, uint8_t rt_day = 15,
                   uint8_t rt_hour = 12, uint8_t rt_minute = 30,
                   uint8_t information_type = 0) {
    Message msg;
    msg.valid = true;
    msg.msg_type = 43;
    msg.initPayload<Mt43Data>();
    Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    mt43->disaster_category = 4;
    mt43->report_classification = report_classification;
    mt43->information_type = information_type;
    mt43->initAs<NankaiData>();

    NankaiData* nankai = mt43->getNankai();
    REQUIRE(nankai != nullptr);
    nankai->info_code = info_code;
    nankai->page = page;
    nankai->total_page = total;
    nankai->report_month = rt_month;
    nankai->report_day = rt_day;
    nankai->report_hour = rt_hour;
    nankai->report_minute = rt_minute;
    for (uint8_t i = 0; i < text_len && i < 18; ++i) {
        nankai->text[i] = static_cast<uint8_t>(text[i]);
    }
    return msg;
}

bool feedAt(azaraC::Parser& parser, const Message& decoded, Message& out,
            uint32_t identity, uint64_t now_ms) {
    return ParserTestHook::postDecode(parser, decoded, out, identity, now_ms);
}

} // namespace

TEST_CASE("Parser clock: partial Nankai duplicate does not reach dedup") {
    azaraC::Parser parser;
    Message out;
    const Message p1 = makeNankai(1, 1, 2, 2, "P1", 2);
    const Message p2 = makeNankai(1, 2, 2, 2, "P2", 2);

    CHECK_FALSE(feedAt(parser, p1, out, 0, 1000));
    CHECK_FALSE(feedAt(parser, p1, out, 0, 1001));  // 未完成の重複ページ
    CHECK(feedAt(parser, p2, out, 0, 1002));        // 完成通知は抑止されない
    REQUIRE(out.getMt43() != nullptr);
    const NankaiData* nankai = out.getMt43()->getNankai();
    REQUIRE(nankai != nullptr);
    REQUIRE(nankai->is_aggregated);
    CHECK(std::string(nankai->aggregated_text_ptr, nankai->aggregated_len) == "P1P2");
}

#if AZARAC_ENABLE_DEDUP
TEST_CASE("Parser clock: completed Nankai duplicate refreshes dedup history") {
    azaraC::Parser parser;
    Message out;
    // 取消の dedup 窓は2時間。バッファの60秒タイムアウト内に再送して履歴だけ更新し、
    // その後バッファを追い出してから窓の境界を超えて再完成させる。
    const Message event_a = makeNankai(1, 1, 1, 2, "A", 1, 6, 15, 12, 30, 2);
    const Message event_b = makeNankai(2, 1, 1, 2, "B", 1);
    const uint64_t t0 = 1000;
    const uint64_t cancel_window = 2ULL * 60 * 60 * 1000;

    CHECK(feedAt(parser, event_a, out, 0, t0));
    // 完成済みバッファへの再送。ここで dedup の last_seen を更新する。
    CHECK_FALSE(feedAt(parser, event_a, out, 0, t0 + 59000));
    // 別事象でバッファを追い出してから、事象Aをもう一度完成させる。
    CHECK(feedAt(parser, event_b, out, 0, t0 + 60000));
    CHECK_FALSE(feedAt(parser, event_a, out, 0, t0 + cancel_window + 1000));
}
#endif // AZARAC_ENABLE_DEDUP

#if !AZARAC_ENABLE_DEDUP
TEST_CASE("Parser clock: dedup off still suppresses completed Nankai pages") {
    azaraC::Parser parser;
    Message out;
    const Message event_a = makeNankai(3, 1, 1, 2, "A", 1);

    CHECK(feedAt(parser, event_a, out, 0, 1000));
    CHECK_FALSE(feedAt(parser, event_a, out, 0, 1001));
}
#endif

#if AZARAC_ENABLE_DEDUP
TEST_CASE("Parser clock: 2^32 gap resets stale dedup and Nankai state") {
    azaraC::Parser parser;
    Message out;
    const Message event_a = makeNankai(4, 1, 1, 2, "A", 1);
    const uint64_t t0 = 1000;

    CHECK(feedAt(parser, event_a, out, 0, t0));
    // 同じ事象を 2^32 ms 以上後に受信すると、古い履歴を捨てて再通知する。
    CHECK(feedAt(parser, event_a, out, 0, t0 + (1ULL << 32)));
}

TEST_CASE("Parser clock: normal 32-bit wrap keeps duplicate suppression") {
    azaraC::Parser parser;
    Message out;
    const Message event_a = makeNankai(5, 1, 1, 2, "A", 1);
    const uint64_t t0 = 0xFFFFFF00ULL;

    CHECK(feedAt(parser, event_a, out, 0, t0));
    CHECK_FALSE(feedAt(parser, event_a, out, 0, (1ULL << 32) + 0x100));
}
#endif // AZARAC_ENABLE_DEDUP
#endif // AZARAC_TESTING && AZARAC_ENABLE_NANKAI
