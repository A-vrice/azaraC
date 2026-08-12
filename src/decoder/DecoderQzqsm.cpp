// MT=43 QZQSM / DC Report decoder (IS-QZSS-DCR-016)

#include "Decoder.h"

namespace azaraC {
namespace internal {

// MT=43 QZQSM / DC Report (IS-QZSS-DCR-016)
// Outer frame layout (offsets 0-indexed from preamble):
//   [14..16]  report_classification (3b)
//   [17..20]  disaster_category     (4b)
//   [21..24]  report_time month     (4b)  — not stored, used only for DHM resolve
//   [25..29]  report_time day       (5b)
//   [30..34]  report_time hour      (5b)
//   [35..40]  report_time minute    (6b)
//   [41..42]  information_type      (2b)
//   [43..46]  reserved / sub-type start
//   [214..219] version (6b) — must be 1
// Sub-type layouts per IS-QZSS-DCR-016 §4.1.2.3.
// Single authoritative category table: X(code, enable_macro, sub_decoder) drives
// the support check, known-category classification, and dispatch in decodeQzqsm().
// Change categories here only.
#define AZARAC_DC_CATEGORIES(X) \
    X(1,  AZARAC_ENABLE_EEW,          decodeEEW)        \
    X(2,  AZARAC_ENABLE_HYPOCENTER,   decodeHypocenter) \
    X(3,  AZARAC_ENABLE_SEISMIC,      decodeSeismic)    \
    X(4,  AZARAC_ENABLE_NANKAI,       decodeNankai)     \
    X(5,  AZARAC_ENABLE_TSUNAMI,      decodeTsunami)    \
    X(6,  AZARAC_ENABLE_NW_PAC_TSUNAMI, decodeNwPacTsu) \
    X(8,  AZARAC_ENABLE_VOLCANO,      decodeVolcano)    \
    X(9,  AZARAC_ENABLE_ASH_FALL,     decodeAshFall)    \
    X(10, AZARAC_ENABLE_WEATHER,      decodeWeather)    \
    X(11, AZARAC_ENABLE_FLOOD,        decodeFlood)      \
    X(12, AZARAC_ENABLE_TYPHOON,      decodeTyphoon)    \
    X(14, AZARAC_ENABLE_MARINE,       decodeMarine)
bool Decoder::decodeQzqsm(const uint8_t* bits, Message& out, uint32_t report_unix) {
    uint8_t ver = getBits(bits, 214, 6);
    if (ver != 1) {
        out.unsupported_reason = UnsupportedReason::UnsupportedVersion;
        return false;
    }

    // Support check from AZARAC_DC_CATEGORIES; each guard is a constant (0/1),
    // so a disabled category reads category_supported = false.
    uint8_t dc_probe = getBits(bits, 17, 4);
    bool category_supported = false;
    bool decoded = false;
    switch (dc_probe) {
#define AZARAC_DC_SUPPORT_CASE(code, enable, decoder) \
        case code: category_supported = (enable) != 0; break;
        AZARAC_DC_CATEGORIES(AZARAC_DC_SUPPORT_CASE)
#undef AZARAC_DC_SUPPORT_CASE
        default: break;
    }
    if (!category_supported) {
        // Recognized-but-disabled or unknown; known codes share the table (guard-independent).
        bool known = false;
        switch (dc_probe) {
#define AZARAC_DC_KNOWN_CASE(code, enable, decoder) case code:
            AZARAC_DC_CATEGORIES(AZARAC_DC_KNOWN_CASE)
#undef AZARAC_DC_KNOWN_CASE
            known = true;
            break;
            default: break;
        }
        out.unsupported_reason = known
            ? UnsupportedReason::DisabledAtCompileTime
            : UnsupportedReason::UnknownCategory;
        return false;
    }

    out.initPayload<Mt43Data>();
    Mt43Data* d = out.getMt43();
    if (!d) return false;

    d->report_classification = getBits(bits, 14,  3);
    d->disaster_category     = dc_probe;
    d->information_type      = getBits(bits, 41,  2);

    // report_time: month(4b)+day(5b)+hour(5b)+min(6b) at bit 21
    uint8_t  rt_month  = getBits(bits, 21, 4);
    uint8_t  rt_day    = getBits(bits, 25, 5);
    uint8_t  rt_hour   = getBits(bits, 30, 5);
    uint8_t  rt_minute = getBits(bits, 35, 6);

    d->event_time = resolveTime(rt_month, rt_day, rt_hour, rt_minute, report_unix);
    uint32_t event_unix = d->event_time.unix_time;
    uint32_t sub_base = (event_unix > 0) ? event_unix : report_unix;

    // Dispatch via same table; guard is a constant → disabled categories are dead branches.
    switch (dc_probe) {
#define AZARAC_DC_DISPATCH_CASE(code, enable, decoder) \
        case code: \
            if (enable) { \
                decoder(bits, out, sub_base); \
                decoded = true; \
            } \
            break;
        AZARAC_DC_CATEGORIES(AZARAC_DC_DISPATCH_CASE)
#undef AZARAC_DC_DISPATCH_CASE
        default: break;
    }
    if (!decoded) {
        out.unsupported_reason = UnsupportedReason::DisabledAtCompileTime;
        return false;
    }

    out.valid = true;
    return true;
}
#undef AZARAC_DC_CATEGORIES

#if (AZARAC_ENABLE_EEW)
// EEW  (disaster_category == 1)
void Decoder::decodeEEW(const uint8_t* b, Message& out, uint32_t report_unix) {
    Mt43Data* d = out.getMt43();
    if (!d) return;
    
    EewData* eew = d->getEew();
    if (!eew) {
        d->initAs<EewData>();
        eew = d->getEew();
        if (!eew) return;
    }
    
    eew->long_period_lower = getBits(b, 47, 3);
    eew->long_period_upper = getBits(b, 50, 3);

    // notifications: 3 × 9 bits at [53..79]
    eew->notification_count = readNotifications(b, 53, eew->notification);

    eew->quake_time   = extractDHM(b, 80, report_unix);
    eew->depth        = getBits(b,  96, 9);
    eew->magnitude    = getBits(b, 105, 7);
    eew->epicenter    = getBits(b, 112, 10);
    eew->intensity_lower = getBits(b, 122, 4);
    eew->intensity_upper = getBits(b, 126, 4);

    // EEW forecast regions: 80-bit bitmask at [130..209], bit i set = region (i+1) alerted
    eew->region_count = 0;
    for (uint8_t i = 0; i < 80 && eew->region_count < 80; ++i) {
        if (getBits(b, 130 + i, 1)) {
            eew->regions[eew->region_count++] = i + 1;
        }
    }
}
#endif // AZARAC_ENABLE_EEW

#if (AZARAC_ENABLE_HYPOCENTER)
// Hypocenter  (disaster_category == 2)
void Decoder::decodeHypocenter(const uint8_t* b, Message& out, uint32_t report_unix) {
    Mt43Data* d = out.getMt43();
    if (!d) return;
    
    HypocenterData* hypo = d->getHypocenter();
    if (!hypo) {
        d->initAs<HypocenterData>();
        hypo = d->getHypocenter();
        if (!hypo) return;
    }
    
    hypo->notification_count = readNotifications(b, 53, hypo->notification);
    hypo->quake_time = extractDHM(b,  80, report_unix);
    hypo->depth      = getBits(b,  96, 9);
    hypo->magnitude  = getBits(b, 105, 7);
    hypo->epicenter  = getBits(b, 112, 10);
    hypo->coords     = extractLatLon(b, 122);  // 41 bits
}
#endif // AZARAC_ENABLE_HYPOCENTER

#if (AZARAC_ENABLE_SEISMIC)
// Seismic Intensity  (disaster_category == 3)
void Decoder::decodeSeismic(const uint8_t* b, Message& out, uint32_t report_unix) {
    Mt43Data* d = out.getMt43();
    if (!d) return;
    
    SeismicData* seis = d->getSeismic();
    if (!seis) {
        d->initAs<SeismicData>();
        seis = d->getSeismic();
        if (!seis) return;
    }
    
    seis->quake_time = extractDHM(b, 53, report_unix);  // day(5)+hour(5)+min(6) at [53]
    seis->count = 0;
    for (uint8_t i = 0; i < 16; ++i) {
        uint16_t off = 69 + i * 9;
        uint8_t es = getBits(b, off,     3);
        uint8_t pl = getBits(b, off + 3, 6);
        if (es == 0 && pl == 0) break;
        if (seis->count < 16) {
            seis->entries[seis->count].intensity_code  = es;
            seis->entries[seis->count].prefecture_code = pl;
            ++seis->count;
        }
    }
}
#endif // AZARAC_ENABLE_SEISMIC

#if (AZARAC_ENABLE_NANKAI)
// Nankai Trough  (disaster_category == 4)
void Decoder::decodeNankai(const uint8_t* b, Message& out, uint32_t report_unix) {
    (void)report_unix;
    Mt43Data* d = out.getMt43();
    if (!d) return;
    
    NankaiData* nankai = d->getNankai();
    if (!nankai) {
        d->initAs<NankaiData>();
        nankai = d->getNankai();
        if (!nankai) return;
    }
    
    nankai->info_code   = getBits(b, 53, 4);
    nankai->page        = getBits(b, 201, 6);
    nankai->total_page  = getBits(b, 207, 6);
    // 18 bytes of text: bits [57..200] = 18×8 = 144 bits
    for (uint8_t i = 0; i < 18; ++i)
        nankai->text[i] = getBits(b, 57 + i * 8, 8);
}
#endif // AZARAC_ENABLE_NANKAI

#if (AZARAC_ENABLE_TSUNAMI)
// Tsunami  (disaster_category == 5)
// arrival time sub-field: nextday(1)+hour(5)+minute(6) = 12 bits
void Decoder::decodeTsunami(const uint8_t* b, Message& out, uint32_t report_unix) {
    (void)report_unix; // Used indirectly via d->event_time.unix_time
    Mt43Data* d = out.getMt43();
    if (!d) return;
    
    TsunamiData* tsunami = d->getTsunami();
    if (!tsunami) {
        d->initAs<TsunamiData>();
        tsunami = d->getTsunami();
        if (!tsunami) return;
    }
    
    tsunami->warning_code = getBits(b, 80, 4);
    tsunami->count = 0;
    for (uint8_t i = 0; i < 5; ++i) {
        uint16_t off = 84 + i * 26;
        // IS-QZSS-DCR-016 Figure 4.1.2-5, Table 4.1.2-21:
        //   Ta(12): Expected Tsunami Arrival Time
        //   Th(4):  Tsunami Height
        //   Pl(10): Tsunami Forecast Region (100–1000)
        // Terminal decision by Pl only (Pl=0 means end)
        uint16_t region = getBits(b, off + 16, 10);
        if (region == 0) break;
        TsunamiEntry& e = tsunami->entries[tsunami->count++];
        e.arrival_time_raw = getBits(b, off,      12);
        e.height_code      = getBits(b, off + 12,  4);
        e.region_code      = region;
        e.arrival_time     = resolveArrivalTime(e.arrival_time_raw, d->event_time.unix_time);
    }
}
#endif // AZARAC_ENABLE_TSUNAMI

#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)
// NW Pacific Tsunami  (disaster_category == 6)
void Decoder::decodeNwPacTsu(const uint8_t* b, Message& out, uint32_t report_unix) {
    (void)report_unix; // Used indirectly via d->event_time.unix_time
    Mt43Data* d = out.getMt43();
    if (!d) return;
    
    NwPacTsunamiData* nw_pac = d->getNwPac();
    if (!nw_pac) {
        d->initAs<NwPacTsunamiData>();
        nw_pac = d->getNwPac();
        if (!nw_pac) return;
    }
    
    nw_pac->potential = getBits(b, 53, 3);
    nw_pac->count = 0;
    for (uint8_t i = 0; i < 5; ++i) {
        uint16_t off = 56 + i * 28;
        // IS-QZSS-DCR-016 Figure 4.1.2-6, Table 4.1.2-26:
        //   Ta(12): Expected Tsunami Arrival Time
        //   Th(9):  Tsunami Height (Table 4.1.2-27a)
        //   Pl(7):  Coastal Region (Table 4.1.2-28, 1–100)
        // Terminal decision by Pl only (Pl=0 means end)
        uint16_t region = getBits(b, off + 21, 7);
        if (region == 0) break;
        NwPacTsunamiEntry& e = nw_pac->entries[nw_pac->count++];
        e.arrival_time_raw = getBits(b, off,      12);
        e.height_code      = getBits(b, off + 12,  9);
        e.region_code      = region;
        e.arrival_time     = resolveArrivalTime(e.arrival_time_raw, d->event_time.unix_time);
    }
}
#endif // AZARAC_ENABLE_NW_PAC_TSUNAMI

#if (AZARAC_ENABLE_VOLCANO)
// Volcano  (disaster_category == 8)
void Decoder::decodeVolcano(const uint8_t* b, Message& out, uint32_t report_unix) {
    Mt43Data* d = out.getMt43();
    if (!d) return;
    
    VolcanoData* vol = d->getVolcano();
    if (!vol) {
        d->initAs<VolcanoData>();
        vol = d->getVolcano();
        if (!vol) return;
    }
    
    vol->ambiguity      = getBits(b, 50, 3);
    vol->activity_time  = extractDHM(b, 53, report_unix);
    vol->warning_code   = getBits(b, 69, 7);
    vol->volcano_name   = getBits(b, 76, 12);
    vol->lg_count = 0;
    for (uint8_t i = 0; i < 5; ++i) {
        uint32_t lg = getBits(b, 88 + i * 23, 23);
        if (lg == 0) break;
        vol->local_govs[vol->lg_count++] = lg;
    }
}
#endif // AZARAC_ENABLE_VOLCANO

#if (AZARAC_ENABLE_ASH_FALL)
// Ash Fall  (disaster_category == 9)
void Decoder::decodeAshFall(const uint8_t* b, Message& out, uint32_t report_unix) {
    Mt43Data* d = out.getMt43();
    if (!d) return;
    
    AshFallData* ash = d->getAshFall();
    if (!ash) {
        d->initAs<AshFallData>();
        ash = d->getAshFall();
        if (!ash) return;
    }
    
    ash->activity_time = extractDHM(b, 53, report_unix);
    ash->warning_type  = getBits(b, 69, 2);
    ash->volcano_name  = getBits(b, 71, 12);
    ash->count = 0;
    for (uint8_t i = 0; i < 4; ++i) {
        uint16_t off = 83 + i * 29;
        if (getBits(b, off, 29) == 0) break;
        ash->entries_time[ash->count] = getBits(b, off,      3);
        ash->entries_code[ash->count] = getBits(b, off +  3, 3);
        ash->entries_lg  [ash->count] = getBits(b, off +  6, 23);
        ++ash->count;
    }
}
#endif // AZARAC_ENABLE_ASH_FALL

#if (AZARAC_ENABLE_WEATHER)
// Weather  (disaster_category == 10)
void Decoder::decodeWeather(const uint8_t* b, Message& out, uint32_t report_unix) {
    (void)report_unix;
    Mt43Data* d = out.getMt43();
    if (!d) return;
    
    WeatherData* wx = d->getWeather();
    if (!wx) {
        d->initAs<WeatherData>();
        wx = d->getWeather();
        if (!wx) return;
    }
    
    wx->warning_state = getBits(b, 53, 3);
    wx->count = 0;
    for (uint8_t i = 0; i < 6; ++i) {
        uint16_t off = 56 + i * 24;
        if (getBits(b, off, 24) == 0) break;
        wx->entries[wx->count].sub_category = getBits(b, off,      5);
        wx->entries[wx->count].region_code  = getBits(b, off +  5, 19);
        ++wx->count;
    }
}
#endif // AZARAC_ENABLE_WEATHER

#if (AZARAC_ENABLE_FLOOD)
// Flood  (disaster_category == 11)
void Decoder::decodeFlood(const uint8_t* b, Message& out, uint32_t report_unix) {
    (void)report_unix;
    Mt43Data* d = out.getMt43();
    if (!d) return;
    
    FloodData* flood = d->getFlood();
    if (!flood) {
        d->initAs<FloodData>();
        flood = d->getFlood();
        if (!flood) return;
    }
    
    flood->count = 0;
    for (uint8_t i = 0; i < 3; ++i) {
        uint16_t off = 53 + i * 44;
        // 44-bit zero means no entry (Region1 Lv range 1-15, 0=unused);
        // getBits64 reads all 44 bits (getBits only returns uint32_t).
        if (getBits64(b, off, 44) == 0) break;
        flood->entries[flood->count].warning_level = getBits(b, off, 4);
        // 40-bit region code — read as two 20-bit halves
        uint64_t hi = getBits(b, off +  4, 20);
        uint64_t lo = getBits(b, off + 24, 20);
        flood->entries[flood->count].region_code = (hi << 20) | lo;
        ++flood->count;
    }
}
#endif // AZARAC_ENABLE_FLOOD

#if (AZARAC_ENABLE_MARINE)
// Marine  (disaster_category == 14)
void Decoder::decodeMarine(const uint8_t* b, Message& out, uint32_t report_unix) {
    (void)report_unix;
    Mt43Data* d = out.getMt43();
    if (!d) return;
    
    MarineData* marine = d->getMarine();
    if (!marine) {
        d->initAs<MarineData>();
        marine = d->getMarine();
        if (!marine) return;
    }
    
    marine->count = 0;
    for (uint8_t i = 0; i < 8; ++i) {
        uint16_t off = 53 + i * 19;
        uint8_t  dw  = getBits(b, off,      5);
        uint16_t pl  = getBits(b, off +  5, 14);
        if (dw == 0 && pl == 0) break;
        marine->entries[marine->count].warning_code = dw;
        marine->entries[marine->count].region_code  = pl;
        ++marine->count;
    }
}
#endif // AZARAC_ENABLE_MARINE

#if (AZARAC_ENABLE_TYPHOON)
// Typhoon  (disaster_category == 12)
// IS-QZSS-DCR-016 Table 4.1.2-47
// Bit layout (from preamble):
//   [53..68]  Bt  Reference Time (day(5)+hour(5)+min(6))
//   [69..71]  Dt  Type of Reference Time (3 bits)
//   [72..79]  Spare2 (8 bits)
//   [80..86]  Du  Elapsed Time (7 bits)
//   [87..93]  Tn  Typhoon Number (7 bits)
//   [94..97]  Sr  Scale Category (4 bits)
//   [98..101] Ic  Intensity Category (4 bits)
//   [102..142] LatLon (41 bits): lat_ns(1)+lat_deg(7)+lat_min(6)+lat_sec(6)+lon_ew(1)+lon_deg(8)+lon_min(6)+lon_sec(6)
//   [143..153] Pr  Central Pressure (11 bits, hPa)
//   [154..160] W1  Maximum wind speed (7 bits, m/s)
//   [161..167] W2  Maximum wind gust speed (7 bits, m/s)
//   [168..213] Spare3 (46 bits)
//   [214..219] Vn  Version Number (6 bits)
void Decoder::decodeTyphoon(const uint8_t* b, Message& out, uint32_t report_unix) {
    Mt43Data* d = out.getMt43();
    if (!d) return;
    
    TyphoonData* typh = d->getTyphoon();
    if (!typh) {
        d->initAs<TyphoonData>();
        typh = d->getTyphoon();
        if (!typh) return;
    }
    
    typh->reference_time = extractDHM(b, 53, report_unix);
    typh->ref_type  = getBits(b,  69, 3);
    // Skip Spare2 [72..79] (8 bits)
    typh->elapsed   = getBits(b,  80, 7);
    typh->number    = getBits(b,  87, 7);
    typh->scale     = getBits(b,  94, 4);
    typh->intensity = getBits(b,  98, 4);

    // LatLon: 41 bits at [102..142]
    typh->coords = extractLatLon(b, 102);

    // Central Pressure: 11 bits at [143..153]
    typh->pressure = getBits(b, 143, 11);

    // Maximum wind speed: 7 bits at [154..160]
    typh->max_wind = getBits(b, 154, 7);

    // Maximum wind gust speed: 7 bits at [161..167]
    typh->max_gust = getBits(b, 161, 7);
}
#endif // AZARAC_ENABLE_TYPHOON

} // namespace internal
} // namespace azaraC
