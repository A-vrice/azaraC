# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Fixed

- **津波通知ラベルのガードと生成物の同期（2026-11-16）**: 津波の通知ラベルを `AZARAC_TSUNAMI_NOTIFICATION_LABELS` で制御するようにした。生成ガード（`gen_definitions.py`）と `AZARAC_FLASH_BUF_SIZE` の640 B分岐を同じマクロで駆動し、非AVR既定は `AZARAC_ENABLE_TSUNAMI`、AVRプリセット既定は0。表はEEW/震源と共有されるため、どちらかが有効なら0でもラベルは出る。`check_flash_buf.py` はこのマクロを擬似カテゴリとして扱い、AVRで有効化した場合の596 Bラベルも検証する。`keywords.txt` と `keywords_check.py` にも追加した（設定マクロ27）。
  津波通知の実アンカー（azarashiの `notifications_on_disaster_prevention_raw` = 122/123/124、warning 3、regions 600/610/760）とCAMF A7上限を `test_realdata_anchors.cpp` に追加し、生成ファイル `test_realdata_generated.cpp` の手書き不変条件を撤去した（再生成で消えるため）。
  `make -C test run-tsunami-labels-off` を追加し、ラベル無効構成（EEW/震源も無効）をCIで回す。
  ドキュメントの実測・実挙動との同期: Parser RAM 6,624 B、未解決時刻の月日は生値、津波 `notifications` の記載、`Message` 91 B、Nankai集約時の `page` 規約。

### Changed

- **ClusterFuzzLiteのfuzzを3つのコンパイル時構成で実行する**: `.clusterfuzzlite/build.sh` が既定構成に加え、AVR相当の縮小構成（Nankaiバッファ1個・最大4ページ、dedup 64スロット、有効カテゴリは震度・南海トラフ・津波のみ）と検証厳格構成（dedup無効、SVID検証レベル2、NMEAの非0パディングを拒否）を別ターゲットとしてビルドする。バッファ追い出しや受理/拒否の分岐は構成で変わるため、既定構成だけでは届かない経路をfuzzで踏む。既定ターゲットの名前と定義は不変で、corpusの継続性は保たれる。fuzz時間はターゲットあたりPR 300秒・週次batch 1200秒とし、ジョブ合計は従来と同程度に保った。

## [2.1.0] - 2026-11-15

### Added

- **公開APIの追加（未テスト経路の回帰と組み込み向けの小口API）**:
  - `azaraC::crc24q(data, bit_len)` を公開した。受信経路が使う `internal::Decoder::crc24q` への薄いinlineで、自前の電文生成（テスト送信器・リピータ）や外部で組み立てた250 bitフレームの検証に使える。既知ベクタ（`"123456789"` = 0xCDE703）、0 bit / 8 bit / 226 bit / 250 bitで参照実装と一致することを固定した。
  - `Parser::feed(const uint8_t* data, size_t len, Message& out, uint32_t report_unix = 0)` を追加した。受信バッファをそのまま流せる。内部は1バイト版のループで、挙動（Nankai集約・dedupを含む）は逐次呼び出しと同一であることを等価性テストで固定した。メンバは増やしていない。
  - `azaraC::toJson(msg, char* buf, size_t len)` を追加した。`Print` を持たない呼び出し側向けの境界付き出力で、`len > 0` なら必ずNUL終端し、バッファ外へは書かない。`Print` 版とバイト一致すること、切り詰め時も `buf[戻り値] == '\0'` になることをテストした。
  - `test/integration/test_parser_clock.cpp` に `Parser::updateClock()`（公開API）を通す回帰を追加した。これまではfriendの `observeClock()` を直接叩いており、wrapperは未実行だった。`AZARAC_TESTING` 限定の時刻ソース注入（`internal::testSetMillisSource` / `TestMillisScope`）で、フレームを1バイトも与えずに世代境界（2³² ms）・1 ms後退の丸め・窓満了を決定的に検証する。リリースの `getMillis()` 分岐（AVRのSREG、Cortex-MのPRIMASK、ESP32の `esp_timer`）には触れていない。
  - 未到達だったエラー経路のテストを追加した: NMEAのSVID非数字／255超の拒否、`invalid_mt44` のnote（MT=44でpayload無し）、NW-PACの表に無い高さコードと未解決到着時刻（`arrival_time:null` + `arrival_status`）、Nankai manager経由の `Rejected`（総ページ数不一致で進行中の集約を壊さない）。
  - `keywords.txt` を公開API全体（型・アクセサ・列挙値）へ拡張し、`examples/custom_framer`（`IFramer` 差し込み）と `examples/basic_dcx`（MT=44の表示）を追加した。
  - `test/Makefile` に `STATIC=1` を追加（MinGWでlibstdc++/libgccを静的リンクする。動的リンクしたテストバイナリが起動時に0xC0000139で落ちる環境向け）。
  - READMEのAVR実測値に「avr-gccの版依存であり、`bench` がゲートするのはSRAM非増加と64 KiB窓である」旨を追記した。

- **南海トラフの訓練/実警報の分離と集約状態の修正**:
  - `NankaiPageKey` と `dedupEventToken` に `report_classification`（Rc、3 bit）を追加した。訓練/試験（Rc=7）と実警報（Rc=2）が同じ事象として抑止・混在するのを防ぐ。事象トークンは26 bitから29 bitになり、合成鍵のpayload 30 bitに収まる。`NankaiPageKey` は7 B、AVRの `NankaiPageBuffer` は1,158 B（4ページ構成は96 B）、ホストは1,160 Bのまま。
  - `NankaiPageBufferManager` がページ範囲を割り当て・LRU追い出しより前に検証するようにした。別事象の不正ページが進行中の正常な集約を消さない。
  - 完成済みNankaiの再送ページは本文を再出力せず、dedupの `last_seen` だけを更新する。未完成ページの重複ではdedupを呼ばない。`AZARAC_ENABLE_DEDUP=0` ではNankaiのページビットマップ抑制が残ることを明記した。
  - `Parser` に64 bit時刻のepoch guardを追加した。通常の32 bit折り返しは符号なし差分で維持し、1,000 ms以内の時計後退は受信順序の揺らぎとして最終観測時刻に丸める。1,000 msを超える後退（時計の再設定）または2³² ms以上の空白のときだけdedup/Nankai履歴を捨てる（再通知は許容し、生きた警報の抑止を避ける）。
  - 回帰テストとして、Rcの分離、訓練/実警報ページの混在防止、不正ページによる既存バッファ破壊の防止、完成後再送の履歴更新、折り返し/後退（1 msの丸め・大きな後退後の満了・Nankai無効時のdedup単独）を追加した。`run-dedup-off` と実avr-g++ の `avr-layout` を追加し、fuzzにstateful Parserと警告の失敗条件を追加した。
  - `examples/rtos_freertos` の `Message` バイトコピー（ISO C++ では未定義動作）を、静的スロット + ready/freeインデックスキューへ変更した。
  - テストの保守性を改善: `test_message_struct.cpp` の全12型copy/moveを型テーブルへ統合し、`test_parser.cpp`/`test_decoder_dcx.cpp` の名前を内容に合わせた。`test_nankai_e2e.cpp` のNankaiフレーム生成はRcを引数化した。

- **レビュー指摘の修正（API契約・入力検証・CIゲート）**:
  - 南海トラフの `aggregated_text_ptr` が `Parser` 内部への借用ポインタであることを `docs/api-reference.md` とREADMEに明記し、`Message` をコピーした後に内容が別の警報文へ変わることを `test/integration/test_nankai_e2e.cpp` で回帰固定した。
  - `AZARAC_ENABLE_DEDUP=0` を追加。`DedupFilter` が状態を持たず常に「新規」を返し、`Parser` から `AZARAC_DEDUP_SLOTS × 8 B`（既定4 KB / AVR 512 B）が消える。`test-macro-compile` に `-DAZARAC_ENABLE_DEDUP=0` を加えて常時コンパイル検証する。
  - `AZARAC_NMEA_STRICT_SVID`（0=00–63 / 1=53–63 / 2=仕様表の55/56/57/58/61）と `AZARAC_NMEA_REJECT_NONZERO_PADDING` を追加。既定は実機互換と警報の可用性を優先し、従来どおり受理する。
  - `AZARAC_FLASH_BUF_SIZE` に64未満を拒否する `static_assert` を追加し、ラベルの切り詰めをUTF-8境界へ丸めるようにした（`azarac_utf8_trim_len`）。
  - 上の3つの政策（`AZARAC_NMEA_STRICT_SVID` / `AZARAC_NMEA_REJECT_NONZERO_PADDING` / UTF-8切り詰め）はどのビルドでも分岐が生きるとは限らないため、`make -C test nmea-policy`（既定 / `STRICT_SVID=1` / `STRICT_SVID=2` + パディング拒否の3構成で受理表をassert）、`make -C test utf8-trim`（`AZARAC_FLASH_BUF_SIZE=64` で切り詰めをassert）、`make -C test avr-layout`（DCX有効構成を追加）と `test_message_struct.cpp` のサイズ `static_assert`（ホスト240 / 104 B、AVR 84 / 199 B）で実行時に固定した。`AZARAC_NMEA_STRICT_SVID` は0-2の外を `#error` にする。
  - ファズの `invalid_crc` / `invalid_preamble` を実加算し、プリアンブルとデータ部の破損を決定的に混ぜた。両方が0ならファズを失敗させる。`Framer rejects` も追加。
  - `Parser::handleFrame` が復号失敗時に `valid` を落とすようにした（`decodeQzqsm()` が `valid=true` を設定した後に `oob_` でfalseを返す経路）。
  - `azaraC.h` の `abs`/`min`/`max` undefを `push_macro`/`pop_macro` で往復し、利用者のスケッチから恒久的に消さないようにした。
  - 生成定義ヘッダに準拠仕様（`IS-QZSS-DCR-017 / IS-QZSS-DCX-004 Rev.004 / EWSS CAMF Issue 1.2`）を記録し、`gen_definitions.py` のテンプレートと139ヘッダを揃えた。
  - `update-definitions.yml` はPR作成前に `make -C test run` と `make -C test bench` を実行する（既定 `GITHUB_TOKEN` のPRはpushでCIが起動せず、`pull_request` も承認待ちになるため）。
  - CIにASan/UBSanジョブを追加（ゲート。`summary` の `needs` に含め、結果をPRコメントの表に出す）。コアヘッダのchronoパッチは対象0件ならwarningに留める（コア側が直った時点で全PRを落とさない）。
  - **全payload型をカテゴリマクロでガード（M7）**: `SeismicData` / `TsunamiData` / `NwPacTsunamiData` / `VolcanoData` / `AshFallData` / `WeatherData` / `FloodData` / `TyphoonData` / `MarineData` と対応するentry型・enum値・`getXxx()`・`typeFor<>` を `AZARAC_ENABLE_*` でガードし、`DedupWindow.h` のカテゴリ別窓計算も同じガードで囲んだ。
    カテゴリを無効にするとRAM枠が連動して縮む（ホスト実測: 津波系無効で `storage_size_` 88→56 B、全無効で1 B。`storage_` が空配列にならないよう1 Bに切り上げ）。
    `DedupWindow.h` のpayload引数は全対象カテゴリ無効時に未使用になるため `(void)payload;` を追加。
    テスト側も同じガードで囲み（`test_message_struct` / `test_json` / `test_json_wellformed` / `test_dedup_window`）、実データ回帰は `gen_realdata_vectors.py` の `DC_TYPE_GUARDS` を全カテゴリに拡張して再生成した。
  - **`make -C test macro` のNANKAI=0を修正**: `test/integration/test_parser_clock.cpp` の外側ガードが `NANKAI || DEDUP` で、`NANKAI=0` でも `NankaiData` を参照してコンパイルできなかった（CIの `macro-runtime-test` が赤）。ガードを `AZARAC_ENABLE_NANKAI` のみに変更。`test_dedup_window.cpp` のdc=5/10/11/14のpayload無し仕様値も各カテゴリマクロで囲み、カテゴリ無効時に `default` へ落ちる挙動と整合させた。

- **CIにLTOゲートを追加**: `make -C test run-lto` を新設し、host-testで `-O2 -flto` の全体再ビルド・テスト実行を必須にした。
  LTOの型不一致（`-Wlto-type-mismatch`）とODR違反（`-Wodr`）はGCCでは既定で警告に留まり素の `-flto` では緑のままなので、この2つだけ `-Werror` にしてゲートで落とす（過去に `AZARAC_DEDUP_SLOTS` の配列長不一致をLTOだけが検出した事例がある）。
  `CXXFLAGS` は依存関係に載らないため `-B` で再ビルドし、終了時に `clean` する。
  あわせて `wf_deg` の桁数ループに上限9を明示し、`-O2 -flto` で出ていた `-Wstringop-overflow` の偽陽性を解消した（`buf[12]` に対する値域証明）。
- **定義テーブルのAVRフットプリント計測ハーネス**（`make -C test bench`、`autoresearch.sh` + `test/bench/avr/`）: `avr-gcc -E` の出力からプールと行のバイト数を数え（`AVR_TABLE_BYTES`）、avr-gcc自身のオブジェクトサイズと突合する（`AVR_TABLE_CROSSCHECK`）。
  ゲートは7つ:
  - 全1,409,708照会のラベル一致（AVR far / AVR 16bit / ホストの3経路）
  - ATmega2560での全カテゴリのコンパイル（プールが上限を下回っているときのみ）
  - 既定AVR構成のリンク
  - SRAM非増加（`UNO_RAM_BYTES` ≤ 142B、`MEGA_RAM_BYTES` ≤ 892B、`AVR_TABLES_IN_RAM` = 0）
  - **コア側PROGMEMが16bit窓（64KiB）内に残ること**（`test/bench/avr/core_progmem.c` を最後にリンクして `MEGA_CORE_PGM_ADDR` ≤ 0xFFFF）
  - **共有ラベルバッファが有効カテゴリの最長ラベルを収めること**（`test/bench/avr/check_flash_buf.py`、`FLASH_BUF_OK`。全カテゴリ組み合わせ×両言語×両プリセットを掃き、`AZARAC_FLASH_BUF_SIZE` の選択連鎖をavr-gccの前処理結果と突合する）
  - そしてazaraC自身のCRC24Q表が16bit窓（64KiB）内に残ること（`src/decoder/Decoder.cpp` の表を `avr-nm` で採取して `MEGA_NEAR_SYM_ADDR` ≤ 0xFFFF。表が消えた・別の節へ移った場合も失敗させる）
  `bash autoresearch.sh --bless-labels` はラベル基準値の再記録用。
- **dedupベンチをCIに戻した**（`make -C test bench-dedup`、`test/bench/run_dedup_bench.sh`）: AVRテーブル計測ハーネスが `autoresearch.sh` を置き換えた際に、旧 `make -C test bench` が回していたdedupのゲート（`NEW_RECALL` / `DUP_SUPPRESS` / `NANKAI_KEY_STABLE` / `PREAMBLE_KEY_STABLE`）と `test/bench/bench_dedup.cpp` をビルドする経路がCIから落ちていた（`bench` はフットプリント計測のまま）。
  旧ハーネスを `test/bench/run_dedup_bench.sh` として復帰させ、`bench-dedup` ターゲットとhost-testジョブのステップを追加した。
  入力は `test/data/*.json` のみ、hostのg++ だけで動く。
  実測: `NEW_CORRECT=118` / `DUP_SUPPRESS=1.0000` / `NANKAI_KEY_STABLE=1` / `PREAMBLE_KEY_STABLE=1` でexit 0となった。
- **libFuzzerのカバレッジ誘導fuzzを追加**: `test/fuzz/fuzz_libfuzzer.cpp` はParser AUTO / NmeaFramer / UbxFramer / toJson+JsonCheckの4経路を `data[0] & 3` で切り替える薄い入口で、`make -C test fuzz-libfuzzer` でビルド・実行する（clang++ が無い環境はSKIPしてexit 0）。
  シードは `test/scripts/gen_fuzz_corpus.py` がテストベクタから生成した682ファイルを `test/fuzz/corpus/` にコミットした（`.gitattributes` で `-text` 指定。改行変換でバイトが変わるとシードが壊れるため）。
  `.github/workflows/fuzz-libfuzzer.yml` はPR 120秒・週次600秒のベストエフォートジョブで、クラッシュ入力をartifactとして14日保持する。
  あわせて `keywords.txt` を公開API（型46・メソッド35・設定マクロ26）へ同期し直し、公開ヘッダの型定義と `azaraC_config.h` のユーザーマクロを双方向照合する `scripts/analysis/keywords_check.py` をCIのversion-syncでゲートにした。

### Changed

- **CIのfixture-driftとテスト集計**: fixture-driftはazarashiの再実行ではなく、コミット済み `nankai_vectors.json` から `--nankai-header-only` でC++ フィクスチャを再生成し、`git diff` でドリフトを検出するようにした。
  JSON全体は `timestamp`（生成時刻）を含むため差分比較に使わず、`nmea` / `type` / `params`（`timestamp` を除く）のSHA-256を `test/data/nankai_vectors.sha256` に固定して `test/scripts/hash_nankai_vectors.py --check` で検証するようにした。
  host-testはdoctestのケース数・アサーション数をGitHub Actionsのstep summaryに出力し、`docs/developer-guide.md` の固定件数を削除した。
- **EEW予報区アクセサの計算量を落とした**: `EewData::regionAt(i)` は毎回ビットマップ先頭から1 bitずつ数えていたため、`regionCount()` と組にしたループがO(N×80) になっていた。
  8bit popcountのヘルパを足し、`regionCount()` は10バイトの立ビット数の和、`regionAt(i)` は「各バイトの立ビット数で `i` を読み飛ばし、該当バイトだけ8 bit走査」にした（最悪80 bit → 10バイト + 8 bit）。
  `region_bitmap[10]` の保持方針（展開配列81Bは不採用）と契約（昇順0始まり・範囲外0・bit i = 予報区i+1）は不変で、JSONの `regions` はバイト単位で同じだ。
  あわせて `addRegion(code)` の「テスト用」という但し書きを外し、公開API（範囲外は無視、既存ビットは保持）として `docs/api-reference.md` に明記した。
  回帰は `test/core/test_message_struct.cpp` に境界（範囲外0/81・バイト跨ぎ8→9・最終ビット80・重複・`i >= regionCount()`）を追加し、ホスト352ケース / 15,180アサーションと `make -C test run-lto` が緑になった。
- **JSONのDフィールドをD番号順に出力**: `detailed_info` のD1–D36がd3, d4, d1, d2, d5… の順で出ていたのを、d1, d2, …, d36の昇順に直した。
  キーの並びはJSONとして意味を持たないので `schema_version` は2のまま上げない。
  既定構成の出力は並び以外バイト単位で不変（`docs/json-formats.md` §1.4の例も追随）。
- **AVRのpayload枠から `alignas(8)` のパディングを外した**: `Mt43Data::storage_` / `Message::payload_storage_` の `alignas(8)` を `alignas(uint64_t)` にした。
  avr-gccの `__alignof__(unsigned long long)` は1なのでAVRではこの指定が境界を要求せず、8の倍数への切り上げだけが残っていた（ホストは `alignof(uint64_t)` が8で、レイアウトは不変）。
  ATmega328P `-Os` の実測: `sizeof(Mt43Data)` 88B → 80B / `sizeof(Message)` 104B → 89B、全カテゴリ有効時は128B → 118B / 144B → 127B。（この89B / 127BはEEW予報区が展開配列 `regions[80]` だった時点の値。続く「メモリ・CPU最適化（第2弾）」で `region_bitmap[10]` にしたため、現在はAVRプリセット84B / EEW有効でも84B、全カテゴリ + DCX/CAMF 199B。ホスト全カテゴリ + DCX/CAMFは240B）
  `Message` はスケッチがグローバルに置くとそのまま `.bss` を食うので、利用側のSRAMも同じだけ減る。
  あわせて `AZARAC_KEY_BUF_SIZE` の既定を40B → 36Bにした（最長キーは35Bで、`static_assert` と `keyBuf()` の書き込み添字はそのまま成立する）。
  AVRベンチ実測: Uno 146B → 142B（data 30 + bss 112、`keyBuf` 40B → 36B）、Mega + DCX/CAMF 896B → 892B（LTO構成も892B）、FlashはUno 14,622B → 14,702B / Mega 146,700B → 146,550B。
  JSONの出力バイト列は不変（`test/json/*` の期待文字列テストとホスト418ケースがそのまま通る）。
- **AVRベンチのスタブが `SREG` / `cli()` を提供していなかった**: f41550aで `internal::getMillis()` がAVRで `SREG` を退避・復元するようになったが、`test/bench/avr/shim/Arduino.h` はArduinoコアの `millis` / `Print` しか持っておらず、`make -C test bench` のUno / Mega / LTOの全構成が `'cli' was not declared in this scope` でコンパイルに失敗していた（exit 12）。
  実コアと同じく `<avr/interrupt.h>` / `<avr/io.h>` を取り込むようにした（`FlashString.h` が `FLASHEND` 用に後者を既に含むため、`SREG` はマクロのこともある）。
- **レビュー指摘の記述を実装に合わせた**: `feed()` が `false` を返す理由（フレーム未完成・CRC誤り・重複でも `false`。`msg.unsupported_reason` に入るのは復号器が完成フレームを拒否した場合だけ）を `docs/api-reference.md` の3箇所で明確にし、 `unsupported_category` が出るのは手動で構築した `Mt43Data` の直列化だけであること（受信電文の復号では無効カテゴリは拒否され `payload_type` は `Empty`）を `docs/json-formats.md` に、
    AVRプリセットで除外されるpayload型が `EewData` / `HypocenterData` / `NankaiData` だけで `SeismicData` / `TsunamiData` はカテゴリを無効にしても定義が残ることを `README.md` に書いた。
