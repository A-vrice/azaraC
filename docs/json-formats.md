# JSON出力仕様 — azaraCとazarashiの比較

azaraCの `JsonSerializer`（C++ / `Print&`）が出力するJSONと、基本的な参照実装であるazarashi（v0.17.1）の `azarashi.json.to_json_dict()` が出力するJSONは スキーマが異なる(azaraC側でazarashiよりも先に実装を始めたため)。
両者で対象が異なる（組込み向けの最小表現か、Python側の完全レコードか）ため、優劣ではなく用途に応じた選択になる。
本ドキュメントはazaraCのスキーマを示し、2ライブラリの差分を整理する。

ルートの `schema_version` は `2`。スキーマを変える変更のときのみ上げる。

本書の数値は `test/data/*_vectors.json` のNMEA 228通（MT=43 98通 / MT=44 130通）で測る（§2.6）。

---

## 1. azaraCのJSONスキーマ

直下の構造はMTによって変わる。本文（電文の内容）は常に `data` の中に入る。

```json
{"schema_version":2,"svid":186,"msg_type":43,"crc24":"0x00F92C3F",
 "report_classification":1,"report_classification_label":"最優先",
 "disaster_category":5,"disaster_category_label":"津波",
 "information_type":0,"information_type_label":"発表",
 "version":1,"report_time":{…},"data":{…}}

{"schema_version":2,"svid":184,"msg_type":44,"crc24":"0x00074DAD","data":{…}}
```

デコードに失敗した場合の `note` は以下の通り

| note | 詳細 |
|--|--|
| `invalid_mt43` | MT=43として解析に失敗 |
| `invalid_mt44` | MT=44として解析に失敗 |
| `unsupported_msg_type` | MTが43/44ではない、または当該型のシリアライザがビルド無効（例: `AZARAC_ENABLE_DCX_CAMF=0` のMT=44）。`crc24`フィールドの直後に`note`を出力しそれ以降のフィールドは出力なし。 |
| `unsupported_category`| 引き受けるシリアライザが無いカテゴリ（規格に無い7/13や、そのカテゴリの `AZARAC_ENABLE_*` が無効なビルド）の `Mt43Data` を直列化した場合。MT=43のメタ情報を出力するが`"data":{"note":"unsupported_category"}`となる。受信電文の復号では無効カテゴリは拒否される（`feed()` は `false`、`payload_type` は `Empty`）ので、このnoteは出ない |

### 1.1共通ヘッダ

| キー | 型 | 内容 |
|---|---|---|
| `schema_version` | int | 常に2 |
| `svid` | int | QZSS L1S PRN。`NmeaFramer` は受理したSatellite IDを `\| 0x80` で正規化（53→181, 54→182, 55–63→183–191）。64–99は6bit外なので拒否し、0–52は通すがPRN 128–180で契約外。`UbxFramer` は `ublox_qzss_svid_prn_map` で変換（1–4→183–186、7→189）し、表に無い `svId` は入力値のまま通す |
| `msg_type` | int | 43 / 44 |
| `crc24` | str | `"0x00F92C3F"`。azarashiの出力には無い |
| `data` | obj | 本文（§1.2 / §1.3）。失敗時は代わりに `note` |
| `note` | str | `invalid_mt43` / `invalid_mt44` / `unsupported_category` / `unsupported_msg_type`（`unsupported_category` のみ `data` の中） |

MT=43はこれに加えてDCRの報告ヘッダをルートに持つ: `report_classification`(+`_label`) / `disaster_category`(+`_label`) / `information_type`(+`_label`) / `version` / `report_time{month,day,hour,min,unix}`
MT=44のルートは `crc24` までで、Aフィールド・拡張部・`sd_sdmt` / `sd_sdm` はすべて `data` の中。
`svid` と `msg_type` のみラベルを持たない。

### 1.2 MT=43の `data`（カテゴリ別）

`(+_label)` は `_label`が付くキー。
津波の `notifications[].label` は定義表（EEW/震源と共有）が有効なときだけ解決し、EEW/震源/`AZARAC_TSUNAMI_NOTIFICATION_LABELS` がすべて無効な構成（AVRプリセットなど）では `null`。

| カテゴリ | ラベル | `data` のキー |
|---|---|---|
| 1 | 緊急地震速報 | `long_period_lower/upper`(+`_label`), `notifications[]{code,label}`, `quake_time`, `depth`(+`_label`), `magnitude`(+`_label`), `epicenter`(+`_label`), `intensity_lower/upper`(+`_label`), `regions[]{code,label}` |
| 2 | 震源 | `coords{lat_ns,lat_deg,lat_min,lat_sec,lon_ew,lon_deg,lon_min,lon_sec}`, `depth`(+`_label`), `magnitude`(+`_label`), `epicenter`(+`_label`), `notifications[]`, `quake_time` |
| 3 | 震度 | `entries[]{prefecture(+_label),intensity(+_label)}`, `quake_time` |
| 4 | 南海トラフ地震 | `info_code`(+`_label`), `page`, `total_page`, `truncated`, `text_utf8`（ページ集約後）/ `text_hex[]`（ページ単体） |
| 5 | 津波 | `warning_code`(+`_label`), `notifications[]{code,label}`, `entries[]{arrival_time_raw,arrival_status?,arrival_time?,height(+`_label`),height_lower,height_upper,region(+`_label`)}` |
| 6 | 北西太平洋津波 | `potential`(+`_label`), `entries[]{…cat5 と同形}` |
| 8 | 火山 | `ambiguity`(+`_label`), `activity_time`, `warning_code`(+`_label`), `volcano_name`(+`_label`), `local_govs[]{code,label}` |
| 9 | 降灰 | `activity_time`, `warning_type`(+`_label`), `volcano_name`(+`_label`), `entries[]{arrival_time_code,arrival_time_label,warning_code(+`_label`),local_gov(+`_label`)}` |
| 10 | 気象 | `warning_state`(+`_label`), `entries[]{region(+_label),sub_category(+_label)}` |
| 11 | 洪水 | `entries[]{region(+_label),warning_level(+_label)}` |
| 12 | 台風 | `coords`, `elapsed`(+`_label`), `intensity`(+`_label`), `max_gust`(+`_label`), `max_wind`(+`_label`), `number`(+`_label`), `pressure`(+`_label`), `ref_type`(+`_label`), `reference_time`, `scale`(+`_label`) |
| 14 | 海上 | `entries[]{region(+_label),warning_code(+_label)}` |

