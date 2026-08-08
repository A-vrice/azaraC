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
│   └── definition/           # 自動生成定義テーブル（103ファイル）
├── scripts/                  # 定義ファイル生成スクリプト
│   ├── gen/                  # 定義生成・AVR 移行（gen_definitions.py, apply_avr_headers.py, apply_avr_std_includes.py, strategy.py）
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
│   └── stub/avr/             # AVR 分岐検証用 pgmspace.h スタブ
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
| `make -C test decode` | decode_to_json CLI ビルド（azarashi 比較用） |
| `make -C test compare-realdata` | azarashi との実データ比較（`pip install azarashi` 必須） |
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

## AVR 開発

AVR ツールチェーン（avr-gcc）は libstdc++ を一切含まないため、標準ライブラリ依存は `src/internal/avr_std/` の最小シム（`optional` / `string_view` / `std::move` 等）が `#if defined(__AVR__)` で自動適用されます。シムの検証は `test/internal/test_avr_std_shim.cpp` で行います。

- **PROGMEM 分岐のホスト検証**: `make -C test pgm-stub` が `__AVR__` とスタブ `test/stub/avr/pgmspace.h` で全テストをコンパイルし、PROGMEM コードパスをホストで検証します。
- **生成ヘッダの AVR 移行**: 生成済み定義ヘッダの AVR 分岐追加は `scripts/gen/apply_avr_headers.py`、標準 include のシム切替は `scripts/gen/apply_avr_std_includes.py` が行います。生成物の再生成は `scripts/gen/gen_definitions.py --out-dir src/definition` です。
- **定義テーブルは CI（`.github/workflows/update-definitions.yml`）で azarashi から自動生成されるため手編集禁止**です。
- **AVR プリセット**（`src/azaraC_config.h`）: 有効カテゴリは SEISMIC/TSUNAMI のみ（他カテゴリは無効）、`AZARAC_DEDUP_SLOTS=4`、`AZARAC_NANKAI_BUFFERS=1`。Uno ジョブ（`.github/workflows/ci.yml` の `arduino-compile-required`）は `basic_ubx` / `basic_nmea` / `basic_uno` の 3 例題をコンパイル検証します。

## コーディング規約

### 命名規則

| 項目 | 規則 | 例 |
|------|------|-----|
| 名前空間 | `azaraC`, `azaraC::internal` | `azaraC::Parser` |
| クラス | PascalCase | `DedupFilter` |
| 関数 | camelCase | `feed()`, `decodeEEW()` |
| メンバ変数 | プレフィックス `_` | `_head`, `_mode` |
| 定数 | UPPER_SNAKE | `AZARAC_DEDUP_SLOTS` |

### メモリ管理

- **ヒープアロケーション禁止**: `new`, `malloc` を使用しない
- **静的バッファ**: 固定サイズの配列を使用
- **AVR では RAM 節約のため静的データは `AZARAC_PROGMEM` を使う**（`src/azaraC_config.h` のマクロ経由。AVR では Flash 配置、非 AVR では no-op）
- **AVR では標準ライブラリはシム範囲（`src/internal/avr_std/`）に限定**されるため、`std::` の新規使用はシムへの追加が必要

## 関連ドキュメント

- [API リファレンス](api-reference.md)
- [アーキテクチャドキュメント](architecture.md)
