#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// Specs: IS-QZSS-DCR-017 / IS-QZSS-DCX-004 Rev.004 / EWSS CAMF Issue 1.2
// azarashi.definitions.qzss.dcr.disaster_category → qzss_dcr_jma_disaster_category_en: 12 entries, strategy binary_search
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

#if (AZARAC_LANG_EN)

static const char AZARAC_PROGMEM QZSS_DCR_JMA_DISASTER_CATEGORY_EN_POOL[] = "Earthquake Early Warning\000Hypocenter\000Seismic Intensity\000Nankai Trough Earthquake\000Tsunami\000Northwest Pacific Tsunami\000Volcano\000Ash Fall\000Weather\000Flood\000Typhoon\000Marine\000";
struct QZSS_DCR_JMA_DISASTER_CATEGORY_EN_Entry { uint8_t id; uint16_t offset; };
static const QZSS_DCR_JMA_DISASTER_CATEGORY_EN_Entry QZSS_DCR_JMA_DISASTER_CATEGORY_EN_TABLE[] AZARAC_PROGMEM = {
    {1u, 0u},
    {2u, 25u},
    {3u, 36u},
    {4u, 54u},
    {5u, 79u},
    {6u, 87u},
    {8u, 113u},
    {9u, 121u},
    {10u, 130u},
    {11u, 138u},
    {12u, 144u},
    {14u, 152u},
};
[[nodiscard]] inline const char* qzss_dcr_jma_disaster_category_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 12;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        azarac_pgm_ptr ep = AZARAC_PGM_PTR(QZSS_DCR_JMA_DISASTER_CATEGORY_EN_TABLE) + static_cast<size_t>(mid) * sizeof(QZSS_DCR_JMA_DISASTER_CATEGORY_EN_Entry);
        uint8_t eid = static_cast<uint8_t>(azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_DISASTER_CATEGORY_EN_Entry, id)));
        if (eid == id) {
            uint16_t off = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_DISASTER_CATEGORY_EN_Entry, offset));
            return azarac_pgm_copy(AZARAC_PGM_PTR(QZSS_DCR_JMA_DISASTER_CATEGORY_EN_POOL) + off);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return nullptr;
}

#else

[[nodiscard]] inline constexpr const char* qzss_dcr_jma_disaster_category_en_lookup(uint8_t id) noexcept {
    (void)id;
    return nullptr;
}

#endif

} // namespace def
} // namespace azaraC
