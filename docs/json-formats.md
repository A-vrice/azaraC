# 概要(azaraCとazarashiのスキーマについて)

azaraCの`JsonSerializer`（C++ / `Print&`）が出力するJSONと、一部参照実装であるazarashi(v0.17.0)の`to_json_dict()`が出力するJSONの**スキーマが異なる**ため比較を行いました。(差異は当ライブラリが先行してJSONを実装し始めたため生じている)
それぞれの用途や対象は異なるため、あくまで優劣ではなく互換性のための比較になります。

なお比較には当リポジトリ内のテスト電文`test/data/*.json`のNMEA文236件(MT43: 103件/MT44: 133件)を使用しました。

---

## 1. azaraC の JSON スキーマ

### 1.1 共通ヘッダ

| キー | 型 | 内容 |
|---|---|---|
| `svid` | int | QZSS L1S PRN。NEMA、UBXともに正規化され基本181-191になる |
| `svid_label` | str | `svid`が既知のみちびき（128–191）を示す場合は`qzss_dcr_satellite_prn`を引く（表は 55/56/57/58/61）。比較では156レコードのうち 95件がに解決され、残り61件（PRN181/182 = DCX 実データ）は表の範囲外のため`""`と出力した。なおフレーマがsvidを変換できなかったときはラベルは付かない |
| `msg_type` | int | `43`か`44` |
| `msg_type_label` | str | `"DCR"`が`"DCX"` |
| `crc24` | str | `"0x00F92C3F"`などのチェックディジット。azarashiの出力には無い |
| `version` | int | MT43のみDCRの `Vn`（214から219までの6bit`）。仕様は1を要求し、かつ`decodeQzqsm`も1以外を拒否するため常に1 |

**MT43**は共通ヘッダのあとに `report_classification` / `disaster_category` /`information_type`と各`_label`、`report_time{month,day,hour,min,unix}`、`detail{...}`を持つ。
**MT44**ではMT43固有のキーは表示せず、Aフィールドを1層目に持つ。

ラベルは`_label`サフィックスのキーに出力される。`AZARAC_LANG_JA=1`かつ`AZARAC_LANG_EN=1`(日英ともに有効化された状態)の条件では、日本語の文字列のキーは`_label`、英語には`_label_en`が併記される。`entries[]` 要素の`height_label` / `prefecture_label` / `warning_level_label` / `sub_category_label`などが対象。
対象外なのは汎用キーのラベル（`notifications[].label`, `regions[].region_label`, `prefecture_labels[]`, `city_labels[]`）で、
要素ごとにコード体系が異なるため固定キー名の `_label_en`では意味が通らない。
詳細は [API リファレンス](api-reference.md#言語選択)。

### 1.2 MT43 の `detail`（カテゴリ別）

テスト電文で確認した形（カテゴリ6のみ実装から記載）。`(+_label)`は`_label`が付くキー。

| cat | ラベル | `detail` のキー |
|---|---|---|
| 1 | 緊急地震速報 | `long_period_lower/upper`(+`_label`), `notifications[]{code,label}`, `quake_time`, `depth`(+`_label`), `magnitude`(+`_label`), `epicenter`(+`_label`), `intensity_lower/upper`(+`_label`), `regions[]{code,label}` |
| 2 | 震源 | `coords{lat_deg,lat_min,lat_sec,lat_ns,lon_deg,lon_min,lon_sec,lon_ew}`, `depth`(+`_label`), `magnitude`(+`_label`), `epicenter`(+`_label`), `notifications[]`, `quake_time` |
| 3 | 震度 | `entries[]{prefecture(+_label),intensity(+_label)}`, `quake_time` |
| 4 | 南海トラフ地震 | `info_code`(+`_label`), `page`, `total_page`, `truncated`, `text_utf8`（ページ集約後）/ `text_hex[]`（ページ単体） |
| 5 | 津波 | `warning_code`(+`_label`), `entries[]{arrival_day_offset,arrival_hour,arrival_min,arrival_time_raw,arrival_time,height(+_label),region(+_label)}` |
| 6 | 北西太平洋津波 | `potential`(+`_label`), `entries[]{…cat5 と同形}` |
| 8 | 火山 | `ambiguity`(+`_label`), `activity_time`, `warning_code`(+`_label`), `volcano_name`(+`_label`), `local_govs[]{code,label}` |
| 9 | 降灰 | `activity_time`, `warning_type`(+`_label`), `volcano_name`(+`_label`), `entries[]{arrival_hour,warning_code(+_label),local_gov(+_label)}` |
| 10 | 気象 | `warning_state`(+`_label`), `entries[]{region(+_label),sub_category(+_label)}` |
| 11 | 洪水 | `entries[]{region(+_label),warning_level(+_label)}` |
| 12 | 台風 | `coords`, `elapsed`(+`_label`), `intensity`(+`_label`), `max_gust`(+`_label`), `max_wind`(+`_label`), `number`(+`_label`), `pressure`(+`_label`), `ref_type`(+`_label`), `reference_time`, `scale`(+`_label`) |
| 14 | 海上 | `entries[]{region(+_label),warning_code(+_label)}` |

カテゴリ6の電文は`test/integration/test_realdata.cpp`にのみある。洪水の予報区コードのように10桁を超えるコードは`uint64_t`でそのまま返却。

### 1.3 MT44のキー

検証データに含まれていた最上位キー。共通ヘッダ5キーを除いて41種。

A フィールド: `dcx_type` / `dcx_type_label`（`NULL` / `L_ALERT` / `J_ALERT` / `LOCAL_GOV` /
`OUTSIDE_JAPAN` / `UNKNOWN`）、`a1_msg_type`, `a2_country`(+`_label`),
`a3_provider`(+`_label`), `a4_hazard` / `a4_hazard_category` / `a4_hazard_type` /
`a4_hazard_definition`, `a5_severity`(+`_label`), `a6_onset_week`(+`_label`),
`a7_onset_minute`, `a8_duration`(+`_label`), `onset_time`,
`a9_type_of_library`(+`_label`), `a10_library_version`(+`_label`), `a11_guidance`(+`_label`),
`a17_type_of_specific_settings`(+`_label`), `a18_specific_settings`。

条件付きブロック（該当時のみ出現）:

| ブロック | 条件 | キー |
|---|---|---|
| `main_ellipse` | A12–A16が存在 | `lat_deg`, `lon_deg`, `semi_major_km`, `semi_minor_km`, `azimuth_deg` |
| `main_ellipse.b1_refinement` | B1 | `c1_lat_offset_deg`, `c2_lon_offset_deg`, `c3_refined_semi_major_km`, `c4_refined_semi_minor_km` |
| `hazard_center` | B2 | `c5_raw`, `c6_raw`, `delta_lat_deg`, `delta_lon_deg` |
| `secondary_ellipse` | B3 | `c7_shift`, `c8_homothetic`, `c9_bearing`, `c10_guidance`(+`_label`), `c10_guidance_code` |
| `detailed_info` | B4 | `a4_code`とa4に応じたDフィールド（§1.4） |
| `jalert_target` | J-Alert | `prefecture_mode`, `prefecture_positions[]` + `prefecture_labels[]`（都道府県）/ `city_codes[]` + `city_labels[]`（市区町村） |
| `additional_area` | EX2–EX7（地方自治体） | `head_to_area`, `ellipse{lat_deg,lon_deg,semi_major_km,semi_minor_km,azimuth_deg}` |
| `ex1_target_area`(+`_label`), `target_area_code` | L-Alert | — |
| `ex8_area_type` | J-Alert | — |
| `ex11_raw` | 国外 | — |
| `ex_vn` | 拡張部あり | 拡張部の版数 |
| `alert_identity{a2,a3,a4,ex1}`, `sd_sdmt`, `sd_sdm` | 常時（MT44） | — |

`main_ellipse`は133通中9通に出て、いずれも `b1_refinement`を伴う（A17=0でも
C1–C4が非ゼロならB1として出る）。`hazard_center`（B2）・`secondary_ellipse`（B3）・
`detailed_info`（B4）・`additional_area`（EX2–EX7）を含む電文はテストデータに無く、
`test/json/test_json_dcx_b1b4.cpp` の合成メッセージで検証している。

### 1.4 D フィールドの形

B4（A17=11）の D1–D36 は **`{"raw": 生値, "label": 表示文字列}`** の2キーで出る。

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

`a4_code`（ハザード種別）ごとに「どの D が意味を持つか」が決まり、該当しないものは
**キーごと出ない**（`a4=1` なら `a4_code` だけ）。欠落と `raw: 0` は別物。
`d5_wave_height` のラベルにあるように、範囲の情報はラベル文字列の中にしか無い（§2.3）。

`d1_magnitude` は raw が 4bit（0–15）だが表は 0–8 しか持たない。表外の raw（例 15）は
`label: ""` になる。azarashi は同コードを `recognized: false` として区別する。

---

## 2. azarashi との対応

### 2.1 その他概要キー
| 要素 | azarashi 0.17 | azaraC | 差 |
|---|---|---|---|
| バージョン | `schema_version: 1` | なし | azaraCはレコード形式の版を持たない |
| 電文版（DCR の `Vn`） | `data.version: 1` | `version: 1`（MT43 のみ） | azaraC は DCR の `Vn` だけを `version` として運ぶ |
| 種別 | `type: "qzss.dcr.tsunami"` | `msg_type: 43` + `msg_type_label` + `disaster_category` | azaraC は数値の組合せ |
| 訓練/試験 | `test: true` | なし | azaraC は `report_classification == 7` を読み手が解釈する |
| 受信時刻 | `received_at: "...Z"` | なし（`report_time.unix` は `Parser` に時刻を渡さないと 0） | azaraC は受信時刻を運ばない |
| 衛星 | `satellite: {system, prn}` \| `null` | `svid` + `svid_label` | azaraC は 1 つの数値で PRN を運ぶ |
| 元電文 | `nmea` | なし | azaraC は再生成しない |
| 本文 | `text`, `text_en` | 南海トラフのみ（`text_utf8`、ページ単体では `text_hex[]`） | azaraC は他カテゴリで本文を生成しない |
| ペイロード | `data`（種別ごと） | 最上位に `detail` 等（種別ごと） | ネストが1段浅い |
| 検査値 | なし | `crc24` | azaraC のみ |

### 2.2 コード値の表し方

**azarashi** — 4 項目を必須とするオブジェクト。

```json
{"scheme": "qzss.dcr.tsunami_forecast_region", "code": "610",
 "recognized": true, "labels": {"ja": "高知県", "en": "Kochi Prefecture"}}