カテゴリ6の電文を検証しているのは `test/data/test_realdata_generated.cpp`。
洪水の予報区コードのように10桁を超えるコードは `uint64_t` のまま数値で出る。
各行はそのカテゴリの `AZARAC_ENABLE_*` が有効なビルドでの形。
無効なビルドでは復号器がそのカテゴリの電文を拒否する（`feed()` は `false`、`payload_type` は `Empty`、`unsupported_reason` は `DisabledAtCompileTime`）。
そのため、受信電文からこの表の形は出ない。
`unsupported_category` は手動で構築した `Mt43Data`（規格に無いカテゴリ7/13など）を直列化したときだけ出る（§1のnote表）。

南海トラフの `info_code_label` は日本語専用の表から引く（azarashiにEN版が無い）。
`AZARAC_LANG_JA=0` の構成では表ごと無いので `null` になる（生コードの `info_code` は残る）。

津波の到着時刻は `arrival_time_raw`（12bit: day_offset 1 + hour 5 + min 6）だけを残す。
`arrival_time` は解決できたときだけオブジェクトとなり、できないときは `null`となる。
解決できなかった理由は `arrival_status` に出る（解決時の出力はなし）

| 失敗理由(上から判定) | `arrival_status` | `arrival_time` |
|---|---|---|
| `hour == 31 && min == 63`（cat 5） | `"arrival_estimated"` | `null` |
| `hour == 31 && min == 63`（cat 6） | `"arrived_or_unknown"` | `null` |
| `day_offset == 0 && hour == 30 && min == 62`（cat 5のみ） | `"no_information"` | `null` |
| `raw == 0`、または `hour > 23`、または `min > 59` | `"unrecognized_code"` | `null` |
| 上記以外 | キーを出さない | `{month,day,hour,min,unix}` |

判定順はazarashiと同じ。
範囲外チェックを先に置くと `hour == 30` の `no_information` が到達不能になる。
`raw == 0` はazarashiが「同日00:00」に解決するのに対しazaraCの `resolveArrivalTime()` は空を返すため `unrecognized_code` になる

### 1.3 MT=44の `data` のキー

テスト電文130通の `data` 内のキー。電文は `test/data/dcx_vectors.json` のもので、すべてA17=0である。

Aフィールド: `dcx_type`（`"NULL"` / `"L_ALERT"` / `"J_ALERT"` / `"LOCAL_GOV"` / `"OUTSIDE_JAPAN"` / `"UNKNOWN"`）、`a1_msg_type`, `a2_country`(+`_label`), `a3_provider`(+`_label`), `a4_hazard` / `a4_hazard_category` / `a4_hazard_type` / `a4_hazard_definition`。
`a5_severity`(+`_label`), `a6_onset_week`(+`_label`), `a7_onset_minute`, `a8_duration`(+`_label`), `onset_time`。
`a9_type_of_library`(+`_label`), `a10_library_version`(+`_label`), `a11_guidance`(+`_label`), `a11_guidance_list_b_label`。
`a17_type_of_specific_settings`(+`_label`), `a18_specific_settings`。

条件付きブロック（該当時のみ出現）:

| ブロック | 条件 | キー |
|---|---|---|
| `main_ellipse` | A12–A16あり | `lat_deg`, `lon_deg`, `semi_major_km`, `semi_minor_km`, `azimuth_deg` |
| `main_ellipse.b1_refinement` | B1 | `c1_lat_offset_deg`, `c2_lon_offset_deg`, `c3_refined_semi_major_km`, `c4_refined_semi_minor_km` |
| `hazard_center` | B2 | `c5_raw`, `c6_raw`, `delta_lat_deg`, `delta_lon_deg` |
| `secondary_ellipse` | B3 | `c7_shift`, `c8_homothetic`, `c9_bearing`, `c10_guidance`(+`_label`), `c10_guidance_code` |
| `detailed_info` | B4 | a4に応じたDフィールド（§1.4）。レイアウトが無ければ `{}` |
| `jalert_target` | J-Alert | `prefectures[]{position,label}`（都道府県）/ `cities[]{code,label}`（市区町村）。どちらか一方だけが出る |
| `additional_area` | EX2–EX7（地方自治体） | `head_to_area`, `ellipse{lat_deg,lon_deg,semi_major_km,semi_minor_km,azimuth_deg}` |
| `ex1_target_area`(+`_label`), `target_area_code` | L-Alert | — |
| `ex8_area_type` | J-Alert | — |
| `ex11_raw` | 国外 | — |
| `ex_vn` | 拡張部あり | L-Alert/地方自治体と国外ではdata直下、J-Alertでは `jalert_target.ex_vn`（`jalert_target` の最後のキー） |
| `sd_sdmt`, `sd_sdm` | 常時（MT=44の最後） | — |

