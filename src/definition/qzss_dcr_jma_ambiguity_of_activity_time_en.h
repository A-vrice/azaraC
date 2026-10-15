#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.ambiguity_of_activity_time
// Variable      : qzss_dcr_jma_ambiguity_of_activity_time_en
// Entries       : 8
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

#if (AZARAC_ENABLE_VOLCANO || AZARAC_ENABLE_ASH_FALL)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_PARENT_POOL[] = "Approximate time (\000";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_ambiguity_of_activity_time_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "No ambiguity"; return azarac_pgm_view(AZARAC_PGM_PTR(s), 12); }
        case 1: { static const char AZARAC_PROGMEM s[] = "equivalent to Approximate time (minute))"; return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_PARENT_POOL) + 0u, AZARAC_PGM_PTR(s)); }
        case 2: { static const char AZARAC_PROGMEM s[] = "second)"; return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_PARENT_POOL) + 0u, AZARAC_PGM_PTR(s)); }
        case 3: { static const char AZARAC_PROGMEM s[] = "minute)"; return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_PARENT_POOL) + 0u, AZARAC_PGM_PTR(s)); }
        case 4: { static const char AZARAC_PROGMEM s[] = "hour)"; return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_PARENT_POOL) + 0u, AZARAC_PGM_PTR(s)); }
        case 5: { static const char AZARAC_PROGMEM s[] = "day)"; return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_PARENT_POOL) + 0u, AZARAC_PGM_PTR(s)); }
        case 6: { static const char AZARAC_PROGMEM s[] = "month)"; return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_PARENT_POOL) + 0u, AZARAC_PGM_PTR(s)); }
        case 7: { static const char AZARAC_PROGMEM s[] = "year)"; return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_PARENT_POOL) + 0u, AZARAC_PGM_PTR(s)); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_ambiguity_of_activity_time_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"No ambiguity", 12};
        case 1: return std::string_view{"Approximate time (equivalent to Approximate time (minute))", 58};
        case 2: return std::string_view{"Approximate time (second)", 25};
        case 3: return std::string_view{"Approximate time (minute)", 25};
        case 4: return std::string_view{"Approximate time (hour)", 23};
        case 5: return std::string_view{"Approximate time (day)", 22};
        case 6: return std::string_view{"Approximate time (month)", 24};
        case 7: return std::string_view{"Approximate time (year)", 23};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_ambiguity_of_activity_time_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_ambiguity_of_activity_time_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
