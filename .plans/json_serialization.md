# JSON シリアライズテスト計画

## 1. JSON エスケープ文字テスト

### 実装対象

- `src/json/JsonWriter.cpp` の `writeStr()` 関数

### テストケース追加予定ファイル

- `test/json/test_json.cpp`

### 仕様書における根拠

- `docs/architecture.md` §6: JsonSerializer はヒープアロケーションなしで固定バッファ処理
- JSON 仕様 (RFC 8259): 文字列内の `"` `\` と制御文字はエスケープが必要（`/` は任意）

### 想定結果

- 文字列フィールドに `"` が含まれる場合、`\"` としてエスケープされる
- `\` は `\\` としてエスケープされる
- `\n` は `\\n` としてエスケープされる
- `\r` は `\\r` としてエスケープされる
- `\t` は `\\t` としてエスケープされる

### 使えそうなデータ

- 合成データ: `writeStr("test\"value")` → `"test\\\"value"` が出力されることを確認
- 定義テーブルのラベルに特殊文字がないか確認（`src/definition/*.h` の lookup テーブル）

---

## 2. MT=43 report_time の JSON 出力

### 実装対象

- `src/json/JsonSerializer.cpp` の `writeDHM(out, "report_time", d->event_time)` 呼び出し

### テストケース追加予定ファイル

- `test/json/test_json.cpp`

### 仕様書における根拠

- `docs/architecture.md` §6: JsonSerializer は Message を JSON 形式にシリアライズ
- IS-QZSS-DCR-016 §5.1.2.1: report_time は month/day/hour/minute

### 想定結果

- JSON に `"report_time":{"month":1,"day":1,"hour":0,"minute":0,"unix_time":1704067200}` のようなフィールドが含まれる

### 使えそうなデータ

- `data/qzqsm_20240101-0107_noto.csv` の各レコードから report_time を生成

---

## 3. MT=44 onset_time の JSON 出力

### 実装対象

- `src/json/JsonSerializerDcx.cpp` の `writeDHM(out, "onset_time", d->onset_time)` 呼び出し

### テストケース追加予定ファイル

- `test/json/test_json.cpp`

### 仕様書における根拠

- IS-QZSS-DCX-003 §4.2.3: onset_time は A6/A7 から計算

### 想定結果

- JSON に `"onset_time":{"month":...,"day":...,"hour":...,"minute":...,"unix_time":...}` が含まれる

### 使えそうなデータ

- A6=0, A7=1 以上の値で onset_time が計算される合成フレーム

---

## 4. MT=44 sd_sdmt=1 のテスト

### 実装対象

- `src/json/JsonSerializerDcx.cpp` の `sd_sdmt` 出力

### テストケース追加予定ファイル

- `test/json/test_json.cpp`

### 仕様書における根拠

- IS-QZSS-DCX-003 §4.2.2: SD (Satellite Designation) の sdmt (1 bit)

### 想定結果

- `"sd_sdmt":1` が出力される

### 使えそうなデータ

- `bits[14] = 1` にセットした合成フレーム

---

## 5. MT=44 a6=0 / a8=0 / a9=0 / a10=0 / a11=0 のテスト

### 実装対象

- `src/json/JsonSerializerDcx.cpp` の各フィールド出力

### テストケース追加予定ファイル

- `test/json/test_json.cpp`

### 仕様書における根拠

- IS-QZSS-DCX-003 §4.2.3: A6 (1 bit), A8 (2 bits), A9 (1 bit), A10 (3 bits), A11 (10 bits)

### 想定結果

- 各フィールドが 0 で出力される
- ルックアップラベルも 0 に対応するラベル（"Unknown" など）が出力される

### 使えそうなデータ

- A6-A11 を全て0にセットした合成フレーム

---

## 6. MT=43 event_time 未解決 (report_unix=0) の JSON 出力

### 実装対象

- `src/json/JsonSerializer.cpp` の `writeDHM()` の unix_time=0 ケース

### テストケース追加予定ファイル

- `test/json/test_json.cpp`

### 仕様書における根拠

- `src/Message.h` の `TimeFields.unix_time`: 0 = not resolved

### 想定結果

- `"unix_time":0` が出力される
- month/day/hour/minute は report_unix から計算された値が入る

### 使えそうなデータ

- `decodeNmea(nmea, msg)` の第三引数に 0 を渡す（デフォルト）
