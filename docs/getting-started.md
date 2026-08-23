# はじめに

<img src="https://raw.githubusercontent.com/A-vrice/azaraC/refs/heads/main/logo.png" alt="azaraC" width="256">

AzaraC は準天頂衛星みちびきの L1S 災害通報メッセージをデコードする Arduino 向け C++17 ライブラリ。
MT=43（DCR/QZQSM）と MT=44（DCX/CAMF）に対応し、外部依存なし・ヒープ割り当てなしで動作します。
`Parser` が UBX と NMEA を自動判別するため、コードはどちらでも同じです。

## インストール

```bash
# Arduino IDE
git clone https://github.com/A-vrice/azaraC \
  <PROJECT_DIR>/libraries/azaraC

# PlatformIO
git clone https://github.com/A-vrice/azaraC \
  <PROJECT_DIR>/.pio/libdeps/<TARGET_BOARD>/azaraC
```

Library Manager / `pio pkg install` でも導入できます。詳細は [README.md](../README.md) を参照。

## クイックスタート

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

UNIX 時刻を渡すとメッセージの年月日も解決できます。

```cpp
uint32_t now = (uint32_t)time(nullptr);
if (parser.feed(byte, msg, now)) { ... }
```

## コンパイル時設定

`azaraC.h` の前に `#define` で指定します。

| マクロ | デフォルト | 説明 |
| ------ | ---------- | ---- |
| `AZARAC_DEDUP_SLOTS` | 8 | 重複除去リングバッファのスロット数 |
| `AZARAC_LANG_JA` / `AZARAC_LANG_EN` | 1 / 0 | 定義テーブルの言語選択 |
| `AZARAC_ENABLE_*`（13個） | 1 | 災害カテゴリ別の定義テーブル除外 |
| `AZARAC_FLASH_BUF_SIZE` | 800 | AVR の PROGMEM ルックアップ用共有 RAM バッファ |

AVR（Uno 等）ではプリセットにより有効カテゴリが絞られ、バッファサイズも縮小されます。詳細は [README.md](../README.md) を参照。

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
