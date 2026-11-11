// MT=43 防災カテゴリ別フィルタリングの例。
// 特定の災害カテゴリのみを Serial に出力する。対応カテゴリ:
//   1  = 緊急地震速報 (EEW)
//   2  = 震源情報 (Hypocenter)
//   3  = 震度情報 (Seismic Intensity)
//   4  = 南海トラフ地震 (Nankai Trough)
//   5  = 津波警報・注意報 (Tsunami)
//   6  = 北太平洋津波 (NW Pacific Tsunami)
//   8  = 火山情報 (Volcano)
//   9  = 降灰情報 (Ash Fall)
//   10 = 気象警報・注意報 (Weather)
//   11 = 洪水警報 (Flood)
//   12 = 台風情報 (Typhoon)
//   14 = 海上警報 (Marine)
//
// 配線 (ESP32-C3 DevKitM-1):
//   GNSS TX → GPIO20 (Serial1 RX)
//   GNSS RX → GPIO21 (Serial1 TX)
//   GND     → GND

#include <azaraC.h>


azaraC::Parser  parser;
azaraC::Message msg;

// (UBX-NAV-PVT 等から別途パースして更新する想定)
static uint32_t cached_gnss_unix_time = 0;

// 出力したい災害カテゴリを設定（true = 出力する）
struct CategoryFilter {
    bool eew          = true;   // 1: 緊急地震速報
    bool hypocenter   = true;   // 2: 震源情報
    bool seismic      = true;   // 3: 震度情報
    bool nankai       = true;   // 4: 南海トラフ
    bool tsunami      = true;   // 5: 津波
    bool nw_pac_tsu   = false;  // 6: 北太平洋津波
    bool volcano      = true;   // 8: 火山
    bool ash_fall     = true;   // 9: 降灰
    bool weather      = false;  // 10: 気象
    bool flood        = true;   // 11: 洪水
    bool typhoon      = true;   // 12: 台風
    bool marine       = false;  // 14: 海上
};

CategoryFilter filter;

// ラベルは F() で Flash に置く（生リテラルは AVR の SRAM に常駐するため）。
const __FlashStringHelper* getCategoryLabel(uint8_t category) {
    switch (category) {
        case 1:  return F("緊急地震速報");
        case 2:  return F("震源情報");
        case 3:  return F("震度情報");
        case 4:  return F("南海トラフ");
        case 5:  return F("津波");
        case 6:  return F("北太平洋津波");
        case 8:  return F("火山");
        case 9:  return F("降灰");
        case 10: return F("気象");
        case 11: return F("洪水");
        case 12: return F("台風");
        case 14: return F("海上");
        default: return F("不明");
    }
}

// 数量コードのセンチネル/境界を考慮して表示する（docs/api-reference.md の数量ラベル表参照）。
// 生コードに単位を付けて出すと 511km / 12.7 のような誤表示になるため、ここで吸収する。
void printMagnitude(uint16_t mag) {
    if (mag == 127) { Serial.print(F("不明")); return; }
    if (mag == 126) { Serial.print(F("不明(8.0より大きい)")); return; }
    if (mag == 101) { Serial.print(F("10.0より大きい")); return; }
    Serial.print(mag / 10);
    Serial.print('.');
    Serial.print(mag % 10);
}

void printDepth(uint16_t depth) {
    if (depth == 511) { Serial.print(F("不明")); return; }
    if (depth == 501) { Serial.print(F("500kmより深い")); return; }
    Serial.print(depth);
    Serial.print(F("km"));
}

bool shouldOutput(uint8_t category) {
    switch (category) {
        case 1:  return filter.eew;
        case 2:  return filter.hypocenter;
        case 3:  return filter.seismic;
        case 4:  return filter.nankai;
        case 5:  return filter.tsunami;
        case 6:  return filter.nw_pac_tsu;
        case 8:  return filter.volcano;
        case 9:  return filter.ash_fall;
        case 10: return filter.weather;
        case 11: return filter.flood;
        case 12: return filter.typhoon;
        case 14: return filter.marine;
        default: return false; // 未知のカテゴリは出力しない（安全のため）
    }
}

