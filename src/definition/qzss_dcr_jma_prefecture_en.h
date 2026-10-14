#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_PREFECTURE_EN_POOL[] = "Hokkaido\000Aomori\000Iwate\000Miyagi\000Akit\000Yamagat\000Fukushim\000Ibaraki\000Tochigi\000Gunm\000Saitam\000Chib\000Tokyo Metropolis\000Kanagaw\000Niigat\000Toyam\000Ishikaw\000Fukui\000Yamanashi\000Nagano\000Gifu\000Shizuok\000Aichi\000Mie \000Shig\000Kyoto\000Osak\000Hyogo\000Nara\000Wakayam\000Tottori\000Shimane\000Okayam\000Hiroshim\000Yamaguchi\000Tokushim\000Kagaw\000Ehime\000Kochi\000Fukuok\000Saga\000Nagasaki\000Kumamoto\000Oita\000Miyazaki\000Kagoshim\000Okinaw\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_PREFECTURE_EN_PARENT_POOL[] = " Prefecture\000Prefecture\000a Prefecture\000";
struct QZSS_DCR_JMA_PREFECTURE_EN_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_PREFECTURE_EN_PARENT_Entry QZSS_DCR_JMA_PREFECTURE_EN_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 11u},
    {12u, 10u},
    {23u, 12u},
};
struct QZSS_DCR_JMA_PREFECTURE_EN_Entry { uint16_t offset; uint8_t len; uint8_t parent; };
static const QZSS_DCR_JMA_PREFECTURE_EN_Entry QZSS_DCR_JMA_PREFECTURE_EN_TABLE[] AZARAC_PROGMEM = {
    {0u, 8u, 0u},
    {9u, 6u, 0u},
    {16u, 5u, 0u},
    {22u, 6u, 0u},
    {29u, 4u, 2u},
    {34u, 7u, 2u},
    {42u, 8u, 2u},
    {51u, 7u, 0u},
    {59u, 7u, 0u},
    {67u, 4u, 2u},
    {72u, 6u, 2u},
    {79u, 4u, 2u},
    {84u, 16u, 255u},
    {101u, 7u, 2u},
    {109u, 6u, 2u},
    {116u, 5u, 2u},
    {122u, 7u, 2u},
    {130u, 5u, 0u},
    {136u, 9u, 0u},
    {146u, 6u, 0u},
    {153u, 4u, 0u},
    {158u, 7u, 2u},
    {166u, 5u, 0u},
    {172u, 4u, 1u},
    {177u, 4u, 2u},
    {182u, 5u, 0u},
    {188u, 4u, 2u},
    {193u, 5u, 0u},
    {199u, 4u, 0u},
    {204u, 7u, 2u},
    {212u, 7u, 0u},
    {220u, 7u, 0u},
    {228u, 6u, 2u},
    {235u, 8u, 2u},
    {244u, 9u, 0u},
    {254u, 8u, 2u},
    {263u, 5u, 2u},
    {269u, 5u, 0u},
    {275u, 5u, 0u},
    {281u, 6u, 2u},
    {288u, 4u, 0u},
    {293u, 8u, 0u},
    {302u, 8u, 0u},
    {311u, 4u, 0u},
    {316u, 8u, 0u},
    {325u, 8u, 2u},
    {334u, 6u, 2u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_prefecture_en_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_PREFECTURE_EN_BASE || id >= QZSS_DCR_JMA_PREFECTURE_EN_BASE + QZSS_DCR_JMA_PREFECTURE_EN_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCR_JMA_PREFECTURE_EN_TABLE[id - 1u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCR_JMA_PREFECTURE_EN_Entry, offset));
    uint8_t n = pgm_read_byte(p + offsetof(QZSS_DCR_JMA_PREFECTURE_EN_Entry, len));
    uint8_t pi = pgm_read_byte(p + offsetof(QZSS_DCR_JMA_PREFECTURE_EN_Entry, parent));
    if (pi == 255u) return azarac_pgm_view(QZSS_DCR_JMA_PREFECTURE_EN_POOL + off, n);
    const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_PREFECTURE_EN_PARENT_TABLE[pi]);
    uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_PREFECTURE_EN_PARENT_Entry, offset));
    uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCR_JMA_PREFECTURE_EN_PARENT_Entry, len));
    return azarac_pgm_join(QZSS_DCR_JMA_PREFECTURE_EN_POOL + off, n, QZSS_DCR_JMA_PREFECTURE_EN_PARENT_POOL + poff, pn);
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
