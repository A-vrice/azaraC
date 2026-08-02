# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


## [Unreleased]

### Changed

- **`Message::clear()` 追加**: デコード時の二重ゼロ初期化（`out = {}` → `initPayload` で `~350B` の冗長 `memset`）を除去。
  `Decoder::decode` と `Parser::postDecode` で `out.clear()` を使用し、ペイロード破棄＋スカラーリセットのみを行う。
- **冗長フィールド再設定を削除**: `Decoder::decode` 内の `out.valid = false` / `out.payload_type = Empty`（`clear()` が既に設定済み）。
- **JSON シリアライザの冗長 `getMt43()` 除去**: 12 のサブシリアライザ関数のシグネチャを `const Message&` → `const Mt43Data*` に変更。
  呼出元で既に検証済みのポインタを渡すことで、各関数内の冗長な `m.getMt43()` + null チェックを除去。
- **`disaster_category` ディスパッチを switch 化**: `JsonSerializer::serialize` の 12 連 if-else チェーンを `switch` に変更し O(1) ディスパッチ化（カテゴリ 7/13 は仕様上未定義）。各 `case` は従来通り `AZARAC_ENABLE_*` で個別にコンパイル制御。
- **DCX B4 の D3/D4 出力を `writeDField` に統合**: `const char*` を返す D3/D4 ルックアップを `std::optional<std::string_view>` にアダプトし、他 34 フィールドと同じヘルパーで出力（手書きコード重複を削除）。出力バイト列は不変（`test_json_dcx_b1b4.cpp` で raw + label を固定し、変更前後で同一を確認）。
- **`processNankaiAggregation` の冗長 `getMt43()` 除去**: `postDecode` が取得済みの `Mt43Data*` をパラメータとして渡すように変更。
- **`a3_provider_identifier` ルックアップ高速化**: 34 エントリの O(n) 線形探索を O(log n) 二分探索に変更。
- **定義テーブルの AVR (PROGMEM) 対応**: `src/definition/*.h` のラベル文字列を AVR では Flash に配置し、ルックアップ時に共有 RAM バッファ（`AZARAC_FLASH_BUF_SIZE`、デフォルト 800B）へコピーして返す方式に変更。非 AVR では従来の constexpr 実装を完全維持。`scripts/gen/gen_definitions.py` の 6 エミッタに AVR 分岐を追加し、`scripts/gen/apply_avr_headers.py` で既存ヘッダを移行。`test/stub/avr/pgmspace.h` + `make pgm-stub` で AVR 分岐の意味をホスト検証。CI の Arduino Uno (AVR) コンパイルチェックを追加。
  - **FlashString 共有バッファを 1 個に統合**: `azarac_pgm_view` と `azarac_pgm_copy` が独立した static buf を持ち 800B × 2 = 1600B 消費して Uno の 2KB SRAM を超過していた。共通 `azarac_flash_buf()` 経由の 1 個に統合し、AVR プリセットでは `AZARAC_FLASH_BUF_SIZE` を 64B に縮小（SEISMIC/TSUNAMI 有効時の最大ラベル 30B 基準）。Uno 実測: RAM 2836B → 1300B (63%)。
- **AVR 用最小 C++ 標準ライブラリシム (`src/internal/avr_std/`)**: Arduino AVR ツールチェーン（avr-gcc 7.3.0）は libstdc++ を一切同梱しないため、`src/` と生成定義ヘッダの標準 include を `#if defined(__AVR__)` でシム（`cstdint`/`cstring`/`cstdio` の C ヘッダ委譲、`new`/`utility`/`algorithm`/`iterator`、最小 `optional`/`string_view`）へ切替。API は不変。`test/internal/test_avr_std_shim.cpp` で最小実装をホスト検証。これにより Uno でコンパイル可能に（CI の Uno ジョブは TSUNAMI + SEISMIC の最小構成）。
  - Arduino.h の `min`/`max` 関数マクロ対策: `azaraC.h` で `#undef`（既存の `abs` 対策と同様）+ `Message.h` の `std::max` を三項演算子化。
  - **AVR プリセットでカテゴリを自動絞り込み**: `azaraC_config.h` の AVR プリセットが SEISMIC/TSUNAMI のみ有効化（他 11 カテゴリは無効、`-D`/`#define` で上書き可）。例題内の `#define` はライブラリ .cpp（別 TU）に効かないため撤去し、config レベルで一括適用。
  - Uno ジョブは例題（全て `Serial1` 依存）の代わりに最小スケッチ（`#include <azaraC.h>` のみ）でライブラリ全体をコンパイル検証。
  - **Dedup.h の `AZARAC_DEDUP_SLOTS` デフォルトを config に一本化**: Dedup.h が独自に `#define 8` を持ち、config を経由しない TU（Dedup.cpp）で AVR プリセット (4) と不一致になり LTO が "array types have different bounds" を検出していた。config include + 重複デフォルト削除で解消。
  - **CI ボード分類をアーキテクチャ代表制に整理**: compile-required（リリースゲート）= RP2040 Pico (ARM) / ESP32-C3 (Xtensa) / Arduino Uno (AVR) の 3 台。compile-extended（ベストエフォート、continue-on-error）= 残り 8 台。Uno のボード名から `(AVR)` 表記を削除。

### Fixed

- **`DecoderDcx.cpp`**: `onset_time` 解決の UNIX 時刻比較定数を `315964800u` → `946684800u` (2000-01-01) に修正。
- **`NankaiPageBuffer.h`**: `NankaiPageKey` の fallback フィールドに `= 0` デフォルト初期化子を追加（不定値防止）。
## [0.13.0] - 2026-07-23

