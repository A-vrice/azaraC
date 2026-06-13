#pragma once
// AUTO-GENERATED from azarashi: qzss_dcx_camf_a3_provider_identifier
#include <cstdint>
#include <optional>
#include <string_view>
namespace azaraC { namespace def {

struct A3Entry { uint16_t key; std::string_view label; };
static constexpr A3Entry QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER[] = {
  {161, std::string_view{"National Emergency Management Agency", 35}},
  {162, std::string_view{"Bureau of Meteorology", 21}},
  {163, std::string_view{"Australian Climate Service", 26}},
  {164, std::string_view{"Geoscience Australia", 19}},
  {165, std::string_view{"Commonwealth Scientific and Industrial Research Organisation", 60}},
  {166, std::string_view{"Australian Bureau of Statistics", 31}},
  {167, std::string_view{"Resilience New South Wales", 26}},
  {168, std::string_view{"State Emergency Service New South Wales", 38}},
  {169, std::string_view{"New South Wales Rural Fire Service", 34}},
  {170, std::string_view{"Joint Australian Tsunami Warning Centre", 38}},
  {171, std::string_view{"Flood Knowledge Centre", 22}},
  {172, std::string_view{"Australian Broadcasting Corporation", 34}},
  {1137, std::string_view{"National Disaster Management Office", 34}},
  {1138, std::string_view{"Fiji Meteorological Service", 25}},
  {1139, std::string_view{"Hydrology Section, Fiji Water Authority", 40}},
  {1140, std::string_view{"Mineral Resources Department", 27}},
  {1141, std::string_view{"Fiji Broadcasting Corporation", 27}},
  {1777, std::string_view{"Foundation for MultiMedia Communications", 40}},
  {1778, std::string_view{"Fire and Disaster Management Agency", 35}},
  {1779, std::string_view{"Related Ministries", 18}},
  {1780, std::string_view{"Local Government", 15}},
  {3505, std::string_view{"Department of Disaster Prevention and Mitigation", 46}},
  {3506, std::string_view{"Thai Meteorological Department", 28}},
  {3507, std::string_view{"National Disaster Warning Center", 31}},
  {3508, std::string_view{"Department of Mineral Resources", 31}},
  {3509, std::string_view{"Navy Hydrographic Department, Royal Thai Navy", 46}},
  {3510, std::string_view{"Department of Water Resources", 28}},
  {3511, std::string_view{"Royal Irrigation Department", 25}},
  {3512, std::string_view{"Department of Pollution Control", 29}},
  {3513, std::string_view{"Geo-Informatics and Space Technology Development Agency", 56}},
  {3514, std::string_view{"Electricity Generating Authority of Thailand", 42}},
  {3515, std::string_view{"Royal Forest Department", 22}},
  {3516, std::string_view{"Department of Parks, Wildlife and Plant Conservation", 50}},
  {3517, std::string_view{"Water Crisis Prevention Center", 30}},
};

[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_lookup(uint16_t country, uint8_t provider) {
  uint16_t key = (uint16_t)((country << 4) | (provider & 0xF));
  for (const auto& e : QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER) {
    if (e.key == key) return e.label;
  }
  return std::nullopt;
}

}} // namespace