`main_ellipse` は130通中8通に出て、いずれも `b1_refinement` を伴う（A17=0でもC1–C4が非ゼロならB1として出る）。
`hazard_center`（B2）・`secondary_ellipse`（B3）・`detailed_info`（B4）・`additional_area`（EX2–EX7）を含む電文はテストデータに無い。
`test/json/test_json_dcx_b1b4.cpp` の合成メッセージで検証している。

`jalert_target` の `position` は JIS都道府県コード（1–47、1始まり）。
`cities[].code` はEX1の市町村コード（仕様と同じ値）。どちらの配列も `{code|position, label}` のオブジェクト配列で、並列配列ではない。

### 1.4 Dフィールドの形

B4（A17=11）のD1–D36は `"dX_name": 生値` と `"dX_name_label": 表示文字列` の2キーで出る。

```json
"detailed_info": {
  "d1_magnitude": 6,      "d1_magnitude_label": "7.0-7.9 - Major",
  "d2_seismic_coeff": 7,  "d2_seismic_coeff_label": "7",
  "d3_azimuth": 5,        "d3_azimuth_label": "112.5°",
  "d4_vector_length": 9,  "d4_vector_length_label": "30",
  "d5_wave_height": 6,    "d5_wave_height_label": "5.0m < H ≤ 10.0m"
}
```

キーはD番号の昇順で出る（該当しないものは飛ばす）。

a4のハザード種別をもとに「どのDフィールドが意味を持つか」が決まり、該当しないものは出力なし。
よってキーの欠落と `0` は意味的に区別される。
Dフィールドを持たないハザード（例a4=1）では`detailed_info` が空オブジェクト `{}` になる（B4が存在した事実は残る）。

`d1_magnitude` はrawが4bit（0–15）だが表は0–8しか持たない。
表外のraw（例15）は `d1_magnitude_label: null` になる。
azarashiは同コードを `status: "undefined"` として区別する。

### 1.5ラベルの3値規則

キーは常に出力する（キーごと省くことはしない）。

| 状況 | 出力 |
|---|---|
| 表を引いたが該当コードが無い（未定義・範囲外） | `"x_label": null` |
| 表に該当し、ラベルが空文字列（例: A11国際ライブラリcode 0） | `"x_label": ""` |
| 表に該当し、ラベルがある | `"x_label": "…"` |
| この構成にラベル表自体が無い（`AZARAC_LANG_JA=0` かつ `AZARAC_LANG_EN=0`） | `"x_label": null` |
| この構成に日本語専用の表が無い（`AZARAC_LANG_JA=0`。azarashiにEN版が無い表: 南海トラフの `info_code_label`） | `"x_label": null` |
| `a11_guidance_label` のみ: A9=1かつA2≠111（国/地域ライブラリが日本以外に無い） | `"a11_guidance_label": null` / `"a11_guidance_list_b_label": null` |

`AZARAC_LANG_JA=1` かつ `AZARAC_LANG_EN=1` の構成では、文字列リテラルのキーを持つ `_label` の後に `_label_en` も出力される。
`_label_en` を持たないのは汎用キー（`keys::label` / `keys::region_label`）で出力するラベル（`notifications[].label`, `regions[].label`, `prefectures[].label`, `cities[].label`, `local_govs[].label`, `entries[].region_label`）である。
固定の文字列リテラルキー（`AZARAC_LABEL`）は配列要素でも `_label_en` を併記する（例: 震度の `entries[].intensity_label`）。
ラベルの言語選択は §1.6を参照。

### 1.6ラベルの言語選択

ラベルの言語は `AZARAC_LANG_JA`（既定1）と `AZARAC_LANG_EN`（既定0）で選ぶ。

両方が1のときは日本語を優先し、その項目に日本語テーブルが無ければ代わりに英語を使う。
`AZARAC_LANG_JA=0 / AZARAC_LANG_EN=1` では英語ラベルを出力する。
英語テーブルを持たない項目（例: 南海トラフの情報番号）は `AZARAC_LANG_JA=1` の間だけ日本語で出る。
`AZARAC_LANG_JA=0` ではその日本語表がコンパイルされないので `null` になる（生コードは残る）。
どちらも0のときは原則ラベルを出力しない。
欠落時は `null`、定義済みで空文字列のラベルは `""` として出力される。
ただし言語非依存表（北西太平洋津波の3表など）は値があれば0/0でも解決して返す。

英語ラベルはazarashi 0.17.1の定義テーブルに由来する。
`AZARAC_LANG_EN` で有効になるのは `_en` という接尾辞のヘッダで、対応する日本語表と対で生成される。

逆に日本語版を持たない英語専用表（北西太平洋津波の `potential` / `height` / `region`）は言語非依存で、`AZARAC_LANG_EN` の設定に関係なく常に出力される。
これはCAMF自体が英語で日本語メッセージの定義が存在しないためで、同じ仕様を参照する他のテーブルも同様の処理がなされる場合がある。
（定義テーブルの `_en` のうち、言語切替の対象になるのは対応する日本語テーブルが存在する場合のみ）

