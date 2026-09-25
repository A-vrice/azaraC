#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_c10_instruction_library_for_second_ellipse
// Variable      : qzss_dcx_camf_c10_instruction_library_for_second_ellipse_code
// Entries       : 19
// Strategy      : binary_search

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

#if (AZARAC_ENABLE_DCX_CAMF)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_POOL[] = "IC-C-01\000IC-C-02\000IC-C-03\000IC-C-04\000IC-C-05\000IC-C-06\000IC-C-07\000IC-C-08\000IC-C-09\000IC-C-10\000IC-C-11\000IC-C-12\000IC-C-13\000IC-C-14\000IC-C-15\000IC-C-16\000IC-C-17\000IC-C-31\000IC-C-32\000";
struct QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_Entry { uint8_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_Entry QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_TABLE[] AZARAC_PROGMEM = {
    {0u, 0u, 7u},
    {1u, 8u, 7u},
    {2u, 16u, 7u},
    {3u, 24u, 7u},
    {4u, 32u, 7u},
    {5u, 40u, 7u},
    {6u, 48u, 7u},
    {7u, 56u, 7u},
    {8u, 64u, 7u},
    {9u, 72u, 7u},
    {10u, 80u, 7u},
    {11u, 88u, 7u},
    {12u, 96u, 7u},
    {13u, 104u, 7u},
    {14u, 112u, 7u},
    {15u, 120u, 7u},
    {16u, 128u, 7u},
    {30u, 136u, 7u},
    {31u, 144u, 7u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_c10_instruction_library_for_second_ellipse_code_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 19;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_Entry, len));
            return azarac_pgm_view(QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_Entry { uint8_t id; const char* label; };
inline constexpr QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_Entry QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_TABLE[] = {
    {0u, "IC-C-01"},
    {1u, "IC-C-02"},
    {2u, "IC-C-03"},
    {3u, "IC-C-04"},
    {4u, "IC-C-05"},
    {5u, "IC-C-06"},
    {6u, "IC-C-07"},
    {7u, "IC-C-08"},
    {8u, "IC-C-09"},
    {9u, "IC-C-10"},
    {10u, "IC-C-11"},
    {11u, "IC-C-12"},
    {12u, "IC-C-13"},
    {13u, "IC-C-14"},
    {14u, "IC-C-15"},
    {15u, "IC-C-16"},
    {16u, "IC-C-17"},
    {30u, "IC-C-31"},
    {31u, "IC-C-32"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_c10_instruction_library_for_second_ellipse_code_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 19;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_TABLE[mid].id == id) {
            const char* s = QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_c10_instruction_library_for_second_ellipse_code_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_c10_instruction_library_for_second_ellipse_code_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
