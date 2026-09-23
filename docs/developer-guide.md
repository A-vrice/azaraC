# AzaraC 開発者ガイド

## 概要

AzaraCライブラリの開発に貢献する開発者向けのガイドです。

## 開発環境のセットアップ

### 必要なツール

| ツール | バージョン | 用途 |
|-------|-----------|------|
| g++ | C++17対応 | ホストテストビルド |
| Python | 3.9+ | 定義ファイル生成 |
| make | - | ビルド自動化 |

### リポジトリのクローン

```bash
git clone https://github.com/A-vrice/azaraC.git
cd azaraC
```

### Python環境のセットアップ

```bash
pip install azarashi
```

## プロジェクト構造

```
azaraC/
├── .github/workflows/        # CI/CD設定
├── docs/                     # ドキュメント
├── examples/                 # サンプルスケッチ
├── src/                      # ソースコード
│   ├── azaraC.h              # メインヘッダ
│   ├── azaraC_config.h       # 軽量設定マクロヘッダ（定義ファイルからも参照）
│   ├── Message.h             # メッセージ構造体
│   ├── Mt43Data.h            # MT=43 タグ付き共用体
│   ├── Mt44Data.h            # MT=44 データ構造体（B4配列含む）
│   ├── Parser.h / Parser.cpp # パーサー（postDecode で重複除去を一元化）
│   ├── decoder/              # デコーダ実装
│   ├── framer/               # フレーマー実装
│   ├── json/                 # JSONシリアライズ実装
│   ├── internal/             # 内部ヘッダ・実装（avr_std/ シム、FlashString.h 含む）
│   └── definition/           # 自動生成定義テーブル（104ファイル）
├── scripts/                  # 定義ファイル生成スクリプト
│   ├── gen/                  # 定義生成（gen_definitions.py, strategy.py）
│   └── analysis/             # 静的解析サマリ（cppcheck_summary.py, gcovr_summary.py）
├── test/                     # テスト
│   ├── Makefile
│   ├── core/                 # コア機能テスト
│   ├── framer/               # フレーマーテスト
│   ├── json/                 # JSONシリアライズテスト
│   ├── internal/             # 内部ヘッダ・実装テスト（avr_std シム等）
│   ├── integration/          # 統合テスト
│   ├── fuzz/                 # ファジングテスト
│   ├── tools/                # decode_to_json 等 CLI
│   ├── scripts/              # azarashi 比較・ベクタ生成スクリプト
│   ├── stub/avr/             # AVR 分岐検証用 pgmspace.h スタブ
│   ├── data/                 # azarashi 生成の参照ベクタ (JSON) + nankai_pages_generated.h
│   └── platformio/           # PlatformIO コンパイル検証プロジェクト
└── library.properties        # Arduinoライブラリ設定
```

## テスト

### テストの実行

```bash
# Linux / macOS / WSL
make -C test run

# Windows (MinGW-w64)
make -C test run MINGW64_BIN=C:\mingw64\bin
```

### テスト結果例

```
=== azaraC unit tests ===
  PASS  crc_known_zeros
  PASS  crc_known_a5
  ...
=== all passed ===
```

### テストカテゴリ

| ディレクトリ | 内容 |
|-------------|------|
| `core/` | CRC, 時間, 緯度経度, 重複除去 |
| `internal/` | 内部ヘルパ（DcxHelper, avr_std シム） |
| `framer/` | NMEA/UBXフレーマー |
| `json/` | JSON出力検証 |
| `integration/` | エンドツーエンドテスト |
| `fuzz/` | ファジングテスト |

### ファジングテスト

```bash
make -C test fuzz FUZZ_ITERATIONS=100000
```

### その他のターゲット

| ターゲット | 用途 |
|----------|------|
| `make -C test pgm-stub` | `__AVR__` + スタブ `avr/pgmspace.h` で全テストをコンパイルし PROGMEM 分岐をホスト検証 |
| `make -C test run-small-pages` | `AZARAC_NANKAI_MAX_PAGES=8` で全体を再ビルドし、ページ打ち切り経路を検証（既定 63 では打ち切りが発生せず該当テストが `#if` で除外されるため） |
| `make -C test decode` | decode_to_jsonのCLIビルド（azarashi 比較用） |
| `make -C test compare-realdata` | azarashiとの処理比較（`pip install azarashi`が必要） |
| `make -C test check` / `check-xml` | 静的解析（cppcheck）と厳格コンパイルチェック |
| `make -C test coverage` / `memprof` | カバレッジ測定 / メモリプロファイル |

