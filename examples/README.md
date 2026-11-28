# azaraC Examples

このディレクトリには、azaraCライブラリの使用例が含まれています。

## 目次

- [基本的な使用例](#基本的な使用例)
- [高度な使用例](#高度な使用例)
- [Example一覧](#example一覧)

---

## 基本的な使用例

### basic_nmea - NMEA $QZQSM 入力

NMEAフォーマットの$QZQSMメッセージを受信し、JSONに変換して出力します。

**対応ハードウェア**: u-blox M10, ZED-F9P, Furuno GT-87 など

```bash
# Arduino IDE で examples/basic_nmea/basic_nmea.ino を開いて書き込み
```

**配線 (ESP32-C3 DevKitM-1)**:
| GNSS | ESP32-C3 |
|------|----------|
| TX | GPIO4 (Serial1 RX) |
| RX | GPIO5 (Serial1 TX) |
| GND | GND |

ESP32 のピンは C3=GPIO4/5、C6=GPIO4/5、classic=GPIO16/17 です。S3/WROVER 等は配線に合わせて変更してください。
C3 DevKitM-1 の GPIO20/21 は USB-UART ブリッジ経由の UART0（シリアルモニタ）用なので、GNSS と共有しません。

---

### basic_ubx - UBX-RXM-SFRBX 入力

u-bloxバイナリフォーマットのUBX-RXM-SFRBXメッセージを受信します。
ucenter2などを利用して受信を有効化してください。

**必要なu-blox設定**:

```
CFG-MSGOUT-UBX_RXM_SFRBX_UART1 = 1
CFG-SIGNAL-QZSS_L1S_ENA        = 1
CFG-UART1-BAUDRATE              = 9600
```

```bash
# Arduino IDE で examples/basic_ubx/basic_ubx.ino を開いて書き込み
```

---

### ublox_config - MCU から u-blox を設定して UBX 入力

起動時に Serial1 から u-blox の UART1 へ UBX 設定を送り、その後は `basic_ubx` と同様に JSON を出力します。
`UBLOX_GENERATION` は M10=`10`（既定）、F9=`9`、M8=`8` から選びます。UART1 の UBX 入出力が有効であることが前提です。
GNSS UART1 TX → MCU RX1、GNSS UART1 RX ← MCU TX1、GND を共通に接続します。ESP32 のピンは上記と同じです。Uno は Serial1 が無いため対象外です。
`GNSS_BAUD` は受信機の現在の速度（既定 9600）に合わせます。この例では受信機の速度を変更しません。電源・I/O 電圧はモジュール仕様に従ってください。

**M10 / F9（CFG-VALSET 対応 FW）**: RAM レイヤーへ次のキーをすべて 1 として送ります。

| キー | ID | 型 |
| --- | --- | --- |
| CFG-MSGOUT-UBX_RXM_SFRBX_UART1 | `0x20910232` | U1 |
| CFG-SIGNAL-QZSS_ENA | `0x10310024` | L |
| CFG-SIGNAL-QZSS_L1S_ENA | `0x10310014` | L |

出典: [u-blox M10 SPG 5.10 Interface description (UBX-21035062 R03)](https://content.u-blox.com/sites/default/files/u-blox-M10-SPG-5.10_InterfaceDescription_UBX-21035062.pdf)、CFG-MSGOUT / CFG-SIGNAL / UBX-CFG-VALSET。
電源断後は再設定します。BBR にも保持する場合は payload の layers を 1 から 3（RAM + BBR）に変更し、バックアップ電源等の条件を確認してください。Flash 保存は行いません。
機種・FW の Interface description で CFG-VALSET と L1S 対応を確認してください。**F9P は型番・FW によって L1S 非対応の場合があり、QZSS L1C/A 対応だけでは不十分です。** GPS 等の既存信号設定は変更しません。

**M8**: CFG-MSG で RXM-SFRBX の UART1 rate を 1（他ポートは 0）にします。
QZSS L1SAIF の有効化は別途必要です。CFG-GNSS を poll し、他 GNSS のブロックやチャネル割り当てを保持して QZSS（gnssId=5）の enable と sigCfgMask=`0x05`（L1C/A + L1SAIF、flags bits 16–23）を設定します。
この例は他の測位設定を壊さないよう CFG-GNSS を自動変更しません。FW・GPS との組み合わせ・チャネル数等の条件を確認してください。
出典: [u-blox 8 / M8 Receiver description (UBX-13003221 R28)](https://content.u-blox.com/sites/default/files/products/documents/u-blox8-M8_ReceiverDescrProtSpec_UBX-13003221.pdf)、§4.2.2 / UBX-CFG-GNSS / UBX-CFG-MSG。

送信後は対象 class/id とチェックサムが一致する ACK / NAK を最大 3 秒待ちます。NAK は機種・FW・信号設定、timeout は配線・速度・UBX 入出力や起動待ちを確認してください。
世代の自動フォールバックは行いません。設定中の受信データは破棄されます。ACK はコマンド受理を示すだけで、L1S の受信や災害電文の到来を保証しません。

### basic_dcx - MT=44 の要約と JSON

DCX/CAMF のサービス種別、地域、楕円中心などの要約と JSON を出力します。GNSS の UNIX 時刻があれば `cached_gnss_unix_time` を更新してください。0 のままなら年は未解決です。
AVR では DCX/CAMF が既定で無効なので、Mega 等の大型品で `-DAZARAC_ENABLE_DCX_CAMF=1`（または `-DAZARAC_AVR_LARGE_FLASH=1`）をライブラリを含む全 TU に指定します。Uno は容量不足のため対象外です。
AVR のこの例は GNSS 入力と JSON 出力が同じ Serial（9600 baud）になります。その他は Serial1 入力です。

### basic_uno - Arduino Uno (AVR) 入力

Arduino Uno 用の最小例です。Uno には Serial1 が無いため、GNSS モジュールを Serial (pin 0=RX) に接続し、JSON も同一の Serial に出力します（ボーレート 9600）。

**対応ハードウェア**: Arduino Uno (AVR)。
`azaraC_config.h` の AVR プリセットにより SEISMIC/TSUNAMI のみ有効化され、32KB Flash に収まります。
ATmega2560（Mega）でも既定は同じ SEISMIC/TSUNAMI のみです。
DCX/CAMF を使う場合は `-DAZARAC_ENABLE_DCX_CAMF=1`（または `-DAZARAC_AVR_LARGE_FLASH=1`）を明示します。
（DCX/CAMF 入りは日本語でフラッシュ148KB / RAM 892B を実測。Arduino コアの実ビルド（`-flto`）でも RAM 892B で同じ — switch 戦略のリテラルは LTO の section 属性落ちを避けるため名前空間スコープに置いている）。

**配線 (Arduino Uno)**:

| GNSS | Arduino Uno |
|------|-------------|
| TX | pin 0 (RX) |
| GND | GND |
| VCC | モジュール仕様に従う |

このスケッチは CI の Uno コンパイルチェック（ライブラリ全体の強制リンク）も兼ねています。

---

### with_sntp - SNTP時刻解決付き

Wi-FiとSNTPを使用してUNIX時刻を取得し、DCR/DCXメッセージの年を正確に解決します。

**機能**:

- Wi-Fi接続
- SNTP時刻同期
- EEW (disaster_category=1) と DCX の詳細ログ表示（JSON は全メッセージを出力）
- DCXメッセージのサービス種別表示

**必要な設定**:

```cpp
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASS "YOUR_PASS"
```

---

## 高度な使用例

### filter_by_category - カテゴリ別フィルタリング

MT=43メッセージを災害カテゴリ別にフィルタリングして出力します。

カテゴリ 1（EEW）と 2（震源）の詳細出力は `#if (AZARAC_ENABLE_EEW)` / `#if (AZARAC_ENABLE_HYPOCENTER)` で囲んであります。
そのカテゴリを無効にしたビルド（AVR プリセットの既定）では型ごと消えるため case も出力されません。
フィルタの `eew` / `hypocenter` フラグ自体は残るので、有効にしたビルドではそのまま効きます。

**対応カテゴリ**:

| カテゴリID | 内容               | デフォルト |
| ---------- | ------------------ | ---------- |
| 1          | 緊急地震速報 (EEW) | ON         |
| 2          | 震源情報           | ON         |
| 3          | 震度情報           | ON         |
| 4          | 南海トラフ地震     | ON         |
| 5          | 津波警報・注意報   | ON         |
| 6          | 北太平洋津波       | OFF        |
| 8          | 火山情報           | ON         |
| 9          | 降灰情報           | ON         |
| 10         | 気象警報・注意報   | OFF        |
| 11         | 洪水警報           | ON         |
| 12         | 台風情報           | ON         |
| 14         | 海上警報           | OFF        |

**フィルタ設定の変更**:

```cpp
// examples/filter_by_category/filter_by_category.ino の CategoryFilter を編集
CategoryFilter filter;
filter.eew = true;        // 緊急地震速報を出力
filter.weather = false;    // 気象警報を出力しない
```

---

### error_handling - エラーハンドリングと統計

メッセージの妥当性チェックと受信統計を表示します。

**機能**:

- メッセージ妥当性チェック（`feed()` が `true` を返した時点で `msg.valid` は保証されるため、スケッチ側では `msg.valid` を再チェックしない）
- SVID範囲チェック (QZSS L1S PRN: 181-191)
- `disaster_category` 範囲チェック (MT=43)
- `service_kind` チェック (MT=44)
- 日付・時刻の妥当性チェック
- 受信統計の定期表示
- 5 秒間隔のハートビート出力

**バリデーション関数**:

```cpp
// SVID とメッセージタイプのチェック
bool validateMessage(const azaraC::Message& msg) {
    // SVIDの範囲チェック (QZSS L1S PRN: 181-191)
    if (msg.svid < QZSS_SVID_MIN || msg.svid > QZSS_SVID_MAX) {
        Serial.print(F("[WARN] Unexpected SVID: "));
        Serial.println(msg.svid);
    }
    if (msg.msg_type != MSG_TYPE_MT43 && msg.msg_type != MSG_TYPE_MT44) {
        Serial.print(F("[ERROR] Unknown msg_type: "));
        Serial.println(msg.msg_type);
        return false;
    }
    return true;
}

// MT=43 メッセージの詳細バリデーション
bool validateMt43(const azaraC::Message& msg) {
    const azaraC::Mt43Data* mt43 = msg.getMt43();
    if (!mt43) return false;
    // disaster_categoryの範囲チェック
    // 日付の妥当性チェック
    // ...
}

// MT=44 メッセージの詳細バリデーション
bool validateMt44(const azaraC::Message& msg) {
    const azaraC::Mt44Data* mt44 = msg.getMt44();
    if (!mt44) return false;
    // service_kindのチェック
    // ...
}
```

**出力例**:

```
=== azaraC Statistics ===
Total messages:    50
MT=43 (QZQSM):     30
MT=44 (DCX):       18
Last SVID:         184
========================

[INFO] Heartbeat - Total: 50
```

---

### wifi_client - Wi-Fiクライアント出力

JSONメッセージをTCPサーバーに送信します。

**用途**:

- MQTTブローカーへの転送
- HTTPエンドポイントへの送信
- リモートログサーバーへの転送

**必要な設定**:

```cpp
#define WIFI_SSID   "YOUR_SSID"
#define WIFI_PASS   "YOUR_PASS"
#define SERVER_HOST "192.168.1.100"
#define SERVER_PORT 1883
```

**カスタムPrintクラス例**:

```cpp
class WifiPrint : public Print {
public:
    WiFiClient& client;
    WifiPrint(WiFiClient& c) : client(c) {}
    size_t write(uint8_t c) override { return client.write(c); }
    size_t write(const uint8_t* buf, size_t len) override { return client.write(buf, len); }
};
```

---

### rtos_freertos - FreeRTOS タスクベース処理

ESP32 で UART RX タスクと出力タスクを分離し、キューでメッセージを渡すサンプルです。`loop()` を使いません。

`Message` をキューのバイトコピーへ直接載せず、静的スロットをコピー代入して ready/free キューではインデックスだけを渡します。キューも静的確保します。
南海トラフ集約本文は Parser への借用ポインタなので、RX タスクで同期出力しスロットへは渡しません。スロット満杯時は新しい出力を捨て、統計へ記録します。
FreeRTOS タスク生成は従来どおり起動時の動的 API を使います（アプリ全体のゼロヒープを保証する例ではありません）。

```bash
# Arduino IDE で examples/rtos_freertos/rtos_freertos.ino を開いて書き込み
```

**対応ハードウェア**: ESP32 系（FreeRTOS 必須）。

---

## Example一覧

| Example            | 入力          | 出力                   | 特徴               |
| ------------------ | ------------- | ---------------------- | ------------------ |
| basic_nmea         | NMEA $QZQSM   | Serial JSON            | 最もシンプル       |
| basic_ubx          | UBX-RXM-SFRBX | Serial JSON            | u-bloxバイナリ     |
| ublox_config       | UBX-RXM-SFRBX | Serial JSON + 設定結果 | MCU から u-blox 設定 |
| basic_dcx          | NMEA/UBX      | Serial JSON + MT44 要約 | DCX/CAMF 有効化が必要 |
| with_sntp          | NMEA $QZQSM   | Serial JSON + 詳細ログ | SNTP時刻解決       |
| filter_by_category | NMEA/UBX      | Serial JSON            | カテゴリフィルタ   |
| error_handling     | NMEA/UBX      | Serial JSON + 統計     | エラーハンドリング |
| wifi_client        | NMEA/UBX      | Serial + TCP           | ネットワーク出力   |
| basic_uno          | NMEA/UBX      | Serial JSON            | AVR 最小構成 (Uno) |
| rtos_freertos      | NMEA/UBX      | Serial JSON            | FreeRTOS タスクベース |

---

## 共通の配線図

### ESP32-C3 DevKitM-1

```
GNSS Module          ESP32-C3 DevKitM-1
+--------+          +------------------+
| TX  ---+--------→ | GPIO4 (Serial1 RX)
| RX  ---+--------← | GPIO5 (Serial1 TX)
| GND ---+--------→ | GND
| VCC ---+--------→ | 3.3V
+--------+          +------------------+
```

### ピン配置のカスタマイズ

```cpp
// ESP32-C3 のデフォルト (GPIO4, GPIO5)
Serial1.begin(9600, SERIAL_8N1, 4, 5);

// カスタムピン (例: GPIO10, GPIO11)
Serial1.begin(9600, SERIAL_8N1, 10, 11);
```

---

## トラブルシューティング

### メッセージが受信されない場合

1. **配線を確認**: GNSSのTXがESP32のRXに接続されているか確認
2. **ボーレートを確認**: 9600 baudがデフォルト
3. **QZSS L1S信号が有効か確認**: u-bloxの設定を確認
4. **アンテナを確認**: 屋外または窓際でテスト

### コンパイルエラーが発生する場合

1. **C++17を有効化**: arduino-cli なら `--build-property "compiler.cpp.extra_flags=-std=gnu++17"`。
   PlatformIO なら `build_flags = -std=gnu++17`（[`platformio.ini.example`](../platformio.ini.example)）。
   Arduino IDE 2.x にはコンパイルフラグの設定項目が無いため、C++17 が既定のコアを使うか PlatformIO を使ってください
2. **ボードサポートを確認**: 推奨環境はESP32 コア ≥ 3.x
3. **ライブラリのインストール**: azaraCがlibrariesフォルダにあるか確認

### JSON出力が不正な場合

1. **バッファサイズを確認**: 大きなメッセージの場合、Serialのバッファを増やす
2. **メモリ不足を確認**: ESP32-C3のメモリ使用量を確認
