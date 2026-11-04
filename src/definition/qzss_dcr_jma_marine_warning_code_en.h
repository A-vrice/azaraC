#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.marine_warning_code → qzss_dcr_jma_marine_warning_code_en: 9 entries, strategy switch
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

#if (AZARAC_ENABLE_MARINE) && (AZARAC_LANG_EN)

static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_C0[] = "Marine Warning Lifted";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_C10[] = "Ice Accretion";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_C11[] = "Fog";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_C12[] = "Swell";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_C20[] = "Wind";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_C21[] = "Gale";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_C22[] = "Storm";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_C23[] = "Typhoon";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_C31[] = "Other Marine";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_PARENT_POOL[] = " Warning\000";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_marine_warning_code_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_C0), 21);
        case 10: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_C10), AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_PARENT_POOL) + 0u);
        case 11: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_C11), AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_PARENT_POOL) + 0u);
        case 12: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_C12), AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_PARENT_POOL) + 0u);
        case 20: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_C20), AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_PARENT_POOL) + 0u);
        case 21: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_C21), AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_PARENT_POOL) + 0u);
        case 22: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_C22), AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_PARENT_POOL) + 0u);
        case 23: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_C23), AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_PARENT_POOL) + 0u);
        case 31: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_C31), AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_EN_PARENT_POOL) + 0u);
        default: return std::nullopt;
    }
}

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
