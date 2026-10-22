#pragma once
// AVR のステータスレジスタと割り込み命令の host 用シム。
// SREG と cli()/sei() は I ビットを十分忠実に模し、
// internal::getMillis() が呼び出し側の割り込み状態を退避・復帰することを検証できる。
#include <stdint.h>

inline uint8_t SREG = 0;
inline void cli() { SREG = 0; }
inline void sei() { SREG = 0x80; }
