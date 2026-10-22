// azaraC — examples/basic_uno/basic_uno.ino
//
// Arduino Uno (AVR) の最小サンプル: バイトを Parser に流し、JSON を Serial に出力する。
// Uno には Serial1 がないため GNSS モジュールには Serial（ピン 0/1）を使う。この共用 UART
// 経路は CI のコンパイル/リンク確認用で、実機では GNSS に SoftwareSerial（または Mega の
// Serial1）を使い、Serial は JSON 用に空けておくこと。そうしないと双方向が衝突する。
//
// AVR ボードの CI コンパイル/リンク確認も兼ねる: Parser を実体化して feed()/toJson() を呼ぶことで、ライブラリ全体（フレーマ、デコーダ、シリアライザ、PROGMEM テーブル）がリンクに残る。`#include <azaraC.h>` だけだとリンカが .cpp を dead-strip してしまう。
//
// Category reduction for the 32KB flash is applied automatically by azaraC_config.h (AVR preset keeps SEISMIC/TSUNAMI only).

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
