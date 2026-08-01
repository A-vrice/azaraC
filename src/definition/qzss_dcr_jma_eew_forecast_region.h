#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_eew_forecast_region
// Variable      : qzss_dcr_jma_eew_forecast_region
// Entries       : 71
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

#if (AZARAC_ENABLE_EEW)

inline constexpr uint8_t QZSS_DCR_JMA_EEW_FORECAST_REGION_BASE = 1;
inline constexpr uint8_t QZSS_DCR_JMA_EEW_FORECAST_REGION_SIZE = 71;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_EEW_FORECAST_REGION_POOL[] = "北海道道央\0北海道道南\0北海道道北\0北海道道東\0青森\0岩手\0宮城\0秋田\0山形\0福島\0茨城\0栃木\0群馬\0埼玉\0千葉\0東京\0伊豆諸島\0小笠原\0神奈川\0新潟\0富山\0石川\0福井\0山梨\0長野\0岐阜\0静岡\0愛知\0三重\0滋賀\0京都\0大阪\0兵庫\0奈良\0和歌山\0鳥取\0島根\0岡山\0広島\0山口\0徳島\0香川\0愛媛\0高知\0福岡\0佐賀\0長崎\0熊本\0大分\0宮崎\0鹿児島\0奄美(群島)\0沖縄本島\0大東島\0宮古島\0八重山\0北海道\0東北\0関東\0伊豆諸島\0小笠原\0北陸\0甲信\0東海\0近畿\0中国\0四国\0九州\0奄美(群島)\0沖縄\0その他の府県予報区および地方予報区\0";
struct QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[] AZARAC_PROGMEM = {
    {0u, 15u},
    {16u, 15u},
    {32u, 15u},
    {48u, 15u},
    {64u, 6u},
    {71u, 6u},
    {78u, 6u},
    {85u, 6u},
    {92u, 6u},
    {99u, 6u},
    {106u, 6u},
    {113u, 6u},
    {120u, 6u},
    {127u, 6u},
    {134u, 6u},
    {141u, 6u},
    {148u, 12u},
    {161u, 9u},
    {171u, 9u},
    {181u, 6u},
    {188u, 6u},
    {195u, 6u},
    {202u, 6u},
    {209u, 6u},
    {216u, 6u},
    {223u, 6u},
    {230u, 6u},
    {237u, 6u},
    {244u, 6u},
    {251u, 6u},
    {258u, 6u},
    {265u, 6u},
    {272u, 6u},
    {279u, 6u},
    {286u, 9u},
    {296u, 6u},
    {303u, 6u},
    {310u, 6u},
    {317u, 6u},
    {324u, 6u},
    {331u, 6u},
    {338u, 6u},
    {345u, 6u},
    {352u, 6u},
    {359u, 6u},
    {366u, 6u},
    {373u, 6u},
    {380u, 6u},
    {387u, 6u},
    {394u, 6u},
    {401u, 9u},
    {411u, 14u},
    {426u, 12u},
    {439u, 9u},
    {449u, 9u},
    {459u, 9u},
    {469u, 9u},
    {479u, 6u},
    {486u, 6u},
    {493u, 12u},
    {506u, 9u},
    {516u, 6u},
    {523u, 6u},
    {530u, 6u},
    {537u, 6u},
    {544u, 6u},
    {551u, 6u},
    {558u, 6u},
    {565u, 14u},
    {580u, 6u},
    {587u, 51u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_EEW_FORECAST_REGION_BASE || id >= QZSS_DCR_JMA_EEW_FORECAST_REGION_BASE + QZSS_DCR_JMA_EEW_FORECAST_REGION_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[id - 1u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry, len));
    if (n == 0) return std::nullopt;
    return azarac_pgm_view(QZSS_DCR_JMA_EEW_FORECAST_REGION_POOL + off, n);
}
#else
inline constexpr std::optional<std::string_view> QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[] = {
    std::string_view{"北海道道央", 15},
    std::string_view{"北海道道南", 15},
    std::string_view{"北海道道北", 15},
    std::string_view{"北海道道東", 15},
    std::string_view{"青森", 6},
    std::string_view{"岩手", 6},
    std::string_view{"宮城", 6},
    std::string_view{"秋田", 6},
    std::string_view{"山形", 6},
    std::string_view{"福島", 6},
    std::string_view{"茨城", 6},
    std::string_view{"栃木", 6},
    std::string_view{"群馬", 6},
    std::string_view{"埼玉", 6},
    std::string_view{"千葉", 6},
    std::string_view{"東京", 6},
    std::string_view{"伊豆諸島", 12},
    std::string_view{"小笠原", 9},
    std::string_view{"神奈川", 9},
    std::string_view{"新潟", 6},
    std::string_view{"富山", 6},
    std::string_view{"石川", 6},
    std::string_view{"福井", 6},
    std::string_view{"山梨", 6},
    std::string_view{"長野", 6},
    std::string_view{"岐阜", 6},
    std::string_view{"静岡", 6},
    std::string_view{"愛知", 6},
    std::string_view{"三重", 6},
    std::string_view{"滋賀", 6},
    std::string_view{"京都", 6},
    std::string_view{"大阪", 6},
    std::string_view{"兵庫", 6},
    std::string_view{"奈良", 6},
    std::string_view{"和歌山", 9},
    std::string_view{"鳥取", 6},
    std::string_view{"島根", 6},
    std::string_view{"岡山", 6},
    std::string_view{"広島", 6},
    std::string_view{"山口", 6},
    std::string_view{"徳島", 6},
    std::string_view{"香川", 6},
    std::string_view{"愛媛", 6},
    std::string_view{"高知", 6},
    std::string_view{"福岡", 6},
    std::string_view{"佐賀", 6},
    std::string_view{"長崎", 6},
    std::string_view{"熊本", 6},
    std::string_view{"大分", 6},
    std::string_view{"宮崎", 6},
    std::string_view{"鹿児島", 9},
    std::string_view{"奄美(群島)", 14},
    std::string_view{"沖縄本島", 12},
    std::string_view{"大東島", 9},
    std::string_view{"宮古島", 9},
    std::string_view{"八重山", 9},
    std::string_view{"北海道", 9},
    std::string_view{"東北", 6},
    std::string_view{"関東", 6},
    std::string_view{"伊豆諸島", 12},
    std::string_view{"小笠原", 9},
    std::string_view{"北陸", 6},
    std::string_view{"甲信", 6},
    std::string_view{"東海", 6},
    std::string_view{"近畿", 6},
    std::string_view{"中国", 6},
    std::string_view{"四国", 6},
    std::string_view{"九州", 6},
    std::string_view{"奄美(群島)", 14},
    std::string_view{"沖縄", 6},
    std::string_view{"その他の府県予報区および地方予報区", 51}
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_EEW_FORECAST_REGION_BASE || id >= QZSS_DCR_JMA_EEW_FORECAST_REGION_BASE + QZSS_DCR_JMA_EEW_FORECAST_REGION_SIZE) return std::nullopt;
    return QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[id - QZSS_DCR_JMA_EEW_FORECAST_REGION_BASE];
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
