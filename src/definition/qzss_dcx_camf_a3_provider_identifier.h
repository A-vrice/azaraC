#pragma once
// AUTO-GENERATED from azarashi: qzss_dcx_camf_a3_provider_identifier
#if defined(__AVR__)
#include "../internal/avr_std/cstdint"
#else
#include <cstdint>
#endif
#if defined(__AVR__)
#include "../internal/avr_std/optional"
#else
#include <optional>
#endif
#if defined(__AVR__)
#include "../internal/avr_std/string_view"
#else
#include <string_view>
#endif
#include "../azaraC_config.h"
#include "../internal/FlashString.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_DCX_CAMF)

#if defined(__AVR__)

// AVR: string pool + offset table stored in Flash (PROGMEM)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_POOL[] =
    "National Emergency Management Agency\0Bureau of Meteorology\0Australian Climate Service\0Geoscience Australia\0Commonwealth Scientific and Industrial Research Organisation\0Australian Bureau of Statistics\0Resilience New South Wales\0State Emergency Service New South Wales\0New South Wales Rural Fire Service\0Joint Australian Tsunami Warning Centre\0Flood Knowledge Centre\0Australian Broadcasting Corporation\0National Disaster Management Office\0Fiji Meteorological Service\0Hydrology Section, Fiji Water Authority\0Mineral Resources Department\0Fiji Broadcasting Corporation\0Foundation for MultiMedia Communications\0Fire and Disaster Management Agency\0Related Ministries\0Local Government\0Department of Disaster Prevention and Mitigation\0Thai Meteorological Department\0National Disaster Warning Center\0Department of Mineral Resources\0Navy Hydrographic Department, Royal Thai Navy\0Department of Water Resources\0Royal Irrigation Department\0Department of Pollution Control\0Geo-Informatics and Space Technology Development Agency\0Electricity Generating Authority of Thailand\0Royal Forest Department\0Department of Parks, Wildlife and Plant Conservation\0Water Crisis Prevention Center\0";

struct QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_Entry {
    uint16_t key;
    uint16_t offset;
    uint16_t len;
};

static const QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_Entry
    QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_TABLE[] AZARAC_PROGMEM = {
    {161u, 0u, 36u},
    {162u, 37u, 21u},
    {163u, 59u, 26u},
    {164u, 86u, 20u},
    {165u, 107u, 60u},
    {166u, 168u, 31u},
    {167u, 200u, 26u},
    {168u, 227u, 39u},
    {169u, 267u, 34u},
    {170u, 302u, 39u},
    {171u, 342u, 22u},
    {172u, 365u, 35u},
    {1137u, 401u, 35u},
    {1138u, 437u, 27u},
    {1139u, 465u, 39u},
    {1140u, 505u, 28u},
    {1141u, 534u, 29u},
    {1777u, 564u, 40u},
    {1778u, 605u, 35u},
    {1779u, 641u, 18u},
    {1780u, 660u, 16u},
    {3505u, 677u, 48u},
    {3506u, 726u, 30u},
    {3507u, 757u, 32u},
    {3508u, 790u, 31u},
    {3509u, 822u, 45u},
    {3510u, 868u, 29u},
    {3511u, 898u, 27u},
    {3512u, 926u, 31u},
    {3513u, 958u, 55u},
    {3514u, 1014u, 44u},
    {3515u, 1059u, 23u},
    {3516u, 1083u, 52u},
    {3517u, 1136u, 30u},
};

[[nodiscard]] inline std::optional<std::string_view>
qzss_dcx_camf_a3_provider_identifier_lookup(uint16_t country, uint8_t provider) {
  uint16_t key = static_cast<uint16_t>((country << 4) | (provider & 0xF));
  uint8_t lo = 0,
          hi = static_cast<uint8_t>(sizeof(QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_TABLE) /
                                    sizeof(QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_TABLE[0]));
  while (lo < hi) {
    uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
    const char* AZARAC_PROGMEM ep =
        reinterpret_cast<const char*>(&QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_TABLE[mid]);
    uint16_t ekey = pgm_read_word(
        ep + offsetof(QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_Entry, key));
    if (ekey == key) {
      uint16_t off = pgm_read_word(
          ep + offsetof(QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_Entry, offset));
      uint16_t n = pgm_read_word(
          ep + offsetof(QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_Entry, len));
      return azarac_pgm_view(QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_POOL + off, n);
    }
    if (ekey < key) lo = mid + 1;
    else hi = mid;
  }
  return std::nullopt;
}

#else

struct A3Entry { uint16_t key; const char* label; };
static constexpr A3Entry QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER[] = {
  {161, "National Emergency Management Agency"},
  {162, "Bureau of Meteorology"},
  {163, "Australian Climate Service"},
  {164, "Geoscience Australia"},
  {165, "Commonwealth Scientific and Industrial Research Organisation"},
  {166, "Australian Bureau of Statistics"},
  {167, "Resilience New South Wales"},
  {168, "State Emergency Service New South Wales"},
  {169, "New South Wales Rural Fire Service"},
  {170, "Joint Australian Tsunami Warning Centre"},
  {171, "Flood Knowledge Centre"},
  {172, "Australian Broadcasting Corporation"},
  {1137, "National Disaster Management Office"},
  {1138, "Fiji Meteorological Service"},
  {1139, "Hydrology Section, Fiji Water Authority"},
  {1140, "Mineral Resources Department"},
  {1141, "Fiji Broadcasting Corporation"},
  {1777, "Foundation for MultiMedia Communications"},
  {1778, "Fire and Disaster Management Agency"},
  {1779, "Related Ministries"},
  {1780, "Local Government"},
  {3505, "Department of Disaster Prevention and Mitigation"},
  {3506, "Thai Meteorological Department"},
  {3507, "National Disaster Warning Center"},
  {3508, "Department of Mineral Resources"},
  {3509, "Navy Hydrographic Department, Royal Thai Navy"},
  {3510, "Department of Water Resources"},
  {3511, "Royal Irrigation Department"},
  {3512, "Department of Pollution Control"},
  {3513, "Geo-Informatics and Space Technology Development Agency"},
  {3514, "Electricity Generating Authority of Thailand"},
  {3515, "Royal Forest Department"},
  {3516, "Department of Parks, Wildlife and Plant Conservation"},
  {3517, "Water Crisis Prevention Center"},
};

[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_lookup(uint16_t country, uint8_t provider) {
  uint16_t key = (uint16_t)((country << 4) | (provider & 0xF));
  constexpr auto _count = std::size(QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER);
  uint16_t lo = 0, hi = static_cast<uint16_t>(_count);
  while (lo < hi) {
    uint16_t mid = static_cast<uint16_t>(lo + (hi - lo) / 2);
    if (QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER[mid].key == key) {
      const char* s = QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER[mid].label;
      return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
    }
    if (QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER[mid].key < key) lo = mid + 1;
    else hi = mid;
  }
  return std::nullopt;
}

#endif // __AVR__

#else

[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_lookup(uint16_t country, uint8_t provider) {
  (void)country;
  (void)provider;
  return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