### Added

- **`AZARAC_DCX_USE_FLOAT` マクロ**: DCX 座標を `double` から `float` に切り替える設定を追加。
  `DecodedEllipse` のサイズが 72B → 36B に削減（`Mt44Decoded` で 72B 節約）。
- **メモリ使用量表**: `README.md` に RAM 要件の表を追記。
- **RAM 要件ドキュメント**: `Parser.h` に最小 RAM 要件コメントを追加。
- **`#warning`**: Arduino Uno で Nankai バッファ数が多すぎる場合にコンパイル時警告を出力。

### Changed

- **`NankaiData::aggregated_text[]` → ポインタ化** (最重要):
  - 固定配列 `aggregated_text[217]` を `const char* aggregated_text_ptr` + `uint16_t aggregated_len` に置き換え。
  - `NankaiData` のサイズを約 250B → 33B に削減。`Message` 全体が ~408B → ~190B に（約 53% 減）。
  - 実テキストは `NankaiPageBuffer::aggregated_text[]` に保持し、完了時にポインタを設定。
  - 次の `Parser::feed()` 呼び出し前に `Message` を消費する必要がある（既存契約と整合）。
  - **注意**: `aggregated_text_ptr` は NankaiPageBuffer の raw per-page buffer を指す。
    NUL バイトを含むページがある場合、ポインタ経由のデータはページ区切りを保持する。
    実データ（UTF-8 Japanese, NUL 不含）では問題にならない。
- **`B4DetailedInfo` 戻り値 → 出力パラメータ**:
  - `decodeB4DetailedInfo()` が 108B の構造体を値返ししていたのを、参照パラメータに変更。
  - スタックコピーを回避し、RAM フットプリントを削減。
- **`NankaiPageKey` フィールド順序最適化**:
  - `uint32_t event_time_unix` を先頭に移動し、パディングを削除。サイズ: 12B → 8B。
- **`NankaiPageBuffer` フィールド順序最適化**:
  - `uint64_t` メンバを先頭に集め、`uint8_t`/`bool` メンバを後ろに配置。
  - パディング削減により ~256B → ~249B（バッファあたり ~7B × 4 = 28B 削減）。
- **不要な標準ライブラリ依存を除去**:
  - `JsonWriter.cpp`: `<cmath>` を削除し、`std::isnan`/`std::isinf` を `v != v || v > 1e308 || v < -1e308` に置換。
  - `Mt43Data.h`: `<algorithm>` を削除し、`std::max({...})` を constexpr lambda に置換。
  - `DcxHelper.cpp`: 全 `static const double` を `static constexpr double` に変更（Flash 配置保証）。
- **`DcxHelper.cpp` decode 関数**: `double` → `dcx_real_t`（`AZARAC_DCX_USE_FLOAT` 有効時に `float` を使用）。

### Fixed

- **Nankai E2E テスト**: NUL バイト打ち切りテストをポインタ化後の raw buffer 動作に合わせて修正。
- **DCX JSON テスト**: float モード時の精度差に対応（`#ifdef AZARAC_DCX_USE_FLOAT` で期待値を切替）。

## [Unreleased]

### Fixed

- **OOB (Out-of-Bounds) 検出テストの偽陰性**: `TestDecoder` の各 static ラッパーが別々の `Decoder` インスタンスを作成していたため、`clearOob()` → `extractBits()` → `checkOob()` 間で OOB フラグが共有されず、OOB 検出テストが常に失敗していた。共有 `inst()` アクセサに統一。
- **DCX メイン楕円 JSON テストの精度不一致**: `writeDouble` が `precision=6` で `35.600000` を出力するのに対し、テストが `35.600`（3桁）を期待していた。`hasField` の値境界チェックが不一致を検出。期待値を `35.600000` に修正。
## [0.12.0] - 2026-07-16

### Added

- **`truncated` フラグ**: `NankaiData` に `bool truncated` を追加。`total_pages` が `AZARAC_NANKAI_MAX_PAGES` を超えた場合にセットされる。
- **`isContiguous()` メソッド**: `NankaiPageBuffer` にビットマップ連続性チェックを追加。受信済みページが番号順に欠落なく連続しているかを O(1) で判定可能。

### Changed

- **`NankaiPageBuffer` リファクタリング（単一バッファ + ビットマップ方式）**:
  - 2重バッファ構造（`PageData[]` + `aggregated_text[]`）を廃止し、`aggregated_text[]` に直接ページを書き込む方式に変更。
  - 受信済みページの追跡を 64-bit ビットマップで行い、重複チェックを O(n) 線形探索 → O(1) ビットテストに高速化。
  - ページソートが不要に（オフセット書き込みのため）。
  - コード行数約140行→約100行に削減。

- **`AZARAC_NANKAI_AGGREGATED_TEXT_SIZE` 自動導出**:
  - デフォルト値を `AZARAC_NANKAI_MAX_PAGES * 18 + 1` から自動計算するよう変更。
  - ユーザは `AZARAC_NANKAI_MAX_PAGES` のみ設定すればよく、2つのマクロを手動同期する必要がなくなった。
  - 明示的な上書きも `#ifndef` ガードにより引き続き可能。
  - `Mt43Data.h` の冗長なデフォルト定義（`217`）を削除。

### Fixed

