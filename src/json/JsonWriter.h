#pragma once
// Common JSON writer helpers for serializers

#include "../Message.h"
#if defined(__AVR__)
#include "../internal/avr_std/optional"
#else
#include <optional>
#endif
#if defined(__AVR__)
#include "../internal/avr_std/string_view"
#else
#include <string_view>
#endif

#if defined(ARDUINO) && ARDUINO >= 1
#  include <Print.h>
#else
#  include "../internal/PrintShim.h"
#endif

// AZARAC_LANG_JA/EN を参照前に確定させる
#include "../azaraC_config.h"

// Language resolution macro
#if AZARAC_LANG_JA && AZARAC_LANG_EN
#define AZARAC_LOOKUP_LANG(func_ja, func_en, id) \
    ([&]() { \
        if (auto result = func_ja(id); result) return result; \
        return func_en(id); \
    }())
#elif AZARAC_LANG_JA
#define AZARAC_LOOKUP_LANG(func_ja, func_en, id) func_ja(id)
#elif AZARAC_LANG_EN
#define AZARAC_LOOKUP_LANG(func_ja, func_en, id) func_en(id)
#else
#define AZARAC_LOOKUP_LANG(func_ja, func_en, id) std::nullopt
#endif

// ラベル 1 本に加え、両言語 ON のときだけ key "_en" を併記する（key は文字列リテラルに限る）。
// 値は必ず AZARAC_LOOKUP_LANG 経由で引く: func_ja を直に呼ぶと AZARAC_LANG_JA=0 のビルドで JA テーブルがコンパイル除外され、 _label が空文字列になって EN の内容が失われる。
#if AZARAC_LANG_JA && AZARAC_LANG_EN
#define AZARAC_LABEL(out, key, func_ja, func_en, id, last) \
    do { \
        wf_s(out, AZARAC_KEY(key), AZARAC_LOOKUP_LANG(func_ja, func_en, id), /*last=*/false); \
        wf_s(out, AZARAC_KEY(key "_en"), func_en(id), /*last=*/last); \
    } while (0)
#else
#define AZARAC_LABEL(out, key, func_ja, func_en, id, last) \
    wf_s(out, AZARAC_KEY(key), AZARAC_LOOKUP_LANG(func_ja, func_en, id), /*last=*/last)
#endif

namespace azaraC {
namespace internal {

// JSON のキー。キーは必ず文字列リテラルなので、AVR では Flash に置く（AZARAC_KEY が PSTR を通す）。値を固定リテラルで出すときも同じ型を使う（`AZARAC_KEY("invalid_mt43")`）。
// 素のリテラルは .rodata に入り、avr-libc のリンカスクリプトがそれを .data（SRAM）へ含めるため、そのまま SRAM を食う（実測: Uno プリセットの .data は 564 B → 88 B、ATmega2560 + DCX/CAMF の .data は 2,902 B → 250 B。いずれも 16進表をやめた分を含む）。
// 長さは sizeof でコンパイル時に決まる（ランタイムの走査も切り詰めも無い）。生の const char* からは暗黙変換できない: 包み忘れはホスト（RAM）では正しく動いて AVR だけ文字化けするので、コンパイルエラーにする。
struct JsonKey {
    const char* p;
    uint8_t     len;
};

// キー／値の 1 次コピー先の長さ。最長はキーの 35 B（a17_type_of_specific_settings_label）、値は 20 B（unsupported_category）。
#ifndef AZARAC_KEY_BUF_SIZE
#define AZARAC_KEY_BUF_SIZE 40
#endif

template <size_t N>
constexpr JsonKey makeKey(const char* literal) {
    static_assert(N > 1 && N - 1 < AZARAC_KEY_BUF_SIZE,
                  "JSON string (key or value) does not fit AZARAC_KEY_BUF_SIZE");
    return JsonKey{literal, static_cast<uint8_t>(N - 1)};
}

#if defined(__AVR__)
// PSTR: リテラルをその場で __progmem__ の static 配列にする (avr-libc)。LTO でも Flash に残る。
#define AZARAC_KEY(s) (::azaraC::internal::makeKey<sizeof(s)>(PSTR(s)))
#else
#define AZARAC_KEY(s) (::azaraC::internal::makeKey<sizeof(s)>(s))
#endif

// ニブル → 16進1文字。表を持たない: 16 エントリの表は `.rodata`（avr-libc のリンカスクリプトでは `.data` = SRAM、または属性を付けても Flash に 17B）を食うだけで、この計算は数命令に畳まれる。
inline char hexDigit(uint8_t nibble) {
    const uint8_t n = static_cast<uint8_t>(nibble & 0x0F);
    return static_cast<char>(n < 10 ? ('0' + n) : ('A' + (n - 10)));
}

// Primitive writers
void writeChar(Print& out, char c);
void writeUint32(Print& out, uint32_t v);
void writeUint64(Print& out, uint64_t v);
void writeStr(Print& out, std::string_view s);
void writeOptStr(Print& out, std::optional<std::string_view> s);
void writeHex(Print& out, uint8_t v);

// key: "foo":
void wk(Print& out, JsonKey k);

// "key":value,
void wf_u(Print& out, JsonKey k, uint32_t v, bool last = false);
void wf_u64(Print& out, JsonKey k, uint64_t v, bool last = false);
void wf_x(Print& out, JsonKey k, uint32_t v, bool last = false);
// "key":<v/denominator>。小数部は denominator の桁数ぶんゼロ埋め（1000000 → 6 桁）。
// 丸めは行わない（v は denominator の倍数で来る前提）。整数演算のみで組み立てるのは、 AVR の double が 24 bit 仮数（≈7.2 桁）で 6 桁精度の角度が host と一致しないため。
void wf_deg(Print& out, JsonKey k, int32_t denominator, int32_t v, bool last = false);
void wf_s(Print& out, JsonKey k, std::optional<std::string_view> v, bool last = false);
void wf_s(Print& out, JsonKey k, const char* v, bool last = false);
// "key":"value"。値も固定リテラルなら AZARAC_KEY で包む（SRAM に置かない）。
// AVR では k と v が同じ 1 次コピー先を共有するので、キーを書き終えてから値の keyView を取る（この順序が契約）。
void wf_s(Print& out, JsonKey k, JsonKey v, bool last = false);
// "field":value,"field_label":label|null
void wf_v(Print& out, JsonKey field, uint32_t value,
          std::optional<std::string_view> label, bool last = false);

// Helpers for repeated structures

void writeDHM(Print& out, JsonKey key, const TimeFields& t, bool last = false);

void writeLatLon(Print& out, JsonKey key, const LatLon& ll, bool last = false);

} // namespace internal
} // namespace azaraC
