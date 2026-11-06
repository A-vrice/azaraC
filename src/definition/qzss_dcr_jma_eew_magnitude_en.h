#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// Specs: IS-QZSS-DCR-017 / IS-QZSS-DCX-004 Rev.004 / EWSS CAMF Issue 1.2
// azarashi.definitions.qzss.dcr.eew_magnitude → qzss_dcr_jma_eew_magnitude_en: 102 entries, strategy binary_search
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

#if (AZARAC_ENABLE_EEW) && (AZARAC_LANG_EN)

static const char AZARAC_PROGMEM QZSS_DCR_JMA_EEW_MAGNITUDE_EN_POOL[] = "0.1\0000.2\0000.3\0000.4\0000.5\0000.6\0000.7\0000.8\0000.9\0001.0\0001.1\0001.2\0001.3\0001.4\0001.5\0001.6\0001.7\0001.8\0001.9\0002.0\0002.1\0002.2\0002.3\0002.4\0002.5\0002.6\0002.7\0002.8\0002.9\0003.0\0003.1\0003.2\0003.3\0003.4\0003.5\0003.6\0003.7\0003.8\0003.9\0004.0\0004.1\0004.2\0004.3\0004.4\0004.5\0004.6\0004.7\0004.8\0004.9\0005.0\0005.1\0005.2\0005.3\0005.4\0005.5\0005.6\0005.7\0005.8\0005.9\0006.0\0006.1\0006.2\0006.3\0006.4\0006.5\0006.6\0006.7\0006.8\0006.9\0007.0\0007.1\0007.2\0007.3\0007.4\0007.5\0007.6\0007.7\0007.8\0007.9\0008.0\0008.1\0008.2\0008.3\0008.4\0008.5\0008.6\0008.7\0008.8\0008.9\0009.0\0009.1\0009.2\0009.3\0009.4\0009.5\0009.6\0009.7\0009.8\0009.9\00010.0\000Over 10.0\000Unknown\000";
struct QZSS_DCR_JMA_EEW_MAGNITUDE_EN_Entry { uint8_t id; uint16_t offset; };
static const QZSS_DCR_JMA_EEW_MAGNITUDE_EN_Entry QZSS_DCR_JMA_EEW_MAGNITUDE_EN_TABLE[] AZARAC_PROGMEM = {
    {1u, 0u},
    {2u, 4u},
    {3u, 8u},
    {4u, 12u},
    {5u, 16u},
    {6u, 20u},
    {7u, 24u},
    {8u, 28u},
    {9u, 32u},
    {10u, 36u},
    {11u, 40u},
    {12u, 44u},
    {13u, 48u},
    {14u, 52u},
    {15u, 56u},
    {16u, 60u},
    {17u, 64u},
    {18u, 68u},
    {19u, 72u},
    {20u, 76u},
    {21u, 80u},
    {22u, 84u},
    {23u, 88u},
    {24u, 92u},
    {25u, 96u},
    {26u, 100u},
    {27u, 104u},
    {28u, 108u},
    {29u, 112u},
    {30u, 116u},
    {31u, 120u},
    {32u, 124u},
    {33u, 128u},
    {34u, 132u},
    {35u, 136u},
    {36u, 140u},
    {37u, 144u},
    {38u, 148u},
    {39u, 152u},
    {40u, 156u},
    {41u, 160u},
    {42u, 164u},
    {43u, 168u},
    {44u, 172u},
    {45u, 176u},
    {46u, 180u},
    {47u, 184u},
    {48u, 188u},
    {49u, 192u},
    {50u, 196u},
    {51u, 200u},
    {52u, 204u},
    {53u, 208u},
    {54u, 212u},
    {55u, 216u},
    {56u, 220u},
    {57u, 224u},
    {58u, 228u},
    {59u, 232u},
    {60u, 236u},
    {61u, 240u},
    {62u, 244u},
    {63u, 248u},
    {64u, 252u},
    {65u, 256u},
    {66u, 260u},
    {67u, 264u},
    {68u, 268u},
    {69u, 272u},
    {70u, 276u},
    {71u, 280u},
    {72u, 284u},
    {73u, 288u},
    {74u, 292u},
    {75u, 296u},
    {76u, 300u},
    {77u, 304u},
    {78u, 308u},
    {79u, 312u},
    {80u, 316u},
    {81u, 320u},
    {82u, 324u},
    {83u, 328u},
    {84u, 332u},
    {85u, 336u},
    {86u, 340u},
    {87u, 344u},
    {88u, 348u},
    {89u, 352u},
    {90u, 356u},
    {91u, 360u},
    {92u, 364u},
    {93u, 368u},
    {94u, 372u},
    {95u, 376u},
    {96u, 380u},
    {97u, 384u},
    {98u, 388u},
    {99u, 392u},
    {100u, 396u},
    {101u, 401u},
    {127u, 411u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_eew_magnitude_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 102;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        azarac_pgm_ptr ep = AZARAC_PGM_PTR(QZSS_DCR_JMA_EEW_MAGNITUDE_EN_TABLE) + static_cast<size_t>(mid) * sizeof(QZSS_DCR_JMA_EEW_MAGNITUDE_EN_Entry);
        uint8_t eid = static_cast<uint8_t>(azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_EEW_MAGNITUDE_EN_Entry, id)));
        if (eid == id) {
            uint16_t off = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_EEW_MAGNITUDE_EN_Entry, offset));
            return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_EEW_MAGNITUDE_EN_POOL) + off);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_eew_magnitude_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_eew_magnitude_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
