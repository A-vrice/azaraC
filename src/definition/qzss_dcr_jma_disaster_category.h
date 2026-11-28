#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// Specs: IS-QZSS-DCR-017 / IS-QZSS-DCX-004 Rev.004 / EWSS CAMF Issue 1.2
// azarashi.definitions.qzss.dcr.disaster_category → qzss_dcr_jma_disaster_category: 12 entries, strategy binary_search
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

#if (AZARAC_LANG_JA)

static const char AZARAC_PROGMEM QZSS_DCR_JMA_DISASTER_CATEGORY_POOL[] = "緊急地震速報\000震源\000震度\000南海トラフ地震\000津波\000北西太平洋津波\000火山\000降灰\000気象\000洪水\000台風\000海上\000";
struct QZSS_DCR_JMA_DISASTER_CATEGORY_Entry { uint8_t id; uint16_t offset; };
static const QZSS_DCR_JMA_DISASTER_CATEGORY_Entry QZSS_DCR_JMA_DISASTER_CATEGORY_TABLE[] AZARAC_PROGMEM = {
    {1u, 0u},
    {2u, 19u},
    {3u, 26u},
    {4u, 33u},
    {5u, 55u},
    {6u, 62u},
    {8u, 84u},
    {9u, 91u},
    {10u, 98u},
    {11u, 105u},
    {12u, 112u},
    {14u, 119u},
};
[[nodiscard]] inline const char* qzss_dcr_jma_disaster_category_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 12;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        azarac_pgm_ptr ep = AZARAC_PGM_PTR(QZSS_DCR_JMA_DISASTER_CATEGORY_TABLE) + static_cast<size_t>(mid) * sizeof(QZSS_DCR_JMA_DISASTER_CATEGORY_Entry);
        uint8_t eid = static_cast<uint8_t>(azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_DISASTER_CATEGORY_Entry, id)));
        if (eid == id) {
            uint16_t off = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_DISASTER_CATEGORY_Entry, offset));
            return azarac_pgm_copy(AZARAC_PGM_PTR(QZSS_DCR_JMA_DISASTER_CATEGORY_POOL) + off);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return nullptr;
}

#else

[[nodiscard]] inline constexpr const char* qzss_dcr_jma_disaster_category_lookup(uint8_t id) noexcept {
    (void)id;
    return nullptr;
}

#endif

} // namespace def
} // namespace azaraC
