#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_marine_forecast_region
// Variable      : qzss_dcr_jma_marine_forecast_region
// Entries       : 49
// Strategy      : binary_search

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_MARINE)

struct QZSS_DCR_JMA_MARINE_FORECAST_REGION_Entry { uint16_t id; std::string_view label; };
inline constexpr QZSS_DCR_JMA_MARINE_FORECAST_REGION_Entry QZSS_DCR_JMA_MARINE_FORECAST_REGION_TABLE[] = {
    {1000u, std::string_view{"日本海北部及びオホーツク海南部", 45}},

    {1010u, std::string_view{"サハリン東方海上", 24}},

    {1020u, std::string_view{"サハリン西方海上", 24}},

    {1030u, std::string_view{"網走沖", 9}},

    {1040u, std::string_view{"宗谷海峡", 12}},

    {1050u, std::string_view{"北海道西方海上", 21}},

    {1100u, std::string_view{"北海道南方及び東方海上", 33}},

    {1110u, std::string_view{"北海道東方海上", 21}},

    {1120u, std::string_view{"釧路沖", 9}},

    {1130u, std::string_view{"日高沖", 9}},

    {1140u, std::string_view{"津軽海峡", 12}},

    {1150u, std::string_view{"檜山津軽沖", 15}},

    {2000u, std::string_view{"三陸沖", 9}},

    {2010u, std::string_view{"三陸沖東部", 15}},

    {2020u, std::string_view{"三陸沖西部", 15}},

    {3000u, std::string_view{"関東海域", 12}},

    {3010u, std::string_view{"関東海域北部", 18}},

    {3020u, std::string_view{"関東海域南部", 18}},

    {3100u, std::string_view{"日本海中部", 15}},

    {3110u, std::string_view{"沿海州南部沖", 18}},

    {3120u, std::string_view{"秋田沖", 9}},

    {3130u, std::string_view{"佐渡沖", 9}},

    {3140u, std::string_view{"能登沖", 9}},

    {3200u, std::string_view{"東海海域", 12}},

    {3210u, std::string_view{"東海海域東部", 18}},

    {3220u, std::string_view{"東海海域西部", 18}},

    {3230u, std::string_view{"東海海域南部", 18}},

    {4000u, std::string_view{"四国沖及び瀬戸内海", 27}},

    {4010u, std::string_view{"瀬戸内海", 12}},

    {4020u, std::string_view{"四国沖北部", 15}},

    {4030u, std::string_view{"四国沖南部", 15}},

    {4100u, std::string_view{"日本海西部", 15}},

    {4110u, std::string_view{"日本海北西部", 18}},

    {4120u, std::string_view{"山陰沖東部及び若狭湾付近", 36}},

    {4130u, std::string_view{"山陰沖西部", 15}},

    {5000u, std::string_view{"対馬海峡", 12}},

    {5100u, std::string_view{"九州西方海上", 18}},

    {5110u, std::string_view{"済州島西海上", 18}},

    {5120u, std::string_view{"長崎西海上", 15}},

    {5130u, std::string_view{"女島南西海上", 18}},

    {5200u, std::string_view{"九州南方海上及び日向灘", 33}},

    {5210u, std::string_view{"日向灘", 9}},

    {5220u, std::string_view{"鹿児島海域", 15}},

    {5230u, std::string_view{"奄美海域", 12}},

    {6000u, std::string_view{"沖縄海域", 12}},

    {6010u, std::string_view{"東シナ海南部", 18}},

    {6020u, std::string_view{"沖縄東方海上", 18}},

    {6030u, std::string_view{"沖縄南方海上", 18}},

    {10000u, std::string_view{"その他の地方海上予報区", 33}},
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_marine_forecast_region_lookup(uint16_t id) {
    uint8_t lo = 0, hi = 49;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_MARINE_FORECAST_REGION_TABLE[mid].id == id) return QZSS_DCR_JMA_MARINE_FORECAST_REGION_TABLE[mid].label;
        if (QZSS_DCR_JMA_MARINE_FORECAST_REGION_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_marine_forecast_region_lookup(uint16_t id) {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
