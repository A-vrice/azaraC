#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.camf.d_fields
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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D35_INFECTION_TYPE_POOL[] = "Anthrax\000Avian influenza in humans\000Botulism\000Bruc\000Campylobacter\000Chikungunya virus\000Chlamydia infections\000Cholera\000COVID - 19\000Creutzfeldt - Jakob Disease - variant(vCJD)\000Cryptosporid\000Dengue\000Diphtheria\000Echinococc\000Giardiasis\000Gonorrhoea\000Hepatitis A\000Hepatitis B\000Hepatitis C\000HIV infection and AIDS\000Infections with haemophilus influenza group B\000Influenza including Influenza A(H1N1)\000Invasive meningococcal\000Invasive pneumococcal\000Legionnaires'\000Leptospir\000Lister\000Lyme neuroborrel\000Malaria\000Measles\000Meningococcal disease, invasive\000Mumps\000Pertussis\000Plague\000Pneumococcal invasive diseases\000Poliomyelitis\000Q fever\000Rabies\000Rubella\000Rubella\000Salmon\000Severe Acute Respiratory Syndrome (SARS)\000Shiga toxin /verocytotoxin -producing Escherichia coli (STEC/VTEC)\000Shig\000Smallpox\000Syphilis\000Syphilis\000Tetanus\000Tick-borne encephalitis\000Toxoplasmosis\000Trichin\000Tubercu\000Tularaemia\000Typhoid and paratyphoid fevers\000Viral haemorrhagic fevers\000West Nile virus infection\000Yellow fever\000Yersin\000Zika virus\000Zika virus disease\000Nosocomial infections\000Antimicrobial resistance\000unidentified infection\000";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D35_INFECTION_TYPE_PARENT_POOL[] = " disease\000, congenital\000ellosis\000iosis\000losis\000osis\000";
struct QZSS_DCX_CAMF_D35_INFECTION_TYPE_PARENT_Entry { uint16_t offset; };
static const QZSS_DCX_CAMF_D35_INFECTION_TYPE_PARENT_Entry QZSS_DCX_CAMF_D35_INFECTION_TYPE_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {9u},
    {22u},
    {30u},
    {36u},
    {42u},
};
struct QZSS_DCX_CAMF_D35_INFECTION_TYPE_Entry { uint16_t offset; uint8_t parent; };
static const QZSS_DCX_CAMF_D35_INFECTION_TYPE_Entry QZSS_DCX_CAMF_D35_INFECTION_TYPE_TABLE[] AZARAC_PROGMEM = {
    {0u, 255u},
    {8u, 255u},
    {34u, 255u},
    {43u, 2u},
    {48u, 3u},
    {62u, 0u},
    {80u, 255u},
    {101u, 255u},
    {109u, 255u},
    {120u, 255u},
    {164u, 3u},
    {177u, 255u},
    {184u, 255u},
    {195u, 5u},
    {206u, 255u},
    {217u, 255u},
    {228u, 255u},
    {240u, 255u},
    {252u, 255u},
    {264u, 255u},
    {287u, 255u},
    {333u, 255u},
    {371u, 0u},
    {394u, 0u},
    {416u, 0u},
    {430u, 5u},
    {440u, 3u},
    {447u, 3u},
    {464u, 255u},
    {472u, 255u},
    {480u, 255u},
    {512u, 255u},
    {518u, 255u},
    {528u, 255u},
    {535u, 255u},
    {566u, 255u},
    {580u, 255u},
    {588u, 255u},
    {595u, 255u},
    {603u, 1u},
    {611u, 2u},
    {618u, 255u},
    {659u, 255u},
    {726u, 2u},
    {731u, 255u},
    {740u, 255u},
    {749u, 1u},
    {758u, 255u},
    {766u, 255u},
    {790u, 1u},
    {804u, 2u},
    {812u, 4u},
    {820u, 255u},
    {831u, 255u},
    {862u, 255u},
    {888u, 255u},
    {914u, 255u},
    {927u, 5u},
    {934u, 0u},
    {945u, 1u},
    {964u, 255u},
    {986u, 255u},
    {1011u, 255u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d35_infection_type_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D35_INFECTION_TYPE_BASE || id >= QZSS_DCX_CAMF_D35_INFECTION_TYPE_BASE + QZSS_DCX_CAMF_D35_INFECTION_TYPE_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D35_INFECTION_TYPE_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D35_INFECTION_TYPE_Entry, offset));
    uint8_t pi = pgm_read_byte(p + offsetof(QZSS_DCX_CAMF_D35_INFECTION_TYPE_Entry, parent));
    if (pi == 255u) return azarac_pgm_view_z(QZSS_DCX_CAMF_D35_INFECTION_TYPE_POOL + off);
    const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D35_INFECTION_TYPE_PARENT_TABLE[pi]);
    uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCX_CAMF_D35_INFECTION_TYPE_PARENT_Entry, offset));
    return azarac_pgm_join_z(QZSS_DCX_CAMF_D35_INFECTION_TYPE_POOL + off, QZSS_DCX_CAMF_D35_INFECTION_TYPE_PARENT_POOL + poff);
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
