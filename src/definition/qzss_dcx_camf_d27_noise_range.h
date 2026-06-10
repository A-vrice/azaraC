#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d27_noise_range
// Entries       : 12
// Strategy      : array

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_D27_NOISE_RANGE_TABLE[] = {
    std::string_view{"40 < dB ≤ 45", 14},
    std::string_view{"45 < dB ≤ 50", 14},
    std::string_view{"50 < dB ≤ 60", 14},
    std::string_view{"60 < dB ≤ 70", 14},
    std::string_view{"70 < dB ≤ 80 (loud)", 21},
    std::string_view{"80 < dB ≤ 90 (very loud)", 26},
    std::string_view{"90 < dB ≤ 100 (very loud)", 27},
    std::string_view{"100 < dB ≤ 110 (very loud)", 28},
    std::string_view{"110 < dB ≤ 120 (extremely loud)", 33},
    std::string_view{"120 < dB ≤ 130 (extremely loud)", 33},
    std::string_view{"130 < dB ≤ 140 (threshold of pain)", 36},
    std::string_view{"dB > 140 (pain)", 15}
};
inline constexpr uint8_t QZSS_DCX_CAMF_D27_NOISE_RANGE_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D27_NOISE_RANGE_SIZE = 12;
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d27_noise_range_lookup(uint8_t id) {
    if (id < QZSS_DCX_CAMF_D27_NOISE_RANGE_BASE || id >= QZSS_DCX_CAMF_D27_NOISE_RANGE_BASE + QZSS_DCX_CAMF_D27_NOISE_RANGE_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_D27_NOISE_RANGE_TABLE[id - QZSS_DCX_CAMF_D27_NOISE_RANGE_BASE];
}

} // namespace def
} // namespace azaraC
