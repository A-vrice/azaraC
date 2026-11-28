# azaraC API リファレンス

## 名前空間

すべてのAPIは`azaraC`名前空間に含まれています。

```cpp
#include <azaraC.h>

// 名前空間の使用
using namespace azaraC;
// または
azaraC::Parser parser;
```

---

## クラスリファレンス

### `azaraC::Parser`

メインのパーサークラス。GNSSモジュールからのバイトストリームを処理し、デコード済みメッセージを出力します。

#### コンストラクタ

```cpp
// デフォルトコンストラクタ (UBX/NMEA自動判別)
Parser();

// カスタムフレーマーを使用する場合
explicit Parser(internal::IFramer& framer);
```

このクラスのコピーやムーブはコンパイルエラーになります（dedupテーブルおよびNankaiバッファを二重に確保せず、`framer`も呼び出し側で所有する参照のため）。

#### メソッド

##### `feed()`

1バイトずつデータを投入し、メッセージが完成したかどうかを返します。

```cpp
bool feed(uint8_t byte, Message& out, uint32_t report_unix = 0);
```

**パラメータ:**
| パラメータ | 型 | 説明 |
|-----------|-----|------|
| `byte` | `uint8_t` | GNSSモジュールからの1バイト |
| `out` | `Message&` | 出力メッセージ (戻り値がtrueの場合に有効) |
| `report_unix` | `uint32_t` | UNIX時刻 (省略時: 0 = 未解決) |

**戻り値:** `bool` - フレームが完成し、デコードに成功し、重複でもない場合に `true`。
フレーム未完成・CRC誤り・未対応バージョン（Vn≠1）・コンパイル時に無効なカテゴリ・仕様上未定義のカテゴリ（7/13）・43/44 以外の MT・重複受信・南海トラフのページ集約途中は `false`。
`out` をメッセージとして読めるのは戻り値が `true` のときだけです。`false` を返したときの `out` の内容は未定義で、直前に完成フレームで設定された値や復号途中のフィールドが残ることがあります（フレーム未完成では `out` を書き換えないため、直前の値がそのまま残ります）。個々のフィールドの残留に依存しないでください。
診断用の `msg.unsupported_reason` だけは、復号器が完成フレームを拒否した場合に理由（`DisabledAtCompileTime` / `UnknownCategory` / `UnsupportedVersion`）が入ります。それ以外の `false`（フレーム未完成・CRC誤り・重複・南海トラフのページ集約途中）では `None` のことが多いですが、値は保証されません。

**使用例:**
```cpp
azaraC::Parser parser;
azaraC::Message msg;

void loop() {
    while (Serial1.available()) {
        uint8_t byte = Serial1.read();
        uint32_t now = (uint32_t)time(nullptr); // SNTPから取得
        
        if (parser.feed(byte, msg, now)) {
            // メッセージ受信完了
            processMessage(msg);
        }
    }
}
```

##### `feed()`（一括）

受信バッファをそのまま流し込みます。内部では 1 バイト版の `feed()` を順に呼ぶだけで、Nankai 集約・重複除去を含め挙動は同じです。

```cpp
bool feed(const uint8_t* data, size_t len, Message& out, uint32_t report_unix = 0);
```

| パラメータ | 型 | 説明 |
|-----------|-----|------|
| `data` | `const uint8_t*` | 入力バッファ（`nullptr` は `false`） |
| `len` | `size_t` | バイト数（0 は `false`） |
| `out` | `Message&` | 出力（最後に成立した電文） |
| `report_unix` | `uint32_t` | UNIX時刻 (省略時: 0 = 未解決) |

**戻り値:** `bool` - 1 通以上成立したら `true`。最初の成立で停止せず、全バイトを処理します。`out` には最後に成立した電文が残り、後続の重複や43/44以外のMTでは消えません。
複数の電文を取りこぼしたくないときは `feedUntilMessage()` を使ってください。
南海トラフ集約の `aggregated_text_ptr` は、同じ呼び出しの後続フレームで借用先のバッファが再利用されると無効になることがあります。
成立しなかったときは `false` を返し、`out.valid` は `false` になります（`nullptr`・長さ 0 の入力を含む）。
復号器の拒否理由は `out.unsupported_reason` に残ります。`nullptr` または長さ 0 の入力ではこの理由を変更しません。それ以外の出力フィールドは `false` のとき未定義です。

```cpp
uint8_t buf[512];
const int bytesRead = client.read(buf, sizeof(buf));
if (bytesRead > 0 && parser.feed(buf, static_cast<size_t>(bytesRead), msg, now)) {
    azaraC::toJson(msg, Serial);
}
```

##### `feedUntilMessage()`

```cpp
size_t feedUntilMessage(const uint8_t* data, size_t len, Message& out, uint32_t report_unix = 0);
```

| 引数 | 型 | 説明 |
|---|---|---|
| `data` | `const uint8_t*` | 入力バッファ。`nullptr` は0を返す |
| `len` | `size_t` | バイト数 |
| `out` | `Message&` | 出力先。読めるのは戻ったときに `out.valid` が `true` のときだけ |
| `report_unix` | `uint32_t` | 時刻解決に使う報告のUNIX epoch。0は未解決 |

