#pragma once
// Minimal Arduino shim for the host-side ARDUINO>=1 / __AVR__ test of internal/TimeFields.h.
// Only the symbols that TimeFields.h needs are provided; see test/stub_arduino/avr/io.h.
#include <stdint.h>
#include <avr/io.h>

unsigned long millis();
