#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.ambiguity_of_activity_time → qzss_dcr_jma_ambiguity_of_activity_time_en: 8 entries, strategy switch
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

#if (AZARAC_ENABLE_VOLCANO || AZARAC_ENABLE_ASH_FALL)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_C0[] = "No ambiguity";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_C1[] = "equivalent to Approximate time (minute))";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_C2[] = "second)";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_C3[] = "minute)";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_C4[] = "hour)";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_C5[] = "day)";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_C6[] = "month)";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_C7[] = "year)";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_PARENT_POOL[] = "Approximate time (\000";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_ambiguity_of_activity_time_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_C0), 12);
        case 1: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_C1));
        case 2: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_C2));
        case 3: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_C3));
        case 4: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_C4));
        case 5: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_C5));
        case 6: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_C6));
        case 7: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCR_JMA_AMBIGUITY_OF_ACTIVITY_TIME_EN_C7));
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