両方1のときの併記: `AZARAC_LANG_JA=1` かつ `AZARAC_LANG_EN=1` のとき、文字列リテラルのキーを持つ `_label` フィールドには `_label_en` が併記される。
`_label` は日本語優先（無ければ英語）、`_label_en` は常に英語である。

```json
{ "depth": 60, "depth_label": "60km", "depth_label_en": "60 km" }
```

配列要素のうち、汎用キー（`notifications[].label` / `regions[].label` / `prefectures[].label` / `cities[].label` / `local_govs[].label` / `entries[].region_label`）の要素は `_label_en` を持たない（要素ごとにコード体系が異なり、固定キー名では併記できないため）。
逆に固定の文字列リテラルキー（`AZARAC_LABEL`）は配列要素でも `_label_en` を併記する（例: 震度の `entries[].intensity_label`）。
要素ごとに言語を選びたい場合は `AZARAC_LANG_JA=0 / AZARAC_LANG_EN=1` 構成を使う。

数量フィールド（`depth` / `magnitude` / `pressure` / `max_wind` / `max_gust` / `elapsed` / `number`）についても `_label` / `_label_en` が含まれる。
生のコード値だけでは意味が取れない値もある（以下の表参照）。

| コード | ラベル | 意味 |
|---|---|---|
| `depth` 501 | `500kmより深い` / `Deeper than 500 km` | 範囲の境界 |
| `magnitude` 101 | `10.0より大きい` / `Over 10.0` | 範囲の境界 |
| `magnitude` 126（震源情報のみ） | `不明(8.0より大きい)` / `Unknown (Over 8.0)` | 範囲の境界 |
| `depth` 511 / `magnitude` 127 | `不明` / `Unknown` | センチネル |
| `max_wind` 0 / `max_gust` 0 | `不明` / `Unknown` | センチネル |

センチネルは全フィールド共通ではなく、例えば `depth` の0は `0km`、`pressure` の0は `0hPa`、`elapsed` の0は `0時間後` で、それぞれ実値として意味を持つ。
ただし `number` の0は `typhoon_number` 表（1スタート）に無いため `number_label` は `null` となる。

`AZARAC_LANG_EN=0`（既定）では `_label_en` は出力されない。
`AZARAC_LANG_JA=0 / AZARAC_LANG_EN=1` の場合、`_label` 自体がすべて英語になるため `_label_en` ではなく `_label` に英語が出力される。
`_label_en` が出るのは日本語/英語ともに有効にした構成のみである。

---

## 2. azarashiとの対応

### 2.1レコード封筒

| 概念 | azarashi 0.17.1 | azaraC | 差 |
|---|---|---|---|
| スキーマ | `schema_version: 2`（0.17.1のJSON v2） | `schema_version: 2` | 値は同じだが版数は独立。azarashiのv2とazaraCのv2は別々に定めた版数で、意味は対応しない |
| バージョン（DCRの `Vn`） | `data.version: {status, value}` | `version: 1`（MT=43のみ） | azaraCはDCRの `Vn` だけを `version` として運ぶ |
| 種別 | `type: "qzss.dcr.tsunami"` | `msg_type: 43` + `disaster_category` | azaraCは数値の組合せ |
| 訓練/試験 | `is_test: true` | なし | azaraCでは利用側が `report_classification == 7` で判定する |
| 受信時刻 | `reception.at: "...Z"` | なし（`report_time.unix` は `Parser` に時刻を渡さないと `null`） | azaraCは受信時刻を運ばない |
| 衛星 | `reception.satellite: {system, prn}` | `svid` | azaraCはPRNを1つの数値で運ぶ。ラベルは無い |
| 元電文 | `reception.nmea` | なし | azaraCは再生成しない |
| 電文識別 | `message_id`, `series: {lifecycle, key}` | なし | azaraCは `crc24` とフィールド値で識別する |
| 本文 | `texts: {ja, en}` | 南海トラフのみ（`text_utf8`、ページ単体では `text_hex[]`） | azaraCは他カテゴリで本文を生成しない |
| ペイロード | `data`（種別ごと） | `data`（種別ごと） | 同じ名前・同じ位置 |
| 検査値 | なし | `crc24` | azaraCのみ |

### 2.2コード値の表し方

**azarashi** — `status` / `code` / `table` / `labels` の4項目（`azarashi/json/tables.py`）。

```json
{"status": "valid", "code": "610", "table": "qzss.dcr.tsunami_forecast_region",
 "labels": {"ja": "高知県", "en": "Kochi Prefecture"}}
```

- `table` がコード体系を一意に決める（`qzss.dcr.*`, `camf.a5_severity`, `camf.a3_provider_identifier.country_71` …）
- `code` は十進文字列。大きい数（洪水の12桁等）も落ちない
- `status` は4値で「そのまま使えるか」を示す: `valid`（定義どおり）／`assumed`（仮定値。緊急地震速報の震源）／`special`（空値・センチネル。長周期のcode 0、A3 providerの0、C10と国際ライブラリList A/Bのcode 0など）／`undefined`（表に無いコード）
- `valid` と `special` にはたいてい `labels` が付く（センチネルにも名前がある。例 `Not used`、`指示なし` / `No instruction`、`該当情報なし` / `No data`）。
  `undefined` は `labels: {}` で、コード番号そのものは `code` に残る
