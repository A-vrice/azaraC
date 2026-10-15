#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.typhoon_elapsed_time_from_reference_time
// Variable      : qzss_dcr_jma_typhoon_elapsed_time_from_reference_time
// Entries       : 128
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

#if (AZARAC_ENABLE_TYPHOON) && (AZARAC_LANG_JA)

inline constexpr uint8_t QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_BASE = 0;
inline constexpr uint8_t QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_SIZE = 128;
#if defined(__AVR__)
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
inline constexpr const char* QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_TABLE[] = {
    "0時間後",
    "1時間後",
    "2時間後",
    "3時間後",
    "4時間後",
    "5時間後",
    "6時間後",
    "7時間後",
    "8時間後",
    "9時間後",
    "10時間後",
    "11時間後",
    "12時間後",
    "13時間後",
    "14時間後",
    "15時間後",
    "16時間後",
    "17時間後",
    "18時間後",
    "19時間後",
    "20時間後",
    "21時間後",
    "22時間後",
    "23時間後",
    "24時間後",
    "25時間後",
    "26時間後",
    "27時間後",
    "28時間後",
    "29時間後",
    "30時間後",
    "31時間後",
    "32時間後",
    "33時間後",
    "34時間後",
    "35時間後",
    "36時間後",
    "37時間後",
    "38時間後",
    "39時間後",
    "40時間後",
    "41時間後",
    "42時間後",
    "43時間後",
    "44時間後",
    "45時間後",
    "46時間後",
    "47時間後",
    "48時間後",
    "49時間後",
    "50時間後",
    "51時間後",
    "52時間後",
    "53時間後",
    "54時間後",
    "55時間後",
    "56時間後",
    "57時間後",
    "58時間後",
    "59時間後",
    "60時間後",
    "61時間後",
    "62時間後",
    "63時間後",
    "64時間後",
    "65時間後",
    "66時間後",
    "67時間後",
    "68時間後",
    "69時間後",
    "70時間後",
    "71時間後",
    "72時間後",
    "73時間後",
    "74時間後",
    "75時間後",
    "76時間後",
    "77時間後",
    "78時間後",
    "79時間後",
    "80時間後",
    "81時間後",
    "82時間後",
    "83時間後",
    "84時間後",
    "85時間後",
    "86時間後",
    "87時間後",
    "88時間後",
    "89時間後",
    "90時間後",
    "91時間後",
    "92時間後",
    "93時間後",
    "94時間後",
    "95時間後",
    "96時間後",
    "97時間後",
    "98時間後",
    "99時間後",
    "100時間後",
    "101時間後",
    "102時間後",
    "103時間後",
    "104時間後",
    "105時間後",
    "106時間後",
    "107時間後",
    "108時間後",
    "109時間後",
    "110時間後",
    "111時間後",
    "112時間後",
    "113時間後",
    "114時間後",
    "115時間後",
    "116時間後",
    "117時間後",
    "118時間後",
    "119時間後",
    "120時間後",
    "121時間後",
    "122時間後",
    "123時間後",
    "124時間後",
    "125時間後",
    "126時間後",
    "127時間後"
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_BASE || id >= QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_BASE + QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_SIZE) return std::nullopt;
    const char* s = QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_TABLE[id - QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_BASE];
    return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
}
#endif

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
