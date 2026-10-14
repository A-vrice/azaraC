#!/usr/bin/env python3
# azaraC - scripts/gen_definitions.py
# Generates src/definition/*.h from azarashi (installed in current env).
#
# Usage:
#   pip install azarashi==<version>
#   python scripts/gen_definitions.py [--out-dir src/definition]

import argparse
import importlib
import os
import pkgutil
import sys

sys.path.insert(0, os.path.dirname(__file__))
from strategy import choose, key_type, uint_type, factor_parents, PARENT_NONE

GUARD_MAP = {
    "qzss_dcr_jma_eew_forecast_region": "AZARAC_ENABLE_EEW",
    "qzss_dcr_jma_epicenter_and_hypocenter": "(AZARAC_ENABLE_EEW || AZARAC_ENABLE_HYPOCENTER)",
    "qzss_dcr_jma_seismic_intensity_lower_limit": "AZARAC_ENABLE_EEW",
    "qzss_dcr_jma_seismic_intensity_upper_limit": "AZARAC_ENABLE_EEW",
    "qzss_dcr_jma_long_period_ground_motion_lower_limit": "AZARAC_ENABLE_EEW",
    "qzss_dcr_jma_long_period_ground_motion_upper_limit": "AZARAC_ENABLE_EEW",
    "qzss_dcr_jma_seismic_intensity": "AZARAC_ENABLE_SEISMIC",
    "qzss_dcr_jma_prefecture": "(AZARAC_ENABLE_SEISMIC || AZARAC_ENABLE_DCX_CAMF)",
    "qzss_dcr_jma_information_serial_code": "AZARAC_ENABLE_NANKAI",
    "qzss_dcr_jma_tsunami_forecast_region": "AZARAC_ENABLE_TSUNAMI",
    "qzss_dcr_jma_tsunami_height": "AZARAC_ENABLE_TSUNAMI",
    "qzss_dcr_jma_tsunami_warning_code": "AZARAC_ENABLE_TSUNAMI",
    "qzss_dcr_jma_northwest_pacific_tsunami_height_en": "AZARAC_ENABLE_NW_PAC_TSUNAMI",
    "qzss_dcr_jma_coastal_region_en": "AZARAC_ENABLE_NW_PAC_TSUNAMI",
    "qzss_dcr_jma_tsunamigenic_potential_en": "AZARAC_ENABLE_NW_PAC_TSUNAMI",
    "qzss_dcr_jma_volcanic_warning_code": "AZARAC_ENABLE_VOLCANO",
    "qzss_dcr_jma_volcano_name": "(AZARAC_ENABLE_VOLCANO || AZARAC_ENABLE_ASH_FALL)",
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
    "qzss_dcx_camf_a1_message_type": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_a2_country_region_name": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_a3_provider_identifier": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_a3_provider_identifier_australia": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_a3_provider_identifier_fiji": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_a3_provider_identifier_japan": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_a3_provider_identifier_map": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_a3_provider_identifier_thailand": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_a4_hazard_category": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_a4_hazard_definition": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_a4_hazard_type": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_a5_severity": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_a6_hazard_onset_week": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_a8_hazard_duration": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_a9_type_of_library": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_a10_library_version": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_a11_international_library": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_a11_international_library_b": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_a11_japanese_library_en": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_a11_japanese_library_ja": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_a17_type_of_specific_settings": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_c10_instruction_library_for_second_ellipse": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_c10_instruction_library_for_second_ellipse_code": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d1_magnitude_on_richter_scale": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d2_seismic_coefficient": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d3_azimuth_from_centre_of_main_ellipse_to_epicentre": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d4_vector_length_between_centre_of_main_ellipse_and_epicentre": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d5_wave_height": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d6_temperature_range": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d7_hurricane_category": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d8_wind_speed": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d9_rainfall_amounts": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d10_damage_category": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d11_tornado_probability": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d12_hail_scale": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d13_visibility": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d14_snow_depth": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d15_flood_severity": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d16_lightning_intensity": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d17_fog_level": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d18_drought_level": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d19_avalanche_warning_level": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d20_ash_fall_amount_and_impact": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d21_geomagnetic_scale": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d22_terrorism_threat_level": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d23_fire_risk_level": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d24_water_quality": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d25_uv_index": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d26_number_of_cases_per_100000_inhabitants": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d27_noise_range": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d28_air_quality_index": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d29_outage_estimated_duration": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d30_nuclear_event_scale": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d31_chemical_hazard_type": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d32_biohazard_level": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d33_biohazard_type": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d34_explosive_hazard_type": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d35_infection_type": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_d36_typhoon_category": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_ex9_target_area_code_en": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_camf_ex9_target_area_code_ja": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_ex1_target_area_code_en": "AZARAC_ENABLE_DCX_CAMF",
    "qzss_dcx_ex1_target_area_code_ja": "AZARAC_ENABLE_DCX_CAMF",

    # azarashi 0.17 added these. Their *_en siblings inherit the guard of the
    # JA table they translate (see category_guard_for), so only the tables with
    # no JA sibling are listed here.
    "qzss_dcr_jma_ambiguity_of_activity_time_en": "(AZARAC_ENABLE_VOLCANO || AZARAC_ENABLE_ASH_FALL)",
    "qzss_dcr_jma_ash_fall_warning_type": "AZARAC_ENABLE_ASH_FALL",
    "qzss_dcr_jma_depth_of_hypocenter": (
        "(AZARAC_ENABLE_EEW || AZARAC_ENABLE_HYPOCENTER || AZARAC_ENABLE_NW_PAC_TSUNAMI)"),
    "qzss_dcr_jma_eew_magnitude": "AZARAC_ENABLE_EEW",
    "qzss_dcr_jma_expected_ash_fall_time": "AZARAC_ENABLE_ASH_FALL",
    "qzss_dcr_jma_hypocenter_magnitude": "(AZARAC_ENABLE_HYPOCENTER || AZARAC_ENABLE_NW_PAC_TSUNAMI)",
    "qzss_dcr_jma_typhoon_central_pressure": "AZARAC_ENABLE_TYPHOON",
    "qzss_dcr_jma_typhoon_elapsed_time_from_reference_time": "AZARAC_ENABLE_TYPHOON",
    "qzss_dcr_jma_typhoon_maximum_gust_wind_speed": "AZARAC_ENABLE_TYPHOON",
    "qzss_dcr_jma_typhoon_maximum_wind_speed": "AZARAC_ENABLE_TYPHOON",
    "qzss_dcr_jma_typhoon_number": "AZARAC_ENABLE_TYPHOON",
}

