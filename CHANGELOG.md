# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [1.0.3] - 2026-08-29

### Added

- **セキュリティ文書**: `SECURITY.md` を追加し、脆弱性報告ポリシーとリリース成果物の検証手順を明記した（#13）。

### Changed

- **未使用コードを削除**: 未使用の生成スクリプト、ヘルパ、型、シム、テストの冗長アサーションとコメントを削除し、`optional` / `string_view` シムを最小実装に整理した（#16）。
- **ドキュメントを整理**: `docs/architecture.md` の図を Mermaid に置換し重複する構成表を削除、`docs/getting-started.md` / `README.md` の重複する表を `docs/` へのリンクに集約、`docs/api-reference.md` の誤ったエラーコード表を削除した。`Dedup.h` の SVID 範囲コメントを `184–202` から `183–191` に訂正した。
- **コメントを簡潔化**: `TimeFields.h` / `Message.h` / `rtos_freertos.ino` のコメントを理由のみの記述に整理し、自動生成ヘッダの不要な接頭辞を除去した。
- **CI のボード表記を整理**: Arduino Uno のボード名から `(AVR)` 接尾辞を除去した。

### Fixed

- `avr_std/optional` に `operator*` / `operator->` を追加し、DCX 有効時の AVR ビルド破綻を解消した。`operator->` が `operator&` 過載型に誤動作する問題を `reinterpret_cast` に修正し、回帰テストを追加した。
- `AZARAC_DEDUP_SLOTS` / `AZARAC_NANKAI_BUFFERS` が 0 に上書きされた場合の modulo ゼロを防ぐ `static_assert` を追加した。
- `examples/rtos_freertos` で `aggregated_text_ptr` が `Parser` 内部バッファへの借用である旨と、受信後に JSON 変換してからキューへ積む推奨パターンを文書化した。
- `NankaiPageKey` に明示的初期化のための `constexpr` コンストラクタを追加した。
- `TimeFields.h` の `volatile` な 64-bit 変数の非アトミック競合による非単調返却・`s_last` 後退・エポック喪失の可能性を文書化した。
- `test/Makefile` の `memprof` ターゲットで valgrind 未導入時に `SKIP` が正しく表示されるよう修正した。
- `Mt43Data::initAs<T>()` にペイロード型の trivially copyable 検証を追加し、`Message::initPayload` に契約コメントを追記した。
- `UbxFramer.cpp` の `_len` 検証を `numWords * 4 + 8` との厳密一致に変更した。
- `NmeaFramer.cpp` の 250-bit 境界マスクを `0xC0` に修正した。
- `NankaiPageBuffer::clearAll()` で `aggregated_text` をゼロクリアするようにした。
- `library.json` と `library.properties` のバージョン乖離を検出する CI チェックを追加した。
- `examples/error_handling` の `to_unix_time()` を整数演算（Howard Hinnant）に置換し、AVR での軽量化と 32-bit `long` 環境での符号付きオーバーフローを解消した。
- `arduino-cli` Action のバージョン追跡を `@v2.0.0` 表記に修正した。
- `examples/rtos_freertos` の Nankai 集約コメントと `TimeFields.h` の説明を事実どおりに訂正した。

## [1.0.1] - 2026-08-20

### Added

- **Supply Chain 強化**: `release.yml` に Artifact Attestation と Scorecard ワークフローを追加し、リリース成果物の署名・検証パイプラインを整備した。
- **カバレッジ連携**: `ci.yml` で `gcovr` の JSON+XML 出力を単一実行に統合し、カバレッジのアップロードを追加した。`src/definition` を対象から除外した。

### Changed

- **CI・リリースワークフローを整備**: `ci.yml` の PlatformIO コンパイルテストを `compile-required`（RP2040 / ESP32-C3 / Uno の 3 代表）と `compile-extended`（残り 8 ボード, `continue-on-error`）に分類し、`concurrency` と `permissions: contents: read` を追加した。`update-definitions.yml` の PyPI フェッチにタイムアウトとリトライを追加した。
- **ドキュメントを再構成**: `docs/README.md` を `docs/getting-started.md` に改名し、`README.md` にバッジを追加した。PlatformIO 設定例をバージョン固定し、`build_unflags` を追加した。
- **品質設定を確定**: リント指摘を解消し、コード品質設定を追加した。`src/definition` を complexity / duplication 解析から除外した。

### Fixed

