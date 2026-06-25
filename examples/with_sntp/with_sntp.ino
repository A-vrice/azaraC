// azaraC — examples/with_sntp/with_sntp.ino
//
// Wi-Fi + SNTP で UNIX 時刻を取得し、DCR/DCX の発生時刻を解決する例
// disaster_category == 1 (EEW) および MT=44 DCX メッセージ のみ Serial に警告ログを出力するフィルタ付き

// #define AZARAC_DEDUP_SLOTS 16
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


// ── グローバル ───────────────────────────────────────────────────────────────
azaraC::Parser  parser;
azaraC::Message msg;

// ── setup ───────────────────────────────────────────────────────────────────
void setup() {
    Serial.begin(115200);
    uint32_t start = millis();
    while (!Serial && (millis() - start < 5000)) { delay(10); } // 5秒タイムアウト

    // Wi-Fi
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

// ── loop ────────────────────────────────────────────────────────────────────
void loop() {
    while (Serial1.available()) {
        // SNTPで取得した現在時刻を UNIX タイムスタンプとして渡す。
        // ※ 万一 SNTP 未同期で 2000 年以前の古い時刻が返る場合でも、
        //   azaraC 内部で未同期と判定され、年の解決がスキップされるため
        //   電文の生データ (月・日・時・分) 自体は安全に取得できます。
        // time_t は 64-bit 環境 (ESP-IDF newlib) で long long の可能性があるため、
        // 負値 (エラー) をガードしてから uint32_t にキャストする。
        time_t now_t = time(nullptr);
        uint32_t now = (now_t > 0) ? static_cast<uint32_t>(now_t) : 0;

        if (parser.feed(static_cast<uint8_t>(Serial1.read()), msg, now)) {
            // ── EEW および DCX 災害警報のみ警告出力（他は通常 JSON）──────────
            // 安全なアクセサを使用してunionメンバーにアクセス
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
                        Serial.print(mt44->mt44_decoded.main_ellipse.lat_deg, 3);
                        Serial.print(F(" Lon: "));
                        Serial.print(mt44->mt44_decoded.main_ellipse.lon_deg, 3);
                    }
                    Serial.println();
                }
            }

            // 全メッセージを JSON で Serial 出力
            azaraC::toJson(msg, Serial);
            Serial.println();
        }
    }
}
