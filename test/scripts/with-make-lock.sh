#!/usr/bin/env bash
# Serialize make runs that share test/*.o (invoked by test/Makefile's lockwrap target).
# Keep this file ASCII-only: native Windows make -> MSYS sh breaks on UTF-8/multiline recipes.
set -u

script_dir="$(cd "$(dirname "$0")" && pwd)"
cd "$script_dir/.." || exit 1

lock_dir=".make-lock"
make_cmd="${AZARAC_MAKE:-make}"

# Allow an explicit bypass (the Makefile also uses AZARAC_LOCK_HELD, but this path makes
# direct script invocation predictable).
if [[ "${AZARAC_LOCK_HELD:-}" == "1" ]]; then
    exec "$make_cmd" "$@"
fi

if ! mkdir "$lock_dir" 2>/dev/null; then
    printf '%s\n' \
        "test/Makefile: $lock_dir exists - another make is running, or a stale lock remains." \
        "  Wait for the other build, or remove it with: rm -rf test/$lock_dir" >&2
    exit 2
fi

cleanup() { rm -rf "$lock_dir"; }
trap cleanup EXIT
trap 'exit 129' HUP
trap 'exit 130' INT
trap 'exit 143' TERM

"$make_cmd" AZARAC_LOCK_HELD=1 "$@"
