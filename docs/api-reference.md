# azaraC API リファレンス

対象バージョン: 2.1.0

すべての API は `azaraC` 名前空間にあります。取り込みは `#include <azaraC.h>` です。

並びは使う順番に合わせてあります。`Parser` で受けて `Message` から取り出すのが基本で、南海トラフのページ集約とカスタムフレーマは後ろに置きました。内部の設計は [アーキテクチャ](architecture.md)、JSON の形式は [JSON 出力仕様](json-formats.md) にあります。

- Parser
- Message
- Mt43Data（MT=43）
- Mt44Data（MT=44）
- TimeFields / LatLon
- toJson
- コンパイル時設定
- 南海トラフのページ集約
- カスタムフレーマ

---

## Parser

GNSS モジュールからのバイト列を 1 バイトずつ受けて、デコード済みのメッセージを出すクラスです。

```cpp
// 既定のコンストラクタ（UBX / NMEA を自動判別）
Parser();

// カスタムフレーマを使う場合
explicit Parser(internal::IFramer& framer);
```

コピーとムーブはできません。dedup テーブルや南海トラフのバッファが二重確保になることと、フレーマが呼び出し側の所有であることが理由です。

メモリの目安: 実体は約 5.4 KB（既定構成。dedup 4 KB + 南海トラフ管理部 1.2 KB + フレーマ/デコーダ）で、静的確保を想定しています。AVR preset では約 0.7 KB。`feed()` のスタック使用量は実測で host -Os が最大 808 B、AVR preset が最大 259 B です（JSON 出力は別の経路で host 1,600 B）。

### feed()

```cpp
bool feed(uint8_t byte, Message& out, uint32_t report_unix = 0);
```

| 引数 | 型 | 説明 |
|---|---|---|
| `byte` | `uint8_t` | GNSS モジュールからの 1 バイト |
| `out` | `Message&` | 出力先。読めるのは戻り値が `true` のときだけ |
| `report_unix` | `uint32_t` | 時刻解決に使う報告の UNIX epoch。0 は未解決（DHM フィールドは残りますが `unix_time` は 0 のまま） |

`feed()` は、新しい電文が1つそろったときだけ `true` を返します。それ以外（受信の途中、CRC の誤り、未対応バージョン、コンパイル時に無効なカテゴリ、仕様上未定義のカテゴリ、43/44 以外の MT、重複受信、南海トラフの集約途中）はすべて `false` です。

`false` のとき `out` の中身は不定です。読まないでください。前の電文の値や、復号の途中の値が残っていることがあります。例外は診断用の `unsupported_reason` だけで、復号器が完成したフレームを断ったときに理由が入ります。それ以外の `false` では値は保証されません。

```cpp
azaraC::Parser parser;
azaraC::Message msg;

void loop() {
    while (Serial1.available()) {
        uint8_t byte = Serial1.read();
        uint32_t now = (uint32_t)time(nullptr); // SNTP から取得

        if (parser.feed(byte, msg, now)) {
            // メッセージ受信完了
            processMessage(msg);
        }
    }
}
```

### feed()（一括）

```cpp
bool feed(const uint8_t* data, size_t len, Message& out, uint32_t report_unix = 0);
```

| 引数 | 型 | 説明 |
|---|---|---|
| `data` | `const uint8_t*` | 入力バッファ。`nullptr` は `false` |
| `len` | `size_t` | バイト数。0 は `false` |
| `out` | `Message&` | 出力先。読めるのは戻り値が `true` のときだけ |
| `report_unix` | `uint32_t` | 時刻解決に使う報告の UNIX epoch。0 は未解決 |

受信バッファをそのまま渡す形です。内部では 1 バイト版の `feed()` を順に呼ぶだけで、南海トラフの集約や重複除去を含め、挙動は同じです。
1 通以上成立したら `true` を返し、`out` の中身は 1 バイト版を順に呼んだ場合と同一です。ただし、成立した後に重複などで `false` になった場合は中身がクリアされることがあります。
複数の電文が入っているバッファでは最後に成立した 1 通だけが残るので、取りこぼしたくないときは 1 バイト版を使ってください。

```cpp
uint8_t buf[512];
size_t n = client.read(buf, sizeof(buf));
if (parser.feed(buf, n, msg, now)) {
    azaraC::toJson(msg, Serial);
}
```

### reset()

```cpp
void reset();
```

フレーマ、デコーダ、重複除去フィルタ、南海トラフの集約バッファを初期状態に戻します。

### updateClock()

```cpp
void updateClock();
```

