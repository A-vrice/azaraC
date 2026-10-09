#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.camf.a11_japanese_library
// Variable      : qzss_dcx_camf_a11_japanese_library_ja
// Entries       : 38
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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_POOL[] = "指示なし\000直ちに命を守るための最善の行動を。\000これは、DCX のテストです。\000直ちに命を守るための最善の行動を。\000ミサイル発射。ミサイル発射。ミサイルが発射されたものとみられます。建物の中、又は地下に避難して下さい。\000ミサイル通過。ミサイル通過。先程のミサイルは通過したものとみられます。避難の呼びかけを解除します。不審なものには決して近寄らず直ちに警察や消防などに連絡して下さい。\000先程のミサイルは、海に落下したものとみられます。避難の呼びかけを解除します。不審なものには決して近寄らず直ちに警察や消防などに連絡して下さい。\000先程のミサイルは、我が国には飛来しないものとみられます。避難の呼びかけを解除します。\000直ちに避難。直ちに避難。直ちに建物の中、又は地下に避難して下さい。ミサイルが、周辺に落下するものとみられます。直ちに避難して下さい。\000先程のミサイルは、迎撃により破壊されました。ミサイルの破片の落下の可能性があります。続報を伝達しますので、引き続き屋内に避難して下さい。\000ミサイル落下。ミサイル落下。ミサイルが、周辺に落下したものとみられます。続報を伝達しますので、引き続き屋内に避難して下さい。\000先程のミサイルは、我が国には落下しないものとみられます。避難の呼びかけを解除します。\000これは、Jアラートのテストです。\000直ちに命を守るための最善の行動を。\000留まれ。\000留まれ。頑丈なものの下/中。\000留まれ。3階以上。\000留まれ。地下。\000留まれ。山。\000留まれ。水場。\000留まれ。工場等化学系を取扱う建物。\000留まれ。崖等崩れやすい場所。\000向かえ。\000向かえ。頑丈なものの下/中。\000向かえ。3階以上。\000向かえ。地下。\000向かえ。山。\000向かえ。水場。\000向かえ。工場等化学系を取扱う建物。\000向かえ。崖等崩れやすい場所。\000離れろ。\000離れろ。頑丈なものの下/中。\000離れろ。3階以上。\000離れろ。地下。\000離れろ。山。\000離れろ。水場。\000離れろ。工場等化学系を取扱う建物。\000離れろ。崖等崩れやすい場所。\000";
struct QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_Entry { uint16_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_Entry QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_TABLE[] AZARAC_PROGMEM = {
    {0u, 0u, 12u},
    {1u, 13u, 51u},
    {126u, 65u, 37u},
    {127u, 103u, 51u},
    {128u, 155u, 153u},
    {129u, 309u, 246u},
    {130u, 556u, 213u},
    {131u, 770u, 126u},
    {132u, 897u, 198u},
    {133u, 1096u, 204u},
    {134u, 1301u, 186u},
    {135u, 1488u, 126u},
    {136u, 1615u, 46u},
    {255u, 1662u, 51u},
    {256u, 1714u, 12u},
    {257u, 1727u, 40u},
    {258u, 1768u, 25u},
    {259u, 1794u, 21u},
    {260u, 1816u, 18u},
    {261u, 1835u, 21u},
    {262u, 1857u, 51u},
    {263u, 1909u, 42u},
    {512u, 1952u, 12u},
    {513u, 1965u, 40u},
    {514u, 2006u, 25u},
    {515u, 2032u, 21u},
    {516u, 2054u, 18u},
    {517u, 2073u, 21u},
    {518u, 2095u, 51u},
    {519u, 2147u, 42u},
    {768u, 2190u, 12u},
    {769u, 2203u, 40u},
    {770u, 2244u, 25u},
    {771u, 2270u, 21u},
    {772u, 2292u, 18u},
    {773u, 2311u, 21u},
    {774u, 2333u, 51u},
    {775u, 2385u, 42u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a11_japanese_library_ja_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 38;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_TABLE[mid]);
        uint16_t eid = pgm_read_word(ep + offsetof(QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_Entry, id));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_Entry, len));
            return azarac_pgm_view(QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_Entry { uint16_t id; const char* label; };
inline constexpr QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_Entry QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_TABLE[] = {
    {0u, "指示なし"},
    {1u, "直ちに命を守るための最善の行動を。"},
    {126u, "これは、DCX のテストです。"},
    {127u, "直ちに命を守るための最善の行動を。"},
    {128u, "ミサイル発射。ミサイル発射。ミサイルが発射されたものとみられます。建物の中、又は地下に避難して下さい。"},
    {129u, "ミサイル通過。ミサイル通過。先程のミサイルは通過したものとみられます。避難の呼びかけを解除します。不審なものには決して近寄らず直ちに警察や消防などに連絡して下さい。"},
    {130u, "先程のミサイルは、海に落下したものとみられます。避難の呼びかけを解除します。不審なものには決して近寄らず直ちに警察や消防などに連絡して下さい。"},
    {131u, "先程のミサイルは、我が国には飛来しないものとみられます。避難の呼びかけを解除します。"},
    {132u, "直ちに避難。直ちに避難。直ちに建物の中、又は地下に避難して下さい。ミサイルが、周辺に落下するものとみられます。直ちに避難して下さい。"},
    {133u, "先程のミサイルは、迎撃により破壊されました。ミサイルの破片の落下の可能性があります。続報を伝達しますので、引き続き屋内に避難して下さい。"},
    {134u, "ミサイル落下。ミサイル落下。ミサイルが、周辺に落下したものとみられます。続報を伝達しますので、引き続き屋内に避難して下さい。"},
    {135u, "先程のミサイルは、我が国には落下しないものとみられます。避難の呼びかけを解除します。"},
    {136u, "これは、Jアラートのテストです。"},
    {255u, "直ちに命を守るための最善の行動を。"},
    {256u, "留まれ。"},
    {257u, "留まれ。頑丈なものの下/中。"},
    {258u, "留まれ。3階以上。"},
    {259u, "留まれ。地下。"},
    {260u, "留まれ。山。"},
    {261u, "留まれ。水場。"},
    {262u, "留まれ。工場等化学系を取扱う建物。"},
    {263u, "留まれ。崖等崩れやすい場所。"},
    {512u, "向かえ。"},
    {513u, "向かえ。頑丈なものの下/中。"},
    {514u, "向かえ。3階以上。"},
    {515u, "向かえ。地下。"},
    {516u, "向かえ。山。"},
    {517u, "向かえ。水場。"},
    {518u, "向かえ。工場等化学系を取扱う建物。"},
    {519u, "向かえ。崖等崩れやすい場所。"},
    {768u, "離れろ。"},
    {769u, "離れろ。頑丈なものの下/中。"},
    {770u, "離れろ。3階以上。"},
    {771u, "離れろ。地下。"},
    {772u, "離れろ。山。"},
    {773u, "離れろ。水場。"},
    {774u, "離れろ。工場等化学系を取扱う建物。"},
    {775u, "離れろ。崖等崩れやすい場所。"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a11_japanese_library_ja_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 38;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_TABLE[mid].id == id) {
            const char* s = QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a11_japanese_library_ja_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a11_japanese_library_ja_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
