// Message構造体の安全なタグ付き共用体テスト

#define ARDUINO 0
#include <utility>
#include "../test_helpers.h"
#include "doctest.h"
#include "../src/internal/TimeFields.h"

using namespace azaraC;

// payload 領域は Mt44Data（uint64_t を含む）を配置できる境界を持つこと。
// alignas(uint64_t) はホストで 8、AVR で 1 に解決されるので、どちらでもこの条件は満たされる。
static_assert(alignof(azaraC::Message) >= alignof(azaraC::Mt44Data),
              "Message payload storage must be aligned for Mt44Data");
// その境界を決めるのは payload 型の側: `alignas(uint64_t)` の枠に載る型は alignof(uint64_t) を超えてはならない。
// 超えた型（メンバに alignas(16) の配列を持つ等）を足すと枠が足りなくなるので、Message の他のメンバに救われて通る書き方ではなくこちらで固定する。
static_assert(alignof(azaraC::Mt43Data) <= alignof(uint64_t),
              "Mt43Data over-aligns the alignas(uint64_t) payload buffer");
static_assert(alignof(azaraC::Mt44Data) <= alignof(uint64_t),
              "Mt44Data over-aligns the alignas(uint64_t) payload buffer");

// Message構造体のテスト

TEST_CASE("Message: デフォルトコンストラクタ") {
    Message msg;
    CHECK(msg.svid == 0);
    CHECK(msg.msg_type == 0);
    CHECK(msg.crc24 == 0);
    CHECK(msg.valid == false);
    CHECK(msg.payload_type == MsgPayloadType::Empty);
    CHECK(msg.getMt43() == nullptr);
    CHECK(msg.getMt44() == nullptr);
}

TEST_CASE("Message: MT=43ペイロードの初期化とアクセス") {
    Message msg;
    msg.initPayload<Mt43Data>();

    CHECK(msg.payload_type == MsgPayloadType::Mt43);
    Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);

    CHECK(mt43->report_classification == 0);
    CHECK(mt43->disaster_category == 0);
    CHECK(mt43->information_type == 0);

    CHECK(msg.getMt44() == nullptr);
}

#if (AZARAC_ENABLE_DCX_CAMF)
TEST_CASE("Message: MT=44ペイロードの初期化とアクセス") {
    Message msg;
    msg.initPayload<Mt44Data>();

    CHECK(msg.payload_type == MsgPayloadType::Mt44);
    Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);

    // placement newでゼロ初期化されるためNullMessage(0)になる
    CHECK(mt44->service_kind == Mt44ServiceKind::NullMessage);
    CHECK(mt44->is_null_message == false);

    CHECK(msg.getMt43() == nullptr);
}
#endif // AZARAC_ENABLE_DCX_CAMF

#if (AZARAC_ENABLE_SEISMIC)
TEST_CASE("Message: コピーコンストラクタ") {
    Message msg1;
    msg1.svid = 184;
    msg1.msg_type = 43;
    msg1.crc24 = 0x123456;
    msg1.valid = true;
    msg1.initPayload<Mt43Data>();
    Mt43Data* src = msg1.getMt43();
    REQUIRE(src != nullptr);
    src->initAs<SeismicData>();
    src->getSeismic()->count = 1;
    src->getSeismic()->entries[0].intensity_code = 4;

    Message msg2(msg1);
    CHECK(msg2.svid == 184);
    CHECK(msg2.msg_type == 43);
    CHECK(msg2.crc24 == 0x123456);
    CHECK(msg2.valid == true);
    CHECK(msg2.payload_type == MsgPayloadType::Mt43);
    REQUIRE(msg2.getMt43() != nullptr);
    const SeismicData* copied = msg2.getMt43()->getSeismic();
    REQUIRE(copied != nullptr);
    CHECK(copied->count == 1);
    CHECK(copied->entries[0].intensity_code == 4);
}
#endif // AZARAC_ENABLE_SEISMIC

