#pragma once
// azaraC - src/json/JsonWriter.h
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

// Ensure language macros are defined before use
#include "../azaraC_config.h"

// ---------------------------------------------------------------------------
// Language resolution macro
// ---------------------------------------------------------------------------
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

namespace azaraC {
namespace internal {

// ---------------------------------------------------------------------------
// Primitive writers
// ---------------------------------------------------------------------------
void writeChar(Print& out, char c);
void writeUint32(Print& out, uint32_t v);
void writeUint64(Print& out, uint64_t v);
void writeDouble(Print& out, double v, int precision = 3);
void writeStr(Print& out, std::string_view s);
void writeOptStr(Print& out, std::optional<std::string_view> s);
void writeHex(Print& out, uint8_t v);

// key: "foo":
void wk(Print& out, std::string_view k);

// "key":value,
void wf_u(Print& out, std::string_view k, uint32_t v, bool last = false);
void wf_u64(Print& out, std::string_view k, uint64_t v, bool last = false);
void wf_x(Print& out, std::string_view k, uint32_t v, bool last = false);
void wf_d(Print& out, std::string_view k, double v, bool last = false, int precision = 3);
void wf_s(Print& out, std::string_view k, std::optional<std::string_view> v, bool last = false);
void wf_s(Print& out, std::string_view k, const char* v, bool last = false);

// ---------------------------------------------------------------------------
// Helpers for repeated structures
// ---------------------------------------------------------------------------

// Write a DHM TimeFields object as nested JSON
void writeDHM(Print& out, std::string_view key, const TimeFields& t, bool last = false);

void writeLatLon(Print& out, std::string_view key, const LatLon& ll, bool last = false);

// Write the 12-bit packed arrival time (day_offset:1, hour:5, min:6)
void writeArrivalTimeFields(Print& out, uint16_t raw);

} // namespace internal

// ---------------------------------------------------------------------------
// Shared key string constants (deduplicate across serializers)
// ---------------------------------------------------------------------------
namespace keys {

// Top-level message keys
inline constexpr const char* note       = "note";
inline constexpr const char* code       = "code";
inline constexpr const char* label      = "label";
inline constexpr const char* region     = "region";
inline constexpr const char* region_label = "region_label";

} // namespace keys
} // namespace azaraC
