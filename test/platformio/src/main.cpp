// Minimal PlatformIO compile test for azaraC.
// Exercises the public API so the library actually links.
#include <Arduino.h>
#include <azaraC.h>

azaraC::Parser parser;
azaraC::Message msg;

void setup() {}

void loop() {
    while (Serial.available()) {
        if (parser.feed(Serial.read(), msg)) {
            azaraC::toJson(msg, Serial);
            Serial.println();
        }
    }
}
