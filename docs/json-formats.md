# JSON 出力仕様 — azaraC と azarashi の対応

azaraC の `JsonSerializer`（C++ / `Print&`）が出力する JSON と、参照実装である
azarashi（v0.17.0）の `to_json_dict()` が出力する JSON は **スキーマが異なる**。
対象が違う（組込み向けの最小表現か、Python 側の完全レコードか）ため、優劣ではなく
用途に応じた選択になる。本ドキュメントは azaraC のスキーマを示し、両者の差分を整理する。

ルートの `schema_version` は現在 `2`。読み手はこの値で分岐する。

数値の比較には `test/data/*.json` の NMEA 236 通（重複文を除く。MT43 103 / MT44 133）
を用いる。重複文も流す `--raw` の 245 通は §2.6 に併記する。

---

## 1. azaraC の JSON スキーマ

ルートの形は 2 通り。本文（電文の内容）は常に `data` の中に入る。

```json
{"schema_version":2,"svid":186,"msg_type":43,"crc24":"0x00F92C3F",
 "report_classification":1,"report_classification_label":"最優先",
 "disaster_category":5,"disaster_category_label":"津波",
 "information_type":0,"information_type_label":"発表",
 "version":1,"report_time":{…},"data":{…}}

{"schema_version":2,"svid":184,"msg_type":44,"crc24":"0x00074DAD","data":{…}}
```

デコードに失敗した場合の `note` は 4 通り。`invalid_mt43` / `invalid_mt44` /
`unsupported_msg_type` は `crc24` の直後に `note` が出て `data` は出ない
（MT43 のメタ情報と `version` / `report_time` も出ない）。`unsupported_category`
だけは MT43 のメタ情報・`version` / `report_time` を出したうえで
`"data":{"note":"unsupported_category"}` を出す（`Parser` 経由では到達しない:
カテゴリはデコード時に `AZARAC_ENABLE_*` で弾かれる）。

### 1.1 共通ヘッダ

| キー | 型 | 内容 |
|---|---|---|
| `schema_version` | int | 常に 2 |
| `svid` | int | QZSS L1S PRN。`NmeaFramer` は受理した Satellite ID を `\| 0x80` で正規化（53→181, 54→182, 55–63→183–191）。`UbxFramer` は `ublox_qzss_svid_prn_map` で変換（1–4→183–186、7→189）し、表に無い `svId` は入力値のまま通す |
| `msg_type` | int | 43 / 44 |
| `crc24` | str | `"0x00F92C3F"`。azarashi の出力には無い |
| `data` | obj | 本文（§1.2 / §1.3）。失敗時は代わりに `note` |
| `note` | str | `invalid_mt43` / `invalid_mt44` / `unsupported_category` / `unsupported_msg_type`（`unsupported_category` のみ `data` の中） |

MT43 はこれに加えて DCR の報告ヘッダをルートに持つ: `report_classification`(+`_label`) /
`disaster_category`(+`_label`) / `information_type`(+`_label`) / `version` /
`report_time{month,day,hour,min,unix}`。MT44 のルートは `crc24` までで、A フィールド・
拡張部・`sd_sdmt` / `sd_sdm` はすべて `data` の中。

`svid` と `msg_type` はラベルを持たない。

### 1.2 MT43 の `data`（カテゴリ別）

テスト電文に現れる形。`(+_label)` は `_label` が付くキー。

