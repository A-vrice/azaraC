// test/bench/avr/probe.cpp
// Flash-footprint probe for autoresearch.sh: linked, never executed.
//
// Built with the whole library for the real AVR target; it is what keeps the decode + serialize path (hence every definition table the serializers look up) reachable, so the linked image is a meaningful "flash a sketch pays" number under --gc-sections.
// The body touches the public API only (Parser::feed + toJson).

#include "azaraC.h"

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
Print g_out;
}  // namespace

int main() {
    azaraC::Parser parser;
    azaraC::Message msg;
    parser.feed(0x00, msg);
    azaraC::toJson(msg, g_out);
    return 0;
}
