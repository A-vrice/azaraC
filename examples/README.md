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
| TX | GPIO20 |
| RX | GPIO21 |
| GND | GND |

> ESP32 の Serial1 ピンはボード別に自動選択されます（C3=GPIO20/21、C6=GPIO4/5、classic ESP32=GPIO16/17）。S3 など他の ESP32 系はスケッチの `#elif` を配線に合わせて変更してください。

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

u-center2 や USB-TTL アダプターを使わず、起動時に Serial1 から設定を送信します。
`examples/ublox_config/ublox_config.ino` を開き、先頭の `UBLOX_GENERATION` を
`10`（既定: M10）、`9`（F9）、`8`（M8）から選択してください。
設定後は `basic_ubx` と同じように受信データを azaraC に渡し、Serial に JSON を出力します。

**配線**: GNSS の **UART1** TX → MCU RX、UART1 RX ← MCU TX、GND 共通。
ESP32 のピンは `basic_nmea` と同じ（C3=20/21、C6=4/5、classic=16/17）。
その他の Serial1 搭載ボードではボードの RX1/TX1 を使います。Uno は対象外です。
電源・I/O 電圧はモジュール仕様に従ってください。
`GNSS_BAUD` は受信機の現在の速度に合わせます（既定 9600、受信機側の速度は変更しません）。
UART1 の UBX 入出力が有効であることが前提です。

**M10 / F9（CFG-VALSET 対応 FW）**:

UBX-CFG-VALSET (`0x06 0x8A`) で次のキーをすべて `1` に設定します。

| キー | ID | 型 |
| --- | --- | --- |
| CFG-MSGOUT-UBX_RXM_SFRBX_UART1 | `0x20910232` | U1 |
| CFG-SIGNAL-QZSS_ENA | `0x10310024` | L |
| CFG-SIGNAL-QZSS_L1S_ENA | `0x10310014` | L |