# Modules / variables to skip during generation (handled manually, or not scalar).
# Matched against both the source module name and the generated variable name.
SKIP_MODULES = {
    # hand-written: the lookup must stay std::optional (see developer-guide.md)
    "ublox_qzss_svid_prn_map",
    "svid_to_prn",
    "qzss_dcx_camf_a3_provider_identifier",
    # azaraC resolves no EX9 area code, so these tables have no consumer
    "qzss_dcx_camf_ex9_target_area_code_en",
    "qzss_dcx_camf_ex9_target_area_code_ja",
    "ex9_target_area_code_en",
    "ex9_target_area_code_ja",
    # not scalar-valued: a dict of tables, an empty table, and a NamedTuple
    "a3_provider_identifier_map",
    "a3_provider_identifier_undefined",
    "a11_library",
    # JSON v2 でラベルを消した／ガードが未定義／消費者が無い表（2026-10 時点で参照ゼロ）
    "qzss_dcr_message_type",
    "qzss_dcr_satellite_prn",
    "qzss_dcr_preamble",
    "qzss_dcx_camf_a11_international_library_code",
    # azarashi 0.17.1 が追加した表のうち azaraC に消費者が無いもの
    "qzss_dcx_camf_a11_international_library_b_code",     # IC-B-nn のコード名（JSON はコード名を出さない）
    "qzss_dcx_camf_c7_shift_of_second_ellipse_centre",    # azaraC は c7/c8/c9 を生値のみ出力
    "qzss_dcx_camf_c8_homothetic_factor_of_second_ellipse",
    "qzss_dcx_camf_c9_bearing_angle_of_second_ellipse",
    "qzss_dcx_ex2_evacuate_direction_type",               # azaraC は EX2 を head_to_area(0/1) の生値のみ出力
}

BASE_MOD = "azarashi.definitions"

def category_guard_for(varname):
    """Resolve the AZARAC_ENABLE_* guard for a table, with inheritance.

    An *_en / *_ja table holds the same data as the table it translates, so it
    must carry that table's category guard. Looking the name up verbatim (the
    old behaviour) left every translated table guarded only by AZARAC_LANG_EN,
    so `-DAZARAC_ENABLE_TSUNAMI=0` dropped the Japanese table from Flash while
    the English one stayed: the macro saved half of what it promises, and the
    JA and EN tables stopped covering the same codes. The comment on GUARD_MAP
    has always claimed the sibling inherits; this makes it true.

    The exact name still wins, because a few families (a11_japanese_library,
    ex1_target_area_code, ex9_target_area_code) exist only as _en/_ja and
    register the guard on those names with no base table to inherit from.
    """
    if varname in GUARD_MAP:
        return GUARD_MAP[varname]
    for suffix, sibling in (("_en", "_ja"), ("_ja", "_en")):
        if not varname.endswith(suffix):
            continue
        base = varname[: -len(suffix)]
        for candidate in (base, base + sibling):
            if candidate in GUARD_MAP:
                return GUARD_MAP[candidate]
    return None

# Modules under azarashi.definitions whose tables reuse azaraC's existing C++
# variable names. azarashi 0.17 dropped the spec prefix from the variable name
# and moved the module; these are the names the two differ on.
NAME_OVERRIDE = {
    "preambles": "qzss_dcr_preamble",
    "message_types": "qzss_dcr_message_type",
    "svid_to_prn": "ublox_qzss_svid_prn_map",
    "message_type": "qzss_dcx_message_type",
}

