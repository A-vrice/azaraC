// test/core/test_message_struct.cpp
// Message構造体の安全なタグ付き共用体テスト

#define ARDUINO 0
#include <utility>
#include "../test_helpers.h"
#include "doctest.h"
#include "../src/internal/TimeFields.h"

using namespace azaraC;

// ── Message構造体のテスト ──────────────────────────────────────────────────

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

TEST_CASE("Message: コピーコンストラクタ") {
    Message msg1;
    msg1.svid = 184;
    msg1.msg_type = 43;
    msg1.crc24 = 0x123456;
    msg1.valid = true;
    msg1.initPayload<Mt43Data>();

    Message msg2(msg1);
    CHECK(msg2.svid == 184);
    CHECK(msg2.msg_type == 43);
    CHECK(msg2.crc24 == 0x123456);
    CHECK(msg2.valid == true);
    CHECK(msg2.payload_type == MsgPayloadType::Mt43);
    CHECK(msg2.getMt43() != nullptr);
}

TEST_CASE("Message: コピー代入演算子") {
    Message msg1;
    msg1.svid = 185;
    msg1.msg_type = 44;
    msg1.crc24 = 0x654321;
    msg1.valid = true;
    msg1.initPayload<Mt44Data>();

    Message msg2;
    msg2 = msg1;
    CHECK(msg2.svid == 185);
    CHECK(msg2.msg_type == 44);
    CHECK(msg2.crc24 == 0x654321);
    CHECK(msg2.valid == true);
    CHECK(msg2.payload_type == MsgPayloadType::Mt44);
    CHECK(msg2.getMt44() != nullptr);
}

TEST_CASE("Message: ムーブコンストラクタ") {
    Message msg1;
    msg1.svid = 186;
    msg1.msg_type = 43;
    msg1.crc24 = 0xABCDEF;
    msg1.valid = true;
    msg1.initPayload<Mt43Data>();

    Message msg2(std::move(msg1));
    CHECK(msg2.svid == 186);
    CHECK(msg2.msg_type == 43);
    CHECK(msg2.crc24 == 0xABCDEF);
    CHECK(msg2.valid == true);
    CHECK(msg2.payload_type == MsgPayloadType::Mt43);
    CHECK(msg2.getMt43() != nullptr);
}

TEST_CASE("Message: ムーブ代入演算子") {
    Message msg1;
    msg1.svid = 187;
    msg1.msg_type = 44;
    msg1.crc24 = 0xFEDCBA;
    msg1.valid = true;
    msg1.initPayload<Mt44Data>();

    Message msg2;
    msg2 = std::move(msg1);
    CHECK(msg2.svid == 187);
    CHECK(msg2.msg_type == 44);
    CHECK(msg2.crc24 == 0xFEDCBA);
    CHECK(msg2.valid == true);
    CHECK(msg2.payload_type == MsgPayloadType::Mt44);
    CHECK(msg2.getMt44() != nullptr);
}

// ── Mt43Dataの安全なタグ付き共用体のテスト ──────────────────────────────────

TEST_CASE("Mt43Data: デフォルトコンストラクタ") {
    Mt43Data data;
    CHECK(data.report_classification == 0);
    CHECK(data.disaster_category == 0);
    CHECK(data.information_type == 0);
    CHECK(data.active_type == Mt43Data::ActiveType::None);
}

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
    CHECK(eew->region_count == 0);

    CHECK(data.getHypocenter() == nullptr);
    CHECK(data.getSeismic() == nullptr);
#if (AZARAC_ENABLE_NANKAI)
    CHECK(data.getNankai() == nullptr);
#endif
}

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

