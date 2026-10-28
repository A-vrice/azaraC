#pragma once
// ビルド時設定マクロ。azaraC.h から分離し、定義ファイル群がマクロだけを読めるようにする。

// 言語選択マクロ
#ifndef AZARAC_LANG_JA
#define AZARAC_LANG_JA 1
#endif

#ifndef AZARAC_LANG_EN
#define AZARAC_LANG_EN 0
#endif

// 災害カテゴリの制御マクロ（下の AVR preset が先に既定値を入れるので、どちらの節でも #ifndef が機能する）。

// AVR などリソース制限向けの preset（バッファサイズとカテゴリを縮小）。
// 通常の既定値より前に置く。ユーザーの -D は両方の節でスキップされるので常に勝ち、AVR は縮小値、非 AVR は通常の既定値へ落ちる。
#if defined(__AVR__)
#ifndef AZARAC_NANKAI_MAX_PAGES
#define AZARAC_NANKAI_MAX_PAGES 4
#endif
#ifndef AZARAC_NANKAI_BUFFERS
#define AZARAC_NANKAI_BUFFERS 1
#endif
#ifndef AZARAC_DEDUP_SLOTS
// 64 スロット（8 セット x 8 way）= 512 B。
// 実測で再通知は 32x8 (256 B) まで 0 件、16x8 (128 B) で 93 件。32 未満へは縮めない。
#define AZARAC_DEDUP_SLOTS 64
#endif
#ifndef AZARAC_DEDUP_WAYS
#define AZARAC_DEDUP_WAYS 8
#endif
#ifndef AZARAC_DEDUP_MT44_MAX_WINDOW_MS
// MT=44 (DCX/CAMF) の窓の上限。
// A8 の窓（6 時間〜7 日、internal/DedupWindow.h）を AVR の 64 スロットで持つと、生きている情報の枠が長く占められて押し出しによる再通知が起きる。
// MT44 の再送は同一電文 2 回（まれに 3〜4 回）・間隔最大 16 秒なので 5 分で足りる。A8 の窓は最短 6 時間なのでこの上限は常に効く。
#define AZARAC_DEDUP_MT44_MAX_WINDOW_MS 300000UL  // 5 min
#endif
// DCX/CAMF は表だけで約 100 KB、decoder がさらに約 20 KB。256 KB Flash の品（ATmega2560 等）向け。
// チップ名で自動有効にはならない: すべての AVR 品は Uno と同じ SEISMIC/TSUNAMI 既定から始まり、-DAZARAC_AVR_LARGE_FLASH=1（この preset が想定する名前）か -DAZARAC_ENABLE_DCX_CAMF=1 でユーザーが有効化する。
// ライブラリは別の翻訳単位なので、スケッチに置いた #define は届かない。
// 64 KiB を超える表は internal/FlashString.h の far Flash アドレッシングも必要で、FLASHEND > 0xFFFF の品は自動的にそれを選ぶ。
// 残りカテゴリは大型品でも既定 off（全部同時で約 242 KiB）。同じ要領で -DAZARAC_ENABLE_EEW=1 等で有効化する。
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

// 定義表引き当て用の共有バッファ（internal/FlashString.h 参照）。カテゴリマクロより後に置く（preset でもサイズを選べるようにするため）。
// 収めるべき長さは「ラベルの出どころとなる全カテゴリの最長ラベル」。
// 表はそれぞれのガードで有効になりこの連鎖では決まらないので、ここに無いカテゴリは黙ってラベルを切り詰める（azarac_pgm_view は AZARAC_FLASH_BUF_SIZE - 1、UTF-8 の途中でも切る）。
// 各分岐の値は test/bench/avr/check_flash_buf.py（make -C test bench）が全カテゴリの組み合わせと突き合わせ、不足すれば失敗する。不足を指摘されたら分岐を足す。
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
// SEISMIC/TSUNAMI の最長ラベルは 45 B。WEATHER/TYPHOON/MARINE と VOLCANO|ASH_FALL の地域表も 63 B 未満なので 64 で収まる。
#define AZARAC_FLASH_BUF_SIZE 64
#endif
// ラベルを正しく保つにはバッファを増やす必要があり、それは Uno の SRAM 2 KB を食う。判断はユーザーに委ねるので warning に留める。
#if AZARAC_FLASH_BUF_SIZE > 256 && defined(ARDUINO_AVR_UNO)
#warning "AZARAC_FLASH_BUF_SIZE is large for the Uno's 2 KB SRAM — enable fewer categories, or shrink it knowing labels then truncate"
#endif
#endif
#endif // __AVR__

// 通常の既定値（非 AVR、または AVR preset を上書きしたとき）
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

