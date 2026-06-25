#pragma once
// azaraC - src/Message.h
// Bit offsets derived from azarashi (IS-QZSS-DCR-016 / IS-QZSS-DCX-003)
//
// Safe tagged union using explicit memory management (placement new).
// No std::variant dependency for Arduino compatibility.

#include <cstdint>
#include <cstring>
#include <new>
#include <utility>

namespace azaraC {

// ---- shared sub-structs ------------------------------------------------

struct TimeFields {
    uint8_t  month;   // 1-12 (0 = unresolved)
    uint8_t  day;     // 1-31 (0 = unresolved)
    uint8_t  hour;    // 0-23
    uint8_t  minute;  // 0-59
    uint32_t unix_time; // 0 = not resolved
};

struct LatLon {
    uint8_t  lat_ns;   // 0=N 1=S
    uint8_t  lat_deg;  // 0-89
    uint8_t  lat_min;  // 0-59
    uint8_t  lat_sec;  // 0-59
    uint8_t  lon_ew;   // 0=E 1=W
    uint16_t lon_deg;  // 0-179
    uint8_t  lon_min;  // 0-59
    uint8_t  lon_sec;  // 0-59
};

// ---- MT=44 DCX type ----------------------------------------------------

enum class Mt44ServiceKind : uint8_t {
    NullMessage,
    LAlert,
    JAlert,
    LocalGovernment,
    OutsideJapan,
    Unknown
};

enum class ExtendedKind : uint8_t {
    None,
    LAlertOrLocal,
    JAlert,
    OutsideJapan
};

struct Mt44Sd {
    uint8_t  sdmt;   // 1 bit
    uint16_t sdm;    // 9 bits
};

struct Mt44CamfRaw {
    uint8_t  a1;    // 2
    uint16_t a2;    // 9
    uint8_t  a3;    // 5
    uint8_t  a4;    // 7
    uint8_t  a5;    // 2
    uint8_t  a6;    // 1
    uint16_t a7;    // 14
    uint8_t  a8;    // 2
    uint8_t  a9;    // 1
    uint8_t  a10;   // 3
    uint16_t a11;   // 10
    uint16_t a12;   // 16 (unsigned, latitude code)
    uint32_t a13;   // 17 (unsigned, longitude code)
    uint8_t  a14;   // 5
    uint8_t  a15;   // 5
    uint8_t  a16;   // 6
    uint8_t  a17;   // 2
    uint16_t a18;   // 15

    // B1 (A17=00) - Improved Resolution of Main Ellipse (EWSS CAMF v1.1 §3.7.1)
    bool     b1_present;
    uint8_t  b1_c1;
    uint8_t  b1_c2;
    uint8_t  b1_c3;
    uint8_t  b1_c4;

    // B2 (A17=01) - Position of the Centre of the Hazard (EWSS CAMF v1.1 §3.7.2)
    bool     b2_present;
    uint8_t  b2_c5;
    uint8_t  b2_c6;

    // B3 (A17=10) - Secondary Ellipse Definition (EWSS CAMF v1.1 §3.7.3)
    bool     b3_present;
    uint8_t  b3_c7;
    uint8_t  b3_c8;
    uint8_t  b3_c9;
    uint8_t  b3_c10;
    double   b3_shift_km;
    double   b3_homothetic_factor;
    double   b3_bearing_deg;

