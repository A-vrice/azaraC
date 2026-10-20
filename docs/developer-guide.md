# azaraC 開発者ガイド

## 概要

azaraCライブラリの開発に貢献する開発者向けのガイドです。

## 開発環境のセットアップ

### 必要なツール

| ツール | バージョン | 用途 |
|-------|-----------|------|
| g++ | C++17対応 | ホストテストビルド |
| Python | 3.9+ | 定義ファイル生成 |
| make | - | ビルド自動化 |

なおmakeはmingwなどのものでも問題ありません。

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
│   └── definition/           # 自動生成定義テーブル（140ファイル、_index.h で集約）
│       └── manual/           # 手書きの定義テーブル（2ファイル。生成器は触らない）
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
│   ├── bench/                # ベンチマーク（bench_dedup.cpp / avr/autoresearch.sh と AVR 計測一式）
│   ├── tools/                # decode_to_json 等 CLI
│   ├── scripts/              # azarashi 比較・ベクタ生成スクリプト
│   ├── stub/avr/             # AVR 分岐検証用 pgmspace.h スタブ
│   ├── data/                 # 生成フィクスチャ（参照ベクタ JSON、nankai_pages_generated.h、test_realdata_generated.cpp）
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
$ make -C test run
run_tests.exe
[doctest] doctest version is "2.5.0"
===============================================================================
[doctest] test cases:   418 |   418 passed | 0 failed | 0 skipped
[doctest] assertions: 10500 | 10500 passed | 0 failed |
[doctest] Status: SUCCESS!
```

### テストカテゴリ

| ディレクトリ | 内容 |
|-------------|------|
| `core/` | CRC, 時間, 緯度経度, 重複除去 |
| `internal/` | 内部ヘルパ（DcxHelper, 情報有効時間 DedupWindow, avr_std シム） |
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
| `make -C test test-time-irq` | `ARDUINO=1` + `__AVR__` + スタブ `avr/io.h` で `internal::getMillis()` の割り込み状態保存・復元をホスト検証 |
| `make -C test run-small-pages` | `AZARAC_NANKAI_MAX_PAGES=8` で全体を再ビルドし、ページ打ち切り経路を検証（既定 63 では打ち切りが発生せず該当テストが `#if` で除外されるため） |
| `make -C test run-lto` | `-O2 -flto -Werror=lto-type-mismatch -Werror=odr` で全体を再ビルド・実行し、リンク時最適化での型不一致・ODR 違反・インライン後 codegen の退行を検証（終了時に `clean`） |
| `make -C test decode` | decode_to_jsonのCLIビルド（azarashi 比較用） |
| `make -C test dedup-realday` | 実日の `.l1s`（`realdata/`）に対する重複判定の再現計測。フレーム数・distinct・生存ピーク・再通知/取りこぼしを METRIC 行で出す。`REALDAY_CAT<n>_*` はカテゴリ別の内訳（`MISSED`=取りこぼし、`FALSE_RE`=再通知）、`REALDAY_UNALIGNED` は非整列フレーム数。`REALDAY_INPUT` で入力、`CXXFLAGS_EXTRA="-DAZARAC_DEDUP_SLOTS=…"` + `-B` で容量を変えて反復（**`CXXFLAGS_EXTRA` は依存関係に載らないため、スイープ後は `make -C test clean`** で残った `.o` を消す） |
| `make -C test bench` | 定義テーブルの AVR フットプリント計測（`test/bench/avr/autoresearch.sh` + `test/bench/avr/`）。avr-gcc / avr-libc と g++ / python が必要。ラベル一致（AVR far / AVR 16bit / ホスト）、ATmega2560 での全カテゴリのコンパイル、Uno と Mega の実リンク、SRAM 非増加、そして**コアの PROGMEM と azaraC 自身の CRC24Q 表がどちらも16bit窓（64KiB）内に残る**ことをゲートする。CI の host-test でも実行 |
| `make -C test bench-dedup` | dedup フィルタのベンチ（`test/bench/bench_dedup.cpp`、`test/bench/run_dedup_bench.sh`）。`NEW_RECALL` / `DUP_SUPPRESS` / `*_KEY_STABLE` をゲート。host の g++ だけで動く。CI の host-test でも実行 |
| `make -C test compare-realdata` | azarashiとの処理比較（`pip install azarashi`が必要）。CI 外（手動。azarashi パッケージが必要） |
| `make -C test check` / `check-xml` | 静的解析（cppcheck）と厳格コンパイルチェック |
| `make -C test coverage` | カバレッジ測定 |
| `make -C test test-no-alloc` | 公開 API が動的確保を行わないことの検証（GNU ld の `--wrap`。macOS ではスキップ） |

