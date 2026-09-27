# JSON 出力仕様の対照表 — azaraC と azarashi

azaraC の `JsonSerializer`（C++ / `Print&`）と azarashi 0.17.0 の `to_json_dict()`（Python）が
出力する JSON を並べて整理する。両者は用途が違う — azaraC は組込みで `Serial` に流す前提、
azarashi は PC での記録・機械処理の前提 — ため、優劣ではなく **どこで情報が落ちるか** を軸にまとめる。

数値はすべて実測。同一の 6 電文（EEW / Tsunami ×2 / Volcano / Typhoon / J-Alert）を
`test/decode_to_json.exe`（`-DAZARAC_LANG_JA=1 -DAZARAC_LANG_EN=1`）と
`azarashi 0.17.0` に通した結果を比較した。

---

## 0. azaraC 側のスキーマ（現状）

リポジトリ内の全テスト電文 236 通（MT43 23 通 / MT44 133 通がデコード成功）を通して
実測した、azaraC が実際に出す構造。§1 以降はこの形を azarashi と突き合わせたもの。

### 0.1 共通の枠

| キー | 型 | 備考 |
|---|---|---|
| `svid` | int | QZSS L1S PRN。`NmeaFramer` は Satellite ID を `\| 0x80` で正規化（53→181, 54→182, 55–63→183–191）、`UbxFramer` は `svid_prn` 表で変換 |
| `svid_label` | str | `svid` の 6 LSB で引いた PRN（`"PRN184"`）。表に無い値は `""` |
| `msg_type` | int | 43 / 44 |
| `msg_type_label` | str | `"DCR"` / `"DCX"` |
| `version` | int | MT43 のみ。DCR の `Vn`（6bit）。仕様は 1 を要求し、`decodeQzqsm` が 1 以外を拒否するため常に 1 |
| `crc24` | str | `"0x00F92C3F"`。azarashi には無い |

**MT43** は更に `report_classification` / `disaster_category` / `information_type` と各 `_label`、
`version`（`Vn`、常に 1）、`report_time{month,day,hour,min,unix}`、`detail{...}` を持つ。
**MT44** は共通部が無く、A フィールド（`a1_msg_type` 〜 `a18_specific_settings`）を最上位に展開する。

### 0.2 MT43 の `detail`（カテゴリ別・実測）

| cat | ラベル | `detail` のキー |
|---|---|---|
| 1 | 緊急地震速報 | `long_period_lower/upper`(+`_label`), `notifications[]{code,label}`, `quake_time`, `depth`(+`_label`), `magnitude`(+`_label`), `epicenter`(+`_label`), `intensity_lower/upper`(+`_label`), `regions[]{code,label}` |
| 2 | 震源 | `coords{lat_deg,lat_min,lat_sec,lat_ns,lon_deg,lon_min,lon_sec,lon_ew}`, `depth`(+`_label`), `magnitude`(+`_label`), `epicenter`(+`_label`), `notifications[]`, `quake_time` |
| 3 | 震度 | `entries[]{prefecture(+_label),intensity(+_label)}`, `quake_time` |
| 4 | 南海トラフ地震 | `info_code`(+`_label`), `page`, `total_page`, `truncated`, `text_utf8` |
| 5 | 津波 | `warning_code`(+`_label`), `entries[]{region(+_label),height(+_label),arrival_day_offset,arrival_hour,arrival_min,arrival_time_raw,arrival_time}` |
| 6 | 北西太平洋津波 | `potential`(+`_label`), `entries[]{region(+_label),height(+_label),arrival_day_offset,arrival_hour,arrival_min,arrival_time_raw,arrival_time}` |
| 8 | 火山 | `ambiguity`(+`_label`), `activity_time`, `warning_code`(+`_label`), `volcano_name`(+`_label`), `local_govs[]{code,label}` |
| 9 | 降灰 | `activity_time`, `warning_type`(+`_label`), `volcano_name`(+`_label`), `entries[]{arrival_hour,local_gov(+_label),warning_code(+_label)}` |
| 10 | 気象 | `warning_state`(+`_label`), `entries[]{region(+_label),sub_category(+_label)}` |
| 11 | 洪水 | `entries[]{region(+_label),warning_level(+_label)}` |
| 12 | 台風 | `coords`, `elapsed`(+`_label`), `intensity`(+`_label`), `max_gust`(+`_label`), `max_wind`(+`_label`), `number`(+`_label`), `pressure`(+`_label`), `ref_type`(+`_label`), `reference_time`, `scale`(+`_label`) |
| 14 | 海上 | `entries[]{region(+_label),warning_code(+_label)}` |