// 重複排除 AZARAC_DEDUP_WAYS: 1 セットあたりのエントリ数（連想度）。大きいほどハッシュ衝突に強く（生きている情報を誤って「新規」にしにくい）、小さいほど 1 判定が安い。
// AZARAC_DEDUP_SLOTS は WAYS で割り切れること。
#ifndef AZARAC_DEDUP_WAYS
#define AZARAC_DEDUP_WAYS 8
#endif
// 512 スロット（64 セット x 8 way）= 4 KB。
// 受信機は有効時間内の情報をすべて保持する必要がある（津波警報は 24 時間生き、気象は同時に複数の情報を運ぶ）ので、生きた集合は数百件になる。
// 2024 年の QZSS アーカイブ 30 日実測（make -C test dedup-realday）での下限が 512: 256 スロットでは最悪日に再通知が残る。
// MISSED（生きている警報を抑止した件数）はどの日・容量でも 0。
#ifndef AZARAC_DEDUP_SLOTS
#define AZARAC_DEDUP_SLOTS 512
#endif

// 1 情報のフォールバック有効時間（ミリ秒）。窓内に再受信しなかった情報は重複扱いをやめる（アプリケーションノートv2 原PDF p.25 手順④'）。
// 配信終了条件のカテゴリ別表（p.26-27: 緊急地震速報 5分 / 震源・震度 2時間 / 津波 最大24時間 / 降灰 最大1時間 / 台風 3時間…）と MT=44 の A8 由来の窓は internal/DedupWindow.h。この値を使うのはその表に無いカテゴリ（未割当・予約の災害種別、payload 未設定）だけ。
// 仕様上の最長窓が 24 時間なので、表に無いカテゴリが生きている間に再通知されることはない。
#ifndef AZARAC_DEDUP_WINDOW_MS
#define AZARAC_DEDUP_WINDOW_MS 86400000UL  // 24 h
#endif

// 南海トラフ前沿のページバッファ MAX_PAGES 63 は仕様の最大ページ数（Pn/Pm は 6 bit、1-63）なので、既定ではページ打ち切りが構造的に起きない（実観測の最大は 27）。
// BUFFERS 1: 南海トラフは 1 電文として連続放送され、複数イベントが同時には進行しない。同時追跡する場合だけ増やす（RAM はバッファ数に比例）。
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
// 使い方: const char s[] AZARAC_PROGMEM = "...";
// AZARAC_PGM_READ_* / AZARAC_STRCPY_P は 16 bit の progmem ポインタで Flash を指すため、先頭 64 KiB にしか届かない。
// それ以上の Flash の品（ATmega2560 等）の定義表は avr-libc の far API を使う（pgm_get_far_address + pgm_read_*_far / memcpy_PF。FLASHEND > 0xFFFF で internal/FlashString.h が選択）。
#ifdef __AVR__
#include <avr/pgmspace.h>
// 定義表を置く場所。avr-libc のリンカスクリプトは progmem クラスタの入力を .text の先頭へ並べ、Arduino のレシピはコア（core.a）を最後にリンクする。
// 約 116 KiB の表をそこに置くとコア自身の PROGMEM が 0xFFFF より上へ押し出され、コアの 16 bit `pgm_read_byte(&digital_pin_to_port_PGM[pin])` が届かない領域に入り、pinMode/digitalWrite が誤ったポートを読む。
// そこで表は `.text.azaraC.<n>` に置く: どの avr-libc スクリプトも `*(.text.*)` を progmem クラスタとコードの両方より後に置くため、コアの表は低い位置に残る。
// `.progmemx.*` は使わない: binutils 2.29 以降（PR 21849）にしか無く、古い atmel 2.26（Ubuntu の binutils-avr、Arduino ツールチェーン）では広い `*(.progmem*)` が同じ名前を低いクラスタへ飲み戻す。
// 連番サフィックスは宣言ごとに 1 セクションを持たせるもの（-fdata-sections が `__progmem__` データにするのと同じ）。
// 共有セクションだと、1 つの表が参照されただけで --gc-sections が全体を残す。
// inline 関数内の関数ローカル static は one-only（weak）で出力され、通常の配列とはセクションを共有できない（"section type conflict"）。
// この配置は far で Flash を読む品だけが必要。64 KiB 以下の品は素の PROGMEM のまま。
#if FLASHEND > 0xFFFF && !defined(AZARAC_AVR_STUB)
#define AZARAC_PGM_STR_(x) #x
#define AZARAC_PGM_STR(x) AZARAC_PGM_STR_(x)
#define AZARAC_PROGMEM \
    __attribute__((__section__(".text.azaraC." AZARAC_PGM_STR(__COUNTER__))))
#else
#define AZARAC_PROGMEM PROGMEM
#endif
// 16 bit の素の Flash ポインタ（AZARAC_PGM_READ_*）で読む小さな定数表用。far アクセサは通さない。
// `PROGMEM` は .text 先頭の `*(.progmem*)` クラスタ（Arduino コア自身の表もいる）へ置くので 16 bit ポインタで届く。
// `AZARAC_PROGMEM` にすると `.text.azaraC.<n>` へ移り、64 KiB 超のイメージではその窓より上に置かれてしまう。
// test/bench/avr/autoresearch.sh（make -C test bench）が large-flash リンクで検査:
// コアの代役 PROGMEM と azaraC の near Flash 表が 0xFFFF 未満に留まること。
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