def _prefix_for(modname):
    """The C++ namespace prefix azaraC's callers already use for a 0.17 module."""
    sub = modname.split(".")
    if sub[0] != "azarashi" or sub[1] != "definitions":
        raise ValueError(f"module outside {BASE_MOD}: {modname}")
    rest = sub[2:]
    if rest[:1] == ["camf"]:
        return "qzss_dcx_camf_"
    if rest[:2] == ["qzss", "dcr"]:
        return "qzss_dcr_jma_"
    if rest[:2] == ["qzss", "dcx"]:
        return "qzss_dcx_"
    if rest[:2] == ["qzss", "l1s"]:
        return "qzss_dcr_"
    if rest[:2] == ["qzss", "ubx"]:
        return "ublox_qzss_"
    raise ValueError(f"no variable-name prefix rule for module: {modname}")

def get_azarashi_version():
    from importlib.metadata import PackageNotFoundError, version

    try:
        return version("azarashi")
    except PackageNotFoundError:
        return "unknown"

def find_def_path():
    import azarashi.definitions as d
    return os.path.dirname(d.__file__)

def iter_definition_modules(base_path):
    """Every module under azarashi.definitions, at any depth."""
    for _, modname, _ in pkgutil.walk_packages([base_path], BASE_MOD + "."):
        yield modname

def tables_of(modname):
    """(varname, entries) for each code table a module defines."""
    mod = importlib.import_module(modname)
    for attr in dir(mod):
        if attr.startswith("_") or attr in SKIP_MODULES or attr == "CodeTable":
            continue
        obj = getattr(mod, attr)
        if not isinstance(obj, dict):
            continue  # CodeTable is a dict; a dict of tables / a NamedTuple is not
        varname = NAME_OVERRIDE.get(attr, _prefix_for(modname) + attr)
        if varname.endswith("_value"):
            continue  # コード→物理量表。azaraC は生コード + ラベルしか出さない（消費者ゼロ）
        if varname in SKIP_MODULES:
            continue
        yield varname, obj

def escape(s):
    return (str(s).replace("\\", "\\\\")
                  .replace('"', '\\"')
                  .replace("\n", "\\n")
                  .replace("\r", ""))

def c_str_literal(s):
    """Return a C-string literal for const char* return type."""
    escaped = escape(s)
    return f'"{escaped}"'

# --- AVR label storage ------------------------------------------------------
# A pool-backed AVR table stores its labels as one NUL-separated literal plus
# rows of {key, offset, len}. Two families (target_area_code, local_government)
# repeat the region a label belongs to on every row — "Sapporo City, Hokkaido
# Prefecture", "北海道札幌市" — so factor_parents (strategy.py) can split those
# labels into a child and a shared parent name; the row then carries a parent
# index and the lookup joins the halves in FlashString's shared RAM buffer, so
# SRAM does not grow. The plain layout stays the default: it is preferred
# whenever factoring does not actually save bytes.

def _len_type(labels) -> str:
    """Narrowest type that holds the longest label (AVR entry `len` field)."""
    return uint_type(max((len(v.encode('utf-8')) for v in labels), default=0))

def _pool_decl(guard, name, strings):
    """The NUL-separated pool literal, plus the {offset, len} of each label."""
    parts, offsets, cur = [], {}, 0
    for key, s in strings:
        b = s.encode('utf-8')
        parts.append(escape(s) + "\\000")
        offsets[key] = (cur, len(b))
        cur += len(b) + 1
    return f'static const char AZARAC_PROGMEM {guard}_{name}[] = "{"".join(parts)}";', offsets

def _read(struct, field, ptr, ltype):
    """pgm_read_* for a struct field of the given width."""
    return (f"pgm_read_byte({ptr} + offsetof({struct}, {field}))" if ltype == "uint8_t"
            else f"pgm_read_word({ptr} + offsetof({struct}, {field}))")