### 0.3 MT44 のキー（実測 68 種）

A フィールドは `a1_msg_type`, `a2_country`(+`_label`), `a3_provider`(+`_label`), `a4_hazard` /
`a4_hazard_category` / `a4_hazard_type` / `a4_hazard_definition`, `a5_severity`(+`_label`),
`a6_onset_week`(+`_label`), `a7_onset_minute`, `a8_duration`(+`_label`),
`a9_type_of_library`(+`_label`), `a10_library_version`(+`_label`), `a11_guidance`(+`_label`),
`a17_type_of_specific_settings`(+`_label`), `a18_specific_settings`。

条件付きブロック（該当時のみ出現）:

| ブロック | 契機 | キー |
|---|---|---|
| `main_ellipse` | A12–A16 あり | `lat_deg`, `lon_deg`, `semi_major_km`, `semi_minor_km`, `azimuth_deg` |
| `main_ellipse.b1_refinement` | B1 | `c1_lat_offset_deg`, `c2_lon_offset_deg`, `c3_refined_semi_major_km`, `c4_refined_semi_minor_km` |
| `hazard_center` | B2 | `c5_raw`, `c6_raw`, `delta_lat_deg`, `delta_lon_deg` |
| `secondary_ellipse` | B3 | `c7_shift`, `c8_homothetic`, `c9_bearing`, `c10_guidance`(+`_label`), `c10_guidance_code` |
| `detailed_info` | B4 | `a4_code` と、a4 に応じた D フィールド（後述） |
| `jalert_target` | J-Alert | `prefecture_mode`, `prefecture_positions[]`, `prefecture_labels[]` |
| `ex1_target_area`(+`_label`), `target_area_code`, `ex_vn` | L-Alert | — |
| `alert_identity{a2,a3,a4,ex1}`, `sd_sdmt`, `sd_sdm` | 常時（MT44） | — |

### 0.4 D フィールドの形 — 既に `{"raw","label"}` の 2 キー

B4（A17=11）の D1–D36 は **`{"raw": 生値, "label": 表示文字列}`** として出る。

```json
"detailed_info": {
  "a4_code": 36,
  "d1_magnitude":     {"raw": 6, "label": "7.0-7.9 - Major"},
  "d2_seismic_coeff": {"raw": 7, "label": "7"},
  "d3_azimuth":       {"raw": 5,  "label": "112.5"},
  "d4_vector_length": {"raw": 9,  "label": "30"},
  "d5_wave_height":   {"raw": 6,  "label": "5.0m < H ≤ 10.0m"}
}
```

`d5_wave_height` のラベルが `5.0m < H ≤ 10.0m` である点が重要 — **範囲の情報は
いまラベル文字列の中にしか無い**（§3 の話が D フィールドにも及ぶ）。`raw` は残るので
生値は失われていない。

D フィールドは `a4_code`（ハザード種別）に応じて「どの D が意味を持つか」が決まり、
該当しないものは**キーごと出ない**（`a4=1` なら `a4_code` だけ）。欠落と `raw:0` は
別物として扱われる。

`d1_magnitude` は raw が 4bit（0–15）だが表は 0–8 しか持たない。表外の raw（例 15）は
`label: ""` になる。azarashi は同コードを `recognized: false` として区別する。

### 0.5 出現しないもの

- D フィールドは**テスト電文では一度も出ない**（全 133 通が A17=0）。合成テスト
  （`test/json/test_json_dcx_b1b4.cpp`）でのみ検証されている
- `text`/`text_en`（南海トラフ以外）、`received_at`、`test`、`scheme`、`nmea` は出さない

---

## 1. 封筒（レコード最上位）

