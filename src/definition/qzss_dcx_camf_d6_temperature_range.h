#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d6_temperature_range
// Entries       : 16
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

inline constexpr uint8_t QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_SIZE = 16;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_POOL[] = "T ≤ -30°C\000-30°C < T ≤ -25°C\000-25°C < T ≤ -20°C\000-20°C < T ≤ -15°C\000-15°C < T ≤ -10°C\000-10°C < T ≤ -5°C\000-5°C < T ≤ 0°C\0000°C < T ≤ 5°C\0005°C < T ≤ 10°C\00010°C < T ≤ 15°C\00015°C < T ≤ 20°C\00020°C < T ≤ 25°C\00025°C < T ≤ 30°C\00030°C < T ≤ 35°C\00035°C < T ≤ 45°C\000T > 45°C\000";
struct QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_Entry QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_TABLE[] AZARAC_PROGMEM = {
    {0u, 12u},
    {13u, 21u},
    {35u, 21u},
    {57u, 21u},
    {79u, 21u},
    {101u, 20u},
    {122u, 18u},
    {141u, 17u},
    {159u, 18u},
    {178u, 19u},
    {198u, 19u},
    {218u, 19u},
    {238u, 19u},
    {258u, 19u},
    {278u, 19u},
    {298u, 9u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d6_temperature_range_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_BASE || id >= QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_BASE + QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_Entry, len));
    if (n == 0) return std::nullopt;
    return azarac_pgm_view(QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_POOL + off, n);
}
#else
inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_TABLE[] = {
    std::string_view{"T ≤ -30°C", 12},
    std::string_view{"-30°C < T ≤ -25°C", 21},
    std::string_view{"-25°C < T ≤ -20°C", 21},
    std::string_view{"-20°C < T ≤ -15°C", 21},
    std::string_view{"-15°C < T ≤ -10°C", 21},
    std::string_view{"-10°C < T ≤ -5°C", 20},
    std::string_view{"-5°C < T ≤ 0°C", 18},
    std::string_view{"0°C < T ≤ 5°C", 17},
    std::string_view{"5°C < T ≤ 10°C", 18},
    std::string_view{"10°C < T ≤ 15°C", 19},
    std::string_view{"15°C < T ≤ 20°C", 19},
    std::string_view{"20°C < T ≤ 25°C", 19},
    std::string_view{"25°C < T ≤ 30°C", 19},
    std::string_view{"30°C < T ≤ 35°C", 19},
    std::string_view{"35°C < T ≤ 45°C", 19},
    std::string_view{"T > 45°C", 9}
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d6_temperature_range_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_BASE || id >= QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_BASE + QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_TABLE[id - QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_BASE];
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d6_temperature_range_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d6_temperature_range_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
