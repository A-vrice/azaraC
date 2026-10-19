#!/usr/bin/env python3
"""Cross-check the primary metric against avr-gcc itself (autoresearch.sh stage 3).

stdin: `avr-nm --print-size --radix=d -C` output for the objects stage 3 built.
argv[1]: the `NAME BYTES` detail file written by measure_tables.py.

Every `*_POOL` / `*_TABLE` symbol avr-gcc actually placed must measure exactly
what measure_tables.py parsed from the preprocessed source; otherwise the metric
is measuring something other than what the compiler stores. This is what keeps
the entry-struct layout model honest: if a compressed encoding changes the
struct, the model and avr-gcc disagree and the run fails instead of quietly
reporting a wrong number.

Coverage is partial by construction: a table lives in the translation units that
reference it, and one too large to compile is in no object at all — so the count
is reported (the harness gates only on the ones that were checked).
azaraC's own hand-written tables (HAND_WRITTEN_TABLES) share the `_TABLE` suffix so
that the RAM gate in autoresearch.sh sees them; they are not parsed here and are
excluded from the count.
"""

import sys

SUFFIXES = ('_POOL', '_TABLE')

# azaraC's own small Flash tables (internal/DcxHelper.cpp) follow the same name
# convention as the generated definition tables so that the "not in RAM" gate picks
# them up, but measure_tables.py does not parse them: they are hand-written, not
# generated. Their placement is gated by MEGA_NEAR_SYM_ADDR instead.
HAND_WRITTEN_TABLES = {'RADIUS_TABLE', 'B4_LAYOUT_TABLE'}


def main(pools_path: str) -> int:
    declared = {}
    with open(pools_path, encoding='utf-8') as fh:
        for line in fh:
            parts = line.split()
            if len(parts) == 2:
                declared[parts[0]] = int(parts[1])

    placed = {}
    for line in sys.stdin:
        parts = line.split()
        if len(parts) < 4 or len(parts[2]) != 1 or not parts[2].isalpha():
            continue
        # A demangled name in an anonymous namespace contains spaces, so the name is
        # everything after the type field, not just parts[3].
        name = ' '.join(parts[3:]).rsplit('::', 1)[-1]
        if name in HAND_WRITTEN_TABLES:
            continue
        if name.endswith(SUFFIXES):
            placed[name] = max(placed.get(name, 0), int(parts[1]))

    matched = 0
    for name, size in sorted(placed.items()):
        want = declared.get(name)
        if want is None:
            print(f'autoresearch: {name} placed but not parsed', file=sys.stderr)
            continue
        if want == size:
            matched += 1
        else:
            print(f'autoresearch: {name}: avr-gcc placed {size} B, parsed {want} B', file=sys.stderr)
    pools = sum(s for n, s in placed.items() if n.endswith('_POOL'))
    tables = sum(s for n, s in placed.items() if n.endswith('_TABLE'))
    print(f'METRIC AVR_TABLE_CROSSCHECK={matched}/{len(placed)}')
    print(f'METRIC AVR_POOL_BYTES_NM={pools}')
    print(f'METRIC AVR_ENTRY_BYTES_NM={tables}')
    return 0


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print(__doc__, file=sys.stderr)
        raise SystemExit(2)
    raise SystemExit(main(sys.argv[1]))
