#pragma once
// Compile-time configuration macros. Separated from azaraC.h so definition files can include only these macros.

// language selection macros
#ifndef AZARAC_LANG_JA
#define AZARAC_LANG_JA 1
#endif

#ifndef AZARAC_LANG_EN
#define AZARAC_LANG_EN 0
#endif

// 災害カテゴリの制御マクロ（下の AVR preset が先に既定値を入れるので、どちらの節でも #ifndef が機能する）。

// AVR/resource-constrained presets: reduced buffer sizes and categories.
// 通常の既定値より前に置き、どちらの節でも #ifndef を成立させる — ユーザーの -D が勝ち（両節ともスキップ）、AVR は縮小値を入れ、非 AVR は通常の既定値まで落ちる。
#if defined(__AVR__)
#ifndef AZARAC_NANKAI_MAX_PAGES
#define AZARAC_NANKAI_MAX_PAGES 4
#endif
#ifndef AZARAC_NANKAI_BUFFERS
#define AZARAC_NANKAI_BUFFERS 1
#endif
#ifndef AZARAC_DEDUP_SLOTS
// 64 スロット（8 セット x 8 way）= 512 B。
// AVR カテゴリ（dc=3 震度、dc=5 津波、8,669 フレーム / 77 種の MT～VN）で実測: 64x8 の再通知 0 件、32x8 (256 B) も 0 件、16x8 (128 B) で 93 件 — 実測の下限は 32x8 だが、Uno の 2 KB SRAM のうち 512 B で買えるのが 64x8。
// 32 未満にはしない。
#define AZARAC_DEDUP_SLOTS 64
#endif
#ifndef AZARAC_DEDUP_WAYS
#define AZARAC_DEDUP_WAYS 8
#endif
#ifndef AZARAC_DEDUP_MT44_MAX_WINDOW_MS
// MT=44 (DCX/CAMF) の窓の上限。
// ホストは A8-Hazard Duration の上限（6 時間〜7 日、internal/DedupWindow.h）を使うが、AVR の 64 スロットでは 7 日の窓が「まだ生きている情報」の枠を長く占め、押し出しによる再通知を招く。
// MT44 の再送は同じ電文が 2 回（まれに 3〜4 回）・間隔は最大 16 秒（issue #34 の実測）なので 5 分で足りる。
// A8 の窓は最短でも 6 時間なので常に効く。
#define AZARAC_DEDUP_MT44_MAX_WINDOW_MS 300000UL  // 5 min
#endif
// DCX/CAMF は表だけで約 100 KB、decoder がさらに約 20 KB なので 256 KB の品（ATmega2560、DCX/CAMF + SEISMIC/TSUNAMI、JA: 144,804 B のイメージ — test/bench/avr 参照）にしか載らない。
// チップ名で何かが有効になることはない: すべての AVR 品は Uno と同じ SEISMIC/TSUNAMI から始まり、ユーザーがビルドフラグで有効化する — -DAZARAC_AVR_LARGE_FLASH=1（この preset が想定する名前）または -DAZARAC_ENABLE_DCX_CAMF=1。ライブラリは別の翻訳単位なので、スケッチに置いた #define は届かない。
// 64 KiB を超える表は internal/FlashString.h の far Flash アドレッシングも必要で、該当デバイスは自動でそれを選ぶ（FLASHEND > 0xFFFF）。
// 残りのカテゴリは大型品でも既定 off のまま（全部同時なら約 242 KiB）。必要に応じて同じ要領で有効化する（-DAZARAC_ENABLE_EEW=1 …）。
#if !defined(AZARAC_AVR_LARGE_FLASH)
#define AZARAC_AVR_LARGE_FLASH 0
#endif
#ifndef AZARAC_ENABLE_EEW
#define AZARAC_ENABLE_EEW 0
#endif
#ifndef AZARAC_ENABLE_HYPOCENTER
#define AZARAC_ENABLE_HYPOCENTER 0
#endif
#ifndef AZARAC_ENABLE_SEISMIC
#define AZARAC_ENABLE_SEISMIC 1
#endif
#ifndef AZARAC_ENABLE_NANKAI
#define AZARAC_ENABLE_NANKAI 0
#endif
#ifndef AZARAC_ENABLE_TSUNAMI
#define AZARAC_ENABLE_TSUNAMI 1
#endif
#ifndef AZARAC_ENABLE_NW_PAC_TSUNAMI
#define AZARAC_ENABLE_NW_PAC_TSUNAMI 0
#endif
#ifndef AZARAC_ENABLE_VOLCANO
#define AZARAC_ENABLE_VOLCANO 0
#endif
#ifndef AZARAC_ENABLE_ASH_FALL
#define AZARAC_ENABLE_ASH_FALL 0
#endif
#ifndef AZARAC_ENABLE_WEATHER
#define AZARAC_ENABLE_WEATHER 0
#endif
#ifndef AZARAC_ENABLE_FLOOD
#define AZARAC_ENABLE_FLOOD 0
#endif
#ifndef AZARAC_ENABLE_TYPHOON
#define AZARAC_ENABLE_TYPHOON 0
#endif
#ifndef AZARAC_ENABLE_MARINE
#define AZARAC_ENABLE_MARINE 0
#endif
#ifndef AZARAC_ENABLE_DCX_CAMF
#define AZARAC_ENABLE_DCX_CAMF AZARAC_AVR_LARGE_FLASH
#endif

