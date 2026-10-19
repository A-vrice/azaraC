// azaraC — examples/with_sntp/with_sntp.ino
//
// Wi-Fi + SNTP で UNIX 時刻を取得し DCR/DCX の「年」を解決する例。 disaster_category == 1 (EEW) と MT=44 DCX のみ警告ログを出し、他は JSON を出力する。

// (AZARAC_DEDUP_SLOTS: no override — the default is sized from 30 QZSS archive days; see src/azaraC_config.h.)
#include <azaraC.h>
#include <WiFi.h>
#include <time.h>

// Wi-Fi 設定を自分の環境に合わせて書き換えてください
#ifndef WIFI_SSID
  #warning "Please set WIFI_SSID in with_sntp.ino"
  #define WIFI_SSID "YOUR_SSID" // <-- Change this
#endif
#ifndef WIFI_PASS
  #warning "Please set WIFI_PASS in with_sntp.ino"
  #define WIFI_PASS "YOUR_PASS" // <-- Change this
#endif


azaraC::Parser  parser;
azaraC::Message msg;

void setup() {
    Serial.begin(115200);
    uint32_t start = millis();
    while (!Serial && (millis() - start < 5000)) { delay(10); } // 5秒タイムアウト

    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.print(F("[wifi] connecting"));
    while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print('.'); }
    Serial.println(F(" OK"));

    // SNTP (pool.ntp.org, JST+9)
    configTime(9 * 3600, 0, "pool.ntp.org", "time.cloudflare.com");
    Serial.print(F("[sntp] syncing"));
    struct tm ti{};
    time_t now;
    while (true) {
        time(&now);
        localtime_r(&now, &ti);
        if (ti.tm_year > (2016 - 1900)) break;
        Serial.print('.');
        delay(1000);
    }
    Serial.println(F(" OK"));

#if defined(ESP32)
    Serial1.begin(9600, SERIAL_8N1, /*rx=*/20, /*tx=*/21);
#else
    Serial1.begin(9600, SERIAL_8N1);
#endif
    Serial.println(F("[azaraC] ready"));
}

void loop() {
    while (Serial1.available()) {
        // SNTP 同期の現在時刻を UNIX 秒で渡す。未同期で 2000 年以前の値でも、azaraC が年解決をスキップするので電文の生データ (月・日・時・分) は正しく取れる。 time_t は 64-bit 環境で long long のため、負値 (エラー) をガードしてから uint32_t にキャストする。
        time_t now_t = time(nullptr);
        uint32_t now = (now_t > 0) ? static_cast<uint32_t>(now_t) : 0;

        if (parser.feed(static_cast<uint8_t>(Serial1.read()), msg, now)) {
            if (msg.msg_type == 43) {
                const azaraC::Mt43Data* mt43 = msg.getMt43();
                if (mt43 && mt43->disaster_category == 1) {
                    const azaraC::EewData* eew = mt43->getEew();
                    if (!eew) return;
                    Serial.print(F("[EEW] epicenter="));
                    Serial.print(eew->epicenter);
                    Serial.print(F(" mag="));
                    Serial.print(eew->magnitude / 10);
                    Serial.print('.');
                    Serial.print(eew->magnitude % 10);
                    Serial.print(F(" depth="));
                    Serial.print(eew->depth);
                    Serial.println(F("km"));
                }
            } else if (msg.msg_type == 44) {
                const azaraC::Mt44Data* mt44 = msg.getMt44();
                if (mt44) {
                    Serial.print(F("[DCX] "));
                    switch (mt44->service_kind) {
                        case azaraC::Mt44ServiceKind::LAlert:          Serial.print(F("L-Alert")); break;
                        case azaraC::Mt44ServiceKind::JAlert:          Serial.print(F("J-Alert")); break;
                        case azaraC::Mt44ServiceKind::LocalGovernment: Serial.print(F("Local Gov")); break;
                        case azaraC::Mt44ServiceKind::OutsideJapan:    Serial.print(F("Outside Japan")); break;
                        case azaraC::Mt44ServiceKind::NullMessage:     Serial.print(F("Null Message")); break;
                        default:                                       Serial.print(F("Unknown")); break;
                    }
                    if (mt44->mt44_decoded.main_ellipse_present) {
                        Serial.print(F(" | Lat: "));
                        Serial.print(mt44->mt44_decoded.main_ellipse.lat_microdeg / 1000000.0, 3);
                        Serial.print(F(" Lon: "));
                        Serial.print(mt44->mt44_decoded.main_ellipse.lon_microdeg / 1000000.0, 3);
                    }
                    Serial.println();
                }
            }

            azaraC::toJson(msg, Serial);
            Serial.println();
        }
    }
}
