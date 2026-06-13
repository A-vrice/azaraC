#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_ex9_target_area_code
// Variable      : qzss_dcx_camf_ex9_target_area_code_en
// Entries       : 47
// Strategy      : binary_search

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_LANG_EN)

struct QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_Entry { uint64_t id; std::string_view label; };
inline constexpr QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_Entry QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_TABLE[] = {
    {1u, std::string_view{"Hokkaido", 8}},

    {2u, std::string_view{"Aomori", 6}},

    {4u, std::string_view{"Iwate", 5}},

    {8u, std::string_view{"Miyagi", 6}},

    {16u, std::string_view{"Akita", 5}},

    {32u, std::string_view{"Yamagata", 8}},

    {64u, std::string_view{"Fukushima", 9}},

    {128u, std::string_view{"Ibaraki", 7}},

    {256u, std::string_view{"Tochigi", 7}},

    {512u, std::string_view{"Gunma", 5}},

    {1024u, std::string_view{"Saitama", 7}},

    {2048u, std::string_view{"Chiba", 5}},

    {4096u, std::string_view{"Tokyo", 5}},

    {8192u, std::string_view{"Kanagawa", 8}},

    {16384u, std::string_view{"Niigata", 7}},

    {32768u, std::string_view{"Toyama", 6}},

    {65536u, std::string_view{"Ishikawa", 8}},

    {131072u, std::string_view{"Fukui", 5}},

    {262144u, std::string_view{"Yamanashi", 9}},

    {524288u, std::string_view{"Nagano", 6}},

    {1048576u, std::string_view{"Gifu", 4}},

    {2097152u, std::string_view{"Shizuoka", 8}},

    {4194304u, std::string_view{"Aichi", 5}},

    {8388608u, std::string_view{"Mie", 3}},

    {16777216u, std::string_view{"Shiga", 5}},

    {33554432u, std::string_view{"Kyoto", 5}},

    {67108864u, std::string_view{"Osaka", 5}},

    {134217728u, std::string_view{"Hyogo", 5}},

    {268435456u, std::string_view{"Nara", 4}},

    {536870912u, std::string_view{"Wakayama", 8}},

    {1073741824u, std::string_view{"Tottori", 7}},

    {2147483648u, std::string_view{"Shimane", 7}},

    {4294967296u, std::string_view{"Okayama", 7}},

    {8589934592u, std::string_view{"Hiroshima", 9}},

    {17179869184u, std::string_view{"Yamaguchi", 9}},

    {34359738368u, std::string_view{"Tokushima", 9}},

    {68719476736u, std::string_view{"Kagawa", 6}},

    {137438953472u, std::string_view{"Ehime", 5}},

    {274877906944u, std::string_view{"Kochi", 5}},

    {549755813888u, std::string_view{"Fukuoka", 7}},

    {1099511627776u, std::string_view{"Saga", 4}},

    {2199023255552u, std::string_view{"Nagasaki", 8}},

    {4398046511104u, std::string_view{"Kumamoto", 8}},

    {8796093022208u, std::string_view{"Oita", 4}},

    {17592186044416u, std::string_view{"Miyazaki", 8}},

    {35184372088832u, std::string_view{"Kagoshima", 9}},

    {70368744177664u, std::string_view{"Okinawa", 7}},
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_ex9_target_area_code_en_lookup(uint64_t id) {
    uint8_t lo = 0, hi = 47;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_TABLE[mid].id == id) return QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_TABLE[mid].label;
        if (QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_ex9_target_area_code_en_lookup(uint64_t id) {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