    // B4 (A17=11) - Quantitative and Detailed Information (EWSS CAMF v1.1 §3.7.4)
    bool     b4_present;
    bool     b4_d1_present;
    bool     b4_d2_present;
    bool     b4_d3_present;
    bool     b4_d4_present;
    bool     b4_d5_present;
    bool     b4_d6_present;
    bool     b4_d7_present;
    bool     b4_d8_present;
    bool     b4_d9_present;
    bool     b4_d10_present;
    bool     b4_d11_present;
    bool     b4_d12_present;
    bool     b4_d13_present;
    bool     b4_d14_present;
    bool     b4_d15_present;
    bool     b4_d16_present;
    bool     b4_d17_present;
    bool     b4_d18_present;
    bool     b4_d19_present;
    bool     b4_d20_present;
    bool     b4_d21_present;
    bool     b4_d22_present;
    bool     b4_d23_present;
    bool     b4_d24_present;
    bool     b4_d25_present;
    bool     b4_d26_present;
    bool     b4_d27_present;
    bool     b4_d28_present;
    bool     b4_d29_present;
    bool     b4_d30_present;
    bool     b4_d31_present;
    bool     b4_d32_present;
    bool     b4_d33_present;
    bool     b4_d34_present;
    bool     b4_d35_present;
    bool     b4_d36_present;
    uint8_t  b4_d1;
    uint8_t  b4_d2;
    uint8_t  b4_d3;
    uint8_t  b4_d4;
    uint8_t  b4_d5;
    uint8_t  b4_d6;
    uint8_t  b4_d7;
    uint8_t  b4_d8;
    uint8_t  b4_d9;
    uint8_t  b4_d10;
    uint8_t  b4_d11;
    uint8_t  b4_d12;
    uint8_t  b4_d13;
    uint8_t  b4_d14;
    uint8_t  b4_d15;
    uint8_t  b4_d16;
    uint8_t  b4_d17;
    uint8_t  b4_d18;
    uint8_t  b4_d19;
    uint8_t  b4_d20;
    uint8_t  b4_d21;
    uint8_t  b4_d22;
    uint8_t  b4_d23;
    uint8_t  b4_d24;
    uint8_t  b4_d25;
    uint8_t  b4_d26;
    uint8_t  b4_d27;
    uint8_t  b4_d28;
    uint8_t  b4_d29;
    uint8_t  b4_d30;
    uint8_t  b4_d31;
    uint8_t  b4_d32;
    uint8_t  b4_d33;
    uint8_t  b4_d34;
    uint8_t  b4_d35;
    uint8_t  b4_d36;
};

struct Mt44ExLAlertOrLocal {
    uint16_t ex1;
    uint8_t  ex2;
    uint32_t ex3;
    uint32_t ex4;
    uint8_t  ex5;
    uint8_t  ex6;
    uint8_t  ex7;
    uint8_t  vn;
};

struct Mt44ExJAlert {
    uint8_t  ex8;
    uint64_t ex9;
    uint8_t  ex10;
    uint8_t  vn;
};

struct Mt44ExOutside {
    uint8_t ex11_raw[9];
    uint8_t vn;
};

// ---- MT=44 Decoded structures (IS-QZSS-DCX-003) --------------------------

struct DecodedEllipse {
    double lat_deg;
    double lon_deg;
    double semi_major_km;
    double semi_minor_km;
    double azimuth_deg;
    double b1_lat_offset_deg;
    double b1_lon_offset_deg;
    double b1_major_factor;
    double b1_minor_factor;
};

struct DecodedAdditionalArea {
    bool present;
    bool head_to_area;
    DecodedEllipse ellipse;
};

struct Mt44AlertIdentity {
    uint16_t a2;
    uint8_t  a3;
    uint8_t  a4;
    uint16_t ex1;

