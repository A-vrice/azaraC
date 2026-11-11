// 別 TU から getMillis() を呼ぶ（C10 回帰）。
// inline（外部リンケージ）なら s_last は全 TU で単一実体。static inline だと TU ごとに別カウンタになる。
// millis() の定義は test_time_irq.cpp 側にある（この TU は定義しない）。
#include "internal/TimeFields.h"
#include <cstdint>

uint64_t readMillisFromOtherTU() {
    return azaraC::internal::getMillis();
}