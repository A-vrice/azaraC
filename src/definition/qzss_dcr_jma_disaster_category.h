#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_disaster_category
// Variable      : qzss_dcr_jma_disaster_category
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

#if (AZARAC_LANG_JA)

inline constexpr uint8_t QZSS_DCR_JMA_DISASTER_CATEGORY_BASE = 1;
inline constexpr uint8_t QZSS_DCR_JMA_DISASTER_CATEGORY_SIZE = 12;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_DISASTER_CATEGORY_POOL[] = "緊急地震速報\000震源\000震度\000南海トラフ地震\000津波\000北西太平洋津波\000火山\000降灰\000気象\000洪水\000台風\000海上\000";
struct QZSS_DCR_JMA_DISASTER_CATEGORY_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_DISASTER_CATEGORY_Entry QZSS_DCR_JMA_DISASTER_CATEGORY_TABLE[] AZARAC_PROGMEM = {
    {0u, 18u},
    {19u, 6u},
    {26u, 6u},
    {33u, 21u},
    {55u, 6u},
    {62u, 21u},
    {84u, 6u},
    {91u, 6u},
    {98u, 6u},
    {105u, 6u},
    {112u, 6u},
    {119u, 6u}
};
[[nodiscard]] inline const char* qzss_dcr_jma_disaster_category_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_DISASTER_CATEGORY_BASE || id >= QZSS_DCR_JMA_DISASTER_CATEGORY_BASE + QZSS_DCR_JMA_DISASTER_CATEGORY_SIZE) return nullptr;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCR_JMA_DISASTER_CATEGORY_TABLE[id - 1u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCR_JMA_DISASTER_CATEGORY_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCR_JMA_DISASTER_CATEGORY_Entry, len));
    if (n == 0) return nullptr;
    return azarac_pgm_copy(QZSS_DCR_JMA_DISASTER_CATEGORY_POOL + off);
}
#else
inline constexpr const char* QZSS_DCR_JMA_DISASTER_CATEGORY_TABLE[] = {
    "緊急地震速報",
    "震源",
    "震度",
    "南海トラフ地震",
    "津波",
    "北西太平洋津波",
    "火山",
    "降灰",
    "気象",
    "洪水",
    "台風",
    "海上"
};
[[nodiscard]] inline constexpr const char* qzss_dcr_jma_disaster_category_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_DISASTER_CATEGORY_BASE || id >= QZSS_DCR_JMA_DISASTER_CATEGORY_BASE + QZSS_DCR_JMA_DISASTER_CATEGORY_SIZE) return nullptr;
    return QZSS_DCR_JMA_DISASTER_CATEGORY_TABLE[id - QZSS_DCR_JMA_DISASTER_CATEGORY_BASE];
}
#endif

#else

[[nodiscard]] inline constexpr const char* qzss_dcr_jma_disaster_category_lookup(uint8_t id) noexcept {
    (void)id;
    return nullptr;
}

#endif

} // namespace def
} // namespace azaraC
