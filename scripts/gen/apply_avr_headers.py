#!/usr/bin/env python3
# azaraC - scripts/gen/apply_avr_headers.py
# One-shot migration: rewrites checked-in definition headers in src/definition/
# with AVR PROGMEM support (#if defined(__AVR__) branches).
#
# Parses existing header content (varname, strategy, use_optional, entries),
# then rebuilds via the updated gen_definitions.build_header.
#
# Manual headers (not regenerated):
#   - ublox_qzss_svid_prn_map.h
#   - qzss_dcx_camf_a3_provider_identifier.h
#
# Usage:
#   cd scripts/gen
#   python apply_avr_headers.py

import os, re, sys
sys.path.insert(0, os.path.dirname(__file__))
from gen_definitions import build_header, GUARD_MAP

DEF_DIR = os.path.normpath(os.path.join(
    os.path.dirname(__file__), "..", "..", "src", "definition"))
MANUAL_FILES = {
    "ublox_qzss_svid_prn_map.h",
    "qzss_dcx_camf_a3_provider_identifier.h",
    # Empty switch (0 entries) — transform would inject a dummy entry,
    # changing the lookup to return "" for id 0 instead of nullptr.
    "qzss_dcx_camf_a3_provider_identifier_map.h",
}


def unescape(s):
    """Reverse the C-string literal escaping applied by escape()."""
    out = []
    i = 0
    while i < len(s):
        if s[i] == '\\' and i + 1 < len(s):
            c = s[i + 1]
            if c == 'n':
                out.append('\n')
            elif c == 't':
                out.append('\t')
            elif c == 'r':
                out.append('\r')
            elif c == '0':
                # \0 embedded in label? Keep as literal (shouldn't happen in labels)
                out.append('\0')
            else:
                out.append(c)
            i += 2
        else:
            out.append(s[i])
            i += 1
    return ''.join(out)


def parse_header(filepath):
    """Parse a generated definition header. Returns (varname, ver, strat, use_optional, entries, all_varnames) or None."""
    with open(filepath, "r", encoding="utf-8") as f:
        content = f.read()

    # Extract metadata from header comment
    vname_m = re.search(r'// Variable\s*:\s*(\S+)', content)
    ver_m   = re.search(r'AUTO-GENERATED from azarashi\s+(\S+)', content)
    strat_m = re.search(r'// Strategy\s*:\s*(\w+)', content)
    if not vname_m or not ver_m or not strat_m:
        print(f"[SKIP] {filepath}: missing metadata comment")
        return None

    varname = vname_m.group(1)
    ver     = ver_m.group(1)
    strat   = strat_m.group(1)
    use_optional = "optional<std::string_view>" in content

    entries = {}

    # ---- Parse strategy-specific entries ----
    if strat == "switch":
        # switch + optional: case K: return std::string_view{"V", N};
        # switch + plain:    case K: return "V";
        if use_optional:
            for m in re.finditer(
                r'case (\d+): return std::string_view\{"((?:[^"\\]|\\.)*)", (\d+)\};',
                content
            ):
                entries[int(m.group(1))] = unescape(m.group(2))
            # Also match constexpr variant (non-AVR branch might be wrapped now)
            for m in re.finditer(
                r'case (\d+): return std::string_view\{"((?:[^"\\]|\\.)*)", (\d+)\}',
                content
            ):
                k = int(m.group(1))
                if k not in entries:
                    entries[k] = unescape(m.group(2))
        else:
            for m in re.finditer(
                r'case (\d+): return "((?:[^"\\]|\\.)*)";',
                content
            ):
                entries[int(m.group(1))] = unescape(m.group(2))

    elif strat == "array":
        # array + optional:  inline constexpr std::optional<std::string_view> GUARD_TABLE[] = { ... };
        # array + plain:     inline constexpr const char* GUARD_TABLE[] = { ... };
        base_m = re.search(r'GUARD_BASE = (\d+)', content)
        if not base_m:
            # Could also be {varname.upper()}_BASE
            base_m = re.search(r'(\w+)_BASE = (\d+)', content)
            base = int(base_m.group(2)) if base_m else 0
        else:
            base = int(base_m.group(1))

        if use_optional:
            table_m = re.search(
                r'std::optional<std::string_view>\s+\w+_TABLE\[\]\s*=\s*\{(.*?)\};', content, re.DOTALL)
            if table_m:
                rows = table_m.group(1)
                i = base
                for m in re.finditer(
                    r'std::string_view\{"((?:[^"\\]|\\.)*)", (\d+)\}', rows):
                    entries[i] = unescape(m.group(1))
                    i += 1
                # Count nullopt holes
                nullopt_count = rows.count("std::nullopt")
                i = base + nullopt_count
        else:
            table_m = re.search(
                r'const char\*\s+\w+_TABLE\[\]\s*=\s*\{(.*?)\};', content, re.DOTALL)
            if table_m:
                rows = table_m.group(1)
                i = base
                for m in re.finditer(r'"((?:[^"\\]|\\.)*)"', rows):
                    entries[i] = unescape(m.group(1))
                    i += 1

    elif strat == "binary_search":
        # bsearch + optional:  {Ku, std::string_view{"V", N}},
        # bsearch + plain:     {Ku, "V"},
        if use_optional:
            for m in re.finditer(
                r'\{(\d+)u, std::string_view\{"((?:[^"\\]|\\.)*)", (\d+)\}\}',
                content
            ):
                entries[int(m.group(1))] = unescape(m.group(2))
        else:
            for m in re.finditer(
                r'\{(\d+)u, "((?:[^"\\]|\\.)*)"\}',
                content
            ):
                entries[int(m.group(1))] = unescape(m.group(2))

    if not entries:
        print(f"[WARN] {filepath}: parsed 0 entries (strat={strat})")

    return varname, ver, strat, use_optional, entries


def main():
    header_files = sorted([
        f for f in os.listdir(DEF_DIR)
        if f.endswith(".h") and f not in MANUAL_FILES
    ])

    # Build all_varnames set (filenames minus .h)
    all_varnames = set()
    for f in os.listdir(DEF_DIR):
        if f.endswith(".h"):
            all_varnames.add(f[:-2])

    transformed = 0
    for hf in header_files:
        path = os.path.join(DEF_DIR, hf)
        parsed = parse_header(path)
        if parsed is None:
            continue
        varname, ver, strat, use_optional, entries = parsed
        if not entries:
            # Empty tables (like a3_provider_identifier_map) still get an
            # entry dict with 0 keys → build_header returns None.
            # Force at least one entry so the header is generated.
            if use_optional:
                entries = {0: None}  # dummy to trigger generation
            else:
                entries = {0: ""}

        # Derive modname from varname (usually the module name is the
        # directory basename in azarashi — not needed for header output,
        # but build_header uses it in the comment)
        modname = varname

        hdr = build_header(
            modname, varname, entries, ver, all_varnames,
            obj=None, use_optional_override=use_optional)
        if hdr is None:
            print(f"[SKIP] {hf}: build_header returned None")
            continue

        with open(path, "w", encoding="utf-8") as f:
            f.write(hdr)
        print(f"[OK] {hf}  ({len(entries)} entries, strat={strat})")
        transformed += 1

    print(f"\nTransformed {transformed} headers in {DEF_DIR}")


if __name__ == "__main__":
    main()
