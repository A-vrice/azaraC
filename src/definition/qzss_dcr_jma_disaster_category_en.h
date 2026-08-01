#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_disaster_category_en
// Variable      : qzss_dcr_jma_disaster_category_en
// Entries       : 12
// Strategy      : array

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

#if (AZARAC_LANG_EN)

inline constexpr uint8_t QZSS_DCR_JMA_DISASTER_CATEGORY_EN_BASE = 1;
inline constexpr uint8_t QZSS_DCR_JMA_DISASTER_CATEGORY_EN_SIZE = 12;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_DISASTER_CATEGORY_EN_POOL[] = "Earthquake Early Warning\0Hypocenter\0Seismic Intensity\0Nankai Trough Earthquake\0Tsunami\0Northwest Pacific Tsunami\0Volcano\0Ash Fall\0Weather\0Flood\0Typhoon\0Marine\0";
struct QZSS_DCR_JMA_DISASTER_CATEGORY_EN_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_DISASTER_CATEGORY_EN_Entry QZSS_DCR_JMA_DISASTER_CATEGORY_EN_TABLE[] AZARAC_PROGMEM = {
    {0u, 24u},
    {25u, 10u},
    {36u, 17u},
    {54u, 24u},
    {79u, 7u},
    {87u, 25u},
    {113u, 7u},
    {121u, 8u},
    {130u, 7u},
    {138u, 5u},
    {144u, 7u},
    {152u, 6u}
};
[[nodiscard]] inline const char* qzss_dcr_jma_disaster_category_en_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_DISASTER_CATEGORY_EN_BASE || id >= QZSS_DCR_JMA_DISASTER_CATEGORY_EN_BASE + QZSS_DCR_JMA_DISASTER_CATEGORY_EN_SIZE) return nullptr;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCR_JMA_DISASTER_CATEGORY_EN_TABLE[id - 1u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCR_JMA_DISASTER_CATEGORY_EN_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCR_JMA_DISASTER_CATEGORY_EN_Entry, len));
    if (n == 0) return nullptr;
    return azarac_pgm_copy(QZSS_DCR_JMA_DISASTER_CATEGORY_EN_POOL + off);
}
#else
inline constexpr const char* QZSS_DCR_JMA_DISASTER_CATEGORY_EN_TABLE[] = {
    "Earthquake Early Warning",
    "Hypocenter",
    "Seismic Intensity",
    "Nankai Trough Earthquake",
    "Tsunami",
    "Northwest Pacific Tsunami",
    "Volcano",
    "Ash Fall",
    "Weather",
    "Flood",
    "Typhoon",
    "Marine"
};
[[nodiscard]] inline constexpr const char* qzss_dcr_jma_disaster_category_en_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_DISASTER_CATEGORY_EN_BASE || id >= QZSS_DCR_JMA_DISASTER_CATEGORY_EN_BASE + QZSS_DCR_JMA_DISASTER_CATEGORY_EN_SIZE) return nullptr;
    return QZSS_DCR_JMA_DISASTER_CATEGORY_EN_TABLE[id - QZSS_DCR_JMA_DISASTER_CATEGORY_EN_BASE];
}
#endif

#else

[[nodiscard]] inline constexpr const char* qzss_dcr_jma_disaster_category_en_lookup(uint8_t id) noexcept {
    (void)id;
    return nullptr;
}

#endif

} // namespace def
} // namespace azaraC
