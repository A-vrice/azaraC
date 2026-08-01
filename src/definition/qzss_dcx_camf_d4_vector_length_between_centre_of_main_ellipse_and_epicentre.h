#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_d4_vector_length_between_centre_of_main_ellipse_and_epicentre
// Variable      : qzss_dcx_camf_d4_vector_length_between_centre_of_main_ellipse_and_epicentre
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

inline constexpr uint8_t QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_SIZE = 16;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_POOL[] = "0.25\00.5\00.75\01\02\03\05\010\020\030\040\050\070\0100\0150\0200\0";
struct QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_Entry QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_TABLE[] AZARAC_PROGMEM = {
    {0u, 4u},
    {5u, 3u},
    {9u, 4u},
    {14u, 1u},
    {16u, 1u},
    {18u, 1u},
    {20u, 1u},
    {22u, 2u},
    {25u, 2u},
    {28u, 2u},
    {31u, 2u},
    {34u, 2u},
    {37u, 2u},
    {40u, 3u},
    {44u, 3u},
    {48u, 3u}
};
[[nodiscard]] inline const char* qzss_dcx_camf_d4_vector_length_between_centre_of_main_ellipse_and_epicentre_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_BASE || id >= QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_BASE + QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_SIZE) return nullptr;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_Entry, len));
    if (n == 0) return nullptr;
    return azarac_pgm_copy(QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_POOL + off);
}
#else
inline constexpr const char* QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_TABLE[] = {
    "0.25",
    "0.5",
    "0.75",
    "1",
    "2",
    "3",
    "5",
    "10",
    "20",
    "30",
    "40",
    "50",
    "70",
    "100",
    "150",
    "200"
};
[[nodiscard]] inline constexpr const char* qzss_dcx_camf_d4_vector_length_between_centre_of_main_ellipse_and_epicentre_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_BASE || id >= QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_BASE + QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_SIZE) return nullptr;
    return QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_TABLE[id - QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_BASE];
}
#endif

#else

[[nodiscard]] inline constexpr const char* qzss_dcx_camf_d4_vector_length_between_centre_of_main_ellipse_and_epicentre_lookup(uint8_t id) noexcept {
    (void)id;
    return nullptr;
}

#endif

} // namespace def
} // namespace azaraC