| cat | ラベル | `data` のキー |
|---|---|---|
| 1 | 緊急地震速報 | `long_period_lower/upper`(+`_label`), `notifications[]{code,label}`, `quake_time`, `depth`(+`_label`), `magnitude`(+`_label`), `epicenter`(+`_label`), `intensity_lower/upper`(+`_label`), `regions[]{code,label}` |
| 2 | 震源 | `coords{lat_deg,lat_min,lat_sec,lat_ns,lon_deg,lon_min,lon_sec,lon_ew}`, `depth`(+`_label`), `magnitude`(+`_label`), `epicenter`(+`_label`), `notifications[]`, `quake_time` |
| 3 | 震度 | `entries[]{prefecture(+_label),intensity(+_label)}`, `quake_time` |
| 4 | 南海トラフ地震 | `info_code`(+`_label`), `page`, `total_page`, `truncated`, `text_utf8`（ページ集約後）/ `text_hex[]`（ページ単体） |
| 5 | 津波 | `warning_code`(+`_label`), `entries[]{arrival_time_raw,arrival_status?,arrival_time?,height(+_label),region(+_label)}` |
| 6 | 北西太平洋津波 | `potential`(+`_label`), `entries[]{…cat5 と同形}` |
| 8 | 火山 | `ambiguity`(+`_label`), `activity_time`, `warning_code`(+`_label`), `volcano_name`(+`_label`), `local_govs[]{code,label}` |
| 9 | 降灰 | `activity_time`, `warning_type`(+`_label`), `volcano_name`(+`_label`), `entries[]{arrival_time_code(+_label),warning_code(+_label),local_gov(+_label)}` |
| 10 | 気象 | `warning_state`(+`_label`), `entries[]{region(+_label),sub_category(+_label)}` |
| 11 | 洪水 | `entries[]{region(+_label),warning_level(+_label)}` |
| 12 | 台風 | `coords`, `elapsed`(+`_label`), `intensity`(+`_label`), `max_gust`(+`_label`), `max_wind`(+`_label`), `number`(+`_label`), `pressure`(+`_label`), `ref_type`(+`_label`), `reference_time`, `scale`(+`_label`) |
| 14 | 海上 | `entries[]{region(+_label),warning_code(+_label)}` |

カテゴリ 6 の電文を検証しているのは `test/integration/test_realdata.cpp`。洪水の予報区
コードのように 10 桁を超えるコードは `uint64_t` のまま数値で出る。

津波の到着時刻は `arrival_time_raw`（12bit: day_offset 1 + hour 5 + min 6）だけを残し、
`arrival_time` は解決できたときだけオブジェクト、できないときは `null`。
解決できなかった理由は `arrival_status` に出る（通常時刻ではキーごと出ない）。

| 判定（上から最初に一致したもの） | `arrival_status` | `arrival_time` |
|---|---|---|
| `hour == 31 && min == 63`（cat 5） | `"arrival_estimated"` | `null` |
| `hour == 31 && min == 63`（cat 6） | `"arrived_or_unknown"` | `null` |
| `day_offset == 0 && hour == 30 && min == 62`（cat 5 のみ） | `"no_information"` | `null` |
| `raw == 0`、または `hour > 23`、または `min > 59` | `"unrecognized_code"` | `null` |
| 上記以外 | キーを出さない | `{month,day,hour,min,unix}` |

判定順は azarashi と同じ（センチネル → 範囲外）。範囲外チェックを先に置くと `hour == 30` の
`no_information` が到達不能になる。`raw == 0` は azarashi が「同日 00:00」に解決するのに対し
azaraC の `resolveArrivalTime()` は空を返すため `unrecognized_code` になる
（読み手は `arrival_time_raw: 0` で `1982` 等と区別できる）。

### 1.3 MT44 の `data` のキー

テスト電文 133 通（すべて A17=0）の `data` 内のキー。

A フィールド: `dcx_type`（`"NULL"` / `"L_ALERT"` / `"J_ALERT"` / `"LOCAL_GOV"` /
`"OUTSIDE_JAPAN"` / `"UNKNOWN"`）、`a1_msg_type`, `a2_country`(+`_label`),
`a3_provider`(+`_label`), `a4_hazard` / `a4_hazard_category` / `a4_hazard_type` /
`a4_hazard_definition`, `a5_severity`(+`_label`), `a6_onset_week`(+`_label`),
`a7_onset_minute`, `a8_duration`(+`_label`), `onset_time`,
`a9_type_of_library`(+`_label`), `a10_library_version`(+`_label`),
`a11_guidance`(+`_label`), `a11_guidance_list_b_label`,
`a17_type_of_specific_settings`(+`_label`), `a18_specific_settings`。

条件付きブロック（該当時のみ出現）:

