<img src="https://raw.githubusercontent.com/A-vrice/azaraC/refs/heads/main/logo.png" width="256">

# AzaraC

準天頂衛星みちびき（QZSS）L1S 信号の災害通報メッセージをデコードする Arduino 向け C++17 ライブラリ。[azarashi](https://github.com/nbtk/azarashi)（Python）の移植です。外部依存ゼロ、ヒープアロケーションなし。

## 対応メッセージ

| msg_type | 規格            | 名称            |
| -------- | --------------- | --------------- |
| 43       | IS-QZSS-DCR-016 | DCR 12種類（QZQSM） |
| 44       | IS-QZSS-DCX-004 | DCX / CAMF（L-Alert, J-Alert など） |

## インストール

```bash
# Arduino IDE
git clone https://github.com/A-vrice/azaraC <PROJECT_DIR>/libraries/azaraC

# PlatformIO
git clone https://github.com/A-vrice/azaraC <PROJECT_DIR>/.pio/libdeps/<TARGET_BOARD>/azaraC
```

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

`feed()` は UBX（RXM-SFRBX）と NMEA（$QZQSM）を自動判別します。UNIX 時刻を渡すとメッセージの年月日も解決できます。

```cpp
uint32_t now = (uint32_t)time(nullptr);
if (parser.feed(byte, msg, now)) { ... }
```

## コンパイル時設定

`azaraC.h` をインクルードする前に `#define` で指定します（`azaraC_config.h` に一元管理）。

| マクロ | デフォルト | 説明 |
| ------ | ---------- | ---- |
| `AZARAC_DEDUP_SLOTS` | 8 | 重複除去リングバッファのスロット数 |
| `AZARAC_LANG_JA` / `AZARAC_LANG_EN` | 1 / 0 | 定義テーブルの言語選択 |
| `AZARAC_ENABLE_*`（13個） | 1 | 災害カテゴリ別の定義テーブル除外 |
| `AZARAC_NANKAI_*` | 12 / 4 | 南海トラフページ集約のバッファ設定 |
| `AZARAC_FLASH_BUF_SIZE` | 800 | AVR の PROGMEM ルックアップ用共有 RAM バッファ |

AVR（Arduino Uno 等）では RAM/Flash が少ないため、プリセットにより有効カテゴリが SEISMIC/TSUNAMI のみに絞られます。

## Examples

詳細な使用例は [`examples/`](examples/) を参照してください。

| Example | 説明 |
| ------- | ---- |
| [basic_nmea](examples/basic_nmea/) | NMEA $QZQSM の基本的な使用例 |
| [basic_ubx](examples/basic_ubx/) | UBX-RXM-SFRBX の基本的な使用例 |
| [basic_uno](examples/basic_uno/) | Arduino Uno (AVR) 用最小例 |
| [with_sntp](examples/with_sntp/) | SNTP時刻解決 + EEWフィルタ |
| [filter_by_category](examples/filter_by_category/) | 災害カテゴリ別フィルタリング |
| [error_handling](examples/error_handling/) | エラーハンドリングと統計 |
| [wifi_client](examples/wifi_client/) | Wi-Fi クライアント出力 |
| [rtos_freertos](examples/rtos_freertos/) | FreeRTOS タスクベース処理 |

## テスト

```bash
make -C test run
```

## ドキュメント

詳細は [`docs/`](docs/README.md) を参照してください。

- [クイックスタート & 使用例](docs/README.md)
- [API リファレンス](docs/api-reference.md)
- [アーキテクチャ](docs/architecture.md)
- [開発者ガイド](docs/developer-guide.md)

## ライセンス

MIT（定義テーブルは [azarashi](https://github.com/nbtk/azarashi)(MIT) 由来）

本ライブラリは非公式なものであり，準天頂衛星システムサービス株式会社，JAXA，その他公共機関など，「みちびき」に関連する組織，NBTK氏の提供するazarashiとは一切関係ありません。また，あるふぁ米およびそのコントリビューターは，受信したメッセージや本ライブラリの出力内容の正確性，完全性，その他のいかなるものについても保証しません。本ライブラリを使用したことによるいかなる損害についても責任は負いかねます。本ライブラリは現状有姿で提供されます。また，本ライブラリを利用される際はQSSの免責条項[参考](https://qzss.go.jp/technical/dod/dc-report/users-manual_agree.html)を確認することを推奨します。

## 不具合など

何か不具合、疑問点があれば[Issue](https://github.com/A-vrice/azaraC/issues)，作者メールアドレス[AzaraC@vrice.f5.si]，およびTwitter(現X)のDMまでお願いします。