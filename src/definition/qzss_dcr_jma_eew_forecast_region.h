#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_eew_forecast_region
// Variable      : qzss_dcr_jma_eew_forecast_region
// Entries       : 71
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

#if (AZARAC_ENABLE_EEW)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_EEW_FORECAST_REGION_POOL[] = "北海道道央\000北海道道南\000北海道道北\000北海道道東\000青森\000岩手\000宮城\000秋田\000山形\000福島\000茨城\000栃木\000群馬\000埼玉\000千葉\000東京\000伊豆諸島\000小笠原\000神奈川\000新潟\000富山\000石川\000福井\000山梨\000長野\000岐阜\000静岡\000愛知\000三重\000滋賀\000京都\000大阪\000兵庫\000奈良\000和歌山\000鳥取\000島根\000岡山\000広島\000山口\000徳島\000香川\000愛媛\000高知\000福岡\000佐賀\000長崎\000熊本\000大分\000宮崎\000鹿児島\000奄美(群島)\000沖縄本島\000大東島\000宮古島\000八重山\000北海道\000東北\000関東\000伊豆諸島\000小笠原\000北陸\000甲信\000東海\000近畿\000中国\000四国\000九州\000奄美(群島)\000沖縄\000その他の府県予報区および地方予報区\000";
struct QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry { uint8_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[] AZARAC_PROGMEM = {
    {1u, 0u, 15u},
    {2u, 16u, 15u},
    {3u, 32u, 15u},
    {4u, 48u, 15u},
    {5u, 64u, 6u},
    {6u, 71u, 6u},
    {7u, 78u, 6u},
    {8u, 85u, 6u},
    {9u, 92u, 6u},
    {10u, 99u, 6u},
    {11u, 106u, 6u},
    {12u, 113u, 6u},
    {13u, 120u, 6u},
    {14u, 127u, 6u},
    {15u, 134u, 6u},
    {16u, 141u, 6u},
    {17u, 148u, 12u},
    {18u, 161u, 9u},
    {19u, 171u, 9u},
    {20u, 181u, 6u},
    {21u, 188u, 6u},
    {22u, 195u, 6u},
    {23u, 202u, 6u},
    {24u, 209u, 6u},
    {25u, 216u, 6u},
    {26u, 223u, 6u},
    {27u, 230u, 6u},
    {28u, 237u, 6u},
    {29u, 244u, 6u},
    {30u, 251u, 6u},
    {31u, 258u, 6u},
    {32u, 265u, 6u},
    {33u, 272u, 6u},
    {34u, 279u, 6u},
    {35u, 286u, 9u},
    {36u, 296u, 6u},
    {37u, 303u, 6u},
    {38u, 310u, 6u},
    {39u, 317u, 6u},
    {40u, 324u, 6u},
    {41u, 331u, 6u},
    {42u, 338u, 6u},
    {43u, 345u, 6u},
    {44u, 352u, 6u},
    {45u, 359u, 6u},
    {46u, 366u, 6u},
    {47u, 373u, 6u},
    {48u, 380u, 6u},
    {49u, 387u, 6u},
    {50u, 394u, 6u},
    {51u, 401u, 9u},
    {52u, 411u, 14u},
    {53u, 426u, 12u},
    {54u, 439u, 9u},
    {55u, 449u, 9u},
    {56u, 459u, 9u},
    {57u, 469u, 9u},
    {58u, 479u, 6u},
    {59u, 486u, 6u},
    {60u, 493u, 12u},
    {61u, 506u, 9u},
    {62u, 516u, 6u},
    {63u, 523u, 6u},
    {64u, 530u, 6u},
    {65u, 537u, 6u},
    {66u, 544u, 6u},
    {67u, 551u, 6u},
    {68u, 558u, 6u},
    {69u, 565u, 14u},
    {70u, 580u, 6u},
    {80u, 587u, 51u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 71;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry, len));
            return azarac_pgm_view(QZSS_DCR_JMA_EEW_FORECAST_REGION_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry { uint8_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[] = {
    {1u, "北海道道央"},
    {2u, "北海道道南"},
    {3u, "北海道道北"},
    {4u, "北海道道東"},
    {5u, "青森"},
    {6u, "岩手"},
    {7u, "宮城"},
    {8u, "秋田"},
    {9u, "山形"},
    {10u, "福島"},
    {11u, "茨城"},
    {12u, "栃木"},
    {13u, "群馬"},
    {14u, "埼玉"},
    {15u, "千葉"},
    {16u, "東京"},
    {17u, "伊豆諸島"},
    {18u, "小笠原"},
    {19u, "神奈川"},
    {20u, "新潟"},
    {21u, "富山"},
    {22u, "石川"},
    {23u, "福井"},
    {24u, "山梨"},
    {25u, "長野"},
    {26u, "岐阜"},
    {27u, "静岡"},
    {28u, "愛知"},
    {29u, "三重"},
    {30u, "滋賀"},
    {31u, "京都"},
    {32u, "大阪"},
    {33u, "兵庫"},
    {34u, "奈良"},
    {35u, "和歌山"},
    {36u, "鳥取"},
    {37u, "島根"},
    {38u, "岡山"},
    {39u, "広島"},
    {40u, "山口"},
    {41u, "徳島"},
    {42u, "香川"},
    {43u, "愛媛"},
    {44u, "高知"},
    {45u, "福岡"},
    {46u, "佐賀"},
    {47u, "長崎"},
    {48u, "熊本"},
    {49u, "大分"},
    {50u, "宮崎"},
    {51u, "鹿児島"},
    {52u, "奄美(群島)"},
    {53u, "沖縄本島"},
    {54u, "大東島"},
    {55u, "宮古島"},
    {56u, "八重山"},
    {57u, "北海道"},
    {58u, "東北"},
    {59u, "関東"},
    {60u, "伊豆諸島"},
    {61u, "小笠原"},
    {62u, "北陸"},
    {63u, "甲信"},
    {64u, "東海"},
    {65u, "近畿"},
    {66u, "中国"},
    {67u, "四国"},
    {68u, "九州"},
    {69u, "奄美(群島)"},
    {70u, "沖縄"},
    {80u, "その他の府県予報区および地方予報区"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 71;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
