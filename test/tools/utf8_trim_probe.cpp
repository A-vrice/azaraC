// azarac_utf8_trim_len / azarac_pgm_join_z の切り詰めを実行検証する。
// make utf8-trim が AZARAC_FLASH_BUF_SIZE=64 でビルド・実行する。
#include <cstdio>
#include <string>
#include <string_view>
#include "internal/FlashString.h"

namespace {

int failures = 0;

void expect_len(size_t got, size_t want, const char* what) {
    if (got == want) return;
    std::printf("FAIL: %s (got %zu, expected %zu)\n", what, got, want);
    ++failures;
}

void expect_fill(std::string_view v, size_t want_len, char fill, const char* what) {
    if (v.size() != want_len) {
        std::printf("FAIL: %s (len %zu, expected %zu)\n", what, v.size(), want_len);
        ++failures;
        return;
    }
    for (char c : v) {
        if (c != fill) {
            std::printf("FAIL: %s (unexpected byte)\n", what);
            ++failures;
            return;
        }
    }
}

// 出力が完全な UTF-8 シーケンスだけで構成されること。
void expect_utf8_complete(std::string_view v, const char* what) {
    size_t i = 0;
    while (i < v.size()) {
        const unsigned char b = static_cast<unsigned char>(v[i]);
        size_t need = 0;
        if (b < 0x80) need = 1;
        else if ((b & 0xE0) == 0xC0) need = 2;
        else if ((b & 0xF0) == 0xE0) need = 3;
        else if ((b & 0xF8) == 0xF0) need = 4;
        if (need == 0 || i + need > v.size()) {
            std::printf("FAIL: %s (invalid or truncated sequence at %zu)\n", what, i);
            ++failures;
            return;
        }
        for (size_t k = 1; k < need; ++k) {
            if ((static_cast<unsigned char>(v[i + k]) & 0xC0) != 0x80) {
                std::printf("FAIL: %s (bad continuation at %zu)\n", what, i + k);
                ++failures;
                return;
            }
        }
        i += need;
    }
}

} // namespace

int main() {
    using azaraC::def::azarac_utf8_trim_len;
    using azaraC::def::azarac_pgm_join_z;

    // 完全な文字列は変更しない。
    expect_len(azarac_utf8_trim_len("abc", 3), 3, "ascii complete");
    expect_len(azarac_utf8_trim_len("\xE3\x81\x82", 3), 3, "3-byte complete");
    expect_len(azarac_utf8_trim_len("\xF0\x9F\x98\x80", 4), 4, "4-byte complete");

    // 途中で切れたシーケンスは先頭バイトまで戻す。
    expect_len(azarac_utf8_trim_len("\xE3\x81", 2), 0, "3-byte truncated at lead");
    expect_len(azarac_utf8_trim_len("a\xE3\x81", 3), 1, "3-byte truncated after ascii");
    expect_len(azarac_utf8_trim_len("ab\xF0\x9F\x98", 5), 2, "4-byte truncated");

    // 不正な先頭バイトは落とす。
    expect_len(azarac_utf8_trim_len("\xFF", 1), 0, "invalid lead byte dropped");

    // バッファ 64 B の打ち切り: 62 'a' + あ(3 B) = 65 B は 63 B で切れ、UTF-8 境界の 62 B に丸まる。
    // 2 本目の断片は空。
    static const char kNone[] = "";
    std::string a(62, 'a');
    a += "\xE3\x81\x82";
    expect_fill(azarac_pgm_join_z(a.c_str(), kNone), 62, 'a', "join_z truncation");
    expect_utf8_complete(azarac_pgm_join_z(a.c_str(), kNone), "join_z output");

    // 境界にちょうど収まる 63 B は切り捨てない。
    std::string b(63, 'b');
    b += "\xE3\x81\x82";
    expect_fill(azarac_pgm_join_z(b.c_str(), kNone), 63, 'b', "exact boundary kept");

    if (failures != 0) {
        std::printf("%d failure(s)\n", failures);
        return 1;
    }
    std::printf("ok\n");
    return 0;
}