受信が無い間も 64 bit 時計を観測し、epoch guard（世代境界と大きな時計後退）を適用します。
`loop()` から定期的に呼ぶことで、2³² ms（約 49.7 日）以上の無受信期間を跨いでも折り返しを検出でき、古い dedup や南海トラフの履歴による偽の重複抑止を防ぎます。`AZARAC_ENABLE_DEDUP` と `AZARAC_ENABLE_NANKAI` が両方無効な構成では何もしません。
ESP32 の `getMillis()` は 64 bit の `esp_timer` を使うため、この呼び出しは必須ではありません。AVR など 32 bit `millis()` のみの環境では、周期的な観測が無いまま 2³² ms 以上空くと折り返し回数を復元できません。

```cpp
void loop() {
    parser.updateClock();
    while (Serial1.available()) {
        if (parser.feed(Serial1.read(), msg)) { ... }
    }
}
```

---

## Message

デコード済みのメッセージを格納する構造体です。

| フィールド | 型 | 説明 |
|---|---|---|
| `svid` | `uint8_t` | 衛星 ID。QZSS L1S PRN（Satellite ID \| 0x80）。DCR は 183–191、DCX の実データには 181/182 もある |
| `msg_type` | `uint8_t` | メッセージタイプ（43 = DCR、44 = DCX） |
| `crc24` | `uint32_t` | CRC-24Q チェックサム |
| `valid` | `bool` | 妥当性フラグ。`feed()` が `true` を返したときは常に `true` |
| `unsupported_reason` | `UnsupportedReason` | 復号器が完成フレームを断った理由（`None` / `DisabledAtCompileTime` / `UnknownCategory` / `UnsupportedVersion`）。`UnknownCategory` は仕様上未定義のカテゴリと 43/44 以外の MT |
| `payload_type` | `MsgPayloadType` | ペイロードの種別（`Empty` / `Mt43` / `Mt44`） |

ペイロードはアクセサで取り出します。種別が合わなければ `nullptr` です。書き換える場合のために非 const 版もあります。

```cpp
Mt43Data*       getMt43();
const Mt43Data* getMt43() const;
Mt44Data*       getMt44();
const Mt44Data* getMt44() const;
```

`AZARAC_ENABLE_DCX_CAMF=0` のとき `getMt44()` は常に `nullptr` を返します。

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

`clear()` はスカラーを初期値へ戻し、ペイロードを破棄します。

---

## Mt43Data（MT=43 QZQSM）

JMA DC Report メッセージのデータ構造です。

| フィールド | 型 | ビット位置 | 説明 |
|---|---|---|---|
| `report_classification` | `uint8_t` | [14..16] | 報告分類（3 bits） |
| `disaster_category` | `uint8_t` | [17..20] | 災害カテゴリ（4 bits） |
| `information_type` | `uint8_t` | [41..42] | 情報種別（2 bits） |
| `event_time` | `TimeFields` | [21..40] | イベント日時（month [21..24] / day [25..29] / hour [30..34] / min [35..40]） |
| `version` | `uint8_t` | [214..219] | Vn。仕様上の値は 1 で、それ以外は `UnsupportedVersion` として拒否する |

カテゴリごとのペイロードはタグ付き union に入っていて、対応する getter で取得します。`active_type` が一致しなければ `nullptr` です。

`AZARAC_ENABLE_<カテゴリ>` を 0 にすると、そのカテゴリの payload 型（`EewData` など）と getter 自体が存在しなくなります。参照するコードは `#if (AZARAC_ENABLE_<カテゴリ>)` で囲んでください。

| カテゴリ ID | 名称 | アクセサ |
|---|---|---|
| 1 | 緊急地震速報 (EEW) | `getEew()` |
| 2 | 震源情報 | `getHypocenter()` |
| 3 | 震度情報 | `getSeismic()` |
| 4 | 南海トラフ地震 | `getNankai()` |
| 5 | 津波警報・注意報 | `getTsunami()` |
| 6 | 北太平洋津波 | `getNwPac()` |
| 8 | 火山情報 | `getVolcano()` |
| 9 | 降灰情報 | `getAshFall()` |
| 10 | 気象警報・注意報 | `getWeather()` |
| 11 | 洪水警報 | `getFlood()` |
| 12 | 台風情報 | `getTyphoon()` |
| 14 | 海上警報 | `getMarine()` |

繰り返し項目は、どの型も `entries[]` と `count` の組で持ちます。

```cpp
const SeismicData* s = mt43->getSeismic();
if (s) {
    for (uint8_t i = 0; i < s->count; ++i) {
        // s->entries[i] を処理する
    }
}
```

以下、型ごとのフィールドです。型は対応する `AZARAC_ENABLE_*` が 1 のときだけ定義されます。

### EewData（緊急地震速報）

