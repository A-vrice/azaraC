#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d26_number_of_cases_per_100000_inhabitants
// Entries       : 21
// Strategy      : array

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_TABLE[] = {
    std::string_view{"0 - 9", 5},
    std::string_view{"10 - 20", 7},
    std::string_view{"21 - 50", 7},
    std::string_view{"51 - 70", 7},
    std::string_view{"71 - 100", 8},
    std::string_view{"101- 125", 8},
    std::string_view{"126 - 150", 9},
    std::string_view{"151 - 175", 9},
    std::string_view{"176 - 200", 9},
    std::string_view{"201 - 250", 9},
    std::string_view{"251 - 300", 9},
    std::string_view{"301 - 350", 9},
    std::string_view{"351 - 400", 9},
    std::string_view{"401 - 450", 9},
    std::string_view{"451 - 500", 9},
    std::string_view{"501 - 750", 9},
    std::string_view{"751 - 1000", 10},
    std::string_view{"> 1000", 6},
    std::string_view{"> 2000", 6},
    std::string_view{"> 3000", 6},
    std::string_view{"> 5000", 6}
};
inline constexpr uint8_t QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_SIZE = 21;
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d26_number_of_cases_per_100000_inhabitants_lookup(uint8_t id) {
    if (id < QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_BASE || id >= QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_BASE + QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_TABLE[id - QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_BASE];
}

} // namespace def
} // namespace azaraC
