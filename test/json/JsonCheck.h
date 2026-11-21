// 最小の JSON 妥当性検査（テスト共有）。
// 値は深追いせず、構造（括弧・引用符・カンマ）と各オブジェクト内のキー重複だけを見る。
// 空白は書かない前提なので厳密でよい。メソッドはクラス内定義（暗黙 inline）で複数 TU から include 可能。

#ifndef AZARAC_TEST_JSONCHECK_H
#define AZARAC_TEST_JSONCHECK_H

#include <cctype>
#include <cstring>
#include <string>
#include <vector>

class JsonCheck {
public:
    explicit JsonCheck(const std::string& s) : s_(s) {}

    // 妥当なら true。不正なら error() に理由が入る。
    bool run() {
        if (!parseValue()) { fail("value"); return false; }
        if (i_ != s_.size()) { fail("trailing"); return false; }
        return true;
    }

    const std::string& error() const { return err_; }

private:
    const std::string& s_;
    size_t i_ = 0;
    std::string err_;
    std::vector<std::string> keys_;   // 現在のオブジェクトのキー集合

    void fail(const char* what) {
        if (err_.empty())
            err_ = std::string(what) + " at offset " + std::to_string(i_);
    }
    bool eof() const { return i_ >= s_.size(); }
    char peek() const { return eof() ? '\0' : s_[i_]; }

    bool parseString() {
        if (peek() != '"') { fail("string open"); return false; }
        ++i_;
        while (!eof()) {
            char c = s_[i_];
            if (c == '\\') { i_ += 2; continue; }   // エスケープは 2 文字消費
            if (c == '"') { ++i_; return true; }
            ++i_;
        }
        fail("string unterminated");
        return false;
    }

    bool parseNumber() {
        size_t start = i_;
        if (peek() == '-') ++i_;
        while (!eof() && (isdigit(static_cast<unsigned char>(peek())) || peek() == '.' ||
                          peek() == 'e' || peek() == 'E' || peek() == '+' || peek() == '-'))
            ++i_;
        if (i_ == start) { fail("number"); return false; }
        return true;
    }

    bool parseLiteral(const char* lit) {
        size_t n = strlen(lit);
        if (s_.compare(i_, n, lit) != 0) { fail(lit); return false; }
        i_ += n;
        return true;
    }

    bool parseObject() {
        if (peek() != '{') { fail("object open"); return false; }
        ++i_;
        auto saved = keys_;
        keys_.clear();
        if (peek() == '}') { ++i_; keys_ = saved; return true; }
        for (;;) {
            size_t keyPos = i_;
            if (!parseString()) return false;
            std::string key = s_.substr(keyPos, i_ - keyPos);
            // 同一オブジェクト内のキー重複を検出する
            for (const auto& k : keys_) {
                if (k == key) {
                    err_ = "duplicate key " + key + " at offset " + std::to_string(keyPos);
                    return false;
                }
            }
            keys_.push_back(key);
            if (peek() != ':') { fail("colon"); return false; }
            ++i_;
            if (!parseValue()) return false;
            if (peek() == ',') { ++i_; continue; }
            if (peek() == '}') { ++i_; keys_ = saved; return true; }
            fail("object sep");
            return false;
        }
    }

    bool parseArray() {
        if (peek() != '[') { fail("array open"); return false; }
        ++i_;
        auto saved = keys_;
        keys_.clear();
        if (peek() == ']') { ++i_; keys_ = saved; return true; }
        for (;;) {
            if (!parseValue()) return false;
            if (peek() == ',') { ++i_; continue; }
            if (peek() == ']') { ++i_; keys_ = saved; return true; }
            fail("array sep");
            return false;
        }
    }

    bool parseValue() {
        switch (peek()) {
            case '"': return parseString();
            case '{': return parseObject();
            case '[': return parseArray();
            case 't': return parseLiteral("true");
            case 'f': return parseLiteral("false");
            case 'n': return parseLiteral("null");
            default:  return parseNumber();
        }
    }
};

#endif // AZARAC_TEST_JSONCHECK_H