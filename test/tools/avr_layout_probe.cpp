// 実 avr-g++ で NankaiPageBuffer/DedupFilter/Message の ABI レイアウトを固定する。
// Makefile の avr-layout が 63 ページ・4 ページ・DCX 有効の 3 構成で -fsyntax-only する。
#include "internal/avr_std/cstddef"
#include "internal/NankaiPageBuffer.h"
#include "internal/Dedup.h"
#include "Message.h"

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

// README / docs/architecture.md が引用する AVR プリセットのサイズ（Mt43Data 75 B + ヘッダ）。
// ページ数には依存しないので、上の #if 連鎖の外（ファイルスコープ）に置く。
#if AZARAC_ENABLE_DCX_CAMF
static_assert(sizeof(azaraC::Message) == 199, "Message AVR + DCX layout changed");
#else
static_assert(sizeof(azaraC::Message) == 84, "Message AVR preset layout changed");
#endif
