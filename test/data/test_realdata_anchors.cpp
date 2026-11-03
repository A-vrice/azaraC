// realdata の独立アンカー。
// test_realdata_generated.cpp の期待値は decode_to_json（azarashi 照合済みスナップショット）だが、
// 生成時点のデコーダ出力を固定するため、デコーダ自身の退行以外は検出できない。
// ここでは dcr_vectors.json / dcx_vectors.json の azarashi 期待値をハードコードし、
// 「実装に依存しない値」で主要フィールドを固定する。

#define ARDUINO 0
#include "../test_helpers.h"
#include "doctest.h"

using namespace azaraC;

#if (AZARAC_ENABLE_EEW)
TEST_CASE("Realdata anchor: EEW (azarashi)") {
    const char* nmea = "$QZQSM,58,9AAF899C80000324000039000548C5E2C000000003DFF8001C000012FE4B0FC*7F";
    Message msg{};
    REQUIRE(decodeNmea(nmea, msg, 0));
    CHECK(msg.msg_type == 43);
    CHECK(msg.svid == 186);

    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    CHECK(mt43->disaster_category == 1);
    CHECK(mt43->report_classification == 7);
    CHECK(mt43->information_type == 0);
    CHECK(mt43->version == 1);

    const EewData* eew = mt43->getEew();
    REQUIRE(eew != nullptr);
    CHECK(eew->depth == 10);
    CHECK(eew->magnitude == 72);
    CHECK(eew->epicenter == 791);
    CHECK(eew->intensity_lower == 8);
    CHECK(eew->intensity_upper == 11);
    REQUIRE(eew->notification_count == 1);
    CHECK(eew->notification[0] == 201);
}
#endif // AZARAC_ENABLE_EEW

#if (AZARAC_ENABLE_DCX_CAMF)
TEST_CASE("Realdata anchor: DCX Null (azarashi)") {
    const char* nmea = "$QZQSM,54,53B0840DE0000000000000000000000000000000000000000000000012ACBD4*0F";
    Message msg{};
    REQUIRE(decodeNmea(nmea, msg, 0));
    CHECK(msg.msg_type == 44);
    CHECK(msg.svid == 182);

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->service_kind == Mt44ServiceKind::NullMessage);
    CHECK(mt44->is_null_message);
    CHECK(mt44->camf.a1 == 0);
    CHECK(mt44->camf.a2 == 111);
    CHECK(mt44->camf.a3 == 0);
    CHECK(mt44->camf.a17 == 0);
    CHECK(mt44->camf.a18 == 0);
}

TEST_CASE("Realdata anchor: DCX L-Alert (azarashi)") {
    const char* nmea = "$QZQSM,54,53B0840DE100868FA0000000000000000000041B40000000000000124402A20*0D";
    Message msg{};
    REQUIRE(decodeNmea(nmea, msg, 0));
    CHECK(msg.msg_type == 44);
    CHECK(msg.svid == 182);

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->service_kind == Mt44ServiceKind::LAlert);
    CHECK(mt44->is_null_message == false);
    CHECK(mt44->camf.a1 == 0);
    CHECK(mt44->camf.a2 == 111);
    CHECK(mt44->camf.a3 == 1);
    CHECK(mt44->camf.a5 == 1);
    CHECK(mt44->ex.ex_lalert_local.vn == 1);
}

TEST_CASE("Realdata anchor: DCX J-Alert (azarashi)") {
    const char* nmea = "$QZQSM,55,9AB0840DE2BF88E9200000000000000000001FFFFFFFFFFFC00000110D0A1B8*71";
    Message msg{};
    REQUIRE(decodeNmea(nmea, msg, 0));
    CHECK(msg.msg_type == 44);
    CHECK(msg.svid == 183);

    const Mt44Data* mt44 = msg.getMt44();
    REQUIRE(mt44 != nullptr);
    CHECK(mt44->service_kind == Mt44ServiceKind::JAlert);
    CHECK(mt44->is_null_message == false);
    CHECK(mt44->camf.a2 == 111);
    CHECK(mt44->camf.a3 == 2);
    CHECK(mt44->camf.a4 == 95);
    CHECK(mt44->camf.a5 == 3);
    CHECK(mt44->camf.a9 == 1);
    CHECK(mt44->ex.ex_jalert.ex8 == 0);
    CHECK(mt44->ex.ex_jalert.ex9 == 18446744073709420544ULL);
    CHECK(mt44->ex.ex_jalert.vn == 1);
}
#endif // AZARAC_ENABLE_DCX_CAMF