TEST_CASE("Mt43Data: コピーコンストラクタ - 全12型") {
    // 各 ActiveType に対してコピーコンストラクタが正しく動作することを検証
    // コピー先の型が正しく、nullptr が適切に返ることを確認（型安全性）
    struct TypeInfo { Mt43Data::ActiveType type; const char* name; };
    TypeInfo types[] = {
        {Mt43Data::ActiveType::Eew,          "Eew"},
        {Mt43Data::ActiveType::Hypocenter,   "Hypocenter"},
        {Mt43Data::ActiveType::Seismic,      "Seismic"},
#if (AZARAC_ENABLE_NANKAI)
        {Mt43Data::ActiveType::Nankai,       "Nankai"},
#endif
        {Mt43Data::ActiveType::Tsunami,      "Tsunami"},
        {Mt43Data::ActiveType::NwPacTsunami, "NwPac"},
        {Mt43Data::ActiveType::Volcano,      "Volcano"},
        {Mt43Data::ActiveType::AshFall,      "AshFall"},
        {Mt43Data::ActiveType::Weather,      "Weather"},
        {Mt43Data::ActiveType::Flood,        "Flood"},
        {Mt43Data::ActiveType::Typhoon,      "Typhoon"},
        {Mt43Data::ActiveType::Marine,       "Marine"},
    };

    for (auto t : types) {
        Mt43Data orig;
        // initAs を使って適切な型で初期化
        switch (t.type) {
            case Mt43Data::ActiveType::Eew:          orig.initAs<EewData>(); break;
            case Mt43Data::ActiveType::Hypocenter:   orig.initAs<HypocenterData>(); break;
            case Mt43Data::ActiveType::Seismic:      orig.initAs<SeismicData>(); break;
#if (AZARAC_ENABLE_NANKAI)
            case Mt43Data::ActiveType::Nankai:       orig.initAs<NankaiData>(); break;
#endif
            case Mt43Data::ActiveType::Tsunami:      orig.initAs<TsunamiData>(); break;
            case Mt43Data::ActiveType::NwPacTsunami: orig.initAs<NwPacTsunamiData>(); break;
            case Mt43Data::ActiveType::Volcano:      orig.initAs<VolcanoData>(); break;
            case Mt43Data::ActiveType::AshFall:      orig.initAs<AshFallData>(); break;
            case Mt43Data::ActiveType::Weather:      orig.initAs<WeatherData>(); break;
            case Mt43Data::ActiveType::Flood:        orig.initAs<FloodData>(); break;
            case Mt43Data::ActiveType::Typhoon:      orig.initAs<TyphoonData>(); break;
            case Mt43Data::ActiveType::Marine:       orig.initAs<MarineData>(); break;
            default: break;
        }
        CHECK(orig.active_type == t.type);

        // コピー構築
        Mt43Data copied(orig);
        CHECK(copied.active_type == t.type);

        // コピー先の正しい型へのアクセスが非nullであること
        switch (t.type) {
            case Mt43Data::ActiveType::Eew:          CHECK(copied.get<EewData>()          != nullptr); break;
            case Mt43Data::ActiveType::Hypocenter:   CHECK(copied.get<HypocenterData>()   != nullptr); break;
            case Mt43Data::ActiveType::Seismic:      CHECK(copied.get<SeismicData>()      != nullptr); break;
#if (AZARAC_ENABLE_NANKAI)
            case Mt43Data::ActiveType::Nankai:       CHECK(copied.get<NankaiData>()       != nullptr); break;
#endif
            case Mt43Data::ActiveType::Tsunami:      CHECK(copied.get<TsunamiData>()      != nullptr); break;
            case Mt43Data::ActiveType::NwPacTsunami: CHECK(copied.get<NwPacTsunamiData>() != nullptr); break;
            case Mt43Data::ActiveType::Volcano:      CHECK(copied.get<VolcanoData>()      != nullptr); break;
            case Mt43Data::ActiveType::AshFall:      CHECK(copied.get<AshFallData>()      != nullptr); break;
            case Mt43Data::ActiveType::Weather:      CHECK(copied.get<WeatherData>()      != nullptr); break;
            case Mt43Data::ActiveType::Flood:        CHECK(copied.get<FloodData>()        != nullptr); break;
            case Mt43Data::ActiveType::Typhoon:      CHECK(copied.get<TyphoonData>()      != nullptr); break;
            case Mt43Data::ActiveType::Marine:       CHECK(copied.get<MarineData>()       != nullptr); break;
            default: break;
        }

        // 異なる型へのアクセスがnullptrであること（型安全性の確認）
        // Eew 以外の型では getEew() が nullptr を返すべき、など
        if (t.type != Mt43Data::ActiveType::Eew)          CHECK(copied.get<EewData>()          == nullptr);
        if (t.type != Mt43Data::ActiveType::Hypocenter)   CHECK(copied.get<HypocenterData>()   == nullptr);
        if (t.type != Mt43Data::ActiveType::Seismic)      CHECK(copied.get<SeismicData>()      == nullptr);
#if (AZARAC_ENABLE_NANKAI)
        if (t.type != Mt43Data::ActiveType::Nankai)       CHECK(copied.get<NankaiData>()       == nullptr);
#endif
        if (t.type != Mt43Data::ActiveType::Tsunami)      CHECK(copied.get<TsunamiData>()      == nullptr);
        if (t.type != Mt43Data::ActiveType::NwPacTsunami) CHECK(copied.get<NwPacTsunamiData>() == nullptr);
        if (t.type != Mt43Data::ActiveType::Volcano)      CHECK(copied.get<VolcanoData>()      == nullptr);
        if (t.type != Mt43Data::ActiveType::AshFall)      CHECK(copied.get<AshFallData>()      == nullptr);
        if (t.type != Mt43Data::ActiveType::Weather)      CHECK(copied.get<WeatherData>()      == nullptr);
        if (t.type != Mt43Data::ActiveType::Flood)        CHECK(copied.get<FloodData>()        == nullptr);
        if (t.type != Mt43Data::ActiveType::Typhoon)      CHECK(copied.get<TyphoonData>()      == nullptr);
        if (t.type != Mt43Data::ActiveType::Marine)       CHECK(copied.get<MarineData>()       == nullptr);
    }
}

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

    // コピー先を変更
    h2->depth = 999;
    // 元データは影響を受けない
    CHECK(h->depth == 500);
}