- **`total_pages > AZARAC_NANKAI_MAX_PAGES` で全ページが破棄されるバグを修正**:
  - 旧実装では `total_pages` が設定値を超えると即座に `false` を返し、全ページが失われていた。
  - 新実装では `total_pages` を `MAX_PAGES` にキャップし、収まる分だけ受け入れる（トランケーション）。
  - トランケーション発生時は `truncated` フラグでユーザに通知。

- **`getTextLength()` / `getText()` の防御的修正**:
  - 完了バッファ以外で呼ばれた場合に未受信ページのゴミデータを読む可能性を排除。
  - ビットマップをチェックし、受信済みページのみを処理するよう修正。

## [0.11.0] - 2026-07-14

### Added

- **軽量設定ヘッダ `azaraC_config.h`**:
  - コンパイル時マクロを分離し、定義ファイル（103ファイル）からの依存を `azaraC.h` 全体から `azaraC_config.h` のみに削減
  - 定義ファイルが `Message.h` → `Mt43Data.h` → `NankaiPageBuffer.h` などのライブラリ本体をプルしなくなる
  - ユーザー向けAPIは `#include <azaraC.h>` のまま変更なし

- **災害カテゴリ別コンパイル除外マクロ**（全13種）:
  - `AZARAC_ENABLE_EEW`, `AZARAC_ENABLE_HYPOCENTER`, `AZARAC_ENABLE_SEISMIC`, `AZARAC_ENABLE_NANKAI`, `AZARAC_ENABLE_TSUNAMI`, `AZARAC_ENABLE_NW_PAC_TSUNAMI`, `AZARAC_ENABLE_VOLCANO`, `AZARAC_ENABLE_ASH_FALL`, `AZARAC_ENABLE_WEATHER`, `AZARAC_ENABLE_FLOOD`, `AZARAC_ENABLE_TYPHOON`, `AZARAC_ENABLE_MARINE`, `AZARAC_ENABLE_DCX_CAMF`
  - 各 `#define` を 0 に設定すると対応する定義テーブルがコンパイル時に完全除外される

- **実データテスト基盤**:
  - `test/tools/decode_to_json.cpp`: NMEA文をJSONに変換するCLIツール（azarashi比較用）
  - `test/scripts/compare_with_azarashi.py`: azarashi参照実装とAzaraCのデコード結果を比較するスクリプト
  - `test/scripts/gen_realdata_vectors.py`: realdata/ からC++テストベクタを自動生成するスクリプト
  - `test/integration/test_realdata.cpp`: 実データを用いた統合テスト（自動生成）
- **南海トラフE2Eテスト**:
  - `test/integration/test_nankai_e2e.cpp`: 複数ページ集約のエンドツーエンドテスト
  - `test/scripts/compare_nankai_aggregation.py`: azarashiとの集約結果比較スクリプト
- **ファズテスト**: `test/fuzz/fuzz_decoder.cpp` を追加（デコーダの堅牢性検証）
- **テストケース拡充**:
  - フレーマーテスト: 複数svId, チェックサムエラー2方式, ガベージリカバリ複数svId
  - JSONテスト: A9/A10/A11境界値, Nankai集約後 text_utf8 出力, unix_time=0 出力
  - azarashi比較テスト: `test_ublox_azarashi.cpp`, `test_azarashi.cpp`, `test_azarashi_dcr.cpp`, `test_azarashi_dcx.cpp`
- **Makefile**: `decode` ターゲット（`decode_to_json` ビルド）, `compare-realdata` ターゲット（azarashi比較実行）

### Changed

- **IS-QZSS-DCX-004 / EWSS CAMF v1.2 対応**:
  - コメント・ドキュメントの参照仕様を IS-QZSS-DCX-003 → IS-QZSS-DCX-004 に更新
  - EWSS CAMF v1.1 → v1.2 に更新
- **Azarashi v0.16.4 対応**:
  - 各種リファクタ変数の修正など。
- **B1 リファインメント修正 (EWSS CAMF v1.2 §3.7.1.3/4 準拠)**:
  - `Message.h`: `DecodedEllipse` の `b1_major_factor`/`b1_minor_factor` を `b1_refined_semi_major_km`/`b1_refined_semi_minor_km` に変更
  - `DcxHelper`: `b1InterpolationFactor()` を廃止し、`b1RefinedRadiusKm()` を新設（正しい半径計算式: `base_radius_km - delta_km * (code / 8.0)`）
  - 旧実装は補間係数（0.0–0.875）を出力していたが、正しくは refinement後の半径（km）を出力すべき
- **B2/B3 ビット抽出修正**:
  - `DecoderDcx.cpp`: B2 C5/C6 のビットシフト位置を修正（`>>0`→`>>8`, `>>7`→`>>1`）
  - B3 C7/C8/C9/C10 のビットシフト位置を修正（`>>0`→`>>13`, `>>2`→`>>10`, `>>5`→`>>5`, `>>10`→`>>0`）
- **B4 独立デコード**:
  - `DecoderDcx.cpp`: B4 をメイン楕円（A12-A16）の有無に関わらず独立してデコードするよう修正
- **JSON シリアライゼーション改善**:
  - `JsonSerializerDcx.cpp`:
    - `a4_hazard_definition` フィールドを追加
    - `a9_selection_of_library` → `a9_type_of_library` に名称変更
    - `a11_guidance_label`: A9（ライブラリ種別）に応じて国際/日本語ライブラリを切り替え
    - `a17_specific_subject` → `a17_type_of_specific_settings` に名称変更
    - `c10_guidance_label` を `c10_guidance_label` + `c10_guidance_code` に分割
    - J-Alert の `city_labels` 出力を追加
    - B1 refinement JSON キー変更（`c3_major_factor` → `c3_refined_semi_major_km`, `c4_minor_factor` → `c4_refined_semi_minor_km`）
  - `JsonSerializerQzqsm.cpp`: 降灰情報に `warning_type_label` を追加
