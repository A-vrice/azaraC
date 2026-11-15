# はじめに

<img src="../logo.svg" alt="azaraCのロゴ" height="128">


準天頂衛星みちびき(QZSS)から発信された[災危通報メッセージ](https://qzss.go.jp/overview/services/sv08_dc-report.html)をデコードするライブラリです。
C++17製のArduino向け実装となっています。
[azarashi](https://github.com/nbtk/azarashi)(Python/MIT)の定義テーブルを参照しますが、マイコンや組み込みなどでも省リソースで動作します。

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

> 注: この例は `Serial1` を持たないボード（Uno など）を対象外とします。AVR でも Mega / Leonardo のように `Serial1` を持つボードではそのまま動きます。Uno などでは [examples/basic_uno](https://github.com/A-vrice/azaraC/tree/main/examples/basic_uno/) を参照してください。

```cpp
#include <azaraC.h>

azaraC::Parser  parser;
azaraC::Message msg;

void setup() {
    Serial.begin(115200);
#if defined(ARDUINO_ESP32C3_DEV) || defined(CONFIG_IDF_TARGET_ESP32C3)
    // ESP32-C3 の UART0 既定ピン（20/21）。Serial1 を持たないボード（Uno など）は examples/basic_uno を参照
    Serial1.begin(9600, SERIAL_8N1, /*rx=*/20, /*tx=*/21);
#elif defined(CONFIG_IDF_TARGET_ESP32C6) || defined(ARDUINO_ESP32C6_DEV)
    // ESP32-C6 は GPIO16/17 が UART0（Serial 出力）なので別ピンを使う
    Serial1.begin(9600, SERIAL_8N1, /*rx=*/4, /*tx=*/5);
#elif defined(ESP32)
    // classic ESP32 は GPIO16/17 が UART2 の既定（RX=16 / TX=17）なのでそのまま例示する。
    // S3 など他の ESP32 は既定ピンが違うので、配線に合わせて変更すること（WROVER は 16/17 が PSRAM）。
    Serial1.begin(9600, SERIAL_8N1, /*rx=*/16, /*tx=*/17);
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

ビルドフラグ（PlatformIO の `build_flags`、arduino-cli の `--build-property compiler.cpp.extra_flags=...` など）で `-D` を渡して指定します。
スケッチ冒頭の `#define` はライブラリ側で認識されず、`Parser` などのサイズが TU(翻訳単位) 間でずれるため使えません。

よく使うものだけ挙げます。全マクロの表は [API リファレンス](api-reference.md#コンパイル時設定) を参照してください。

| マクロ | 既定 | 説明 |
| ------ | ---------- | ---- |
| `AZARAC_ENABLE_*`（13個） | 1（AVR は SEISMIC/TSUNAMI のみ） | 災害カテゴリ別のデコード有効化/無効化。AVR で DCX/CAMF を使うには `-DAZARAC_AVR_LARGE_FLASH=1` または `-DAZARAC_ENABLE_DCX_CAMF=1` を明示する |
| `AZARAC_LANG_JA` / `AZARAC_LANG_EN` | 1 / 0 | 定義テーブルの言語選択 |
| `AZARAC_DEDUP_SLOTS` | 512 | 重複判定表のエントリ数（1エントリ8B。AVRプリセットは64） |
| `AZARAC_ENABLE_DEDUP` | 1 | 重複排除テーブルの有効化。0 で `AZARAC_DEDUP_SLOTS × 8 B`（既定 4 KB / AVR 512 B）が消える |
| `AZARAC_NANKAI_MAX_PAGES` / `AZARAC_NANKAI_BUFFERS` | 63 / 2 | 南海トラフ地震の最大収集ページ数(1-63)と最大同時追跡数。AVR preset は 4 / 1 |
| `AZARAC_NMEA_STRICT_SVID` | 0 | NMEA の svid 受理範囲（0=00–63 / 1=53–63 / 2=仕様表の 55/56/57/58/61）。既定は実機互換優先 |

AVR（Arduino Uno等）では専用プリセットにより有効カテゴリが SEISMIC/TSUNAMI のみに絞られ、バッファサイズも縮小されます。
プリセット値とメモリ要件の詳細は [アーキテクチャ](architecture.md#メモリ設計) を参照してください。

## 使い方のパターン

前提はひとつだけで、`feed()` が `true` を返したメッセージだけを処理することです。そのとき `msg.valid` は保証されます。`false` のときの `out` は未定義です（直前の値や復号途中のフィールドが残り得ます）。診断用に `msg.unsupported_reason` だけは、復号器の拒否理由が入ることがあります。

```cpp
void processMessage(const azaraC::Message& msg) {
    // SVID範囲チェック（PRN は 181-191: 53/54 -> 181/182 も実データに存在）
    if (msg.svid < 181 || msg.svid > 191) {
        Serial.print(F("[WARN] Unexpected SVID: "));
        Serial.println(msg.svid);
    }

    // メッセージタイプ別処理
    if (msg.msg_type == 43) {
        const azaraC::Mt43Data* mt43 = msg.getMt43();
        // EEW 無効ビルド（AVR プリセットの既定）では dc=1 の電文は復号されず feed() が false を返すので、ここには来ない。
        if (mt43 && mt43->disaster_category == 1) {
            // EEW処理（handleEEW は EewData を触るなら #if (AZARAC_ENABLE_EEW) で囲む）
            handleEEW(*mt43);
        }
    }
}
```

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
