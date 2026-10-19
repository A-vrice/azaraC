#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.long_period_ground_motion_lower_limit → qzss_dcr_jma_long_period_ground_motion_lower_limit: 7 entries, strategy switch
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

#if (AZARAC_ENABLE_EEW) && (AZARAC_LANG_JA)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_LONG_PERIOD_GROUND_MOTION_LOWER_LIMIT_C0[] = "該当情報なし";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_LONG_PERIOD_GROUND_MOTION_LOWER_LIMIT_C1[] = "1未満";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_LONG_PERIOD_GROUND_MOTION_LOWER_LIMIT_C2[] = "1";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_LONG_PERIOD_GROUND_MOTION_LOWER_LIMIT_C3[] = "2";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_LONG_PERIOD_GROUND_MOTION_LOWER_LIMIT_C4[] = "3";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_LONG_PERIOD_GROUND_MOTION_LOWER_LIMIT_C5[] = "4";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_LONG_PERIOD_GROUND_MOTION_LOWER_LIMIT_C7[] = "不明";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_LONG_PERIOD_GROUND_MOTION_LOWER_LIMIT_PARENT_POOL[] = "長周期地震動階級\000";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_long_period_ground_motion_lower_limit_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_LONG_PERIOD_GROUND_MOTION_LOWER_LIMIT_C0), 18);
        case 1: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_LONG_PERIOD_GROUND_MOTION_LOWER_LIMIT_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCR_JMA_LONG_PERIOD_GROUND_MOTION_LOWER_LIMIT_C1));
        case 2: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_LONG_PERIOD_GROUND_MOTION_LOWER_LIMIT_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCR_JMA_LONG_PERIOD_GROUND_MOTION_LOWER_LIMIT_C2));
        case 3: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_LONG_PERIOD_GROUND_MOTION_LOWER_LIMIT_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCR_JMA_LONG_PERIOD_GROUND_MOTION_LOWER_LIMIT_C3));
        case 4: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_LONG_PERIOD_GROUND_MOTION_LOWER_LIMIT_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCR_JMA_LONG_PERIOD_GROUND_MOTION_LOWER_LIMIT_C4));
        case 5: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_LONG_PERIOD_GROUND_MOTION_LOWER_LIMIT_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCR_JMA_LONG_PERIOD_GROUND_MOTION_LOWER_LIMIT_C5));
        case 7: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_LONG_PERIOD_GROUND_MOTION_LOWER_LIMIT_C7), 6);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_long_period_ground_motion_lower_limit_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"該当情報なし", 18};
        case 1: return std::string_view{"長周期地震動階級1未満", 31};
        case 2: return std::string_view{"長周期地震動階級1", 25};
        case 3: return std::string_view{"長周期地震動階級2", 25};
        case 4: return std::string_view{"長周期地震動階級3", 25};
        case 5: return std::string_view{"長周期地震動階級4", 25};
        case 7: return std::string_view{"不明", 6};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_long_period_ground_motion_lower_limit_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_long_period_ground_motion_lower_limit_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