    bool operator==(const Mt44AlertIdentity& o) const {
        return a2 == o.a2 && a3 == o.a3 && a4 == o.a4 && ex1 == o.ex1;
    }
};

struct Mt44Decoded {
    Mt44ServiceKind service_kind;
    bool is_null_message;
    bool main_ellipse_present;
    DecodedEllipse main_ellipse;
    bool target_area_code_present;
    uint16_t target_area_code;
    bool jalert_prefecture_mode;
    uint8_t prefecture_positions[47];
    uint8_t prefecture_count;
    uint16_t city_codes[4];
    uint8_t city_code_count;
    DecodedAdditionalArea additional_area;
    Mt44AlertIdentity alert_identity;
};

// ---- MT=43 JMA disaster_category mapping (IS-QZSS-DCR-016 Table 5.1.2-1) -

// ---- repeating record structs (up to 8 each) ---------------------------

struct TsunamiEntry {
    uint16_t   arrival_time_raw;
    TimeFields arrival_time;
    uint8_t    height_code;
    uint16_t   region_code;
};

struct SeismicEntry {
    uint8_t intensity_code;
    uint8_t prefecture_code;
};

struct WeatherEntry {
    uint8_t  sub_category;
    uint32_t region_code;
};

struct FloodEntry {
    uint8_t  warning_level;
    uint64_t region_code;
};

struct MarineEntry {
    uint8_t  warning_code;
    uint16_t region_code;
};

struct NwPacTsunamiEntry {
    uint16_t   arrival_time_raw;
    TimeFields arrival_time;
    uint16_t   height_code;
    uint8_t    region_code;
};

// ---- MT=43 Data (QZQSM / DC Report) ------------------------------------

struct EewData {
    uint8_t  long_period_lower;
    uint8_t  long_period_upper;
    uint16_t notification[3];
    uint8_t  notification_count;
    TimeFields quake_time;
    uint16_t depth;
    uint8_t  magnitude;
    uint16_t epicenter;
    uint8_t  intensity_lower;
    uint8_t  intensity_upper;
    uint8_t  regions[80];
    uint8_t  region_count;
};

struct HypocenterData {
    uint16_t   notification[3];
    uint8_t    notification_count;
    TimeFields quake_time;
    uint16_t   depth;
    uint8_t    magnitude;
    uint16_t   epicenter;
    LatLon     coords;
};

struct SeismicData {
    TimeFields   quake_time;
    SeismicEntry entries[16];
    uint8_t      count;
};

struct NankaiData {
    uint8_t info_code;
    uint8_t text[18];
    uint8_t page;
    uint8_t total_page;
    char aggregated_text[1135];
    uint16_t aggregated_len;
    bool is_aggregated;
};

struct TsunamiData {
    uint8_t      warning_code;
    TsunamiEntry entries[5];
    uint8_t      count;
};

struct NwPacTsunamiData {
    uint8_t            potential;
    NwPacTsunamiEntry entries[5];
    uint8_t            count;
};

struct VolcanoData {
    uint8_t    ambiguity;
    TimeFields activity_time;
    uint8_t    warning_code;
    uint16_t   volcano_name;
    uint32_t   local_govs[5];
    uint8_t    lg_count;
};

struct AshFallData {
    TimeFields activity_time;
    uint8_t    warning_type;
    uint16_t   volcano_name;
    uint8_t    entries_time[4];
    uint8_t    entries_code[4];
    uint32_t   entries_lg[4];
    uint8_t    count;
};

struct WeatherData {
    uint8_t      warning_state;
    WeatherEntry entries[6];
    uint8_t      count;
};

struct FloodData {
    FloodEntry entries[3];
    uint8_t    count;
};

struct TyphoonData {
    TimeFields reference_time;
    uint8_t    ref_type;
    uint8_t    elapsed;
    uint8_t    number;
    uint8_t    scale;
    uint8_t    intensity;
    LatLon     coords;
    uint16_t   pressure;
    uint8_t    max_wind;
    uint8_t    max_gust;
};

struct MarineData {
    MarineEntry entries[8];
    uint8_t     count;
};

// ---- Safe tagged union for MT=43 disaster_category data -------------------

struct Mt43Data {
    uint8_t  report_classification;
    uint8_t  disaster_category;
    uint8_t  information_type;
    TimeFields event_time;

    enum class ActiveType : uint8_t {
        None, Eew, Hypocenter, Seismic, Nankai, Tsunami, NwPacTsunami,
        Volcano, AshFall, Weather, Flood, Typhoon, Marine
    };

    ActiveType active_type = ActiveType::None;

    // Storage for the active union member (aligned to 8 bytes)
    // NankaiData is the largest due to aggregated_text buffer (1135 bytes)
    alignas(8) unsigned char storage_[sizeof(NankaiData)];

    Mt43Data()
        : report_classification(0)
        , disaster_category(0)
        , information_type(0)
        , event_time{}
        , active_type(ActiveType::None)
    {
        memset(storage_, 0, sizeof(storage_));
    }

    Mt43Data(const Mt43Data& other)
        : report_classification(other.report_classification)
        , disaster_category(other.disaster_category)
        , information_type(other.information_type)
        , event_time(other.event_time)
        , active_type(other.active_type)
    {
        copyFrom(other);
    }

    Mt43Data& operator=(const Mt43Data& other) {
        if (this != &other) {
            destroyActive();
            report_classification = other.report_classification;
            disaster_category = other.disaster_category;
            information_type = other.information_type;
            event_time = other.event_time;
            active_type = other.active_type;
            copyFrom(other);
        }
        return *this;
    }

