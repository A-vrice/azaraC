# デコーダエッジケーステスト計画

## 1. MT=43 disaster_category=7 (未割り当て) のエラーハンドリング

### 実装対象
- `src/decoder/DecoderQzqsm.cpp` の `decodeQzqsm()` における `default: return false` 分岐

### テストケース追加予定ファイル
- `test/integration/test_error_handling.cpp`

### 仕様書における根拠
- IS-QZSS-DCR-016 Table 5.1.2-1: disaster_category は 1-12, 14 が有効。7 と 13 は未割り当て。
- `docs/architecture.md` §3: 「MT=43 (QZQSM) サブデコーダー」のテーブルに category 7, 13 は存在しない。

### 想定結果
- `decodeQzqsm()` が `false` を返す
- `msg.valid` が `false` のままになる

### 使えそうなデータ
- `test/data/dcr_vectors.json` の既存ベクトルを改変し、`disaster_category` を 7 にした合成ベクトルを生成
- または `test/test_helpers.h` の `setBits()` で `bits[17..20] = 0b0111` (7) をセットしたフレームを構築

---

## 2. MT=43 disaster_category=13 (未割り当て) のエラーハンドリング

### 実装対象
- 上記と同じ `default: return false` 分岐

### テストケース追加予定ファイル
- `test/integration/test_error_handling.cpp`

### 仕様書における根拠
- IS-QZSS-DCR-016 Table 5.1.2-1: category 13 は予約済み

### 想定結果
- `decodeQzqsm()` が `false` を返す

### 使えそうなデータ
- `bits[17..20] = 0b1101` (13) をセットしたフレーム

---

## 3. MT=43 report_classification の全値網羅

### 実装対象
- `src/decoder/DecoderQzqsm.cpp` の `d->report_classification = getBits(bits, 14, 3)`

### テストケース追加予定ファイル
- `test/core/test_core.cpp` または新規 `test/core/test_report_classification.cpp`

### 仕様書における根拠
- IS-QZSS-DCR-016 §5.1.2.1: report_classification (3 bits) = 0-7
- 値の意味: 0=未使用, 1=訓練, 2=試験, 3=発表, 4=訂正, 5=取消, 6=予報, 7=実況

### 想定結果
- 各値でデコードが成功し、`msg.getMt43()->report_classification` が正しい値を持つ

### 使えそうなデータ
- `data/qzqsm_history.md` から各 classification の実例を取得:
  - 1=訓練: `9AAF8DED25000325BA00DA4A0F5AAC5A8000000008000000200000136DCCFB4*02`
  - 3=発表: `9AAC89558B0003240000AB160F3A2499B40000000000002000000010C93712C*0F`
  - 4=訂正: `53AD15BA49800351C5007412FFC7EE405E00FCC00000000000000012A54CEC8*7F`
  - 5=取消: `9AADDD34A78000E0A8F548908E0A8F54DD60E0A8F584EB00000000128716040*07`

---

## 4. MT=43 information_type の全値網羅

### 実装対象
- `src/decoder/DecoderQzqsm.cpp` の `d->information_type = getBits(bits, 41, 2)`

### テストケース追加予定ファイル
- `test/core/test_core.cpp`

### 仕様書における根拠
- IS-QZSS-DCR-016 §5.1.2.1: information_type (2 bits) = 0-3
- 値の意味: 0=地震, 1=津波, 2=火山, 3=気象

### 想定結果
- 各値でデコードが成功し、`msg.getMt43()->information_type` が正しい値を持つ

### 使えそうなデータ
- `data/qzqsm_20240101-0107_noto.csv` から各 information_type の実例を取得

---

## 5. MT=44 A12=0 かつ EX1≠0 の target_area_code

### 実装対象
- `src/decoder/DecoderDcx.cpp` の `target_area_code_present` ロジック

### テストケース追加予定ファイル
- `test/integration/test_parser.cpp`

### 仕様書における根拠
- IS-QZSS-DCX-003 §4.2.3: EX1 は target area code。main ellipse (A12-A15) が全て0の場合、EX1 が target area として使用される。

### 想定結果
- `dec.target_area_code_present == true`
- `dec.target_area_code == ex1_value`

### 使えそうなデータ
- A12-A15 を全て0、EX1 に有効な値（例: 1100 = 札幌市中央区）をセットした合成フレーム

---

## 6. MT=44 EX8=1 (city code list) モード

### 実装対象
- `src/internal/DcxHelper.cpp` の `decodeCityCodeList()`
- `src/decoder/DecoderDcx.cpp` の `city_code_count` 処理

### テストケース追加予定ファイル
- `test/integration/test_parser.cpp`

### 仕様書における根拠
- IS-QZSS-DCX-003 §4.2.3.2: EX8=1 の場合、EX9 は 4つの 16-bit city/town/village code を含む。

### 想定結果
- `dec.jalert_prefecture_mode == false`
- `dec.city_code_count` が有効なコードの数（1-4）と一致
- `dec.city_codes[]` に正しいコードが格納

### 使えそうなデータ
- EX8=1、EX9 に 4つの city code（例: 1100, 1101, 1102, 1103）をセットした合成フレーム

---

## 7. MT=44 Outside Japan ex11_raw のJSON出力

### 実装対象
- `src/json/JsonSerializerDcx.cpp` の `ex_outside.ex11_raw` の16進列出力

### テストケース追加予定ファイル
- `test/json/test_json.cpp`

### 仕様書における根拠
- IS-QZSS-DCX-003 §4.2.3.3: Outside Japan の場合、EX11 は 68-bit の raw データ。

### 想定結果
- JSON に `"ex11_raw":"..."` の16進数文字列が含まれる

### 使えそうなデータ
- `test/integration/test_azarashi_dcx.cpp` の Fiji テストベクトル: `$QZQSM,56,9AB08408E0598969E00066AFFE8E6F70091200000000000000000100CD1A410*0C`

---

## 8. MT=44 A17/A18 specific settings の意味テスト

### 実装対象
- `src/json/JsonSerializerDcx.cpp` の `a17_specific_subject` / `a18_specific_settings` 出力

### テストケース追加予定ファイル
- `test/json/test_json_dcx_b1b4.cpp`

### 仕様書における根拠
- IS-QZSS-DCX-003 §4.2.3.1: A17 (2 bits) = specific subject for specific settings
- A18 (15 bits) = specific settings (B1-B4 に意味が依存)

### 想定結果
- `a17_specific_subject` のルックアップラベルが正しく出力される
- `a18_specific_settings` の raw 値が正しく出力される

### 使えそうなデータ
- A17=0, 1, 2, 3 の各値で A18 にダミーデータをセットした合成フレーム

---

## 9. MT=44 D36 (typhoon category) の単独テスト

### 実装対象
- `src/internal/DcxHelper.cpp` の `decodeB4DetailedInfo()` の `case 82` (Typhoon)

### テストケース追加予定ファイル
- `test/json/test_json_dcx_b1b4.cpp`

### 仕様書における根拠
- IS-QZSS-DCX-003 §3.7.4: D36 (3 bits) = Typhoon category

### 想定結果
- `d36_present == true`
- `d36` の値が正しくデコードされ、ルックアップラベルが出力される

### 使えそうなデータ
- A4=82 (Typhoon) で A18 の d36 ビットが設定された合成フレーム