| フィールド | 型 | 説明 |
|---|---|---|
| `long_period_lower` | `uint8_t` | 長周期地震動下限（3 bits） |
| `long_period_upper` | `uint8_t` | 長周期地震動上限（3 bits） |
| `notification[3]` | `uint16_t` | 防災気象情報通知（3 × 9 bits） |
| `notification_count` | `uint8_t` | 通知数 |
| `quake_time` | `TimeFields` | 発震時刻 |
| `depth` | `uint16_t` | 震源の深さ（km、コード値 = km） |
| `magnitude` | `uint8_t` | マグニチュード（×0.1） |
| `epicenter` | `uint16_t` | 震央地名コード |
| `intensity_lower` | `uint8_t` | 震度下限（4 bits） |
| `intensity_upper` | `uint8_t` | 震度上限（4 bits） |
| `region_bitmap[10]` | `uint8_t` | 予報区 80 区のビットマップ（bit i = 予報区 i+1） |

予報区はビットマップのまま保持されているので、アクセサを使います。

- `regionCount()` … 対象予報区数
- `regionAt(i)` … 昇順 i 番目（0 始まり）の予報区コード（1..80）。`i >= regionCount()` は 0
- `addRegion(code)` … 予報区コード（1..80）を対象に追加する。範囲外は無視

### HypocenterData（震源情報）

| フィールド | 型 | 説明 |
|---|---|---|
| `notification[3]` | `uint16_t` | 防災気象情報通知（3 × 9 bits） |
| `notification_count` | `uint8_t` | 通知数 |
| `quake_time` | `TimeFields` | 発震時刻 |
| `depth` | `uint16_t` | 震源の深さ（km、コード値 = km） |
| `magnitude` | `uint8_t` | マグニチュード（×0.1） |
| `epicenter` | `uint16_t` | 震央地名コード |
| `coords` | `LatLon` | 震源位置 |

### SeismicData（震度情報）

| フィールド | 型 | 説明 |
|---|---|---|
| `quake_time` | `TimeFields` | 発震時刻 |
| `entries[16]` | `SeismicEntry` | 震度・地域の組 |
| `count` | `uint8_t` | エントリ数 |

`SeismicEntry` は `intensity_code`（震度コード）と `prefecture_code`（都道府県コード）の組です。

### NankaiData（南海トラフ地震）

| フィールド | 型 | 説明 |
|---|---|---|
| `info_code` | `uint8_t` | 情報コード |
| `text[18]` | `uint8_t` | 本文（1 ページ分、生バイト） |
| `page` | `uint8_t` | このページの番号 |
| `total_page` | `uint8_t` | 総ページ数 |
| `report_month` / `report_day` / `report_hour` / `report_minute` | `uint8_t` | 受信した電文の report_time そのもの。集約キーの軸で、`event_time` と違って時刻解決の正規化を受けない |
| `aggregated_text_ptr` | `const char*` | 集約済み本文へのポインタ（下記の注意を参照） |
| `aggregated_len` | `uint16_t` | 集約済み本文の長さ |
| `is_aggregated` | `bool` | ページ集約が完了したかどうか |
| `truncated` | `bool` | ページ数上限で本文が打ち切られたかどうか |

`aggregated_text_ptr` は Parser 内部のバッファを指すポインタで、所有権はありません。有効なのは `feed()` が `true` を返した直後から、次に `feed()` か `reset()` を呼ぶまでです。内容はバッファの再利用で上書きされます。`Message` をコピーしてもポインタが複製されるだけで、実体は移りません。残したい場合は、その場でコピーするか `toJson()` で出してください。本文はプロトコルの生バイトで、UTF-8 の妥当性は `toJson()` の `text_utf8` 出力でのみ保証されます（不正な並びは U+FFFD に置換）。

```cpp
if (parser.feed(b, msg)) {
    const Mt43Data* m = msg.getMt43();
    const NankaiData* n = m ? m->getNankai() : nullptr;
    if (n && n->is_aggregated) {
        text.assign(n->aggregated_text_ptr, n->aggregated_len);  // ここでコピーする
    }
}
```

集約の仕組み（追い出しやメモリの内訳）は [アーキテクチャ](architecture.md) の「NankaiPageBuffer」を参照してください。`examples/rtos_freertos` は、集約済みの南海トラフだけキューに載せず、そのタスクで JSON 化してから送る実装例です。

### TsunamiData（津波警報・注意報）

| フィールド | 型 | 説明 |
|---|---|---|
| `warning_code` | `uint8_t` | 津波警報コード |
| `entries[5]` | `TsunamiEntry` | 予報区ごとの組 |
| `count` | `uint8_t` | エントリ数 |

`TsunamiEntry` のフィールドは `arrival_time_raw`（到達時刻の生コード、12 bits）、`arrival_time`（解決済みの到達時刻）、`height_code`（津波の高さコード、4 bits）、`region_code`（津波予報区コード、10 bits）です。

