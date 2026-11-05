#pragma once
// MT=43 (QZQSM/DCR) のデータ構造とタグ付き union。ビット位置は IS-QZSS-DCR-017（azarashi の定義表）由来。
//
// 規約: payload の全型（EewData … MarineData）は trivially copyable/destructible のまま維持すること（スカラ・固定長配列・POD のみ、所有ポインタ禁止）。
// コピー/ムーブ/破棄が memcpy とタグのリセットで済む前提。

#if defined(__AVR__)
#include "internal/avr_std/cstdint"
#else
#include <cstdint>
#endif
#if defined(__AVR__)
#include "internal/avr_std/cstring"
#else
#include <cstring>
#endif
#if defined(__AVR__)
#include "internal/avr_std/new"
#else
#include <new>
#endif
#if !defined(__AVR__) || defined(AZARAC_AVR_STUB)
#include <type_traits>
#endif

#include "azaraC_config.h"
#include "internal/MtCommonTypes.h"

#if AZARAC_ENABLE_NANKAI
#include "internal/NankaiPageBuffer.h"
#endif

namespace azaraC {

// 繰返しエントリの要素型（各カテゴリの entries[] に並ぶ）

struct TsunamiEntry {
    // Ta(12b) は単独の 16 bit ユニットを使う。Th(4b)+Pl(10b) が次のユニットを共有する（間の TimeFields がユニットを分断する）。
    uint16_t   arrival_time_raw : 12;
    TimeFields arrival_time;
    uint16_t   height_code      : 4;
    uint16_t   region_code      : 10;
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
    // 同様に Th(9b)+Pl(7b) が 1 ユニットを共有する（Ta は単独、間の TimeFields が分断する）。
    uint16_t   arrival_time_raw : 12;
    TimeFields arrival_time;
    uint16_t   height_code      : 9;
    uint16_t   region_code      : 7;
};

// MT=43 payload

#if AZARAC_ENABLE_EEW
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
    // 予報区 80 区を電文 [130..209] のビット配置のまま保持（bit i = 予報区 i+1）。展開配列だと 81 B かかる。
    uint8_t  region_bitmap[10];

    // 対象予報区の個数
    uint8_t regionCount() const {
        uint8_t n = 0;
        for (uint8_t byt = 0; byt < 10; ++byt) n = (uint8_t)(n + popcount8(region_bitmap[byt]));
        return n;
    }
    // 昇順 i 番目 (0 始まり) の対象予報区コード (1..80)。i >= regionCount() は 0。
    // 各バイトの立ビット数を数え、i がそのバイトに無ければ丸ごと読み飛ばす（最悪 80 bit 走査 → 10 バイト + 8 bit）。
    uint8_t regionAt(uint8_t i) const {
        for (uint8_t byt = 0; byt < 10; ++byt) {
            const uint8_t v = region_bitmap[byt];
            const uint8_t n = popcount8(v);
            if (i >= n) { i = (uint8_t)(i - n); continue; }
            for (uint8_t bit = 0; bit < 8; ++bit) {
                if (!(v & (0x80u >> bit))) continue;
                if (i == 0) return (uint8_t)(byt * 8u + bit + 1u);
                --i;
            }
        }
        return 0;
    }
    // 予報区 code (1..80) を対象に加える。範囲外は無視し、既に立っているビットはそのまま。
    void addRegion(uint8_t code) {
        if (code == 0 || code > 80) return;
        region_bitmap[(code - 1u) >> 3] = (uint8_t)(region_bitmap[(code - 1u) >> 3] | (0x80u >> ((code - 1u) & 7u)));
    }

  private:
    // 1 バイト中の立っているビット数（Kernighan 法）
    static uint8_t popcount8(uint8_t v) {
        uint8_t n = 0;
        while (v) { v = (uint8_t)(v & (uint8_t)(v - 1u)); ++n; }
        return n;
    }
};
#endif // AZARAC_ENABLE_EEW

#if AZARAC_ENABLE_HYPOCENTER
struct HypocenterData {
    uint16_t   notification[3];
    uint8_t    notification_count;
    TimeFields quake_time;
    uint16_t   depth;
    uint8_t    magnitude;
    uint16_t   epicenter;
    LatLon     coords;
};
#endif // AZARAC_ENABLE_HYPOCENTER

struct SeismicData {
    TimeFields   quake_time;
    SeismicEntry entries[16];
    uint8_t      count;
};

#if AZARAC_ENABLE_NANKAI
// 南海トラフ前沿のページ集約。
// aggregated_text_ptr（is_aggregated のとき）は Parser が静的保持する NankaiPageBuffer::aggregated_text[] への借用で、次の feed()/reset() かスロット再利用で無効になる（その頃バッファは別の事象を持ち得る）。
// 呼び出し側は直ちにコピー/シリアライズすること。
// Message ごとに AZARAC_NANKAI_MAX_PAGES*18 B のコピーを避けるゼロコピー設計。
struct NankaiData {
    uint8_t info_code;
    uint8_t text[18];
    uint8_t page;
    uint8_t total_page;
    // 受信した MT=43 の report_time（bit 21/25/30/35）をそのまま保持し、集約キーの軸にする。
    // event_time と違い Decoder::resolveTime の正規化を受けないので、放送途中で report_unix が有効/無効になっても鍵がずれない。
    uint8_t report_month;   // 1-12 (4b)
    uint8_t report_day;     // 1-31 (5b)
    uint8_t report_hour;    // 0-23 (5b)
    uint8_t report_minute;  // 0-59 (6b)
    const char* aggregated_text_ptr = nullptr;  // 次の feed()/reset() まで
    uint16_t aggregated_len = 0;
    bool is_aggregated = false;
    bool truncated = false;
};
#endif

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

