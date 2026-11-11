// UBX-RXM-SFRBX（バイナリ）をデコードして Serial (USB) へ JSON を出す配線 (ESP32-C3 DevKitM-1):
//   u-blox TX → GPIO20 (Serial1 RX)
//   u-blox RX → GPIO21 (Serial1 TX)
//   GND       → GND
//
// u-blox に設定が必要:
//   CFG-MSGOUT-UBX_RXM_SFRBX_UART1 = 1
//   CFG-SIGNAL-QZSS_L1S_ENA        = 1
//   CFG-UART1-BAUDRATE              = 9600

// (AZARAC_DEDUP_SLOTS: 上書き不要 — 非 AVR の既定は 512 スロットで、AVR プリセットが既に 64 まで下げている。実測した誤再通知回数は src/azaraC_config.h を参照。)

// Arduino Uno (AVR) 互換: Serial1 がなく（ハードウェア UART はピン 0/1 の Serial のみ）、GNSS モジュールと JSON 出力が同じポートを共用する。
// 32KB フラッシュ向けのカテゴリ削減は azaraC_config.h が自動で適用する（AVR プリセットは SEISMIC/TSUNAMI のみ残す）。
#include <azaraC.h>


azaraC::Parser  parser;
azaraC::Message msg;

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

#if defined(ARDUINO_ESP32C3_DEV) || defined(CONFIG_IDF_TARGET_ESP32C3)
    Serial1.begin(9600, SERIAL_8N1, /*rx=*/20, /*tx=*/21);
#elif defined(CONFIG_IDF_TARGET_ESP32C6) || defined(ARDUINO_ESP32C6_DEV)
    // ESP32-C6 は GPIO16/17 が UART0（Serial 出力）なので別ピンを使う
    Serial1.begin(9600, SERIAL_8N1, /*rx=*/4, /*tx=*/5);
#elif defined(ESP32)
    // classic ESP32 は GPIO16/17 が UART2 の既定（RX=16 / TX=17）。S3 などは既定が違うので配線に合わせて変更する。WROVER は 16/17 が PSRAM
    Serial1.begin(9600, SERIAL_8N1, /*rx=*/16, /*tx=*/17);
#elif !defined(ARDUINO_ARCH_AVR)
    Serial1.begin(9600, SERIAL_8N1);
#endif
    Serial.println(F("[azaraC] ready, waiting for UBX-RXM-SFRBX..."));
}

void loop() {
    // AVR: GNSSはUARTの Serial、それ以外は Serial1
#if defined(ARDUINO_ARCH_AVR)
    Stream& gnss = Serial;
#else
    Stream& gnss = Serial1;
#endif
    while (gnss.available()) {
        uint8_t b = static_cast<uint8_t>(gnss.read());


        // 第3引数now_unixにGNSSなどの時刻を渡すことで、DCR/DCX電文の「年」を正確に算出できます。
        // 未同期時 (now_unix = 0) の場合、年は解決されませんが、電文の生データ (月・日・時・分) は正しく取得・出力されます。
        if (parser.feed(b, msg, cached_gnss_unix_time)) {
            azaraC::toJson(msg, Serial);
            Serial.println();
        }
    }
}
