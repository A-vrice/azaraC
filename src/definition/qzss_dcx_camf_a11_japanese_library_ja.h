#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_a11_japanese_library
// Variable      : qzss_dcx_camf_a11_japanese_library_ja
// Entries       : 38
// Strategy      : binary_search

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

struct QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_Entry { uint16_t id; std::string_view label; };
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

    {775u, std::string_view{"離れろ。崖等崩れやすい場所。", 42}},
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a11_japanese_library_ja_lookup(uint16_t id) {
    uint8_t lo = 0, hi = 38;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_TABLE[mid].id == id) return QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_TABLE[mid].label;
        if (QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_JA_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}

} // namespace def
} // namespace azaraC