- `ja`/`en` は併記される（両方ある場合）

**azaraC** — 数値とラベルの並置。

```json
{"region": 610, "region_label": "高知県"}
```

- キー名が `region` なので体系は文脈依存（`table` に相当する情報はキー名とカテゴリだけ）
- 値は数値。洪水のような大きな数は `uint64_t` で2進数のまま
- ラベルは `_label` サフィックスのキーで、言語はビルド時に決定
- 未定義コードは `null`、定義済みの空ラベルは `""` → 区別できる

| 状況 | azarashi 0.17.1 | azaraC |
|---|---|---|
| 表に無いコード | `status:"undefined"`, `labels:{}`, `code` は保持 | `"_label": null`, 元コードは数値キーに残る |
| 定義済みの空値・センチネル | `status:"special"` + `labels`（`Not used` / `指示なし` / `No data` 等） | `_label` は定義表の文字列。表が `""` を持つ2表（国際List A/Bのcode 0）だけ `""` |
| provider code 0（Fiji, A2=71） | `status:"special"`, `labels:{en:"Not used"}` | 手書き表に0が無く `a3_provider_label: null` |
| 表そのものが無い | `status:"undefined"` | `"_label": null` |

`a11_guidance_label` は元コードA11と、A9/A2で選ぶライブラリで決まる。A11の表はIS-QZSS-DCX-004 §4.2.3.11(1) Table 4.2-15（日本）/ (2) Table 4.2-16（国際）、国際ライブラリはEWSS CAMF v1.2 §3.5.3 / §11。§4.2.3.9 Table 4.2-12はA9の選択表で、A2による国別ライブラリ選択はCAMF v1.2 §3.5.1。
A11は10bitだが、国際ライブラリ（A9=0）ではEWSS CAMF v1.2 §3.5.3 / §11のとおり List A 5bit（`a11 >> 5`）とList B 5bit（`a11 & 0x1F`）の2コード に分かれ、それぞれ別の表を引く。
List Bのラベルは常に出力する `a11_guidance_list_b_label`に出る

| A9 | A2 | `a11_guidance_label` が引く表 | `a11_guidance_list_b_label` |
|---|---|---|---|
| 0 | — | International library List A（`a11 >> 5`、0–31を全定義） | International library List B（`a11 & 0x1F`）。29/30は表に無く `null` |
| 1 | 111 | Japanese library（A11の10bitをそのまま鍵にする結合表） | 対応する表が無いため `null` |
| 1 | ≠111 | 無し → `null` | `null` |

CAMFの表は英語のみなので `_label_en` は出ない。
List A / List Bのcode 0は定義済みの空文字列 `""`。
A11の10bitすべてが表の定義域なので「範囲外で `null`」は起きない（List Bは欠落コード29/30が `null`）

**A11国際ライブラリのcode 0の表記。**
azarashiのJSONは、国際ライブラリのList A / List B（およびC10）のcode 0を `status:"special"` + `labels:{en:"No instruction"}` と表記する（`azarashi/json/tables.py` が定義表の `0: ''` を `No instruction` で上書きする）。
azaraCは定義表の値である `""`（定義済みの空）を出す。
CAMF Issue 1.2はこのコードを §3.5.3の本文で「Empty values are provided for each list (bit sequence 'null' in each list) … it is still possible to broadcast an alert message without any instruction」＝空値と述べ、`no instruction` と明記するのはC10の §3.7.3.4だけ（List A / List Bの表とAnnex §11では `reserved`）。
仕様が名前を1つに定めていないため、azaraCは空値（`""`）を出す。
両者は同じ意味の別表記として扱える。

実データ130通（`test/data/dcx_vectors.json`）の内訳はA9=1 / A2=111が124通（A11=0が81、136が41、128が1、134が1）。
A9=1 / A2=71が5通、A9=0 / A2=111（Null Message）が1通。
出力は3つに分かれる:

| `a11_guidance_label` の出力 | 通数 | 内訳 |
|---|---|---|
| ラベルあり | 124 | 国内表A11=0（81、`指示なし` / `_label_en` は `No instruction`）・136（41）・128（1）・134（1）。例: 136 =「これは、Jアラートのテストです。」 |
| `""`（定義済みの空ラベル） | 1 | 国際表List A code 0（Null Message、A9=0 / A2=111）。`a11_guidance_list_b_label` もList B 0で `""` |
| `null`（表が無い） | 5 | A9=1 / A2≠111（71）。表そのものが存在しない |

124 + 1 + 5 = 130。
国内表（A9=1 / A2=111）を通る124通の `a11_guidance_list_b_label` はすべて `null`（日本の表はList A / List Bを10bitの結合表で持つため）。

### 2.3数量（数値＋単位）

**azarashi** — コードオブジェクト（§2.2）に形と `unit` が加わる（`azarashi/json/model.py` の `PROFILES`）。

| 形 | 内容 | 例 |
|---|---|---|
| `value` | `value` + `unit` | `depth` = `{"status":"valid","code":"10","table":"qzss.dcr.depth_of_hypocenter","labels":{…},"value":10,"unit":"km"}` |
| `range` | `range{lower,upper}` + `unit` | 津波の高さ `3m` = `{"range":{"lower":1,"upper":3},"unit":"m"}`（1m超〜3m以下） |
| 値なし | `status`（`assumed` / `special` / `undefined`）+ `value: null` | 深さ511、長周期のcode 0 |

