#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.camf.d_fields
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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_POOL[] = "0 < duration < 30 mi\00030 min ≤ duration < 45 mi\00045 min ≤ duration < 1\0001 h ≤ duration < 1 h 30 mi\0001 h 30 min ≤ duration < 2\0002 h ≤ duration < 3\0003 h ≤ duration < 4\0004 h ≤ duration < 5\0005 h ≤ duration < 10\00010 h ≤ duration < 24\00024 h ≤ duration < 2 days\0002 days ≤ duration < 7 days\0007 days ≤ duratio\000";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_PARENT_POOL[] = " h\000n\000";
struct QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_PARENT_Entry QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 2u},
    {3u, 1u},
};
struct QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_Entry { uint16_t offset; uint8_t len; uint8_t parent; };
static const QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_Entry QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_TABLE[] AZARAC_PROGMEM = {
    {0u, 20u, 1u},
    {21u, 27u, 1u},
    {49u, 23u, 0u},
    {73u, 28u, 1u},
    {102u, 27u, 0u},
    {130u, 20u, 0u},
    {151u, 20u, 0u},
    {172u, 20u, 0u},
    {193u, 21u, 0u},
    {215u, 22u, 0u},
    {238u, 26u, 255u},
    {265u, 28u, 255u},
    {294u, 18u, 1u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d29_outage_estimated_duration_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_BASE || id >= QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_BASE + QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_Entry, offset));
    uint8_t n = pgm_read_byte(p + offsetof(QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_Entry, len));
    uint8_t pi = pgm_read_byte(p + offsetof(QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_Entry, parent));
    if (pi == 255u) return azarac_pgm_view(QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_POOL + off, n);
    const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_PARENT_TABLE[pi]);
    uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_PARENT_Entry, offset));
    uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_PARENT_Entry, len));
    return azarac_pgm_join(QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_POOL + off, n, QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_PARENT_POOL + poff, pn);
}
#else
inline constexpr const char* QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_TABLE[] = {
    "0 < duration < 30 min",
    "30 min ≤ duration < 45 min",
    "45 min ≤ duration < 1 h",
    "1 h ≤ duration < 1 h 30 min",
    "1 h 30 min ≤ duration < 2 h",
    "2 h ≤ duration < 3 h",
    "3 h ≤ duration < 4 h",
    "4 h ≤ duration < 5 h",
    "5 h ≤ duration < 10 h",
    "10 h ≤ duration < 24 h",
    "24 h ≤ duration < 2 days",
    "2 days ≤ duration < 7 days",
    "7 days ≤ duration"
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d29_outage_estimated_duration_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_BASE || id >= QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_BASE + QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_SIZE) return std::nullopt;
    const char* s = QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_TABLE[id - QZSS_DCX_CAMF_D29_OUTAGE_ESTIMATED_DURATION_BASE];
    return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
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