// 災害カテゴリ別 payload の tagged union

struct Mt43Data {
    uint8_t  report_classification;
    uint8_t  disaster_category;
    uint8_t  information_type;
    uint8_t  version;        // Vn: [214..219]、仕様上の値は 1
    TimeFields event_time;

    enum class ActiveType : uint8_t {
        None,
#if AZARAC_ENABLE_EEW
        Eew,
#endif
#if AZARAC_ENABLE_HYPOCENTER
        Hypocenter,
#endif
        Seismic,
#if AZARAC_ENABLE_NANKAI
        Nankai,
#endif
        Tsunami, NwPacTsunami,
        Volcano, AshFall, Weather, Flood, Typhoon, Marine
    };

    ActiveType active_type = ActiveType::None;

    static constexpr size_t storage_size_ = []() -> size_t {
        constexpr size_t sizes[] = {
#if AZARAC_ENABLE_EEW
            sizeof(EewData),
#endif
#if AZARAC_ENABLE_HYPOCENTER
            sizeof(HypocenterData),
#endif
            sizeof(SeismicData),
#if AZARAC_ENABLE_NANKAI
            sizeof(NankaiData),
#endif
            sizeof(TsunamiData),
            sizeof(NwPacTsunamiData),
            sizeof(VolcanoData),
            sizeof(AshFallData),
            sizeof(WeatherData),
            sizeof(FloodData),
            sizeof(TyphoonData),
            sizeof(MarineData)
        };
        size_t m = 0;
        for (auto x : sizes) if (x > m) m = x;
        return m;
    }();
    // uint64_t を含む型（FloodEntry 等）が入るため境界指定が必要。AVR の alignof(uint64_t) は 1 なので実質要求なし（8 の倍数への切り上げが起きない）、ホストは 8。
    alignas(uint64_t) unsigned char storage_[storage_size_];

    Mt43Data()
        : report_classification(0)
        , disaster_category(0)
        , information_type(0)
        , version(0)
        , event_time{}
        , active_type(ActiveType::None)
    {
        memset(storage_, 0, sizeof(storage_));
    }

    Mt43Data(const Mt43Data& other)
        : report_classification(other.report_classification)
        , disaster_category(other.disaster_category)
        , information_type(other.information_type)
        , version(other.version)
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
            version = other.version;
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
        , version(other.version)
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
            version = other.version;
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
        static_assert(sizeof(T) <= storage_size_,
                      "Payload type exceeds Mt43Data storage (missing from storage_size_?)");
#if !defined(__AVR__) || defined(AZARAC_AVR_STUB)
        static_assert(std::is_trivially_copyable_v<T>,
                      "Payload type must be trivially copyable for placement new");
#endif
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

#if AZARAC_ENABLE_EEW
    EewData* getEew() { return get<EewData>(); }
#endif
#if AZARAC_ENABLE_HYPOCENTER
    HypocenterData* getHypocenter() { return get<HypocenterData>(); }
#endif
    SeismicData* getSeismic() { return get<SeismicData>(); }
#if AZARAC_ENABLE_NANKAI
    NankaiData* getNankai() { return get<NankaiData>(); }
#endif
    TsunamiData* getTsunami() { return get<TsunamiData>(); }
    NwPacTsunamiData* getNwPac() { return get<NwPacTsunamiData>(); }
    VolcanoData* getVolcano() { return get<VolcanoData>(); }
    AshFallData* getAshFall() { return get<AshFallData>(); }
    WeatherData* getWeather() { return get<WeatherData>(); }
    FloodData* getFlood() { return get<FloodData>(); }
    TyphoonData* getTyphoon() { return get<TyphoonData>(); }
    MarineData* getMarine() { return get<MarineData>(); }

#if AZARAC_ENABLE_EEW
    const EewData* getEew() const { return get<EewData>(); }
#endif
#if AZARAC_ENABLE_HYPOCENTER
    const HypocenterData* getHypocenter() const { return get<HypocenterData>(); }
#endif
    const SeismicData* getSeismic() const { return get<SeismicData>(); }
#if AZARAC_ENABLE_NANKAI
    const NankaiData* getNankai() const { return get<NankaiData>(); }
#endif
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
        active_type = ActiveType::None;  // payload 型はすべて trivially destructible なので破棄は不要
    }

    void copyFrom(const Mt43Data& other) {
        memcpy(storage_, other.storage_, storage_size_);  // payload 型はすべて trivially copyable
    }

    void moveFrom(Mt43Data& other) {
        memcpy(storage_, other.storage_, storage_size_);  // trivial なのでムーブはコピーと同じ
        other.active_type = ActiveType::None;
    }
};

#if AZARAC_ENABLE_EEW
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<EewData>() { return ActiveType::Eew; }
#endif
#if AZARAC_ENABLE_HYPOCENTER
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<HypocenterData>() { return ActiveType::Hypocenter; }
#endif
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<SeismicData>() { return ActiveType::Seismic; }
#if AZARAC_ENABLE_NANKAI
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<NankaiData>() { return ActiveType::Nankai; }
#endif
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<TsunamiData>() { return ActiveType::Tsunami; }
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<NwPacTsunamiData>() { return ActiveType::NwPacTsunami; }
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<VolcanoData>() { return ActiveType::Volcano; }
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<AshFallData>() { return ActiveType::AshFall; }
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<WeatherData>() { return ActiveType::Weather; }
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<FloodData>() { return ActiveType::Flood; }
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<TyphoonData>() { return ActiveType::Typhoon; }
template<> inline Mt43Data::ActiveType Mt43Data::typeFor<MarineData>() { return ActiveType::Marine; }

} // namespace azaraC