def avr_label_storage(guard, kt, keys, entries, ptr, as_cstr=False):
    """AVR storage for a key-indexed label table.

    Returns (decls, fetch). `decls` holds the pool, the shared-parent pool when
    one pays off, the row structs and the row arrays, in dependency order.
    `fetch` turns the row at pointer `ptr` into a label (and returns it): a
    std::string_view, or the same buffer as a NUL-terminated const char* when
    `as_cstr`.
    """
    plan = factor_parents(entries)
    children = plan["children"] if plan else entries
    entry = f"{guard}_Entry"
    ltype = _len_type(children.values())
    pool, offs = _pool_decl(guard, "POOL", [(k, children[k]) for k in keys])
    decls = [pool]
    fetch = [f"uint16_t off = {_read(entry, 'offset', ptr, 'uint16_t')};",
             f"{ltype} n = {_read(entry, 'len', ptr, ltype)};"]
    ret = ".data()" if as_cstr else ""
    if plan:
        parent = f"{guard}_PARENT_Entry"
        pltype = _len_type(plan["parents"])
        ppool, poffs = _pool_decl(guard, "PARENT_POOL", list(enumerate(plan["parents"])))
        decls += [
            ppool,
            f"struct {parent} {{ uint16_t offset; {pltype} len; }};",
            f"static const {parent} {guard}_PARENT_TABLE[] AZARAC_PROGMEM = {{",
            "\n".join(f'    {{{poffs[i][0]}u, {poffs[i][1]}u}},' for i in range(len(plan["parents"]))),
            "};",
            f"struct {entry} {{ {kt} id; uint8_t parent; uint16_t offset; {ltype} len; }};",
        ]
        rows = [f'    {{{k}u, {sel}u, {offs[k][0]}u, {offs[k][1]}u}},'
                for k, sel in ((k, plan["sel"][k] if plan["sel"][k] is not None else PARENT_NONE)
                               for k in keys)]
        fetch += [
            f"uint8_t pi = {_read(entry, 'parent', ptr, 'uint8_t')};",
            f"if (pi == {PARENT_NONE}u) return azarac_pgm_view({guard}_POOL + off, n){ret};",
            f"const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&{guard}_PARENT_TABLE[pi]);",
            f"uint16_t poff = {_read(parent, 'offset', 'pp', 'uint16_t')};",
            f"{pltype} pn = {_read(parent, 'len', 'pp', pltype)};",
            # 'pre': "北海道" + "札幌市"; 'post': "Sapporo City" + ", Hokkaido Prefecture".
            f"return azarac_pgm_join({guard}_PARENT_POOL + poff, pn, {guard}_POOL + off, n){ret};"
            if plan["order"] == "pre" else
            f"return azarac_pgm_join({guard}_POOL + off, n, {guard}_PARENT_POOL + poff, pn){ret};",
        ]
    else:
        rows = [f'    {{{k}u, {offs[k][0]}u, {offs[k][1]}u}},' for k in keys]
        decls += [f"struct {entry} {{ {kt} id; uint16_t offset; {ltype} len; }};"]
        fetch += [f"return azarac_pgm_view({guard}_POOL + off, n){ret};"]
    decls += [f"static const {entry} {guard}_TABLE[] AZARAC_PROGMEM = {{",
              "\n".join(rows),
              "};"]
    return decls, fetch

def avr_positional_label_storage(guard, table, ptr):
    """AVR storage for an array-strategy table: rows are addressed by
    `id - BASE`, so they carry no id column. `table[i]` is the label at that id
    (None = the id is not defined). Returns (decls, fetch) like
    avr_label_storage; `fetch` leaves the label's length in `n`.
    """
    labels = {i: v for i, v in enumerate(table) if v is not None}
    plan = factor_parents(labels)
    children = plan["children"] if plan else labels
    entry = f"{guard}_Entry"
    ltype = _len_type(children.values())
    pool, offs = _pool_decl(guard, "POOL", [(i, children.get(i, "")) for i in range(len(table))])
    decls = [pool]
    fetch = [f"uint16_t off = {_read(entry, 'offset', ptr, 'uint16_t')};",
             f"{ltype} n = {_read(entry, 'len', ptr, ltype)};"]
    if plan:
        parent = f"{guard}_PARENT_Entry"
        pltype = _len_type(plan["parents"])
        ppool, poffs = _pool_decl(guard, "PARENT_POOL", list(enumerate(plan["parents"])))
        decls += [
            ppool,
            f"struct {parent} {{ uint16_t offset; {pltype} len; }};",
            f"static const {parent} {guard}_PARENT_TABLE[] AZARAC_PROGMEM = {{",
            "\n".join(f'    {{{poffs[i][0]}u, {poffs[i][1]}u}},' for i in range(len(plan["parents"]))),
            "};",
            f"struct {entry} {{ uint16_t offset; {ltype} len; uint8_t parent; }};",
        ]
        rows = [f'    {{{offs[i][0]}u, {offs[i][1]}u, {sel}u}}'
                for i, sel in ((i, plan["sel"][i] if i in plan["sel"] and plan["sel"][i] is not None
                                else PARENT_NONE)
                               for i in range(len(table)))]
        fetch += [
            f"uint8_t pi = {_read(entry, 'parent', ptr, 'uint8_t')};",
            f"if (pi == {PARENT_NONE}u) return azarac_pgm_view({guard}_POOL + off, n);",
            f"const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&{guard}_PARENT_TABLE[pi]);",
            f"uint16_t poff = {_read(parent, 'offset', 'pp', 'uint16_t')};",
            f"{pltype} pn = {_read(parent, 'len', 'pp', pltype)};",
            f"return azarac_pgm_join({guard}_PARENT_POOL + poff, pn, {guard}_POOL + off, n);"
            if plan["order"] == "pre" else
            f"return azarac_pgm_join({guard}_POOL + off, n, {guard}_PARENT_POOL + poff, pn);",
        ]
    else:
        rows = [f'    {{{offs[i][0]}u, {offs[i][1]}u}}' for i in range(len(table))]
        decls += [f"struct {entry} {{ uint16_t offset; {ltype} len; }};"]
        fetch += [f"return azarac_pgm_view({guard}_POOL + off, n);"]
    decls += [f"static const {entry} {guard}_TABLE[] AZARAC_PROGMEM = {{",
              ",\n".join(rows),
              "};"]
    return decls, fetch

