// azaraC — examples/basic_ubx/basic_ubx.ino
//
// UBX-RXM-SFRBX (binary) → JSON on Serial (USB)
//
// Wiring (ESP32-C3 DevKitM-1):
//   u-blox TX → GPIO20 (Serial1 RX)
//   u-blox RX → GPIO21 (Serial1 TX)
//   GND       → GND
//
// u-blox config required:
//   CFG-MSGOUT-UBX_RXM_SFRBX_UART1 = 1
//   CFG-SIGNAL-QZSS_L1S_ENA        = 1
//   CFG-UART1-BAUDRATE              = 9600

// #define AZARAC_DEDUP_SLOTS 16   // increase if using multiple SVs

// Arduino Uno (AVR) compatibility: the Uno has no Serial1 (single hardware
// UART = Serial on pins 0/1), so the GNSS module connects to Serial and JSON
// goes out the same port. Category reduction for the 32KB flash is applied
// automatically by azaraC_config.h (AVR preset keeps SEISMIC/TSUNAMI only).
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

#if defined(ESP32)
    Serial1.begin(9600, SERIAL_8N1, /*rx=*/20, /*tx=*/21);
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
        // 未同期時 (now_unix = 0) の場合、年は解決されませんが、
        // 電文の生データ (月・日・時・分) は正しく取得・出力されます。
        if (parser.feed(b, msg, cached_gnss_unix_time)) {
            azaraC::toJson(msg, Serial);
            Serial.println();
        }
    }
}
