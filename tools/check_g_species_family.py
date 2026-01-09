#!/usr/bin/env python3
"""Simple static validator for src/data/pokemon/g_species_family.h

Checks performed:
- file contains include guard
- contains `const u16 gSpeciesFamily[NUM_SPECIES] =` and a braced initializer
- braces match and initializer ends with `};`
- each initializer line matches `[SPECIES_X] = SPECIES_Y,`
- no duplicate SPECIES_X entries
"""
import re
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
PATH = ROOT / 'src' / 'data' / 'pokemon' / 'g_species_family.h'

if not PATH.exists():
    print('Missing', PATH)
    sys.exit(2)

text = PATH.read_text(encoding='utf-8', errors='ignore')

ok = True
if 'GUARD_DATA_POKEMON_G_SPECIES_FAMILY_H' not in text:
    print('Missing include guard macro')
    ok = False

init_sig = 'const u16 gSpeciesFamily[NUM_SPECIES] ='
if init_sig not in text:
    print('Missing initializer signature')
    ok = False

# Find the initializer block
start = text.find(init_sig)
brace_pos = text.find('{', start)
if start == -1 or brace_pos == -1:
    print('Cannot find initializer brace')
    ok = False
else:
    depth = 0
    end_pos = -1
    for i, ch in enumerate(text[brace_pos:], start=brace_pos):
        if ch == '{':
            depth += 1
        elif ch == '}':
            depth -= 1
            if depth == 0:
                end_pos = i
                break
    if end_pos == -1:
        print('Unmatched braces in initializer')
        ok = False
    else:
        tail = text[end_pos+1:end_pos+4]
        if not text[end_pos+1:end_pos+4].strip().startswith(';') and '};' not in text[end_pos:end_pos+4]:
            # allow small whitespace between } and ;
            if not text[end_pos:end_pos+3].endswith('};'):
                print('Initializer does not end with ";"')
                ok = False

# Validate entries
entry_re = re.compile(r"\[SPECIES_([A-Z0-9_]+)\]\s*=\s*SPECIES_([A-Z0-9_]+)\s*,")
seen = {}
for m in entry_re.finditer(text):
    child, leader = m.group(1), m.group(2)
    if child in seen:
        print(f'Duplicate entry for SPECIES_{child} (previous leader SPECIES_{seen[child]})')
        ok = False
    seen[child] = leader

# Quick heuristic: ensure at least several hundred entries parsed
if len(seen) < 200:
    print('Parsed suspiciously few species entries:', len(seen))
    ok = False

if ok:
    print('Static check passed — parsed', len(seen), 'entries')
    sys.exit(0)
else:
    print('Static check failed')
    sys.exit(1)