## 定義ファイルの自動生成

### 生成の仕組み

```text
azarashi (PyPI) → definition/*.py
    ↓ scripts/gen/gen_definitions.py --out-dir src/definition
src/definition/*.h
    ↓ GitHub Actions (毎日 06:00 UTC)
PR自動作成 → レビュー → マージ
```

### 手動での定義テーブル生成

```bash
pip install --upgrade azarashi
python scripts/gen/gen_definitions.py --out-dir src/definition
```

### 手書きの定義ヘッダ（`src/definition/manual/`）

`src/definition/` 直下の `*.h` はすべて自動生成物です。手書きの定義だけを `src/definition/manual/` に置きます。生成器は `SKIP_MODULES` で生成対象から外し、`extra_headers` として `_index.h` の末尾に include を残すだけで、この 2 本の中身を書き換えません。

| ファイル | 手書きである理由 |
|---|---|
| `manual/ublox_qzss_svid_prn_map.h` | 生成される表の形（id → ラベル）に合わない小さな固定マップ |
| `manual/qzss_dcx_camf_a3_provider_identifier.h` | 生成器は 1 キーの lookup しか出さないが、CAMF A3 は `(country, provider)` の 2 キーで、戻り値も `std::optional` である必要がある |

`manual/` 以外は手編集してはいけません（先頭コメントにも `HAND-MAINTAINED` / `AUTO-GENERATED` と明記）。`src/definition/*.h` が生成物だけであることは、lint・静的解析の除外パターン（`src/definition/*.h`）とレビューボットの ignore がこの区切りに依存しているため、`manual/` を直下へ戻さないでください。

### テストベクタの生成

`test/data/*_vectors.json` は azarashi の出力を参照ベクタとして固定したものです。南海トラフ用の`test/data/nankai_pages_generated.h`は`gen_all_vectors.py` の `gen_nankai()` が同じ `nankai_vectors.json` から生成する派生物で、いずれも直接編集せず再生成してください。参照ベクタ（JSON）は azarashi のバージョンで形式が変わるため書き換えません。

```bash
# nankai_pages_generated.h だけを既存の JSON から再生成する（azarashi 不要・JSON は書き換えない）
python test/scripts/gen_all_vectors.py --nankai-header-only

# JSON ベクタごと作り直す場合（azarashi が必要。JSON は参照ベクタなので、固定を保つなら元に戻す）
pip install azarashi==0.17.1
python test/scripts/gen_all_vectors.py
git checkout -- test/data/dcr_vectors.json test/data/dcx_vectors.json test/data/nankai_vectors.json
```

`*_vectors.json` は azarashi 0.17.1 で `params` の形が変わり（`type` の改名、`satellite_svid` の追加、`report_time` のタイムゾーン付与など）、さらに `timestamp` と暦年の解決が `datetime.now()` に依存するため、再生成のたびに内容が変わります。`*_vectors.json` は `make -C test bench-dedup`（`test/bench/bench_dedup.cpp`）や `compare_nankai_aggregation.py` が読む参照データとしてリポジトリに残すため、**再生成後にコミットするのは `nankai_pages_generated.h` のみ**とし、JSON は上のコマンドで元に戻します（同ヘッダは azarashi 0.17.0 と 0.17.1 で同一。`.github/workflows/ci.yml` の fixture-drift も JSON は検査せずヘッダだけを見ます）。

## AVR 開発

AVRツールチェーン（avr-gcc）はC++の標準ライブラリを一切含まないため、それらへの依存は`src/internal/avr_std/`にあるシム（`optional` / `string_view` / `std::move` 等）が自動で適用されます。シムは`test/internal/test_avr_std_shim.cpp`で検証します。