    Mt43Data(Mt43Data&& other) noexcept
        : report_classification(other.report_classification)
        , disaster_category(other.disaster_category)
        , information_type(other.information_type)
        , event_time(other.event_time)
        , active_type(other.active_type)
    {
        moveFrom(other);
    }

    Mt43Data& operator=(Mt43Data&& other) noexcept {
        if (this != &other) {
            destroyActive();
            report_classification = other.report_classification;
            disaster_category = other.disaster_category;
            information_type = other.information_type;
            event_time = other.event_time;
            active_type = other.active_type;
            moveFrom(other);
        }
        return *this;
    }

    ~Mt43Data() {
        destroyActive();
    }

    template<typename T>
    void initAs() {
        destroyActive();
        new (storage_) T();
        active_type = typeFor<T>();
    }

    template<typename T>
    T* get() {
        return (active_type == typeFor<T>()) ? reinterpret_cast<T*>(storage_) : nullptr;
    }

    template<typename T>
    const T* get() const {
        return (active_type == typeFor<T>()) ? reinterpret_cast<const T*>(storage_) : nullptr;
    }

    EewData* getEew() { return get<EewData>(); }
    HypocenterData* getHypocenter() { return get<HypocenterData>(); }
    SeismicData* getSeismic() { return get<SeismicData>(); }
    NankaiData* getNankai() { return get<NankaiData>(); }
    TsunamiData* getTsunami() { return get<TsunamiData>(); }
    NwPacTsunamiData* getNwPac() { return get<NwPacTsunamiData>(); }
    VolcanoData* getVolcano() { return get<VolcanoData>(); }
    AshFallData* getAshFall() { return get<AshFallData>(); }
    WeatherData* getWeather() { return get<WeatherData>(); }
    FloodData* getFlood() { return get<FloodData>(); }
    TyphoonData* getTyphoon() { return get<TyphoonData>(); }
    MarineData* getMarine() { return get<MarineData>(); }

    const EewData* getEew() const { return get<EewData>(); }
    const HypocenterData* getHypocenter() const { return get<HypocenterData>(); }
    const SeismicData* getSeismic() const { return get<SeismicData>(); }
    const NankaiData* getNankai() const { return get<NankaiData>(); }
    const TsunamiData* getTsunami() const { return get<TsunamiData>(); }
    const NwPacTsunamiData* getNwPac() const { return get<NwPacTsunamiData>(); }
    const VolcanoData* getVolcano() const { return get<VolcanoData>(); }
    const AshFallData* getAshFall() const { return get<AshFallData>(); }
    const WeatherData* getWeather() const { return get<WeatherData>(); }
    const FloodData* getFlood() const { return get<FloodData>(); }
    const TyphoonData* getTyphoon() const { return get<TyphoonData>(); }
    const MarineData* getMarine() const { return get<MarineData>(); }

private:
    template<typename T> static ActiveType typeFor();

    void destroyActive() {
        if (active_type == ActiveType::None) return;
        switch (active_type) {
            case ActiveType::Eew:            getEew()->~EewData(); break;
            case ActiveType::Hypocenter:     getHypocenter()->~HypocenterData(); break;
            case ActiveType::Seismic:        getSeismic()->~SeismicData(); break;
            case ActiveType::Nankai:         getNankai()->~NankaiData(); break;
            case ActiveType::Tsunami:        getTsunami()->~TsunamiData(); break;
            case ActiveType::NwPacTsunami:    getNwPac()->~NwPacTsunamiData(); break;
            case ActiveType::Volcano:        getVolcano()->~VolcanoData(); break;
            case ActiveType::AshFall:        getAshFall()->~AshFallData(); break;
            case ActiveType::Weather:        getWeather()->~WeatherData(); break;
            case ActiveType::Flood:          getFlood()->~FloodData(); break;
            case ActiveType::Typhoon:        getTyphoon()->~TyphoonData(); break;
            case ActiveType::Marine:         getMarine()->~MarineData(); break;
            case ActiveType::None: break;
        }
        active_type = ActiveType::None;
    }

