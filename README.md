<img src="https://raw.githubusercontent.com/A-vrice/azaraC/refs/heads/main/logo.png" width="256">

# AzaraC

## このライブラリについて

AzaraCは準天頂衛星みちびきが送信する災害通報メッセージのデコーダーである[azarashi](https://github.com/nbtk/azarashi)をArduino向けに移植したものです。QZSS L1S信号を用いた災害通報の**DC Report/QZQSM**(MT=43)および**DCX/CAMF**(MT=44)に対応しており、ESP32シリーズなどのArduino互換ボード向けに設計されています。外部ライブラリには依存していません。

変換に使用する定義テーブル(`definition/*.h`)は、[`.github/workflows/update-definitions.yml`](.github/workflows/update-definitions.yml) により毎日午前6時(UTC)に自動生成されます（`workflow_dispatch` による手動実行も可能）。azarashiのバージョンが更新されると付随してPRが作成されるため、azarashiと同様の出力が期待できます。

## 対応メッセージ

| msg_type | 規格            | 名称            |
| -------- | --------------- | --------------- |
| 43       | IS-QZSS-DCR-016 | DCR 12種類      |
| 44       | IS-QZSS-DCX-004 | DCX / CAMF など |

### MT=43 防災カテゴリ一覧

| カテゴリID | 名称                              | 規格セクション |
| ---------- | --------------------------------- | -------------- |
| 1          | 緊急地震速報 (EEW)                | §5.1.2.3.1     |
| 2          | 震源情報 (Hypocenter)             | §5.1.2.3.2     |
| 3          | 震度情報 (Seismic Intensity)      | §5.1.2.3.3     |
| 4          | 南海トラフ地震 (Nankai Trough)    | §5.1.2.3.4     |
| 5          | 津波警報・注意報 (Tsunami)        | §5.1.2.3.5     |
| 6          | 北太平洋津波 (NW Pacific Tsunami) | §5.1.2.3.6     |
| 8          | 火山情報 (Volcano)                | §5.1.2.3.7     |
| 9          | 降灰情報 (Ash Fall)               | §5.1.2.3.8     |
| 10         | 気象警報・注意報 (Weather)        | §5.1.2.3.9     |
| 11         | 洪水警報 (Flood)                  | §5.1.2.3.10    |
| 12         | 台風情報 (Typhoon)                | §5.1.2.3.11    |
| 14         | 海上警報 (Marine)                 | §5.1.2.3.12    |

### MT=44 サービス種別

| 種別            | 名称                             | 判定条件                                                        |
| --------------- | -------------------------------- | --------------------------------------------------------------- |
| NullMessage     | Null Message                     | A1=0, A2=111 (Japan), A3=0, かつ全CAMF/Extendedフィールドがゼロ |
| LAlert          | L-Alert (地方自治体向け緊急速報) | A2=111 (Japan) & A3=1                                           |
| JAlert          | J-Alert (全国瞬時警報システム)   | A2=111 (Japan) & A3=0,2,3                                       |
| LocalGovernment | 地方自治体送信情報               | A2=111 (Japan) & A3=4-31                                        |
| OutsideJapan    | 国外向け情報                     | A2≠111                                                          |
| Unknown         | 不明                             | 上記以外                                                        |

## 推奨環境など

| 項目            | 値                                                                                                         |
| --------------- | ---------------------------------------------------------------------------------------------------------- |
| 主要ターゲット  | ESP32-C3 (FreeRTOS / Arduino framework)                                                                    |
| ビルド確認済み  | ESP32-S3/C3, Teensy4.0, Nano 33 BLE, Giga R1 Wi-Fi, STM32 Nucleo H563ZI, Arduino Zero (SAMD21)                |
| 推奨環境        | 推奨: 256 KB+ RAM（全機能・全カテゴリ有効）/ 動作可能: 32 KB+ RAM（SAMD21 等、デフォルト設定で動作）/ 最小: ~2 KB RAM（AVR、Nankai/DCX 無効化必須） |
| ホストテスト    | g++ -std=c++17 (Linux / macOS / WSL / Windows)                                                             |
| GNSS モジュール | u-blox (UBX-RXM-SFRBX) / NMEA $QZQSM 出力機                                                                |

[注意] AzaraCはC++17で記述されています。利用の際は、お使いのIDEのC++コンパイラ設定を17以上にしてください。多くのボードメーカでは標準設定がC++11となっており、本ライブラリのコンパイル時にエラーが発生する可能性があります。SAMD21 等の ARM GCC 7 ツールチェーンでも `-std=gnu++17` でコンパイル可能です。

## インストール

### Arduino IDE（手動）

```bash
git clone https://github.com/A-vrice/azaraC \
  <PROJECT_DIR>/libraries/azaraC
```

### PlatformIO（手動）

```bash
git clone https://github.com/A-vrice/azaraC \
  <PROJECT_DIR>/.pio/libdeps/<TARGET_BOARD>/azaraC
```

---

## クイックスタート

### NMEA ($QZQSM) を使用する場合

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

### UBX (RXM-SFRBX) を使用する場合

u-blox(u-center2など) の設定:

```
CFG-MSGOUT-UBX_RXM_SFRBX_UART1 = 1
CFG-SIGNAL-QZSS_L1S_ENA        = 1
```

コードは`Parser`が自動判別するためNMEAと同じものが利用できます。

### UNIX時刻付き（メッセージから年月を含めた日時情報を取得したい場合）

```cpp
// SNTP/GPS等で取得したUNIX時刻を渡す
uint32_t now = (uint32_t)time(nullptr);
if (parser.feed(byte, msg, now)) { ... }
```

詳細は[`examples/with_sntp/`](examples/with_sntp/)を参照してください。

---

## API

### `azaraC::Parser`

```cpp
// 1バイト投入。新しい有効メッセージが揃ったら true を返す
bool feed(uint8_t byte, Message& out, uint32_t now_unix = 0);

void reset();  // フレーマ・重複フィルタをリセット
```

重複除去は **{svid, msg_type, crc24}** のリングバッファで行います。デフォルトの保存数は8メッセージです。複数衛星から受信する場合などで重複がみられる場合は32や128などに適宜調整してください:

```cpp
#define AZARAC_DEDUP_SLOTS 32
#include <azaraC.h>
```

### コンパイル時設定マクロ

設定は [`azaraC_config.h`](src/azaraC_config.h) に一元管理されており、[`azaraC.h`](src/azaraC.h) をインクルードする前に `#define` で上書きできます。

#### 言語選択

定義テーブルの言語を選択してFlash使用量を削減できます。デフォルトは日本語のみ有効です。

```cpp
// 日本語のみ（デフォルト）: 英語テーブルを除外
#include <azaraC.h>

// 英語のみ
#define AZARAC_LANG_JA 0
#define AZARAC_LANG_EN 1
#include <azaraC.h>

// 両方有効
#define AZARAC_LANG_JA 1
#define AZARAC_LANG_EN 1
#include <azaraC.h>
```

#### 災害カテゴリ選択

不要な災害カテゴリの定義テーブルをコンパイル時に除外し、Flash使用量を削減できます。

| マクロ                         | デフォルト | 除外対象                 |
| ------------------------------ | ---------- | ------------------------ |
| `AZARAC_ENABLE_EEW`            | 1          | 緊急地震速報関連テーブル |
| `AZARAC_ENABLE_HYPOCENTER`     | 1          | 震源情報関連テーブル     |
| `AZARAC_ENABLE_SEISMIC`        | 1          | 震度情報関連テーブル     |
| `AZARAC_ENABLE_NANKAI`         | 1          | 南海トラフ関連テーブル   |
| `AZARAC_ENABLE_TSUNAMI`        | 1          | 津波情報関連テーブル     |
| `AZARAC_ENABLE_VOLCANO`        | 1          | 火山情報関連テーブル     |
| `AZARAC_ENABLE_WEATHER`        | 1          | 気象情報関連テーブル     |
| `AZARAC_ENABLE_FLOOD`          | 1          | 洪水警報関連テーブル     |
| `AZARAC_ENABLE_TYPHOON`        | 1          | 台風情報関連テーブル     |
| `AZARAC_ENABLE_MARINE`         | 1          | 海上警報関連テーブル     |
| `AZARAC_ENABLE_NW_PAC_TSUNAMI` | 1          | 北太平洋津波関連テーブル |
| `AZARAC_ENABLE_ASH_FALL`       | 1          | 降灰情報関連テーブル     |
| `AZARAC_ENABLE_DCX_CAMF`       | 1          | DCX/CAMF全テーブル       |

```cpp
// 緊急地震速報のみ読み込み
#define AZARAC_ENABLE_EEW 1
#define AZARAC_ENABLE_HYPOCENTER 0
#define AZARAC_ENABLE_SEISMIC 0
#define AZARAC_ENABLE_NANKAI 0
#define AZARAC_ENABLE_TSUNAMI 0
#define AZARAC_ENABLE_VOLCANO 0
#define AZARAC_ENABLE_WEATHER 0
#define AZARAC_ENABLE_FLOOD 0
#define AZARAC_ENABLE_TYPHOON 0
#define AZARAC_ENABLE_MARINE 0
#define AZARAC_ENABLE_NW_PAC_TSUNAMI 0
#define AZARAC_ENABLE_ASH_FALL 0
#define AZARAC_ENABLE_DCX_CAMF 0

#include <azaraC.h>
```

### `azaraC::toJson(msg, out)`

`Message`をJSON形式で`Serial`, `WiFiClient`などの`Print`系クラスに渡せます。

### `azaraC::Message`

```cpp
struct Message {
    uint8_t  svid;
    uint8_t  msg_type;   // 43 or 44
    uint32_t crc24;
    bool     valid;

    // MT=44 フィールド: service_kind, a1_message_type, a2_country_code ...
    // MT=43 フィールド: report_classification, disaster_category,
    //                   information_type, event_time
    //                   + サブタイプ別フィールド(eew_*, seis_*, tsu_* ...)
};
```

フィールド詳細は[`src/Message.h`](src/Message.h)を参照してください。

### 安全なアクセサ

```cpp
azaraC::Message msg;
// ...
if (msg.msg_type == 43) {
    const azaraC::Mt43Data* mt43 = msg.getMt43();
    if (mt43) {
        // MT=43 フィールドにアクセス
        uint8_t category = mt43->disaster_category;
    }
} else if (msg.msg_type == 44) {
    const azaraC::Mt44Data* mt44 = msg.getMt44();
    if (mt44) {
        // MT=44 フィールドにアクセス
        auto kind = mt44->service_kind;
    }
}
```

### Nankai Trough ページ集約

MT=43 カテゴリ4（南海トラフ地震）メッセージは、複数ページにまたがって送信される場合があります。AzaraCは受信したページを自動的に集約し、`NankaiData::aggregated_text_ptr` に集約テキストを指すポインタを設定します。

```cpp
const azaraC::Mt43Data* mt43 = msg.getMt43();
if (mt43 && mt43->disaster_category == 4) {
    const azaraC::NankaiData* nankai = mt43->getNankai();
    if (nankai && nankai->is_aggregated) {
        // nankai->aggregated_text_ptr に集約テキストへのポインタが格納されている
        // nankai->aggregated_len に文字数
    }
```

---
### メモリ使用量（RAM要件）

| 構成 | Parser + Message | スタック (feed 1回あたり) | 備考 |
| ---- | ---------------- | ------------------------ | ---- |
| デフォルト (Nankai 4 buffers) | ~700 B | ~200 B | 標準構成 |
| フル構成 (Nankai 63 buffers) | ~2.5 KB | ~200 B | 全ページ集約対応、ホストテスト構成 |
| 最小構成 (Nankai 1 buffer) | ~400 B | ~200 B | RAM 2 KB 級ターゲット（Arduino Uno等、Nankai/DCX 無効化が必要） |
| DCX float モード追加 | さらに 72 B 削減 | — | `AZARAC_DCX_USE_FLOAT` 有効時 |

注意: Parser は static 配置推奨（スタック配置は ~1 KB の消費）。`feed()` は Message をスタックに構築するため、ループ内での冗長な Message コピーを避けること。

---


## JSON 出力例

### MT=43 EEW (緊急地震速報)

```json
{
  "svid": 184,
  "msg_type": 43,
  "crc24": 12345678,
  "report_classification": 1,
  "report_classification_label": "警報",
  "disaster_category": 1,
  "disaster_category_label": "緊急地震速報",
  "information_type": 0,
  "information_type_label": "発表",
  "report_time": { "day": 19, "hour": 14, "min": 30, "unix": 0 },
  "detail": {
    "depth": 60,
    "magnitude": 65,
    "epicenter": 42,
    "epicenter_label": "千葉県北西部",
    "intensity_lower": 5,
    "intensity_lower_label": "5弱",
    "intensity_upper": 6,
    "intensity_upper_label": "6強",
    "regions": [
      { "code": 1, "label": "北海道道央" },
      { "code": 12, "label": "東京都" }
    ]
  }
}
```

### MT=43 台風情報

```json
{
  "svid": 189,
  "msg_type": 43,
  "disaster_category": 12,
  "disaster_category_label": "台風情報",
  "detail": {
    "reference_time": { "day": 15, "hour": 9, "min": 0 },
    "ref_type": 1,
    "ref_type_label": "Analysis",
    "number": 202401,
    "scale": 3,
    "scale_label": "大型",
    "intensity": 2,
    "intensity_label": "強い",
    "lat_deg": 28.5,
    "lon_deg": 135.2,
    "pressure": 965,
    "max_wind": 33,
    "max_gust": 50
  }
}
```

### MT=44 DCX (L-Alert)

```json
{
  "svid": 184,
  "msg_type": 44,
  "crc24": 11259375,
  "service_kind": 1,
  "service_kind_label": "L_ALERT",
  "a1_msg_type": "Alert",
  "a2_country": 111,
  "a2_country_label": "Japan",
  "a3_provider": 1,
  "a4_hazard": 10,
  "a4_hazard_category": "Geological",
  "a4_hazard_definition": "Geological Earthquake",
  "a4_hazard_type": "Earthquake",
  "a5_severity": 3,
  "a5_severity_label": "Extreme",
  "onset_time": { "day": 19, "hour": 14, "min": 30, "unix": 1745123400 },
  "main_ellipse": {
    "lat_deg": 35.688258,
    "lon_deg": 139.690855,
    "semi_major_km": 10.933,
    "semi_minor_km": 8.085,
    "azimuth_deg": 45.0
  },
  "ex1_target_area": 1100,
  "ex1_target_area_label": "Sapporo-shi",
  "alert_identity": { "a2": 111, "a3": 1, "a4": 10, "ex1": 1100 }
}
```

### MT=44 DCX (J-Alert) — 都道府県モード

```json
{
  "svid": 184,
  "msg_type": 44,
  "service_kind": 2,
  "service_kind_label": "J_ALERT",
  "a4_hazard": 10,
  "a4_hazard_type": "Earthquake",
  "jalert_prefecture_mode": true,
  "prefecture_positions": [1, 12, 13, 14],
  "prefecture_count": 4,
  "prefecture_labels": ["北海道", "東京都", "神奈川県", "埼玉県"]
}
```

### MT=44 DCX (J-Alert) — 市区町村モード

```json
{
  "svid": 184,
  "msg_type": 44,
  "service_kind": 2,
  "service_kind_label": "J_ALERT",
  "a4_hazard": 10,
  "a4_hazard_type": "Earthquake",
  "jalert_prefecture_mode": false,
  "city_codes": [1100, 1201],
  "city_labels": ["Sapporo-shi", "Chiyoda-ku"]
}
```

### MT=44 DCX A17 拡張フィールド (EWSS CAMF v1.2)

A17フィールドにより、メイン楕円の精度向上や追加情報が提供されます。

| A17 | 名称                                      | 仕様セクション |
| --- | ----------------------------------------- | -------------- |
| 00  | B1: Improved Resolution of Main Ellipse   | §3.7.1         |
| 01  | B2: Hazard Center Position                | §3.7.2         |
| 10  | B3: Secondary Ellipse Definition          | §3.7.3         |
| 11  | B4: Quantitative and Detailed Information | §3.7.4         |

**B1 リファインメント** - メイン楕円の緯度・経度・軸長を精密化（EWSS CAMF v1.1 §3.7.1.3/4）

```json
{
  "main_ellipse": {
    "lat_deg": 35.688258,
    "lon_deg": 139.690855,
    "semi_major_km": 10.933,
    "semi_minor_km": 8.085,
    "azimuth_deg": 45.0,
    "b1_refinement": {
      "c1_lat_offset_deg": 0.000343,
      "c2_lon_offset_deg": 0.000343,
      "c3_refined_semi_major_km": 135.125,
      "c4_refined_semi_minor_km": 108.1
    }
  }
}
```

**B2 ハザード中心位置** - 楕円中心からの相対オフセット

```json
{
  "hazard_center": {
    "delta_lat_deg": 0.5,
    "delta_lon_deg": -0.3
  }
}
```

**B3 第2楕円** - シフト・相似比・方位角による追加楕円

```json
{
  "secondary_ellipse": {
    "shift_km": 5.0,
    "homothetic_factor": 0.5,
    "bearing_deg": 45.0,
    "c10_guidance_label": "Evacuate",
    "c10_guidance_code": "EVACUATE"
  }
}
```

**B4 詳細情報** - ハザード種別に応じたD-seriesフィールド（D1-D36）

```json
{
  "detailed_info": {
    "d1_magnitude": 65,
    "d5_wave_height": 3,
    "d8_wind_speed": 15
  }
}
```

---

## Examples

詳細な使用例は[`examples/`](examples/)ディレクトリを参照してください。

| Example                                            | 説明                           |
| -------------------------------------------------- | ------------------------------ |
| [basic_nmea](examples/basic_nmea/)                 | NMEA $QZQSM の基本的な使用例   |
| [basic_ubx](examples/basic_ubx/)                   | UBX-RXM-SFRBX の基本的な使用例 |
| [with_sntp](examples/with_sntp/)                   | SNTP時刻解決 + EEWフィルタ     |
| [filter_by_category](examples/filter_by_category/) | 災害カテゴリ別フィルタリング   |
| [error_handling](examples/error_handling/)         | エラーハンドリングと統計       |
| [wifi_client](examples/wifi_client/)               | Wi-Fiクライアント出力          |
| [rtos_freertos](examples/rtos_freertos/)           | FreeRTOS タスクベース処理      |

### RTOS (FreeRTOS) 対応

`examples/rtos_freertos/` では、FreeRTOS タスクベースの NMEA/UBX 同時処理サンプルを示しています。`loop()` を使わず、UART RX タスクと出力タスクでメッセージを処理し、キューで受け渡します。

### エラーハンドリングの詳細

`examples/error_handling/` では、メッセージの妥当性チェックと受信統計を表示する方法を示しています。

**機能**:

- メッセージ妥当性チェック (`msg.valid`)
- SVID範囲チェック (QZSS L1S: 183-192)
- `disaster_category` 範囲チェック (MT=43)
- `service_kind` チェック (MT=44)
- 日付・時刻の妥当性チェック
- 受信統計の定期表示

**出力例**:

```
=== azaraC Statistics ===
Total messages:    50
Valid messages:    48
Duplicate skipped: 2
MT=43 (QZQSM):     30
MT=44 (DCX):       18
Last SVID:         184
Valid ratio:       96%
========================
```

---

## 定義ファイルの自動生成

```
azarashi (PyPI)
  └── definition/*.py
        ↓ .github/workflows/update-definitions.yml (毎日 06:00 UTC)
  scripts/gen_definitions.py  → src/definition/*.h
        ↓ PR 自動作成 (peter-evans/create-pull-request)
  レビュー → マージ
```

手動実行:

```bash
pip install azarashi
python scripts/gen_definitions.py
```

---

## ホストテスト

ESP32 不要でビルド・実行できます。テストには MinGW-w64（Windows）または g++（Linux/macOS/WSL）が必要です。

```bash
make -C test run        # 全テスト実行
make -C test fuzz       # ファズテストビルド
make -C test decode     # decode_to_json CLIツールビルド
```

### Windows でのビルド

Windows で MinGW-w64 を使用する場合、`test/Makefile` は既定で `D:\apps\mingw64\bin` をPATH に追加します。MinGW-w64 が別の場所にインストールされているか、既に PATH に含まれている場合は `MINGW64_BIN` 変数で上書きできます。

```bash
# カスタムパスを指定
make -C test run MINGW64_BIN=C:\mingw64\bin

# MinGW-w64 が既に PATH に含まれている場合: 空に設定
make -C test run MINGW64_BIN=
```

```
[doctest] doctest version is "2.5.0"
[doctest] run with "--help" for options
===============================================================================
[doctest] test cases:  219 |  219 passed | 0 failed | 0 skipped
[doctest] assertions: 1827 | 1827 passed | 0 failed |
[doctest] Status: SUCCESS!
```

---

## トラブルシューティング

### メッセージが受信されない場合

1. **配線を確認**: GNSSのTXがESP32のRXに接続されているか確認してみてください。
2. **C++17を有効化**: Arduino IDE → ツール → C++ Standard → C++17
3. **ボードのサポートを確認**: Arduino系のエントリー気だと動かない場合があります。
4. **ライブラリのインストール**: azaraCがlibrariesフォルダにあるか確認してみてください。

### コンパイルエラーが発生する場合

1. **バッファサイズを確認**: 大きなメッセージの場合、Serialのバッファを増やしてみてください。
2. **メモリ不足を確認**: ボードのメモリ使用量を確認してみてください。
3. **ボードサポートを確認**: ESP32 コア ≥ 3.x
4. **ライブラリのインストール**: azaraCがlibrariesフォルダにあるか確認してみてください。

### JSON出力が不正な場合

1. **バッファサイズを確認**: 大きなメッセージの場合、Serialのバッファを増やす
2. **メモリ不足を確認**: ESP32-C3のメモリ使用量を確認

---

## 仕様書リファレンス

| 規格            | 名称                        | バージョン等   |
| --------------- | --------------------------- | -------------- |
| IS-QZSS-DCR-016 | DC Report Service (MT=43)   | April 03, 2026 |
| IS-QZSS-DCX-004 | DCX Service (MT=44)         | May, 2026      |
| EWSS CAMF v1.2  | Common Alert Message Format | Version 1.2    |

---

## 謝辞

本ライブラリのメッセージ定義は [azarashi](https://github.com/nbtk/azarashi)(MIT)の`definition/*.py` を元とさせていただきました。また、ビット構造の解析・実装の参考としても同ライブラリのデコーダを参考にさせていただきました。

## Acknowledgements

The original project `azarashi` was developed by [NBTK](https://github.com/nbtk) during his time at BitMeister Inc., with support and resources generously provided by the company.

AzaraC is maintained independently by [A-vrice](https://github.com/A-vrice).

## 不具合など

何か不具合、疑問点があれば[Issue](https://github.com/A-vrice/azaraC/issues)，作者メールアドレス[AzaraC@vrice.f5.si]，およびTwitter(現X)のDMまでお願いします。

## Disclaimer Policy

本ライブラリは非公式なものであり，準天頂衛星システムサービス株式会社，JAXA，その他公共機関など，「みちびき」に関連する組織，NBTK氏の提供するazarashiとは一切関係ありません。また，あるふぁ米およびそのコントリビューターは，受信したメッセージや本ライブラリの出力内容の正確性，完全性，その他のいかなるものについても保証しません。本ライブラリを使用したことによるいかなる損害についても責任は負いかねます。本ライブラリは現状有姿で提供されます。
