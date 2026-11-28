#include "Parser.h"
#include "internal/TimeFields.h"
#include <cassert>
#include <cstdio>

namespace {
uint64_t now_ms = 0;
}

unsigned long millis() { return static_cast<uint32_t>(now_ms); }
int64_t esp_timer_get_time() { return static_cast<int64_t>(now_ms * 1000 + 999); }

namespace azaraC {
struct ParserClockTestAccess {
    static uint64_t last(const Parser& parser) { return parser._last_now_ms; }
    static bool seen(Parser& parser) {
        return parser._dedup.isDuplicate(internal::dedupEventKey(123),
            static_cast<uint32_t>(now_ms), 60000);
    }
#if AZARAC_ENABLE_NANKAI
    static void addPage(Parser& parser, const internal::NankaiPageKey& key) {
        const uint8_t text[18] = {'A'};
        parser._nankaiBuffers.addPage(key, 1, 2, text, now_ms);
    }
#endif
};
}

int main() {
    using Access = azaraC::ParserClockTestAccess;
    azaraC::Parser parser;
    now_ms = 0xFFFFFF00ULL;
    parser.updateClock();
    assert(Access::last(parser) == now_ms);
    assert(!Access::seen(parser));
    assert(Access::seen(parser));
#if AZARAC_ENABLE_NANKAI
    const azaraC::internal::NankaiPageKey key{12, 6, 15, 12, 30, 0, 2};
    Access::addPage(parser, key);
    assert(parser.getNankaiBuffer(key) != nullptr);
#endif
    now_ms = (1ULL << 32) + 0x100;
    parser.updateClock();
    assert(Access::last(parser) == now_ms);
    assert(!Access::seen(parser));
#if AZARAC_ENABLE_NANKAI
    assert(parser.getNankaiBuffer(key) == nullptr);
#endif
    parser.updateClock();
    assert(Access::seen(parser));
#if defined(ESP32) || defined(ARDUINO_ARCH_ESP32)
    now_ms += 2ULL << 32;
    parser.updateClock();
    assert(Access::last(parser) == now_ms);
    assert(!Access::seen(parser));
#endif
    std::puts("clock-idle: OK");
}
