#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.eew_forecast_region → qzss_dcr_jma_eew_forecast_region: 71 entries, strategy binary_search
// Unknown id returns nullptr — callers MUST null-check.

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

#if (AZARAC_ENABLE_EEW) && (AZARAC_LANG_JA)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_EEW_FORECAST_REGION_POOL[] = "北海道道央\000北海道道南\000北海道道北\000北海道道東\000青森\000岩手\000宮城\000秋田\000山形\000福島\000茨城\000栃木\000群馬\000埼玉\000千葉\000東京\000伊豆諸島\000小笠原\000神奈川\000新潟\000富山\000石川\000福井\000山梨\000長野\000岐阜\000静岡\000愛知\000三重\000滋賀\000京都\000大阪\000兵庫\000奈良\000和歌山\000鳥取\000島根\000岡山\000広島\000山口\000徳島\000香川\000愛媛\000高知\000福岡\000佐賀\000長崎\000熊本\000大分\000宮崎\000鹿児島\000奄美(群島)\000沖縄本島\000大東島\000宮古島\000八重山\000北海道\000東北\000関東\000伊豆諸島\000小笠原\000北陸\000甲信\000東海\000近畿\000中国\000四国\000九州\000奄美(群島)\000沖縄\000その他の府県予報区および地方予報区_緊急地震速報(警報)\000";
struct QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry { uint8_t id; uint16_t offset; };
static const QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[] AZARAC_PROGMEM = {
    {1u, 0u},
    {2u, 16u},
    {3u, 32u},
    {4u, 48u},
    {5u, 64u},
    {6u, 71u},
    {7u, 78u},
    {8u, 85u},
    {9u, 92u},
    {10u, 99u},
    {11u, 106u},
    {12u, 113u},
    {13u, 120u},
    {14u, 127u},
    {15u, 134u},
    {16u, 141u},
    {17u, 148u},
    {18u, 161u},
    {19u, 171u},
    {20u, 181u},
    {21u, 188u},
    {22u, 195u},
    {23u, 202u},
    {24u, 209u},
    {25u, 216u},
    {26u, 223u},
    {27u, 230u},
    {28u, 237u},
    {29u, 244u},
    {30u, 251u},
    {31u, 258u},
    {32u, 265u},
    {33u, 272u},
    {34u, 279u},
    {35u, 286u},
    {36u, 296u},
    {37u, 303u},
    {38u, 310u},
    {39u, 317u},
    {40u, 324u},
    {41u, 331u},
    {42u, 338u},
    {43u, 345u},
    {44u, 352u},
    {45u, 359u},
    {46u, 366u},
    {47u, 373u},
    {48u, 380u},
    {49u, 387u},
    {50u, 394u},
    {51u, 401u},
    {52u, 411u},
    {53u, 426u},
    {54u, 439u},
    {55u, 449u},
    {56u, 459u},
    {57u, 469u},
    {58u, 479u},
    {59u, 486u},
    {60u, 493u},
    {61u, 506u},
    {62u, 516u},
    {63u, 523u},
    {64u, 530u},
    {65u, 537u},
    {66u, 544u},
    {67u, 551u},
    {68u, 558u},
    {69u, 565u},
    {70u, 580u},
    {80u, 587u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 71;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        azarac_pgm_ptr ep = AZARAC_PGM_PTR(QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE) + static_cast<size_t>(mid) * sizeof(QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry);
        uint8_t eid = static_cast<uint8_t>(azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry, id)));
        if (eid == id) {
            uint16_t off = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry, offset));
            return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_EEW_FORECAST_REGION_POOL) + off);
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
    {80u, "その他の府県予報区および地方予報区_緊急地震速報(警報)"},};
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
