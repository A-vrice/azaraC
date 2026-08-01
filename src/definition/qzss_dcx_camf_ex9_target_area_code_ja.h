#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_ex9_target_area_code_ja
// Variable      : qzss_dcx_camf_ex9_target_area_code_ja
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

#if (AZARAC_ENABLE_DCX_CAMF) && (AZARAC_LANG_JA)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_POOL[] = "北海道\0青森県\0岩手県\0宮城県\0秋田県\0山形県\0福島県\0茨城県\0栃木県\0群馬県\0埼玉県\0千葉県\0東京都\0神奈川県\0新潟県\0富山県\0石川県\0福井県\0山梨県\0長野県\0岐阜県\0静岡県\0愛知県\0三重県\0滋賀県\0京都府\0大阪府\0兵庫県\0奈良県\0和歌山県\0鳥取県\0島根県\0岡山県\0広島県\0山口県\0徳島県\0香川県\0愛媛県\0高知県\0福岡県\0佐賀県\0長崎県\0熊本県\0大分県\0宮崎県\0鹿児島県\0沖縄県\0";
struct QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_Entry { uint64_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_Entry QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_TABLE[] AZARAC_PROGMEM = {
    {1u, 0u, 9u},
    {2u, 10u, 9u},
    {4u, 20u, 9u},
    {8u, 30u, 9u},
    {16u, 40u, 9u},
    {32u, 50u, 9u},
    {64u, 60u, 9u},
    {128u, 70u, 9u},
    {256u, 80u, 9u},
    {512u, 90u, 9u},
    {1024u, 100u, 9u},
    {2048u, 110u, 9u},
    {4096u, 120u, 9u},
    {8192u, 130u, 12u},
    {16384u, 143u, 9u},
    {32768u, 153u, 9u},
    {65536u, 163u, 9u},
    {131072u, 173u, 9u},
    {262144u, 183u, 9u},
    {524288u, 193u, 9u},
    {1048576u, 203u, 9u},
    {2097152u, 213u, 9u},
    {4194304u, 223u, 9u},
    {8388608u, 233u, 9u},
    {16777216u, 243u, 9u},
    {33554432u, 253u, 9u},
    {67108864u, 263u, 9u},
    {134217728u, 273u, 9u},
    {268435456u, 283u, 9u},
    {536870912u, 293u, 12u},
    {1073741824u, 306u, 9u},
    {2147483648u, 316u, 9u},
    {4294967296u, 326u, 9u},
    {8589934592u, 336u, 9u},
    {17179869184u, 346u, 9u},
    {34359738368u, 356u, 9u},
    {68719476736u, 366u, 9u},
    {137438953472u, 376u, 9u},
    {274877906944u, 386u, 9u},
    {549755813888u, 396u, 9u},
    {1099511627776u, 406u, 9u},
    {2199023255552u, 416u, 9u},
    {4398046511104u, 426u, 9u},
    {8796093022208u, 436u, 9u},
    {17592186044416u, 446u, 9u},
    {35184372088832u, 456u, 12u},
    {70368744177664u, 469u, 9u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_ex9_target_area_code_ja_lookup(uint64_t id) noexcept {
    uint8_t lo = 0, hi = 47;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_TABLE[mid]);
        uint64_t eid = (static_cast<uint64_t>(pgm_read_dword(ep + offsetof(QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_Entry, id) + 4)) << 32) | pgm_read_dword(ep + offsetof(QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_Entry, id));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_Entry, len));
            if (n == 0) return std::nullopt;
            return azarac_pgm_view(QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_Entry { uint64_t id; std::optional<std::string_view> label; };
inline constexpr QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_Entry QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_TABLE[] = {
    {1u, std::string_view{"北海道", 9}},
    {2u, std::string_view{"青森県", 9}},
    {4u, std::string_view{"岩手県", 9}},
    {8u, std::string_view{"宮城県", 9}},
    {16u, std::string_view{"秋田県", 9}},
    {32u, std::string_view{"山形県", 9}},
    {64u, std::string_view{"福島県", 9}},
    {128u, std::string_view{"茨城県", 9}},
    {256u, std::string_view{"栃木県", 9}},
    {512u, std::string_view{"群馬県", 9}},
    {1024u, std::string_view{"埼玉県", 9}},
    {2048u, std::string_view{"千葉県", 9}},
    {4096u, std::string_view{"東京都", 9}},
    {8192u, std::string_view{"神奈川県", 12}},
    {16384u, std::string_view{"新潟県", 9}},
    {32768u, std::string_view{"富山県", 9}},
    {65536u, std::string_view{"石川県", 9}},
    {131072u, std::string_view{"福井県", 9}},
    {262144u, std::string_view{"山梨県", 9}},
    {524288u, std::string_view{"長野県", 9}},
    {1048576u, std::string_view{"岐阜県", 9}},
    {2097152u, std::string_view{"静岡県", 9}},
    {4194304u, std::string_view{"愛知県", 9}},
    {8388608u, std::string_view{"三重県", 9}},
    {16777216u, std::string_view{"滋賀県", 9}},
    {33554432u, std::string_view{"京都府", 9}},
    {67108864u, std::string_view{"大阪府", 9}},
    {134217728u, std::string_view{"兵庫県", 9}},
    {268435456u, std::string_view{"奈良県", 9}},
    {536870912u, std::string_view{"和歌山県", 12}},
    {1073741824u, std::string_view{"鳥取県", 9}},
    {2147483648u, std::string_view{"島根県", 9}},
    {4294967296u, std::string_view{"岡山県", 9}},
    {8589934592u, std::string_view{"広島県", 9}},
    {17179869184u, std::string_view{"山口県", 9}},
    {34359738368u, std::string_view{"徳島県", 9}},
    {68719476736u, std::string_view{"香川県", 9}},
    {137438953472u, std::string_view{"愛媛県", 9}},
    {274877906944u, std::string_view{"高知県", 9}},
    {549755813888u, std::string_view{"福岡県", 9}},
    {1099511627776u, std::string_view{"佐賀県", 9}},
    {2199023255552u, std::string_view{"長崎県", 9}},
    {4398046511104u, std::string_view{"熊本県", 9}},
    {8796093022208u, std::string_view{"大分県", 9}},
    {17592186044416u, std::string_view{"宮崎県", 9}},
    {35184372088832u, std::string_view{"鹿児島県", 12}},
    {70368744177664u, std::string_view{"沖縄県", 9}},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_ex9_target_area_code_ja_lookup(uint64_t id) noexcept {
    uint8_t lo = 0, hi = 47;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_TABLE[mid].id == id) return QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_TABLE[mid].label;
        if (QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_ex9_target_area_code_ja_lookup(uint64_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