- **PROGMEM 分岐のホスト検証**: `make -C test pgm-stub`が`__AVR__`とスタブ`test/stub/avr/pgmspace.h`で全テストをコンパイルし、PROGMEMコードパスをホストで検証します。
- **定義ヘッダの再生成**: `scripts/gen/gen_definitions.py --out-dir src/definition`で再生成できます。
- **定義テーブルは CI（`.github/workflows/update-definitions.yml`）でazarashiから自動生成されるため手編集禁止**です（例外は上記「手書きの定義ヘッダ」の2本のみ）。
- **AVR プリセット**（`src/azaraC_config.h`）: 有効カテゴリはボードによらずSEISMIC/TSUNAMIのみで、DCX/CAMFはオプトイン（`AZARAC_AVR_LARGE_FLASH=1` / `AZARAC_ENABLE_DCX_CAMF=1`。他10カテゴリは無効）、`AZARAC_DEDUP_SLOTS=64`（`AZARAC_DEDUP_WAYS=8`、512B）、`AZARAC_NANKAI_MAX_PAGES=4`、`AZARAC_NANKAI_BUFFERS=1`。`arduino-compile-required`（`.github/workflows/ci.yml`）はAVRをUnoとMega 2560の2台で見ます — Unoは`basic_ubx` / `basic_nmea` / `basic_uno`の3つ、MegaはWiFi/RTOSを除く全exampleを既定カテゴリ（DCX/CAMF無効）でコンパイル/検証します。DCX/CAMF入りのfar-Flash構成は`make -C test bench`（`test/bench/avr/autoresearch.sh` stage 5）が実avr-gccでリンクしてゲートします。同 stage 5b は Arduino の実レシピ（`-flto`）でも組み、LTO 画像の SRAM を計測します（レポートのみ。switch 戦略のリテラルは LTO で `.data` に落ちないよう名前空間スコープに置いており、実測 896B）。

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