def emit_switch(varname, entries, guard, kt):
    avr_cases = "\n".join(
        f'        case {k}: {{ static const char AZARAC_PROGMEM s[] = {c_str_literal(v)}; return azarac_pgm_copy(s); }}'
        for k, v in sorted(entries.items()))
    avr_body = "\n".join([
        f"[[nodiscard]] inline const char* {varname}_lookup({kt} id) noexcept {{",
        "    switch (id) {",
        avr_cases,
        "        default: return nullptr;",
        "    }",
        "}",
    ])
    non_avr_cases = "\n".join(
        f'        case {k}: return {c_str_literal(v)};' for k, v in sorted(entries.items()))
    non_avr_body = "\n".join([
        f"[[nodiscard]] inline constexpr const char* {varname}_lookup({kt} id) noexcept {{",
        "    switch (id) {",
        non_avr_cases,
        "        default: return nullptr;",
        "    }",
        "}",
    ])
    return f"#if defined(__AVR__)\n{avr_body}\n#else\n{non_avr_body}\n#endif"


def emit_switch_optional(varname, entries, guard, kt):
    avr_cases = []
    for k, v in sorted(entries.items()):
        if v is not None:
            byte_len = len(v.encode('utf-8'))
            avr_cases.append(
                f'        case {k}: {{ static const char AZARAC_PROGMEM s[] = {c_str_literal(v)}; '
                f'return azarac_pgm_view(s, {byte_len}); }}')
        else:
            avr_cases.append(f'        case {k}: return std::nullopt;')
    avr_body = "\n".join([
        f"[[nodiscard]] inline std::optional<std::string_view> {varname}_lookup({kt} id) noexcept {{",
        "    switch (id) {",
        *avr_cases,
        "        default: return std::nullopt;",
        "    }",
        "}",
    ])
    non_avr_cases = []
    for k, v in sorted(entries.items()):
        if v is not None:
            byte_len = len(v.encode('utf-8'))
            non_avr_cases.append(f'        case {k}: return std::string_view{{{c_str_literal(v)}, {byte_len}}};')
        else:
            non_avr_cases.append(f'        case {k}: return std::nullopt;')
    non_avr_body = "\n".join([
        f"[[nodiscard]] inline constexpr std::optional<std::string_view> {varname}_lookup({kt} id) noexcept {{",
        "    switch (id) {",
        *non_avr_cases,
        "        default: return std::nullopt;",
        "    }",
        "}",
    ])
    return f"#if defined(__AVR__)\n{avr_body}\n#else\n{non_avr_body}\n#endif"


def emit_array(varname, entries, guard, kt):
    keys = sorted(entries.keys())
    base, top = keys[0], keys[-1]
    table = [entries.get(i) for i in range(base, top + 1)]
    n = len(table)
    # AVR: string pool + offset table
    pool_parts = []
    offsets = []
    cur = 0
    for v in table:
        if v is not None:
            b = v.encode('utf-8')
            pool_parts.append(escape(v) + "\\000")
            offsets.append((cur, len(b)))
            cur += len(b) + 1
        else:
            pool_parts.append("\\000")
            offsets.append((0, 0))
            cur += 1
    pool_str = "".join(pool_parts)
    avr_body = "\n".join([
        f'static const char AZARAC_PROGMEM {guard}_POOL[] = "{pool_str}";',
        # The copy-based lookup stops at the NUL that already ends each pool
        # entry, so these rows only need the offset: the len field the
        # string_view tables carry would be dead weight here.
        f"struct {guard}_Entry {{ uint16_t offset; }};",
        f"static const {guard}_Entry {guard}_TABLE[] AZARAC_PROGMEM = {{",
        ",\n".join(f"    {{{off}u}}" for off, _ in offsets),
        "};",
        f"[[nodiscard]] inline const char* {varname}_lookup({kt} id) noexcept {{",
        f"    if (id < {guard}_BASE || id >= {guard}_BASE + {guard}_SIZE) return nullptr;",
        f"    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&{guard}_TABLE[id - {base}u]);",
        f"    uint16_t off = pgm_read_word(p + offsetof({guard}_Entry, offset));",
        f"    return azarac_pgm_copy({guard}_POOL + off);",
        "}",
    ])
    # Non-AVR (unchanged constexpr logic)
    rows = ",\n    ".join(
        c_str_literal(v) if v is not None else "nullptr" for v in table)
    non_avr_body = "\n".join([
        f"inline constexpr const char* {guard}_TABLE[] = {{",
        f"    {rows}", "};",
        f"[[nodiscard]] inline constexpr const char* {varname}_lookup({kt} id) noexcept {{",
        f"    if (id < {guard}_BASE || id >= {guard}_BASE + {guard}_SIZE) return nullptr;",
        f"    return {guard}_TABLE[id - {guard}_BASE];", "}",
    ])
    return "\n".join([
        f"inline constexpr {kt} {guard}_BASE = {base};",
        f"inline constexpr {kt} {guard}_SIZE = {n};",
        "#if defined(__AVR__)",
        avr_body,
        "#else",
        non_avr_body,
        "#endif",
    ])


