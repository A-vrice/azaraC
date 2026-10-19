#pragma once
// Minimal stand-in for the Arduino core's <Arduino.h>.
//
// autoresearch.sh builds the real library for the real AVR target (avr-gcc, ATmega2560) to measure flash bytes, but the Arduino core is a network download and cannot be part of a deterministic offline benchmark, so only the surface azaraC touches (millis and Print) is provided.
// Reached only with -DARDUINO=1, which makes azaraC.h include <Print.h> and take the Arduino branch of internal/TimeFields.h; not the library's own build path.

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
