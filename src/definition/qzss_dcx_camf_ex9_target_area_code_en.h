#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_ex9_target_area_code_en
// Variable      : qzss_dcx_camf_ex9_target_area_code_en
// Entries       : 47
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

#if (AZARAC_ENABLE_DCX_CAMF) && (AZARAC_LANG_EN)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_POOL[] = "Hokkaido\000Aomori\000Iwate\000Miyagi\000Akita\000Yamagata\000Fukushima\000Ibaraki\000Tochigi\000Gunma\000Saitama\000Chiba\000Tokyo\000Kanagawa\000Niigata\000Toyama\000Ishikawa\000Fukui\000Yamanashi\000Nagano\000Gifu\000Shizuoka\000Aichi\000Mie\000Shiga\000Kyoto\000Osaka\000Hyogo\000Nara\000Wakayama\000Tottori\000Shimane\000Okayama\000Hiroshima\000Yamaguchi\000Tokushima\000Kagawa\000Ehime\000Kochi\000Fukuoka\000Saga\000Nagasaki\000Kumamoto\000Oita\000Miyazaki\000Kagoshima\000Okinawa\000";
struct QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_Entry { uint64_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_Entry QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_TABLE[] AZARAC_PROGMEM = {
    {1u, 0u, 8u},
    {2u, 9u, 6u},
    {4u, 16u, 5u},
    {8u, 22u, 6u},
    {16u, 29u, 5u},
    {32u, 35u, 8u},
    {64u, 44u, 9u},
    {128u, 54u, 7u},
    {256u, 62u, 7u},
    {512u, 70u, 5u},
    {1024u, 76u, 7u},
    {2048u, 84u, 5u},
    {4096u, 90u, 5u},
    {8192u, 96u, 8u},
    {16384u, 105u, 7u},
    {32768u, 113u, 6u},
    {65536u, 120u, 8u},
    {131072u, 129u, 5u},
    {262144u, 135u, 9u},
    {524288u, 145u, 6u},
    {1048576u, 152u, 4u},
    {2097152u, 157u, 8u},
    {4194304u, 166u, 5u},
    {8388608u, 172u, 3u},
    {16777216u, 176u, 5u},
    {33554432u, 182u, 5u},
    {67108864u, 188u, 5u},
    {134217728u, 194u, 5u},
    {268435456u, 200u, 4u},
    {536870912u, 205u, 8u},
    {1073741824u, 214u, 7u},
    {2147483648u, 222u, 7u},
    {4294967296u, 230u, 7u},
    {8589934592u, 238u, 9u},
    {17179869184u, 248u, 9u},
    {34359738368u, 258u, 9u},
    {68719476736u, 268u, 6u},
    {137438953472u, 275u, 5u},
    {274877906944u, 281u, 5u},
    {549755813888u, 287u, 7u},
    {1099511627776u, 295u, 4u},
    {2199023255552u, 300u, 8u},
    {4398046511104u, 309u, 8u},
    {8796093022208u, 318u, 4u},
    {17592186044416u, 323u, 8u},
    {35184372088832u, 332u, 9u},
    {70368744177664u, 342u, 7u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_ex9_target_area_code_en_lookup(uint64_t id) noexcept {
    uint8_t lo = 0, hi = 47;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_TABLE[mid]);
        uint64_t eid = (static_cast<uint64_t>(pgm_read_dword(ep + offsetof(QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_Entry, id) + 4)) << 32) | pgm_read_dword(ep + offsetof(QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_Entry, id));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_Entry, len));
            return azarac_pgm_view(QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_Entry { uint64_t id; const char* label; };
inline constexpr QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_Entry QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_TABLE[] = {
    {1u, "Hokkaido"},
    {2u, "Aomori"},
    {4u, "Iwate"},
    {8u, "Miyagi"},
    {16u, "Akita"},
    {32u, "Yamagata"},
    {64u, "Fukushima"},
    {128u, "Ibaraki"},
    {256u, "Tochigi"},
    {512u, "Gunma"},
    {1024u, "Saitama"},
    {2048u, "Chiba"},
    {4096u, "Tokyo"},
    {8192u, "Kanagawa"},
    {16384u, "Niigata"},
    {32768u, "Toyama"},
    {65536u, "Ishikawa"},
    {131072u, "Fukui"},
    {262144u, "Yamanashi"},
    {524288u, "Nagano"},
    {1048576u, "Gifu"},
    {2097152u, "Shizuoka"},
    {4194304u, "Aichi"},
    {8388608u, "Mie"},
    {16777216u, "Shiga"},
    {33554432u, "Kyoto"},
    {67108864u, "Osaka"},
    {134217728u, "Hyogo"},
    {268435456u, "Nara"},
    {536870912u, "Wakayama"},
    {1073741824u, "Tottori"},
    {2147483648u, "Shimane"},
    {4294967296u, "Okayama"},
    {8589934592u, "Hiroshima"},
    {17179869184u, "Yamaguchi"},
    {34359738368u, "Tokushima"},
    {68719476736u, "Kagawa"},
    {137438953472u, "Ehime"},
    {274877906944u, "Kochi"},
    {549755813888u, "Fukuoka"},
    {1099511627776u, "Saga"},
    {2199023255552u, "Nagasaki"},
    {4398046511104u, "Kumamoto"},
    {8796093022208u, "Oita"},
    {17592186044416u, "Miyazaki"},
    {35184372088832u, "Kagoshima"},
    {70368744177664u, "Okinawa"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_ex9_target_area_code_en_lookup(uint64_t id) noexcept {
    uint8_t lo = 0, hi = 47;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_TABLE[mid].id == id) {
            const char* s = QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_ex9_target_area_code_en_lookup(uint64_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_ex9_target_area_code_en_lookup(uint64_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
