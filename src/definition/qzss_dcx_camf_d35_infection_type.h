#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d35_infection_type
// Entries       : 63
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

#if (AZARAC_ENABLE_DCX_CAMF)

inline constexpr uint8_t QZSS_DCX_CAMF_D35_INFECTION_TYPE_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D35_INFECTION_TYPE_SIZE = 63;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D35_INFECTION_TYPE_POOL[] = "Anthrax\000Avian influenza in humans\000Botulism\000Brucellosis\000Campylobacteriosis\000Chikungunya virus disease\000Chlamydia infections\000Cholera\000COVID - 19\000Creutzfeldt - Jakob Disease - variant(vCJD)\000Cryptosporidiosis\000Dengue\000Diphtheria\000Echinococcosis\000Giardiasis\000Gonorrhoea\000Hepatitis A\000Hepatitis B\000Hepatitis C\000HIV infection and AIDS\000Infections with haemophilus influenza group B\000Influenza including Influenza A(H1N1)\000Invasive meningococcal disease\000Invasive pneumococcal disease\000Legionnaires' disease\000Leptospirosis\000Listeriosis\000Lyme neuroborreliosis\000Malaria\000Measles\000Meningococcal disease, invasive\000Mumps\000Pertussis\000Plague\000Pneumococcal invasive diseases\000Poliomyelitis\000Q fever\000Rabies\000Rubella\000Rubella, congenital\000Salmonellosis\000Severe Acute Respiratory Syndrome (SARS)\000Shiga toxin /verocytotoxin -producing Escherichia coli (STEC/VTEC)\000Shigellosis\000Smallpox\000Syphilis\000Syphilis, congenital\000Tetanus\000Tick-borne encephalitis\000Toxoplasmosis, congenital\000Trichinellosis\000Tuberculosis\000Tularaemia\000Typhoid and paratyphoid fevers\000Viral haemorrhagic fevers\000West Nile virus infection\000Yellow fever\000Yersinosis\000Zika virus disease\000Zika virus disease, congenital\000Nosocomial infections\000Antimicrobial resistance\000unidentified infection\000";
struct QZSS_DCX_CAMF_D35_INFECTION_TYPE_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_D35_INFECTION_TYPE_Entry QZSS_DCX_CAMF_D35_INFECTION_TYPE_TABLE[] AZARAC_PROGMEM = {
    {0u, 7u},
    {8u, 25u},
    {34u, 8u},
    {43u, 11u},
    {55u, 18u},
    {74u, 25u},
    {100u, 20u},
    {121u, 7u},
    {129u, 10u},
    {140u, 43u},
    {184u, 17u},
    {202u, 6u},
    {209u, 10u},
    {220u, 14u},
    {235u, 10u},
    {246u, 10u},
    {257u, 11u},
    {269u, 11u},
    {281u, 11u},
    {293u, 22u},
    {316u, 45u},
    {362u, 37u},
    {400u, 30u},
    {431u, 29u},
    {461u, 21u},
    {483u, 13u},
    {497u, 11u},
    {509u, 21u},
    {531u, 7u},
    {539u, 7u},
    {547u, 31u},
    {579u, 5u},
    {585u, 9u},
    {595u, 6u},
    {602u, 30u},
    {633u, 13u},
    {647u, 7u},
    {655u, 6u},
    {662u, 7u},
    {670u, 19u},
    {690u, 13u},
    {704u, 40u},
    {745u, 66u},
    {812u, 11u},
    {824u, 8u},
    {833u, 8u},
    {842u, 20u},
    {863u, 7u},
    {871u, 23u},
    {895u, 25u},
    {921u, 14u},
    {936u, 12u},
    {949u, 10u},
    {960u, 30u},
    {991u, 25u},
    {1017u, 25u},
    {1043u, 12u},
    {1056u, 10u},
    {1067u, 18u},
    {1086u, 30u},
    {1117u, 21u},
    {1139u, 24u},
    {1164u, 22u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d35_infection_type_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D35_INFECTION_TYPE_BASE || id >= QZSS_DCX_CAMF_D35_INFECTION_TYPE_BASE + QZSS_DCX_CAMF_D35_INFECTION_TYPE_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D35_INFECTION_TYPE_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D35_INFECTION_TYPE_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D35_INFECTION_TYPE_Entry, len));
    return azarac_pgm_view(QZSS_DCX_CAMF_D35_INFECTION_TYPE_POOL + off, n);
}
#else
inline constexpr const char* QZSS_DCX_CAMF_D35_INFECTION_TYPE_TABLE[] = {
    "Anthrax",
    "Avian influenza in humans",
    "Botulism",
    "Brucellosis",
    "Campylobacteriosis",
    "Chikungunya virus disease",
    "Chlamydia infections",
    "Cholera",
    "COVID - 19",
    "Creutzfeldt - Jakob Disease - variant(vCJD)",
    "Cryptosporidiosis",
    "Dengue",
    "Diphtheria",
    "Echinococcosis",
    "Giardiasis",
    "Gonorrhoea",
    "Hepatitis A",
    "Hepatitis B",
    "Hepatitis C",
    "HIV infection and AIDS",
    "Infections with haemophilus influenza group B",
    "Influenza including Influenza A(H1N1)",
    "Invasive meningococcal disease",
    "Invasive pneumococcal disease",
    "Legionnaires' disease",
    "Leptospirosis",
    "Listeriosis",
    "Lyme neuroborreliosis",
    "Malaria",
    "Measles",
    "Meningococcal disease, invasive",
    "Mumps",
    "Pertussis",
    "Plague",
    "Pneumococcal invasive diseases",
    "Poliomyelitis",
    "Q fever",
    "Rabies",
    "Rubella",
    "Rubella, congenital",
    "Salmonellosis",
    "Severe Acute Respiratory Syndrome (SARS)",
    "Shiga toxin /verocytotoxin -producing Escherichia coli (STEC/VTEC)",
    "Shigellosis",
    "Smallpox",
    "Syphilis",
    "Syphilis, congenital",
    "Tetanus",
    "Tick-borne encephalitis",
    "Toxoplasmosis, congenital",
    "Trichinellosis",
    "Tuberculosis",
    "Tularaemia",
    "Typhoid and paratyphoid fevers",
    "Viral haemorrhagic fevers",
    "West Nile virus infection",
    "Yellow fever",
    "Yersinosis",
    "Zika virus disease",
    "Zika virus disease, congenital",
    "Nosocomial infections",
    "Antimicrobial resistance",
    "unidentified infection"
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d35_infection_type_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D35_INFECTION_TYPE_BASE || id >= QZSS_DCX_CAMF_D35_INFECTION_TYPE_BASE + QZSS_DCX_CAMF_D35_INFECTION_TYPE_SIZE) return std::nullopt;
    const char* s = QZSS_DCX_CAMF_D35_INFECTION_TYPE_TABLE[id - QZSS_DCX_CAMF_D35_INFECTION_TYPE_BASE];
    return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d35_infection_type_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d35_infection_type_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
