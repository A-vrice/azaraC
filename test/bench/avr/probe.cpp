// test/bench/avr/probe.cpp
// autoresearch.sh 用の Flash フットプリント・プローブ: リンクするだけで実行はしない。
//
// 実 AVR ターゲット向けにライブラリ全体とともにビルドされ、decode + serialize 経路（ひいてはシリアライザが引く全定義テーブル）を到達可能に保つ。これによりリンク済みイメージが --gc-sections 下でも「スケッチが払う flash」として意味を持つ数値になる。
// 本体は公開 API（Parser::feed + toJson）だけに触れる。
//
// 両端を意図的に不透明にしている:
//   - 入力バイトは volatile。コンパイラが feed() を「まだフレームなし」に畳んで decode 経路を落とせないようにする。
//   - シンクの write() は渡されたバイトを生かし続ける（入力オペランド付きの空 asm）。これでラベルと、その元になる定義テーブルがイメージに残る。
// 何でも飲み込むシンクだと LTO が serialize 経路とそれが読むテーブルを削除でき、flash 数値はスケッチが払う額を意味しなくなる。

#include "azaraC.h"

#include <stddef.h>
#include <stdlib.h>

// Arduino コアが提供するもの: AVR ツールチェーンは自前の C++ ランタイムを持たない。

unsigned long millis(void) { return 0; }
void noInterrupts(void) {}
void interrupts(void) {}

void* operator new(size_t n) { return malloc(n); }
void* operator new[](size_t n) { return malloc(n); }
void operator delete(void* p) { free(p); }
void operator delete[](void* p) { free(p); }
void operator delete(void* p, size_t) { free(p); }
void operator delete[](void* p, size_t) { free(p); }

namespace {
// シンク。write() はライブラリがキーとラベルに使う経路（out.write(s.data(), s.size())）なので、
// これを上書きすることがテーブルをイメージに結びつける。asm はポインタと長さを生かしたまま
// 何も格納しない: カウンタに SRAM を使わない。
class ProbePrint : public Print {
public:
    size_t write(uint8_t) override {
        asm volatile("" ::: "memory");
        return 1;
    }
    size_t write(const char* s, size_t n) override {
        asm volatile("" : : "r"(s), "r"(n) : "memory");
        return n;
    }
};

ProbePrint g_out;
}  // namespace

int main() {
    azaraC::Parser parser;
    azaraC::Message msg;
    volatile uint8_t byte = 0x00;
    parser.feed(byte, msg);
    azaraC::toJson(msg, g_out);
    return 0;
}
