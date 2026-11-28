#include "internal/FlashString.h"
#include <cassert>
#include <cstdio>
#include <cstring>

int main() {
    using namespace azaraC::def;
    assert(azarac_utf8_trim_len(nullptr, 0) == 0);
    assert(azarac_utf8_trim_len(nullptr, 3) == 0);
    assert(azarac_utf8_trim_len("abc", 3) == 3);
    const char* samples[] = {"\xC2\xA2", "\xE3\x81\x82", "\xF0\x9F\x98\x80"};
    for (const char* s : samples) {
        const size_t len = std::strlen(s);
        assert(azarac_utf8_trim_len(s, len) == len);
        for (size_t n = 1; n < len; ++n) assert(azarac_utf8_trim_len(s, n) == 0);
    }
    assert(azarac_utf8_trim_len("ab\xF0\x9F\x98", 5) == 2);
    assert(azarac_utf8_trim_len("\xFF", 1) == 0);
    assert(azarac_utf8_trim_len("\x80", 1) == 0);
    char text[68] = {};
    std::memset(text, 'a', 62);
    std::memcpy(text + 62, "\xE3\x81\x82", 3);
    auto view = azarac_pgm_join_z(AZARAC_PGM_PTR(text), AZARAC_PGM_PTR(""));
    assert(view.size() == 62);
    for (char c : view) assert(c == 'a');
    assert(view.data()[view.size()] == '\0');
    view = azarac_pgm_join3(AZARAC_PGM_PTR(""), AZARAC_PGM_PTR(text), AZARAC_PGM_PTR("tail"));
    assert(view.size() == 62);
    view = azarac_pgm_view_z(AZARAC_PGM_PTR(text));
    assert(view.size() == 62);
    view = azarac_pgm_join_z(AZARAC_PGM_PTR("\xE3"), AZARAC_PGM_PTR("\x81\x82"));
    assert(view == "\xE3\x81\x82");
    view = azarac_pgm_join_z(AZARAC_PGM_PTR(""), AZARAC_PGM_PTR(""));
    assert(view.empty());
    std::memset(text, 'b', 63);
    std::memcpy(text + 63, "\xE3\x81\x82", 4);
    view = azarac_pgm_join_z(AZARAC_PGM_PTR(text), AZARAC_PGM_PTR(""));
    assert(view.size() == 63);
#ifdef __AVR__
    std::memset(text, 'a', 62);
    std::memcpy(text + 62, "\xE3\x81\x82", 4);
    assert(azarac_pgm_view(AZARAC_PGM_PTR(text), 65).size() == 62);
    assert(std::strlen(azarac_pgm_copy(AZARAC_PGM_PTR(text))) == 62);
#endif
    std::puts("utf8-trim: OK");
}
