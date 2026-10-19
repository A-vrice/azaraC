#!/usr/bin/env python3
"""Generate the exhaustive definition-label dump (autoresearch.sh stage 2).

Writes a C++ program that calls *every* `*_lookup()` in the included definition
headers over its whole id domain and hashes the `(lookup, id, label)` stream.
autoresearch.sh builds it twice — AVR branch (`-D__AVR__` + the PROGMEM stub of
test/stub) and host branch — and compares both hashes against
test/bench/avr/labels.golden.

Why the whole domain and not the table rows: the AVR pools are about to be
re-encoded (issue #35), so the tables must be free to change shape. Probing
`lookup(id)` for every id in the domain pins the *contract* (what a caller
gets) instead of the storage, and catches a label lost to a bad offset/length
just as well as one lost to a bad join.

Usage: gen_label_dump.py <output.cpp>
"""

import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
DEF_DIR = os.path.normpath(os.path.join(HERE, '..', '..', '..', 'src', 'definition'))

LOOKUP = re.compile(r'(\w+_lookup)\s*\(([^)]*)\)')
TABLE = re.compile(r'(\w+_TABLE)\[\]\s*(?:AZARAC_PROGMEM\s*)?=\s*\{(.*?)\n\s*\};', re.S)
TABLE_FIRST_FIELD = re.compile(r'\{\s*(\d+)[uUlL]*\s*[,}]')

# *_PARENT_TABLE / *_GRAND_TABLE hold pool offsets, so their first field is a byte offset, not a key.
NOT_ID_TABLES = re.compile(r'_(PARENT|GRAND)_TABLE$')

# id domains probed per signature.
# `uint32_t`/`uint64_t` keys are not enumerable, so those probe the ids the header declares (plus 0..max when that range is small enough).
U8_IDS = 256
U16_IDS = 1 << 16
DENSE_LIMIT = 1 << 18
PROVIDER_FACTOR = 1 << 4          # key = (country << 4) | (provider & 0xF)


def params_of(raw: str):
    out = []
    for part in raw.split(','):
        part = part.strip()
        if not part:
            continue
        fields = part.split()
        if len(fields) != 2:
            raise SystemExit(f'gen_label_dump: cannot parse parameter {part!r}')
        out.append((fields[0], fields[1]))
    return out


def table_ids(text: str):
    ids = set()
    for m in TABLE.finditer(text):
        if NOT_ID_TABLES.search(m.group(1)):
            continue
        ids.update(int(v) for v in TABLE_FIRST_FIELD.findall(m.group(2)))
    return sorted(ids)


def main(out_path: str) -> int:
    with open(os.path.join(DEF_DIR, '_index.h'), encoding='utf-8') as fh:
        index = fh.read()
    headers = [h for h in re.findall(r'#include "([^"]+)"', index)]
    if not headers:
        raise SystemExit('gen_label_dump: no definition headers in _index.h')

    lookups = {}          # name -> (params, ids)
    for header in headers:
        path = os.path.join(DEF_DIR, header)
        with open(path, encoding='utf-8') as fh:
            text = fh.read()
        ids = None
        for m in LOOKUP.finditer(text):
            name, raw = m.group(1), m.group(2)
            params = params_of(raw)
            if ids is None and any(t in ('uint32_t', 'uint64_t') for t, _ in params):
                ids = table_ids(text)
            if name in lookups and lookups[name][0] != params:
                raise SystemExit(f'gen_label_dump: {name} declared twice with different parameters')
            lookups[name] = (params, ids)

    calls = []
    for name in sorted(lookups):
        params, ids = lookups[name]
        types = [t for t, _ in params]
        calls.append(f'    START_LOOKUP("{name}");')
        if len(params) == 1 and types[0] == 'uint8_t':
            calls.append(f'    for (unsigned i = 0; i < {U8_IDS}; ++i) '
                         f'probe("{name}", i, {name}(static_cast<uint8_t>(i)));')
        elif len(params) == 1 and types[0] == 'uint16_t':
            calls.append(f'    for (unsigned i = 0; i < {U16_IDS}; ++i) '
                         f'probe("{name}", i, {name}(static_cast<uint16_t>(i)));')
        elif len(params) == 1 and types[0] in ('uint32_t', 'uint64_t'):
            if not ids:
                raise SystemExit(f'gen_label_dump: {name} has a {types[0]} key but no table to take ids from')
            if ids[-1] <= DENSE_LIMIT:
                calls.append(f'    for (unsigned long long i = 0; i <= {ids[-1]}ull; ++i) '
                             f'probe("{name}", i, {name}(static_cast<{types[0]}>(i)));')
            else:
                joined = ', '.join(f'{v}ull' for v in ids)
                calls.append(f'    {{ static const unsigned long long ids[] = {{{joined}}};')
                calls.append(f'      for (unsigned long long i : ids) '
                             f'probe("{name}", i, {name}(static_cast<{types[0]}>(i))); }}')
        elif types == ['uint16_t', 'uint8_t']:
            # Hand-written a3 provider table: key = (country << 4) | (provider & 0xF).
            calls.append(f'    for (unsigned c = 0; c < {U16_IDS // PROVIDER_FACTOR}; ++c)')
            calls.append(f'        for (unsigned p = 0; p < {PROVIDER_FACTOR}; ++p)')
            calls.append(f'            probe("{name}", (c << 4) | p, '
                         f'{name}(static_cast<uint16_t>(c), static_cast<uint8_t>(p)));')
        else:
            raise SystemExit(f'gen_label_dump: unsupported signature {name}({", ".join(types)})')

    with open(out_path, 'w', encoding='utf-8', newline='\n') as fh:
        fh.write(PROLOGUE)
        fh.write('\n'.join(calls))
        fh.write('\n')
        fh.write(EPILOGUE)
    print(f'gen_label_dump: {len(lookups)} lookups -> {out_path}')
    return 0


