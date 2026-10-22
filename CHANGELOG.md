# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- **CI に LTO ゲートを追加**: `make -C test run-lto` を新設し、host-test で `-O2 -flto` の全体再ビルド・テスト実行を必須にした。LTO の型不一致（`-Wlto-type-mismatch`）と ODR 違反（`-Wodr`）は GCC では既定で警告に留まり素の `-flto` では緑のままなので、この 2 つだけ `-Werror` にしてゲートで落とす（過去に `AZARAC_DEDUP_SLOTS` の配列長不一致を LTO だけが検出した事例がある）。`CXXFLAGS` は依存関係に載らないため `-B` で再ビルドし、終了時に `clean` する。あわせて `wf_deg` の桁数ループに上限 9 を明示し、`-O2 -flto` で出ていた `-Wstringop-overflow` の偽陽性を解消した（`buf[12]` に対する値域証明）。

### Fixed

- **レビュー指摘の修正（コア）**: `internal::getMillis()` が `noInterrupts()` の後に無条件で `interrupts()` を呼び、呼び出し側の割り込み禁止区間を破っていた問題を修正した。AVR は `SREG`、Cortex-M は `PRIMASK` を退避・復元し、`test-time-irq`（`ARDUINO=1` / `__AVR__` のホストスタブ）で検証する。`NmeaFramer` は 2 桁でも 6bit に収まらない Satellite ID 64–99 を拒否する（0–52 は PRN 128–180 として通すが契約外）。`Parser.h` の `report_unix=0` の説明を実装（未解決）に合わせ、`Parser::feed()` のカスタムフレーマ経路で局所 `Frame` をゼロ初期化し、`IFramer::feed()` に Frame の全フィールドを埋める契約を明記した。UBX の `numWords` は実データに合わせて 8/9 のみ受理し（9 は u-blox が付ける余剰 word）、10 以上はコメントと回帰テストで拒否する。
- **FreeRTOS example の出力競合**: RX タスク（集約済み南海トラフ）と Output タスクが同じ `Serial` に書いていたため、JSON 1 通・統計行・起動行を FreeRTOS ミューテックスで直列化した。キューは引き続き `Message` のバイトコピーで、payload が trivially copyable で所有ポインタを持たないこと（標準のコピー意味論ではなくオブジェクト表現のコピーとして扱う）、借用ポインタを持つ集約済み南海トラフを載せないことをコメント化した。`xTaskCreatePinnedToCore` を使うため ESP32 専用であることも明示した。
- **レビュー指摘（計測・サンプル）を反映**: `test/bench/avr/shim/Arduino.h` の `Print::print()` を実コア同様に `write()` へ流した。従来は空実装だったため LTO が `writeUint32` / `writeUint64` の桁変換など「出力を作る側」の処理ごと削除でき、計測した Flash が実スケッチより小さかった。これで JSON の区切り・`null`・エスケープ列の生リテラルが `.data`（SRAM）に現れたため、`writeRaw(Print&, JsonKey)` を追加して `AZARAC_KEY` 経由で Flash に置いた。最終実測（`make -C test bench`）: Uno 15,692B / 142B、Mega 148,516B / 892B、Mega LTO 144,408B / 892B。`examples/rtos_freertos` のミューテックスは `xSemaphoreCreateMutexStatic()` + `StaticSemaphore_t` にして FreeRTOS ヒープを消費しない。PR で追加した英語コメントは日本語に揃えた。
- **テスト・ドキュメント整理**: JSON DCX シリアライザの B4 ブロックのインデントを直し、未使用の `has()` オーバーロードを削除した。テスト件数を 418 ケース / 10,500 アサーションに更新し、NMEA の svid 範囲（64–99 拒否、0–52 は契約外）を `architecture.md` / `json-formats.md` に追記した。

### Changed

- **AVR の payload 枠から `alignas(8)` のパディングを外した**: `Mt43Data::storage_` / `Message::payload_storage_` の `alignas(8)` を `alignas(uint64_t)` にした。avr-gcc の `__alignof__(unsigned long long)` は 1 なので AVR ではこの指定が境界を要求せず、8 の倍数への切り上げだけが残っていた（ホストは `alignof(uint64_t)` が 8 で、レイアウトは不変）。ATmega328P `-Os` の実測: `sizeof(Mt43Data)` 88B → 80B / `sizeof(Message)` 104B → 89B、全カテゴリ有効時は 128B → 118B / 144B → 127B。`Message` はスケッチがグローバルに置くとそのまま `.bss` を食うので、利用側の SRAM も同じだけ減る。あわせて `AZARAC_KEY_BUF_SIZE` の既定を 40B → 36B にした（最長キーは 35B で、`static_assert` と `keyBuf()` の書き込み添字はそのまま成立する）。AVR ベンチ実測: Uno 146B → 142B（data 30 + bss 112、`keyBuf` 40B → 36B）、Mega + DCX/CAMF 896B → 892B（LTO 構成も 892B）、Flash は Uno 14,622B → 14,702B / Mega 146,700B → 146,550B。JSON の出力バイト列は不変（`test/json/*` の期待文字列テストとホスト 418 ケースがそのまま通る）。
- **AVR ベンチのスタブが `SREG` / `cli()` を提供していなかった**: f41550a で `internal::getMillis()` が AVR で `SREG` を退避・復元するようになったが、`test/bench/avr/shim/Arduino.h` は Arduino コアの `millis` / `Print` しか持っておらず、`make -C test bench` の Uno / Mega / LTO の全構成が `'cli' was not declared in this scope` でコンパイルに失敗していた（exit 12）。実コアと同じく `<avr/interrupt.h>` / `<avr/io.h>` を取り込むようにした（`FlashString.h` が `FLASHEND` 用に後者を既に含むため、`SREG` はマクロのこともある）。
- **レビュー指摘の記述を実装に合わせた**: `feed()` が `false` を返す理由（フレーム未完成・CRC誤り・重複でも `false`。`msg.unsupported_reason` に入るのは復号器が完成フレームを拒否した場合だけ）を `docs/api-reference.md` の 3 箇所で明確にし、`unsupported_category` が出るのは手動で構築した `Mt43Data` の直列化だけであること（受信電文の復号では無効カテゴリは拒否され `payload_type` は `Empty`）を `docs/json-formats.md` に、AVR プリセットで除外される payload 型が `EewData` / `HypocenterData` / `NankaiData` だけで `SeismicData` / `TsunamiData` はカテゴリを無効にしても定義が残ることを `README.md` に書いた。
- **AVR の計測に実機構成のゲートを追加**: `test/bench/avr/autoresearch.sh` の stage 5b（Arduino コアと同じ `-flto` の構成）は、リンクできることと ATmega2560 の SRAM 8,192B に収まることがゲートになった（実測 896B）。プローブ（`test/bench/avr/probe.cpp`）は入力バイトを `volatile` にして `feed()` が「フレーム未完成」に畳み込まれないようし、出力 sink の `write()` を不透明（中身を見ない演算）にしてシリアライズ経路と定義表が画像に残るようした。リンク画像に復号経路・シリアライザ・定義表が残っているかもゲートで検査する（実測: Uno に表 8 / Mega に 100 / Mega LTO に 98 シンボルが残る）。プローブの sink で Uno の画像は +132B（14,470 → 14,602）、Mega は +18B（146,672 → 146,690）。SRAM は変わらない（Uno 146B / Mega 896B）。いずれも計測プローブの改造によるもので、ライブラリのコードも公開 API・JSON の出力も変わらない。
- **生成物と手書き物の置き場を分けた**: `test/integration/test_realdata.cpp`（`gen_realdata_vectors.py` の生成物）を `test/data/test_realdata_generated.cpp` へ、ルート直下の `autoresearch.sh` を `test/bench/avr/autoresearch.sh` へ移動した。`src/definition/` の手書き2本（svid→PRN マップ、CAMF A3 提供者名）も `src/definition/manual/` へ移し、直下は生成物だけになった — 生成器の `extra_headers`、`_index.h` の include、`greptile.json` / `.codacy` の除外パターン（`src/definition/*.h`）を追随させた。
- **手書きテーブル2本の出所表記を修正**: `qzss_dcx_camf_a3_provider_identifier.h` が「AUTO-GENERATED」と名乗っていたのを `HAND-MAINTAINED` に直し、`_index.h` の件数行を実態（138 generated + 2 hand-written）に合わせた。