先頭から1バイト版の `feed()` を順に呼び、電文が1通成立した時点で止めます。戻り値は消費したバイト数です。
`out.valid` が `true` なら、消費した最後のバイトで電文が成立しています。成立しなかったときは `len` を返し、`out.valid` は `false` です。
残りのバイトを渡し直せば、1つのバッファに入った複数の電文を順にすべて受け取れます。

```cpp
uint8_t buf[512];
const int bytesRead = client.read(buf, sizeof(buf));
size_t n = bytesRead > 0 ? static_cast<size_t>(bytesRead) : 0;
const uint8_t* p = buf;
while (n > 0) {
    size_t used = parser.feedUntilMessage(p, n, msg, now);
    if (msg.valid) azaraC::toJson(msg, Serial);
    p += used;
    n -= used;
}
```

##### `reset()`

パーサーの状態をリセットします。フレーマー、デコーダー、重複除去フィルタ、**NankaiPageBufferManager**が初期化されます。

```cpp
void reset();
```

##### `getNankaiBuffer()`

南海トラフメッセージのページ集約バッファを取得します。

```cpp
const internal::NankaiPageBuffer* getNankaiBuffer(const internal::NankaiPageKey& key) const;
```

`NankaiPageKey`の識別子は`{info_code, information_type, report_timeのmonth/day/hour/minute, report_classification}`です（`information_type`は発表=0/取消=2で、同一`info_code`+報告時刻の発表と取消を別情報として扱うために含めます。`report_classification`は実警報=2/訓練・試験=7で、訓練と実警報を混ぜないために含めます）。
呼び出しキーは`NankaiPageKey{info_code, month, day, hour, minute, information_type, report_classification}`で生成します。`report_classification`は電文の`Mt43Data::report_classification`と一致させてください（既定値の0では実警報・訓練のどちらのバッファにも一致しません）。
`report_time`はそのまま渡すこと（`resolveTime`の正規化でキーが変わらないようにするため）。

返るバッファは受信途中でもよく、完了判定は `isComplete()` で行います。返却ポインタは次の `feed()` / `reset()` までのみ有効です。

---

### `azaraC::internal::NankaiPageBufferManager`

南海トラフ複数ページメッセージの集約を管理するクラス。

#### コンパイル時設定

| マクロ | デフォルト | 説明 |
|--------|-----------|------|
| `AZARAC_NANKAI_MAX_PAGES` | 63 | 1 電文あたりの最大ページ数（仕様上の最大も 63） |
| `AZARAC_NANKAI_BUFFERS` | 1 | 同時に追跡可能な南海トラフ地震の数 |

#### メモリ使用量

各バッファはページを`aggregated_text[MAX_PAGES * 18 + 1]`に保管します：
- バッファあたり: メタデータ24B + `MAX_PAGES×18+1` B（既定63ページで1,135B、構造体サイズはアラインメント込み1,160B）
- バッファ: 既定1バッファで約1.16KB。バッファ数を増やすと比例して増加（4バッファ・63ページで4,640B）

#### LRU エビクション

全てのバッファが使用中の場合、最も古いバッファが自動的に解放されます。

---

### `azaraC::Message`

デコード済みメッセージを格納する構造体。

#### 共通フィールド

| フィールド | 型 | 説明 |
|-----------|-----|------|
| `svid` | `uint8_t` | 衛星ID。QZSS L1S PRN（`Satellite ID \| 0x80`）。DCR は 183–191、DCX 実データには 181/182 もある |
| `msg_type` | `uint8_t` | メッセージタイプ (43=DCR, 44=DCX) |
| `crc24` | `uint32_t` | CRC-24Qチェックサム |
| `valid` | `bool` | メッセージの妥当性フラグ。`feed()` が `true` を返したときは常に `true` |
| `unsupported_reason` | `UnsupportedReason` | 復号器が完成フレームを拒否した理由（`None` / `DisabledAtCompileTime` / `UnknownCategory` / `UnsupportedVersion`）。`UnknownCategory` は仕様上未定義のカテゴリと 43/44 以外の MT。`feed()` が `false` でも診断用に入ることがあるが、`out` の他のフィールドは一括版の `valid == false` を除き未定義（`feed()` の戻り値の説明を参照） |
| `payload_type` | `MsgPayloadType` | ペイロードタイプ |

#### 安全なアクセサ

```cpp
// MT=43 データへのアクセス
const Mt43Data* getMt43() const;

// MT=44 データへのアクセス
const Mt44Data* getMt44() const;
```

**使用例:**
```cpp
void processMessage(const azaraC::Message& msg) {
    if (msg.msg_type == 43) {
        const azaraC::Mt43Data* mt43 = msg.getMt43();
        if (mt43) {
            uint8_t category = mt43->disaster_category;
            // MT=43 固有の処理
        }
    } else if (msg.msg_type == 44) {
        const azaraC::Mt44Data* mt44 = msg.getMt44();
        if (mt44) {
            auto kind = mt44->service_kind;
            // MT=44 固有の処理
        }
    }
}
```

---

### `azaraC::Mt43Data` (MT=43 QZQSM)

JMA DC Reportメッセージのデータ構造。

