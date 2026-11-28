#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// Specs: IS-QZSS-DCR-017 / IS-QZSS-DCX-004 Rev.004 / EWSS CAMF Issue 1.2
// azarashi.definitions.qzss.dcr.typhoon_elapsed_time_from_reference_time → qzss_dcr_jma_typhoon_elapsed_time_from_reference_time: 128 entries, strategy array
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

#if (AZARAC_ENABLE_TYPHOON) && (AZARAC_LANG_JA)

inline constexpr uint8_t QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_BASE = 0;
inline constexpr uint8_t QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_SIZE = 128;
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_POOL[] = "0\0001\0002\0003\0004\0005\0006\0007\0008\0009\0001\0001\0001\0001\0001\0001\0001\0001\0001\0001\0002\0002\0002\0002\0002\0002\0002\0002\0002\0002\0003\0003\0003\0003\0003\0003\0003\0003\0003\0003\0004\0004\0004\0004\0004\0004\0004\0004\0004\0004\0005\0005\0005\0005\0005\0005\0005\0005\0005\0005\0006\0006\0006\0006\0006\0006\0006\0006\0006\0006\0007\0007\0007\0007\0007\0007\0007\0007\0007\0007\0008\0008\0008\0008\0008\0008\0008\0008\0008\0008\0009\0009\0009\0009\0009\0009\0009\0009\0009\0009\00010\00010\00010\00010\00010\00010\00010\00010\00010\00010\00011\00011\00011\00011\00011\00011\00011\00011\00011\00011\00012\00012\00012\00012\00012\00012\00012\00012\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_PARENT_POOL[] = "0時間後\0001時間後\0002時間後\0003時間後\0004時間後\0005時間後\0006時間後\0007時間後\0008時間後\0009時間後\000時間後\000";
struct QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_PARENT_Entry QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {11u},
    {22u},
    {33u},
    {44u},
    {55u},
    {66u},
    {77u},
    {88u},
    {99u},
    {110u},
};
struct QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_Entry { uint16_t offset; uint8_t parent; };
static const QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_Entry QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_TABLE[] AZARAC_PROGMEM = {
    {0u, 10u},
    {2u, 10u},
    {4u, 10u},
    {6u, 10u},
    {8u, 10u},
    {10u, 10u},
    {12u, 10u},
    {14u, 10u},
    {16u, 10u},
    {18u, 10u},
    {20u, 0u},
    {22u, 1u},
    {24u, 2u},
    {26u, 3u},
    {28u, 4u},
    {30u, 5u},
    {32u, 6u},
    {34u, 7u},
    {36u, 8u},
    {38u, 9u},
    {40u, 0u},
    {42u, 1u},
    {44u, 2u},
    {46u, 3u},
    {48u, 4u},
    {50u, 5u},
    {52u, 6u},
    {54u, 7u},
    {56u, 8u},
    {58u, 9u},
    {60u, 0u},
    {62u, 1u},
    {64u, 2u},
    {66u, 3u},
    {68u, 4u},
    {70u, 5u},
    {72u, 6u},
    {74u, 7u},
    {76u, 8u},
    {78u, 9u},
    {80u, 0u},
    {82u, 1u},
    {84u, 2u},
    {86u, 3u},
    {88u, 4u},
    {90u, 5u},
    {92u, 6u},
    {94u, 7u},
    {96u, 8u},
    {98u, 9u},
    {100u, 0u},
    {102u, 1u},
    {104u, 2u},
    {106u, 3u},
    {108u, 4u},
    {110u, 5u},
    {112u, 6u},
    {114u, 7u},
    {116u, 8u},
    {118u, 9u},
    {120u, 0u},
    {122u, 1u},
    {124u, 2u},
    {126u, 3u},
    {128u, 4u},
    {130u, 5u},
    {132u, 6u},
    {134u, 7u},
    {136u, 8u},
    {138u, 9u},
    {140u, 0u},
    {142u, 1u},
    {144u, 2u},
    {146u, 3u},
    {148u, 4u},
    {150u, 5u},
    {152u, 6u},
    {154u, 7u},
    {156u, 8u},
    {158u, 9u},
    {160u, 0u},
    {162u, 1u},
    {164u, 2u},
    {166u, 3u},
    {168u, 4u},
    {170u, 5u},
    {172u, 6u},
    {174u, 7u},
    {176u, 8u},
    {178u, 9u},
    {180u, 0u},
    {182u, 1u},
    {184u, 2u},
    {186u, 3u},
    {188u, 4u},
    {190u, 5u},
    {192u, 6u},
    {194u, 7u},
    {196u, 8u},
    {198u, 9u},
    {200u, 0u},
    {203u, 1u},
    {206u, 2u},
    {209u, 3u},
    {212u, 4u},
    {215u, 5u},
    {218u, 6u},
    {221u, 7u},
    {224u, 8u},
    {227u, 9u},
    {230u, 0u},
    {233u, 1u},
    {236u, 2u},
    {239u, 3u},
    {242u, 4u},
    {245u, 5u},
    {248u, 6u},
    {251u, 7u},
    {254u, 8u},
    {257u, 9u},
    {260u, 0u},
    {263u, 1u},
    {266u, 2u},
    {269u, 3u},
    {272u, 4u},
    {275u, 5u},
    {278u, 6u},
    {281u, 7u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_BASE || id >= QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_BASE + QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_SIZE) return std::nullopt;
    azarac_pgm_ptr p = AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_TABLE) + static_cast<size_t>(id - 0u) * sizeof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_Entry);
    uint16_t off = azarac_read_word(p, offsetof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_Entry, offset));
    uint8_t pi = azarac_read_byte(p, offsetof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_Entry, parent));
    if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_POOL) + off);
    azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_PARENT_Entry);
    uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_PARENT_Entry, offset));
    return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_POOL) + off, AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_PARENT_POOL) + poff);
}

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
