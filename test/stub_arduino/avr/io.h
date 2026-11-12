#pragma once
// AVR のステータスレジスタと割り込み命令の host 用シム。
// 実 AVR の cli()/sei() は I ビット（bit7）のみ操作する。SREG の他ビットは保存する。
// internal::getMillis() が呼び出し側の割り込み状態（SREG 全体）を退避・復帰することを検証できる。
#include <stdint.h>

inline uint8_t SREG = 0;
inline void cli() { SREG &= static_cast<uint8_t>(~0x80); }
inline void sei() { SREG |= 0x80; }
