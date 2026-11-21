#include "doctest.h"
#include "Parser.h"
#include "internal/Dedup.h"

namespace azaraC {
struct ParserClockTestAccess {
    static uint64_t observe(Parser& p, uint64_t now) { return p.observeClock(now); }
    static bool seen(Parser& p, uint32_t now, uint32_t window) {
        return p._dedup.isDuplicate(internal::dedupEventKey(0x1234u), now, window);
    }
};
} // namespace azaraC

using azaraC::Parser;
using Access = azaraC::ParserClockTestAccess;

TEST_CASE("Parser clock: small rollback is clamped and keeps history") {
    Parser parser;
    CHECK(Access::observe(parser, 10000) == 10000);
    CHECK_FALSE(Access::seen(parser, 10000, 60000));
    CHECK(Access::observe(parser, 9500) == 10000);
    CHECK(Access::seen(parser, 10000, 60000));
}

TEST_CASE("Parser clock: large rollback drops history") {
    Parser parser;
    Access::observe(parser, 100000);
    CHECK_FALSE(Access::seen(parser, 100000, 60000));
    CHECK(Access::observe(parser, 1000) == 1000);
    CHECK_FALSE(Access::seen(parser, 1000, 60000));
}

TEST_CASE("Parser clock: crossing a 2^32 ms generation drops history") {
    Parser parser;
    const uint64_t before = (1ULL << 32) - 10;
    Access::observe(parser, before);
    CHECK_FALSE(Access::seen(parser, static_cast<uint32_t>(before), 60000));
    const uint64_t after = (1ULL << 32) + 5;
    CHECK(Access::observe(parser, after) == after);
    CHECK_FALSE(Access::seen(parser, static_cast<uint32_t>(after), 60000));
}

TEST_CASE("Parser clock: an entry 2^32 ms old is not seen as recent") {
    Parser parser;
    Access::observe(parser, 1000);
    CHECK_FALSE(Access::seen(parser, 1000, 60000));
    const uint64_t later = (1ULL << 32) + 1000;
    Access::observe(parser, later);
    CHECK_FALSE(Access::seen(parser, static_cast<uint32_t>(later), 60000));
}
