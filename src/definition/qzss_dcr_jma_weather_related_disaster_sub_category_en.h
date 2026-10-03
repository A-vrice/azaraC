#pragma once
// AUTO-GENERATED from azarashi 0.17.0 with CI-CD
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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_POOL[] = "Snowstorm Emergency Warning\000Heavy Rain Emergency Warning\000Storm Emergency Warning\000Heavy Snow Emergency Warning\000High Wave Emergency Warning\000Storm Surge Emergency Warning\000All Weather Emergency Warnings\000Record-breaking heavy rain in a short time\000Hazardous Wind Watch\000Landslide Alert Information\000Other Warning\000";
struct QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_Entry { uint8_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_Entry QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_TABLE[] AZARAC_PROGMEM = {
    {1u, 0u, 27u},
    {2u, 28u, 28u},
    {3u, 57u, 23u},
    {4u, 81u, 28u},
    {5u, 110u, 27u},
    {6u, 138u, 29u},
    {7u, 168u, 30u},
    {21u, 199u, 42u},
    {22u, 242u, 20u},
    {23u, 263u, 27u},
    {31u, 291u, 13u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_weather_related_disaster_sub_category_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 11;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_Entry, len));
            return azarac_pgm_view(QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_EN_POOL + off, n);
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
