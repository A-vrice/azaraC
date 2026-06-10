#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_tsunami_forecast_region
// Variable      : qzss_dcr_jma_tsunami_forecast_region
// Entries       : 99
// Strategy      : binary_search

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

struct QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry { uint16_t id; std::string_view label; };
inline constexpr QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_TABLE[] = {
    {100u, std::string_view{"北海道太平洋沿岸東部", 30}},

    {101u, std::string_view{"北海道太平洋沿岸中部", 30}},

    {102u, std::string_view{"北海道太平洋沿岸西部", 30}},

    {110u, std::string_view{"北海道日本海沿岸北部", 30}},

    {111u, std::string_view{"北海道日本海沿岸南部", 30}},

    {120u, std::string_view{"オホーツク海沿岸", 24}},

    {191u, std::string_view{"北海道太平洋沿岸", 24}},

    {192u, std::string_view{"北海道日本海沿岸", 24}},

    {200u, std::string_view{"青森県日本海沿岸", 24}},

    {201u, std::string_view{"青森県太平洋沿岸", 24}},

    {202u, std::string_view{"陸奥湾", 9}},

    {210u, std::string_view{"岩手県", 9}},

    {220u, std::string_view{"宮城県", 9}},

    {230u, std::string_view{"秋田県", 9}},

    {240u, std::string_view{"山形県", 9}},

    {250u, std::string_view{"福島県", 9}},

    {281u, std::string_view{"青森県", 9}},

    {291u, std::string_view{"東北地方太平洋沿岸", 27}},

    {292u, std::string_view{"東北地方日本海沿岸", 27}},

    {300u, std::string_view{"茨城県", 9}},

    {310u, std::string_view{"千葉県九十九里・外房", 30}},

    {311u, std::string_view{"千葉県内房", 15}},

    {312u, std::string_view{"東京湾内湾", 15}},

    {320u, std::string_view{"伊豆諸島", 12}},

    {321u, std::string_view{"小笠原諸島", 15}},

    {330u, std::string_view{"相模湾・三浦半島", 24}},

    {340u, std::string_view{"新潟県上中下越", 21}},

    {341u, std::string_view{"佐渡", 6}},

    {350u, std::string_view{"富山県", 9}},

    {360u, std::string_view{"石川県能登", 15}},

    {361u, std::string_view{"石川県加賀", 15}},

    {370u, std::string_view{"福井県", 9}},

    {380u, std::string_view{"静岡県", 9}},

    {390u, std::string_view{"愛知県外海", 15}},

    {391u, std::string_view{"伊勢・三河湾", 18}},

    {400u, std::string_view{"三重県南部", 15}},

    {481u, std::string_view{"千葉県", 9}},

    {482u, std::string_view{"神奈川県", 12}},

    {483u, std::string_view{"新潟県", 9}},

    {484u, std::string_view{"石川県", 9}},

    {485u, std::string_view{"愛知県", 9}},

    {486u, std::string_view{"三重県", 9}},

    {491u, std::string_view{"関東地方", 12}},

    {492u, std::string_view{"伊豆・小笠原諸島", 24}},

    {493u, std::string_view{"北陸地方", 12}},

    {494u, std::string_view{"東海地方", 12}},

    {500u, std::string_view{"京都府", 9}},

    {510u, std::string_view{"大阪府", 9}},

    {520u, std::string_view{"兵庫県北部", 15}},

    {521u, std::string_view{"兵庫県瀬戸内海沿岸", 27}},

    {522u, std::string_view{"淡路島南部", 15}},

    {530u, std::string_view{"和歌山県", 12}},

    {540u, std::string_view{"鳥取県", 9}},

    {550u, std::string_view{"島根県出雲・石見", 24}},

    {551u, std::string_view{"隠岐", 6}},

    {560u, std::string_view{"岡山県", 9}},

    {570u, std::string_view{"広島県", 9}},

    {580u, std::string_view{"徳島県", 9}},

    {590u, std::string_view{"香川県", 9}},

    {600u, std::string_view{"愛媛県宇和海沿岸", 24}},

    {601u, std::string_view{"愛媛県瀬戸内海沿岸", 27}},

    {610u, std::string_view{"高知県", 9}},

    {681u, std::string_view{"兵庫県", 9}},

    {682u, std::string_view{"島根県", 9}},

    {683u, std::string_view{"愛媛県", 9}},

    {691u, std::string_view{"近畿四国太平洋沿岸", 27}},

    {692u, std::string_view{"近畿中国日本海沿岸", 27}},

    {693u, std::string_view{"瀬戸内海沿岸", 18}},

    {700u, std::string_view{"山口県日本海沿岸", 24}},

    {701u, std::string_view{"山口県瀬戸内海沿岸", 27}},

    {710u, std::string_view{"福岡県瀬戸内海沿岸", 27}},

    {711u, std::string_view{"福岡県日本海沿岸", 24}},

    {712u, std::string_view{"有明・八代海", 18}},

    {720u, std::string_view{"佐賀県北部", 15}},

    {730u, std::string_view{"長崎県西方", 15}},

    {731u, std::string_view{"壱岐・対馬", 15}},

    {740u, std::string_view{"熊本県天草灘沿岸", 24}},

    {750u, std::string_view{"大分県瀬戸内海沿岸", 27}},

    {751u, std::string_view{"大分県豊後水道沿岸", 27}},

    {760u, std::string_view{"宮崎県", 9}},

    {770u, std::string_view{"鹿児島県東部", 18}},

    {771u, std::string_view{"種子島・屋久島地方", 27}},

    {772u, std::string_view{"奄美群島・トカラ列島", 30}},

    {773u, std::string_view{"鹿児島県西部", 18}},

    {781u, std::string_view{"山口県", 9}},

    {782u, std::string_view{"福岡県", 9}},

    {783u, std::string_view{"佐賀県", 9}},

    {784u, std::string_view{"長崎県", 9}},

    {785u, std::string_view{"熊本県", 9}},

    {786u, std::string_view{"大分県", 9}},

    {787u, std::string_view{"鹿児島県", 12}},

    {791u, std::string_view{"九州地方東部", 18}},

    {792u, std::string_view{"九州地方西部", 18}},

    {793u, std::string_view{"薩南諸島", 12}},

    {800u, std::string_view{"沖縄本島地方", 18}},

    {801u, std::string_view{"大東島地方", 15}},

    {802u, std::string_view{"宮古島・八重山地方", 27}},

    {891u, std::string_view{"沖縄県地方", 15}},

    {1000u, std::string_view{"その他の津波予報区", 27}},
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_forecast_region_lookup(uint16_t id) {
    uint8_t lo = 0, hi = 99;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_TABLE[mid].id == id) return QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_TABLE[mid].label;
        if (QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}

} // namespace def
} // namespace azaraC
