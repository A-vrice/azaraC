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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D35_INFECTION_TYPE_POOL[] = "Anthrax\000Avian influenza in human\000Botulism\000Bruc\000Campylobacter\000Chikungunya virus\000Chlamydia infection\000Choler\000COVID - 19\000Creutzfeldt - Jakob Disease - variant(vCJD\000Cryptosporid\000Dengu\000Diphtheri\000Echinococc\000Giardia\000Gonorrhoe\000Hepatitis A\000Hepatitis B\000Hepatitis C\000HIV infection and AIDS\000Infections with haemophilus influenza group B\000Influenza including Influenza A(H1N1\000Invasive meningococcal\000Invasive pneumococcal\000Legionnaires'\000Leptospir\000Lister\000Lyme neuroborrel\000Malari\000Measle\000Meningococcal disease, invasiv\000Mump\000Pertus\000Plagu\000Pneumococcal invasive disease\000Poliomyelit\000Q fever\000Rabie\000Rubell\000Rubella\000Salmon\000Severe Acute Respiratory Syndrome (SARS\000Shiga toxin /verocytotoxin -producing Escherichia coli (STEC/VTEC\000Shig\000Smallpox\000Syphil\000Syphilis\000Tetanu\000Tick-borne encephalit\000Toxoplasmosis\000Trichin\000Tubercu\000Tularaemi\000Typhoid and paratyphoid fever\000Viral haemorrhagic fever\000West Nile virus infection\000Yellow fever\000Yersin\000Zika virus\000Zika virus disease\000Nosocomial infection\000Antimicrobial resistanc\000unidentified infection\000";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D35_INFECTION_TYPE_PARENT_POOL[] = " disease\000)\000, congenital\000a\000e\000ellosis\000iosis\000is\000losis\000osis\000s\000sis\000";
struct QZSS_DCX_CAMF_D35_INFECTION_TYPE_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCX_CAMF_D35_INFECTION_TYPE_PARENT_Entry QZSS_DCX_CAMF_D35_INFECTION_TYPE_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 8u},
    {9u, 1u},
    {11u, 12u},
    {24u, 1u},
    {26u, 1u},
    {28u, 7u},
    {36u, 5u},
    {42u, 2u},
    {45u, 5u},
    {51u, 4u},
    {56u, 1u},
    {58u, 3u},
};
struct QZSS_DCX_CAMF_D35_INFECTION_TYPE_Entry { uint16_t offset; uint8_t len; uint8_t parent; };
static const QZSS_DCX_CAMF_D35_INFECTION_TYPE_Entry QZSS_DCX_CAMF_D35_INFECTION_TYPE_TABLE[] AZARAC_PROGMEM = {
    {0u, 7u, 255u},
    {8u, 24u, 10u},
    {33u, 8u, 255u},
    {42u, 4u, 5u},
    {47u, 13u, 6u},
    {61u, 17u, 0u},
    {79u, 19u, 10u},
    {99u, 6u, 3u},
    {106u, 10u, 255u},
    {117u, 42u, 1u},
    {160u, 12u, 6u},
    {173u, 5u, 4u},
    {179u, 9u, 3u},
    {189u, 10u, 9u},
    {200u, 7u, 11u},
    {208u, 9u, 3u},
    {218u, 11u, 255u},
    {230u, 11u, 255u},
    {242u, 11u, 255u},
    {254u, 22u, 255u},
    {277u, 45u, 255u},
    {323u, 36u, 1u},
    {360u, 22u, 0u},
    {383u, 21u, 0u},
    {405u, 13u, 0u},
    {419u, 9u, 9u},
    {429u, 6u, 6u},
    {436u, 16u, 6u},
    {453u, 6u, 3u},
    {460u, 6u, 10u},
    {467u, 30u, 4u},
    {498u, 4u, 10u},
    {503u, 6u, 11u},
    {510u, 5u, 4u},
    {516u, 29u, 10u},
    {546u, 11u, 7u},
    {558u, 7u, 255u},
    {566u, 5u, 10u},
    {572u, 6u, 3u},
    {579u, 7u, 2u},
    {587u, 6u, 5u},
    {594u, 39u, 1u},
    {634u, 65u, 1u},
    {700u, 4u, 5u},
    {705u, 8u, 255u},
    {714u, 6u, 7u},
    {721u, 8u, 2u},
    {730u, 6u, 10u},
    {737u, 21u, 7u},
    {759u, 13u, 2u},
    {773u, 7u, 5u},
    {781u, 7u, 8u},
    {789u, 9u, 3u},
    {799u, 29u, 10u},
    {829u, 24u, 10u},
    {854u, 25u, 255u},
    {880u, 12u, 255u},
    {893u, 6u, 9u},
    {900u, 10u, 0u},
    {911u, 18u, 2u},
    {930u, 20u, 10u},
    {951u, 23u, 4u},
    {975u, 22u, 255u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d35_infection_type_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D35_INFECTION_TYPE_BASE || id >= QZSS_DCX_CAMF_D35_INFECTION_TYPE_BASE + QZSS_DCX_CAMF_D35_INFECTION_TYPE_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D35_INFECTION_TYPE_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D35_INFECTION_TYPE_Entry, offset));
    uint8_t n = pgm_read_byte(p + offsetof(QZSS_DCX_CAMF_D35_INFECTION_TYPE_Entry, len));
    uint8_t pi = pgm_read_byte(p + offsetof(QZSS_DCX_CAMF_D35_INFECTION_TYPE_Entry, parent));
    if (pi == 255u) return azarac_pgm_view(QZSS_DCX_CAMF_D35_INFECTION_TYPE_POOL + off, n);
    const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D35_INFECTION_TYPE_PARENT_TABLE[pi]);
    uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCX_CAMF_D35_INFECTION_TYPE_PARENT_Entry, offset));
    uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCX_CAMF_D35_INFECTION_TYPE_PARENT_Entry, len));
    return azarac_pgm_join(QZSS_DCX_CAMF_D35_INFECTION_TYPE_POOL + off, n, QZSS_DCX_CAMF_D35_INFECTION_TYPE_PARENT_POOL + poff, pn);
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
