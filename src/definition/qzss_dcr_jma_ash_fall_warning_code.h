#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.ash_fall_warning_code → qzss_dcr_jma_ash_fall_warning_code: 5 entries, strategy switch
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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_ASH_FALL_WARNING_CODE_C1[] = "少量の降灰";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_ASH_FALL_WARNING_CODE_C2[] = "やや多量の降灰";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_ASH_FALL_WARNING_CODE_C3[] = "多量の降灰";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_ASH_FALL_WARNING_CODE_C4[] = "小さな噴石の落下";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_ASH_FALL_WARNING_CODE_C7[] = "その他の防災気象情報要素2";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_ash_fall_warning_code_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_ASH_FALL_WARNING_CODE_C1), 15);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_ASH_FALL_WARNING_CODE_C2), 21);
        case 3: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_ASH_FALL_WARNING_CODE_C3), 15);
        case 4: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_ASH_FALL_WARNING_CODE_C4), 24);
        case 7: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_ASH_FALL_WARNING_CODE_C7), 37);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_ash_fall_warning_code_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"少量の降灰", 15};
        case 2: return std::string_view{"やや多量の降灰", 21};
        case 3: return std::string_view{"多量の降灰", 15};
        case 4: return std::string_view{"小さな噴石の落下", 24};
        case 7: return std::string_view{"その他の防災気象情報要素2", 37};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_ash_fall_warning_code_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_ash_fall_warning_code_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
