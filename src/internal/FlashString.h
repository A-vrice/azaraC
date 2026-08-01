#pragma once
// azaraC - src/internal/FlashString.h
// Definition-table string access with AVR PROGMEM support.
//
// On AVR (Harvard architecture), generated definition tables place label
// strings in Flash (PROGMEM). std::string_view cannot address Flash,
// so lookups copy the string into a shared RAM buffer and return a
// view/pointer into it. The returned value is valid only until the NEXT
// definition lookup call.
//
// On non-AVR platforms these helpers are identity passthroughs
// (data already in .rodata).
//
// AVR address-space limitation: string pools use 16-bit Flash offsets.
// On ATmega2560 (256 KB Flash) a pool may be placed above 64 KB by the
// linker. If you encounter garbled labels, disable large categories
// (DCX, EX1) for that board. ATmega328P (Uno, 32 KB) is always safe.

#include "../azaraC_config.h"
#if defined(__AVR__)
#include "avr_std/cstddef"
#else
#include <cstddef>
#endif
#if defined(__AVR__)
#include "avr_std/string_view"
#else
#include <string_view>
#endif

#ifndef AZARAC_FLASH_BUF_SIZE
// Largest generated label is 769 bytes (D20 ash-fall description).
#define AZARAC_FLASH_BUF_SIZE 800
#endif

namespace azaraC {
namespace def {

#ifdef __AVR__
#include <avr/pgmspace.h>
inline std::string_view azarac_pgm_view(const char* src, size_t n) {
    static char buf[AZARAC_FLASH_BUF_SIZE];
    if (n >= AZARAC_FLASH_BUF_SIZE) n = AZARAC_FLASH_BUF_SIZE - 1;
    memcpy_P(buf, src, n);
    buf[n] = '\0';
    return std::string_view(buf, n);
}
inline const char* azarac_pgm_copy(const char* src) {
    static char buf[AZARAC_FLASH_BUF_SIZE];
    strncpy_P(buf, src, AZARAC_FLASH_BUF_SIZE - 1);
    buf[AZARAC_FLASH_BUF_SIZE - 1] = '\0';
    return buf;
}
#else
inline std::string_view azarac_pgm_view(const char* src, size_t n) {
    return std::string_view(src, n);
}
inline const char* azarac_pgm_copy(const char* src) { return src; }
#endif

}  // namespace def
}  // namespace azaraC
