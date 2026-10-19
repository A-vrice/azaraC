#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.d_fields → qzss_dcx_camf_d25_uv_index: 10 entries, strategy switch
// Unknown id returns nullptr — callers MUST null-check.

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

#if (AZARAC_ENABLE_DCX_CAMF)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D25_UV_INDEX_C0[] = "Index 0 - 2 Low. No protection needed. You can safely stay outside using minimal sun protection.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D25_UV_INDEX_C1[] = "Index 3/11 Moderate";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D25_UV_INDEX_C2[] = "Index 4/11 Moderate";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D25_UV_INDEX_C3[] = "Index 5/11 High";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D25_UV_INDEX_C4[] = "Index 6/11 High";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D25_UV_INDEX_C5[] = "Index 7/11 High";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D25_UV_INDEX_C6[] = "Index 8/11 Very high";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D25_UV_INDEX_C7[] = "Index 9/11 Very high";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D25_UV_INDEX_C8[] = "Index 10/11 Extreme";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D25_UV_INDEX_C9[] = "Index 11/11 Extreme";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D25_UV_INDEX_PARENT_POOL[] = ". Extra protection needed. Be careful outside, especially during late morning through mid-afternoon. If your shadow is shorter than you, seek shade and wear protective clothing, a wide-brimmed hat, and sunglasses, and generously apply a minimum of SPF-15, broad-spectrum sunscreen on exposed skin.\000. Protection needed. Seek shade during late morning through mid-afternoon. When outside, generously apply broad-spectrum SPF-15 or higher sunscreen on exposed skin, and wear protective clothing, a wide-brimmed hat, and sunglasses.\000";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d25_uv_index_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D25_UV_INDEX_C0), 96);
        case 1: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D25_UV_INDEX_C1), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D25_UV_INDEX_PARENT_POOL) + 298u);
        case 2: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D25_UV_INDEX_C2), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D25_UV_INDEX_PARENT_POOL) + 298u);
        case 3: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D25_UV_INDEX_C3), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D25_UV_INDEX_PARENT_POOL) + 298u);
        case 4: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D25_UV_INDEX_C4), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D25_UV_INDEX_PARENT_POOL) + 298u);
        case 5: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D25_UV_INDEX_C5), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D25_UV_INDEX_PARENT_POOL) + 298u);
        case 6: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D25_UV_INDEX_C6), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D25_UV_INDEX_PARENT_POOL) + 0u);
        case 7: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D25_UV_INDEX_C7), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D25_UV_INDEX_PARENT_POOL) + 0u);
        case 8: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D25_UV_INDEX_C8), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D25_UV_INDEX_PARENT_POOL) + 0u);
        case 9: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D25_UV_INDEX_C9), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D25_UV_INDEX_PARENT_POOL) + 0u);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d25_uv_index_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Index 0 - 2 Low. No protection needed. You can safely stay outside using minimal sun protection.", 96};
        case 1: return std::string_view{"Index 3/11 Moderate. Protection needed. Seek shade during late morning through mid-afternoon. When outside, generously apply broad-spectrum SPF-15 or higher sunscreen on exposed skin, and wear protective clothing, a wide-brimmed hat, and sunglasses.", 249};
        case 2: return std::string_view{"Index 4/11 Moderate. Protection needed. Seek shade during late morning through mid-afternoon. When outside, generously apply broad-spectrum SPF-15 or higher sunscreen on exposed skin, and wear protective clothing, a wide-brimmed hat, and sunglasses.", 249};
        case 3: return std::string_view{"Index 5/11 High. Protection needed. Seek shade during late morning through mid-afternoon. When outside, generously apply broad-spectrum SPF-15 or higher sunscreen on exposed skin, and wear protective clothing, a wide-brimmed hat, and sunglasses.", 245};
        case 4: return std::string_view{"Index 6/11 High. Protection needed. Seek shade during late morning through mid-afternoon. When outside, generously apply broad-spectrum SPF-15 or higher sunscreen on exposed skin, and wear protective clothing, a wide-brimmed hat, and sunglasses.", 245};
        case 5: return std::string_view{"Index 7/11 High. Protection needed. Seek shade during late morning through mid-afternoon. When outside, generously apply broad-spectrum SPF-15 or higher sunscreen on exposed skin, and wear protective clothing, a wide-brimmed hat, and sunglasses.", 245};
        case 6: return std::string_view{"Index 8/11 Very high. Extra protection needed. Be careful outside, especially during late morning through mid-afternoon. If your shadow is shorter than you, seek shade and wear protective clothing, a wide-brimmed hat, and sunglasses, and generously apply a minimum of SPF-15, broad-spectrum sunscreen on exposed skin.", 317};
        case 7: return std::string_view{"Index 9/11 Very high. Extra protection needed. Be careful outside, especially during late morning through mid-afternoon. If your shadow is shorter than you, seek shade and wear protective clothing, a wide-brimmed hat, and sunglasses, and generously apply a minimum of SPF-15, broad-spectrum sunscreen on exposed skin.", 317};
        case 8: return std::string_view{"Index 10/11 Extreme. Extra protection needed. Be careful outside, especially during late morning through mid-afternoon. If your shadow is shorter than you, seek shade and wear protective clothing, a wide-brimmed hat, and sunglasses, and generously apply a minimum of SPF-15, broad-spectrum sunscreen on exposed skin.", 316};
        case 9: return std::string_view{"Index 11/11 Extreme. Extra protection needed. Be careful outside, especially during late morning through mid-afternoon. If your shadow is shorter than you, seek shade and wear protective clothing, a wide-brimmed hat, and sunglasses, and generously apply a minimum of SPF-15, broad-spectrum sunscreen on exposed skin.", 316};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d25_uv_index_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d25_uv_index_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