TEST_CASE("Message: コピー代入演算子") {
    Message msg1;
    msg1.svid = 185;
#if (AZARAC_ENABLE_DCX_CAMF)
    msg1.msg_type = 44;
#else
    msg1.msg_type = 43;
#endif
    msg1.crc24 = 0x654321;
    msg1.valid = true;
#if (AZARAC_ENABLE_DCX_CAMF)
    msg1.initPayload<Mt44Data>();
    Mt44Data* src44 = msg1.getMt44();
    REQUIRE(src44 != nullptr);
    src44->service_kind = Mt44ServiceKind::JAlert;
    src44->camf.a2 = 111;
#else
    msg1.initPayload<Mt43Data>();
    Mt43Data* src43 = msg1.getMt43();
    REQUIRE(src43 != nullptr);
#if (AZARAC_ENABLE_SEISMIC)
    src43->initAs<SeismicData>();
    src43->getSeismic()->count = 1;
    src43->getSeismic()->entries[0].intensity_code = 4;
#endif
#endif

    Message msg2;
    msg2 = msg1;
    CHECK(msg2.svid == 185);
#if (AZARAC_ENABLE_DCX_CAMF)
    CHECK(msg2.msg_type == 44);
#else
    CHECK(msg2.msg_type == 43);
#endif
    CHECK(msg2.crc24 == 0x654321);
    CHECK(msg2.valid == true);
#if (AZARAC_ENABLE_DCX_CAMF)
    CHECK(msg2.payload_type == MsgPayloadType::Mt44);
    const Mt44Data* copied44 = msg2.getMt44();
    REQUIRE(copied44 != nullptr);
    CHECK(copied44->service_kind == Mt44ServiceKind::JAlert);
    CHECK(copied44->camf.a2 == 111);
#else
    CHECK(msg2.payload_type == MsgPayloadType::Mt43);
    const Mt43Data* copied43 = msg2.getMt43();
    REQUIRE(copied43 != nullptr);
#if (AZARAC_ENABLE_SEISMIC)
    const SeismicData* copied = copied43->getSeismic();
    REQUIRE(copied != nullptr);
    CHECK(copied->count == 1);
    CHECK(copied->entries[0].intensity_code == 4);
#endif
#endif
}

// Mt43Dataの安全なタグ付き共用体のテスト

TEST_CASE("Mt43Data: デフォルトコンストラクタ") {
    Mt43Data data;
    CHECK(data.report_classification == 0);
    CHECK(data.disaster_category == 0);
    CHECK(data.information_type == 0);
    CHECK(data.active_type == Mt43Data::ActiveType::None);
}

#if (AZARAC_ENABLE_EEW)
TEST_CASE("Mt43Data: EewDataの初期化とアクセス") {
    Mt43Data data;
    data.initAs<EewData>();

    CHECK(data.active_type == Mt43Data::ActiveType::Eew);

    EewData* eew = data.getEew();
    REQUIRE(eew != nullptr);
    CHECK(eew->long_period_lower == 0);
    CHECK(eew->long_period_upper == 0);
    CHECK(eew->notification_count == 0);
    CHECK(eew->depth == 0);
    CHECK(eew->magnitude == 0);
    CHECK(eew->epicenter == 0);
    CHECK(eew->intensity_lower == 0);
    CHECK(eew->intensity_upper == 0);
    CHECK(eew->regionCount() == 0);

#if (AZARAC_ENABLE_HYPOCENTER)
    CHECK(data.getHypocenter() == nullptr);
#endif
#if (AZARAC_ENABLE_SEISMIC)
    CHECK(data.getSeismic() == nullptr);
#endif
#if (AZARAC_ENABLE_NANKAI)
    CHECK(data.getNankai() == nullptr);
#endif
}

TEST_CASE("Mt43Data: EewData 予報区アクセサ") {
    EewData eew{};
    CHECK(eew.regionCount() == 0);
    CHECK(eew.regionAt(0) == 0);

    eew.addRegion(0);    // 範囲外は無視
    eew.addRegion(81);
    CHECK(eew.regionCount() == 0);

    eew.addRegion(8);
    eew.addRegion(9);    // バイト境界またぎ（bit 7 → 次バイト bit 0）
    eew.addRegion(16);
    eew.addRegion(80);   // 最終ビット
    eew.addRegion(9);    // 重複は無視
    CHECK(eew.regionCount() == 4);
    CHECK(eew.regionAt(0) == 8);
    CHECK(eew.regionAt(1) == 9);
    CHECK(eew.regionAt(2) == 16);
    CHECK(eew.regionAt(3) == 80);
    CHECK(eew.regionAt(4) == 0);    // i >= regionCount()
    CHECK(eew.regionAt(255) == 0);
}
#endif // AZARAC_ENABLE_EEW

