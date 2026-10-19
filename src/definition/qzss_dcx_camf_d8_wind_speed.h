#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.d_fields → qzss_dcx_camf_d8_wind_speed: 13 entries, strategy array
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

#if (AZARAC_ENABLE_DCX_CAMF)

inline constexpr uint8_t QZSS_DCX_CAMF_D8_WIND_SPEED_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D8_WIND_SPEED_SIZE = 13;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D8_WIND_SPEED_POOL[] = "0 - 0km/h < v < 1km/h - Calm\0001 - 1km/h < v < 5km/h - Light Air\0002 - 6km/h < v < 11km/h - Light Breeze\0003 - 12km/h < v < 19km/h - Gentle Breeze\0004 - 20km/h < v < 30km/h - Moderate Breeze\0005 - 31km/h < v < 39km/h - Fresh Breeze\0006 - 40km/h < v < 50km/h - Strong Breeze\0007 - 51km/h < v < 61km/h - Near Gale\0008 - 62km/h < v < 74km/h - Gale\0009 - 75km/h < v < 88km/h - Strong Gale\00010 - 89km/h < v < 102km/h - Storm\00011 - 103km/h < v < 117km/h - Violent Storm\00012 - v > 118km/h - Hurricane\000";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D8_WIND_SPEED_PARENT_POOL[] = "Beaufort \000";
struct QZSS_DCX_CAMF_D8_WIND_SPEED_PARENT_Entry { uint16_t offset; };
static const QZSS_DCX_CAMF_D8_WIND_SPEED_PARENT_Entry QZSS_DCX_CAMF_D8_WIND_SPEED_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
};
struct QZSS_DCX_CAMF_D8_WIND_SPEED_Entry { uint16_t offset; uint8_t parent; };
static const QZSS_DCX_CAMF_D8_WIND_SPEED_Entry QZSS_DCX_CAMF_D8_WIND_SPEED_TABLE[] AZARAC_PROGMEM = {
    {0u, 0u},
    {29u, 0u},
    {63u, 0u},
    {101u, 0u},
    {141u, 0u},
    {183u, 0u},
    {222u, 0u},
    {262u, 0u},
    {298u, 0u},
    {329u, 0u},
    {367u, 0u},
    {401u, 0u},
    {444u, 0u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d8_wind_speed_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D8_WIND_SPEED_BASE || id >= QZSS_DCX_CAMF_D8_WIND_SPEED_BASE + QZSS_DCX_CAMF_D8_WIND_SPEED_SIZE) return std::nullopt;
    azarac_pgm_ptr p = AZARAC_PGM_PTR(QZSS_DCX_CAMF_D8_WIND_SPEED_TABLE) + static_cast<size_t>(id - 0u) * sizeof(QZSS_DCX_CAMF_D8_WIND_SPEED_Entry);
    uint16_t off = azarac_read_word(p, offsetof(QZSS_DCX_CAMF_D8_WIND_SPEED_Entry, offset));
    uint8_t pi = azarac_read_byte(p, offsetof(QZSS_DCX_CAMF_D8_WIND_SPEED_Entry, parent));
    if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D8_WIND_SPEED_POOL) + off);
    azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCX_CAMF_D8_WIND_SPEED_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCX_CAMF_D8_WIND_SPEED_PARENT_Entry);
    uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCX_CAMF_D8_WIND_SPEED_PARENT_Entry, offset));
    return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D8_WIND_SPEED_PARENT_POOL) + poff, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D8_WIND_SPEED_POOL) + off);
}
#else
inline constexpr const char* QZSS_DCX_CAMF_D8_WIND_SPEED_TABLE[] = {
    "Beaufort 0 - 0km/h < v < 1km/h - Calm",
    "Beaufort 1 - 1km/h < v < 5km/h - Light Air",
    "Beaufort 2 - 6km/h < v < 11km/h - Light Breeze",
    "Beaufort 3 - 12km/h < v < 19km/h - Gentle Breeze",
    "Beaufort 4 - 20km/h < v < 30km/h - Moderate Breeze",
    "Beaufort 5 - 31km/h < v < 39km/h - Fresh Breeze",
    "Beaufort 6 - 40km/h < v < 50km/h - Strong Breeze",
    "Beaufort 7 - 51km/h < v < 61km/h - Near Gale",
    "Beaufort 8 - 62km/h < v < 74km/h - Gale",
    "Beaufort 9 - 75km/h < v < 88km/h - Strong Gale",
    "Beaufort 10 - 89km/h < v < 102km/h - Storm",
    "Beaufort 11 - 103km/h < v < 117km/h - Violent Storm",
    "Beaufort 12 - v > 118km/h - Hurricane"
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d8_wind_speed_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D8_WIND_SPEED_BASE || id >= QZSS_DCX_CAMF_D8_WIND_SPEED_BASE + QZSS_DCX_CAMF_D8_WIND_SPEED_SIZE) return std::nullopt;
    const char* s = QZSS_DCX_CAMF_D8_WIND_SPEED_TABLE[id - QZSS_DCX_CAMF_D8_WIND_SPEED_BASE];
    return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d8_wind_speed_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d8_wind_speed_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
