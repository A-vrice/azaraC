#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// Specs: IS-QZSS-DCR-017 / IS-QZSS-DCX-004 Rev.004 / EWSS CAMF Issue 1.2
// azarashi.definitions.qzss.dcr.marine_warning_code → qzss_dcr_jma_marine_warning_code: 9 entries, strategy switch
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

#if (AZARAC_ENABLE_MARINE) && (AZARAC_LANG_JA)

static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_C0[] = "警報解除";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_C10[] = "着氷警報";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_C11[] = "濃霧警報";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_C12[] = "うねり警報";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_C20[] = "風警報";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_C21[] = "強風警報";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_C22[] = "暴風警報";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_C23[] = "台風警報";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_C31[] = "その他の警報等情報要素_海上警報";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_PARENT_POOL[] = "海上\000";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_marine_warning_code_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_C0));
        case 10: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_C10));
        case 11: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_C11));
        case 12: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_C12));
        case 20: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_C20));
        case 21: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_C21));
        case 22: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_C22));
        case 23: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_C23));
        case 31: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_C31), 46);
        default: return std::nullopt;
    }
}

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_marine_warning_code_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_marine_warning_code_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