- **定義ファイルの更新**:
  - `azarashi` 0.16.4 に対応
  - ファイル名を仕様書の正式名称に合わせてリネーム:
    - `a9_selection_of_library` → `a9_type_of_library`
    - `a17_main_subject_for_specific_settings` → `a17_type_of_specific_settings`
    - `c10_guidance_library_for_second_ellipse` → `c10_instruction_library_for_second_ellipse`
    - `c10_guidance_library_for_second_ellipse_code` → `c10_instruction_library_for_second_ellipse_code`
  - 未使用の A3 プロバイダ別ファイル・EX9 ファイルを `_index.h` から削除（92定義に整理）
- **`Parser::feed()` リファクタリング**:
  - `feed()` 内部のカスタムフレーマー経路とAUTOモード経路で重複していたデコード後処理を `postDecode()` メソッドに抽出
  - Nankai集約→Dedupチェック→コピーのパイプラインが1箇所に統一
- **`B4DetailedInfo` / `Mt44CamfRaw` B4フィールド配列化**:
  - D1〜D36の72個の個別フィールドを `b4_d_present[36]` + `b4_d_values[36]` に統合
  - `DecoderDcx.cpp`: 72行の手動初期化/コピーを `memset`/`memcpy` に置換（〜140行削減）
  - `DcxHelper.cpp`: `decodeB4DetailedInfo` の全ケースを配列インデックスアクセスに変更
  - `JsonSerializerDcx.cpp`: D3/D4（const char\*）以外を配列インデックスに統一
- **`azaraC.h`**: 未使用の `AZARAC_ENABLE_QZSS_DCR_PREAMBLE` マクロを削除

### Fixed

- **ビルドシステム**:
  - `test/Makefile`: Windowsでのメモリ割り当てを増強（スタック 64MB→256MB, ヒープ 256MB→512MB）
- **CI/CD**:
  - `.github/workflows/ci.yml`: 全 `actions/checkout` ステップに `persist-credentials: false` を追加（セキュリティ強化）

### Removed

- `.plans/` ディレクトリ（計画ドキュメント）を削除
- `data/` ディレクトリの実データCSV/MDファイルを削除（realdata/ に移行）

---

## [0.10.0] - 2026-06-27

### Changed

- **DCX-004 小数点以下の保証に準拠**:
  - `JsonWriter::wf_d` に `precision` パラメータを追加（デフォルト=3、後方互換性維持）
  - 緯度・経度フィールド（`lat_deg`, `lon_deg`, `delta_lat_deg`, `delta_lon_deg`, `b1_lat_offset_deg`, `b1_lon_offset_deg`）を 1e-6度（小数点以下6桁）に変更
  - 角度フィールド（`azimuth_deg`, `bearing_deg`）を 1e-5度（小数点以下5桁）に変更
  - 距離フィールド（`semi_major_km`, `semi_minor_km`, `shift_km`, `b1_refined_semi_major_km`, `b1_refined_semi_minor_km`）は 1m = 0.001km（小数点以下3桁）のまま維持
- `library.properties`: `version=0.10.0` に更新
- `README.md`: 仕様書リファレンスを IS-QZSS-DCX-004 / EWSS CAMF v1.2 に更新
- `README.md`: JSON出力例をDCX-004準拠の精度に更新

### 仕様準拠

- IS-QZSS-DCX-004 に準拠（May, 2026）
- General Assumptions §2.5 の丸めルールを適用:
  - 緯度・経度: 10⁻⁶度
  - 角度: 10⁻⁵度
  - 距離: 1m（0.001km）

---

## [0.9.0] - 2026-06-25

### Changed

- **冗長なファイル削除**:
  - testの一部を整理・統合
  - 一部をタグ付き共用体に。
- **`.gitignore`の更新**:
  - `.plans/` と `data/` を追加。

### Fixed

- `DecoderQzqsm.cpp`: `current_message_id` の重複除去バッファへの格納位置修正
  - 既存の格納位置（477,478）から `MT43_MESSAGE_ID_OFFSET`（348）に移動
  - これにより、重複除去バッファが正しく機能するようになる

## [0.8.0] - 2026-06-19

### Added

- **Nankai Trough ページ集約機能**:
  - `NankaiPageBuffer` / `NankaiPageBufferManager`: スパースページ対応のメモリ効率の良い集約バッファを実装。
  - `Parser`: 複数ページにまたがる南海トラフ地震メッセージの集約ロジックを追加。
  - `test/integration/test_nankai.cpp`: ページ集約の統合テストを追加。
- **RTOS (FreeRTOS) 対応**:
  - `examples/rtos_freertos/`: FreeRTOS 環境での NMEA/UBX 同時処理サンプルを追加。
- **JsonWriter ユーティリティ**:
  - `src/internal/JsonWriter.h` / `JsonWriter.cpp`: プリミティブ型・共通データ構造のJSONシリアライズヘルパーを追加。
- **PrintShim ホストテスト対応**:
  - `src/internal/PrintShim.h`: ホストサイドテスト向けストリーム出力オーバーロードを追加。
