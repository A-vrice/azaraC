#pragma once
// azaraC - src/Mt43Data.h
// MT=43 (QZQSM/DCR) data structures and tagged union
// Bit offsets derived from azarashi (IS-QZSS-DCR-016)

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <new>
#include <utility>

#include "internal/MtCommonTypes.h"

// Nankai Trough aggregated text buffer size (default: 217 bytes)
// Maximum possible: 63 pages × 18 bytes = 1134 bytes + null terminator
// Default is sized for AZARAC_NANKAI_MAX_PAGES (default 12): 12 × 18 + 1 = 217
// Increase for full spec coverage: #define AZARAC_NANKAI_AGGREGATED_TEXT_SIZE 1135
#include "internal/NankaiPageBuffer.h"

#ifndef AZARAC_NANKAI_AGGREGATED_TEXT_SIZE
#define AZARAC_NANKAI_AGGREGATED_TEXT_SIZE 217
#endif

static_assert(AZARAC_NANKAI_AGGREGATED_TEXT_SIZE >=
              azaraC::internal::NankaiPageBuffer::MAX_PAGES *
              azaraC::internal::NankaiPageBuffer::TEXT_PER_PAGE + 1,
              "AZARAC_NANKAI_AGGREGATED_TEXT_SIZE too small for AZARAC_NANKAI_MAX_PAGES");

namespace azaraC {

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
    // Configurable aggregated text buffer size (default: 1135 bytes)
    // Set AZARAC_NANKAI_AGGREGATED_TEXT_SIZE before including azaraC.h to reduce memory usage
    char aggregated_text[AZARAC_NANKAI_AGGREGATED_TEXT_SIZE];
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
    // Size is based on the maximum of all supported variant types to ensure
    // safe placement-new for any type, even when AZARAC_NANKAI_AGGREGATED_TEXT_SIZE
    // is configured to a small value.
    static constexpr size_t storage_size_ = std::max(sizeof(EewData),
        std::max(sizeof(HypocenterData),
        std::max(sizeof(SeismicData),
        std::max(sizeof(NankaiData),
        std::max(sizeof(TsunamiData),
        std::max(sizeof(NwPacTsunamiData),
        std::max(sizeof(VolcanoData),
        std::max(sizeof(AshFallData),
        std::max(sizeof(WeatherData),
        std::max(sizeof(FloodData),
        std::max(sizeof(TyphoonData),
        sizeof(MarineData))))))))))));
    alignas(8) unsigned char storage_[storage_size_];

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

} // namespace azaraC