| ブロック | 契機 | キー |
|---|---|---|
| `main_ellipse` | A12–A16 あり | `lat_deg`, `lon_deg`, `semi_major_km`, `semi_minor_km`, `azimuth_deg` |
| `main_ellipse.b1_refinement` | B1 | `c1_lat_offset_deg`, `c2_lon_offset_deg`, `c3_refined_semi_major_km`, `c4_refined_semi_minor_km` |
| `hazard_center` | B2 | `c5_raw`, `c6_raw`, `delta_lat_deg`, `delta_lon_deg` |
| `secondary_ellipse` | B3 | `c7_shift`, `c8_homothetic`, `c9_bearing`, `c10_guidance`(+`_label`), `c10_guidance_code` |
| `detailed_info` | B4 | a4 に応じた D フィールド（§1.4）。レイアウトが無ければ `{}` |
| `jalert_target` | J-Alert | `prefectures[]{position,label}`（都道府県）/ `cities[]{code,label}`（市区町村）。どちらか一方だけが出る |
| `additional_area` | EX2–EX7（地方自治体） | `head_to_area`, `ellipse{lat_deg,lon_deg,semi_major_km,semi_minor_km,azimuth_deg}` |
| `ex1_target_area`(+`_label`), `target_area_code` | L-Alert | — |
| `ex8_area_type` | J-Alert | — |
| `ex11_raw` | 国外 | — |
| `ex_vn` | 拡張部あり | 拡張部の版数 |
| `sd_sdmt`, `sd_sdm` | 常時（MT44 の最後） | — |

`main_ellipse` は 133 通中 9 通に出て、いずれも `b1_refinement` を伴う（A17=0 でも
C1–C4 が非ゼロなら B1 として出る）。`hazard_center`（B2）・`secondary_ellipse`（B3）・
`detailed_info`（B4）・`additional_area`（EX2–EX7）を含む電文はテストデータに無く、
`test/json/test_json_dcx_b1b4.cpp` の合成メッセージで検証している。

`jalert_target` の `position` は **JIS 都道府県コード（1–47、1 始まり）**。
`cities[].code` は EX1 の市町村コード（仕様と同じ値）。どちらの配列も
`{code|position, label}` のオブジェクト配列で、並列配列ではない。

### 1.4 D フィールドの形

B4（A17=11）の D1–D36 は **`"dX_name": 生値` と `"dX_name_label": 表示文字列` の 2 キー**で出る。

```json
"detailed_info": {
  "d1_magnitude": 6,      "d1_magnitude_label": "7.0-7.9 - Major",
  "d2_seismic_coeff": 7,  "d2_seismic_coeff_label": "7",
  "d3_azimuth": 5,        "d3_azimuth_label": "112.5°",
  "d4_vector_length": 9,  "d4_vector_length_label": "30",
  "d5_wave_height": 6,    "d5_wave_height_label": "5.0m < H ≤ 10.0m"
}
```

a4 のハザード種別ごとに「どの D が意味を持つか」が決まり、該当しないものは
**キーごと出ない**。欠落と `0` は別物。D レイアウトを持たない a4（例 a4=1）では
`detailed_info` が空オブジェクト `{}` になる（B4 が存在した事実は残る）。

`d1_magnitude` は raw が 4bit（0–15）だが表は 0–8 しか持たない。表外の raw（例 15）は
`d1_magnitude_label: null` になる。azarashi は同コードを `recognized: false` として区別する。

### 1.5 ラベルの 3 値規則

キーは常に出力する（キーごと省くことはしない）。

| 状況 | 出力 |
|---|---|
| 表を引いたが該当コードが無い（未定義・範囲外） | `"x_label": null` |
| 表に該当し、ラベルが空文字列（例: A11 国際ライブラリ code 0） | `"x_label": ""` |
| 表に該当し、ラベルがある | `"x_label": "…"` |
| この構成にラベル表自体が無い（`AZARAC_LANG_JA=0` かつ `AZARAC_LANG_EN=0`） | `"x_label": null` |
| `a11_guidance_label` のみ: A9=1 かつ A2≠111（国/地域ライブラリが日本以外に無い） | `"a11_guidance_label": null` / `"a11_guidance_list_b_label": null` |

