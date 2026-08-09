#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_information_serial_code
// Variable      : qzss_dcr_jma_information_serial_code
// Entries       : 7
// Strategy      : switch

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

#if (AZARAC_ENABLE_NANKAI)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_information_serial_code_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: { static const char AZARAC_PROGMEM s[] = "調査中A（監視領域内でマグニチュード6.8以上の地震が発生したことにより、臨時に「南海トラフ沿いの地震に関する評価検討会」を開催）"; return azarac_pgm_view(s, 187); }
        case 2: { static const char AZARAC_PROGMEM s[] = "調査中B（1カ所以上のひずみ計での有意な変化と共に、他の複数の観測点でもそれに関係すると思われる変化が観測され、想定震源域内のプレート境界で通常と異なるゆっくりすべりが発生している可能性がある場合など、ひずみ計で南海トラフ地震との関連性の検討が必要と認められる変化を観測したことにより、臨時に「南海トラフ沿いの地震に関する評価検討会」を開催）"; return azarac_pgm_view(s, 509); }
        case 3: { static const char AZARAC_PROGMEM s[] = "調査中C（その他、想定震源域内のプレート境界の固着状態の変化を示す可能性のある現象が観測される等、南海トラフ地震との関連性の検討が必要と認められる現象を観測したことにより、臨時に「南海トラフ沿いの地震に関する評価検討会」を開催）"; return azarac_pgm_view(s, 340); }
        case 4: { static const char AZARAC_PROGMEM s[] = "巨大地震警戒"; return azarac_pgm_view(s, 18); }
        case 5: { static const char AZARAC_PROGMEM s[] = "巨大地震注意"; return azarac_pgm_view(s, 18); }
        case 6: { static const char AZARAC_PROGMEM s[] = "調査終了"; return azarac_pgm_view(s, 12); }
        case 15: { static const char AZARAC_PROGMEM s[] = "その他の情報"; return azarac_pgm_view(s, 18); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_information_serial_code_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"調査中A（監視領域内でマグニチュード6.8以上の地震が発生したことにより、臨時に「南海トラフ沿いの地震に関する評価検討会」を開催）", 187};
        case 2: return std::string_view{"調査中B（1カ所以上のひずみ計での有意な変化と共に、他の複数の観測点でもそれに関係すると思われる変化が観測され、想定震源域内のプレート境界で通常と異なるゆっくりすべりが発生している可能性がある場合など、ひずみ計で南海トラフ地震との関連性の検討が必要と認められる変化を観測したことにより、臨時に「南海トラフ沿いの地震に関する評価検討会」を開催）", 509};
        case 3: return std::string_view{"調査中C（その他、想定震源域内のプレート境界の固着状態の変化を示す可能性のある現象が観測される等、南海トラフ地震との関連性の検討が必要と認められる現象を観測したことにより、臨時に「南海トラフ沿いの地震に関する評価検討会」を開催）", 340};
        case 4: return std::string_view{"巨大地震警戒", 18};
        case 5: return std::string_view{"巨大地震注意", 18};
        case 6: return std::string_view{"調査終了", 12};
        case 15: return std::string_view{"その他の情報", 18};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_information_serial_code_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_information_serial_code_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
