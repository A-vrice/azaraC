#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d35_infection_type
// Entries       : 63
// Strategy      : array

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

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
inline constexpr uint8_t QZSS_DCX_CAMF_D35_INFECTION_TYPE_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D35_INFECTION_TYPE_SIZE = 63;
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d35_infection_type_lookup(uint8_t id) {
    if (id < QZSS_DCX_CAMF_D35_INFECTION_TYPE_BASE || id >= QZSS_DCX_CAMF_D35_INFECTION_TYPE_BASE + QZSS_DCX_CAMF_D35_INFECTION_TYPE_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_D35_INFECTION_TYPE_TABLE[id - QZSS_DCX_CAMF_D35_INFECTION_TYPE_BASE];
}

} // namespace def
} // namespace azaraC