#### 共通フィールド

| フィールド | 型 | ビット位置 | 説明 |
|-----------|-----|-----------|------|
| `report_classification` | `uint8_t` | [14..16] | 報告分類 (3bits) |
| `disaster_category` | `uint8_t` | [17..20] | 災害カテゴリ (4bits) |
| `information_type` | `uint8_t` | [41..42] | 情報種別 (2bits) |
| `event_time` | `TimeFields` | [21..40] | イベント日時（month[21..24]/day[25..29]/hour[30..34]/min[35..40]） |
| `version` | `uint8_t` | [214..219] | Vn。仕様は 1 を要求し、1 以外は `UnsupportedVersion` としてデコードを拒否する |

#### 災害カテゴリ

`Mt43Data` はタグ付きユニオンで、有効なペイロードは対応する getter で取得します（`active_type` が一致しなければ `nullptr`）。

| カテゴリID | 名称 | アクセサ |
|-----------|------|-----------|
| 1 | 緊急地震速報 (EEW) | `getEew()`（`AZARAC_ENABLE_EEW=1` のときのみ。0 では `EewData` 型自体が存在しない） |
| 2 | 震源情報 | `getHypocenter()`（`AZARAC_ENABLE_HYPOCENTER=1` のときのみ。0 では `HypocenterData` 型自体が存在しない） |
| 3 | 震度情報 | `getSeismic()` |
| 4 | 南海トラフ地震 | `getNankai()`（`AZARAC_ENABLE_NANKAI=1` のときのみ） |
| 5 | 津波警報・注意報 | `getTsunami()` |
| 6 | 北太平洋津波 | `getNwPac()` |
| 8 | 火山情報 | `getVolcano()` |
| 9 | 降灰情報 | `getAshFall()` |
| 10 | 気象警報・注意報 | `getWeather()` |
| 11 | 洪水警報 | `getFlood()` |
| 12 | 台風情報 | `getTyphoon()` |
| 14 | 海上警報 | `getMarine()` |

#### EEWデータ (`EewData`)

`AZARAC_ENABLE_EEW=1`（非AVRの既定）のときだけ定義されます。
0のときはこの型と `getEew()` は存在しないため、コードで参照する場合は `#if (AZARAC_ENABLE_EEW)` で囲む必要があります（`HypocenterData` / `NankaiData` についてもそれぞれ同様の処理が必要）。

```cpp
struct EewData {
    uint8_t  long_period_lower;   // 長周期地震動下限 (3bits)
    uint8_t  long_period_upper;   // 長周期地震動上限 (3bits)
    uint16_t notification[3];     // 防災気象情報通知 (3×9bits)
    uint8_t  notification_count;  // 通知数
    TimeFields quake_time;        // 発震時刻
    uint16_t depth;               // 震源の深さ (×10km)
    uint8_t  magnitude;           // マグニチュード (×0.1)
    uint16_t epicenter;           // 震央地名コード
    uint8_t  intensity_lower;     // 震度下限 (4bits)
    uint8_t  intensity_upper;     // 震度上限 (4bits)
    uint8_t  region_bitmap[10];   // 予報区 80 区のビットマップ（bit i = 予報区 i+1）
    // アクセサ: regionCount() = 対象予報区数、regionAt(i) = 昇順 i 番目の予報区コード
    // (1..80、範囲外は 0)、addRegion(code) = テスト等で予報区を追加
};
```

#### 台風データ (`TyphoonData`)

```cpp
struct TyphoonData {
    TimeFields reference_time;  // 基準時刻
    uint8_t    ref_type;        // 参照時刻種別 (1:Analysis 2:Estimate 3:Forecast)
    uint8_t    elapsed;         // 経過時間 (時間)
    uint8_t    number;          // 台風番号
    uint8_t    scale;           // 大きさ (4bits)
    uint8_t    intensity;       // 強さ (4bits)
    LatLon     coords;          // 台風位置
    uint16_t   pressure;        // 中心気圧 (hPa)
    uint8_t    max_wind;        // 最大風速 (m/s)
    uint8_t    max_gust;        // 最大瞬間風速 (m/s)
};
```

---

### `azaraC::Mt44Data` (MT=44 DCX/CAMF)

DCX/CAMFメッセージのデータ構造。

#### 共通フィールド

| フィールド | 型 | 説明 |
|-----------|-----|------|
| `service_kind` | `Mt44ServiceKind` | サービス種別 |
| `is_null_message` | `bool` | Null Messageフラグ |
| `sd` | `Mt44Sd` | 送信元情報 |
| `camf` | `Mt44CamfRaw` | CAMFフィールド (Raw) |
| `onset_time` | `TimeFields` | ハザード発生日時 |
| `ex_kind` | `ExtendedKind` | 拡張メッセージ種別 |
| `mt44_decoded` | `Mt44Decoded` | デコード済み情報 |

#### サービス種別 (`Mt44ServiceKind`)

