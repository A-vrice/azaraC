#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_c10_instruction_library_for_second_ellipse_code
// Variable      : qzss_dcx_camf_c10_instruction_library_for_second_ellipse_code
// Entries       : 19
// Strategy      : binary_search

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"
#include "../internal/FlashString.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_DCX_CAMF)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_POOL[] = "IC-C-01\0IC-C-02\0IC-C-03\0IC-C-04\0IC-C-05\0IC-C-06\0IC-C-07\0IC-C-08\0IC-C-09\0IC-C-10\0IC-C-11\0IC-C-12\0IC-C-13\0IC-C-14\0IC-C-15\0IC-C-16\0IC-C-17\0IC-C-31\0IC-C-32\0";
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
            if (n == 0) return std::nullopt;
            return azarac_pgm_view(QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_Entry { uint8_t id; std::optional<std::string_view> label; };
inline constexpr QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_Entry QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_TABLE[] = {
    {0u, std::string_view{"IC-C-01", 7}},
    {1u, std::string_view{"IC-C-02", 7}},
    {2u, std::string_view{"IC-C-03", 7}},
    {3u, std::string_view{"IC-C-04", 7}},
    {4u, std::string_view{"IC-C-05", 7}},
    {5u, std::string_view{"IC-C-06", 7}},
    {6u, std::string_view{"IC-C-07", 7}},
    {7u, std::string_view{"IC-C-08", 7}},
    {8u, std::string_view{"IC-C-09", 7}},
    {9u, std::string_view{"IC-C-10", 7}},
    {10u, std::string_view{"IC-C-11", 7}},
    {11u, std::string_view{"IC-C-12", 7}},
    {12u, std::string_view{"IC-C-13", 7}},
    {13u, std::string_view{"IC-C-14", 7}},
    {14u, std::string_view{"IC-C-15", 7}},
    {15u, std::string_view{"IC-C-16", 7}},
    {16u, std::string_view{"IC-C-17", 7}},
    {30u, std::string_view{"IC-C-31", 7}},
    {31u, std::string_view{"IC-C-32", 7}},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_c10_instruction_library_for_second_ellipse_code_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 19;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_TABLE[mid].id == id) return QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_TABLE[mid].label;
        if (QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_c10_instruction_library_for_second_ellipse_code_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