| 概念 | azarashi 0.17 | azaraC | 差 |
|---|---|---|---|
| 形式版 | `schema_version: 1` | なし | azaraC は版を持たない |
| 種別 | `type: "qzss.dcr.tsunami"` | `msg_type: 43` + `msg_type_label` + `disaster_category` | azaraC は数値の組合せ |
| 訓練/試験 | `test: true` | なし | azaraC は `report_classification == 7` を利用者が解釈 |
| 受信時刻 | `received_at: "...Z"` | なし（`report_time.unix` は **常に 0**） | azaraC は受信時刻を運ばない |
| 衛星 | `satellite: {system, prn}` \| `null` | `svid` + `svid_label`（`"PRN184"` 等） | azaraC は `satellite_id` と PRN の両方を 1 つの数値で運ぶ |
| 元電文 | `nmea` | なし | azaraC は再生成しない |
| 本文 | `text`, `text_en` | 南海トラフの `text_utf8` のみ | azaraC は他カテゴリで本文を生成しない |
| ペイロード | `data`（種別ごと） | 最上位に `detail` 等（種別ごと） | 入れ子の深さが違う |
| 検査値 | なし | `crc24: "0x00BACDBD"` | azaraC のみ |

azaraC の共通部（MT43）は `report_classification` / `disaster_category` / `information_type` と
それぞれの `_label`、`report_time{month,day,hour,min,unix}`、`detail{}`。
MT44 は共通部が無く A フィールドを最上位に展開する。

---

## 2. コード値の表し方

**azarashi** — 4 項目を必須とするオブジェクト。

```json
{"scheme": "qzss.dcr.tsunami_forecast_region", "code": "610",
 "recognized": true, "labels": {"ja": "高知県", "en": "Kochi Prefecture"}}
```

- `scheme` がコード体系を一意に決める（`camf.a5_severity`, `qzss.dcr.*`, `camf.provider.country_111` …）
- `code` は十進文字列。大整数コード（Flood の 12 桁等）も落ちない
- `recognized: false` = コード表に定義が無い。`labels` は `{}` で、**コード番号そのものは保持**
- 表示文字列が無い定義済みコードは `labels: {}`。「未定義」と区別できる
- `ja`/`en` は併記される（両方ある場合）

**azaraC** — 数値とラベルの並置。

```json
{"region": 610, "region_label": "高知県"}
```

- キー名が `region` なので体系は文脈依存（`scheme` に相当する情報はキー名とカテゴリだけ）
- 値は数値。Flood のような 12 桁コードは `uint64_t` で数値のまま
- ラベルは `_label` サフィックスのキー、値は **文字列 1 本**（言語はビルド時に決定）
- `AZARAC_LANG_JA=1` かつ `AZARAC_LANG_EN=1` のときは `_label_en`（英語）も併記される
- 未定義コードは `""`、定義済みの空ラベルも `""` → **区別できない**

### 実測した差

| 状況 | azarashi | azaraC |
|---|---|---|
| 未定義コード | `recognized:false`, `labels:{}`, `code` 保持 | `"_label": ""`, 元コードは数値キーに残る |
| 定義済み・表示なし | `labels: {}` | `"_label": ""` |
| 例: A11 code 0 | `labels: {"en": "No instruction"}` | `a11_guidance_label: ""` |
| 例: provider code 0（Fiji） | `recognized:false`, `labels:{}` | `a3_provider_label: ""` |

上の 2 例は azaraC 側で**同じ `""` になる**。「指示なし」と「未知の提供者」を利用者が区別できない。

---

## 3. 数量（数値＋単位）

**azarashi** — `kind` で形を決める。

| `kind` | 内容 | 例 |
|---|---|---|
| `scalar` | `value`, `unit` | `{"kind":"scalar","value":10,"unit":"km", ...}` |
| `bounds` | `lower`/`upper`（各 `{value,inclusive}`） | 津波の高さ `3m` = 1m 超〜3m 以下 |
| `category` | コードのみ（数値境界なし） | 北西太平洋津波の高さ区分 |
| `missing` | `reason` (`unknown`/`no_information`/`unrecognized_code`) | 深さ 511 |

**azaraC** — `kind` も `unit` も無く、数値を素で置く。ただし数量フィールドには
`_label` が付き、境界（`500kmより深い`）とセンチネル（`不明`）は可視化される。