```

- `scheme`がコード体系を一意に決める（`camf.a5_severity`, `qzss.dcr.*`, `camf.provider.country_111` …）
- `code`は十進文字列。大きな整数コード（洪水の 12桁等）も落ちない
- `recognized: false` = コード表に定義が無い。`labels`は`{}`で、**コード番号そのものは保持**
- 表示文字列が無い定義済みコードも`labels: {}`。「未定義」と区別できる
- `ja`/`en` は併記される（両方ある場合）

**azaraC** — 数値とラベルの並置。

```json
{"region": 610, "region_label": "高知県"}
```

- キー名が `region` なので体系は文脈依存（`scheme` に相当する情報はキー名とカテゴリだけ） //修正予定
- 値は数値。洪水のような大コードは`uint64_t` で数値のまま
- ラベルは`_label`サフィックスのキーで、言語はビルド時に決定
- 未定義コードは`""`、定義済みの空ラベルも`""`→ **区別できない** //修正予定

| 状況 | azarashi | azaraC |
|---|---|---|
| 未定義コード | `recognized:false`, `labels:{}`, `code` 保持 | `"_label": ""`, 元コードは数値キーに残る |
| 定義済み・表示なし | `labels: {}` | `"_label": ""` |
| provider code 0（Fiji, A2=71） | `recognized:false`, `labels:{}` | `a3_provider_label: ""` |

「定義済み・表示なし」（例: A11 code 0）と「未知の提供者」（provider code 0, Fiji）は
azaraC 側で**同じ `""`** になる。両者を読み手は区別できない。

`a11_guidance_label` は元コード A11 と、A9/A2 で選ぶライブラリ（DCX-004 §4.2.3.9
Table 4.2-12）で決まる:

| A9 | A2 | 引く表 | 出力 |
|---|---|---|---|
| 0 | — | International library（コード 0–31） | `_label` 1 本のみ（日本語の兄弟表が無いので `_label_en` は出ない） |
| 1 | 111 | Japanese library | `_label`（＋両言語ビルドでは `_label_en`） |
| 1 | ≠111 | 無し | `_label: ""` |

範囲外のコードは `""`。実データ 133 通（重複文を除く）では A9=1 / A2=111 が 125 通
（A11=136 が 41 通、128 が 1、134 が 1、0 が 82）、A9=1 / A2=71 が 6 通、A9=0 / A2=111
（Null Message）が 2 通。国内表に当たる 43 通だけがラベル非空になり（例: 136 =
「これは、Jアラートのテストです。」）、残り 90 通は空になる。

### 2.3 数量（数値＋単位）

**azarashi** — `kind` で形を決める（`azarashi/json/model.py` の `PROFILES`）。

| `kind` | 内容 | 例 |
|---|---|---|
| `scalar` | `value`, `unit` | `{"kind":"scalar","value":10,"unit":"km", …}` |
| `bounds` | `lower`/`upper`（各 `{value,inclusive}`） | 津波の高さ `3m` = 1m 超〜3m 以下 |
| `category` | コードのみ（数値境界なし） | 北西太平洋津波の高さ区分 |
| `missing` | `reason` (`unknown`/`no_information`/`unrecognized_code`) | 深さ 511 |

**azaraC** — `kind` も `unit` も無く、数値を素で置く。ただし数量フィールドには `_label` が
付き、境界（`500kmより深い`）とセンチネル（`不明`）は可視化される。

| 電文 | フィールド | azarashi | azaraC | 落ちるもの |
|---|---|---|---|---|
| EEW | `depth` | `scalar 10, unit km` | `"depth": 10` + `depth_label: "10km"` | 単位（機械可読） |
| EEW | `magnitude` | `scalar 7.2, unit null` | `"magnitude": 72` + `magnitude_label: "7.2"` | **実数化**（生コード 72 = 7.2） |
| Tsunami | `height` | `bounds 1<x≤3, unit m` | `"height": 3` + `height_label: "3m"` | 単位・範囲 |
| Typhoon | `central_pressure` | `scalar 955, unit hPa` | `"pressure": 955` + `pressure_label: "955hPa"` | 単位（機械可読） |
| Typhoon | `maximum_wind_speed` | `scalar 40, unit m/s` | `"max_wind": 40` + `max_wind_label: "40m/s"` | 単位（機械可読） |
| Typhoon | `elapsed_time` | `scalar 0, unit h` | `"elapsed": 0` + `elapsed_label: "0時間後"` | 単位（機械可読） |

`_label` / `_label_en` により単位とセンチネルは**人間には読める**が、値自体は生コードのままなので
**機械可読な単位・境界型は持たない**。津波の高さは特に注意が必要で、仕様の `3m` は
「1m 超〜3m 以下」という *範囲* であり単一値ではない（`is-qzss-dcr-017`
Table 4.1.2-23）。

### 2.4 時刻

**azarashi** — `status` / `value` / `basis` の 3 項目（`azarashi/json/model.py` の `_time_value`）。

| `status` | 意味 |
|---|---|
| `time` | UTC 日時。`basis` が `received_at` か `report_time` か |
| `arrival_estimated` | 国内津波の「津波到達中と推測」（Ta = hour 31, min 63） |
| `arrived_or_unknown` | 北西太平洋津波の「到達済みまたは不明」 |
| `no_information` | 国内津波の「該当情報なし」（Ta = day 0, hour 30, min 62） |
| `not_used` | DCX の時刻フィールドが未使用（A7 = 0） |
| `unrecognized_code` | 日時に変換不能。`source` に生の日・時・分 |

`basis` は「年・月・日を補うのに何を基準にしたか」を示す。

**azaraC** — `{month, day, hour, min, unix}` の 5 項目。

`resolveArrivalTime()`（`src/decoder/Decoder.cpp`）は

```cpp
if (hour > 23 || min > 59) return t;   // 全ゼロ
```

とするため、**`31:63`（到達中）と `30:62`（情報なし）と `25:00`（不正）がすべて同じ全ゼロに潰れる**。 //修正予定
実測（`test/integration/test_realdata.cpp` の `$QZQSM,56,53ADA8BECF…`、Ta = 2047 = hour 31, min 63）:

```
azarashi:  "arrival": {"status": "arrival_estimated", "value": null, "basis": null}
azaraC  :  "arrival_hour": 31, "arrival_min": 63, "arrival_time_raw": 2047,
           "arrival_time": {"month":0,"day":0,"hour":0,"min":0,"unix":0}