- **Fuzz テスト基盤**:
  - `test/fuzz/fuzz_decoder.cpp`: デコーダの堅牢性検証用ファズテストを追加。
- **カテゴリフィルタリングサンプル**:
  - `examples/filter_by_category/`: 特定の disaster_category のみをフィルタリングして出力するサンプルを追加。
- **定義ファイル自動生成パイプラインの強化**:
  - `scripts/gen_definitions.py` の改善と CI ワークフロー (`update-definitions.yml`) の更新。
- **CI/CD の拡充**:
  - ホストテスト・ファズテスト・多プラットフォーム Arduino コンパイルを統合した GitHub Actions ワークフロー。
  - CodeQL セキュリティ解析ワークフローの追加。

### Changed

- `library.properties`: `version=0.8.0` に更新。
- `src/Parser.cpp`: Nankai Trough ページ集約ロジックの統合。
- `src/internal/JsonSerializer.h` / `JsonSerializer.cpp`: JsonWriter ユーティリティとの統合。
- `examples/` 全般: API の一般的な使い方に合わせてサンプルを改善。
- `TimeFields.h`: 時刻フィールド処理の更新。
- `.gitignore`: ネットワーク関連ファイル・CI 関連ファイルを追加。

### Fixed

- ESP32-C3 での `Serial2` 設定の修正。
- 一部ボード定義でのオプション名の修正。
- README.md の UTF-8 文字化けを修正。

---

## [0.7.0] - 2026-06-07

### Added

- **Error Handling Example** (`examples/error_handling/error_handling.ino`):
  - MT=44 メッセージのパース失敗を検出してエラー内容を出力するサンプルスケッチを追加。
  - `parse_result` の `ParseResultCode` と `error_detail` を利用した具体的なエラーハンドリング方法を提示。
  - エラーコード一覧（001-007, 100-109）に対応するエラーハンドリングロジックを実装。
- **DCX A17 B2/B3/B4 の実装** (EWSS CAMF v1.1 §3.7.2-3.7.4):
  - `DcxHelper.cpp`: B2/B3/B4 デコード関数の追加:
    - `decodeB2HazardCenter()`: C5/C6 から緯度/経度オフセットを計算（±10°範囲、0.15625°ステップ）
    - `decodeB3SecondaryEllipse()`: C7-C10 から第2楕円パラメータを計算（シフト・相似比・方位角・ガイダンス）
    - `decodeB4DetailedInfo()`: A4 ハザード種別に応じて D1-D36 フィールドを抽出（36種のD-series）
  - `DcxHelper.h`: `B2HazardCenter`, `B3SecondaryEllipse`, `B4DetailedInfo` 構造体および上記関数の宣言を追加
  - `Message.h`: `Mt44CamfRaw` に B2/B3/B4 フィールド（raw values）を追加
  - `DecoderDcx.cpp`: A17=01/10/11 の場合の B2/B3/B4 解析処理を実装
  - `JsonSerializerDcx.cpp`: B2/B3/B4 の JSON 出力を追加
  - `JsonSerializerDcx.cpp`: `DcxHelper.h` のインクルードを追加（`decodeLatitude16`/`decodeLongitude17` 使用）

### Changed

- **ディレクトリ構造のリファクタリング**:
  - `include/` ディレクトリを作成し、Arduino配布用ヘッダを分離
  - `src/` をテスト用実装ディレクトリに再編成:
    - `src/decoder/` — Decoder.cpp, DecoderDcx.cpp, DecoderQzqsm.cpp
    - `src/framer/` — UbxFramer.cpp, NmeaFramer.cpp
    - `src/json/` — JsonWriter.cpp, JsonSerializer.cpp, JsonSerializerDcx.cpp, JsonSerializerQzqsm.cpp
    - `src/helper/` — DcxHelper.cpp, Dedup.cpp
  - `test/` を機能別サブディレクトリに整理:
    - `test/core/` — CRC, 時間変換, 緯度経度, 重複除去テスト
    - `test/decoder/` — QZQSM, DCXデコーダテスト
    - `test/framer/` — UBX/NMEAフレーマーテスト
    - `test/json/` — JSONシリアライザテスト
    - `test/integration/` — 統合テスト, データ駆動テスト, エッジケーステスト
  - 旧テストファイル（test_crc.cpp等）を新テストファイルに統合
  - `src/definition/` を削除（`include/definition/` と重複していたため）
  - `library.properties` に `includes=azaraC.h` を追加
- `DecoderDcx.cpp`: B2/B3 のビット抽出を B1 と同じパターン（LSB から順）に統一
- `DcxHelper.cpp`: B4 の各ハザード D フィールドのビット配置を仕様書（EWSS CAMF v1.1 §3.7.4）と整合
- `DecoderDcx.cpp`: B2/B3/B4 フィールドの初期化を追加（ゼロクリア）
- `DecoderDcx.cpp`: 構文エラーの返却コードを `ParseResultCode::Error` に変更
- `DecoderDcx.h`: `parse_result` の型を `ParseResultCode` に変更（旧 `Error` 型を削除）
- デフォルト重複除去スロット数を8に再変更
- 言語テーブルの選択的コンパイルオプションを追加

### Fixed

- `DecoderDcx.cpp`: B3 の未使用変数警告を修正（`(void)` キャスト）

### Documentation

- **エラーハンドリングガイドの追加**:
  - エラーハンドリングセクションを追加：
    - 全エラーコード一覧（001-007, 100-109）
    - デコード失敗理由ごとの具体的なハンドリング方法
    - デコード成功・失敗のフロー図
    - MT44/MT43 共通の処理フロー
  - `examples/error_handling/error_handling.ino` で上記ガイドを実践的に解説。

