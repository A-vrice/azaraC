#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.camf.c10_instruction_library_for_second_ellipse
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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_POOL[] = "1\0002\0003\0004\0005\0006\0007\0008\0009\0000\0001\0002\0003\0004\0005\0006\0007\00031\00032\000";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_PARENT_POOL[] = "IC-C-\000IC-C-0\000IC-C-1\000";
struct QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_PARENT_Entry { uint16_t offset; };
static const QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_PARENT_Entry QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {6u},
    {13u},
};
struct QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_Entry { uint8_t id; uint8_t parent; uint16_t offset; };
static const QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_Entry QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_TABLE[] AZARAC_PROGMEM = {
    {0u, 1u, 0u},
    {1u, 1u, 2u},
    {2u, 1u, 4u},
    {3u, 1u, 6u},
    {4u, 1u, 8u},
    {5u, 1u, 10u},
    {6u, 1u, 12u},
    {7u, 1u, 14u},
    {8u, 1u, 16u},
    {9u, 2u, 18u},
    {10u, 2u, 20u},
    {11u, 2u, 22u},
    {12u, 2u, 24u},
    {13u, 2u, 26u},
    {14u, 2u, 28u},
    {15u, 2u, 30u},
    {16u, 2u, 32u},
    {30u, 0u, 34u},
    {31u, 0u, 37u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_c10_instruction_library_for_second_ellipse_code_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 19;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        azarac_pgm_ptr ep = AZARAC_PGM_PTR(QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_TABLE) + static_cast<size_t>(mid) * sizeof(QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_Entry);
        uint8_t eid = static_cast<uint8_t>(azarac_read_byte(ep, offsetof(QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_Entry, id)));
        if (eid == id) {
            uint16_t off = azarac_read_word(ep, offsetof(QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_Entry, offset));
            uint8_t pi = azarac_read_byte(ep, offsetof(QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_Entry, parent));
            if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_POOL) + off);
            azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_PARENT_Entry);
            uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_PARENT_Entry, offset));
            return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_PARENT_POOL) + poff, AZARAC_PGM_PTR(QZSS_DCX_CAMF_C10_INSTRUCTION_LIBRARY_FOR_SECOND_ELLIPSE_CODE_POOL) + off);
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