- **無効カテゴリの payload 型をコンパイルから外した（AVR の SRAM を解放）**: `EewData`（`regions[80]` を含む 105B）と `HypocenterData` を `AZARAC_ENABLE_EEW` / `AZARAC_ENABLE_HYPOCENTER` でガードし、既存の `NankaiData` と同じ扱いにした — struct 定義、`Mt43Data::ActiveType` の列挙子、`storage_size_` の `sizeof`、`getEew()` / `getHypocenter()`（const / 非 const 計 4 定義）、`typeFor<…>()` の特殊化。AVR プリセットは既定で両方 0 なので `Mt43Data` の payload 枠は 128B → 88B、`Message` は 144B → 104B（avr-gcc `-Os`、ATmega328P で `sizeof` を実測）。効くのは EEW の `regions[80]` だけで、`HypocenterData`（22B）は他カテゴリの最大値（津波 / 北太平洋津波の 67B）を超えないため単独では 0B の削減。`internal/DedupWindow.h` が参照する津波・気象・洪水・海上の payload は decode 設定と無関係に dedup が使うのでガードしない。decoder / serializer の呼び出し側は元からすべて `#if` 内だったが、テスト（`test_message_struct` / `test_json` / `test_json_wellformed` / `test_realdata`）と `examples/filter_by_category`・`examples/with_sntp` の EEW / 震源の case にガードを足した。`AZARAC_ENABLE_EEW=0` / `AZARAC_ENABLE_HYPOCENTER=0` の `make -C test macro` は 13 マクロすべて通る。
- **JSON の値リテラルも Flash へ移した**: `wf_s` に `JsonKey` の値を受け取るオーバーロードを足し、`"invalid_mt43"` / `"unsupported_category"` / `"unsupported_msg_type"` / `"invalid_mt44"`、`arrival_status` の 4 語（`arrival_estimated` / `arrived_or_unknown` / `no_information` / `unrecognized_code`）、DCX の `dcx_type` ラベル（`NULL` / `L_ALERT` / `J_ALERT` / `LOCAL_GOV` / `OUTSIDE_JAPAN` / `UNKNOWN`）を `AZARAC_KEY(...)` 経由にした。あわせて `QZQSM,` の先頭一致を `strncmp` から `AZARAC_STRNCMP_P`（AVR は `strncmp_P(a, PSTR(b), n)`、非 AVR は `strncmp`）にした。AVR の実測（`make -C test bench`）: Uno の `.data` 88B → 30B（残るのは allocator のグローバルと framer の vtable 2 つ）、フラッシュ +194B（14,276B → 14,470B）。Mega + DCX/CAMF は `.data` 234B → 44B、フラッシュ +154B（146,518B → 146,672B）。JSON の出力バイト列は不変（`test/json/*` の期待文字列テストがそのまま通る）。
- **JSON のキーを Flash へ移した（AVR の SRAM を大きく解放）**: `wf_u` / `wf_u64` / `wf_x` / `wf_deg` / `wf_s` / `wf_v` / `wk` / `writeDHM` / `writeLatLon` のキー引数を `std::string_view` から `internal::JsonKey` に変え、呼び出し側は `AZARAC_KEY("key")` で包む。AVR では `PSTR`（avr-libc）でリテラルをその場で `__progmem__` の static 配列にし、長さは `sizeof` で決まる（実行時の NUL 走査も切り詰めも無い）。非AVR では素のポインタと長さになるだけで出力は不変。`JsonKey` は生の `const char*` から暗黙変換できない（`explicit`）ので、包み忘れは**ホストのコンパイルで落ちる** — ホストのリテラルは RAM にあるため、包み忘れはホストでは正しく動いて AVR だけ文字化けするからだ。書き出し時はキーを `JsonWriter.cpp` の 40B の共有バッファ（`AZARAC_KEY_BUF_SIZE`）へ 1 度だけ写す: ラベルは呼び出し側で `internal/FlashString.h` の共有バッファへ既に展開済みで、同じバッファを使うとキーのコピーがラベルを壊す（`wf_s` はキー→ラベルの順に書く）。`keys::note` 等の共有キー定数は `AZARAC_KEY("note")` に置き換えて削除した。理由: avr-libc のリンカスクリプトは `*(.rodata*)` を `.data` に含めるため、JSON のキーリテラルはそのまま SRAM に載っていた（Uno の `.data` 564B のうち約 537B がキー、Mega の DCX/CAMF 構成では約 1.8KB）。実測（`autoresearch.sh`、値リテラルの Flash 化まで含めた最終値）: Uno プリセット（SEISMIC/TSUNAMI、JA、LTO リンク）RAM 640B → **146B**（data 564 → 30、bss 76 → 116 = キーバッファ 40B）、フラッシュ 13,546B → 14,470B（+924B）。Mega（DCX/CAMF をオプトイン、LTO なしリンク）RAM 3,714B → **896B**（data 2,902 → 44）、フラッシュ 144,806B → 146,672B（+1,866B）。
- **AVR で SRAM に落ちていた補助テーブルを Flash へ移した**: `internal/DcxHelper.cpp` の半径表（`radius_table_m` → `RADIUS_TABLE`、128B）と B4 レイアウト表（`B4_LAYOUTS` → `B4_LAYOUT_TABLE`、585B）は `const` の配列だが、avr-libc のリンカスクリプトが `.rodata` を `.data`（SRAM）へ含めるため、そのまま SRAM を食っていた（Mega の DCX/CAMF リンクで 585B は `0x800227`、128B は `0x800470`）。新設の `AZARAC_PROGMEM_NEAR`（AVR では `PROGMEM`。読み出しが 16bit の `AZARAC_PGM_READ_*` で届く低い progmem クラスタに置く。`AZARAC_PROGMEM` は 64KiB 超のデバイスで `.text.azaraC.<N>` へ行き far アクセサが要るので使わない）を付け、読み出しを `AZARAC_PGM_READ_DWORD` / `AZARAC_PGM_READ_BYTE` に変えた（非AVR では通常のロードで、同じ経路がホストテストと `pgm-stub` で実行検証される）。B4 の表は行（13B）を byte 単位で読むため、`static_assert` でパディング無しを固定した。名前を `_TABLE` で終わらせているのは `autoresearch.sh` の「定義テーブルが RAM に落ちていない」ゲート（`AVR_TABLES_IN_RAM` / `MEGA_TABLES_IN_RAM`）に載せるため — 従来この2表は `_POOL`/`_TABLE` で終わらない名前だったのでゲートを素通りしていた。あわせてハーネスは near-Flash 表（CRC24Q の 3×16B、半径表、B4 レイアウト表）の最高アドレスを `avr-nm` で採取し、64KiB の16bit窓内にあることをゲートする（`MEGA_NEAR_SYM_ADDR`。1つでも窓の外へ出ると `pgm_read_*` が黙ってゴミを返し、CRC 不一致で全フレームが落ちる）。`UNO_RAM_BYTES` / `MEGA_RAM_BYTES` の上限は新しい実測値（146B / 896B）へ下げた。同じ理由で、`json/JsonWriter.cpp` の16進表（`HEX_CHARS` 17B）は Flash へ移さず**表をやめて三項演算**（`n < 10 ? '0' + n : 'A' + n - 10`）にした: 16エントリの表は畳まれないビルドでは `.data` を食い、畳まれるビルドでも Flash に 17B 残るうえ、`pgm_read_byte` にすると最適化が効かなくなる。実測（ATmega328P + `-flto`、Uno 実リンク、stage 4 と同じレシピ）: 表を Flash へ置いた場合 13,982B に対し **13,546B**（＝表を畳んでいた元の実装と同値）。出力バイト列は不変。

- **コメントを整理**: `src/`・`test/`・`examples/`・`scripts/`・CI のコメントから、コードの復唱・作業経緯・重複した説明を削った。途中で折り返していた行は 1 行にまとめ、長い場合は句点で改行する（文の途中では折り返さない）。仕様参照・ビット配置・契約・実測値とその結論は短くして残した。生成ヘッダのコメントは手で直さず `scripts/gen/gen_definitions.py` のテンプレートを 7 行 → 3 行に縮めて `src/definition/*.h`（138 ファイル）を再生成した（azarashi 0.17.1 で再現）。コード・文字列リテラルは不変で、ホストテスト 414 件 / 10,471 アサーションが通る。
- **`Parser` のコピー・ムーブを禁止（破壊的変更）**: `Parser` は 4KB の dedup テーブルと南海トラフのページバッファを実体で持ち、`_custom` は呼び出し側が所有する framer を指す。複製は SRAM を二重に消費し framer も二重所有になるため、コピー/ムーブのコンストラクタと代入演算子を `= delete` にした（`Parser p2 = p;`、値渡し、コンテナへの格納はいずれもコンパイルエラー）。あわせて `feed()` の復号先を局所 `Message` から呼び出し側の `out` に変え、1 フレームあたり `Message`（288B）1個ぶんのスタックとコピーを削った（worst-case スタック: host `-Os` 1,112B → 808B、AVR プリセット `-Os` 414B → 259B。`-fstack-usage` の call graph 合計）。
- **CRC-24Q を 4bit 表（ニブル表）に置き換えた**: ビットごとの `crc <<= 1` ループを、host は 32bit の `constexpr` 表、AVR は 3 分割した PROGMEM のバイト表（3×16B）＋ 3 バイトで持つ 24bit レジスタで、4bit 単位に書き換えた（AVR で 32bit シフトが LSR/ROR の回転ループに展開されるのを避け、ループ回数を従来の 1/4 にするのが狙い）。`bit_len & 3` の端数は表の対象外なのでビット直列のまま処理する。旧実装との等価性は 4,000 ケース（ビット長 0〜256 の乱数）でビット直列の参照実装と一致（不一致 0）することを確認した。AVR のフラッシュは `crc24q` のコード 142B ＋ 表 48B の **+190B**（実測: Uno 17,936B → 18,126B、ATmega2560 145,802B → 145,992B。avr-gcc `-Os`、差はどちらの構成でも同じ。デコード結果と SRAM は不変）。
- **DCX の角度・半径の出力を整数演算にした**: `main_ellipse`・B1 補正（`c1_lat_offset_deg` など）・`hazard_center` の `delta_*`・`additional_area.ellipse` の lat/lon・semi-axes・azimuth・delta を、`double` を経由する `wf_d` から新しい `wf_deg` に置き換えた。AVR の `double` は 24bit 仮数（約 7.2 桁）で、6 桁精度の角度は host と下位桁が一致しない（同じ電文でもボードによって JSON が変わる）。値が 10 の累乗を分母とする整数（マイクロ度・ミリ度）であることを使い、商と余りだけで組み立てる（小数部は分母の桁数ぶんゼロ埋め）ので float/double を一切通らない。出力バイト列は、従来の `wf_d` と 60,026 ケース（分母 10⁶ / 10³、負値と小数点以下の桁を含む乱数）で一致（不一致 0）することを確認した。あわせて `JsonWriter::writeEscaped` に、エスケープが不要な文字列（キーとほぼ全てのラベル）を 1 回の `write()` で出す fast path を追加した。
- **AVR向けに定義テーブルのフラッシュ消費を削減（issue #35）**: 生成表は地域名の親（都道府県・市区町村）を1件ごとに繰り返していた（英語の地域コード表だけで63,064B）。`strategy.py` の `factor_parents` が、同じ表の中で4件以上に共通する最長の接頭辞／接尾辞（`北海道札幌市` の `北海道`、`Sapporo City, Hokkaido Prefecture` の ` City, Hokkaido Prefecture`）を「親」として切り出し、`<GUARD>_PARENT_POOL` に1回だけ置いて、行には親の添字（`0xFF`＝親なし）を持たせ、参照時に `azarac_pgm_join_z` が既存の共有RAMバッファ内で連結する。切り出した親自身も同じ規則で再帰的に切り出せる（2段目。` City, Hokkaido Prefecture` → ` City, ` ＋ `Hokkaido Prefecture`）。binary_search / array 戦略の全表が対象。switch 戦略は行を持たないため、共有断片のオフセットを case 本体に定数として埋め込む。あわせて行から `len` を削除した（プールはNUL区切りなので長さは `azarac_pgm_len` が取る）。
  - 2段目は呼び出し側に分岐と `azarac_pgm_join3` を足すため、表の削減がそのコード（実測60〜130B/呼び出し）を上回る表だけ採用する（閾値 128B）。閾値が無いと既定AVR構成のリンクが122B増えることを実測で確認した。
  - 行の増分は「親を持つ行は常に1B増える」で見積る — AVRの行形（`{id, parent, offset}` / `{offset, parent}`）に長さフィールドは無く、親バイトを相殺できるものがない（AVR-GCCは行構造体にバイト整列を与える）。旧見積りは「子が255Bを超えるときだけ増える」としていたので、子が短い表では親バイトを無料と数えていた。そのため圧縮が得に見えていた5表（EEW予報区 JA/EN・都道府県・火山名・CAMF A2国地域名）が圧縮をやめ、合計 −289B になった。
  - **非AVR（ホスト）側の出力は従来どおり非圧縮**（issue #35 の方針）。ラベルは全1,409,708照会でAVR経路・ホスト経路ともバイト単位一致（`test/bench/avr/labels.golden`。断片の結合順をわざと入れ替えるとこのゲートが落ちることも確認済み）。
  - 実測（全カテゴリ + 日英、`test/bench/avr/measure_tables.py`）: 474,484B → 300,827B（−36.6%）。最大の単一リテラルが 63,064B → 20,944B になり、avr-gcc の1オブジェクト上限 32,767B を下回ったため、**ATmega2560 で DCX/CAMF・火山・降灰の各カテゴリがビルド可能になった**（従来は `size of variable is too large` でコンパイル不可）。実際に ATmega2560 向けに DCX/CAMF + SEISMIC/TSUNAMI を**日英**（`AZARAC_LANG_JA=1` / `AZARAC_LANG_EN=1`）でリンクすると、フラッシュ 184,998B（上限 262,144B）・RAM 3,970B（上限 8,192B）に収まり、DCX/CAMF の定義テーブル 100 シンボルがすべてFlash側に置かれることを `avr-nm` で確認した（2026-10 実測。`autoresearch.sh` stage 5 と同じリンク条件。日本語のみの構成は 144,804B / 3,714B で、下記「AVR向けプリセット…」の値と同一。日英と日本語のみは言語構成が違うだけの別測定）。定義テーブルは各プールが64KiB未満に収まるため、16bitのFlashオフセットで扱える範囲も広がった。
  - **SRAMは不変**: Uno実リンクで data+bss = 702B（変更前と同じ。この改修時点のベースラインで、JSON キーと補助テーブルの Flash 移行後は 204B）、表がRAMに落ちていないことを `AVR_TABLES_IN_RAM=0` で確認。結合は `internal/FlashString.h` の共有バッファ（800B、既存）内で行う。既定AVRプリセット（SEISMIC/TSUNAMI、JA）は表+プール 3,011B・リンク後フラッシュ 17,930B → 17,656B。
