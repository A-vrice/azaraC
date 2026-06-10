#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d14_snow_depth
// Entries       : 31
// Strategy      : array

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_D14_SNOW_DEPTH_TABLE[] = {
    std::string_view{"0cm < daily snow depth ≤ 20cm", 31},
    std::string_view{"20cm < daily snow depth ≤ 40cm", 32},
    std::string_view{"40cm < daily snow depth ≤ 60cm", 32},
    std::string_view{"60cm < daily snow depth ≤ 80cm", 32},
    std::string_view{"80cm < daily snow depth ≤ 100cm", 33},
    std::string_view{"100cm < daily snow depth ≤ 120cm", 34},
    std::string_view{"120cm < daily snow depth ≤ 140cm", 34},
    std::string_view{"140cm < daily snow depth ≤ 160cm", 34},
    std::string_view{"160cm < daily snow depth ≤ 180cm", 34},
    std::string_view{"180cm < daily snow depth ≤ 200cm", 34},
    std::string_view{"200cm < daily snow depth ≤ 220cm", 34},
    std::string_view{"220cm < daily snow depth ≤ 240cm", 34},
    std::string_view{"240cm < daily snow depth ≤ 260cm", 34},
    std::string_view{"260cm < daily snow depth ≤ 280cm", 34},
    std::string_view{"280cm < daily snow depth ≤ 300cm", 34},
    std::string_view{"300cm < daily snow depth ≤ 320cm", 34},
    std::string_view{"320cm < daily snow depth ≤ 340cm", 34},
    std::string_view{"340cm < daily snow depth ≤ 360cm", 34},
    std::string_view{"360cm < daily snow depth ≤ 380cm", 34},
    std::string_view{"380cm < daily snow depth ≤ 400cm", 34},
    std::string_view{"400cm < daily snow depth ≤ 420cm", 34},
    std::string_view{"420cm < daily snow depth ≤ 440cm", 34},
    std::string_view{"440cm < daily snow depth ≤ 460cm", 34},
    std::string_view{"460cm < daily snow depth ≤ 480cm", 34},
    std::string_view{"480cm < daily snow depth ≤ 500cm", 34},
    std::string_view{"500cm < daily snow depth ≤ 520cm", 34},
    std::string_view{"520cm < daily snow depth ≤ 540cm", 34},
    std::string_view{"540cm < daily snow depth ≤ 560cm", 34},
    std::string_view{"560cm < daily snow depth ≤ 580cm", 34},
    std::string_view{"580cm < daily snow depth ≤ 600cm", 34},
    std::string_view{"daily snow depth > 600cm", 24}
};
inline constexpr uint8_t QZSS_DCX_CAMF_D14_SNOW_DEPTH_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D14_SNOW_DEPTH_SIZE = 31;
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d14_snow_depth_lookup(uint8_t id) {
    if (id < QZSS_DCX_CAMF_D14_SNOW_DEPTH_BASE || id >= QZSS_DCX_CAMF_D14_SNOW_DEPTH_BASE + QZSS_DCX_CAMF_D14_SNOW_DEPTH_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_D14_SNOW_DEPTH_TABLE[id - QZSS_DCX_CAMF_D14_SNOW_DEPTH_BASE];
}

} // namespace def
} // namespace azaraC