```

azaraC は `arrival_time_raw` と分解フィールド（`arrival_hour`/`arrival_min`）を残すので
情報自体は失われていないが、`arrival_time` だけを見ると「時刻不明」と読める。

| 項目 | azarashi | azaraC |
|---|---|---|
| `report_time` | `status:time`, `basis:received_at` | `Parser::feed()` に渡した時刻で解決。CLI は 0 を渡すため `unix` は 0 |
| DCX `onset` | 週 + 週内分から `received_at` を基準に解決 | 同上（CLI では全ゼロ） |
| 火山の曖昧さ | `activity_time_ambiguity`（コードオブジェクト）を必須で併記し、`Du` に応じて `activity_time` の有効範囲を解釈 | `ambiguity` + `ambiguity_label`（`Du` の 0–7 を明示）。`activity_time` の有効範囲は解釈しない |

`unix: 0` は「未解決」の意味だが、スキーマ上は正当な値（1970-01-01）でもある。
azarashi は `status` で明示するのでこの曖昧さが無い。

### 2.5 繰り返し項目の組み方

**azarashi** — 1 件 1 オブジェクト。並列配列を作らない。

```json
"forecasts": [
  {"region": {…}, "height": {…}, "arrival": {…}}
]
```

**azaraC** — 種別により 2 通り。

```json
"entries": [{"arrival_*": …, "height": 3, "region": 600, "region_label": "…"}]
"jalert_target": {"prefecture_mode": 1,
                  "prefecture_positions": [1,2,3,…],
                  "prefecture_labels": ["北海道","青森県",…]}
