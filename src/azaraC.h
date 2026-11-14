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
