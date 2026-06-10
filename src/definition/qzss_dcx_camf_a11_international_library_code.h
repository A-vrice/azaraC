#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_a11_international_library
// Variable      : qzss_dcx_camf_a11_international_library_code
// Entries       : 32
// Strategy      : array

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_TABLE[] = {
    std::string_view{"IC-A-01", 7},
    std::string_view{"IC-A-02", 7},
    std::string_view{"IC-A-03", 7},
    std::string_view{"IC-A-04", 7},
    std::string_view{"IC-A-05", 7},
    std::string_view{"IC-A-06", 7},
    std::string_view{"IC-A-07", 7},
    std::string_view{"IC-A-08", 7},
    std::string_view{"IC-A-09", 7},
    std::string_view{"IC-A-10", 7},
    std::string_view{"IC-A-11", 7},
    std::string_view{"IC-A-12", 7},
    std::string_view{"IC-A-13", 7},
    std::string_view{"IC-A-14", 7},
    std::string_view{"IC-A-15", 7},
    std::string_view{"IC-A-16", 7},
    std::string_view{"IC-A-17", 7},
    std::string_view{"IC-A-18", 7},
    std::string_view{"IC-A-19", 7},
    std::string_view{"IC-A-20", 7},
    std::string_view{"IC-A-21", 7},
    std::string_view{"IC-A-22", 7},
    std::string_view{"IC-A-23", 7},
    std::string_view{"IC-A-24", 7},
    std::string_view{"IC-A-25", 7},
    std::string_view{"IC-A-26", 7},
    std::string_view{"IC-A-27", 7},
    std::string_view{"IC-A-28", 7},
    std::string_view{"IC-A-29", 7},
    std::string_view{"IC-A-30", 7},
    std::string_view{"IC-A-31", 7},
    std::string_view{"IC-A-32", 7}
};
inline constexpr uint8_t QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_SIZE = 32;
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a11_international_library_code_lookup(uint8_t id) {
    if (id < QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_BASE || id >= QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_BASE + QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_TABLE[id - QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_BASE];
}

} // namespace def
} // namespace azaraC