- **ヒープアロケーションをしないこと**: `new`, `malloc`等の動的メモリ管理はしないこと。
- **静的バッファを基本とすること**: 固定サイズの配列を使用すること。
- **静的な定義テーブルを使用すること**: RAM容量節約のためAVRでは`AZARAC_PROGMEM`経由でFlash(PROGMEM)を使用、非AVRではno-opを使用すること。**Flashが64KiBを超えるデバイスでは配置先が変わる**: avr-libcのリンカスクリプトは `*(.progmem.*)` を `.text` の先頭に、リンク順（Arduinoは `core.a` が最後）に並べるため、ここに116KiBの表を置くとコア自身のPROGMEM（`digital_pin_to_port_PGM` など）が16bit窓の外へ押し出され、`pinMode`/`digitalWrite` が誤ったポートを読む。そこで `FLASHEND > 0xFFFF` では `AZARAC_PROGMEM` が `.text.azaraC.<N>`（`*(.text.*)` クラスタ。`.text` の先頭のprogmemクラスタより後ろ）を指す（`.progmemx.*` は binutils 2.29 以降のスクリプトにしか無く、同梱の atmel 2.26 では広い `*(.progmem*)` に取り込まれて同じ失敗になる）。関数内の静的リテラル（switch戦略の `s[]`）は one-only（weak）なので、`AZARAC_PROGMEM` は宣言ごとに `__COUNTER__` で別の節名（`.text.azaraC.<N>`）を付ける（`-fdata-sections` と同じ粒度。1つの節にまとめると、そのTUの1表が参照されただけで節全体が `--gc-sections` に残り、weakと通常配列の同居もできない）。`autoresearch.sh` はコア側PROGMEMを模したオブジェクトを最後にリンクし、そのアドレスが64KiB以内に収まることをゲートする（`test/bench/avr/core_progmem.c`）。azaraC 自身が 16bit の `AZARAC_PGM_READ_*` で読む表も同じ窓の制約を受ける: `src/decoder/Decoder.cpp` の CRC24Q ニブル表 3×16B、`src/internal/DcxHelper.cpp` の `RADIUS_TABLE` / `B4_LAYOUT_TABLE` は `AZARAC_PROGMEM_NEAR`（＝ `PROGMEM`。読み出しが16bitで届くので far アクセサは要らず、低い progmem クラスタに置く）で持ち、`autoresearch.sh` が `avr-nm` でそれらのアドレスを採取して64KiB以内であることをゲートする（`MEGA_NEAR_SYM_ADDR`。表が消えた・別の節へ移った場合も失敗させる）。**`AZARAC_PROGMEM` / `AZARAC_PROGMEM_NEAR` を付け忘れた `const` 配列は、avr-libc のリンカスクリプトが `.rodata` を `.data` に含めるためそのまま SRAM を食う**（実測: B4 レイアウト表 585B + 半径表 128B = 713B）。16エントリ程度の小さな表は作らずに計算する（`src/json/JsonWriter.cpp` の16進1文字は三項演算。表は畳まれないビルドでは `.data` を食い、畳まれるビルドでも Flash に 17B 残る。実測: Uno 実リンク 13,546B → 13,982B）。
- **定義テーブルの格納は効率よく**: AVRは文字列プール + `{offset}`（長さはプールのNUL区切りから `azarac_pgm_len` が取るので行に持たない）＋ 共有断片を使う表は親の添字（`0xFF`＝親なし、`<GUARD>_PARENT_POOL` の1件を参照）、非AVRは `const char*` 配列（4B/エントリ、32bit機）。同じ表の中で4件以上に共通する接頭辞／接尾辞（「北海道札幌市」の`北海道`、「Sapporo City, Hokkaido Prefecture」の` City, Hokkaido Prefecture`）は `strategy.py` の `factor_parents` が切り出し、参照時に `azarac_pgm_join_z` が既存の共有バッファ内で連結する（表ごとに1方向）。切り出した親も同じ規則で再帰的に切り出せ（2段目、`_GRAND_POOL` ＋ `azarac_pgm_join3`）、採用するのは削減量が追加コード（1呼び出しあたり60〜130B）を上回る表だけ（`GRAND_MIN_GAIN`）。switch戦略は行を持たないので共有断片のオフセットをcase本体に定数として埋め込む。非AVRのルックアップ戻り値は両者で `std::optional<std::string_view>` に統一し、`nullptr`＝欠落・`""`＝定義済み空文字列を区別すること（`opt`系エミッタと手書きの `qzss_dcx_camf_a3_provider_identifier.h` が対象）。文字列実体は各ヘッダにリテラルとして現れるが、リンカの重複統合により同一文字列は1コピーに落ちる。
- **共有断片はRAMを増やさないこと**: AVRの結合は `internal/FlashString.h` の共有バッファ（`AZARAC_FLASH_BUF_SIZE`）内で行う。Flashを削るためにSRAMを増やす変更は不可（`test/bench/avr/autoresearch.sh` が `UNO_RAM_BYTES` と `AVR_TABLES_IN_RAM` でゲートする）。テーブル変数名は `_TABLE` / `_POOL` で終えること（ゲートはその接尾辞で表を数える）。
- **JSONのキーは `AZARAC_KEY("key")` で包むこと**: `wf_u` / `wf_s` / `wk` / `writeDHM` などのキー引数は `internal::JsonKey` を取り、生の `const char*` からは暗黙変換できない（包み忘れはホスト＝RAMリテラルでは正しく動き、AVRだけ文字化けするので、コンパイルエラーにしてある）。`AZARAC_KEY` は AVRでは `PSTR` を通してリテラルをFlashに置き（長さは `sizeof` で決まるので実行時の走査も切り詰めも無い）、非AVRでは素のポインタになる。書き出し時にキーは `JsonWriter.cpp` の共有バッファ（`AZARAC_KEY_BUF_SIZE`、既定36B）へ1度だけ写す — ラベルは呼び出し側で `FlashString.h` の共有バッファに既に展開済みなので、同じバッファを使うとキーのコピーがラベルを壊す。固定の値リテラル（`"invalid_mt43"`、`arrival_status` の語、DCX の `dcx_type` ラベルなど）も同じ理由で `AZARAC_KEY("...")` で包み、`wf_s(out, key, AZARAC_KEY("..."))`（`JsonKey` オーバーロード）で出す。ルックアップ結果のように実行時に決まる文字列は従来どおり `std::optional<std::string_view>` / `const char*` のオーバーロードに渡す（生成ヘッダの `_lookup` は `const char*` を返すものがあるので、その経路は残してある）。AVR ではキーと値が同じ 1 次コピー先を共有するため、**キーを書き終えてから値の `keyView` を取る**順序が契約で、ホスト（リテラルを直接指す）では順序の誤りを検出できず `make -C test pgm-stub` が `__AVR__` 経路で落とす。
- **RAM上の文字列と固定リテラルの比較には `AZARAC_STRNCMP_P` を使うこと**: `strncmp(buf, "QZQSM,", 6)` のリテラルは AVR では `.data`（＝SRAM）に載る。`AZARAC_STRNCMP_P(buf, "QZQSM,", 6)` は AVR で `strncmp_P(buf, PSTR("QZQSM,"), 6)`、非AVR で `strncmp` に展開される（マクロ側が `PSTR` を付けるので呼び出しは素のリテラルのまま）。`make -C test pgm-stub` は `strncmp_P` のスタブ（`test/stub/avr/pgmspace.h`）経由でこの経路を通る。
- **カテゴリ無効時の型ガード**: `AZARAC_ENABLE_EEW` / `AZARAC_ENABLE_HYPOCENTER` / `AZARAC_ENABLE_NANKAI` は定義テーブルだけでなく payload 型と getter を消す。カテゴリを追加するときは `src/Mt43Data.h` の 6 箇所（struct 定義、`Mt43Data::ActiveType` の列挙子、`storage_size_` の `sizeof`、`getXxx()` の const / 非 const、`typeFor<T>()` の特殊化）を同じマクロで囲み、decoder / serializer は定義側だけでなく **テストとサンプルも** ガードする — `test/core/test_message_struct.cpp`、`test/json/test_json.cpp` の `initMt43As`、`test/json/test_json_wellformed.cpp`、`examples/*` にガードが無いと `make -C test macro` と CI の `arduino-compile-required` が落ちる。`test/data/test_realdata_generated.cpp` は生成物なので手で直さず、`test/scripts/gen_realdata_vectors.py` の `DC_TYPE_GUARDS` にマクロを足す。`internal/DedupWindow.h` が参照する津波・気象・洪水・海上の payload は decode 設定と無関係に dedup が使うのでガードしない。
- **Flashが64KiBを超えるAVRではfar参照を使うこと**: 定義テーブルはリンク時に64KiBを超えて配置されるため、16bitのPROGMEMポインタでは届かない。配列のアドレスは `AZARAC_PGM_PTR(array)`（`FLASHEND > 0xFFFF` のデバイスでは `pgm_get_far_address`、それ以外は通常のポインタ）、行・プールの読み出しは `azarac_read_byte/word/dword` / `azarac_read_block` を経由する（`pgm_read_*_far` / `memcpy_PF`）。プール内のオフセットは16bitのままでよい（1プールは64KiB未満）。`make -C test pgm-stub` は「64KiB超のデバイス」を装ったホストビルドなので、far経路はそこで実行検証される。
- **AVRでの標準ライブラリ**： 基本azaraCで実装したシム(`src/internal/avr_std/`)のみ利用するため、`std::`の新規関数の仕様はシムへの追加が必要

