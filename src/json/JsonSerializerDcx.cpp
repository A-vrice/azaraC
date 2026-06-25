// azaraC - src/internal/JsonSerializerDcx.cpp
// MT=44 DCX JSON serializer

#include "azaraC.h"
#include "internal/JsonWriter.h"
#include "internal/DcxHelper.h"
#include "definition/_index.h"
#include <optional>
#include <string_view>

namespace azaraC {
namespace internal {

// ---------------------------------------------------------------------------
// MT=44 DCX
// ---------------------------------------------------------------------------
void serializeDcx(const Message& m, Print& out) {
    using namespace azaraC::def;

    // Use safe accessor for Mt44Data
    const Mt44Data* d = m.getMt44();
    if (!d) {
        wf_s(out, "note", "invalid_mt44", /*last=*/true);
        return;
    }

    wf_u(out, "dcx_type", (uint32_t)static_cast<uint8_t>(d->service_kind));

    std::string_view dcx_label = std::string_view{"UNKNOWN", 7};
    switch (d->service_kind) {
        case Mt44ServiceKind::NullMessage:     dcx_label = std::string_view{"NULL", 4}; break;
        case Mt44ServiceKind::LAlert:          dcx_label = std::string_view{"L_ALERT", 7}; break;
        case Mt44ServiceKind::JAlert:          dcx_label = std::string_view{"J_ALERT", 7}; break;
        case Mt44ServiceKind::LocalGovernment: dcx_label = std::string_view{"LOCAL_GOV", 9}; break;
        case Mt44ServiceKind::OutsideJapan:    dcx_label = std::string_view{"OUTSIDE_JAPAN", 13}; break;
        default: break;
    }
    wf_s(out, "dcx_type_label", dcx_label);

    wf_s(out, "a1_msg_type",
        qzss_dcx_camf_a1_message_type_lookup(d->camf.a1));
    wf_u(out, "a2_country", d->camf.a2);
    wf_s(out, "a2_country_label",
        qzss_dcx_camf_a2_country_region_name_lookup(d->camf.a2));
    wf_u(out, "a3_provider", d->camf.a3);
    wf_s(out, "a3_provider_label",
        qzss_dcx_camf_a3_provider_identifier_lookup(d->camf.a2, d->camf.a3));
    wf_u(out, "a4_hazard", d->camf.a4);
    wf_s(out, "a4_hazard_category",
        qzss_dcx_camf_a4_hazard_category_lookup(d->camf.a4));
    wf_s(out, "a4_hazard_type",
        qzss_dcx_camf_a4_hazard_type_lookup(d->camf.a4));
    wf_u(out, "a5_severity", d->camf.a5);
    wf_s(out, "a5_severity_label",
        qzss_dcx_camf_a5_severity_lookup(d->camf.a5));
    wf_u(out, "a6_onset_week", d->camf.a6);
    wf_s(out, "a6_onset_week_label",
        qzss_dcx_camf_a6_hazard_onset_week_lookup(d->camf.a6));
    wf_u(out, "a7_onset_minute", d->camf.a7);
    wf_u(out, "a8_duration", d->camf.a8);
    wf_s(out, "a8_duration_label",
        qzss_dcx_camf_a8_hazard_duration_lookup(d->camf.a8));
    writeDHM(out, "onset_time", d->onset_time);

    // A9/A10 Library selection
    wf_u(out, "a9_selection_of_library", d->camf.a9);
    wf_s(out, "a9_selection_of_library_label",
        qzss_dcx_camf_a9_selection_of_library_lookup(d->camf.a9));
    wf_u(out, "a10_library_version", d->camf.a10);
    wf_s(out, "a10_library_version_label",
        qzss_dcx_camf_a10_library_version_lookup(d->camf.a10));

    // A11 Guidance to react library
    wf_u(out, "a11_guidance", d->camf.a11);
    wf_s(out, "a11_guidance_label",
        AZARAC_LOOKUP_LANG(qzss_dcx_camf_a11_japanese_library_ja_lookup, qzss_dcx_camf_a11_japanese_library_en_lookup, d->camf.a11));

    // A17/A18 Specific Settings
    wf_u(out, "a17_specific_subject", d->camf.a17);
    wf_s(out, "a17_specific_subject_label",
        qzss_dcx_camf_a17_main_subject_for_specific_settings_lookup(d->camf.a17));
    wf_u(out, "a18_specific_settings", d->camf.a18);

    // Decoded main ellipse (A12-A16)
    const Mt44Decoded& dec = d->mt44_decoded;
    if (dec.main_ellipse_present) {
        wk(out, "main_ellipse");
        out.print('{');
        wf_d(out, "lat_deg", dec.main_ellipse.lat_deg);
        wf_d(out, "lon_deg", dec.main_ellipse.lon_deg);
        wf_d(out, "semi_major_km", dec.main_ellipse.semi_major_km);
        wf_d(out, "semi_minor_km", dec.main_ellipse.semi_minor_km);
        wf_d(out, "azimuth_deg", dec.main_ellipse.azimuth_deg, /*last=*/!d->camf.b1_present);

        // B1 refinement (EWSS CAMF v1.1 §3.7.1)
        if (d->camf.b1_present) {
            wk(out, "b1_refinement");
            out.print('{');
            wf_d(out, "c1_lat_offset_deg", dec.main_ellipse.b1_lat_offset_deg);
            wf_d(out, "c2_lon_offset_deg", dec.main_ellipse.b1_lon_offset_deg);
            wf_d(out, "c3_major_factor", dec.main_ellipse.b1_major_factor);
            wf_d(out, "c4_minor_factor", dec.main_ellipse.b1_minor_factor, /*last=*/true);
            out.print('}');
        }

        out.print('}');
        writeChar(out, ',');
    }

    // B2 (A17=01) - Hazard center offset (EWSS CAMF v1.1 §3.7.2)
    if (d->camf.b2_present) {
        wk(out, "hazard_center");
        out.print('{');
        wf_u(out, "c5_raw", d->camf.b2_c5);
        wf_u(out, "c6_raw", d->camf.b2_c6);
        double base_lat = decodeLatitude16(d->camf.a12);
        double base_lon = decodeLongitude17(d->camf.a13);
        wf_d(out, "delta_lat_deg", dec.main_ellipse.lat_deg - base_lat);
        wf_d(out, "delta_lon_deg", dec.main_ellipse.lon_deg - base_lon, /*last=*/true);
        out.print('}');
        writeChar(out, ',');
    }

    // B3 (A17=10) - Secondary ellipse definition (EWSS CAMF v1.1 §3.7.3)
    if (d->camf.b3_present) {
        wk(out, "secondary_ellipse");
        out.print('{');
        wf_u(out, "c7_shift", d->camf.b3_c7);
        wf_u(out, "c8_homothetic", d->camf.b3_c8);
        wf_u(out, "c9_bearing", d->camf.b3_c9);
        wf_u(out, "c10_guidance", d->camf.b3_c10);
        wf_s(out, "c10_guidance_label",
            qzss_dcx_camf_c10_guidance_library_for_second_ellipse_lookup(d->camf.b3_c10), /*last=*/true);
        out.print('}');
        writeChar(out, ',');
    }

    // B4 (A17=11) - Detailed hazard information (EWSS CAMF v1.1 §3.7.4)
    if (d->camf.b4_present) {
        wk(out, "detailed_info");
        out.print('{');
        bool first_detail_field = true;
        auto beginDetailField = [&]() {
            if (!first_detail_field) writeChar(out, ',');
            first_detail_field = false;
        };

        // a4_code is always present
        beginDetailField();
        wk(out, "a4_code");
        writeUint32(out, d->camf.a4);

        // Helper lambda for lookups returning std::optional<std::string_view>
        auto writeDField = [&](const char* name, uint32_t value, bool present, auto lookup) {
            if (!present) return;
            beginDetailField();
            wk(out, name);
            out.print("{\"raw\":");
            writeUint32(out, value);
            out.print(",\"label\":");
            auto label = lookup(static_cast<uint8_t>(value));
            if (label) {
                writeStr(out, *label);
            } else {
                out.print("\"\"");
            }
            out.print('}');
        };

        // Helper lambda for lookups returning const char* (e.g. D3, D4)
        auto writeDFieldC = [&](const char* name, uint32_t value, bool present, const char* (*lookup)(uint8_t)) {
            if (!present) return;
            beginDetailField();
            wk(out, name);
            out.print("{\"raw\":");
            writeUint32(out, value);
            out.print(",\"label\":");
            const char* label = lookup(static_cast<uint8_t>(value));
            if (label) {
                writeStr(out, std::string_view{label});
            } else {
                out.print("\"\"");
            }
            out.print('}');
        };

        writeDField("d1_magnitude",       d->camf.b4_d1,  d->camf.b4_d1_present,  qzss_dcx_camf_d1_magnitude_on_richter_scale_lookup);
        writeDField("d2_seismic_coeff",    d->camf.b4_d2,  d->camf.b4_d2_present,  qzss_dcx_camf_d2_seismic_coefficient_lookup);
        writeDFieldC("d3_azimuth",        d->camf.b4_d3,  d->camf.b4_d3_present,  qzss_dcx_camf_d3_azimuth_from_centre_of_main_ellipse_to_epicentre_lookup);
        writeDFieldC("d4_vector_length",  d->camf.b4_d4,  d->camf.b4_d4_present,  qzss_dcx_camf_d4_vector_length_between_centre_of_main_ellipse_and_epicentre_lookup);
        writeDField("d5_wave_height",      d->camf.b4_d5,  d->camf.b4_d5_present,  qzss_dcx_camf_d5_wave_height_lookup);
        writeDField("d6_temp_range",      d->camf.b4_d6,  d->camf.b4_d6_present,  qzss_dcx_camf_d6_temperature_range_lookup);
        writeDField("d7_hurricane_cat",   d->camf.b4_d7,  d->camf.b4_d7_present,  qzss_dcx_camf_d7_hurricane_category_lookup);
        writeDField("d8_wind_speed",      d->camf.b4_d8,  d->camf.b4_d8_present,  qzss_dcx_camf_d8_wind_speed_lookup);
        writeDField("d9_rainfall",        d->camf.b4_d9,  d->camf.b4_d9_present,  qzss_dcx_camf_d9_rainfall_amounts_lookup);
        writeDField("d10_damage",         d->camf.b4_d10, d->camf.b4_d10_present, qzss_dcx_camf_d10_damage_category_lookup);
        writeDField("d11_tornado_prob",   d->camf.b4_d11, d->camf.b4_d11_present, qzss_dcx_camf_d11_tornado_probability_lookup);
        writeDField("d12_hail_scale",     d->camf.b4_d12, d->camf.b4_d12_present, qzss_dcx_camf_d12_hail_scale_lookup);
        writeDField("d13_visibility",     d->camf.b4_d13, d->camf.b4_d13_present, qzss_dcx_camf_d13_visibility_lookup);
        writeDField("d14_snow_depth",     d->camf.b4_d14, d->camf.b4_d14_present, qzss_dcx_camf_d14_snow_depth_lookup);
        writeDField("d15_flood_severity", d->camf.b4_d15, d->camf.b4_d15_present, qzss_dcx_camf_d15_flood_severity_lookup);
        writeDField("d16_lightning",      d->camf.b4_d16, d->camf.b4_d16_present, qzss_dcx_camf_d16_lightning_intensity_lookup);
        writeDField("d17_fog_level",      d->camf.b4_d17, d->camf.b4_d17_present, qzss_dcx_camf_d17_fog_level_lookup);
        writeDField("d18_drought",        d->camf.b4_d18, d->camf.b4_d18_present, qzss_dcx_camf_d18_drought_level_lookup);
        writeDField("d19_avalanche",      d->camf.b4_d19, d->camf.b4_d19_present, qzss_dcx_camf_d19_avalanche_warning_level_lookup);
        writeDField("d20_ash_fall",       d->camf.b4_d20, d->camf.b4_d20_present, qzss_dcx_camf_d20_ash_fall_amount_and_impact_lookup);
        writeDField("d21_geomagnetic",    d->camf.b4_d21, d->camf.b4_d21_present, qzss_dcx_camf_d21_geomagnetic_scale_lookup);
        writeDField("d22_terrorism",      d->camf.b4_d22, d->camf.b4_d22_present, qzss_dcx_camf_d22_terrorism_threat_level_lookup);
        writeDField("d23_fire_risk",      d->camf.b4_d23, d->camf.b4_d23_present, qzss_dcx_camf_d23_fire_risk_level_lookup);
        writeDField("d24_water_quality",   d->camf.b4_d24, d->camf.b4_d24_present, qzss_dcx_camf_d24_water_quality_lookup);
        writeDField("d25_uv_index",       d->camf.b4_d25, d->camf.b4_d25_present, qzss_dcx_camf_d25_uv_index_lookup);
        writeDField("d26_cases_per_100k", d->camf.b4_d26, d->camf.b4_d26_present, qzss_dcx_camf_d26_number_of_cases_per_100000_inhabitants_lookup);
        writeDField("d27_noise",          d->camf.b4_d27, d->camf.b4_d27_present, qzss_dcx_camf_d27_noise_range_lookup);
        writeDField("d28_air_quality",    d->camf.b4_d28, d->camf.b4_d28_present, qzss_dcx_camf_d28_air_quality_index_lookup);
        writeDField("d29_outage_duration",d->camf.b4_d29, d->camf.b4_d29_present, qzss_dcx_camf_d29_outage_estimated_duration_lookup);
        writeDField("d30_nuclear_scale",  d->camf.b4_d30, d->camf.b4_d30_present, qzss_dcx_camf_d30_nuclear_event_scale_lookup);
        writeDField("d31_chemical_type",   d->camf.b4_d31, d->camf.b4_d31_present, qzss_dcx_camf_d31_chemical_hazard_type_lookup);
        writeDField("d32_biohazard_level", d->camf.b4_d32, d->camf.b4_d32_present, qzss_dcx_camf_d32_biohazard_level_lookup);
        writeDField("d33_biohazard_type",  d->camf.b4_d33, d->camf.b4_d33_present, qzss_dcx_camf_d33_biohazard_type_lookup);
        writeDField("d34_explosive_type",  d->camf.b4_d34, d->camf.b4_d34_present, qzss_dcx_camf_d34_explosive_hazard_type_lookup);
        writeDField("d35_infection_type",  d->camf.b4_d35, d->camf.b4_d35_present, qzss_dcx_camf_d35_infection_type_lookup);
        writeDField("d36_typhoon_cat",    d->camf.b4_d36, d->camf.b4_d36_present, qzss_dcx_camf_d36_typhoon_category_lookup);

        out.print('}');
        writeChar(out, ',');
    }

    // Extended Message fields
    if (d->ex_kind == ExtendedKind::LAlertOrLocal) {
        wf_u(out, "ex1_target_area", d->ex_lalert_local.ex1);
        wf_s(out, "ex1_target_area_label",
            AZARAC_LOOKUP_LANG(qzss_dcx_ex1_target_area_code_ja_lookup, qzss_dcx_ex1_target_area_code_en_lookup, d->ex_lalert_local.ex1));

        // Decoded target area code (when main ellipse is absent)
        if (dec.target_area_code_present) {
            wf_u(out, "target_area_code", dec.target_area_code);
        }

        // EX2-EX7 Additional Ellipse (local government only)
        if (dec.additional_area.present) {
            wk(out, "additional_area");
            out.print('{');
            wf_u(out, "head_to_area", dec.additional_area.head_to_area);
            wk(out, "ellipse");
            out.print('{');
            wf_d(out, "lat_deg", dec.additional_area.ellipse.lat_deg);
            wf_d(out, "lon_deg", dec.additional_area.ellipse.lon_deg);
            wf_d(out, "semi_major_km", dec.additional_area.ellipse.semi_major_km);
            wf_d(out, "semi_minor_km", dec.additional_area.ellipse.semi_minor_km);
            wf_d(out, "azimuth_deg", dec.additional_area.ellipse.azimuth_deg, /*last=*/true);
            out.print('}');
            out.print('}');
            writeChar(out, ',');
        }
        wf_u(out, "ex_vn", d->ex_lalert_local.vn);
    } else if (d->ex_kind == ExtendedKind::JAlert) {
        wf_u(out, "ex8_area_type", d->ex_jalert.ex8);

        // Decoded J-Alert target area
        wk(out, "jalert_target");
        out.print('{');
        wf_u(out, "prefecture_mode", dec.jalert_prefecture_mode);
        if (dec.jalert_prefecture_mode) {
            // Prefecture positions
            wk(out, "prefecture_positions");
            out.print('[');
            for (uint8_t i = 0; i < dec.prefecture_count; ++i) {
                if (i) writeChar(out, ',');
                writeUint32(out, dec.prefecture_positions[i]);
            }
            out.print("],");
            // Prefecture labels
            wk(out, "prefecture_labels");
            out.print('[');
            for (uint8_t i = 0; i < dec.prefecture_count; ++i) {
                if (i) writeChar(out, ',');
                uint8_t pos = dec.prefecture_positions[i];
                std::optional<std::string_view> label = qzss_dcr_jma_prefecture_lookup(pos);
                writeOptStr(out, label);
            }
            out.print(']');
        } else {
            // City/town/village codes
            wk(out, "city_codes");
            out.print('[');
            for (uint8_t i = 0; i < dec.city_code_count; ++i) {
                if (i) writeChar(out, ',');
                writeUint32(out, dec.city_codes[i]);
            }
            out.print("],");
            // City labels
        }
        wf_u(out, "ex_vn", d->ex_jalert.vn);
    } else if (d->ex_kind == ExtendedKind::OutsideJapan) {
        // EX11 raw data (68 bits) - output as hex string
        wk(out, "ex11_raw");
        writeChar(out, '"');
        const char hex[] = "0123456789ABCDEF";
        for (int i = 0; i < 8; ++i) {
            uint8_t v = d->ex_outside.ex11_raw[i];
            writeChar(out, hex[v >> 4]);
            writeChar(out, hex[v & 0x0F]);
        }
        writeChar(out, hex[d->ex_outside.ex11_raw[8] >> 4]);
        writeChar(out, '"');
        writeChar(out, ',');
        wf_u(out, "ex_vn", d->ex_outside.vn);
    }

    // Alert identity
    wk(out, "alert_identity");
    out.print('{');
    wf_u(out, "a2", dec.alert_identity.a2);
    wf_u(out, "a3", dec.alert_identity.a3);
    wf_u(out, "a4", dec.alert_identity.a4);
    wf_u(out, "ex1", dec.alert_identity.ex1, /*last=*/true);
    out.print('}');
    writeChar(out, ',');

    wf_u(out, "sd_sdmt", d->sd.sdmt);
    wf_u(out, "sd_sdm", d->sd.sdm, /*last=*/true);
}

} // namespace internal
} // namespace azaraC
