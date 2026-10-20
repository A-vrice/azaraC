// test/bench/avr/probe.cpp
// Flash-footprint probe for autoresearch.sh: linked, never executed.
//
// Built with the whole library for the real AVR target; it is what keeps the decode + serialize path (hence every definition table the serializers look up) reachable, so the linked image is a meaningful "flash a sketch pays" number under --gc-sections.
// The body touches the public API only (Parser::feed + toJson).
//
// Both ends are opaque on purpose:
//   - the input byte is volatile, so the compiler cannot fold feed() into "no frame yet" and drop the decode path;
//   - the sink's write() keeps the bytes it is handed alive (an empty asm with input operands), so the labels and the definition tables they come from stay in the image.
// A sink that swallowed everything would let LTO delete the serialize path and the tables it reads, and the flash number would stop meaning what a sketch pays.

#include "azaraC.h"

#include <stddef.h>
#include <stdlib.h>

// Supplied by the Arduino core: the AVR toolchain ships no C++ runtime of its own.

unsigned long millis(void) { return 0; }
void noInterrupts(void) {}
void interrupts(void) {}

void* operator new(size_t n) { return malloc(n); }
void* operator new[](size_t n) { return malloc(n); }
void operator delete(void* p) { free(p); }
void operator delete[](void* p) { free(p); }
void operator delete(void* p, size_t) { free(p); }
void operator delete[](void* p, size_t) { free(p); }

namespace {
// The sink. write() is the path the library uses for keys and labels (out.write(s.data(), s.size())),
// so overriding it is what ties the tables to the image. The asm keeps the pointer and the length
// live without storing anything: no SRAM is spent on a counter.
class ProbePrint : public Print {
public:
    size_t write(uint8_t) override {
        asm volatile("" : : "r"((uint8_t)0) : "memory");
        return 1;
    }
    size_t write(const char* s, size_t n) override {
        asm volatile("" : : "r"(s), "r"(n) : "memory");
        return n;
    }
};

ProbePrint g_out;
}  // namespace

int main() {
    azaraC::Parser parser;
    azaraC::Message msg;
    volatile uint8_t byte = 0x00;
    parser.feed(byte, msg);
    azaraC::toJson(msg, g_out);
    return 0;
}
