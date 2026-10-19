#!/usr/bin/env python3
"""AVR flash cost of the generated definition tables (autoresearch.sh stage 1).

Input: the translation unit emitted by `avr-gcc -E` for ATmega2560 with every
category and both languages enabled ("tables.i"). Because the *real* AVR
preprocessor selects the branch, the text holds exactly the tables an AVR build
compiles — no duplicate model of the AZARAC_ENABLE_* / AZARAC_LANG_* guards.

Counted here (all of it lands in Flash on AVR):

  AVR_STRING_BYTES   every `[] = "..."` initializer: the string pools proper
                     plus the per-case literals of `switch` strategy tables.
                     GCC places len+1 bytes for a literal of len bytes (implicit
                     terminating NUL).
  AVR_ENTRY_BYTES    every `..._TABLE[]` array, as rows x sizeof(the header's
                     own `..._Entry`), laid out with natural alignment the way
                     AVR-GCC lays it out.

  AVR_TABLE_BYTES    the sum — the primary metric.

Both terms are cross-checked against the sizes avr-gcc reports for the same
symbols (crosscheck_tables.py).

Every line of output is a `METRIC <name>=<value>` line.
"""

import re
import sys

# Preprocessed output splits declarations across `# 12 "file.h"` markers and hoists __attribute__((__progmem__)) onto its own line; only the declaration bodies matter, so that is stripped first.
# With more than 64 KiB of Flash AZARAC_PROGMEM expands to an inline `__attribute__((__section__(".text.azaraC.<n>")))` instead — same attribute, one more parenthesis level — so the pattern accepts both (the text is parsed, not compiled).
MARKER = re.compile(r'^# \d+ "[^"]*"(?: \d+)*$', re.M)
ATTR = re.compile(r'__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)')
LITERAL_START = re.compile(r'\[\]\s*=\s*"')
ENTRY_STRUCT = re.compile(r'struct\s+(\w+_Entry)\s*\{([^}]*)\}\s*;')
TABLE = re.compile(r'(\w+_TABLE)\[\]\s*=\s*\{(.*?)\n\s*\};', re.S)
ROW = re.compile(r'\{\s*[0-9][0-9a-fA-FxXuUlL]*(?:\s*,\s*[0-9][0-9a-fA-FxXuUlL]*)*\s*\}')
NAME = re.compile(r'(\w+)\s*$')

# AVR-GCC gives these fields byte alignment (measured on avr-gcc 7.3.0: a `{uint8_t id; uint16_t offset; uint16_t len;}` entry is 5 bytes, not the 6 a 2-byte alignment would give, and alignof(uint64_t) is 1), so an entry is the plain sum of its fields.
# An unknown field means the layout model must be revisited, not guessed; crosscheck_tables.py checks the result against avr-gcc either way.
SCALARS = {'uint8_t': 1, 'int8_t': 1, 'char': 1, 'bool': 1,
           'uint16_t': 2, 'int16_t': 2, 'uint32_t': 4, 'int32_t': 4,
           'uint64_t': 8, 'int64_t': 8,
           'const char*': 2, 'char*': 2}

# Pools the issue tracks individually (issue #35). Reported only.
TRACKED = (
    'QZSS_DCX_EX1_TARGET_AREA_CODE_EN_POOL',
    'QZSS_DCX_EX1_TARGET_AREA_CODE_JA_POOL',
    'QZSS_DCR_JMA_LOCAL_GOVERNMENT_EN_POOL',
    'QZSS_DCR_JMA_LOCAL_GOVERNMENT_POOL',
)


def literal_bytes(lit: str) -> int:
    """Bytes the compiler stores for a string literal body (escapes decoded)."""
    n = 0
    i = 0
    while i < len(lit):
        c = lit[i]
        if c != '\\':
            n += len(c.encode('utf-8', 'surrogateescape'))
            i += 1
            continue
        j = lit[i + 1]
        if j in '01234567':                      # \NNN
            k = i + 1
            while k < len(lit) and k < i + 4 and lit[k] in '01234567':
                k += 1
            n += 1
            i = k
        elif j == 'x':                           # \xNN
            k = i + 2
            while k < len(lit) and lit[k] in '0123456789abcdefABCDEF':
                k += 1
            n += 1
            i = k
        elif j in 'uU':                          # \uNNNN / \UNNNNNNNN
            width = 4 if j == 'u' else 8
            try:
                n += len(chr(int(lit[i + 2:i + 2 + width], 16)).encode('utf-8'))
                i += 2 + width
            except ValueError:
                n += 1
                i += 2
        else:                                    # \n \t \" \\ \'
            n += 1
            i += 2
    return n