- **ATmega2560 など Flash が 64KiB を超える AVR で定義テーブルを正しく参照できるようにした**: テーブル（DCX/CAMF を含む構成では ~140KB）はリンク時に 0xFFFF より上へ配置され、16bit の PROGMEM ポインタでは届かない（実測: 195 シンボル中 138 個が 64KiB 超。従来のコードは `lpm` のみで `RAMPZ` を一切使わなかった）。`internal/FlashString.h` がデバイスに応じてアドレス方式を切り替え、`FLASHEND > 0xFFFF` では配列のアドレスを `pgm_get_far_address`（`AZARAC_PGM_PTR`）で取り、読み出しを `pgm_read_*_far` / `memcpy_PF` / `strncpy_PF` で行う（64KiB 以下は従来どおり16bitポインタのまま）。プール内のオフセットは16bitのままで、行の形（`{id, parent, offset}`）も不変。`make -C test pgm-stub` は 64KiB 超のデバイスを装う（`FLASHEND=0x3FFFF`）ので far 経路はホストで実行検証され、ラベルは全 1,409,708 照会でホスト経路と一致する。
- **AVR 向けプリセットはチップ名でカテゴリを切り替えなくなった（破壊的変更: Mega の DCX/CAMF はオプトイン）**: これまで Flash の大きいボード（`AZARAC_AVR_LARGE_FLASH`: `ARDUINO_AVR_MEGA2560` / `__AVR_ATmega2560__` / `__AVR_ATmega2561__`）では DCX/CAMF も自動で有効にしていたが、既定は全 AVR で 0（SEISMIC/TSUNAMI のみ、Uno と同じ）にした。DCX/CAMF は `-DAZARAC_AVR_LARGE_FLASH=1`（従来の名前。明示していた既存コードはそのまま動く）または `-DAZARAC_ENABLE_DCX_CAMF=1` を渡した時だけ有効になり、Flash 145KB を使う構成は自分で選ぶことになる。ATmega2560 + DCX/CAMF + SEISMIC/TSUNAMI を**日本語のみ**（`AZARAC_LANG_EN=0`、AVRの既定）でリンクした実測は**フラッシュ 144,804B（上限 262,144B）・RAM 3,714B（上限 8,192B）**で、DCX の定義テーブル 90 シンボルは全て Flash 側（RAM 0。日英構成は 184,998B / 3,970B — 上記「フラッシュ消費を削減」の項）。`AZARAC_FLASH_BUF_SIZE` の自動選択はカテゴリ既定の解決後に評価されるので、`-DAZARAC_ENABLE_DCX_CAMF=1` でも 800B になる。他10カテゴリは大容量ボードでも無効のまま（全て同時にすると 250,138B/262,144B でユーザーコードの余地が 12KB しかない）。
- **JSON から `double` を排除（`wf_d` / `writeDouble` を削除）**: 津波の高さの境界（`height_lower` / `height_upper`）を 10 分の 1 m の整数と `wf_deg`（分母 10）に置き換えた。出力文字列は従来と同一（`0.2` / `1.0` / `3.0` / `5.0` / `10.0`、境界なしは `null`）。従来の `writeDouble` は非有限値を `null` にするガードを `v > 1e308` で書いていたが、AVR の `double` は 32bit なのでこの定数は範囲外（`inf`）になり、NaN しか検出できず `-Woverflow` も出ていた（host と AVR で挙動が違う）。利用者が高さの 2 箇所だけだったため関数ごと削除し、これで JSON 経路に float/double が 1 つも残らない。実測（`--gc-sections` のリンク後）: Uno 18,126B → **16,874B**・RAM 702B → **654B**、ATmega2560 プリセット 145,992B → **144,804B**・RAM 3,762B → **3,714B**（`test/bench/avr`）。`writeDouble` の単体テスト 9 件は対象関数の削除に伴い削除し、代わりに高さコード 1〜6 と 508 の全区分を 1 通ずつ組む JSON テストを追加した。
- **AVR ビルドで範囲外の浮動小数点定数をエラー化（`-Werror=overflow`）**: `autoresearch.sh` の AVR ビルド 3 箇所（全カテゴリ・Uno プリセット・Mega プリセット）に追加した。AVR の `double` は 32bit なので、host では有効な定数（`1e308` など）が AVR では `inf` になり、比較が黙って成立しなくなる。追加時点でこれに該当したのは `src/json/JsonWriter.cpp` の 1 箇所のみで、他の 11 TU は緑だった。
- **AVR ベンチの Uno 実リンクを LTO にした**: Arduino AVR コアは `-flto -fuse-linker-plugin` でコンパイル/リンクするので、同フラグを Uno ステージ（`AVR_LTO`）にも入れ、実測が実機どおりになるようにした。Uno: フラッシュ 16,874B → 13,546B、RAM 654B → 640B。**Mega（DCX/CAMF）ステージには入れていない** — avr-gcc 7.3 + LTO では生成ヘッダの関数ローカルなリテラル静的変数から `.text.azaraC.<n>` 属性が落ち、`.rodata`（＝リンカスクリプト上 `.data`、実体は SRAM）へ移動する。同一レシピの実測で `.data` 2,902B → 28,230B（Mega の SRAM は 8,192B）で、far-Flash 配置の検証が成立しないため。Mega の SRAM も `MAX_MEGA_RAM_BYTES`（3,714B）でゲートするようにした。（その後、生成器側の修正で関数ローカルのリテラルは LTO でも Flash に残るようになったので、`autoresearch.sh` はステージ 5b として同じ Mega 構成を LTO でも組み、`MEGA_LTO_FLASH_BYTES` / `MEGA_LTO_RAM_BYTES` として報告する。ゲートにはせず、LTO 無しとの差が 64B を超えたときだけ報告する。測定のためリンク時のみ `--defsym=__DATA_REGION_LENGTH__=0x8000` でデータ領域を広げる。修正後の実測: LTO 無し 3,714B に対し 3,718B。詳細は下記「switch 戦略のラベルが LTO で SRAM へ落ち」の項。）
- **Arduino Mega 2560 のコンパイルを必須ジョブに昇格**: `arduino-compile-required` に Mega（`arduino:avr:mega`）を加え、`arduino-compile-extended` から外した（WiFi/SNTP 例は AVR では `WiFi.h` が無いので従来どおりスキップ）。これで AVR は Uno（`basic_*` 3 例）と Mega（WiFi/RTOS 以外の全例）が既定カテゴリで必須になる。
- **リリースワークフローの `run:` から式の直接展開を外した**: `release.yml` の `slsa-verifier` ステップで provenance の成果物名を `${{ ... }}` として直接埋めていたのを、他ステップと同じく `env: PROVENANCE` 経由の参照（`"$PROVENANCE"`）に統一した。

### Added

- **定義テーブルのAVRフットプリント計測ハーネス**（`make -C test bench`、`autoresearch.sh` + `test/bench/avr/`）: `avr-gcc -E` の出力からプールと行のバイト数を数え（`AVR_TABLE_BYTES`）、avr-gcc 自身のオブジェクトサイズと突合する（`AVR_TABLE_CROSSCHECK`）。ゲートは7つ——全1,409,708照会のラベル一致（AVR far / AVR 16bit / ホストの3経路）、ATmega2560での全カテゴリのコンパイル（プールが上限を下回っているときのみ）、既定AVR構成のリンク、SRAM非増加（`UNO_RAM_BYTES` ≤ 146B、`MEGA_RAM_BYTES` ≤ 896B、`AVR_TABLES_IN_RAM` = 0）、**コア側PROGMEMが16bit窓（64KiB）内に残ること**（`test/bench/avr/core_progmem.c` を最後にリンクして `MEGA_CORE_PGM_ADDR` ≤ 0xFFFF）、**共有ラベルバッファが有効カテゴリの最長ラベルを収めること**（`test/bench/avr/check_flash_buf.py`、`FLASH_BUF_OK`。全カテゴリ組み合わせ×両言語×両プリセットを掃き、`AZARAC_FLASH_BUF_SIZE` の選択連鎖を avr-gcc の前処理結果と突合する）、そして**azaraC 自身の CRC24Q 表が16bit窓（64KiB）内に残ること**（`src/decoder/Decoder.cpp` の表を `avr-nm` で採取して `MEGA_NEAR_SYM_ADDR` ≤ 0xFFFF。表が消えた・別の節へ移った場合も失敗させる）。`bash autoresearch.sh --bless-labels` はラベル基準値の再記録用。
- **dedup ベンチを CI に戻した**（`make -C test bench-dedup`、`test/bench/run_dedup_bench.sh`）: AVR テーブル計測ハーネスが `autoresearch.sh` を置き換えた際に、旧 `make -C test bench` が回していた dedup のゲート（`NEW_RECALL` / `DUP_SUPPRESS` / `NANKAI_KEY_STABLE` / `PREAMBLE_KEY_STABLE`）と `test/bench/bench_dedup.cpp` をビルドする経路が CI から落ちていた（`bench` はフットプリント計測のまま）。旧ハーネスを `test/bench/run_dedup_bench.sh` として復帰させ、`bench-dedup` ターゲットと host-test ジョブのステップを追加した。入力は `test/data/*.json` のみ、host の g++ だけで動く。実測: `NEW_CORRECT=118` / `DUP_SUPPRESS=1.0000` / `NANKAI_KEY_STABLE=1` / `PREAMBLE_KEY_STABLE=1` で exit 0。

### Fixed