TEST_CASE("Mt43Data: コピー代入演算子 - 代入先の元データが破棄される") {
    Mt43Data eew;
    eew.initAs<EewData>();
    Mt43Data typhoon;
    typhoon.initAs<TyphoonData>();

    // Eew → Typhoon に代入。元の Eew が破棄される
    eew = typhoon;
    CHECK(eew.active_type == Mt43Data::ActiveType::Typhoon);
    CHECK(eew.getTyphoon() != nullptr);
    CHECK(eew.getEew() == nullptr);  // 型が変わったので nullptr

    // 自己代入
    eew = eew;
    CHECK(eew.active_type == Mt43Data::ActiveType::Typhoon);
    CHECK(eew.getTyphoon() != nullptr);
}

TEST_CASE("Mt43Data: ムーブコンストラクタ - 全12型") {
    struct TypeInfo { Mt43Data::ActiveType type; const char* name; };
    TypeInfo types[] = {
        {Mt43Data::ActiveType::Eew,          "Eew"},
        {Mt43Data::ActiveType::Hypocenter,   "Hypocenter"},
        {Mt43Data::ActiveType::Seismic,      "Seismic"},
#if (AZARAC_ENABLE_NANKAI)
        {Mt43Data::ActiveType::Nankai,       "Nankai"},
#endif
        {Mt43Data::ActiveType::Tsunami,      "Tsunami"},
        {Mt43Data::ActiveType::NwPacTsunami, "NwPac"},
        {Mt43Data::ActiveType::Volcano,      "Volcano"},
        {Mt43Data::ActiveType::AshFall,      "AshFall"},
        {Mt43Data::ActiveType::Weather,      "Weather"},
        {Mt43Data::ActiveType::Flood,        "Flood"},
        {Mt43Data::ActiveType::Typhoon,      "Typhoon"},
        {Mt43Data::ActiveType::Marine,       "Marine"},
    };

    for (auto t : types) {
        Mt43Data orig;
        switch (t.type) {
            case Mt43Data::ActiveType::Eew:          orig.initAs<EewData>(); break;
            case Mt43Data::ActiveType::Hypocenter:   orig.initAs<HypocenterData>(); break;
            case Mt43Data::ActiveType::Seismic:      orig.initAs<SeismicData>(); break;
#if (AZARAC_ENABLE_NANKAI)
            case Mt43Data::ActiveType::Nankai:       orig.initAs<NankaiData>(); break;
#endif
            case Mt43Data::ActiveType::Tsunami:      orig.initAs<TsunamiData>(); break;
            case Mt43Data::ActiveType::NwPacTsunami: orig.initAs<NwPacTsunamiData>(); break;
            case Mt43Data::ActiveType::Volcano:      orig.initAs<VolcanoData>(); break;
            case Mt43Data::ActiveType::AshFall:      orig.initAs<AshFallData>(); break;
            case Mt43Data::ActiveType::Weather:      orig.initAs<WeatherData>(); break;
            case Mt43Data::ActiveType::Flood:        orig.initAs<FloodData>(); break;
            case Mt43Data::ActiveType::Typhoon:      orig.initAs<TyphoonData>(); break;
            case Mt43Data::ActiveType::Marine:       orig.initAs<MarineData>(); break;
            default: break;
        }
        CHECK(orig.active_type == t.type);

        // ムーブ構築
        Mt43Data moved(std::move(orig));
        CHECK(moved.active_type == t.type);

        // ムーブ元は None になっている
        CHECK(orig.active_type == Mt43Data::ActiveType::None);

        // ムーブ先の正しい型へのアクセスが非nullであること
        switch (t.type) {
            case Mt43Data::ActiveType::Eew:          CHECK(moved.get<EewData>()          != nullptr); break;
            case Mt43Data::ActiveType::Hypocenter:   CHECK(moved.get<HypocenterData>()   != nullptr); break;
            case Mt43Data::ActiveType::Seismic:      CHECK(moved.get<SeismicData>()      != nullptr); break;
#if (AZARAC_ENABLE_NANKAI)
            case Mt43Data::ActiveType::Nankai:       CHECK(moved.get<NankaiData>()       != nullptr); break;
#endif
            case Mt43Data::ActiveType::Tsunami:      CHECK(moved.get<TsunamiData>()      != nullptr); break;
            case Mt43Data::ActiveType::NwPacTsunami: CHECK(moved.get<NwPacTsunamiData>() != nullptr); break;
            case Mt43Data::ActiveType::Volcano:      CHECK(moved.get<VolcanoData>()      != nullptr); break;
            case Mt43Data::ActiveType::AshFall:      CHECK(moved.get<AshFallData>()      != nullptr); break;
            case Mt43Data::ActiveType::Weather:      CHECK(moved.get<WeatherData>()      != nullptr); break;
            case Mt43Data::ActiveType::Flood:        CHECK(moved.get<FloodData>()        != nullptr); break;
            case Mt43Data::ActiveType::Typhoon:      CHECK(moved.get<TyphoonData>()      != nullptr); break;
            case Mt43Data::ActiveType::Marine:       CHECK(moved.get<MarineData>()       != nullptr); break;
            default: break;
        }

        // ムーブ先の異なる型は nullptr
        if (t.type != Mt43Data::ActiveType::Eew)          CHECK(moved.get<EewData>()          == nullptr);
        if (t.type != Mt43Data::ActiveType::Hypocenter)   CHECK(moved.get<HypocenterData>()   == nullptr);
        if (t.type != Mt43Data::ActiveType::Seismic)      CHECK(moved.get<SeismicData>()      == nullptr);
#if (AZARAC_ENABLE_NANKAI)
        if (t.type != Mt43Data::ActiveType::Nankai)       CHECK(moved.get<NankaiData>()       == nullptr);
#endif
    }
}

