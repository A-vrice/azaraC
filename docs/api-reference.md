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

**戻り値:** `bool` - 新しいメッセージが完成した場合に `true`

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

`NankaiPageKey`の識別子は`{info_code, report_timeのmonth/day/hour/minute}`です。呼び出しキーは`NankaiPageKey{info_code, month, day, hour, minute}` で生成できます。引数は `Decoder` が解決する前の生の `report_time` 値を渡す（`resolveTime` の正規化で鍵が変わらないようにするため）。

---

### `azaraC::internal::NankaiPageBufferManager`

南海トラフ複数ページメッセージの集約を管理するクラス。

#### コンパイル時設定

| マクロ | デフォルト | 説明 |
|--------|-----------|------|
| `AZARAC_NANKAI_MAX_PAGES` | 63 | 1 電文あたりの最大ページ数（仕様最大 63、6bit） |
| `AZARAC_NANKAI_BUFFERS` | 1 | 同時に追跡可能な南海トラフ数 |

#### メモリ使用量

各バッファはページを`aggregated_text[MAX_PAGES * 18 + 1]`に保管します：
- バッファあたり: メタデータ28B + `MAX_PAGES×18+1` B（既定63ページで1,135B、構造体サイズはアラインメント込み1,168B）
- バッファ: 規定1バッファで約1.17KB。バッファ数を増やすと比例して増加（4バッファ・63ページで約4.7KB）

#### LRU エビクション

全てのバッファが使用中の場合、最も古いバッファが自動的に解放されます。

---

### `azaraC::Message`

デコード済みメッセージを格納する構造体。

#### 共通フィールド

| フィールド | 型 | 説明 |
|-----------|-----|------|
| `svid` | `uint8_t` | 衛星ID。QZSS L1S PRN（`Satellite ID \| 0x80`）。DCR は 183–191、DCX 実データには 181/182 もある |
| `msg_type` | `uint8_t` | メッセージタイプ (43=QZQSM, 44=DCX) |
| `crc24` | `uint32_t` | CRC-24Qチェックサム |
| `valid` | `bool` | メッセージの妥当性フラグ |
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
| `event_time` | `TimeFields` | [25..40] | イベント日時 |

#### 災害カテゴリ

| カテゴリID | 名称 | データ構造 |
|-----------|------|-----------|
| 1 | 緊急地震速報 (EEW) | `EewData eew` |
| 2 | 震源情報 | `HypocenterData hypo` |
| 3 | 震度情報 | `SeismicData seis` |
| 4 | 南海トラフ地震 | `NankaiData nankai` |
| 5 | 津波警報・注意報 | `TsunamiData tsunami` |
| 6 | 北太平洋津波 | `NwPacTsunamiData nw_pac` |
| 8 | 火山情報 | `VolcanoData vol` |
| 9 | 降灰情報 | `AshFallData ash` |
| 10 | 気象警報・注意報 | `WeatherData wx` |
| 11 | 洪水警報 | `FloodData flood` |
| 12 | 台風情報 | `TyphoonData typh` |
| 14 | 海上警報 | `MarineData marine` |

#### EEWデータ (`EewData`)

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
    uint8_t  regions[80];         // 地域別フラグ
    uint8_t  region_count;        // 地域数
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
| `JAlert` | J-Alert | A2=111, A3=0,2,3 |
| `LocalGovernment` | 地方自治体 | A2=111, A3=4-31 |
| `OutsideJapan` | 国外 | A2≠111 |
| `Unknown` | 不明 | 上記以外 |

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
`Mt44CamfRaw` 上には B4 の有無を示す `b4_present` (bool) のみが保持され、個別の D-field 値はシリアライズ時に `decodeB4DetailedInfo(a18, a4, out)` で再計算されます。

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
```

**パラメータ:**
| パラメータ | 型 | 説明 |
|-----------|-----|------|
| `msg` | `const Message&` | シリアライズするメッセージ |
| `out` | `Print&` | 出力先 (Serial, WiFiClient等) |

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

## コンパイル時設定

`#include <azaraC.h>` の前に `#define` で上書きできます。
設定マクロは [`azaraC_config.h`](../src/azaraC_config.h) に一元管理されています。

### 汎用設定

| マクロ | デフォルト | 説明 |
|-------|-----------|------|
| `AZARAC_DEDUP_SLOTS` | 512 | 重複判定表のエントリ数（`AZARAC_DEDUP_WAYS`の倍数、商は2の冪）。1エントリ8B |
| `AZARAC_DEDUP_WAYS` | 8 | 表の連想度（1セットあたりのエントリ数）。大きいほどハッシュ衝突に強い |
| `AZARAC_DEDUP_WINDOW_MS` | 86400000 | 情報有効時間(ms)のフォールバック。災害種別ごとの配信終了条件（`internal/DedupWindow.h`）に無いカテゴリ（MT=44など）だけがこれを使う |

### 言語選択

| マクロ | デフォルト | 説明 |
|-------|-----------|------|
| `AZARAC_LANG_JA` | 1 | 日本語ラベルを有効化 |
| `AZARAC_LANG_EN` | 0 | 英語ラベルを有効化 |

両方 1 のときは日本語を優先し、そのコードに日本語が無ければ英語を使う。
`AZARAC_LANG_JA=0 / AZARAC_LANG_EN=1` では英語ラベルを出力する。
英語表を持たない項目（例: 南海トラフの情報番号）は日本語のままになる。
どちらも 0 のときは原則ラベルを出力しない。欠落時は `null`、定義済みで空文字列のラベルは `""` として出力される。ただし言語非依存表（北西太平洋津波の 3 表など）は値があれば 0/0 でも解決して返す。