| 電文 | フィールド | azarashi | azaraC | 落ちるもの |
|---|---|---|---|---|
| EEW | `depth` | `scalar 10, unit km` | `"depth": 10` + `depth_label: "10km"` | 単位（機械可読） |
| EEW | `magnitude` | `scalar 7.2, unit null` | `"magnitude": 72` + `magnitude_label: "7.2"` | **実数化**（生コード 72 = 7.2） |
| Tsunami | `height` | `bounds 1<x≤3, unit m` | `"height": 3` + `height_label: "3m"` | 単位・範囲 |
| Typhoon | `central_pressure` | `scalar 955, unit hPa` | `"pressure": 955` + `pressure_label: "955hPa"` | 単位（機械可読） |
| Typhoon | `maximum_wind_speed` | `scalar 40, unit m/s` | `"max_wind": 40` + `max_wind_label: "40m/s"` | 単位（機械可読） |
| Typhoon | `elapsed_time` | `scalar 0, unit h` | `"elapsed": 0` + `elapsed_label: "0時間後"` | 単位（機械可読） |

`_label` / `_label_en` により単位とセンチネルは**人間には読める**が、
値自体は依然として生コードのままなので **機械可読な単位・境界型は持たない**。

津波の高さは特に注意が必要。仕様の `3m` は「1m 超〜3m 以下」という *範囲* であり、
単一値ではない。azarashi は `bounds` でこれを保持し、azaraC はコード `3` とラベル `"3m"` だけを持つ。

---

## 4. 時刻

**azarashi** — `status` / `value` / `basis` の 3 項目。

| `status` | 意味 | 電文例 |
|---|---|---|
| `time` | UTC 日時。`basis` が `received_at` か `report_time` か | 通常 |
| `arrival_estimated` | 国内津波の「津波到達中と推測」（Ta = hour 31, min 63） | 実データに存在 |
| `arrived_or_unknown` | 北西太平洋津波の「到達済みまたは不明」 | — |
| `no_information` | 国内津波の「該当情報なし」（Ta = day 0, hour 30, min 62） | DCR-017 で新設 |
| `not_used` | DCX の時刻フィールドが未使用 | A7 = 0 |
| `unrecognized_code` | 日時に変換不能。`source` に生の日・時・分 | hour 25 等 |

`basis` は「年・月・日を補うのに何を基準にしたか」を示す。利用者が再現できる。

**azaraC** — `{month, day, hour, min, unix}` の 5 項目。

`resolveArrivalTime()`（`src/decoder/Decoder.cpp`）は

```cpp
if (hour > 23 || min > 59) return t;   // 全ゼロ
```

とするため、**`31:63`（到達中）と `30:62`（情報なし）と `25:00`（不正）がすべて同じ全ゼロに潰れる**。
azaraC の出力は `{"month":0,"day":0,"hour":0,"min":0,"unix":0}` で、3 者を区別できない。

実測（`$QZQSM,56,53ADA8BECF...`、Ta = 2047 = hour 31, min 63）:

```
azarashi:  "arrival": {"status": "arrival_estimated", "value": null, "basis": null}
azaraC  :  "arrival_hour": 31, "arrival_min": 63, "arrival_time_raw": 2047,
           "arrival_time": {"month":0,"day":0,"hour":0,"min":0,"unix":0}
```

azaraC は幸い `arrival_time_raw` と分解フィールド（`arrival_hour`/`arrival_min`）を残すので
情報自体は失われていないが、`arrival_time` を見た利用者は「時刻不明」と誤読する。

その他の時刻の差:

| 項目 | azarashi | azaraC |
|---|---|---|
| `report_time` | `status:time`, `basis:received_at` | `unix` は **常に 0**（CLI が timestamp を渡さないため） |
| DCX `onset` | 週 + 週内分から解決。`basis: received_at` | **133/133 で全ゼロ**（同じ理由） |
| 火山の曖昧さ | `activity_time_ambiguity`（コードオブジェクト）を必須で併記し、`Du` に応じて `activity_time` の有効範囲を解釈 | `ambiguity` + `ambiguity_label`（`Du` の 0–7 を明示）。`activity_time` の有効範囲は解釈しない |

`unix: 0` は「未解決」の意味だが、スキーマ上は正当な値（1970-01-01）でもある。
azarashi は `status` で明示するのでこの曖昧さが無い。

---

## 5. 繰り返し項目の組み方

**azarashi** — 1 件 1 オブジェクト。並列配列を作らない。

```json
"forecasts": [
  {"region": {...}, "height": {...}, "arrival": {...}}
]
```

**azaraC** — 種別により 2 通り。