```

J-Alert の都道府県は **並列配列**で、`prefecture_positions[i]` と `prefecture_labels[i]` の
対応を読み手が保つ必要がある（`city_codes`/`city_labels` も同様）。azarashi は
`target_regions` のオブジェクト配列で、`qzss.dcx.prefecture_bit` の code を
**下位から 0 始まりのビット位置**として持つ。azaraC は 1 始まりの位置を出す
（同じ電文で azaraC `[1,2,…]` ↔ azarashi `code: "0"`, `"1"`, …）。

EX9 の元 64 ビット整数は azarashi は出さない（`nmea` に残る）。azaraC は
`prefecture_positions` / `city_codes` に展開する。

### 2.6 サイズと入れ子の深さ

同一 236 電文の合計（区切り文字なしのコンパクト表現、UTF-8 バイト）。

| 対象 | バイト | 1 レコード平均 |
|---|---|---|
| azarashi レコード全体 | 708,539 | 3,002 |
| azarashi `data` のみ | 362,858 | 1,538 |
| **azaraC レコード全体（`--raw`）** | **261,339** | **1,107** |
| azaraC レコード全体（重複除去あり） | 205,925 | — |

azarashi のレコード全体では `data` が 51%、`text`/`text_en` が 41% を占める。
`data` の内訳は `labels` オブジェクトが 32%、`scheme` キー＋値が 25%
（`scheme` は 236 電文で 2,483 回出現し、同じ体系名が地域の数だけ繰り返される）。

入れ子の深さ（オブジェクト／配列の段数、ルートを 1 とする）:

| 電文 | azarashi | azaraC |
|---|---|---|
| Tsunami | 7 | 5 |
| EEW | 5 | 4 |
| Volcano | 5 | 4 |
| Typhoon | 5 | 3 |
| J-Alert | 5 | 3 |

azarashi が深いのは、コード値を `{scheme, code, recognized, labels}` で包むため。
`scheme` は同じ体系名を要素の数だけ繰り返すので、`data` の中身に対して冗長な比重が大きい。

---

## 3. 落ちる情報と互換方針

azaraC が出さないもの（すべて §2 で特定）: 未定義コードの識別（`recognized`）、
コード体系の明示（`scheme`）、時刻の状態（`status`/`basis`）、単位（`unit`）、
津波高の範囲（`bounds`）、マグニチュードの実数値、受信時刻（`received_at`）、
訓練/試験フラグ（`test`）、本文（`text`/`text_en`）。

ただし失っているのは主に**メタ情報**で、電文が運んだコード値そのものはほぼ全て残る
（`arrival_time_raw`、生の `magnitude`、`ambiguity`、`sd_sdm` 等）。

方針: **形は azaraC のまま、azarashi の意味論のうち azaraC が落としている部分だけを取り込む。**
azarashi の封筒（`scheme`/`labels`/`bounds`）をそのまま真似るとサイズが 3 倍近くになり
組込みでの利点を失う。

- `scheme` は入れない — 体系はキー名（`region` → 津波の予報区、北西太平洋の沿岸区域、
  火山の自治体、…）とカテゴリで決まり、冗長性を払う価値が無い
- `labels` は入れない — 言語はビルド時に選び、`_label` 1 本で運ぶ
- `bounds` は入れない — 津波の高さだけが該当し、境界は `height_label` で読める
- `text`/`text_en` は入れない — サイズが 41% 増える
- `received_at` は `Parser::feed()` に与えた時刻を `report_time`/`onset_time` に反映する形で扱う

`recognized` 相当（未定義コードの識別）、`unit`、津波高の境界型、`report_time` の
`status`/`basis` は現状持たない。これらが必要な用途では azarashi の出力を使う。

---

## 4. 参照

- azarashi 0.17.0 `azarashi/json/model.py` — `PROFILES`（数量の境界・センチネル）と
  `_time_value`（時刻の `status`）の原典
- azarashi 0.17.0 `azarashi/json/schemas/report-v1.schema.json` — JSON Schema
- azaraC `src/json/JsonSerializer*.cpp` / `src/json/JsonWriter.h` — 実装
- azaraC `test/json/test_json_dcx_b1b4.cpp` — B1–B4 の D フィールド検証
- `qzss-specs/is-qzss-dcr-017.md` Table 4.1.2-21（Ta のセンチネル）、Table 4.1.2-23（津波高）
