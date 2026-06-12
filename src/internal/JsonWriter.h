#pragma once
// azaraC - src/internal/JsonWriter.h
// Common JSON writer helpers for serializers

#include "../Message.h"
#include <optional>
#include <string_view>

#if defined(ARDUINO) && ARDUINO >= 1
#  include <Print.h>
#else
#  include "PrintShim.h"
#endif

// ---------------------------------------------------------------------------
// Language resolution macro
// ---------------------------------------------------------------------------
#if AZARAC_LANG_JA && AZARAC_LANG_EN
#define AZARAC_LOOKUP_LANG(func_ja, func_en, id) \
    ([&]() { \
        if (auto result = func_ja(id); result.has_value()) return result; \
        return func_en(id); \
    }())
#elif AZARAC_LANG_JA
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
void wf_d(Print& out, std::string_view k, double v, bool last = false);
void wf_s(Print& out, std::string_view k, std::optional<std::string_view> v, bool last = false);

// ---------------------------------------------------------------------------
// Helpers for repeated structures
// ---------------------------------------------------------------------------

// Write a DHM TimeFields object as nested JSON
void writeDHM(Print& out, std::string_view key, const TimeFields& t, bool last = false);

void writeLatLon(Print& out, std::string_view key, const LatLon& ll, bool last = false);

// Write the 12-bit packed arrival time (day_offset:1, hour:5, min:6)
void writeArrivalTimeFields(Print& out, uint16_t raw);

} // namespace internal
} // namespace azaraC