| 値 | 名称 | 説明 |
|---|------|------|
| `NullMessage` | Null Message | A1=0, A2=111, A3=0, かつ全CAMFフィールド(A4–A18)および拡張フィールドがゼロ |
| `LAlert` | L-Alert | A2=111, A3=1 |
| `JAlert` | J-Alert | A2=111, A3=2,3 |
| `LocalGovernment` | 地方自治体 | A2=111, A3=4 |
| `OutsideJapan` | 国外 | A2≠111 |
| `Unknown` | 不明 | 上記以外（A3=0, 5–31 を含む） |

#### CAMFフィールド (`Mt44CamfRaw`)

| フィールド | 型 | ビット数 | 説明 |
|-----------|-----|---------|------|
| `a1` | `uint8_t` | 2 | メッセージ種別 |
| `a2` | `uint16_t` | 9 | 国/地域コード |
| `a3` | `uint8_t` | 5 | プロバイダID |
| `a4` | `uint8_t` | 7 | ハザード種別 |
| `a5` | `uint8_t` | 2 | 深刻度 |
| `a6` | `uint8_t` | 1 | 週コード |
| `a7` | `uint16_t` | 14 | 発生日時 |
| `a8` | `uint8_t` | 2 | ハザード継続時間 |
| `a9` | `uint8_t` | 1 | ライブラリ選択 |
| `a10` | `uint8_t` | 3 | ライブラリバージョン |
| `a11` | `uint16_t` | 10 | 国際/国内ライブラリコード |
| `a12` | `uint16_t` | 16 | 緯度コード |
| `a13` | `uint32_t` | 17 | 経度コード |
| `a14` | `uint8_t` | 5 | 長半径 |
| `a15` | `uint8_t` | 5 | 短半径 |
| `a16` | `uint8_t` | 6 | 方位角 |
| `a17` | `uint8_t` | 2 | 拡張フィールド種別 |
| `a18` | `uint16_t` | 15 | 拡張データ |

#### A17 拡張フィールド (EWSS CAMF v1.2)

| A17値 | 名称 | 説明 |
|-------|------|------|
| 00 | B1 | Improved Resolution of Main Ellipse |
| 01 | B2 | Hazard Center Position |
| 10 | B3 | Secondary Ellipse Definition |
| 11 | B4 | Quantitative and Detailed Information (D1-D36) |

**B4 (A17=11)** D-series フィールド（D1〜D36）は、デコード時に内部計算され JSON シリアライズで出力されます。
`Mt44CamfRaw` 上には B4 の有無を示す `b4_present` (bool) のみが保持されます。
個別の D-field 値はシリアライズ時に `decodeB4DetailedInfo(a18, a4, out)` で再計算されます。

```cpp
// B4 の有無を確認
if (mt44->camf.b4_present) {
    // D1-D36 の値は azaraC::toJson(msg, out) で自動的に出力されます
    // 個別の値が必要な場合は、decodeB4DetailedInfo() を直接呼び出してください:
    // B4DetailedInfo b4;
    // internal::decodeB4DetailedInfo(mt44->camf.a18, mt44->camf.a4, b4);
    // if (b4.d_present[i]) { uint8_t d = b4.d_values[i]; }
}
```

#### デコード済み楕円 (`DecodedEllipse`)

```cpp
struct DecodedEllipse {
    int32_t lat_microdeg;              // microdegrees (×1,000,000)
    int32_t lon_microdeg;              // microdegrees (×1,000,000)
    int32_t semi_major_m;              // meters (×1,000 from km)
    int32_t semi_minor_m;              // meters (×1,000 from km)
    int32_t azimuth_decideg;           // dexadegrees (×100,000)
    int32_t b1_lat_offset_microdeg;    // microdegrees (×1,000,000)
    int32_t b1_lon_offset_microdeg;    // microdegrees (×1,000,000)
    int32_t b1_refined_semi_major_m;   // meters (×1,000 from km)
    int32_t b1_refined_semi_minor_m;   // meters (×1,000 from km)
};
```

---

### `azaraC::TimeFields`

日時情報を格納する構造体。

```cpp
struct TimeFields {
    uint8_t  month;      // 月 (1-12, 0=未解決)
    uint8_t  day;        // 日 (1-31, 0=未解決)
    uint8_t  hour;       // 時 (0-23)
    uint8_t  minute;     // 分 (0-59)
    uint32_t unix_time;  // UNIX時刻 (0=未解決)
};
```

---

### `azaraC::LatLon`

緯度経度情報を格納する構造体。

```cpp
struct LatLon {
    uint8_t  lat_ns;    // 北緯/南緯 (0=N, 1=S)
    uint8_t  lat_deg;   // 緯度度 (0-89)
    uint8_t  lat_min;   // 緯度分 (0-59)
    uint8_t  lat_sec;   // 緯度秒 (0-59)
    uint8_t  lon_ew;    // 東経/西経 (0=E, 1=W)
    uint16_t lon_deg;   // 経度度 (0-179)
    uint8_t  lon_min;   // 経度分 (0-59)
    uint8_t  lon_sec;   // 経度秒 (0-59)
};
```

---

## グローバル関数

### `toJson()`

MessageをJSON形式で出力します。

```cpp
void toJson(const Message& msg, Print& out);
size_t toJson(const Message& msg, char* buf, size_t len, size_t* required = nullptr);
```

