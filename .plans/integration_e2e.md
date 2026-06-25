# 統合テスト E2E テスト計画

## 1. Nankai 27ページ完全集約 E2E テスト

### 実装対象
- `src/Parser.cpp` の Nankai ページ集約ロジック
- `src/internal/NankaiPageBuffer.h` の集約バッファ

### テストケース追加予定ファイル
- `test/integration/test_nankai_e2e.cpp`

### 仕様書における根拠
- IS-QZSS-DCR-016 §5.1.2.3.4: 南海トラフは最大63ページ（実際には27ページのテストベクトルが存在）
- `docs/architecture.md` §5: NankaiPageBuffer の集約処理

### 想定結果
- 27ページの全メッセージを順番に投入後、`nankai->is_aggregated == true`
- `nankai->aggregated_len` が全ページのテキスト長と一致
- `nankai->aggregated_text` に連結されたテキストが格納

### 使えそうなデータ
- `test/data/nankai_vectors.json`: 27ページ分のテストベクトル
- `test/integration/test_azarashi_dcr.cpp` の NankaiCase 配列（20ページ分）を拡張

---

## 2. Nankai 集約後の text_utf8 出力テスト

### 実装対象
- `src/json/JsonSerializerQzqsm.cpp` の `serializeNankai()` の `text_utf8` 出力

### テストケース追加予定ファイル
- `test/json/test_json.cpp`

### 仕様書における根拠
- `docs/architecture.md` §6: JsonSerializer の text_utf8 出力

### 想定結果
- 集約完了後、JSON に `"text_utf8":"南海トラフ地震..."` が含まれる
- ページ未集約時は `"text_hex":[...]` が出力される

### 使えそうなデータ
- `test/integration/test_nankai.cpp` の UTF-8 テストデータ（`"こんにちは"` → `"南海トラフ地震"`）

---

## 3. Nankai ページ欠損時の動作

### 実装対象
- `src/internal/NankaiPageBuffer.h` の `isComplete()` ロジック

### テストケース追加予定ファイル
- `test/integration/test_nankai.cpp`

### 仕様書における根拠
- `docs/architecture.md` §5: ページ集約は全ページ受信で完了

### 想定結果
- 27ページ中1ページが欠損しても `isComplete() == false`
- `isAggregated() == false`

### 使えそうなデータ
- `test/data/nankai_vectors.json` から1ページを除外したデータセット

---

## 4. Nankai ページ重複時の動作

### 実装対象
- `src/internal/NankaiPageBuffer.h` の `addPage()` の重複チェック

### テストケース追加予定ファイル
- `test/integration/test_nankai.cpp`

### 仕様書における根拠
- `docs/architecture.md` §5: 重複ページは拒否される

### 想定結果
- 同じページ番号が2回来た場合、2回目は拒否（`addPage()` が `false` を返す）
- `received_pages` は増えない

### 使えそうなデータ
- `test/data/nankai_vectors.json` の同じページを2回投入

---

## 5. Nankai イベント間切り替え

### 実装対象
- `src/internal/NankaiPageBuffer.h` の NankaiPageBufferManager

### テストケース追加予定ファイル
- `test/integration/test_nankai.cpp`

### 仕様書における根拠
- `docs/architecture.md` §5: NankaiPageBufferManager は複数のイベントを管理

### 想定結果
- 異なる `info_code` の2つのイベントが混在しても、それぞれ独立して集約される

### 使えそうなデータ
- `test/data/nankai_vectors.json` の異なる info_code のイベント

---

## 6. Nankai バッファ制限後の同キー再作成

### 実装対象
- `src/internal/NankaiPageBuffer.h` の LRU eviction

### テストケース追加予定ファイル
- `test/integration/test_nankai.cpp`

### 仕様書における根拠
- `docs/architecture.md` §5: MAX_BUFFERS を超えた場合、最も古いバッファを解放

### 想定結果
- eviction 後、同じキーで新規作成が可能
- 新しいバッファは空の状態で開始

### 使えそうなデータ
- `test/integration/test_nankai.cpp` の `NankaiPageBufferManager buffer limit` テストを拡張

---

## 7. Parser reset後の Nankai バッファ状態

### 実装対象
- `src/Parser.cpp` の `reset()` メソッド

### テストケース追加予定ファイル
- `test/integration/test_nankai_e2e.cpp`

### 仕様書における根拠
- `docs/architecture.md` §1: Parser の reset メソッド

### 想定結果
- `parser.reset()` 後、Nankai バッファもクリアされる
- 同じメッセージを再投入すると、新しく集約が開始される

### 使えそうなデータ
- `test/data/nankai_vectors.json` の1ページ目のみ投入 → reset → 再投入

---

## 8. NMEA+UBX 複雑シーケンス

### 実装対象
- `src/Parser.cpp` のフレーマー自動判別

### テストケース追加予定ファイル
- `test/integration/test_parser_integration.cpp`

### 仕様書における根拠
- `docs/architecture.md` §2: フレーマー自動判別アルゴリズム

### 想定結果
- UBX → NMEA → UBX の順番でメッセージを投入しても、各メッセージが正しくデコードされる

### 使えそうなデータ
- `test/data/ublox_vectors.json` と `test/data/dcr_vectors.json` の組み合わせ
