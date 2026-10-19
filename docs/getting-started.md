# はじめに

<img src="../logo.svg" alt="azaraCのロゴ" height="128">


準天頂衛星みちびき(QZSS)から発信された[災危通報メッセージ](https://qzss.go.jp/overview/services/sv08_dc-report.html)をデコードするC++17製のArduino向けライブラリです。[azarashi](https://github.com/nbtk/azarashi)(Python/MIT)の定義テーブルを参照しますが、マイコンや組み込みなどでも省リソースで動作します。

## インストール

パッケージマネージャーから導入できます:

```bash
# Arduino Library Manager（Arduino IDE / arduino-cli）
arduino-cli lib install azaraC

# PlatformIO
pio pkg install --library "a-vrice/azaraC"
```

開発版は git clone でも導入できます:

```bash
# Arduino IDE
git clone https://github.com/A-vrice/azaraC \
  <PROJECT_DIR>/libraries/azaraC

# PlatformIO
git clone https://github.com/A-vrice/azaraC \
  <PROJECT_DIR>/.pio/libdeps/<TARGET_BOARD>/azaraC
```

## クイックスタート

ライブラリ側でプロトコルを自動判別するため、UBX/NMEAの形式を問わずそのままデコードできます。

```cpp
#include <azaraC.h>

azaraC::Parser  parser;
azaraC::Message msg;

void setup() {
    Serial.begin(115200);
#if defined(ESP32)
    // ESP32 のピン配置。AVR（Uno など）は Serial1 が無いので examples/basic_uno を参照
    Serial1.begin(9600, SERIAL_8N1, /*rx=*/20, /*tx=*/21);
#else
    Serial1.begin(9600);
#endif
}

void loop() {
    while (Serial1.available()) {
        if (parser.feed(Serial1.read(), msg)) {
            azaraC::toJson(msg, Serial);
            Serial.println();
        }
    }
}
```

UNIX時刻を渡すと発生時刻の年月日も解決/推測できます。

```cpp
uint32_t now = (uint32_t)time(nullptr);
if (parser.feed(byte, msg, now)) { ... }
```

## コンパイル時設定

ビルドフラグ（PlatformIO の `build_flags`、arduino-cli の `--build-property compiler.cpp.extra_flags=...` など）で `-D` を渡して指定します。スケッチ冒頭の `#define` はライブラリの `.cpp`（別 TU）には届かず、`Parser` などのサイズが TU 間でずれるため使えません。

| マクロ | デフォルト | 説明 |
| ------ | ---------- | ---- |
| `AZARAC_DEDUP_SLOTS` | 512 | 重複判定表のエントリ数（1エントリ8B。AVRプリセットは64） |
| `AZARAC_DEDUP_WAYS` | 8 | 重複判定表の連想度 |
| `AZARAC_DEDUP_WINDOW_MS` | 86400000 | 情報有効時間(ms)のフォールバック。災害種別ごとの配信終了条件と MT=44 の A8 由来の窓に無いカテゴリだけが使う |
| `AZARAC_DEDUP_MT44_MAX_WINDOW_MS` | 300000 | MT=44 の情報有効時間(ms)の上限。AVRのみ定義（ホストは A8 由来の窓をそのまま使用） |
| `AZARAC_NANKAI_MAX_PAGES` / `AZARAC_NANKAI_BUFFERS` | 63 / 1 | 防災気象情報(南海トラフ地震)の最大収集ページ数(1-63)と最大同時追跡数(1-32) |
| `AZARAC_LANG_JA` / `AZARAC_LANG_EN` | 1 / 0 | 定義テーブルの言語選択 |
| `AZARAC_ENABLE_*`（13個） | 1（AVR は SEISMIC/TSUNAMI のみ） | 災害カテゴリ別のデコード有効化/無効化。AVR で DCX/CAMF を使うには `-DAZARAC_AVR_LARGE_FLASH=1` または `-DAZARAC_ENABLE_DCX_CAMF=1` を明示する |
| `AZARAC_FLASH_BUF_SIZE` | カテゴリ連鎖（AVR既定=64） | PROGMEM参照用RAMバッファのサイズ。AVRでは有効カテゴリに応じて 64 / 80 / 96 / 540 / 640 / 800 に自動選択（有効なカテゴリの最長ラベルを収める）。非AVRでは使われない |

AVR（Arduino Uno等）では専用プリセットにより有効カテゴリが SEISMIC/TSUNAMI のみに絞られ、バッファサイズも縮小されます（チップ名では何も有効化しません）。プリセット値とメモリ要件の詳細は [アーキテクチャ](architecture.md#メモリ設計) を参照してください。

## Examples

| Example | 説明 |
|-------|----|
| [basic_nmea](https://github.com/A-vrice/azaraC/tree/main/examples/basic_nmea/) | NMEA $QZQSM の基本的な使用例 |
| [basic_ubx](https://github.com/A-vrice/azaraC/tree/main/examples/basic_ubx/) | UBX-RXM-SFRBX の基本的な使用例 |
| [basic_uno](https://github.com/A-vrice/azaraC/tree/main/examples/basic_uno/) | Arduino Uno (AVR) 用最小例 |
| [with_sntp](https://github.com/A-vrice/azaraC/tree/main/examples/with_sntp/) | SNTP 時刻解決 + EEW フィルタ |
| [filter_by_category](https://github.com/A-vrice/azaraC/tree/main/examples/filter_by_category/) | 災害カテゴリ別フィルタリング |
| [error_handling](https://github.com/A-vrice/azaraC/tree/main/examples/error_handling/) | エラーハンドリングと統計 |
| [wifi_client](https://github.com/A-vrice/azaraC/tree/main/examples/wifi_client/) | Wi-Fi クライアント出力 |
| [rtos_freertos](https://github.com/A-vrice/azaraC/tree/main/examples/rtos_freertos/) | FreeRTOS タスクベース処理 |

## テスト

```bash
make -C test run
```

## ドキュメント

| ドキュメント | 内容 |
|------------|----|
| [API リファレンス](api-reference.md) | 詳細な API 仕様・データ構造 |
| [アーキテクチャ](architecture.md) | 内部設計とデータフロー |
| [開発者ガイド](developer-guide.md) | ビルド方法、テスト、コーディング規約 |
| [JSON 出力仕様](json-formats.md) | azaraC の出力スキーマと azarashi との対応 |
