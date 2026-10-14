#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.camf.d_fields
// Variable      : qzss_dcx_camf_d3_azimuth_from_centre_of_main_ellipse_to_epicentre
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

inline constexpr uint8_t QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_SIZE = 16;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_POOL[] = "0°\00022.5\00045°\00067.5\00090°\000112.\000135°\000157.\000180°\000202.\000225°\000247.\000270°\000292.\000315°\000337.\000";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_PARENT_POOL[] = "5°\000°\000";
struct QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_PARENT_Entry QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 3u},
    {4u, 2u},
};
struct QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_Entry { uint16_t offset; uint8_t len; uint8_t parent; };
static const QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_Entry QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_TABLE[] AZARAC_PROGMEM = {
    {0u, 3u, 255u},
    {4u, 4u, 1u},
    {9u, 4u, 255u},
    {14u, 4u, 1u},
    {19u, 4u, 255u},
    {24u, 4u, 0u},
    {29u, 5u, 255u},
    {35u, 4u, 0u},
    {40u, 5u, 255u},
    {46u, 4u, 0u},
    {51u, 5u, 255u},
    {57u, 4u, 0u},
    {62u, 5u, 255u},
    {68u, 4u, 0u},
    {73u, 5u, 255u},
    {79u, 4u, 0u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d3_azimuth_from_centre_of_main_ellipse_to_epicentre_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_BASE || id >= QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_BASE + QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_Entry, offset));
    uint8_t n = pgm_read_byte(p + offsetof(QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_Entry, len));
    uint8_t pi = pgm_read_byte(p + offsetof(QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_Entry, parent));
    if (pi == 255u) return azarac_pgm_view(QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_POOL + off, n);
    const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_PARENT_TABLE[pi]);
    uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_PARENT_Entry, offset));
    uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_PARENT_Entry, len));
    return azarac_pgm_join(QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_POOL + off, n, QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_PARENT_POOL + poff, pn);
}
#else
inline constexpr const char* QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_TABLE[] = {
    "0°",
    "22.5°",
    "45°",
    "67.5°",
    "90°",
    "112.5°",
    "135°",
    "157.5°",
    "180°",
    "202.5°",
    "225°",
    "247.5°",
    "270°",
    "292.5°",
    "315°",
    "337.5°"
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d3_azimuth_from_centre_of_main_ellipse_to_epicentre_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_BASE || id >= QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_BASE + QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_SIZE) return std::nullopt;
    const char* s = QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_TABLE[id - QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_BASE];
    return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d3_azimuth_from_centre_of_main_ellipse_to_epicentre_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d3_azimuth_from_centre_of_main_ellipse_to_epicentre_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
