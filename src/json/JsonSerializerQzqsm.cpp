// MT=43 QZQSM JSON serializer

#include "azaraC.h"
#include "JsonWriter.h"
#include "definition/_index.h"
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

namespace azaraC {
namespace internal {

// MT=43 sub-type serializers
// Each returns after writing its last field with last=true

#if (AZARAC_ENABLE_EEW)
bool serializeEEW(const Mt43Data* d, Print& out) {
    using namespace azaraC::def;
    
    const EewData* eew = d->getEew();
    if (!eew) return false;
    
    wf_u(out, "long_period_lower", eew->long_period_lower);
    AZARAC_LABEL(out, "long_period_lower_label",
        qzss_dcr_jma_long_period_ground_motion_lower_limit_lookup,
        qzss_dcr_jma_long_period_ground_motion_lower_limit_en_lookup, eew->long_period_lower, false);
    wf_u(out, "long_period_upper", eew->long_period_upper);
    AZARAC_LABEL(out, "long_period_upper_label",
        qzss_dcr_jma_long_period_ground_motion_upper_limit_lookup,
        qzss_dcr_jma_long_period_ground_motion_upper_limit_en_lookup, eew->long_period_upper, false);
    wk(out, "notifications"); out.print('[');
    for (uint8_t i = 0; i < eew->notification_count; ++i) {
        if (i) writeChar(out, ',');
        uint16_t code = eew->notification[i];
        out.print('{');
        wf_u(out, keys::code, code);
        wf_s(out, keys::label, AZARAC_LOOKUP_LANG(qzss_dcr_jma_notification_on_disaster_prevention_lookup, qzss_dcr_jma_notification_on_disaster_prevention_en_lookup, code), /*last=*/true);
        out.print('}');
    }
    out.print("],");
    writeDHM(out, "quake_time", eew->quake_time);
    wf_u(out, "depth", eew->depth);
    AZARAC_LABEL(out, "depth_label",
        qzss_dcr_jma_depth_of_hypocenter_lookup,
        qzss_dcr_jma_depth_of_hypocenter_en_lookup, eew->depth, false);
    wf_u(out, "magnitude", eew->magnitude);
    AZARAC_LABEL(out, "magnitude_label",
        qzss_dcr_jma_eew_magnitude_lookup,
        qzss_dcr_jma_eew_magnitude_en_lookup, eew->magnitude, false);
    wf_u(out, "epicenter", eew->epicenter);
    AZARAC_LABEL(out, "epicenter_label",
        qzss_dcr_jma_epicenter_and_hypocenter_lookup,
        qzss_dcr_jma_epicenter_and_hypocenter_en_lookup, eew->epicenter, false);
    wf_u(out, "intensity_lower", eew->intensity_lower);
    AZARAC_LABEL(out, "intensity_lower_label",
        qzss_dcr_jma_seismic_intensity_lower_limit_lookup,
        qzss_dcr_jma_seismic_intensity_lower_limit_en_lookup, eew->intensity_lower, false);
    wf_u(out, "intensity_upper", eew->intensity_upper);
    AZARAC_LABEL(out, "intensity_upper_label",
        qzss_dcr_jma_seismic_intensity_upper_limit_lookup,
        qzss_dcr_jma_seismic_intensity_upper_limit_en_lookup, eew->intensity_upper, false);
    wk(out, "regions"); out.print('[');
    for (uint8_t i = 0; i < eew->region_count; ++i) {
        if (i) writeChar(out, ',');
        uint16_t code = eew->regions[i];
        out.print('{');
        wf_u(out, keys::code, code);
        wf_s(out, keys::label,
            AZARAC_LOOKUP_LANG(qzss_dcr_jma_eew_forecast_region_lookup, qzss_dcr_jma_eew_forecast_region_en_lookup, code), /*last=*/true);
        out.print('}');
    }
    out.print(']');
    return true;
}
#endif // AZARAC_ENABLE_EEW

#if (AZARAC_ENABLE_HYPOCENTER)
bool serializeHypocenter(const Mt43Data* d, Print& out) {
    using namespace azaraC::def;
    
    const HypocenterData* hypo = d->getHypocenter();
    if (!hypo) return false;
    
    writeDHM(out, "quake_time", hypo->quake_time);
    wf_u(out, "depth",     hypo->depth);
    AZARAC_LABEL(out, "depth_label",
        qzss_dcr_jma_depth_of_hypocenter_lookup,
        qzss_dcr_jma_depth_of_hypocenter_en_lookup, hypo->depth, false);
    wf_u(out, "magnitude", hypo->magnitude);
    AZARAC_LABEL(out, "magnitude_label",
        qzss_dcr_jma_hypocenter_magnitude_lookup,
        qzss_dcr_jma_hypocenter_magnitude_en_lookup, hypo->magnitude, false);
    wf_u(out, "epicenter", hypo->epicenter);
    AZARAC_LABEL(out, "epicenter_label",
        qzss_dcr_jma_epicenter_and_hypocenter_lookup,
        qzss_dcr_jma_epicenter_and_hypocenter_en_lookup, hypo->epicenter, false);
    wk(out, "notifications"); out.print('[');
    for (uint8_t i = 0; i < hypo->notification_count; ++i) {
        if (i) writeChar(out, ',');
        uint16_t code = hypo->notification[i];
        out.print('{');
        wf_u(out, keys::code, code);
        wf_s(out, keys::label, AZARAC_LOOKUP_LANG(qzss_dcr_jma_notification_on_disaster_prevention_lookup, qzss_dcr_jma_notification_on_disaster_prevention_en_lookup, code), /*last=*/true);
        out.print('}');
    }
    out.print("],");
    writeLatLon(out, "coords", hypo->coords, /*last=*/true);
    return true;
}
#endif // AZARAC_ENABLE_HYPOCENTER

#if (AZARAC_ENABLE_SEISMIC)
bool serializeSeismic(const Mt43Data* d, Print& out) {
    using namespace azaraC::def;
    
    const SeismicData* seis = d->getSeismic();
    if (!seis) return false;
    
    writeDHM(out, "quake_time", seis->quake_time);
    wk(out, "entries"); out.print('[');
    for (uint8_t i = 0; i < seis->count; ++i) {
        if (i) writeChar(out, ',');
        out.print('{');
        wf_u(out, "intensity", seis->entries[i].intensity_code);
        AZARAC_LABEL(out, "intensity_label",
            qzss_dcr_jma_seismic_intensity_lookup,
            qzss_dcr_jma_seismic_intensity_en_lookup, seis->entries[i].intensity_code, false);
        wf_u(out, "prefecture", seis->entries[i].prefecture_code);
        AZARAC_LABEL(out, "prefecture_label",
            qzss_dcr_jma_prefecture_lookup,
            qzss_dcr_jma_prefecture_en_lookup, seis->entries[i].prefecture_code, /*last=*/true);
        out.print('}');
    }
    out.print(']');
    return true;
}
#endif // AZARAC_ENABLE_SEISMIC

#if (AZARAC_ENABLE_NANKAI)
bool serializeNankai(const Mt43Data* d, Print& out) {
    using namespace azaraC::def;
    
    const NankaiData* nankai = d->getNankai();
    if (!nankai) return false;
    
    wf_u(out, "info_code", nankai->info_code);
    wf_s(out, "info_code_label",
        qzss_dcr_jma_information_serial_code_lookup(nankai->info_code));
    
    // Aggregated complete text if available, else per-page info + hex
    if (nankai->is_aggregated && nankai->aggregated_len > 0) {
        wf_u(out, "truncated", nankai->truncated ? 1u : 0u);
        wf_u(out, "page", nankai->page);
        wf_u(out, "total_page", nankai->total_page);
        wk(out, "text_utf8");
        writeStr(out, std::string_view(nankai->aggregated_text_ptr, nankai->aggregated_len));
    } else {
        wf_u(out, "page", nankai->page);
        wf_u(out, "total_page", nankai->total_page);
        wk(out, "text_hex"); out.print('[');
        for (uint8_t i = 0; i < 18; ++i) {
            if (i) writeChar(out, ',');
            writeHex(out, nankai->text[i]);
        }
        out.print(']');
    }
    return true;
}
#endif // AZARAC_ENABLE_NANKAI

#if (AZARAC_ENABLE_TSUNAMI)
bool serializeTsunami(const Mt43Data* d, Print& out) {
    using namespace azaraC::def;
    
    const TsunamiData* tsunami = d->getTsunami();
    if (!tsunami) return false;
    
    wf_u(out, "warning_code", tsunami->warning_code);
    AZARAC_LABEL(out, "warning_code_label",
        qzss_dcr_jma_tsunami_warning_code_lookup,
        qzss_dcr_jma_tsunami_warning_code_en_lookup, tsunami->warning_code, false);
    wk(out, "entries"); out.print('[');
    for (uint8_t i = 0; i < tsunami->count; ++i) {
        if (i) writeChar(out, ',');
        const TsunamiEntry& e = tsunami->entries[i];
        out.print('{');
        uint16_t raw = e.arrival_time_raw;
        writeArrivalTimeFields(out, raw);
        wf_u(out, "arrival_time_raw", raw);
        writeDHM(out, "arrival_time", e.arrival_time);
        wf_u(out, "height",           e.height_code);
        AZARAC_LABEL(out, "height_label",
            qzss_dcr_jma_tsunami_height_lookup,
            qzss_dcr_jma_tsunami_height_en_lookup, e.height_code, false);
        wf_u(out, keys::region,           e.region_code);
        wf_s(out, keys::region_label,
            AZARAC_LOOKUP_LANG(qzss_dcr_jma_tsunami_forecast_region_lookup, qzss_dcr_jma_tsunami_forecast_region_en_lookup, e.region_code), /*last=*/true);
        out.print('}');
    }
    out.print(']');
    return true;
}
#endif // AZARAC_ENABLE_TSUNAMI

#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)
bool serializeNwPacTsu(const Mt43Data* d, Print& out) {
    using namespace azaraC::def;
    
    const NwPacTsunamiData* nw_pac = d->getNwPac();
    if (!nw_pac) return false;
    
    wf_u(out, "potential", nw_pac->potential);
    wf_s(out, "potential_label",
        qzss_dcr_jma_tsunamigenic_potential_en_lookup(nw_pac->potential));
    wk(out, "entries"); out.print('[');
    for (uint8_t i = 0; i < nw_pac->count; ++i) {
        if (i) writeChar(out, ',');
        const NwPacTsunamiEntry& e = nw_pac->entries[i];
        out.print('{');
        uint16_t raw = e.arrival_time_raw;
        writeArrivalTimeFields(out, raw);
        wf_u(out, "arrival_time_raw", raw);
        writeDHM(out, "arrival_time", e.arrival_time);
        wf_u(out, "height",           e.height_code);
        wf_s(out, "height_label",
            qzss_dcr_jma_northwest_pacific_tsunami_height_en_lookup(e.height_code));
        wf_u(out, keys::region,           e.region_code);
        wf_s(out, keys::region_label,
            qzss_dcr_jma_coastal_region_en_lookup(e.region_code), /*last=*/true);
        out.print('}');
    }
    out.print(']');
    return true;
}
#endif // AZARAC_ENABLE_NW_PAC_TSUNAMI

#if (AZARAC_ENABLE_VOLCANO)
bool serializeVolcano(const Mt43Data* d, Print& out) {
    using namespace azaraC::def;
    
    const VolcanoData* vol = d->getVolcano();
    if (!vol) return false;
    
    wf_u(out, "ambiguity",     vol->ambiguity);
    // 日本語版を持たない英語専用表なので言語非依存（_label_en は出さない）
    wf_s(out, "ambiguity_label",
        qzss_dcr_jma_ambiguity_of_activity_time_en_lookup(vol->ambiguity));
    writeDHM(out, "activity_time", vol->activity_time);
    wf_u(out, "warning_code",  vol->warning_code);
    AZARAC_LABEL(out, "warning_code_label",
        qzss_dcr_jma_volcanic_warning_code_lookup,
        qzss_dcr_jma_volcanic_warning_code_en_lookup, vol->warning_code, false);
    wf_u(out, "volcano_name",  vol->volcano_name);
    AZARAC_LABEL(out, "volcano_name_label",
        qzss_dcr_jma_volcano_name_lookup,
        qzss_dcr_jma_volcano_name_en_lookup, vol->volcano_name, false);
    wk(out, "local_govs"); out.print('[');
    for (uint8_t i = 0; i < vol->lg_count; ++i) {
        if (i) writeChar(out, ',');
        out.print('{');
        wf_u(out, keys::code, vol->local_govs[i]);
        wf_s(out, keys::label,
            AZARAC_LOOKUP_LANG(qzss_dcr_jma_local_government_lookup, qzss_dcr_jma_local_government_en_lookup, vol->local_govs[i]), /*last=*/true);
        out.print('}');
    }
    out.print(']');
    return true;
}
#endif // AZARAC_ENABLE_VOLCANO

#if (AZARAC_ENABLE_ASH_FALL)
bool serializeAshFall(const Mt43Data* d, Print& out) {
    using namespace azaraC::def;
    
    const AshFallData* ash = d->getAshFall();
    if (!ash) return false;
    
    writeDHM(out, "activity_time", ash->activity_time);
    wf_u(out, "warning_type", ash->warning_type);
    AZARAC_LABEL(out, "warning_type_label",
        qzss_dcr_jma_ash_fall_warning_type_lookup,
        qzss_dcr_jma_ash_fall_warning_type_en_lookup, ash->warning_type, false);
    wf_u(out, "volcano_name", ash->volcano_name);
    AZARAC_LABEL(out, "volcano_name_label",
        qzss_dcr_jma_volcano_name_lookup,
        qzss_dcr_jma_volcano_name_en_lookup, ash->volcano_name, false);
    wk(out, "entries"); out.print('[');
    for (uint8_t i = 0; i < ash->count; ++i) {
        if (i) writeChar(out, ',');
        out.print('{');
        wf_u(out, "arrival_hour", ash->entries_time[i]);
        wf_u(out, "warning_code", ash->entries_code[i]);
        AZARAC_LABEL(out, "warning_code_label",
            qzss_dcr_jma_ash_fall_warning_code_lookup,
            qzss_dcr_jma_ash_fall_warning_code_en_lookup, ash->entries_code[i], false);
        wf_u(out, "local_gov", ash->entries_lg[i]);
        AZARAC_LABEL(out, "local_gov_label",
            qzss_dcr_jma_local_government_lookup,
            qzss_dcr_jma_local_government_en_lookup, ash->entries_lg[i], /*last=*/true);
        out.print('}');
    }
    out.print(']');
    return true;
}
#endif // AZARAC_ENABLE_ASH_FALL

#if (AZARAC_ENABLE_WEATHER)
bool serializeWeather(const Mt43Data* d, Print& out) {
    using namespace azaraC::def;
    
    const WeatherData* wx = d->getWeather();
    if (!wx) return false;
    
    wf_u(out, "warning_state", wx->warning_state);
    AZARAC_LABEL(out, "warning_state_label",
        qzss_dcr_jma_weather_warning_state_lookup,
        qzss_dcr_jma_weather_warning_state_en_lookup, wx->warning_state, false);
    wk(out, "entries"); out.print('[');
    for (uint8_t i = 0; i < wx->count; ++i) {
        if (i) writeChar(out, ',');
        const WeatherEntry& e = wx->entries[i];
        out.print('{');
        wf_u(out, "sub_category", e.sub_category);
        AZARAC_LABEL(out, "sub_category_label",
            qzss_dcr_jma_weather_related_disaster_sub_category_lookup,
            qzss_dcr_jma_weather_related_disaster_sub_category_en_lookup, e.sub_category, false);
        wf_u(out, keys::region, e.region_code);
        wf_s(out, keys::region_label,
            AZARAC_LOOKUP_LANG(qzss_dcr_jma_weather_forecast_region_lookup, qzss_dcr_jma_weather_forecast_region_en_lookup, e.region_code), /*last=*/true);
        out.print('}');
    }
    out.print(']');
    return true;
}
#endif // AZARAC_ENABLE_WEATHER

#if (AZARAC_ENABLE_FLOOD)
bool serializeFlood(const Mt43Data* d, Print& out) {
    using namespace azaraC::def;
    
    const FloodData* flood = d->getFlood();
    if (!flood) return false;
    
    wk(out, "entries"); out.print('[');
    for (uint8_t i = 0; i < flood->count; ++i) {
        if (i) writeChar(out, ',');
        const FloodEntry& e = flood->entries[i];
        out.print('{');
        wf_u(out, "warning_level", e.warning_level);
        AZARAC_LABEL(out, "warning_level_label",
            qzss_dcr_jma_flood_warning_level_lookup,
            qzss_dcr_jma_flood_warning_level_en_lookup, e.warning_level, false);
        wf_u64(out, keys::region, e.region_code);
        wf_s(out, keys::region_label,
            AZARAC_LOOKUP_LANG(qzss_dcr_jma_flood_forecast_region_lookup, qzss_dcr_jma_flood_forecast_region_en_lookup, e.region_code), /*last=*/true);
        out.print('}');
    }
    out.print(']');
    return true;
}
#endif // AZARAC_ENABLE_FLOOD

#if (AZARAC_ENABLE_MARINE)
bool serializeMarine(const Mt43Data* d, Print& out) {
    using namespace azaraC::def;
    
    const MarineData* marine = d->getMarine();
    if (!marine) return false;
    
    wk(out, "entries"); out.print('[');
    for (uint8_t i = 0; i < marine->count; ++i) {
        if (i) writeChar(out, ',');
        const MarineEntry& e = marine->entries[i];
        out.print('{');
        wf_u(out, "warning_code", e.warning_code);
        AZARAC_LABEL(out, "warning_code_label",
            qzss_dcr_jma_marine_warning_code_lookup,
            qzss_dcr_jma_marine_warning_code_en_lookup, e.warning_code, false);
        wf_u(out, keys::region, e.region_code);
        wf_s(out, keys::region_label,
            AZARAC_LOOKUP_LANG(qzss_dcr_jma_marine_forecast_region_lookup, qzss_dcr_jma_marine_forecast_region_en_lookup, e.region_code), /*last=*/true);
        out.print('}');
    }
    out.print(']');
    return true;
}
#endif // AZARAC_ENABLE_MARINE

#if (AZARAC_ENABLE_TYPHOON)
bool serializeTyphoon(const Mt43Data* d, Print& out) {
    using namespace azaraC::def;
    
    const TyphoonData* typh = d->getTyphoon();
    if (!typh) return false;
    
    writeDHM(out, "reference_time", typh->reference_time);
    wf_u(out, "ref_type", typh->ref_type);
    AZARAC_LABEL(out, "ref_type_label",
        qzss_dcr_jma_typhoon_reference_time_type_lookup,
        qzss_dcr_jma_typhoon_reference_time_type_en_lookup, typh->ref_type, false);
    wf_u(out, "elapsed",   typh->elapsed);
    AZARAC_LABEL(out, "elapsed_label",
        qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_lookup,
        qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_en_lookup, typh->elapsed, false);
    wf_u(out, "number",    typh->number);
    AZARAC_LABEL(out, "number_label",
        qzss_dcr_jma_typhoon_number_lookup,
        qzss_dcr_jma_typhoon_number_en_lookup, typh->number, false);
    wf_u(out, "scale",     typh->scale);
    AZARAC_LABEL(out, "scale_label",
        qzss_dcr_jma_typhoon_scale_category_lookup,
        qzss_dcr_jma_typhoon_scale_category_en_lookup, typh->scale, false);
    wf_u(out, "intensity", typh->intensity);
    AZARAC_LABEL(out, "intensity_label",
        qzss_dcr_jma_typhoon_intensity_category_lookup,
        qzss_dcr_jma_typhoon_intensity_category_en_lookup, typh->intensity, false);
    // Typhoon center coordinates (LatLon: 41-bit DMS format)
    writeLatLon(out, "coords", typh->coords);
    // Central pressure (11 bits, hPa)
    wf_u(out, "pressure", typh->pressure);
    AZARAC_LABEL(out, "pressure_label",
        qzss_dcr_jma_typhoon_central_pressure_lookup,
        qzss_dcr_jma_typhoon_central_pressure_en_lookup, typh->pressure, false);
    // Maximum wind speed (7 bits, m/s)
    wf_u(out, "max_wind", typh->max_wind);
    AZARAC_LABEL(out, "max_wind_label",
        qzss_dcr_jma_typhoon_maximum_wind_speed_lookup,
        qzss_dcr_jma_typhoon_maximum_wind_speed_en_lookup, typh->max_wind, false);
    // Maximum wind gust speed (7 bits, m/s)
    wf_u(out, "max_gust", typh->max_gust);
    AZARAC_LABEL(out, "max_gust_label",
        qzss_dcr_jma_typhoon_maximum_gust_wind_speed_lookup,
        qzss_dcr_jma_typhoon_maximum_gust_wind_speed_en_lookup, typh->max_gust, /*last=*/true);
    return true;
}
#endif // AZARAC_ENABLE_TYPHOON

} // namespace internal
} // namespace azaraC