void printMt43Details(const azaraC::Message& msg) {
    const azaraC::Mt43Data* mt43 = msg.getMt43();
    if (!mt43) return;

    switch (mt43->disaster_category) {
#if (AZARAC_ENABLE_EEW)
        case 1: { // EEW
            const azaraC::EewData* eew = mt43->getEew();
            if (!eew) break;
            Serial.print(F("  震源: "));
            Serial.print(eew->epicenter);
            Serial.print(F(" マグニチュード: "));
            printMagnitude(eew->magnitude);
            Serial.print(F(" 深さ: "));
            printDepth(eew->depth);
            Serial.println();
            break;
        }
#endif // AZARAC_ENABLE_EEW
#if (AZARAC_ENABLE_HYPOCENTER)
        case 2: { // Hypocenter
            const azaraC::HypocenterData* hypo = mt43->getHypocenter();
            if (!hypo) break;
            Serial.print(F("  震源: "));
            Serial.print(hypo->epicenter);
            Serial.print(F(" マグニチュード: "));
            printMagnitude(hypo->magnitude);
            Serial.println();
            break;
        }
#endif // AZARAC_ENABLE_HYPOCENTER
#if (AZARAC_ENABLE_SEISMIC)
        case 3: { // Seismic Intensity
            const azaraC::SeismicData* seis = mt43->getSeismic();
            if (!seis) break;
            Serial.print(F("  観測地点数: "));
            Serial.println(seis->count);
            break;
        }
#endif // AZARAC_ENABLE_SEISMIC
#if (AZARAC_ENABLE_TSUNAMI)
        case 5: { // Tsunami
            const azaraC::TsunamiData* tsunami = mt43->getTsunami();
            if (!tsunami) break;
            Serial.print(F("  警報コード: "));
            Serial.print(tsunami->warning_code);
            Serial.print(F(" 海域数: "));
            Serial.println(tsunami->count);
            break;
        }
#endif // AZARAC_ENABLE_TSUNAMI
#if (AZARAC_ENABLE_TYPHOON)
        case 12: { // Typhoon
            const azaraC::TyphoonData* typh = mt43->getTyphoon();
            if (!typh) break;
            Serial.print(F("  台風番号: "));
            Serial.print(typh->number);
            Serial.print(F(" 中心気圧: "));
            Serial.print(typh->pressure);
            Serial.print(F("hPa 最大風速: "));
            if (typh->max_wind == 0) {
                Serial.print(F("不明"));   // 0 はセンチネル（不明）
            } else {
                Serial.print(typh->max_wind);
                Serial.print(F("m/s"));
            }
            Serial.println();
            break;
        }
#endif // AZARAC_ENABLE_TYPHOON
        default:
            break;
    }
}

void setup() {
    Serial.begin(115200);
    uint32_t start = millis();
    while (!Serial && (millis() - start < 5000)) { delay(10); } // 5秒タイムアウト

    #if defined(ARDUINO_ESP32C3_DEV) || defined(CONFIG_IDF_TARGET_ESP32C3)
        Serial1.begin(9600, SERIAL_8N1, /*rx=*/20, /*tx=*/21);
    #elif defined(CONFIG_IDF_TARGET_ESP32C6) || defined(ARDUINO_ESP32C6_DEV)
        // ESP32-C6 は GPIO16/17 が UART0（Serial 出力）なので別ピンを使う
        Serial1.begin(9600, SERIAL_8N1, /*rx=*/4, /*tx=*/5);
    #elif defined(ESP32)
        // classic ESP32 は GPIO16/17 が UART2 の既定。S3 などは配線に合わせて変更する
        Serial1.begin(9600, SERIAL_8N1, /*rx=*/16, /*tx=*/17);
    #else
        Serial1.begin(9600, SERIAL_8N1);   // Mega など Serial1 を持つ非 ESP32 ボードの既定ピン
    #endif
    Serial.println(F("[azaraC] filter_by_category ready"));
    Serial.println(F("出力カテゴリ:"));
    Serial.println(F("  [ON]  EEW, 震源, 震度, 南海トラフ, 津波, 火山, 降灰, 洪水, 台風"));
    Serial.println(F("  [OFF] 北太平洋津波, 気象, 海上"));
}

void loop() {
    while (Serial1.available()) {
        uint8_t b = static_cast<uint8_t>(Serial1.read());

        // 第3引数に UNIX 時刻を渡すと DCR/DCX 電文の「年」が解決する
        if (parser.feed(b, msg, cached_gnss_unix_time)) {
            if (msg.msg_type == 43) {
                const azaraC::Mt43Data* mt43 = msg.getMt43();
                if (mt43 && shouldOutput(mt43->disaster_category)) {
                    Serial.print(F("[MT43:"));
                    Serial.print(getCategoryLabel(mt43->disaster_category));
                    Serial.print(F("] SVID="));
                    Serial.print(msg.svid);
                    Serial.println();
                    printMt43Details(msg);
                    azaraC::toJson(msg, Serial);
                    Serial.println();
                }
            } else if (msg.msg_type == 44) {
                // DCX (MT=44) はカテゴリフィルタの対象外。フィルタしたい場合は shouldOutput() に分岐を足す。
                Serial.print(F("[MT44] SVID="));
                Serial.println(msg.svid);
                azaraC::toJson(msg, Serial);
                Serial.println();
            }
        }
    }
}
