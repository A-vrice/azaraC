# azaraC開発者ガイド

## 概要

azaraCライブラリの開発に貢献する開発者向けのガイドである。

## 開発環境のセットアップ

### 必要なツール

| ツール | バージョン | 用途 |
|-------|-----------|------|
| g++ | C++17対応 | ホストテストビルド |
| Python | 3.9+ | 定義ファイル生成 |
| make | - | ビルド自動化 |

mingw等のmakeでも動作する。

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

# 動的リンクしたテストバイナリが起動しない Windows 環境（0xC0000139 / 出力なし / exit 127）
make -C test run STATIC=1
```

`STATIC=1` はlibstdc++ / libgccを静的リンクする（`LDFLAGS` に `-static` を足すだけ）。
Linux CIでは不要である。

同じ `test/*.o` や `test/` 直下の成果物を共有するターゲット同士の同時実行は `test/scripts/with-make-lock.sh` が直列化し、`bench` / `test-time-irq` / `avr-layout` / `nmea-policy` / `utf8-trim` も含みます。
別のmakeが実行中ならexit 2で止まるので、終わるまで待つこと（ロックは終了時に自動で解放される）。
ロックだけが残るのはSIGKILLなどでtrapを実行できなかった場合だけなので、実行中のmakeが無いことを確認できたときだけ `test/.make-lock` を削除すること。
意図的にロックを迂回する場合は `make -C test AZARAC_LOCK_HELD=1 run` を使う。
`run-lang-defaults` と `test-no-alloc` は複数行レシピのためWindowsでは未検証である（Linux CIで実行）。
`nmea-policy` と `utf8-trim` も複数行レシピである。WindowsのMinGW環境で3構成 / 1構成とも `ok` を実測済みで、CIの `host-test` にもステップを追加した。

### テスト結果

`make -C test run` の最後にdoctestがケース数・アサーション数・成否を出力する。
```
$ make -C test run
[doctest] test cases:    ... |    ... passed | 0 failed | 0 skipped
[doctest] assertions: ... | ... passed | 0 failed |
[doctest] Status: SUCCESS!
```
件数はテストを追加するたびに変わるため、ここには固定値を書かない。CIのhost-testは同じ集計をGitHub Actionsのstep summaryに出力する。

### カバレッジの見方

`make -C test coverage` は既定構成（全カテゴリ + DCX/CAMF + dedup + Nankai）の行カバレッジを測る。
未到達行の多くは「その構成でしかコンパイルされない」もので、別ターゲットが担保する。

| 未到達の例 | 担当するターゲット |
|---|---|
| `DecoderQzqsm.cpp` の `DisabledAtCompileTime` 経路 | `make -C test macro`（13構成） |
| `PROGMEM` / far Flash分岐 | `make -C test pgm-stub`、`make -C test bench` |
| `azarac_utf8_trim_len` の打ち切り・不正先頭バイト | `make -C test utf8-trim` |
| `src/internal/avr_std/*`、`PrintShim.h` | AVR/ホストのシム専用（既定構成では通らない。対象外） |

残る未到達行は設計上の防御コード（`Decoder::resolveArrivalTime` の終端 `return`、`Parser` の `if (!buffer)` など）だけである。
逆に 既定構成で到達し得るのに未到達ならテストの穴なので、追加対象にする。

### テストカテゴリ

| ディレクトリ | 内容 |
|-------------|------|
| `core/` | CRC, 時間, 緯度経度, 重複除去 |
| `internal/` | 内部ヘルパ（DcxHelper, 情報有効時間DedupWindow, avr_stdシム） |
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
| `make -C test pgm-stub` | `__AVR__` + スタブ `avr/pgmspace.h` で全テストをコンパイルしPROGMEM分岐をホスト検証 |
| `make -C test test-time-irq` | `ARDUINO=1` + `__AVR__` + スタブ `avr/io.h` で `internal::getMillis()` の割り込み状態保存・復元と32 bit折り返しの64 bit拡張をホスト検証。ESP32は `esp_timer_get_time()` の64 bit分岐を使うため、このテストの対象外 |
| `make -C test run-small-pages` | `AZARAC_NANKAI_MAX_PAGES=8` で全体を再ビルドし、ページ打ち切り経路を検証（既定63では打ち切りが発生せず該当テストが `#if` で除外されるため） |
| `make -C test run-dedup-off` | `AZARAC_ENABLE_DEDUP=0` で全テストを再ビルド・実行し、dedup無効構成でもテストがコンパイル・動作することを検証（終了時に `clean`） |
| `make -C test avr-layout` | 実avr-g++ で `NankaiPageKey`/`NankaiPageBuffer`/`DedupFilter`/`Message` のABIサイズと `aggregated_text` オフセットを検証（63ページ・4ページ・DCX/CAMF有効の3構成、`-fsyntax-only`。`Message` は84 B / DCX有効199 B） |
| `make -C test nmea-policy` | `AZARAC_NMEA_STRICT_SVID` / `AZARAC_NMEA_REJECT_NONZERO_PADDING` の受理表を、既定・`STRICT_SVID=1`・`STRICT_SVID=2` + パディング拒否の3構成でビルド・実行してassert（`test/tools/nmea_policy_probe.cpp`）。マクロで分岐が消えるため `.o` は共有しない |
| `make -C test utf8-trim` | `AZARAC_FLASH_BUF_SIZE=64` で `azarac_utf8_trim_len` / `azarac_pgm_join_z` の打ち切りとUTF-8境界の丸めをassert（`test/tools/utf8_trim_probe.cpp`）。既定800 Bでは最長ラベル769 Bに届かず切り詰め経路が踏まれない |
| `make -C test run-lto` | `-O2 -flto -Werror=lto-type-mismatch -Werror=odr` で全体を再ビルド・実行し、リンク時最適化での型不一致・ODR違反・インライン後codegenの退行を検証（終了時に `clean`） |
| `make -C test decode` | decode_to_jsonのCLIビルド（azarashi比較用） |
| `make -C test dedup-realday` | 実日の `.l1s`（`realdata/`）に対する重複判定の再現計測。フレーム数・distinct・生存ピーク・再通知/取りこぼしをMETRIC行で出す。`REALDAY_CAT<n>_*` はカテゴリ別の内訳（`MISSED`=取りこぼし、`FALSE_RE`=再通知）、`REALDAY_UNALIGNED` は非整列フレーム数。`REALDAY_INPUT` で入力、`CXXFLAGS_EXTRA="-DAZARAC_DEDUP_SLOTS=…"` + `-B` で容量を変えて反復（`CXXFLAGS_EXTRA` は依存関係に載らないため、スイープ後は `make -C test clean` で残った `.o` を消す） |
| `make -C test bench` | 定義テーブルのAVRフットプリント計測（`test/bench/avr/autoresearch.sh` + `test/bench/avr/`）。avr-gcc / avr-libcとg++ / pythonが必要。ラベル一致（AVR far / AVR 16bit / ホスト）、ATmega2560での全カテゴリのコンパイル、UnoとMegaの実リンク、SRAM非増加、そしてコアのPROGMEMとazaraC自身のCRC24Q表がどちらも16bit窓（64KiB）内に残ることをゲートする。CIのhost-testでも実行 |
| `make -C test bench-dedup` | dedupフィルタのベンチ（`test/bench/bench_dedup.cpp`、`test/bench/run_dedup_bench.sh`）。`NEW_RECALL` / `DUP_SUPPRESS` / `*_KEY_STABLE` をゲート。hostのg++ だけで動く。CIのhost-testでも実行 |
| `make -C test compare-realdata` | azarashiとの処理比較（`pip install azarashi`が必要）。CI外（手動。azarashiパッケージが必要） |
| `make -C test check` / `check-xml` | 静的解析（cppcheck）と厳格コンパイルチェック |
| `make -C test coverage` | カバレッジ測定 |
| `make -C test test-no-alloc` | 公開APIが動的確保を行わないことの検証（GNU ldの `--wrap`。macOSではスキップ） |

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

生成ヘッダには `// Specs: IS-QZSS-DCR-017 / IS-QZSS-DCX-004 Rev.004 / EWSS CAMF Issue 1.2` が入る（`scripts/gen/gen_definitions.py` の `SPEC_BASELINE`）。仕様を改訂したらここを更新すること。azarashiの版だけでは「どの仕様に追随した更新か」が `git diff` から読めないためである。

自動更新PRは、作成前に `make -C test run` と `make -C test bench` を実行する（`.github/workflows/update-definitions.yml`）。既定の `GITHUB_TOKEN` で作ったPRは `push` でCIが起動せず、`pull_request` も承認待ちで止まるため、ゲートはPR作成前に置いている。

### 手書きの定義ヘッダ（`src/definition/manual/`）

`src/definition/` 直下の `*.h` はすべて自動生成物である。
自動で生成できない定義は `src/definition/manual/` に置く。

| ファイル | 手書きである理由 |
|---|---|
| `manual/ublox_qzss_svid_prn_map.h` | 生成される表の形（id → ラベル）に合わない小さな固定マップ |
| `manual/qzss_dcx_camf_a3_provider_identifier.h` | 生成器は1キーの参照しか出さないが、CAMF A3は `(country, provider)` の2キーで、戻り値も `std::optional` である必要がある |

`manual/` 以外は手編集してはいけない（先頭コメントにも `HAND-MAINTAINED` / `AUTO-GENERATED` と明記）。
`src/definition/*.h` が生成物だけであることは、lint・静的解析の除外パターン（`src/definition/*.h`）とレビューボットのignoreがこの区切りに依存しているため。`manual/` を直下へ移動させないこと。

### 言語ガードの規則

生成器は表が日本語か英語かで `AZARAC_LANG_JA` / `AZARAC_LANG_EN` のガードを付ける。判定は変数名から行う。

| 表の形 | ガード |
|---|---|
| `_en` が付く表で、同じ番号の `_ja` か無印のペアがある | `AZARAC_LANG_EN` |
| `_ja` が付く表、または同じ番号の `_en` ペアがある | `AZARAC_LANG_JA` |
| `qzss_dcr_jma_` 系統で `_en` ペアが無い（例: `information_serial_code`） | `AZARAC_LANG_JA` |
| それ以外（CAMF系など仕様自体が英語の表） | ガードなし（常にコンパイル） |

3行目が無いと、`AZARAC_LANG_JA=0` の構成でも日本語の表が生きていてラベルが漏れる。
`AZARAC_LANG_JA=0` の構成では該当の `_label` が `null` になる（3値規則の「表が無い」に相当）。
表を足すときはこの4行のどれに当たるか必ず確認すること。

### テストベクタの生成

`test/data/*_vectors.json` はazarashiの出力を参照ベクタとして固定したものである。
南海トラフ用の`test/data/nankai_pages_generated.h`は`gen_all_vectors.py` の `gen_nankai()` が同じ `nankai_vectors.json` から生成する派生物である。
いずれも直接編集せず更新の際はスクリプトで再生成すること。
ただし参照ベクタ（JSON）はazarashiのバージョンで形式が変わるため書き換えない。

```bash
# nankai_pages_generated.h だけを既存の JSON から再生成する（azarashi 不要・JSON は書き換えない）
python test/scripts/gen_all_vectors.py --nankai-header-only

# JSON ベクタごと作り直す場合（azarashi が必要。JSON は参照ベクタなので、固定を保つなら元に戻す）
pip install azarashi==0.17.1
python test/scripts/gen_all_vectors.py
git checkout -- test/data/dcr_vectors.json test/data/dcx_vectors.json test/data/nankai_vectors.json
```

`*_vectors.json` はazarashi 0.17.1で `params` の形が変わり（`type` の改名、`satellite_svid` の追加、`report_time` のタイムゾーン付与など）。
さらに `timestamp` と暦年の解決が `datetime.now()` に依存するため、再生成のたびに内容が変わる。
`*_vectors.json` は `make -C test bench-dedup`（`test/bench/bench_dedup.cpp`）や `compare_nankai_aggregation.py` が読む参照データとしてリポジトリに残すため、再生成後にコミットするのは `nankai_pages_generated.h` のみとします。
JSONは上のコマンドで元に戻す。
同ヘッダはazarashi 0.17.0と0.17.1で同一である。`.github/workflows/ci.yml` のfixture-driftもJSONは検査せずヘッダだけを見る。

## AVR開発

AVRツールチェーン（avr-gcc）はC++の標準ライブラリを一切含まないため、それらへの依存は`src/internal/avr_std/`にあるシム（`optional` / `string_view` / `std::move` 等）が自動で適用される。
シムは`test/internal/test_avr_std_shim.cpp`で検証する。

- **PROGMEM分岐のホスト検証**: `make -C test pgm-stub`が`__AVR__`とスタブ`test/stub/avr/pgmspace.h`で全テストをコンパイルする。
  PROGMEMコードパスをホストで検証する。
- **定義ヘッダの再生成**: `scripts/gen/gen_definitions.py --out-dir src/definition`で再生成できる。
- **定義テーブルはCI（`.github/workflows/update-definitions.yml`）でazarashiから自動生成されるため手編集禁止**である（例外は上記「手書きの定義ヘッダ」の2本のみである）。
- **AVRプリセット**（`src/azaraC_config.h`）: 有効カテゴリはボードによらずSEISMIC/TSUNAMIのみで、DCX/CAMFはオプトイン（`AZARAC_AVR_LARGE_FLASH=1` / `AZARAC_ENABLE_DCX_CAMF=1`。他10カテゴリは無効）。
  `AZARAC_DEDUP_SLOTS=64`（`AZARAC_DEDUP_WAYS=8`、512B）、`AZARAC_NANKAI_MAX_PAGES=4`、`AZARAC_NANKAI_BUFFERS=1`。
  `arduino-compile-required`（`.github/workflows/ci.yml`）はAVRをUnoとMega 2560の2台で見る — Unoは`basic_ubx` / `basic_nmea` / `basic_uno`の3つ、MegaはWiFi/RTOSを除く全exampleを既定カテゴリ（DCX/CAMF無効）でコンパイル/検証します。
  DCX/CAMF入りのfar-Flash構成は`make -C test bench`（`test/bench/avr/autoresearch.sh` stage 5）がArduinoの実レシピ（`-flto`）でリンクしてゲートする。SRAMの実測は892Bである。switch戦略のリテラルは、LTOで `.data` に落ちないよう名前空間スコープに置いている。
  LTO無しのMegaリンクは廃止した: 非LTO画像は約150KBで16bit関数ポインタの届く128KiBを超え、binutils 2.43ではリンクエラーになるためである（旧binutilsは警告で壊れたELFを通していました）。
- **64 KiBを超えるFlashを持つAVR**: 定義テーブルは64 KiBを超えて配置されるため、`AZARAC_PGM_READ_*` / `AZARAC_STRCPY_P`（16 bitのPROGMEMポインタ）では範囲外になる。
  このとき定義テーブル自身は `internal/FlashString.h` がfar参照へ切り替わる。
  RAM上の文字列と固定リテラルを比較するときは `AZARAC_STRNCMP_P(a, "literal", n)` を使うこと（AVRでは `strncmp_P(a, PSTR(b), n)` になり、リテラルがSRAMに載らない。非AVRでは `strncmp`）。
  16 bit読み出しを使うのは一部progmemクラスタに置く表（`AZARAC_PROGMEM_NEAR`: CRC24Q・半径・B4レイアウト）とJSONキー（`PSTR`）のみである。
  自前のデータを追加で置く場合もavr-libcのfar API（`pgm_get_far_address` + `pgm_read_*_far` / `memcpy_PF`）が必要である。
  64 KiB超のデバイスでは `AZARAC_PROGMEM` の配置先がArduinoコア（`core.a`）と競合するため、`.text.azaraC.<N>` に置く（配置の理由は `azaraC_config.h` のコメントとアーキテクチャの「メモリ設計」を参照）。

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
- **静的な定義テーブルを使用すること**: RAM容量節約のためAVRでは`AZARAC_PROGMEM`経由でFlash(PROGMEM)を使用、非AVRではno-opを使用すること。
  - **Flashが64KiBを超えるデバイスは配置先が変わる**: avr-libcのリンカスクリプトは `*(.progmem.*)` を `.text` の先頭にリンク順（Arduinoは `core.a`が最後）で並べる。
    ここに116KiBの表を置くとコア自身のPROGMEM（`digital_pin_to_port_PGM` など）が16bit窓の外へ押し出され、`pinMode`/`digitalWrite` が誤ったポートを読む。
    そこで `FLASHEND > 0xFFFF` では `AZARAC_PROGMEM` が `.text.azaraC.<N>`（progmemクラスタより後ろの `*(.text.*)`）を指す。
    `.progmemx.*` はbinutils 2.29以降にしか無く、同梱のatmel 2.26では広い `*(.progmem*)` に取り込まれて同じ失敗になる。
  - **宣言ごとに節を分ける**: 関数内の静的リテラル（switch戦略の `s[]`）はone-only（weak）。
    `AZARAC_PROGMEM` は `__COUNTER__` で節名を分ける（`-fdata-sections` と同じ粒度）。
    1つの節にまとめると、そのTUの1表が参照されただけで節全体が `--gc-sections` に残り、weakと通常配列も同居できない。
  - **16bitで読む表は `AZARAC_PROGMEM_NEAR`**: azaraC自身が `AZARAC_PGM_READ_*`（16bit）で読む表 — `src/decoder/Decoder.cpp`のCRC24Qニブル表、`src/internal/DcxHelper.cpp` の `RADIUS_TABLE` / `B4_LAYOUT_TABLE`— は低いprogmemクラスタに置く（farアクセサは要らない）。
  - **ゲート**: `autoresearch.sh` はコア側PROGMEMを模したオブジェクト（`test/bench/avr/core_progmem.c`）を最後にリンクし、そのアドレスが64KiB以内であることを確かめる。
    near表も `avr-nm` でアドレスを採って窓内を検査する。検査には `MEGA_NEAR_SYM_ADDR` を使い、表が消えた場合や別の節へ移った場合も失敗させる。
  - **付け忘れはSRAMを食う**: `AZARAC_PROGMEM` / `AZARAC_PROGMEM_NEAR` を付け忘れた `const` 配列は、avr-libcが `.rodata` を `.data`に含めるためそのままSRAMに入る。
  - 16エントリ程度の小さな表は作らずに計算する（`src/json/JsonWriter.cpp` の16進1文字は三項演算）。
- **定義テーブルの格納は効率よく**: AVRは文字列プール + `{offset}`（長さはプールのNUL区切りから `azarac_pgm_len` が取るので行に持たない）＋ 共有断片を使う表は親の添字（`0xFF`＝親なし、`<GUARD>_PARENT_POOL` の1件を参照）。
  非AVRは `const char*` 配列（4B/エントリ、32bit機）。
  同じ表の中で4件以上に共通する接頭辞／接尾辞（「北海道札幌市」の`北海道`、「Sapporo City, Hokkaido Prefecture」の` City, Hokkaido Prefecture`）は `strategy.py` の `factor_parents` が切り出す。
  参照時に `azarac_pgm_join_z` が既存の共有バッファ内で連結する（表ごとに1方向）。
  切り出した親も同じ規則で再帰的に切り出せ（2段目、`_GRAND_POOL` ＋ `azarac_pgm_join3`）。
  採用するのは削減量が追加コード（1呼び出しあたり60〜130B）を上回る表だけ（`GRAND_MIN_GAIN`）。
  switch戦略は行を持たないので共有断片のオフセットをcase本体に定数として埋め込む。
  非AVRのルックアップ戻り値は両者で `std::optional<std::string_view>` に統一し、`nullptr`＝欠落・`""`＝定義済み空文字列を区別すること。
  （`opt`系エミッタと手書きの `qzss_dcx_camf_a3_provider_identifier.h` が対象）
  文字列実体は各ヘッダにリテラルとして現れるが、リンカの重複統合により同一文字列は1コピーに落ちる。
- **共有断片はRAMを増やさないこと**: AVRの結合は `internal/FlashString.h` の共有バッファ（`AZARAC_FLASH_BUF_SIZE`）内で行う。
  Flashを削るためにSRAMを増やす変更は不可（`test/bench/avr/autoresearch.sh` が `UNO_RAM_BYTES` と `AVR_TABLES_IN_RAM` でゲートする）。
  テーブル変数名は `_TABLE` / `_POOL` で終えること（ゲートはその接尾辞で表を数える）。
- **JSONのキーは `AZARAC_KEY("key")` で包むこと**: `wf_u` / `wf_s` / `wk` / `writeDHM` などのキー引数は `internal::JsonKey` を取り、生の `const char*`からは暗黙変換できない。
  包み忘れはホスト（RAMリテラル）では正しく動きAVRだけ文字化けするので、コンパイルエラーにしてある。
  `AZARAC_KEY` はAVRでは `PSTR` を通してリテラルをFlashに置き（長さは `sizeof` で決まるので実行時の走査も切り詰めも無い）、非AVRでは素のポインタになる。
  固定の値リテラル（`"invalid_mt43"`、`arrival_status` の語、DCXの `dcx_type` ラベルなど）も同じ理由で `AZARAC_KEY("...")` で包む。
  `wf_s(out, key, AZARAC_KEY("..."))`（`JsonKey` オーバーロード）で出す。
  ルックアップ結果のように実行時に決まる文字列は `std::optional<std::string_view>` / `const char*` のオーバーロードに渡す（生成ヘッダの `_lookup` には `const char*`を返すものがある）。
  書き出しはキーも値もFlashから走査し、必要ならスタックの一時バッファ（`AZARAC_KEY_BUF_SIZE`、既定36B）へ1度写して出す。
  静的な共有バッファを持たないので、書き出し順序の制約はない。
- **RAM上の文字列と固定リテラルの比較には `AZARAC_STRNCMP_P` を使うこと**: `strncmp(buf, "QZQSM,", 6)` のリテラルはAVRでは `.data`（＝SRAM）に載る。
  `AZARAC_STRNCMP_P(buf, "QZQSM,", 6)` はAVRで `strncmp_P(buf, PSTR("QZQSM,"), 6)`、非AVRで `strncmp` に展開される（マクロ側が `PSTR` を付けるので呼び出しは素のリテラルのまま）。
  `make -C test pgm-stub` は `strncmp_P` のスタブ（`test/stub/avr/pgmspace.h`）経由でこの経路を通る。
- **カテゴリ無効時の型ガード**: `AZARAC_ENABLE_*` は定義テーブルだけでなくpayload型とgetterを消す（全12型）。
  カテゴリを追加するときは `src/Mt43Data.h` の6箇所（struct定義、`Mt43Data::ActiveType` の列挙子、`storage_size_` の `sizeof`、`getXxx()` のconst / 非const、`typeFor<T>()` の特殊化）と、対応するentry型を同じマクロで囲み、decoder / serializerは定義側だけでなく テストとサンプルも ガードする。
  `test/core/test_message_struct.cpp`、`test/json/test_json.cpp` の `initMt43As`、`test/json/test_json_wellformed.cpp`、`test/internal/test_dedup_window.cpp`、`test/integration/test_parser_clock.cpp`、`examples/*` にガードが無いと `make -C test macro` とCIの `arduino-compile-required` が落ちる。
  `test/data/test_realdata_generated.cpp` は生成物なので手で直さず、`test/scripts/gen_realdata_vectors.py` の `DC_TYPE_GUARDS`（= `DISABLED_DC_MACROS`）にマクロを足す。
  `internal/DedupWindow.h` も同じマクロで `case 5/10/11/14` と `ActiveType` 分岐をガードする（全対象カテゴリ無効時はpayload引数が未使用になるので `(void)payload;` を置く）。カテゴリ無効時にそのdcの窓は `default` のフォールバックへ落ちるため、`test_dedup_window.cpp` の仕様値アサートも同じマクロで囲む。
- **Flashが64KiBを超えるAVRではfar参照を使うこと**: 定義テーブルはリンク時に64KiBを超えて配置されるため、16bitのPROGMEMポインタでは届かない。
  配列のアドレスは `AZARAC_PGM_PTR(array)`（`FLASHEND > 0xFFFF` のデバイスでは `pgm_get_far_address`、それ以外は通常のポインタ）。
  行・プールの読み出しは `azarac_read_byte/word/dword` / `azarac_read_block` を経由する（`pgm_read_*_far` / `memcpy_PF`）。
  プール内のオフセットは16bitのままでよい（1プールは64KiB未満）。
  `make -C test pgm-stub` は「64KiB超のデバイス」を装ったホストビルドなので、far経路はそこで実行検証される。
- **AVRでの標準ライブラリ**： 基本azaraCで実装したシム(`src/internal/avr_std/`)のみ利用するため、`std::`の新規関数の仕様はシムへの追加が必要

## Issue / PRへのラベル付け

ラベルは `.github/workflows/labeler.yml` が自動付与する（付与のみで削除はしない）。

| ラベル | 付与条件 | 定義 |
|-------|---------|------|
| `dependencies` | PRのブランチ名が `renovate/` で始まる、または `renovate.json` を変更 | `.github/labeler.yml` |
| `ci` | `.github/**`、`platformio.ini.example`、`library.json`、`library.properties`、`keywords.txt` を変更 | 同上 |
| `test` | `test/**` を変更 | 同上 |
| `definition` | `src/definition/**` を変更（azarashi生成物 + 手書き2本） | 同上 |
| `documentation` | `docs/**`、`README.md`、`CHANGELOG.md` を変更 | 同上 |
| `dependencies` / `bug` / `documentation` / `enhancement` / `question` | Issueのタイトル・本文のキーワード（日本語・英語） | `.github/issue-labeler.yml` |

- 条件を変えるときは上記の設定ファイルだけを変更すること（ワークフロー本体は触らない）。
- 追加するラベルは先にリポジトリへ作成しておくこと（未作成の場合、そのラベルは無警告でスキップされる）。
- `issues` イベントのワークフローはデフォルトブランチ（`main`）の内容で動くため、Issueの自動ラベルは `main` にマージされてから有効になる。
  PR側はPR時点の内容で動く。
- 付与のみで削除はしない（`sync-labels` は無効）。よって手動で付与したラベルが自動で消えることはない。

```bash
gh label create <name> --color <hex> --description "<説明>"
```

## 文章とコメントの折り返し

- 固定桁での折り返しはしない。エディタやビューワのソフトウェアラップに任せる。
- Markdownは1文1行。段落内の改行はレンダラで空白になるため、文末以外で折らない。
- 1文が長い場合は、文を分割し、句点などで改行する。目安は表示幅160桁（全角80字）。
- それでもまだ文が長い場合は、読点などの節境界で折る。Markdownでは改行位置に空白が入ることを許容する。
- コードコメントも同じ。原則1文1行で書き、固定桁で折らない。
- 表・コードブロック・URL・生成物・第三者コード（`test/doctest.h` など）は対象外。
- ツール設定:
  - markdownlintのMD013（line length）は無効にする。
  - Prettierは `proseWrap: "preserve"` を使う。
  - clang-formatを使う場合は `ReflowComments: false` にする。

## 関連ドキュメント

- [APIリファレンス](api-reference.md)
- [アーキテクチャドキュメント](architecture.md)
- [JSON出力仕様](json-formats.md)