**パラメータ:**
| パラメータ | 型 | 説明 |
|-----------|-----|------|
| `msg` | `const Message&` | シリアライズするメッセージ |
| `out` | `Print&` | 出力先 (Serial, WiFiClient等) |
| `buf` | `char*` | 固定長の出力バッファ（`nullptr` は書き込みなし） |
| `len` | `size_t` | `buf` の容量（NUL 終端を含む）。0 は書き込みなし |
| `required` | `size_t*` | 省略可。完全な JSON の長さ（NUL を除く）を格納する |

`Print&` 版の出力は従来どおりです。バッファ版も同じ JSON を生成し、実際に格納したバイト数（NUL を除く）を返します。
`buf != nullptr && len > 0` なら必ず `buf[戻り値]` を NUL 終端し、容量を超える部分は捨てます。`*required > 戻り値` なら切り詰められています。完全な JSON には `*required + 1` バイトが必要です。
`buf == nullptr` または `len == 0` の場合は何も書かず 0 を返しますが、`required` が非 `nullptr` なら完全な長さを計算します。ヒープ確保は行いません。切り詰めた出力は有効な JSON や UTF-8 とは限らないため、そのまま送信しないでください。

```cpp
char json[512];
size_t required = 0;
const size_t written = azaraC::toJson(msg, json, sizeof(json), &required);
if (written == required) {
    Serial.write(reinterpret_cast<const uint8_t*>(json), written);
}
```

**スレッド安全性:** AVR / 非 AVR のどちらもラベル用の共有バッファ（`AZARAC_FLASH_BUF_SIZE` の 1 本）を使うため、`toJson()` と定義テーブルの lookup を複数のタスク/スレッドから同時に呼ばないこと。AVR では lookup のたびに Flash からこのバッファへコピーする。
FreeRTOS では呼び出し側で排他する（`examples/rtos_freertos` の `printJson()` を参照）。

**使用例:**
```cpp
// Serialに出力
azaraC::toJson(msg, Serial);
Serial.println();

// WiFiClientに出力
WiFiClient client;
if (client.connect(server, port)) {
    azaraC::toJson(msg, client);
    client.println();
}
```

---

### `Parser::updateClock()`

```cpp
void updateClock();
```

受信バイトがなくても内部時計を観測し、32 bit 世代の切り替わりや大きな時計の後退で重複履歴・南海トラフ集約をリセットします。電文は出力しません。
32 bit `millis()` を使う Arduino では、`loop()` から 49.7 日（2^32 ms）未満の間隔で定期的に呼んでください。観測なしで一周以上すると経過した周回数を復元できません。
ESP32 は `esp_timer_get_time()` の 64 bit 時刻を使うため、長い無受信期間でも周回を失いません。外部リンケージの `inline getMillis()` は引き続き全 TU で状態を共有します。
他の Parser 操作と同じタスクから呼んでください。時計の観測で南海トラフ集約が破棄されると、以前返された集約本文への借用ポインタも無効になります。

### `crc24q()`

```cpp
uint32_t crc24q(const uint8_t* data, uint16_t bit_len);
```

受信経路と同じ CRC-24Q 実装を公開します。`data[0]` の MSB から `bit_len` ビットを処理し、下位 24 ビットに CRC を返します（初期値 0、最終 XOR なし）。長さはバイト数ではありません。
`bit_len == 0` は 0 を返します。それ以外では `data` に少なくとも `ceil(bit_len / 8)` バイトの読み出せる領域が必要です。ポインタや容量の検証は行いません。
L1S フレームでは bit 0〜225 の CRC を計算し、bit 226〜249 の受信 CRC と照合します。通常の受信処理は `Parser` が行うため、自前の電文生成や検証向けです。

---

## コンパイル時設定

