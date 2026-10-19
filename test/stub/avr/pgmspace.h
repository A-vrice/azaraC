#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>
#define PROGMEM
#define PGM_P const char*
// avr-libc の PSTR 相当。実機はリテラルを __progmem__ の static 配列にする statement expression だが、host では PROGMEM が空なのでリテラルそのままでよい。
#define PSTR(s) ((const char*)(s))
// Stands in for a device with more than 64 KiB of Flash, so the host build exercises the far addressing path (AZARAC_PGM_PTR / pgm_read_*_far); the short path is the uno's and is compiled by the real toolchain.
#ifndef FLASHEND
#define FLASHEND 0x3FFFFUL
#endif
inline void* memcpy_P(void* d, const void* s, std::size_t n) { return std::memcpy(d, s, n); }
inline char* strncpy_P(char* d, const char* s, std::size_t n) { return std::strncpy(d, s, n); }
inline char* strcpy_P(char* d, const char* s) { return std::strcpy(d, s); }
inline uint8_t  pgm_read_byte(const void* a)  { return *static_cast<const uint8_t*>(a); }
// memcpy into a typed local: the source may be unaligned (PROGMEM pools are byte-packed), and dereferencing a cast pointer can trap on hosts with strict alignment (e.g.
// ARM).
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

// Far variants: on a host a Flash address is just an address, so a cast suffices (avr-libc loads RAMPZ and uses lpm/memcpy_PF).
// Addresses must be host-wide (uintptr_t): a 32-bit one would truncate.
#define pgm_get_far_address(flash_array) \
    (static_cast<uintptr_t>(reinterpret_cast<uintptr_t>(&(flash_array))))
inline uint8_t  pgm_read_byte_far(uintptr_t a)  { return *reinterpret_cast<const uint8_t*>(a); }
inline uint16_t pgm_read_word_far(uintptr_t a) {
    uint16_t v;
    std::memcpy(&v, reinterpret_cast<const void*>(a), sizeof(v));
    return v;
}
inline uint32_t pgm_read_dword_far(uintptr_t a) {
    uint32_t v;
    std::memcpy(&v, reinterpret_cast<const void*>(a), sizeof(v));
    return v;
}
inline void* memcpy_PF(void* d, uintptr_t s, std::size_t n) {
    return std::memcpy(d, reinterpret_cast<const void*>(s), n);
}
inline char* strncpy_PF(char* d, uintptr_t s, std::size_t n) {
    return std::strncpy(d, reinterpret_cast<const char*>(s), n);
}
