#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.flood_warning_level → qzss_dcr_jma_flood_warning_level: 5 entries, strategy switch
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

#if (AZARAC_ENABLE_FLOOD) && (AZARAC_LANG_JA)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_FLOOD_WARNING_LEVEL_C1[] = "警報解除";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_FLOOD_WARNING_LEVEL_C2[] = "氾濫警戒情報";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_FLOOD_WARNING_LEVEL_C3[] = "氾濫危険情報";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_FLOOD_WARNING_LEVEL_C4[] = "氾濫発生情報";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_FLOOD_WARNING_LEVEL_C15[] = "その他の警戒レベル";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_flood_warning_level_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_FLOOD_WARNING_LEVEL_C1), 12);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_FLOOD_WARNING_LEVEL_C2), 18);
        case 3: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_FLOOD_WARNING_LEVEL_C3), 18);
        case 4: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_FLOOD_WARNING_LEVEL_C4), 18);
        case 15: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_FLOOD_WARNING_LEVEL_C15), 27);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_flood_warning_level_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"警報解除", 12};
        case 2: return std::string_view{"氾濫警戒情報", 18};
        case 3: return std::string_view{"氾濫危険情報", 18};
        case 4: return std::string_view{"氾濫発生情報", 18};
        case 15: return std::string_view{"その他の警戒レベル", 27};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_flood_warning_level_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_flood_warning_level_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
