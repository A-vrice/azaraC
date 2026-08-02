#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_d8_wind_speed
// Variable      : qzss_dcx_camf_d8_wind_speed
// Entries       : 13
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

#if (AZARAC_ENABLE_DCX_CAMF)

inline constexpr uint8_t QZSS_DCX_CAMF_D8_WIND_SPEED_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D8_WIND_SPEED_SIZE = 13;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D8_WIND_SPEED_POOL[] = "Beaufort 0 - 0km/h < v < 1km/h - Calm\000Beaufort 1 - 1km/h < v < 5km/h - Light Air\000Beaufort 2 - 6km/h < v < 11km/h - Light Breeze\000Beaufort 3 - 12km/h < v < 19km/h - Gentle Breeze\000Beaufort 4 - 20km/h < v < 30km/h - Moderate Breeze\000Beaufort 5 - 31km/h < v < 39km/h - Fresh Breeze\000Beaufort 6 - 40km/h < v < 50km/h - Strong Breeze\000Beaufort 7 - 51km/h < v < 61km/h - Near Gale\000Beaufort 8 - 62km/h < v < 74km/h - Gale\000Beaufort 9 - 75km/h < v < 88km/h - Strong Gale\000Beaufort 10 - 89km/h < v < 102km/h - Storm\000Beaufort 11 - 103km/h < v < 117km/h - Violent Storm\000Beaufort 12 - v > 118km/h - Hurricane\000";
struct QZSS_DCX_CAMF_D8_WIND_SPEED_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_D8_WIND_SPEED_Entry QZSS_DCX_CAMF_D8_WIND_SPEED_TABLE[] AZARAC_PROGMEM = {
    {0u, 37u},
    {38u, 42u},
    {81u, 46u},
    {128u, 48u},
    {177u, 50u},
    {228u, 47u},
    {276u, 48u},
    {325u, 44u},
    {370u, 39u},
    {410u, 46u},
    {457u, 42u},
    {500u, 51u},
    {552u, 37u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d8_wind_speed_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D8_WIND_SPEED_BASE || id >= QZSS_DCX_CAMF_D8_WIND_SPEED_BASE + QZSS_DCX_CAMF_D8_WIND_SPEED_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D8_WIND_SPEED_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D8_WIND_SPEED_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D8_WIND_SPEED_Entry, len));
    if (n == 0) return std::nullopt;
    return azarac_pgm_view(QZSS_DCX_CAMF_D8_WIND_SPEED_POOL + off, n);
}
#else
inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_D8_WIND_SPEED_TABLE[] = {
    std::string_view{"Beaufort 0 - 0km/h < v < 1km/h - Calm", 37},
    std::string_view{"Beaufort 1 - 1km/h < v < 5km/h - Light Air", 42},
    std::string_view{"Beaufort 2 - 6km/h < v < 11km/h - Light Breeze", 46},
    std::string_view{"Beaufort 3 - 12km/h < v < 19km/h - Gentle Breeze", 48},
    std::string_view{"Beaufort 4 - 20km/h < v < 30km/h - Moderate Breeze", 50},
    std::string_view{"Beaufort 5 - 31km/h < v < 39km/h - Fresh Breeze", 47},
    std::string_view{"Beaufort 6 - 40km/h < v < 50km/h - Strong Breeze", 48},
    std::string_view{"Beaufort 7 - 51km/h < v < 61km/h - Near Gale", 44},
    std::string_view{"Beaufort 8 - 62km/h < v < 74km/h - Gale", 39},
    std::string_view{"Beaufort 9 - 75km/h < v < 88km/h - Strong Gale", 46},
    std::string_view{"Beaufort 10 - 89km/h < v < 102km/h - Storm", 42},
    std::string_view{"Beaufort 11 - 103km/h < v < 117km/h - Violent Storm", 51},
    std::string_view{"Beaufort 12 - v > 118km/h - Hurricane", 37}
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d8_wind_speed_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D8_WIND_SPEED_BASE || id >= QZSS_DCX_CAMF_D8_WIND_SPEED_BASE + QZSS_DCX_CAMF_D8_WIND_SPEED_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_D8_WIND_SPEED_TABLE[id - QZSS_DCX_CAMF_D8_WIND_SPEED_BASE];
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