### NwPacTsunamiData（北太平洋津波）

| フィールド | 型 | 説明 |
|---|---|---|
| `potential` | `uint8_t` | 津波発生可能性コード |
| `entries[5]` | `NwPacTsunamiEntry` | 地点ごとの組 |
| `count` | `uint8_t` | エントリ数 |

`NwPacTsunamiEntry` のフィールドは `arrival_time_raw`（12 bits）、`arrival_time`、`height_code`（9 bits）、`region_code`（7 bits）です。

### VolcanoData（火山情報）

| フィールド | 型 | 説明 |
|---|---|---|
| `ambiguity` | `uint8_t` | 活動時刻の曖昧さコード |
| `activity_time` | `TimeFields` | 活動時刻 |
| `warning_code` | `uint8_t` | 火山警報コード |
| `volcano_name` | `uint16_t` | 火山名コード |
| `local_govs[5]` | `uint32_t` | 対象の地方公共団体コード |
| `lg_count` | `uint8_t` | 団体コード数 |

### AshFallData（降灰情報）

| フィールド | 型 | 説明 |
|---|---|---|
| `activity_time` | `TimeFields` | 活動時刻 |
| `warning_type` | `uint8_t` | 降灰警報種別 |
| `volcano_name` | `uint16_t` | 火山名コード |
| `entries_time[4]` | `uint8_t` | 降灰予想時刻コード（要素ごと） |
| `entries_code[4]` | `uint8_t` | 降灰量コード（要素ごと） |
| `entries_lg[4]` | `uint32_t` | 対象の地方公共団体コード（要素ごと） |
| `count` | `uint8_t` | エントリ数 |

この型だけは並行配列で持ちます。`entries_time[i]` / `entries_code[i]` / `entries_lg[i]` が同じ対象の組です。

### WeatherData（気象警報・注意報）

| フィールド | 型 | 説明 |
|---|---|---|
| `warning_state` | `uint8_t` | 警報の状態コード |
| `entries[6]` | `WeatherEntry` | 地域ごとの組 |
| `count` | `uint8_t` | エントリ数 |

`WeatherEntry` は `sub_category`（警報サブカテゴリ）と `region_code`（気象予報区コード）の組です。

### FloodData（洪水警報）

| フィールド | 型 | 説明 |
|---|---|---|
| `entries[3]` | `FloodEntry` | 地域ごとの組 |
| `count` | `uint8_t` | エントリ数 |

`FloodEntry` は `warning_level`（洪水警報レベル）と `region_code`（洪水予報区コード）の組です。

### TyphoonData（台風情報）

| フィールド | 型 | 説明 |
|---|---|---|
| `reference_time` | `TimeFields` | 基準時刻 |
| `ref_type` | `uint8_t` | 参照時刻種別（1: Analysis、2: Estimate、3: Forecast） |
| `elapsed` | `uint8_t` | 経過時間（時間） |
| `number` | `uint8_t` | 台風番号 |
| `scale` | `uint8_t` | 大きさ（4 bits） |
| `intensity` | `uint8_t` | 強さ（4 bits） |
| `coords` | `LatLon` | 台風位置 |
| `pressure` | `uint16_t` | 中心気圧（hPa） |
| `max_wind` | `uint8_t` | 最大風速（m/s） |
| `max_gust` | `uint8_t` | 最大瞬間風速（m/s） |

### MarineData（海上警報）

| フィールド | 型 | 説明 |
|---|---|---|
| `entries[8]` | `MarineEntry` | 海域ごとの組 |
| `count` | `uint8_t` | エントリ数 |

`MarineEntry` は `warning_code`（海上警報コード）と `region_code`（海域コード）の組です。

---

## Mt44Data（MT=44 DCX/CAMF）

DCX/CAMF メッセージのデータ構造です。

| フィールド | 型 | 説明 |
|---|---|---|
| `service_kind` | `Mt44ServiceKind` | サービス種別 |
| `is_null_message` | `bool` | Null Message フラグ |
| `sd` | `Mt44Sd` | 送信元情報（`sdmt` 1 bit、`sdm` 9 bits） |
| `camf` | `Mt44CamfRaw` | CAMF フィールド（生コード） |
| `onset_time` | `TimeFields` | ハザード発生日時 |
| `ex_kind` | `ExtendedKind` | 拡張部の種別 |
| `ex` | union | 拡張部。読み方は下記の「拡張部」 |
| `mt44_decoded` | `Mt44Decoded` | デコード済みの派生値。下記の「デコード済み」 |

### サービス種別（Mt44ServiceKind）

