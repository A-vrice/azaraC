#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d4_vector_length_between_centre_of_main_ellipse_and_epicentre
// Entries       : 16
// Strategy      : array

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_TABLE[] = {
    std::string_view{"0.25", 4},
    std::string_view{"0.5", 3},
    std::string_view{"0.75", 4},
    std::string_view{"1", 1},
    std::string_view{"2", 1},
    std::string_view{"3", 1},
    std::string_view{"5", 1},
    std::string_view{"10", 2},
    std::string_view{"20", 2},
    std::string_view{"30", 2},
    std::string_view{"40", 2},
    std::string_view{"50", 2},
    std::string_view{"70", 2},
    std::string_view{"100", 3},
    std::string_view{"150", 3},
    std::string_view{"200", 3}
};
inline constexpr uint8_t QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_SIZE = 16;
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d4_vector_length_between_centre_of_main_ellipse_and_epicentre_lookup(uint8_t id) {
    if (id < QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_BASE || id >= QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_BASE + QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_TABLE[id - QZSS_DCX_CAMF_D4_VECTOR_LENGTH_BETWEEN_CENTRE_OF_MAIN_ELLIPSE_AND_EPICENTRE_BASE];
}

} // namespace def
} // namespace azaraC
