#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_tsunami_forecast_region
// Variable      : qzss_dcr_jma_tsunami_forecast_region
// Entries       : 99
// Strategy      : binary_search

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_TSUNAMI)

struct QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry { uint16_t id; std::optional<std::string_view> label; };
inline constexpr QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_TABLE[] = {
    {100u, std::string_view{"北海道太平洋沿岸東部", 10}},
    {101u, std::string_view{"北海道太平洋沿岸中部", 10}},
    {102u, std::string_view{"北海道太平洋沿岸西部", 10}},
    {110u, std::string_view{"北海道日本海沿岸北部", 10}},
    {111u, std::string_view{"北海道日本海沿岸南部", 10}},
    {120u, std::string_view{"オホーツク海沿岸", 8}},
    {191u, std::string_view{"北海道太平洋沿岸", 8}},
    {192u, std::string_view{"北海道日本海沿岸", 8}},
    {200u, std::string_view{"青森県日本海沿岸", 8}},
    {201u, std::string_view{"青森県太平洋沿岸", 8}},
    {202u, std::string_view{"陸奥湾", 3}},
    {210u, std::string_view{"岩手県", 3}},
    {220u, std::string_view{"宮城県", 3}},
    {230u, std::string_view{"秋田県", 3}},
    {240u, std::string_view{"山形県", 3}},
    {250u, std::string_view{"福島県", 3}},
    {281u, std::string_view{"青森県", 3}},
    {291u, std::string_view{"東北地方太平洋沿岸", 9}},
    {292u, std::string_view{"東北地方日本海沿岸", 9}},
    {300u, std::string_view{"茨城県", 3}},
    {310u, std::string_view{"千葉県九十九里・外房", 10}},
    {311u, std::string_view{"千葉県内房", 5}},
    {312u, std::string_view{"東京湾内湾", 5}},
    {320u, std::string_view{"伊豆諸島", 4}},
    {321u, std::string_view{"小笠原諸島", 5}},
    {330u, std::string_view{"相模湾・三浦半島", 8}},
    {340u, std::string_view{"新潟県上中下越", 7}},
    {341u, std::string_view{"佐渡", 2}},
    {350u, std::string_view{"富山県", 3}},
    {360u, std::string_view{"石川県能登", 5}},
    {361u, std::string_view{"石川県加賀", 5}},
    {370u, std::string_view{"福井県", 3}},
    {380u, std::string_view{"静岡県", 3}},
    {390u, std::string_view{"愛知県外海", 5}},
    {391u, std::string_view{"伊勢・三河湾", 6}},
    {400u, std::string_view{"三重県南部", 5}},
    {481u, std::string_view{"千葉県", 3}},
    {482u, std::string_view{"神奈川県", 4}},
    {483u, std::string_view{"新潟県", 3}},
    {484u, std::string_view{"石川県", 3}},
    {485u, std::string_view{"愛知県", 3}},
    {486u, std::string_view{"三重県", 3}},
    {491u, std::string_view{"関東地方", 4}},
    {492u, std::string_view{"伊豆・小笠原諸島", 8}},
    {493u, std::string_view{"北陸地方", 4}},
    {494u, std::string_view{"東海地方", 4}},
    {500u, std::string_view{"京都府", 3}},
    {510u, std::string_view{"大阪府", 3}},
    {520u, std::string_view{"兵庫県北部", 5}},
    {521u, std::string_view{"兵庫県瀬戸内海沿岸", 9}},
    {522u, std::string_view{"淡路島南部", 5}},
    {530u, std::string_view{"和歌山県", 4}},
    {540u, std::string_view{"鳥取県", 3}},
    {550u, std::string_view{"島根県出雲・石見", 8}},
    {551u, std::string_view{"隠岐", 2}},
    {560u, std::string_view{"岡山県", 3}},
    {570u, std::string_view{"広島県", 3}},
    {580u, std::string_view{"徳島県", 3}},
    {590u, std::string_view{"香川県", 3}},
    {600u, std::string_view{"愛媛県宇和海沿岸", 8}},
    {601u, std::string_view{"愛媛県瀬戸内海沿岸", 9}},
    {610u, std::string_view{"高知県", 3}},
    {681u, std::string_view{"兵庫県", 3}},
    {682u, std::string_view{"島根県", 3}},
    {683u, std::string_view{"愛媛県", 3}},
    {691u, std::string_view{"近畿四国太平洋沿岸", 9}},
    {692u, std::string_view{"近畿中国日本海沿岸", 9}},
    {693u, std::string_view{"瀬戸内海沿岸", 6}},
    {700u, std::string_view{"山口県日本海沿岸", 8}},
    {701u, std::string_view{"山口県瀬戸内海沿岸", 9}},
    {710u, std::string_view{"福岡県瀬戸内海沿岸", 9}},
    {711u, std::string_view{"福岡県日本海沿岸", 8}},
    {712u, std::string_view{"有明・八代海", 6}},
    {720u, std::string_view{"佐賀県北部", 5}},
    {730u, std::string_view{"長崎県西方", 5}},
    {731u, std::string_view{"壱岐・対馬", 5}},
    {740u, std::string_view{"熊本県天草灘沿岸", 8}},
    {750u, std::string_view{"大分県瀬戸内海沿岸", 9}},
    {751u, std::string_view{"大分県豊後水道沿岸", 9}},
    {760u, std::string_view{"宮崎県", 3}},
    {770u, std::string_view{"鹿児島県東部", 6}},
    {771u, std::string_view{"種子島・屋久島地方", 9}},
    {772u, std::string_view{"奄美群島・トカラ列島", 10}},
    {773u, std::string_view{"鹿児島県西部", 6}},
    {781u, std::string_view{"山口県", 3}},
    {782u, std::string_view{"福岡県", 3}},
    {783u, std::string_view{"佐賀県", 3}},
    {784u, std::string_view{"長崎県", 3}},
    {785u, std::string_view{"熊本県", 3}},
    {786u, std::string_view{"大分県", 3}},
    {787u, std::string_view{"鹿児島県", 4}},
    {791u, std::string_view{"九州地方東部", 6}},
    {792u, std::string_view{"九州地方西部", 6}},
    {793u, std::string_view{"薩南諸島", 4}},
    {800u, std::string_view{"沖縄本島地方", 6}},
    {801u, std::string_view{"大東島地方", 5}},
    {802u, std::string_view{"宮古島・八重山地方", 9}},
    {891u, std::string_view{"沖縄県地方", 5}},
    {1000u, std::string_view{"その他の津波予報区", 9}},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_forecast_region_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 99;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_TABLE[mid].id == id) return QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_TABLE[mid].label;
        if (QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_forecast_region_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
