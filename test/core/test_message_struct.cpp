// test/core/test_message_struct.cpp
// Message構造体の安全なタグ付き共用体テスト

#define ARDUINO 0
#include <utility>
#include "../test_helpers.h"
#include "doctest.h"

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
    CHECK(data.getNankai() == nullptr);
}

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

    data.initAs<NankaiData>();
    CHECK(data.active_type == Mt43Data::ActiveType::Nankai);
    CHECK(data.getNankai() != nullptr);
    CHECK(data.getEew() == nullptr);
}

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
