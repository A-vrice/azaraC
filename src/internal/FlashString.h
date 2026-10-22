#pragma once
// 定義表の文字列アクセス（AVR の PROGMEM 対応）。
// AVR ではラベル文字列が Flash にあり std::string_view では指せないため、引き当て時に共有 RAM バッファへコピーする。返り値の view/ポインタは次の定義引き当て呼び出しまでのみ有効。
// 非 AVR: 素通し。
//
// AVR のアドレス: 64 KiB 超の Flash の品では表が 0xFFFF より上にリンクされ、16 bit の progmem ポインタでは届かない。そのためアドレスと読み出しは far アクセサ経由にする（それ未満では素の progmem ポインタ）。
// 行は {id, parent, offset} のまま — オフセットはプール内の 16 bit で、どれも 64 KiB より遥かに小さい。
// これにより表は Arduino コアの表と共有する低 Flash の progmem クラスタからも外れる（azaraC_config.h の AZARAC_PROGMEM）。

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

// プールは `azarac_pgm_ptr` で指す: far の品では Flash アドレス、それ以外では素の progmem ポインタ。
// 読み出しは下のアクセサでそのアドレスへの *オフセット* を指定し、配列のアドレスは AZARAC_PGM_PTR で取る — 素のポインタは far の品では切り詰められる。
#if FLASHEND > 0xFFFF
#if defined(AZARAC_AVR_STUB)
// ホスト検証ビルド: 「Flash アドレス」はホストのポインタで、ポインタと同じ幅（test/stub/avr/pgmspace.h）。
using azarac_pgm_ptr = uintptr_t;
#else
using azarac_pgm_ptr = uint32_t;     // 24 bit の Flash アドレス
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

// 共有 RAM バッファは 1 本: 800 B を 2 本持つと Uno の 2 KB SRAM を溢れる。次の引き当てまで有効。
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
// プールのエントリは NUL 区切りなので行に長さを持たない — 約 17,000 行で 1 行 1 バイトの節約。
// バッファサイズで上限を切り、壊れたプールでも末尾を越えて走査しない。
inline size_t azarac_pgm_len(azarac_pgm_ptr src) {
    size_t n = 0;
    while (n < AZARAC_FLASH_BUF_SIZE - 1 && azarac_read_byte(src, n) != '\0') ++n;
    return n;
}
inline std::string_view azarac_pgm_view_z(azarac_pgm_ptr src) {
    return azarac_pgm_view(src, azarac_pgm_len(src));
}
// 2 分割ラベル: 表が共有の地域名を 1 回だけ持ち、引き当て時に子と連結する（scripts/gen/strategy.py、factor_parents）。
// 両方とも Flash にあるので、連結に SRAM は要らない。
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
// 3 分割ラベル: 同じ考えを 1 段深くし、共有断片自体が繰り返す場合に使う（" City, Aichi Prefecture" を " City, " + "Aichi Prefecture" で表す）。
// コピーは同じバッファへの 1 回分のまま。
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