**azaraC** — 形（`value` / `range`）の区別も `unit` も持たず、生値を出力。
ただし数量フィールドには `_label` が付き、境界（`500kmより深い`）とセンチネル（`不明`）は区別される。

| 電文 | フィールド | azarashi | azaraC | 落ちるもの |
|---|---|---|---|---|
| EEW | `depth` | `value 10, unit km` | `"depth": 10` + `depth_label: "10km"` | 単位（可読） |
| EEW | `magnitude` | `value 7.2` | `"magnitude": 72` + `magnitude_label: "7.2"` | 実数化（生コード72 = 7.2） |
| Tsunami | `height` | `range 1<x≤3, unit m` | `"height": 3` + `height_label: "3m"` + `"height_lower": 1.0` + `"height_upper": 3.0` | 単位（可読）。範囲は出る |
| Typhoon | `central_pressure` | `value 955, unit hPa` | `"pressure": 955` + `pressure_label: "955hPa"` | 単位（可読） |
| Typhoon | `maximum_wind_speed` | `value 40, unit m/s` | `"max_wind": 40` + `max_wind_label: "40m/s"` | 単位（可読） |
| Typhoon | `elapsed_time` | `value 0, unit h` | `"elapsed": 0` + `elapsed_label: "0時間後"` | 単位（可読） |

`_label` / `_label_en` により単位とセンチネルは人間には読めるが、値自体は生コードのままで、単位は `_label` の文字列にしか無い。
機械可読な境界を持つのは津波の高さだけで、`height_lower` / `height_upper`（m）として出る。
特に津波の高さは注意が必要で、`3m` は「1m超〜3m以下」という *範囲* であり単一値ではない。
この境界は仕様の表には無く（Table 4.1.2-23は `1m` / `3m` / … としか書かない）、JMAの階級区分をazarashi 0.17.1が `PROFILES["qzss.dcr.tsunami_height"]` の `(1, 3)` として持つ。

| `height`（cat 5） | 境界（下端は開・上端は閉） | `height_lower` / `height_upper` | `height_label` |
|---|---|---|---|
| 1 | h < 0.2 | `null` / `0.2` | `0.2m未満` |
| 2 | 0.2 < h ≤ 1 | `0.2` / `1.0` | `1m` |
| 3 | 1 < h ≤ 3 | `1.0` / `3.0` | `3m` |
| 4 | 3 < h ≤ 5 | `3.0` / `5.0` | `5m` |
| 5 | 5 < h ≤ 10 | `5.0` / `10.0` | `10m` |
| 6 | 10 < h | `10.0` / `null` | `10m超` |
| 13 / 14 / 15 | 境界なし | `null` / `null` | `該当情報なし` / `不明` / `その他の津波の高さ` |

同じ境界をcat 6（北西太平洋津波）も `height_lower` / `height_upper` で出す。
こちらは `height_label` 自体が範囲（`0.3m~1m` / `3m~5m` / …）である。
`508` は上限なし（`height_upper: null`）で、`509`（Huge）/ `510`（High）/ `511`（Unknown）は境界を持たず両方 `null` になる。

### 2.4時刻

**azarashi** — `status` / `value` / `precision` / `source` の4項目（`azarashi/json/model.py` の `_time_value`）。`basis` は0.17.1で無くなった。

- `status` は §2.2と同じ4値。
  `valid` なら `value` がUTC日時。
  センチネルは `special` で `value: null` とし、意味は `labels` が運ぶ（例 `津波到達中と推測` / `Tsunami arrival expected`）
- `precision` は `value` の粒度（`minute` など）
- `source` は常にあり、電文が運んだ生の分解値を持つ。値は `{month, day, hour, minute}` で、DCXのonsetは `{week, minute_of_week}` です

例（`$QZQSM,56,53ADA8BECF…`、Ta = 2047 = hour 31, min 63の国内津波）:

```json
{"status": "special", "value": null,
 "labels": {"ja": "津波到達中と推測", "en": "Tsunami arrival expected"},
 "source": {"day": 0, "hour": 31, "minute": 63}}
```

**azaraC** — `{month, day, hour, min, unix}` の5項目。
`unix` は `unix_time == 0`（未解決）のとき **`null`**、解決済みのときは数値。
未解決（`report_unix` が2000-01-01未満）でも `month` / `day` / `hour` / `min` は生値のまま保持し、`unix` だけが `null`。範囲外の `day` / `hour` / `min` は0、`month` は与えられた値のまま。

- 津波の到着時刻は §1.2の `arrival_status` で状態を明示する。
  例（`test/data/test_realdata_generated.cpp` の `$QZQSM,56,53ADA8BECF…`、Ta = 2047 = hour 31, min 63）:

  ```
  azarashi:  "arrival": {"status": "special", "value": null, "labels": {…}, "source": {"day": 0, "hour": 31, "minute": 63}}
  azaraC: "arrival_time_raw": 2047, "arrival_status": "arrival_estimated", "arrival_time": null
  ```

  3つのセンチネル（`31:63` / `30:62` / 不正値）は全ゼロの `arrival_time` に潰れない。
  状態は `arrival_status` に出る。`arrival_time_raw` は導出前の生値として残る。
- DCXの `onset_time` はA7=0でも「未使用」と「解決できなかった」を区別しない（`unix: null` は両方で出る）。
  azarashiはv1で `not_used` という専用statusを持っていたが、v2は4値に統一された。

