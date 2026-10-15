#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.eew_forecast_region
// Variable      : qzss_dcr_jma_eew_forecast_region_en
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

#if (AZARAC_ENABLE_EEW) && (AZARAC_LANG_EN)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_POOL[] = "Central Area of Hokkaido (Do'o)\000Southern Area of Hokkaido (Donan)\000Northern Area of Hokkaido (Dohoku)\000Eastern Area of Hokkaido (Doto)\000Aomori\000Iwate\000Miyagi\000Akita\000Yamagata\000Fuku\000Ibaraki\000Tochigi\000Gunma\000Saitama\000Chiba\000Tokyo\000Izu Islands\000Ogasawara\000Kanagawa\000Niigata\000To\000Ishikawa\000Fukui\000Yamanashi\000Nagano\000Gifu\000Shizuoka\000Aichi\000Mie\000Shiga\000Kyoto\000Osaka\000Hyogo\000Nara\000Waka\000Tottori\000Shimane\000Oka\000Hiro\000Yamaguchi\000Toku\000Kagawa\000Ehime\000Kochi\000Fukuoka\000Saga\000Nagasaki\000Kumamoto\000Oita\000Miyazaki\000Kago\000Amami (Islands)\000Okinawa Main Island\000Daitojima Island\000Miyakojima Island\000Yae\000Hokkaido\000Tohoku\000Kanto\000Izu Islands\000Ogasawara\000Hokuriku\000Koshin\000Tokai\000Kinki\000Chugoku\000Shikoku\000Kyushu\000Amami (Islands)\000Okinawa\000Other Forecast Region (Earthquake Early Warning)\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_PARENT_POOL[] = "shima\000yama\000";
struct QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_PARENT_Entry QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {6u},
};
struct QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_Entry { uint8_t id; uint8_t parent; uint16_t offset; };
static const QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_Entry QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_TABLE[] AZARAC_PROGMEM = {
    {1u, 255u, 0u},
    {2u, 255u, 32u},
    {3u, 255u, 66u},
    {4u, 255u, 101u},
    {5u, 255u, 133u},
    {6u, 255u, 140u},
    {7u, 255u, 146u},
    {8u, 255u, 153u},
    {9u, 255u, 159u},
    {10u, 0u, 168u},
    {11u, 255u, 173u},
    {12u, 255u, 181u},
    {13u, 255u, 189u},
    {14u, 255u, 195u},
    {15u, 255u, 203u},
    {16u, 255u, 209u},
    {17u, 255u, 215u},
    {18u, 255u, 227u},
    {19u, 255u, 237u},
    {20u, 255u, 246u},
    {21u, 1u, 254u},
    {22u, 255u, 257u},
    {23u, 255u, 266u},
    {24u, 255u, 272u},
    {25u, 255u, 282u},
    {26u, 255u, 289u},
    {27u, 255u, 294u},
    {28u, 255u, 303u},
    {29u, 255u, 309u},
    {30u, 255u, 313u},
    {31u, 255u, 319u},
    {32u, 255u, 325u},
    {33u, 255u, 331u},
    {34u, 255u, 337u},
    {35u, 1u, 342u},
    {36u, 255u, 347u},
    {37u, 255u, 355u},
    {38u, 1u, 363u},
    {39u, 0u, 367u},
    {40u, 255u, 372u},
    {41u, 0u, 382u},
    {42u, 255u, 387u},
    {43u, 255u, 394u},
    {44u, 255u, 400u},
    {45u, 255u, 406u},
    {46u, 255u, 414u},
    {47u, 255u, 419u},
    {48u, 255u, 428u},
    {49u, 255u, 437u},
    {50u, 255u, 442u},
    {51u, 0u, 451u},
    {52u, 255u, 456u},
    {53u, 255u, 472u},
    {54u, 255u, 492u},
    {55u, 255u, 509u},
    {56u, 1u, 527u},
    {57u, 255u, 531u},
    {58u, 255u, 540u},
    {59u, 255u, 547u},
    {60u, 255u, 553u},
    {61u, 255u, 565u},
    {62u, 255u, 575u},
    {63u, 255u, 584u},
    {64u, 255u, 591u},
    {65u, 255u, 597u},
    {66u, 255u, 603u},
    {67u, 255u, 611u},
    {68u, 255u, 619u},
    {69u, 255u, 626u},
    {70u, 255u, 642u},
    {80u, 255u, 650u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 71;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        azarac_pgm_ptr ep = AZARAC_PGM_PTR(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_TABLE) + static_cast<size_t>(mid) * sizeof(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_Entry);
        uint8_t eid = static_cast<uint8_t>(azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_Entry, id)));
        if (eid == id) {
            uint16_t off = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_Entry, offset));
            uint8_t pi = azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_Entry, parent));
            if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_POOL) + off);
            azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_PARENT_Entry);
            uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_PARENT_Entry, offset));
            return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_POOL) + off, AZARAC_PGM_PTR(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_PARENT_POOL) + poff);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_Entry { uint8_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_Entry QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_TABLE[] = {
    {1u, "Central Area of Hokkaido (Do'o)"},
    {2u, "Southern Area of Hokkaido (Donan)"},
    {3u, "Northern Area of Hokkaido (Dohoku)"},
    {4u, "Eastern Area of Hokkaido (Doto)"},
    {5u, "Aomori"},
    {6u, "Iwate"},
    {7u, "Miyagi"},
    {8u, "Akita"},
    {9u, "Yamagata"},
    {10u, "Fukushima"},
    {11u, "Ibaraki"},
    {12u, "Tochigi"},
    {13u, "Gunma"},
    {14u, "Saitama"},
    {15u, "Chiba"},
    {16u, "Tokyo"},
    {17u, "Izu Islands"},
    {18u, "Ogasawara"},
    {19u, "Kanagawa"},
    {20u, "Niigata"},
    {21u, "Toyama"},
    {22u, "Ishikawa"},
    {23u, "Fukui"},
    {24u, "Yamanashi"},
    {25u, "Nagano"},
    {26u, "Gifu"},
    {27u, "Shizuoka"},
    {28u, "Aichi"},
    {29u, "Mie"},
    {30u, "Shiga"},
    {31u, "Kyoto"},
    {32u, "Osaka"},
    {33u, "Hyogo"},
    {34u, "Nara"},
    {35u, "Wakayama"},
    {36u, "Tottori"},
    {37u, "Shimane"},
    {38u, "Okayama"},
    {39u, "Hiroshima"},
    {40u, "Yamaguchi"},
    {41u, "Tokushima"},
    {42u, "Kagawa"},
    {43u, "Ehime"},
    {44u, "Kochi"},
    {45u, "Fukuoka"},
    {46u, "Saga"},
    {47u, "Nagasaki"},
    {48u, "Kumamoto"},
    {49u, "Oita"},
    {50u, "Miyazaki"},
    {51u, "Kagoshima"},
    {52u, "Amami (Islands)"},
    {53u, "Okinawa Main Island"},
    {54u, "Daitojima Island"},
    {55u, "Miyakojima Island"},
    {56u, "Yaeyama"},
    {57u, "Hokkaido"},
    {58u, "Tohoku"},
    {59u, "Kanto"},
    {60u, "Izu Islands"},
    {61u, "Ogasawara"},
    {62u, "Hokuriku"},
    {63u, "Koshin"},
    {64u, "Tokai"},
    {65u, "Kinki"},
    {66u, "Chugoku"},
    {67u, "Shikoku"},
    {68u, "Kyushu"},
    {69u, "Amami (Islands)"},
    {70u, "Okinawa"},
    {80u, "Other Forecast Region (Earthquake Early Warning)"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 71;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
