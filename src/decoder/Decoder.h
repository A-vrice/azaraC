#pragma once

#include "../azaraC_config.h"
#include "../framer/Frame.h"
#include "../Message.h"

namespace azaraC {
namespace internal {

class Decoder {
public:
    bool decode(const Frame& frame, Message& out, uint32_t report_unix = 0);

    // CRC-24Q (IS-QZSS-L1S-009 §4.1.1.3)。data[0] の MSB から bit_len ビットを処理する。
    // Parser も同じ実装を使う（手順③ の照合対象 MT～VN = bit 8..219 の digest）。
    static uint32_t crc24q(const uint8_t* data, uint16_t bit_len);

    // 手順③ の照合対象（MT～VN = frame bit 8..219）の digest。
    // プリアンブル（bit 0..7）と Reserved（bit 220..225）は範囲外。
    // QZS 事務局回答: 照合範囲「MT および CAMF〜EM」に SDMT・SDM・Reserved を含めない。
    // MT=44 は SD（SDMT 1 bit + SDM 9 bit = frame bit 14..23）をゼロにしてから取る。
    // bits が非 const なのは、対象 2 バイトを外して戻すだけでフレームのコピーを作らないため（呼び出しの前後で内容が変わらない）。
    static uint32_t messageIdentity(uint8_t* bits);

protected:
    // 日付変換（西暦日 ↔ 1970-01-01 からの日数）
    static void civil_from_days(uint32_t days_since_1970, uint32_t& y, uint32_t& m, uint32_t& d);
    static uint32_t days_from_civil(uint32_t y, uint32_t m, uint32_t d);

    // ビット抽出（MSB-first、フレーム先頭から 0 始まり）
    uint32_t getBits(const uint8_t* buf, uint16_t start, uint8_t len);
    uint64_t getBits64(const uint8_t* buf, uint16_t start, uint8_t len);

    // 41 bit フィールドから LatLon（lat_ns:1, lat_d:7, lat_m:6, lat_s:6, lon_ew:1, lon_d:8, lon_m:6, lon_s:6）
    LatLon  extractLatLon(const uint8_t* buf, uint16_t start);

    // day(5)+hour(5)+min(6)=16 bit のサブフィールド -> TimeFields report_unix: GPS/SNTP の UNIX 時刻。0 は未解決。
    TimeFields extractDHM(const uint8_t* buf, uint16_t start, uint32_t report_unix);

    // report_unix を基準に (month,day,hour,minute) を解決する。
    // 範囲外入力（day 1-31 / hour 0-23 / minute 0-59 / month 0-12 以外）はフィールドを 0 化して拒否。
    // 基準時刻が無効（< 2000-01-01）、または暦に存在しない日付（2/30・4/31・平年 2/29 等）は
    // unix_time=0 の未解決（生フィールドは保持）。黙って別月日へ正規化しない。
    static TimeFields resolveTime(uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint32_t report_unix);

    // 12 bit の到着時刻（day_offset:1, hour:5, min:6）-> TimeFields
    static TimeFields resolveArrivalTime(uint16_t raw, uint32_t base_unix);

    // ビット位置から通知コード（各 9 bit、0 で終端）を最大 3 個読み、読んだ個数を返す
    uint8_t readNotifications(const uint8_t* b, uint16_t start, uint16_t* notification);

#if (AZARAC_ENABLE_DCX_CAMF)
    bool decodeDcx(const uint8_t* bits, Message& out, uint32_t report_unix);
#endif

    bool decodeQzqsm(const uint8_t* bits, Message& out, uint32_t report_unix);

    // OOB フラグ: 256 bit のフレーム外を読むと getBits/getBits64 が立てる。
    // decode() は呼び出しごとにクリアし、立っていれば失敗させる。
    bool oob_ = false;

    // MT=43 JMA サブデコーダ。
    // 宣言は無条件（コードサイズを抑えるガードは定義側に置く）。
    // decodeQzqsm() は共有の AZARAC_DC_CATEGORIES 表で振り分けるので、無効カテゴリは呼ばれない。
    void decodeEEW(const uint8_t* b, Message& out, uint32_t report_unix);
    void decodeHypocenter(const uint8_t* b, Message& out, uint32_t report_unix);
    void decodeSeismic(const uint8_t* b, Message& out, uint32_t report_unix);
    void decodeNankai(const uint8_t* b, Message& out, uint32_t report_unix);
    void decodeTsunami(const uint8_t* b, Message& out, uint32_t report_unix);
    void decodeNwPacTsu(const uint8_t* b, Message& out, uint32_t report_unix);
    void decodeVolcano(const uint8_t* b, Message& out, uint32_t report_unix);
    void decodeAshFall(const uint8_t* b, Message& out, uint32_t report_unix);
    void decodeWeather(const uint8_t* b, Message& out, uint32_t report_unix);
    void decodeFlood(const uint8_t* b, Message& out, uint32_t report_unix);
    void decodeTyphoon(const uint8_t* b, Message& out, uint32_t report_unix);
    void decodeMarine(const uint8_t* b, Message& out, uint32_t report_unix);
};

} // namespace internal
} // namespace azaraC