- **NMEA `$QZQSM` の Satellite ID を仕様どおり2桁に限定した**: 仕様の Satellite ID は PRN 下位 6bit の2桁10進（IS-QZSS-DCR-017 §4.3.1 / DCX-004 §4.3.1、Table 4.3.1-1）で、azarashi も長さ 2 以外を拒否する。azaraC は任意桁数を受けていたため、3桁（例 `$QZQSM,100,…`）を通すと `| 0x80` の結果が PRN 契約（181-191）の外の値（228）になり、`Frame::svid` に PRN でない値が載っていた。桁数を数えて 2 以外を拒否するようにした。あわせてテストヘルパ `makeNmeaQzqsm` が PRN（183-191）をそのまま3桁で書いていたのを、電文どおり下位 6bit の2桁に落として書くよう直した（PRN 184 → `56` → 受信側で 184 に戻る）。3桁を受けることを前提にしていた `UBX: SFRBX sv56 pattern1 - Marine` の往復テストはこれで仕様どおりの電文になった。
- **AVR で A6/A7 のオンセット時刻が a7=1094 以上で誤っていた（16bit 幅の静かな折り返し）**: `decodeDcx` は `(d->camf.a7 - 1u) * 60u` を `uint32_t onset_unix` へ足していたが、a7 は `uint16_t` で AVR の `unsigned int` は 16bit のため、この乗算は 16bit で行われ `a7 > 1093` から 65,535 を超えて折り返していた（a7 の範囲は 1..10080。a7=10080 なら 604,740 秒が 14,916 秒 = 週内の別の時刻になる）。`onsetOffsetSec()`（`static_cast<uint32_t>` で 32bit に広げる）に切り出し、同じ式が 16bit に戻ったら **AVR ビルドが `static_assert` で落ちる**ようにした（ホストの `int` は 32bit なので、この欠陥はホストテストでは決して現れない）。境界の意味（a7=1094 と上限 10080 = 翌週の日曜 23:59）は `test/integration/test_time_resolution.cpp` で固定した。
- **ドキュメントとコードの食い違いを修正**: `feed()` の戻り値（完成・成功・非重複の3条件、重複時は `out` をクリア）と `unsupported_reason`、`event_time` のビット範囲（`[21..40]`）、`version` とカテゴリ別の getter（`getEew()` 等。`EewData eew` のような公開メンバは無い）を API リファレンスに合わせた。`_label_en` が付く条件（固定リテラルキーの `AZARAC_LABEL` のみ）、降灰の `arrival_time_label`、`ex_vn` の位置（J-Alert は `jalert_target.ex_vn`）、`unsupported_msg_type` / `unsupported_category` の条件も JSON 仕様に合わせた。テスト件数（414 / 10,471）、`AZARAC_FLASH_BUF_SIZE` の既定（AVR 既定 64、非AVR では未使用）、avr_std シムの一覧、NankaiPageBuffer のサイズ（ホスト 1,168B / AVR 1,161B）、L1S 規格の原本がリポジトリに無い旨も直した。`platformio.ini.example` の Registry ピンは `^2.0.0`（Registry の公開版）に更新し、install 手順・AVR のオプトイン・`#define` ではなくビルドフラグで指定する点を README / getting-started に追記した。examples の `error_handling` / `with_sntp` の説明と出力例を実装に合わせた。
- **AVR で `AZARAC_FLASH_BUF_SIZE` の自動選択が一部カテゴリのラベルを黙って切り詰めていた**: バッファ長は有効カテゴリから選ぶが（`src/azaraC_config.h`）、ラベルは独立したガード（`src/definition/*.h`）で有効になる。選択連鎖が知っていたのは DCX/CAMF（800）・南海トラフ（540）・北西太平洋津波（80）だけで、**緊急地震速報・震源（最長 596B、`notification_on_disaster_prevention`）・火山（88B）・洪水（78B）**は 64B に落ちていた。`azarac_pgm_view` は `AZARAC_FLASH_BUF_SIZE - 1` で切り詰めるため（しかも UTF-8 の途中で切れる）、`-DAZARAC_ENABLE_EEW=1` のような設定では 596B のラベルが 63B になって返っていた（実測: 63B → 修正後 596B）。連鎖に 640（EEW/震源）と 96（火山/洪水）の段を足し、`make -C test bench` に全カテゴリ組み合わせのゲートを追加した（`FLASH_BUF_OK`。既定プリセットの Uno/Mega は値・RAM とも不変）。Uno（`ARDUINO_AVR_UNO`）で 256B を超える構成には `#warning` を出す（プリセットは 64B なので、長いラベルを持つカテゴリを有効にした場合だけ発火する。既存の `AZARAC_NANKAI_BUFFERS` 警告と同じ扱い）。
- **ラベル長ゲート（`check_flash_buf.py`）がフレーム内の OR を AND として読んでいた**: 生成ヘッダのガードは `(AZARAC_ENABLE_VOLCANO || AZARAC_ENABLE_ASH_FALL) && (AZARAC_LANG_JA)` のようにフレーム内が OR・フレーム間が AND だが、スキャナは開いているフレームのカテゴリを1つの集合に統合し、`needed` がその全要素の有効を要求していた。片方だけ有効な構成（`-DAZARAC_ENABLE_VOLCANO=1`）が選ぶ表を検査対象から落としていた（実測: 12,288構成中3,136構成で要求長を過小評価。`VOLCANO` のみの構成で 47B → 58B）。フレームごとに OR 集合を保って判定するようにし、最小余裕 3B（Uno・`ASH_FALL`＋英語）で全構成が収まることを確認した。現時点で実際に切り詰められる構成は無く、ゲートの見逃し余地を塞ぐ修正。
- **switch 戦略のラベルが LTO で SRAM へ落ち、Mega の DCX/CAMF 構成が実機でビルドできなかった**: 生成ヘッダは switch の各 case に `static const char s[] AZARAC_PROGMEM = "..."` を関数内に置いていた。Arduino AVR コアは `-flto` でビルドするので、inline 関数内の static（one-only）では `__section__` が落ちて `.rodata` へ移り、avr-libc のスクリプトがそれを `.data`（SRAM）に置く（最小再現: 同じ属性の配列が、名前空間スコープなら LTO 有無どちらでも Flash、inline 関数内なら LTO 有りのときだけ RAM。節名を固定しても変わらないので、名前ではなく one-only の扱いの問題）。実機実測（arduino-cli 1.5.2 + arduino:avr 1.8.8 + atmel 7.3.0、ATmega2560 + `-DAZARAC_AVR_LARGE_FLASH=1`、`examples/basic_nmea`）: RAM 30,236B（上限 8,192B）で `data section exceeds available space in board`、DCX 無しの既定構成は 2,004B で通っていた。`scripts/gen/gen_definitions.py` の `switch_labels()` が case リテラルをテーブルごとの名前空間スコープ配列（`<GUARD>_C<key>[]`）として出すようにし、宣言ごとの節（`__COUNTER__`）と `--gc-sections` の粒度はそのまま保つ。同じ実機構成で RAM 30,236B → **4,908B**、フラッシュは 143,432B で不変、far 参照（elpm/RAMPZ）も不変。定義ヘッダは再生成済み（生成器の出力は冪等）。ベンチの LTO 画像も 29,042B → 3,718B（LTO 無し 3,714B）になり、`autoresearch.sh` は LTO 画像と LTO 無し画像の差が 64B を超えたときに報告する（ゲートにはしない）。ラベルは 1,409,708 照会で不変（`labels.golden`）、`AVR_TABLE_BYTES` 300,827B・既定 AVR 構成・Uno も不変。
- **64KiB 超の AVR で、定義テーブルが Arduino コア自身の PROGMEM を16bit窓の外へ押し出していた**: avr-libc のリンカスクリプトは progmem クラスタ（`*(.progmem.gcc*)` / `*(.progmem*)`）を `.text` の先頭にリンク順で並べ、Arduino は `core.a` を最後にリンクする。`FLASHEND > 0xFFFF` のデバイスで116KiBの定義テーブルがそこに置かれると、コアの `digital_pin_to_port_PGM` などが64KiB以上へ移動し、16bitの `pgm_read_byte(&table[pin])` が届かなくなる（`pinMode`/`digitalWrite` が誤ったポートを読む。実測: コア模擬PROGMEMが 0x19F46、すなわちテーブルの直後）。`AZARAC_PROGMEM` を `.text.azaraC.<n>`（`*(.text.*)` クラスタ。progmem クラスタより後ろ）へ移した（宣言ごとに `__COUNTER__` で節名を分け、`-fdata-sections` と同じ `--gc-sections` 粒度を保つ。1節にまとめると、そのTUの1表が参照されただけで節全体が残り、関数内の静的リテラル（one-only/weak）は通常の配列と同居もできない）。`.progmemx.*` は使わない — そのクラスタは binutils 2.29 以降（PR 21849）のスクリプトにしか無く、atmel 2.26（Ubuntu の `binutils-avr` も Arduino 同梱のツールチェーンもこれ）では広い `*(.progmem*)` に取り込まれて同じ失敗に戻る（実測 0x19F46）。64KiB以下のデバイスは従来どおり `PROGMEM`。実測（ATmega2560 + DCX/CAMF + SEISMIC/TSUNAMI）: コア模擬PROGMEMのアドレス **0x19F46 → 0x0368**（binutils 2.30 のスクリプトでも 2.26 形でも同じ値）、RAM 3,714B は**不変**、フラッシュは節の整列で +2B（144,804B → 144,806B。Uno は 16,874B / 654B）。`autoresearch.sh` がコア模擬オブジェクト（`test/bench/avr/core_progmem.c`）を最後にリンクしてこのアドレスをゲートする。
- **`gen_definitions.py` の書き込みが一過性のOSErrorで落ちると、生成が途中で止まったまま古いヘッダが残る**: ファイルスキャナが新規ファイルを一時的に掴むWindowsで `OSError(EINVAL)` が出るため、5回まで再試行する（`write_file`）。CI（Linux）では発生しない。

## [2.0.0] - 2026-10-13

### Changed (破壊的変更 — JSON v2)

- **`JsonSerializer` の出力を v2 に改訂（v1 と非互換）**: ルートに `schema_version: 2` を追加し、曖昧だった 4 点を明示化した。互換エイリアスは設けない（読み手は `schema_version` で分岐する）。`docs/json-formats.md` を v2 仕様として書き直した。
  - **本文を `data` に統一**: MT43 は `detail` → `data`、MT44 はルート直下に散っていた A フィールド・拡張部・`sd_sdmt`/`sd_sdm` を `data` の下へ移動した。MT43 の報告ヘッダ（`report_classification` / `disaster_category` / `information_type` / `version` / `report_time`）はルートに残る。MT44 のルートは `schema_version` / `svid` / `msg_type` / `crc24` / `data` の 5 キーだけになる。
  - **ラベルを 3 値に**: `_label` は「表に該当なし（未定義・範囲外・表なし）→ `null`」「定義済みだが空文字列 → `""`」「ラベルあり → 文字列」の 3 値。v1 は未定義と定義済み空が同じ `""` に潰れていた。キーは従来どおり常に出力する。
  - **時刻の `unix` を `null` で未解決表示**: `unix_time == 0` は `"unix": 0`（1970-01-01 と区別できない）ではなく `"unix": null`。`month`/`day`/`hour`/`min` は v1 のまま。
  - **津波の到着時刻の状態を明示**: cat 5/6 の `arrival_day_offset` / `arrival_hour` / `arrival_min` を削除し、`arrival_time_raw`（12bit の生値）＋解決できたときだけ `arrival_time`（できなければ `"arrival_time":null`）、加えて `arrival_status`（`arrival_estimated` / `arrived_or_unknown` / `no_information` / `unrecognized_code`）にした。v1 は `31:63`（到達中と推測）・`30:62`（該当情報なし）・不正値が同じ全ゼロ時刻に潰れていた。判定順は azarashi と同じで、範囲外チェックを先に置くと `30:62` の `no_information` が到達不能になる。
  - **重複キーの削除**: `svid_label` / `msg_type_label`（`msg_type` から一意）、`alert_identity{a2,a3,a4,ex1}`（`a2_country` 等と同値。`Mt44AlertIdentity` 構造体ごと削除）、`detailed_info.a4_code`（`a4_hazard` と同値）、`jalert_target.prefecture_mode`（`prefectures`/`cities` の有無で決まる）。
  - **並列配列の解消**: `jalert_target` の `prefecture_positions[]` + `prefecture_labels[]` を `prefectures[{position,label}]` に、`city_codes[]` + `city_labels[]` を `cities[{code,label}]` に統合した。`position` は JIS 都道府県コード（1–47、1 始まり）で v1 の値を維持する。
  - **D フィールドの平坦化**: B4 の `"dX": {"raw": N, "label": L}` を `"dX": N` + `"dX_label": L` にした（`JsonWriter` の `wf_v`）。D レイアウトを持たない a4 では `detailed_info` が空オブジェクトになる（B4 が存在した事実は残る）。
  - **`dcx_type` を数値から文字列へ**: `"dcx_type": 1` + `"dcx_type_label": "L_ALERT"` → `"dcx_type": "L_ALERT"`。値は `Mt44ServiceKind` と同じ 6 種（`NULL` / `L_ALERT` / `J_ALERT` / `LOCAL_GOV` / `OUTSIDE_JAPAN` / `UNKNOWN`）。
  - **降灰の `arrival_hour` を改名**: これは時刻ではなく 3bit の「予想降灰時刻」コードなので `arrival_time_code` + `arrival_time_label` にした（未使用だった `qzss_dcr_jma_expected_ash_fall_time{,_en}` を `AZARAC_LABEL` 経由で引く）。
  - **実測サイズ**（同一 236 電文、コンパクト表現）: 254,196 B / 平均 1,077 B（v1 は 259,450 B / 1,099 B。同一コミットの worktree を再ビルドし同じ計量関数で測定）。MT44 の単体レコードは `prefectures` のオブジェクト配列化により最大 +859 B、MT43 は降灰（cat 9）で `arrival_hour` が `arrival_time_code` + `arrival_time_label`(+`_label_en`) になった分で最大 +242 B 増える（`detail` → `data` はルート直下の同レベル改名なので深さ・バイト数に影響しない）。総量は `dcx_type` の重複や `alert_identity` / `a4_code` / 分解済み到着時刻の削除で減る（MT44 合計 −3,734 B / MT43 合計 −1,520 B）。