| 項目 | azarashi | azaraC |
|---|---|---|
| `report_time` | `status:"valid"` + `value`（UTC日時）+ `precision:"minute"` + `source`。年は受信時刻から補う（v1の `basis` は無い） | `Parser::feed()` に渡した時刻で解決。CLIは0を渡すため `unix` は `null` |
| DCX `onset` | `value`（UTC日時）+ `source:{week, minute_of_week}` | 週 + 週内分から解決（同上。CLIでは `null`） |
| 火山の曖昧さ | `activity_time_ambiguity`（コードオブジェクト）を併記し、`Du` に応じて `activity_time` の有効範囲を解釈 | `ambiguity` + `ambiguity_label`（`Du` の0–7を明示）。`activity_time` の有効範囲は解釈しない |

### 2.5繰り返し項目の組み方

**azarashi** — 1件1オブジェクト。並列配列を作らない。

```json
"forecasts": [
  {"region": {…}, "height": {…}, "arrival": {…}}
]
```

**azaraC** — `entries[]` などの数値キーと `_label` の並置、およびJ-Alertのオブジェクト配列の2通り。

```json
"entries": [{"arrival_time_raw": 488, "arrival_time": {…}, "height": 3,
             "region": 600, "region_label": "…"}]
"jalert_target": {"prefectures": [{"position": 1, "label": "北海道"},
                                  {"position": 2, "label": "青森県"}]}
```

`entries[]` の要素は平坦（`{height, height_label, height_lower, height_upper}` の並置）のままで、ネストした `{code, label}` オブジェクトにはしない。
唯一のオブジェクト配列は `jalert_target` の `prefectures` / `cities`。

プロトコル上の位置は「どのオブジェクト配列か」で決まるので、 `prefectures` / `cities` のどちらが出たか（および `data.ex8_area_type`）で読み分ける。
`position` はJIS都道府県コード（1–47、1始まり）。
azarashiも0.17.1から同じ1–47を `target_regions[].code` として出す（`qzss.dcx.ex9_target_area_code_list`）。
同じ電文で両者は一致する（v1は `qzss.dcx.prefecture_bit` の下位から0始まりのビット位置だった）。

EX9の元64ビット整数はazarashiは出さない（`reception.nmea` に残る）。
azaraCは `prefectures` / `cities` に展開する。

### 2.6サイズと入れ子の深さ

`test/data/dcr_vectors.json` + `test/data/dcx_vectors.json` のNMEA 228通 （MT=43 98 / MT=44 130。すべてazaraCが受理）の合計（区切り文字なしのコンパクト表現、 UTF-8バイト）。
両者を同じ計量関数で測る。
azarashiは `azarashi.json.to_json_dict()` の完全レコード。

| 対象 | バイト | 1レコード平均 |
|---|---|---|
| azarashiレコード全体 | 613,976 | 2,692 |
| azarashi `data` のみ | 371,812 | 1,630 |
| azaraCレコード全体 | 260,750 | 1,143 |
| azaraC `data` のみ | 203,609 | 893 |

同じ228通を `make -C test decode`（`test/decode_to_json --raw`）と `azarashi.json.to_json_dict()` に通し、それぞれ `json.dumps(…, separators=(',',':'))` で測って再現できる（津波の `height_lower` / `height_upper`（§2.3）を含む）。

azarashiのレコード全体の内訳は `data` が61%、`texts` が25%。
`data` のうち `labels` オブジェクトが31%、`table` のキー＋値が25%（92,706 B、2,416回）。
`table` の最多は `qzss.dcx.ex9_target_area_code_list` の430回で、同じ体系名を都道府県の数だけ繰り返す。

入れ子の深さ（オブジェクト／配列の段数、ルートを1とする）。
同じ228通のカテゴリごとの最大値。
azarashiは封筒（`schema_version` / `type` / `message_id` / `series` / `reception`（`at`/`satellite`/`nmea`）/ `texts` / `data` …）を含む完全レコード（`azarashi.json.to_json_dict()`）で測る。
`get_params()` はヘッダを除外するため使わない。

| 電文 | azarashi | azaraC |
|---|---|---|
| 津波 | 7 | 6 |
| 緊急地震速報 | 6 | 5 |
| 震源 | 6 | 5 |
| 震度 | 7 | 5 |
| 火山 | 6 | 5 |
| 降灰 | 7 | 5 |
| 気象 | 7 | 5 |
| 洪水 | 7 | 5 |
| 南海トラフ | 5 | 4 |
| L-Alert | 7 | 5 |
| J-Alert | 6 | 6 |
| 国外 | 7 | 5 |
| Null | 4 | 4 |

差は主に出力の階層表現にある。
azarashiはコードを `{status, code, table, labels}` で1段深くし、MT=44ではazaraCの `jalert_target.prefectures[]` / `cities[]` が オブジェクト配列の分だけ1段深くなる（4 → 5）。
両者が釣り合うJ-Alertでは同じ深さになる。

## 3. 落ちる情報と設計方針

azaraCが出さないもの: コード体系の明示（`table`）、単位（`unit`）、境界の入れ子（azarashiの `range{lower,upper}`）。
マグニチュードの実数値、受信時刻（`reception.at`）、訓練/試験フラグ（`is_test`）。
電文識別（`message_id` / `series`）、本文（`texts`）、DCX `onset_time` の「未使用」と「未解決」の区別。

