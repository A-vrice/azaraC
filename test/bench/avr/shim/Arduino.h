#pragma once
// Minimal stand-in for the Arduino core's <Arduino.h>.
//
// benchmarks/autoresearch.sh builds the real library for the real AVR target
// (avr-gcc, ATmega2560) to measure flash bytes. The Arduino core itself is a
// network download, so it cannot be part of a deterministic offline benchmark.
// Only the surface azaraC touches is provided here: millis() and Print.
//
// This header is NOT part of the library build path; it is reached only because
// the probe compiles with -DARDUINO=1, which is what makes azaraC.h include
// <Print.h> and pick up the Arduino branch of internal/TimeFields.h.

#include <stddef.h>
#include <stdint.h>

#include "internal/avr_std/string_view"

unsigned long millis(void);
void noInterrupts(void);
void interrupts(void);

class Print {
public:
    virtual ~Print() = default;

    virtual size_t write(uint8_t) { return 1; }
    virtual size_t write(const char*, size_t n) { return n; }

    void print(char) {}
    void print(const char*) {}
    void print(const void*) {}
    void print(std::string_view) {}
    void print(int) {}
    void print(unsigned int) {}

    void println() {}
    void println(const char*) {}
    void println(std::string_view) {}
};