#if (AZARAC_ENABLE_NANKAI)
TEST_CASE("Mt43Data: NankaiDataの初期化とアクセス") {
    Mt43Data data;
    data.initAs<NankaiData>();

    CHECK(data.active_type == Mt43Data::ActiveType::Nankai);

    NankaiData* nankai = data.getNankai();
    REQUIRE(nankai != nullptr);
    CHECK(nankai->info_code == 0);
    CHECK(nankai->page == 0);
    CHECK(nankai->total_page == 0);
    CHECK(nankai->is_aggregated == false);
    CHECK(nankai->aggregated_len == 0);
}
#endif

#if (AZARAC_ENABLE_TYPHOON)
TEST_CASE("Mt43Data: TyphoonDataの初期化とアクセス") {
    Mt43Data data;
    data.initAs<TyphoonData>();

    CHECK(data.active_type == Mt43Data::ActiveType::Typhoon);

    TyphoonData* typh = data.getTyphoon();
    REQUIRE(typh != nullptr);
    CHECK(typh->ref_type == 0);
    CHECK(typh->elapsed == 0);
    CHECK(typh->number == 0);
    CHECK(typh->scale == 0);
    CHECK(typh->intensity == 0);
    CHECK(typh->pressure == 0);
    CHECK(typh->max_wind == 0);
    CHECK(typh->max_gust == 0);
}
#endif // AZARAC_ENABLE_TYPHOON

#if (AZARAC_ENABLE_EEW)
TEST_CASE("Mt43Data: 型の切り替え") {
    Mt43Data data;

    data.initAs<EewData>();
    CHECK(data.active_type == Mt43Data::ActiveType::Eew);
    CHECK(data.getEew() != nullptr);

#if (AZARAC_ENABLE_NANKAI)
    data.initAs<NankaiData>();
    CHECK(data.active_type == Mt43Data::ActiveType::Nankai);
    CHECK(data.getNankai() != nullptr);
    CHECK(data.getEew() == nullptr);
#endif
}
#endif // AZARAC_ENABLE_EEW

#if (AZARAC_ENABLE_NANKAI)
TEST_CASE("Mt43Data: コピーコンストラクタ") {
    Mt43Data data1;
    data1.report_classification = 1;
    data1.disaster_category = 4;
    data1.initAs<NankaiData>();

    Mt43Data data2(data1);
    CHECK(data2.report_classification == 1);
    CHECK(data2.disaster_category == 4);
    CHECK(data2.active_type == Mt43Data::ActiveType::Nankai);
    CHECK(data2.getNankai() != nullptr);
}
#endif

#if (AZARAC_ENABLE_TSUNAMI)
TEST_CASE("Mt43Data: コピー代入演算子") {
    Mt43Data data1;
    data1.report_classification = 2;
    data1.disaster_category = 5;
    data1.initAs<TsunamiData>();

    Mt43Data data2;
    data2 = data1;
    CHECK(data2.report_classification == 2);
    CHECK(data2.disaster_category == 5);
    CHECK(data2.active_type == Mt43Data::ActiveType::Tsunami);
    CHECK(data2.getTsunami() != nullptr);
}
#endif // AZARAC_ENABLE_TSUNAMI