// 定義表引き当て用の共有バッファ（internal/FlashString.h 参照）。
// 上のカテゴリより後に置く（ユーザーの -D だけでなく preset もサイズを選べるようにするため）。またラベルの出どころとなる全カテゴリの最長ラベルを収める必要がある: 表はそれぞれのガードで有効になり、この連鎖では決まらないので、ここに無いカテゴリは黙ってラベルを切り詰める（azarac_pgm_view は AZARAC_FLASH_BUF_SIZE - 1 で、UTF-8 の途中でも切る）。
// 最長ラベルの順。`test/bench/avr/check_flash_buf.py` が全カテゴリの組み合わせをこの連鎖と突き合わせ、不足すれば失敗する（`make -C test bench` で実行）— 不足を指摘されたら分岐を足す。
#ifndef AZARAC_FLASH_BUF_SIZE
#if AZARAC_ENABLE_DCX_CAMF
// DCX/CAMF はさらに長いラベルを足す（a4_hazard_definition: 683 B）→ 800 B。
#define AZARAC_FLASH_BUF_SIZE 800
#elif AZARAC_ENABLE_EEW || AZARAC_ENABLE_HYPOCENTER
// 最長は 596 B（notification_on_disaster_prevention、JA）/ 515 B（EN）。
#define AZARAC_FLASH_BUF_SIZE 640
#elif AZARAC_ENABLE_NANKAI
// NANKAI の info-code 最長ラベルは 509 B（"調査中B"）。540 で余裕を持つ。
#define AZARAC_FLASH_BUF_SIZE 540
#elif AZARAC_ENABLE_VOLCANO || AZARAC_ENABLE_FLOOD
// 88 B（volcanic_warning_code、EN）と 78 B（flood_forecast_region、EN）。
#define AZARAC_FLASH_BUF_SIZE 96
#elif AZARAC_ENABLE_NW_PAC_TSUNAMI
// NW-PAC の最長ラベルは 72 B（英語の tsunamigenic potential）。80 で余裕を持つ。
#define AZARAC_FLASH_BUF_SIZE 80
#else
// SEISMIC/TSUNAMI の最長ラベルは 45 B。WEATHER/TYPHOON/MARINE と
// VOLCANO|ASH_FALL の地域表も 63 B 未満なので 64 で収まる。
#define AZARAC_FLASH_BUF_SIZE 64
#endif
// preset は Uno を 64 B に保つので、ここが効くのは長ラベルのカテゴリを上乗せしたときだけ: ラベルを正しく保つにはバッファを増やす必要があり、それは Uno の SRAM 2 KB を食う。
// 判断はユーザーに委ねるので warning に留める。
#if AZARAC_FLASH_BUF_SIZE > 256 && defined(ARDUINO_AVR_UNO)
#warning "AZARAC_FLASH_BUF_SIZE is large for the Uno's 2 KB SRAM — enable fewer categories, or shrink it knowing labels then truncate"
#endif
#endif
#endif // __AVR__

