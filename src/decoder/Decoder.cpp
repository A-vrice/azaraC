// Common decoder utilities (CRC, bit extraction, time resolution)

#include "Decoder.h"
#if defined(__AVR__)
#include <avr/pgmspace.h>   // PROGMEM ニブル表（crc24q の AVR 版）
#endif

namespace azaraC {
namespace internal {

// CRC-24Q  (generator 0x1864CFB, GPS/QZSS standard)
static constexpr uint32_t CRC24Q_POLY = 0x1864CFBu;

// ニブル表の 1 項目: 4 bit の {i, 0000} を MSB-first, init=0 で取り込んだ結果。 1 ビットずつの `crc <<= 1; if (crc & 0x1000000) crc ^= POLY;` 4 回ぶん。表はこれから生成する（手書き定数を置かない）。
static constexpr uint32_t crc24qT4(uint32_t i) {
    uint32_t c = i << 20;
    for (uint8_t k = 0; k < 4; ++k) {
        c <<= 1;
        if (c & 0x1000000u) c ^= CRC24Q_POLY;
    }
    return c & 0xFFFFFFu;
}

#if defined(__AVR__)
// AVR: 32 bit の `>> 20` / `<< 4` は LSR/ROR の回転ループに展開されるため（実測: -Os）、 24 bit レジスタを 3 バイトで持ち 8 bit 演算だけで回す。表は Flash に置き 3 分割で読む。
#define AZARAC_CRC24Q_T4B(BYTE) \
    (uint8_t)(crc24qT4(0)  >> (BYTE)), (uint8_t)(crc24qT4(1)  >> (BYTE)), \
    (uint8_t)(crc24qT4(2)  >> (BYTE)), (uint8_t)(crc24qT4(3)  >> (BYTE)), \
    (uint8_t)(crc24qT4(4)  >> (BYTE)), (uint8_t)(crc24qT4(5)  >> (BYTE)), \
    (uint8_t)(crc24qT4(6)  >> (BYTE)), (uint8_t)(crc24qT4(7)  >> (BYTE)), \
    (uint8_t)(crc24qT4(8)  >> (BYTE)), (uint8_t)(crc24qT4(9)  >> (BYTE)), \
    (uint8_t)(crc24qT4(10) >> (BYTE)), (uint8_t)(crc24qT4(11) >> (BYTE)), \
    (uint8_t)(crc24qT4(12) >> (BYTE)), (uint8_t)(crc24qT4(13) >> (BYTE)), \
    (uint8_t)(crc24qT4(14) >> (BYTE)), (uint8_t)(crc24qT4(15) >> (BYTE))

static const uint8_t PROGMEM CRC24Q_T4B2[16] = { AZARAC_CRC24Q_T4B(16) };
static const uint8_t PROGMEM CRC24Q_T4B1[16] = { AZARAC_CRC24Q_T4B(8) };
static const uint8_t PROGMEM CRC24Q_T4B0[16] = { AZARAC_CRC24Q_T4B(0) };
#undef AZARAC_CRC24Q_T4B

uint32_t Decoder::crc24q(const uint8_t* data, uint16_t bit_len) {
    uint8_t c0 = 0, c1 = 0, c2 = 0;   // 24 bit レジスタ（c2 が上位バイト）
    const uint16_t nibbles = bit_len >> 2;
    for (uint16_t n = 0; n < nibbles; ++n) {
        const uint8_t nib = (n & 1u) ? (data[n >> 1] & 0x0Fu) : (uint8_t)(data[n >> 1] >> 4);
        const uint8_t idx = (uint8_t)((c2 >> 4) ^ nib);
        const uint8_t n0 = c0, n1 = c1, n2 = c2;
        c0 = (uint8_t)((n0 << 4) ^ pgm_read_byte(&CRC24Q_T4B0[idx]));
        c1 = (uint8_t)((((n1 & 0x0Fu) << 4) | (n0 >> 4)) ^ pgm_read_byte(&CRC24Q_T4B1[idx]));
        c2 = (uint8_t)((((n2 & 0x0Fu) << 4) | (n1 >> 4)) ^ pgm_read_byte(&CRC24Q_T4B2[idx]));
    }
    // 端数（bit_len & 3 bit）は表の対象外なのでビット直列のまま処理する。
    const uint8_t rem = bit_len & 3u;
    if (rem) {
        uint8_t byte = data[nibbles >> 1];
        if (nibbles & 1u) byte = (uint8_t)(byte << 4);   // 端数は下位ニブルの上位 rem bit
        byte &= (uint8_t)(0xFFu << (8u - rem));
        c2 ^= byte;
        for (uint8_t j = 0; j < rem; ++j) {
            const uint8_t carry = (uint8_t)(c2 >> 7);
            c2 = (uint8_t)((c2 << 1) | (c1 >> 7));
            c1 = (uint8_t)((c1 << 1) | (c0 >> 7));
            c0 = (uint8_t)(c0 << 1);
            if (carry) { c0 ^= 0xFBu; c1 ^= 0x4Cu; c2 ^= 0x86u; }   // POLY 0x1864CFB の下位 24 bit
        }
    }
    return ((uint32_t)c2 << 16) | ((uint32_t)c1 << 8) | c0;
}

#else

// host: 32 bit シフトが 1 命令で済むので 32 bit 表をそのまま使う。
static constexpr uint32_t CRC24Q_T4[16] = {
    crc24qT4(0),  crc24qT4(1),  crc24qT4(2),  crc24qT4(3),
    crc24qT4(4),  crc24qT4(5),  crc24qT4(6),  crc24qT4(7),
    crc24qT4(8),  crc24qT4(9),  crc24qT4(10), crc24qT4(11),
    crc24qT4(12), crc24qT4(13), crc24qT4(14), crc24qT4(15),
};

uint32_t Decoder::crc24q(const uint8_t* data, uint16_t bit_len) {
    uint32_t crc = 0;
    const uint16_t nibbles = bit_len >> 2;
    for (uint16_t n = 0; n < nibbles; ++n) {
        const uint8_t nib = (n & 1u) ? (data[n >> 1] & 0x0Fu) : (uint8_t)(data[n >> 1] >> 4);
        crc = ((crc << 4) & 0xFFFFFFu) ^ CRC24Q_T4[((crc >> 20) ^ nib) & 0x0Fu];
    }
    // 端数（bit_len & 3 bit）は表の対象外なのでビット直列のまま処理する。
    const uint8_t rem = bit_len & 3u;
    if (rem) {
        uint8_t byte = data[nibbles >> 1];
        if (nibbles & 1u) byte = (uint8_t)(byte << 4);   // 端数は下位ニブルの上位 rem bit
        byte &= (uint8_t)(0xFFu << (8u - rem));
        crc ^= (uint32_t)byte << 16;
        for (uint8_t j = 0; j < rem; ++j) {
            crc <<= 1;
            if (crc & 0x1000000u) crc ^= CRC24Q_POLY;
        }
    }
    return crc & 0xFFFFFFu;
}
#endif

uint32_t Decoder::messageIdentity(uint8_t* bits) {
    const uint8_t mt = (uint8_t)((bits[1] >> 2) & 0x3Fu);   // MT = frame bit 8..13（byte 1 の上位 6 bit）
    if (mt != 44) return crc24q(bits + 1, 212);
    // SD（byte 1 の下位 2 bit + byte 2 = frame bit 14..23）だけゼロにして digest を取る。 32 B のフレームをコピーしないよう、対象 2 バイトを外して取ったあと戻す（呼び出し側から見てフレームは不変）。
    const uint8_t sd_hi = bits[1];
    const uint8_t sd_lo = bits[2];
    bits[1] &= 0xFCu;
    bits[2]  = 0x00u;
    const uint32_t identity = crc24q(bits + 1, 212);
    bits[1] = sd_hi;
    bits[2] = sd_lo;
    return identity;
}

uint32_t Decoder::getBits(const uint8_t* buf, uint16_t start, uint8_t len) {
    // OOB は 0 を返して oob_ を立て、decode() 側で弾く（組込みなので assert は使わない）。上限は 250 ではなく 256: Frame::bits は 256 bit 幅で、bit 250-255 は詰め物。
    if (start + len > 256) { oob_ = true; return 0; }
    uint32_t val = 0;
    for (uint8_t i = 0; i < len; ++i) {
        uint16_t pos = start + i;
        val = (val << 1) | ((buf[pos >> 3] >> (7u - (pos & 7u))) & 1u);
    }
    return val;
}

// 64 bit 抽出（MSB-first, 0 始まり）— 32 bit を超えるフィールド用
uint64_t Decoder::getBits64(const uint8_t* buf, uint16_t start, uint8_t len) {
    // Same silent-zero-with-oob-flag policy as getBits()
    if (start + len > 256) { oob_ = true; return 0; }
    uint64_t val = 0;
    for (uint8_t i = 0; i < len; ++i) {
        uint16_t pos = start + i;
        val = (val << 1) | ((buf[pos >> 3] >> (7u - (pos & 7u))) & 1u);
    }
    return val;
}

void Decoder::civil_from_days(uint32_t days_since_1970, uint32_t& y, uint32_t& m, uint32_t& d) {
    uint32_t z = days_since_1970 + 719468u;
    uint32_t era = z / 146097u;
    uint32_t doe = z - era * 146097u;
    uint32_t yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
    y = yoe + era * 400;
    uint32_t doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
    uint32_t mp = (5 * doy + 2) / 153;
    d = doy - (153 * mp + 2) / 5 + 1;
    m = mp + (mp < 10 ? 3 : -9);
    y += (m <= 2);
}

uint32_t Decoder::days_from_civil(uint32_t y, uint32_t m, uint32_t d) {
    y -= (m <= 2);
    uint32_t era = y / 400;
    uint32_t yoe = y - era * 400;
    uint32_t doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;
    uint32_t doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return era * 146097 + doe - 719468;
}

LatLon Decoder::extractLatLon(const uint8_t* buf, uint16_t start) {
    LatLon ll{};
    ll.lat_ns  = getBits(buf, start,      1);
    ll.lat_deg = getBits(buf, start +  1, 7);
    ll.lat_min = getBits(buf, start +  8, 6);
    ll.lat_sec = getBits(buf, start + 14, 6);
    ll.lon_ew  = getBits(buf, start + 20, 1);
    ll.lon_deg = getBits(buf, start + 21, 8);
    ll.lon_min = getBits(buf, start + 29, 6);
    ll.lon_sec = getBits(buf, start + 35, 6);
    return ll;
}

TimeFields Decoder::extractDHM(const uint8_t* buf, uint16_t start, uint32_t report_unix) {
    uint8_t d = getBits(buf, start,      5);
    uint8_t h = getBits(buf, start +  5, 5);
    uint8_t m = getBits(buf, start + 10, 6);
    return resolveTime(0, d, h, m, report_unix);
}

TimeFields Decoder::resolveTime(uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint32_t report_unix) {
    TimeFields t{month, day, hour, minute, 0};
    if (day < 1 || day > 31 || hour > 23 || minute > 59 || (month > 12 && month != 0)) {
        t.day = t.hour = t.minute = 0;
        return t;
    }

    // 基準時刻が無効（< 2000-01-01）なら年解決を飛ばす。unix_time は 0 のまま。
    if (report_unix < 946684800u) {
        return t;
    }

    uint32_t base_unix = report_unix;

    uint32_t base_days = base_unix / 86400u;
    uint32_t y, m, d;
    civil_from_days(base_days, y, m, d);

    if (month == 0) {
        // 月なし（DHM のみ）: report_unix に最も近い (day,hour,minute) を選ぶ。
        // 数日の余裕は時計のずれと月境界を吸収する（01/31 23:00 の通報 + 02/01 02:00 の事象 → 2 月）。
        // 余裕を超えたら古い通報とみなし、直近の過去の出現へ落とす。
        static constexpr uint32_t MARGIN_SEC = 3u * 86400u;
        uint32_t best_y = y, best_m = m;
        uint32_t best_diff = 0xFFFFFFFFu;
        for (int8_t dm = -1; dm <= 1; ++dm) {
            int32_t cm = (int32_t)m + dm;
            uint32_t cy = y, cand_m;
            if      (cm <= 0) { cand_m = 12; cy = y - 1; }
            else if (cm >= 13) { cand_m = 1;  cy = y + 1; }
            else              { cand_m = (uint32_t)cm; }
            uint32_t ts = days_from_civil(cy, cand_m, day) * 86400u
                        + (uint32_t)hour * 3600u + (uint32_t)minute * 60u;
            uint32_t diff = ts > base_unix ? ts - base_unix : base_unix - ts;
            if (diff < best_diff) { best_diff = diff; best_y = cy; best_m = cand_m; }
        }
        if (best_diff <= MARGIN_SEC) {
            y = best_y;
            m = best_m;
        } else {
            // Stale: most recent occurrence on/before report_unix (never future).
            uint32_t cur_ts = days_from_civil(y, m, day) * 86400u
                            + (uint32_t)hour * 3600u + (uint32_t)minute * 60u;
            if (cur_ts > base_unix) {
                if (m == 1) { m = 12; y--; } else { m--; }
            }
        }
    } else {
        // 月あり（MDHM）: 基準時刻から年を決め、月跨ぎを補正する。
        uint32_t cur_m = m;
        m = month;
        int32_t diff = (int32_t)month - (int32_t)cur_m;
        if      (diff >  6) y--;
        else if (diff < -6) y++;
    }

    // 日付を正規化する（例: 平年の 2 月 29 日は 3 月 1 日になる）。
    uint32_t resolved_days = days_from_civil(y, m, day);
    civil_from_days(resolved_days, y, m, d);

    t.unix_time = resolved_days * 86400u + (uint32_t)hour * 3600u + (uint32_t)minute * 60u;
    t.day = d;
    t.month = m;
    return t;
}

TimeFields Decoder::resolveArrivalTime(uint16_t raw, uint32_t base_unix) {
    TimeFields t{};
    if (raw == 0) return t;

    uint8_t next = (raw >> 11) & 1;
    uint8_t hour = (raw >>  6) & 0x1F;
    uint8_t min  = raw & 0x3F;

    if (hour > 23 || min > 59) return t;

    // 基準時刻が無効（< 2000-01-01）なら年・月の解決を飛ばす。unix_time, month, day は 0 のまま。
    if (base_unix < 946684800u) {
        t.hour = hour;
        t.minute = min;
        return t;
    }

    uint32_t base_days = base_unix / 86400u;
    uint32_t arrival_days = base_days + next;
    uint32_t y, m, d;
    civil_from_days(arrival_days, y, m, d);

    t.day = d;
    t.month = m;
    t.hour = hour;
    t.minute = min;
    t.unix_time = arrival_days * 86400u + (uint32_t)hour * 3600u + (uint32_t)min * 60u;
    return t;
}

uint8_t Decoder::readNotifications(const uint8_t* b, uint16_t start, uint16_t* notification) {
    uint8_t count = 0;
    for (uint8_t i = 0; i < 3; ++i) {
        uint16_t co = getBits(b, start + i * 9, 9);
        if (co == 0) break;
        notification[count++] = co;
    }
    return count;
}

bool Decoder::decode(const Frame& frame, Message& out, uint32_t report_unix) {
    oob_ = false;
    out.clear();
    out.svid    = frame.svid;
    const uint8_t* bits = frame.bits;

    // L1S subframe: CRC-24Q covers bits [0..225], CRC stored at [226..249]
    uint32_t calc = crc24q(bits, 226);
    uint32_t recv = getBits(bits, 226, 24);
    if (calc != recv) return false;

    out.crc24   = recv;

    uint8_t preamble = getBits(bits, 0, 8);
    if (preamble != 0x53 && preamble != 0x9A && preamble != 0xC6) return false;  // IS-QZSS-L1S §3.2.4

    uint8_t mt = getBits(bits, 8, 6);
    out.msg_type = mt;

    if (mt == 44) {
#if (AZARAC_ENABLE_DCX_CAMF)
        bool ok = decodeDcx(bits, out, report_unix);
        return ok && !oob_;
#else
        out.unsupported_reason = UnsupportedReason::DisabledAtCompileTime;
        return false;
#endif
    }
    if (mt == 43) { bool ok = decodeQzqsm(bits, out, report_unix); return ok && !oob_; }
    out.unsupported_reason = UnsupportedReason::UnknownCategory;
    return false;
}

} // namespace internal
} // namespace azaraC