namespace {

// コピー/ムーブで payload の値が失われないことを型ごとに確認するための代表値。
void setSentinel(Mt43Data& d) {
    switch (d.active_type) {
#if (AZARAC_ENABLE_EEW)
        case Mt43Data::ActiveType::Eew: {
            EewData* p = d.getEew();
            REQUIRE(p != nullptr);
            p->depth = 500; p->magnitude = 70; p->epicenter = 12345;
            break;
        }
#endif
#if (AZARAC_ENABLE_HYPOCENTER)
        case Mt43Data::ActiveType::Hypocenter: {
            HypocenterData* p = d.getHypocenter();
            REQUIRE(p != nullptr);
            p->depth = 500; p->magnitude = 70; p->epicenter = 12345;
            break;
        }
#endif
#if (AZARAC_ENABLE_SEISMIC)
        case Mt43Data::ActiveType::Seismic: {
            SeismicData* p = d.getSeismic();
            REQUIRE(p != nullptr);
            p->count = 1; p->entries[0].intensity_code = 4; p->entries[0].prefecture_code = 13;
            break;
        }
#endif // AZARAC_ENABLE_SEISMIC
#if (AZARAC_ENABLE_NANKAI)
        case Mt43Data::ActiveType::Nankai: {
            NankaiData* p = d.getNankai();
            REQUIRE(p != nullptr);
            p->info_code = 7; p->page = 3; p->total_page = 27; p->text[0] = 'N';
            break;
        }
#endif
#if (AZARAC_ENABLE_TSUNAMI)
        case Mt43Data::ActiveType::Tsunami: {
            TsunamiData* p = d.getTsunami();
            REQUIRE(p != nullptr);
            p->warning_code = 3; p->count = 1;
            p->entries[0].region_code = 65; p->entries[0].height_code = 4;
            break;
        }
#endif // AZARAC_ENABLE_TSUNAMI
#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)
        case Mt43Data::ActiveType::NwPacTsunami: {
            NwPacTsunamiData* p = d.getNwPac();
            REQUIRE(p != nullptr);
            p->potential = 2; p->count = 1;
            p->entries[0].region_code = 7; p->entries[0].height_code = 9;
            break;
        }
#endif // AZARAC_ENABLE_NW_PAC_TSUNAMI
#if (AZARAC_ENABLE_VOLCANO)
        case Mt43Data::ActiveType::Volcano: {
            VolcanoData* p = d.getVolcano();
            REQUIRE(p != nullptr);
            p->warning_code = 52; p->volcano_name = 503;
            p->lg_count = 1; p->local_govs[0] = 4600000;
            break;
        }
#endif // AZARAC_ENABLE_VOLCANO
#if (AZARAC_ENABLE_ASH_FALL)
        case Mt43Data::ActiveType::AshFall: {
            AshFallData* p = d.getAshFall();
            REQUIRE(p != nullptr);
            p->warning_type = 1; p->volcano_name = 503; p->count = 2;
            p->entries_code[1] = 5; p->entries_lg[1] = 1200000;
            break;
        }
#endif // AZARAC_ENABLE_ASH_FALL
#if (AZARAC_ENABLE_WEATHER)
        case Mt43Data::ActiveType::Weather: {
            WeatherData* p = d.getWeather();
            REQUIRE(p != nullptr);
            p->warning_state = 1; p->count = 2;
            p->entries[1].sub_category = 3; p->entries[1].region_code = 12000;
            break;
        }
#endif // AZARAC_ENABLE_WEATHER
#if (AZARAC_ENABLE_FLOOD)
        case Mt43Data::ActiveType::Flood: {
            FloodData* p = d.getFlood();
            REQUIRE(p != nullptr);
            p->count = 1; p->entries[0].warning_level = 3; p->entries[0].region_code = 1234567ULL;
            break;
        }
#endif // AZARAC_ENABLE_FLOOD
#if (AZARAC_ENABLE_TYPHOON)
        case Mt43Data::ActiveType::Typhoon: {
            TyphoonData* p = d.getTyphoon();
            REQUIRE(p != nullptr);
            p->number = 21; p->pressure = 980; p->max_wind = 35; p->coords.lat_deg = 25;
            break;
        }
#endif // AZARAC_ENABLE_TYPHOON
#if (AZARAC_ENABLE_MARINE)
        case Mt43Data::ActiveType::Marine: {
            MarineData* p = d.getMarine();
            REQUIRE(p != nullptr);
            p->count = 1; p->entries[0].warning_code = 20; p->entries[0].region_code = 11000;
            break;
        }
#endif // AZARAC_ENABLE_MARINE
        default: break;
    }
}

void checkSentinel(const Mt43Data& d) {
    switch (d.active_type) {
#if (AZARAC_ENABLE_EEW)
        case Mt43Data::ActiveType::Eew: {
            const EewData* p = d.getEew();
            REQUIRE(p != nullptr);
            CHECK(p->depth == 500); CHECK(p->magnitude == 70); CHECK(p->epicenter == 12345);
            break;
        }
#endif
#if (AZARAC_ENABLE_HYPOCENTER)
        case Mt43Data::ActiveType::Hypocenter: {
            const HypocenterData* p = d.getHypocenter();
            REQUIRE(p != nullptr);
            CHECK(p->depth == 500); CHECK(p->magnitude == 70); CHECK(p->epicenter == 12345);
            break;
        }
#endif
#if (AZARAC_ENABLE_SEISMIC)
        case Mt43Data::ActiveType::Seismic: {
            const SeismicData* p = d.getSeismic();
            REQUIRE(p != nullptr);
            CHECK(p->count == 1); CHECK(p->entries[0].intensity_code == 4);
            CHECK(p->entries[0].prefecture_code == 13);
            break;
        }
#endif // AZARAC_ENABLE_SEISMIC
#if (AZARAC_ENABLE_NANKAI)
        case Mt43Data::ActiveType::Nankai: {
            const NankaiData* p = d.getNankai();
            REQUIRE(p != nullptr);
            CHECK(p->info_code == 7); CHECK(p->page == 3); CHECK(p->total_page == 27);
            CHECK(p->text[0] == 'N');
            break;
        }
#endif
#if (AZARAC_ENABLE_TSUNAMI)
        case Mt43Data::ActiveType::Tsunami: {
            const TsunamiData* p = d.getTsunami();
            REQUIRE(p != nullptr);
            CHECK(p->warning_code == 3); CHECK(p->count == 1);
            CHECK(p->entries[0].region_code == 65); CHECK(p->entries[0].height_code == 4);
            break;
        }
#endif // AZARAC_ENABLE_TSUNAMI
#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)
        case Mt43Data::ActiveType::NwPacTsunami: {
            const NwPacTsunamiData* p = d.getNwPac();
            REQUIRE(p != nullptr);
            CHECK(p->potential == 2); CHECK(p->count == 1);
            CHECK(p->entries[0].region_code == 7); CHECK(p->entries[0].height_code == 9);
            break;
        }
#endif // AZARAC_ENABLE_NW_PAC_TSUNAMI
#if (AZARAC_ENABLE_VOLCANO)
        case Mt43Data::ActiveType::Volcano: {
            const VolcanoData* p = d.getVolcano();
            REQUIRE(p != nullptr);
            CHECK(p->warning_code == 52); CHECK(p->volcano_name == 503);
            CHECK(p->lg_count == 1); CHECK(p->local_govs[0] == 4600000);
            break;
        }
#endif // AZARAC_ENABLE_VOLCANO
#if (AZARAC_ENABLE_ASH_FALL)
        case Mt43Data::ActiveType::AshFall: {
            const AshFallData* p = d.getAshFall();
            REQUIRE(p != nullptr);
            CHECK(p->warning_type == 1); CHECK(p->volcano_name == 503); CHECK(p->count == 2);
            CHECK(p->entries_code[1] == 5); CHECK(p->entries_lg[1] == 1200000);
            break;
        }
#endif // AZARAC_ENABLE_ASH_FALL
#if (AZARAC_ENABLE_WEATHER)
        case Mt43Data::ActiveType::Weather: {
            const WeatherData* p = d.getWeather();
            REQUIRE(p != nullptr);
            CHECK(p->warning_state == 1); CHECK(p->count == 2);
            CHECK(p->entries[1].sub_category == 3); CHECK(p->entries[1].region_code == 12000);
            break;
        }
#endif // AZARAC_ENABLE_WEATHER
#if (AZARAC_ENABLE_FLOOD)
        case Mt43Data::ActiveType::Flood: {
            const FloodData* p = d.getFlood();
            REQUIRE(p != nullptr);
            CHECK(p->count == 1); CHECK(p->entries[0].warning_level == 3);
            CHECK(p->entries[0].region_code == 1234567ULL);
            break;
        }
#endif // AZARAC_ENABLE_FLOOD
#if (AZARAC_ENABLE_TYPHOON)
        case Mt43Data::ActiveType::Typhoon: {
            const TyphoonData* p = d.getTyphoon();
            REQUIRE(p != nullptr);
            CHECK(p->number == 21); CHECK(p->pressure == 980);
            CHECK(p->max_wind == 35); CHECK(p->coords.lat_deg == 25);
            break;
        }
#endif // AZARAC_ENABLE_TYPHOON
#if (AZARAC_ENABLE_MARINE)
        case Mt43Data::ActiveType::Marine: {
            const MarineData* p = d.getMarine();
            REQUIRE(p != nullptr);
            CHECK(p->count == 1); CHECK(p->entries[0].warning_code == 20);
            CHECK(p->entries[0].region_code == 11000);
            break;
        }
#endif // AZARAC_ENABLE_MARINE
        default: break;
    }
}

// 全 payload 型の初期化と型安全性チェックを1か所に集約する。
// copy/move の各テストはこのテーブルを回すだけで、型を追加したときの修正箇所を減らす。
static const Mt43Data::ActiveType kPayloadTypes[] = {
#if (AZARAC_ENABLE_EEW)
    Mt43Data::ActiveType::Eew,
#endif
#if (AZARAC_ENABLE_HYPOCENTER)
    Mt43Data::ActiveType::Hypocenter,
#endif
#if (AZARAC_ENABLE_SEISMIC)
    Mt43Data::ActiveType::Seismic,
#endif // AZARAC_ENABLE_SEISMIC
#if (AZARAC_ENABLE_NANKAI)
    Mt43Data::ActiveType::Nankai,
#endif
#if (AZARAC_ENABLE_TSUNAMI)
    Mt43Data::ActiveType::Tsunami,
#endif // AZARAC_ENABLE_TSUNAMI
#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)
    Mt43Data::ActiveType::NwPacTsunami,
#endif // AZARAC_ENABLE_NW_PAC_TSUNAMI
#if (AZARAC_ENABLE_VOLCANO)
    Mt43Data::ActiveType::Volcano,
#endif // AZARAC_ENABLE_VOLCANO
#if (AZARAC_ENABLE_ASH_FALL)
    Mt43Data::ActiveType::AshFall,
#endif // AZARAC_ENABLE_ASH_FALL
#if (AZARAC_ENABLE_WEATHER)
    Mt43Data::ActiveType::Weather,
#endif // AZARAC_ENABLE_WEATHER
#if (AZARAC_ENABLE_FLOOD)
    Mt43Data::ActiveType::Flood,
#endif // AZARAC_ENABLE_FLOOD
#if (AZARAC_ENABLE_TYPHOON)
    Mt43Data::ActiveType::Typhoon,
#endif // AZARAC_ENABLE_TYPHOON
#if (AZARAC_ENABLE_MARINE)
    Mt43Data::ActiveType::Marine,
#endif // AZARAC_ENABLE_MARINE
};

static void initAsType(Mt43Data& data, Mt43Data::ActiveType type) {
    (void)data;   // 全カテゴリ無効では下の case がすべて消える
    switch (type) {
#if (AZARAC_ENABLE_EEW)
        case Mt43Data::ActiveType::Eew:          data.initAs<EewData>(); break;
#endif
#if (AZARAC_ENABLE_HYPOCENTER)
        case Mt43Data::ActiveType::Hypocenter:   data.initAs<HypocenterData>(); break;
#endif
#if (AZARAC_ENABLE_SEISMIC)
        case Mt43Data::ActiveType::Seismic:      data.initAs<SeismicData>(); break;
#endif // AZARAC_ENABLE_SEISMIC
#if (AZARAC_ENABLE_NANKAI)
        case Mt43Data::ActiveType::Nankai:       data.initAs<NankaiData>(); break;
#endif
#if (AZARAC_ENABLE_TSUNAMI)
        case Mt43Data::ActiveType::Tsunami:      data.initAs<TsunamiData>(); break;
#endif // AZARAC_ENABLE_TSUNAMI
#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)
        case Mt43Data::ActiveType::NwPacTsunami: data.initAs<NwPacTsunamiData>(); break;
#endif // AZARAC_ENABLE_NW_PAC_TSUNAMI
#if (AZARAC_ENABLE_VOLCANO)
        case Mt43Data::ActiveType::Volcano:      data.initAs<VolcanoData>(); break;
#endif // AZARAC_ENABLE_VOLCANO
#if (AZARAC_ENABLE_ASH_FALL)
        case Mt43Data::ActiveType::AshFall:      data.initAs<AshFallData>(); break;
#endif // AZARAC_ENABLE_ASH_FALL
#if (AZARAC_ENABLE_WEATHER)
        case Mt43Data::ActiveType::Weather:      data.initAs<WeatherData>(); break;
#endif // AZARAC_ENABLE_WEATHER
#if (AZARAC_ENABLE_FLOOD)
        case Mt43Data::ActiveType::Flood:        data.initAs<FloodData>(); break;
#endif // AZARAC_ENABLE_FLOOD
#if (AZARAC_ENABLE_TYPHOON)
        case Mt43Data::ActiveType::Typhoon:      data.initAs<TyphoonData>(); break;
#endif // AZARAC_ENABLE_TYPHOON
#if (AZARAC_ENABLE_MARINE)
        case Mt43Data::ActiveType::Marine:       data.initAs<MarineData>(); break;
#endif // AZARAC_ENABLE_MARINE
        default: break;
    }
}

static void checkAccessors(const Mt43Data& data) {
    (void)data;   // 全カテゴリ無効では下の CHECK がすべて消える
#define CHECK_ACCESSOR(Type, Active) \
    CHECK((data.active_type == Mt43Data::ActiveType::Active) == (data.get<Type>() != nullptr))
#if (AZARAC_ENABLE_EEW)
    CHECK_ACCESSOR(EewData, Eew);
#endif
#if (AZARAC_ENABLE_HYPOCENTER)
    CHECK_ACCESSOR(HypocenterData, Hypocenter);
#endif
#if (AZARAC_ENABLE_SEISMIC)
    CHECK_ACCESSOR(SeismicData, Seismic);
#endif // AZARAC_ENABLE_SEISMIC
#if (AZARAC_ENABLE_NANKAI)
    CHECK_ACCESSOR(NankaiData, Nankai);
#endif
#if (AZARAC_ENABLE_TSUNAMI)
    CHECK_ACCESSOR(TsunamiData, Tsunami);
#endif // AZARAC_ENABLE_TSUNAMI
#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)
    CHECK_ACCESSOR(NwPacTsunamiData, NwPacTsunami);
#endif // AZARAC_ENABLE_NW_PAC_TSUNAMI
#if (AZARAC_ENABLE_VOLCANO)
    CHECK_ACCESSOR(VolcanoData, Volcano);
#endif // AZARAC_ENABLE_VOLCANO
#if (AZARAC_ENABLE_ASH_FALL)
    CHECK_ACCESSOR(AshFallData, AshFall);
#endif // AZARAC_ENABLE_ASH_FALL
#if (AZARAC_ENABLE_WEATHER)
    CHECK_ACCESSOR(WeatherData, Weather);
#endif // AZARAC_ENABLE_WEATHER
#if (AZARAC_ENABLE_FLOOD)
    CHECK_ACCESSOR(FloodData, Flood);
#endif // AZARAC_ENABLE_FLOOD
#if (AZARAC_ENABLE_TYPHOON)
    CHECK_ACCESSOR(TyphoonData, Typhoon);
#endif // AZARAC_ENABLE_TYPHOON
#if (AZARAC_ENABLE_MARINE)
    CHECK_ACCESSOR(MarineData, Marine);
#endif // AZARAC_ENABLE_MARINE
#undef CHECK_ACCESSOR
}

} // namespace

