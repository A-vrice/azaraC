#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.eew_forecast_region
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

#if (AZARAC_ENABLE_EEW) && (AZARAC_LANG_JA)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_EEW_FORECAST_REGION_POOL[] = "央\000南\000北\000東\000青森\000岩手\000宮城\000秋田\000山形\000福島\000茨城\000栃木\000群馬\000埼玉\000千葉\000東京\000伊豆諸島\000小笠原\000神奈川\000新潟\000富山\000石川\000福井\000山梨\000長野\000岐阜\000静岡\000愛知\000三重\000滋賀\000京都\000大阪\000兵庫\000奈良\000和歌山\000鳥取\000島根\000岡山\000広島\000山口\000徳島\000香川\000愛媛\000高知\000福岡\000佐賀\000長崎\000熊本\000大分\000宮崎\000鹿児島\000奄美(群島)\000沖縄本島\000大東島\000宮古島\000八重山\000道\000東北\000関東\000伊豆諸島\000小笠原\000北陸\000甲信\000東海\000近畿\000中国\000四国\000九州\000奄美(群島)\000沖縄\000その他の府県予報区および地方予報区_緊急地震速報(警報)\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_EEW_FORECAST_REGION_PARENT_POOL[] = "北海\000北海道道\000";
struct QZSS_DCR_JMA_EEW_FORECAST_REGION_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_EEW_FORECAST_REGION_PARENT_Entry QZSS_DCR_JMA_EEW_FORECAST_REGION_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {7u},
};
struct QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry { uint8_t id; uint8_t parent; uint16_t offset; };
static const QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[] AZARAC_PROGMEM = {
    {1u, 1u, 0u},
    {2u, 1u, 4u},
    {3u, 1u, 8u},
    {4u, 1u, 12u},
    {5u, 255u, 16u},
    {6u, 255u, 23u},
    {7u, 255u, 30u},
    {8u, 255u, 37u},
    {9u, 255u, 44u},
    {10u, 255u, 51u},
    {11u, 255u, 58u},
    {12u, 255u, 65u},
    {13u, 255u, 72u},
    {14u, 255u, 79u},
    {15u, 255u, 86u},
    {16u, 255u, 93u},
    {17u, 255u, 100u},
    {18u, 255u, 113u},
    {19u, 255u, 123u},
    {20u, 255u, 133u},
    {21u, 255u, 140u},
    {22u, 255u, 147u},
    {23u, 255u, 154u},
    {24u, 255u, 161u},
    {25u, 255u, 168u},
    {26u, 255u, 175u},
    {27u, 255u, 182u},
    {28u, 255u, 189u},
    {29u, 255u, 196u},
    {30u, 255u, 203u},
    {31u, 255u, 210u},
    {32u, 255u, 217u},
    {33u, 255u, 224u},
    {34u, 255u, 231u},
    {35u, 255u, 238u},
    {36u, 255u, 248u},
    {37u, 255u, 255u},
    {38u, 255u, 262u},
    {39u, 255u, 269u},
    {40u, 255u, 276u},
    {41u, 255u, 283u},
    {42u, 255u, 290u},
    {43u, 255u, 297u},
    {44u, 255u, 304u},
    {45u, 255u, 311u},
    {46u, 255u, 318u},
    {47u, 255u, 325u},
    {48u, 255u, 332u},
    {49u, 255u, 339u},
    {50u, 255u, 346u},
    {51u, 255u, 353u},
    {52u, 255u, 363u},
    {53u, 255u, 378u},
    {54u, 255u, 391u},
    {55u, 255u, 401u},
    {56u, 255u, 411u},
    {57u, 0u, 421u},
    {58u, 255u, 425u},
    {59u, 255u, 432u},
    {60u, 255u, 439u},
    {61u, 255u, 452u},
    {62u, 255u, 462u},
    {63u, 255u, 469u},
    {64u, 255u, 476u},
    {65u, 255u, 483u},
    {66u, 255u, 490u},
    {67u, 255u, 497u},
    {68u, 255u, 504u},
    {69u, 255u, 511u},
    {70u, 255u, 526u},
    {80u, 255u, 533u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 71;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        azarac_pgm_ptr ep = AZARAC_PGM_PTR(QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE) + static_cast<size_t>(mid) * sizeof(QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry);
        uint8_t eid = static_cast<uint8_t>(azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry, id)));
        if (eid == id) {
            uint16_t off = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry, offset));
            uint8_t pi = azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry, parent));
            if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_EEW_FORECAST_REGION_POOL) + off);
            azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCR_JMA_EEW_FORECAST_REGION_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCR_JMA_EEW_FORECAST_REGION_PARENT_Entry);
            uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_PARENT_Entry, offset));
            return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_EEW_FORECAST_REGION_PARENT_POOL) + poff, AZARAC_PGM_PTR(QZSS_DCR_JMA_EEW_FORECAST_REGION_POOL) + off);
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
