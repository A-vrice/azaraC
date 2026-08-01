// azaraC - test/uno_sketch/uno_sketch.ino
// Arduino Uno (AVR) compile check sketch for CI.
//
// Instantiates the Parser and calls feed()/toJson() so the linker keeps the
// whole library (framers, decoders, JSON serializers, definition tables in
// PROGMEM). Without these calls the library .cpp files are dead-stripped and
// the build would only prove the headers parse.
//
// All examples use Serial1 for the GNSS module, which the Uno does not have,
// so this sketch is used by the Arduino Uno (AVR) CI job instead.

#include <azaraC.h>

azaraC::Parser  parser;
azaraC::Message msg;

void setup() {}

void loop() {
    // Feeding an invalid byte forces the framer/decoder paths to link
    // without requiring a real GNSS module.
    uint8_t b = 0;
    if (parser.feed(b, msg, 0)) {
        azaraC::toJson(msg, Serial);
    }
}