TEST_CASE("Mt43Data: コピーコンストラクタ - 全12型") {
    // 全 ActiveType でコピー後の型が一致し、他型アクセスのみ nullptr を返す（型安全性）
    for (auto type : kPayloadTypes) {
        Mt43Data orig;
        initAsType(orig, type);
        CHECK(orig.active_type == type);
        setSentinel(orig);

        Mt43Data copied(orig);
        CHECK(copied.active_type == type);
        checkSentinel(copied);
        checkAccessors(copied);
    }
}

#if (AZARAC_ENABLE_HYPOCENTER)
TEST_CASE("Mt43Data: コピーコンストラクタ - 深いコピー") {
    // コピー先を変更しても元データに影響しないことの確認
    Mt43Data orig;
    orig.initAs<HypocenterData>();
    HypocenterData* h = orig.getHypocenter();
    REQUIRE(h != nullptr);
    h->depth = 500;
    h->magnitude = 70;
    h->epicenter = 12345;

    Mt43Data copied(orig);
    HypocenterData* h2 = copied.getHypocenter();
    REQUIRE(h2 != nullptr);
    CHECK(h2->depth == 500);
    CHECK(h2->magnitude == 70);
    CHECK(h2->epicenter == 12345);

    h2->depth = 999;
    CHECK(h->depth == 500);
}
#endif // AZARAC_ENABLE_HYPOCENTER

