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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_POOL[] = "Central Area of Hokkaido (Do'o\000Southern Area of Hokkaido (Donan\000Northern Area of Hokkaido (Dohoku\000Eastern Area of Hokkaido (Doto\000Aomor\000Iwate\000Miyag\000Akit\000Yamagat\000Fuku\000Ibarak\000Tochig\000Gunm\000Sait\000Chib\000Toky\000Izu Islands\000Ogasawar\000Kanaga\000Niigat\000Toya\000Ishika\000Fuku\000Yamanash\000Nagan\000Gifu\000Shizuok\000Aich\000Mie\000Shig\000Kyot\000Osak\000Hyog\000Nara\000Wakay\000Tottor\000Shimane\000Okay\000Hiro\000Yamaguch\000Toku\000Kaga\000Ehime\000Koch\000Fukuok\000Saga\000Nagasak\000Kumamot\000Oita\000Miyazak\000Kago\000Amami (Islands\000Okinawa Main Island\000Daitojima Island\000Miyakojima Island\000Yaey\000Hokkaid\000Toho\000Kant\000Izu Islands\000Ogasawar\000Hokuri\000Koshin\000Toka\000Kink\000Chugo\000Shiko\000Kyush\000Amami (Islands\000Okina\000Other Forecast Region (Earthquake Early Warning\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_PARENT_POOL[] = ")\000a\000ama\000i\000ku\000ma\000o\000shima\000u\000wa\000";
struct QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_PARENT_Entry QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 1u},
    {2u, 1u},
    {4u, 3u},
    {8u, 1u},
    {10u, 2u},
    {13u, 2u},
    {16u, 1u},
    {18u, 5u},
    {24u, 1u},
    {26u, 2u},
};
struct QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_Entry { uint8_t id; uint8_t parent; uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_Entry QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_TABLE[] AZARAC_PROGMEM = {
    {1u, 0u, 0u, 30u},
    {2u, 0u, 31u, 32u},
    {3u, 0u, 64u, 33u},
    {4u, 0u, 98u, 30u},
    {5u, 3u, 129u, 5u},
    {6u, 255u, 135u, 5u},
    {7u, 3u, 141u, 5u},
    {8u, 1u, 147u, 4u},
    {9u, 1u, 152u, 7u},
    {10u, 7u, 160u, 4u},
    {11u, 3u, 165u, 6u},
    {12u, 3u, 172u, 6u},
    {13u, 1u, 179u, 4u},
    {14u, 2u, 184u, 4u},
    {15u, 1u, 189u, 4u},
    {16u, 6u, 194u, 4u},
    {17u, 255u, 199u, 11u},
    {18u, 1u, 211u, 8u},
    {19u, 9u, 220u, 6u},
    {20u, 1u, 227u, 6u},
    {21u, 5u, 234u, 4u},
    {22u, 9u, 239u, 6u},
    {23u, 3u, 246u, 4u},
    {24u, 3u, 251u, 8u},
    {25u, 6u, 260u, 5u},
    {26u, 255u, 266u, 4u},
    {27u, 1u, 271u, 7u},
    {28u, 3u, 279u, 4u},
    {29u, 255u, 284u, 3u},
    {30u, 1u, 288u, 4u},
    {31u, 6u, 293u, 4u},
    {32u, 1u, 298u, 4u},
    {33u, 6u, 303u, 4u},
    {34u, 255u, 308u, 4u},
    {35u, 2u, 313u, 5u},
    {36u, 3u, 319u, 6u},
    {37u, 255u, 326u, 7u},
    {38u, 2u, 334u, 4u},
    {39u, 7u, 339u, 4u},
    {40u, 3u, 344u, 8u},
    {41u, 7u, 353u, 4u},
    {42u, 9u, 358u, 4u},
    {43u, 255u, 363u, 5u},
    {44u, 3u, 369u, 4u},
    {45u, 1u, 374u, 6u},
    {46u, 255u, 381u, 4u},
    {47u, 3u, 386u, 7u},
    {48u, 6u, 394u, 7u},
    {49u, 255u, 402u, 4u},
    {50u, 3u, 407u, 7u},
    {51u, 7u, 415u, 4u},
    {52u, 0u, 420u, 14u},
    {53u, 255u, 435u, 19u},
    {54u, 255u, 455u, 16u},
    {55u, 255u, 472u, 17u},
    {56u, 2u, 490u, 4u},
    {57u, 6u, 495u, 7u},
    {58u, 4u, 503u, 4u},
    {59u, 6u, 508u, 4u},
    {60u, 255u, 513u, 11u},
    {61u, 1u, 525u, 8u},
    {62u, 4u, 534u, 6u},
    {63u, 255u, 541u, 6u},
    {64u, 3u, 548u, 4u},
    {65u, 3u, 553u, 4u},
    {66u, 4u, 558u, 5u},
    {67u, 4u, 564u, 5u},
    {68u, 8u, 570u, 5u},
    {69u, 0u, 576u, 14u},
    {70u, 9u, 591u, 5u},
    {80u, 0u, 597u, 47u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 71;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_Entry, offset));
            uint8_t n = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_Entry, len));
            uint8_t pi = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_Entry, parent));
            if (pi == 255u) return azarac_pgm_view(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_POOL + off, n);
            const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_PARENT_TABLE[pi]);
            uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_PARENT_Entry, offset));
            uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_PARENT_Entry, len));
            return azarac_pgm_join(QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_POOL + off, n, QZSS_DCR_JMA_EEW_FORECAST_REGION_EN_PARENT_POOL + poff, pn);
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
