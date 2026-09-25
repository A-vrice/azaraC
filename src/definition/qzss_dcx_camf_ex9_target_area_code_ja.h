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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_POOL[] = "北海道\000青森県\000岩手県\000宮城県\000秋田県\000山形県\000福島県\000茨城県\000栃木県\000群馬県\000埼玉県\000千葉県\000東京都\000神奈川県\000新潟県\000富山県\000石川県\000福井県\000山梨県\000長野県\000岐阜県\000静岡県\000愛知県\000三重県\000滋賀県\000京都府\000大阪府\000兵庫県\000奈良県\000和歌山県\000鳥取県\000島根県\000岡山県\000広島県\000山口県\000徳島県\000香川県\000愛媛県\000高知県\000福岡県\000佐賀県\000長崎県\000熊本県\000大分県\000宮崎県\000鹿児島県\000沖縄県\000";
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
            return azarac_pgm_view(QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_Entry { uint64_t id; const char* label; };
inline constexpr QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_Entry QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_TABLE[] = {
    {1u, "北海道"},
    {2u, "青森県"},
    {4u, "岩手県"},
    {8u, "宮城県"},
    {16u, "秋田県"},
    {32u, "山形県"},
    {64u, "福島県"},
    {128u, "茨城県"},
    {256u, "栃木県"},
    {512u, "群馬県"},
    {1024u, "埼玉県"},
    {2048u, "千葉県"},
    {4096u, "東京都"},
    {8192u, "神奈川県"},
    {16384u, "新潟県"},
    {32768u, "富山県"},
    {65536u, "石川県"},
    {131072u, "福井県"},
    {262144u, "山梨県"},
    {524288u, "長野県"},
    {1048576u, "岐阜県"},
    {2097152u, "静岡県"},
    {4194304u, "愛知県"},
    {8388608u, "三重県"},
    {16777216u, "滋賀県"},
    {33554432u, "京都府"},
    {67108864u, "大阪府"},
    {134217728u, "兵庫県"},
    {268435456u, "奈良県"},
    {536870912u, "和歌山県"},
    {1073741824u, "鳥取県"},
    {2147483648u, "島根県"},
    {4294967296u, "岡山県"},
    {8589934592u, "広島県"},
    {17179869184u, "山口県"},
    {34359738368u, "徳島県"},
    {68719476736u, "香川県"},
    {137438953472u, "愛媛県"},
    {274877906944u, "高知県"},
    {549755813888u, "福岡県"},
    {1099511627776u, "佐賀県"},
    {2199023255552u, "長崎県"},
    {4398046511104u, "熊本県"},
    {8796093022208u, "大分県"},
    {17592186044416u, "宮崎県"},
    {35184372088832u, "鹿児島県"},
    {70368744177664u, "沖縄県"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_ex9_target_area_code_ja_lookup(uint64_t id) noexcept {
    uint8_t lo = 0, hi = 47;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_TABLE[mid].id == id) {
            const char* s = QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCX_CAMF_EX9_TARGET_AREA_CODE_JA_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_ex9_target_area_code_ja_lookup(uint64_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_ex9_target_area_code_ja_lookup(uint64_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