#if (AZARAC_ENABLE_EEW) && (AZARAC_ENABLE_TYPHOON)
TEST_CASE("Mt43Data: コピー代入演算子 - 代入先の元データが破棄される") {
    Mt43Data eew;
    eew.initAs<EewData>();
    Mt43Data typhoon;
    typhoon.initAs<TyphoonData>();
    setSentinel(typhoon);

    eew = typhoon;
    CHECK(eew.active_type == Mt43Data::ActiveType::Typhoon);
    CHECK(eew.getTyphoon() != nullptr);
    checkSentinel(eew);
    CHECK(eew.getEew() == nullptr);  // 型が変わったので nullptr

    eew = eew;
    CHECK(eew.active_type == Mt43Data::ActiveType::Typhoon);
    CHECK(eew.getTyphoon() != nullptr);
}
#endif // AZARAC_ENABLE_EEW && AZARAC_ENABLE_TYPHOON

TEST_CASE("Mt43Data: ムーブコンストラクタ - 全12型") {
    for (auto type : kPayloadTypes) {
        Mt43Data orig;
        initAsType(orig, type);
        CHECK(orig.active_type == type);
        setSentinel(orig);

        Mt43Data moved(std::move(orig));
        CHECK(moved.active_type == type);
        checkSentinel(moved);
        checkAccessors(moved);

        // ムーブ元は None
        CHECK(orig.active_type == Mt43Data::ActiveType::None);
    }
}

