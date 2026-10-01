# はじめに

<img src="../logo.svg" alt="azaraCのロゴ" height="128">


準天頂衛星みちびき(QZSS)から発信された[災危通報メッセージ](https://qzss.go.jp/overview/services/sv08_dc-report.html)をデコードするC++17製のArduino向けライブラリです。[azarashi](https://github.com/nbtk/azarashi)(Python/MIT)の定義テーブルを参照しますが、マイコンや組み込みなどでも省リソースで動作します。

## インストール

```bash
# Arduino IDE
git clone https://github.com/A-vrice/azaraC \
  <PROJECT_DIR>/libraries/azaraC

# PlatformIO
git clone https://github.com/A-vrice/azaraC \
  <PROJECT_DIR>/.pio/libdeps/<TARGET_BOARD>/azaraC
```

> **注:** Library Manager / `pio pkg install` は未申請のため現時点で利用できません。

## クイックスタート

ライブラリ側でプロトコルを自動判別するため、UBX/NMEAの形式を問わずそのままデコードできます。

```cpp
#include <azaraC.h>

azaraC::Parser  parser;
azaraC::Message msg;

void setup() {
    Serial.begin(115200);
    Serial1.begin(9600, SERIAL_8N1, /*rx=*/20, /*tx=*/21);
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

`azaraC.h`の前に`#define`で指定します。

| マクロ | デフォルト | 説明 |
| ------ | ---------- | ---- |
| `AZARAC_DEDUP_SLOTS` | 512 | 重複判定表のエントリ数（1エントリ8B。AVRプリセットは64） |
| `AZARAC_DEDUP_WAYS` | 8 | 重複判定表の連想度 |
| `AZARAC_DEDUP_WINDOW_MS` | 86400000 | 情報有効時間(ms)のフォールバック。災害種別ごとの配信終了条件に無いカテゴリだけが使う |
| `AZARAC_NANKAI_MAX_PAGES` / `AZARAC_NANKAI_BUFFERS` | 63 / 1 | 防災気象情報(南海トラフ地震)の最大収集ページ数(1-63)と最大同時追跡数(1-32) |
| `AZARAC_LANG_JA` / `AZARAC_LANG_EN` | 1 / 0 | 定義テーブルの言語選択 |
| `AZARAC_ENABLE_*`（13個） | 1 | 災害カテゴリ別のデコード有効化/無効化|
| `AZARAC_FLASH_BUF_SIZE`(AVRボードのみ) | 800 | AVRボードのPROGMEM参照用RAMバッファのサイズ |

AVR（Arduino Uno等）では専用プリセットにより有効カテゴリが絞られ、バッファサイズも縮小されます。プリセット値とメモリ要件の詳細は [アーキテクチャ](architecture.md#メモリ設計) を参照してください。

## Examples

| Example | 説明 |
| ------- | ---- |
| [basic_nmea](../examples/basic_nmea/) | NMEA $QZQSM の基本的な使用例 |
| [basic_ubx](../examples/basic_ubx/) | UBX-RXM-SFRBX の基本的な使用例 |
| [basic_uno](../examples/basic_uno/) | Arduino Uno (AVR) 用最小例 |
| [with_sntp](../examples/with_sntp/) | SNTP 時刻解決 + EEW フィルタ |
| [filter_by_category](../examples/filter_by_category/) | 災害カテゴリ別フィルタリング |
| [error_handling](../examples/error_handling/) | エラーハンドリングと統計 |
| [wifi_client](../examples/wifi_client/) | Wi-Fi クライアント出力 |
| [rtos_freertos](../examples/rtos_freertos/) | FreeRTOS タスクベース処理 |

## テスト

```bash
make -C test run
```

## ドキュメント

| ドキュメント | 内容 |
| ------------ | ---- |
| [API リファレンス](api-reference.md) | 詳細な API 仕様・データ構造 |
| [アーキテクチャ](architecture.md) | 内部設計とデータフロー |
| [開発者ガイド](developer-guide.md) | ビルド方法、テスト、コーディング規約 |
| [JSON 出力仕様](json-formats.md) | azaraC の出力スキーマと azarashi との対応 |