    void copyFrom(const Mt43Data& other) {
        if (other.active_type == ActiveType::None) return;
        switch (other.active_type) {
            case ActiveType::Eew:            new (storage_) EewData(*other.getEew()); break;
            case ActiveType::Hypocenter:     new (storage_) HypocenterData(*other.getHypocenter()); break;
            case ActiveType::Seismic:        new (storage_) SeismicData(*other.getSeismic()); break;
            case ActiveType::Nankai:         new (storage_) NankaiData(*other.getNankai()); break;
            case ActiveType::Tsunami:        new (storage_) TsunamiData(*other.getTsunami()); break;
            case ActiveType::NwPacTsunami:    new (storage_) NwPacTsunamiData(*other.getNwPac()); break;
            case ActiveType::Volcano:        new (storage_) VolcanoData(*other.getVolcano()); break;
            case ActiveType::AshFall:        new (storage_) AshFallData(*other.getAshFall()); break;
            case ActiveType::Weather:        new (storage_) WeatherData(*other.getWeather()); break;
            case ActiveType::Flood:          new (storage_) FloodData(*other.getFlood()); break;
            case ActiveType::Typhoon:        new (storage_) TyphoonData(*other.getTyphoon()); break;
            case ActiveType::Marine:         new (storage_) MarineData(*other.getMarine()); break;
            case ActiveType::None: break;
        }
    }

    void moveFrom(Mt43Data& other) {
        if (other.active_type == ActiveType::None) return;
        switch (other.active_type) {
            case ActiveType::Eew:            new (storage_) EewData(std::move(*other.getEew())); break;
            case ActiveType::Hypocenter:     new (storage_) HypocenterData(std::move(*other.getHypocenter())); break;
            case ActiveType::Seismic:        new (storage_) SeismicData(std::move(*other.getSeismic())); break;
            case ActiveType::Nankai:         new (storage_) NankaiData(std::move(*other.getNankai())); break;
            case ActiveType::Tsunami:        new (storage_) TsunamiData(std::move(*other.getTsunami())); break;
            case ActiveType::NwPacTsunami:    new (storage_) NwPacTsunamiData(std::move(*other.getNwPac())); break;
            case ActiveType::Volcano:        new (storage_) VolcanoData(std::move(*other.getVolcano())); break;
            case ActiveType::AshFall:        new (storage_) AshFallData(std::move(*other.getAshFall())); break;
            case ActiveType::Weather:        new (storage_) WeatherData(std::move(*other.getWeather())); break;
            case ActiveType::Flood:          new (storage_) FloodData(std::move(*other.getFlood())); break;
            case ActiveType::Typhoon:        new (storage_) TyphoonData(std::move(*other.getTyphoon())); break;
            case ActiveType::Marine:         new (storage_) MarineData(std::move(*other.getMarine())); break;
            case ActiveType::None: break;
        }
        other.active_type = ActiveType::None;
    }
};

// Type mapping specializations
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<EewData>() { return ActiveType::Eew; }
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<HypocenterData>() { return ActiveType::Hypocenter; }
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<SeismicData>() { return ActiveType::Seismic; }
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<NankaiData>() { return ActiveType::Nankai; }
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<TsunamiData>() { return ActiveType::Tsunami; }
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<NwPacTsunamiData>() { return ActiveType::NwPacTsunami; }
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<VolcanoData>() { return ActiveType::Volcano; }
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<AshFallData>() { return ActiveType::AshFall; }
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<WeatherData>() { return ActiveType::Weather; }
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<FloodData>() { return ActiveType::Flood; }
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<TyphoonData>() { return ActiveType::Typhoon; }
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<MarineData>() { return ActiveType::Marine; }

// ---- MT=44 Data (DCX / CAMF) -------------------------------------------

struct Mt44Data {
    Mt44ServiceKind service_kind;
    bool            is_null_message;
    Mt44Sd          sd;
    Mt44CamfRaw     camf;
    TimeFields      onset_time;
    ExtendedKind        ex_kind;
    Mt44ExLAlertOrLocal ex_lalert_local;
    Mt44ExJAlert        ex_jalert;
    Mt44ExOutside       ex_outside;
    Mt44Decoded      mt44_decoded;
};

// ---- Message payload type tag ------------------------------------------

enum class MsgPayloadType : uint8_t {
    Empty,
    Mt43,
    Mt44
};

// ---- main message struct (Safe tagged union) ---------------------------

struct Message {
    uint8_t  svid = 0;
    uint8_t  msg_type = 0;
    uint32_t crc24 = 0;
    bool     valid = false;
    MsgPayloadType payload_type = MsgPayloadType::Empty;

