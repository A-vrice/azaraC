#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_weather_related_disaster_sub_category
// Variable      : qzss_dcr_jma_weather_related_disaster_sub_category
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

#if (AZARAC_ENABLE_WEATHER)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_POOL[] = "暴風雪特別警報\000大雨特別警報\000暴風特別警報\000大雪特別警報\000波浪特別警報\000高潮特別警報\000全ての気象特別警報\000記録的短時間大雨情報\000竜巻注意情報\000土砂災害警戒情報\000その他の警報等情報要素\000";
struct QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_Entry { uint8_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_Entry QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_TABLE[] AZARAC_PROGMEM = {
    {1u, 0u, 21u},
    {2u, 22u, 18u},
    {3u, 41u, 18u},
    {4u, 60u, 18u},
    {5u, 79u, 18u},
    {6u, 98u, 18u},
    {7u, 117u, 27u},
    {21u, 145u, 30u},
    {22u, 176u, 18u},
    {23u, 195u, 24u},
    {31u, 220u, 33u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_weather_related_disaster_sub_category_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 11;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_Entry, len));
            if (n == 0) return std::nullopt;
            return azarac_pgm_view(QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_Entry { uint8_t id; std::optional<std::string_view> label; };
inline constexpr QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_Entry QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_TABLE[] = {
    {1u, std::string_view{"暴風雪特別警報", 21}},
    {2u, std::string_view{"大雨特別警報", 18}},
    {3u, std::string_view{"暴風特別警報", 18}},
    {4u, std::string_view{"大雪特別警報", 18}},
    {5u, std::string_view{"波浪特別警報", 18}},
    {6u, std::string_view{"高潮特別警報", 18}},
    {7u, std::string_view{"全ての気象特別警報", 27}},
    {21u, std::string_view{"記録的短時間大雨情報", 30}},
    {22u, std::string_view{"竜巻注意情報", 18}},
    {23u, std::string_view{"土砂災害警戒情報", 24}},
    {31u, std::string_view{"その他の警報等情報要素", 33}},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_weather_related_disaster_sub_category_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 11;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_TABLE[mid].id == id) return QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_TABLE[mid].label;
        if (QZSS_DCR_JMA_WEATHER_RELATED_DISASTER_SUB_CATEGORY_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_weather_related_disaster_sub_category_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_weather_related_disaster_sub_category_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