#if (AZARAC_ENABLE_EEW) && (AZARAC_ENABLE_TYPHOON)
TEST_CASE("Mt43Data: ムーブ代入演算子") {
    Mt43Data eew;
    eew.initAs<EewData>();
    REQUIRE(eew.getEew() != nullptr);

    Mt43Data typhoon;
    typhoon.initAs<TyphoonData>();
    setSentinel(typhoon);

    eew = std::move(typhoon);
    CHECK(eew.active_type == Mt43Data::ActiveType::Typhoon);
    CHECK(eew.getTyphoon() != nullptr);
    checkSentinel(eew);
    CHECK(eew.getEew() == nullptr);
    // ムーブ元は None
    CHECK(typhoon.active_type == Mt43Data::ActiveType::None);
}
#endif // AZARAC_ENABLE_EEW && AZARAC_ENABLE_TYPHOON

#if (AZARAC_ENABLE_TYPHOON) && (AZARAC_ENABLE_VOLCANO) && (AZARAC_ENABLE_MARINE)
TEST_CASE("Mt43Data: 型切り替えでデストラクタが呼ばれる") {
    Mt43Data data;
    data.initAs<TyphoonData>();
    CHECK(data.getTyphoon() != nullptr);

    // destroyActive 経由で旧型のデストラクタが呼ばれる
    data.initAs<VolcanoData>();
    CHECK(data.active_type == Mt43Data::ActiveType::Volcano);
    CHECK(data.getVolcano() != nullptr);
    CHECK(data.getTyphoon() == nullptr);

    data.initAs<MarineData>();
    CHECK(data.active_type == Mt43Data::ActiveType::Marine);
    CHECK(data.getMarine() != nullptr);
    CHECK(data.getVolcano() == nullptr);
}
#endif // AZARAC_ENABLE_TYPHOON && AZARAC_ENABLE_VOLCANO && AZARAC_ENABLE_MARINE

TEST_CASE("Mt43Data: None のコピー/ムーブは安全") {
    Mt43Data empty;
    CHECK(empty.active_type == Mt43Data::ActiveType::None);

    Mt43Data copied(empty);
    CHECK(copied.active_type == Mt43Data::ActiveType::None);

    Mt43Data moved(std::move(empty));
    CHECK(moved.active_type == Mt43Data::ActiveType::None);
}

// getMillis()のオーバーフロー対策テスト

TEST_CASE("getMillis: uint64_tを返す") {
    uint64_t ms = internal::getMillis();
    CHECK(ms > 0);
}