```json
"entries": [{"arrival_*": …, "height": 3, "region": 600, "region_label": "…"}]
"jalert_target": {"prefecture_mode": 1,
                  "prefecture_positions": [1,2,3,…],
                  "prefecture_labels": ["北海道","青森県",…]}
```

J-Alert の都道府県は **並列配列**。`prefecture_positions[i]` と `prefecture_labels[i]` の
対応を利用者が保つ必要がある。azarashi は `target_regions` のオブジェクト配列で、
`qzss.dcx.prefecture_bit` の code を **下位から 0 始まりのビット位置**として持つ
（azaraC は 1 始まりの位置を出す — 実測で `[1,2,3,…]`）。

EX9 の元 64 ビット整数は azarashi は出さない（`nmea` に残る）。azaraC は
`prefecture_positions` に展開する。

---

## 6. 実装上の問題（比較で判明したもの）

### 6.1 `svid_label` が常に空（修正済み）

`src/json/JsonSerializer.cpp` は `qzss_dcr_satellite_prn_lookup(msg.svid)` を呼んでいたが、
この表のキーは `55,56,57,58,61`。一方 `NmeaFramer` は svid 55–63 を `+128` して
`183–191` に、`UbxFramer` は svid_prn マップで `183–189` を返すため**必ず引き外れていた。**

IS-QZSS-DCR-017 §4.3.1 は「Satellite ID is 6 LSB of the 8 bit which represented PRN of the
L1S」と定めており、表のキーはまさにその 6 LSB。`msg.svid & 0x3F` を引くよう修正した。

実測（236 電文）: 修正前 0/156 解決 → 修正後 **95/156 解決**（`PRN183`–`PRN189`）。
残り 61 件は svid 53/54（DCX ベクタ）で、表が覆う `{55,56,57,58,61}` の外にあるため
空文字列が正しい。

#### `svid` の正規化（修正済み）

`svid_label` の空とは別に、`svid` の値自体が azarashi と食い違っていた。

| 入力フィールド | 修正前 azaraC | 修正後 azaraC | azarashi `satellite_id` / `satellite_prn` |
|---|---|---|---|
| 55–63 | 183–191（`+128`） | 183–191（`\| 0x80`） | 55–63 / 183–191 |
| 53 | **53**（変換せず） | **181** | 53 / **181** |
| 54 | **54** | **182** | 54 / **182** |

`Frame::svid` の契約は **PRN**（`docs/api-reference.md` の「衛星ID (QZSS L1S PRN: 183-191)」、
DCR-017 §4.3.1 と DCX-004 の双方が「PRN を表す 8bit の**下位 6bit**」と規定）。
azarashi も `nmea.py:78` / `net.py:33` で**全 ID に `| 0x80`** を適用する。

旧 `NmeaFramer` は `55 <= svid <= 63` のときだけ `+128` し、それ以外は入力をそのまま
通していたため、実データに 61 通ある 53/54（PRN181/182）が生 ID のまま `svid` に出ていた。
`svid | 0x80` に統一した（`55–63` では `+128` と同一、128 以上は恒等なので二重変換しない）。
`test/data/dcx_vectors.json` の期待値 `(53, 181)` / `(54, 182)` と一致するようになった。

なお PRN181/182 に対応するラベルは azarashi の表にも無い（表は 55/56/57/58/61 のみ）ため、
`svid_label` は空のままで正しい。

### 6.2 未定義コードと定義済み空ラベルの混同

§2 のとおり。azarashi は `recognized` で分ける。

### 6.3 数量の単位・実数化の欠落

§3 のとおり。特に `magnitude: 72`（実値 7.2）は利用者を誤らせる。

### 6.4 `version` を捨てている（修正済み）

DCR の 6 ビット `Vn`（必須値 1）は `DecoderQzqsm` が検証するが `Mt43Data` に保持されず、
どこにも出力されなかった。`Mt43Data::version` に保持し、**MT43 の共通枠**（`detail{}` の外、
`report_classification` 等と同じ階層）に `"version"` として出す。

`decodeQzqsm` は `Vn != 1` を `UnsupportedVersion` として拒否するため、デコード成功時に
この値は**常に 1** になる。それでも出すのは、「フィールドが存在しない」と
「Vn=1 を読んだ」を利用者が区別できるようにするため。

### 6.5 受信時刻を運ばない

