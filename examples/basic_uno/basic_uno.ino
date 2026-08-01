// azaraC — examples/basic_uno/basic_uno.ino
//
// Minimal Arduino Uno (AVR) example: feeds bytes into the Parser and prints
// JSON on Serial. Unlike the other examples it uses Serial (pins 0/1) for
// the GNSS module, because the Uno has no Serial1.
//
// Also serves as the CI compile/link check for the AVR board: instantiating
// the Parser and calling feed()/toJson() keeps the whole library (framers,
// decoders, JSON serializers, definition tables in PROGMEM) in the link;
// a bare `#include <azaraC.h>` would let the linker dead-strip the .cpp
// files and only prove the headers parse.

// Arduino Uno: 32KB Flash cannot hold all definition tables; only the small
// categories (SEISMIC / TSUNAMI) are enabled. Other boards keep the defaults.
#if defined(ARDUINO_ARCH_AVR)
#  define AZARAC_ENABLE_EEW 0
#  define AZARAC_ENABLE_HYPOCENTER 0
#  define AZARAC_ENABLE_SEISMIC 1
#  define AZARAC_ENABLE_NANKAI 0
#  define AZARAC_ENABLE_TSUNAMI 1
#  define AZARAC_ENABLE_NW_PAC_TSUNAMI 0
#  define AZARAC_ENABLE_VOLCANO 0
#  define AZARAC_ENABLE_ASH_FALL 0
#  define AZARAC_ENABLE_WEATHER 0
#  define AZARAC_ENABLE_FLOOD 0
#  define AZARAC_ENABLE_TYPHOON 0
#  define AZARAC_ENABLE_MARINE 0
#  define AZARAC_ENABLE_DCX_CAMF 0
#endif

#include <azaraC.h>

azaraC::Parser  parser;
azaraC::Message msg;

void setup() {
    Serial.begin(9600);
    uint32_t start = millis();
    while (!Serial && (millis() - start < 5000)) { delay(10); } // 5秒タイムアウト
    Serial.println(F("[azaraC] ready, feeding Serial (pins 0/1)..."));
}

void loop() {
    while (Serial.available()) {
        uint8_t b = static_cast<uint8_t>(Serial.read());
        if (parser.feed(b, msg, 0)) {
            azaraC::toJson(msg, Serial);
            Serial.println();
        }
    }
}
