#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.marine_forecast_region
// Variable      : qzss_dcr_jma_marine_forecast_region
// Entries       : 49
// Strategy      : binary_search

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#if defined(__AVR__)
#include "../internal/avr_std/cstdint"
#include "../internal/avr_std/optional"
#include "../internal/avr_std/string_view"
#else
#include <cstdint>
#include <optional>
#include <string_view>
#endif
#include "../azaraC.h"
#include "../internal/FlashString.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_MARINE) && (AZARAC_LANG_JA)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_FORECAST_REGION_POOL[] = "日本海北部及びオホーツク海南部\000サハリン\000サハリン西\000網走沖\000宗谷海峡\000北海道西\000北海道南方及び\000北海道\000釧路沖\000日高沖\000津軽海峡\000檜山津軽沖\000三陸沖\000三陸沖東部\000三陸沖\000関東\000関東海域北部\000関東海域\000日本海中部\000沿海州南部沖\000秋田沖\000佐渡沖\000能登沖\000東海海域\000東海海域東部\000東海海域西部\000東海海域南部\000四国沖及び瀬戸内海\000瀬戸内海\000四国沖北部\000四国沖\000日本海西部\000日本海北西部\000山陰沖東部及び若狭湾付近\000山陰沖\000対馬海峡\000九州西\000済州島西\000長崎西\000女島南西\000九州南方海上及び日向灘\000日向灘\000鹿児島\000奄美\000沖縄\000東シナ海\000沖縄\000沖縄南\000その他の地方海上予報区\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_FORECAST_REGION_PARENT_POOL[] = "南部\000方海上\000東方海上\000海上\000海域\000西部\000";
struct QZSS_DCR_JMA_MARINE_FORECAST_REGION_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_MARINE_FORECAST_REGION_PARENT_Entry QZSS_DCR_JMA_MARINE_FORECAST_REGION_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {7u},
    {17u},
    {30u},
    {37u},
    {44u},
};
struct QZSS_DCR_JMA_MARINE_FORECAST_REGION_Entry { uint16_t id; uint8_t parent; uint16_t offset; };
static const QZSS_DCR_JMA_MARINE_FORECAST_REGION_Entry QZSS_DCR_JMA_MARINE_FORECAST_REGION_TABLE[] AZARAC_PROGMEM = {
    {1000u, 255u, 0u},
    {1010u, 2u, 46u},
    {1020u, 1u, 59u},
    {1030u, 255u, 75u},
    {1040u, 255u, 85u},
    {1050u, 1u, 98u},
    {1100u, 2u, 111u},
    {1110u, 2u, 133u},
    {1120u, 255u, 143u},
    {1130u, 255u, 153u},
    {1140u, 255u, 163u},
    {1150u, 255u, 176u},
    {2000u, 255u, 192u},
    {2010u, 255u, 202u},
    {2020u, 5u, 218u},
    {3000u, 4u, 228u},
    {3010u, 255u, 235u},
    {3020u, 0u, 254u},
    {3100u, 255u, 267u},
    {3110u, 255u, 283u},
    {3120u, 255u, 302u},
    {3130u, 255u, 312u},
    {3140u, 255u, 322u},
    {3200u, 255u, 332u},
    {3210u, 255u, 345u},
    {3220u, 255u, 364u},
    {3230u, 255u, 383u},
    {4000u, 255u, 402u},
    {4010u, 255u, 430u},
    {4020u, 255u, 443u},
    {4030u, 0u, 459u},
    {4100u, 255u, 469u},
    {4110u, 255u, 485u},
    {4120u, 255u, 504u},
    {4130u, 5u, 541u},
    {5000u, 255u, 551u},
    {5100u, 1u, 564u},
    {5110u, 3u, 574u},
    {5120u, 3u, 587u},
    {5130u, 3u, 597u},
    {5200u, 255u, 610u},
    {5210u, 255u, 644u},
    {5220u, 4u, 654u},
    {5230u, 4u, 664u},
    {6000u, 4u, 671u},
    {6010u, 0u, 678u},
    {6020u, 2u, 691u},
    {6030u, 1u, 698u},
    {10000u, 255u, 708u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_marine_forecast_region_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 49;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        azarac_pgm_ptr ep = AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_FORECAST_REGION_TABLE) + static_cast<size_t>(mid) * sizeof(QZSS_DCR_JMA_MARINE_FORECAST_REGION_Entry);
        uint16_t eid = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_MARINE_FORECAST_REGION_Entry, id));
        if (eid == id) {
            uint16_t off = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_MARINE_FORECAST_REGION_Entry, offset));
            uint8_t pi = azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_MARINE_FORECAST_REGION_Entry, parent));
            if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_FORECAST_REGION_POOL) + off);
            azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_FORECAST_REGION_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCR_JMA_MARINE_FORECAST_REGION_PARENT_Entry);
            uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCR_JMA_MARINE_FORECAST_REGION_PARENT_Entry, offset));
            return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_FORECAST_REGION_POOL) + off, AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_FORECAST_REGION_PARENT_POOL) + poff);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_MARINE_FORECAST_REGION_Entry { uint16_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_MARINE_FORECAST_REGION_Entry QZSS_DCR_JMA_MARINE_FORECAST_REGION_TABLE[] = {
    {1000u, "日本海北部及びオホーツク海南部"},
    {1010u, "サハリン東方海上"},
    {1020u, "サハリン西方海上"},
    {1030u, "網走沖"},
    {1040u, "宗谷海峡"},
    {1050u, "北海道西方海上"},
    {1100u, "北海道南方及び東方海上"},
    {1110u, "北海道東方海上"},
    {1120u, "釧路沖"},
    {1130u, "日高沖"},
    {1140u, "津軽海峡"},
    {1150u, "檜山津軽沖"},
    {2000u, "三陸沖"},
    {2010u, "三陸沖東部"},
    {2020u, "三陸沖西部"},
    {3000u, "関東海域"},
    {3010u, "関東海域北部"},
    {3020u, "関東海域南部"},
    {3100u, "日本海中部"},
    {3110u, "沿海州南部沖"},
    {3120u, "秋田沖"},
    {3130u, "佐渡沖"},
    {3140u, "能登沖"},
    {3200u, "東海海域"},
    {3210u, "東海海域東部"},
    {3220u, "東海海域西部"},
    {3230u, "東海海域南部"},
    {4000u, "四国沖及び瀬戸内海"},
    {4010u, "瀬戸内海"},
    {4020u, "四国沖北部"},
    {4030u, "四国沖南部"},
    {4100u, "日本海西部"},
    {4110u, "日本海北西部"},
    {4120u, "山陰沖東部及び若狭湾付近"},
    {4130u, "山陰沖西部"},
    {5000u, "対馬海峡"},
    {5100u, "九州西方海上"},
    {5110u, "済州島西海上"},
    {5120u, "長崎西海上"},
    {5130u, "女島南西海上"},
    {5200u, "九州南方海上及び日向灘"},
    {5210u, "日向灘"},
    {5220u, "鹿児島海域"},
    {5230u, "奄美海域"},
    {6000u, "沖縄海域"},
    {6010u, "東シナ海南部"},
    {6020u, "沖縄東方海上"},
    {6030u, "沖縄南方海上"},
    {10000u, "その他の地方海上予報区"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_marine_forecast_region_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 49;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_MARINE_FORECAST_REGION_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_MARINE_FORECAST_REGION_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_MARINE_FORECAST_REGION_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_marine_forecast_region_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_marine_forecast_region_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