`report_time.unix` と DCX `onset_time` が 0 になるのは、CLI が `decoder.decode(f, msg, 0)` と
timestamp 0 を渡すため。ライブラリ利用者は `Parser` に正しい時刻を与えれば解決するが、
**JSON に受信時刻そのものを出す手段が無い**ため、azarashi の `received_at` に相当する情報は
azaraC の出力からは得られない。

---

## 7. 実測サイズ

同一 6 電文の合計バイト数（区切り文字なしのコンパクト表現）。

| 対象 | バイト | 指数 |
|---|---|---|
| azarashi レコード全体 | 28,688 | 4.84× |
| azarashi `data` のみ | 18,652 | 3.15× |
| **azaraC レコード全体** | **5,929** | **1.00×** |

azarashi の `data` 内訳:

| 要素 | バイト | 割合 |
|---|---|---|
| `scheme` キー＋値 | 4,760 | 26% |
| `labels` オブジェクト | 5,386 | 29% |
| その他 | 8,506 | 45% |

レコード全体では `text`/`text_en` が 40%、`data` が 52% を占める（79 例の平均）。

`scheme` は 6 電文で 124 回出現する。同じ体系名（例 `qzss.dcr.tsunami_forecast_region`）が
地域の数だけ繰り返される。azarashi 自身もこれは認識しており、重複判定は
`type` と `data` の一致で行うと定めている。

入れ子の深さ（実測）:

| 電文 | azarashi | azaraC |
|---|---|---|
| Tsunami | 7 | 5 |
| J-Alert | 5 | 3 |
| EEW | 5 | 4 |

---

## 8. 評価

### azaraC が勝る点（実測で裏づけあり）

1. **サイズが 1/3**（5,929 vs 18,652 B）。組込みで `Serial` に出し、無線で送る用途では決定的
2. **入れ子が浅い**（最大 5 段 vs 7 段）。`detail.entries[i].arrival_time` のように
   1 パスで辿れる
3. **人間が読みやすい**。`"height": 3, "height_label": "3m"` は `bounds` の
   `lower/upper/inclusive` より即座に意味が取れる
4. **`crc24` を持つ**（azarashi には無い）
5. **ラベルが 1 本**。日英併記の azarashi に対し、ビルド時に選んだ言語だけを持つ
   （AVR のフラッシュ制約下では必然）

利用者の「azaraC のほうが見やすい」という印象は、主に (2)(3) に由来する。妥当。

### azarashi が勝る点

1. **`recognized`** — 未定義コードと定義済み空ラベルを区別できる
2. **`scheme`** — キー名だけでは体系が決まらない（`region` は津波なら Tsunami Forecast Region、
   北西太平洋なら Coastal Region、火山なら Local Government）
3. **`status`/`basis`** — 時刻が「無い」のか「未解決」なのかが明示される
4. **`kind`/`unit`** — 機械が数値を解釈できる。範囲（`bounds`）も表現できる
5. **`test`** — 訓練/試験が 1 キーで分かる
6. **`received_at`** — 電文に無い受信時刻を運ぶ
7. **`text`/`text_en`** — 人間向け本文
8. **JSON Schema が同梱** — 機械検証できる

### 落ちる情報の総量

同じ 6 電文で、azaraC は以下を表現できない（すべて §6 で特定）:
未定義コードの識別、コード体系の明示、時刻の状態、単位、津波高の範囲、
マグニチュードの実数値、受信時刻、訓練/試験フラグ、本文。

ただし **azaraC が失っているのは主に「メタ情報」で、電文が運んだコード値そのものは
ほぼ全て残っている**（`arrival_time_raw`、生の `magnitude`、`ambiguity`、`sd_sdm` 等）。
azarashi の冗長な `scheme`/`labels` は、コード値から再構成できる情報でもある。

---

## 9. 互換性を保つための方針

**結論: 形は azaraC のまま、azarashi の意味論のうち azaraC が落としている部分だけを取り込む。**
azarashi の封筒（`scheme`/`labels`/`bounds`）をそのまま真似ると、サイズが 3 倍になり
組込みでの利点を失う。真似る必要も無い — 落ちているのは形ではなく**意味**である。

優先度順。各項目は独立して入れられる。

