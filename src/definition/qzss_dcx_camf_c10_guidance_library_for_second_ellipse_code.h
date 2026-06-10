#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_c10_guidance_library_for_second_ellipse
// Variable      : qzss_dcx_camf_c10_guidance_library_for_second_ellipse_code
// Entries       : 19
// Strategy      : binary_search

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

struct QZSS_DCX_CAMF_C10_GUIDANCE_LIBRARY_FOR_SECOND_ELLIPSE_CODE_Entry { uint8_t id; std::string_view label; };
inline constexpr QZSS_DCX_CAMF_C10_GUIDANCE_LIBRARY_FOR_SECOND_ELLIPSE_CODE_Entry QZSS_DCX_CAMF_C10_GUIDANCE_LIBRARY_FOR_SECOND_ELLIPSE_CODE_TABLE[] = {
    {0u, std::string_view{"IC-C-01", 7}},

    {1u, std::string_view{"IC-C-02", 7}},

    {2u, std::string_view{"IC-C-03", 7}},

    {3u, std::string_view{"IC-C-04", 7}},

    {4u, std::string_view{"IC-C-05", 7}},

    {5u, std::string_view{"IC-C-06", 7}},

    {6u, std::string_view{"IC-C-07", 7}},

    {7u, std::string_view{"IC-C-08", 7}},

    {8u, std::string_view{"IC-C-09", 7}},

    {9u, std::string_view{"IC-C-10", 7}},

    {10u, std::string_view{"IC-C-11", 7}},

    {11u, std::string_view{"IC-C-12", 7}},

    {12u, std::string_view{"IC-C-13", 7}},

    {13u, std::string_view{"IC-C-14", 7}},

    {14u, std::string_view{"IC-C-15", 7}},

    {15u, std::string_view{"IC-C-16", 7}},

    {16u, std::string_view{"IC-C-17", 7}},

    {30u, std::string_view{"IC-C-31", 7}},

    {31u, std::string_view{"IC-C-32", 7}},
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_c10_guidance_library_for_second_ellipse_code_lookup(uint8_t id) {
    uint8_t lo = 0, hi = 19;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCX_CAMF_C10_GUIDANCE_LIBRARY_FOR_SECOND_ELLIPSE_CODE_TABLE[mid].id == id) return QZSS_DCX_CAMF_C10_GUIDANCE_LIBRARY_FOR_SECOND_ELLIPSE_CODE_TABLE[mid].label;
        if (QZSS_DCX_CAMF_C10_GUIDANCE_LIBRARY_FOR_SECOND_ELLIPSE_CODE_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}

} // namespace def
} // namespace azaraC