- **AVRの計測に実機構成のゲートを追加**: `test/bench/avr/autoresearch.sh` のstage 5b（Arduinoコアと同じ `-flto` の構成）は、リンクできることとATmega2560のSRAM 8,192Bに収まることがゲートになった（実測892B）。
  プローブ（`test/bench/avr/probe.cpp`）は入力バイトを `volatile` にして `feed()` が「フレーム未完成」に畳み込まれないようし、出力sinkの `write()` を不透明（中身を見ない演算）にしてシリアライズ経路と定義表が画像に残るようした。
  リンク画像に復号経路・シリアライザ・定義表が残っているかもゲートで検査する（実測: Unoに表8 / Megaに100 / Mega LTOに98シンボルが残る）。
  プローブのsinkでUnoの画像は +132B（14,470 → 14,602）、Megaは +18B（146,672 → 146,690）。
  当時のSRAMは変わらない（Uno 146B / Mega 896B）。
  いずれも計測プローブの改造によるもので、ライブラリのコードも公開API・JSONの出力も変わらない。
- **生成物と手書き物の置き場を分けた**: `test/integration/test_realdata.cpp`（`gen_realdata_vectors.py` の生成物）を `test/data/test_realdata_generated.cpp` へ、ルート直下の `autoresearch.sh` を `test/bench/avr/autoresearch.sh` へ移動した。
  `src/definition/` の手書き2本（svid→PRNマップ、CAMF A3提供者名）も `src/definition/manual/` へ移し、直下は生成物だけになった — 生成器の `extra_headers`、`_index.h` のinclude、`greptile.json` / `.codacy` の除外パターン（`src/definition/*.h`）を追随させた。
- **手書きテーブル2本の出所表記を修正**: `qzss_dcx_camf_a3_provider_identifier.h` が「AUTO-GENERATED」と名乗っていたのを `HAND-MAINTAINED` に直し、`_index.h` の件数行を実態（138 generated + 2 hand-written）に合わせた。
- **メモリ・CPU最適化（第2弾）**:
  - ① デコード熱経路: `getBits` / `getBits64` を1bitループからバイト一括組み立てに変更した（全start×len組合せで旧実装と出力一致、OOB契約は不変）。
    UBXの250bit詰めをバイトスワップ直接ストアに（30万乱数フレームで等価検証）。
    AshFall/Weather/Floodの終端判定とNankai本文18Bを一括読み取りに、EEW予報区80bitをバイトスキャンに、SVID→PRNを数値直接参照に（AVRの共有バッファコピー+再パースを除去）。
    ホスト実測（bench-decode追加、`make -C test bench-decode`）: MT43 SEISMIC 3,250→1,642 / EEW 3,768→1,664 / MT44 2,136→1,474 cycles/通。
  - ② payloadのRAM削減: MT=44拡張部3構造体をunion化した（AVR −21B）。
    `Mt44Decoded` のミラー 4フィールドを削除した（`target_area_code` はserializerがex1から再計算）。
    追加楕円をB1精密化なしのコア型に（−16B）。
    `TsunamiEntry` / `NwPacTsunamiEntry` をビットフィールド化し、`NankaiPageBuffer::last_update_ms` を32bit化した。
    ATmega328P `-Os` 実測: `Message` 89B→84B（プリセット）、全カテゴリ+DCX/CAMF 242B→199B。
  - ③ EEW予報区を展開配列 `regions[80]`+`region_count`（81B）から電文そのままの `region_bitmap[10]`+`regionCount()`/`regionAt()`/`addRegion()` に変更した（破壊的変更、JSON出力は不変）。
    EEW有効化の `Message` 127B→84BでRAMペナルティがゼロになった。
  - ④ JSON writer: 静的キーバッファ（36B `.bss`）を廃止しFlashから直接書き出し、数値書き出しの `strlen` を除去した。
  - ⑤ 日付変換（AVRのみ）: `civil_from_days` のera除算を引き算ループに、`days_from_civil` をu16演算にした。
    1970..2400の全日で旧実装（Hinnantオラクル）と完全一致する `test_time_equivalence.cpp` を追加した（+2,405アサーション）。
  - ⑥ 非AVRも定義テーブルの共有断片プールを使う: 生成コードをAVR/非AVR同一テキストに統一し `FlashString.h` に非AVRアクセサ一式を追加した。
    hostバイナリ実測 −129,618B（全カテゴリ+両言語）。
    ラベルは `gen_label_dump`（1,409,708 lookup）のハッシュがAVR/host両方で `labels.golden` と完全一致し、AVR側のセクション配置は不変だった。
    AVRベンチ実測（`make -C test bench`）: Uno Flash 15,738→15,622B / SRAM 142→108B、Mega LTO Flash 144,444→144,134B / SRAM 892→858B。
  - ⑦ テスト修正: `test_json_wellformed` の `JsonCheck` が `const char*` からの一時 `std::string` をメンバ参照に束縛して全程の終わりで破壊されるdangling referenceを持っていた（非AVR表のfactoringがヒープレイアウトを変え、LTO構成で顕在化）。
    入力文字列をループ内変数に置いて寿命を確保した。
- **無効カテゴリのpayload型をコンパイルから外した（AVRのSRAMを解放）**: `EewData`（`regions[80]` を含む105B）と `HypocenterData` を `AZARAC_ENABLE_EEW` / `AZARAC_ENABLE_HYPOCENTER` でガードし、既存の `NankaiData` と同じ扱いにした — struct定義、`Mt43Data::ActiveType` の列挙子、
  `storage_size_` の `sizeof`、`getEew()` / `getHypocenter()`（const / 非const計4定義）、`typeFor<…>()` の特殊化。
  AVRプリセットは既定で両方0なので `Mt43Data` のpayload枠は128B → 88B、`Message` は144B → 104B（avr-gcc `-Os`、ATmega328Pで `sizeof` を実測）。
  効くのはEEWの `regions[80]` だけで、`HypocenterData`（22B）は他カテゴリの最大値（津波 / 北西太平洋津波の67B）を超えないため単独では0Bの削減。
  `internal/DedupWindow.h` が参照する津波・気象・洪水・海上のpayloadはdecode設定と無関係にdedupが使うのでガードしない。
  decoder / serializerの呼び出し側は元からすべて `#if` 内だったが、テスト（`test_message_struct` / `test_json` / `test_json_wellformed` / `test_realdata`）と `examples/filter_by_category`・`examples/with_sntp` のEEW / 震源のcaseにガードを足した。
  `AZARAC_ENABLE_EEW=0` / `AZARAC_ENABLE_HYPOCENTER=0` の `make -C test macro` は13マクロすべて通る。
- **JSONの値リテラルもFlashへ移した**: `wf_s` に `JsonKey` の値を受け取るオーバーロードを足し、 `"invalid_mt43"` / `"unsupported_category"` / `"unsupported_msg_type"` / `"invalid_mt44"`、 `arrival_status` の4語（`arrival_estimated` / `arrived_or_unknown` / `no_information` / `unrecognized_code`）、
    DCXの `dcx_type` ラベル（`NULL` / `L_ALERT` / `J_ALERT` / `LOCAL_GOV` / `OUTSIDE_JAPAN` / `UNKNOWN`）を `AZARAC_KEY(...)` 経由にした。
  あわせて `QZQSM,` の先頭一致を `strncmp` から `AZARAC_STRNCMP_P`（AVRは `strncmp_P(a, PSTR(b), n)`、非AVRは `strncmp`）にした。
  AVRの実測（`make -C test bench`）: Unoの `.data` 88B → 30B（残るのはallocatorのグローバルとframerのvtable 2つ）、フラッシュ +194B（14,276B → 14,470B）。
  Mega + DCX/CAMFは `.data` 234B → 44B、フラッシュ +154B（146,518B → 146,672B）。
  JSONの出力バイト列は不変（`test/json/*` の期待文字列テストがそのまま通る）。
- **JSONのキーをFlashへ移した（AVRのSRAMを大きく解放）**: `wf_u` / `wf_u64` / `wf_x` / `wf_deg` / `wf_s` / `wf_v` / `wk` / `writeDHM` / `writeLatLon` のキー引数を `std::string_view` から `internal::JsonKey` に変え、呼び出し側は `AZARAC_KEY("key")` で包む。
  AVRでは `PSTR`（avr-libc）でリテラルをその場で `__progmem__` のstatic配列にし、長さは `sizeof` で決まる（実行時のNUL走査も切り詰めも無い）。
  非AVRでは素のポインタと長さになるだけで出力は不変。
  `JsonKey` は生の `const char*` から暗黙変換できない（`explicit`）ので、包み忘れはホストのコンパイルで落ちる — ホストのリテラルはRAMにあるため、包み忘れはホストでは正しく動いてAVRだけ文字化けするからだ。
  書き出し時はキーを `JsonWriter.cpp` の40Bの共有バッファ（`AZARAC_KEY_BUF_SIZE`）へ1度だけ写す: ラベルは呼び出し側で `internal/FlashString.h` の共有バッファへ既に展開済みで、同じバッファを使うとキーのコピーがラベルを壊す（`wf_s` はキー→ラベルの順に書く）。
  `keys::note` 等の共有キー定数は `AZARAC_KEY("note")` に置き換えて削除した。
  理由: avr-libcのリンカスクリプトは `*(.rodata*)` を `.data` に含めるため、JSONのキーリテラルはそのままSRAMに載っていた（Unoの `.data` 564Bのうち約537Bがキー、MegaのDCX/CAMF構成では約1.8KB）。
  実測（`autoresearch.sh`、値リテラルのFlash化まで含めた最終値）: Unoプリセット（SEISMIC/TSUNAMI、JA、LTOリンク）RAM 640B → 146B（data 564 → 30、bss 76 → 116 = キーバッファ40B）、フラッシュ13,546B → 14,470B（+924B）。
  Mega（DCX/CAMFをオプトイン、LTOなしリンク）RAM 3,714B → 896B（data 2,902 → 44）、フラッシュ144,806B → 146,672B（+1,866B）。
- **AVRでSRAMに落ちていた補助テーブルをFlashへ移した**: `internal/DcxHelper.cpp` の半径表（`radius_table_m` → `RADIUS_TABLE`、128B）とB4レイアウト表（`B4_LAYOUTS` → `B4_LAYOUT_TABLE`、585B）は `const` の配列だが、avr-libcのリンカスクリプトが `.rodata` を `.data`（SRAM）へ含めるため、
  そのままSRAMを食っていた（MegaのDCX/CAMFリンクで585Bは `0x800227`、128Bは `0x800470`）。
  新設の `AZARAC_PROGMEM_NEAR`（AVRでは `PROGMEM`。読み出しが16bitの `AZARAC_PGM_READ_*` で届く低いprogmemクラスタに置く。`AZARAC_PROGMEM` は64KiB超のデバイスで `.text.azaraC.<N>` へ行きfarアクセサが要るので使わない）を付け、読み出しを `AZARAC_PGM_READ_DWORD` / `AZARAC_PGM_READ_BYTE` に変えた（非AVRでは通常のロードで、同じ経路がホストテストと `pgm-stub` で実行検証される）。
  B4の表は行（13B）をbyte単位で読むため、`static_assert` でパディング無しを固定した。
  名前を `_TABLE` で終わらせているのは `autoresearch.sh` の「定義テーブルがRAMに落ちていない」ゲート（`AVR_TABLES_IN_RAM` / `MEGA_TABLES_IN_RAM`）に載せるため — 従来この2表は `_POOL`/`_TABLE` で終わらない名前だったのでゲートを素通りしていた。
  あわせてハーネスはnear-Flash表（CRC24Qの3×16B、半径表、B4レイアウト表）の最高アドレスを `avr-nm` で採取し、64KiBの16bit窓内にあることをゲートする（`MEGA_NEAR_SYM_ADDR`。1つでも窓の外へ出ると `pgm_read_*` が黙ってゴミを返し、CRC不一致で全フレームが落ちる）。
  `UNO_RAM_BYTES` / `MEGA_RAM_BYTES` の上限は新しい実測値（146B / 896B）へ下げた。
  同じ理由で、`json/JsonWriter.cpp` の16進表（`HEX_CHARS` 17B）はFlashへ移さず表をやめて三項演算（`n < 10 ? '0' + n : 'A' + n - 10`）にした: 16エントリの表は畳まれないビルドでは `.data` を食い、畳まれるビルドでもFlashに17B残るうえ、`pgm_read_byte` にすると最適化が効かなくなる。
  実測（ATmega328P + `-flto`、Uno実リンク、stage 4と同じレシピ）: 表をFlashへ置いた場合13,982Bに対し13,546B（＝表を畳んでいた元の実装と同値）。
  出力バイト列は不変。
- **コメントを整理**: `src/`・`test/`・`examples/`・`scripts/`・CIのコメントから、コードの復唱・作業経緯・重複した説明を削った。
  途中で折り返していた行は1行にまとめ、長い場合は句点で改行する（文の途中では折り返さない）。
  仕様参照・ビット配置・契約・実測値とその結論は短くして残した。
  生成ヘッダのコメントは手で直さず `scripts/gen/gen_definitions.py` のテンプレートを7行 → 3行に縮めて `src/definition/*.h`（138ファイル）を再生成した（azarashi 0.17.1で再現）。
  コード・文字列リテラルは不変で、ホストテスト414件 / 10,471アサーションが通る。
- **`Parser` のコピー・ムーブを禁止（破壊的変更）**: `Parser` は4KBのdedupテーブルと南海トラフのページバッファを実体で持ち、`_custom` は呼び出し側が所有するframerを指す。
  複製はSRAMを二重に消費しframerも二重所有になるため、コピー/ムーブのコンストラクタと代入演算子を `= delete` にした（`Parser p2 = p;`、値渡し、コンテナへの格納はいずれもコンパイルエラー）。
  あわせて `feed()` の復号先を局所 `Message` から呼び出し側の `out` に変え、1フレームあたり `Message`（当時のホスト・全カテゴリ + DCX/CAMF構成で288B。現在は240B）1個ぶんのスタックとコピーを削った（worst-caseスタック: host `-Os` 1,112B → 808B、AVRプリセット `-Os` 414B → 259B。`-fstack-usage` のcall graph合計）。
- **CRC-24Qを4bit表（ニブル表）に置き換えた**: ビットごとの `crc <<= 1` ループを、hostは32bitの `constexpr` 表、AVRは3分割したPROGMEMのバイト表（3×16B）＋ 3バイトで持つ24bitレジスタで、4bit単位に書き換えた（AVRで32bitシフトがLSR/RORの回転ループに展開されるのを避け、ループ回数を従来の1/4にするのが狙い）。
  `bit_len & 3` の端数は表の対象外なのでビット直列のまま処理する。
  旧実装との等価性は4,000ケース（ビット長0〜256の乱数）でビット直列の参照実装と一致（不一致0）することを確認した。
  AVRのフラッシュは `crc24q` のコード142B ＋ 表48Bの +190B（実測: Uno 17,936B → 18,126B、ATmega2560 145,802B → 145,992B。avr-gcc `-Os`、差はどちらの構成でも同じ。デコード結果とSRAMは不変）。
- **DCXの角度・半径の出力を整数演算にした**: `main_ellipse`・B1補正（`c1_lat_offset_deg` など）・`hazard_center` の `delta_*`・`additional_area.ellipse` のlat/lon・semi-axes・azimuth・deltaを、`double` を経由する `wf_d` から新しい `wf_deg` に置き換えた。
  AVRの `double` は24bit仮数（約7.2桁）で、6桁精度の角度はhostと下位桁が一致しない（同じ電文でもボードによってJSONが変わる）。
  値が10の累乗を分母とする整数（マイクロ度・ミリ度）であることを使い、商と余りだけで組み立てる（小数部は分母の桁数ぶんゼロ埋め）のでfloat/doubleを一切通らない。
  出力バイト列は、従来の `wf_d` と60,026ケース（分母10⁶ / 10³、負値と小数点以下の桁を含む乱数）で一致（不一致0）することを確認した。
  あわせて `JsonWriter::writeEscaped` に、エスケープが不要な文字列（キーとほぼ全てのラベル）を1回の `write()` で出すfast pathを追加した。
- **AVR向けに定義テーブルのフラッシュ消費を削減（issue #35）**: 生成表は地域名の親（都道府県・市区町村）を1件ごとに繰り返していた（英語の地域コード表だけで63,064B）。
  `strategy.py` の `factor_parents` が、同じ表の中で4件以上に共通する最長の接頭辞／接尾辞（`北海道札幌市` の `北海道`、`Sapporo City, Hokkaido Prefecture` の ` City, Hokkaido Prefecture`）を「親」として切り出し、`<GUARD>_PARENT_POOL` に1回だけ置いて、行には親の添字（`0xFF`＝親なし）を持たせ、
  参照時に `azarac_pgm_join_z` が既存の共有RAMバッファ内で連結する。
  切り出した親自身も同じ規則で再帰的に切り出せる（2段目。` City, Hokkaido Prefecture` → ` City, ` ＋ `Hokkaido Prefecture`）。
  binary_search / array戦略の全表が対象。
  switch戦略は行を持たないため、共有断片のオフセットをcase本体に定数として埋め込む。
  あわせて行から `len` を削除した（プールはNUL区切りなので長さは `azarac_pgm_len` が取る）。
  - 2段目は呼び出し側に分岐と `azarac_pgm_join3` を足すため、表の削減がそのコード（実測60〜130B/呼び出し）を上回る表だけ採用する（閾値128B）。
    閾値が無いと既定AVR構成のリンクが122B増えることを実測で確認した。
  - 行の増分は「親を持つ行は常に1B増える」で見積る — AVRの行形（`{id, parent, offset}` / `{offset, parent}`）に長さフィールドは無く、親バイトを相殺できるものがない（AVR-GCCは行構造体にバイト整列を与える）。
    旧見積りは「子が255Bを超えるときだけ増える」としていたので、子が短い表では親バイトを無料と数えていた。
    そのため圧縮が得に見えていた5表（EEW予報区JA/EN・都道府県・火山名・CAMF A2国地域名）が圧縮をやめ、合計 −289Bになった。
  - **非AVR（ホスト）側の出力は従来どおり非圧縮**（issue #35の方針）。
    ラベルは全1,409,708照会でAVR経路・ホスト経路ともバイト単位一致（`test/bench/avr/labels.golden`。断片の結合順をわざと入れ替えるとこのゲートが落ちることも確認済み）。
  - 実測（全カテゴリ + 日英、`test/bench/avr/measure_tables.py`）: 474,484B → 300,827B（−36.6%）。
    最大の単一リテラルが63,064B → 20,944Bになり、avr-gccの1オブジェクト上限32,767Bを下回ったため、ATmega2560でDCX/CAMF・火山・降灰の各カテゴリがビルド可能になった（従来は `size of variable is too large` でコンパイル不可）。
    実際にATmega2560向けにDCX/CAMF + SEISMIC/TSUNAMIを日英（`AZARAC_LANG_JA=1` / `AZARAC_LANG_EN=1`）でリンクすると、フラッシュ184,998B（上限262,144B）・RAM 3,970B（上限8,192B）に収まり、DCX/CAMFの定義テーブル100シンボルがすべてFlash側に置かれることを `avr-nm` で確認した（2026-10実測。`autoresearch.sh` stage 5と同じリンク条件。日本語のみの構成は144,804B / 3,714Bで、下記「AVR向けプリセット…」の値と同一。日英と日本語のみは言語構成が違うだけの別測定）。
    定義テーブルは各プールが64KiB未満に収まるため、16bitのFlashオフセットで扱える範囲も広がった。
  - **SRAMは不変**: Uno実リンクでdata+bss = 702B（変更前と同じ。この改修時点のベースラインで、JSONキーと補助テーブルのFlash移行後は204B）、表がRAMに落ちていないことを `AVR_TABLES_IN_RAM=0` で確認。
    結合は `internal/FlashString.h` の共有バッファ（800B、既存）内で行う。
    既定AVRプリセット（SEISMIC/TSUNAMI、JA）は表+プール3,011B・リンク後フラッシュ17,930B → 17,656B。
- **ATmega2560などFlashが64KiBを超えるAVRで定義テーブルを正しく参照できるようにした**: テーブル（DCX/CAMFを含む構成では ~140KB）はリンク時に0xFFFFより上へ配置され、16bitのPROGMEMポインタでは届かない（実測: 195シンボル中138個が64KiB超。従来のコードは `lpm` のみで `RAMPZ` を一切使わなかった）。
  `internal/FlashString.h` がデバイスに応じてアドレス方式を切り替え、`FLASHEND > 0xFFFF` では配列のアドレスを `pgm_get_far_address`（`AZARAC_PGM_PTR`）で取り、読み出しを `pgm_read_*_far` / `memcpy_PF` / `strncpy_PF` で行う（64KiB以下は従来どおり16bitポインタのまま）。
  プール内のオフセットは16bitのままで、行の形（`{id, parent, offset}`）も不変。
  `make -C test pgm-stub` は64KiB超のデバイスを装う（`FLASHEND=0x3FFFF`）のでfar経路はホストで実行検証され、ラベルは全1,409,708照会でホスト経路と一致する。
- **AVR向けプリセットはチップ名でカテゴリを切り替えなくなった（破壊的変更: MegaのDCX/CAMFはオプトイン）**:これまでFlashの大きいボード（`AZARAC_AVR_LARGE_FLASH`: `ARDUINO_AVR_MEGA2560` / `__AVR_ATmega2560__` / `__AVR_ATmega2561__`）ではDCX/CAMFも自動で有効にしていたが、
  既定は全AVRで0（SEISMIC/TSUNAMIのみ、Unoと同じ）にした。
  DCX/CAMFは `-DAZARAC_AVR_LARGE_FLASH=1`（従来の名前。明示していた既存コードはそのまま動く）または `-DAZARAC_ENABLE_DCX_CAMF=1` を渡した時だけ有効になり、Flash 145KBを使う構成は自分で選ぶことになる。
  ATmega2560 + DCX/CAMF + SEISMIC/TSUNAMIを日本語のみ（`AZARAC_LANG_EN=0`、AVRの既定）でリンクした実測はフラッシュ144,804B（上限262,144B）・RAM 3,714B（上限8,192B）で、DCXの定義テーブル90シンボルは全てFlash側（RAM 0。日英構成は184,998B / 3,970B — 上記「フラッシュ消費を削減」の項）。
  `AZARAC_FLASH_BUF_SIZE` の自動選択はカテゴリ既定の解決後に評価されるので、`-DAZARAC_ENABLE_DCX_CAMF=1` でも800Bになる。
  他10カテゴリは大容量ボードでも無効のまま（全て同時にすると250,138B/262,144Bでユーザーコードの余地が12KBしかない）。
