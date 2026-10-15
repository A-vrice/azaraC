#pragma once
// Definition-table string access with AVR PROGMEM support.
// On AVR, label strings live in Flash; std::string_view cannot address it, so lookups copy into a shared RAM buffer. The returned view/pointer is valid only until the NEXT definition lookup call. Non-AVR: identity passthroughs.
//
// AVR address spaces: on a device with more than 64 KiB of Flash the tables are
// linked well above 0xFFFF, where a 16-bit progmem pointer cannot reach them, so
// addresses (and reads) go through the far accessors there; on smaller devices
// they are plain progmem pointers. Offsets stay 16-bit relative to a pool — each
// pool is far smaller than 64 KiB — so a row is still {id, parent, offset}.

#include "../azaraC_config.h"
#if defined(__AVR__)
#include "avr_std/cstddef"
#include "avr_std/cstdint"
#else
#include <cstddef>
#include <cstdint>
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
#if !defined(AZARAC_AVR_STUB)
#include <avr/io.h>          // FLASHEND
#endif

// A pool is addressed by `azarac_pgm_ptr`: a Flash address on devices that need
// more than 16 bits for it, a plain progmem pointer otherwise. Read the byte /
// word at an *offset into* such an address with the accessors below, and take an
// array's address with AZARAC_PGM_PTR — a bare pointer would be truncated on the
// far devices.
#if FLASHEND > 0xFFFF
#if defined(AZARAC_AVR_STUB)
// Host validation build: a "Flash address" is a host pointer there, so it is as
// wide as one (see test/stub/avr/pgmspace.h).
using azarac_pgm_ptr = uintptr_t;
#else
using azarac_pgm_ptr = uint32_t;     // a 24-bit Flash address
#endif
#define AZARAC_PGM_PTR(flash_array) (pgm_get_far_address(flash_array))
inline uint8_t azarac_read_byte(azarac_pgm_ptr p, size_t i) { return pgm_read_byte_far(p + i); }
inline uint16_t azarac_read_word(azarac_pgm_ptr p, size_t i) { return pgm_read_word_far(p + i); }
inline uint32_t azarac_read_dword(azarac_pgm_ptr p, size_t i) { return pgm_read_dword_far(p + i); }
inline void azarac_read_block(char* dst, azarac_pgm_ptr src, size_t n) { memcpy_PF(dst, src, n); }
inline void azarac_copy_string(char* dst, azarac_pgm_ptr src, size_t n) { strncpy_PF(dst, src, n); }
#else
using azarac_pgm_ptr = const char*;
#define AZARAC_PGM_PTR(flash_array) (reinterpret_cast<azarac_pgm_ptr>(flash_array))
inline uint8_t azarac_read_byte(azarac_pgm_ptr p, size_t i) { return pgm_read_byte(p + i); }
inline uint16_t azarac_read_word(azarac_pgm_ptr p, size_t i) { return pgm_read_word(p + i); }
inline uint32_t azarac_read_dword(azarac_pgm_ptr p, size_t i) { return pgm_read_dword(p + i); }
inline void azarac_read_block(char* dst, azarac_pgm_ptr src, size_t n) { memcpy_P(dst, src, n); }
inline void azarac_copy_string(char* dst, azarac_pgm_ptr src, size_t n) { strncpy_P(dst, src, n); }
#endif

// Single shared RAM buffer: two static buffers (800 B each) would overflow the Uno's 2 KB SRAM. Valid until the next definition lookup call.
inline char* azarac_flash_buf() {
    static char buf[AZARAC_FLASH_BUF_SIZE];
    return buf;
}
inline std::string_view azarac_pgm_view(azarac_pgm_ptr src, size_t n) {
    char* buf = azarac_flash_buf();
    if (n >= AZARAC_FLASH_BUF_SIZE) n = AZARAC_FLASH_BUF_SIZE - 1;
    azarac_read_block(buf, src, n);
    buf[n] = '\0';
    return std::string_view(buf, n);
}
// Length of a pool entry: the pools are NUL-separated, so a table does not have
// to store the length in its row — one byte saved per row across ~17,000 rows.
// Bounded by the buffer size so a malformed pool cannot walk off the end.
inline size_t azarac_pgm_len(azarac_pgm_ptr src) {
    size_t n = 0;
    while (n < AZARAC_FLASH_BUF_SIZE - 1 && azarac_read_byte(src, n) != '\0') ++n;
    return n;
}
inline std::string_view azarac_pgm_view_z(azarac_pgm_ptr src) {
    return azarac_pgm_view(src, azarac_pgm_len(src));
}
// Two-part labels: a generated table may store a shared region name once and
// join it to the child at lookup time (see scripts/gen/strategy.py,
// factor_parents). Both halves live in Flash, so the join lands in the same
// shared RAM buffer — the two-copy form costs no extra SRAM.
inline size_t azarac_pgm_append(char* buf, size_t at, azarac_pgm_ptr src) {
    size_t n = azarac_pgm_len(src);
    if (n > AZARAC_FLASH_BUF_SIZE - 1 - at) n = AZARAC_FLASH_BUF_SIZE - 1 - at;
    azarac_read_block(buf + at, src, n);
    return at + n;
}
inline std::string_view azarac_pgm_join_z(azarac_pgm_ptr a, azarac_pgm_ptr b) {
    char* buf = azarac_flash_buf();
    size_t n = azarac_pgm_append(buf, 0, a);
    n = azarac_pgm_append(buf, n, b);
    buf[n] = '\0';
    return std::string_view(buf, n);
}
// Three-part labels: the same idea one level deeper — a shared fragment may
// itself repeat (" City, Aichi Prefecture" over " City, " + "Aichi
// Prefecture"). Still one copy into the same buffer.
inline std::string_view azarac_pgm_join3(azarac_pgm_ptr a, azarac_pgm_ptr b, azarac_pgm_ptr c) {
    char* buf = azarac_flash_buf();
    size_t n = azarac_pgm_append(buf, 0, a);
    n = azarac_pgm_append(buf, n, b);
    n = azarac_pgm_append(buf, n, c);
    buf[n] = '\0';
    return std::string_view(buf, n);
}
inline const char* azarac_pgm_copy(azarac_pgm_ptr src) {
    char* buf = azarac_flash_buf();
    azarac_copy_string(buf, src, AZARAC_FLASH_BUF_SIZE - 1);
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
