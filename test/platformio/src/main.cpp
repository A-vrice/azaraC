// PlatformIO の最小コンパイルテスト: 公開 API を叩いてライブラリがリンクされることを確認する。
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