// normal defaults (non-AVR or overridden values)
#ifndef AZARAC_ENABLE_EEW
#define AZARAC_ENABLE_EEW 1
#endif
#ifndef AZARAC_ENABLE_HYPOCENTER
#define AZARAC_ENABLE_HYPOCENTER 1
#endif
#ifndef AZARAC_ENABLE_SEISMIC
#define AZARAC_ENABLE_SEISMIC 1
#endif
#ifndef AZARAC_ENABLE_NANKAI
#define AZARAC_ENABLE_NANKAI 1
#endif
#ifndef AZARAC_ENABLE_TSUNAMI
#define AZARAC_ENABLE_TSUNAMI 1
#endif
#ifndef AZARAC_ENABLE_NW_PAC_TSUNAMI
#define AZARAC_ENABLE_NW_PAC_TSUNAMI 1
#endif
#ifndef AZARAC_ENABLE_VOLCANO
#define AZARAC_ENABLE_VOLCANO 1
#endif
#ifndef AZARAC_ENABLE_ASH_FALL
#define AZARAC_ENABLE_ASH_FALL 1
#endif
#ifndef AZARAC_ENABLE_WEATHER
#define AZARAC_ENABLE_WEATHER 1
#endif
#ifndef AZARAC_ENABLE_FLOOD
#define AZARAC_ENABLE_FLOOD 1
#endif
#ifndef AZARAC_ENABLE_TYPHOON
#define AZARAC_ENABLE_TYPHOON 1
#endif
#ifndef AZARAC_ENABLE_MARINE
#define AZARAC_ENABLE_MARINE 1
#endif
#ifndef AZARAC_ENABLE_DCX_CAMF
#define AZARAC_ENABLE_DCX_CAMF 1
#endif

// duplicate suppression
// dedup テーブルの連想度: 1 セットあたり WAYS エントリ。
// 大きいほどハッシュ衝突に強く（生きている情報を誤って「新規」にしにくい）、小さいほど 1 判定が安い。
// AZARAC_DEDUP_SLOTS は割り切れる必要がある。
#ifndef AZARAC_DEDUP_WAYS
#define AZARAC_DEDUP_WAYS 8
#endif
// 512 スロット（64 セット x 8 way）= 4 KB。
// 受信機は有効時間内の情報をすべて保持する必要がある: 津波警報は 24 時間生き続け、気象は同時に複数の情報を運び得るため、生きた集合は数百件になる。
// 出荷中の DedupFilter を 2024 年の QZSS アーカイブ 30 日で実測（`make -C test dedup-realday`）: 同時に生きている情報のピークは 20..327（中央値 66）で、最悪日（2024-08-28、327 件）でも 256 スロットで再通知が残る — 実測の下限は 512。
// 静かな 1 日だけを見れば 128 で足りるように見えるが、足りない。
// MISSED（生きている警報を抑止した件数）はどの日・どの容量でも 0。
#ifndef AZARAC_DEDUP_SLOTS
#define AZARAC_DEDUP_SLOTS 512
#endif

// 1 情報のフォールバック有効時間（ミリ秒）: 窓内に再受信しなかった情報は重複扱いをやめる（アプリケーションノートv2 原PDF p.25 手順④'）。
// 配信終了条件のカテゴリ別表（p.26-27: 緊急地震速報 5分 / 震源・震度 2時間 / 津波 最大24時間 / 降灰 最大1時間 / 台風 3時間…）と MT=44 の A8 由来の窓は internal/DedupWindow.h にあり、この値を使うのはその表に無いカテゴリ（未割当・予約の災害種別、payload 未設定）だけ。仕様上の最長窓が 24 時間なので、表に無いカテゴリが生きている間に再通知されることはない。
#ifndef AZARAC_DEDUP_WINDOW_MS
#define AZARAC_DEDUP_WINDOW_MS 86400000UL  // 24 h
#endif

// Nankai Trough page buffer config
// MAX_PAGES 63 = 仕様最大ページ数（Pn/Pm は 6bit、1-63）なので、既定ではページ打ち切りが構造的に起きない（縮小の目安: 実観測の最大は 27）。
// BUFFERS 1 = 南海トラフは 1 電文として連続放送され、複数イベントが同時並行しない。
// 増やすのは同時追跡時のみ（RAM はバッファ数に比例）。
#ifndef AZARAC_NANKAI_MAX_PAGES
#define AZARAC_NANKAI_MAX_PAGES 63
#endif
#ifndef AZARAC_NANKAI_BUFFERS
#define AZARAC_NANKAI_BUFFERS 1
#endif

#if AZARAC_NANKAI_BUFFERS > 2 && defined(ARDUINO_AVR_UNO)
#warning "Nankai buffers may exhaust SRAM on Arduino Uno. Consider AZARAC_NANKAI_BUFFERS=1"
#endif