失うのは主にメタ情報で、電文が運んだコード値そのものはほぼ全て残る（`arrival_time_raw`、生の `magnitude`、`ambiguity`、`sd_sdm` 等）。
未定義コードは `_label: null`、時刻の状態は `unix: null` と `arrival_status` で表す。

### azarashiとの既知の意味論差（仕様準拠電文では実害なし）

- **EEW仮定震源**: De=10かつMa=10の「仮定震源」をazarashiは `status:"assumed"` で区別するが、azaraCは区別しない（`depth`/`magnitude` の生コードは残る）。
- **火山 `activity_time` の曖昧さ（Du）**: azarashiはDu≥6で時刻をNone、Du≥5で時分を0にするが、azaraCはDuを `activity_time` に適用しない（`ambiguity` は別途出力）。Du≥6でも `unix` が非nullで出るため、消費側は `ambiguity` を見て判断すること。
- **津波 `Ta=0`**: azarashiは00:00を有効な到着時刻として扱うが、azaraCは `Ta` raw=0を未定義コードとして `null` 扱いにする。
- **暦に存在しない日付**: 2/30・4/31・平年2/29等はazarashiが電文拒否（2/29は最寄り閏年）するのに対し、azaraCは `unix: null` の未解決とする（生フィールドは保持。黙って別月日へ正規化しない）。
- **DCX `Vn`/`A1`**: azarashi準拠でバージョン無検証（将来バージョンでもv1配置で復号しうる）。MT=43の `ver!=1` 拒否とは非対称な設計判断。
- **楕円半径code 29**: azaraCは仕様表（Table 4.2-17）の1367.116 km（1367116 m）を使う。azarashiは対数式の丸めで1367.117 kmになり1 m異なる（他31コードは一致）。
- **南海トラフの同時追跡**: `AZARAC_NANKAI_BUFFERS`（ホスト既定2）を超える事象が同時進行すると集約できない限界がある（APIリファレンス参照）。

方針: 形はazaraCのまま、azarashiの意味論のうちazaraCが落としている部分だけを取り込む。
azarashiの出力（`table`/`labels`/`range`）をそのまま真似るとサイズが2.35倍になり組込みでの利点を失う。

- `table` は入れない（v1の `scheme`） — 体系はキー名（`region` → 津波の予報区、北西太平洋の沿岸区域、火山の自治体、…）とカテゴリで決まり、冗長性を払う価値が無い
- `labels` は入れない — 言語はビルド時に選び、`_label` 1本で運ぶ
- `range` の入れ子は入れない — 境界を持つのは津波の高さだけで、`height_lower` / `height_upper` の2キー（m、境界なしは `null`）で出す。
  azarashiの `range{lower,upper}` + `unit` は真似ない
- `texts` は入れない — azarashiのレコード全体の25% を占める
- `reception.at` は `Parser::feed()` に与えた時刻を `report_time`/`onset_time` に反映する形で扱う

`unit` は持たない（単位は `_label` の文字列にしか無い）。
境界型は津波の高さの `height_lower` / `height_upper` だけ。
これら以外が必要な用途ではazarashiの出力を使う。

---

## 4. v1.0.xからの変更点

`schema_version` が無かったv1.0.x（リリース済みの最新はv1.0.3）からJSONを読む場合の差分。
読み手は `schema_version` の有無で分岐できる。
下表の「現在」列は `schema_version: 2` の出力（`CHANGELOG.md` の `[2.0.0]`）で、リリース済みv1.0.3の出力ではない。

| v1.0.x | 現在 |
|---|---|
| （版数なし） | `schema_version: 2` |
| `svid_label` | 削除（`svid` はPRNそのもの） |
| `msg_type_label` | 削除 |
| `detail`（MT=43本文） | `data` |
| MT=44のルート直下フィールド | `data` 配下 |
| `dcx_type`（数値）+ `dcx_type_label` | `dcx_type`（文字列） |
| `alert_identity{a2,a3,a4,ex1}` | 削除（`a2_country` 等と同値） |
| `detailed_info.a4_code` | 削除（`a4_hazard` と同値） |
| `detailed_info.dX:{raw,label}` | `dX` + `dX_label` |
| `jalert_target.prefecture_mode` | 削除（`prefectures` / `cities` の有無で決まる） |
| `jalert_target.prefecture_positions[]` + `prefecture_labels[]` | `jalert_target.prefectures[{position,label}]` |
| `jalert_target.city_codes[]` + `city_labels[]` | `jalert_target.cities[{code,label}]` |
| `entries[].arrival_day_offset` / `arrival_hour` / `arrival_min`（cat 5/6） | 削除（`arrival_time_raw` から導出、状態は `arrival_status`） |
| `entries[].height`（生コードのみ、cat 5/6） | `height` + `height_lower` / `height_upper`（境界、m。境界なしは `null`） |
| `entries[].arrival_hour`（cat 9） | `arrival_time_code` + `arrival_time_label` |
| 未定義・空ラベルの `""` | `null` / `""` を区別 |
| `unix: 0`（未解決） | `unix: null` |

上記以外のキー名（`note` / `code` / `label` / `region` / `region_label`、`hazard_center` / `secondary_ellipse` / `main_ellipse` / `additional_area` /
`ex11_raw` / `sd_sdmt` / `sd_sdm` / `ex_vn` / `ex1_target_area` / `target_area_code` / `a4_hazard_category` 系）は変わらない。
`sd_sdmt` / `sd_sdm` は `data` の中へ移動した。
