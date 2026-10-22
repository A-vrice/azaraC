#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>
#define PROGMEM
#define PGM_P const char*
// avr-libc の PSTR 相当。実機はリテラルを __progmem__ の static 配列にする statement expression だが、host では PROGMEM が空なのでリテラルそのままでよい。
#define PSTR(s) ((const char*)(s))
// Flash 64 KiB 超の品を模し、host ビルドで far アドレッシング経路（AZARAC_PGM_PTR / pgm_read_*_far）を通す。短い経路は uno のもので、実ツールチェーンがコンパイルする。
#ifndef FLASHEND
#define FLASHEND 0x3FFFFUL
#endif
inline void* memcpy_P(void* d, const void* s, std::size_t n) { return std::memcpy(d, s, n); }
inline char* strncpy_P(char* d, const char* s, std::size_t n) { return std::strncpy(d, s, n); }
inline char* strcpy_P(char* d, const char* s) { return std::strcpy(d, s); }
inline int strncmp_P(const char* a, const char* b, std::size_t n) { return std::strncmp(a, b, n); }
inline uint8_t  pgm_read_byte(const void* a)  { return *static_cast<const uint8_t*>(a); }
// 型付きローカルへ memcpy する: ソースは非アラインかもしれず（PROGMEM プールはバイト詰め）、
// キャストしたポインタの参照外しはアラインメントに厳しい host（例: ARM）でトラップし得る。
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

// far 版: host では Flash アドレスは単なるアドレスなのでキャストで足りる（avr-libc は RAMPZ をロードして lpm/memcpy_PF を使う）。
// アドレスは host の幅（uintptr_t）でなければならない: 32 ビットだと切り詰められる。
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