def emit_array_optional(varname, entries, guard, kt):
    keys = sorted(entries.keys())
    base, top = keys[0], keys[-1]
    table = [entries.get(i) for i in range(base, top + 1)]
    n = len(table)
    decls, fetch = avr_positional_label_storage(guard, table, "p")
    avr_body = "\n".join(decls + [
        f"[[nodiscard]] inline std::optional<std::string_view> {varname}_lookup({kt} id) noexcept {{",
        f"    if (id < {guard}_BASE || id >= {guard}_BASE + {guard}_SIZE) return std::nullopt;",
        f"    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&{guard}_TABLE[id - {base}u]);",
        *[f"    {line}" for line in fetch],
        "}",
    ])
    # Non-AVR: const char* payload (4 B on 32-bit targets vs 12 B for a
    # std::optional<std::string_view> entry).  The lookup still returns
    # std::optional<std::string_view> so that absent (nullptr) and
    # defined-but-empty ("") stay distinguishable at the call site.
    rows = ",\n    ".join(
        c_str_literal(v) if v is not None else "nullptr" for v in table)
    non_avr_body = "\n".join([
        f"inline constexpr const char* {guard}_TABLE[] = {{",
        f"    {rows}", "};",
        f"[[nodiscard]] inline constexpr std::optional<std::string_view> {varname}_lookup({kt} id) noexcept {{",
        f"    if (id < {guard}_BASE || id >= {guard}_BASE + {guard}_SIZE) return std::nullopt;",
        f"    const char* s = {guard}_TABLE[id - {guard}_BASE];",
        "    return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;", "}",
    ])
    return "\n".join([
        f"inline constexpr {kt} {guard}_BASE = {base};",
        f"inline constexpr {kt} {guard}_SIZE = {n};",
        "#if defined(__AVR__)",
        avr_body,
        "#else",
        non_avr_body,
        "#endif",
    ])


def emit_bsearch(varname, entries, guard, kt):
    keys = sorted(entries.keys())
    n = len(keys)
    idx_type = "uint8_t" if n <= 255 else ("uint16_t" if n <= 65535 else "uint32_t")
    # AVR: string pool + id/offset/len entries + manual bsearch.
    # The id field uses the same type as the key (kt) to avoid narrowing.
    if kt == "uint8_t":
        read_id = f"static_cast<{kt}>(pgm_read_byte(ep + offsetof({guard}_Entry, id)))"
    elif kt == "uint16_t":
        read_id = f"pgm_read_word(ep + offsetof({guard}_Entry, id))"
    elif kt == "uint64_t":
        read_id = (
            f"(static_cast<uint64_t>(pgm_read_dword(ep + offsetof({guard}_Entry, id) + 4)) << 32)"
            f" | pgm_read_dword(ep + offsetof({guard}_Entry, id))")
    else:
        read_id = f"pgm_read_dword(ep + offsetof({guard}_Entry, id))"
    decls, fetch = avr_label_storage(guard, kt, keys, entries, "ep", as_cstr=True)
    avr_body = "\n".join(decls + [
        f"[[nodiscard]] inline const char* {varname}_lookup({kt} id) noexcept {{",
        f"    {idx_type} lo = 0, hi = {n};",
        "    while (lo < hi) {",
        f"        {idx_type} mid = static_cast<{idx_type}>(lo + (hi - lo) / 2);",
        f"        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&{guard}_TABLE[mid]);",
        f"        {kt} eid = {read_id};",
        "        if (eid == id) {",
        *[f"            {line}" for line in fetch],
        "        }",
        f"        if (eid < id) lo = static_cast<{idx_type}>(mid + 1); else hi = mid;",
        "    }",
        "    return nullptr;",
        "}",
    ])
    # Non-AVR (unchanged constexpr)
    rows = "\n".join(f'    {{{k}u, {c_str_literal(entries[k])}}},' for k in keys)
    non_avr_body = "\n".join([
        f"struct {guard}_Entry {{ {kt} id; const char* label; }};",
        f"inline constexpr {guard}_Entry {guard}_TABLE[] = {{",
        rows + "};",
        f"[[nodiscard]] inline constexpr const char* {varname}_lookup({kt} id) noexcept {{",
        f"    {idx_type} lo = 0, hi = {n};",
        "    while (lo < hi) {",
        f"        {idx_type} mid = static_cast<{idx_type}>(lo + (hi - lo) / 2);",
        f"        if ({guard}_TABLE[mid].id == id) return {guard}_TABLE[mid].label;",
        f"        if ({guard}_TABLE[mid].id < id) lo = mid + 1;",
        "        else hi = mid;",
        "    }",
        "    return nullptr;", "}",
    ])
    return f"#if defined(__AVR__)\n{avr_body}\n#else\n{non_avr_body}\n#endif"