## 定義ファイルの自動生成

### 生成の仕組み

```text
azarashi (PyPI) → definition/*.py
    ↓ scripts/gen/gen_definitions.py --out-dir src/definition
src/definition/*.h
    ↓ GitHub Actions (毎日 06:00 UTC)
PR自動作成 → レビュー → マージ
```

### 手動での生成

```bash
pip install --upgrade azarashi
python scripts/gen/gen_definitions.py --out-dir src/definition
```

### テストベクタの生成

`test/data/*.json`はテスト用ベクタです。南海トラフ用のテストデータである`test/data/nankai_pages_generated.h`も`nankai_vectors.json`と共にに生成されるため、直接変更はせず再生成してください。

```bash
python test/scripts/gen_all_vectors.py    # 全ベクタ + nankai_pages_generated.h を再生成
```

再生成のたびに `params.timestamp`（`datetime.now()`）だけが差分になる。全ての consumer は
`timestamp` を無視するため、差分が出ても page データの変更ではない。

## AVR 開発

AVR ツールチェーン（avr-gcc）は libstdc++ を一切含まないため、標準ライブラリ依存は `src/internal/avr_std/` の最小シム（`optional` / `string_view` / `std::move` 等）が `#if defined(__AVR__)` で自動適用されます。シムの検証は `test/internal/test_avr_std_shim.cpp` で行います。

- **PROGMEM 分岐のホスト検証**: `make -C test pgm-stub` が `__AVR__` とスタブ `test/stub/avr/pgmspace.h` で全テストをコンパイルし、PROGMEM コードパスをホストで検証します。
- **定義ヘッダの再生成**: `scripts/gen/gen_definitions.py --out-dir src/definition` で再生成できます。
- **定義テーブルは CI（`.github/workflows/update-definitions.yml`）で azarashi から自動生成されるため手編集禁止**です。
- **AVR プリセット**（`src/azaraC_config.h`）: 有効カテゴリはSEISMIC/TSUNAMIのみ(他カテゴリは無効)、`AZARAC_DEDUP_SLOTS=4`、`AZARAC_NANKAI_MAX_PAGES=4`、`AZARAC_NANKAI_BUFFERS=1`。Uno ジョブ（`.github/workflows/ci.yml`の`arduino-compile-required`）は`basic_ubx` / `basic_nmea` / `basic_uno`の3つをコンパイル/検証します。

## コーディング規約

### 命名規則

| 項目 | 規則 | 例 |
|------|------|-----|
| 名前空間 | `azaraC`, `azaraC::internal` | `azaraC::Parser` |
| クラス | PascalCase | `DedupFilter` |
| 関数 | camelCase | `feed()`, `decodeEEW()` |
| メンバ変数 | プレフィックス `_` | `_head`, `_mode` |
| 定数 | UPPER_SNAKE | `AZARAC_DEDUP_SLOTS` |

### メモリ管理とルール

- **ヒープアロケーションゼロ**: `new`, `malloc`等の動的メモリ管理はしないこと。
- **静的バッファ**: 固定サイズの配列を使用すること。
- **静的な定義テーブル**: RAM容量節約のためAVRでは`AZARAC_PROGMEM`経由でFlash(PROGMEM)を使用、非AVRではno-opを使用すること。
- **定義テーブルの格納形式**: AVRは文字列プール + `{offset,len}`（16bit×2）、非AVRは `const char*` 配列（4B/エントリ、32bit機）。非AVRのルックアップ戻り値は両者で `std::optional<std::string_view>` に統一し、`nullptr`＝欠落・`""`＝定義済み空文字列を区別すること（`opt`系エミッタと手書きの `qzss_dcx_camf_a3_provider_identifier.h` が対象）。文字列実体は各ヘッダにリテラルとして現れるが、リンカの重複統合により同一文字列は1コピーに落ちる。
- **AVRでの標準ライブラリ**： 基本AzaraCで実装したシム(`src/internal/avr_std/`)のみ利用するため、`std::`の新規関数の仕様はシムへの追加が必要

## 関連ドキュメント

- [API リファレンス](api-reference.md)
- [アーキテクチャドキュメント](architecture.md)
