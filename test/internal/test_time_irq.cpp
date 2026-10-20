// Host-side check for the Arduino branch of internal/TimeFields.h.
// Built with -D__AVR__ so the SREG save/restore path is exercised; the stubs in
// test/stub_arduino provide SREG, cli()/sei() and millis().
#include "internal/TimeFields.h"

#include <cstdint>
#include <cstdio>

namespace {
unsigned long g_millis = 0;
bool g_millisSawInterrupts = false;
int failures = 0;
} // namespace

unsigned long millis() {
    // getMillis() must have masked interrupts before reading the counter.
    if (SREG & 0x80) g_millisSawInterrupts = true;
    return g_millis;
}

#define CHECK(cond)                                                            \
    do {                                                                       \
        if (!(cond)) {                                                         \
            std::fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond); \
            ++failures;                                                        \
        }                                                                      \
    } while (0)

int main() {
    // Interrupts disabled before the call: getMillis() must leave them disabled.
    SREG = 0x00;
    g_millis = 1000;
    uint64_t a = azaraC::internal::getMillis();
    CHECK(SREG == 0x00);

    // Interrupts enabled before the call: getMillis() must leave them enabled,
    // and must read millis() only after masking interrupts.
    SREG = 0x80;
    g_millis = 2000;
    g_millisSawInterrupts = false;
    uint64_t b = azaraC::internal::getMillis();
    CHECK(!g_millisSawInterrupts);
    CHECK(SREG == 0x80);
    CHECK(b > a);

    // The whole SREG byte is restored, not only the I-bit. Non-I bits must survive.
    SREG = 0x81;
    g_millis = 2500;
    g_millisSawInterrupts = false;
    uint64_t c0 = azaraC::internal::getMillis();
    CHECK(!g_millisSawInterrupts);
    CHECK(SREG == 0x81);
    CHECK(c0 > b);

    // 32-bit millis() wrap is still extended to a monotonically increasing 64-bit value.
    SREG = 0x80;
    g_millis = 0xFFFFFF00UL;
    uint64_t c = azaraC::internal::getMillis();
    g_millis = 0x00000100UL;
    uint64_t d = azaraC::internal::getMillis();
    CHECK(d > c);
    CHECK(SREG == 0x80);

    if (failures == 0) std::puts("time-irq: OK");
    return failures == 0 ? 0 : 1;
}
