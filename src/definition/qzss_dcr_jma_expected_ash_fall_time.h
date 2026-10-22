#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.expected_ash_fall_time → qzss_dcr_jma_expected_ash_fall_time: 6 entries, strategy switch
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

#if (AZARAC_ENABLE_ASH_FALL) && (AZARAC_LANG_JA)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_EXPECTED_ASH_FALL_TIME_C1[] = "1";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_EXPECTED_ASH_FALL_TIME_C2[] = "2";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_EXPECTED_ASH_FALL_TIME_C3[] = "3";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_EXPECTED_ASH_FALL_TIME_C4[] = "4";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_EXPECTED_ASH_FALL_TIME_C5[] = "5";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_EXPECTED_ASH_FALL_TIME_C6[] = "6";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_EXPECTED_ASH_FALL_TIME_PARENT_POOL[] = "時間\000";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_expected_ash_fall_time_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_EXPECTED_ASH_FALL_TIME_C1), AZARAC_PGM_PTR(QZSS_DCR_JMA_EXPECTED_ASH_FALL_TIME_PARENT_POOL) + 0u);
        case 2: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_EXPECTED_ASH_FALL_TIME_C2), AZARAC_PGM_PTR(QZSS_DCR_JMA_EXPECTED_ASH_FALL_TIME_PARENT_POOL) + 0u);
        case 3: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_EXPECTED_ASH_FALL_TIME_C3), AZARAC_PGM_PTR(QZSS_DCR_JMA_EXPECTED_ASH_FALL_TIME_PARENT_POOL) + 0u);
        case 4: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_EXPECTED_ASH_FALL_TIME_C4), AZARAC_PGM_PTR(QZSS_DCR_JMA_EXPECTED_ASH_FALL_TIME_PARENT_POOL) + 0u);
        case 5: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_EXPECTED_ASH_FALL_TIME_C5), AZARAC_PGM_PTR(QZSS_DCR_JMA_EXPECTED_ASH_FALL_TIME_PARENT_POOL) + 0u);
        case 6: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_EXPECTED_ASH_FALL_TIME_C6), AZARAC_PGM_PTR(QZSS_DCR_JMA_EXPECTED_ASH_FALL_TIME_PARENT_POOL) + 0u);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_expected_ash_fall_time_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"1時間", 7};
        case 2: return std::string_view{"2時間", 7};
        case 3: return std::string_view{"3時間", 7};
        case 4: return std::string_view{"4時間", 7};
        case 5: return std::string_view{"5時間", 7};
        case 6: return std::string_view{"6時間", 7};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_expected_ash_fall_time_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_expected_ash_fall_time_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
