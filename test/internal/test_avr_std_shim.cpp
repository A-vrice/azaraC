// Arduino AVR ツールチェーンが使う実際の最小 AVR C++ stdlib シム（src/internal/avr_std/）を、AZARAC_AVR_STUB なしで host 上で検証する。
// 対象は optional / string_view / placement-new のみ。
// 自明な utility/algorithm/iterator シム（move / max / size）は除外する（doctest が本物の <utility>/<algorithm> を引き込むと衝突するため）。
// この翻訳単位は azaraC ライブラリを含めないこと（シムが本物の標準ライブラリと同じ std::optional / std::string_view を定義する）。

#define DOCTEST_CONFIG_IMPLEMENT_WITHOUT_MAIN
#include "../doctest.h"

// シムヘッダ（test/internal/ からの相対）
#include "../../src/internal/avr_std/optional"
#include "../../src/internal/avr_std/string_view"
#include "../../src/internal/avr_std/new"

#include <stdint.h>
#include <string.h>

TEST_CASE("avr_std optional basic operations") {
    std::optional<int> empty;
    CHECK_FALSE(empty.has_value());
    CHECK_FALSE(static_cast<bool>(empty));

    std::optional<int> v(42);
    CHECK(v.has_value());
    CHECK(static_cast<bool>(v));
    CHECK(v.value() == 42);

    // 値からの暗黙構築（引き当て関数の戻り値のような形）
    std::optional<int> fromValue = 7;
    CHECK(fromValue.value() == 7);

    // nullopt から構築
    std::optional<int> fromNull = std::nullopt;
    CHECK_FALSE(fromNull.has_value());

    // コピー
    std::optional<int> copy = v;
    CHECK(copy.value() == 42);

    // 代入 / reset
    copy = std::nullopt;
    CHECK_FALSE(copy.has_value());
    copy = 99;
    CHECK(copy.value() == 99);
    copy.reset();
    CHECK_FALSE(copy.has_value());

    // 値からの代入
    copy = 123;
    CHECK(copy.value() == 123);

    // value_or
    CHECK(copy.value_or(0) == 123);
    std::optional<int> empty2;
    CHECK(empty2.value_or(-1) == -1);
    std::optional<std::string_view> svEmpty;
    CHECK(svEmpty.value_or(std::string_view("", 0)).size() == 0);
    std::optional<std::string_view> svVal = std::string_view("abc", 3);
    CHECK(svVal.value_or(std::string_view("", 0)).size() == 3);
}

TEST_CASE("avr_std optional string_view integration") {
    // lookup 形式: バッファ上の optional<string_view>
    char buf[] = "北海道札幌市";
    std::optional<std::string_view> r = std::string_view(buf, 18);
    CHECK(r.has_value());
    CHECK(r.value().size() == 18);
    CHECK(r.value().data() == buf);


    std::optional<std::string_view> none = std::nullopt;
    CHECK_FALSE(none.has_value());
    if (none) {
        FAIL("nullopt should be falsy");
    }
}

TEST_CASE("avr_std optional operator-> bypasses overloaded operator&") {
    struct AddressOverloaded {
        int value;
        AddressOverloaded* operator&() { return nullptr; }
        const AddressOverloaded* operator&() const { return nullptr; }
    };
    std::optional<AddressOverloaded> v(AddressOverloaded{0});
    v->value = 42;
    CHECK(v->value == 42);
    CHECK(v.has_value());

    const std::optional<AddressOverloaded>& cv = v;
    CHECK(cv->value == 42);
}

TEST_CASE("avr_std string_view operations") {
    std::string_view s("abcdef", 6);
    CHECK(s.size() == 6);
    CHECK_FALSE(s.empty());
    CHECK(s[0] == 'a');
    CHECK(s[5] == 'f');

    // C 文字列から構築
    std::string_view c = "hello";
    CHECK(c.size() == 5);
    CHECK(c == std::string_view("hello", 5));

    // 空の view
    std::string_view e;
    CHECK(e.empty());
    CHECK(e.size() == 0);

    // 比較演算子
    CHECK(s == std::string_view("abcdef", 6));
    CHECK(s != std::string_view("abcde", 5));
    CHECK(s < std::string_view("abcdez", 6));
    CHECK(s > std::string_view("abcde", 5));
}

// avr_std/new による placement new
struct ShimPlacementTest {
    int v;
    explicit ShimPlacementTest(int x) : v(x) {}
};

TEST_CASE("avr_std placement new") {
    alignas(ShimPlacementTest) unsigned char storage[sizeof(ShimPlacementTest)];
    ShimPlacementTest* p = new (static_cast<void*>(storage)) ShimPlacementTest(5);
    CHECK(p->v == 5);
    p->~ShimPlacementTest();
}
