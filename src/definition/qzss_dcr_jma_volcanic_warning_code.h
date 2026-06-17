#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_volcanic_warning_code
// Variable      : qzss_dcr_jma_volcanic_warning_code
// Entries       : 15
// Strategy      : binary_search

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_VOLCANO)

struct QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_Entry { uint8_t id; std::string_view label; };
inline constexpr QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_Entry QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_TABLE[] = {
    {11u, std::string_view{"レベル1(活火山であることに留意)", 45}},

    {12u, std::string_view{"レベル2(火口周辺規制)", 30}},

    {13u, std::string_view{"レベル3(入山規制)", 24}},

    {14u, std::string_view{"レベル4(高齢者等避難)", 30}},

    {15u, std::string_view{"レベル5(避難)", 18}},

    {21u, std::string_view{"活火山であることに留意", 33}},

    {22u, std::string_view{"火口周辺危険", 18}},

    {23u, std::string_view{"入山危険", 12}},

    {24u, std::string_view{"山麓厳重警戒", 18}},

    {25u, std::string_view{"居住地域厳重警戒", 24}},

    {35u, std::string_view{"活火山であることに留意(海底火山)", 47}},

    {36u, std::string_view{"周辺海域警戒", 18}},

    {52u, std::string_view{"噴火", 6}},

    {62u, std::string_view{"噴火したもよう", 21}},

    {127u, std::string_view{"その他の防災気象情報要素", 36}},
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_volcanic_warning_code_lookup(uint8_t id) {
    uint8_t lo = 0, hi = 15;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_TABLE[mid].id == id) return QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_TABLE[mid].label;
        if (QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_volcanic_warning_code_lookup(uint8_t id) {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
