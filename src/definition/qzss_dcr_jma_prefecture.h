#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_prefecture
// Variable      : qzss_dcr_jma_prefecture
// Entries       : 47
// Strategy      : array

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_SEISMIC)

inline constexpr std::optional<std::string_view> QZSS_DCR_JMA_PREFECTURE_TABLE[] = {
    std::string_view{"北海道", 9},
    std::string_view{"青森県", 9},
    std::string_view{"岩手県", 9},
    std::string_view{"宮城県", 9},
    std::string_view{"秋田県", 9},
    std::string_view{"山形県", 9},
    std::string_view{"福島県", 9},
    std::string_view{"茨城県", 9},
    std::string_view{"栃木県", 9},
    std::string_view{"群馬県", 9},
    std::string_view{"埼玉県", 9},
    std::string_view{"千葉県", 9},
    std::string_view{"東京都", 9},
    std::string_view{"神奈川県", 12},
    std::string_view{"新潟県", 9},
    std::string_view{"富山県", 9},
    std::string_view{"石川県", 9},
    std::string_view{"福井県", 9},
    std::string_view{"山梨県", 9},
    std::string_view{"長野県", 9},
    std::string_view{"岐阜県", 9},
    std::string_view{"静岡県", 9},
    std::string_view{"愛知県", 9},
    std::string_view{"三重県", 9},
    std::string_view{"滋賀県", 9},
    std::string_view{"京都府", 9},
    std::string_view{"大阪府", 9},
    std::string_view{"兵庫県", 9},
    std::string_view{"奈良県", 9},
    std::string_view{"和歌山県", 12},
    std::string_view{"鳥取県", 9},
    std::string_view{"島根県", 9},
    std::string_view{"岡山県", 9},
    std::string_view{"広島県", 9},
    std::string_view{"山口県", 9},
    std::string_view{"徳島県", 9},
    std::string_view{"香川県", 9},
    std::string_view{"愛媛県", 9},
    std::string_view{"高知県", 9},
    std::string_view{"福岡県", 9},
    std::string_view{"佐賀県", 9},
    std::string_view{"長崎県", 9},
    std::string_view{"熊本県", 9},
    std::string_view{"大分県", 9},
    std::string_view{"宮崎県", 9},
    std::string_view{"鹿児島県", 12},
    std::string_view{"沖縄県", 9}
};
inline constexpr uint8_t QZSS_DCR_JMA_PREFECTURE_BASE = 1;
inline constexpr uint8_t QZSS_DCR_JMA_PREFECTURE_SIZE = 47;
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_prefecture_lookup(uint8_t id) {
    if (id < QZSS_DCR_JMA_PREFECTURE_BASE || id >= QZSS_DCR_JMA_PREFECTURE_BASE + QZSS_DCR_JMA_PREFECTURE_SIZE) return std::nullopt;
    return QZSS_DCR_JMA_PREFECTURE_TABLE[id - QZSS_DCR_JMA_PREFECTURE_BASE];
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_prefecture_lookup(uint8_t id) {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