PROLOGUE = '''// GENERATED by test/bench/avr/gen_label_dump.py — do not edit.
//
// Calls every definition lookup over its whole id domain and hashes the
// (lookup, id, label) stream. Built twice by autoresearch.sh — AVR branch
// (-D__AVR__ -DAZARAC_AVR_STUB, PROGMEM string views) and host branch — and
// compared against test/bench/avr/labels.golden. `dump` as argv[1] prints every
// non-null label so a hash mismatch can be diffed by hand.
#include "definition/_index.h"

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <optional>
#include <string_view>

using namespace azaraC::def;

static uint64_t g_hash = 1469598103934665603ULL;  // FNV-1a, 64 bit
static uint64_t g_calls = 0;
static uint64_t g_labels = 0;
static bool g_dump = false;

// Progress marker: only visible in `dump` mode, where it says which lookup was
// being walked when a gate failure has to be debugged.
#define START_LOOKUP(n) do { if (g_dump) std::fprintf(stderr, "== %s\\n", n); } while (0)

static void mix(const void* p, size_t n) {
    const unsigned char* b = static_cast<const unsigned char*>(p);
    for (size_t i = 0; i < n; ++i) g_hash = (g_hash ^ b[i]) * 1099511628211ULL;
}

template <size_t N>
static void probe(const char (&name)[N], unsigned long long id,
                  const std::optional<std::string_view>& r) {
    ++g_calls;
    mix(name, N - 1);
    mix(&id, sizeof id);
    if (r) {
        ++g_labels;
        const size_t n = r->size();
        mix(&n, sizeof n);
        mix(r->data(), n);
        if (g_dump) std::printf("%s %llu %zu %.*s\\n", name, id, n, static_cast<int>(n), r->data());
    } else {
        mix("~", 1);
    }
}

// Some tables (the category lists) historically return a C string, not a
// string_view. Keeping the two overloads hashing the same stream is what makes
// the AVR and host dumps comparable across both shapes.
template <size_t N>
static void probe(const char (&name)[N], unsigned long long id, const char* s) {
    ++g_calls;
    mix(name, N - 1);
    mix(&id, sizeof id);
    if (s) {
        ++g_labels;
        const size_t n = std::strlen(s);
        mix(&n, sizeof n);
        mix(s, n);
        if (g_dump) std::printf("%s %llu %zu %s\\n", name, id, n, s);
    } else {
        mix("~", 1);
    }
}

int main(int argc, char** argv) {
    g_dump = argc > 1 && std::strcmp(argv[1], "dump") == 0;
'''

EPILOGUE = '''    std::printf("LABELHASH %016llx calls=%llu labels=%llu\\n",
                static_cast<unsigned long long>(g_hash),
                static_cast<unsigned long long>(g_calls),
                static_cast<unsigned long long>(g_labels));
    return 0;
}
'''

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print(__doc__, file=sys.stderr)
        raise SystemExit(2)
    raise SystemExit(main(sys.argv[1]))
