// MT=44 DCX / CAMF デコーダ (IS-QZSS-DCX-004) EWSS CAMF v1.2 (B1-B4)

#include "Decoder.h"
#include "internal/DcxHelper.h"

namespace azaraC {
namespace internal {

#if (AZARAC_ENABLE_DCX_CAMF)

// A6/A7（週の先頭からの分、A7 = 1..10080）を週頭からの秒数へ。32 bit で計算する:
// AVR の unsigned int は 16 bit で、10079*60 = 604,740 は 65,535 を超える（a7 >= 1094 で onset が黙って週内の別時刻になる）。
// ホストの int は 32 bit なので、この static_assert は AVR ビルドでのみ意味を持つ。
static constexpr uint32_t onsetOffsetSec(uint16_t a7) {
    return static_cast<uint32_t>(a7 - 1u) * 60u;
}
static_assert(onsetOffsetSec(10080) == 604740u,
              "onset offset must be computed in 32 bits (AVR unsigned int is 16-bit)");

bool Decoder::decodeDcx(const uint8_t* bits, Message& out, uint32_t report_unix) {
    out.initPayload<Mt44Data>();
    Mt44Data* d = out.getMt44();
    if (!d) return false;

    d->service_kind = Mt44ServiceKind::Unknown;
    d->is_null_message = false;
    d->ex_kind = ExtendedKind::None;

    d->sd.sdmt = getBits(bits, 14, 1);
    d->sd.sdm  = getBits(bits, 15, 9);

    d->camf.a1  = getBits(bits, 24, 2);
    d->camf.a2  = getBits(bits, 26, 9);
    d->camf.a3  = getBits(bits, 35, 5);
    d->camf.a4  = getBits(bits, 40, 7);
    d->camf.a5  = getBits(bits, 47, 2);
    d->camf.a6  = getBits(bits, 49, 1);
    d->camf.a7  = getBits(bits, 50, 14);
    d->camf.a8  = getBits(bits, 64, 2);
    d->camf.a9  = getBits(bits, 66, 1);
    d->camf.a10 = getBits(bits, 67, 3);
    d->camf.a11 = getBits(bits, 70, 10);
    // A12/A13: 式で復号する unsigned コード（2 の補数ではない）
    d->camf.a12 = getBits(bits, 80, 16);
    d->camf.a13 = getBits(bits, 96, 17);
    d->camf.a14 = getBits(bits, 113, 5);
    d->camf.a15 = getBits(bits, 118, 5);
    d->camf.a16 = getBits(bits, 123, 6);
    d->camf.a17 = getBits(bits, 129, 2);
    d->camf.a18 = getBits(bits, 131, 15);

    d->camf.b1_present = false;

    d->camf.b2_present = false;
    d->camf.b2_c5 = 0;
    d->camf.b2_c6 = 0;

    d->camf.b3_present = false;
    d->camf.b3_c7 = 0;
    d->camf.b3_c8 = 0;
    d->camf.b3_c9 = 0;
    d->camf.b3_c10 = 0;

    // Null Message 検査 (IS-QZSS-DCX-004 §4.3): A1=0, A2=111, A3=0, A4–A18=0, 拡張=0。
    if (d->camf.a1 == 0 && d->camf.a2 == DCX_COUNTRY_CODE_JAPAN && d->camf.a3 == 0 &&
        d->camf.a4 == 0 && d->camf.a5 == 0 && d->camf.a6 == 0 &&
        d->camf.a7 == 0 && d->camf.a8 == 0 && d->camf.a9 == 0 &&
        d->camf.a10 == 0 && d->camf.a11 == 0 &&
        d->camf.a12 == 0 && d->camf.a13 == 0 && d->camf.a14 == 0 &&
        d->camf.a15 == 0 && d->camf.a16 == 0 && d->camf.a17 == 0 &&
        d->camf.a18 == 0) {
        // 拡張メッセージ部分もすべて 0 であること（bit 146..219 = 74 bit）。
        uint32_t ex_part1 = getBits(bits, 146, 32);  // bits 146..177
        uint32_t ex_part2 = getBits(bits, 178, 32);  // bits 178..209
        uint32_t ex_part3 = getBits(bits, 210, 10);  // bits 210..219
        if (ex_part1 == 0 && ex_part2 == 0 && ex_part3 == 0) {
            d->is_null_message = true;
            d->service_kind = Mt44ServiceKind::NullMessage;
            d->ex_kind = ExtendedKind::None;
            out.valid = true;
            return true;
        }
    }

    // 発現時刻: A6（0 = 今週, 1 = 翌週）+ A7（14 bit、1 分刻み）で 15 bit を成し、最大 2 週先まで表せる。
    // IS-QZSS-DCX-004 §4.2.3.6, Table 4.2-9（A6=0 は今週、A6=1 は翌週）/ §4.2.3.7, Table 4.2-10（週は月曜 00:00 UTC に始まり日曜 23:59 UTC に終わる）/ EWSS CAMF v1.2 §3.3。
    if (d->camf.a7 > 0 && d->camf.a7 <= 10080 && report_unix >= 946684800u) {
        // 1970-01-01 は木曜なので (days + 3) % 7 が 0=月 … 6=日になる。
        // report_unix を含む週の月曜 00:00 UTC を求める。
        uint32_t days        = report_unix / 86400u;
        uint32_t dow         = (days + 3u) % 7u;   // 0=Mon, …, 6=Sun
        uint32_t monday_days = days - dow;

        if (d->camf.a6 == 1) {
            monday_days += 7u;  // 翌週
        }

        uint32_t monday_unix = monday_days * 86400u;
        uint32_t onset_unix  = monday_unix + onsetOffsetSec(d->camf.a7);
        d->onset_time.unix_time = onset_unix;

        uint32_t y, m, day_val;
        Decoder::civil_from_days(onset_unix / 86400u, y, m, day_val);
        d->onset_time.month  = m;
        d->onset_time.day    = day_val;
        d->onset_time.hour   = ((d->camf.a7 - 1u) % 1440u) / 60u;
        d->onset_time.minute = (d->camf.a7 - 1u) % 60u;
    }

    if (d->camf.a2 != DCX_COUNTRY_CODE_JAPAN) {
        d->service_kind = Mt44ServiceKind::OutsideJapan;
        d->ex_kind = ExtendedKind::OutsideJapan;
    } else {
        if (d->camf.a3 == 2 || d->camf.a3 == 3) {
            // A3=2: J-Alert（消防庁/FDMA）、A3=3: J-Alert（関係省庁/Related Ministries）— IS-QZSS-DCX-004 §4.2.3.3 Table 4.2-6
            d->service_kind = Mt44ServiceKind::JAlert;
            d->ex_kind = ExtendedKind::JAlert;
        } else if (d->camf.a3 == 1) {
            d->service_kind = Mt44ServiceKind::LAlert;
            d->ex_kind = ExtendedKind::LAlertOrLocal;
        } else if (d->camf.a3 == 4) {
            // A3=4: 地方公共団体。A3=5-31 は予約のため Unknown — 同 Table 4.2-6
            d->service_kind = Mt44ServiceKind::LocalGovernment;
            d->ex_kind = ExtendedKind::LAlertOrLocal;
        } else {
            d->service_kind = Mt44ServiceKind::Unknown;
            d->ex_kind = ExtendedKind::None;
        }
    }

    if (d->ex_kind == ExtendedKind::LAlertOrLocal) {
        d->ex.ex_lalert_local.ex1 = getBits(bits, 146, 16);
        d->ex.ex_lalert_local.ex2 = getBits(bits, 162, 1);
        // EX3/EX4: 式で復号する unsigned コード（緯度・経度。2 の補数ではない）
        d->ex.ex_lalert_local.ex3 = getBits(bits, 163, 17);
        d->ex.ex_lalert_local.ex4 = getBits(bits, 180, 17);
        d->ex.ex_lalert_local.ex5 = getBits(bits, 197, 5);
        d->ex.ex_lalert_local.ex6 = getBits(bits, 202, 5);
        d->ex.ex_lalert_local.ex7 = getBits(bits, 207, 7);
        d->ex.ex_lalert_local.vn  = getBits(bits, 214, 6);
    } else if (d->ex_kind == ExtendedKind::JAlert) {
        d->ex.ex_jalert.ex8  = getBits(bits, 146, 1);
        uint32_t ex9_hi = getBits(bits, 147, 32);
        uint32_t ex9_lo = getBits(bits, 179, 32);
        d->ex.ex_jalert.ex9  = ((uint64_t)ex9_hi << 32) | ex9_lo;
        d->ex.ex_jalert.ex10 = getBits(bits, 211, 3);
        d->ex.ex_jalert.vn   = getBits(bits, 214, 6);
    } else if (d->ex_kind == ExtendedKind::OutsideJapan) {
        for (int i = 0; i < 8; ++i) {
            d->ex.ex_outside.ex11_raw[i] = getBits(bits, 146 + i * 8, 8);
        }
        d->ex.ex_outside.ex11_raw[8] = getBits(bits, 210, 4) << 4;  // 残り 4 bit
        d->ex.ex_outside.vn = getBits(bits, 214, 6);
    }

    // 復号済み構造を埋める（主楕円は DCX-004 §4.2.3.12–16、B1–B4 は EWSS CAMF v1.2 §3.7）

    Mt44Decoded& dec = d->mt44_decoded;
    dec.main_ellipse_present = false;
    dec.jalert_prefecture_mode = false;
    dec.prefecture_count = 0;
    dec.city_code_count = 0;
    dec.additional_area.present = false;

    // 主楕円 (A12-A16): A12..A16 のいずれかが非 0 なら存在
    bool has_main_ellipse = (d->camf.a12 != 0 || d->camf.a13 != 0 ||
                             d->camf.a14 != 0 || d->camf.a15 != 0 ||
                             d->camf.a16 != 0);
    if (has_main_ellipse) {
        dec.main_ellipse_present = true;
        dec.main_ellipse.lat_microdeg = decodeLatitude16(d->camf.a12);
        dec.main_ellipse.lon_microdeg = decodeLongitude17(d->camf.a13);
        dec.main_ellipse.semi_major_m = decodeRadiusCode(d->camf.a14);
        dec.main_ellipse.semi_minor_m = decodeRadiusCode(d->camf.a15);
        dec.main_ellipse.azimuth_decideg = decodeAzimuth6(d->camf.a16);

        // B1 (A17=00) - Improved Resolution of Main Ellipse (EWSS CAMF v1.2 §3.7.1) A18 (15bit) = C1(3bit)[12:14] + C2(3bit)[9:11] + C3(3bit)[6:8] + C4(3bit)[3:5] + Reserved(3bit)[0:2]
        if (d->camf.a17 == 0) {
            B1Refinement b1 = decodeB1Refinement(d->camf.a18);
            d->camf.b1_present = (b1.c1 != 0 || b1.c2 != 0 || b1.c3 != 0 || b1.c4 != 0);

            // 精細化した値を復号済み楕円へ格納する（EWSS CAMF v1.2 §3.7.1.3/4）。
            // 半径の倍率: C3 → 長半径（A14）、C4 → 短半径（A15）。
            dec.main_ellipse.b1_lat_offset_microdeg = b1RefinedLatitudeOffset(b1.c1);
            dec.main_ellipse.b1_lon_offset_microdeg = b1RefinedLongitudeOffset(b1.c2);
            dec.main_ellipse.b1_refined_semi_major_m = b1RefinedRadiusM(
                b1.c3, dec.main_ellipse.semi_major_m, d->camf.a14);
            dec.main_ellipse.b1_refined_semi_minor_m = b1RefinedRadiusM(
                b1.c4, dec.main_ellipse.semi_minor_m, d->camf.a15);
        }
        // B2 (A17=01) - Position of the Centre of the Hazard (EWSS CAMF v1.2 §3.7.2) C5: spec bits 131-137; C6: spec bits 138-144; Reserved: a18[0]
        else if (d->camf.a17 == 1) {
            uint8_t c5 = (d->camf.a18 >> 8) & 0x7F;  // spec bits[131:137] → a18[14:8]
            uint8_t c6 = (d->camf.a18 >> 1) & 0x7F;  // spec bits[138:144] → a18[7:1]
            B2HazardCenter b2 = decodeB2HazardCenter(c5, c6);
            d->camf.b2_present = true;
            d->camf.b2_c5 = c5;
            d->camf.b2_c6 = c6;
            dec.b2_hazard_lat_microdeg = dec.main_ellipse.lat_microdeg + b2.delta_lat_microdeg;
            dec.b2_hazard_lon_microdeg = dec.main_ellipse.lon_microdeg + b2.delta_lon_microdeg;
            // dec.main_ellipse は変更しない（元の楕円中心を維持）
        }
        // B3 (A17=10) - Secondary Ellipse Definition (EWSS CAMF v1.2 §3.7.3) C7: spec bits 131-132; C8: 133-135; C9: 136-140; C10: 141-145
        else if (d->camf.a17 == 2) {
            uint8_t c7  = (d->camf.a18 >> 13) & 0x03;  // spec bits[131:132] → a18[14:13]
            uint8_t c8  = (d->camf.a18 >> 10) & 0x07;  // spec bits[133:135] → a18[12:10]
            uint8_t c9  = (d->camf.a18 >> 5)  & 0x1F;  // spec bits[136:140] → a18[9:5]
            uint8_t c10 = (d->camf.a18 >> 0)  & 0x1F;  // spec bits[141:145] → a18[4:0]
            d->camf.b3_present = true;
            d->camf.b3_c7 = c7;
            d->camf.b3_c8 = c8;
            d->camf.b3_c9 = c9;
            d->camf.b3_c10 = c10;
        }
    }
    // B4 (A17=11) - Quantitative and Detailed Information (EWSS CAMF v1.2 §3.7.4)。
    // B4 の詳細 D1–D36 は JsonSerializerDcx.cpp 側で復号する。
    if (d->camf.a17 == 3) {
        d->camf.b4_present = true;
    }

    if (d->ex_kind == ExtendedKind::LAlertOrLocal) {
        // 追加地域（地方公共団体のみ）: EX2-EX7
        if (d->service_kind == Mt44ServiceKind::LocalGovernment) {
            bool has_additional = (d->ex.ex_lalert_local.ex2 != 0 ||
                                   d->ex.ex_lalert_local.ex3 != 0 ||
                                   d->ex.ex_lalert_local.ex4 != 0 ||
                                   d->ex.ex_lalert_local.ex5 != 0 ||
                                   d->ex.ex_lalert_local.ex6 != 0 ||
                                   d->ex.ex_lalert_local.ex7 != 0);
            if (has_additional) {
                dec.additional_area.present = true;
                dec.additional_area.head_to_area = (d->ex.ex_lalert_local.ex2 != 0);
                dec.additional_area.ellipse.lat_microdeg = decodeLatitude17(d->ex.ex_lalert_local.ex3);
                dec.additional_area.ellipse.lon_microdeg = decodeLongitude17_45_225(d->ex.ex_lalert_local.ex4);
                dec.additional_area.ellipse.semi_major_m = decodeRadiusCode(d->ex.ex_lalert_local.ex5);
                dec.additional_area.ellipse.semi_minor_m = decodeRadiusCode(d->ex.ex_lalert_local.ex6);
                dec.additional_area.ellipse.azimuth_decideg = decodeAzimuth7(d->ex.ex_lalert_local.ex7);
            }
        }
    } else if (d->ex_kind == ExtendedKind::JAlert) {
        dec.jalert_prefecture_mode = (d->ex.ex_jalert.ex8 == 0);
        if (dec.jalert_prefecture_mode) {
            dec.prefecture_count = decodePrefectureBitmask(d->ex.ex_jalert.ex9, dec.prefecture_positions);
        } else {
            dec.city_code_count = decodeCityCodeList(d->ex.ex_jalert.ex9, dec.city_codes);
        }
    }

    out.valid = true;
    return true;
}

#endif // AZARAC_ENABLE_DCX_CAMF

} // namespace internal
} // namespace azaraC
