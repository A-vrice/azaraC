#pragma once
// azaraC — Arduino 向け QZSS L1S DCX/CAMF + QZQSM デコーダ
#if __cplusplus < 201703L
#error "This tool requires C++17 or later"
#endif

// std の名前と衝突する Arduino コアの `abs`/`min`/`max` マクロを、このヘッダを取り込む間だけ undef する
// （mbed の pinDefinitions.h は abs、Arduino.h は min/max を定義する）。
// 利用者のスケッチから恒久的に消さないよう push_macro / pop_macro で往復する
// （未対応のプリプロセッサでは pragma が無視され、従来どおり undef のままになる）。
#if defined(ARDUINO)
#  if defined(abs)
#    define AZARAC_RESTORE_ABS 1
#    pragma push_macro("abs")
#    undef abs
#  endif
#  if defined(min)
#    define AZARAC_RESTORE_MIN 1
#    pragma push_macro("min")
#    undef min
#  endif
#  if defined(max)
#    define AZARAC_RESTORE_MAX 1
#    pragma push_macro("max")
#    undef max
#  endif
#endif

// この include より前に定義した AZARAC_* の上書きは azaraC_config.h で効く。
#include "azaraC_config.h"

#include "Message.h"
#include "Parser.h"
#include "decoder/Decoder.h"
#include "json/JsonSerializer.h"

#if defined(ARDUINO) && ARDUINO >= 1
#  include <Print.h>
#endif

namespace azaraC {

// msg を JSON 化して任意の Print&（Serial、WiFiClient 等）へ書き出す。
inline void toJson(const Message& msg, Print& out) {
    internal::JsonSerializer::serialize(msg, out);
}

// msg を境界付きバッファへ JSON 化する（Print を持たない呼び出し側、String や固定バッファ向け）。
// buf は len > 0 なら必ず NUL 終端。入り切らない残りは捨て、バッファ外へは書かない。
// 戻り値は書き込んだバイト数（NUL を除く）で、buf[返り値] が NUL。
// required を渡すと完全な JSON の長さ（NUL を除く）が入り、*required > 返り値 なら切り詰め。
// buf == nullptr / len == 0 でも required は埋まる（長さだけ測る用途）。
inline size_t toJson(const Message& msg, char* buf, size_t len, size_t* required = nullptr) {
    return internal::JsonSerializer::serialize(msg, buf, len, required);
}

// CRC-24Q（IS-QZSS-L1S-009 §4.1.1.3）。data[0] の MSB から bit_len ビットを処理する。
// 受信経路が使うのと同じ実装で、自前の電文生成（テスト送信器、リピータ）や
// 外部で組み立てたフレームの検証に使う。
// 受信した Message の crc24 は Decoder が入れた値なので、通常はこちらを呼ぶ必要はない。
inline uint32_t crc24q(const uint8_t* data, uint16_t bit_len) {
    return internal::Decoder::crc24q(data, bit_len);
}

} // namespace azaraC

// 取り込み前に存在した Arduino コアのマクロを戻す（利用者のスケッチの挙動を変えない）。
#if defined(AZARAC_RESTORE_ABS)
#  pragma pop_macro("abs")
#  undef AZARAC_RESTORE_ABS
#endif
#if defined(AZARAC_RESTORE_MIN)
#  pragma pop_macro("min")
#  undef AZARAC_RESTORE_MIN
#endif
#if defined(AZARAC_RESTORE_MAX)
#  pragma pop_macro("max")
#  undef AZARAC_RESTORE_MAX
#endif
