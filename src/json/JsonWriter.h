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
        wf_s(out, key, AZARAC_LOOKUP_LANG(func_ja, func_en, id), /*last=*/false); \
        wf_s(out, key "_en", func_en(id), /*last=*/last); \
    } while (0)
#else
#define AZARAC_LABEL(out, key, func_ja, func_en, id, last) \
    wf_s(out, key, AZARAC_LOOKUP_LANG(func_ja, func_en, id), /*last=*/last)
#endif

namespace azaraC {
namespace internal {

// Primitive writers
void writeChar(Print& out, char c);
void writeUint32(Print& out, uint32_t v);
void writeUint64(Print& out, uint64_t v);
void writeStr(Print& out, std::string_view s);
void writeOptStr(Print& out, std::optional<std::string_view> s);
void writeHex(Print& out, uint8_t v);

// key: "foo":
void wk(Print& out, std::string_view k);

// "key":value,
void wf_u(Print& out, std::string_view k, uint32_t v, bool last = false);
void wf_u64(Print& out, std::string_view k, uint64_t v, bool last = false);
void wf_x(Print& out, std::string_view k, uint32_t v, bool last = false);
// "key":<v/denominator>。小数部は denominator の桁数ぶんゼロ埋め（1000000 → 6 桁）。
// 丸めは行わない（v は denominator の倍数で来る前提）。整数演算のみで組み立てるのは、 AVR の double が 24 bit 仮数（≈7.2 桁）で 6 桁精度の角度が host と一致しないため。
void wf_deg(Print& out, std::string_view k, int32_t denominator, int32_t v, bool last = false);
void wf_s(Print& out, std::string_view k, std::optional<std::string_view> v, bool last = false);
void wf_s(Print& out, std::string_view k, const char* v, bool last = false);
// "field":value,"field_label":label|null   (field は文字列リテラルに限る)
void wf_v(Print& out, std::string_view field, uint32_t value,
          std::optional<std::string_view> label, bool last = false);

// Helpers for repeated structures

void writeDHM(Print& out, std::string_view key, const TimeFields& t, bool last = false);

void writeLatLon(Print& out, std::string_view key, const LatLon& ll, bool last = false);

} // namespace internal

// Shared key string constants
namespace keys {

// Top-level message keys
inline constexpr const char* note       = "note";
inline constexpr const char* code       = "code";
inline constexpr const char* label      = "label";
inline constexpr const char* region     = "region";
inline constexpr const char* region_label = "region_label";

} // namespace keys
} // namespace azaraC
