#!/usr/bin/env python3
# azaraC - scripts/gen/apply_avr_std_includes.py
# One-shot migration: wraps the C++ standard library includes in src/ (and
# the 3 manually-maintained definition headers) with
#   #if defined(__AVR__)
#   #include "<relpath>/avr_std/<header>"
#   #else
#   #include <<header>>
#   #endif
#
# The Arduino AVR toolchain ships no libstdc++, so on AVR the includes are
# redirected to src/internal/avr_std/ (minimal shims).
#
# Host-only headers (<string>, <chrono>, <atomic>, and everything inside
# PrintShim.h / TimeFields.h host blocks) are intentionally left untouched.
#
# Usage:
#   cd scripts/gen && python apply_avr_std_includes.py

import os, re

REPO = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", ".."))

# file -> (relative prefix to avr_std from that file's dir, [headers])
TARGETS = {
    # --- src/ root ---
    "src/Message.h":              ("internal/avr_std/", ["algorithm", "cstdint", "cstring", "new", "utility"]),
    "src/Mt43Data.h":             ("internal/avr_std/", ["cstdint", "cstring", "new", "utility"]),
    "src/Mt44Data.h":             ("internal/avr_std/", ["cstdint"]),
    # --- src/framer/ ---
    "src/framer/Frame.h":         ("../internal/avr_std/", ["cstdint"]),
    "src/framer/IFramer.h":       ("../internal/avr_std/", ["cstdint"]),
    "src/framer/NmeaFramer.cpp":  ("../internal/avr_std/", ["cstring"]),
    "src/framer/UbxFramer.cpp":   ("../internal/avr_std/", ["cstring"]),
    # --- src/internal/ ---
    "src/internal/Dedup.h":       ("avr_std/", ["cstdint", "cstring"]),
    "src/internal/MtCommonTypes.h": ("avr_std/", ["cstdint"]),
    "src/internal/NankaiPageBuffer.h": ("avr_std/", ["cstdint", "cstring", "climits"]),
    "src/internal/TimeFields.h":  ("avr_std/", ["cstdint"]),
    "src/internal/FlashString.h": ("avr_std/", ["cstddef", "string_view"]),
    # --- src/json/ ---
    "src/json/JsonSerializer.cpp":   ("../internal/avr_std/", ["optional", "string_view"]),
    "src/json/JsonSerializerDcx.cpp":("../internal/avr_std/", ["optional", "string_view"]),
    "src/json/JsonSerializerQzqsm.cpp": ("../internal/avr_std/", ["optional", "string_view"]),
    "src/json/JsonWriter.h":       ("../internal/avr_std/", ["optional", "string_view"]),
    "src/json/JsonWriter.cpp":     ("../internal/avr_std/", ["cstdio"]),
    # --- manually-maintained definition headers ---
    "src/definition/ublox_qzss_svid_prn_map.h": ("../internal/avr_std/", ["cstdint", "optional", "string_view"]),
    "src/definition/qzss_dcx_camf_a3_provider_identifier.h": ("../internal/avr_std/", ["cstdint", "iterator", "optional", "string_view"]),
    "src/definition/qzss_dcx_camf_a3_provider_identifier_map.h": ("../internal/avr_std/", ["cstdint", "optional", "string_view"]),
}

RE_INCLUDE = re.compile(r'^#include <([a-z_]+)>$')


def guard_block(header, prefix):
    return (
        f"#if defined(__AVR__)\n"
        f'#include "{prefix}{header}"\n'
        f"#else\n"
        f"#include <{header}>\n"
        f"#endif"
    )


def process(path, prefix, headers):
    with open(path, encoding="utf-8") as f:
        lines = f.readlines()
    out = []
    changed = 0
    for line in lines:
        m = RE_INCLUDE.match(line.rstrip("\n"))
        if m and m.group(1) in headers:
            out.append(guard_block(m.group(1), prefix) + "\n")
            changed += 1
        else:
            out.append(line)
    if changed:
        with open(path, "w", encoding="utf-8") as f:
            f.writelines(out)
    print(f"[{'OK' if changed else 'SKIP'}] {path} ({changed} include(s))")


def main():
    for rel, (prefix, headers) in sorted(TARGETS.items()):
        path = os.path.join(REPO, rel)
        process(path, prefix, headers)


if __name__ == "__main__":
    main()