出典: [u-blox M10 SPG 5.10 Interface description (UBX-21035062 R03)](https://content.u-blox.com/sites/default/files/u-blox-M10-SPG-5.10_InterfaceDescription_UBX-21035062.pdf)
の CFG-MSGOUT / CFG-SIGNAL および UBX-CFG-VALSET。
既定は RAM レイヤーのみで、電源断後は再設定します。BBR にも保持する場合は
payload の layers を `1` から `3`（RAM + BBR）に変更します（バックアップ電源等が必要）。
Flash への保存は行いません。

プロトコル番号だけで互換性を判断せず、機種・FW の Interface description で
CFG-VALSET と L1S 対応を確認してください（M8 の protocol 23.01 と F9/M10 は別系統）。
**F9P は型番・FW によって L1S が非対応の場合があります**。QZSS L1C/A 対応だけでは不十分です。
非対応キーや信号の組み合わせは NAK になり得ます。GPS 等の既存信号設定は変更しません。

**M8**:

UBX-CFG-MSG (`0x06 0x01`) で RXM-SFRBX (`0x02 0x13`) の UART1 rate を `1` にします。
この例では他ポートの同メッセージ出力は `0` になります。
**QZSS L1SAIF（L1S）の有効化は別途必要**で、CFG-GNSS は自動変更しません。
MCU から UBX-CFG-GNSS (`0x06 0x3E`) を poll し、現在のチャネル割り当て・他 GNSS ブロックを
保持したまま、QZSS (`gnssId=5`) ブロックの enable を有効にし、`sigCfgMask` を
`0x05`（L1C/A=`0x01` + L1SAIF=`0x04`）にして書き戻してください。
`sigCfgMask` は flags の bits 16–23 です。対応 FW、GPS との組み合わせ、チャネル数等の
制約を確認し、ACK を待ちます。固定の CFG-GNSS を上書きすると他の測位設定を壊すため、
この例は出力設定だけに留めています。
出典: [u-blox 8 / M8 Receiver description (UBX-13003221 R28)](https://content.u-blox.com/sites/default/files/products/documents/u-blox8-M8_ReceiverDescrProtSpec_UBX-13003221.pdf)
§4.2.2「Configuring QZSS L1SAIF」、UBX-CFG-GNSS / UBX-CFG-MSG。

**結果の確認**: Fletcher チェックサムを計算して送信し、対象 class/id とチェックサムが一致する
UBX-ACK-ACK / NAK を最大 3 秒待ちます。結果は `ACK` / `NAK` / `timeout` と表示します。
NAK は世代・FW・信号設定、timeout は配線・速度・UBX 入出力設定や起動待ち時間を確認してください。
世代の自動フォールバックは行いません。設定中の受信データは破棄されます。
ACK はコマンド受理の意味であり、L1S の受信や災害電文の到来を保証しません。
対応アンテナと受信環境も確認してください。

---

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

### basic_dcx - MT=44（DCX / CAMF）表示

MT=44 の L-Alert / J-Alert / 地方自治体 / 国外 メッセージを、JSON と 1 行要約の両方で出力します。
MT=44 は定義表が約 100 KB あるため既定の AVR プリセットでは無効です。有効化が必要です。

```bash
# ESP32 / RP2040 など（非 AVR の既定は DCX 有効）。そのままビルドできます
# AVR の大型品（Mega など）
-DAZARAC_ENABLE_DCX_CAMF=1   # または -DAZARAC_AVR_LARGE_FLASH=1
```

**出力例**:

```
[MT44] svid=184 service=J-Alert a1=1 a2=111 a3=2 center=35.681236,139.767125 radius_km=120 prefectures=3 cities=0
{"schema_version":2,"svid":184,"msg_type":44,"crc24":"0x00074DAD","data":{...}}
```

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

| カテゴリID | 内容               | filter_by_category サンプルの既定 |
| ---------- | ------------------ | ---------- |
| 1          | 緊急地震速報 (EEW) | ON         |
| 2          | 震源情報           | ON         |
| 3          | 震度情報           | ON         |
| 4          | 南海トラフ地震     | ON         |
| 5          | 津波警報・注意報   | ON         |
| 6          | 北西太平洋津波     | OFF        |
| 8          | 火山情報           | ON         |
| 9          | 降灰情報           | ON         |
| 10         | 気象警報・注意報   | OFF        |
| 11         | 洪水警報           | ON         |
| 12         | 台風情報           | ON         |
| 14         | 海上警報           | OFF        |

ライブラリ既定（非 AVR）は全カテゴリ ON。AVR プリセットは SEISMIC/TSUNAMI のみ有効（上記表はサンプルの `CategoryFilter` 既定であり、ライブラリの `AZARAC_ENABLE_*` 既定とは異なる）。

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

```bash
# Arduino IDE で examples/rtos_freertos/rtos_freertos.ino を開いて書き込み
```

**対応ハードウェア**: ESP32 系（FreeRTOS 必須）。

---

### custom_framer - 独自フレーマ（`IFramer`）の差し込み

受信機が `$QZQSM` でも `RXM-SFRBX` でもない場合に、`azaraC::internal::IFramer` を実装して
1 フレーム分の 250 bit と SVID を `Parser` へ渡す例です。
例ではデバッグ用の 1 行テキスト `AZC,<svid>,<64 桁の 16 進>\n` を 1 フレームとして扱います。

```cpp
class MyFramer : public azaraC::internal::IFramer {
    bool feed(uint8_t byte, azaraC::internal::Frame& out) override;
    void reset() override;
};

MyFramer framer;
azaraC::Parser parser(framer);   // UBX/NMEA の自動判定は行わない
```

**契約**: `feed()` はフレーム完成時だけ `true` を返し、`svid` と `bits[32]` を全て埋めてから返します（部分書きのまま `true` を返すと全ゼロのフレームとして復号されます）。

---

## Example一覧

| Example            | 入力          | 出力                   | 特徴               |
| ------------------ | ------------- | ---------------------- | ------------------ |
| basic_nmea         | NMEA $QZQSM   | Serial JSON            | 最もシンプル       |
| basic_ubx          | UBX-RXM-SFRBX | Serial JSON            | u-bloxバイナリ     |
| ublox_config       | UBX-RXM-SFRBX | Serial JSON + 設定結果 | MCU から u-blox 設定 |
| with_sntp          | NMEA $QZQSM   | Serial JSON + 詳細ログ | SNTP時刻解決       |
| filter_by_category | NMEA/UBX      | Serial JSON            | カテゴリフィルタ   |
| error_handling     | NMEA/UBX      | Serial JSON + 統計     | エラーハンドリング |
| wifi_client        | NMEA/UBX      | Serial + TCP           | ネットワーク出力   |
| basic_uno          | NMEA/UBX      | Serial JSON            | AVR 最小構成 (Uno) |
| basic_dcx          | NMEA/UBX      | Serial JSON + 要約     | MT=44 (DCX/CAMF)   |
| custom_framer      | 独自テキスト  | Serial JSON            | `IFramer` 差し込み |
| rtos_freertos      | NMEA/UBX      | Serial JSON            | FreeRTOS タスクベース |

---

## 共通の配線図

### ESP32-C3 DevKitM-1

```
GNSS Module          ESP32-C3 DevKitM-1
+--------+          +------------------+
| TX  ---+--------→ | GPIO20 (Serial1 RX)
| RX  ---+--------← | GPIO21 (Serial1 TX)
| GND ---+--------→ | GND
| VCC ---+--------→ | 3.3V
+--------+          +------------------+
```

### ピン配置のカスタマイズ

```cpp
// デフォルト (GPIO20, GPIO21)
Serial1.begin(9600, SERIAL_8N1, 20, 21);

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