## Issue / PR へのラベル付け

ラベルは `.github/workflows/labeler.yml` が自動付与します（付与のみで削除はしません）。

| ラベル | 付与条件 | 定義 |
|-------|---------|------|
| `dependencies` | PR のブランチ名が `renovate/` で始まる、または `renovate.json` を変更 | `.github/labeler.yml` |
| `ci` | `.github/**`、`platformio.ini.example`、`library.json`、`library.properties`、`keywords.txt` を変更 | 同上 |
| `test` | `test/**` を変更 | 同上 |
| `definition` | `src/definition/**` を変更（azarashi 生成物 + 手書き2本） | 同上 |
| `documentation` | `docs/**`、`README.md`、`CHANGELOG.md` を変更 | 同上 |
| `dependencies` / `bug` / `documentation` / `enhancement` / `question` | Issue のタイトル・本文のキーワード（日本語・英語） | `.github/issue-labeler.yml` |

- 条件を変えるときは上記の設定ファイルだけを変更すること（ワークフロー本体は触らない）。
- 追加するラベルは先にリポジトリへ作成しておくこと（未作成の場合、そのラベルは無警告でスキップされる）。
- `issues` イベントのワークフローはデフォルトブランチ（`main`）の内容で動くため、Issue の自動ラベルは `main` にマージされてから有効になる。PR 側は PR 時点の内容で動く。
- 付与のみで削除はしない（`sync-labels` は無効）。よって手動で付与したラベルが自動で消えることはない。

```bash
gh label create <name> --color <hex> --description "<説明>"
```

## 関連ドキュメント

- [API リファレンス](api-reference.md)
- [アーキテクチャドキュメント](architecture.md)
- [JSON 出力仕様](json-formats.md)