| 値 | 名称 | 説明 |
|---|---|---|
| `NullMessage` | Null Message | A1=0、A2=111、A3=0、かつ全 CAMF フィールド（A4–A18）および拡張フィールドがゼロ |
| `LAlert` | L-Alert | A2=111、A3=1 |
| `JAlert` | J-Alert | A2=111、A3=2,3 |
| `LocalGovernment` | 地方自治体 | A2=111、A3=4 |
| `OutsideJapan` | 国外 | A2≠111 |
| `Unknown` | 不明 | 上記以外（A3=0、5–31 を含む） |

### CAMF フィールド（Mt44CamfRaw）

| フィールド | 型 | ビット数 | 説明 |
|---|---|---|---|
| `a1` | `uint8_t` | 2 | メッセージ種別 |
| `a2` | `uint16_t` | 9 | 国/地域コード |
| `a3` | `uint8_t` | 5 | プロバイダ ID |
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

A17（拡張フィールド種別）の値によって、追加のフィールドが有効になります。

| A17 値 | 名称 | 有効になるフィールド |
|---|---|---|
| 00 | B1: 主楕円の高精度化 | `b1_present` |
| 01 | B2: ハザード中心位置 | `b2_present`、`b2_c5`、`b2_c6` |
| 10 | B3: 第2楕円の定義 | `b3_present`、`b3_c7`、`b3_c8`、`b3_c9`、`b3_c10` |
| 11 | B4: 定量・詳細情報（D1–D36） | `b4_present` |

`b*_present` が `false` のとき、対応するフィールドの値は意味を持ちません。デコード済みの楕円や中心位置は `mt44_decoded` 側にあります（B1 の反映もそちら）。

B4（A17=11）の D 系列（D1〜D36）は、`Mt44CamfRaw` には `b4_present` しか残りません。個別の値は JSON 出力のときに再計算されます。

```cpp
if (mt44->camf.b4_present) {
    // D1-D36 の値は azaraC::toJson(msg, out) で自動的に出力される
}
```

### 拡張部

拡張部は union で、`ex_kind` がどの枝が有効かを示します。`ex_kind` が `None` のときは拡張部なしです。有効でない枝の値は未規定なので読まないでください。

| `ex_kind` | 枝 | フィールド |
|---|---|---|
| `LAlertOrLocal` | `ex.ex_lalert_local` | `ex1`（対象地域コード）、`ex2`〜`ex7`、`vn` |
| `JAlert` | `ex.ex_jalert` | `ex8`、`ex9`（都道府県ビットマップ、64 bits）、`ex10`、`vn` |
| `OutsideJapan` | `ex.ex_outside` | `ex11_raw[9]`（生バイト列）、`vn` |

```cpp
if (mt44->ex_kind == azaraC::ExtendedKind::JAlert) {
    uint64_t prefectures = mt44->ex.ex_jalert.ex9;
    // 都道府県ビットマップとして処理する
}
```

### デコード済み（Mt44Decoded）

生コードからは直接読めない派生値だけをまとめた構造体です。楕円の緯度経度や、B2 の中心位置が物理量に変換されて入ります。

| フィールド | 型 | 説明 |
|---|---|---|
| `main_ellipse_present` | `bool` | 主楕円があるかどうか |
| `main_ellipse` | `DecodedEllipse` | 主楕円（B1 の高精度化を反映済み） |
| `jalert_prefecture_mode` | `bool` | J-Alert の対象が都道府県単位かどうか |
| `b2_hazard_lat_microdeg` | `int32_t` | B2 ハザード中心の緯度（microdegrees、×1,000,000） |
| `b2_hazard_lon_microdeg` | `int32_t` | B2 ハザード中心の経度（microdegrees、×1,000,000） |
| `prefecture_positions[47]` | `uint8_t` | 対象都道府県の位置 |
| `prefecture_count` | `uint8_t` | 都道府県数 |
| `city_codes[4]` | `uint16_t` | 対象市町村コード |
| `city_code_count` | `uint8_t` | 市町村コード数 |
| `additional_area` | `DecodedAdditionalArea` | 第2楕円（B3）。`present`、`head_to_area`、`ellipse`（`DecodedEllipseCore`）を持つ |

`DecodedEllipse` は、`DecodedEllipseCore` の共通部に B1 の分を足したものです。

```cpp
struct DecodedEllipse {
    int32_t lat_microdeg;              // 緯度（microdegrees、×1,000,000）
    int32_t lon_microdeg;              // 経度（microdegrees、×1,000,000）
    int32_t semi_major_m;              // 長半径（m、km の ×1,000）
    int32_t semi_minor_m;              // 短半径（m、km の ×1,000）
    int32_t azimuth_decideg;           // 方位角（1e-5 度、×100,000）。名前は歴史的経緯で、3.0.0 で改名を検討
    int32_t b1_lat_offset_microdeg;    // B1 緯度オフセット（microdegrees）
    int32_t b1_lon_offset_microdeg;    // B1 経度オフセット（microdegrees）
    int32_t b1_refined_semi_major_m;   // B1 反映後の長半径（m）
    int32_t b1_refined_semi_minor_m;   // B1 反映後の短半径（m）
};
```

