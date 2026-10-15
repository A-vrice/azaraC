#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.marine_warning_code
// Variable      : qzss_dcr_jma_marine_warning_code_en
// Entries       : 9
// Strategy      : switch

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

#if (AZARAC_ENABLE_MARINE) && (AZARAC_LANG_EN)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_PARENT_POOL[] = " Warning\000";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_marine_warning_code_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "Marine Warning Lifted"; return azarac_pgm_view(s, 21); }
        case 10: { static const char AZARAC_PROGMEM s[] = "Ice Accretion"; return azarac_pgm_join_z(s, QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_PARENT_POOL + 0u); }
        case 11: { static const char AZARAC_PROGMEM s[] = "Fog"; return azarac_pgm_join_z(s, QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_PARENT_POOL + 0u); }
        case 12: { static const char AZARAC_PROGMEM s[] = "Swell"; return azarac_pgm_join_z(s, QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_PARENT_POOL + 0u); }
        case 20: { static const char AZARAC_PROGMEM s[] = "Wind"; return azarac_pgm_join_z(s, QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_PARENT_POOL + 0u); }
        case 21: { static const char AZARAC_PROGMEM s[] = "Gale"; return azarac_pgm_join_z(s, QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_PARENT_POOL + 0u); }
        case 22: { static const char AZARAC_PROGMEM s[] = "Storm"; return azarac_pgm_join_z(s, QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_PARENT_POOL + 0u); }
        case 23: { static const char AZARAC_PROGMEM s[] = "Typhoon"; return azarac_pgm_join_z(s, QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_PARENT_POOL + 0u); }
        case 31: { static const char AZARAC_PROGMEM s[] = "Other Marine"; return azarac_pgm_join_z(s, QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_PARENT_POOL + 0u); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_marine_warning_code_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Marine Warning Lifted", 21};
        case 10: return std::string_view{"Ice Accretion Warning", 21};
        case 11: return std::string_view{"Fog Warning", 11};
        case 12: return std::string_view{"Swell Warning", 13};
        case 20: return std::string_view{"Wind Warning", 12};
        case 21: return std::string_view{"Gale Warning", 12};
        case 22: return std::string_view{"Storm Warning", 13};
        case 23: return std::string_view{"Typhoon Warning", 15};
        case 31: return std::string_view{"Other Marine Warning", 20};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_marine_warning_code_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_marine_warning_code_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
