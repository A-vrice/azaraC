#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_seismic_intensity_upper_limit
// Variable      : qzss_dcr_jma_seismic_intensity_upper_limit
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

#if (AZARAC_ENABLE_EEW)

inline constexpr uint8_t QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_BASE = 1;
inline constexpr uint8_t QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_SIZE = 13;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_POOL[] = "震度0\0震度1\0震度2\0震度3\0震度4\0震度5弱\0震度5強\0震度6弱\0震度6強\0震度7\0〜程度以上\0なし\0不明\0";
struct QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_Entry QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_TABLE[] AZARAC_PROGMEM = {
    {0u, 7u},
    {8u, 7u},
    {16u, 7u},
    {24u, 7u},
    {32u, 7u},
    {40u, 10u},
    {51u, 10u},
    {62u, 10u},
    {73u, 10u},
    {84u, 7u},
    {92u, 15u},
    {108u, 6u},
    {115u, 6u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_upper_limit_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_BASE || id >= QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_BASE + QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_TABLE[id - 1u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_Entry, len));
    if (n == 0) return std::nullopt;
    return azarac_pgm_view(QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_POOL + off, n);
}
#else
inline constexpr std::optional<std::string_view> QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_TABLE[] = {
    std::string_view{"震度0", 7},
    std::string_view{"震度1", 7},
    std::string_view{"震度2", 7},
    std::string_view{"震度3", 7},
    std::string_view{"震度4", 7},
    std::string_view{"震度5弱", 10},
    std::string_view{"震度5強", 10},
    std::string_view{"震度6弱", 10},
    std::string_view{"震度6強", 10},
    std::string_view{"震度7", 7},
    std::string_view{"〜程度以上", 15},
    std::string_view{"なし", 6},
    std::string_view{"不明", 6}
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_upper_limit_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_BASE || id >= QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_BASE + QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_SIZE) return std::nullopt;
    return QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_TABLE[id - QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_BASE];
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_upper_limit_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_upper_limit_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
