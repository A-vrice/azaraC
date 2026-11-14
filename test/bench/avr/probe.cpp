// autoresearch.sh 用の Flash フットプリント・プローブ: リンクするだけで実行はしない。
//
// 実 AVR ターゲット向けにライブラリ全体とともにビルドされ、decode + serialize 経路（ひいてはシリアライザが引く全定義テーブル）を到達可能に保つ。
// これによりリンク済みイメージが --gc-sections 下でも「スケッチが払う flash」として意味を持つ数値になる。
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
// シンク。
// write() はライブラリがキーとラベルに使う経路（out.write(s.data(), s.size())）なので、これを上書きすることがテーブルをイメージに結びつける。
// asm はポインタと長さを生かしたまま何も格納しない: カウンタに SRAM を使わない。
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

// 目印関数。autoresearch.sh の image_has_path() はこの名前を nm で探す。
// gcc 14 の LTO は Decoder::decode などを呼び出し元へ inline して記号を消すため、
// ライブラリ内部の関数名ではなく、inline されないこの 2 つで経路の存在を確かめる。
extern "C" __attribute__((noinline)) void azarac_probe_decode(azaraC::Parser& parser, azaraC::Message& msg) {
    volatile uint8_t byte = 0x00;
    parser.feed(byte, msg);
}

extern "C" __attribute__((noinline)) void azarac_probe_serialize(const azaraC::Message& msg) {
    azaraC::toJson(msg, g_out);
}

int main() {
    azaraC::Parser parser;
    azaraC::Message msg;
    azarac_probe_decode(parser, msg);
    azarac_probe_serialize(msg);
    return 0;
}
