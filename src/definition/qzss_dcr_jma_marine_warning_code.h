#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.marine_warning_code
// Variable      : qzss_dcr_jma_marine_warning_code
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

#if (AZARAC_ENABLE_MARINE) && (AZARAC_LANG_JA)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_WARNING_CODE_PARENT_POOL[] = "海上\000";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_marine_warning_code_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "警報解除"; return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_PARENT_POOL) + 0u, AZARAC_PGM_PTR(s)); }
        case 10: { static const char AZARAC_PROGMEM s[] = "着氷警報"; return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_PARENT_POOL) + 0u, AZARAC_PGM_PTR(s)); }
        case 11: { static const char AZARAC_PROGMEM s[] = "濃霧警報"; return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_PARENT_POOL) + 0u, AZARAC_PGM_PTR(s)); }
        case 12: { static const char AZARAC_PROGMEM s[] = "うねり警報"; return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_PARENT_POOL) + 0u, AZARAC_PGM_PTR(s)); }
        case 20: { static const char AZARAC_PROGMEM s[] = "風警報"; return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_PARENT_POOL) + 0u, AZARAC_PGM_PTR(s)); }
        case 21: { static const char AZARAC_PROGMEM s[] = "強風警報"; return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_PARENT_POOL) + 0u, AZARAC_PGM_PTR(s)); }
        case 22: { static const char AZARAC_PROGMEM s[] = "暴風警報"; return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_PARENT_POOL) + 0u, AZARAC_PGM_PTR(s)); }
        case 23: { static const char AZARAC_PROGMEM s[] = "台風警報"; return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_WARNING_CODE_PARENT_POOL) + 0u, AZARAC_PGM_PTR(s)); }
        case 31: { static const char AZARAC_PROGMEM s[] = "その他の警報等情報要素_海上警報"; return azarac_pgm_view(AZARAC_PGM_PTR(s), 46); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_marine_warning_code_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"海上警報解除", 18};
        case 10: return std::string_view{"海上着氷警報", 18};
        case 11: return std::string_view{"海上濃霧警報", 18};
        case 12: return std::string_view{"海上うねり警報", 21};
        case 20: return std::string_view{"海上風警報", 15};
        case 21: return std::string_view{"海上強風警報", 18};
        case 22: return std::string_view{"海上暴風警報", 18};
        case 23: return std::string_view{"海上台風警報", 18};
        case 31: return std::string_view{"その他の警報等情報要素_海上警報", 46};
        default: return std::nullopt;
    }
}
#endif

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
