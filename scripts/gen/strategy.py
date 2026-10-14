# azaraC - scripts/strategy.py
# Lookup strategy selector (shared by gen_definitions.py).

def key_type(keys: list) -> str:
    mx = max(keys) if keys else 0
    if mx > 0xFFFFFFFF: return "uint64_t"
    if mx > 0xFFFF:     return "uint32_t"
    if mx > 0xFF:       return "uint16_t"
    return "uint8_t"

def choose(keys: list) -> str:
    """
    switch        : n <= 10
    array         : fill_ratio >= 0.6 AND keys are contiguous (no gaps) AND max key <= 0xFFFF
    binary_search : otherwise (sparse, large keys)
    """
    if not keys: return "switch"
    n  = len(keys)
    mn, mx = min(keys), max(keys)
    span = mx - mn + 1
    fill = n / span if span > 0 else 1.0
    if mx > 0xFFFF:   return "binary_search"
    if n <= 10:       return "switch"
    # array indexes by `id - BASE`; a gap in the key range would silently
    # shift every subsequent entry (wrong labels). Require contiguity.
    if fill >= 0.6 and span == n: return "array"
    return "binary_search"

def uint_type(limit: int) -> str:
    """Narrowest unsigned type that holds `limit`."""
    if limit <= 0xFF:   return "uint8_t"
    if limit <= 0xFFFF: return "uint16_t"
    return "uint32_t"

# Index of the "no parent" row: a table may use 0..254 as parent indices.
PARENT_NONE = 0xFF

def _split_offsets(text: bytes, min_len: int) -> list:
    """Split points that keep both halves valid UTF-8 (never inside a char)."""
    return [k for k in range(min_len, len(text)) if text[k] & 0xC0 != 0x80]

def factor_parents(labels: dict, min_len: int = 4,
                   min_uses = (4, 8, 16, 32, 64), max_parents: int = 0xFF):
    """Split labels into a child and a shared parent name (issue #35).

    Target-area and local-government labels repeat the region they belong to —
    "Sapporo City, Hokkaido Prefecture", "北海道札幌市" — so the table pays for
    "Hokkaido Prefecture" once per city. Storing each repeated part once and
    joining it at lookup time is what this returns.

    A parent is any prefix or suffix shared by at least `min_uses` labels of the
    table; each label takes the longest such part. `min_uses` is swept because
    the two costs pull in opposite directions: a long part is worth more per
    label but is shared by fewer of them, so the parent table's own bytes are
    amortised over less. The cheapest candidate wins.

    One direction is kept per table (majority wins): the join is then a
    compile-time constant, and the entry needs a parent index but no order bit.
    The labels of the losing direction stay uncompressed.

    Returns None when nothing beats the plain pool, else:
      children : {key: child string}      - the pool the entries point into
      parents  : [parent string, ...]     - emitted once each
      sel      : {key: parent index | None}
      order    : 'pre'  -> label == parent + child
                 'post' -> label == child + parent
    """
    keys = sorted(labels)
    texts = [labels[k].encode('utf-8') for k in keys]
    baseline = sum(len(t) + 1 for t in texts)
    best = None
    for uses_min in min_uses:
        head, tail = {}, {}
        for t in texts:
            for k in _split_offsets(t, min_len):
                head[t[:k]] = head.get(t[:k], 0) + 1
                tail[t[k:]] = tail.get(t[k:], 0) + 1
        cand_of = {}
        for i, t in enumerate(texts):
            best_i = None
            for k in _split_offsets(t, min_len):
                for kind, part, child in (('pre', t[:k], t[k:]), ('post', t[k:], t[:k])):
                    uses = (head if kind == 'pre' else tail).get(part, 0)
                    if uses < uses_min:
                        continue
                    score = (len(part), uses)
                    if best_i is None or score > best_i[0]:
                        best_i = (score, kind, part, child)
            if best_i:
                cand_of[i] = best_i[1:]
        if not cand_of:
            continue
        counts = {}
        for kind, _, _ in cand_of.values():
            counts[kind] = counts.get(kind, 0) + 1
        order = max(sorted(counts), key=lambda k: counts[k])
        plan = {i: v for i, v in cand_of.items() if v[0] == order}
        parents = sorted({v[1] for v in plan.values()})
        if len(parents) > max_parents:
            continue
        index = {p: i for i, p in enumerate(parents)}

        children = {k: (plan[i][2] if i in plan else texts[i]) for i, k in enumerate(keys)}
        children_bytes = sum(len(c) + 1 for c in children.values())
        parent_bytes = sum(len(p) + 1 for p in parents)
        # Adding the parent index grows every row by a byte unless the length
        # field can shrink to match (AVR row layout, see azaraC_config.h).
        rows_extra = 0 if max(len(c) for c in children.values()) <= 0xFF else len(keys)
        cost = children_bytes + parent_bytes + rows_extra
        if cost >= baseline:
            continue
        if best is None or cost < best[0]:
            best = (cost, order, [p.decode('utf-8') for p in parents],
                    {k: (index[plan[i][1]] if i in plan else None) for i, k in enumerate(keys)},
                    {k: v.decode('utf-8') for k, v in children.items()})
    if best is None:
        return None
    _, order, parents, sel, children = best
    return {'children': children, 'parents': parents, 'sel': sel, 'order': order}

