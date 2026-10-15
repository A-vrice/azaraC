#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.weather_related_disaster_sub_category
// Variable      : qzss_dcr_jma_weather_related_disaster_sub_category_en
// Entries       : 11
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

#if (AZARAC_ENABLE_WEATHER) && (AZARAC_LANG_EN)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_POOL[] = "Snowstorm\000Heavy Rain\000Storm\000Heavy Snow\000High Wave\000Storm Surge\000All Weather Emergency Warnings\000Record-breaking heavy rain in a short time\000Hazardous Wind Watch\000Landslide Alert Information\000Other\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_PARENT_POOL[] = " Emergency Warning\000 Warning\000";
struct QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_PARENT_Entry QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {19u},
};
struct QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_Entry { uint8_t id; uint8_t parent; uint16_t offset; };
static const QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_Entry QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_TABLE[] AZARAC_PROGMEM = {
    {1u, 0u, 0u},
    {2u, 0u, 10u},
    {3u, 0u, 21u},
    {4u, 0u, 27u},
    {5u, 0u, 38u},
    {6u, 0u, 48u},
    {7u, 255u, 60u},
    {21u, 255u, 91u},
    {22u, 255u, 134u},
    {23u, 255u, 155u},
    {31u, 1u, 183u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_weather_related_disaster_sub_category_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 11;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        azarac_pgm_ptr ep = AZARAC_PGM_PTR(QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_TABLE) + static_cast<size_t>(mid) * sizeof(QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_Entry);
        uint8_t eid = static_cast<uint8_t>(azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_Entry, id)));
        if (eid == id) {
            uint16_t off = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_Entry, offset));
            uint8_t pi = azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_Entry, parent));
            if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_POOL) + off);
            azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_PARENT_Entry);
            uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_PARENT_Entry, offset));
            return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_POOL) + off, AZARAC_PGM_PTR(QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_PARENT_POOL) + poff);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_Entry { uint8_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_Entry QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_TABLE[] = {
    {1u, "Snowstorm Emergency Warning"},
    {2u, "Heavy Rain Emergency Warning"},
    {3u, "Storm Emergency Warning"},
    {4u, "Heavy Snow Emergency Warning"},
    {5u, "High Wave Emergency Warning"},
    {6u, "Storm Surge Emergency Warning"},
    {7u, "All Weather Emergency Warnings"},
    {21u, "Record-breaking heavy rain in a short time"},
    {22u, "Hazardous Wind Watch"},
    {23u, "Landslide Alert Information"},
    {31u, "Other Warning"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_weather_related_disaster_sub_category_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 11;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_weather_related_disaster_sub_category_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_weather_related_disaster_sub_category_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
