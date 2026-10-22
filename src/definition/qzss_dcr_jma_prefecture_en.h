#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.prefecture → qzss_dcr_jma_prefecture_en: 47 entries, strategy array
// Unknown id returns nullptr — callers MUST null-check.

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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_PREFECTURE_EN_POOL[] = "Hokkaido\000Aomori\000Iwate\000Miyagi\000Akit\000Yamagat\000Fukushim\000Ibaraki\000Tochigi\000Gunm\000Saitam\000Chib\000Tokyo Metropolis\000Kanagaw\000Niigat\000Toyam\000Ishikaw\000Fukui\000Yamanashi\000Nagano\000Gifu\000Shizuok\000Aichi\000Mie\000Shig\000Kyoto\000Osak\000Hyogo\000Nar\000Wakayam\000Tottori\000Shimane\000Okayam\000Hiroshim\000Yamaguchi\000Tokushim\000Kagaw\000Ehime\000Kochi\000Fukuok\000Sag\000Nagasaki\000Kumamoto\000Oit\000Miyazaki\000Kagoshim\000Okinaw\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_PREFECTURE_EN_PARENT_POOL[] = " Prefecture\000a Prefecture\000";
struct QZSS_DCR_JMA_PREFECTURE_EN_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_PREFECTURE_EN_PARENT_Entry QZSS_DCR_JMA_PREFECTURE_EN_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {12u},
};
struct QZSS_DCR_JMA_PREFECTURE_EN_Entry { uint16_t offset; uint8_t parent; };
static const QZSS_DCR_JMA_PREFECTURE_EN_Entry QZSS_DCR_JMA_PREFECTURE_EN_TABLE[] AZARAC_PROGMEM = {
    {0u, 0u},
    {9u, 0u},
    {16u, 0u},
    {22u, 0u},
    {29u, 1u},
    {34u, 1u},
    {42u, 1u},
    {51u, 0u},
    {59u, 0u},
    {67u, 1u},
    {72u, 1u},
    {79u, 1u},
    {84u, 255u},
    {101u, 1u},
    {109u, 1u},
    {116u, 1u},
    {122u, 1u},
    {130u, 0u},
    {136u, 0u},
    {146u, 0u},
    {153u, 0u},
    {158u, 1u},
    {166u, 0u},
    {172u, 0u},
    {176u, 1u},
    {181u, 0u},
    {187u, 1u},
    {192u, 0u},
    {198u, 1u},
    {202u, 1u},
    {210u, 0u},
    {218u, 0u},
    {226u, 1u},
    {233u, 1u},
    {242u, 0u},
    {252u, 1u},
    {261u, 1u},
    {267u, 0u},
    {273u, 0u},
    {279u, 1u},
    {286u, 1u},
    {290u, 0u},
    {299u, 0u},
    {308u, 1u},
    {312u, 0u},
    {321u, 1u},
    {330u, 1u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_prefecture_en_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_PREFECTURE_EN_BASE || id >= QZSS_DCR_JMA_PREFECTURE_EN_BASE + QZSS_DCR_JMA_PREFECTURE_EN_SIZE) return std::nullopt;
    azarac_pgm_ptr p = AZARAC_PGM_PTR(QZSS_DCR_JMA_PREFECTURE_EN_TABLE) + static_cast<size_t>(id - 1u) * sizeof(QZSS_DCR_JMA_PREFECTURE_EN_Entry);
    uint16_t off = azarac_read_word(p, offsetof(QZSS_DCR_JMA_PREFECTURE_EN_Entry, offset));
    uint8_t pi = azarac_read_byte(p, offsetof(QZSS_DCR_JMA_PREFECTURE_EN_Entry, parent));
    if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_PREFECTURE_EN_POOL) + off);
    azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCR_JMA_PREFECTURE_EN_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCR_JMA_PREFECTURE_EN_PARENT_Entry);
    uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCR_JMA_PREFECTURE_EN_PARENT_Entry, offset));
    return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_PREFECTURE_EN_POOL) + off, AZARAC_PGM_PTR(QZSS_DCR_JMA_PREFECTURE_EN_PARENT_POOL) + poff);
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