### 仕様準拠

- EWSS CAMF v1.1 §3.7.2-3.7.4 に準拠
- A17=01 (B2: Hazard Center Position) のデコード対応
- A17=10 (B3: Secondary Ellipse Definition) のデコード対応
- A17=11 (B4: Quantitative and Detailed Information) のデコード対応

---

## [0.6.0] - 2026-05-31

### Added

- **DCX A17 B1 (Improved Resolution of Main Ellipse) の実装** (EWSS CAMF v1.1 §3.7.1):
  - `DcxHelper.cpp`: B1 リファインメント関数の追加:
    - `decodeB1Refinement()`: A18 (15bit) から C1-C4 を抽出
    - `b1RefinedLatitudeOffset()`: C1 から緯度補正オフセットを計算
    - `b1RefinedLongitudeOffset()`: C2 から経度補正オフセットを計算
    - `b1InterpolationFactor()`: C3/C4 から補間係数を計算
  - `DcxHelper.h`: `B1Refinement` 構造体および上記関数の宣言を追加
  - `Message.h`: `Mt44CamfRaw` に B1 フィールド (`b1_present`, `b1_c1`-`b1_c4`) を追加
  - `Message.h`: `DecodedEllipse` に B1 リファインメント値 (`b1_lat_offset_deg`, `b1_lon_offset_deg`, `b1_major_factor`, `b1_minor_factor`) を追加
  - `DecoderDcx.cpp`: A17=00 の場合の B1 解析処理を実装

### Changed

- `DecoderDcx.cpp`: Null Message 検出時の Extended Message チェックを `getBits` を使用するように修正（ビット境界の正確性向上）

### 仕様準拠

- EWSS CAMF v1.1 §3.7.1 に準拠
- A17=00 (B1: Improved Resolution of Main Ellipse) のデコード対応

---

## [0.5.0] - 2026-05-27

### Added

- **DCX MT44 デコーダの IS-QZSS-DCX-003 完全準拠リファクタ**:
  - `DecoderDcx.cpp`: MT44 デコーダを仕様書通りのビット配置（PAB|MT|SD|CAMF|EX|Reserved|CRC）で再実装。
  - `A2 Country/Region Name` および `A3 Provider Identifier` に基づくサービス種別判定ロジックを実装（L-Alert, J-Alert, Local Government, Outside Japan, Null Message, Unknown）。
  - `Extended Message` のサービス種別ごとの個別パース処理を実装：
    - L-Alert/Local Government: `EX1..EX7 + Vn`
    - J-Alert: `EX8..EX10 + Vn`
    - Outside Japan: `EX11(68bit raw) + Vn`
  - `Message.h`: `Mt44Decoded` 構造体にデコード済み楕円座標（`DecodedEllipse`）、追加領域（`DecodedAdditionalArea`）、アラート識別子（`Mt44AlertIdentity`）を追加。
  - `Message.h`: `DecodedEllipse`, `DecodedAdditionalArea`, `Mt44AlertIdentity` 構造体を新規定義。
- **DcxHelper 関数の追加**:
  - `decodeLatitude16()`: 16ビット緯度コードを WGS84 度に変換。
  - `decodeLongitude17()`: 17ビット経度コードを WGS84 度に変換。
  - `decodeLatitude17()`: 17ビット緯度コード（EX3用）を WGS84 度に変換。
  - `decodeLongitude17_45_225()`: 17ビット経度コード（EX4用、45-225度範囲）を WGS84 度に変換。
  - `decodeRadiusCode()`: 5ビット半径コードを km に変換（IS-QZSS-DCX-003 Table 4.2-17 対数テーブル）。
  - `decodeAzimuth6()`: 6ビット方位角コードを度に変換。
  - `decodeAzimuth7()`: 7ビット方位角コード（EX7用）を度に変換。
  - `decodePrefectureBitmask()`: EX9 64ビットフィールドから都道府県ビットマスクをデコード。
  - `decodeCityCodeList()`: EX9 64ビットフィールドから市区町村コードリストをデコード。
- **テストファイルの追加**:
  - `test/test_dcx_helper.cpp`: DcxHelper 全関数のユニットテスト（緯度・経度・半径・方位角・都道府県ビットマスク・市区町村コード）。
  - `test/test_latlon.cpp`: `extractLatLon` 関数の緯度経度抽出テスト。
  - `test/test_decoder.cpp`: DCX MT44 デコードテスト（L-Alert, J-Alert, Local Government, Outside Japan, Null Message, 未知A3）および `decodePrefectureBitmask` 単体テストを追加。

### Changed

- **J-Alert 都道府県デコードバグ修正** (`check.md` に基づく):
  - `DcxHelper.cpp::decodePrefectureBitmask()`: EX9[63:17] に格納される47ビット都道府県フィールドの抽出ロジックを修正（`ex9 >> 17` で右シフトしてから検査）。
  - JIS コード計算を `47 - i` から `i + 1` に修正（bit 0 = 北海道/JIS 1）。
- `Message.h`: `Mt44CamfRaw` の `a12`, `a13` のコメントを「unsigned, latitude/longitude code」に更新。
- `Message.h`: `Mt44ExLAlertOrLocal` の `ex3`, `ex4` のコメントを「unsigned」に更新。

### Fixed

