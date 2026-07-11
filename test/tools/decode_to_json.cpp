// test/tools/decode_to_json.cpp
// AzaraC NMEA decoder → JSON output CLI
// Usage: echo "$QZQSM,57,..." | decode_to_json
//        decode_to_json < nmea_lines.txt
// Output: JSON array of decoded messages.
// Uses Parser (not raw Decoder) so that Nankai multi-page aggregation works.

#define ARDUINO 0
#include "azaraC.h"
#include "Parser.h"
#include "json/JsonSerializer.h"
#include "internal/PrintShim.h"
#include <cstdio>
#include <cstring>
#include <string>

using namespace azaraC;
using namespace azaraC::internal;

int main() {
    // Read all stdin into a string
    std::string input;
    char buf[4096];
    while (fgets(buf, sizeof(buf), stdin)) {
        input += buf;
    }

    printf("[\n");

    Parser parser;
    Message msg;
    bool first = true;

    auto emit = [&](Message& m) {
        if (!first) printf(",\n");
        first = false;
        StringPrint sp;
        JsonSerializer::serialize(m, sp);
        printf("  %s", sp.str().c_str());
    };

    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];
        if (c == '\n' || c == '\r') {
            if (i > 0 && input[i-1] != '\n' && input[i-1] != '\r') {
                // End of a non-empty line — feed a synthetic newline
                // to help the NMEA framer detect sentence boundaries.
                // The parser ignores non-NMEA bytes, so this is safe.
                if (parser.feed(static_cast<uint8_t>('\n'), msg, 0)) emit(msg);
            }
        } else {
            if (parser.feed(static_cast<uint8_t>(c), msg, 0)) emit(msg);
        }
    }

    // Flush any remaining buffered data
    if (parser.feed(static_cast<uint8_t>('\n'), msg, 0)) emit(msg);

    printf("\n]\n");
    return 0;
}