// PROGMEM 抽象化: AVR では const データを Flash に置く（デスクトップでは何もしない）。
// 使い方: const char s[] AZARAC_PROGMEM = "..."; AZARAC_PGM_READ_* / AZARAC_STRCPY_P ヘルパは 16 bit の progmem ポインタで Flash を指すため、Flash の先頭 64 KiB にしか届かない。
// より大きい Flash の品（ATmega2560 …）では avr-libc の far API（`pgm_get_far_address` + `pgm_read_*_far` / `memcpy_PF`）を使う — 定義表が FLASHEND > 0xFFFF でそうしている（internal/FlashString.h 参照）。
#ifdef __AVR__
#include <avr/pgmspace.h>
// 定義表を置く場所。avr-libc のリンカスクリプトは progmem クラスタの入力を入力順に .text の *先頭* へ並べ、Arduino のレシピはコア（core.a）を最後にリンクするので、そこに約 116 KiB の表（large-flash preset）を置くとコア自身の PROGMEM が 0xFFFF より上へ押し出される。そこはコアの 16 bit `pgm_read_byte(&digital_pin_to_port_PGM[pin])` が届かない領域で、pinMode/digitalWrite が誤ったポートを読む（test/bench/avr のコア代役を使った Mega 2560 のイメージで実測 — コアの表は 0x19F46、すなわち我々の表の直後に着地する）。
// そこで表は `.text.azaraC.<n>` に置く: どの avr-libc スクリプトも `*(.text.*)` を progmem クラスタとコードの両方より後に置くため、コアの表は低い位置に残る。
// `.progmemx.*` は使わない — このクラスタは binutils 2.29 以降のスクリプトにしか無く（PR 21849）、古い atmel 2.26 のスクリプト（Ubuntu の binutils-avr と Arduino ツールチェーン）には `.progmemx.*` のパターンが無く、広い `*(.progmem*)` がこの名前を低いクラスタへ飲み戻してしまう。まさに避けたい失敗そのもの（そこでも 0x19F46 を実測）。
// far で Flash を読む品だけが必要とする機能で、その場合セクションの位置は無関係。64 KiB 以下の品は素の PROGMEM のまま。
// 連番サフィックスは宣言ごとに 1 セクションを保つ（-fdata-sections が `__progmem__` データに対してするのと同じ）: 共有セクションだと、翻訳単位内の 1 つの表が参照された時点で --gc-sections が全体を残してしまう。また inline 関数内の関数ローカル static は one-only（weak）で出力され、通常の配列とはそもそもセクションを共有できない（"section type conflict"）。
#if FLASHEND > 0xFFFF && !defined(AZARAC_AVR_STUB)
#define AZARAC_PGM_STR_(x) #x
#define AZARAC_PGM_STR(x) AZARAC_PGM_STR_(x)
#define AZARAC_PROGMEM \
    __attribute__((__section__(".text.azaraC." AZARAC_PGM_STR(__COUNTER__))))
#else
#define AZARAC_PROGMEM PROGMEM
#endif
// 16 bit の素の Flash ポインタ（AZARAC_PGM_READ_*）で読む小さな定数表で、far アクセサは通さない。
// `PROGMEM` は .text 先頭の `*(.progmem*)` クラスタ（Arduino コア自身の表もここにいる）へ置くので 16 bit ポインタで届く。`AZARAC_PROGMEM` だと `.text.azaraC.<n>` へ移り、64 KiB 超のイメージではその窓より上に置かれてしまう。
// autoresearch.sh が両端を検査する: large-flash リンクではコアの代役 PROGMEM と azaraC 自身の near Flash 表が 0xFFFF 未満に留まること。
#define AZARAC_PROGMEM_NEAR PROGMEM
#define AZARAC_PGM_READ_BYTE(addr)    pgm_read_byte(addr)
#define AZARAC_PGM_READ_WORD(addr)    pgm_read_word(addr)
#define AZARAC_PGM_READ_DWORD(addr)   pgm_read_dword(addr)
#define AZARAC_PGM_READ_PTR(addr)     pgm_read_ptr(addr)
#define AZARAC_STRCPY_P(dst, src)     strcpy_P(dst, src)
#define AZARAC_STRNCMP_P(a, b, n)     strncmp_P(a, PSTR(b), n)
#else
#define AZARAC_PROGMEM
#define AZARAC_PROGMEM_NEAR
#define AZARAC_PGM_READ_BYTE(addr)    (*(addr))
#define AZARAC_PGM_READ_WORD(addr)    (*(addr))
#define AZARAC_PGM_READ_DWORD(addr)   (*(addr))
#define AZARAC_PGM_READ_PTR(addr)     (*(addr))
#define AZARAC_STRCPY_P(dst, src)     strcpy(dst, src)
#define AZARAC_STRNCMP_P(a, b, n)     strncmp(a, b, n)
#endif
