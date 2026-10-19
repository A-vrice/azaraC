#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.tsunami_height → qzss_dcr_jma_tsunami_height: 9 entries, strategy switch
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

#if (AZARAC_ENABLE_TSUNAMI) && (AZARAC_LANG_JA)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_HEIGHT_C1[] = "0.2m未満";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_HEIGHT_C2[] = "1m";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_HEIGHT_C3[] = "3m";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_HEIGHT_C4[] = "5m";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_HEIGHT_C5[] = "10m";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_HEIGHT_C6[] = "10m超";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_HEIGHT_C13[] = "該当情報なし";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_HEIGHT_C14[] = "不明";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_HEIGHT_C15[] = "その他の津波の高さ";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_tsunami_height_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMI_HEIGHT_C1), 10);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMI_HEIGHT_C2), 2);
        case 3: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMI_HEIGHT_C3), 2);
        case 4: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMI_HEIGHT_C4), 2);
        case 5: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMI_HEIGHT_C5), 3);
        case 6: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMI_HEIGHT_C6), 6);
        case 13: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMI_HEIGHT_C13), 18);
        case 14: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMI_HEIGHT_C14), 6);
        case 15: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMI_HEIGHT_C15), 27);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_height_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"0.2m未満", 10};
        case 2: return std::string_view{"1m", 2};
        case 3: return std::string_view{"3m", 2};
        case 4: return std::string_view{"5m", 2};
        case 5: return std::string_view{"10m", 3};
        case 6: return std::string_view{"10m超", 6};
        case 13: return std::string_view{"該当情報なし", 18};
        case 14: return std::string_view{"不明", 6};
        case 15: return std::string_view{"その他の津波の高さ", 27};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_tsunami_height_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_height_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