- **JSONから `double` を排除（`wf_d` / `writeDouble` を削除）**: 津波の高さの境界（`height_lower` / `height_upper`）を10分の1 mの整数と `wf_deg`（分母10）に置き換えた。
  出力文字列は従来と同一（`0.2` / `1.0` / `3.0` / `5.0` / `10.0`、境界なしは `null`）。
  従来の `writeDouble` は非有限値を `null` にするガードを `v > 1e308` で書いていたが、AVRの `double` は32bitなのでこの定数は範囲外（`inf`）になり、NaNしか検出できず `-Woverflow` も出ていた（hostとAVRで挙動が違う）。
  利用者が高さの2箇所だけだったため関数ごと削除し、これでJSON経路にfloat/doubleが1つも残らない。
  実測（`--gc-sections` のリンク後）: Uno 18,126B → 16,874B・RAM 702B → 654B、ATmega2560プリセット145,992B → 144,804B・RAM 3,762B → 3,714B（`test/bench/avr`）。
  `writeDouble` の単体テスト9件は対象関数の削除に伴い削除し、代わりに高さコード1〜6と508の全区分を1通ずつ組むJSONテストを追加した。
- **AVRビルドで範囲外の浮動小数点定数をエラー化（`-Werror=overflow`）**: `autoresearch.sh` のAVRビルド3箇所（全カテゴリ・Unoプリセット・Megaプリセット）に追加した。
  AVRの `double` は32bitなので、hostでは有効な定数（`1e308` など）がAVRでは `inf` になり、比較が黙って成立しなくなる。
  追加時点でこれに該当したのは `src/json/JsonWriter.cpp` の1箇所のみで、他の11 TUは緑だった。
- **AVRベンチのUno実リンクをLTOにした**: Arduino AVRコアは `-flto -fuse-linker-plugin` でコンパイル/リンクするので、同フラグをUnoステージ（`AVR_LTO`）にも入れ、実測が実機どおりになるようにした。
  Uno: フラッシュ16,874B → 13,546B、RAM 654B → 640B。
  **Mega（DCX/CAMF）ステージには入れていない** — avr-gcc 7.3 + LTOでは生成ヘッダの関数ローカルなリテラル静的変数から `.text.azaraC.<n>` 属性が落ち、`.rodata`（＝リンカスクリプト上 `.data`、実体はSRAM）へ移動する。
  同一レシピの実測で `.data` 2,902B → 28,230B（MegaのSRAMは8,192B）で、far-Flash配置の検証が成立しないため。
  MegaのSRAMも `MAX_MEGA_RAM_BYTES`（3,714B）でゲートするようにした。
  （その後、生成器側の修正で関数ローカルのリテラルはLTOでもFlashに残るようになったので、`autoresearch.sh` はステージ5bとして同じMega構成をLTOでも組み、`MEGA_LTO_FLASH_BYTES` / `MEGA_LTO_RAM_BYTES` として報告する。ゲートにはせず、LTO無しとの差が64Bを超えたときだけ報告する。測定のためリンク時のみ `--defsym=__DATA_REGION_LENGTH__=0x8000` でデータ領域を広げる。修正後の実測: LTO無し3,714Bに対し3,718B。詳細は下記「switch戦略のラベルがLTOでSRAMへ落ち」の項。）
- **Arduino Mega 2560のコンパイルを必須ジョブに昇格**: `arduino-compile-required` にMega（`arduino:avr:mega`）を加え、`arduino-compile-extended` から外した（WiFi/SNTP例はAVRでは `WiFi.h` が無いので従来どおりスキップ）。
  これでAVRはUno（`basic_*` 3例）とMega（WiFi/RTOS以外の全例）が既定カテゴリで必須になる。
- **リリースワークフローの `run:` から式の直接展開を外した**: `release.yml` の `slsa-verifier` ステップでprovenanceの成果物名を `${{ ... }}` として直接埋めていたのを、他ステップと同じく `env: PROVENANCE` 経由の参照（`"$PROVENANCE"`）に統一した。

### Fixed

- **Printシムが実コアと食い違っていた**: ホスト用 `PrintShim.h` とAVRベンチのシムが `write(const char*, size_t)` をvirtualにしており、実コア（virtualは `write(const uint8_t*, size_t)` のみ）では上書きされない経路をホストテストが通してしまっていた。シムを実コアの形に揃え、シンク側は `write(const uint8_t*, size_t)` のoverrideと `using Print::write;` に統一した（`src/json/JsonSerializer.cpp` の呼び出し側も同じ形に統一）。
- **cppcheckが `avr_layout_probe.cpp` の `#error` で落ちていた**: `-DAZARAC_NANKAI_MAX_PAGES=63` を渡すとcppcheckは「ユーザー定義あり」とみなして `#error` を報告する（`Preprocessor::handleErrors` の `showerror = !userDefines.empty() && !force`）。`avr-g++` 専用の `test/tools/avr_layout_probe.cpp` に `__AVR__` ガードを足した時点で、`static-analysis` ジョブが `preprocessorErrorDirective` で常時赤になった。
  `CPPCHECK_OPTS` と `scripts/analysis/cppcheck_summary.py` に `-D__CPPCHECK__` を追加し、ガードを `!defined(__AVR__) && !defined(__CPPCHECK__)` に変更した。`--suppress=preprocessorErrorDirective:tools/avr_layout_probe.cpp` ではなく定義で外すのは、抑制がファイル単位で将来の本物の `#error` 退行まで隠すため（`-D__CPPCHECK__` はcppcheck自身のselfcheckも使う慣用句で、実コンパイラに対してはガードが生きたまま残る）。
- **Wi-Fi例の非ESP32ガードが効いていなかった**: `#error` が `#include <WiFi.h>` の後ろにあり、`WiFi.h` を持たないボードでは先に「ファイルが無い」エラーになっていた。ガードをincludeの前に移し、CIのWi-Fi例スキップ条件をボード名の列挙からFQBNの `esp32:` 判定へ揃えた（拡張マトリクスの `Arduino GIGA R1 WiFi` と `RP2040 Pico W` が落ちていた）。
- **CIのcppcheckレポートとカバレッジが空だった**: `check` / `check-strict-compile` の末尾が `$(MAKE) clean` だったため、`check-xml` が書いた `cppcheck_report.xml` と `coverage` の `*.gcda` を後続ステップの前に消していた（`static-analysis` のサマリーがERROR行のみ、`coverage` のgcovrがデータ0件で100% 表示）。
  後始末を解析ビルドが作るlibの `.o`/`.d` の削除に限定した。`make -C test coverage` が `coverage_report.json` と `coverage.xml` も書き出し、`clean` はその2つを消さない（`ci.yml` の重複したgcovrステップは削除）。
- **`getMillis()` がTUごとに別カウンタを持っていた**: `static inline`（内部リンケージ）のためヘッダをincludeしたTUごとに `s_last` が別実体になり、複数TUから呼ぶと相互に矛盾する時刻を返す潜在問題があった（本番呼び出しはParser.cppのみで顕在化せず）。
  `inline`（外部リンケージ）に変更しC++17で `s_last` を単一実体化。`test_time_irq` に第2 TU（`test_time_irq_b.cpp`）を追加し、折返し後に別TUから呼んでも同じ上位ビットを観測することを固定（static inlineでは失敗する）。
- **南海トラフの訓練/実警報が同時進行すると互いに追い出し合っていた**: `NankaiPageKey` がRc（訓練=7/実警報=2）を区別するため別バッファを要求するが、ホスト既定 `AZARAC_NANKAI_BUFFERS=1` では交互到着のたびにLRU追い出しが起き、どちらも永久に集約できなかった。
  ホスト既定を2に変更（`sizeof(Parser)` 5,464→6,624 B、`static_assert` 上限5500→6700）。AVRプリセットはNANKAI自体が無効で、有効化時の既定は1のまま。`findOldestBuffer` の到達しない空バッファ分岐を削除し、追い出しは「最古・同値は先頭スロット」（真のLRUではない）であることをコメント明記。
  `test_nankai_e2e.cpp` に完全交互到着で両事象が完成する回帰（BUFFERS>=2）と、BUFFERS=1の限界を固定する回帰を追加。3イベント以上の交互到着は依然未完成＝DoS限界はdocsに明記（60sタイムアウトがメモリ上限を保証）。
- **南海トラフ集約テキストの不正UTF-8がJSONへ素通りしていた**: 衛星由来の生バイト（CRC通過後の破損・非UTF-8ペイロード・ページ打ち切り時の末尾切断）が `text_utf8` に無検証で出力され、厳格な下流JSONパーサが文書全体を拒否しうる状態だった（生バイトがJSON文字列に入る経路はここ1箇所）。
  `writeStrUtf8` を追加し、UTF-8として検証して不正シーケンスをU+FFFDに置換する（Python `errors="replace"` と同じmaximal subpart規則）。出力は常にvalid UTF-8。`AZARAC_ENABLE_NANKAI` ガード付きでAVRプリセットのFlashは不変。テーブルラベルは従来どおり `writeStr` を使い、全JSONへのper-byteコスト増を避ける。
  `test_json_utf8.cpp` にPythonオラクル一致・全1/2バイト入力の出力妥当性網羅（約6.5万）・独立コードポイント検証器・JSONエスケープ併存・Nankai E2Eを追加。AVR（atmega2560, NANKAI=1）コンパイル成功。
- **2³² ms以上の無受信期間で時刻の折り返しを取りこぼし得た**: `getMillis()` は呼び出し時にしか `millis()` の折り返しを数えないため、受信が無いまま49.7日以上経過すると古いdedup/Nankai履歴が「最近」に見え、同一警報を抑止し得た。
  `Parser::updateClock()` を追加し、`loop()` から受信の有無に関係なく64 bit時計を観測できるようにした。`postDecodeAt()` のepoch guardを `observeClock()` に共通化し、`updateClock()` も同じ経路を通る。examplesの各ループから呼ぶ。ESP32は64 bitの `esp_timer_get_time()` を直接使うため、この取りこぼしは起きない。AVRなど32 bit `millis()` のみの環境では、周期的な観測が無いまま2³² ms以上空く場合の限界をdocsに明記した。
  `test_parser_clock.cpp` に、フレームを挟まずに世代境界を観測するとNankaiバッファが消える回帰を追加した。
- **49.7日連続運転で古いdedup履歴が偽重複化し警報を抑止していた**: epoch guardが「呼び出し間隔 ≥ 2^32 ms」でしか発火せず、連続受信ではエントリの年齢が2^32 ms（約49.7日）を超えて符号なし差分が小さく巻き戻り、古い履歴が「最近」に見えて新規警報を抑止していた。
  guardを `now_ms64` の上位32 bit（世代）比較 `(now_ms64 >> 32) != (_last_now_ms >> 32)` に変更。世代境界を跨げば経過が短くても履歴を捨て、再通知に倒す（安全方向）。RAM増分ゼロ・`DedupFilter::Entry` 8 B / `static_assert` 維持。`Dedup.cpp` の年齢差コメントも実態（世代内では49.7日未満で厳密）に修正。
  `test_parser_clock.cpp` の折返しテストを「世代境界で再通知」に意味反転し、1 ms gapでの世代跨ぎ・49.7日連続運転後のstale事象再通知の回帰を追加。
- **暦に存在しない日付を黙って別月日へ正規化していた**: `resolveTime` の検証がday>31までで月別日数・閏年を検査せず、2/30・4/31・平年2/29を `days_from_civil` の正規化で別月日（例: 2/30→3/2、12月基準の2/30→翌年3/2）として出力していた。MDHM経路は未来クランプが無く最大 +76日のずれも生じていた。
  月長判定（`daysInMonth`、閏年込み・SRAM不使用）を追加し、暦外日付は `unix_time=0` の未解決（生フィールド保持）に倒す。DHMの候補ループは暦外候補を失格させ、stale分岐は有効月だけを遡るbounded searchに置き換えて未来日付の生成を防ぐ。検証済み日付の正規化ラウンドトリップは削除（`civil_from_days` 1回減）。
  `test_time_resolution.cpp` に暦外日付の未解決化・閏年2/29・年跨ぎ・未来日付防止の回帰と、約1.4万組の不変条件掃引（解決済みなら月日が化けない／DHMはbase+3日を超えない）を追加。`make -C test avr-layout` 3構成コンパイル成功。
- **津波/北西太平洋津波のリスト終端判定がPlのみだった**: IS-QZSS-DCR-017 Table 4.1.2-21 / 4.1.2-26は未使用エントリをTa/Th/Plすべて0と定めるが、Pl=0だけで打ち切っていたため、Pl=0かつTa/Th非0の非準拠電文で後続エントリを取りこぼしていた（azarashiはエントリ全体で判定）。
  津波は26 bit・北西太平洋は28 bitのエントリ全体の0で終端するよう修正。仕様準拠電文の出力は変わらない。`test_tsunami_list.cpp` に全0終端／Pl=0&Ta≠0は終端しない／Pl≠0&Ta=Th=0は含む、の回帰を追加した。
- **J-Alert市区町村コードリストの順序が送信順と逆だった**: `decodeCityCodeList` がex9をLSB先頭で読んでいたため、4コードの並びが送信順（MSB先頭、IS-QZSS-DCX-004 §4.2.4.2.2）と逆転していた（例: 送信 [札幌中央, 千代田, 大阪, 那覇] → [那覇, 大阪, 千代田, 札幌中央]）。
  `ex9 >> (48 - i*16)` で送信順に復号するよう修正した。JSON `data.jalert_target.cities[]` の順序も送信順になる（`schema_version` 2のまま、キー構造の変更なし）。
  期待値が実装のLSB仮定を写していた `test_dcx_helper.cpp` / `test_error_handling.cpp` を送信順に直し、`test_azarashi_dcx.cpp` にazarashi 0.17.1生成の実電文4件（1/2/3/4コード）の順序回帰（struct＋JSON）を追加した。
- **時計の小さな後退でdedup/Nankai履歴が全消去されていた**: `getMillis()` はFreeRTOSのマルチコアで数ms逆行し得るが、epoch guardが任意の後退で履歴を捨てていたため、生きた警報が再通知され、集約中の南海トラフも消えていた。
  1秒以内の後退は最終観測時刻に丸め、1秒を超える後退だけ履歴を捨てるようにした。
  1 ms後退で抑圧が続くこと、大きな後退の後に新しい基準で窓が満了すること（旧高値へ丸めて凍結しないこと）を `test_parser_clock.cpp` に追加した。
- **`Parser::_last_now_ms` がdedup/Nankai無効でも8 B残っていた**: epoch guardの `#if` と同じ条件でメンバを囲み、`reset()` の初期化も揃えた。
- **カテゴリ無効時に `examples/filter_by_category` がコンパイルできなかった**: `SeismicData` / `TsunamiData` / `TyphoonData` の利用が `AZARAC_ENABLE_*` でガードされておらず、AVRプリセット（TYPHOON=0）のMegaと全カテゴリ無効のArduino ZeroでCIが赤になっていた。各caseを型と同じマクロで囲んだ。
- **Codacyの新規指摘2件**: `test_decoder_dcx.cpp` の `memcpy` 4箇所を `std::copy_n(bits, sizeof(frame.bits), frame.bits)` に置き換え（コピー長を宛先サイズから取る）、新規スクリプト `hash_nankai_vectors.py` のshebangを削除した（CIは `python <path>` で起動し、Codacyはgitの実行ビットを見ないため）。
- **`compactText()` 後の `getTextLength()` がページ割り付けを読んでいた**: `compactText()` は受信済みページを `aggregated_text` の先頭へ詰めるが、`received_bitmap` と `total_pages` は受信済みのままなので、`getTextLength()` が `p * TEXT_PER_PAGE` の位置からページ長を足し、ページ境界をまたいだ本文を誤って読んでいた（`getNankaiBuffer()` 経由の長さが `aggregated_len` と一致しない）。
  `compacted` フラグを追加し、`compactText()` 後は先頭からの連続文字列として長さを返す。
  `clearAll()` でフラグを戻すため、バッファ再利用後の再受信は従来のページ経路に戻る。
  回帰は `test_nankai.cpp` に「全ページ」「欠落ページあり」「clearAll後の再受信」、`test_nankai_e2e.cpp` に27ページ集約とNUL途中終端で `getNankaiBuffer()->getTextLength() == aggregated_len` を追加（ホスト350ケース / 15,164アサーション）。
- **`feed()` が `false` のとき壊れたフレームの `svid` が残っていた**: `Decoder::decode()` が `out.clear()` の直後に `out.svid = frame.svid` を書いていたため、CRC不正で復号を中止してもNMEA/UBXヘッダ由来の `svid` だけが `out` に残っていた。
  CRC失敗時に `out.svid` を0に戻すようにした（書き込みをCRC検証の後ろへ移すと `frame` がCRC呼び出し越しに生き、host `-Os` の `Decoder::decode` スタックが80B → 96Bに増えるため）。
  `feed()` の `out` 契約を「`true` を返したときだけメッセージとして読める（`false` 時は未定義。診断用の `unsupported_reason` を除く）」と `Parser.h` / `docs/api-reference.md` に明記した。
  `Message` の一時オブジェクトを経由する案は、CHANGELOG記載のスタック削減（host 1,112→808B / AVR 414→259B）を戻すため採らない。
  回帰は `Decoder` 単体（CRC不正で `svid == 0`）と `Parser` 経由（正常→CRC不正で直前の値も残らない）を追加（ホスト351ケース / 15,147アサーション）。
- **dedupのLRUが空エントリを基準に初期化されていた**: `DedupFilter::isDuplicate()` の追い出し対象 `oldest` を `&set[0]` で初期化していたため、set[0] が空だと `last_seen_ms`（0）との差が巨大になり、有効エントリが比較で選ばれない。
  空きwayがある場合は `free_slot` を使うので実害は無かったが、最初の有効エントリで初期化するよう直した。
- **`Message` のコピー ctorが `payload_storage_` を初期化していなかった**: コピー元が `payload_type == Empty` のとき、コピー先のpayload領域が不定のまま残っていた（読み出し経路は無いが、静的解析の未初期化警告になる）。
  メンバ初期化子で `payload_storage_{}` を値初期化するようにした。
  コピー元にpayloadがある場合は `copyPayloadFrom()` が上書きする。
- **EN専用ビルドで日本語ラベルが漏れていた**: `AZARAC_LANG_JA=0` / `AZARAC_LANG_EN=1` の構成でも、南海トラフの `info_code_label` が日本語（「巨大地震注意」など）を返していた。
  azarashiにEN版が無い日本語専用の表 `qzss_dcr_jma_information_serial_code` に言語ガードが無く、`AZARAC_LANG_JA` を切っても表がコンパイルされたままだった。
  生成器（`scripts/gen/gen_definitions.py`）に「DCR/JMA家族で `_en` 対応表が無いものは `AZARAC_LANG_JA` でガードする」規則を足し、生成ヘッダを再生成した。
  JA無効の構成では `info_code_label` は `null` になる（生コードの `info_code` は残る）。
  回帰テストは `test/json/test_json.cpp` で言語構成ごとに期待値を切り替え、修正を戻すとJA無効の構成で落ちることを確認済み。
- **AVRの1月/2月で日時解決が壊れる問題を修正**: `civil_from_days()` の月計算 `mp + (mp < 10u ? 3u : -9u)` は、AVRの16-bit `unsigned int` で `-9u` が65527になり、Jan/Febで `m=65537/65538` を作っていた。
  月を32-bitの `constexpr` helperに切り出し、`static_assert` でJan/Febの変換を固定した。
  `make -C test bench` が実 `avr-gcc` でこのTUをコンパイルするため、16-bit幅の退行はCIで落ちる。
  `test_time_equivalence` のオラクルも実装と同じ式を共有していたため、独立した月テーブルに変更した。
- **WindowsのテストロックとCIの補助を修正**: `test/Makefile` の複数行・非ASCIIのロックレシピがnative Windows makeからMSYS shへ渡る際に壊れ、`make -C test run` が起動前に失敗していた。
  ロックを `test/scripts/with-make-lock.sh` に移し、`$(USER_GOALS)` 全体をロック下の再帰makeに渡すようにした。
  `compare-realdata` をロック対象に追加し、`update-definitions.yml` のArduinoコンパイルにも `-std=gnu++17` を明示した。
  `NankaiPageBuffer` の契約（未完了バッファも返る）と実測サイズ（host 1,160B / AVR 1,157B）、`Mt43Data::initAs()` のサイズ検査、ESP32の `getMillis()` の制約もコード/ドキュメントに反映した。
- **レビュー指摘の修正（リポジトリ運用・CI・サンプル）**: `.gitignore` の `.vscode/` と矛盾して追跡されていた `.vscode/settings.json` / `.vscode/c_cpp_properties.json` の追跡を解除した（ローカルファイルは残る）。
  `test/` 4本のコメントに残っていたEWSS CAMF v1.1参照をv1.2に統一した（`src/` は2.0.0で更新済み。Issue 1.2はv1.1から節番号・内容が不変のため §番号はそのまま）。
  Arduino CLIのインストールと `core update-index` の3回リトライを複合アクション `.github/actions/setup-arduino-cli` に共通化し、`ci.yml` の2ジョブと `update-definitions.yml` の3箇所から置換した。
  CIサマリのextendedマトリクス件数 `expected=8`（ハードコード）は `slug:` フィールド（extended専用）の実数から動的に算出するようにした。
  `examples/error_handling` に、NMEAのSatellite ID 0–52がPRN 128–180に正規化されて通る契約外経路の注意コメントを追記。
  `examples/filter_by_category` のMT=43ブランチもMT=44と同じく `toJson()` でJSON出力するように対称化した。
