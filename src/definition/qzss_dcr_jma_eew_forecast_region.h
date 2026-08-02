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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_EEW_FORECAST_REGION_POOL[] = "北海道道央\000北海道道南\000北海道道北\000北海道道東\000青森\000岩手\000宮城\000秋田\000山形\000福島\000茨城\000栃木\000群馬\000埼玉\000千葉\000東京\000伊豆諸島\000小笠原\000神奈川\000新潟\000富山\000石川\000福井\000山梨\000長野\000岐阜\000静岡\000愛知\000三重\000滋賀\000京都\000大阪\000兵庫\000奈良\000和歌山\000鳥取\000島根\000岡山\000広島\000山口\000徳島\000香川\000愛媛\000高知\000福岡\000佐賀\000長崎\000熊本\000大分\000宮崎\000鹿児島\000奄美(群島)\000沖縄本島\000大東島\000宮古島\000八重山\000北海道\000東北\000関東\000伊豆諸島\000小笠原\000北陸\000甲信\000東海\000近畿\000中国\000四国\000九州\000奄美(群島)\000沖縄\000その他の府県予報区および地方予報区\000";
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

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
