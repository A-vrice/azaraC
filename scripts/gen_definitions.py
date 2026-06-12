#!/usr/bin/env python3
# azaraC - scripts/gen_definitions.py
# Generates include/definition/*.h from azarashi (installed in current env).
#
# Usage:
#   pip install azarashi==<version>
#   python scripts/gen_definitions.py [--out-dir include/definition]

import argparse, importlib, os, pkgutil, sys
sys.path.insert(0, os.path.dirname(__file__))
from strategy import choose, key_type

GUARD_MAP = {
    "qzss_dcr_jma_eew_forecast_region": "AZARAC_ENABLE_EEW",
    "qzss_dcr_jma_epicenter_and_hypocenter": "(AZARAC_ENABLE_EEW || AZARAC_ENABLE_HYPOCENTER)",
    "qzss_dcr_jma_seismic_intensity_lower_limit": "AZARAC_ENABLE_EEW",
    "qzss_dcr_jma_seismic_intensity_upper_limit": "AZARAC_ENABLE_EEW",
    "qzss_dcr_jma_long_period_ground_motion_lower_limit": "AZARAC_ENABLE_EEW",
    "qzss_dcr_jma_long_period_ground_motion_upper_limit": "AZARAC_ENABLE_EEW",
    "qzss_dcr_jma_seismic_intensity": "AZARAC_ENABLE_SEISMIC",
    "qzss_dcr_jma_prefecture": "AZARAC_ENABLE_SEISMIC",
    "qzss_dcr_jma_information_serial_code": "AZARAC_ENABLE_NANKAI",
    "qzss_dcr_jma_tsunami_forecast_region": "AZARAC_ENABLE_TSUNAMI",
    "qzss_dcr_jma_tsunami_height": "AZARAC_ENABLE_TSUNAMI",
    "qzss_dcr_jma_tsunami_warning_code": "AZARAC_ENABLE_TSUNAMI",
    "qzss_dcr_jma_northwest_pacific_tsunami_height_en": "AZARAC_ENABLE_NW_PAC_TSUNAMI",
    "qzss_dcr_jma_coastal_region_en": "AZARAC_ENABLE_NW_PAC_TSUNAMI",
    "qzss_dcr_jma_tsunamigenic_potential_en": "AZARAC_ENABLE_NW_PAC_TSUNAMI",
    "qzss_dcr_jma_volcanic_warning_code": "AZARAC_ENABLE_VOLCANO",
    "qzss_dcr_jma_volcano_name": "AZARAC_ENABLE_VOLCANO",
    "qzss_dcr_jma_ash_fall_warning_code": "AZARAC_ENABLE_ASH_FALL",
    "qzss_dcr_jma_local_government": "(AZARAC_ENABLE_VOLCANO || AZARAC_ENABLE_ASH_FALL)",
    "qzss_dcr_jma_weather_forecast_region": "AZARAC_ENABLE_WEATHER",
    "qzss_dcr_jma_weather_related_disaster_sub_category": "AZARAC_ENABLE_WEATHER",
    "qzss_dcr_jma_weather_warning_state": "AZARAC_ENABLE_WEATHER",
    "qzss_dcr_jma_flood_forecast_region": "AZARAC_ENABLE_FLOOD",
    "qzss_dcr_jma_flood_warning_level": "AZARAC_ENABLE_FLOOD",
    "qzss_dcr_jma_typhoon_intensity_category": "AZARAC_ENABLE_TYPHOON",
    "qzss_dcr_jma_typhoon_reference_time_type": "AZARAC_ENABLE_TYPHOON",
    "qzss_dcr_jma_typhoon_scale_category": "AZARAC_ENABLE_TYPHOON",
    "qzss_dcr_jma_marine_forecast_region": "AZARAC_ENABLE_MARINE",
    "qzss_dcr_jma_marine_warning_code": "AZARAC_ENABLE_MARINE",
    "qzss_dcr_jma_notification_on_disaster_prevention": "(AZARAC_ENABLE_EEW || AZARAC_ENABLE_HYPOCENTER)",
}

