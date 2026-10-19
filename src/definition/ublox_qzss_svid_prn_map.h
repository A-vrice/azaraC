#pragma once
// HAND-MAINTAINED — NOT auto-generated. scripts/gen/gen_definitions.py lists this
// table in SKIP_MODULES (extra_headers) and never overwrites it, so nothing here
// tracks azarashi automatically. Keep in sync by hand with azarashi's
// azarashi.definitions.qzss.ubx.svid_to_prn (verified equal to azarashi 0.17.1:
// {1: 183, 2: 184, 3: 185, 4: 186, 7: 189}).
// Source module : ublox_qzss_svid_prn_map
// Variable      : ublox_qzss_svid_prn_map
// Entries       : 5
// Strategy      : switch

#if defined(__AVR__)
#include "../internal/avr_std/cstdint"
#else
#include <cstdint>
#endif
#if defined(__AVR__)
#include "../internal/avr_std/optional"
#else
#include <optional>
#endif
#if defined(__AVR__)
#include "../internal/avr_std/string_view"
#else
#include <string_view>
#endif
#include "../azaraC_config.h"
#include "../internal/FlashString.h"

namespace azaraC {
namespace def {

#if defined(__AVR__)

// Labels are namespace-scope arrays, not function-local statics: the Arduino core
// builds with LTO, which drops the `__section__` attribute of an inline function's
// local static (a one-only symbol), so such a label lands in .rodata — i.e. in
// SRAM. Same shape as the generated tables (see gen_definitions.py, switch_labels).
static const char AZARAC_PROGMEM UBLOX_QZSS_SVID_PRN_MAP_C1[] = "183";
static const char AZARAC_PROGMEM UBLOX_QZSS_SVID_PRN_MAP_C2[] = "184";
static const char AZARAC_PROGMEM UBLOX_QZSS_SVID_PRN_MAP_C3[] = "185";
static const char AZARAC_PROGMEM UBLOX_QZSS_SVID_PRN_MAP_C4[] = "186";
static const char AZARAC_PROGMEM UBLOX_QZSS_SVID_PRN_MAP_C7[] = "189";

[[nodiscard]] inline std::optional<std::string_view> ublox_qzss_svid_prn_map_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(UBLOX_QZSS_SVID_PRN_MAP_C1), 3);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(UBLOX_QZSS_SVID_PRN_MAP_C2), 3);
        case 3: return azarac_pgm_view(AZARAC_PGM_PTR(UBLOX_QZSS_SVID_PRN_MAP_C3), 3);
        case 4: return azarac_pgm_view(AZARAC_PGM_PTR(UBLOX_QZSS_SVID_PRN_MAP_C4), 3);
        case 7: return azarac_pgm_view(AZARAC_PGM_PTR(UBLOX_QZSS_SVID_PRN_MAP_C7), 3);
        default: return std::nullopt;
    }
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> ublox_qzss_svid_prn_map_lookup(uint8_t id) {
    switch (id) {
        case 1: return std::string_view{"183", 3};
        case 2: return std::string_view{"184", 3};
        case 3: return std::string_view{"185", 3};
        case 4: return std::string_view{"186", 3};
        case 7: return std::string_view{"189", 3};
        default: return std::nullopt;
    }
}

#endif

} // namespace def
} // namespace azaraC
