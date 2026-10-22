#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.d_fields → qzss_dcx_camf_d3_azimuth_from_centre_of_main_ellipse_to_epicentre: 16 entries, strategy array
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

inline constexpr uint8_t QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_SIZE = 16;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_POOL[] = "0°\0002\00045°\0006\00090°\00011\000135°\00015\000180°\00020\000225°\00024\000270°\00029\000315°\00033\000";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_PARENT_POOL[] = "2.5°\0007.5°\000";
struct QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_PARENT_Entry { uint16_t offset; };
static const QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_PARENT_Entry QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {6u},
};
struct QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_Entry { uint16_t offset; uint8_t parent; };
static const QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_Entry QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_TABLE[] AZARAC_PROGMEM = {
    {0u, 255u},
    {4u, 0u},
    {6u, 255u},
    {11u, 1u},
    {13u, 255u},
    {18u, 0u},
    {21u, 255u},
    {27u, 1u},
    {30u, 255u},
    {36u, 0u},
    {39u, 255u},
    {45u, 1u},
    {48u, 255u},
    {54u, 0u},
    {57u, 255u},
    {63u, 1u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d3_azimuth_from_centre_of_main_ellipse_to_epicentre_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_BASE || id >= QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_BASE + QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_SIZE) return std::nullopt;
    azarac_pgm_ptr p = AZARAC_PGM_PTR(QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_TABLE) + static_cast<size_t>(id - 0u) * sizeof(QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_Entry);
    uint16_t off = azarac_read_word(p, offsetof(QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_Entry, offset));
    uint8_t pi = azarac_read_byte(p, offsetof(QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_Entry, parent));
    if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_POOL) + off);
    azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_PARENT_Entry);
    uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_PARENT_Entry, offset));
    return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_POOL) + off, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_PARENT_POOL) + poff);
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
