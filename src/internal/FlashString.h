#pragma once
// 定義表の文字列アクセス（AVR の PROGMEM 対応）。
// AVR ではラベル文字列が Flash にあり std::string_view では指せないため、引き当て時に共有 RAM バッファへコピーする。
// 返り値の view/ポインタは次の定義引き当て呼び出しまでのみ有効。非 AVR: view 系は素通し、join 系は同じ共有バッファへ連結する。
// バッファは全呼び出しで共有するため、スレッド/タスク間で同時に引き当てないこと（呼び出し側で排他する）。
//
// AVR のアドレス: 64 KiB 超の Flash の品では表が 0xFFFF より上にリンクされ、16 bit の progmem ポインタでは届かない。
// そのためアドレスと読み出しは far アクセサ経由にする（それ未満では素の progmem ポインタ）。
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
// 生成される最長ラベルは 769 B（D20 降灰:description）
#define AZARAC_FLASH_BUF_SIZE 800
#endif

// 下限: 最小 preset（SEISMIC/TSUNAMI）の最長ラベル 45 B + NUL を収める 64 B。
// これ未満は定義ラベルが構造的に切れるため、警告ではなくビルド時に止める。
static_assert(AZARAC_FLASH_BUF_SIZE >= 64,
              "AZARAC_FLASH_BUF_SIZE must be >= 64: the longest SEISMIC/TSUNAMI label is 45 bytes");

