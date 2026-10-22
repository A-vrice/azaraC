#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.d_fields → qzss_dcx_camf_d17_fog_level: 5 entries, strategy switch
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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D17_FOG_LEVEL_C0[] = "1 of 5: Slight fog or Mist. On land, object appear hazy or blurry. Road and rail traffic are unhindered. On sea, horizon cannot be seen. Lights and landmarks can be seen at working distances.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D17_FOG_LEVEL_C1[] = "2 of 5: Slight fog. On land, railroad traffic takes additional caution. On sea, Lights on passing vessel are generally not distinct at distances under 1 mile. Fog signals are sounded.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D17_FOG_LEVEL_C2[] = "3 of 5: Moderate fog. On land, rail and road traffic is obstructed. On sea, Lights on passing vessels are generally not distinct at distances under 1 mile. Fog signals are sounded. On river, navigation is unhindered but extra caution is required.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D17_FOG_LEVEL_C3[] = "4 of 5: Moderate fog. On land, rail and road traffic impeded. On sea, lights on ships and other vessels cannot be seen at distances of 4 miles or less. On river, navigation is suspended.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D17_FOG_LEVEL_C4[] = "5 of 5: Thick fog. On land, all traffic is impeded and totally disorganised. On sea, lights on ships and other vessels cannot be seen at distances of 4 miles or less. On river, navigation is suspended.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D17_FOG_LEVEL_PARENT_POOL[] = "Level \000";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d17_fog_level_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D17_FOG_LEVEL_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D17_FOG_LEVEL_C0));
        case 1: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D17_FOG_LEVEL_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D17_FOG_LEVEL_C1));
        case 2: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D17_FOG_LEVEL_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D17_FOG_LEVEL_C2));
        case 3: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D17_FOG_LEVEL_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D17_FOG_LEVEL_C3));
        case 4: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D17_FOG_LEVEL_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D17_FOG_LEVEL_C4));
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d17_fog_level_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Level 1 of 5: Slight fog or Mist. On land, object appear hazy or blurry. Road and rail traffic are unhindered. On sea, horizon cannot be seen. Lights and landmarks can be seen at working distances.", 197};
        case 1: return std::string_view{"Level 2 of 5: Slight fog. On land, railroad traffic takes additional caution. On sea, Lights on passing vessel are generally not distinct at distances under 1 mile. Fog signals are sounded.", 189};
        case 2: return std::string_view{"Level 3 of 5: Moderate fog. On land, rail and road traffic is obstructed. On sea, Lights on passing vessels are generally not distinct at distances under 1 mile. Fog signals are sounded. On river, navigation is unhindered but extra caution is required.", 252};
        case 3: return std::string_view{"Level 4 of 5: Moderate fog. On land, rail and road traffic impeded. On sea, lights on ships and other vessels cannot be seen at distances of 4 miles or less. On river, navigation is suspended.", 192};
        case 4: return std::string_view{"Level 5 of 5: Thick fog. On land, all traffic is impeded and totally disorganised. On sea, lights on ships and other vessels cannot be seen at distances of 4 miles or less. On river, navigation is suspended.", 207};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d17_fog_level_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d17_fog_level_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
