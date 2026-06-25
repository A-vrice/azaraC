# フレーマー境界値テスト計画

## 1. NMEA ペイロード長 61文字 / 60文字 の境界値テスト

### 実装対象

- `src/framer/NmeaFramer.cpp` のペイロード長バリデーション

### テストケース追加予定ファイル

- `test/framer/test_framer.cpp`

### 仕様書における根拠

- IS-QZSS-DCR-016: NMEA $QZQSM のペイロード長は 63文字（31バイト分の16進数 + 1ニブル）。
- 64文字以上は拒否されるべき。

### 想定結果

- 63文字: 拒否（false を返す、フレーム未検出）
- 64文字: 拒否

### 使えそうなデータ

- `test/test_helpers.h` の `makeNmeaQzqsmHex(63)` / `makeNmeaQzqsmHex(64)` を使用

---

## 2. NMEA 部分フレーム後の正常フレーム復帰

### 実装対象

- `src/framer/NmeaFramer.cpp` の状態管理

### テストケース追加予定ファイル

- `test/framer/test_framer.cpp`

### 仕様書における根拠

- `docs/architecture.md` §2: フレーマー自動判別アルゴリズムで「判別失敗: 次のバイトで再試行」

### 想定結果

- `$QZQSM,55,9AAF` （途中で途切れたフレーム）→ フレーム未検出
- その後に `$QZQSM,55,53AD160D2800039400001A28FFFFEE601800C8F00000000000000011BF8D908*01\r\n` （正常フレーム）→ フレーム検出成功

### 使えそうなデータ

- `test/data/dcr_vectors.json` の `test_helpers.h` の `makeNmeaQzqsm()` を使用

---

## 3. UBX SFRBX 不正 length フィールドの拒否

### 実装対象

- `src/framer/UbxFramer.cpp` の length バリデーション

### テストケース追加予定ファイル

- `test/framer/test_framer.cpp`

### 仕様書における根拠

- UBX-RXM-SFRBX 仕様: length = 8 + 8×4 = 40 バイト（固定）

### 想定結果

- length が 40 以外の場合、フレームとして検出されない

### 使えそうなデータ

- `test/test_helpers.h` の `makeUbxSfrbx()` で正常パケット生成後、`pkt[4]` や `pkt[5]` を改変して length を不正にする

---

## 4. UBX 複数メッセージ連続テスト

### 実装対象

- `src/framer/UbxFramer.cpp` の連続フレーム処理

### テストケース追加予定ファイル

- `test/framer/test_framer.cpp`

### 仕様書における根拠

- `docs/architecture.md` §2: UbxFramer は UBX-RXM-SFRBX を処理

### 想定結果

- 2つの有効な UBX フレームを連続して投入した場合、両方とも正しく検出される

### 使えそうなデータ

- `test/test_helpers.h` の `makeUbxSfrbx(2, bits1)` と `makeUbxSfrbx(3, bits2)` を連続して使用

---

## 5. NMEA チェックサム `*00` / `*FF` の境界値テスト

### 実装対象

- `src/framer/NmeaFramer.cpp` のチェックサム検証

### テストケース追加予定ファイル

- `test/framer/test_framer.cpp`

### 仕様書における根拠

- NMEA 0183: チェックサムは `$` と `*` の間の全バイトの XOR

### 想定結果

- `*00` は正しいチェックサムと一致しない限り拒否される
- `*FF` も同様

### 使えそうなデータ

- `test/test_helpers.h` の `makeNmeaQzqsm()` で正しいチェックサムを計算し、その後 `*00` や `*FF` に書き換えたものを生成
