#pragma once
// internal/TimeFields.h の host 側 ARDUINO>=1 / __AVR__ テスト用の最小 Arduino シム。
// TimeFields.h が必要とするシンボルだけを提供する。test/stub_arduino/avr/io.h を参照。
#include <stdint.h>
#include <avr/io.h>

unsigned long millis();