なお `service_kind`、`is_null_message`、B2 中心の有無（`camf.b2_present`）、対象地域コード（`ex.ex_lalert_local.ex1`）は `Mt44Data` / `Mt44CamfRaw` 側の値そのものなので、`Mt44Decoded` には複製されていません。

---

## TimeFields / LatLon

日時を表す構造体です。

```cpp
struct TimeFields {
    uint8_t  month;      // 月（1-12、0 = 未解決）
    uint8_t  day;        // 日（1-31、0 = 未解決）
    uint8_t  hour;       // 時（0-23）
    uint8_t  minute;     // 分（0-59）
    uint32_t unix_time;  // UNIX 時刻（0 = 未解決）
};
```

緯度経度を度分秒で表す構造体です。

```cpp
struct LatLon {
    uint8_t  lat_ns;    // 北緯/南緯（0 = N、1 = S）
    uint8_t  lat_deg;   // 緯度（度、0-89）
    uint8_t  lat_min;   // 緯度（分、0-59）
    uint8_t  lat_sec;   // 緯度（秒、0-59）
    uint8_t  lon_ew;    // 東経/西経（0 = E、1 = W）
    uint16_t lon_deg;   // 経度（度、0-179）
    uint8_t  lon_min;   // 経度（分、0-59）
    uint8_t  lon_sec;   // 経度（秒、0-59）
};
```

---

## toJson

```cpp
void toJson(const Message& msg, Print& out);
size_t toJson(const Message& msg, char* buf, size_t len);
```

`Message` を JSON 形式で `out`（Serial、WiFiClient 等）へ書き出します。JSON の形式そのものは [JSON 出力仕様](json-formats.md) を参照してください。

バッファ版は `Print` を持たない呼び出し側（`String`、固定バッファ、独自の送信キュー）向けです。
`len > 0` なら必ず NUL 終端し、入り切らない分は捨てます。バッファの外へは書きません。
戻り値は書き込んだバイト数（NUL を除く）で、`buf[戻り値] == '\0'` が成り立ちます。
必要な長さは事前には分からないため、完全な JSON が要る場合は十分な `len` を渡すか `Print` 版を使ってください。

```cpp
char json[512];
size_t n = azaraC::toJson(msg, json, sizeof(json));   // n == strlen(json)
```

スレッド安全性: ラベル用の共有バッファ（`AZARAC_FLASH_BUF_SIZE` の 1 本）を使うため、`toJson()` と定義テーブルの lookup を複数のタスク/スレッドから同時に呼ばないでください。FreeRTOS では呼び出し側で排他します（`examples/rtos_freertos` の `printJson()` を参照）。

```cpp
azaraC::toJson(msg, Serial);
Serial.println();
```

---

### crc24q()

CRC-24Q（IS-QZSS-L1S-009 §4.1.1.3）を計算します。受信経路が使うのと同じ実装です。

```cpp
uint32_t crc24q(const uint8_t* data, uint16_t bit_len);
```

`data[0]` の MSB から `bit_len` ビットを処理し、24 bit の CRC を返します。
受信した `Message` の `crc24` は `Decoder` が入れた値なので通常は不要ですが、自前の電文生成（テスト送信器、リピータ）や、外部で組み立てた 250 bit フレームの検証に使えます。

```cpp
uint8_t bits[32] = {};
// ... 0..225 bit を組み立てる ...
uint32_t crc = azaraC::crc24q(bits, 226);
setBits(bits, 226, 24, crc);   // 226..249 bit に CRC を置く
```

---

## コンパイル時設定

