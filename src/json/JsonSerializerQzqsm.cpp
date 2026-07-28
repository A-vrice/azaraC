// azaraC - src/internal/JsonSerializerQzqsm.cpp
// MT=43 QZQSM JSON serializer

#include "azaraC.h"
#include "JsonWriter.h"
#include "definition/_index.h"
#include <optional>
#include <string_view>

namespace azaraC {
namespace internal {

// ---------------------------------------------------------------------------
// MT=43 sub-type serializers
// Each returns after writing its last field with last=true
// ---------------------------------------------------------------------------

#if (AZARAC_ENABLE_EEW)
void serializeEEW(const Message& m, Print& out) {
    using namespace azaraC::def;
    const Mt43Data* d = m.getMt43();
    if (!d) return;
    
    const EewData* eew = d->getEew();
    if (!eew) return;
    
    wf_u(out, "long_period_lower", eew->long_period_lower);
    wf_s(out, "long_period_lower_label",
        qzss_dcr_jma_long_period_ground_motion_lower_limit_lookup(eew->long_period_lower));
    wf_u(out, "long_period_upper", eew->long_period_upper);
    wf_s(out, "long_period_upper_label",
        qzss_dcr_jma_long_period_ground_motion_upper_limit_lookup(eew->long_period_upper));
    wk(out, "notifications"); out.print('[');
    for (uint8_t i = 0; i < eew->notification_count; ++i) {
        if (i) writeChar(out, ',');
        uint16_t code = eew->notification[i];
        out.print('{');
        wf_u(out, keys::code, code);
        wf_s(out, keys::label, qzss_dcr_jma_notification_on_disaster_prevention_lookup(code), /*last=*/true);
        out.print('}');
    }
    out.print("],");
    writeDHM(out, "quake_time", eew->quake_time);
    wf_u(out, "depth", eew->depth);
    wf_u(out, "magnitude", eew->magnitude);
    wf_u(out, "epicenter", eew->epicenter);
    wf_s(out, "epicenter_label",
        qzss_dcr_jma_epicenter_and_hypocenter_lookup(eew->epicenter));
    wf_u(out, "intensity_lower", eew->intensity_lower);
    wf_s(out, "intensity_lower_label",
        qzss_dcr_jma_seismic_intensity_lower_limit_lookup(eew->intensity_lower));
    wf_u(out, "intensity_upper", eew->intensity_upper);
    wf_s(out, "intensity_upper_label",
        qzss_dcr_jma_seismic_intensity_upper_limit_lookup(eew->intensity_upper));
    // regions array
    wk(out, "regions"); out.print('[');
    for (uint8_t i = 0; i < eew->region_count; ++i) {
        if (i) writeChar(out, ',');
        uint16_t code = eew->regions[i];
        out.print('{');
        wf_u(out, keys::code, code);
        wf_s(out, keys::label,
            qzss_dcr_jma_eew_forecast_region_lookup(code), /*last=*/true);
        out.print('}');
    }
    out.print(']');
}
#endif // AZARAC_ENABLE_EEW

#if (AZARAC_ENABLE_HYPOCENTER)
void serializeHypocenter(const Message& m, Print& out) {
    using namespace azaraC::def;
    const Mt43Data* d = m.getMt43();
    if (!d) return;
    
    const HypocenterData* hypo = d->getHypocenter();
    if (!hypo) return;
    
    writeDHM(out, "quake_time", hypo->quake_time);
    wf_u(out, "depth",     hypo->depth);
    wf_u(out, "magnitude", hypo->magnitude);
    wf_u(out, "epicenter", hypo->epicenter);
    wf_s(out, "epicenter_label",
        qzss_dcr_jma_epicenter_and_hypocenter_lookup(hypo->epicenter));
    wk(out, "notifications"); out.print('[');
    for (uint8_t i = 0; i < hypo->notification_count; ++i) {
        if (i) writeChar(out, ',');
        uint16_t code = hypo->notification[i];
        out.print('{');
        wf_u(out, keys::code, code);
        wf_s(out, keys::label, qzss_dcr_jma_notification_on_disaster_prevention_lookup(code), /*last=*/true);
        out.print('}');
    }
    out.print("],");
    writeLatLon(out, "coords", hypo->coords, /*last=*/true);
}
#endif // AZARAC_ENABLE_HYPOCENTER

#if (AZARAC_ENABLE_SEISMIC)
void serializeSeismic(const Message& m, Print& out) {
    using namespace azaraC::def;
    const Mt43Data* d = m.getMt43();
    if (!d) return;
    
    const SeismicData* seis = d->getSeismic();
    if (!seis) return;
    
    writeDHM(out, "quake_time", seis->quake_time);
    wk(out, "entries"); out.print('[');
    for (uint8_t i = 0; i < seis->count; ++i) {
        if (i) writeChar(out, ',');
        out.print('{');
        wf_u(out, "intensity", seis->entries[i].intensity_code);
        wf_s(out, "intensity_label",
            qzss_dcr_jma_seismic_intensity_lookup(seis->entries[i].intensity_code));
        wf_u(out, "prefecture", seis->entries[i].prefecture_code);
        wf_s(out, "prefecture_label",
            qzss_dcr_jma_prefecture_lookup(seis->entries[i].prefecture_code), /*last=*/true);
        out.print('}');
    }
    out.print(']');
}
#endif // AZARAC_ENABLE_SEISMIC

#if (AZARAC_ENABLE_NANKAI)
void serializeNankai(const Message& m, Print& out) {
    using namespace azaraC::def;
    const Mt43Data* d = m.getMt43();
    if (!d) return;
    
    const NankaiData* nankai = d->getNankai();
    if (!nankai) return;
    
    wf_u(out, "info_code", nankai->info_code);
    wf_s(out, "info_code_label",
        qzss_dcr_jma_information_serial_code_lookup(nankai->info_code));
    
    // Output aggregated text if available (multi-page complete)
    if (nankai->is_aggregated && nankai->aggregated_len > 0) {
        wf_u(out, "truncated", nankai->truncated ? 1u : 0u);
        wf_u(out, "page", 1);
        wf_u(out, "total_page", 1);
        wk(out, "text_utf8");
        writeStr(out, std::string_view(nankai->aggregated_text_ptr, nankai->aggregated_len));
    } else {
        // Single page or incomplete - output page info and hex
        wf_u(out, "page", nankai->page);
        wf_u(out, "total_page", nankai->total_page);
        // text as hex bytes array
        wk(out, "text_hex"); out.print('[');
        for (uint8_t i = 0; i < 18; ++i) {
            if (i) writeChar(out, ',');
            writeHex(out, nankai->text[i]);
        }
        out.print(']');
    }
}
#endif // AZARAC_ENABLE_NANKAI

#if (AZARAC_ENABLE_TSUNAMI)
void serializeTsunami(const Message& m, Print& out) {
    using namespace azaraC::def;
    const Mt43Data* d = m.getMt43();
    if (!d) return;
    
    const TsunamiData* tsunami = d->getTsunami();
    if (!tsunami) return;
    
    wf_u(out, "warning_code", tsunami->warning_code);
    wf_s(out, "warning_code_label",
        qzss_dcr_jma_tsunami_warning_code_lookup(tsunami->warning_code));
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
        wf_s(out, "height_label",
            qzss_dcr_jma_tsunami_height_lookup(e.height_code));
        wf_u(out, keys::region,           e.region_code);
        wf_s(out, keys::region_label,
            qzss_dcr_jma_tsunami_forecast_region_lookup(e.region_code), /*last=*/true);
        out.print('}');
    }
    out.print(']');
}
#endif // AZARAC_ENABLE_TSUNAMI

#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)
void serializeNwPacTsu(const Message& m, Print& out) {
    using namespace azaraC::def;
    const Mt43Data* d = m.getMt43();
    if (!d) return;
    
    const NwPacTsunamiData* nw_pac = d->getNwPac();
    if (!nw_pac) return;
    
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
}
#endif // AZARAC_ENABLE_NW_PAC_TSUNAMI

#if (AZARAC_ENABLE_VOLCANO)
void serializeVolcano(const Message& m, Print& out) {
    using namespace azaraC::def;
    const Mt43Data* d = m.getMt43();
    if (!d) return;
    
    const VolcanoData* vol = d->getVolcano();
    if (!vol) return;
    
    wf_u(out, "ambiguity",     vol->ambiguity);
    writeDHM(out, "activity_time", vol->activity_time);
    wf_u(out, "warning_code",  vol->warning_code);
    wf_s(out, "warning_code_label",
        qzss_dcr_jma_volcanic_warning_code_lookup(vol->warning_code));
    wf_u(out, "volcano_name",  vol->volcano_name);
    wf_s(out, "volcano_name_label",
        qzss_dcr_jma_volcano_name_lookup(vol->volcano_name));
    wk(out, "local_govs"); out.print('[');
    for (uint8_t i = 0; i < vol->lg_count; ++i) {
        if (i) writeChar(out, ',');
        out.print('{');
        wf_u(out, keys::code, vol->local_govs[i]);
        wf_s(out, keys::label,
            qzss_dcr_jma_local_government_lookup(vol->local_govs[i]), /*last=*/true);
        out.print('}');
    }
    out.print(']');
}
#endif // AZARAC_ENABLE_VOLCANO

#if (AZARAC_ENABLE_ASH_FALL)
void serializeAshFall(const Message& m, Print& out) {
    using namespace azaraC::def;
    const Mt43Data* d = m.getMt43();
    if (!d) return;
    
    const AshFallData* ash = d->getAshFall();
    if (!ash) return;
    
    writeDHM(out, "activity_time", ash->activity_time);
    wf_u(out, "warning_type", ash->warning_type);
    wf_s(out, "warning_type_label",
        qzss_dcr_jma_ash_fall_warning_code_lookup(ash->warning_type));
    wf_u(out, "volcano_name", ash->volcano_name);
    wf_s(out, "volcano_name_label",
        qzss_dcr_jma_volcano_name_lookup(ash->volcano_name));
    wk(out, "entries"); out.print('[');
    for (uint8_t i = 0; i < ash->count; ++i) {
        if (i) writeChar(out, ',');
        out.print('{');
        wf_u(out, "arrival_hour", ash->entries_time[i]);
        wf_u(out, "warning_code", ash->entries_code[i]);
        wf_s(out, "warning_code_label",
            qzss_dcr_jma_ash_fall_warning_code_lookup(ash->entries_code[i]));
        wf_u(out, "local_gov", ash->entries_lg[i]);
        wf_s(out, "local_gov_label",
            qzss_dcr_jma_local_government_lookup(ash->entries_lg[i]), /*last=*/true);
        out.print('}');
    }
    out.print(']');
}
#endif // AZARAC_ENABLE_ASH_FALL

#if (AZARAC_ENABLE_WEATHER)
void serializeWeather(const Message& m, Print& out) {
    using namespace azaraC::def;
    const Mt43Data* d = m.getMt43();
    if (!d) return;
    
    const WeatherData* wx = d->getWeather();
    if (!wx) return;
    
    wf_u(out, "warning_state", wx->warning_state);
    wf_s(out, "warning_state_label",
        qzss_dcr_jma_weather_warning_state_lookup(wx->warning_state));
    wk(out, "entries"); out.print('[');
    for (uint8_t i = 0; i < wx->count; ++i) {
        if (i) writeChar(out, ',');
        const WeatherEntry& e = wx->entries[i];
        out.print('{');
        wf_u(out, "sub_category", e.sub_category);
        wf_s(out, "sub_category_label",
            qzss_dcr_jma_weather_related_disaster_sub_category_lookup(e.sub_category));
        wf_u(out, keys::region, e.region_code);
        wf_s(out, keys::region_label,
            qzss_dcr_jma_weather_forecast_region_lookup(e.region_code), /*last=*/true);
        out.print('}');
    }
    out.print(']');
}
#endif // AZARAC_ENABLE_WEATHER

#if (AZARAC_ENABLE_FLOOD)
void serializeFlood(const Message& m, Print& out) {
    using namespace azaraC::def;
    const Mt43Data* d = m.getMt43();
    if (!d) return;
    
    const FloodData* flood = d->getFlood();
    if (!flood) return;
    
    wk(out, "entries"); out.print('[');
    for (uint8_t i = 0; i < flood->count; ++i) {
        if (i) writeChar(out, ',');
        const FloodEntry& e = flood->entries[i];
        out.print('{');
        wf_u(out, "warning_level", e.warning_level);
        wf_s(out, "warning_level_label",
            qzss_dcr_jma_flood_warning_level_lookup(e.warning_level));
        wf_u(out, keys::region, e.region_code);
        wf_s(out, keys::region_label,
            qzss_dcr_jma_flood_forecast_region_lookup(e.region_code), /*last=*/true);
        out.print('}');
    }
    out.print(']');
}
#endif // AZARAC_ENABLE_FLOOD

#if (AZARAC_ENABLE_MARINE)
void serializeMarine(const Message& m, Print& out) {
    using namespace azaraC::def;
    const Mt43Data* d = m.getMt43();
    if (!d) return;
    
    const MarineData* marine = d->getMarine();
    if (!marine) return;
    
    wk(out, "entries"); out.print('[');
    for (uint8_t i = 0; i < marine->count; ++i) {
        if (i) writeChar(out, ',');
        const MarineEntry& e = marine->entries[i];
        out.print('{');
        wf_u(out, "warning_code", e.warning_code);
        wf_s(out, "warning_code_label",
            qzss_dcr_jma_marine_warning_code_lookup(e.warning_code));
        wf_u(out, keys::region, e.region_code);
        wf_s(out, keys::region_label,
            qzss_dcr_jma_marine_forecast_region_lookup(e.region_code), /*last=*/true);
        out.print('}');
    }
    out.print(']');
}
#endif // AZARAC_ENABLE_MARINE

#if (AZARAC_ENABLE_TYPHOON)
void serializeTyphoon(const Message& m, Print& out) {
    using namespace azaraC::def;
    const Mt43Data* d = m.getMt43();
    if (!d) return;
    
    const TyphoonData* typh = d->getTyphoon();
    if (!typh) return;
    
    writeDHM(out, "reference_time", typh->reference_time);
    wf_u(out, "ref_type", typh->ref_type);
    wf_s(out, "ref_type_label",
        qzss_dcr_jma_typhoon_reference_time_type_lookup(typh->ref_type));
    wf_u(out, "elapsed",   typh->elapsed);
    wf_u(out, "number",    typh->number);
    wf_u(out, "scale",     typh->scale);
    wf_s(out, "scale_label",
        qzss_dcr_jma_typhoon_scale_category_lookup(typh->scale));
    wf_u(out, "intensity", typh->intensity);
    wf_s(out, "intensity_label",
        qzss_dcr_jma_typhoon_intensity_category_lookup(typh->intensity));
    // Typhoon center coordinates (LatLon: 41-bit DMS format)
    writeLatLon(out, "coords", typh->coords);
    // Central pressure (11 bits, hPa)
    wf_u(out, "pressure", typh->pressure);
    // Maximum wind speed (7 bits, m/s)
    wf_u(out, "max_wind", typh->max_wind);
    // Maximum wind gust speed (7 bits, m/s)
    wf_u(out, "max_gust", typh->max_gust, /*last=*/true);
}
#endif // AZARAC_ENABLE_TYPHOON

} // namespace internal
} // namespace azaraC
