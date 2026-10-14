#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.camf.d_fields
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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_POOL[] = "T ≤ -3\000-30°C < T ≤ -2\000-25°C < T ≤ -2\000-20°C < T ≤ -1\000-15°C < T ≤ -1\000-10°C < T ≤ -\000-5°C < T ≤ \0000°C < T ≤ \0005°C < T ≤ 1\00010°C < T ≤ 1\00015°C < T ≤ 2\00020°C < T ≤ 2\00025°C < T ≤ 3\00030°C < T ≤ 3\00035°C < T ≤ 4\000T > 4\000";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_PARENT_POOL[] = "0°C\0005°C\000";
struct QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_PARENT_Entry QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 4u},
    {5u, 4u},
};
struct QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_Entry { uint16_t offset; uint8_t len; uint8_t parent; };
static const QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_Entry QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_TABLE[] AZARAC_PROGMEM = {
    {0u, 8u, 0u},
    {9u, 17u, 1u},
    {27u, 17u, 0u},
    {45u, 17u, 1u},
    {63u, 17u, 0u},
    {81u, 16u, 1u},
    {98u, 14u, 0u},
    {113u, 13u, 1u},
    {127u, 14u, 0u},
    {142u, 15u, 1u},
    {158u, 15u, 0u},
    {174u, 15u, 1u},
    {190u, 15u, 0u},
    {206u, 15u, 1u},
    {222u, 15u, 1u},
    {238u, 5u, 1u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d6_temperature_range_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_BASE || id >= QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_BASE + QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_Entry, offset));
    uint8_t n = pgm_read_byte(p + offsetof(QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_Entry, len));
    uint8_t pi = pgm_read_byte(p + offsetof(QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_Entry, parent));
    if (pi == 255u) return azarac_pgm_view(QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_POOL + off, n);
    const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_PARENT_TABLE[pi]);
    uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_PARENT_Entry, offset));
    uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_PARENT_Entry, len));
    return azarac_pgm_join(QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_POOL + off, n, QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_PARENT_POOL + poff, pn);
}
#else
inline constexpr const char* QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_TABLE[] = {
    "T ≤ -30°C",
    "-30°C < T ≤ -25°C",
    "-25°C < T ≤ -20°C",
    "-20°C < T ≤ -15°C",
    "-15°C < T ≤ -10°C",
    "-10°C < T ≤ -5°C",
    "-5°C < T ≤ 0°C",
    "0°C < T ≤ 5°C",
    "5°C < T ≤ 10°C",
    "10°C < T ≤ 15°C",
    "15°C < T ≤ 20°C",
    "20°C < T ≤ 25°C",
    "25°C < T ≤ 30°C",
    "30°C < T ≤ 35°C",
    "35°C < T ≤ 45°C",
    "T > 45°C"
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d6_temperature_range_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_BASE || id >= QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_BASE + QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_SIZE) return std::nullopt;
    const char* s = QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_TABLE[id - QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_BASE];
    return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
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
