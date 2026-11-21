// realdata の独立アンカー。
// test_realdata_generated.cpp の期待値は decode_to_json（azarashi 照合済みスナップショット）だが、
// 生成時点のデコーダ出力を固定するため、デコーダ自身の退行以外は検出できない。
// ここでは dcr_vectors.json / dcx_vectors.json の azarashi 期待値をハードコードし、
// 「実装に依存しない値」で主要フィールドを固定する。

#define ARDUINO 0
#include "../test_helpers.h"
#include "../src/internal/PrintShim.h"
#include "../src/json/JsonSerializer.h"
#include "doctest.h"
#include <string>

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

#if (AZARAC_ENABLE_TSUNAMI)
// 津波（dc=5）の通知コードとラベルを azarashi の値で固定する。
// Table 4.1.2-21: Co_1..Co_3 = bit 53..79（9 bit × 3、0 終端）。
TEST_CASE("Realdata anchor: Tsunami notifications (azarashi)") {
    const char* nmea = "$QZQSM,58,9AAFA99C828001E8F67C31053960414E621053BE00000000000000132735038*0F";
    Message msg{};
    REQUIRE(decodeNmea(nmea, msg, 0));
    CHECK(msg.msg_type == 43);
    CHECK(msg.svid == 186);

    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    CHECK(mt43->disaster_category == 5);
    CHECK(mt43->report_classification == 7);   // 訓練/試験（仕様値 1/2/3/7 のいずれか）
    CHECK(mt43->version == 1);

    const TsunamiData* t = mt43->getTsunami();
    REQUIRE(t != nullptr);
    CHECK(t->warning_code == 3);
    REQUIRE(t->notification_count == 3);
    CHECK(t->notification[0] == 122);
    CHECK(t->notification[1] == 123);
    CHECK(t->notification[2] == 124);

    REQUIRE(t->count == 3);
    const uint16_t expected_regions[3] = {600, 610, 760};
    for (uint8_t i = 0; i < 3; ++i) {
        CHECK(t->entries[i].arrival_time_raw == 261);
        CHECK(t->entries[i].height_code == 3);
        CHECK(t->entries[i].region_code == expected_regions[i]);
    }

#if (AZARAC_ENABLE_EEW || AZARAC_ENABLE_HYPOCENTER || AZARAC_TSUNAMI_NOTIFICATION_LABELS)
    // 表が有効な構成（非 AVR 既定、または EEW/震源有効）ではラベルが解決する。
    StringPrint sp;
    internal::JsonSerializer::serialize(msg, sp);
    const std::string& s = sp.str();
#if AZARAC_LANG_JA
    CHECK(s.find("津波警報") != std::string::npos);
#endif
    CHECK(s.find("\"label\":null") == std::string::npos);
#endif // EEW || HYPOCENTER || AZARAC_TSUNAMI_NOTIFICATION_LABELS
}
#endif // AZARAC_ENABLE_TSUNAMI

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
    CHECK(mt44->camf.a7 <= 10080);   // A7 は仕様上 1..10080（週頭からの分）
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
    CHECK(mt44->camf.a7 <= 10080);   // A7 は仕様上 1..10080（週頭からの分）
    CHECK(mt44->ex.ex_jalert.ex8 == 0);
    CHECK(mt44->ex.ex_jalert.ex9 == 18446744073709420544ULL);
    CHECK(mt44->ex.ex_jalert.vn == 1);
}
#endif // AZARAC_ENABLE_DCX_CAMF