英語ラベルは azarashi 0.17.0 以降の定義テーブルに由来する。
`AZARAC_LANG_EN` で有効になるのは `_en` という接尾辞のヘッダで、
対応する日本語表と対で生成される。

逆に**日本語版を持たない英語専用表**（北西太平洋津波の `potential` /
`height` / `region`）は言語非依存で、`AZARAC_LANG_EN` に関係なく常に出力されます。
仕様自体が英語で日本語版が無いためです。同じ扱いの表が CAMF に多数あります
（定義テーブルの `_en` のうち、言語切替の対象になるのは対応する JA 表があるものだけ）。

**両方 1 のときの併記**: `AZARAC_LANG_JA=1` かつ `AZARAC_LANG_EN=1` のとき、
文字列リテラルのキーを持つ `_label` フィールドには `_label_en` が併記される。
`_label` は日本語優先（無ければ英語）、`_label_en` は常に英語。

```json
{ "depth": 60, "depth_label": "60km", "depth_label_en": "60 km" }
```

配列要素のラベル（`notifications[].label` / `regions[].region_label` /
`prefectures[].label` / `cities[].label`）は `_label_en` を持たない。これらは
汎用キーで要素ごとにコード体系が異なるため、`label_en` という固定キー名では
並記しても意味が通らない。要素ごとに言語を選びたい場合は
`AZARAC_LANG_JA=0 / AZARAC_LANG_EN=1` 構成を使う。

数量フィールド（`depth` / `magnitude` / `pressure` / `max_wind` / `max_gust` /
`elapsed` / `number`）にも `_label` / `_label_en` が付く。生のコード値だけでは
意味が取れない値を含む:

| コード | ラベル | 意味 |
|---|---|---|
| `depth` 501 | `500kmより深い` / `Deeper than 500 km` | 範囲の境界 |
| `magnitude` 101 | `10.0より大きい` / `Over 10.0` | 範囲の境界 |
| `magnitude` 126（震源情報のみ） | `不明(8.0より大きい)` / `Unknown (Over 8.0)` | 範囲の境界 |
| `depth` 511 / `magnitude` 127 | `不明` / `Unknown` | センチネル |
| `max_wind` 0 / `max_gust` 0 | `不明` / `Unknown` | センチネル |

センチネルは全フィールド共通ではない。`depth` 0 は `0km`、`pressure` 0 は `0hPa`、
`elapsed` 0 は `0時間後` で、それぞれ実値として意味を持つ。`number` 0 は
`typhoon_number` 表（1 起点）に無いため `number_label` は `null` になる。

`AZARAC_LANG_EN=0`（ライブラリ既定）では `_label_en` は出力されず、
`AZARAC_LANG_JA=0 / AZARAC_LANG_EN=1` でも `_label` 自体が英語になるため併記しない。
`_label_en` が出るのは両言語を 1 にした構成だけ。

### 災害カテゴリ選択

不要なカテゴリの定義テーブルをコンパイル時に除外しFlash使用量を削減できます。
日本語表と英語表は同じデータなので、**カテゴリを無効にすると両方が同時に除外されます**
（`AZARAC_LANG_EN` だけの英語専用表も含む）。

| マクロ | デフォルト | 説明 |
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

### リソース制約・AVR 関連

| マクロ | デフォルト | 説明 |
|-------|-----------|------|
| `AZARAC_FLASH_BUF_SIZE` | 800 | PROGMEMルックアップ用の共有RAMバッファサイズ (バイト)。AVRでは有効カテゴリに応じて 64（SEISMIC/TSUNAMI のみ）/ 80（＋北西太平洋津波）/ 540（＋南海トラフ）/ 800（＋DCX/CAMF）に自動縮小 |

**AVRプリセット**: `__AVR__`では`azaraC_config.h`のプリセットがデフォルトを変更します。有効カテゴリはSEISMIC/TSUNAMIのみ（他11カテゴリは無効）、`AZARAC_DEDUP_SLOTS=64`（`AZARAC_DEDUP_WAYS=8`、512B）、`AZARAC_NANKAI_BUFFERS=1`、`AZARAC_NANKAI_MAX_PAGES=4`となります。`-D`または`#define`（`azaraC.h`インクルード前）で明示することで上書き可能です。

**AVR 標準ライブラリシム**: AVRツールチェーンはlibstdc++を含まないため、`#if defined(__AVR__)`で`src/internal/avr_std/`の最小シム（`optional`/`string_view`/`std::move`等）が自動適用されます。ライブラリの利用方法/API自体は非AVRと同一です。

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
void processMessage(const azaraC::Message& msg) {
    // 基本的な妥当性チェック
    if (!msg.valid) {
        Serial.println(F("[WARN] Invalid message"));
        return;
    }
    
    // SVID範囲チェック（PRN は 181-191: 53/54 -> 181/182 も実データに存在）
    if (msg.svid < 181 || msg.svid > 191) {
        Serial.print(F("[WARN] Unexpected SVID: "));
        Serial.println(msg.svid);
    }
    
    // メッセージタイプ別処理
    if (msg.msg_type == 43) {
        const azaraC::Mt43Data* mt43 = msg.getMt43();
        if (mt43 && mt43->disaster_category == 1) {
            // EEW処理
            handleEEW(*mt43);
        }
    }
}
```

---

## 関連ドキュメント

- [アーキテクチャドキュメント](architecture.md)
- [開発者ガイド](developer-guide.md)
