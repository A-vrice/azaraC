#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.seismic_intensity_lower_limit
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

#if (AZARAC_ENABLE_EEW) && (AZARAC_LANG_JA)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_POOL[] = "0\0001\0002\0003\0004\0005弱\0005強\0006弱\0006強\0007\000なし\000不明\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_PARENT_POOL[] = "震度\000";
struct QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_PARENT_Entry QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 6u},
};
struct QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_Entry { uint8_t id; uint8_t parent; uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_Entry QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_TABLE[] AZARAC_PROGMEM = {
    {1u, 0u, 0u, 1u},
    {2u, 0u, 2u, 1u},
    {3u, 0u, 4u, 1u},
    {4u, 0u, 6u, 1u},
    {5u, 0u, 8u, 1u},
    {6u, 0u, 10u, 4u},
    {7u, 0u, 15u, 4u},
    {8u, 0u, 20u, 4u},
    {9u, 0u, 25u, 4u},
    {10u, 0u, 30u, 1u},
    {14u, 255u, 32u, 6u},
    {15u, 255u, 39u, 6u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lower_limit_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 12;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_Entry, offset));
            uint8_t n = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_Entry, len));
            uint8_t pi = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_Entry, parent));
            if (pi == 255u) return azarac_pgm_view(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_POOL + off, n);
            const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_PARENT_TABLE[pi]);
            uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_PARENT_Entry, offset));
            uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_PARENT_Entry, len));
            return azarac_pgm_join(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_PARENT_POOL + poff, pn, QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_POOL + off, n);
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
