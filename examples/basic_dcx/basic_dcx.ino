// MT=44（DCX / CAMF: L-Alert・J-Alert・地方自治体・国外）を表示する例。
// MT=43 の DCR は basic_nmea / basic_ubx を参照。
//
// MT=44 は定義表だけで約 100 KB あるため、既定では AVR プリセット（SEISMIC/TSUNAMI）で無効です。
// 有効化するには -DAZARAC_ENABLE_DCX_CAMF=1（AVR の大型品は -DAZARAC_AVR_LARGE_FLASH=1）を
// ビルドフラグで指定してください（スケッチ冒頭の #define はライブラリ側の TU に届きません）。

#include <azaraC.h>

#if !AZARAC_ENABLE_DCX_CAMF
#error "examples/basic_dcx は DCX/CAMF を有効にしたビルドが必要です (-DAZARAC_ENABLE_DCX_CAMF=1)"
#endif

azaraC::Parser  parser;
azaraC::Message msg;

// GNSS から得た UNIX 時刻（SNTP / $GPRMC などで更新する）。0 は未解決。
uint32_t cached_gnss_unix_time = 0;

static const char* serviceName(azaraC::Mt44ServiceKind kind) {
    switch (kind) {
        case azaraC::Mt44ServiceKind::NullMessage:      return "null";
        case azaraC::Mt44ServiceKind::LAlert:           return "L-Alert";
        case azaraC::Mt44ServiceKind::JAlert:           return "J-Alert";
        case azaraC::Mt44ServiceKind::LocalGovernment:  return "LocalGov";
        case azaraC::Mt44ServiceKind::OutsideJapan:     return "OutsideJapan";
        default:                                        return "unknown";
    }
}

// microdegrees（×1,000,000）を "35.681236" の形で出す（浮動小数も整数の print も使わない）。
// 桁ごとに 1 文字ずつ出すのは、int が 16 bit の AVR でも 6 桁の小数部を安全に扱うため。
static void printMicrodeg(Print& out, int32_t microdeg) {
    if (microdeg < 0) {
        out.print('-');
        microdeg = -microdeg;
    }
    int32_t whole = microdeg / 1000000;
    const int32_t frac = microdeg % 1000000;

    char digits[4];
    uint8_t n = 0;
    do {
        digits[n++] = static_cast<char>('0' + (whole % 10));
        whole /= 10;
    } while (whole != 0 && n < sizeof(digits));
    while (n > 0) out.print(digits[--n]);

    out.print('.');
    for (int32_t div = 100000; div > 0; div /= 10) {
        out.print(static_cast<char>('0' + (frac / div) % 10));
    }
}

// JSON ではなく、人が読むための 1 行要約。
static void printSummary(const azaraC::Message& m) {
    const azaraC::Mt44Data* d = m.getMt44();
    if (!d) return;

    Serial.print(F("[MT44] svid="));
    Serial.print(m.svid);
    Serial.print(F(" service="));
    Serial.print(serviceName(d->service_kind));
    Serial.print(F(" a1="));
    Serial.print(d->camf.a1);
    Serial.print(F(" a2="));
    Serial.print(d->camf.a2);
    Serial.print(F(" a3="));
    Serial.print(d->camf.a3);

    if (d->mt44_decoded.main_ellipse_present) {
        Serial.print(F(" center="));
        printMicrodeg(Serial, d->mt44_decoded.main_ellipse.lat_microdeg);
        Serial.print(',');
        printMicrodeg(Serial, d->mt44_decoded.main_ellipse.lon_microdeg);
        Serial.print(F(" radius_km="));
        Serial.print(static_cast<int>(d->mt44_decoded.main_ellipse.semi_major_m / 1000));
    }
    if (d->service_kind == azaraC::Mt44ServiceKind::JAlert) {
        Serial.print(F(" prefectures="));
        Serial.print(static_cast<int>(d->mt44_decoded.prefecture_count));
        Serial.print(F(" cities="));
        Serial.print(static_cast<int>(d->mt44_decoded.city_code_count));
    }
    Serial.println();
}

void setup() {
#if defined(ARDUINO_ARCH_AVR)
    Serial.begin(9600);   // AVR: GNSS と JSON 出力が同じ UART（basic_uno と同じ制約）
#else
    Serial.begin(115200);
#endif
    uint32_t start = millis();
    while (!Serial && (millis() - start < 5000)) { delay(10); }

#if defined(ARDUINO_ESP32C3_DEV) || defined(CONFIG_IDF_TARGET_ESP32C3)
    Serial1.begin(9600, SERIAL_8N1, /*rx=*/4, /*tx=*/5);
#elif defined(CONFIG_IDF_TARGET_ESP32C6) || defined(ARDUINO_ESP32C6_DEV)
    Serial1.begin(9600, SERIAL_8N1, /*rx=*/4, /*tx=*/5);
#elif defined(ESP32)
    Serial1.begin(9600, SERIAL_8N1, /*rx=*/16, /*tx=*/17);
#elif !defined(ARDUINO_ARCH_AVR)
    Serial1.begin(9600, SERIAL_8N1);
#endif

    Serial.println(F("[azaraC] MT=44 (DCX/CAMF) ready"));
}

void loop() {
    parser.updateClock();

#if defined(ARDUINO_ARCH_AVR)
    Stream& gnss = Serial;
#else
    Stream& gnss = Serial1;
#endif

    while (gnss.available()) {
        const uint8_t b = static_cast<uint8_t>(gnss.read());
        if (!parser.feed(b, msg, cached_gnss_unix_time)) continue;

        if (msg.msg_type == 44) {
            printSummary(msg);
        }
        azaraC::toJson(msg, Serial);
        Serial.println();
    }
}