- `DecoderDcx.cpp`: A12/A13 の符号付きパース（2の補数）を符号なしパースに修正（IS-QZSS-DCX-003 仕様準拠）。
- `DecoderDcx.cpp`: EX3/EX4 の符号付きパースを符号なしパースに修正。

### 仕様準拠

- IS-QZSS-DCX-003 に完全準拠
- サービス種別（Service Kind）の識別ロジックを A2 Country および A3 Provider に基づいて実装
- 階層構造化されたCAMF（Common Alert Message Format）のパース処理を刷新

---

## [0.4.0] - 2026-05-20

### Added

- **テストスイートの拡充と検証カバレッジの強化**:
  - `test/test_ublox.cpp`: u-blox SFRBX (RXM-SFRBX) パケットに対するデコーダの動作検証、および NMEA 出力との整合性を確認するテストを新規追加。
  - `test/test_coverage.cpp`: MT=43 各防災カテゴリ（南海トラフ、降灰、洪水、気象、震度、火山等）の詳細フィールド検証、年末年始・うるう年等の日付境界テスト、および NMEA 文字数上限や不正プリアンブル等の異常系に対するエッジケーステストを新規追加。
- **デコーダ内部共通処理の共通関数化と符号付きパース関数の追加**:
  - `Decoder::readNotifications()`: 防災気象情報通知コード（9ビット）読み出しロジックを共通化。
  - `Decoder::resolveArrivalTime()`: 津波予測の到着日時（12ビット）計算ロジックを共通化。
  - `Decoder::extractSignedLatLon()`: 台風中心位置等の符号付き緯度・経度の抽出処理を共通化。
  - `Decoder::getSignedBits()`: 符号付きビットフィールド（2の補数表現）抽出ヘルパーを追加。
- `.gitignore` のアップデート: VSCode設定、エージェント用作業ファイル（`.agents/`）、ビルド中間ファイルなどを除外対象に追加。

### Changed

- **MT=44 (DCX) デコーダの IS-QZSS-DCX-003 仕様適合**:
  - MT=44 DCXメッセージデコーダおよびJSONシリアライズロジックを `IS-QZSS-DCX-003` 仕様に完全に適合するよう改修。
  - サービス種別（Service Kind: J-Alert, L-Alert, 地方自治体, 国外等）の識別ロジックを `A2 Country` および `A3 Provider` に基づき行うように修正。
  - 階層構造化されたCAMF（Common Alert Message Format）および各種拡張メッセージのパース処理を刷新し、テストベクタとシリアライズ出力を完全同期。
  - `Message.h` 上の `dcx_type` を `service_kind` へ変更し、`Mt44ServiceKind` / `ExtendedKind` 列挙型および拡張情報領域の各種サブ構造体（`Mt44Sd`, `Mt44CamfRaw`, `Mt44ExLAlertOrLocal`, `Mt44ExJAlert`, `Mt44ExOutside`）を定義。
- **モダンC++安全性向上 (C++17対応)**:
  - 定義ルックアップ関数の戻り値を `std::string_view` から `std::optional<std::string_view>` へ変更。
  - 値が見つからなかった場合に `std::nullopt` を返却するよう型安全性を強化し、不正なメモリアクセスや未定義動作をコンパイル時に防止。
  - 生成されるすべての検索関数（Switch文、配列、二分探索）に対して `[[nodiscard]]` 属性を付与し、戻り値の無視を防止。
- `scripts/gen_definitions.py`: `std::optional` および `[[nodiscard]]` への移行に伴い、自動生成されるヘッダーのテンプレートおよび生成スクリプトのロジックを更新。
- 手動管理定義ファイル (`qzss_dcx_camf_a3_provider_identifier.h` および `ublox_qzss_svid_prn_map.h`) も上記 C++17 安全設計に同期。
- `src/internal/JsonSerializer.cpp`:
  - `std::optional<std::string_view>` を受け取る `wf_s` 文字列出力関数のオーバーロードを追加・整理。
  - `std::nullopt` を受け取った際には安全に空文字列 (`""`) にフォールバックするよう `v.value_or("")` 処理を追加。
  - 暗黙の型変換に伴うコンパイル時のシグネチャ競合（ambiguous overloads）を解決するため、不要な中間型変換のオーバーロードを削除・最適化。
- **azarashi定義データのアップデート**:
  - 対応リファレンスバージョンを `azarashi 0.15.1` から `azarashi 0.16.1` へ更新（`.azarashi-version`）。
  - 自動生成ヘッダーのコメントテンプレートを `AUTO-GENERATED from azarashi {ver} with CI-CD` へ更新。
- **フレーマーの制限強化と検証精度向上**:
  - `NmeaFramer.cpp`: `IS-QZSS-DCX-003` 仕様に基づき、NMEA の hex 文字数が 63 文字であることを厳密に判定するよう変更。
  - `UbxFramer.cpp`: u-blox の L1S 信号判定において、`sigId == 0` に加えて `sigId == 1` も許容するようサポート範囲を拡大。
  - `PrintShim.h`: `std::string_view` のストリーム出力オーバーロードを追加。
- **テストコードにおけるプレースホルダー検証の修正**:
  - `test_azarashi.cpp` 等における `CHECK((ok || !ok))` のようなプレースホルダーテストを、`CHECK_FALSE(ok)` 等の実際のデコード失敗検証へと修正。

### Fixed

