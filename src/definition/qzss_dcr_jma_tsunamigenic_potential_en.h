#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.tsunamigenic_potential → qzss_dcr_jma_tsunamigenic_potential_en: 6 entries, strategy switch
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

#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMIGENIC_POTENTIAL_EN_C0[] = "No Possibility of a Tsunami";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMIGENIC_POTENTIAL_EN_C1[] = "Possibility of a Destructive Ocean-Wide Tsunami";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMIGENIC_POTENTIAL_EN_C2[] = "Possibility of a Destructive Regional Tsunami";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMIGENIC_POTENTIAL_EN_C3[] = "Possibility of a Destructive Local Tsunami Near the Epicenter";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMIGENIC_POTENTIAL_EN_C4[] = "Very Small Possibility of a Destructive Local Tsunami";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMIGENIC_POTENTIAL_EN_C7[] = "Other Tsunamigenic Potential";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMIGENIC_POTENTIAL_EN_PARENT_POOL[] = "There is \000There is a \000";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_tsunamigenic_potential_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMIGENIC_POTENTIAL_EN_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMIGENIC_POTENTIAL_EN_C0));
        case 1: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMIGENIC_POTENTIAL_EN_PARENT_POOL) + 10u, AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMIGENIC_POTENTIAL_EN_C1));
        case 2: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMIGENIC_POTENTIAL_EN_PARENT_POOL) + 10u, AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMIGENIC_POTENTIAL_EN_C2));
        case 3: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMIGENIC_POTENTIAL_EN_PARENT_POOL) + 10u, AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMIGENIC_POTENTIAL_EN_C3));
        case 4: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMIGENIC_POTENTIAL_EN_PARENT_POOL) + 10u, AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMIGENIC_POTENTIAL_EN_C4));
        case 7: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMIGENIC_POTENTIAL_EN_C7), 28);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunamigenic_potential_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"There is No Possibility of a Tsunami", 36};
        case 1: return std::string_view{"There is a Possibility of a Destructive Ocean-Wide Tsunami", 58};
        case 2: return std::string_view{"There is a Possibility of a Destructive Regional Tsunami", 56};
        case 3: return std::string_view{"There is a Possibility of a Destructive Local Tsunami Near the Epicenter", 72};
        case 4: return std::string_view{"There is a Very Small Possibility of a Destructive Local Tsunami", 64};
        case 7: return std::string_view{"Other Tsunamigenic Potential", 28};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_tsunamigenic_potential_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunamigenic_potential_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