BASE_MOD = "azarashi.qzss_dcr_lib.definition"

def get_azarashi_version():
    try:
        from importlib.metadata import version
        return version("azarashi")
    except Exception:
        return "unknown"

def find_def_path():
    import azarashi.qzss_dcr_lib.definition as d
    return os.path.dirname(d.__file__)

def escape(s):
    return (str(s).replace("\\", "\\\\")
                  .replace('"', '\\"')
                  .replace("\n", "\\n")
                  .replace("\r", ""))

def sv_literal(s):
    """Return a std::string_view literal with explicit length to avoid
    std::char_traits<char>::length() which is not constexpr on older libstdc++."""
    escaped = escape(s)
    byte_len = len(escaped.encode("utf-8"))
    return f'std::string_view{{"{escaped}", {byte_len}}}'

def emit_switch(varname, entries, guard, kt):
    lines = [f"[[nodiscard]] inline constexpr std::optional<std::string_view> {varname}_lookup({kt} id) {{",
             "    switch (id) {"]
    for k, v in sorted(entries.items()):
        lines.append(f'        case {k}: return {sv_literal(v)};')
    lines += ['        default: return std::nullopt;', "    }", "}"]
    return "\n".join(lines)

def emit_array(varname, entries, guard, kt):
    keys = sorted(entries.keys())
    base, top = keys[0], keys[-1]
    table = [entries.get(i) for i in range(base, top + 1)]
    rows = ",\n    ".join(
        sv_literal(v) if v is not None else "std::nullopt" for v in table)
    return "\n".join([
        f"inline constexpr std::optional<std::string_view> {guard}_TABLE[] = {{",
        f"    {rows}", "};",
        f"inline constexpr {kt} {guard}_BASE = {base};",
        f"inline constexpr {kt} {guard}_SIZE = {top - base + 1};",
        f"[[nodiscard]] inline constexpr std::optional<std::string_view> {varname}_lookup({kt} id) {{",
        f"    if (id < {guard}_BASE || id >= {guard}_BASE + {guard}_SIZE) return std::nullopt;",
        f"    return {guard}_TABLE[id - {guard}_BASE];", "}",
    ])

def emit_bsearch(varname, entries, guard, kt):
    keys = sorted(entries.keys())
    n = len(keys)
    idx_type = "uint8_t" if n <= 255 else ("uint16_t" if n <= 65535 else "uint32_t")
    rows = "\n".join(f'    {{{k}u, {sv_literal(entries[k])}}},\n' for k in keys)
    return "\n".join([
        f"struct {guard}_Entry {{ {kt} id; std::string_view label; }};",
        f"inline constexpr {guard}_Entry {guard}_TABLE[] = {{",
        rows + "};",
        f"[[nodiscard]] inline constexpr std::optional<std::string_view> {varname}_lookup({kt} id) {{",
        f"    {idx_type} lo = 0, hi = {n};",
        "    while (lo < hi) {",
        f"        {idx_type} mid = static_cast<{idx_type}>(lo + (hi - lo) / 2);",
        f"        if ({guard}_TABLE[mid].id == id) return {guard}_TABLE[mid].label;",
        f"        if ({guard}_TABLE[mid].id < id) lo = mid + 1;",
        "        else hi = mid;",
        "    }",
        "    return std::nullopt;", "}",
    ])

