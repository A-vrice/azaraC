#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_marine_forecast_region
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

#if (AZARAC_ENABLE_MARINE)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_FORECAST_REGION_POOL[] = "日本海北部及びオホーツク海南部\000サハリン東方海上\000サハリン西方海上\000網走沖\000宗谷海峡\000北海道西方海上\000北海道南方及び東方海上\000北海道東方海上\000釧路沖\000日高沖\000津軽海峡\000檜山津軽沖\000三陸沖\000三陸沖東部\000三陸沖西部\000関東海域\000関東海域北部\000関東海域南部\000日本海中部\000沿海州南部沖\000秋田沖\000佐渡沖\000能登沖\000東海海域\000東海海域東部\000東海海域西部\000東海海域南部\000四国沖及び瀬戸内海\000瀬戸内海\000四国沖北部\000四国沖南部\000日本海西部\000日本海北西部\000山陰沖東部及び若狭湾付近\000山陰沖西部\000対馬海峡\000九州西方海上\000済州島西海上\000長崎西海上\000女島南西海上\000九州南方海上及び日向灘\000日向灘\000鹿児島海域\000奄美海域\000沖縄海域\000東シナ海南部\000沖縄東方海上\000沖縄南方海上\000その他の地方海上予報区\000";
struct QZSS_DCR_JMA_MARINE_FORECAST_REGION_Entry { uint16_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_MARINE_FORECAST_REGION_Entry QZSS_DCR_JMA_MARINE_FORECAST_REGION_TABLE[] AZARAC_PROGMEM = {
    {1000u, 0u, 45u},
    {1010u, 46u, 24u},
    {1020u, 71u, 24u},
    {1030u, 96u, 9u},
    {1040u, 106u, 12u},
    {1050u, 119u, 21u},
    {1100u, 141u, 33u},
    {1110u, 175u, 21u},
    {1120u, 197u, 9u},
    {1130u, 207u, 9u},
    {1140u, 217u, 12u},
    {1150u, 230u, 15u},
    {2000u, 246u, 9u},
    {2010u, 256u, 15u},
    {2020u, 272u, 15u},
    {3000u, 288u, 12u},
    {3010u, 301u, 18u},
    {3020u, 320u, 18u},
    {3100u, 339u, 15u},
    {3110u, 355u, 18u},
    {3120u, 374u, 9u},
    {3130u, 384u, 9u},
    {3140u, 394u, 9u},
    {3200u, 404u, 12u},
    {3210u, 417u, 18u},
    {3220u, 436u, 18u},
    {3230u, 455u, 18u},
    {4000u, 474u, 27u},
    {4010u, 502u, 12u},
    {4020u, 515u, 15u},
    {4030u, 531u, 15u},
    {4100u, 547u, 15u},
    {4110u, 563u, 18u},
    {4120u, 582u, 36u},
    {4130u, 619u, 15u},
    {5000u, 635u, 12u},
    {5100u, 648u, 18u},
    {5110u, 667u, 18u},
    {5120u, 686u, 15u},
    {5130u, 702u, 18u},
    {5200u, 721u, 33u},
    {5210u, 755u, 9u},
    {5220u, 765u, 15u},
    {5230u, 781u, 12u},
    {6000u, 794u, 12u},
    {6010u, 807u, 18u},
    {6020u, 826u, 18u},
    {6030u, 845u, 18u},
    {10000u, 864u, 33u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_marine_forecast_region_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 49;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_MARINE_FORECAST_REGION_TABLE[mid]);
        uint16_t eid = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_MARINE_FORECAST_REGION_Entry, id));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_MARINE_FORECAST_REGION_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_MARINE_FORECAST_REGION_Entry, len));
            return azarac_pgm_view(QZSS_DCR_JMA_MARINE_FORECAST_REGION_POOL + off, n);
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