- **レビュー指摘の修正（コア）**: `internal::getMillis()` が `noInterrupts()` の後に無条件で `interrupts()` を呼び、呼び出し側の割り込み禁止区間を破っていた問題を修正した。
  AVRは `SREG`、Cortex-Mは `PRIMASK` を退避・復元し、`test-time-irq`（`ARDUINO=1` / `__AVR__` のホストスタブ）で検証する。
  `NmeaFramer` は2桁でも6bitに収まらないSatellite ID 64–99を拒否する（0–52はPRN 128–180として通すが契約外）。
  `Parser.h` の `report_unix=0` の説明を実装（未解決）に合わせ、`Parser::feed()` のカスタムフレーマ経路で局所 `Frame` をゼロ初期化し、`IFramer::feed()` にFrameの全フィールドを埋める契約を明記した。
  UBXの `numWords` は実データに合わせて8/9のみ受理し（9はu-bloxが付ける余剰word）、10以上はコメントと回帰テストで拒否する。
- **FreeRTOS exampleの出力競合**: RXタスク（集約済み南海トラフ）とOutputタスクが同じ `Serial` に書いていたため、JSON 1通・統計行・起動行をFreeRTOSミューテックスで直列化した。
  キューは引き続き `Message` のバイトコピーで、payloadがtrivially copyableで所有ポインタを持たないこと（標準のコピー意味論ではなくオブジェクト表現のコピーとして扱う）、借用ポインタを持つ集約済み南海トラフを載せないことをコメント化した。
  `xTaskCreatePinnedToCore` を使うためESP32専用であることも明示した。
- **レビュー指摘（計測・サンプル）を反映**: `test/bench/avr/shim/Arduino.h` の `Print::print()` を実コア同様に `write()` へ流した。
  従来は空実装だったためLTOが `writeUint32` / `writeUint64` の桁変換など「出力を作る側」の処理ごと削除でき、計測したFlashが実スケッチより小さかった。
  これでJSONの区切り・`null`・エスケープ列の生リテラルが `.data`（SRAM）に現れたため、`writeRaw(Print&, JsonKey)` を追加して `AZARAC_KEY` 経由でFlashに置いた。
  最終実測（`make -C test bench`）: Uno 15,738B / 142B、Mega 148,552B / 892B、Mega LTO 144,444B / 892B。
  `examples/rtos_freertos` のミューテックスは `xSemaphoreCreateMutexStatic()` + `StaticSemaphore_t` にしてFreeRTOSヒープを消費しない。
  PRで追加した英語コメントは日本語に揃えた。
- **テスト・ドキュメント整理**: JSON DCXシリアライザのB4ブロックのインデントを直し、未使用の `has()` オーバーロードを削除した。
  テスト件数を418ケース / 10,500アサーションに更新し、NMEAのsvid範囲（64–99拒否、0–52は契約外）を `architecture.md` / `json-formats.md` に追記した。
- **NMEA `$QZQSM` のSatellite IDを仕様どおり2桁に限定した**: 仕様のSatellite IDはPRN下位6bitの2桁10進（IS-QZSS-DCR-017 §4.3.1 / DCX-004 §4.3.1、Table 4.3.1-1）で、azarashiも長さ2以外を拒否する。
  azaraCは任意桁数を受けていたため、3桁（例 `$QZQSM,100,…`）を通すと `| 0x80` の結果がPRN契約（181-191）の外の値（228）になり、`Frame::svid` にPRNでない値が載っていた。
  桁数を数えて2以外を拒否するようにした。
  あわせてテストヘルパ `makeNmeaQzqsm` がPRN（183-191）をそのまま3桁で書いていたのを、電文どおり下位6bitの2桁に落として書くよう直した（PRN 184 → `56` → 受信側で184に戻る）。
  3桁を受けることを前提にしていた `UBX: SFRBX sv56 pattern1 - Marine` の往復テストはこれで仕様どおりの電文になった。
- **AVRでA6/A7のオンセット時刻がa7=1094以上で誤っていた（16bit幅の静かな折り返し）**:`decodeDcx` は `(d->camf.a7 - 1u) * 60u` を `uint32_t onset_unix` へ足していたが、a7は `uint16_t` でAVRの `unsigned int` は16bitのため、この乗算は16bitで行われ `a7 > 1093` から65,535を超えて折り返していた（a7の範囲は1..10080。a7=10080なら604,740秒が14,916秒 = 週内の別の時刻になる）。
  `onsetOffsetSec()`（`static_cast<uint32_t>` で32bitに広げる）に切り出し、同じ式が16bitに戻ったらAVRビルドが `static_assert` で落ちるようにした（ホストの `int` は32bitなので、この欠陥はホストテストでは決して現れない）。
  境界の意味（a7=1094と上限10080 = 翌週の日曜23:59）は `test/integration/test_time_resolution.cpp` で固定した。
- **ドキュメントとコードの食い違いを修正**: `feed()` の戻り値（完成・成功・非重複の3条件、重複時は `out` をクリア）と `unsupported_reason`、`event_time` のビット範囲（`[21..40]`）、`version` とカテゴリ別のgetter（`getEew()` 等。`EewData eew` のような公開メンバは無い）をAPIリファレンスに合わせた。
  `_label_en` が付く条件（固定リテラルキーの `AZARAC_LABEL` のみ）、降灰の `arrival_time_label`、`ex_vn` の位置（J-Alertは `jalert_target.ex_vn`）、`unsupported_msg_type` / `unsupported_category` の条件もJSON仕様に合わせた。
  テスト件数（414 / 10,471）、`AZARAC_FLASH_BUF_SIZE` の既定（AVR既定64、非AVRでは未使用）、avr_stdシムの一覧、NankaiPageBufferのサイズ（ホスト1,168B / AVR 1,161B）、L1S規格の原本がリポジトリに無い旨も直した。
  `platformio.ini.example` のRegistryピンは `^2.0.0`（Registryの公開版）に更新し、install手順・AVRのオプトイン・`#define` ではなくビルドフラグで指定する点をREADME / getting-startedに追記した。
  examplesの `error_handling` / `with_sntp` の説明と出力例を実装に合わせた。
- **AVRで `AZARAC_FLASH_BUF_SIZE` の自動選択が一部カテゴリのラベルを黙って切り詰めていた**: バッファ長は有効カテゴリから選ぶが（`src/azaraC_config.h`）、ラベルは独立したガード（`src/definition/*.h`）で有効になる。
  選択連鎖が知っていたのはDCX/CAMF（800）・南海トラフ（540）・北西太平洋津波（80）だけで、緊急地震速報・震源（最長596B、`notification_on_disaster_prevention`）・火山（88B）・洪水（78B）は64Bに落ちていた。
  `azarac_pgm_view` は `AZARAC_FLASH_BUF_SIZE - 1` で切り詰めるため（しかもUTF-8の途中で切れる）、`-DAZARAC_ENABLE_EEW=1` のような設定では596Bのラベルが63Bになって返っていた（実測: 63B → 修正後596B）。
  連鎖に640（EEW/震源）と96（火山/洪水）の段を足し、`make -C test bench` に全カテゴリ組み合わせのゲートを追加した（`FLASH_BUF_OK`。既定プリセットのUno/Megaは値・RAMとも不変）。
  Uno（`ARDUINO_AVR_UNO`）で256Bを超える構成には `#warning` を出す（プリセットは64Bなので、長いラベルを持つカテゴリを有効にした場合だけ発火する。既存の `AZARAC_NANKAI_BUFFERS` 警告と同じ扱い）。
- **ラベル長ゲート（`check_flash_buf.py`）がフレーム内のORをANDとして読んでいた**: 生成ヘッダのガードは `(AZARAC_ENABLE_VOLCANO || AZARAC_ENABLE_ASH_FALL) && (AZARAC_LANG_JA)` のようにフレーム内がOR・フレーム間がANDだが、スキャナは開いているフレームのカテゴリを1つの集合に統合し、`needed` がその全要素の有効を要求していた。
  片方だけ有効な構成（`-DAZARAC_ENABLE_VOLCANO=1`）が選ぶ表を検査対象から落としていた（実測: 12,288構成中3,136構成で要求長を過小評価。`VOLCANO` のみの構成で47B → 58B）。
  フレームごとにOR集合を保って判定するようにし、最小余裕3B（Uno・`ASH_FALL`＋英語）で全構成が収まることを確認した。
  現時点で実際に切り詰められる構成は無く、ゲートの見逃し余地を塞ぐ修正。
- **switch戦略のラベルがLTOでSRAMへ落ち、MegaのDCX/CAMF構成が実機でビルドできなかった**: 生成ヘッダはswitchの各caseに `static const char s[] AZARAC_PROGMEM = "..."` を関数内に置いていた。
  Arduino AVRコアは `-flto` でビルドするので、inline関数内のstatic（one-only）では `__section__` が落ちて `.rodata` へ移り、avr-libcのスクリプトがそれを `.data`（SRAM）に置く（最小再現: 同じ属性の配列が、名前空間スコープならLTO有無どちらでもFlash、inline関数内ならLTO有りのときだけRAM。節名を固定しても変わらないので、名前ではなくone-onlyの扱いの問題）。
  実機実測（arduino-cli 1.5.2 + arduino:avr 1.8.8 + atmel 7.3.0、ATmega2560 + `-DAZARAC_AVR_LARGE_FLASH=1`、`examples/basic_nmea`）: RAM 30,236B（上限8,192B）で `data section exceeds available space in board`、DCX無しの既定構成は2,004Bで通っていた。
  `scripts/gen/gen_definitions.py` の `switch_labels()` がcaseリテラルをテーブルごとの名前空間スコープ配列（`<GUARD>_C<key>[]`）として出すようにし、宣言ごとの節（`__COUNTER__`）と `--gc-sections` の粒度はそのまま保つ。
  同じ実機構成でRAM 30,236B → 4,908B、フラッシュは143,432Bで不変、far参照（elpm/RAMPZ）も不変。
  定義ヘッダは再生成済み（生成器の出力は冪等）。
  ベンチのLTO画像も29,042B → 3,718B（LTO無し3,714B）になり、`autoresearch.sh` はLTO画像とLTO無し画像の差が64Bを超えたときに報告する（ゲートにはしない）。
  ラベルは1,409,708照会で不変（`labels.golden`）、`AVR_TABLE_BYTES` 300,827B・既定AVR構成・Unoも不変。
- **64KiB超のAVRで、定義テーブルがArduinoコア自身のPROGMEMを16bit窓の外へ押し出していた**: avr-libcのリンカスクリプトはprogmemクラスタ（`*(.progmem.gcc*)` / `*(.progmem*)`）を `.text` の先頭にリンク順で並べ、Arduinoは `core.a` を最後にリンクする。
  `FLASHEND > 0xFFFF` のデバイスで116KiBの定義テーブルがそこに置かれると、コアの `digital_pin_to_port_PGM` などが64KiB以上へ移動し、16bitの `pgm_read_byte(&table[pin])` が届かなくなる（`pinMode`/`digitalWrite` が誤ったポートを読む。実測: コア模擬PROGMEMが0x19F46、すなわちテーブルの直後）。
  `AZARAC_PROGMEM` を `.text.azaraC.<n>`（`*(.text.*)` クラスタ。progmemクラスタより後ろ）へ移した（宣言ごとに `__COUNTER__` で節名を分け、`-fdata-sections` と同じ `--gc-sections` 粒度を保つ。1節にまとめると、そのTUの1表が参照されただけで節全体が残り、関数内の静的リテラル（one-only/weak）は通常の配列と同居もできない）。
  `.progmemx.*` は使わない — そのクラスタはbinutils 2.29以降（PR 21849）のスクリプトにしか無く、atmel 2.26（Ubuntuの `binutils-avr` もArduino同梱のツールチェーンもこれ）では広い `*(.progmem*)` に取り込まれて同じ失敗に戻る（実測0x19F46）。
  64KiB以下のデバイスは従来どおり `PROGMEM`。
  実測（ATmega2560 + DCX/CAMF + SEISMIC/TSUNAMI）: コア模擬PROGMEMのアドレス0x19F46 → 0x0368（binutils 2.30のスクリプトでも2.26形でも同じ値）、RAM 3,714Bは不変、フラッシュは節の整列で +2B（144,804B → 144,806B。Unoは16,874B / 654B）。
  `autoresearch.sh` がコア模擬オブジェクト（`test/bench/avr/core_progmem.c`）を最後にリンクしてこのアドレスをゲートする。
- **`gen_definitions.py` の書き込みが一過性のOSErrorで落ちると、生成が途中で止まったまま古いヘッダが残る**: ファイルスキャナが新規ファイルを一時的に掴むWindowsで `OSError(EINVAL)` が出るため、5回まで再試行する（`write_file`）。
  CI（Linux）では発生しない。

## [2.0.0] - 2026-10-13

> **破壊的変更**: JSON出力がv2になりました（v1と非互換）。

### Added

- **動的確保ゼロ検証 `make -C test test-no-alloc`**: 公開API（`Parser::feed` / `toJson`）が `malloc`/`calloc`/`realloc`/`posix_memalign` と `operator new`/`new[]` を呼ばないことを、GNU ldの `--wrap` で差し替えた生カウンタで直接検証する（`test/integration/test_no_alloc.cpp`）。
  MT43（緊急地震速報）・MT44（国外CAMF）・UBX-RXM-SFRBX（海上警報）・南海トラフ27ページ集約の4経路で確保0をassertする。
  `--wrap` は未解決参照のみ差し替えるため別バイナリ・別オブジェクトディレクトリ（`.noalloc/`）でリンクし、実行後に `clean` する。
  macOSのld64は `--wrap` を持たないためスキップする。
- **`macro-size-check` の失敗がCIを赤にする**: `Measure macro size impact` ステップで `set -o pipefail` + 終了コード捕捉を追加した。
  従来は `make ... | tee` の `tee` の0が採用され、`test-macro-sizes` が落ちても緑になっていた。
- **数量フィールドに `_label` を追加**: `depth` / `magnitude` / `pressure` / `max_wind` / `max_gust` / `elapsed` / `number` は境界（`depth` 501 = 500kmより深い、`magnitude` 101 = 10.0より大きい）とセンチネル（`depth` 511 / `magnitude` 127 / `max_wind` 0 / `max_gust` 0 = 不明）を含むコード値で、
  生の値からは意味が取れなかった。
  `JsonWriter.h` に `AZARAC_LABEL` を追加し、既存28箇所のラベル出力を集約したうえで、これら7フィールドに `_label` を付与した。
  センチネルは全フィールド共通ではなく、`depth` 0は `0km`、`pressure` 0は `0hPa`、`elapsed` 0は `0時間後` で実値。
  表に無いコードはazaraCもazarashiもラベルを出さない（azarashiは `recognized: false`、`labels: {}`）。
  `CodeTable.__getitem__` は未知コードに `台風番号(コード番号：N)` を合成するが、JSON経路の `_coded()` は `value in table` でガードしてから引くためその文字列は使われない。
  `number` 0（`typhoon_number` は `BASE=1`）は両者とも空のまま。
- **津波の高さの境界を出力（`height_lower` / `height_upper`）**: 津波の高さコードは単一値ではなく範囲で、仕様の `3m` は「1m超〜3m以下」（cat 6は `3m~5m` のように `height_label` 自体が範囲だが、cat 5のラベルは上端 `3m` しか出さず範囲は読めなかった）。
  cat 5/6の `entries[]` に境界（m、下端は開・上端は閉）を2キーで追加した。
  区分はazarashi 0.17.1の `PROFILES["qzss.dcr.tsunami_height"]` / `PROFILES["qzss.dcr.northwest_pacific_tsunami_height"]` と同じ。
  境界を持たないコード（`該当情報なし` / `不明` / `その他` / `Huge` / `High` / `Unknown`）と、片側だけ無い区分（`0.2m未満` の下端、`10m超` の上端）は `null`。
  生コード `height` と `height_label` は従来どおり残る。
  実測 +36〜41 B/entry（テストベクタ228通で +266 B）。
- **両言語併記 `_label_en`**: `AZARAC_LANG_JA=1` かつ `AZARAC_LANG_EN=1` のとき、文字列リテラルのキーを持つ `_label` に `_label_en`（英語）を併記する。
  `_label` は従来どおり日本語優先。
  `AZARAC_LANG_EN=0`（ライブラリ既定）と `AZARAC_LANG_JA=0 / AZARAC_LANG_EN=1` では `_label_en` を出さないため、既定構成の出力は本変更前と同一（詳細は `docs/api-reference.md`）。
- **火山の `ambiguity` に `_label` を追加**: `Du`（活動時刻の曖昧さ、3bit、0–7）は生の数値だけでは「どの粒度で時刻が有効か」が読めなかった。
  `ambiguity_of_activity_time_en` 表は日本語版を持たない英語専用表のため、北西太平洋津波の `potential_label` と同じく言語非依存で常に出力される（`_label_en` は出ない）。
- **`version`（DCRの `Vn`）を出力**: 6bit at `[214..219]`。
  `DecoderQzqsm` は `Vn != 1` を `UnsupportedVersion` として拒否していたが値を捨てていたため、`Mt43Data::version` に保持して最上位に `"version"` として出す。
  デコード成功時は常に1になるが、「フィールドが無い」と「Vn=1を読んだ」を区別できる。
- **英語索引のテストを追加**: `test/internal/test_definition_labels.cpp` に、azarashi 0.17が追加した `_en` 表を3戦略すべてで引く検証を追加した。
  array（`BASE` / `BASE+SIZE-1` / 範囲外、隣接行の入れ替え検出）、疎キー（歯抜けの前後と欠落）、switch（`nullopt` になるコードと、0が「未定義」ではなく「解除/発表」であること）を、実ヘッダから実測した期待値で固定する。
  あわせてJA表とEN表が同じコード集合を引くこと（片方だけにコードがあると、言語を切り替えただけでラベルが消える）を全数検査する。
- **英語ラベルを全面有効化**: azarashi 0.17.0が37表に英語版を追加したため、定義ヘッダを再生成し、シリアライザの全ラベル参照を `AZARAC_LOOKUP_LANG` 経由にした。
  `AZARAC_LANG_JA=0 / AZARAC_LANG_EN=1` の構成で、従来は日本語のままだった39ラベルが英語になる（`JSON Serialization: MT=43 Tsunami` の `height_label` は `5m` → `5 m`）。
  英語表を持たない項目（南海トラフの情報番号など）は日本語のままになる。
- **`make -C test dedup-realday`（実日の再現計測）を追加**: `realdata/*.l1s` を走査し、Decoderが受理したフレーム・同一性のdistinct・生存ピーク（カテゴリ別窓／一律24時間）・`DedupFilter` の偽再通知／取りこぼしをMETRIC行で出す（`test/tools/dedup_realday.cpp`）。
  窓・ハッシュ・カテゴリ判定はライブラリ本体（`Decoder::decode` / `internal::dedupWindowMs` / `internal::DedupFilter`）をそのまま呼ぶため、本体から静かにずれない。
  `realdata/` はgitignore対象なので入力が無ければ `SKIP` を出す。
- **ベンチに `PREAMBLE_KEY_STABLE` を追加し、識別鍵の指標をゲート化**: 同一のMT～VNを3つのプリアンブル（0x53/0x9A/0xC6）で再放送しても通知がちょうど1回になることを、実データのコーパス（226 distinct）の1文から行動的に測る（`test/bench/bench_dedup.cpp`、`NANKAI_KEY_STABLE` と同じ形）。
  あわせて `autoresearch.sh` で `NANKAI_KEY_STABLE` と `PREAMBLE_KEY_STABLE` を実際のゲートにした（`NEW_RECALL` / `DUP_SUPPRESS` は鍵を250ビット全体に戻す回帰でも緑のままなので、指標を並べるだけでは回帰が素通りする。キーを広げると `PREAMBLE_KEY_STABLE=0` でexit 8になることを確認）。

### Changed

