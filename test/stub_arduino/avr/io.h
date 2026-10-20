#pragma once
// Host shim for the AVR status register and interrupt instructions.
// SREG and cli()/sei() model the I-bit closely enough to verify that
// internal::getMillis() saves and restores the caller's interrupt state.
#include <stdint.h>

inline uint8_t SREG = 0;
inline void cli() { SREG = 0; }
inline void sei() { SREG = 0x80; }
