#pragma once
// Definition-table string access with AVR PROGMEM support.
// On AVR, label strings live in Flash; std::string_view cannot address it, so lookups copy into a shared RAM buffer. The returned view/pointer is valid only until the NEXT definition lookup call. Non-AVR: identity passthroughs.
//
// AVR address-space limitation: string pools use 16-bit Flash offsets, so a pool on ATmega2560 (256 KB) may land above 64 KB. If labels garble, disable large categories (DCX, EX1). ATmega328P (Uno, 32 KB) is always safe.

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
// Single shared RAM buffer: two static buffers (800 B each) would overflow the Uno's 2 KB SRAM. Valid until the next definition lookup call.
inline char* azarac_flash_buf() {
    static char buf[AZARAC_FLASH_BUF_SIZE];
    return buf;
}
inline std::string_view azarac_pgm_view(const char* src, size_t n) {
    char* buf = azarac_flash_buf();
    if (n >= AZARAC_FLASH_BUF_SIZE) n = AZARAC_FLASH_BUF_SIZE - 1;
    memcpy_P(buf, src, n);
    buf[n] = '\0';
    return std::string_view(buf, n);
}
// Length of a pool entry: the pools are NUL-separated, so a table does not have
// to store the length in its row — one byte saved per row across ~17,000 rows.
// Bounded by the buffer size so a malformed pool cannot walk off the end.
inline size_t azarac_pgm_len(const char* src) {
    size_t n = 0;
    while (n < AZARAC_FLASH_BUF_SIZE - 1 && pgm_read_byte(src + n) != '\0') ++n;
    return n;
}
inline std::string_view azarac_pgm_view_z(const char* src) {
    return azarac_pgm_view(src, azarac_pgm_len(src));
}
// Two-part labels: a generated table may store a shared region name once and
// join it to the child at lookup time (see scripts/gen/strategy.py,
// factor_parents). Both halves live in Flash, so the join lands in the same
// shared RAM buffer — the two-copy form costs no extra SRAM.
inline std::string_view azarac_pgm_join_z(const char* a, const char* b) {
    char* buf = azarac_flash_buf();
    size_t a_n = azarac_pgm_len(a);
    if (a_n > AZARAC_FLASH_BUF_SIZE - 1) a_n = AZARAC_FLASH_BUF_SIZE - 1;
    size_t b_n = azarac_pgm_len(b);
    if (b_n > AZARAC_FLASH_BUF_SIZE - 1 - a_n) b_n = AZARAC_FLASH_BUF_SIZE - 1 - a_n;
    memcpy_P(buf, a, a_n);
    memcpy_P(buf + a_n, b, b_n);
    buf[a_n + b_n] = '\0';
    return std::string_view(buf, a_n + b_n);
}
inline const char* azarac_pgm_copy(const char* src) {
    char* buf = azarac_flash_buf();
    strncpy_P(buf, src, AZARAC_FLASH_BUF_SIZE - 1);
    buf[AZARAC_FLASH_BUF_SIZE - 1] = '\0';
    return buf;
}
#else
inline std::string_view azarac_pgm_view(const char* src, size_t n) {
    return std::string_view(src, n);
}
inline size_t azarac_pgm_len(const char* src) {
    size_t n = 0;
    while (n < AZARAC_FLASH_BUF_SIZE - 1 && src[n] != '\0') ++n;
    return n;
}
inline const char* azarac_pgm_copy(const char* src) { return src; }
#endif

}  // namespace def
}  // namespace azaraC
