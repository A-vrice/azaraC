// internal/TimeFields.h の Arduino 分岐の host 側チェック。
// -D__AVR__ でビルドし、SREG の退避・復帰経路を通す。スタブは
// test/stub_arduino が SREG、cli()/sei()、millis() を提供する。
#include "internal/TimeFields.h"

#include <cstdint>
#include <cstdio>

namespace {
unsigned long g_millis = 0;
bool g_millisSawInterrupts = false;
int failures = 0;
} // namespace

unsigned long millis() {
    // getMillis() はカウンタを読む前に割り込みをマスクしていなければならない。
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
    // 呼び出し前に割り込み禁止: getMillis() は禁止のまま返さなければならない。
    SREG = 0x00;
    g_millis = 1000;
    uint64_t a = azaraC::internal::getMillis();
    CHECK(SREG == 0x00);

    // 呼び出し前に割り込み許可: getMillis() は許可のまま返し、
    // millis() の読み出しは割り込みをマスクした後でなければならない。
    SREG = 0x80;
    g_millis = 2000;
    g_millisSawInterrupts = false;
    uint64_t b = azaraC::internal::getMillis();
    CHECK(!g_millisSawInterrupts);
    CHECK(SREG == 0x80);
    CHECK(b > a);

    // 復帰するのは I ビットだけでなく SREG 全体。I 以外のビットも残らなければならない。
    SREG = 0x81;
    g_millis = 2500;
    g_millisSawInterrupts = false;
    uint64_t c0 = azaraC::internal::getMillis();
    CHECK(!g_millisSawInterrupts);
    CHECK(SREG == 0x81);
    CHECK(c0 > b);

    // 32 ビット millis() の折り返しも、単調増加する 64 ビット値へ拡張される。
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
