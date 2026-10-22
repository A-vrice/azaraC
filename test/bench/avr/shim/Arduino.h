#pragma once
// Arduino コアの <Arduino.h> の最小代用。
//
// autoresearch.sh は Arduino コアを使わず avr-gcc (ATmega2560) で実ライブラリをリンクし、Flash 使用量を測る。コアはネットワーク取得でオフライン計測に載らないため、azaraC が触れる面（millis と Print）だけを提供する。
// -DARDUINO=1 のときだけ到達する（azaraC.h が <Print.h> を取り、internal/TimeFields.h が Arduino 分岐に入る）。ライブラリ本来のビルド経路ではない。

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#if defined(__AVR__)
// internal/TimeFields.h は __AVR__ で SREG を退避して cli() を呼ぶ（f41550a）。実コアはどちらも <avr/interrupt.h> から得る。ツールチェーンのヘッダをそのまま使うことで、shim が状態を偽らないようにする（FlashString.h が FLASHEND 用に <avr/io.h> を先に取り込むため、SREG はこの時点でマクロかもしれない）。
#include <avr/interrupt.h>
#include <avr/io.h>
#endif

#include "internal/avr_std/string_view"

unsigned long millis(void);
void noInterrupts(void);
void interrupts(void);

class Print {
public:
    virtual ~Print() = default;

    virtual size_t write(uint8_t) { return 1; }
    virtual size_t write(const char*, size_t n) { return n; }

    // 実コアと同じく print() は write() へ流す。ここで捨てると LTO が出力を作る側の処理（writeUint32 の桁変換など）ごと消し、計測した Flash がスケッチの実費より小さくなる。
    size_t print(char c) { return write(static_cast<uint8_t>(c)); }
    size_t print(const char* s) { return write(s, strlen(s)); }
    size_t print(std::string_view s) { return s.empty() ? 0 : write(s.data(), s.size()); }

    // 数値も実コア同様に 10 進へ展開して write() へ渡す。
    size_t print(unsigned int v) { return printUnsigned(v); }
    size_t print(int v) {
        if (v < 0) {
            const size_t n = print('-');
            return n + printUnsigned(0u - static_cast<unsigned int>(v));
        }
        return printUnsigned(static_cast<unsigned int>(v));
    }

    void println() { print('\n'); }
    void println(const char* s) { print(s); print('\n'); }
    void println(std::string_view s) { print(s); print('\n'); }

private:
    size_t printUnsigned(unsigned int v) {
        char buf[11];  // unsigned int の最大桁数 + NUL（AVR では 5 桁）
        int8_t i = 10;
        buf[i] = '\0';
        do { buf[--i] = static_cast<char>('0' + (v % 10)); v /= 10; } while (v);
        return write(buf + i, 10 - static_cast<size_t>(i));
    }
};
