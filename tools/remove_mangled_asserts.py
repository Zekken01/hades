#!/usr/bin/env python3
"""Strip `mangled_x86(...)` / `mangled_prefix_assert(...)` asserts from the sources.

Removes:
  * standalone assert lines            `    mangled_x86(MANGLED_DEFAULT, "?Foo@@YAXXZ");`
  * commented-out assert lines         `// mangled_x86(...); no body to assert in`
    (keep these with --keep-commented)
  * asserts sharing a line with code   `{ mangled_x86(...);`  ->  `{`

Blank lines the removal would leave dangling are dropped too: a blank line right
after the opening `{` of a body, a doubled blank line, or a blank line right
before a closing `}`.

Files come from `git grep` (tracked files only; `libs/` and the macro header are
skipped) unless paths are passed explicitly. Line endings and bytes outside the
removed text are preserved.

    python tools/remove_mangled_asserts.py --dry-run     # report, write nothing
    python tools/remove_mangled_asserts.py               # rewrite files in place
    python tools/remove_mangled_asserts.py path/a.cpp    # only these files
"""

import argparse
import difflib
import re
import subprocess
import sys
from pathlib import Path

MACROS = r"mangled_(?:x86|prefix_assert)"
# One macro call: name, balanced-enough argument list (string literals may hold
# anything), then the terminating semicolon.
CALL = rf"\b{MACROS}\s*\((?:[^()\"]|\"(?:[^\"\\]|\\.)*\")*\)\s*;"

LIVE_LINE = re.compile(rf"^[ \t]*{CALL}[ \t]*$")
COMMENTED_LINE = re.compile(rf"^[ \t]*//[ \t]*{MACROS}\s*\(")
INLINE_CALL = re.compile(rf"[ \t]*{CALL}")
ANY_USE = re.compile(rf"\b{MACROS}\s*\(")

EXCLUDE = ("libs/", "hades/mangled_assert.h")


def split_eol(line):
    """Return (text, eol) for a line that may end in \\r\\n, \\n, or nothing."""
    for eol in ("\r\n", "\n"):
        if line.endswith(eol):
            return line[: -len(eol)], eol
    return line, ""


def is_blank(line):
    return split_eol(line)[0].strip(" \t") == ""


def strip_line(body, keep_commented):
    """Return (new_body or None to drop the line, asserts removed)."""
    if body.lstrip().startswith("#"):
        return body, 0  # never touch preprocessor lines
    if LIVE_LINE.match(body):
        return None, 1
    if COMMENTED_LINE.match(body):
        return (body, 0) if keep_commented else (None, 1)
    if body.lstrip().startswith("//"):
        return body, 0
    stripped, n = INLINE_CALL.subn("", body)
    if not n:
        return body, 0
    stripped = stripped.rstrip(" \t")
    return (stripped if stripped.strip(" \t") else None), n


def rewrite(text, keep_commented):
    """Return (new_text, removed_count, leftover_lines)."""
    lines = re.split(r"(?<=\n)", text)
    if lines and lines[-1] == "":
        lines.pop()

    out = []
    removed = 0
    i = 0
    while i < len(lines):
        body, eol = split_eol(lines[i])
        new_body, n = strip_line(body, keep_commented)
        removed += n
        i += 1
        if new_body is not None:
            out.append(lines[i - 1] if new_body == body else new_body + eol)
            continue

        # Line dropped; swallow the rest of a run of assert lines.
        while i < len(lines):
            new_body, n = strip_line(split_eol(lines[i])[0], keep_commented)
            if new_body is not None:
                break
            removed += n
            i += 1

        prev = split_eol(out[-1])[0].rstrip(" \t") if out else None
        # `{` / start-of-file / blank before, blank after: the blank is now dangling.
        if prev is None or prev == "" or prev.endswith("{"):
            while i < len(lines) and is_blank(lines[i]):
                i += 1
        # Blank before, `}` / end-of-file after: drop the trailing blank instead.
        if i >= len(lines) or split_eol(lines[i])[0].lstrip().startswith("}"):
            while out and is_blank(out[-1]) and len(out) > 1:
                out.pop()

    new_text = "".join(out)
    leftovers = [
        (n, l) for n, l in enumerate(new_text.split("\n"), 1)
        if ANY_USE.search(l) and not (keep_commented and COMMENTED_LINE.match(l))
    ]
    return new_text, removed, leftovers


def tracked_files(root):
    res = subprocess.run(
        ["git", "grep", "-lE", r"\bmangled_(x86|prefix_assert)\s*\("],
        cwd=root, capture_output=True, text=True,
    )
    if res.returncode not in (0, 1):
        sys.exit(res.stderr.strip() or "git grep failed")
    return [
        root / p for p in res.stdout.splitlines()
        if not any(p.startswith(x) for x in EXCLUDE)
    ]


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("paths", nargs="*", type=Path, help="files to process (default: git grep)")
    ap.add_argument("--dry-run", action="store_true", help="report changes without writing")
    ap.add_argument("--diff", action="store_true", help="print a unified diff of every change")
    ap.add_argument("--keep-commented", action="store_true", help="leave `// mangled_x86(...)` lines alone")
    args = ap.parse_args()

    root = Path(__file__).resolve().parent.parent
    files = args.paths or tracked_files(root)

    total = changed = 0
    leftover_report = []
    for path in files:
        # latin-1 round-trips every byte, so encodings and BOMs survive untouched.
        text = path.read_bytes().decode("latin-1")
        new_text, removed, leftovers = rewrite(text, args.keep_commented)
        rel = path.resolve().relative_to(root) if path.resolve().is_relative_to(root) else path
        leftover_report += [f"{rel}:{n}: {l.strip()}" for n, l in leftovers]
        if new_text == text:
            continue
        changed += 1
        total += removed
        if args.diff:
            sys.stdout.writelines(difflib.unified_diff(
                text.splitlines(True), new_text.splitlines(True),
                f"a/{rel}".replace("\\", "/"), f"b/{rel}".replace("\\", "/"),
            ))
        if not args.dry_run:
            path.write_bytes(new_text.encode("latin-1"))

    verb = "would remove" if args.dry_run else "removed"
    print(f"{verb} {total} asserts in {changed} files", file=sys.stderr)
    if leftover_report:
        print(f"{len(leftover_report)} uses left for manual review:", file=sys.stderr)
        for l in leftover_report:
            print("  " + l, file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
