#include "azaraC.h"
#include <cassert>
#include <cstdio>

namespace {
void setBits(uint8_t* bits, unsigned start, unsigned len, uint32_t value) {
    for (unsigned i = 0; i < len; ++i) {
        const unsigned bit = start + i;
        if ((value >> (len - i - 1)) & 1u) bits[bit / 8] |= static_cast<uint8_t>(0x80u >> (bit % 8));
    }
}

class FixedFramer : public azaraC::internal::IFramer {
public:
    azaraC::internal::Frame frame{};
    bool feed(uint8_t, azaraC::internal::Frame& out) override { out = frame; return true; }
    void reset() override {}
};
}

int main() {
    using namespace azaraC;
#if AZARAC_ENABLE_DEDUP
    static_assert(sizeof(internal::DedupFilter) == AZARAC_DEDUP_SLOTS * 8);
#else
    static_assert(sizeof(internal::DedupFilter) == 1);
#endif
    internal::DedupFilter filter;
    const auto key = internal::dedupEventKey(123);
    const bool firstDuplicate = filter.isDuplicate(key, 1000, 100);
    assert(!firstDuplicate);
    const bool repeatedDuplicate = filter.isDuplicate(key, 1000, 100);
    assert(repeatedDuplicate == bool(AZARAC_ENABLE_DEDUP));
    const bool expiredDuplicate = filter.isDuplicate(key, 1200, 100);
    assert(!expiredDuplicate);
    filter.reset();
    const bool resetDuplicate = filter.isDuplicate(key, 1200, 100);
    assert(!resetDuplicate);
    FixedFramer framer;
    uint8_t* bits = framer.frame.bits;
    framer.frame.svid = 186;
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 2);
    setBits(bits, 17, 4, 3);
    setBits(bits, 214, 6, 1);
    setBits(bits, 226, 24, crc24q(bits, 226));
    Parser parser(framer);
    Message msg;
    const bool emptyAccepted = parser.feed(nullptr, 0, msg);
    assert(!emptyAccepted);
    assert(!msg.valid);
    const bool firstAccepted = parser.feed(uint8_t(0), msg);
    assert(firstAccepted);
    assert(msg.valid);
    const bool repeatedAccepted = parser.feed(uint8_t(0), msg);
    assert(repeatedAccepted == !bool(AZARAC_ENABLE_DEDUP));
    assert(msg.valid == !bool(AZARAC_ENABLE_DEDUP));
    parser.reset();
    const bool resetAccepted = parser.feed(uint8_t(0), msg);
    assert(resetAccepted);
    bits[10] ^= 1;
    const bool corruptedAccepted = parser.feed(uint8_t(0), msg);
    assert(!corruptedAccepted);
    assert(!msg.valid);
    std::printf("dedup-policy: OK (enabled=%d)\n", AZARAC_ENABLE_DEDUP);
}