設定マクロの一覧は、この節の表が正です。指定はビルドフラグ（`-DAZARAC_...=...`、PlatformIO の `build_flags`、arduino-cli の `--build-property compiler.cpp.extra_flags=...`）で渡します。
スケッチ冒頭の `#define` はライブラリ側（別 TU）で認識されず、`Parser` などのサイズが TU 間でずれるため使えません。
定義は [`azaraC_config.h`](https://github.com/A-vrice/azaraC/tree/main/src/azaraC_config.h) にあります。

### 汎用

| マクロ | 既定 | 説明 |
|---|---|---|
| `AZARAC_DEDUP_SLOTS` | 512 | 重複判定表のエントリ数（`AZARAC_DEDUP_WAYS` の倍数、商は 2 の冪）。1 エントリ 8 B |
| `AZARAC_DEDUP_WAYS` | 8 | 表の連想度（1 セットあたりのエントリ数）。大きいほどハッシュ衝突に強い |
| `AZARAC_DEDUP_WINDOW_MS` | 86400000 | 情報有効時間（ms）のフォールバック。カテゴリ別の配信終了条件（MT=43）と MT=44 の A8 由来の窓に無いカテゴリだけが使う |
| `AZARAC_ENABLE_DEDUP` | 1 | 0 で重複排除を無効化。`DedupFilter` が状態を持たず常に「新規」を返し、`Parser` から `AZARAC_DEDUP_SLOTS × 8 B`（既定 4 KB / AVR 512 B）が消える。同一情報の再放送もすべて受け取りたいロガー・冗長系・検証機向け。ただし南海トラフのページビットマップによる同一ページの抑制は残る |

### 言語選択

| マクロ | 既定 | 説明 |
|---|---|---|
| `AZARAC_LANG_JA` | 1 | 日本語ラベルを有効化 |
| `AZARAC_LANG_EN` | 0 | 英語ラベルを有効化 |

両方 1 のときは日本語を優先し、日本語の表が無い項目だけ英語になります。ラベルが JSON にどう出るか（`_label_en` の併記、欠けたときの `null`、センチネルの扱い）は [JSON 出力仕様](json-formats.md) の「ラベルの言語選択」を参照してください。

### 災害カテゴリ選択

不要なカテゴリは、定義テーブルごとコンパイル対象から外して Flash 使用量を減らせます。日本語表と英語表は、そのカテゴリを無効にすると両方とも除外されます（`AZARAC_LANG_EN` だけの英語専用表も含む）。

| マクロ | 既定 | 説明（カテゴリ） |
|---|---|---|
| `AZARAC_ENABLE_EEW` | 1 | 緊急地震速報（カテゴリ 1） |
| `AZARAC_ENABLE_HYPOCENTER` | 1 | 震源情報（カテゴリ 2） |
| `AZARAC_ENABLE_SEISMIC` | 1 | 震度情報（カテゴリ 3） |
| `AZARAC_ENABLE_NANKAI` | 1 | 南海トラフ地震（カテゴリ 4） |
| `AZARAC_ENABLE_TSUNAMI` | 1 | 津波警報（カテゴリ 5） |
| `AZARAC_ENABLE_NW_PAC_TSUNAMI` | 1 | 北太平洋津波（カテゴリ 6） |
| `AZARAC_ENABLE_VOLCANO` | 1 | 火山情報（カテゴリ 8） |
| `AZARAC_ENABLE_ASH_FALL` | 1 | 降灰情報（カテゴリ 9） |
| `AZARAC_ENABLE_WEATHER` | 1 | 気象警報（カテゴリ 10） |
| `AZARAC_ENABLE_FLOOD` | 1 | 洪水警報（カテゴリ 11） |
| `AZARAC_ENABLE_TYPHOON` | 1 | 台風情報（カテゴリ 12） |
| `AZARAC_ENABLE_MARINE` | 1 | 海上警報（カテゴリ 14） |
| `AZARAC_ENABLE_DCX_CAMF` | 1 | DCX/CAMF 全般（MT=44） |

DCR のカテゴリマクロ（12 個）を 0 にすると、定義テーブルだけでなく payload 型そのもの（`EewData` / `SeismicData` / `TsunamiData` など全 12 型）と対応する getter もコンパイル対象から外れます。`Mt43Data` のペイロード枠（`storage_size_`）は、残ったカテゴリのうち最大の `sizeof` まで小さくなります。
`AZARAC_ENABLE_DCX_CAMF=0` は別扱いで、`Mt44Data` 型と `getMt44()` は残り、`getMt44()` は常に `nullptr` を返します（型ガードではなく実行時無効化）。
無効にしたカテゴリの型を扱うコードはコンパイルエラーになるので、構成の違うビルドでコードを使い回す場合は `#if (AZARAC_ENABLE_EEW)` などで囲んでください（`examples/filter_by_category`、`examples/with_sntp` の EEW ブロックを参照）。

### リソース制約・AVR 関連

| マクロ | 既定 | 説明 |
|---|---|---|
| `AZARAC_NANKAI_MAX_PAGES` | 63（AVR: 4） | 南海トラフ 1 電文あたりの最大ページ数（仕様上の最大も 63） |
| `AZARAC_NANKAI_BUFFERS` | 2（AVR: 1） | 同時に追跡できる南海トラフ事象の数。訓練（Rc=7）と実警報（Rc=2）の同時進行に 2 必要 |
| `AZARAC_FLASH_BUF_SIZE` | AVR: カテゴリ連鎖（既定 64）/ 非 AVR: 800 | ラベル引き当て用の共有 RAM バッファ（バイト）。AVR では有効カテゴリに応じて 64 / 80 / 96 / 540 / 640 / 800 に自動選択され、有効なカテゴリの最長ラベルを必ず収める（`make -C test bench` の `FLASH_BUF_OK` ゲート）。64 未満は `static_assert` で拒否。非 AVR でも分割ラベルの連結と長さ取得に使う。切り詰め位置が UTF-8 の途中なら、不完全な末尾を捨てて境界まで戻す |
| `AZARAC_DEDUP_MT44_MAX_WINDOW_MS` | 300000 | MT=44 の情報有効時間（ms）の上限。`__AVR__` のみ定義され、常に A8 由来の窓（最短 6 時間）を置き換える。ホストは上限を設けず A8 の窓をそのまま使う |
| `AZARAC_NMEA_STRICT_SVID` | 0 | `$QZQSM` の Satellite ID 検証。0 = 00–63 を受理（実機互換）/ 1 = 53–63（PRN 181–191）/ 2 = 仕様表の 55/56/57/58/61 のみ。0–2 以外はその場で `#error` |
| `AZARAC_NMEA_REJECT_NONZERO_PADDING` | 0 | 1 でフレーム bit 250–255（仕様上 `00`）が非 0 の NMEA 電文を拒否する。既定はマスクして受理（CRC 被覆域の外なので、警報を落とさない方を優先） |
| `AZARAC_KEY_BUF_SIZE` | 36 | AVR で JSON のキーと固定値リテラルを Flash から書き出すときの、スタック上の一時バッファのバイト数。最長はキーの 35 B で、収まらないリテラルは `JsonKey` の生成時に `static_assert` でコンパイルエラーになる。非 AVR では使われない |

AVR プリセット: `__AVR__` では `azaraC_config.h` のプリセットが効き、有効カテゴリはボードによらず SEISMIC/TSUNAMI のみになります。他の 10 カテゴリは大容量ボードでも既定は無効です（全部有効にすると、256 KB のボードでもユーザーのコードを置く余地がほぼ残りません）。DCX/CAMF はオプトインで、`AZARAC_AVR_LARGE_FLASH=1` または `AZARAC_ENABLE_DCX_CAMF=1` で有効になります。プリセットの値とメモリ要件は [アーキテクチャ](architecture.md#メモリ設計) を参照してください。
AVR ツールチェーンは libstdc++ を含まないため、`src/internal/avr_std/` の最小シムが自動で適用され、API は他のアーキテクチャと揃います。64 KiB を超える Flash を持つ AVR での PROGMEM の扱いは [開発者ガイド](developer-guide.md) の「AVR 開発」を参照してください。

---

## 南海トラフのページ集約

### getNankaiBuffer()

```cpp
const internal::NankaiPageBuffer* getNankaiBuffer(const internal::NankaiPageKey& key) const;
```

受信途中のものも含め、キーに合う集約バッファを返します。そろったかどうかは、返ってきたバッファの `isComplete()` で見ます。ポインタは次の `feed()` か `reset()` まで有効です。`AZARAC_ENABLE_NANKAI=0` のときはこのメソッド自体がありません。

キーは `NankaiPageKey{info_code, month, day, hour, minute, information_type, report_classification}` の順で作ります。末尾の 2 つは省略できますが、省略すると `report_classification = 0` になって、実際のバッファ（実警報は 2、訓練・試験は 7）には一致しません。受信した電文の Rc をそのまま渡してください。`information_type`（発表 = 0 / 取消 = 2）と `report_classification` をキーに含めるのは、同一 `info_code` + 報告時刻の発表と取消、訓練と実警報を別事象として扱うためです。

時刻は `report_time` の値をそのまま使います。正規化した時刻を渡すと、キーがずれて見つからなくなります。

追い出しポリシーやメモリ使用量といった管理側の話は [アーキテクチャ](architecture.md) の「NankaiPageBuffer」を参照してください。

---

## カスタムフレーマ

組み込みのフレーマが対応していない受信機の形式は、フレーマを差し替えて扱えます。コンストラクタで渡したフレーマは呼び出し側の所有で、`Parser` は参照だけを持ちます。

```cpp
class IFramer {
public:
    virtual bool feed(uint8_t byte, Frame& out) = 0;
    virtual void reset() = 0;
    virtual ~IFramer() = default;
};
```

`Frame` は 250 bit のフレーム本体（`bits[32]`、MSB-first。末尾 6 bit は詰め物）と `svid` を持ちます。`svid` は L1S の PRN（181–191）に寄せた値を入れてください。

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

## 関連ドキュメント

- [はじめに](getting-started.md)
- [アーキテクチャ](architecture.md)
- [開発者ガイド](developer-guide.md)
- [JSON 出力仕様](json-formats.md)