def emit_bsearch_optional(varname, entries, guard, kt):
    keys = sorted(entries.keys())
    n = len(keys)
    idx_type = "uint8_t" if n <= 255 else ("uint16_t" if n <= 65535 else "uint32_t")
    # AVR: string pool + id/offset/len entries + manual bsearch.
    # The id field uses the same type as the key (kt) to avoid narrowing.
    if kt == "uint8_t":
        read_id = f"static_cast<{kt}>(pgm_read_byte(ep + offsetof({guard}_Entry, id)))"
    elif kt == "uint16_t":
        read_id = f"pgm_read_word(ep + offsetof({guard}_Entry, id))"
    elif kt == "uint64_t":
        read_id = (
            f"(static_cast<uint64_t>(pgm_read_dword(ep + offsetof({guard}_Entry, id) + 4)) << 32)"
            f" | pgm_read_dword(ep + offsetof({guard}_Entry, id))")
    else:
        read_id = f"pgm_read_dword(ep + offsetof({guard}_Entry, id))"
    decls, fetch = avr_label_storage(guard, kt, keys, entries, "ep")
    avr_body = "\n".join(decls + [
        f"[[nodiscard]] inline std::optional<std::string_view> {varname}_lookup({kt} id) noexcept {{",
        f"    {idx_type} lo = 0, hi = {n};",
        "    while (lo < hi) {",
        f"        {idx_type} mid = static_cast<{idx_type}>(lo + (hi - lo) / 2);",
        f"        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&{guard}_TABLE[mid]);",
        f"        {kt} eid = {read_id};",
        "        if (eid == id) {",
        *[f"            {line}" for line in fetch],
        "        }",
        f"        if (eid < id) lo = static_cast<{idx_type}>(mid + 1); else hi = mid;",
        "    }",
        "    return std::nullopt;",
        "}",
    ])
    # Non-AVR: const char* payload, same width as emit_bsearch.  The lookup
    # still returns std::optional<std::string_view>; a missing key is the
    # absent signal for binary search, so no nullptr row is needed.
    rows = "\n".join(f'    {{{k}u, {c_str_literal(entries[k])}}},' for k in keys)
    non_avr_body = "\n".join([
        f"struct {guard}_Entry {{ {kt} id; const char* label; }};",
        f"inline constexpr {guard}_Entry {guard}_TABLE[] = {{",
        rows + "};",
        f"[[nodiscard]] inline constexpr std::optional<std::string_view> {varname}_lookup({kt} id) noexcept {{",
        f"    {idx_type} lo = 0, hi = {n};",
        "    while (lo < hi) {",
        f"        {idx_type} mid = static_cast<{idx_type}>(lo + (hi - lo) / 2);",
        f"        if ({guard}_TABLE[mid].id == id) {{",
        f"            const char* s = {guard}_TABLE[mid].label;",
        "            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;",
        "        }",
        f"        if ({guard}_TABLE[mid].id < id) lo = mid + 1;",
        "        else hi = mid;",
        "    }",
        "    return std::nullopt;", "}",
    ])
    return f"#if defined(__AVR__)\n{avr_body}\n#else\n{non_avr_body}\n#endif"

def build_header(modname, varname, entries, ver, all_varnames, obj=None, use_optional_override=None):
    keys = [k for k in entries if isinstance(k, int)]
    if not keys: return None
    # Filter entries to include string, int, and float values for lookup
    int_entries = {k: str(entries[k]) for k in keys if isinstance(entries[k], (str, int, float))}
    if not int_entries: return None
    guard = varname.upper()
    kt    = key_type(keys)
    strat = choose(keys)
    
    # Check if this is a QzssDcrDefinition with undefined attribute,
    # or override via use_optional_override (used by header transform scripts).
    use_optional = False
    if use_optional_override is not None:
        use_optional = use_optional_override
    elif obj is not None and hasattr(obj, 'undefined') and obj.undefined is not None:
        use_optional = True
    
    if use_optional:
        if   strat == "switch": body = emit_switch_optional(varname, int_entries, guard, kt)
        elif strat == "array":  body = emit_array_optional(varname, int_entries, guard, kt)
        else:                   body = emit_bsearch_optional(varname, int_entries, guard, kt)
    else:
        if   strat == "switch": body = emit_switch(varname, int_entries, guard, kt)
        elif strat == "array":  body = emit_array(varname, int_entries, guard, kt)
        else:                   body = emit_bsearch(varname, int_entries, guard, kt)

    category_guard = category_guard_for(varname)
    lang_guard = None
    if varname.endswith("_en"):
        # Only an _en table that has a JA counterpart is a language variant.
        # A lone _en table has no JA sibling, so it is the only source of that
        # data (the spec itself is English, as with the CAMF tables) and must
        # not be gated on AZARAC_LANG_EN: doing so compiles it to a nullopt
        # stub in the library default (AZARAC_LANG_JA=1 / AZARAC_LANG_EN=0)
        # and erases the label entirely.
        if varname[:-3] in all_varnames or f"{varname[:-3]}_ja" in all_varnames:
            lang_guard = "AZARAC_LANG_EN"
    elif varname.endswith("_ja") or f"{varname}_en" in all_varnames:
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
        if use_optional:
            # The AVR stdlib shim optional has a non-trivial destructor and is
            # not a literal type, so the stub cannot be constexpr on AVR.
            wrapped_body += "#if defined(__AVR__)\n"
            wrapped_body += (
                f"[[nodiscard]] inline std::optional<std::string_view> {varname}_lookup({kt} id)"
                f" noexcept {{\n")
            wrapped_body += "    (void)id;\n    return std::nullopt;\n}\n"
            wrapped_body += "#else\n"
            wrapped_body += (
                f"[[nodiscard]] inline constexpr std::optional<std::string_view> {varname}_lookup({kt} id)"
                f" noexcept {{\n")
            wrapped_body += "    (void)id;\n    return std::nullopt;\n}\n"
            wrapped_body += "#endif\n\n#endif\n"
        else:
            # const char* is a literal type even on AVR.
            wrapped_body += f"[[nodiscard]] inline constexpr const char* {varname}_lookup({kt} id) noexcept {{\n"
            wrapped_body += "    (void)id;\n    return nullptr;\n}\n\n#endif\n"
    else:
        wrapped_body = f"{body}\n"

    return (
        f"#pragma once\n"
        f"// AUTO-GENERATED from azarashi {ver} with CI-CD\n"
        f"// Source module : {modname}\n"
        f"// Variable      : {varname}\n"
        f"// Entries       : {len(keys)}\n"
        f"// Strategy      : {strat}\n\n"
        f"// NOTE: This function may return nullptr for unknown IDs.\n"
        f"// Callers MUST perform a null-check before using the result.\n\n"
        f"#if defined(__AVR__)\n"
        f"#include \"../internal/avr_std/cstdint\"\n"
        f"#include \"../internal/avr_std/optional\"\n"
        f"#include \"../internal/avr_std/string_view\"\n"
        f"#else\n"
        f"#include <cstdint>\n"
        f"#include <optional>\n"
        f"#include <string_view>\n"
        f"#endif\n"
        f'#include "../azaraC.h"\n'
        f'#include "../internal/FlashString.h"\n\n'
        f"namespace azaraC {{\nnamespace def {{\n\n"
        f"{wrapped_body}\n"
        f"}} // namespace def\n}} // namespace azaraC\n"
    )

