#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d29_outage_estimated_duration
// Entries       : 13
// Strategy      : array

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_TABLE[] = {
    std::string_view{"0 < duration < 30 min", 21},
    std::string_view{"30 min ≤ duration < 45 min", 28},
    std::string_view{"45 min ≤ duration < 1 h", 25},
    std::string_view{"1 h ≤ duration < 1 h 30 min", 29},
    std::string_view{"1 h 30 min ≤ duration < 2 h", 29},
    std::string_view{"2 h ≤ duration < 3 h", 22},
    std::string_view{"3 h ≤ duration < 4 h", 22},
    std::string_view{"4 h ≤ duration < 5 h", 22},
    std::string_view{"5 h ≤ duration < 10 h", 23},
    std::string_view{"10 h ≤ duration < 24 h", 24},
    std::string_view{"24 h ≤ duration < 2 days", 26},
    std::string_view{"2 days ≤ duration < 7 days", 28},
    std::string_view{"7 days ≤ duration", 19}
};
inline constexpr uint8_t QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_SIZE = 13;
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d29_outage_estimated_duration_lookup(uint8_t id) {
    if (id < QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_BASE || id >= QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_BASE + QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_TABLE[id - QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_BASE];
}

} // namespace def
} // namespace azaraC
