#pragma once
// ホスト側ユニットテスト用の最小限の Arduino Print shim

#if !defined(ARDUINO) || ARDUINO < 1
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <string_view>
#include <string>

class Print {
public:
    virtual ~Print() = default;
    virtual size_t write(uint8_t c) { putchar(c); return 1; }
    virtual size_t write(const char* s, size_t size) { if (s && size) return fwrite(s, 1, size, stdout); return 0; }
    virtual void print(char c)         { write(c); }
    // 実コアの Print と同じく print() は write() へ流す（write のみ override する sink で取りこぼさない）。
    virtual void print(const char* s)  { if (s) write(s, strlen(s)); }
    virtual void print(std::string_view s) { if (!s.empty()) write(s.data(), s.size()); }
    virtual void print(int v)          { printf("%d", v); }
    virtual void print(unsigned int v) { printf("%u", v); }
    virtual void println()             { write('\n'); }
    virtual void println(const char* s){ print(s); write('\n'); }
    virtual void println(std::string_view s) { print(s); write('\n'); }
    virtual void print(const void* s)  { if (s) print(static_cast<const char*>(s)); }
};

// 動的バッファ（オーバーフローフリー）
class StringPrint : public Print {
    std::string _buf;

public:
    size_t write(uint8_t c) override {
        _buf += static_cast<char>(c);
        return 1;
    }

    size_t write(const char* s, size_t size) override {
        if (s && size) {
            _buf.append(s, size);
            return size;
        }
        return 0;
    }

    void print(char c) override {
        _buf += c;
    }

    void print(const char* s) override {
        if (s) _buf += s;
    }

    void print(std::string_view s) override {
        if (!s.empty()) _buf.append(s.data(), s.size());
    }

    void print(const void* s) override {
        if (s) _buf += static_cast<const char*>(s);
    }

    void print(int v) override {
        _buf += std::to_string(v);
    }

    void print(unsigned int v) override {
        _buf += std::to_string(v);
    }

    void println() override {
        _buf += '\n';
    }

    void println(const char* s) override {
        if (s) _buf += s;
        _buf += '\n';
    }

    void println(std::string_view s) override {
        if (!s.empty()) _buf.append(s.data(), s.size());
        _buf += '\n';
    }

    const std::string& str() const { return _buf; }
    void clear() { _buf.clear(); }
};

inline constexpr const char* F(const char* s) { return s; }
#endif