def build_header(modname, varname, entries, ver, all_varnames):
    keys = [k for k in entries.keys() if isinstance(k, int)]
    if not keys: return None
    int_entries = {k: entries[k] for k in keys}
    guard = varname.upper()
    kt    = key_type(keys)
    strat = choose(keys)
    if   strat == "switch": body = emit_switch(varname, int_entries, guard, kt)
    elif strat == "array":  body = emit_array(varname, int_entries, guard, kt)
    else:                   body = emit_bsearch(varname, int_entries, guard, kt)

    category_guard = GUARD_MAP.get(varname)
    lang_guard = None
    if varname.endswith("_en"):
        lang_guard = "AZARAC_LANG_EN"
    elif varname.endswith("_ja"):
        lang_guard = "AZARAC_LANG_JA"
    elif f"{varname}_en" in all_varnames:
        lang_guard = "AZARAC_LANG_JA"

    def wrap_guard(expr):
        s = expr.strip()
        if s.startswith("(") and s.endswith(")"):
            return s
        return f"({expr})"

    guards = []
    if category_guard:
        guards.append(wrap_guard(category_guard))
    if lang_guard:
        guards.append(wrap_guard(lang_guard))

    if guards:
        full_guard = " && ".join(guards)
        wrapped_body = f"#if {full_guard}\n\n{body}\n\n#else\n\n"
        wrapped_body += f"[[nodiscard]] inline constexpr std::optional<std::string_view> {varname}_lookup({kt} id) {{\n"
        wrapped_body += "    (void)id;\n    return std::nullopt;\n}\n\n#endif\n"
    else:
        wrapped_body = f"{body}\n"

    return (
        f"#pragma once\n"
        f"// AUTO-GENERATED from azarashi {ver} with CI-CD\n"
        f"// Source module : {modname}\n"
        f"// Variable      : {varname}\n"
        f"// Entries       : {len(keys)}\n"
        f"// Strategy      : {strat}\n\n"
        f"#include <cstdint>\n"
        f"#include <optional>\n"
        f"#include <string_view>\n"
        f'#include "../azaraC.h"\n\n'
        f"namespace azaraC {{\nnamespace def {{\n\n"
        f"{wrapped_body}\n"
        f"}} // namespace def\n}} // namespace azaraC\n"
    )

def run(out_dir):
    os.makedirs(out_dir, exist_ok=True)
    base_path = find_def_path()
    ver = get_azarashi_version()
    generated = []
    all_varnames = set()
    for _, modname, _ in pkgutil.iter_modules([base_path]):
        try:
            mod = importlib.import_module(f"{BASE_MOD}.{modname}")
        except Exception:
            continue
        for attr in dir(mod):
            if not attr.startswith("_") and isinstance(getattr(mod, attr), dict):
                all_varnames.add(attr)

    for _, modname, _ in pkgutil.iter_modules([base_path]):
        try:
            mod = importlib.import_module(f"{BASE_MOD}.{modname}")
        except Exception as e:
            print(f"[WARN] skip {modname}: {e}", file=sys.stderr)
            continue
        for attr in dir(mod):
            if attr.startswith("_"): continue
            obj = getattr(mod, attr)
            if not isinstance(obj, dict): continue
            hdr = build_header(modname, attr, obj, ver, all_varnames)
            if hdr is None: continue
            with open(os.path.join(out_dir, f"{attr}.h"), "w", encoding="utf-8") as f:
                f.write(hdr)
            generated.append(attr)
    # _index.h
    idx = (
        "#pragma once\n"
        f"// AUTO-GENERATED from azarashi {ver} — do not edit\n"
        f"// {len(generated)} definition headers\n\n"
        + "\n".join(f'#include "{a}.h"' for a in sorted(generated))
        + "\n"
        + '#include "ublox_qzss_svid_prn_map.h"\n'
        + '#include "qzss_dcx_camf_a3_provider_identifier.h"\n'
    )
    with open(os.path.join(out_dir, "_index.h"), "w", encoding="utf-8") as f:
        f.write(idx)
    # version marker (write to repo root, relative to script location)
    repo_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    with open(os.path.join(repo_root, ".azarashi-version"), "w") as f:
        f.write(ver + "\n")
    print(f"Generated {len(generated)} headers + _index.h  (azarashi {ver})")

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--out-dir", default="include/definition")
    args = parser.parse_args()
    run(args.out_dir)