def run(out_dir):
    os.makedirs(out_dir, exist_ok=True)
    base_path = find_def_path()
    ver = get_azarashi_version()

    # Pass 1 — every generated variable name, so that build_header can tell
    # whether a table has an _en sibling (which makes the JA table EN-aware).
    modules = list(iter_definition_modules(base_path))
    tables = []
    for modname in modules:
        try:
            tables.extend((modname, varname, obj) for varname, obj in tables_of(modname))
        # azarashi 側モジュールが import 時に投げる例外は種類を問わないため、
        # 1 モジュールの失敗で生成全体を止めずに警告で続行する。
        except Exception as e:  # noqa: BLE001
            print(f"[WARN] skip {modname}: {e}", file=sys.stderr)
    all_varnames = {varname for _, varname, _ in tables}

    generated = []
    for modname, varname, obj in tables:
        hdr = build_header(modname, varname, obj, ver, all_varnames, obj)
        if hdr is None:
            print(f"[SKIP] {varname}: no integer keys", file=sys.stderr)
            continue
        with open(os.path.join(out_dir, f"{varname}.h"), "w", encoding="utf-8", newline="\n") as f:
            f.write(hdr)
        generated.append(varname)

    # _index.h — the hand-written headers are included last, so that a reader
    # sees them together and the generated set stays in alphabetical order.
    extra_headers = [
        "ublox_qzss_svid_prn_map.h",
        "qzss_dcx_camf_a3_provider_identifier.h",
    ]
    extra_includes = ""
    for h in extra_headers:
        if os.path.exists(os.path.join(out_dir, h)):
            extra_includes += f'#include "{h}"\n'
        else:
            print(f"[WARN] Extra header not found: {h}", file=sys.stderr)
    # Headers for tables azaraC has no consumer for must not linger from an
    # earlier run: _index.h is regenerated in full, so a stale .h would still
    # compile but silently ship.
    keep = set(generated) | {h[:-2] for h in extra_headers}
    for name in os.listdir(out_dir):
        if name == "_index.h" or not name.endswith(".h"):
            continue
        if name[:-2] not in keep:
            os.remove(os.path.join(out_dir, name))
            print(f"[REMOVED] {name} (no longer generated)", file=sys.stderr)
    idx = (
        "#pragma once\n"
        f"// AUTO-GENERATED from azarashi {ver} — do not edit\n"
        f"// {len(generated)} generated + extra definition headers\n\n"
        + "\n".join(f'#include "{a}.h"' for a in sorted(generated))
        + "\n"
        + extra_includes
    )
    with open(os.path.join(out_dir, "_index.h"), "w", encoding="utf-8", newline="\n") as f:
        f.write(idx)
    # version marker (write to repo root, relative to script location)
    repo_root = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    with open(os.path.join(repo_root, ".azarashi-version"), "w", newline="\n") as f:
        f.write(ver + "\n")
    print(f"Generated {len(generated)} headers + _index.h  (azarashi {ver})")

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--out-dir", default="src/definition")
    args = parser.parse_args()
    run(args.out_dir)