- **`JsonSerializer` の出力をv2に改訂（v1と非互換）**: ルートに `schema_version: 2` を追加し、曖昧だった4点を明示化した。
  互換エイリアスは設けない（読み手は `schema_version` で分岐する）。
  `docs/json-formats.md` をv2仕様として書き直した。
  - **本文を `data` に統一**: MT43は `detail` → `data`、MT44はルート直下に散っていたAフィールド・拡張部・`sd_sdmt`/`sd_sdm` を `data` の下へ移動した。
    MT43の報告ヘッダ（`report_classification` / `disaster_category` / `information_type` / `version` / `report_time`）はルートに残る。
    MT44のルートは `schema_version` / `svid` / `msg_type` / `crc24` / `data` の5キーだけになる。
  - **ラベルを3値に**: `_label` は「表に該当なし（未定義・範囲外・表なし）→ `null`」「定義済みだが空文字列 → `""`」「ラベルあり → 文字列」の3値。
    v1は未定義と定義済み空が同じ `""` に潰れていた。
    キーは従来どおり常に出力する。
  - **時刻の `unix` を `null` で未解決表示**: `unix_time == 0` は `"unix": 0`（1970-01-01と区別できない）ではなく `"unix": null`。
    `month`/`day`/`hour`/`min` はv1のまま。
  - **津波の到着時刻の状態を明示**: cat 5/6の `arrival_day_offset` / `arrival_hour` / `arrival_min` を削除し、`arrival_time_raw`（12bitの生値）＋解決できたときだけ `arrival_time`（できなければ `"arrival_time":null`）、加えて `arrival_status`（`arrival_estimated` / `arrived_or_unknown` / `no_information` / `unrecognized_code`）にした。
    v1は `31:63`（到達中と推測）・`30:62`（該当情報なし）・不正値が同じ全ゼロ時刻に潰れていた。
    判定順はazarashiと同じで、範囲外チェックを先に置くと `30:62` の `no_information` が到達不能になる。
  - **重複キーの削除**: `svid_label` / `msg_type_label`（`msg_type` から一意）、`alert_identity{a2,a3,a4,ex1}`（`a2_country` 等と同値。`Mt44AlertIdentity` 構造体ごと削除）、`detailed_info.a4_code`（`a4_hazard` と同値）、`jalert_target.prefecture_mode`（`prefectures`/`cities` の有無で決まる）。
  - **並列配列の解消**: `jalert_target` の `prefecture_positions[]` + `prefecture_labels[]` を `prefectures[{position,label}]` に、`city_codes[]` + `city_labels[]` を `cities[{code,label}]` に統合した。
    `position` はJIS都道府県コード（1–47、1始まり）でv1の値を維持する。
  - **Dフィールドの平坦化**: B4の `"dX": {"raw": N, "label": L}` を `"dX": N` + `"dX_label": L` にした（`JsonWriter` の `wf_v`）。
    Dレイアウトを持たないa4では `detailed_info` が空オブジェクトになる（B4が存在した事実は残る）。
  - **`dcx_type` を数値から文字列へ**: `"dcx_type": 1` + `"dcx_type_label": "L_ALERT"` → `"dcx_type": "L_ALERT"`。
    値は `Mt44ServiceKind` と同じ6種（`NULL` / `L_ALERT` / `J_ALERT` / `LOCAL_GOV` / `OUTSIDE_JAPAN` / `UNKNOWN`）。
  - **降灰の `arrival_hour` を改名**: これは時刻ではなく3bitの「予想降灰時刻」コードなので `arrival_time_code` + `arrival_time_label` にした（未使用だった `qzss_dcr_jma_expected_ash_fall_time{,_en}` を `AZARAC_LABEL` 経由で引く）。
  - **実測サイズ**（同一236電文、コンパクト表現）: 254,196 B / 平均1,077 B（v1は259,450 B / 1,099 B。同一コミットのworktreeを再ビルドし同じ計量関数で測定）。
    MT44の単体レコードは `prefectures` のオブジェクト配列化により最大 +859 B、MT43は降灰（cat 9）で `arrival_hour` が `arrival_time_code` + `arrival_time_label`(+`_label_en`) になった分で最大 +242 B増える（`detail` → `data` はルート直下の同レベル改名なので深さ・バイト数に影響しない）。
    総量は `dcx_type` の重複や `alert_identity` / `a4_code` / 分解済み到着時刻の削除で減る（MT44合計 −3,734 B / MT43合計 −1,520 B）。
- **`writeOptStr` が `nullopt` を `null` として描画**: 従来は `nullopt` と `optional("")` をどちらも `""` にしていたため、JSON層で「表に該当なし」と「定義済みの空ラベル」を区別できなかった。
- **情報有効時間を災害種別ごとの配信終了条件（手順④）に変更**: 一律 `AZARAC_DEDUP_WINDOW_MS`（24時間）だった窓を、原PDF p.26–27の条件表から決めるようにした（`src/internal/DedupWindow.h`、緊急地震速報5分 / 震源・震度2時間 / 南海トラフ 発表24時間・取消2時間 / 津波 発表かつ警報コード3-5は最大24時間・他は10時間 / 北西太平洋津波10時間 / 火山24時間 / 降灰 最大1時間 / 気象 発表かつWw∈{1..6,23} は最大24時間・他は3時間 / 洪水 発表・訂正かつLv∈{2,3,4} は最大24時間・他は3時間 / 台風3時間 / 海上 各警報は最大24時間・解除は最大3時間）。
  1通に複数の副種別が入る場合は「条件にて該当する情報の配信が終了する」ため、条件を満たすうち最長の窓を採る（短い側に倒すと生きた情報を再通知する）。
  一律24時間は表に無いカテゴリのフォールバックとして残る（MT=44はA8由来の窓を使う。下記）。
- **MT=44（DCX/CAMF）の照合鍵からSDを除外（#34）**: 照合対象はQZS事務局回答のとおり「MTおよびCAMF〜EM」でSDを含まないため、`Decoder::messageIdentity` がMT=44のときだけSD（SDMT bit 14・SDM bit 15..23）をゼロにしてからCRC-24Qを取る（フレーム自体は呼び出しの前後で不変）。
  SDMだけが違う同一内容は同一情報として抑止される。
  回帰は `test/integration/test_parser_integration.cpp`（SDのみ相違→抑止、A8相違→別情報）で固定した。
- **MT=44の有効時間をA8-Hazard Durationの上限に変更（#34）**: 一律 `AZARAC_DEDUP_WINDOW_MS`（24時間）だったMT=44の窓を、A8の区分（`00`=1週間（DCX §5.4。All Clear未受信時）/ `01`=6時間 / `10`=12時間 / `11`=24時間）から決めるようにした（`src/internal/DedupWindow.h`）。
  AVRはスロットが64と少なく7日の窓が生きた情報の枠を占めるため、`AZARAC_DEDUP_MT44_MAX_WINDOW_MS`（既定5分）で頭打ちにする（実測: MT=44の再送は同一電文2回・最大間隔16秒）。
  回帰は `test/internal/test_dedup_window.cpp`（A8各値とAVR上限）。
- **重複判定表の既定容量を実測に合わせて変更**: 非AVRの `AZARAC_DEDUP_SLOTS` を64 → 512（4KB）、AVRプリセットを16×4（`AZARAC_DEDUP_WAYS=4`、128B）→ 64×8（512B）にした。
  **2024年のQZSSアーカイブ30日分**（月次サンプル12日 + 台風期8月の連続20日弱）を `make -C test dedup-realday` で計測:

  | 生存ピーク | 日数 | 256×8の偽再通知 | 512×8の偽再通知 |
  |---|---:|---:|---:|
  | 20–50 | 11 | 0 | 0 |
  | 51–100 | 13 | 0 | 0 |
  | 101–130 | 3 | 0 | 0 |
  | 327（2024-08-28のみ） | 1 | 2 | 0 |

  生存ピークの範囲は20〜327（中央値66）。
  512×8は30日すべて偽再通知0 / MISSED 0、256×8で偽再通知が出たのは最悪日（2024-08-28、台風10号＋大雨）1日だけ。
  512が実測上の下限で、能登1日（生存ピーク75）だけを見ると128で足りるように見えるが、同時生存327件の複合災害日で256でも不足する。
  **MISSED（生きた警報を抑制）は30日 × 全容量で0** — 満杯時の追い出しが「最も古い=窓切れに近い」1件を選ぶため、容量不足は再通知として現れ、警報は落ちない。
  AVRプリセット（64×8）は能登のSEISMIC/TSUNAMI部分で0件（32×8も0、16×8は93、旧16×4は106）。
  `test/Makefile` の `pgm-stub` も `AZARAC_DEDUP_SLOTS=8`（AVRプリセットのWAYS=8と組み合わさってSETS=1になり容量を全く検証しない）から64に変え、AVRプリセットと一致させた。
- **`memprof` ジョブ（Valgrind Massif）を廃止**: ヒープのプロファイラは「ライブラリ自身が確保していない」ことを直接示さないため、上記の `test-no-alloc` に置き換えた。
  CIの `memprof` ジョブと `test/Makefile` の `memprof` ターゲットを削除した。
  `macro-size-check` はマクロ別 `.text` 相対差の計測として維持する。
- **azarashi 0.17.1対応**: `.azarashi-version` を0.16.4 → 0.17.1、`library.properties` の宣言をIS-QZSS-DCR-017 / IS-QZSS-DCX-004 Rev.004に更新し、`src/` と `README.md` のDCR-016参照をDCR-017に置換した。
  `scripts/requirements.txt` の下限とCIのfixture-driftジョブのピンも0.17.1に揃えた（同ジョブがdiffする `test/data/nankai_pages_generated.h` は0.17.0と0.17.1で同一）。
- **長周期地震動階級code 0の突合を修正**: azarashi 0.17.1はこの階級の表にcode 0（`該当情報なし` / `No data`）を追加したが、報告属性は `None` のまま返す（JSON側は名前を持つ）。
  `test/scripts/compare_with_azarashi.py` は属性とazaraCのラベルを突合するため、`make -C test compare-realdata` がrealdata 974通中7通（967/974 passed）の偽差分（`long_period_ground_motion_{lower,upper}_limit` の2キー）でexit 1になっていた。
  「情報なし」を意味する `該当情報なし` / `No data` を `None` と同値として扱い、差分0に戻した。
- **ドキュメントとコメントの版数・API名を更新**: `docs/json-formats.md` と `docs/api-reference.md` のazarashi版数を0.17.1に、`to_json_dict()` を `azarashi.json.to_json_dict()`（0.17.1でJSON層が `azarashi.json` モジュールへ移動）に直した。
  `test/` の3本にある「azarashi v0.16.1のデコード結果と照合」は版数に依存しない表現（定義テーブルはazarashi 0.17.1）にし、`a3` code 0のコメントを0.17.1の表記（`Not used`）に合わせた。
  `src/` の仕様引用はCAMF v1.1 → v1.2（`DecoderDcx.cpp` は `(B1-B4)` に整理）、`README.md` にMT=44のBフィールドとC10の根拠（EWSS CAMF Issue 1.2）を明記した。
  Issue 1.2（2026-03公開）はv1.1から節番号と内容が変わっていないことを確認した（§3.5.3 = A11はList A / List B各32命令、§3.7.4 = B4、§11 = List A / List B、§18.2 = C5/C6の式）。
- **`gen_definitions.py` をazarashi 0.17の定義パッケージ構成に対応**: 定義パッケージが `azarashi.qzss_dcr_lib.definition` から `azarashi.definitions` へ移り、テーブル変数名から仕様接頭辞が落ちたため、モジュールパスからazaraC側の既存C++ 名を復元する規則（`definitions.qzss.dcr/*` → `qzss_dcr_jma_*`、`definitions.camf/*` → `qzss_dcx_camf_*`、`definitions.qzss.dcx/*` → `qzss_dcx_*`、`definitions.qzss.l1s/*` → `qzss_dcr_*`、`definitions.qzss.ubx/*` → `ublox_qzss_*`）と、
  それで戻らない4名の上書き（`preambles` → `qzss_dcr_preamble` 等）を追加した。
  再帰探索（`pkgutil.walk_packages`）によりサブパッケージ下の表も生成対象になる。
  生成後に、今回生成しなかった `.h` を `src/definition/` から削除する（`_index.h` を全再生成するため、残骸が黙って残らない）。
- **定義ヘッダをazarashi 0.17.1で再生成**: 生成ヘッダ138本 + 手書き2本。
  旧104本から48本増、11本減（うち4本は `qzss_dcr_{message_type,satellite_prn,preamble}.h` と `qzss_dcx_camf_a11_international_library_code.h` — JSON v2のラベル削除・ガード未定義・消費者ゼロのため生成対象外にした）。
  内訳は英語表37本（既存表の `_en` 26 + 新規表の `_en` 11）、新規日本語表10本（`depth_of_hypocenter`, `eew_magnitude`, `hypocenter_magnitude`, `typhoon_number`, `typhoon_central_pressure`, `typhoon_maximum_wind_speed`, `typhoon_maximum_gust_wind_speed`, `typhoon_elapsed_time_from_reference_time`, `expected_ash_fall_time`, `ash_fall_warning_type`）。
  削除は `qzss_dcx_camf_a3_provider_identifier_{australia,fiji,japan,map,thailand}.h`（0.17では `a3_provider_identifier_map` に統合。手書きの `qzss_dcx_camf_a3_provider_identifier.h` が既に同等で、中身の一致を確認済み）と `qzss_dcx_camf_ex9_target_area_code_{en,ja}.h`（参照ゼロ）。
  なお `qzss_dcx_ex1_target_area_code_en.h` は1980件すべての表記が変わる（例: `Sapporo-shi, Hokkaido` → `Sapporo City, Hokkaido Prefecture`）。
  `AZARAC_LANG_JA=0 / AZARAC_LANG_EN=1` 構成の都市名ラベル出力が変わるため、ENを有効にしている利用者はラベル文字列の変化に注意。
  azarashi 0.17.1が追加した表のうち、消費者が無い `qzss_dcx_camf_{c7,c8,c9}_*`・`qzss_dcx_ex2_evacuate_direction_type`・`qzss_dcx_camf_a11_international_library_b_code`（IC-B-nnのコード名）と `*_value`（コード→物理量）表は生成対象外にした（前者はJSONが生値のみ、後者はコード + ラベルしか出さないため）。
- **IS-QZSS-DCR-017のコード表変更を反映**: 津波の高さに `13 該当情報なし` を追加、 洪水予報区に3件追加（`880801000200` 石手川 ほか）と2件改名（`890907000100` 矢部川 → 矢部川下流部、 `890917000100` 番匠川 → 番匠川水系）、 海上警報31の表記を `その他の警報等情報要素_海上警報` に、 緊急地震速報の予報区80を `その他の府県予報区および地方予報区_緊急地震速報(警報)` に更新（ いずれも今回のヘッダ再生成に含まれる）。
- **降灰の `warning_type_label` をハードコードから定義テーブルへ**: azarashi 0.17.0が `ash_fall_warning_type` 表（1=速報/Preliminary, 2=詳細/Detailed）を持ったため、`JsonSerializerQzqsm.cpp` の `ashFallWarningTypeLabel()` を削除し `AZARAC_LOOKUP_LANG` に統一した。
  値は同一。
- **南海トラフ既定バッファ予算を修正**: 非AVRの既定 `AZARAC_NANKAI_MAX_PAGES` を12 → 63（仕様最大、Pn/Pmは6bit）に、`AZARAC_NANKAI_BUFFERS` を4 → 1に変更した。
  既定構成でページ打ち切りが構造的に発生しない。
  集約領域を常時確保するため `Parser` のRAMは1256B → 1432Bに増加する（削減したい場合は `AZARAC_NANKAI_MAX_PAGES` を下げる。本リリースでdedup表が512×8=4KBになったため、既定構成の `sizeof(Parser)` はさらに5,464Bになった — 上記Changed節と `src/Parser.h` を参照）。
  AVRプリセット（4ページ / 1バッファ）は変更なし。
- **`docs/json-formats.md` のazarashi側を0.17.1（JSON v2）に追随**: §2の記述をv2の形に更新した。
  コードは `{scheme, code, recognized, labels}` → `{status, code, table, labels}`（`status` は `valid` / `assumed` / `special` / `undefined` の4値、`table` が体系名）、時刻は `{status, value, precision, source}`（`basis` は廃止、センチネルは `special` + `labels`）、
  数量は `value` か `range{lower,upper}` + `unit`（`kind` は廃止）、封筒は `is_test` / `reception{at,satellite,nmea}` / `message_id` / `series` / `texts`。
  EX9の都道府県コードはazarashiも0.17.1から1–47（`qzss.dcx.ex9_target_area_code_list`）になり、azaraCの `position` と一致する（v1は `qzss.dcx.prefecture_bit` の0始まりビット位置で、同じ電文で `1` ↔ `0` とずれていた）。
- **§2.6のサイズ・深さを再計測**: コーパスを再現可能な `test/data/*_vectors.json` のNMEA 228通（MT43 98 / MT44 130。すべてazaraCが受理）に固定し、両者を同じ計量関数（UTF-8・区切り文字なしのコンパクト表現）で測り直した。
  azarashi 613,976 B（平均2,692）/ `data` 371,812 B、azaraC 260,750 B（平均1,143）/ `data` 203,609 Bで、azaraCはazarashiの1/2.35。
  azarashi側の内訳は `texts` が全体の25%、`data` のうち `labels` が31%、`table` のキー＋値が25%（92,706 B、2,416回。最多はEX9の430回）。
  入れ子の深さの表も同じ228通のカテゴリごとに測り直した。
  あわせて §1.3・§2.2の通数（133 → 130、`main_ellipse` 9 → 8、A11の内訳125/2/6 → 124/1/5）を実測値に揃えた。
- **A11国際ライブラリのcode 0はazarashiと表記が違うと明記**: azarashiのJSONは国際List A / List B（とC10）のcode 0を `status:"special"` + `labels:{en:"No instruction"}` と表記する（`azarashi/json/tables.py` が表の `0: ''` を上書きする）。
  CAMF Issue 1.2は §3.5.3の本文でこのコードを「Empty values …（各リストの 'null' ビット列）」＝空値と述べ、表とAnnex §11では `reserved`、`no instruction` と明記するのはC10の §3.7.3.4だけなので、azaraCは定義表の `""`（定義済みの空）を出す。
  同じ意味の別表記であることを `docs/json-formats.md` に明記した。
- **`docs/json-formats.md` を仕様書として再構成**: azaraCのJSONスキーマ（共通ヘッダ、MT43 `detail` のカテゴリ別キー、MT44のAフィールドと条件付きブロック、B4のDフィールド）を示したうえで、azarashiとの対応（封筒、コード値、数量、時刻、繰り返し、サイズと深さ）と落ちる情報・互換方針を並べる形にした。
  数値の基準（`test/data/*_vectors.json` のNMEA 228通と `make -C test decode`）も明記した。
  あわせて `developer-guide.md` の定義ファイル数（104 → 140）とテスト結果例、ドキュメント表のリンクを実態に合わせた。
- **`NankaiPageBuffer.h` の既定値重複定義を削除**: `AZARAC_NANKAI_MAX_PAGES` / `AZARAC_NANKAI_BUFFERS` の定義元を `azaraC_config.h` に一本化した。
- **CIのPlatformIOインストール手順を簡素化**: `platformio==6.2.0` は `starlette<2` を要求し、旧6.1.19の `starlette<0.53` 制約（PYSEC-2026-161/2280/2281/248/249）は解消済みのため、`scripts/requirements.txt` を超えてstarletteを強制上書きしていた `pip install --no-deps` ワークアラウンドを削除した。
- **ドキュメントを実装に一致**: `architecture.md` のメモリ表（`DedupFilter` 8B/スロット、`NankaiPageBuffer` 28B + `MAX_PAGES × 18 + 1`、定義テーブル: 表エントリ39本で122KiB（124,960B）、定義文字列を含むライブラリ全体の `.rdata` 344KiB（351,896B）、AVRプリセットは3.4KiB（3,520B）。全カテゴリ・日英ラベル有効、64bitホスト `g++ 15.2 -O2 -fdata-sections`（AVRは `-O0`）実測。253,568Bは `const char*` 化前の表エントリ計量）、
  `library.properties` のEWSS CAMF版数（v1.1 → v1.2）、`developer-guide.md` の定義ファイル数（103 → 104）とテスト構成、`getting-started.md` の参照先と設定マクロ表、`README.md` のC++17要件を修正した。
  `README.md` の連続する引用ブロックを `>` で連結し、Markdownパーサ間で別ブロック引用と解釈され得る空白行を除去した（markdownlint MD028）。
- **`NankaiPageKey` のidentityをreport_time DHMに正規化**: 鍵を `{info_code, report_time month/day/hour/minute}` に統一し、解決済みUNIX時刻をidentityから除外した（`event_time_unix` フィールドを削除、`month` を追加）。
  `report_unix` が受信中に解決/未解決へ変わっても同一イベントが1バッファに集約される。
  従来は解決済み鍵と未解決鍵が不一致となり、`AZARAC_NANKAI_BUFFERS=1` では投入済みページが破棄され、`>1` ではバッファが分裂して集約が完了しなかった。
  `getNankaiBuffer()` に渡す鍵の生成方法が変わる（コンストラクタ引数は `(info_code, month, day, hour, minute)`）。
- **ドキュメントとコメントの書き掛け・装飾・文字化けを整理**: `architecture.md` のスロット数根拠を、計測手順の記述（30日分の取得、「このテストでの最悪値」、`REALDAY_INPUT` の切替手順）からデータと結論に絞り、`json-formats.md` のv1.0.x差分表の前置き（「`[Unreleased]` の作業中の内容」）と「テスト電文で確認した」表現を整理した。
  `test/integration/test_error_handling.cpp` の1行目とセクション見出しに残っていた文字化け（無効バイト + U+FFFD）を修復し、`test_json.cpp` / `dedup_realday.cpp` / `gen_realdata_vectors.py` / `test_core.cpp` の作業ログ的な記述（「本作業の目的」「以前は」「ため削除した」）を設計記述に直した。
  `# ── ラベル ──` / `# ══…══` の装飾コメント（`.github/workflows/ci.yml`、`scripts/analysis/*.py`、`test/scripts/*.py`）をラベルだけに揃え、コメントとツール出力の `AzaraC` 表記を `azaraC` に統一した。
  挙動の変更は無い（`make -C test run` は418ケース / 10417アサーションで緑）。

### Fixed

- **重複判定の同一性が仕様の照合対象（MT～VN）ではなく250ビット全体だった問題を修正**: 鍵の `crc24` は `Decoder::decode` がフレームのbit 0..225から計算した値で、プリアンブル（bit 0..7）を含んでいた。
  仕様（アプリケーションノートv2手順③、原PDF p.24–25）の照合対象はMT～VN（フレームbit 8..219 = 212 bit）で、付属フローチャートも「MT～Vnの212bitについて比較する」と明記している。
  `Parser::handleFrame` が `Decoder::crc24q(frame.bits + 1, 212)` で部分区間のdigestを作って渡すようにした（`crc24q` は `internal::Decoder` のpublic staticに移動。`DedupKey::crc24` は `identity` に改名）。
  **Reserved 6 bit（220..225）も含めない**: 実放送では16値が巡回し、正しい162個の同一性のうち138個が複数のReserved値を持つため、含めると1情報が約11個に分裂する（能登の実日: 212 bitでdistinct 162、218 bitで1,764、250ビット全体で3,697）。
  受信衛星を鍵に含めない方針は変更なし。
  回帰は `Parser: プリアンブルが違っても同一 MT～VN は 1 回だけ通知される`（`test/integration/test_parser_integration.cpp`）と、実データの `PREAMBLE_KEY_STABLE`（ベンチ）で固定した。
