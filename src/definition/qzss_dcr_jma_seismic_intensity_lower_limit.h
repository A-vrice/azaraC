#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_seismic_intensity_lower_limit
// Variable      : qzss_dcr_jma_seismic_intensity_lower_limit
// Entries       : 12
// Strategy      : binary_search

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#if defined(__AVR__)
#include "../internal/avr_std/cstdint"
#include "../internal/avr_std/optional"
#include "../internal/avr_std/string_view"
#else
#include <cstdint>
#include <optional>
#include <string_view>
#endif
#include "../azaraC.h"
#include "../internal/FlashString.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_EEW)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_POOL[] = "震度0\000震度1\000震度2\000震度3\000震度4\000震度5弱\000震度5強\000震度6弱\000震度6強\000震度7\000なし\000不明\000";
struct QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_Entry { uint8_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_Entry QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_TABLE[] AZARAC_PROGMEM = {
    {1u, 0u, 7u},
    {2u, 8u, 7u},
    {3u, 16u, 7u},
    {4u, 24u, 7u},
    {5u, 32u, 7u},
    {6u, 40u, 10u},
    {7u, 51u, 10u},
    {8u, 62u, 10u},
    {9u, 73u, 10u},
    {10u, 84u, 7u},
    {14u, 92u, 6u},
    {15u, 99u, 6u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lower_limit_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 12;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_Entry, len));
            return azarac_pgm_view(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_Entry { uint8_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_Entry QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_TABLE[] = {
    {1u, "震度0"},
    {2u, "震度1"},
    {3u, "震度2"},
    {4u, "震度3"},
    {5u, "震度4"},
    {6u, "震度5弱"},
    {7u, "震度5強"},
    {8u, "震度6弱"},
    {9u, "震度6強"},
    {10u, "震度7"},
    {14u, "なし"},
    {15u, "不明"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lower_limit_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 12;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lower_limit_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lower_limit_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
