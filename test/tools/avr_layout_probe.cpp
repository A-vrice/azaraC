// 実 avr-g++ で NankaiPageBuffer/DedupFilter の ABI レイアウトを固定する。
// Makefile の avr-layout が 63 ページと 4 ページの2構成で -fsyntax-only する。
#include "internal/avr_std/cstddef"
#include "internal/NankaiPageBuffer.h"
#include "internal/Dedup.h"

static_assert(sizeof(azaraC::internal::NankaiPageKey) == 7,
              "NankaiPageKey must be 7 bytes on AVR");
static_assert(sizeof(azaraC::internal::DedupFilter) == AZARAC_DEDUP_SLOTS * 8,
              "DedupFilter RAM must remain SLOTS * 8 bytes on AVR");

#if AZARAC_NANKAI_MAX_PAGES == 63
static_assert(sizeof(azaraC::internal::NankaiPageBuffer) == 1158,
              "NankaiPageBuffer AVR 63-page layout changed");
static_assert(offsetof(azaraC::internal::NankaiPageBuffer, aggregated_text) == 23,
              "NankaiPageBuffer AVR aggregated_text offset changed");
#elif AZARAC_NANKAI_MAX_PAGES == 4
static_assert(sizeof(azaraC::internal::NankaiPageBuffer) == 96,
              "NankaiPageBuffer AVR 4-page layout changed");
static_assert(offsetof(azaraC::internal::NankaiPageBuffer, aggregated_text) == 23,
              "NankaiPageBuffer AVR preset aggregated_text offset changed");
#else
#error "avr_layout_probe expects AZARAC_NANKAI_MAX_PAGES=63 or 4"
#endif