    // Storage for the active payload (aligned to 8 bytes)
    // Mt43Data (1176 bytes) is larger than Mt44Data (464 bytes) due to NankaiData's aggregated_text buffer
    alignas(8) unsigned char payload_storage_[sizeof(Mt43Data)];

    Message() : payload_type(MsgPayloadType::Empty) {
        memset(payload_storage_, 0, sizeof(payload_storage_));
    }

    Message(const Message& other)
        : svid(other.svid)
        , msg_type(other.msg_type)
        , crc24(other.crc24)
        , valid(other.valid)
        , payload_type(other.payload_type)
    {
        copyPayloadFrom(other);
    }

    Message& operator=(const Message& other) {
        if (this != &other) {
            destroyPayload();
            svid = other.svid;
            msg_type = other.msg_type;
            crc24 = other.crc24;
            valid = other.valid;
            payload_type = other.payload_type;
            copyPayloadFrom(other);
        }
        return *this;
    }

    Message(Message&& other) noexcept
        : svid(other.svid)
        , msg_type(other.msg_type)
        , crc24(other.crc24)
        , valid(other.valid)
        , payload_type(other.payload_type)
    {
        movePayloadFrom(other);
    }

    Message& operator=(Message&& other) noexcept {
        if (this != &other) {
            destroyPayload();
            svid = other.svid;
            msg_type = other.msg_type;
            crc24 = other.crc24;
            valid = other.valid;
            payload_type = other.payload_type;
            movePayloadFrom(other);
        }
        return *this;
    }

    ~Message() {
        destroyPayload();
    }

    template<typename T>
    void initPayload() {
        destroyPayload();
        new (payload_storage_) T();
        payload_type = typeForPayload<T>();
    }

    Mt43Data* getMt43() {
        return (payload_type == MsgPayloadType::Mt43)
            ? reinterpret_cast<Mt43Data*>(payload_storage_) : nullptr;
    }

    Mt44Data* getMt44() {
        return (payload_type == MsgPayloadType::Mt44)
            ? reinterpret_cast<Mt44Data*>(payload_storage_) : nullptr;
    }

    const Mt43Data* getMt43() const {
        return (payload_type == MsgPayloadType::Mt43)
            ? reinterpret_cast<const Mt43Data*>(payload_storage_) : nullptr;
    }

    const Mt44Data* getMt44() const {
        return (payload_type == MsgPayloadType::Mt44)
            ? reinterpret_cast<const Mt44Data*>(payload_storage_) : nullptr;
    }

private:
    template<typename T> static MsgPayloadType typeForPayload();

    void destroyPayload() {
        if (payload_type == MsgPayloadType::Empty) return;
        switch (payload_type) {
            case MsgPayloadType::Mt43: getMt43()->~Mt43Data(); break;
            case MsgPayloadType::Mt44: getMt44()->~Mt44Data(); break;
            case MsgPayloadType::Empty: break;
        }
        payload_type = MsgPayloadType::Empty;
    }

    void copyPayloadFrom(const Message& other) {
        if (other.payload_type == MsgPayloadType::Empty) return;
        switch (other.payload_type) {
            case MsgPayloadType::Mt43: new (payload_storage_) Mt43Data(*other.getMt43()); break;
            case MsgPayloadType::Mt44: new (payload_storage_) Mt44Data(*other.getMt44()); break;
            case MsgPayloadType::Empty: break;
        }
    }

    void movePayloadFrom(Message& other) {
        if (other.payload_type == MsgPayloadType::Empty) return;
        switch (other.payload_type) {
            case MsgPayloadType::Mt43: new (payload_storage_) Mt43Data(std::move(*other.getMt43())); break;
            case MsgPayloadType::Mt44: new (payload_storage_) Mt44Data(std::move(*other.getMt44())); break;
            case MsgPayloadType::Empty: break;
        }
        other.payload_type = MsgPayloadType::Empty;
    }
};

// Type mapping specializations for Message payload
template<> inline MsgPayloadType Message::typeForPayload<Mt43Data>() { return MsgPayloadType::Mt43; }
template<> inline MsgPayloadType Message::typeForPayload<Mt44Data>() { return MsgPayloadType::Mt44; }

} // namespace azaraC
