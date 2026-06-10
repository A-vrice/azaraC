#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_ex9_target_area_code
// Variable      : qzss_dcx_camf_ex9_target_area_code_ja
// Entries       : 47
// Strategy      : binary_search

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

struct QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_Entry { uint64_t id; std::string_view label; };
inline constexpr QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_Entry QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_TABLE[] = {
    {1u, std::string_view{"北海道", 9}},

    {2u, std::string_view{"青森県", 9}},

    {4u, std::string_view{"岩手県", 9}},

    {8u, std::string_view{"宮城県", 9}},

    {16u, std::string_view{"秋田県", 9}},

    {32u, std::string_view{"山形県", 9}},

    {64u, std::string_view{"福島県", 9}},

    {128u, std::string_view{"茨城県", 9}},

    {256u, std::string_view{"栃木県", 9}},

    {512u, std::string_view{"群馬県", 9}},

    {1024u, std::string_view{"埼玉県", 9}},

    {2048u, std::string_view{"千葉県", 9}},

    {4096u, std::string_view{"東京都", 9}},

    {8192u, std::string_view{"神奈川県", 12}},

    {16384u, std::string_view{"新潟県", 9}},

    {32768u, std::string_view{"富山県", 9}},

    {65536u, std::string_view{"石川県", 9}},

    {131072u, std::string_view{"福井県", 9}},

    {262144u, std::string_view{"山梨県", 9}},

    {524288u, std::string_view{"長野県", 9}},

    {1048576u, std::string_view{"岐阜県", 9}},

    {2097152u, std::string_view{"静岡県", 9}},

    {4194304u, std::string_view{"愛知県", 9}},

    {8388608u, std::string_view{"三重県", 9}},

    {16777216u, std::string_view{"滋賀県", 9}},

    {33554432u, std::string_view{"京都府", 9}},

    {67108864u, std::string_view{"大阪府", 9}},

    {134217728u, std::string_view{"兵庫県", 9}},

    {268435456u, std::string_view{"奈良県", 9}},

    {536870912u, std::string_view{"和歌山県", 12}},

    {1073741824u, std::string_view{"鳥取県", 9}},

    {2147483648u, std::string_view{"島根県", 9}},

    {4294967296u, std::string_view{"岡山県", 9}},

    {8589934592u, std::string_view{"広島県", 9}},

    {17179869184u, std::string_view{"山口県", 9}},

    {34359738368u, std::string_view{"徳島県", 9}},

    {68719476736u, std::string_view{"香川県", 9}},

    {137438953472u, std::string_view{"愛媛県", 9}},

    {274877906944u, std::string_view{"高知県", 9}},

    {549755813888u, std::string_view{"福岡県", 9}},

    {1099511627776u, std::string_view{"佐賀県", 9}},

    {2199023255552u, std::string_view{"長崎県", 9}},

    {4398046511104u, std::string_view{"熊本県", 9}},

    {8796093022208u, std::string_view{"大分県", 9}},

    {17592186044416u, std::string_view{"宮崎県", 9}},

    {35184372088832u, std::string_view{"鹿児島県", 12}},

    {70368744177664u, std::string_view{"沖縄県", 9}},
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_ex9_target_area_code_ja_lookup(uint64_t id) {
    uint8_t lo = 0, hi = 47;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_TABLE[mid].id == id) return QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_TABLE[mid].label;
        if (QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}

} // namespace def
} // namespace azaraC