- **リリースワークフローを修正** (#11, #12): `private-repository` オーバーライドを追加し `verify` 成功後のみリリースを作成するよう順序を修正した。`sha256sum` の出力を bare hex 形式に修正した。
- **依存関係を更新**: `actions/checkout` v7, `actions/download-artifact` v8, `actions/upload-artifact` v7, `arduino/arduino-lint-action` v3, `github/codeql-action` の digest を更新した。

## [1.0.0] - 2026-08-14

### Changed

- **タグ付き共用体のコピー/破棄を簡略化**: `Mt43Data` / `Message` の手動タグ付き共用体について、全ペイロード型が trivially copyable かつ trivially destructible であることを利用し、`placement-new` + 12 分岐 `switch` による `destroyActive` / `copyFrom` / `moveFrom` を `memcpy`（コピー/ムーブ）とタグリセット（破棄）の 1–2 行に置換した。ムーブは trivial 型ではコピーと同値（送り元タグのみリセット）とした。`#include <utility>` を削除した。構造体レイアウトと外的 API は不変（`sizeof` ガードと全 368 件のテストおよび `pgm-stub` AVR パスで検証）とした。ヘッダに「全ペイロード型は trivially copyable + trivially destructible を維持すること」の契約コメントを追記した。
- **`NankaiPageBuffer` の共通化**: 1 ページあたりの有効長（NUL まで）を返す private ヘルパ `pageTextLength_()` を抽出し、`getTextLength()` / `getText()` の二重実装を解消した。
- **`Message::clear()` を追加**: デコード時の二重ゼロ初期化（`out = {}` 後の `initPayload` による約 350B の冗長 `memset`）を除去し、`Decoder::decode` と `Parser::postDecode` で `out.clear()` を用いるようにした。
- **冗長なフィールド再設定を削除**: `Decoder::decode` 内の `out.valid = false` / `out.payload_type = Empty` の再設定を削除した（`clear()` が設定済みのため）。
- **JSON シリアライザの冗長な `getMt43()` を除去**: 12 のサブシリアライザのシグネチャを `const Message&` から `const Mt43Data*` に変更し、呼出元で検証済みのポインタを渡すことで各関数内の `getMt43()` と null チェックを除去した。
- **`disaster_category` のディスパッチを `switch` 化**: `JsonSerializer::serialize` の 12 連 `if-else` を `switch` に変更し O(1) ディスパッチ化した。カテゴリ 7 / 13 は仕様上未定義とした。各 `case` は従来どおり `AZARAC_ENABLE_*` で個別にコンパイル制御する。
- **DCX B4 の D3/D4 出力を `writeDField` に統合**: `const char*` を返す D3/D4 ルックアップを `std::optional<std::string_view>` にアダプトし、他 34 フィールドと同じヘルパで出力するようにした。出力バイト列は不変（`test_json_dcx_b1b4.cpp` で検証）とした。
- **`processNankaiAggregation` の冗長な `getMt43()` を除去**: `postDecode` が取得済みの `Mt43Data*` を引数で渡すように変更した。
- **`a3_provider_identifier` のルックアップを高速化**: 34 エントリの O(n) 線形探索を O(log n) 二分探索に変更した。
- **定義テーブルの AVR (PROGMEM) 対応**: `src/definition/*.h` のラベル文字列を AVR では Flash に配置し、ルックアップ時に共有 RAM バッファ（`AZARAC_FLASH_BUF_SIZE`、既定 800B）へコピーして返す方式に変更した。非 AVR では従来の `constexpr` 実装を維持した。`scripts/gen/gen_definitions.py` の 6 エミッタに AVR 分岐を追加し、`scripts/gen/apply_avr_headers.py` で既存ヘッダを移行した。`test/stub/avr/pgmspace.h` と `make pgm-stub` でホスト検証する。CI に Arduino Uno (AVR) コンパイルチェックを追加した。
  - **FlashString 共有バッファを 1 個に統合**: `azarac_pgm_view` と `azarac_pgm_copy` がそれぞれ 800B の static バッファを持ち合計 1600B で Uno の 2KB SRAM を超過していた問題を、共通 `azarac_flash_buf()` 経由の 1 個に統合して解消した。AVR プリセットでは `AZARAC_FLASH_BUF_SIZE` を 64B に縮小した（SEISMIC / TSUNAMI 有効時の最大ラベル 30B 基準）。Uno 実測で RAM 使用量を 2836B から 1300B（63%）に削減した。
- **AVR 用最小 C++ 標準ライブラリシムを追加** (`src/internal/avr_std/`): Arduino AVR ツールチェーン（avr-gcc 7.3.0）が `libstdc++` を同梱しないため、`src/` と生成定義ヘッダの標準 include を `#if defined(__AVR__)` でシム（`cstdint` / `cstring` / `cstdio` の C ヘッダ委譲, `new` / `algorithm` / `iterator`, 最小 `optional` / `string_view`）へ切り替えるようにした。API は不変とした。`test/internal/test_avr_std_shim.cpp` で検証する。
  - Arduino.h の `min` / `max` 関数マクロ対策として `azaraC.h` で `#undef` し、`Message.h` の `std::max` を三項演算子に置換した。
  - **AVR プリセットでカテゴリを自動絞り込み**: `azaraC_config.h` の AVR プリセットで SEISMIC / TSUNAMI のみを既定有効とし、他 11 カテゴリは無効とした（`-D` / `#define` で上書き可能）。例題内の `#define` は別 TU のライブラリ `.cpp` に効かないため撤去し、config レベルで一括適用するようにした。
  - Uno ジョブでは AVR 対応の基本 3 例題（`basic_ubx` / `basic_nmea` / `basic_uno`）でライブラリ全体をコンパイル検証する（他例題は `Serial1` 依存または容量不足のためスキップ）。
  - **`AZARAC_DEDUP_SLOTS` の既定値を `config` に一本化**: `Dedup.h` が独自に `#define 8` を持ち `Dedup.cpp` で AVR プリセット（4）と不一致になり LTO が `array types have different bounds` を検出していた問題を、`config` include と重複既定値の削除で解消した。
  - **CI のボード分類をアーキテクチャ代表制に整理**: `compile-required`（リリースゲート）を RP2040 Pico (ARM) / ESP32-C3 (Xtensa) / Arduino Uno (AVR) の 3 台とし、`compile-extended`（ベストエフォート, `continue-on-error`）を残り 8 台とした。
- **CI の権限と例題を整理**: CI にトップレベル `permissions: contents: read` を追加した。例題 `basic_nmea` / `basic_ubx` の `loop()` を `Stream& gnss` エイリアスで統一し重複 `while` ループを削除した。`avr_std/string_view` シムの `strlen` を `constexpr` ヘルパ化し `compare` を unsigned char 比較に、`find` の境界比較を減算ベースにしてオーバーフローを回避した。`Dedup.h` / `Mt44Data.h` の `cstdint` AVR 分岐を `MtCommonTypes.h` に一本化した。`writeEscaped` の `snprintf` を `std::snprintf` に統一した。AVR `pgmspace.h` スタブの `pgm_read_word` / `pgm_read_dword` を `memcpy` ベース化した。`DecodedEllipse` のフィールド名を実単位にリネームした（`lat_deg` → `lat_microdeg`, `semi_major_km` → `semi_major_m`, `azimuth_deg` → `azimuth_decideg` 等および `b1RefinedRadiusKm` → `b1RefinedRadiusM`）。JSON 出力は不変とした。`AZARAC_FLASH_BUF_SIZE` の AVR 既定値を DCX/CAMF 有効時は 800B、それ以外は 64B に条件分岐した。
- **AVR プールの NUL エスケープを修正**: 定義テーブル生成スクリプトがプール区切り NUL を `\0` と出力し、後続が数字始まりのラベル（例: `"112.5"`）と連結して 8 進エスケープ化（`\011` 等）されていた問題を `\000`（3 桁）に修正し、既存ヘッダ 44 ファイルを修復した。非 AVR は影響なしとした。
- **MT=43 カテゴリ定義を X-macro で一元化**: `DecoderQzqsm` のカテゴリサポート判定・既知分類・サブデコーダディスパッチを単一の `AZARAC_DC_CATEGORIES` テーブルから生成し、`Decoder.h` のサブデコーダ宣言を無条件化した。
- **コメントと実装の乖離を修正 (S2)**: `DcxHelper.h` の B1 ビットレイアウトコメント（`a18[14:12]` 始まりの MSB 順に修正）、`DcxHelper.cpp` の B2 delta 式（code 64..127 の切り上げを明記）、`UbxFramer.h` / `cpp` の `sigId`（`∈{0,1}`）と 8 ワード目末尾 6 ビット（`parity` → `padding`）、`NmeaFramer.cpp` の 252-bit（250 data + 2-bit ゼロ詰め）記載、`Parser.h` の `getNankaiBuffer` 戻り値説明、`NankaiPageBuffer.h` の `clear()` 説明、`DecoderDcx.cpp` の spec 版数（DCX-003 → DCX-004, EWSS CAMF v1.1/v1.2 注記）を修正した。
- **死んだマクロを削除**: 実コードで未使用だった `AZARAC_DCX_USE_FLOAT` と `AZARAC_NANKAI_AGGREGATED_TEXT_SIZE` を `azaraC_config.h` 等から削除し、関連コメントと `test/Makefile` の `-D` フラグを除去した。
- **`PrintShim.h` の欠落オーバーライドを追加**: ホストテスト用 `StringPrint` に `print(const void*)` の `override` を追加し、未オーバーライド時に基底の `fputs` で stdout に漏出していた問題を修正した。
- **降灰 `warning_type_label` の誤ラベルを修正**: `warning_type`（IS-QZSS-DCR-016 Table 4.1.2-35 の `Dw1`、1=速報/Preliminary, 2=詳細/Detailed）に降灰コードテーブル（Table 4.1.2-36: 1=少量の降灰, 2=やや多量の降灰）を誤用していた問題を修正した。Warning Type 用ラベル関数 `ashFallWarningTypeLabel()` を追加し正しい「速報/詳細」を出力するようにした（azarashi 0.16.4 と同挙動）。

### Added

- **ラベル文字列出力のテストを追加**: `test/json/test_json.cpp` の全 QZQSM カテゴリ（EEW / Hypocenter / Seismic / Nankai / Tsunami / NWPac / Volcano / AshFall / Weather / Flood / Typhoon / Marine）に `_label` フィールドのアサーションを追加した（+36 件）。降灰の `warning_type_label` は修正後の「速報」を検証する。
- **azarashi ラベル突合を復活**: `test/scripts/compare_with_azarashi.py` に `LABEL_MAPPING` を追加し、`_ignore` でスキップしていた約 20 種のラベル文字列（`disaster_category`, `report_classification`, `information_type`, `seismic_intensity_*`, `eew_forecast_regions`, `tsunami_*`, `marine_*`, `local_governments` 等）を azarashi と直接比較するようにした。realdata 全 974 メッセージで 0 差分を確認した。
- **`DecoderQzqsm.cpp` に仕様節番号を追記**: 12 のサブデコーダのブロックコメントに IS-QZSS-DCR-016 の節番号（§4.1.2.3.2–§4.1.2.3.13）を追記した。

### Fixed

- **`examples/with_sntp/with_sntp.ino` のコンパイルエラーを修正**: `DecodedEllipse` のフィールド名リネーム（`lat_deg` → `lat_microdeg` 等）に追随し、`lat_microdeg / 1000000.0` で度単位表示を維持するようにした。
- **ラベルテーブルのマクロ跨ぎ依存を修正（サイレント空ラベル）**: 定義テーブルのガードが参照先シリアライザの有効化マクロをカバーしていない 2 箇所を修正した。`qzss_dcr_jma_volcano_name` を `AZARAC_ENABLE_VOLCANO` から `(|| AZARAC_ENABLE_ASH_FALL)` に、`qzss_dcr_jma_prefecture` を `AZARAC_ENABLE_SEISMIC` から `(|| AZARAC_ENABLE_DCX_CAMF)` に拡張した（`gen_definitions.py` の `GUARD_MAP` と生成済みヘッダの両方）。`VOLCANO=0` / `SEISMIC=0` のマクロ無効化ビルドでも降灰の `volcano_name_label`・DCX の `prefecture_labels` が空にならないようにした。
- **生成定義テーブルの疎キー array バグを修正（ラベルズレ）**: `scripts/gen/strategy.py` の `choose()` が `fill_ratio ≥ 0.6` の疎キー辞書を `id - BASE` で索引する array 戦略に落とし、欠番以降の全エントリのラベルがズレていた問題を修正した。`fill ≥ 0.6 && span == n`（キー連続）の場合のみ array を選択するようにし、`disaster_category`（8=火山が降灰に化けていた）、`eew_forecast_region`（80=その他府県予報区）、`seismic_intensity_{lower,upper}_limit`、`coastal_region_en` の 6 テーブルを `binary_search` に切り替えた。定義ヘッダを azarashi 0.16.4 で再生成した。
- **`DecoderDcx.cpp` の `onset_time` 閾値を修正**: UNIX 時刻比較定数を `315964800u`（1980-01-06, GPS エポック）から `946684800u`（2000-01-01）に修正した。
- **`NankaiPageBuffer.h` の未初期化を修正**: `NankaiPageKey` の fallback フィールドに `= 0` 既定初期化子を追加した。
- **OOB 検出テストの偽陰性を修正**: `TestDecoder` の各 static ラッパが別々の `Decoder` インスタンスを作成していたため `clearOob()` → `extractBits()` → `checkOob()` 間で OOB フラグが共有されず常に失敗していた問題を、共有 `inst()` アクセサに統一して修正した。
- **DCX メイン楕円 JSON テストの精度不一致を修正**: `writeDouble` が `precision=6` で `35.600000` を出力するのに対しテストが `35.600`（3 桁）を期待していた不一致を、期待値を `35.600000` に修正して解消した。

## [0.13.0] - 2026-07-28

### Added

- **DCX 座標の `float` 切替マクロを追加**: `AZARAC_DCX_USE_FLOAT` を追加し、`DecodedEllipse` のサイズを 72B から 36B に削減可能にした（`Mt44Decoded` で 72B 節約）。
- **メモリ使用量表を追記**: `README.md` に RAM 要件表を追記し、`Parser.h` に最小 RAM 要件コメントを追加した。
- **コンパイル時警告を追加**: Arduino Uno で `AZARAC_NANKAI_BUFFERS` が多すぎる場合に `#warning` を出力するようにした。

### Changed

- **`NankaiData::aggregated_text[]` をポインタ化** (最重要): 固定配列 `aggregated_text[217]` を `const char* aggregated_text_ptr` + `uint16_t aggregated_len` に置換した。`NankaiData` のサイズを約 250B から 33B に、`Message` 全体を約 408B から約 190B に削減した（約 53% 減）。実テキストは `NankaiPageBuffer::aggregated_text[]` に保持し完了時にポインタを設定する。次の `Parser::feed()` 呼び出し前に `Message` を消費する必要がある（既存契約と整合）。`aggregated_text_ptr` は `NankaiPageBuffer` の raw per-page バッファを指す借用ポインタである点に注意する。
- **`B4DetailedInfo` の戻り値を出力パラメータに変更**: `decodeB4DetailedInfo()` が 108B の構造体を値返ししていたのを参照パラメータに変更し、スタックコピーを回避した。
- **`NankaiPageKey` のフィールド順序を最適化**: `uint32_t event_time_unix` を先頭に移動しパディングを削除した（12B → 8B）。
- **`NankaiPageBuffer` のフィールド順序を最適化**: `uint64_t` メンバを先頭に集め、`uint8_t` / `bool` メンバを後方に配置しパディングを削減した（バッファあたり約 7B 削減）。
- **不要な標準ライブラリ依存を除去**: `JsonWriter.cpp` から `<cmath>` を除去し `std::isnan` / `std::isinf` を `v != v || v > 1e308 || v < -1e308` に置換した。`Mt43Data.h` から `<algorithm>` を除去し `std::max({...})` を `constexpr` lambda に置換した。`DcxHelper.cpp` の全 `static const double` を `static constexpr double` に変更した。
- **`DcxHelper.cpp` の decode 関数を `dcx_real_t` に移行**: `AZARAC_DCX_USE_FLOAT` 有効時は `float` を用いるようにした。

### Fixed

- **Nankai E2E テストを修正**: NUL バイト打ち切りテストをポインタ化後の raw buffer 動作に合わせて修正した。
- **DCX JSON テストを修正**: `float` モード時の精度差に対応した（`#ifdef AZARAC_DCX_USE_FLOAT` で期待値を切替）。
- **OOB 検出テストの偽陰性を修正**: `TestDecoder` の共有 `inst()` 化により OOB 検出が常に失敗していた問題を修正した。
- **DCX メイン楕円 JSON テストの精度不一致を修正**: 期待値を `35.600000` に修正した。

## [0.12.0] - 2026-07-16

### Added

- **`truncated` フラグを追加**: `NankaiData` に `bool truncated` を追加し、`total_pages` が `AZARAC_NANKAI_MAX_PAGES` を超えた場合にセットされるようにした。
- **`isContiguous()` メソッドを追加**: `NankaiPageBuffer` にビットマップ連続性チェックを追加し、受信済みページが番号順に欠落なく連続しているかを O(1) で判定可能にした。

### Changed

- **`NankaiPageBuffer` を単一バッファ + ビットマップ方式に刷新**: 2 重バッファ構造（`PageData[]` + `aggregated_text[]`）を廃止し `aggregated_text[]` に直接ページを書き込む方式に変更した。受信済みページの追跡を 64-bit ビットマップで行い重複チェックを O(n) から O(1) ビットテストに高速化した。ページソートを不要化（オフセット書き込みのため）し、コード行数を約 140 行から約 100 行に削減した。
- **`AZARAC_NANKAI_AGGREGATED_TEXT_SIZE` を自動導出化**: 既定値を `AZARAC_NANKAI_MAX_PAGES * 18 + 1` から自動計算するように変更し、ユーザは `AZARAC_NANKAI_MAX_PAGES` のみ設定すればよいようにした。明示的上書きは `#ifndef` ガードで引き続き可能とした。`Mt43Data.h` の冗長な既定値（`217`）を削除した。

### Fixed

- **`total_pages > AZARAC_NANKAI_MAX_PAGES` で全ページが破棄されるバグを修正**: 旧実装では `total_pages` が設定値を超えると即座に `false` を返し全ページが失われていたが、`total_pages` を `MAX_PAGES` にキャップし収まる分だけ受け入れ、超過時は `truncated` フラグで通知するようにした。
- **`getTextLength()` / `getText()` の防御的修正**: 完了バッファ以外で呼ばれた場合に未受信ページのゴミデータを読む可能性を排除し、ビットマップをチェックして受信済みページのみを処理するようにした。

## [0.11.0] - 2026-07-14

### Added

- **軽量設定ヘッダ `azaraC_config.h` を追加**: コンパイル時マクロを分離し、定義ファイル（103 ファイル）からの依存を `azaraC.h` 全体から `azaraC_config.h` のみに削減した。定義ファイルが `Message.h` → `Mt43Data.h` → `NankaiPageBuffer.h` などのライブラリ本体をプルしなくなった。ユーザ向け API は `#include <azaraC.h>` のまま変更なしとした。
- **災害カテゴリ別コンパイル除外マクロを追加**（全 13 種）: `AZARAC_ENABLE_EEW`, `AZARAC_ENABLE_HYPOCENTER`, `AZARAC_ENABLE_SEISMIC`, `AZARAC_ENABLE_NANKAI`, `AZARAC_ENABLE_TSUNAMI`, `AZARAC_ENABLE_NW_PAC_TSUNAMI`, `AZARAC_ENABLE_VOLCANO`, `AZARAC_ENABLE_ASH_FALL`, `AZARAC_ENABLE_WEATHER`, `AZARAC_ENABLE_FLOOD`, `AZARAC_ENABLE_TYPHOON`, `AZARAC_ENABLE_MARINE`, `AZARAC_ENABLE_DCX_CAMF` を追加した。各 `#define` を 0 に設定すると対応する定義テーブルがコンパイル時に完全除外される。
- **実データテスト基盤を追加**: `test/tools/decode_to_json.cpp`（NMEA → JSON 変換 CLI）、`test/scripts/compare_with_azarashi.py`（azarashi 比較）、`test/scripts/gen_realdata_vectors.py`（ベクタ自動生成）、`test/integration/test_realdata.cpp`（統合テスト）を追加した。
- **南海トラフ E2E テストを追加**: `test/integration/test_nankai_e2e.cpp` と `test/scripts/compare_nankai_aggregation.py` を追加した。
- **ファズテストを追加**: `test/fuzz/fuzz_decoder.cpp` を追加した。
- **テストケースを拡充**: フレーマーテストで複数 `svId` / チェックサムエラー 2 方式 / ガベージリカバリ複数 `svId` を追加し、JSON テストで A9/A10/A11 境界値 / Nankai 集約後 `text_utf8` 出力 / `unix_time=0` 出力を追加し、azarashi 比較テスト（`test_ublox_azarashi.cpp` 等）を追加した。
- **`Makefile` にターゲットを追加**: `decode`（`decode_to_json` ビルド）と `compare-realdata`（azarashi 比較実行）を追加した。

### Changed

- **IS-QZSS-DCX-004 / EWSS CAMF v1.2 対応**: コメント・ドキュメントの参照仕様を IS-QZSS-DCX-003 から IS-QZSS-DCX-004 に、EWSS CAMF v1.1 から v1.2 に更新した。
- **azarashi v0.16.4 対応**: 各種リファクタに追随し、定義ヘッダを azarashi 0.16.4 で再生成した。
- **B1 リファインメントを修正 (EWSS CAMF v1.2 §3.7.1.3/4 準拠)**: `Message.h` の `b1_major_factor` / `b1_minor_factor` を `b1_refined_semi_major_km` / `b1_refined_semi_minor_km` に変更し、`DcxHelper::b1InterpolationFactor()` を廃止して `b1RefinedRadiusKm()`（`base_radius_km - delta_km * (code / 8.0)`）を新設した。旧実装は補間係数（0.0–0.875）を出力していたが、正しくは refinement 後の半径（km）を出力するようにした。
- **B2/B3 のビット抽出を修正**: `DecoderDcx.cpp` で B2 C5/C6 のビットシフト位置を修正し（`>>0` → `>>8`, `>>7` → `>>1`）、B3 C7/C8/C9/C10 のビットシフト位置を修正した（`>>0` → `>>13`, `>>2` → `>>10`, `>>5` → `>>5`, `>>10` → `>>0`）。
- **B4 を独立デコード化**: `DecoderDcx.cpp` で B4 をメイン楕円（A12–A16）の有無に関わらず独立してデコードするようにした。
- **JSON シリアライゼーションを改善**: `JsonSerializerDcx.cpp` で `a4_hazard_definition` フィールドを追加し `a9_selection_of_library` を `a9_type_of_library` に、`a17_specific_subject` を `a17_type_of_specific_settings` に改名し、`c10_guidance_label` を `c10_guidance_label` + `c10_guidance_code` に分割し、J-Alert の `city_labels` 出力を追加し、B1 refinement の JSON キーを変更した（`c3_major_factor` → `c3_refined_semi_major_km` 等）。`JsonSerializerQzqsm.cpp` で降灰情報に `warning_type_label` を追加した。
- **定義ファイルを更新**: azarashi 0.16.4 に対応し、ファイル名を仕様書の正式名称に合わせてリネームした（`a9_selection_of_library` → `a9_type_of_library` 等）。未使用の A3 プロバイダ別ファイル・EX9 ファイルを `_index.h` から削除し 92 定義に整理した。
- **`Parser::feed()` をリファクタ**: `feed()` 内部のカスタムフレーマ経路と AUTO モード経路で重複していたデコード後処理を `postDecode()` メソッドに抽出し、Nankai 集約 → Dedup チェック → コピーのパイプラインを 1 箇所に統一した。
- **`B4DetailedInfo` / `Mt44CamfRaw` の B4 フィールドを配列化**: D1–D36 の 72 個の個別フィールドを `b4_d_present[36]` + `b4_d_values[36]` に統合し、`DecoderDcx.cpp` の 72 行の手動初期化/コピーを `memset` / `memcpy` に置換した（約 140 行削減）。`DcxHelper.cpp` と `JsonSerializerDcx.cpp` を配列インデックスアクセスに統一した。
- **`azaraC.h` の未使用マクロを削除**: `AZARAC_ENABLE_QZSS_DCR_PREAMBLE` を削除した。

### Fixed

- **ビルドシステムを修正**: `test/Makefile` の Windows でのメモリ割り当てを増強した（スタック 64MB → 256MB, ヒープ 256MB → 512MB）。
- **CI/CD のセキュリティを強化**: `.github/workflows/ci.yml` の全 `actions/checkout` ステップに `persist-credentials: false` を追加した。

### Removed

- `.plans/` ディレクトリ（計画ドキュメント）を削除した。
- `data/` ディレクトリの実データ CSV / MD ファイルを削除し `realdata/` に移行した。

---

## [0.10.0] - 2026-06-27

### Changed

- **DCX-004 の小数点以下保証に準拠**: `JsonWriter::wf_d` に `precision` パラメータを追加し（既定 3、後方互換性維持）、緯度・経度フィールド（`lat_deg`, `lon_deg` 等）を 1e-6 度（小数点以下 6 桁）に、角度フィールド（`azimuth_deg`, `bearing_deg`）を 1e-5 度（小数点以下 5 桁）に変更した。距離フィールド（`semi_major_km` 等）は 1m = 0.001km（小数点以下 3 桁）のまま維持した。
- `library.properties` の `version` を `0.10.0` に更新した。
- `README.md` の仕様書リファレンスを IS-QZSS-DCX-004 / EWSS CAMF v1.2 に更新し、JSON 出力例を DCX-004 準拠の精度に更新した。

### 仕様準拠

- IS-QZSS-DCX-004 に準拠（May, 2026）し、General Assumptions §2.5 の丸めルールを適用した（緯度・経度: 10⁻⁶ 度、角度: 10⁻⁵ 度、距離: 1m）。

---

## [0.9.0] - 2026-06-25

### Changed

- **タグ付き共用体を `placement-new` ベースに移行**: `Message.h` / `Mt43Data.h` のタグ付き共用体を raw storage + `placement-new` / 明示デストラクタ方式に移行し、旧来の共用体メンバ直接アクセスを廃止した。`Parser.cpp` の Nankai 集約パスと dedup パイプラインを `getMt43()` / `getNankai()` アクセサ経由に統一した。
- **NMEA / UBX フレーマの SVID 正規化を改善**: `NmeaFramer.cpp` で QZQSM SVID（55–63）を L1S PRN（183–191）に変換するロジックを追加し、64 hex 文字（32B）入力の末尾ニブルを `0xF0` でマスクする処理を追加した。`UbxFramer.cpp` で `definition/_index.h` の `ublox_qzss_svid_prn_map` を用いた PRN 変換に対応した。
- **テストの一部を整理・統合**: 旧テストファイル（`test_crc.cpp` 等）を機能別サブディレクトリに統合した。
- **`.gitignore` を更新**: `.plans/` と `data/` を追加した。

### Fixed

- **Parser の Nankai 集約パスのエイリアシング対策を強化**: `decoded` と `out` を別オブジェクトとして扱い、`processNankaiAggregation` 内でのエイリアシング UB を回避するようにした。

## [0.8.0] - 2026-06-19

### Added

- **南海トラフページ集約機能を追加**: `NankaiPageBuffer` / `NankaiPageBufferManager` によるスパースページ対応のメモリ効率の良い集約バッファを実装し、`Parser` に複数ページにまたがる南海トラフ地震メッセージの集約ロジックを追加した。`test/integration/test_nankai.cpp` を追加した。
- **RTOS (FreeRTOS) 対応を追加**: `examples/rtos_freertos/` に FreeRTOS 環境での NMEA / UBX 同時処理サンプルを追加した。
- **JsonWriter ユーティリティを追加**: `src/internal/JsonWriter.h` / `JsonWriter.cpp` にプリミティブ型・共通データ構造の JSON シリアライズヘルパを追加した。
- **PrintShim のホストテスト対応を追加**: `src/internal/PrintShim.h` にホストサイドテスト向けストリーム出力オーバーロードを追加した。
- **ファズテスト基盤を追加**: `test/fuzz/fuzz_decoder.cpp` を追加した。
- **カテゴリフィルタリングサンプルを追加**: `examples/filter_by_category/` を追加した。
- **定義ファイル自動生成パイプラインを強化**: `scripts/gen/gen_definitions.py` の改善と CI ワークフロー（`update-definitions.yml`）を更新した。
- **CI/CD を拡充**: ホストテスト・ファズテスト・多プラットフォーム Arduino コンパイルを統合した GitHub Actions ワークフローと CodeQL セキュリティ解析ワークフローを追加した。

### Changed

- `library.properties` の `version` を `0.8.0` に更新した。
- `src/Parser.cpp` に南海トラフページ集約ロジックを統合した。
- `src/internal/JsonSerializer.h` / `JsonSerializer.cpp` を JsonWriter ユーティリティと統合した。
- `examples/` 全般のサンプルを API の一般的な使い方に合わせて改善した。
- `TimeFields.h` の時刻フィールド処理を更新した。
- `.gitignore` にネットワーク関連ファイル・CI 関連ファイルを追加した。

### Fixed

- ESP32-C3 での `Serial2` 設定を修正した。
- 一部ボード定義でのオプション名を修正した。
- `README.md` の UTF-8 文字化けを修正した。

---

## [0.7.0] - 2026-06-07

### Added

- **Error Handling サンプルを追加** (`examples/error_handling/error_handling.ino`): MT=44 メッセージのパース失敗を検出してエラー内容を出力するサンプルを追加し、`ParseResultCode` と `error_detail` を用いた具体的なエラーハンドリング方法を提示した。エラーコード一覧（001–007, 100–109）に対応するロジックを実装した。
- **DCX A17 B2/B3/B4 を実装** (EWSS CAMF v1.1 §3.7.2–3.7.4): `DcxHelper.cpp` に `decodeB2HazardCenter()` / `decodeB3SecondaryEllipse()` / `decodeB4DetailedInfo()` を追加し、`DcxHelper.h` に `B2HazardCenter` / `B3SecondaryEllipse` / `B4DetailedInfo` 構造体を追加した。`Message.h` の `Mt44CamfRaw` に B2/B3/B4 フィールドを追加し、`DecoderDcx.cpp` で A17=01/10/11 の場合の解析処理を実装し、`JsonSerializerDcx.cpp` で JSON 出力を追加した。

### Changed

- **ディレクトリ構造をリファクタ**: `include/` ディレクトリを作成して Arduino 配布用ヘッダを分離し、`src/` をテスト用実装ディレクトリに再編成した（`src/decoder/` / `src/framer/` / `src/json/` / `src/helper/` 等）。`test/` を機能別サブディレクトリに整理し、旧テストファイル（`test_crc.cpp` 等）を新テストファイルに統合した。`src/definition/` の重複を削除し、`library.properties` に `includes=azaraC.h` を追加した。
- `DecoderDcx.cpp` の B2/B3 ビット抽出を B1 と同じパターン（LSB から順）に統一した。
- `DcxHelper.cpp` の B4 各ハザード D フィールドのビット配置を EWSS CAMF v1.1 §3.7.4 と整合させた。
- `DecoderDcx.cpp` の B2/B3/B4 フィールド初期化を追加（ゼロクリア）した。
- `DecoderDcx.cpp` の構文エラー返却コードを `ParseResultCode::Error` に変更した。
- `DecoderDcx.h` の `parse_result` の型を `ParseResultCode` に変更し旧 `Error` 型を削除した。
- 既定の重複除去スロット数を 8 に再設定した。
- 言語テーブルの選択的コンパイルオプションを追加した。

### Fixed

- `DecoderDcx.cpp` の B3 未使用変数警告を `(void)` キャストで修正した。

### Documentation

- **エラーハンドリングガイドを追加**: エラーハンドリングセクションに全エラーコード一覧（001–007, 100–109）、デコード失敗理由ごとの具体的なハンドリング方法、デコード成功・失敗のフロー図、MT44/MT43 共通の処理フローを追記し、`examples/error_handling/error_handling.ino` で実践的に解説した。

### 仕様準拠

- EWSS CAMF v1.1 §3.7.2–3.7.4 に準拠し、A17=01 (B2) / A17=10 (B3) / A17=11 (B4) のデコードに対応した。

---

## [0.6.0] - 2026-05-31

### Added

- **DCX A17 B1 (Improved Resolution of Main Ellipse) を実装** (EWSS CAMF v1.1 §3.7.1): `DcxHelper.cpp` に `decodeB1Refinement()` / `b1RefinedLatitudeOffset()` / `b1RefinedLongitudeOffset()` / `b1InterpolationFactor()` を追加し、`DcxHelper.h` に `B1Refinement` 構造体を追加した。`Message.h` の `Mt44CamfRaw` に B1 フィールド（`b1_present`, `b1_c1`–`b1_c4`）を追加し、`Message.h` の `DecodedEllipse` に B1 リファインメント値を追加した。`DecoderDcx.cpp` で A17=00 の場合の B1 解析処理を実装した。

### Changed

- `DecoderDcx.cpp` の Null Message 検出時の Extended Message チェックを `getBits` を用いるように修正し、ビット境界の正確性を向上させた。

### 仕様準拠

- EWSS CAMF v1.1 §3.7.1 に準拠し、A17=00 (B1) のデコードに対応した。

---

## [0.5.0] - 2026-05-27

### Added

- **DCX MT44 デコーダを IS-QZSS-DCX-003 完全準拠でリファクタ**: `DecoderDcx.cpp` を仕様書どおりのビット配置（PAB|MT|SD|CAMF|EX|Reserved|CRC）で再実装した。`A2 Country/Region Name` および `A3 Provider Identifier` に基づくサービス種別判定ロジック（L-Alert, J-Alert, Local Government, Outside Japan, Null Message, Unknown）を実装し、Extended Message のサービス種別ごとの個別パース処理を実装した（L-Alert/Local Government: `EX1..EX7 + Vn`、J-Alert: `EX8..EX10 + Vn`、Outside Japan: `EX11(68bit raw) + Vn`）。`Message.h` に `Mt44Decoded` 構造体にデコード済み楕円座標（`DecodedEllipse`）、追加領域（`DecodedAdditionalArea`）、アラート識別子（`Mt44AlertIdentity`）を追加し、`DecodedEllipse` / `DecodedAdditionalArea` / `Mt44AlertIdentity` 構造体を新規定義した。
- **DcxHelper 関数を追加**: `decodeLatitude16()`（16-bit 緯度 → WGS84 度）、`decodeLongitude17()`（17-bit 経度 → WGS84 度）、`decodeLatitude17()`（17-bit 緯度, EX3 用）、`decodeLongitude17_45_225()`（17-bit 経度, 45–225 度範囲）、`decodeRadiusCode()`（5-bit 半径 → km, Table 4.2-17 対数テーブル）、`decodeAzimuth6()`（6-bit 方位角 → 度）、`decodeAzimuth7()`（7-bit 方位角, EX7 用）、`decodePrefectureBitmask()`（EX9 64-bit から都道府県ビットマスクをデコード）、`decodeCityCodeList()`（EX9 64-bit から市区町村コードリストをデコード）を追加した。
- **テストファイルを追加**: `test/test_dcx_helper.cpp`（DcxHelper 全関数）、`test/test_latlon.cpp`（`extractLatLon`）、`test/test_decoder.cpp`（DCX MT44 デコード全サービス種別および `decodePrefectureBitmask`）を追加した。

### Changed

- **J-Alert 都道府県デコードバグを修正** (`check.md` に基づく): `DcxHelper.cpp::decodePrefectureBitmask()` の EX9[63:17] に格納される 47-bit 都道府県フィールドの抽出ロジックを修正し（`ex9 >> 17` で右シフトしてから検査）、JIS コード計算を `47 - i` から `i + 1` に修正した（bit 0 = 北海道/JIS 1）。
- `Message.h` の `Mt44CamfRaw` の `a12` / `a13` のコメントを「unsigned, latitude/longitude code」に更新した。
- `Message.h` の `Mt44ExLAlertOrLocal` の `ex3` / `ex4` のコメントを「unsigned」に更新した。

### Fixed

- `DecoderDcx.cpp` の A12/A13 の符号付きパース（2 の補数）を符号なしパースに修正した（IS-QZSS-DCX-003 仕様準拠）。
- `DecoderDcx.cpp` の EX3/EX4 の符号付きパースを符号なしパースに修正した。

### 仕様準拠

- IS-QZSS-DCX-003 に完全準拠し、サービス種別（Service Kind）の識別ロジックを A2 Country および A3 Provider に基づいて実装し、階層構造化された CAMF のパース処理を刷新した。

---

## [0.4.0] - 2026-05-20

### Added

- **テストスイートを拡充**: `test/test_ublox.cpp`（u-blox SFRBX パケットのデコーダ動作検証および NMEA 出力との整合性確認）と `test/test_coverage.cpp`（MT=43 各防災カテゴリの詳細フィールド検証、年末年始・うるう年等の日付境界テスト、NMEA 文字数上限や不正プリアンブル等の異常系エッジケース）を追加した。
- **デコーダ内部共通処理を共通化**: `Decoder::readNotifications()`（9-bit 防災気象情報通知コード読み出し）、`Decoder::resolveArrivalTime()`（12-bit 津波到着日時計算）、`Decoder::extractSignedLatLon()`（台風中心位置等の符号付き緯度・経度抽出）、`Decoder::getSignedBits()`（2 の補数符号付きビットフィールド抽出）を追加した。
- `.gitignore` を更新し、VSCode 設定、エージェント用作業ファイル（`.agents/`）、ビルド中間ファイルなどを除外対象に追加した。

### Changed

- **MT=44 (DCX) デコーダを IS-QZSS-DCX-003 仕様適合に改修**: MT=44 DCX メッセージデコーダおよび JSON シリアライズロジックを `IS-QZSS-DCX-003` 仕様に完全に適合するよう改修し、サービス種別（Service Kind: J-Alert, L-Alert, 地方自治体, 国外等）の識別ロジックを `A2 Country` および `A3 Provider` に基づき行うように修正した。階層構造化された CAMF および各種拡張メッセージのパース処理を刷新し、テストベクタとシリアライズ出力を完全同期させた。`Message.h` 上の `dcx_type` を `service_kind` へ変更し、`Mt44ServiceKind` / `ExtendedKind` 列挙型および拡張情報領域の各種サブ構造体（`Mt44Sd`, `Mt44CamfRaw`, `Mt44ExLAlertOrLocal`, `Mt44ExJAlert`, `Mt44ExOutside`）を定義した。
- **C++17 安全性を向上**: 定義ルックアップ関数の戻り値を `std::string_view` から `std::optional<std::string_view>` に変更し、値が見つからない場合に `std::nullopt` を返すようにして不正なメモリアクセスや未定義動作をコンパイル時に防止した。生成されるすべての検索関数に `[[nodiscard]]` 属性を付与し戻り値の無視を防止した。
- `scripts/gen_definitions.py` を `std::optional` および `[[nodiscard]]` 移行に伴い更新した。手動管理定義ファイル（`qzss_dcx_camf_a3_provider_identifier.h` および `ublox_qzss_svid_prn_map.h`）も上記 C++17 安全設計に同期させた。
- `src/internal/JsonSerializer.cpp` に `std::optional<std::string_view>` を受け取る `wf_s` オーバーロードを追加・整理し、`std::nullopt` 時に `v.value_or("")` で空文字列にフォールバックするようにした。不要な中間型変換のオーバーロードを削除・最適化した。
- **azarashi 定義データを更新**: 対応リファレンスバージョンを `azarashi 0.15.1` から `azarashi 0.16.1` に更新した（`.azarashi-version`）。自動生成ヘッダのコメントテンプレートを `AUTO-GENERATED from azarashi {ver} with CI-CD` に更新した。
- **フレーマーの制限強化と検証精度を向上**: `NmeaFramer.cpp` で NMEA の hex 文字数が 63 文字であることを厳密に判定するように変更し、`UbxFramer.cpp` で u-blox の L1S 信号判定において `sigId == 0` に加えて `sigId == 1` も許容するようにした。`PrintShim.h` に `std::string_view` のストリーム出力オーバーロードを追加した。
- **プレースホルダー検証を修正**: `test_azarashi.cpp` 等の `CHECK((ok || !ok))` のようなプレースホルダーテストを `CHECK_FALSE(ok)` 等の実際のデコード失敗検証に修正した。

### Fixed

- **ビルド時の曖昧警告・エラーを解消**: `JsonSerializer.cpp` のオーバーロード競合を解消するため `std::optional` 型文字列解決用の `wf_s` オーバーロードを整理した。`make -C test run` が警告・コンパイルエラーなく全 113 件のテストケース（578 アサーション）を 100% SUCCESS で通過することを確認した。

### 仕様準拠

- IS-QZSS-DCX-003 仕様への完全適合と C++17 標準への準拠・安全性向上を達成した。

---

## [0.3.2] - 2026-05-12

### Fixed

- `test/test_json.cpp` の MT=43 Seismic Intensity テストケースのカテゴリ ID ミスを修正した（5 → 3）。
- `test/test_azarashi.cpp` の実態と乖離していたテストケース名（`DCX: Null Msg`）を修正した。
- `test/test_crc.cpp` の DCX デコード時の誤解を招くコメントを修正した。
- `src/internal/JsonSerializer.cpp` の `writeInt32` における `INT32_MIN` 処理時の潜在的な未定義動作を回避した。
- `src/internal/JsonSerializer.cpp` の災害カテゴリ (2, 3, 4, 5, 12, 14) のシリアライザ関数マッピングを修正した。

### Changed

- `src/internal/Dedup.h` の `AZARAC_DEDUP_SLOTS` の既定値を 8 から 32 に拡張し、重複排除の耐性を向上させた。

---

## [0.3.1] - 2026-04-28

### Fixed

- Definition headers の `static constexpr` を `inline constexpr` に変更し、linker-scope symbol として複数ソースからの参照を可能にした。
- `Decoder::decodeQzqsm` の unused-parameter 警告を削除した。

---

## [0.3.0] - 2026-04-19

### Added

- `examples/with_sntp`（Wi-Fi + SNTP 時刻解決 + EEW フィルタ付きサンプル）を追加した。
- `test/test_crc.cpp`（CRC-24Q / `getBits` / MT=44 合成フレーム 12 テスト）を追加した。
- `test/test_json.cpp`（DCX・EEW・震度・津波キー検証 + 全 `disaster_category` ブレースバランス検証, 28 テスト）を追加した。
- `test/Makefile` にホストビルド（`make -C test run`）を追加した。
- CI に `host-test` ジョブを追加した（`g++` ホストテスト → `arduino-cli` コンパイルの順）。
- `README` にクイックスタート・API・JSON 出力例・定義自動生成フローを追記した。

### Fixed

- `JsonSerializer.h` / `PrintShim.h` / `azaraC.h` の `#ifdef ARDUINO` ガードを `#if defined(ARDUINO) && ARDUINO >= 1` に統一し、`ARDUINO=0` ホストビルドに対応した。
- `Decoder.h` のテスト用サブクラスアクセスのため `private` を `protected` に変更した。
- `Decoder.cpp` の `decodeTsunami` / `decodeNwPacTsu` の unused-parameter 警告を修正した。

---

## [0.2.0] - 2026-04-19

### Added

- MT=43 JMA DC Report の全 12 カテゴリをデコード対応した（EEW, Hypocenter, Seismic Intensity, Nankai Trough, Tsunami, NW Pacific Tsunami, Volcano, Ash Fall, Weather, Flood, Marine, Typhoon）。
- `Message` 構造体をカテゴリ別フィールドと繰り返しレコード配列で拡張した。
- `JsonSerializer` で MT=43 の JSON 出力（カテゴリ別 `detail` サブオブジェクト）を追加した。
- 全ラベル文字列を自動生成 `definition/_index.h` のルックアップ関数経由で解決するようにした（azarashi 駆動、ハードコードなし）。

### Changed

- `Decoder::decodeQzqsm` をスケルトンから完全実装に昇格させた。
- `Message.h` をサブ構造体（`TsunamiEntry`, `SeismicEntry`, `WeatherEntry`, `FloodEntry`, `MarineEntry`, `NwPacTsunamiEntry`, `TyphoonPos`）で再構成した。

---

## [0.1.0] - 2026-04-19

### Added

- UBX (RXM-SFRBX) および NMEA (`$QZQSM`) フレーマを追加した。
- CRC-24Q 検証を追加した。
- MT=44 DCX/CAMF の全フィールド抽出（A1–A13）を追加した。
- MT=43 外枠デコード（スケルトン）を追加した。
- `DedupFilter`（`{svid, msg_type, crc24}` によるリングバッファ重複排除）を追加した。
- `JsonSerializer`（ヒープアロケーションなしの `Print&` 出力）を追加した。
- `Parser`（UBX/NMEA 自動判別、pluggable `IFramer` インターフェース）を追加した。
- 102 の定義ヘッダを azarashi 0.15.1 から自動生成した。
- CI に `arduino-cli` コンパイルチェック（ESP32-C3）を追加した。
- CI に azarashi バージョン bump 時の自動 PR（日次スケジュール）を追加した。
