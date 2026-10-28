#pragma once
// azaraC — Arduino 向け QZSS L1S DCX/CAMF + QZQSM デコーダ
#if __cplusplus < 201703L
#error "This tool requires C++17 or later"
#endif

// std の名前と衝突する Arduino コアの `abs`/`min`/`max` マクロを undef する（mbed の pinDefinitions.h は abs、Arduino.h は min/max を定義する）。
#if defined(ARDUINO)
#  if defined(abs)
#    undef abs
#  endif
#  if defined(min)
#    undef min
#  endif
#  if defined(max)
#    undef max
#  endif
#endif

// この include より前に定義した AZARAC_* の上書きは azaraC_config.h で効く。
#include "azaraC_config.h"

#include "Message.h"
#include "Parser.h"
#include "json/JsonSerializer.h"

#if defined(ARDUINO) && ARDUINO >= 1
#  include <Print.h>
#endif

namespace azaraC {

// msg を JSON 化して任意の Print&（Serial、WiFiClient 等）へ書き出す。
inline void toJson(const Message& msg, Print& out) {
    internal::JsonSerializer::serialize(msg, out);
}

} // namespace azaraC
