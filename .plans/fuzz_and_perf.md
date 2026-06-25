# ファジング・パフォーマンステスト計画

## 1. ファザーの長時間実行改善

### 実装対象

- `test/fuzz/fuzz_decoder.cpp` の `test_long_running()`

### テストケース追加予定ファイル

- `test/fuzz/fuzz_decoder.cpp`

### 仕様書における根拠

- `docs/architecture.md` §3: ヒープアロケーション禁止、静的バッファ使用

### 想定結果

- 50000回イテレーション後もメモリ使用量が安定（増加率 < 10%）
- チェックポイントごとにメモリ使用量を出力

### 使えそうなデータ

- 既存のランダムデータ生成ロジックを流用

---

## 2. NMEA $ 文字消去テスト

### 実装対象

- `test/fuzz/fuzz_decoder.cpp` の `test_corrupted_nmea()`

### テストケース追加予定ファイル

- `test/fuzz/fuzz_decoder.cpp`

### 仕様書における根拠

- `docs/architecture.md` §2: NMEA '$' 文字チェック

### 想定結果

- 先頭の `$` を消した NMEA メッセージは検出されない
- 例外が発生しない

### 使えそうなデータ

- `$QZQSM,55,53AD160D2800039400001A28FFFFEE601800C8F00000000000000011BF8D908*01` の先頭 `$` を除去

---

## 3. UBX SYNC 文字破損テスト

### 実装対象

- `test/fuzz/fuzz_decoder.cpp` の `test_corrupted_ubx()`

### テストケース追加予定ファイル

- `test/fuzz/fuzz_decoder.cpp`

### 仕様書における根拠

- UBX プロトコル: SYNC 文字 `0xB5 0x62` でフレーム開始

### 想定結果

- SYNC 文字が破損した UBX フレームは検出されない
- 例外が発生しない

### 使えそうなデータ

- `makeUbxSfrbx()` で生成したパケットの `pkt[0]` を `0x00` に変更

---

## 4. report_unix=0 + SVID 境界値テスト

### 実装対象

- `test/fuzz/fuzz_decoder.cpp` の `test_boundary_values()`

### テストケース追加予定ファイル

- `test/fuzz/fuzz_decoder.cpp`

### 仕様書における根拠

- IS-QZSS-DCR-016: QZSS 有効範囲 SVID 183-192

### 想定結果

- `report_unix=0` で `svid=0` の場合、デコードが失敗または未解決のままになる
- `report_unix=0` で `svid=255` の場合も同様

### 使えそうなデータ

- `report_unix=0` と `svid=182`, `svid=183`, `svid=192`, `svid=193` の組み合わせ
