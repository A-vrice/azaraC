#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>
#define PROGMEM
#define PGM_P const char*
inline void* memcpy_P(void* d, const void* s, std::size_t n) { return std::memcpy(d, s, n); }
inline char* strncpy_P(char* d, const char* s, std::size_t n) { return std::strncpy(d, s, n); }
inline char* strcpy_P(char* d, const char* s) { return std::strcpy(d, s); }
inline uint8_t  pgm_read_byte(const void* a)  { return *static_cast<const uint8_t*>(a); }
// Read via memcpy into a typed local: the source may be unaligned (PROGMEM
// pools are byte-packed), so dereferencing a cast pointer can trap on hosts
// with strict alignment (e.g. ARM).
inline uint16_t pgm_read_word(const void* a) {
    uint16_t v;
    std::memcpy(&v, a, sizeof(v));
    return v;
}
inline uint32_t pgm_read_dword(const void* a) {
    uint32_t v;
    std::memcpy(&v, a, sizeof(v));
    return v;
}
inline const void* pgm_read_ptr(const void* a) { return *static_cast<void* const*>(a); }