namespace azaraC {
namespace def {

// 切り詰めが UTF-8 の途中に落ちたとき、不完全な末尾シーケンスを捨てる。
// ラベルは日本語（3 バイト）と英語（1 バイト）が混在するため、バイト境界で切ると JSON に不正な UTF-8 が出る。
// 末尾が完全なシーケンスなら n をそのまま返す（正常系では何もしない）。
inline size_t azarac_utf8_trim_len(const char* buf, size_t n) {
    size_t i = n;
    size_t back = 0;
    // 継続バイト（10xxxxxx）は最大 3 個。先頭バイトまで戻る。
    while (i > 0 && back < 3 && (static_cast<unsigned char>(buf[i - 1]) & 0xC0u) == 0x80u) {
        --i;
        ++back;
    }
    if (i == 0) return 0;
    const unsigned char lead = static_cast<unsigned char>(buf[i - 1]);
    size_t need;
    if ((lead & 0x80u) == 0x00u)      need = 1;
    else if ((lead & 0xE0u) == 0xC0u) need = 2;
    else if ((lead & 0xF0u) == 0xE0u) need = 3;
    else if ((lead & 0xF8u) == 0xF0u) need = 4;
    else return i - 1;                 // 不正な先頭バイトは落とす
    const size_t have = n - (i - 1);
    return (have >= need) ? n : (i - 1);
}

#ifdef __AVR__
#include <avr/pgmspace.h>
#if !defined(AZARAC_AVR_STUB)
#include <avr/io.h>          // FLASHEND
#endif

// プールは `azarac_pgm_ptr` で指す: far の品では Flash アドレス、それ以外では素の progmem ポインタ。
// 読み出しは下のアクセサでそのアドレスへの *オフセット* を指定し、配列のアドレスは AZARAC_PGM_PTR で取る（素のポインタは far の品では切り詰められる）。
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
// 非 AVR の join 系も同じ 1 本を使う（並行呼び出しは呼び出し側で排他する）。
inline char* azarac_flash_buf() {
    static char buf[AZARAC_FLASH_BUF_SIZE];
    return buf;
}
inline std::string_view azarac_pgm_view(azarac_pgm_ptr src, size_t n) {
    char* buf = azarac_flash_buf();
    if (n >= AZARAC_FLASH_BUF_SIZE) n = AZARAC_FLASH_BUF_SIZE - 1;
    azarac_read_block(buf, src, n);
    n = azarac_utf8_trim_len(buf, n);   // 切った位置が UTF-8 の途中なら戻す
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
    n = azarac_utf8_trim_len(buf, n);   // 連結後の打ち切りが UTF-8 の途中なら戻す
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
    n = azarac_utf8_trim_len(buf, n);   // 連結後の打ち切りが UTF-8 の途中なら戻す
    buf[n] = '\0';
    return std::string_view(buf, n);
}
inline const char* azarac_pgm_copy(azarac_pgm_ptr src) {
    char* buf = azarac_flash_buf();
    azarac_copy_string(buf, src, AZARAC_FLASH_BUF_SIZE - 1);
    buf[AZARAC_FLASH_BUF_SIZE - 1] = '\0';
    size_t n = 0;
    while (buf[n] != '\0') ++n;
    n = azarac_utf8_trim_len(buf, n);
    buf[n] = '\0';
    return buf;
}
#else
// 非 AVR: ラベルの実体は .rodata（Flash 側）に落ちる。
// 定義テーブルの生成コード (scripts/gen/gen_definitions.py) は AVR と同一テキストを両アーキテクチャへ出すため、AVR 側のアクセサ一式（byte offset 読み出し・NUL 区切りプール走査・共有バッファ連結）を同一署名で用意する。
// これで非 AVR も factor_parents による共有断片プールの恩恵を受け、フルラベル保持よりフラッシュが減る（local_government で ja 約 14KB / en 約 39KB、target_area_code で ja 約 15KB / en 約 42KB）。
// join 系のみ RAM バッファへ 1 回コピーし、切り詰めは AVR と同じ AZARAC_FLASH_BUF_SIZE に揃える。
// そのバッファも全呼び出しで共有する 1 本なので、並行して join しないこと。
// view 系はゼロコピーのまま。
using azarac_pgm_ptr = const char*;
#define AZARAC_PGM_PTR(flash_array) (reinterpret_cast<const char*>(flash_array))
inline uint8_t azarac_read_byte(azarac_pgm_ptr p, size_t i) { return static_cast<uint8_t>(p[i]); }
inline uint16_t azarac_read_word(azarac_pgm_ptr p, size_t i) {
    uint16_t v;
    __builtin_memcpy(&v, p + i, sizeof(v));
    return v;
}
inline uint32_t azarac_read_dword(azarac_pgm_ptr p, size_t i) {
    uint32_t v;
    __builtin_memcpy(&v, p + i, sizeof(v));
    return v;
}
inline void azarac_read_block(char* dst, azarac_pgm_ptr src, size_t n) { __builtin_memcpy(dst, src, n); }
inline void azarac_copy_string(char* dst, azarac_pgm_ptr src, size_t n) {
    size_t i = 0;
    while (i + 1 < n && src[i] != '\0') { dst[i] = src[i]; ++i; }
    dst[i] = '\0';
}
inline size_t azarac_pgm_len(azarac_pgm_ptr src) {
    size_t n = 0;
    while (n < AZARAC_FLASH_BUF_SIZE - 1 && src[n] != '\0') ++n;
    return n;
}
inline std::string_view azarac_pgm_view(azarac_pgm_ptr src, size_t n) {
    return std::string_view(src, n);
}
inline std::string_view azarac_pgm_view_z(azarac_pgm_ptr src) {
    const size_t n = azarac_pgm_len(src);
    return std::string_view(src, azarac_utf8_trim_len(src, n));
}
inline size_t azarac_pgm_append(char* buf, size_t at, azarac_pgm_ptr src) {
    size_t n = azarac_pgm_len(src);
    if (n > AZARAC_FLASH_BUF_SIZE - 1 - at) n = AZARAC_FLASH_BUF_SIZE - 1 - at;
    azarac_read_block(buf + at, src, n);
    return at + n;
}
inline char* azarac_flash_buf() {
    static char buf[AZARAC_FLASH_BUF_SIZE];
    return buf;
}
inline std::string_view azarac_pgm_join_z(azarac_pgm_ptr a, azarac_pgm_ptr b) {
    char* buf = azarac_flash_buf();
    size_t n = azarac_pgm_append(buf, 0, a);
    n = azarac_pgm_append(buf, n, b);
    n = azarac_utf8_trim_len(buf, n);   // 連結後の打ち切りが UTF-8 の途中なら戻す
    buf[n] = '\0';
    return std::string_view(buf, n);
}
inline std::string_view azarac_pgm_join3(azarac_pgm_ptr a, azarac_pgm_ptr b, azarac_pgm_ptr c) {
    char* buf = azarac_flash_buf();
    size_t n = azarac_pgm_append(buf, 0, a);
    n = azarac_pgm_append(buf, n, b);
    n = azarac_pgm_append(buf, n, c);
    n = azarac_utf8_trim_len(buf, n);   // 連結後の打ち切りが UTF-8 の途中なら戻す
    buf[n] = '\0';
    return std::string_view(buf, n);
}
inline const char* azarac_pgm_copy(azarac_pgm_ptr src) { return src; }
#endif

}  // namespace def
}  // namespace azaraC