- **重複判定が仕様（アプリケーションノートv2原PDF p.23–25）と一致していなかった問題を修正**: 鍵が`{svid, msg_type, crc24}`だったため、①複数衛星からの重複判定が成立していなかった（250ビットのフレームに衛星IDは含まれず、`svid`はNMEA/UBXヘッダ由来の別レイヤ。衛星ごとに鍵が変わるので、中継された同一情報を衛星数だけ再通知する）。
  実測の一致率は0.0044（`test/bench/bench_dedup.cpp`、実データ226種）。
  加えて時刻を持たないため手順④'「一定時間受信しなかった情報は履歴から削除する」が実装できず、10分無受信後の再放送を重複として抑止していた（同0.3818）。
- **南海トラフの集約メッセージが到着順で別情報になっていた問題を修正**: 集約結果の重複判定は「ページ集合を完成させた電文」の `crc24` を鍵にしていたため、同じ事象を別のページ順で再放送すると毎回新しい情報として通知されていた。
  同一性を事象そのもの（`info_code` + `information_type` + 報告時刻、`NankaiPageKey` と同一の26ビット）に変更した。
  集約鍵は電文鍵とタグで名前空間を分けており（`DedupKey::synthetic`）、同じ数値の電文CRCと衝突しない。
  回帰は `test/integration/test_nankai_e2e.cpp`（同一事象を逆順で再投入 → 再通知なし）で固定した。
- **南海トラフの事象鍵が情報種別（発表/取消）を区別していなかった問題を修正**: `info_code` と報告時刻が同一で `information_type` だけが異なる発表（It=0、窓24時間）と取消（It=2、窓2時間）が、dedupの事象トークンでも集約鍵でも同じ鍵になり得た。
  取消が発表のdedup履歴に潰されて通知が落ち、集約バッファでも同じPnのページが先着優先で捨てられて2つの文面が混ざる。
  事象鍵に `information_type` を加えて26ビットにし、`DedupKey` の合成名前空間をbits 0..29へ広げた（実鍵はbit 30を立てないため衝突しない）。
  `NankaiPageKey` も同一の6フィールドに揃え、`NankaiPageBuffer` のレイアウト（メタデータ28B・構造体1,168B）は変わらない。
  回帰は `Nankai E2E: 同一 info_code + 報告時刻でも発表と取消は別に通知する`（`test/integration/test_nankai_e2e.cpp`）で固定し、トークンからItを落としても集約鍵からItを落としてもこのテストが落ちることを確認した。
- **重複判定表の追い出しが「最も古い情報」ではなかった問題を修正**: 巡回リングは書き込み位置で上書きするため、満杯時は最新の情報を捨て古い情報を残していた。
  通知済みの生きた警報が再通知され、逆に古い情報が居座る。
  情報ごとの最終受信時刻（手順④'）を基準に最も古い1件を置換するようにした。
- **`DedupFilter`の既定スロット数が実運用の同時情報数に足りていなかった問題を修正**: 既定8スロットに対し、24時間有効な津波警報や同時多発する気象情報では同時保持数が数十件になる。
  既定を64スロット（`AZARAC_DEDUP_WAYS=8`、512B）に増やした（本リリースでさらに512スロット / 4KB、AVRプリセットは64×8へ引き上げた — 上記Changed節を参照）。
  あわせて表をセットアソシアティブ化し、1決定あたりの走査を連想度（8）で頭打ちにした（全探索では32スロット時に97ns/決定、セットアソシアティブでは12.7ns/決定）。
  実測（実データ226種・2478決定）: 抑止率0.38 → 1.00、新規情報の通知34/38 → 118/118。
  AVRプリセットは当時16スロット（`AZARAC_DEDUP_WAYS=4`、128B）で、旧実装の4スロットより多かった（本リリースで64×8 = 512Bへ変更済み — 上記Changed節）。
- **PRN空間外の `svid` に `svid_label` を付けないよう修正（v2で `svid_label` を削除したためラベル部分は無効。`Frame::svid` のPRN範囲記載の修正は有効）**: 定義表を `msg.svid & 0x3F` で無条件に引いていたため、PRNでないsvidにも実在しないラベルが付き得た。
  `NmeaFramer` の `svid | 0x80` は仕様外の生ID（64以上）でPRN空間外の値を作り（例: 119 → 247、`247 & 0x3F` = 55 = PRN183）、`UbxFramer` は `ublox_qzss_svid_prn_map` に無いsvIdをそのまま通す。
  `svid` がPRN空間（128–191）のときだけ表を引くようにした（ラベルのPRNは `key + 128` なので、この範囲では `svid == PRN`）。
  実データ（`$QZQSM` のIDは53–61 = PRN181–189）はすべてPRN空間内のため175/236の解決数は変わらない。
  あわせて `Frame::svid` のPRN範囲の記載（183–191）を181–191に修正した（`docs/architecture.md`, `src/framer/Frame.h`, `src/internal/Dedup.h`, `src/framer/NmeaFramer.cpp`）。
  `docs/json-formats.md` のMT44記述も、共通ヘッダ5キーを出している実装に合わせて「MT43固有項目を持たず」に直した。
- **A11ラベルのライブラリ選択を仕様どおりに修正**: `JsonSerializerDcx.cpp` はA9=1をInternational library（コード0–31）、A9=0をJapanese libraryへ送っていたが、DCX-004 §4.2.3.9 Table 4.2-12は逆の定義。
  分岐を戻し、A9=1かつA2=111のときだけ国/地域libraryを引くようにした。
  実データ（重複文を除く133通）ではA9=1の131通がすべて空だったのが、国内表（A9=1 / A2=111）を引く125通のうち43通がラベル非空になった（A11=136が41通、A11=128とA11=134が各1通。例: 136 = 「これは、Jアラートのテストです。」）。
  A9=1 / A2≠111は表が無いため `null`。
- **A11をList A / List Bの2コードとして解決**: 国際ライブラリ（A9=0）のA11を10bitのまま32件の国際表へ索引していたため、List B（下位5bit）のコードをList Aの別の指示として表示し、A11 ≥ 32では有効なList A指示が `null` になっていた。
  EWSS CAMF v1.1 §3.5.3 / §11はA11 = List A 5bit + List B 5bitと定めるため、`a11 >> 5` でList Aを、`a11 & 0x1F` でList Bを引き、List Bを新キー `a11_guidance_list_b_label`（常時出力）に出すようにした。
  日本の表は10bitを鍵にした結合表なのでList Bは `null`。
  国際表List A / List Bのcode 0は定義済みの空文字列 `""`、List Bの29/30は表に無く `null`。
  List Bの表（`qzss_dcx_camf_a11_international_library_b`、30キー）はazarashi 0.17.1の定義ヘッダ再生成で得た。
  同0.17.1はcode 0のラベルも追加しており（`a11_japanese_library_ja` 0 = 「指示なし」、`c10_instruction_library_for_second_ellipse` 0 = `No instruction`、A3/A4 = `Not used`、長周期地震動0 = 「該当情報なし」/`No data`、津波高13 = `No data`、津波発生の可能性7 = `Other Tsunamigenic Potential`）、
  実データ133通（重複文を除く）の内訳は「ラベルあり125（A11=0の82通が `指示なし` になる）/ `""` 2 / `null` 6」に変わる。
  d3/d4の表は `undefined` 付きになり戻り値が `std::optional`、ラベルも数量表記へ変わった（`112.5` → `112.5°`）。
- **`NmeaFramer` のSatellite ID正規化を仕様どおりに修正**: `Frame::svid` の契約はPRN（`api-reference.md` の「衛星ID (QZSS L1S PRN: 183-191)」）だが、`NmeaFramer` は `55 <= svid <= 63` のときだけ `+128` し、それ以外は入力値をそのまま通していた。
  Satellite IDは「PRNを表す8bitの下位6bit」（DCR-017 §4.3.1 / DCX-004 §4.3.1）なので、53/54もPRN181/182に正規化されるべきで、azarashiも全IDに `| 0x80` を適用する。
  実データ236通のうち61通（53: 5 / 54: 56）で `svid` がazarashi・`test/data/dcx_vectors.json` の期待値（`(53,181)` / `(54,182)`）と食い違っていた。
  `svid | 0x80` に統一（`55–63` では `+128` と同一、128以上は恒等なので二重変換しない）。
- **`svid_label` が常に空だったバグを修正（v2で `svid_label` を削除したためこの修正は2.0.0の出力に現れない。記録として残す）**: IS-QZSS-DCR-017 §4.3.1は「Satellite ID is 6 LSB of the 8 bit which represented PRN of the L1S」と定め、定義表 `qzss_dcr_satellite_prn` のキーもその6 LSB（`55,56,57,58,61`）。
  一方フレーマはsvidをPRNに正規化する（`NmeaFramer` は `+128`、`UbxFramer` は `svid_prn` 経由）ため、`qzss_dcr_satellite_prn_lookup(msg.svid)` は必ず引き外れて常に空文字列になっていた。
  `msg.svid & 0x3F` を引くよう修正。
  236電文での実測で0/236 → 175/236解決（`PRN183`–`PRN189`）。
  残り61件はPRN181/182（正規化前の生ID 53/54）で、表が覆う `{55,56,57,58,61}` の外にあるため空文字列が正しい（azarashiも同じくラベルを持たない）。
- **カテゴリ無効化が英語表に効いていなかった問題を修正**: 生成器の `category_guard` は `GUARD_MAP` を変数名の完全一致で引いていたため、`*_en` / `*_ja` 表が翻訳元のカテゴリガードを継承していなかった（`GUARD_MAP` のコメントは以前から継承を前提に書かれていた）。
  影響は2つ。
  `-DAZARAC_ENABLE_TSUNAMI=0` で日本語表は消えるのに英語表が残り、Flash削減が半分しか効かない。
  そして「JAとENは同じコード集合を引く」不変条件が崩れ、`make macro` が `AZARAC_ENABLE_EEW=0` で落ちていた（実測36表、`test_definition_labels.cpp` のJA/EN一致検証で `id=1..15` が不一致）。
  `category_guard_for()` で継承を実装し、定義ヘッダ（`*_en` 39本）を再生成した。
  `a11_japanese_library` / `ex1_target_area_code` / `ex9_target_area_code` は `_en`/`_ja` しか存在しないため完全一致を優先する（継承でガードが消えない）。
  EN表の内容テストも各カテゴリのガードに合わせて `#if` で囲んだ。
- **JA専用テーブルが無い `_en` 表が既定構成で消えていた問題を修正**: `gen_definitions.py` が `_en` 接尾辞の表を無条件に `AZARAC_LANG_EN` でガードしていたため、日本語版を持たない英語専用表（`tsunamigenic_potential_en` / `coastal_region_en` / `northwest_pacific_tsunami_height_en` / `ambiguity_of_activity_time_en`）がライブラリ既定（`AZARAC_LANG_JA=1 / AZARAC_LANG_EN=0`）で `nullopt` スタブになり、
  北西太平洋津波カテゴリの `potential_label` / `height_label` / `region_label` がすべて空文字列になっていた（実電文で実測）。
  仕様自体が英語のため日本語版が存在しない表で、CAMFの各表と同じく言語非依存として扱うべきもの。
  日本語版を持つ `_en` 表（`prefecture_en` など）は `AZARAC_LANG_EN` と翻訳元のカテゴリガードの両方でガードされる（後者は上記の継承修正で入った）。
  定義ヘッダを再生成した（4本のガード行のみ変更）。
  回帰は `test/internal/test_definition_labels.cpp` の「lone `_en` tables resolve regardless of `AZARAC_LANG_EN`」で固定し、`make -C test run-lang-defaults`（JA単独 / EN単独の2構成）を新設してCIに追加した。
  テスト既定（JA=1 / EN=1）だけではこの回帰は現れない（EN表が生きているため）。
- **`test_definition_labels.cpp` のa11英語ラベル期待値を修正**: azarashi 0.17.0は日本語ライブラリの英語版コード0に `No instruction` を与えたため、`size() == 0` を期待していた検証を「値が存在する」に変更した。
  英語ビルドで落ちるようになっていた。
- **`test_json.cpp` のラベル検証を言語非依存化**: ラベル期待値が日本語リテラル直書きだったため、`AZARAC_LANG_JA=0 / AZARAC_LANG_EN=1` の構成で33アサーションが落ちていた（本変更前から存在する不具合）。
  `LBL(ja, en)` マクロで言語ごとの期待値を持たせ、検証する不変条件（コード→ラベルの対応）を全構成で保つようにした。
  `AZARAC_LANG_EN` を有効にした初の検証は、この構成で `make -C test run` が通ることをもって完了とする。
- **テストが既定構成を検証していなかった問題を修正**: `test/Makefile` が `-DAZARAC_NANKAI_MAX_PAGES=63` を無条件に渡していたため、ライブラリ既定値の経路が未検証だった。
  `-D` を削除し、既定（63）を `make -C test run` で検証、縮小バジェット経路を `make -C test run-small-pages`（`AZARAC_NANKAI_MAX_PAGES=8`）とCIステップで検証する。
  `run-small-pages` / `pgm-stub` は `-D` 群が依存関係に載らないため終了時に `clean` し、別構成の `.o` が既定構成の `.o` と混在して以降の `run` が再ビルドされない（または `check-strict-compile` 後の混在リンクで落ちる）問題を防ぐ。
- **`NankaiPageKey::isValid()` を削除**: 本番コードから呼ばれておらず（`addPage` は `isValid()` を見ない）、identityが生 `report_time` + `info_code` に一本化された後は意味のある不変条件を表さないため削除した。
  空バッファ誤マッチは `NankaiPageBuffer::matchesKey()` の `isEmpty()` ガードが担う。
- **打ち切りのE2Eテストを追加**: `total_pages > MAX_PAGES` のとき `MAX_PAGES` ページで集約が完了し `truncated=true` / `total_page` が電文の総ページ数を報告することを検証する。
- `scripts/analysis/cppcheck_summary.py` から削除済みマクロ `AZARAC_NANKAI_AGGREGATED_TEXT_SIZE` の指定を削除した。
- **`.gitignore` と `test/Makefile clean` を整備**: テスト生成物（`test/cppcheck_report.xml`, `test/coverage_report.json`, `test/macro_sizes.txt`, `test/no_alloc_tests`, `test/bench/bench_dedup` 等）を追跡対象外にした。
  `test/Makefile` の `MINGW64_BIN` 既定値から個人パスを削除し、コマンドライン指定の任意設定にした。
- **ゼロ鍵が空バッファに誤マッチする問題を修正**: `NankaiPageBuffer::matchesKey()` が空（全ゼロ鍵）バッファを一致扱いしていたため、ゼロ鍵イベントが継続中バッファではなく空きスロットに書かれ、スロット再利用時に分裂し得た。
  空バッファは一致しないようにした。
- **Nankaiページフィクスチャをazarashiから生成し二重管理を解消**: `test/scripts/gen_all_vectors.py` のNankai入力を上流の27電文に拡張し、`test/data/nankai_vectors.json` を27ページに完全化、同じJSONから `test/data/nankai_pages_generated.h`（C++ フィクスチャ）を生成するようにした。
  `test_nankai_e2e.cpp` の手書き配列と `compare_nankai_aggregation.py` の重複コピーを削除した。
  実データの最終ページはNUL埋め（「い。」のみ）で、期待集約長は合成値時代の486ではなく474バイトになる（テストはNUL打ち切りを反映して算出）。
- **DCXの未検証項目にテストを追加**: `decodeLatitude17` / `decodeLongitude17_45_225` / `decodeB2HazardCenter`（`c5/c6 > 63` の丸め分岐を含む）/ `decodeCityCodeList` の単体テスト、B4の複数レイアウト（a4=47/51/64/77/80/82）のJSON raw値と未知a4、主楕円・追加楕円の統合座標を検証する。
- **デッドコードを削除**: `#if 0` の `test/integration/test_azarashi.cpp` と、未使用の `test/test_helpers.h` の `testDecode*` ラッパ11個を削除した。
- **v2テストにカテゴリマクロガードを追加**: 新規5テストが `#if (AZARAC_ENABLE_*)` の外にあり、`AZARAC_ENABLE_TSUNAMI=0` で9アサーション失敗、`AZARAC_ENABLE_DCX_CAMF=0` で `initMt44` 未宣言のコンパイルエラー 3件（`test/json/test_json.cpp`）になっていた。
  `make -C test macro` がTSUNAMIで打ち切られるためDCX_CAMFはCIでは未到達だった。
  テストが使うカテゴリのガードで囲み、アサーションは変更していない。

## [1.0.3] - 2026-08-29

### Added

- **セキュリティ文書**: `SECURITY.md` を追加し、脆弱性報告ポリシーとリリース成果物の検証手順を明記した（#13）。

### Changed

- **未使用コードを削除**: 未使用の生成スクリプト、ヘルパ、型、シム、テストの冗長アサーションとコメントを削除し、`optional` / `string_view` シムを最小実装に整理した（#16）。
- **ドキュメントを整理**: `docs/architecture.md` の図をMermaidに置換し重複する構成表を削除、`docs/getting-started.md` / `README.md` の重複する表を `docs/` へのリンクに集約、`docs/api-reference.md` の誤ったエラーコード表を削除した。
  `Dedup.h` のSVID範囲コメントを `184–202` から `183–191` に訂正した。
- **コメントを簡潔化**: `TimeFields.h` / `Message.h` / `rtos_freertos.ino` のコメントを理由のみの記述に整理し、自動生成ヘッダの不要な接頭辞を除去した。
- **CIのボード表記を整理**: Arduino Unoのボード名から `(AVR)` 接尾辞を除去した。

### Fixed

- `avr_std/optional` に `operator*` / `operator->` を追加し、DCX有効時のAVRビルド破綻を解消した。
  `operator->` が `operator&` 過載型に誤動作する問題を `reinterpret_cast` に修正し、回帰テストを追加した。
- `AZARAC_DEDUP_SLOTS` / `AZARAC_NANKAI_BUFFERS` が0に上書きされた場合のmoduloゼロを防ぐ `static_assert` を追加した。
- `examples/rtos_freertos` で `aggregated_text_ptr` が `Parser` 内部バッファへの借用である旨と、受信後にJSON変換してからキューへ積む推奨パターンを文書化した。
- `NankaiPageKey` に明示的初期化のための `constexpr` コンストラクタを追加した。
- `TimeFields.h` の `volatile` な64-bit変数の非アトミック競合による非単調返却・`s_last` 後退・エポック喪失の可能性を文書化した。
- `test/Makefile` の `memprof` ターゲットでvalgrind未導入時に `SKIP` が正しく表示されるよう修正した。
- `Mt43Data::initAs<T>()` にペイロード型のtrivially copyable検証を追加し、`Message::initPayload` に契約コメントを追記した。
- `UbxFramer.cpp` の `_len` 検証を `numWords * 4 + 8` との厳密一致に変更した。
- `NmeaFramer.cpp` の250-bit境界マスクを `0xC0` に修正した。
- `NankaiPageBuffer::clearAll()` で `aggregated_text` をゼロクリアするようにした。
- `library.json` と `library.properties` のバージョン乖離を検出するCIチェックを追加した。
- `examples/error_handling` の `to_unix_time()` を整数演算（Howard Hinnant）に置換し、AVRでの軽量化と32-bit `long` 環境での符号付きオーバーフローを解消した。
- `arduino-cli` Actionのバージョン追跡を `@v2.0.0` 表記に修正した。
- `examples/rtos_freertos` のNankai集約コメントと `TimeFields.h` の説明を事実どおりに訂正した。

## [1.0.1] - 2026-08-20

### Added

- **Supply Chain強化**: `release.yml` にArtifact AttestationとScorecardワークフローを追加し、リリース成果物の署名・検証パイプラインを整備した。
- **カバレッジ連携**: `ci.yml` で `gcovr` のJSON+XML出力を単一実行に統合し、カバレッジのアップロードを追加した。
  `src/definition` を対象から除外した。

### Changed

- **CI・リリースワークフローを整備**: `ci.yml` のPlatformIOコンパイルテストを `compile-required`（RP2040 / ESP32-C3 / Unoの3代表）と `compile-extended`（残り8ボード, `continue-on-error`）に分類し、`concurrency` と `permissions: contents: read` を追加した。
  `update-definitions.yml` のPyPIフェッチにタイムアウトとリトライを追加した。
- **ドキュメントを再構成**: `docs/README.md` を `docs/getting-started.md` に改名し、`README.md` にバッジを追加した。
  PlatformIO設定例をバージョン固定し、`build_unflags` を追加した。
- **品質設定を確定**: リント指摘を解消し、コード品質設定を追加した。
  `src/definition` をcomplexity / duplication解析から除外した。

### Fixed

