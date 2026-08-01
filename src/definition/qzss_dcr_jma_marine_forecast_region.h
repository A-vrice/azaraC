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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_FORECAST_REGION_POOL[] = "日本海北部及びオホーツク海南部\0サハリン東方海上\0サハリン西方海上\0網走沖\0宗谷海峡\0北海道西方海上\0北海道南方及び東方海上\0北海道東方海上\0釧路沖\0日高沖\0津軽海峡\0檜山津軽沖\0三陸沖\0三陸沖東部\0三陸沖西部\0関東海域\0関東海域北部\0関東海域南部\0日本海中部\0沿海州南部沖\0秋田沖\0佐渡沖\0能登沖\0東海海域\0東海海域東部\0東海海域西部\0東海海域南部\0四国沖及び瀬戸内海\0瀬戸内海\0四国沖北部\0四国沖南部\0日本海西部\0日本海北西部\0山陰沖東部及び若狭湾付近\0山陰沖西部\0対馬海峡\0九州西方海上\0済州島西海上\0長崎西海上\0女島南西海上\0九州南方海上及び日向灘\0日向灘\0鹿児島海域\0奄美海域\0沖縄海域\0東シナ海南部\0沖縄東方海上\0沖縄南方海上\0その他の地方海上予報区\0";
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
            if (n == 0) return std::nullopt;
            return azarac_pgm_view(QZSS_DCR_JMA_MARINE_FORECAST_REGION_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_MARINE_FORECAST_REGION_Entry { uint16_t id; std::optional<std::string_view> label; };
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
    {10000u, std::string_view{"その他の地方海上予報区", 33}},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_marine_forecast_region_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 49;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_MARINE_FORECAST_REGION_TABLE[mid].id == id) return QZSS_DCR_JMA_MARINE_FORECAST_REGION_TABLE[mid].label;
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
