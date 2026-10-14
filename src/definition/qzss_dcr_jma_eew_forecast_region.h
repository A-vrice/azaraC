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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_EEW_FORECAST_REGION_POOL[] = "北海道道央\000北海道道南\000北海道道北\000北海道道東\000青森\000岩手\000宮城\000秋田\000山形\000福島\000茨城\000栃木\000群馬\000埼玉\000千葉\000東京\000伊豆諸\000小笠原\000神奈川\000新潟\000富山\000石川\000福井\000山梨\000長野\000岐阜\000静岡\000愛知\000三重\000滋賀\000京都\000大阪\000兵庫\000奈良\000和歌山\000鳥取\000島根\000岡山\000広島\000山口\000徳島\000香川\000愛媛\000高知\000福岡\000佐賀\000長崎\000熊本\000大分\000宮崎\000鹿児\000奄美(群島)\000沖縄本\000大東\000宮古\000八重山\000北海道\000東北\000関東\000伊豆諸\000小笠原\000北陸\000甲信\000東海\000近畿\000中国\000四国\000九州\000奄美(群島)\000沖縄\000その他の府県予報区および地方予報区_緊急地震速報(警報)\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_EEW_FORECAST_REGION_PARENT_POOL[] = "島\000";
struct QZSS_DCR_JMA_EEW_FORECAST_REGION_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_EEW_FORECAST_REGION_PARENT_Entry QZSS_DCR_JMA_EEW_FORECAST_REGION_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 3u},
};
struct QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry { uint8_t id; uint8_t parent; uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[] AZARAC_PROGMEM = {
    {1u, 255u, 0u, 15u},
    {2u, 255u, 16u, 15u},
    {3u, 255u, 32u, 15u},
    {4u, 255u, 48u, 15u},
    {5u, 255u, 64u, 6u},
    {6u, 255u, 71u, 6u},
    {7u, 255u, 78u, 6u},
    {8u, 255u, 85u, 6u},
    {9u, 255u, 92u, 6u},
    {10u, 255u, 99u, 6u},
    {11u, 255u, 106u, 6u},
    {12u, 255u, 113u, 6u},
    {13u, 255u, 120u, 6u},
    {14u, 255u, 127u, 6u},
    {15u, 255u, 134u, 6u},
    {16u, 255u, 141u, 6u},
    {17u, 0u, 148u, 9u},
    {18u, 255u, 158u, 9u},
    {19u, 255u, 168u, 9u},
    {20u, 255u, 178u, 6u},
    {21u, 255u, 185u, 6u},
    {22u, 255u, 192u, 6u},
    {23u, 255u, 199u, 6u},
    {24u, 255u, 206u, 6u},
    {25u, 255u, 213u, 6u},
    {26u, 255u, 220u, 6u},
    {27u, 255u, 227u, 6u},
    {28u, 255u, 234u, 6u},
    {29u, 255u, 241u, 6u},
    {30u, 255u, 248u, 6u},
    {31u, 255u, 255u, 6u},
    {32u, 255u, 262u, 6u},
    {33u, 255u, 269u, 6u},
    {34u, 255u, 276u, 6u},
    {35u, 255u, 283u, 9u},
    {36u, 255u, 293u, 6u},
    {37u, 255u, 300u, 6u},
    {38u, 255u, 307u, 6u},
    {39u, 255u, 314u, 6u},
    {40u, 255u, 321u, 6u},
    {41u, 255u, 328u, 6u},
    {42u, 255u, 335u, 6u},
    {43u, 255u, 342u, 6u},
    {44u, 255u, 349u, 6u},
    {45u, 255u, 356u, 6u},
    {46u, 255u, 363u, 6u},
    {47u, 255u, 370u, 6u},
    {48u, 255u, 377u, 6u},
    {49u, 255u, 384u, 6u},
    {50u, 255u, 391u, 6u},
    {51u, 0u, 398u, 6u},
    {52u, 255u, 405u, 14u},
    {53u, 0u, 420u, 9u},
    {54u, 0u, 430u, 6u},
    {55u, 0u, 437u, 6u},
    {56u, 255u, 444u, 9u},
    {57u, 255u, 454u, 9u},
    {58u, 255u, 464u, 6u},
    {59u, 255u, 471u, 6u},
    {60u, 0u, 478u, 9u},
    {61u, 255u, 488u, 9u},
    {62u, 255u, 498u, 6u},
    {63u, 255u, 505u, 6u},
    {64u, 255u, 512u, 6u},
    {65u, 255u, 519u, 6u},
    {66u, 255u, 526u, 6u},
    {67u, 255u, 533u, 6u},
    {68u, 255u, 540u, 6u},
    {69u, 255u, 547u, 14u},
    {70u, 255u, 562u, 6u},
    {80u, 255u, 569u, 78u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 71;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry, offset));
            uint8_t n = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry, len));
            uint8_t pi = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry, parent));
            if (pi == 255u) return azarac_pgm_view(QZSS_DCR_JMA_EEW_FORECAST_REGION_POOL + off, n);
            const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_EEW_FORECAST_REGION_PARENT_TABLE[pi]);
            uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_PARENT_Entry, offset));
            uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_PARENT_Entry, len));
            return azarac_pgm_join(QZSS_DCR_JMA_EEW_FORECAST_REGION_POOL + off, n, QZSS_DCR_JMA_EEW_FORECAST_REGION_PARENT_POOL + poff, pn);
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