| # | 変更 | 効果 | コスト |
|---|---|---|---|
| 1 | ~~`svid_label` を `svid - 128` で引く（§6.1）~~ **完了**（`svid & 0x3F`） | バグ修正 | 1 行 |
| 2 | `magnitude` を実数化（`/10`）し `magnitude_raw` を追加 | 誤読の解消 | 小 |
| 3 | `recognized: true/false` を各 `_label` の隣に追加 | 未定義の識別 | 全ラベル箇所 |
| 4 | 津波 `arrival` に `status` を追加（`time`/`arrival_estimated`/`no_information`/`unrecognized`） | DCR-017 の 2 センチネルを表現 | `resolveArrivalTime` の改修 |
| 5 | 数値キーに `_unit` を併記（`depth_unit: "km"` 等） | 機械可読化 | 小 |
| 6 | `test` を最上位に追加 | 1 キーで判別 | 小 |
| 7 | `report_time` に `basis` を追加 | `unix: 0` の曖昧さ解消 | 小 |
| 8 | ~~`version` を `detail` に追加~~ **完了**（最上位 `version`） | 欠落の解消 | 小 |
| 9 | `text`/`text_en` は **入れない** | サイズ 40% 増 | — |
| 10 | `scheme` は **入れない** | サイズ 26% 増、キー名で足りる | — |
| 11 | `received_at` は利用者が `Parser` に与える時刻をそのまま出す | azarashi 相当 | 小 |

実装状況: **1 は完了**（`svid & 0x3F`）、`8` は完了（`Mt43Data::version` → `"version"`）。
残りは未着手。`version` の出力先は計画時の `detail.version` ではなく最上位にした
（MT43 の共通ヘッダは `detail{}` の外にあり、`report_classification` 等と同じ階層が自然なため）。

### 判断が必要な点

- **`scheme` 相当を入れるか** — azaraC のキー名は文脈依存（`region` が 7 種の表を指す）。
  `scheme` を入れる代わりに **キー名を具体化**すれば（`region` → `tsunami_region` 等）
  冗長性ゼロで体系が一意になる。既存キー名が変わるため互換性は切れる。
  なお azarashi 自身も `region` を使い分けており（`scheme` で区別）、統一感の面では
  現状維持にも根拠がある。
- **`bounds` を入れるか** — 津波の高さだけが該当。azarashi の実際の境界は次のとおり
  （`azarashi.json.model` の `tsunami_height` 定義から実測）。

  | code | 表示 | lower | upper |
  |---|---|---|---|
  | 1 | 0.2m未満 | — | 0.2（含まない） |
  | 2 | 1m | 0.2（含む） | 1（含む） |
  | 3 | 3m | 1（含まない） | 3（含む） |
  | 4 | 5m | 3（含まない） | 5（含む） |
  | 5 | 10m | 5（含まない） | 10（含む） |
  | 6 | 10m超 | 10（含まない） | — |
  | 13 / 14 | 該当情報なし / 不明 | `missing` |
  | 15 | その他の津波の高さ | 定性的区分（境界なし） |

  `height: 3` に加えて `height_min: 1.0, height_max: 3.0` を併記すれば、`kind` を
  導入せずに範囲を表現できる。ただし片側開区間（`10m超` の上限なし、`3m` の下限が
  開）は表現できないため、境界の含否まで要るなら `kind` 相当が要る。
- **`_label` の言語** — azarashi 0.17.0 の定義ヘッダを取り込み済みで、`AZARAC_LANG=JA`
  では日本語、`AZARAC_LANG=EN` では英語を出力する（`AZARAC_LANG_JA=1` かつ
  `AZARAC_LANG_EN=1` は日本語優先、無ければ英語）。英語表を持たない項目
  （南海トラフの情報番号など）は日本語のままになる。

### 追随しないもの

azarashi の API 変更（`decode()` 移行、例外の `Azarashi*` 改名、`reports.dcr`/`reports.dcx` への
クラス移動、tz-aware な UTC）は azaraC の C++ 実装に影響しない。azaraC が azarashi から
取り込むのは**定義テーブルの値だけ**である。

---

## 10. 参照

- azarashi 0.17.0 `docs/json.md` — 上記の規則の原典
- azarashi 0.17.0 `azarashi/json/schemas/report-v1.schema.json` — JSON Schema
- `docs/json/report-v1.examples.pretty.json` — 79 例
- azaraC `src/json/JsonSerializer*.cpp` — 実装
- `qzss-specs/is-qzss-dcr-017.md` Table 4.1.2-21（Ta のセンチネル）、Table 4.1.2-23（津波高 13）
