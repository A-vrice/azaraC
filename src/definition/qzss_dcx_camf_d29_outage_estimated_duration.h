#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_d29_outage_estimated_duration
// Variable      : qzss_dcx_camf_d29_outage_estimated_duration
// Entries       : 13
// Strategy      : array

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

inline constexpr uint8_t QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_SIZE = 13;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_POOL[] = "0 < duration < 30 min\030 min ≤ duration < 45 min\045 min ≤ duration < 1 h\01 h ≤ duration < 1 h 30 min\01 h 30 min ≤ duration < 2 h\02 h ≤ duration < 3 h\03 h ≤ duration < 4 h\04 h ≤ duration < 5 h\05 h ≤ duration < 10 h\010 h ≤ duration < 24 h\024 h ≤ duration < 2 days\02 days ≤ duration < 7 days\07 days ≤ duration\0";
struct QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_Entry QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_TABLE[] AZARAC_PROGMEM = {
    {0u, 21u},
    {22u, 28u},
    {51u, 25u},
    {77u, 29u},
    {107u, 29u},
    {137u, 22u},
    {160u, 22u},
    {183u, 22u},
    {206u, 23u},
    {230u, 24u},
    {255u, 26u},
    {282u, 28u},
    {311u, 19u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d29_outage_estimated_duration_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_BASE || id >= QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_BASE + QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_Entry, len));
    if (n == 0) return std::nullopt;
    return azarac_pgm_view(QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_POOL + off, n);
}
#else
inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_TABLE[] = {
    std::string_view{"0 < duration < 30 min", 21},
    std::string_view{"30 min ≤ duration < 45 min", 28},
    std::string_view{"45 min ≤ duration < 1 h", 25},
    std::string_view{"1 h ≤ duration < 1 h 30 min", 29},
    std::string_view{"1 h 30 min ≤ duration < 2 h", 29},
    std::string_view{"2 h ≤ duration < 3 h", 22},
    std::string_view{"3 h ≤ duration < 4 h", 22},
    std::string_view{"4 h ≤ duration < 5 h", 22},
    std::string_view{"5 h ≤ duration < 10 h", 23},
    std::string_view{"10 h ≤ duration < 24 h", 24},
    std::string_view{"24 h ≤ duration < 2 days", 26},
    std::string_view{"2 days ≤ duration < 7 days", 28},
    std::string_view{"7 days ≤ duration", 19}
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d29_outage_estimated_duration_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_BASE || id >= QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_BASE + QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_TABLE[id - QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_BASE];
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d29_outage_estimated_duration_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d29_outage_estimated_duration_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