- **`writeOptStr` が `nullopt` を `null` として描画**: 従来は `nullopt` と `optional("")` をどちらも `""` にしていたため、JSON 層で「表に該当なし」と「定義済みの空ラベル」を区別できなかった。

### Added

- **動的確保ゼロ検証 `make -C test test-no-alloc`**: 公開 API（`Parser::feed` / `toJson`）が `malloc`/`calloc`/`realloc`/`posix_memalign` と `operator new`/`new[]` を呼ばないことを、GNU ld の `--wrap` で差し替えた生カウンタで直接検証する（`test/integration/test_no_alloc.cpp`）。MT43（緊急地震速報）・MT44（国外 CAMF）・UBX-RXM-SFRBX（海上警報）・南海トラフ 27 ページ集約の 4 経路で確保 0 を assert する。`--wrap` は未解決参照のみ差し替えるため別バイナリ・別オブジェクトディレクトリ（`.noalloc/`）でリンクし、実行後に `clean` する。macOS の ld64 は `--wrap` を持たないためスキップする。
- **`macro-size-check` の失敗が CI を赤にする**: `Measure macro size impact` ステップで `set -o pipefail` + 終了コード捕捉を追加した。従来は `make ... | tee` の `tee` の 0 が採用され、`test-macro-sizes` が落ちても緑になっていた。
- **数量フィールドに `_label` を追加**: `depth` / `magnitude` / `pressure` / `max_wind` / `max_gust` / `elapsed` / `number` は境界（`depth` 501 = 500km より深い、`magnitude` 101 = 10.0 より大きい）とセンチネル（`depth` 511 / `magnitude` 127 / `max_wind` 0 / `max_gust` 0 = 不明）を含むコード値で、生の値からは意味が取れなかった。`JsonWriter.h` に `AZARAC_LABEL` を追加し、既存 28 箇所のラベル出力を集約したうえで、これら 7 フィールドに `_label` を付与した。センチネルは全フィールド共通ではなく、`depth` 0 は `0km`、`pressure` 0 は `0hPa`、`elapsed` 0 は `0時間後` で実値。表に無いコードは azaraC も azarashi もラベルを出さない（azarashi は `recognized: false`、`labels: {}`）。`CodeTable.__getitem__` は未知コードに `台風番号(コード番号：N)` を合成するが、JSON 経路の `_coded()` は `value in table` でガードしてから引くためその文字列は使われない。`number` 0（`typhoon_number` は `BASE=1`）は両者とも空のまま。
- **津波の高さの境界を出力（`height_lower` / `height_upper`）**: 津波の高さコードは単一値ではなく範囲で、仕様の `3m` は「1m 超〜3m 以下」（cat 6 は `3m~5m` のように `height_label` 自体が範囲だが、cat 5 のラベルは上端 `3m` しか出さず範囲は読めなかった）。cat 5/6 の `entries[]` に境界（m、下端は開・上端は閉）を 2 キーで追加した。区分は azarashi 0.17.1 の `PROFILES["qzss.dcr.tsunami_height"]` / `PROFILES["qzss.dcr.northwest_pacific_tsunami_height"]` と同じ。境界を持たないコード（`該当情報なし` / `不明` / `その他` / `Huge` / `High` / `Unknown`）と、片側だけ無い区分（`0.2m未満` の下端、`10m超` の上端）は `null`。生コード `height` と `height_label` は従来どおり残る。実測 +36〜41 B/entry（テストベクタ 228 通で +266 B）。
- **両言語併記 `_label_en`**: `AZARAC_LANG_JA=1` かつ `AZARAC_LANG_EN=1` のとき、文字列リテラルのキーを持つ `_label` に `_label_en`（英語）を併記する。`_label` は従来どおり日本語優先。`AZARAC_LANG_EN=0`（ライブラリ既定）と `AZARAC_LANG_JA=0 / AZARAC_LANG_EN=1` では `_label_en` を出さないため、既定構成の出力は本変更前と同一（詳細は `docs/api-reference.md`）。
- **火山の `ambiguity` に `_label` を追加**: `Du`（活動時刻の曖昧さ、3bit、0–7）は生の数値だけでは「どの粒度で時刻が有効か」が読めなかった。`ambiguity_of_activity_time_en` 表は日本語版を持たない英語専用表のため、北西太平洋津波の `potential_label` と同じく言語非依存で常に出力される（`_label_en` は出ない）。
- **`version`（DCR の `Vn`）を出力**: 6bit at `[214..219]`。`DecoderQzqsm` は `Vn != 1` を `UnsupportedVersion` として拒否していたが値を捨てていたため、`Mt43Data::version` に保持して最上位に `"version"` として出す。デコード成功時は常に 1 になるが、「フィールドが無い」と「Vn=1 を読んだ」を区別できる。
- **英語索引のテストを追加**: `test/internal/test_definition_labels.cpp` に、azarashi 0.17 が追加した `_en` 表を 3 戦略すべてで引く検証を追加した。array（`BASE` / `BASE+SIZE-1` / 範囲外、隣接行の入れ替え検出）、疎キー（歯抜けの前後と欠落）、switch（`nullopt` になるコードと、0 が「未定義」ではなく「解除/発表」であること）を、実ヘッダから実測した期待値で固定する。あわせて JA 表と EN 表が同じコード集合を引くこと（片方だけにコードがあると、言語を切り替えただけでラベルが消える）を全数検査する。
- **英語ラベルを全面有効化**: azarashi 0.17.0 が 37 表に英語版を追加したため、定義ヘッダを再生成し、シリアライザの全ラベル参照を `AZARAC_LOOKUP_LANG` 経由にした。`AZARAC_LANG_JA=0 / AZARAC_LANG_EN=1` の構成で、従来は日本語のままだった 39 ラベルが英語になる（`JSON Serialization: MT=43 Tsunami` の `height_label` は `5m` → `5 m`）。英語表を持たない項目（南海トラフの情報番号など）は日本語のままになる。

- **`make -C test dedup-realday`（実日の再現計測）を追加**: `realdata/*.l1s` を走査し、Decoder が受理したフレーム・同一性の distinct・生存ピーク（カテゴリ別窓／一律24時間）・`DedupFilter` の偽再通知／取りこぼしを METRIC 行で出す（`test/tools/dedup_realday.cpp`）。窓・ハッシュ・カテゴリ判定はライブラリ本体（`Decoder::decode` / `internal::dedupWindowMs` / `internal::DedupFilter`）をそのまま呼ぶため、本体から静かにずれない。`realdata/` は gitignore 対象なので入力が無ければ `SKIP` を出す。
- **ベンチに `PREAMBLE_KEY_STABLE` を追加し、識別鍵の指標をゲート化**: 同一の MT～VN を 3 つのプリアンブル（0x53/0x9A/0xC6）で再放送しても通知がちょうど 1 回になることを、実データのコーパス（226 distinct）の 1 文から行動的に測る（`test/bench/bench_dedup.cpp`、`NANKAI_KEY_STABLE` と同じ形）。あわせて `autoresearch.sh` で `NANKAI_KEY_STABLE` と `PREAMBLE_KEY_STABLE` を実際のゲートにした（`NEW_RECALL` / `DUP_SUPPRESS` は鍵を 250 ビット全体に戻す回帰でも緑のままなので、指標を並べるだけでは回帰が素通りする。キーを広げると `PREAMBLE_KEY_STABLE=0` で exit 8 になることを確認）。

### Changed

- **情報有効時間を災害種別ごとの配信終了条件（手順④）に変更**: 一律 `AZARAC_DEDUP_WINDOW_MS`（24時間）だった窓を、原PDF p.26–27 の条件表から決めるようにした（`src/internal/DedupWindow.h`、緊急地震速報 5分 / 震源・震度 2時間 / 南海トラフ 発表24時間・取消2時間 / 津波 発表かつ警報コード3-5 は最大24時間・他は10時間 / 北西太平洋津波 10時間 / 火山 24時間 / 降灰 最大1時間 / 気象 発表かつWw∈{1..6,23} は最大24時間・他は3時間 / 洪水 発表・訂正かつLv∈{2,3,4} は最大24時間・他は3時間 / 台風 3時間 / 海上 各警報は最大24時間・解除は最大3時間）。1通に複数の副種別が入る場合は「条件にて該当する情報の配信が終了する」ため、条件を満たすうち最長の窓を採る（短い側に倒すと生きた情報を再通知する）。一律24時間は表に無いカテゴリのフォールバックとして残る（MT=44 は A8 由来の窓を使う。下記）。
- **MT=44（DCX/CAMF）の照合鍵から SD を除外（#34）**: 照合対象は QZS 事務局回答のとおり「MT および CAMF〜EM」で SD を含まないため、`Decoder::messageIdentity` が MT=44 のときだけ SD（SDMT bit 14・SDM bit 15..23）をゼロにしてから CRC-24Q を取る（フレーム自体は呼び出しの前後で不変）。SDM だけが違う同一内容は同一情報として抑止される。回帰は `test/integration/test_parser_integration.cpp`（SD のみ相違→抑止、A8 相違→別情報）で固定した。
- **MT=44 の有効時間を A8-Hazard Duration の上限に変更（#34）**: 一律 `AZARAC_DEDUP_WINDOW_MS`（24時間）だった MT=44 の窓を、A8 の区分（`00`=1週間（DCX §5.4。All Clear 未受信時）/ `01`=6時間 / `10`=12時間 / `11`=24時間）から決めるようにした（`src/internal/DedupWindow.h`）。AVR はスロットが 64 と少なく 7 日の窓が生きた情報の枠を占めるため、`AZARAC_DEDUP_MT44_MAX_WINDOW_MS`（既定 5 分）で頭打ちにする（実測: MT=44 の再送は同一電文 2 回・最大間隔 16 秒）。回帰は `test/internal/test_dedup_window.cpp`（A8 各値と AVR 上限）。
- **重複判定表の既定容量を実測に合わせて変更**: 非 AVR の `AZARAC_DEDUP_SLOTS` を 64 → 512（4KB）、AVR プリセットを 16×4（`AZARAC_DEDUP_WAYS=4`、128B）→ 64×8（512B）にした。**2024 年の QZSS アーカイブ 30 日分**（月次サンプル 12 日 + 台風期 8 月の連続 20 日弱）を `make -C test dedup-realday` で計測:

  | 生存ピーク | 日数 | 256×8 の偽再通知 | 512×8 の偽再通知 |
  |---|---:|---:|---:|
  | 20–50 | 11 | 0 | 0 |
  | 51–100 | 13 | 0 | 0 |
  | 101–130 | 3 | 0 | 0 |
  | **327**（2024-08-28 のみ） | 1 | **2** | **0** |

  生存ピークの範囲は **20〜327**（中央値 66）。**512×8 は 30 日すべて偽再通知 0 / MISSED 0**、256×8 で偽再通知が出たのは最悪日（2024-08-28、台風10号＋大雨）1 日だけ。**512 が実測上の下限**で、能登 1 日（生存ピーク 75）だけを見ると 128 で足りるように見えるが、同時生存 327 件の複合災害日で 256 でも不足する。**MISSED（生きた警報を抑制）は 30 日 × 全容量で 0** — 満杯時の追い出しが「最も古い=窓切れに近い」1 件を選ぶため、容量不足は再通知として現れ、警報は落ちない。AVR プリセット（64×8）は能登の SEISMIC/TSUNAMI 部分で 0 件（32×8 も 0、16×8 は 93、旧 16×4 は 106）。`test/Makefile` の `pgm-stub` も `AZARAC_DEDUP_SLOTS=8`（AVR プリセットの WAYS=8 と組み合わさって SETS=1 になり容量を全く検証しない）から 64 に変え、AVR プリセットと一致させた。

