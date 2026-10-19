#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.flood_warning_level → qzss_dcr_jma_flood_warning_level: 5 entries, strategy switch
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

#if (AZARAC_ENABLE_FLOOD) && (AZARAC_LANG_JA)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_flood_warning_level_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: { static const char AZARAC_PROGMEM s[] = "警報解除"; return azarac_pgm_view(AZARAC_PGM_PTR(s), 12); }
        case 2: { static const char AZARAC_PROGMEM s[] = "氾濫警戒情報"; return azarac_pgm_view(AZARAC_PGM_PTR(s), 18); }
        case 3: { static const char AZARAC_PROGMEM s[] = "氾濫危険情報"; return azarac_pgm_view(AZARAC_PGM_PTR(s), 18); }
        case 4: { static const char AZARAC_PROGMEM s[] = "氾濫発生情報"; return azarac_pgm_view(AZARAC_PGM_PTR(s), 18); }
        case 15: { static const char AZARAC_PROGMEM s[] = "その他の警戒レベル"; return azarac_pgm_view(AZARAC_PGM_PTR(s), 27); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_flood_warning_level_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"警報解除", 12};
        case 2: return std::string_view{"氾濫警戒情報", 18};
        case 3: return std::string_view{"氾濫危険情報", 18};
        case 4: return std::string_view{"氾濫発生情報", 18};
        case 15: return std::string_view{"その他の警戒レベル", 27};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_flood_warning_level_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_flood_warning_level_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