ビルドフラグ（`-DAZARAC_...=...`、PlatformIO の `build_flags`、arduino-cli の `--build-property compiler.cpp.extra_flags=...`）で指定します。
スケッチ冒頭の `#define` はライブラリ側（別 TU）で認識されず、`Parser`などのサイズが TU(翻訳単位) 間でずれるため使えません。
設定のマクロは[`azaraC_config.h`](https://github.com/A-vrice/azaraC/tree/main/src/azaraC_config.h)で定義されています。

### 汎用設定

| マクロ | デフォルト | 説明 |
|-------|-----------|------|
| `AZARAC_DEDUP_SLOTS` | 512 | 重複判定表のエントリ数（`AZARAC_DEDUP_WAYS`の倍数、商は2の冪）。1エントリ8B |
| `AZARAC_DEDUP_WAYS` | 8 | 表の連想度（1セットあたりのエントリ数）。大きいほどハッシュ衝突に強い |
| `AZARAC_DEDUP_WINDOW_MS` | 86400000 | 情報有効時間(ms)のフォールバック。災害種別ごとの配信終了条件（MT=43）と MT=44 の A8 由来の窓（`internal/DedupWindow.h`）に無いカテゴリだけがこれを使う |

### 言語選択

| マクロ | デフォルト | 説明 |
|-------|-----------|------|
| `AZARAC_LANG_JA` | 1 | 日本語ラベルを有効化 |
| `AZARAC_LANG_EN` | 0 | 英語ラベルを有効化 |

両方が 1 のときは日本語を優先し、その項目に日本語テーブルが無ければ代わりに英語を使う。
`AZARAC_LANG_JA=0 / AZARAC_LANG_EN=1` では英語ラベルを出力する。
英語テーブルを持たない項目（例: 南海トラフの情報番号）は `AZARAC_LANG_JA=1` の間だけ日本語で出る。
`AZARAC_LANG_JA=0` ではその日本語表がコンパイルされないので `null` になる（生コードは残る）。
どちらも 0 のときは原則ラベルを出力しない。
欠落時は `null`、定義済みで空文字列のラベルは `""` として出力される。
ただし言語非依存表（北西太平洋津波の 3 表など）は値があれば 0/0 でも解決して返す。

英語ラベルはazarashi 0.17.1の定義テーブルに由来する。
`AZARAC_LANG_EN`で有効になるのは`_en`という接尾辞のヘッダで、対応する日本語表と対で生成される。

逆に**日本語版を持たない英語専用表**（北西太平洋津波の `potential` / `height` / `region`）は言語非依存で、`AZARAC_LANG_EN` の設定に関係なく常に出力される。
これはCAMF自体が英語で日本語メッセージの定義が存在しないためで、同じ仕様を参照する他のテーブルも同様の処理がなされる場合がある。
（定義テーブルの`_en`のうち、言語切替の対象になるのは対応する日本語テーブルが存在する場合のみ）

**両方 1 のときの併記**: `AZARAC_LANG_JA=1`かつ`AZARAC_LANG_EN=1`のとき、文字列リテラルのキーを持つ `_label` フィールドには `_label_en` が併記される。
`_label` は日本語優先（無ければ英語）、`_label_en` は常に英語となる。

```json
{ "depth": 60, "depth_label": "60km", "depth_label_en": "60 km" }
```

配列要素のうち、汎用キー（`notifications[].label` / `regions[].label` / `prefectures[].label` / `cities[].label` / `local_govs[].label` / `entries[].region_label`）の要素は `_label_en` を持たない。（要素ごとにコード体系が異なり、固定キー名では併記できないため）
逆に固定の文字列リテラルキー（`AZARAC_LABEL`）は配列要素でも `_label_en` を併記する（例: 震度の `entries[].intensity_label`）。
要素ごとに言語を選びたい場合は`AZARAC_LANG_JA=0 / AZARAC_LANG_EN=1` 構成を使うこと。

数量フィールド（`depth` / `magnitude` / `pressure` / `max_wind` / `max_gust` / `elapsed` / `number`）についても `_label` / `_label_en` が含まれる。
これには生のコード値だけでは意味が取れない値も含む(以下の表参照)。

| コード | ラベル | 意味 |
|---|---|---|
| `depth` 501 | `500kmより深い` / `Deeper than 500 km` | 範囲の境界 |
| `magnitude` 101 | `10.0より大きい` / `Over 10.0` | 範囲の境界 |
| `magnitude` 126（震源情報のみ） | `不明(8.0より大きい)` / `Unknown (Over 8.0)` | 範囲の境界 |
| `depth` 511 / `magnitude` 127 | `不明` / `Unknown` | センチネル |
| `max_wind` 0 / `max_gust` 0 | `不明` / `Unknown` | センチネル |

センチネルは全フィールド共通ではなく、例えば`depth`の0は`0km`、`pressure`の0は`0hPa`、`elapsed`の0は`0時間後`で、それぞれ実値として意味を持つ。
ただし`number`の0は`typhoon_number`表（1スタート）に無いため`number_label`は`null`となる。

`AZARAC_LANG_EN=0`（既定）では`_label_en`は出力されない。
`AZARAC_LANG_JA=0 / AZARAC_LANG_EN=1`の場合、`_label`自体がすべて英語になるため`_label_en`ではなく`_label`に英語が出力される。
包括すると`_label_en`が出るのは**日本語/英語ともに有効にした構成のみ**。

### 受信ポリシー

| マクロ | デフォルト | 説明 |
|-------|-----------|------|
| `AZARAC_ENABLE_DEDUP` | 1 | 0 では dedup 履歴を持たず、再放送を dedup では抑止しない。南海トラフのページ集約・受信済みページの抑止は残る（下記）。`AZARAC_DEDUP_*` は未使用となり、履歴の RAM（既定でホスト 4 KB / AVR 512 B）を削減 |
| `AZARAC_NMEA_STRICT_SVID` | 0 | `$QZQSM` の衛星 ID 受理範囲。0: 2 桁の 00–63、1: 53–63（PRN 181–191）、2: 仕様表の 55/56/57/58/61 のみ。0–2 以外はコンパイルエラー |
| `AZARAC_NMEA_REJECT_NONZERO_PADDING` | 0 | 0: bit 250–255 の詰め物をマスクして受理、1: 非 0 なら拒否。63 桁 / 64 桁の両方の hex 表現に適用。CRC 被覆外の領域で、既定は実機互換を優先 |

重複排除を無効にしても CRC 検査や南海トラフのページ集約は残り、すべてのバイトや未完成ページが出力されるわけではありません。
南海トラフの完成済み複数ページ集合は、同じ集約バッファを保持している間、再受信しても出力しません。`NankaiPageBuffer::TIMEOUT_MS` は 60000 ms で、最後の新規ページ（完成時）から **60 秒を超える**と失効します（ちょうど 60 秒では失効しません）。完成後の重複ページはこの時刻を更新しません。失効後に全ページを再受信・再集約すると、`AZARAC_ENABLE_DEDUP=0` では再び出力されます。未完成集合は重複ページでも寿命を延長します。reset・時計補正によるクリアや、別事象によるバッファの追い出しでは、期限前でも集約状態が失われます。
各設定はライブラリを含む全翻訳単位に同じ値を指定してください（ビルドフラグ、または `azaraC_config.h`）。
`azaraC.h` は Arduino コアの `abs` / `min` / `max` マクロをヘッダの読み込み中だけ退避し、読み込み後に元の定義へ戻します。元々無いマクロは未定義のままです。

### 災害カテゴリ選択

不要なカテゴリの定義テーブルをコンパイル時に除外することでFlash使用量を削減可能。
日本語表と英語表はともに**そのカテゴリを無効にすると両方が同時に除外される**（`AZARAC_LANG_EN` だけの英語専用表も含む）。

| マクロ | デフォルト | 説明(カテゴリ) |
|-------|-----------|------|
| `AZARAC_ENABLE_EEW` | 1 | 緊急地震速報 (カテゴリ1) |
| `AZARAC_ENABLE_HYPOCENTER` | 1 | 震源情報 (カテゴリ2) |
| `AZARAC_ENABLE_SEISMIC` | 1 | 震度情報 (カテゴリ3) |
| `AZARAC_ENABLE_NANKAI` | 1 | 南海トラフ地震 (カテゴリ4) |
| `AZARAC_ENABLE_TSUNAMI` | 1 | 津波警報 (カテゴリ5) |
| `AZARAC_ENABLE_NW_PAC_TSUNAMI` | 1 | 北太平洋津波 (カテゴリ6) |
| `AZARAC_ENABLE_VOLCANO` | 1 | 火山情報 (カテゴリ8) |
| `AZARAC_ENABLE_ASH_FALL` | 1 | 降灰情報 (カテゴリ9) |
| `AZARAC_ENABLE_WEATHER` | 1 | 気象警報 (カテゴリ10) |
| `AZARAC_ENABLE_FLOOD` | 1 | 洪水警報 (カテゴリ11) |
| `AZARAC_ENABLE_TYPHOON` | 1 | 台風情報 (カテゴリ12) |
| `AZARAC_ENABLE_MARINE` | 1 | 海上警報 (カテゴリ14) |
| `AZARAC_ENABLE_DCX_CAMF` | 1 | DCX/CAMF全般 (MT=44) |

`AZARAC_ENABLE_EEW` / `AZARAC_ENABLE_HYPOCENTER` / `AZARAC_ENABLE_NANKAI` を 0 にすると、定義テーブルだけでなく**payload 型そのもの**（`EewData` / `HypocenterData` / `NankaiData`）と対応する取得関数（`getEew()` など）もコンパイル対象から外れる。
また同時に`Mt43Data` のペイロードサイズ（`storage_size_`）は残ったカテゴリのうち最大の `sizeof` まで小さくなる。
AVR プリセットは EEW・震源が既定で 0 なので `sizeof(Mt43Data)` は 75B、`Message` は 84B となる（EEW を有効にしても予報エリアは `region_bitmap[10]` 保持のため 75B / 84B のまま。DCRの全カテゴリおよび DCX/CAMF 有効時は `Mt44Data` 190B、`Message` 199Bとなる。avr-gcc `-Os`、ATmega328Pボードの設定で計測）。
無効にしたカテゴリの型を扱うコードはコンパイルエラーになるので異なるアーキテクチャーでコードを使いまわす場合は `#if (AZARAC_ENABLE_EEW)` などで囲む必要がある（`examples/filter_by_category`・`examples/with_sntp` の EEW ブロックを参照のこと）。

### リソース制約・AVR 関連

| マクロ | デフォルト | 説明 |
|-------|-----------|------|
| `AZARAC_FLASH_BUF_SIZE` | AVR: カテゴリ連鎖（既定=64）/ 非 AVR: 800 | ラベル引き当て用の共有RAMバッファサイズ (バイト)。AVRでは有効カテゴリに応じて 64（SEISMIC/TSUNAMI など）/ 80（＋北西太平洋津波）/ 96（＋火山・洪水）/ 540（＋南海トラフ）/ 640（＋緊急地震速報・震源）/ 800（＋DCX/CAMF）に自動選択。有効なカテゴリの最長ラベルを必ず収める（`make -C test bench` の `FLASH_BUF_OK` ゲート）。非 AVR でも join 系（`azarac_pgm_join_z` / `azarac_pgm_join3`）と `azarac_pgm_len` の打ち切りに使う |
| `AZARAC_DEDUP_MT44_MAX_WINDOW_MS` | 300000 | MT=44 の情報有効時間(ms)の上限。`__AVR__`のみ定義され、常に A8 由来の窓（最短6時間）を置き換える。ホストは上限を設けず A8 の窓をそのまま使う |
| `AZARAC_KEY_BUF_SIZE` | 36 | AVR で JSON のキーと固定値リテラルを Flash から書き出すときのスタック上の一時バッファのバイト数（どちらも `AZARAC_KEY("...")` で包む。値は `wf_s` の `JsonKey` オーバーロードが受ける）。最長はキーの35B（`a17_type_of_specific_settings_label`）、値は20B（`unsupported_category`）で、`JsonKey` の生成時に `static_assert` が収まらないリテラルをコンパイルエラーにする。非AVRでは使われない |

`AZARAC_FLASH_BUF_SIZE` は 64 未満をコンパイル時に拒否します。ラベルの切り詰めでは末尾の不完全な UTF-8 文字を捨て、文字境界に戻します（ラベル全体が収まる保証ではありません）。

**AVRプリセット**: `__AVR__`では`azaraC_config.h`のプリセットがAVR専用のものに置き換わる。具体的には以下の変更が行われる。
有効カテゴリはボードによらず**SEISMIC/TSUNAMIのみ**。
他10カテゴリは大容量ボードでも無効となる（全部同時にすると、たとえ 256KB のボードでも 250,138B/262,144B となりユーザーのコードを 12KB しか置けなくなる）。
DCX/CAMFはオプトインで、`AZARAC_AVR_LARGE_FLASH=1`または`AZARAC_ENABLE_DCX_CAMF=1`を指定すると有効になる。（このときATmega2560 + DCX/CAMF + SEISMIC/TSUNAMI、日本語でフラッシュ148KB / RAM 892B を計測済み）。
その他には`AZARAC_DEDUP_SLOTS=64`（`AZARAC_DEDUP_WAYS=8`、512B）、`AZARAC_DEDUP_MT44_MAX_WINDOW_MS=300000`、`AZARAC_NANKAI_BUFFERS=1`、`AZARAC_NANKAI_MAX_PAGES=4`となる。
但しコンパイル時の `-D` などで明示することで設定は上書きできる（例: DCX/CAMF有効化 `-DAZARAC_ENABLE_DCX_CAMF=1`、全カテゴリ有効化 `-DAZARAC_ENABLE_EEW=1 ...`）。

**AVR 標準ライブラリシム**: AVRツールチェーンはlibstdc++を含まないため、`#if defined(__AVR__)`で`src/internal/avr_std/`の最小シム（`cstddef`/`cstdint`/`cstring`/`new`/`optional`/`string_view`）が自動で適用される。
これを利用してライブラリの利用方法/APIはほかのアーキテクチャと揃うようになっている。

**64KiBを超えるFlashをもつAVR**: 定義テーブルは64KiBを超えて配置されるため、`AZARAC_PGM_READ_*` / `AZARAC_STRCPY_P`（16bitのPROGMEMポインタ）では範囲外になる。
このとき定義テーブル自身は `internal/FlashString.h` が far 参照へ切り替わる。
RAM上の文字列と固定リテラルを比較するときは `AZARAC_STRNCMP_P(a, "literal", n)` を使用すること（AVRでは `strncmp_P(a, PSTR(b), n)` になり、リテラルが SRAM に載らない。非AVRでは `strncmp`）。
16bit読み出しを使うのは一部progmemクラスタに置く（`AZARAC_PROGMEM_NEAR`: CRC24Q・半径・B4レイアウト）とJSONキー（`PSTR`）のみ。
この時自前のデータを追加で置く場合も avr-libc のfar API（`pgm_get_far_address` + `pgm_read_*_far` / `memcpy_PF`）を使用する必要がある。
64KiB超のデバイスでは `AZARAC_PROGMEM` の `*(.progmem.*)` が Arduino コア（`core.a`）と競合するため `.text.azaraC.<N>` に配置される。
この競合によりコア自身のPROGMEMが16bitで扱える範囲外に押しだされる。
この実装の内部の詳細は開発者ガイドの「静的な定義テーブルを使用すること」を参照。

---

## 内部インターフェース

### `azaraC::internal::IFramer`

カスタムフレーマーを実装するためのインターフェース。

```cpp
class IFramer {
public:
    virtual bool feed(uint8_t byte, Frame& out) = 0;
    virtual void reset() = 0;
    virtual ~IFramer() = default;
};
```

**実装例:**
```cpp
class MyFramer : public azaraC::internal::IFramer {
public:
    bool feed(uint8_t byte, azaraC::internal::Frame& out) override {
        // フレーミング処理
        // フレーム完成時: return true
        return false;
    }
    
    void reset() override {
        // 状態リセット
    }
};
```

---

## 使用パターン

基本パターンは[はじめに](getting-started.md#クイックスタート)を参照。

### エラーハンドリング付きパターン

```cpp
// feed() が true を返したメッセージだけを渡す（msg.valid はそこで保証される）。
// false のときの out は未定義（直前の値や復号途中のフィールドが残り得る）。
// 診断用に msg.unsupported_reason だけは復号器の拒否理由が入ることがある。
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

---

## 関連ドキュメント

- [アーキテクチャドキュメント](architecture.md)
- [開発者ガイド](developer-guide.md)
