#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.seismic_intensity_upper_limit → qzss_dcr_jma_seismic_intensity_upper_limit: 13 entries, strategy binary_search
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

#if (AZARAC_ENABLE_EEW) && (AZARAC_LANG_JA)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_POOL[] = "0\0001\0002\0003\0004\0005弱\0005強\0006弱\0006強\0007\000〜程度以上\000なし\000不明\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_PARENT_POOL[] = "震度\000";
struct QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_PARENT_Entry QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
};
struct QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_Entry { uint8_t id; uint8_t parent; uint16_t offset; };
static const QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_Entry QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_TABLE[] AZARAC_PROGMEM = {
    {1u, 0u, 0u},
    {2u, 0u, 2u},
    {3u, 0u, 4u},
    {4u, 0u, 6u},
    {5u, 0u, 8u},
    {6u, 0u, 10u},
    {7u, 0u, 15u},
    {8u, 0u, 20u},
    {9u, 0u, 25u},
    {10u, 0u, 30u},
    {11u, 255u, 32u},
    {14u, 255u, 48u},
    {15u, 255u, 55u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_upper_limit_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 13;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        azarac_pgm_ptr ep = AZARAC_PGM_PTR(QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_TABLE) + static_cast<size_t>(mid) * sizeof(QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_Entry);
        uint8_t eid = static_cast<uint8_t>(azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_Entry, id)));
        if (eid == id) {
            uint16_t off = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_Entry, offset));
            uint8_t pi = azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_Entry, parent));
            if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_POOL) + off);
            azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_PARENT_Entry);
            uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_PARENT_Entry, offset));
            return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_PARENT_POOL) + poff, AZARAC_PGM_PTR(QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_POOL) + off);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_Entry { uint8_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_Entry QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_TABLE[] = {
    {1u, "震度0"},
    {2u, "震度1"},
    {3u, "震度2"},
    {4u, "震度3"},
    {5u, "震度4"},
    {6u, "震度5弱"},
    {7u, "震度5強"},
    {8u, "震度6弱"},
    {9u, "震度6強"},
    {10u, "震度7"},
    {11u, "〜程度以上"},
    {14u, "なし"},
    {15u, "不明"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_upper_limit_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 13;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_SEISMIC_INTENSITY_UPPER_LIMIT_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
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
