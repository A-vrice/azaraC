// azaraC — examples/basic_nmea/basic_nmea.ino
//
// NMEA $QZQSM (9600 baud) → JSON on Serial (USB)
//
// Wiring (ESP32-C3 DevKitM-1):
//   GNSS TX → GPIO20 (Serial1 RX)
//   GNSS RX → GPIO21 (Serial1 TX)  [optional, for config]
//   GND     → GND
//
// Tested with: u-blox M10 / ZED-F9P (L1S enabled), Furuno GT-87

// Arduino Uno (AVR) 互換: Serial1 がなく（ハードウェア UART はピン 0/1 の Serial のみ）、GNSS モジュールと JSON 出力が同じポートを共用する。この共用 UART 経路はコンパイル/リンク検証用で、実際に GNSS を繋ぐ場合は SoftwareSerial か、2 つ目の UART を持つボード（例: Mega の Serial1）を使うこと。そうしないと Serial に書いた JSON が GNSS モジュールにも送られる。32KB フラッシュ向けのカテゴリ削減は azaraC_config.h が自動で適用する（AVR プリセットは SEISMIC/TSUNAMI のみ残す）。
#include <azaraC.h>


azaraC::Parser  parser;
azaraC::Message msg;

// (TinyGPS++等を併用して$GPRMCや$GPZDAなどから取得・更新する想定)
uint32_t cached_gnss_unix_time = 0;

void setup() {
    // AVR: GNSSとJSON出力が同一Serialを共用するためボーレートを9600に設定。
#if defined(ARDUINO_ARCH_AVR)
    Serial.begin(9600);
#else
    Serial.begin(115200);
#endif
    uint32_t start = millis();
    while (!Serial && (millis() - start < 5000)) { delay(10); } // 5秒タイムアウト

#if defined(ESP32)
    Serial1.begin(9600, SERIAL_8N1, /*rx=*/20, /*tx=*/21);
#elif !defined(ARDUINO_ARCH_AVR)
    Serial1.begin(9600, SERIAL_8N1);
#endif
    Serial.println(F("[azaraC] ready, waiting for $QZQSM..."));
}

void loop() {
    // AVR: GNSSはUARTのSerial、それ以外はSerial1
#if defined(ARDUINO_ARCH_AVR)
    Stream& gnss = Serial;
#else
    Stream& gnss = Serial1;
#endif
    while (gnss.available()) {
        uint8_t b = static_cast<uint8_t>(gnss.read());

        // TinyGPS++ 等で NMEA をパースして時刻が更新されたら、 cached_gnss_unix_time = ... と更新する想定。

        // 第3引数now_unixにGNSSなどの時刻を渡すことで、DCR/DCX電文の「年」を正確に算出できます。
        // 未同期時 (now_unix = 0) の場合、年は解決されませんが、電文の生データ (月・日・時・分) は正しく取得・出力されます。
        if (parser.feed(b, msg, cached_gnss_unix_time)) {
            azaraC::toJson(msg, Serial);
            Serial.println();
        }
    }
}