`AZARAC_LANG_JA=1` かつ `AZARAC_LANG_EN=1` の構成では、文字列リテラルのキーを持つ
`_label` に `_label_en` が併記される。`_label_en` も同じ規則。`_label_en` を持たないのは
汎用キーのラベル（`notifications[].label`, `regions[].region_label`, `prefectures[].label`,
`cities[].label`, `entries[].label`, `local_govs[].label`）で、要素ごとにコード体系が
異なるため固定キー名の `_label_en` では意味が通らない。詳細は
[API リファレンス](api-reference.md#言語選択)。

---

## 2. azarashi との対応

### 2.1 レコード封筒

| 概念 | azarashi 0.17 | azaraC | 差 |
|---|---|---|---|
| レコード版 | `schema_version: 1` | `schema_version: 2` | 版数は独立 |
| 電文版（DCR の `Vn`） | `data.version: 1` | `version: 1`（MT43 のみ） | azaraC は DCR の `Vn` だけを `version` として運ぶ |
| 種別 | `type: "qzss.dcr.tsunami"` | `msg_type: 43` + `disaster_category` | azaraC は数値の組合せ |
| 訓練/試験 | `test: true` | なし | azaraC は `report_classification == 7` を読み手が解釈する |
| 受信時刻 | `received_at: "...Z"` | なし（`report_time.unix` は `Parser` に時刻を渡さないと `null`） | azaraC は受信時刻を運ばない |
| 衛星 | `satellite: {system, prn}` \| `null` | `svid` | azaraC は PRN を 1 つの数値で運ぶ。ラベルは無い |
| 元電文 | `nmea` | なし | azaraC は再生成しない |
| 本文 | `text`, `text_en` | 南海トラフのみ（`text_utf8`、ページ単体では `text_hex[]`） | azaraC は他カテゴリで本文を生成しない |
| ペイロード | `data`（種別ごと） | `data`（種別ごと） | 同じ名前・同じ位置 |
| 検査値 | なし | `crc24` | azaraC のみ |

### 2.2 コード値の表し方

**azarashi** — 4 項目を必須とするオブジェクト。

```json
{"scheme": "qzss.dcr.tsunami_forecast_region", "code": "610",
 "recognized": true, "labels": {"ja": "高知県", "en": "Kochi Prefecture"}}
```

- `scheme` がコード体系を一意に決める（`camf.a5_severity`, `qzss.dcr.*`, `camf.provider.country_111` …）
- `code` は十進文字列。大整数コード（洪水の 12 桁等）も落ちない
- `recognized: false` = コード表に定義が無い。`labels` は `{}` で、**コード番号そのものは保持**
- 表示文字列が無い定義済みコードも `labels: {}`。「未定義」と区別できる
- `ja`/`en` は併記される（両方ある場合）

**azaraC** — 数値とラベルの並置。

```json
{"region": 610, "region_label": "高知県"}
```

- キー名が `region` なので体系は文脈依存（`scheme` に相当する情報はキー名とカテゴリだけ）
- 値は数値。洪水のような大コードは `uint64_t` で数値のまま
- ラベルは `_label` サフィックスのキーで、言語はビルド時に決定
- 未定義コードは `null`、定義済みの空ラベルは `""` → **区別できる**

| 状況 | azarashi | azaraC |
|---|---|---|
| 未定義コード | `recognized:false`, `labels:{}`, `code` 保持 | `"_label": null`, 元コードは数値キーに残る |
| 定義済み・表示なし | `labels: {}` | `"_label": ""` |
| provider code 0（Fiji, A2=71） | `recognized:false`, `labels:{}` | `a3_provider_label: null` |
| 表そのものが無い | `recognized:false` | `"_label": null` |

`a11_guidance_label` は元コード A11 と、A9/A2 で選ぶライブラリ（DCX-004 §4.2.3.9
Table 4.2-12）で決まる。A11 は 10bit だが、国際ライブラリ（A9=0）では EWSS CAMF v1.1
§3.5.3 / §11 のとおり **List A 5bit（`a11 >> 5`）と List B 5bit（`a11 & 0x1F`）の 2 コード**
に分かれ、それぞれ別の表を引く。List B のラベルは常に出力する `a11_guidance_list_b_label`
に出る:

| A9 | A2 | `a11_guidance_label` が引く表 | `a11_guidance_list_b_label` |
|---|---|---|---|
| 0 | — | International library List A（`a11 >> 5`、0–31 を全定義） | International library List B（`a11 & 0x1F`）。29/30 は表に無く `null` |
| 1 | 111 | Japanese library（A11 の 10bit をそのまま鍵にする結合表） | 対応する表が無いため `null` |
| 1 | ≠111 | 無し → `null` | `null` |

国際表は英語のみなので `_label_en` は出ない。国際表 List A / List B の code 0 は定義済みの
空文字列 `""`。A11 の 10bit すべてが表の定義域なので「範囲外で `null`」は起きない
（List B は欠落コード 29/30 が `null`）。

実データ 133 通（重複文を除く）の内訳は A9=1 / A2=111 が 125 通（A11=0 が 82、136 が 41、
128 が 1、134 が 1）、A9=1 / A2=71 が 6 通、A9=0 / A2=111（Null Message）が 2 通。出力は
3 つに分かれる:

| `a11_guidance_label` の出力 | 通数 | 内訳 |
|---|---|---|
| ラベルあり | 125 | 国内表 A11=0（82、`指示なし` / `_label_en` は `No instruction`）・136（41）・128（1）・134（1）。例: 136 =「これは、Jアラートのテストです。」 |
| `""`（定義済みの空ラベル） | 2 | 国際表 List A code 0（A9=0 / A2=111）。`a11_guidance_list_b_label` も List B 0 で `""` |
| `null`（表が無い） | 6 | A9=1 / A2≠111（71）。表そのものが存在しない |

125 + 2 + 6 = 133。国内表（A9=1 / A2=111）を通る 125 通の
`a11_guidance_list_b_label` はすべて `null`（日本の表は List A / List B を 10bit の
結合表で持つため）。

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
「1m 超〜3m 以下」という *範囲* であり単一値ではない（`qzss-specs/is-qzss-dcr-017.md`
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

**azaraC** — `{month, day, hour, min, unix}` の 5 項目。`unix` は
`unix_time == 0`（未解決）のとき **`null`**、解決済みのときは数値。
`month` / `day` / `hour` / `min` は生の分解値のまま（未解決時は 0）。

- 津波の到着時刻は §1.2 の `arrival_status` で状態を明示する。例
  （`test/integration/test_realdata.cpp` の `$QZQSM,56,53ADA8BECF…`、Ta = 2047 = hour 31, min 63）:

  ```
  azarashi:  "arrival": {"status": "arrival_estimated", "value": null, "basis": null}
  azaraC: "arrival_time_raw": 2047, "arrival_status": "arrival_estimated", "arrival_time": null
  ```

  3 つのセンチネル（`31:63` / `30:62` / 不正値）は全ゼロの `arrival_time` に潰れない。
  状態は `arrival_status` に出る。`arrival_time_raw` は導出前の生値として残る。
- DCX の `onset_time` は A7=0 でも「未使用」と「解決できなかった」を区別しない
  （`unix: null` は両方で出る）。azarashi の `not_used` に相当する status は持たない。

| 項目 | azarashi | azaraC |
|---|---|---|
| `report_time` | `status:time`, `basis:received_at` | `Parser::feed()` に渡した時刻で解決。CLI は 0 を渡すため `unix` は `null` |
| DCX `onset` | 週 + 週内分から `received_at` を基準に解決 | 同上（CLI では `null`） |
| 火山の曖昧さ | `activity_time_ambiguity`（コードオブジェクト）を必須で併記し、`Du` に応じて `activity_time` の有効範囲を解釈 | `ambiguity` + `ambiguity_label`（`Du` の 0–7 を明示）。`activity_time` の有効範囲は解釈しない |

### 2.5 繰り返し項目の組み方

**azarashi** — 1 件 1 オブジェクト。並列配列を作らない。

```json
"forecasts": [
  {"region": {…}, "height": {…}, "arrival": {…}}
]
```

**azaraC** — `entries[]` などの数値キーと `_label` の並置、および J-Alert の
オブジェクト配列の 2 通り。

```json
"entries": [{"arrival_time_raw": 488, "arrival_time": {…}, "height": 3,
             "region": 600, "region_label": "…"}]
"jalert_target": {"prefectures": [{"position": 1, "label": "北海道"},
                                  {"position": 2, "label": "青森県"}]}
```

`entries[]` の要素は平坦（`{height, height_label}` の並置）のままで、ネストした
`{code, label}` オブジェクトにはしない。唯一のオブジェクト配列は `jalert_target` の
`prefectures` / `cities`。

プロトコル上の位置は「どのオブジェクト配列か」で決まるので、
`prefectures` / `cities` のどちらが出たか（および `data.ex8_area_type`）で読み分ける。
`position` は JIS 都道府県コード（1–47、1 始まり）で、azarashi が
`qzss.dcx.prefecture_bit` の code として **下位から 0 始まりのビット位置**を出すのとは
基準が違う（同じ電文で azaraC `1` ↔ azarashi `code: "0"`）。

EX9 の元 64 ビット整数は azarashi は出さない（`nmea` に残る）。azaraC は
`prefectures` / `cities` に展開する。

### 2.6 サイズと入れ子の深さ

同一 236 電文の合計（区切り文字なしのコンパクト表現、UTF-8 バイト）。両者を同じ計量
関数で測る。azarashi は `to_json_dict()` の完全レコード。

| 対象 | バイト | 1 レコード平均 |
|---|---|---|
| azarashi レコード全体 | 652,740 | 2,765 |
| azarashi `data` のみ | 352,777 | 1,494 |
| **azaraC レコード全体** | **254,196** | **1,077** |
| **azaraC `data` のみ** | **208,043** | **881** |

重複除去なしの 245 通では 268,816 バイト（平均 1,097）。

azarashi のレコード全体では `data` が 54%、`text`/`text_en` が 36% を占める。
`data`（352,777 B）のうち `labels` オブジェクトが 84,367 B（24%）、
`scheme` キー＋値が 87,440 B（25%）。`scheme` は 236 電文で 2,483 回出現し、
同じ体系名が地域の数だけ繰り返される。

入れ子の深さ（オブジェクト／配列の段数、ルートを 1 とする）。同一 236 電文の
カテゴリごとの最大値。azarashi は封筒（`schema_version` / `type` / `satellite` /
`nmea` / `text` / `data` …）を含む完全レコード（`azarashi.json.to_json_dict()`）で測る。
`get_params()` は封筒を外すため使わない。

| 電文 | azarashi | azaraC |
|---|---|---|
| Tsunami | 7 | 5 |
| EEW | 6 | 4 |
| Volcano | 5 | 4 |
| Typhoon | 6 | 4 |
| J-Alert | 6 | 5 |
| Ash fall | 7 | 4 |

差は主にコード値の包み方にある。azarashi は `{scheme, code, recognized, labels}` で
1 段深くし、MT44 では azaraC の `jalert_target.prefectures[]` / `cities[]` が
オブジェクト配列の分だけ 1 段深くなる（4 → 5）。

## 3. 落ちる情報と設計方針

azaraC が出さないもの: コード体系の明示（`scheme`）、単位（`unit`）、
津波高の範囲（`bounds`）、マグニチュードの実数値、受信時刻（`received_at`）、
訓練/試験フラグ（`test`）、本文（`text`/`text_en`）、
DCX `onset_time` の「未使用」と「未解決」の区別。

失うのは主に**メタ情報**で、電文が運んだコード値そのものはほぼ全て残る
（`arrival_time_raw`、生の `magnitude`、`ambiguity`、`sd_sdm` 等）。
未定義コードは `_label: null`、時刻の状態は `unix: null` と `arrival_status` で表す。

方針: **形は azaraC のまま、azarashi の意味論のうち azaraC が落としている部分だけを取り込む。**
azarashi の封筒（`scheme`/`labels`/`bounds`）をそのまま真似るとサイズが 2.6 倍になり
組込みでの利点を失う。

- `scheme` は入れない — 体系はキー名（`region` → 津波の予報区、北西太平洋の沿岸区域、
  火山の自治体、…）とカテゴリで決まり、冗長性を払う価値が無い
- `labels` は入れない — 言語はビルド時に選び、`_label` 1 本で運ぶ
- `bounds` は入れない — 津波の高さだけが該当し、境界は `height_label` で読める
- `text`/`text_en` は入れない — azarashi のレコード全体の 36% を占める
- `received_at` は `Parser::feed()` に与えた時刻を `report_time`/`onset_time` に反映する形で扱う

`unit`、津波高の境界型は現状持たない。これらが必要な用途では azarashi の出力を使う。

---

## 4. 参照

- azarashi 0.17.0 `azarashi/json/model.py` — `PROFILES`（数量の境界・センチネル）と
  `_time_value`（時刻の `status`）の原典
- azarashi 0.17.0 `azarashi/json/schemas/report-v1.schema.json` — JSON Schema
- azaraC `src/json/JsonSerializer*.cpp` / `src/json/JsonWriter.h` — 実装
- azaraC `test/json/test_json.cpp` — ヘッダ / `data` / 到着状態 / ラベル 3 値 / J-Alert
- azaraC `test/json/test_json_dcx_b1b4.cpp` — B1–B4 の D フィールド検証
- `qzss-specs/is-qzss-dcr-017.md` Table 4.1.2-21（Ta のセンチネル）、Table 4.1.2-23（津波高）

## 5. v1.0.x からの変更点

`schema_version` が無かった v1.0.x（リリース済みの最新は v1.0.3）から JSON を読む場合の
差分。読み手は `schema_version` の有無で分岐できる。下表の「現在」列は
`schema_version: 2` の出力（`CHANGELOG.md` の `[Unreleased]`）で、リリース済み v1.0.3 の
出力ではない。

| v1.0.x | 現在 |
|---|---|
| （版数なし） | `schema_version: 2` |
| `svid_label` | 削除（`svid` は PRN そのもの） |
| `msg_type_label` | 削除 |
| `detail`（MT43 本文） | `data` |
| MT44 のルート直下フィールド | `data` 配下 |
| `dcx_type`（数値）+ `dcx_type_label` | `dcx_type`（文字列） |
| `alert_identity{a2,a3,a4,ex1}` | 削除（`a2_country` 等と同値） |
| `detailed_info.a4_code` | 削除（`a4_hazard` と同値） |
| `detailed_info.dX:{raw,label}` | `dX` + `dX_label` |
| `jalert_target.prefecture_mode` | 削除（`prefectures` / `cities` の有無で決まる） |
| `jalert_target.prefecture_positions[]` + `prefecture_labels[]` | `jalert_target.prefectures[{position,label}]` |
| `jalert_target.city_codes[]` + `city_labels[]` | `jalert_target.cities[{code,label}]` |
| `entries[].arrival_day_offset` / `arrival_hour` / `arrival_min`（cat 5/6） | 削除（`arrival_time_raw` から導出、状態は `arrival_status`） |
| `entries[].arrival_hour`（cat 9） | `arrival_time_code` + `arrival_time_label` |
| 未定義・空ラベルの `""` | `null` / `""` を区別 |
| `unix: 0`（未解決） | `unix: null` |

上記以外のキー名（`note` / `code` / `label` / `region` / `region_label`、
`hazard_center` / `secondary_ellipse` / `main_ellipse` / `additional_area` / `ex11_raw` /
`sd_sdmt` / `sd_sdm` / `ex_vn` / `ex1_target_area` / `target_area_code` /
`a4_hazard_category` 系）は変わらない。`sd_sdmt` / `sd_sdm` は `data` の中へ移動した。
