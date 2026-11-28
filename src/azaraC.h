#pragma once
// azaraC — Arduino 向け QZSS L1S DCX/CAMF + QZQSM デコーダ
#if __cplusplus < 201703L
#error "This tool requires C++17 or later"
#endif

// std と衝突する Arduino マクロを、このヘッダを読む間だけ退避する。
#if defined(ARDUINO)
#  pragma push_macro("abs")
#  pragma push_macro("min")
#  pragma push_macro("max")
#  undef abs
#  undef min
#  undef max
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

// 固定長バッファへ書き、NUL を除く書き込み長を返す。buf が非 nullptr かつ len > 0 なら NUL 終端する。
// required は切り詰め前の長さ（NUL を除く）。nullptr / len == 0 でも必要長を取得できる。
inline size_t toJson(const Message& msg, char* buf, size_t len, size_t* required = nullptr) {
    return internal::JsonSerializer::serialize(msg, buf, len, required);
}

// data[0] の MSB から bit_len ビットの CRC-24Q（受信経路と同じ実装）。
inline uint32_t crc24q(const uint8_t* data, uint16_t bit_len) {
    return internal::Decoder::crc24q(data, bit_len);
}

} // namespace azaraC

#if defined(ARDUINO)
#  pragma pop_macro("max")
#  pragma pop_macro("min")
#  pragma pop_macro("abs")
#endif
