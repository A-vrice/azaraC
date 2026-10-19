#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.tsunami_warning_code → qzss_dcr_jma_tsunami_warning_code: 6 entries, strategy switch
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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_WARNING_CODE_C1[] = "津波なし";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_WARNING_CODE_C2[] = "警報解除";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_WARNING_CODE_C3[] = "津波警報";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_WARNING_CODE_C4[] = "大津波警報";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_WARNING_CODE_C5[] = "大津波警報：発表";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_WARNING_CODE_C15[] = "その他の警報";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_tsunami_warning_code_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMI_WARNING_CODE_C1), 12);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMI_WARNING_CODE_C2), 12);
        case 3: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMI_WARNING_CODE_C3), 12);
        case 4: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMI_WARNING_CODE_C4), 15);
        case 5: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMI_WARNING_CODE_C5), 24);
        case 15: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMI_WARNING_CODE_C15), 18);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_warning_code_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"津波なし", 12};
        case 2: return std::string_view{"警報解除", 12};
        case 3: return std::string_view{"津波警報", 12};
        case 4: return std::string_view{"大津波警報", 15};
        case 5: return std::string_view{"大津波警報：発表", 24};
        case 15: return std::string_view{"その他の警報", 18};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_tsunami_warning_code_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_warning_code_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
