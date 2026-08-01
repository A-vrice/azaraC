#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_a11_japanese_library_ja
// Variable      : qzss_dcx_camf_a11_japanese_library_ja
// Entries       : 38
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

#if (AZARAC_ENABLE_DCX_CAMF) && (AZARAC_LANG_JA)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_POOL[] = "\0直ちに命を守るための最善の行動を。\0これは、DCX のテストです。\0直ちに命を守るための最善の行動を。\0ミサイル発射。ミサイル発射。ミサイルが発射されたものとみられます。建物の中、又は地下に避難して下さい。\0ミサイル通過。ミサイル通過。先程のミサイルは通過したものとみられます。避難の呼びかけを解除します。不審なものには決して近寄らず直ちに警察や消防などに連絡して下さい。\0先程のミサイルは、海に落下したものとみられます。避難の呼びかけを解除します。不審なものには決して近寄らず直ちに警察や消防などに連絡して下さい。\0先程のミサイルは、我が国には飛来しないものとみられます。避難の呼びかけを解除します。\0直ちに避難。直ちに避難。直ちに建物の中、又は地下に避難して下さい。ミサイルが、周辺に落下するものとみられます。直ちに避難して下さい。\0先程のミサイルは、迎撃により破壊されました。ミサイルの破片の落下の可能性があります。続報を伝達しますので、引き続き屋内に避難して下さい。\0ミサイル落下。ミサイル落下。ミサイルが、周辺に落下したものとみられます。続報を伝達しますので、引き続き屋内に避難して下さい。\0先程のミサイルは、我が国には落下しないものとみられます。避難の呼びかけを解除します。\0これは、Jアラートのテストです。\0直ちに命を守るための最善の行動を。\0留まれ。\0留まれ。頑丈なものの下/中。\0留まれ。3階以上。\0留まれ。地下。\0留まれ。山。\0留まれ。水場。\0留まれ。工場等化学系を取扱う建物。\0留まれ。崖等崩れやすい場所。\0向かえ。\0向かえ。頑丈なものの下/中。\0向かえ。3階以上。\0向かえ。地下。\0向かえ。山。\0向かえ。水場。\0向かえ。工場等化学系を取扱う建物。\0向かえ。崖等崩れやすい場所。\0離れろ。\0離れろ。頑丈なものの下/中。\0離れろ。3階以上。\0離れろ。地下。\0離れろ。山。\0離れろ。水場。\0離れろ。工場等化学系を取扱う建物。\0離れろ。崖等崩れやすい場所。\0";
struct QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_Entry { uint16_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_Entry QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_TABLE[] AZARAC_PROGMEM = {
    {0u, 0u, 0u},
    {1u, 1u, 51u},
    {126u, 53u, 40u},
    {127u, 94u, 51u},
    {128u, 146u, 153u},
    {129u, 300u, 246u},
    {130u, 547u, 213u},
    {131u, 761u, 126u},
    {132u, 888u, 198u},
    {133u, 1087u, 204u},
    {134u, 1292u, 186u},
    {135u, 1479u, 126u},
    {136u, 1606u, 46u},
    {255u, 1653u, 51u},
    {256u, 1705u, 12u},
    {257u, 1718u, 40u},
    {258u, 1759u, 25u},
    {259u, 1785u, 21u},
    {260u, 1807u, 18u},
    {261u, 1826u, 21u},
    {262u, 1848u, 51u},
    {263u, 1900u, 42u},
    {512u, 1943u, 12u},
    {513u, 1956u, 40u},
    {514u, 1997u, 25u},
    {515u, 2023u, 21u},
    {516u, 2045u, 18u},
    {517u, 2064u, 21u},
    {518u, 2086u, 51u},
    {519u, 2138u, 42u},
    {768u, 2181u, 12u},
    {769u, 2194u, 40u},
    {770u, 2235u, 25u},
    {771u, 2261u, 21u},
    {772u, 2283u, 18u},
    {773u, 2302u, 21u},
    {774u, 2324u, 51u},
    {775u, 2376u, 42u},
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
            if (n == 0) return std::nullopt;
            return azarac_pgm_view(QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_Entry { uint16_t id; std::optional<std::string_view> label; };
inline constexpr QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_Entry QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_TABLE[] = {
    {0u, std::string_view{"", 0}},
    {1u, std::string_view{"直ちに命を守るための最善の行動を。", 51}},
    {126u, std::string_view{"これは、DCX のテストです。", 40}},
    {127u, std::string_view{"直ちに命を守るための最善の行動を。", 51}},
    {128u, std::string_view{"ミサイル発射。ミサイル発射。ミサイルが発射されたものとみられます。建物の中、又は地下に避難して下さい。", 153}},
    {129u, std::string_view{"ミサイル通過。ミサイル通過。先程のミサイルは通過したものとみられます。避難の呼びかけを解除します。不審なものには決して近寄らず直ちに警察や消防などに連絡して下さい。", 246}},
    {130u, std::string_view{"先程のミサイルは、海に落下したものとみられます。避難の呼びかけを解除します。不審なものには決して近寄らず直ちに警察や消防などに連絡して下さい。", 213}},
    {131u, std::string_view{"先程のミサイルは、我が国には飛来しないものとみられます。避難の呼びかけを解除します。", 126}},
    {132u, std::string_view{"直ちに避難。直ちに避難。直ちに建物の中、又は地下に避難して下さい。ミサイルが、周辺に落下するものとみられます。直ちに避難して下さい。", 198}},
    {133u, std::string_view{"先程のミサイルは、迎撃により破壊されました。ミサイルの破片の落下の可能性があります。続報を伝達しますので、引き続き屋内に避難して下さい。", 204}},
    {134u, std::string_view{"ミサイル落下。ミサイル落下。ミサイルが、周辺に落下したものとみられます。続報を伝達しますので、引き続き屋内に避難して下さい。", 186}},
    {135u, std::string_view{"先程のミサイルは、我が国には落下しないものとみられます。避難の呼びかけを解除します。", 126}},
    {136u, std::string_view{"これは、Jアラートのテストです。", 46}},
    {255u, std::string_view{"直ちに命を守るための最善の行動を。", 51}},
    {256u, std::string_view{"留まれ。", 12}},
    {257u, std::string_view{"留まれ。頑丈なものの下/中。", 40}},
    {258u, std::string_view{"留まれ。3階以上。", 25}},
    {259u, std::string_view{"留まれ。地下。", 21}},
    {260u, std::string_view{"留まれ。山。", 18}},
    {261u, std::string_view{"留まれ。水場。", 21}},
    {262u, std::string_view{"留まれ。工場等化学系を取扱う建物。", 51}},
    {263u, std::string_view{"留まれ。崖等崩れやすい場所。", 42}},
    {512u, std::string_view{"向かえ。", 12}},
    {513u, std::string_view{"向かえ。頑丈なものの下/中。", 40}},
    {514u, std::string_view{"向かえ。3階以上。", 25}},
    {515u, std::string_view{"向かえ。地下。", 21}},
    {516u, std::string_view{"向かえ。山。", 18}},
    {517u, std::string_view{"向かえ。水場。", 21}},
    {518u, std::string_view{"向かえ。工場等化学系を取扱う建物。", 51}},
    {519u, std::string_view{"向かえ。崖等崩れやすい場所。", 42}},
    {768u, std::string_view{"離れろ。", 12}},
    {769u, std::string_view{"離れろ。頑丈なものの下/中。", 40}},
    {770u, std::string_view{"離れろ。3階以上。", 25}},
    {771u, std::string_view{"離れろ。地下。", 21}},
    {772u, std::string_view{"離れろ。山。", 18}},
    {773u, std::string_view{"離れろ。水場。", 21}},
    {774u, std::string_view{"離れろ。工場等化学系を取扱う建物。", 51}},
    {775u, std::string_view{"離れろ。崖等崩れやすい場所。", 42}},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a11_japanese_library_ja_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 38;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_TABLE[mid].id == id) return QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_TABLE[mid].label;
        if (QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a11_japanese_library_ja_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
