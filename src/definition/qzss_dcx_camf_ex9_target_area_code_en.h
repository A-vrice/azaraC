#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_ex9_target_area_code_en
// Variable      : qzss_dcx_camf_ex9_target_area_code_en
// Entries       : 47
// Strategy      : binary_search

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"
#include "../internal/FlashString.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_DCX_CAMF) && (AZARAC_LANG_EN)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_POOL[] = "Hokkaido\0Aomori\0Iwate\0Miyagi\0Akita\0Yamagata\0Fukushima\0Ibaraki\0Tochigi\0Gunma\0Saitama\0Chiba\0Tokyo\0Kanagawa\0Niigata\0Toyama\0Ishikawa\0Fukui\0Yamanashi\0Nagano\0Gifu\0Shizuoka\0Aichi\0Mie\0Shiga\0Kyoto\0Osaka\0Hyogo\0Nara\0Wakayama\0Tottori\0Shimane\0Okayama\0Hiroshima\0Yamaguchi\0Tokushima\0Kagawa\0Ehime\0Kochi\0Fukuoka\0Saga\0Nagasaki\0Kumamoto\0Oita\0Miyazaki\0Kagoshima\0Okinawa\0";
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
            if (n == 0) return std::nullopt;
            return azarac_pgm_view(QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_Entry { uint64_t id; std::optional<std::string_view> label; };
inline constexpr QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_Entry QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_TABLE[] = {
    {1u, std::string_view{"Hokkaido", 8}},
    {2u, std::string_view{"Aomori", 6}},
    {4u, std::string_view{"Iwate", 5}},
    {8u, std::string_view{"Miyagi", 6}},
    {16u, std::string_view{"Akita", 5}},
    {32u, std::string_view{"Yamagata", 8}},
    {64u, std::string_view{"Fukushima", 9}},
    {128u, std::string_view{"Ibaraki", 7}},
    {256u, std::string_view{"Tochigi", 7}},
    {512u, std::string_view{"Gunma", 5}},
    {1024u, std::string_view{"Saitama", 7}},
    {2048u, std::string_view{"Chiba", 5}},
    {4096u, std::string_view{"Tokyo", 5}},
    {8192u, std::string_view{"Kanagawa", 8}},
    {16384u, std::string_view{"Niigata", 7}},
    {32768u, std::string_view{"Toyama", 6}},
    {65536u, std::string_view{"Ishikawa", 8}},
    {131072u, std::string_view{"Fukui", 5}},
    {262144u, std::string_view{"Yamanashi", 9}},
    {524288u, std::string_view{"Nagano", 6}},
    {1048576u, std::string_view{"Gifu", 4}},
    {2097152u, std::string_view{"Shizuoka", 8}},
    {4194304u, std::string_view{"Aichi", 5}},
    {8388608u, std::string_view{"Mie", 3}},
    {16777216u, std::string_view{"Shiga", 5}},
    {33554432u, std::string_view{"Kyoto", 5}},
    {67108864u, std::string_view{"Osaka", 5}},
    {134217728u, std::string_view{"Hyogo", 5}},
    {268435456u, std::string_view{"Nara", 4}},
    {536870912u, std::string_view{"Wakayama", 8}},
    {1073741824u, std::string_view{"Tottori", 7}},
    {2147483648u, std::string_view{"Shimane", 7}},
    {4294967296u, std::string_view{"Okayama", 7}},
    {8589934592u, std::string_view{"Hiroshima", 9}},
    {17179869184u, std::string_view{"Yamaguchi", 9}},
    {34359738368u, std::string_view{"Tokushima", 9}},
    {68719476736u, std::string_view{"Kagawa", 6}},
    {137438953472u, std::string_view{"Ehime", 5}},
    {274877906944u, std::string_view{"Kochi", 5}},
    {549755813888u, std::string_view{"Fukuoka", 7}},
    {1099511627776u, std::string_view{"Saga", 4}},
    {2199023255552u, std::string_view{"Nagasaki", 8}},
    {4398046511104u, std::string_view{"Kumamoto", 8}},
    {8796093022208u, std::string_view{"Oita", 4}},
    {17592186044416u, std::string_view{"Miyazaki", 8}},
    {35184372088832u, std::string_view{"Kagoshima", 9}},
    {70368744177664u, std::string_view{"Okinawa", 7}},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_ex9_target_area_code_en_lookup(uint64_t id) noexcept {
    uint8_t lo = 0, hi = 47;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_TABLE[mid].id == id) return QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_TABLE[mid].label;
        if (QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_EN_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_ex9_target_area_code_en_lookup(uint64_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
