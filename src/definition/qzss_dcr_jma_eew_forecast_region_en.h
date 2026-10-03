#pragma once
// AUTO-GENERATED from azarashi 0.17.0 with CI-CD
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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_POOL[] = "Central Area of Hokkaido (Do'o)\000Southern Area of Hokkaido (Donan)\000Northern Area of Hokkaido (Dohoku)\000Eastern Area of Hokkaido (Doto)\000Aomori\000Iwate\000Miyagi\000Akita\000Yamagata\000Fukushima\000Ibaraki\000Tochigi\000Gunma\000Saitama\000Chiba\000Tokyo\000Izu Islands\000Ogasawara\000Kanagawa\000Niigata\000Toyama\000Ishikawa\000Fukui\000Yamanashi\000Nagano\000Gifu\000Shizuoka\000Aichi\000Mie\000Shiga\000Kyoto\000Osaka\000Hyogo\000Nara\000Wakayama\000Tottori\000Shimane\000Okayama\000Hiroshima\000Yamaguchi\000Tokushima\000Kagawa\000Ehime\000Kochi\000Fukuoka\000Saga\000Nagasaki\000Kumamoto\000Oita\000Miyazaki\000Kagoshima\000Amami (Islands)\000Okinawa Main Island\000Daitojima Island\000Miyakojima Island\000Yaeyama\000Hokkaido\000Tohoku\000Kanto\000Izu Islands\000Ogasawara\000Hokuriku\000Koshin\000Tokai\000Kinki\000Chugoku\000Shikoku\000Kyushu\000Amami (Islands)\000Okinawa\000Other Forecast Region (Earthquake Early Warning)\000";
struct QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_Entry { uint8_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_Entry QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_TABLE[] AZARAC_PROGMEM = {
    {1u, 0u, 31u},
    {2u, 32u, 33u},
    {3u, 66u, 34u},
    {4u, 101u, 31u},
    {5u, 133u, 6u},
    {6u, 140u, 5u},
    {7u, 146u, 6u},
    {8u, 153u, 5u},
    {9u, 159u, 8u},
    {10u, 168u, 9u},
    {11u, 178u, 7u},
    {12u, 186u, 7u},
    {13u, 194u, 5u},
    {14u, 200u, 7u},
    {15u, 208u, 5u},
    {16u, 214u, 5u},
    {17u, 220u, 11u},
    {18u, 232u, 9u},
    {19u, 242u, 8u},
    {20u, 251u, 7u},
    {21u, 259u, 6u},
    {22u, 266u, 8u},
    {23u, 275u, 5u},
    {24u, 281u, 9u},
    {25u, 291u, 6u},
    {26u, 298u, 4u},
    {27u, 303u, 8u},
    {28u, 312u, 5u},
    {29u, 318u, 3u},
    {30u, 322u, 5u},
    {31u, 328u, 5u},
    {32u, 334u, 5u},
    {33u, 340u, 5u},
    {34u, 346u, 4u},
    {35u, 351u, 8u},
    {36u, 360u, 7u},
    {37u, 368u, 7u},
    {38u, 376u, 7u},
    {39u, 384u, 9u},
    {40u, 394u, 9u},
    {41u, 404u, 9u},
    {42u, 414u, 6u},
    {43u, 421u, 5u},
    {44u, 427u, 5u},
    {45u, 433u, 7u},
    {46u, 441u, 4u},
    {47u, 446u, 8u},
    {48u, 455u, 8u},
    {49u, 464u, 4u},
    {50u, 469u, 8u},
    {51u, 478u, 9u},
    {52u, 488u, 15u},
    {53u, 504u, 19u},
    {54u, 524u, 16u},
    {55u, 541u, 17u},
    {56u, 559u, 7u},
    {57u, 567u, 8u},
    {58u, 576u, 6u},
    {59u, 583u, 5u},
    {60u, 589u, 11u},
    {61u, 601u, 9u},
    {62u, 611u, 8u},
    {63u, 620u, 6u},
    {64u, 627u, 5u},
    {65u, 633u, 5u},
    {66u, 639u, 7u},
    {67u, 647u, 7u},
    {68u, 655u, 6u},
    {69u, 662u, 15u},
    {70u, 678u, 7u},
    {80u, 686u, 48u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 71;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_Entry, len));
            return azarac_pgm_view(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_POOL + off, n);
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