def scan_literal(text: str, quote: int):
    """Bytes of the string literal starting at `text[quote] == '"'` (plus any
    adjacent literals the compiler would concatenate) and the index after it."""
    total = 0
    i = quote
    while True:
        j = i + 1
        while True:
            if text[j] == '\\':
                j += 2
                continue
            if text[j] == '"':
                break
            j += 1
        total += literal_bytes(text[i + 1:j])
        j += 1
        k = j
        while k < len(text) and text[k] in ' \t\n':
            k += 1
        if k < len(text) and text[k] == '"':
            i = k
            continue
        return total + 1, j          # +1: the implicit terminating NUL


def struct_size(body: str) -> int:
    """sizeof an `{ type field; ... }` entry struct as AVR-GCC lays it out."""
    size = 0
    for decl in body.split(';'):
        decl = decl.strip()
        if not decl:
            continue
        key = ' '.join(decl.split()[:-1]).replace(' *', '*')
        if key not in SCALARS:
            raise SystemExit(f'measure_tables: unsupported entry field {decl!r}')
        size += SCALARS[key]
    return size


def main(path: str, detail_path=None) -> int:
    with open(path, 'r', encoding='utf-8', errors='surrogateescape') as fh:
        text = ATTR.sub('', MARKER.sub('', fh.read()))

    sizes = {name: struct_size(body) for name, body in ENTRY_STRUCT.findall(text)}
    if not sizes:
        raise SystemExit('measure_tables: no entry structs found — wrong input?')

    entries = {}
    pools = {}
    count = 0
    largest = 0
    for m in LITERAL_START.finditer(text):
        head = NAME.search(text[max(0, m.start() - 200):m.start()])
        name = head.group(1) if head else '?'
        size, _ = scan_literal(text, m.end() - 1)
        pools[name] = pools.get(name, 0) + size
        count += 1
        largest = max(largest, size)

    rows = 0
    for m in TABLE.finditer(text):
        name = m.group(1)
        entry = name[:-len('_TABLE')] + '_Entry'
        if entry not in sizes:
            raise SystemExit(f'measure_tables: no struct for {name}')
        n = len(ROW.findall(m.group(2)))
        rows += n
        entries[name] = n * sizes[entry]

    strings = sum(pools.values())
    entry_bytes = sum(entries.values())
    row_bytes = entry_bytes // rows if rows else 0
    print(f'METRIC AVR_TABLE_BYTES={strings + entry_bytes}')
    print(f'METRIC AVR_STRING_BYTES={strings}')
    print(f'METRIC AVR_ENTRY_BYTES={entry_bytes}')
    print(f'METRIC AVR_ENTRY_ROWS={rows}')
    print(f'METRIC AVR_ENTRY_ROW_BYTES={row_bytes}')
    print(f'METRIC AVR_LARGEST_LITERAL={largest}')
    print(f'METRIC AVR_LITERALS={count}')
    print(f'METRIC AVR_TABLES={len(entries)}')
    for pool in TRACKED:
        if pool in pools:
            print(f'METRIC {pool}={pools[pool]}')
    if detail_path:
        # Every measured symbol, so the harness can compare these bytes with avr-gcc's.
        with open(detail_path, 'w', encoding='utf-8', newline='\n') as fh:
            for name in sorted(list(pools) + list(entries)):
                fh.write(f'{name} {pools.get(name, entries.get(name))}\n')
    return 0


if __name__ == '__main__':
    if len(sys.argv) not in (2, 3):
        print(__doc__, file=sys.stderr)
        raise SystemExit(2)
    raise SystemExit(main(*sys.argv[1:]))
