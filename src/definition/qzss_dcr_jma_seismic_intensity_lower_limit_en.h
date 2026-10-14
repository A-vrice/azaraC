#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.seismic_intensity_lower_limit
// Variable      : qzss_dcr_jma_seismic_intensity_lower_limit_en
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

#if (AZARAC_ENABLE_EEW) && (AZARAC_LANG_EN)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_POOL[] = "0\0001\0002\0003\0004\0005-lower\0005-upper\0006-lower\0006-upper\0007\000None\000Unknown\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_PARENT_POOL[] = "Seismic intensity of \000";
struct QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_PARENT_Entry QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
};
struct QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_Entry { uint8_t id; uint8_t parent; uint16_t offset; };
static const QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_Entry QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_TABLE[] AZARAC_PROGMEM = {
    {1u, 0u, 0u},
    {2u, 0u, 2u},
    {3u, 0u, 4u},
    {4u, 0u, 6u},
    {5u, 0u, 8u},
    {6u, 0u, 10u},
    {7u, 0u, 18u},
    {8u, 0u, 26u},
    {9u, 0u, 34u},
    {10u, 0u, 42u},
    {14u, 255u, 44u},
    {15u, 255u, 49u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lower_limit_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 12;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_Entry, offset));
            uint8_t pi = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_Entry, parent));
            if (pi == 255u) return azarac_pgm_view_z(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_POOL + off);
            const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_PARENT_TABLE[pi]);
            uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_PARENT_Entry, offset));
            return azarac_pgm_join_z(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_PARENT_POOL + poff, QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_POOL + off);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_Entry { uint8_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_Entry QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_TABLE[] = {
    {1u, "Seismic intensity of 0"},
    {2u, "Seismic intensity of 1"},
    {3u, "Seismic intensity of 2"},
    {4u, "Seismic intensity of 3"},
    {5u, "Seismic intensity of 4"},
    {6u, "Seismic intensity of 5-lower"},
    {7u, "Seismic intensity of 5-upper"},
    {8u, "Seismic intensity of 6-lower"},
    {9u, "Seismic intensity of 6-upper"},
    {10u, "Seismic intensity of 7"},
    {14u, "None"},
    {15u, "Unknown"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lower_limit_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 12;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lower_limit_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lower_limit_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
