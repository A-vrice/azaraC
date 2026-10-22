/* test/bench/avr/core_progmem.c
   Arduino コア自身の PROGMEM テーブルの代替。core.a と同じく最後にリンクされる。

   鏡像の危険: コアはピンテーブルを 16 ビットポインタで読む —
   wiring_digital.c の `pgm_read_byte(&digital_pin_to_port_PGM[pin])` は Flash の
   先頭 64 KiB にしか届かない。avr-libc のリンカスクリプトは progmem クラスタ
   （`*(.progmem.gcc*)` / `*(.progmem*)`）をリンク順で .text の先頭に置き、
   Arduino レシピは core.a を最後に置くので、その前にリンクされた PROGMEM ライブラリが
   コアのテーブルを押し上げる。0xFFFF を越えると切り詰められたポインタは誤った
   アドレスを読み、pinMode/digitalWrite が誤ったポートを駆動する。

   autoresearch.sh はこのオブジェクトをライブラリのオブジェクトの後にリンクし、
   `core_probe_pin_to_port_PGM` が 16 ビット窓内に収まることをゲートする。この
   オブジェクトが残るのは `-Wl,--undefined=core_probe_read_pin` による（コアの
   コードがこれを呼ぶので、コア側のコピーが --gc-sections を生き残る理由でもある）。

   ここで問題になるのはアドレス幅だけなので、意図的に小さなテーブルにしており、
   pins_arduino.h の実レイアウトではない。 */

#include <avr/pgmspace.h>
#include <stdint.h>

// cppcheck は avr/pgmspace.h を見ない（include パスにない）ため、PROGMEM と
// pgm_read_byte を未知の名前として扱う — コアが使うのと同じマクロ。
// cppcheck-suppress unknownMacro
const uint8_t core_probe_pin_to_port_PGM[16] PROGMEM = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
};

uint8_t core_probe_read_pin(uint8_t pin) {
    return pgm_read_byte(&core_probe_pin_to_port_PGM[pin & 15u]);
}
