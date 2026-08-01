#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_d35_infection_type
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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D35_INFECTION_TYPE_POOL[] = "Anthrax\0Avian influenza in humans\0Botulism\0Brucellosis\0Campylobacteriosis\0Chikungunya virus disease\0Chlamydia infections\0Cholera\0COVID - 19\0Creutzfeldt - Jakob Disease - variant(vCJD)\0Cryptosporidiosis\0Dengue\0Diphtheria\0Echinococcosis\0Giardiasis\0Gonorrhoea\0Hepatitis A\0Hepatitis B\0Hepatitis C\0HIV infection and AIDS\0Infections with haemophilus influenza group B\0Influenza including Influenza A(H1N1)\0Invasive meningococcal disease\0Invasive pneumococcal disease\0Legionnaires' disease\0Leptospirosis\0Listeriosis\0Lyme neuroborreliosis\0Malaria\0Measles\0Meningococcal disease, invasive\0Mumps\0Pertussis\0Plague\0Pneumococcal invasive diseases\0Poliomyelitis\0Q fever\0Rabies\0Rubella\0Rubella, congenital\0Salmonellosis\0Severe Acute Respiratory Syndrome (SARS)\0Shiga toxin /verocytotoxin -producing Escherichia coli (STEC/VTEC)\0Shigellosis\0Smallpox\0Syphilis\0Syphilis, congenital\0Tetanus\0Tick-borne encephalitis\0Toxoplasmosis, congenital\0Trichinellosis\0Tuberculosis\0Tularaemia\0Typhoid and paratyphoid fevers\0Viral haemorrhagic fevers\0West Nile virus infection\0Yellow fever\0Yersinosis\0Zika virus disease\0Zika virus disease, congenital\0Nosocomial infections\0Antimicrobial resistance\0unidentified infection\0";
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
    if (n == 0) return std::nullopt;
    return azarac_pgm_view(QZSS_DCX_CAMF_D35_INFECTION_TYPE_POOL + off, n);
}
#else
inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_D35_INFECTION_TYPE_TABLE[] = {
    std::string_view{"Anthrax", 7},
    std::string_view{"Avian influenza in humans", 25},
    std::string_view{"Botulism", 8},
    std::string_view{"Brucellosis", 11},
    std::string_view{"Campylobacteriosis", 18},
    std::string_view{"Chikungunya virus disease", 25},
    std::string_view{"Chlamydia infections", 20},
    std::string_view{"Cholera", 7},
    std::string_view{"COVID - 19", 10},
    std::string_view{"Creutzfeldt - Jakob Disease - variant(vCJD)", 43},
    std::string_view{"Cryptosporidiosis", 17},
    std::string_view{"Dengue", 6},
    std::string_view{"Diphtheria", 10},
    std::string_view{"Echinococcosis", 14},
    std::string_view{"Giardiasis", 10},
    std::string_view{"Gonorrhoea", 10},
    std::string_view{"Hepatitis A", 11},
    std::string_view{"Hepatitis B", 11},
    std::string_view{"Hepatitis C", 11},
    std::string_view{"HIV infection and AIDS", 22},
    std::string_view{"Infections with haemophilus influenza group B", 45},
    std::string_view{"Influenza including Influenza A(H1N1)", 37},
    std::string_view{"Invasive meningococcal disease", 30},
    std::string_view{"Invasive pneumococcal disease", 29},
    std::string_view{"Legionnaires' disease", 21},
    std::string_view{"Leptospirosis", 13},
    std::string_view{"Listeriosis", 11},
    std::string_view{"Lyme neuroborreliosis", 21},
    std::string_view{"Malaria", 7},
    std::string_view{"Measles", 7},
    std::string_view{"Meningococcal disease, invasive", 31},
    std::string_view{"Mumps", 5},
    std::string_view{"Pertussis", 9},
    std::string_view{"Plague", 6},
    std::string_view{"Pneumococcal invasive diseases", 30},
    std::string_view{"Poliomyelitis", 13},
    std::string_view{"Q fever", 7},
    std::string_view{"Rabies", 6},
    std::string_view{"Rubella", 7},
    std::string_view{"Rubella, congenital", 19},
    std::string_view{"Salmonellosis", 13},
    std::string_view{"Severe Acute Respiratory Syndrome (SARS)", 40},
    std::string_view{"Shiga toxin /verocytotoxin -producing Escherichia coli (STEC/VTEC)", 66},
    std::string_view{"Shigellosis", 11},
    std::string_view{"Smallpox", 8},
    std::string_view{"Syphilis", 8},
    std::string_view{"Syphilis, congenital", 20},
    std::string_view{"Tetanus", 7},
    std::string_view{"Tick-borne encephalitis", 23},
    std::string_view{"Toxoplasmosis, congenital", 25},
    std::string_view{"Trichinellosis", 14},
    std::string_view{"Tuberculosis", 12},
    std::string_view{"Tularaemia", 10},
    std::string_view{"Typhoid and paratyphoid fevers", 30},
    std::string_view{"Viral haemorrhagic fevers", 25},
    std::string_view{"West Nile virus infection", 25},
    std::string_view{"Yellow fever", 12},
    std::string_view{"Yersinosis", 10},
    std::string_view{"Zika virus disease", 18},
    std::string_view{"Zika virus disease, congenital", 30},
    std::string_view{"Nosocomial infections", 21},
    std::string_view{"Antimicrobial resistance", 24},
    std::string_view{"unidentified infection", 22}
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d35_infection_type_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D35_INFECTION_TYPE_BASE || id >= QZSS_DCX_CAMF_D35_INFECTION_TYPE_BASE + QZSS_DCX_CAMF_D35_INFECTION_TYPE_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_D35_INFECTION_TYPE_TABLE[id - QZSS_DCX_CAMF_D35_INFECTION_TYPE_BASE];
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
