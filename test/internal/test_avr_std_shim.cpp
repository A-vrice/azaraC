// azaraC - test/internal/test_avr_std_shim.cpp
// Host validation of the minimal AVR C++ standard library shims
// (src/internal/avr_std/) WITHOUT AZARAC_AVR_STUB, i.e. the real minimal
// implementations that the Arduino AVR toolchain uses.
//
// Only optional / string_view / placement-new are exercised here. The
// utility/algorithm/iterator shims are trivial (std::move / std::max /
// std::size) and are excluded to avoid redefinition conflicts if doctest
// or its dependencies pull the real <utility>/<algorithm>.
//
// NOTE: this TU must not include the azaraC library — the shim defines the
// same std::optional/std::string_view names as the real standard library.

#define DOCTEST_CONFIG_IMPLEMENT_WITHOUT_MAIN
#include "../doctest.h"

// Shim headers (relative to test/internal/)
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

    // implicit construction from value (as returned by lookup functions)
    std::optional<int> fromValue = 7;
    CHECK(fromValue.value() == 7);

    // nullopt construction
    std::optional<int> fromNull = std::nullopt;
    CHECK_FALSE(fromNull.has_value());

    // copy
    std::optional<int> copy = v;
    CHECK(copy.value() == 42);

    // assignment / reset
    copy = std::nullopt;
    CHECK_FALSE(copy.has_value());
    copy = 99;
    CHECK(copy.value() == 99);
    copy.reset();
    CHECK_FALSE(copy.has_value());

    // assignment from value
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
    // lookup-style: build an optional<string_view> over a shared buffer
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

    // C-string constructor
    std::string_view c = "hello";
    CHECK(c.size() == 5);
    CHECK(c == std::string_view("hello", 5));

    // empty view
    std::string_view e;
    CHECK(e.empty());
    CHECK(e.size() == 0);

    // comparison operators
    CHECK(s == std::string_view("abcdef", 6));
    CHECK(s != std::string_view("abcde", 5));
    CHECK(s < std::string_view("abcdez", 6));
    CHECK(s > std::string_view("abcde", 5));
}

// placement new via avr_std/new
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