- **`memprof` ジョブ（Valgrind Massif）を廃止**: ヒープのプロファイラは「ライブラリ自身が確保していない」ことを直接示さないため、上記の `test-no-alloc` に置き換えた。CI の `memprof` ジョブと `test/Makefile` の `memprof` ターゲットを削除した。`macro-size-check` はマクロ別 `.text` 相対差の計測として維持する。
- **azarashi 0.17.1 対応**: `.azarashi-version` を 0.16.4 → 0.17.1、`library.properties` の宣言を IS-QZSS-DCR-017 / IS-QZSS-DCX-004 Rev.004 に更新し、`src/` と `README.md` の DCR-016 参照を DCR-017 に置換した。`scripts/requirements.txt` の下限と CI の fixture-drift ジョブのピンも 0.17.1 に揃えた（同ジョブが diff する `test/data/nankai_pages_generated.h` は 0.17.0 と 0.17.1 で同一）。
- **長周期地震動階級 code 0 の突合を修正**: azarashi 0.17.1 はこの階級の表に code 0（`該当情報なし` / `No data`）を追加したが、報告属性は `None` のまま返す（JSON 側は名前を持つ）。`test/scripts/compare_with_azarashi.py` は属性と azaraC のラベルを突合するため、`make -C test compare-realdata` が realdata 974 通中 7 通（967/974 passed）の偽差分（`long_period_ground_motion_{lower,upper}_limit` の 2 キー）で exit 1 になっていた。「情報なし」を意味する `該当情報なし` / `No data` を `None` と同値として扱い、差分 0 に戻した。
- **ドキュメントとコメントの版数・API 名を更新**: `docs/json-formats.md` と `docs/api-reference.md` の azarashi 版数を 0.17.1 に、`to_json_dict()` を `azarashi.json.to_json_dict()`（0.17.1 で JSON 層が `azarashi.json` モジュールへ移動）に直した。`test/` の 3 本にある「azarashi v0.16.1 のデコード結果と照合」は版数に依存しない表現（定義テーブルは azarashi 0.17.1）にし、`a3` code 0 のコメントを 0.17.1 の表記（`Not used`）に合わせた。`src/` の仕様引用は CAMF v1.1 → v1.2（`DecoderDcx.cpp` は `(B1-B4)` に整理）、`README.md` に MT=44 の B フィールドと C10 の根拠（EWSS CAMF Issue 1.2）を明記した。Issue 1.2（2026-03 公開）は v1.1 から節番号と内容が変わっていないことを確認した（§3.5.3 = A11 は List A / List B 各 32 命令、§3.7.4 = B4、§11 = List A / List B、§18.2 = C5/C6 の式）。
- **`gen_definitions.py` を azarashi 0.17 の定義パッケージ構成に対応**: 定義パッケージが `azarashi.qzss_dcr_lib.definition` から `azarashi.definitions` へ移り、テーブル変数名から仕様接頭辞が落ちたため、モジュールパスから azaraC 側の既存 C++ 名を復元する規則（`definitions.qzss.dcr/*` → `qzss_dcr_jma_*`、`definitions.camf/*` → `qzss_dcx_camf_*`、`definitions.qzss.dcx/*` → `qzss_dcx_*`、`definitions.qzss.l1s/*` → `qzss_dcr_*`、`definitions.qzss.ubx/*` → `ublox_qzss_*`）と、それで戻らない 4 名の上書き（`preambles` → `qzss_dcr_preamble` 等）を追加した。再帰探索（`pkgutil.walk_packages`）によりサブパッケージ下の表も生成対象になる。生成後に、今回生成しなかった `.h` を `src/definition/` から削除する（`_index.h` を全再生成するため、残骸が黙って残らない）。
- **定義ヘッダを azarashi 0.17.1 で再生成**: 生成ヘッダ 138 本 + 手書き 2 本。旧 104 本から 48 本増、11 本減（うち 4 本は `qzss_dcr_{message_type,satellite_prn,preamble}.h` と `qzss_dcx_camf_a11_international_library_code.h` — JSON v2 のラベル削除・ガード未定義・消費者ゼロのため生成対象外にした）。内訳は英語表 37 本（既存表の `_en` 26 + 新規表の `_en` 11）、新規日本語表 10 本（`depth_of_hypocenter`, `eew_magnitude`, `hypocenter_magnitude`, `typhoon_number`, `typhoon_central_pressure`, `typhoon_maximum_wind_speed`, `typhoon_maximum_gust_wind_speed`, `typhoon_elapsed_time_from_reference_time`, `expected_ash_fall_time`, `ash_fall_warning_type`）。削除は `qzss_dcx_camf_a3_provider_identifier_{australia,fiji,japan,map,thailand}.h`（0.17 では `a3_provider_identifier_map` に統合。手書きの `qzss_dcx_camf_a3_provider_identifier.h` が既に同等で、中身の一致を確認済み）と `qzss_dcx_camf_ex9_target_area_code_{en,ja}.h`（参照ゼロ）。なお `qzss_dcx_ex1_target_area_code_en.h` は 1980 件すべての表記が変わる（例: `Sapporo-shi, Hokkaido` → `Sapporo City, Hokkaido Prefecture`）。`AZARAC_LANG_JA=0 / AZARAC_LANG_EN=1` 構成の都市名ラベル出力が変わるため、EN を有効にしている利用者はラベル文字列の変化に注意。azarashi 0.17.1 が追加した表のうち、消費者が無い `qzss_dcx_camf_{c7,c8,c9}_*`・`qzss_dcx_ex2_evacuate_direction_type`・`qzss_dcx_camf_a11_international_library_b_code`（IC-B-nn のコード名）と `*_value`（コード→物理量）表は生成対象外にした（前者は JSON が生値のみ、後者はコード + ラベルしか出さないため）。
- **IS-QZSS-DCR-017 のコード表変更を反映**: 津波の高さに `13 該当情報なし` を追加、洪水予報区に 3 件追加（`880801000200` 石手川 ほか）と 2 件改名（`890907000100` 矢部川 → 矢部川下流部、`890917000100` 番匠川 → 番匠川水系）、海上警報 31 の表記を `その他の警報等情報要素_海上警報` に、緊急地震速報の予報区 80 を `その他の府県予報区および地方予報区_緊急地震速報(警報)` に更新（いずれも今回のヘッダ再生成に含まれる）。
- **降灰の `warning_type_label` をハードコードから定義テーブルへ**: azarashi 0.17.0 が `ash_fall_warning_type` 表（1=速報/Preliminary, 2=詳細/Detailed）を持ったため、`JsonSerializerQzqsm.cpp` の `ashFallWarningTypeLabel()` を削除し `AZARAC_LOOKUP_LANG` に統一した。値は同一。
- **南海トラフ既定バッファ予算を修正**: 非 AVR の既定 `AZARAC_NANKAI_MAX_PAGES` を 12 → 63（仕様最大、Pn/Pm は 6bit）に、`AZARAC_NANKAI_BUFFERS` を 4 → 1 に変更した。既定構成でページ打ち切りが構造的に発生しない。集約領域を常時確保するため `Parser` の RAM は 1256B → 1432B に増加する（削減したい場合は `AZARAC_NANKAI_MAX_PAGES` を下げる。本リリースで dedup 表が 512×8=4KB になったため、既定構成の `sizeof(Parser)` はさらに 5,464B になった — 上記 Changed 節と `src/Parser.h` を参照）。AVR プリセット（4 ページ / 1 バッファ）は変更なし。
- **`docs/json-formats.md` の azarashi 側を 0.17.1（JSON v2）に追随**: §2 の記述を v2 の形に更新した。コードは `{scheme, code, recognized, labels}` → `{status, code, table, labels}`（`status` は `valid` / `assumed` / `special` / `undefined` の 4 値、`table` が体系名）、時刻は `{status, value, precision, source}`（`basis` は廃止、センチネルは `special` + `labels`）、数量は `value` か `range{lower,upper}` + `unit`（`kind` は廃止）、封筒は `is_test` / `reception{at,satellite,nmea}` / `message_id` / `series` / `texts`。EX9 の都道府県コードは azarashi も 0.17.1 から 1–47（`qzss.dcx.ex9_target_area_code_list`）になり、azaraC の `position` と一致する（v1 は `qzss.dcx.prefecture_bit` の 0 始まりビット位置で、同じ電文で `1` ↔ `0` とずれていた）。
- **§2.6 のサイズ・深さを再計測**: コーパスを再現可能な `test/data/*_vectors.json` の NMEA 228 通（MT43 98 / MT44 130。すべて azaraC が受理）に固定し、両者を同じ計量関数（UTF-8・区切り文字なしのコンパクト表現）で測り直した。azarashi 613,976 B（平均 2,692）/ `data` 371,812 B、azaraC 260,750 B（平均 1,143）/ `data` 203,609 B で、azaraC は azarashi の **1/2.35**。azarashi 側の内訳は `texts` が全体の 25%、`data` のうち `labels` が 31%、`table` のキー＋値が 25%（92,706 B、2,416 回。最多は EX9 の 430 回）。入れ子の深さの表も同じ 228 通のカテゴリごとに測り直した。あわせて §1.3・§2.2 の通数（133 → 130、`main_ellipse` 9 → 8、A11 の内訳 125/2/6 → 124/1/5）を実測値に揃えた。
- **A11 国際ライブラリの code 0 は azarashi と表記が違うと明記**: azarashi の JSON は国際 List A / List B（と C10）の code 0 を `status:"special"` + `labels:{en:"No instruction"}` と表記する（`azarashi/json/tables.py` が表の `0: ''` を上書きする）。CAMF Issue 1.2 は §3.5.3 の本文でこのコードを「Empty values …（各リストの 'null' ビット列）」＝空値と述べ、表と Annex §11 では `reserved`、`no instruction` と明記するのは C10 の §3.7.3.4 だけなので、azaraC は定義表の `""`（定義済みの空）を出す。同じ意味の別表記であることを `docs/json-formats.md` に明記した。
- **`docs/json-formats.md` を仕様書として再構成**: azaraC の JSON スキーマ（共通ヘッダ、MT43 `detail` のカテゴリ別キー、MT44 の A フィールドと条件付きブロック、B4 の D フィールド）を示したうえで、azarashi との対応（封筒、コード値、数量、時刻、繰り返し、サイズと深さ）と落ちる情報・互換方針を並べる形にした。数値の基準（`test/data/*_vectors.json` の NMEA 228 通と `make -C test decode`）も明記した。あわせて `developer-guide.md` の定義ファイル数（104 → 140）とテスト結果例、ドキュメント表のリンクを実態に合わせた。
- **`NankaiPageBuffer.h` の既定値重複定義を削除**: `AZARAC_NANKAI_MAX_PAGES` / `AZARAC_NANKAI_BUFFERS` の定義元を `azaraC_config.h` に一本化した。
- **CI の PlatformIO インストール手順を簡素化**: `platformio==6.2.0` は `starlette<2` を要求し、旧 6.1.19 の `starlette<0.53` 制約（PYSEC-2026-161/2280/2281/248/249）は解消済みのため、`scripts/requirements.txt` を超えて starlette を強制上書きしていた `pip install --no-deps` ワークアラウンドを削除した。
- **ドキュメントを実装に一致**: `architecture.md` のメモリ表（`DedupFilter` 8B/スロット、`NankaiPageBuffer` 28B + `MAX_PAGES × 18 + 1`、定義テーブル: 表エントリ 39 本で 122KiB（124,960B）、定義文字列を含むライブラリ全体の `.rdata` 344KiB（351,896B）、AVR プリセットは 3.4KiB（3,520B）。全カテゴリ・日英ラベル有効、64bit ホスト `g++ 15.2 -O2 -fdata-sections`（AVR は `-O0`）実測。253,568B は `const char*` 化前の表エントリ計量）、`library.properties` の EWSS CAMF 版数（v1.1 → v1.2）、`developer-guide.md` の定義ファイル数（103 → 104）とテスト構成、`getting-started.md` の参照先と設定マクロ表、`README.md` の C++17 要件を修正した。`README.md` の連続する引用ブロックを `>` で連結し、Markdown パーサ間で別ブロック引用と解釈され得る空白行を除去した（markdownlint MD028）。
- **`NankaiPageKey` の identity を report_time DHM に正規化**: 鍵を `{info_code, report_time month/day/hour/minute}` に統一し、解決済み UNIX 時刻を identity から除外した（`event_time_unix` フィールドを削除、`month` を追加）。`report_unix` が受信中に解決/未解決へ変わっても同一イベントが 1 バッファに集約される。従来は解決済み鍵と未解決鍵が不一致となり、`AZARAC_NANKAI_BUFFERS=1` では投入済みページが破棄され、`>1` ではバッファが分裂して集約が完了しなかった。`getNankaiBuffer()` に渡す鍵の生成方法が変わる（コンストラクタ引数は `(info_code, month, day, hour, minute)`）。
- **ドキュメントとコメントの書き掛け・装飾・文字化けを整理**: `architecture.md` のスロット数根拠を、計測手順の記述（30日分の取得、「このテストでの最悪値」、`REALDAY_INPUT` の切替手順）からデータと結論に絞り、`json-formats.md` の v1.0.x 差分表の前置き（「`[Unreleased]` の作業中の内容」）と「テスト電文で確認した」表現を整理した。`test/integration/test_error_handling.cpp` の 1 行目とセクション見出しに残っていた文字化け（無効バイト + U+FFFD）を修復し、`test_json.cpp` / `dedup_realday.cpp` / `gen_realdata_vectors.py` / `test_core.cpp` の作業ログ的な記述（「本作業の目的」「以前は」「ため削除した」）を設計記述に直した。`# ── ラベル ──` / `# ══…══` の装飾コメント（`.github/workflows/ci.yml`、`scripts/analysis/*.py`、`test/scripts/*.py`）をラベルだけに揃え、コメントとツール出力の `AzaraC` 表記を `azaraC` に統一した。挙動の変更は無い（`make -C test run` は 418 ケース / 10417 アサーションで緑）。