- リリースワークフローを修正 (#11, #12): `private-repository` オーバーライドを追加し `verify` 成功後のみリリースを作成するよう順序を修正した。
  `sha256sum` の出力をbare hex形式に修正した。
- **依存関係を更新**: `actions/checkout` v7, `actions/download-artifact` v8, `actions/upload-artifact` v7, `arduino/arduino-lint-action` v3, `github/codeql-action` のdigestを更新した。

## [1.0.0] - 2026-08-14

### Added

- **ラベル文字列出力のテストを追加**: `test/json/test_json.cpp` の全QZQSMカテゴリ（EEW / Hypocenter / Seismic / Nankai / Tsunami / NWPac / Volcano / AshFall / Weather / Flood / Typhoon / Marine）に `_label` フィールドのアサーションを追加した（+36件）。
  降灰の `warning_type_label` は修正後の「速報」を検証する。
- **azarashiラベル突合を復活**: `test/scripts/compare_with_azarashi.py` に `LABEL_MAPPING` を追加し、`_ignore` でスキップしていた約20種のラベル文字列（`disaster_category`, `report_classification`, `information_type`, `seismic_intensity_*`, `eew_forecast_regions`, `tsunami_*`, `marine_*`, `local_governments` 等）をazarashiと直接比較するようにした。
  realdata全974メッセージで0差分を確認した。
- **`DecoderQzqsm.cpp` に仕様節番号を追記**: 12のサブデコーダのブロックコメントにIS-QZSS-DCR-016の節番号（§4.1.2.3.2–§4.1.2.3.13）を追記した。

### Changed

- **タグ付き共用体のコピー/破棄を簡略化**: `Mt43Data` / `Message` の手動タグ付き共用体について、全ペイロード型がtrivially copyableかつtrivially destructibleであることを利用し、`placement-new` + 12分岐 `switch` による `destroyActive` / `copyFrom` / `moveFrom` を `memcpy`（コピー/ムーブ）とタグリセット（破棄）の1–2行に置換した。
  ムーブはtrivial型ではコピーと同値（送り元タグのみリセット）とした。
  `#include <utility>` を削除した。
  構造体レイアウトと外的APIは不変（`sizeof` ガードと全368件のテストおよび `pgm-stub` AVRパスで検証）とした。
  ヘッダに「全ペイロード型はtrivially copyable + trivially destructibleを維持すること」の契約コメントを追記した。
- **`NankaiPageBuffer` の共通化**: 1ページあたりの有効長（NULまで）を返すprivateヘルパ `pageTextLength_()` を抽出し、`getTextLength()` / `getText()` の二重実装を解消した。
- **`Message::clear()` を追加**: デコード時の二重ゼロ初期化（`out = {}` 後の `initPayload` による約350Bの冗長 `memset`）を除去し、`Decoder::decode` と `Parser::postDecode` で `out.clear()` を用いるようにした。
- **冗長なフィールド再設定を削除**: `Decoder::decode` 内の `out.valid = false` / `out.payload_type = Empty` の再設定を削除した（`clear()` が設定済みのため）。
- **JSONシリアライザの冗長な `getMt43()` を除去**: 12のサブシリアライザのシグネチャを `const Message&` から `const Mt43Data*` に変更し、呼出元で検証済みのポインタを渡すことで各関数内の `getMt43()` とnullチェックを除去した。
- **`disaster_category` のディスパッチを `switch` 化**: `JsonSerializer::serialize` の12連 `if-else` を `switch` に変更しO(1) ディスパッチ化した。
  カテゴリ7 / 13は仕様上未定義とした。
  各 `case` は従来どおり `AZARAC_ENABLE_*` で個別にコンパイル制御する。
- **DCX B4のD3/D4出力を `writeDField` に統合**: `const char*` を返すD3/D4ルックアップを `std::optional<std::string_view>` にアダプトし、他34フィールドと同じヘルパで出力するようにした。
  出力バイト列は不変（`test_json_dcx_b1b4.cpp` で検証）とした。
- **`processNankaiAggregation` の冗長な `getMt43()` を除去**: `postDecode` が取得済みの `Mt43Data*` を引数で渡すように変更した。
- **`a3_provider_identifier` のルックアップを高速化**: 34エントリのO(n) 線形探索をO(log n) 二分探索に変更した。
- **定義テーブルのAVR (PROGMEM) 対応**: `src/definition/*.h` のラベル文字列をAVRではFlashに配置し、ルックアップ時に共有RAMバッファ（`AZARAC_FLASH_BUF_SIZE`、既定800B）へコピーして返す方式に変更した。
  非AVRでは従来の `constexpr` 実装を維持した。
  `scripts/gen/gen_definitions.py` の6エミッタにAVR分岐を追加し、`scripts/gen/apply_avr_headers.py` で既存ヘッダを移行した。
  `test/stub/avr/pgmspace.h` と `make pgm-stub` でホスト検証する。
  CIにArduino Uno (AVR) コンパイルチェックを追加した。
  - **FlashString共有バッファを1個に統合**: `azarac_pgm_view` と `azarac_pgm_copy` がそれぞれ800Bのstaticバッファを持ち合計1600BでUnoの2KB SRAMを超過していた問題を、共通 `azarac_flash_buf()` 経由の1個に統合して解消した。
    AVRプリセットでは `AZARAC_FLASH_BUF_SIZE` を64Bに縮小した（SEISMIC / TSUNAMI有効時の最大ラベル30B基準）。
    Uno実測でRAM使用量を2836Bから1300B（63%）に削減した。
- AVR用最小C++ 標準ライブラリシムを追加 (`src/internal/avr_std/`): Arduino AVRツールチェーン（avr-gcc 7.3.0）が `libstdc++` を同梱しないため、`src/` と生成定義ヘッダの標準includeを `#if defined(__AVR__)` でシム（`cstdint` / `cstring` / `cstdio` のCヘッダ委譲, `new` / `algorithm` / `iterator`, 最小 `optional` / `string_view`）へ切り替えるようにした。
  APIは不変とした。
  `test/internal/test_avr_std_shim.cpp` で検証する。
  - Arduino.hの `min` / `max` 関数マクロ対策として `azaraC.h` で `#undef` し、`Message.h` の `std::max` を三項演算子に置換した。
  - **AVRプリセットでカテゴリを自動絞り込み**: `azaraC_config.h` のAVRプリセットでSEISMIC / TSUNAMIのみを既定有効とし、他11カテゴリは無効とした（`-D` / `#define` で上書き可能）。
    例題内の `#define` は別TUのライブラリ `.cpp` に効かないため撤去し、configレベルで一括適用するようにした。
  - UnoジョブではAVR対応の基本3例題（`basic_ubx` / `basic_nmea` / `basic_uno`）でライブラリ全体をコンパイル検証する（他例題は `Serial1` 依存または容量不足のためスキップ）。
  - **`AZARAC_DEDUP_SLOTS` の既定値を `config` に一本化**: `Dedup.h` が独自に `#define 8` を持ち `Dedup.cpp` でAVRプリセット（4）と不一致になりLTOが `array types have different bounds` を検出していた問題を、`config` includeと重複既定値の削除で解消した。
  - **CIのボード分類をアーキテクチャ代表制に整理**: `compile-required`（リリースゲート）をRP2040 Pico (ARM) / ESP32-C3 (Xtensa) / Arduino Uno (AVR) の3台とし、`compile-extended`（ベストエフォート, `continue-on-error`）を残り8台とした。
- **CIの権限と例題を整理**: CIにトップレベル `permissions: contents: read` を追加した。
  例題 `basic_nmea` / `basic_ubx` の `loop()` を `Stream& gnss` エイリアスで統一し重複 `while` ループを削除した。
  `avr_std/string_view` シムの `strlen` を `constexpr` ヘルパ化し `compare` をunsigned char比較に、`find` の境界比較を減算ベースにしてオーバーフローを回避した。
  `Dedup.h` / `Mt44Data.h` の `cstdint` AVR分岐を `MtCommonTypes.h` に一本化した。
  `writeEscaped` の `snprintf` を `std::snprintf` に統一した。
  AVR `pgmspace.h` スタブの `pgm_read_word` / `pgm_read_dword` を `memcpy` ベース化した。
  `DecodedEllipse` のフィールド名を実単位にリネームした（`lat_deg` → `lat_microdeg`, `semi_major_km` → `semi_major_m`, `azimuth_deg` → `azimuth_decideg` 等および `b1RefinedRadiusKm` → `b1RefinedRadiusM`）。
  JSON出力は不変とした。
  `AZARAC_FLASH_BUF_SIZE` のAVR既定値をDCX/CAMF有効時は800B、それ以外は64Bに条件分岐した。
- **AVRプールのNULエスケープを修正**: 定義テーブル生成スクリプトがプール区切りNULを `\0` と出力し、後続が数字始まりのラベル（例: `"112.5"`）と連結して8進エスケープ化（`\011` 等）されていた問題を `\000`（3桁）に修正し、既存ヘッダ44ファイルを修復した。
  非AVRは影響なしとした。
- **MT=43カテゴリ定義をX-macroで一元化**: `DecoderQzqsm` のカテゴリサポート判定・既知分類・サブデコーダディスパッチを単一の `AZARAC_DC_CATEGORIES` テーブルから生成し、`Decoder.h` のサブデコーダ宣言を無条件化した。
- **コメントと実装の乖離を修正 (S2)**: `DcxHelper.h` のB1ビットレイアウトコメント（`a18[14:12]` 始まりのMSB順に修正）、 `DcxHelper.cpp` のB2 delta式（code 64..127の切り上げを明記）、 `UbxFramer.h` / `cpp` の `sigId`（`∈{0,1}`）と8ワード目末尾6ビット（`parity` → `padding`）、
    `NmeaFramer.cpp` の252-bit（250 data + 2-bitゼロ詰め）記載、 `Parser.h` の `getNankaiBuffer` 戻り値説明、 `NankaiPageBuffer.h` の `clear()` 説明、 `DecoderDcx.cpp` のspec版数（DCX-003 → DCX-004, EWSS CAMF v1.1/v1.2注記）を修正した。
- **死んだマクロを削除**: 実コードで未使用だった `AZARAC_DCX_USE_FLOAT` と `AZARAC_NANKAI_AGGREGATED_TEXT_SIZE` を `azaraC_config.h` 等から削除し、関連コメントと `test/Makefile` の `-D` フラグを除去した。
- **`PrintShim.h` の欠落オーバーライドを追加**: ホストテスト用 `StringPrint` に `print(const void*)` の `override` を追加し、未オーバーライド時に基底の `fputs` でstdoutに漏出していた問題を修正した。
- **降灰 `warning_type_label` の誤ラベルを修正**: `warning_type`（IS-QZSS-DCR-016 Table 4.1.2-35の `Dw1`、1=速報/Preliminary, 2=詳細/Detailed）に降灰コードテーブル（Table 4.1.2-36: 1=少量の降灰, 2=やや多量の降灰）を誤用していた問題を修正した。
  Warning Type用ラベル関数 `ashFallWarningTypeLabel()` を追加し正しい「速報/詳細」を出力するようにした（azarashi 0.16.4と同挙動）。

### Fixed

- **`examples/with_sntp/with_sntp.ino` のコンパイルエラーを修正**: `DecodedEllipse` のフィールド名リネーム（`lat_deg` → `lat_microdeg` 等）に追随し、`lat_microdeg / 1000000.0` で度単位表示を維持するようにした。
- **ラベルテーブルのマクロ跨ぎ依存を修正（サイレント空ラベル）**: 定義テーブルのガードが参照先シリアライザの有効化マクロをカバーしていない2箇所を修正した。
  `qzss_dcr_jma_volcano_name` を `AZARAC_ENABLE_VOLCANO` から `(|| AZARAC_ENABLE_ASH_FALL)` に、`qzss_dcr_jma_prefecture` を `AZARAC_ENABLE_SEISMIC` から `(|| AZARAC_ENABLE_DCX_CAMF)` に拡張した（`gen_definitions.py` の `GUARD_MAP` と生成済みヘッダの両方）。
  `VOLCANO=0` / `SEISMIC=0` のマクロ無効化ビルドでも降灰の `volcano_name_label`・DCXの `prefecture_labels` が空にならないようにした。
- **生成定義テーブルの疎キー arrayバグを修正（ラベルズレ）**: `scripts/gen/strategy.py` の `choose()` が `fill_ratio ≥ 0.6` の疎キー辞書を `id - BASE` で索引するarray戦略に落とし、欠番以降の全エントリのラベルがズレていた問題を修正した。
  `fill ≥ 0.6 && span == n`（キー連続）の場合のみarrayを選択するようにし、`disaster_category`（8=火山が降灰に化けていた）、`eew_forecast_region`（80=その他府県予報区）、`seismic_intensity_{lower,upper}_limit`、`coastal_region_en` の6テーブルを `binary_search` に切り替えた。
  定義ヘッダをazarashi 0.16.4で再生成した。
- **`DecoderDcx.cpp` の `onset_time` 閾値を修正**: UNIX時刻比較定数を `315964800u`（1980-01-06, GPSエポック）から `946684800u`（2000-01-01）に修正した。
- **`NankaiPageBuffer.h` の未初期化を修正**: `NankaiPageKey` のfallbackフィールドに `= 0` 既定初期化子を追加した。
- **OOB検出テストの偽陰性を修正**: `TestDecoder` の各staticラッパが別々の `Decoder` インスタンスを作成していたため `clearOob()` → `extractBits()` → `checkOob()` 間でOOBフラグが共有されず常に失敗していた問題を、共有 `inst()` アクセサに統一して修正した。
- **DCXメイン楕円JSONテストの精度不一致を修正**: `writeDouble` が `precision=6` で `35.600000` を出力するのに対しテストが `35.600`（3桁）を期待していた不一致を、期待値を `35.600000` に修正して解消した。

## [0.13.0] - 2026-07-28

### Added

- **DCX座標の `float` 切替マクロを追加**: `AZARAC_DCX_USE_FLOAT` を追加し、`DecodedEllipse` のサイズを72Bから36Bに削減可能にした（`Mt44Decoded` で72B節約）。
- **メモリ使用量表を追記**: `README.md` にRAM要件表を追記し、`Parser.h` に最小RAM要件コメントを追加した。
- **コンパイル時警告を追加**: Arduino Unoで `AZARAC_NANKAI_BUFFERS` が多すぎる場合に `#warning` を出力するようにした。

### Changed

- `NankaiData::aggregated_text[]` をポインタ化 (最重要): 固定配列 `aggregated_text[217]` を `const char* aggregated_text_ptr` + `uint16_t aggregated_len` に置換した。
  `NankaiData` のサイズを約250Bから33Bに、`Message` 全体を約408Bから約190Bに削減した（約53% 減）。
  実テキストは `NankaiPageBuffer::aggregated_text[]` に保持し完了時にポインタを設定する。
  次の `Parser::feed()` 呼び出し前に `Message` を消費する必要がある（既存契約と整合）。
  `aggregated_text_ptr` は `NankaiPageBuffer` のraw per-pageバッファを指す借用ポインタである点に注意する。
- **`B4DetailedInfo` の戻り値を出力パラメータに変更**: `decodeB4DetailedInfo()` が108Bの構造体を値返ししていたのを参照パラメータに変更し、スタックコピーを回避した。
- **`NankaiPageKey` のフィールド順序を最適化**: `uint32_t event_time_unix` を先頭に移動しパディングを削除した（12B → 8B）。
- **`NankaiPageBuffer` のフィールド順序を最適化**: `uint64_t` メンバを先頭に集め、`uint8_t` / `bool` メンバを後方に配置しパディングを削減した（バッファあたり約7B削減）。
- **不要な標準ライブラリ依存を除去**: `JsonWriter.cpp` から `<cmath>` を除去し `std::isnan` / `std::isinf` を `v != v || v > 1e308 || v < -1e308` に置換した。
  `Mt43Data.h` から `<algorithm>` を除去し `std::max({...})` を `constexpr` lambdaに置換した。
  `DcxHelper.cpp` の全 `static const double` を `static constexpr double` に変更した。
- **`DcxHelper.cpp` のdecode関数を `dcx_real_t` に移行**: `AZARAC_DCX_USE_FLOAT` 有効時は `float` を用いるようにした。

### Fixed

- **Nankai E2Eテストを修正**: NULバイト打ち切りテストをポインタ化後のraw buffer動作に合わせて修正した。
- **DCX JSONテストを修正**: `float` モード時の精度差に対応した（`#ifdef AZARAC_DCX_USE_FLOAT` で期待値を切替）。
- **OOB検出テストの偽陰性を修正**: `TestDecoder` の共有 `inst()` 化によりOOB検出が常に失敗していた問題を修正した。
- **DCXメイン楕円JSONテストの精度不一致を修正**: 期待値を `35.600000` に修正した。

## [0.12.0] - 2026-07-16

### Added

- **`truncated` フラグを追加**: `NankaiData` に `bool truncated` を追加し、`total_pages` が `AZARAC_NANKAI_MAX_PAGES` を超えた場合にセットされるようにした。
- **`isContiguous()` メソッドを追加**: `NankaiPageBuffer` にビットマップ連続性チェックを追加し、受信済みページが番号順に欠落なく連続しているかをO(1) で判定可能にした。

### Changed

- **`NankaiPageBuffer` を単一バッファ + ビットマップ方式に刷新**: 2重バッファ構造（`PageData[]` + `aggregated_text[]`）を廃止し `aggregated_text[]` に直接ページを書き込む方式に変更した。
  受信済みページの追跡を64-bitビットマップで行い重複チェックをO(n) からO(1) ビットテストに高速化した。
  ページソートを不要化（オフセット書き込みのため）し、コード行数を約140行から約100行に削減した。
- **`AZARAC_NANKAI_AGGREGATED_TEXT_SIZE` を自動導出化**: 既定値を `AZARAC_NANKAI_MAX_PAGES * 18 + 1` から自動計算するように変更し、ユーザは `AZARAC_NANKAI_MAX_PAGES` のみ設定すればよいようにした。
  明示的上書きは `#ifndef` ガードで引き続き可能とした。
  `Mt43Data.h` の冗長な既定値（`217`）を削除した。

### Fixed

- **`total_pages > AZARAC_NANKAI_MAX_PAGES` で全ページが破棄されるバグを修正**: 旧実装では `total_pages` が設定値を超えると即座に `false` を返し全ページが失われていたが、`total_pages` を `MAX_PAGES` にキャップし収まる分だけ受け入れ、超過時は `truncated` フラグで通知するようにした。
- **`getTextLength()` / `getText()` の防御的修正**: 完了バッファ以外で呼ばれた場合に未受信ページのゴミデータを読む可能性を排除し、ビットマップをチェックして受信済みページのみを処理するようにした。

## [0.11.0] - 2026-07-14

### Added

- **軽量設定ヘッダ `azaraC_config.h` を追加**: コンパイル時マクロを分離し、定義ファイル（103ファイル）からの依存を `azaraC.h` 全体から `azaraC_config.h` のみに削減した。
  定義ファイルが `Message.h` → `Mt43Data.h` → `NankaiPageBuffer.h` などのライブラリ本体をプルしなくなった。
  ユーザ向けAPIは `#include <azaraC.h>` のまま変更なしとした。
- **災害カテゴリ別コンパイル除外マクロを追加**（全13種）: `AZARAC_ENABLE_EEW`, `AZARAC_ENABLE_HYPOCENTER`, `AZARAC_ENABLE_SEISMIC`, `AZARAC_ENABLE_NANKAI`, `AZARAC_ENABLE_TSUNAMI`, `AZARAC_ENABLE_NW_PAC_TSUNAMI`, `AZARAC_ENABLE_VOLCANO`, `AZARAC_ENABLE_ASH_FALL`, `AZARAC_ENABLE_WEATHER`, `AZARAC_ENABLE_FLOOD`, `AZARAC_ENABLE_TYPHOON`, `AZARAC_ENABLE_MARINE`, `AZARAC_ENABLE_DCX_CAMF` を追加した。
  各 `#define` を0に設定すると対応する定義テーブルがコンパイル時に完全除外される。
- **実データテスト基盤を追加**: `test/tools/decode_to_json.cpp`（NMEA → JSON変換CLI）、`test/scripts/compare_with_azarashi.py`（azarashi比較）、`test/scripts/gen_realdata_vectors.py`（ベクタ自動生成）、`test/integration/test_realdata.cpp`（統合テスト）を追加した。
- **南海トラフE2Eテストを追加**: `test/integration/test_nankai_e2e.cpp` と `test/scripts/compare_nankai_aggregation.py` を追加した。
- **ファズテストを追加**: `test/fuzz/fuzz_decoder.cpp` を追加した。
- **テストケースを拡充**: フレーマーテストで複数 `svId` / チェックサムエラー 2方式 / ガベージリカバリ複数 `svId` を追加し、JSONテストでA9/A10/A11境界値 / Nankai集約後 `text_utf8` 出力 / `unix_time=0` 出力を追加し、azarashi比較テスト（`test_ublox_azarashi.cpp` 等）を追加した。
- **`Makefile` にターゲットを追加**: `decode`（`decode_to_json` ビルド）と `compare-realdata`（azarashi比較実行）を追加した。

### Changed

- **IS-QZSS-DCX-004 / EWSS CAMF v1.2対応**: コメントとドキュメントの参照仕様をIS-QZSS-DCX-003からIS-QZSS-DCX-004に、EWSS CAMF v1.1からv1.2に更新した。
- **azarashi v0.16.4対応**: 各種リファクタに追随し、定義ヘッダをazarashi 0.16.4で再生成した。
- **B1リファインメントを修正 (EWSS CAMF v1.2 §3.7.1.3/4準拠)**: `Message.h` の `b1_major_factor` と `b1_minor_factor` を `b1_refined_semi_major_km` と `b1_refined_semi_minor_km` に変更し、 `DcxHelper::b1InterpolationFactor()` を廃止して `b1RefinedRadiusKm()`（`base_radius_km - delta_km * (code / 8.0)`）を新設した。
  旧実装は補間係数（0.0–0.875）を出力していたが、正しくはリファインメント後の半径（km）を出力するようにした。
- **B2/B3のビット抽出を修正**: `DecoderDcx.cpp` でB2 C5/C6のビットシフト位置を修正し（`>>0` → `>>8`, `>>7` → `>>1`）、B3 C7/C8/C9/C10のビットシフト位置を修正した（`>>0` → `>>13`, `>>2` → `>>10`, `>>5` → `>>5`, `>>10` → `>>0`）。
- **B4を独立デコード化**: `DecoderDcx.cpp` でB4をメイン楕円（A12–A16）の有無に関わらず独立してデコードするようにした。
- **JSONシリアライゼーションを改善**: `JsonSerializerDcx.cpp` で `a4_hazard_definition` フィールドを追加し `a9_selection_of_library` を `a9_type_of_library` に、 `a17_specific_subject` を `a17_type_of_specific_settings` に改名し、 `c10_guidance_label` を `c10_guidance_label` + `c10_guidance_code` に分割し、
    J-Alertの `city_labels` 出力を追加し、B1 refinementのJSONキーを変更した（`c3_major_factor` → `c3_refined_semi_major_km` 等）。
  `JsonSerializerQzqsm.cpp` で降灰情報に `warning_type_label` を追加した。
- **定義ファイルを更新**: azarashi 0.16.4に対応し、ファイル名を仕様書の正式名称に合わせてリネームした（`a9_selection_of_library` → `a9_type_of_library` 等）。
  未使用のA3プロバイダ別ファイル・EX9ファイルを `_index.h` から削除し92定義に整理した。
- **`Parser::feed()` をリファクタ**: `feed()` 内部のカスタムフレーマ経路とAUTOモード経路で重複していたデコード後処理を `postDecode()` メソッドに抽出し、Nankai集約 → Dedupチェック → コピーのパイプラインを1箇所に統一した。
- **`B4DetailedInfo` / `Mt44CamfRaw` のB4フィールドを配列化**: D1–D36の72個の個別フィールドを `b4_d_present[36]` + `b4_d_values[36]` に統合し、`DecoderDcx.cpp` の72行の手動初期化/コピーを `memset` / `memcpy` に置換した（約140行削減）。
  `DcxHelper.cpp` と `JsonSerializerDcx.cpp` を配列インデックスアクセスに統一した。
- **`azaraC.h` の未使用マクロを削除**: `AZARAC_ENABLE_QZSS_DCR_PREAMBLE` を削除した。

### Removed

- `.plans/` ディレクトリ（計画ドキュメント）を削除した。
- `data/` ディレクトリの実データCSV / MDファイルを削除し `realdata/` に移行した。

### Fixed

- **ビルドシステムを修正**: `test/Makefile` のWindowsでのメモリ割り当てを増強した（スタック64MB → 256MB, ヒープ256MB → 512MB）。
- **CI/CDのセキュリティを強化**: `.github/workflows/ci.yml` の全 `actions/checkout` ステップに `persist-credentials: false` を追加した。

## [0.10.0] - 2026-06-27

### Changed

- **DCX-004の小数点以下保証に準拠**: `JsonWriter::wf_d` に `precision` パラメータを追加し（既定3、後方互換性維持）、緯度・経度フィールド（`lat_deg`, `lon_deg` 等）を1e-6度（小数点以下6桁）に、角度フィールド（`azimuth_deg`, `bearing_deg`）を1e-5度（小数点以下5桁）に変更した。
  距離フィールド（`semi_major_km` 等）は1m = 0.001km（小数点以下3桁）のまま維持した。
- `library.properties` の `version` を `0.10.0` に更新した。
- `README.md` の仕様書リファレンスをIS-QZSS-DCX-004 / EWSS CAMF v1.2に更新した。JSON出力例をDCX-004準拠の精度に更新した。
- IS-QZSS-DCX-004に準拠（May, 2026）し、General Assumptions §2.5の丸めルールを適用した（緯度・経度: 10⁻⁶ 度、角度: 10⁻⁵ 度、距離: 1m）。

## [0.9.0] - 2026-06-25

### Changed

- **タグ付き共用体を `placement-new` ベースに移行**: `Message.h` / `Mt43Data.h` のタグ付き共用体をraw storage + `placement-new` / 明示デストラクタ方式に移行し、旧来の共用体メンバ直接アクセスを廃止した。
  `Parser.cpp` のNankai集約パスとdedupパイプラインを `getMt43()` / `getNankai()` アクセサ経由に統一した。
- **NMEA / UBXフレーマのSVID正規化を改善**: `NmeaFramer.cpp` でQZQSM SVID（55–63）をL1S PRN（183–191）に変換するロジックを追加し、64 hex文字（32B）入力の末尾ニブルを `0xF0` でマスクする処理を追加した。
  `UbxFramer.cpp` で `definition/_index.h` の `ublox_qzss_svid_prn_map` を用いたPRN変換に対応した。
- **テストの一部を整理・統合**: 旧テストファイル（`test_crc.cpp` 等）を機能別サブディレクトリに統合した。
- **`.gitignore` を更新**: `.plans/` と `data/` を追加した。

### Fixed

- **ParserのNankai集約パスのエイリアシング対策を強化**: `decoded` と `out` を別オブジェクトとして扱い、`processNankaiAggregation` 内でのエイリアシングUBを回避するようにした。

## [0.8.0] - 2026-06-19

### Added

- **南海トラフページ集約機能を追加**: `NankaiPageBuffer` / `NankaiPageBufferManager` によるスパースページ対応のメモリ効率の良い集約バッファを実装し、`Parser` に複数ページにまたがる南海トラフ地震メッセージの集約ロジックを追加した。
  `test/integration/test_nankai.cpp` を追加した。
- **RTOS (FreeRTOS) 対応を追加**: `examples/rtos_freertos/` にFreeRTOS環境でのNMEA / UBX同時処理サンプルを追加した。
- **JsonWriterユーティリティを追加**: `src/internal/JsonWriter.h` / `JsonWriter.cpp` にプリミティブ型・共通データ構造のJSONシリアライズヘルパを追加した。
- **PrintShimのホストテスト対応を追加**: `src/internal/PrintShim.h` にホストサイドテスト向けストリーム出力オーバーロードを追加した。
- **ファズテスト基盤を追加**: `test/fuzz/fuzz_decoder.cpp` を追加した。
- **カテゴリフィルタリングサンプルを追加**: `examples/filter_by_category/` を追加した。
- **定義ファイル自動生成パイプラインを強化**: `scripts/gen/gen_definitions.py` の改善とCIワークフロー（`update-definitions.yml`）を更新した。
- **CI/CDを拡充**: ホストテスト・ファズテスト・多プラットフォームArduinoコンパイルを統合したGitHub ActionsワークフローとCodeQLセキュリティ解析ワークフローを追加した。

### Changed

- `library.properties` の `version` を `0.8.0` に更新した。
- `src/Parser.cpp` に南海トラフページ集約ロジックを統合した。
- `src/internal/JsonSerializer.h` と `JsonSerializer.cpp` をJsonWriterユーティリティと統合した。
- `examples/` 全般のサンプルをAPIの一般的な使い方に合わせて改善した。
- `TimeFields.h` の時刻フィールド処理を更新した。
- `.gitignore` にネットワーク関連ファイル・CI関連ファイルを追加した。

### Fixed

- ESP32-C3における `Serial2` の設定を修正した。
- 一部ボード定義でのオプション名を修正した。
- `README.md` のUTF-8文字化けを修正した。

## [0.7.0] - 2026-06-07

### Added

- Error Handlingサンプルを追加 (`examples/error_handling/error_handling.ino`): MT=44メッセージのパース失敗を検出してエラー内容を出力するサンプルを追加し、`ParseResultCode` と `error_detail` を用いた具体的なエラーハンドリング方法を提示した。
  エラーコード一覧（001–007, 100–109）に対応するロジックを実装した。
- DCX A17 B2/B3/B4を実装 (EWSS CAMF v1.1 §3.7.2–3.7.4): `DcxHelper.cpp` に `decodeB2HazardCenter()` / `decodeB3SecondaryEllipse()` / `decodeB4DetailedInfo()` を追加し、`DcxHelper.h` に `B2HazardCenter` / `B3SecondaryEllipse` / `B4DetailedInfo` 構造体を追加した。
  `Message.h` の `Mt44CamfRaw` にB2/B3/B4フィールドを追加し、`DecoderDcx.cpp` でA17=01/10/11の場合の解析処理を実装し、`JsonSerializerDcx.cpp` でJSON出力を追加した。

### Changed

- **ディレクトリ構造をリファクタ**: `include/` ディレクトリを作成してArduino配布用ヘッダを分離し、`src/` をテスト用実装ディレクトリに再編成した（`src/decoder/` / `src/framer/` / `src/json/` / `src/helper/` 等）。
  `test/` を機能別サブディレクトリに整理し、旧テストファイル（`test_crc.cpp` 等）を新テストファイルに統合した。
  `src/definition/` の重複を削除し、`library.properties` に `includes=azaraC.h` を追加した。
- `DecoderDcx.cpp` のB2/B3ビット抽出をB1と同じパターン（LSBから順）に統一した。
- `DcxHelper.cpp` のB4各ハザードDフィールドのビット配置をEWSS CAMF v1.1 §3.7.4と整合させた。
- `DecoderDcx.cpp` のB2/B3/B4フィールド初期化を追加し、ゼロクリアした。
- `DecoderDcx.cpp` の構文エラー返却コードを `ParseResultCode::Error` に変更した。
- `DecoderDcx.h` の `parse_result` の型を `ParseResultCode` に変更し旧 `Error` 型を削除した。
- 既定の重複除去スロット数を8に再設定した。
- 言語テーブルの選択的コンパイルオプションを追加した。
- **エラーハンドリングガイドを追加**: エラーハンドリングセクションに全エラーコード一覧（001–007, 100–109）、デコード失敗理由ごとの具体的なハンドリング方法、デコード成功・失敗のフロー図、MT44/MT43共通の処理フローを追記した。`examples/error_handling/error_handling.ino` で実践的に解説した。
- EWSS CAMF v1.1 §3.7.2–3.7.4に準拠し、A17=01 (B2) / A17=10 (B3) / A17=11 (B4) のデコードに対応した。

### Fixed

- `DecoderDcx.cpp` のB3未使用変数警告を `(void)` キャストで修正した。

## [0.6.0] - 2026-05-31

### Added

- DCX A17 B1 (Improved Resolution of Main Ellipse) を実装 (EWSS CAMF v1.1 §3.7.1): `DcxHelper.cpp` に `decodeB1Refinement()` / `b1RefinedLatitudeOffset()` / `b1RefinedLongitudeOffset()` / `b1InterpolationFactor()` を追加し、
    `DcxHelper.h` に `B1Refinement` 構造体を追加した。
  `Message.h` の `Mt44CamfRaw` にB1フィールド（`b1_present`, `b1_c1`–`b1_c4`）を追加し、`Message.h` の `DecodedEllipse` にB1リファインメント値を追加した。
  `DecoderDcx.cpp` でA17=00の場合のB1解析処理を実装した。

### Changed

- `DecoderDcx.cpp` のNull Message検出時のExtended Messageチェックを `getBits` を用いるように修正し、ビット境界の正確性を向上させた。
- EWSS CAMF v1.1 §3.7.1に準拠し、A17=00 (B1) のデコードに対応した。

## [0.5.0] - 2026-05-27

### Added

- **DCX MT44デコーダをIS-QZSS-DCX-003完全準拠でリファクタ**: `DecoderDcx.cpp` を仕様書どおりのビット配置（PAB|MT|SD|CAMF|EX|Reserved|CRC）で再実装した。
  `A2 Country/Region Name` および `A3 Provider Identifier` に基づくサービス種別判定ロジック（L-Alert, J-Alert, Local Government, Outside Japan, Null Message, Unknown）を実装し、Extended Messageのサービス種別ごとの個別パース処理を実装した（L-Alert/Local Government: `EX1..EX7 + Vn`、J-Alert: `EX8..EX10 + Vn`、Outside Japan: `EX11(68bit raw) + Vn`）。
  `Message.h` に `Mt44Decoded` 構造体にデコード済み楕円座標（`DecodedEllipse`）、追加領域（`DecodedAdditionalArea`）、アラート識別子（`Mt44AlertIdentity`）を追加し、`DecodedEllipse` / `DecodedAdditionalArea` / `Mt44AlertIdentity` 構造体を新規定義した。
- **DcxHelper関数を追加**: `decodeLatitude16()`（16-bit緯度 → WGS84度）、 `decodeLongitude17()`（17-bit経度 → WGS84度）、 `decodeLatitude17()`（17-bit緯度, EX3用）、 `decodeLongitude17_45_225()`（17-bit経度, 45–225度範囲）、
    `decodeRadiusCode()`（5-bit半径 → km, Table 4.2-17対数テーブル）、 `decodeAzimuth6()`（6-bit方位角 → 度）、 `decodeAzimuth7()`（7-bit方位角, EX7用）、 `decodePrefectureBitmask()`（EX9 64-bitから都道府県ビットマスクをデコード）、 `decodeCityCodeList()`（EX9 64-bitから市区町村コードリストをデコード）を追加した。
- **テストファイルを追加**: `test/test_dcx_helper.cpp`（DcxHelper全関数）、`test/test_latlon.cpp`（`extractLatLon`）、`test/test_decoder.cpp`（DCX MT44デコード全サービス種別および `decodePrefectureBitmask`）を追加した。

### Changed

- J-Alert都道府県デコードバグを修正 (`check.md` に基づく): `DcxHelper.cpp::decodePrefectureBitmask()` のEX9[63:17] に格納される47-bit都道府県フィールドの抽出ロジックを修正し（`ex9 >> 17` で右シフトしてから検査）、JISコード計算を `47 - i` から `i + 1` に修正した（bit 0 = 北海道/JIS 1）。
- `Message.h` の `Mt44CamfRaw` の `a12` / `a13` のコメントを「unsigned, latitude/longitude code」に更新した。
- `Message.h` の `Mt44ExLAlertOrLocal` の `ex3` / `ex4` のコメントを「unsigned」に更新した。
- IS-QZSS-DCX-003に完全準拠し、サービス種別（Service Kind）の識別ロジックをA2 CountryおよびA3 Providerに基づいて実装し、階層構造化されたCAMFのパース処理を刷新した。

### Fixed

- `DecoderDcx.cpp` のA12/A13の符号付きパース（2の補数）を符号なしパースに修正した（IS-QZSS-DCX-003仕様準拠）。
- `DecoderDcx.cpp` のEX3/EX4の符号付きパースを符号なしパースに修正した。

## [0.4.0] - 2026-05-20

### Added

- **テストスイートを拡充**: `test/test_ublox.cpp`（u-blox SFRBXパケットのデコーダ動作検証およびNMEA出力との整合性確認）と `test/test_coverage.cpp`（MT=43各防災カテゴリの詳細フィールド検証、年末年始・うるう年等の日付境界テスト、NMEA文字数上限や不正プリアンブル等の異常系エッジケース）を追加した。
- **デコーダ内部共通処理を共通化**: `Decoder::readNotifications()`（9-bit防災気象情報通知コード読み出し）、`Decoder::resolveArrivalTime()`（12-bit津波到着日時計算）、`Decoder::extractSignedLatLon()`（台風中心位置等の符号付き緯度・経度抽出）、`Decoder::getSignedBits()`（2の補数符号付きビットフィールド抽出）を追加した。
- `.gitignore` を更新し、VSCode設定、エージェント用作業ファイル（`.agents/`）、ビルド中間ファイルなどを除外対象に追加した。

### Changed

- **MT=44 (DCX) デコーダをIS-QZSS-DCX-003仕様適合に改修**: MT=44 DCXメッセージデコーダおよびJSONシリアライズロジックを `IS-QZSS-DCX-003` 仕様に完全に適合するよう改修し、サービス種別（Service Kind: J-Alert, L-Alert, 地方自治体, 国外等）の識別ロジックを `A2 Country` および `A3 Provider` に基づき行うように修正した。
  階層構造化されたCAMFおよび各種拡張メッセージのパース処理を刷新し、テストベクタとシリアライズ出力を完全同期させた。
  `Message.h` 上の `dcx_type` を `service_kind` へ変更し、`Mt44ServiceKind` / `ExtendedKind` 列挙型および拡張情報領域の各種サブ構造体（`Mt44Sd`, `Mt44CamfRaw`, `Mt44ExLAlertOrLocal`, `Mt44ExJAlert`, `Mt44ExOutside`）を定義した。
- **C++17安全性を向上**: 定義ルックアップ関数の戻り値を `std::string_view` から `std::optional<std::string_view>` に変更し、値が見つからない場合に `std::nullopt` を返すようにして不正なメモリアクセスや未定義動作をコンパイル時に防止した。
  生成されるすべての検索関数に `[[nodiscard]]` 属性を付与し戻り値の無視を防止した。
- `scripts/gen_definitions.py` を `std::optional` および `[[nodiscard]]` 移行に伴い更新した。
  手動管理定義ファイル（`qzss_dcx_camf_a3_provider_identifier.h` および `ublox_qzss_svid_prn_map.h`）も上記C++17安全設計に同期させた。
- `src/internal/JsonSerializer.cpp` に `std::optional<std::string_view>` を受け取る `wf_s` オーバーロードを追加・整理し、`std::nullopt` 時に `v.value_or("")` で空文字列にフォールバックするようにした。
  不要な中間型変換のオーバーロードを削除・最適化した。
- **azarashi定義データを更新**: 対応リファレンスバージョンを `azarashi 0.15.1` から `azarashi 0.16.1` に更新した（`.azarashi-version`）。
  自動生成ヘッダのコメントテンプレートを `AUTO-GENERATED from azarashi {ver} with CI-CD` に更新した。
- **フレーマーの制限強化と検証精度を向上**: `NmeaFramer.cpp` でNMEAのhex文字数が63文字であることを厳密に判定するように変更し、`UbxFramer.cpp` でu-bloxのL1S信号判定において `sigId == 0` に加えて `sigId == 1` も許容するようにした。
  `PrintShim.h` に `std::string_view` のストリーム出力オーバーロードを追加した。
- **プレースホルダー検証を修正**: `test_azarashi.cpp` 等の `CHECK((ok || !ok))` のようなプレースホルダーテストを `CHECK_FALSE(ok)` 等の実際のデコード失敗検証に修正した。
- IS-QZSS-DCX-003仕様への完全適合とC++17標準への準拠・安全性向上を達成した。

### Fixed

- **ビルド時の曖昧警告・エラーを解消**: `JsonSerializer.cpp` のオーバーロード競合を解消するため `std::optional` 型文字列解決用の `wf_s` オーバーロードを整理した。
  `make -C test run` が警告・コンパイルエラーなく全113件のテストケース（578アサーション）を100% SUCCESSで通過することを確認した。

## [0.3.2] - 2026-05-12

### Changed

- `src/internal/Dedup.h` の `AZARAC_DEDUP_SLOTS` の既定値を8から32に拡張し、重複排除の耐性を向上させた。

### Fixed

- `test/test_json.cpp` のMT=43 Seismic IntensityテストケースのカテゴリIDミスを修正した（5 → 3）。
- `test/test_azarashi.cpp` の実態と乖離していたテストケース名（`DCX: Null Msg`）を修正した。
- `test/test_crc.cpp` のDCXデコード時の誤解を招くコメントを修正した。
- `src/internal/JsonSerializer.cpp` の `writeInt32` における `INT32_MIN` 処理時の潜在的な未定義動作を回避した。
- `src/internal/JsonSerializer.cpp` の災害カテゴリ (2, 3, 4, 5, 12, 14) のシリアライザ関数マッピングを修正した。

## [0.3.1] - 2026-04-28

### Fixed

- Definition headersの `static constexpr` を `inline constexpr` に変更した。
   linker-scope symbolとして複数ソースからの参照を可能にした。
- `Decoder::decodeQzqsm` のunused-parameter警告を削除した。

## [0.3.0] - 2026-04-19

### Added

- `examples/with_sntp`（Wi-Fi + SNTP時刻解決 + EEWフィルタ付きサンプル）を追加した。
- `test/test_crc.cpp`（CRC-24Q / `getBits` / MT=44合成フレーム12テスト）を追加した。
- `test/test_json.cpp`（DCX・EEW・震度・津波キー検証 + 全 `disaster_category` ブレースバランス検証, 28テスト）を追加した。
- `test/Makefile` にホストビルド（`make -C test run`）を追加した。
- CIに `host-test` ジョブを追加した（`g++` ホストテスト → `arduino-cli` コンパイルの順）。
- `README` にクイックスタート・API・JSON出力例・定義自動生成フローを追記した。

### Fixed

- `JsonSerializer.h` / `PrintShim.h` / `azaraC.h` の `#ifdef ARDUINO` ガードを `#if defined(ARDUINO) && ARDUINO >= 1` に統一し、`ARDUINO=0` ホストビルドに対応した。
- `Decoder.h` のテスト用サブクラスアクセスのため `private` を `protected` に変更した。
- `Decoder.cpp` の `decodeTsunami` / `decodeNwPacTsu` のunused-parameter警告を修正した。

## [0.2.0] - 2026-04-19

### Added

- MT=43 JMA DC Reportの全12カテゴリをデコード対応した（EEW, Hypocenter, Seismic Intensity, Nankai Trough, Tsunami, NW Pacific Tsunami, Volcano, Ash Fall, Weather, Flood, Marine, Typhoon）。
- `Message` 構造体をカテゴリ別フィールドと繰り返しレコード配列で拡張した。
- `JsonSerializer` でMT=43のJSON出力（カテゴリ別 `detail` サブオブジェクト）を追加した。
- 全ラベル文字列を自動生成 `definition/_index.h` のルックアップ関数経由で解決するようにした（azarashi駆動、ハードコードなし）。

### Changed

- `Decoder::decodeQzqsm` をスケルトンから完全実装に昇格させた。
- `Message.h` をサブ構造体（`TsunamiEntry`, `SeismicEntry`, `WeatherEntry`, `FloodEntry`, `MarineEntry`, `NwPacTsunamiEntry`, `TyphoonPos`）で再構成した。

## [0.1.0] - 2026-04-19

### Added

- UBX（RXM-SFRBX）およびNMEA（`$QZQSM`）のフレーマを追加した。
- CRC-24Q検証を追加した。
- MT=44 DCX/CAMFの全フィールド抽出（A1–A13）を追加した。
- MT=43外枠デコード（スケルトン）を追加した。
- `DedupFilter`（`{svid, msg_type, crc24}` によるリングバッファ重複排除）を追加した。
- `JsonSerializer`（ヒープアロケーションなしの `Print&` 出力）を追加した。
- `Parser`（UBX/NMEA自動判別、pluggable `IFramer` インターフェース）を追加した。
- 102の定義ヘッダをazarashi 0.15.1から自動生成した。
- CIに `arduino-cli` コンパイルチェック（ESP32-C3）を追加した。
- CIにazarashiバージョンbump時の自動PR（日次スケジュール）を追加した。
