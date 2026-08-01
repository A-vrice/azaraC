#pragma once
#include <cstdint>
#include <cstring>
#define PROGMEM
#define PGM_P const char*
inline void* memcpy_P(void* d, const void* s, size_t n) { return memcpy(d, s, n); }
inline char* strncpy_P(char* d, const char* s, size_t n) { return strncpy(d, s, n); }
inline char* strcpy_P(char* d, const char* s) { return strcpy(d, s); }
inline uint8_t  pgm_read_byte(const void* a)  { return *static_cast<const uint8_t*>(a); }
inline uint16_t pgm_read_word(const void* a)  { return *static_cast<const uint16_t*>(a); }
inline uint32_t pgm_read_dword(const void* a) { return *static_cast<const uint32_t*>(a); }
inline const void* pgm_read_ptr(const void* a) { return *static_cast<void* const*>(a); }