### Fixed

- **重複判定の同一性が仕様の照合対象（MT～VN）ではなく250ビット全体だった問題を修正**: 鍵の `crc24` は `Decoder::decode` がフレームの bit 0..225 から計算した値で、**プリアンブル（bit 0..7）を含んでいた**。仕様（アプリケーションノートv2 手順③、原PDF p.24–25）の照合対象は MT～VN（フレーム bit 8..219 = 212 bit）で、付属フローチャートも「MT～Vnの212bitについて比較する」と明記している。`Parser::handleFrame` が `Decoder::crc24q(frame.bits + 1, 212)` で部分区間の digest を作って渡すようにした（`crc24q` は `internal::Decoder` の public static に移動。`DedupKey::crc24` は `identity` に改名）。**Reserved 6 bit（220..225）も含めない**: 実放送では 16 値が巡回し、正しい 162 個の同一性のうち 138 個が複数の Reserved 値を持つため、含めると 1 情報が約 11 個に分裂する（能登の実日: 212 bit で distinct 162、218 bit で 1,764、250 ビット全体で 3,697）。受信衛星を鍵に含めない方針は変更なし。回帰は `Parser: プリアンブルが違っても同一 MT～VN は 1 回だけ通知される`（`test/integration/test_parser_integration.cpp`）と、実データの `PREAMBLE_KEY_STABLE`（ベンチ）で固定した。
- **重複判定が仕様（アプリケーションノートv2 原PDF p.23–25）と一致していなかった問題を修正**: 鍵が`{svid, msg_type, crc24}`だったため、①複数衛星からの重複判定が成立していなかった（250ビットのフレームに衛星IDは含まれず、`svid`はNMEA/UBXヘッダ由来の別レイヤ。衛星ごとに鍵が変わるので、中継された同一情報を衛星数だけ再通知する）。実測の一致率は 0.0044（`test/bench/bench_dedup.cpp`、実データ226種）。加えて時刻を持たないため手順④'「一定時間受信しなかった情報は履歴から削除する」が実装できず、10分無受信後の再放送を重複として抑止していた（同 0.3818）。
- **南海トラフの集約メッセージが到着順で別情報になっていた問題を修正**: 集約結果の重複判定は「ページ集合を完成させた電文」の `crc24` を鍵にしていたため、同じ事象を別のページ順で再放送すると毎回新しい情報として通知されていた。同一性を事象そのもの（`info_code` + `information_type` + 報告時刻、`NankaiPageKey` と同一の 26 ビット）に変更した。集約鍵は電文鍵とタグで名前空間を分けており（`DedupKey::synthetic`）、同じ数値の電文 CRC と衝突しない。回帰は `test/integration/test_nankai_e2e.cpp`（同一事象を逆順で再投入 → 再通知なし）で固定した。
- **南海トラフの事象鍵が情報種別（発表/取消）を区別していなかった問題を修正**: `info_code` と報告時刻が同一で `information_type` だけが異なる発表（It=0、窓24時間）と取消（It=2、窓2時間）が、dedup の事象トークンでも集約鍵でも同じ鍵になり得た。取消が発表の dedup 履歴に潰されて通知が落ち、集約バッファでも同じ Pn のページが先着優先で捨てられて 2 つの文面が混ざる。事象鍵に `information_type` を加えて 26 ビットにし、`DedupKey` の合成名前空間を bits 0..29 へ広げた（実鍵は bit 30 を立てないため衝突しない）。`NankaiPageKey` も同一の 6 フィールドに揃え、`NankaiPageBuffer` のレイアウト（メタデータ 28B・構造体 1,168B）は変わらない。回帰は `Nankai E2E: 同一 info_code + 報告時刻でも発表と取消は別に通知する`（`test/integration/test_nankai_e2e.cpp`）で固定し、トークンから It を落としても集約鍵から It を落としてもこのテストが落ちることを確認した。
- **重複判定表の追い出しが「最も古い情報」ではなかった問題を修正**: 巡回リングは書き込み位置で上書きするため、満杯時は**最新**の情報を捨て古い情報を残していた。通知済みの生きた警報が再通知され、逆に古い情報が居座る。情報ごとの最終受信時刻（手順④'）を基準に最も古い1件を置換するようにした。
- **`DedupFilter`の既定スロット数が実運用の同時情報数に足りていなかった問題を修正**: 既定8スロットに対し、24時間有効な津波警報や同時多発する気象情報では同時保持数が数十件になる。既定を64スロット（`AZARAC_DEDUP_WAYS=8`、512B）に増やした（本リリースでさらに 512 スロット / 4KB、AVR プリセットは 64×8 へ引き上げた — 上記 Changed 節を参照）。あわせて表をセットアソシアティブ化し、1決定あたりの走査を連想度（8）で頭打ちにした（全探索では32スロット時に97ns/決定、セットアソシアティブでは12.7ns/決定）。実測（実データ226種・2478決定）: 抑止率 0.38 → 1.00、新規情報の通知 34/38 → 118/118。AVRプリセットは当時16スロット（`AZARAC_DEDUP_WAYS=4`、128B）で、旧実装の4スロットより多かった（本リリースで 64×8 = 512B へ変更済み — 上記 Changed 節）。
- **PRN 空間外の `svid` に `svid_label` を付けないよう修正（v2 で `svid_label` を削除したためラベル部分は無効。`Frame::svid` の PRN 範囲記載の修正は有効）**: 定義表を `msg.svid & 0x3F` で無条件に引いていたため、PRN でない svid にも実在しないラベルが付き得た。`NmeaFramer` の `svid | 0x80` は仕様外の生 ID（64 以上）で PRN 空間外の値を作り（例: 119 → 247、`247 & 0x3F` = 55 = PRN183）、`UbxFramer` は `ublox_qzss_svid_prn_map` に無い svId をそのまま通す。`svid` が PRN 空間（128–191）のときだけ表を引くようにした（ラベルの PRN は `key + 128` なので、この範囲では `svid == PRN`）。実データ（`$QZQSM` の ID は 53–61 = PRN181–189）はすべて PRN 空間内のため 175/236 の解決数は変わらない。あわせて `Frame::svid` の PRN 範囲の記載（183–191）を 181–191 に修正した（`docs/architecture.md`, `src/framer/Frame.h`, `src/internal/Dedup.h`, `src/framer/NmeaFramer.cpp`）。`docs/json-formats.md` の MT44 記述も、共通ヘッダ 5 キーを出している実装に合わせて「MT43 固有項目を持たず」に直した。
- **A11 ラベルのライブラリ選択を仕様どおりに修正**: `JsonSerializerDcx.cpp` は A9=1 を International library（コード 0–31）、A9=0 を Japanese library へ送っていたが、DCX-004 §4.2.3.9 Table 4.2-12 は逆の定義。分岐を戻し、A9=1 かつ A2=111 のときだけ国/地域 library を引くようにした。実データ（重複文を除く 133 通）では A9=1 の 131 通がすべて空だったのが、国内表（A9=1 / A2=111）を引く 125 通のうち 43 通がラベル非空になった（A11=136 が 41 通、A11=128 と A11=134 が各 1 通。例: 136 = 「これは、Jアラートのテストです。」）。A9=1 / A2≠111 は表が無いため `null`。
- **A11 を List A / List B の2コードとして解決**: 国際ライブラリ（A9=0）の A11 を 10bit のまま 32 件の国際表へ索引していたため、List B（下位 5bit）のコードを List A の別の指示として表示し、A11 ≥ 32 では有効な List A 指示が `null` になっていた。EWSS CAMF v1.1 §3.5.3 / §11 は A11 = List A 5bit + List B 5bit と定めるため、`a11 >> 5` で List A を、`a11 & 0x1F` で List B を引き、List B を新キー `a11_guidance_list_b_label`（常時出力）に出すようにした。日本の表は 10bit を鍵にした結合表なので List B は `null`。国際表 List A / List B の code 0 は定義済みの空文字列 `""`、List B の 29/30 は表に無く `null`。List B の表（`qzss_dcx_camf_a11_international_library_b`、30 キー）は azarashi 0.17.1 の定義ヘッダ再生成で得た。同 0.17.1 は code 0 のラベルも追加しており（`a11_japanese_library_ja` 0 = 「指示なし」、`c10_instruction_library_for_second_ellipse` 0 = `No instruction`、A3/A4 = `Not used`、長周期地震動 0 = 「該当情報なし」/`No data`、津波高 13 = `No data`、津波発生の可能性 7 = `Other Tsunamigenic Potential`）、実データ 133 通（重複文を除く）の内訳は「ラベルあり 125（A11=0 の 82 通が `指示なし` になる）/ `""` 2 / `null` 6」に変わる。d3/d4 の表は `undefined` 付きになり戻り値が `std::optional`、ラベルも数量表記へ変わった（`112.5` → `112.5°`）。
- **`NmeaFramer` の Satellite ID 正規化を仕様どおりに修正**: `Frame::svid` の契約は PRN（`api-reference.md` の「衛星ID (QZSS L1S PRN: 183-191)」）だが、`NmeaFramer` は `55 <= svid <= 63` のときだけ `+128` し、それ以外は入力値をそのまま通していた。Satellite ID は「PRN を表す 8bit の下位 6bit」（DCR-017 §4.3.1 / DCX-004 §4.3.1）なので、53/54 も PRN181/182 に正規化されるべきで、azarashi も全 ID に `| 0x80` を適用する。実データ 236 通のうち 61 通（53: 5 / 54: 56）で `svid` が azarashi・`test/data/dcx_vectors.json` の期待値（`(53,181)` / `(54,182)`）と食い違っていた。`svid | 0x80` に統一（`55–63` では `+128` と同一、128 以上は恒等なので二重変換しない）。
- **`svid_label` が常に空だったバグを修正（v2 で `svid_label` を削除したためこの修正は 2.0.0 の出力に現れない。記録として残す）**: IS-QZSS-DCR-017 §4.3.1 は「Satellite ID is 6 LSB of the 8 bit which represented PRN of the L1S」と定め、定義表 `qzss_dcr_satellite_prn` のキーもその 6 LSB（`55,56,57,58,61`）。一方フレーマは svid を PRN に正規化する（`NmeaFramer` は `+128`、`UbxFramer` は `svid_prn` 経由）ため、`qzss_dcr_satellite_prn_lookup(msg.svid)` は**必ず引き外れて常に空文字列**になっていた。`msg.svid & 0x3F` を引くよう修正。236 電文での実測で 0/236 → **175/236** 解決（`PRN183`–`PRN189`）。残り 61 件は PRN181/182（正規化前の生 ID 53/54）で、表が覆う `{55,56,57,58,61}` の外にあるため空文字列が正しい（azarashi も同じくラベルを持たない）。
- **カテゴリ無効化が英語表に効いていなかった問題を修正**: 生成器の `category_guard` は `GUARD_MAP` を変数名の完全一致で引いていたため、`*_en` / `*_ja` 表が翻訳元のカテゴリガードを継承していなかった（`GUARD_MAP` のコメントは以前から継承を前提に書かれていた）。影響は 2 つ。`-DAZARAC_ENABLE_TSUNAMI=0` で日本語表は消えるのに英語表が残り、**Flash 削減が半分しか効かない**。そして「JA と EN は同じコード集合を引く」不変条件が崩れ、`make macro` が `AZARAC_ENABLE_EEW=0` で落ちていた（実測 36 表、`test_definition_labels.cpp` の JA/EN 一致検証で `id=1..15` が不一致）。`category_guard_for()` で継承を実装し、定義ヘッダ（`*_en` 39 本）を再生成した。`a11_japanese_library` / `ex1_target_area_code` / `ex9_target_area_code` は `_en`/`_ja` しか存在しないため完全一致を優先する（継承でガードが消えない）。EN 表の内容テストも各カテゴリのガードに合わせて `#if` で囲んだ。
- **JA 専用テーブルが無い `_en` 表が既定構成で消えていた問題を修正**: `gen_definitions.py` が `_en` 接尾辞の表を無条件に `AZARAC_LANG_EN` でガードしていたため、日本語版を持たない英語専用表（`tsunamigenic_potential_en` / `coastal_region_en` / `northwest_pacific_tsunami_height_en` / `ambiguity_of_activity_time_en`）がライブラリ既定（`AZARAC_LANG_JA=1 / AZARAC_LANG_EN=0`）で `nullopt` スタブになり、北西太平洋津波カテゴリの `potential_label` / `height_label` / `region_label` が**すべて空文字列**になっていた（実電文で実測）。仕様自体が英語のため日本語版が存在しない表で、CAMF の各表と同じく言語非依存として扱うべきもの。日本語版を持つ `_en` 表（`prefecture_en` など）は `AZARAC_LANG_EN` と翻訳元のカテゴリガードの両方でガードされる（後者は上記の継承修正で入った）。定義ヘッダを再生成した（4 本のガード行のみ変更）。回帰は `test/internal/test_definition_labels.cpp` の「lone `_en` tables resolve regardless of `AZARAC_LANG_EN`」で固定し、`make -C test run-lang-defaults`（JA 単独 / EN 単独の 2 構成）を新設して CI に追加した。テスト既定（JA=1 / EN=1）だけではこの回帰は現れない（EN 表が生きているため）。
- **`test_definition_labels.cpp` の a11 英語ラベル期待値を修正**: azarashi 0.17.0 は日本語ライブラリの英語版コード 0 に `No instruction` を与えたため、`size() == 0` を期待していた検証を「値が存在する」に変更した。英語ビルドで落ちるようになっていた。
- **`test_json.cpp` のラベル検証を言語非依存化**: ラベル期待値が日本語リテラル直書きだったため、`AZARAC_LANG_JA=0 / AZARAC_LANG_EN=1` の構成で 33 アサーションが落ちていた（本変更前から存在する不具合）。`LBL(ja, en)` マクロで言語ごとの期待値を持たせ、検証する不変条件（コード→ラベルの対応）を全構成で保つようにした。`AZARAC_LANG_EN` を有効にした初の検証は、この構成で `make -C test run` が通ることをもって完了とする。
- **テストが既定構成を検証していなかった問題を修正**: `test/Makefile` が `-DAZARAC_NANKAI_MAX_PAGES=63` を無条件に渡していたため、ライブラリ既定値の経路が未検証だった。`-D` を削除し、既定（63）を `make -C test run` で検証、縮小バジェット経路を `make -C test run-small-pages`（`AZARAC_NANKAI_MAX_PAGES=8`）と CI ステップで検証する。`run-small-pages` / `pgm-stub` は `-D` 群が依存関係に載らないため終了時に `clean` し、別構成の `.o` が既定構成の `.o` と混在して以降の `run` が再ビルドされない（または `check-strict-compile` 後の混在リンクで落ちる）問題を防ぐ。
- **`NankaiPageKey::isValid()` を削除**: 本番コードから呼ばれておらず（`addPage` は `isValid()` を見ない）、identity が生 `report_time` + `info_code` に一本化された後は意味のある不変条件を表さないため削除した。空バッファ誤マッチは `NankaiPageBuffer::matchesKey()` の `isEmpty()` ガードが担う。
- **打ち切りの E2E テストを追加**: `total_pages > MAX_PAGES` のとき `MAX_PAGES` ページで集約が完了し `truncated=true` / `total_page` が電文の総ページ数を報告することを検証する。
- `scripts/analysis/cppcheck_summary.py` から削除済みマクロ `AZARAC_NANKAI_AGGREGATED_TEXT_SIZE` の指定を削除した。
- **`.gitignore` と `test/Makefile clean` を整備**: テスト生成物（`test/cppcheck_report.xml`, `test/coverage_report.json`, `test/macro_sizes.txt`, `test/no_alloc_tests`, `test/bench/bench_dedup` 等）を追跡対象外にした。`test/Makefile` の `MINGW64_BIN` 既定値から個人パスを削除し、コマンドライン指定の任意設定にした。
- **ゼロ鍵が空バッファに誤マッチする問題を修正**: `NankaiPageBuffer::matchesKey()` が空（全ゼロ鍵）バッファを一致扱いしていたため、ゼロ鍵イベントが継続中バッファではなく空きスロットに書かれ、スロット再利用時に分裂し得た。空バッファは一致しないようにした。
- **Nankai ページフィクスチャを azarashi から生成し二重管理を解消**: `test/scripts/gen_all_vectors.py` の Nankai 入力を上流の 27 電文に拡張し、`test/data/nankai_vectors.json` を 27 ページに完全化、同じ JSON から `test/data/nankai_pages_generated.h`（C++ フィクスチャ）を生成するようにした。`test_nankai_e2e.cpp` の手書き配列と `compare_nankai_aggregation.py` の重複コピーを削除した。実データの最終ページは NUL 埋め（「い。」のみ）で、期待集約長は合成値時代の 486 ではなく 474 バイトになる（テストは NUL 打ち切りを反映して算出）。
- **DCX の未検証項目にテストを追加**: `decodeLatitude17` / `decodeLongitude17_45_225` / `decodeB2HazardCenter`（`c5/c6 > 63` の丸め分岐を含む）/ `decodeCityCodeList` の単体テスト、B4 の複数レイアウト（a4=47/51/64/77/80/82）の JSON raw 値と未知 a4、主楕円・追加楕円の統合座標を検証する。
- **デッドコードを削除**: `#if 0` の `test/integration/test_azarashi.cpp` と、未使用の `test/test_helpers.h` の `testDecode*` ラッパ 11 個を削除した。
- **v2 テストにカテゴリマクロガードを追加**: 新規 5 テストが `#if (AZARAC_ENABLE_*)` の外にあり、`AZARAC_ENABLE_TSUNAMI=0` で 9 アサーション失敗、`AZARAC_ENABLE_DCX_CAMF=0` で `initMt44` 未宣言のコンパイルエラー 3 件（`test/json/test_json.cpp`）になっていた。`make -C test macro` が TSUNAMI で打ち切られるため DCX_CAMF は CI では未到達だった。テストが使うカテゴリのガードで囲み、アサーションは変更していない。

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
