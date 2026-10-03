#pragma once
// AUTO-GENERATED from azarashi 0.17.0 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.prefecture
// Variable      : qzss_dcr_jma_prefecture_en
// Entries       : 47
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

#if (AZARAC_ENABLE_SEISMIC || AZARAC_ENABLE_DCX_CAMF) && (AZARAC_LANG_EN)

inline constexpr uint8_t QZSS_DCR_JMA_PREFECTURE_EN_BASE = 1;
inline constexpr uint8_t QZSS_DCR_JMA_PREFECTURE_EN_SIZE = 47;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_PREFECTURE_EN_POOL[] = "Hokkaido Prefecture\000Aomori Prefecture\000Iwate Prefecture\000Miyagi Prefecture\000Akita Prefecture\000Yamagata Prefecture\000Fukushima Prefecture\000Ibaraki Prefecture\000Tochigi Prefecture\000Gunma Prefecture\000Saitama Prefecture\000Chiba Prefecture\000Tokyo Metropolis\000Kanagawa Prefecture\000Niigata Prefecture\000Toyama Prefecture\000Ishikawa Prefecture\000Fukui Prefecture\000Yamanashi Prefecture\000Nagano Prefecture\000Gifu Prefecture\000Shizuoka Prefecture\000Aichi Prefecture\000Mie Prefecture\000Shiga Prefecture\000Kyoto Prefecture\000Osaka Prefecture\000Hyogo Prefecture\000Nara Prefecture\000Wakayama Prefecture\000Tottori Prefecture\000Shimane Prefecture\000Okayama Prefecture\000Hiroshima Prefecture\000Yamaguchi Prefecture\000Tokushima Prefecture\000Kagawa Prefecture\000Ehime Prefecture\000Kochi Prefecture\000Fukuoka Prefecture\000Saga Prefecture\000Nagasaki Prefecture\000Kumamoto Prefecture\000Oita Prefecture\000Miyazaki Prefecture\000Kagoshima Prefecture\000Okinawa Prefecture\000";
struct QZSS_DCR_JMA_PREFECTURE_EN_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_PREFECTURE_EN_Entry QZSS_DCR_JMA_PREFECTURE_EN_TABLE[] AZARAC_PROGMEM = {
    {0u, 19u},
    {20u, 17u},
    {38u, 16u},
    {55u, 17u},
    {73u, 16u},
    {90u, 19u},
    {110u, 20u},
    {131u, 18u},
    {150u, 18u},
    {169u, 16u},
    {186u, 18u},
    {205u, 16u},
    {222u, 16u},
    {239u, 19u},
    {259u, 18u},
    {278u, 17u},
    {296u, 19u},
    {316u, 16u},
    {333u, 20u},
    {354u, 17u},
    {372u, 15u},
    {388u, 19u},
    {408u, 16u},
    {425u, 14u},
    {440u, 16u},
    {457u, 16u},
    {474u, 16u},
    {491u, 16u},
    {508u, 15u},
    {524u, 19u},
    {544u, 18u},
    {563u, 18u},
    {582u, 18u},
    {601u, 20u},
    {622u, 20u},
    {643u, 20u},
    {664u, 17u},
    {682u, 16u},
    {699u, 16u},
    {716u, 18u},
    {735u, 15u},
    {751u, 19u},
    {771u, 19u},
    {791u, 15u},
    {807u, 19u},
    {827u, 20u},
    {848u, 18u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_prefecture_en_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_PREFECTURE_EN_BASE || id >= QZSS_DCR_JMA_PREFECTURE_EN_BASE + QZSS_DCR_JMA_PREFECTURE_EN_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCR_JMA_PREFECTURE_EN_TABLE[id - 1u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCR_JMA_PREFECTURE_EN_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCR_JMA_PREFECTURE_EN_Entry, len));
    return azarac_pgm_view(QZSS_DCR_JMA_PREFECTURE_EN_POOL + off, n);
}
#else
inline constexpr const char* QZSS_DCR_JMA_PREFECTURE_EN_TABLE[] = {
    "Hokkaido Prefecture",
    "Aomori Prefecture",
    "Iwate Prefecture",
    "Miyagi Prefecture",
    "Akita Prefecture",
    "Yamagata Prefecture",
    "Fukushima Prefecture",
    "Ibaraki Prefecture",
    "Tochigi Prefecture",
    "Gunma Prefecture",
    "Saitama Prefecture",
    "Chiba Prefecture",
    "Tokyo Metropolis",
    "Kanagawa Prefecture",
    "Niigata Prefecture",
    "Toyama Prefecture",
    "Ishikawa Prefecture",
    "Fukui Prefecture",
    "Yamanashi Prefecture",
    "Nagano Prefecture",
    "Gifu Prefecture",
    "Shizuoka Prefecture",
    "Aichi Prefecture",
    "Mie Prefecture",
    "Shiga Prefecture",
    "Kyoto Prefecture",
    "Osaka Prefecture",
    "Hyogo Prefecture",
    "Nara Prefecture",
    "Wakayama Prefecture",
    "Tottori Prefecture",
    "Shimane Prefecture",
    "Okayama Prefecture",
    "Hiroshima Prefecture",
    "Yamaguchi Prefecture",
    "Tokushima Prefecture",
    "Kagawa Prefecture",
    "Ehime Prefecture",
    "Kochi Prefecture",
    "Fukuoka Prefecture",
    "Saga Prefecture",
    "Nagasaki Prefecture",
    "Kumamoto Prefecture",
    "Oita Prefecture",
    "Miyazaki Prefecture",
    "Kagoshima Prefecture",
    "Okinawa Prefecture"
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_prefecture_en_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_PREFECTURE_EN_BASE || id >= QZSS_DCR_JMA_PREFECTURE_EN_BASE + QZSS_DCR_JMA_PREFECTURE_EN_SIZE) return std::nullopt;
    const char* s = QZSS_DCR_JMA_PREFECTURE_EN_TABLE[id - QZSS_DCR_JMA_PREFECTURE_EN_BASE];
    return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_prefecture_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_prefecture_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