- **ビルド時の曖昧警告・エラーの解消**:
  - `JsonSerializer.cpp` のオーバーロード競合を解消するため、`std::optional` 型文字列解決用の `wf_s` オーバーロードを整理。
  - `make -C test run` が警告・コンパイルエラーなく、全113件のテストケース（578アサーション）を 100% SUCCESS で通過することを確認。

### 仕様準拠

- IS-QZSS-DCX-003 仕様への完全適合
- C++17 標準への準拠と安全性向上

---

## [0.3.2] - 2026-05-12

### Fixed

- `test/test_json.cpp`: MT=43 Seismic Intensity テストケースのカテゴリIDミスを修正 (5 → 3)
- `test/test_azarashi.cpp`: 実態と乖離していたテストケース名 (`DCX: Null Msg`) を修正
- `test/test_crc.cpp`: DCXデコード時の誤解を招くコメントを修正
- `src/internal/JsonSerializer.cpp`: `writeInt32` における `INT32_MIN` 処理時の潜在的な未定義動作を回避
- `src/internal/JsonSerializer.cpp`: 災害カテゴリ (2, 3, 4, 5, 12, 14) のシリアライザ関数マッピングを修正

### Changed

- `src/internal/Dedup.h`: `AZARAC_DEDUP_SLOTS` のデフォルト値を 8 から 32 に拡張 (重複排除の耐性向上)

---

## [0.3.1] - 2026-04-28

### Fixed

- Definition headers: `static constexpr` → `inline constexpr` 変更
  (linker-scope symbol となり、複数のソースからの参照が可能)
- `Decoder::decodeQzqsm` の unused-parameter 警告削除

---

## [0.3.0] - 2026-04-19

### Added (Phase 3)

- `examples/with_sntp`: Wi-Fi + SNTP 時刻解決 + EEW フィルタ付きサンプル
- `test/test_crc.cpp`: CRC-24Q / getBits / MT=44 合成フレーム 12 テスト
- `test/test_json.cpp`: DCX・EEW・震度・津波キー検証 + 全 disaster_category
  ブレースバランス検証 (28 テスト)
- `test/Makefile`: ホストビルド (`make -C test run`)
- CI: `host-test` ジョブ追加 (g++ ホストテスト → arduino-cli コンパイル の順)
- README: クイックスタート・API・JSON 出力例・定義自動生成フロー

### Fixed

- `JsonSerializer.h` / `PrintShim.h` / `azaraC.h`: `#ifdef ARDUINO` ガードを
  `#if defined(ARDUINO) && ARDUINO >= 1` に統一 (ARDUINO=0 ホストビルド対応)
- `Decoder.h`: テスト用サブクラスアクセスのため `private` → `protected`
- `Decoder.cpp`: `decodeTsunami` / `decodeNwPacTsu` の unused-parameter 警告修正

---

## [0.2.0] - 2026-04-19

### Added (Phase 2)

- MT=43 JMA DC Report full sub-type decode (all 12 categories):
  EEW, Hypocenter, Seismic Intensity, Nankai Trough, Tsunami,
  NW Pacific Tsunami, Volcano, Ash Fall, Weather, Flood, Marine, Typhoon
- `Message` struct extended with per-category fields and repeating record arrays
- `JsonSerializer`: MT=43 full JSON output with `detail` sub-object per category
- All label strings resolved via auto-generated `definition/_index.h` lookup functions
  (no disaster strings hardcoded — fully azarashi-driven)

### Changed

- `Decoder::decodeQzqsm` promoted from skeleton to full implementation
- `Message.h` restructured with sub-structs:
  `TsunamiEntry`, `SeismicEntry`, `WeatherEntry`, `FloodEntry`,
  `MarineEntry`, `NwPacTsunamiEntry`, `TyphoonPos`

### 対応カテゴリ一覧

| disaster_category | 内容                              |
| ----------------- | --------------------------------- |
| 1                 | 緊急地震速報 (EEW)                |
| 2                 | 震源情報 (Hypocenter)             |
| 3                 | 震度情報 (Seismic Intensity)      |
| 4                 | 南海トラフ地震 (Nankai Trough)    |
| 5                 | 津波警報・注意報 (Tsunami)        |
| 6                 | 北太平洋津波 (NW Pacific Tsunami) |
| 8                 | 火山情報 (Volcano)                |
| 9                 | 降灰情報 (Ash Fall)               |
| 10                | 気象警報・注意報 (Weather)        |
| 11                | 洪水警報 (Flood)                  |
| 12                | 台風情報 (Typhoon)                |
| 14                | 海上警報 (Marine)                 |

---

## [0.1.0] - 2026-04-19

### Added (Phase 1)

- UBX (RXM-SFRBX) and NMEA ($QZQSM) framers
- CRC-24Q verification
- MT=44 DCX/CAMF full field extraction (A1-A13)
- MT=43 outer frame decode (skeleton)
- DedupFilter: ring-buffer keyed on {svid, msg_type, crc24}
- JsonSerializer: heap-free Print& output
- Parser: UBX/NMEA auto-detect, pluggable IFramer interface
- 102 definition headers auto-generated from azarashi 0.15.1
- CI: arduino-cli compile check on ESP32-C3
- CI: auto PR on azarashi version bump (daily schedule)

### アーキテクチャ

- **Framer**: UBX/NMEA 自動判別、pluggable IFramer インターフェース
- **Decoder**: MT=43 (QZQSM) / MT=44 (DCX) デコード
- **DedupFilter**: {svid, msg_type, crc24} によるリングバッファ重複排除
- **JsonSerializer**: ヒープアロケーションなしの Print& 出力
