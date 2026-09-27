#pragma once
// AUTO-GENERATED from azarashi 0.17.0 with CI-CD
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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_POOL[] = "Seismic intensity of 0\000Seismic intensity of 1\000Seismic intensity of 2\000Seismic intensity of 3\000Seismic intensity of 4\000Seismic intensity of 5-lower\000Seismic intensity of 5-upper\000Seismic intensity of 6-lower\000Seismic intensity of 6-upper\000Seismic intensity of 7\000None\000Unknown\000";
struct QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_Entry { uint8_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_Entry QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_TABLE[] AZARAC_PROGMEM = {
    {1u, 0u, 22u},
    {2u, 23u, 22u},
    {3u, 46u, 22u},
    {4u, 69u, 22u},
    {5u, 92u, 22u},
    {6u, 115u, 28u},
    {7u, 144u, 28u},
    {8u, 173u, 28u},
    {9u, 202u, 28u},
    {10u, 231u, 22u},
    {14u, 254u, 4u},
    {15u, 259u, 7u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lower_limit_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 12;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_Entry, len));
            return azarac_pgm_view(QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_EN_POOL + off, n);
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
