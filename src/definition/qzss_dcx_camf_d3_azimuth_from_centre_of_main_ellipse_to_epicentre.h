#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_d3_azimuth_from_centre_of_main_ellipse_to_epicentre
// Variable      : qzss_dcx_camf_d3_azimuth_from_centre_of_main_ellipse_to_epicentre
// Entries       : 16
// Strategy      : array

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"
#include "../internal/FlashString.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_DCX_CAMF)

inline constexpr uint8_t QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_SIZE = 16;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_POOL[] = "0.0\022.5\045.0\067.5\090.0\0112.5\0135.0\0157.5\0180.0\0202.5\0225.0\0247.5\0270.0\0292.5\0315.0\0337.5\0";
struct QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_Entry QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_TABLE[] AZARAC_PROGMEM = {
    {0u, 3u},
    {4u, 4u},
    {9u, 4u},
    {14u, 4u},
    {19u, 4u},
    {24u, 5u},
    {30u, 5u},
    {36u, 5u},
    {42u, 5u},
    {48u, 5u},
    {54u, 5u},
    {60u, 5u},
    {66u, 5u},
    {72u, 5u},
    {78u, 5u},
    {84u, 5u}
};
[[nodiscard]] inline const char* qzss_dcx_camf_d3_azimuth_from_centre_of_main_ellipse_to_epicentre_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_BASE || id >= QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_BASE + QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_SIZE) return nullptr;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_Entry, len));
    if (n == 0) return nullptr;
    return azarac_pgm_copy(QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_POOL + off);
}
#else
inline constexpr const char* QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_TABLE[] = {
    "0.0",
    "22.5",
    "45.0",
    "67.5",
    "90.0",
    "112.5",
    "135.0",
    "157.5",
    "180.0",
    "202.5",
    "225.0",
    "247.5",
    "270.0",
    "292.5",
    "315.0",
    "337.5"
};
[[nodiscard]] inline constexpr const char* qzss_dcx_camf_d3_azimuth_from_centre_of_main_ellipse_to_epicentre_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_BASE || id >= QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_BASE + QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_SIZE) return nullptr;
    return QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_TABLE[id - QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_BASE];
}
#endif

#else

[[nodiscard]] inline constexpr const char* qzss_dcx_camf_d3_azimuth_from_centre_of_main_ellipse_to_epicentre_lookup(uint8_t id) noexcept {
    (void)id;
    return nullptr;
}

#endif

} // namespace def
} // namespace azaraC
