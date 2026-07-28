// test/tools/decode_to_json.cpp
// AzaraC NMEA decoder → JSON output CLI
// Usage: echo "$QZQSM,57,..." | decode_to_json
//        decode_to_json < nmea_lines.txt
// Output: JSON array of decoded messages.
// Uses Parser (not raw Decoder) so that Nankai multi-page aggregation works.

#define ARDUINO 0
#include "azaraC.h"
#include "Parser.h"
#include "framer/NmeaFramer.h"
#include "decoder/Decoder.h"
#include "json/JsonSerializer.h"
#include "internal/PrintShim.h"
#include <cstdio>
#include <cstring>
#include <string>

using namespace azaraC;
using namespace azaraC::internal;

int main(int argc, char* argv[]) {
    bool raw_mode = false;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--raw") == 0 || strcmp(argv[i], "--no-dedup") == 0) {
            raw_mode = true;
        }
    }

    // Read all stdin into a string
    std::string input;
    char buf[4096];
    while (fgets(buf, sizeof(buf), stdin)) {
        input += buf;
    }

    printf("[\n");

    Parser parser;
    NmeaFramer nmea_framer;
    Decoder decoder;
    bool first = true;

    auto emit = [&](Message& m) {
        if (!first) printf(",\n");
        first = false;
        StringPrint sp;
        JsonSerializer::serialize(m, sp);
        printf("  %s", sp.str().c_str());
    };

    auto process_line = [&](const std::string& line) {
        if (raw_mode) {
            Frame frame;
            bool parsed = false;
            auto decode_frame = [&](Frame& f) {
                Message msg;
                if (decoder.decode(f, msg, 0)) {
                    emit(msg);
                } else {
                    if (!first) printf(",\n");
                    first = false;
                    printf("  {\"_error\": \"decode_failed\"}");
                }
            };
            for (char c : line) {
                if (nmea_framer.feed(static_cast<uint8_t>(c), frame)) {
                    decode_frame(frame);
                    parsed = true;
                }
            }
            if (nmea_framer.feed(static_cast<uint8_t>('\n'), frame)) {
                decode_frame(frame);
                parsed = true;
            }
            if (!parsed) {
                if (!first) printf(",\n");
                first = false;
                printf("  {\"_error\": \"parse_failed\"}");
            }
            nmea_framer.reset();
        } else {
            Message msg;
            for (char c : line) {
                if (parser.feed(static_cast<uint8_t>(c), msg, 0)) emit(msg);
            }
            if (parser.feed(static_cast<uint8_t>('\n'), msg, 0)) emit(msg);
        }
    };

    std::string line;
    for (char c : input) {
        if (c == '\n' || c == '\r') {
            if (!line.empty()) {
                process_line(line);
                line.clear();
            }
        } else {
            line += c;
        }
    }
    if (!line.empty()) {
        process_line(line);
    }

    printf("\n]\n");
    return 0;
}

