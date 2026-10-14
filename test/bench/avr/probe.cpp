// test/bench/avr/probe.cpp
// Flash-footprint probe for autoresearch.sh.
//
// Compiled together with the whole library for the real AVR target. It is the
// only thing that keeps the decode + serialize path (and therefore every
// definition table the serializers look up) reachable, which is what makes the
// linked image a meaningful "flash a sketch pays" number under --gc-sections.
//
// The body deliberately touches the public API only: Parser::feed + toJson.
// It is never executed, only linked.

#include "azaraC.h"

#include <stdlib.h>

// The Arduino core supplies the following (the AVR toolchain ships no C++
// runtime of its own); the shim only declares the types.

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