TEST_CASE("Mt43Data: ムーブ代入演算子") {
    Mt43Data eew;
    eew.initAs<EewData>();
    REQUIRE(eew.getEew() != nullptr);

    Mt43Data typhoon;
    typhoon.initAs<TyphoonData>();

    // Eew → Typhoon にムーブ代入
    eew = std::move(typhoon);
    CHECK(eew.active_type == Mt43Data::ActiveType::Typhoon);
    CHECK(eew.getTyphoon() != nullptr);
    CHECK(eew.getEew() == nullptr);
    // ムーブ元は None
    CHECK(typhoon.active_type == Mt43Data::ActiveType::None);
}

TEST_CASE("Mt43Data: 型切り替えでデストラクタが呼ばれる") {
    Mt43Data data;
    data.initAs<TyphoonData>();
    CHECK(data.getTyphoon() != nullptr);

    // 別の型に切り替え → Typhoon のデストラクタが呼ばれる (destroyActive経由)
    data.initAs<VolcanoData>();
    CHECK(data.active_type == Mt43Data::ActiveType::Volcano);
    CHECK(data.getVolcano() != nullptr);
    CHECK(data.getTyphoon() == nullptr);

    // もう一度切り替え
    data.initAs<MarineData>();
    CHECK(data.active_type == Mt43Data::ActiveType::Marine);
    CHECK(data.getMarine() != nullptr);
    CHECK(data.getVolcano() == nullptr);
}

TEST_CASE("Mt43Data: None のコピー/ムーブは安全") {
    Mt43Data empty;
    CHECK(empty.active_type == Mt43Data::ActiveType::None);

    // None からのコピー
    Mt43Data copied(empty);
    CHECK(copied.active_type == Mt43Data::ActiveType::None);

    // None からのムーブ
    Mt43Data moved(std::move(empty));
    CHECK(moved.active_type == Mt43Data::ActiveType::None);
}

// ── getMillis()のオーバーフロー対策テスト ────────────────────────────────────

TEST_CASE("getMillis: uint64_tを返す") {
    uint64_t ms = internal::getMillis();
    CHECK(ms > 0);
}

TEST_CASE("millisDiff: 正常な差分計算") {
    uint64_t prev = 1000;
    uint64_t curr = 5000;
    uint32_t diff = internal::millisDiff(curr, prev);
    CHECK(diff == 4000);
}

TEST_CASE("millisDiff: オーバーフロー後の差分計算") {
    uint64_t prev = 0xFFFFFFF0;
    uint64_t curr = 0x00000010;
    uint32_t diff = internal::millisDiff(curr, prev);
    CHECK(diff == 32);
}
