#!/usr/bin/env python3
"""
Script to apply changes from PokemonFossilizedHoennDex.csv to gen_X family files,
update movesets, and rewrite the Hoenn dex order in src/pokemon.c.

Behavior:
- Read CSV (case-insensitive headers). The Pokémon name header can be "pokemon", "species" or "name".
- For each row, locate the species in any gen_*_families.h file by matching "[SPECIES_<NAME>]" (case-insensitive name match but exact spelling required).
- If ability columns are present (ability1, ability2, hidden_ability, etc.), replace the `.abilities = { ... },` line. Empty values become `ABILITY_NONE`.
- If stat columns are present (hp, atk, def, spatk, spdef, speed), overwrite a `.baseStats = { ... },` block.
- If type columns are present (type1, type2), update the types.
- Process move columns (all columns after "Attack Changes"):
  * Lines starting with a number (e.g., "50: Move Name") are level-up moves
  * Lines starting with "Evo:" are evolution moves
  * Lines starting with "Learnable:" are teachable/TM moves
  * Lines starting with "Egg:" are egg moves
  * Lines with "OLD_MOVE -> NEW_MOVE" are move swaps (replace in all learnsets)
- Build a Hoenn order list from the CSV rows (in CSV order) for species that were found, and replace the sHoennToNationalOrder array in `src/pokemon.c`.
- Print species that were not found and continue.

Ignored CSV fields: "aquire method", "fossil" (these are skipped).

Usage: run from repo root. Defaults to the attached CSV and repository paths.
"""

import argparse
import csv
import os
import re
import sys
from collections import OrderedDict
from pathlib import Path


def normalize_name(name: str) -> str:
    # Keep spelling exact but uppercase for macro usage.
    return name.strip()


def macro_name_for_species(name: str) -> str:
    # Convert to upper and replace spaces/hyphens with underscores
    s = name.upper()
    s = re.sub(r"[^A-Z0-9_]+", "_", s)
    s = re.sub(r"__+", "_", s)
    return s


def ability_macro(name: str) -> str:
    if not name or name.strip() == "":
        return "ABILITY_NONE"
    s = name.strip().upper()
    s = re.sub(r"[^A-Z0-9_]+", "_", s)
    return "ABILITY_" + s


def load_abilities_set(path: str):
    if not os.path.isfile(path):
        return set()
    txt = load_file(path)
    # find tokens like ABILITY_WHATEVER
    names = set(re.findall(r"\b(ABILITY_[A-Z0-9_]+)\b", txt))
    return names


def load_moves_set(path: str):
    """Load all MOVE_* macros from include/constants/moves.h"""
    if not os.path.isfile(path):
        return set()
    txt = load_file(path)
    # find tokens like MOVE_WHATEVER
    names = set(re.findall(r"\b(MOVE_[A-Z0-9_]+)\b", txt))
    return names


def type_macro(name: str) -> str:
    if not name or name.strip() == "":
        return "TYPE_NONE"
    s = name.strip().upper()
    s = re.sub(r"[^A-Z0-9_]+", "_", s)
    return "TYPE_" + s


def move_macro(name: str) -> str:
    """Convert a move name to a MOVE_* macro."""
    if not name or name.strip() == "":
        return None
    s = name.strip().upper()
    s = re.sub(r"[^A-Z0-9_]+", "_", s)
    s = re.sub(r"__+", "_", s)
    return "MOVE_" + s


def replace_types_in_block(block: str, type_macros: list) -> str:
    # type_macros should be [type1, type2]
    t1 = type_macros[0] if len(type_macros) > 0 else 'TYPE_NONE'
    t2 = type_macros[1] if len(type_macros) > 1 else 'TYPE_NONE'
    # Prefer single-argument MON_TYPES(TYPE_X) when the second type is empty/TYPE_NONE
    if t1 == 'TYPE_NONE' and t2 != 'TYPE_NONE':
        new_types = f".types = MON_TYPES({t2}),"
    elif t2 == 'TYPE_NONE' or not t2:
        new_types = f".types = MON_TYPES({t1}),"
    else:
        new_types = f".types = MON_TYPES({t1}, {t2}),"

    # Replace existing MON_TYPES(...) usage
    if re.search(r"\.types\s*=\s*MON_TYPES\(", block):
        block = re.sub(r"\.types\s*=\s*MON_TYPES\([^)]*\),", new_types, block)
    elif re.search(r"\.types\s*=\s*\{", block):
        block = re.sub(r"\.types\s*=\s*\{[^}]*\},", new_types, block)
    else:
        # Try individual .type1/.type2 fields
        replaced = False
        if re.search(r"\.type1\s*=\s*TYPE_", block) or re.search(r"\.type2\s*=\s*TYPE_", block):
            block = re.sub(r"\.type1\s*=\s*TYPE_[A-Z0-9_]+\s*,", f".type1 = {t1},", block)
            block = re.sub(r"\.type2\s*=\s*TYPE_[A-Z0-9_]+\s*,", f".type2 = {t2},", block)
            replaced = True

        if not replaced:
            parts = block.split('\n', 1)
            if len(parts) == 2:
                block = parts[0] + '\n    ' + new_types + '\n' + parts[1]
            else:
                block = block + '\n    ' + new_types + '\n'

    return block


def find_family_files(species_dir):
    files = []
    for fname in os.listdir(species_dir):
        if fname.endswith("_families.h") and fname.startswith("gen_"):
            files.append(os.path.join(species_dir, fname))
    return files


def find_learnset_files(learnset_dir):
    """Find all gen_*.h files in the level_up_learnsets directory."""
    files = []
    if os.path.isdir(learnset_dir):
        for fname in os.listdir(learnset_dir):
            if fname.endswith(".h") and fname.startswith("gen_"):
                files.append(os.path.join(learnset_dir, fname))
    return files


def load_file(path):
    with open(path, "r", encoding="utf-8") as f:
        return f.read()


def write_file(path, data):
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        f.write(data)


def find_species_block(content: str, species_macro: str):
    # Find the [SPECIES_NAME] = ... { ... }, block. Return (start_idx, end_idx, block_text) or (None, None, None)
    pat = re.compile(r"\[\s*SPECIES_%s\s*\]\s*=\s*\{" % re.escape(species_macro), re.IGNORECASE)
    m = pat.search(content)
    if not m:
        return None, None, None
    start = m.start()
    # Find opening brace position
    brace_pos = content.find('{', m.end() - 1)
    if brace_pos == -1:
        return None, None, None
    i = brace_pos
    depth = 0
    end = None
    while i < len(content):
        if content[i] == '{':
            depth += 1
        elif content[i] == '}':
            depth -= 1
            if depth == 0:
                # include trailing comma if present
                j = i + 1
                while j < len(content) and content[j].isspace():
                    j += 1
                if j < len(content) and content[j] == ',':
                    end = j + 1
                else:
                    end = i + 1
                break
        i += 1
    if end is None:
        return None, None, None
    return start, end, content[start:end]


def replace_abilities_in_block(block: str, ability_macros: list) -> str:
    new_abilities = ".abilities = { %s }," % ", ".join(ability_macros)
    # Try to replace an existing .abilities = { ... }, line
    if re.search(r"\.abilities\s*=\s*\{", block):
        block = re.sub(r"\.abilities\s*=\s*\{[^}]*\},", new_abilities, block)
    else:
        # Insert abilities near top of block (after first newline)
        parts = block.split('\n', 1)
        if len(parts) == 2:
            block = parts[0] + '\n    ' + new_abilities + '\n' + parts[1]
        else:
            block = block + '\n    ' + new_abilities + '\n'
    return block


def replace_base_stats_in_block(block: str, stats: dict) -> str:
    # Replace individual fields like .baseHP, .baseAttack, .baseDefense, .baseSpAttack, .baseSpDefense, .baseSpeed
    if not stats:
        return block
    fields = {
        'hp': ('.baseHP', stats.get('hp')),
        'atk': ('.baseAttack', stats.get('atk')),
        'def': ('.baseDefense', stats.get('def')),
        'spatk': ('.baseSpAttack', stats.get('spatk')),
        'spdef': ('.baseSpDefense', stats.get('spdef')),
        'speed': ('.baseSpeed', stats.get('speed')),
    }
    new_block = block
    for key, (field_name, val) in fields.items():
        if val is None:
            continue
        # try to replace existing line
        pat = re.compile(r"(\.%s\s*=\s*)\d+\s*," % re.escape(field_name[1:]))
        if pat.search(new_block):
            new_block = pat.sub(lambda m, v=val: m.group(1) + str(v) + ',', new_block)
        else:
            # insert near top of block after first line
            parts = new_block.split('\n', 1)
            line = f"    {field_name} = {val},"
            if len(parts) == 2:
                new_block = parts[0] + '\n' + line + '\n' + parts[1]
            else:
                new_block = new_block + '\n' + line + '\n'
    return new_block


def update_levelup_moves(learnset_content: str, species_macro: str, move_changes: dict) -> str:
    """
    Update level-up moves in learnset content.
    move_changes: dict with level (int) -> MOVE_* macro (str)
    Returns modified content or original if species not found.
    """
    # Find the learnset array: static const struct LevelUpMove s<Species>LevelUpLearnset[]
    species_camel = re.sub(r'_(.)', lambda m: m.group(1).upper(), species_macro.lower())
    species_camel = species_camel[0].upper() + species_camel[1:]  # Capitalize first letter
    
    pat = re.compile(r"static const struct LevelUpMove\s+s%sLevelUpLearnset\s*\[\s*\]\s*=\s*\{" % re.escape(species_camel), re.IGNORECASE)
    m = pat.search(learnset_content)
    if not m:
        return learnset_content
    
    start = m.start()
    # Find the matching closing brace
    brace_pos = learnset_content.find('{', m.end() - 1)
    i = brace_pos
    depth = 0
    end = None
    while i < len(learnset_content):
        if learnset_content[i] == '{':
            depth += 1
        elif learnset_content[i] == '}':
            depth -= 1
            if depth == 0:
                j = i + 1
                while j < len(learnset_content) and learnset_content[j].isspace():
                    j += 1
                if j < len(learnset_content) and learnset_content[j] == ';':
                    end = j + 1
                else:
                    end = i + 1
                break
        i += 1
    
    if end is None:
        return learnset_content
    
    old_block = learnset_content[start:end]
    
    # Parse existing moves
    existing_moves = {}  # level -> MOVE_*
    for match in re.finditer(r"LEVEL_UP_MOVE\s*\(\s*(\d+)\s*,\s*(MOVE_[A-Z0-9_]+)\s*\)", old_block):
        level = int(match.group(1))
        move = match.group(2)
        existing_moves[level] = move
    
    # Update with new moves
    for level, move in move_changes.items():
        existing_moves[level] = move
    
    # Build new block
    new_lines = []
    for level in sorted(existing_moves.keys()):
        new_lines.append(f"    LEVEL_UP_MOVE({level:2d}, {existing_moves[level]}),")
    new_lines.append("    LEVEL_UP_END")
    new_lines.append("};")
    
    new_block = old_block.split('{')[0] + "{\n" + "\n".join(new_lines) + "\n"
    
    return learnset_content[:start] + new_block + learnset_content[end:]


def find_and_update_egg_moves(egg_moves_content: str, species_macro: str, new_egg_moves: list) -> str:
    """
    Add new egg moves to the egg moves learnset.
    new_egg_moves: list of MOVE_* macros
    Returns modified content.
    """
    # Find the array: static const u16 s<Species>EggMoveLearnset[]
    species_camel = re.sub(r'_(.)', lambda m: m.group(1).upper(), species_macro.lower())
    species_camel = species_camel[0].upper() + species_camel[1:]


def add_evo_moves(learnset_content: str, species_macro: str, evo_moves: list) -> str:
    """
    Add evolution moves to learnset. Evolution moves are added as LEVEL_UP_MOVE(0, ...)
    since level 0 typically represents moves learned upon evolution.
    evo_moves: list of MOVE_* macros
    Returns modified content or original if species not found.
    """
    # Find the learnset array: static const struct LevelUpMove s<Species>LevelUpLearnset[]
    species_camel = re.sub(r'_(.)', lambda m: m.group(1).upper(), species_macro.lower())
    species_camel = species_camel[0].upper() + species_camel[1:]
    
    pat = re.compile(r"static const struct LevelUpMove\s+s%sLevelUpLearnset\s*\[\s*\]\s*=\s*\{" % re.escape(species_camel), re.IGNORECASE)
    m = pat.search(learnset_content)
    if not m:
        return learnset_content
    
    start = m.start()
    # Find the matching closing brace
    brace_pos = learnset_content.find('{', m.end() - 1)
    i = brace_pos
    depth = 0
    end = None
    while i < len(learnset_content):
        if learnset_content[i] == '{':
            depth += 1
        elif learnset_content[i] == '}':
            depth -= 1
            if depth == 0:
                j = i + 1
                while j < len(learnset_content) and learnset_content[j].isspace():
                    j += 1
                if j < len(learnset_content) and learnset_content[j] == ';':
                    end = j + 1
                else:
                    end = i + 1
                break
        i += 1
    
    if end is None:
        return learnset_content
    
    old_block = learnset_content[start:end]
    
    # Check if evo moves already exist
    existing_evo_moves = set()
    for match in re.finditer(r"LEVEL_UP_MOVE\s*\(\s*0\s*,\s*(MOVE_[A-Z0-9_]+)\s*\)", old_block):
        existing_evo_moves.add(match.group(1))
    
    # Add new evo moves that don't already exist
    new_evo_moves_to_add = [m for m in evo_moves if m not in existing_evo_moves]
    
    if not new_evo_moves_to_add:
        return learnset_content
    
    # Insert new evo moves at the beginning (after opening brace)
    # Find where to insert (after the opening {)
    open_brace = old_block.find('{')
    insert_pos = open_brace + 1
    # Skip whitespace/newlines after brace
    while insert_pos < len(old_block) and old_block[insert_pos] in ' \t\n\r':
        insert_pos += 1
    
    # Build new evo move lines
    evo_move_lines = []
    for move in new_evo_moves_to_add:
        evo_move_lines.append(f"    LEVEL_UP_MOVE( 0, {move}),")
    
    # Insert the new lines
    new_block = old_block[:insert_pos] + "\n".join(evo_move_lines) + "\n" + old_block[insert_pos:]
    
    return learnset_content[:start] + new_block + learnset_content[end:]

    
    pat = re.compile(r"static const u16\s+s%sEggMoveLearnset\s*\[\s*\]\s*=\s*\{" % re.escape(species_camel), re.IGNORECASE)
    m = pat.search(egg_moves_content)
    if not m:
        return egg_moves_content
    
    start = m.start()
    brace_pos = egg_moves_content.find('{', m.end() - 1)
    i = brace_pos
    depth = 0
    end = None
    while i < len(egg_moves_content):
        if egg_moves_content[i] == '{':
            depth += 1
        elif egg_moves_content[i] == '}':
            depth -= 1
            if depth == 0:
                j = i + 1
                while j < len(egg_moves_content) and egg_moves_content[j].isspace():
                    j += 1
                if j < len(egg_moves_content) and egg_moves_content[j] == ';':
                    end = j + 1
                else:
                    end = i + 1
                break
        i += 1
    
    if end is None:
        return egg_moves_content
    
    old_block = egg_moves_content[start:end]
    
    # Parse existing egg moves (excluding MOVE_UNAVAILABLE)
    existing_egg_moves = []
    for match in re.finditer(r"\b(MOVE_[A-Z0-9_]+)\b", old_block):
        move = match.group(1)
        if move != "MOVE_UNAVAILABLE":
            existing_egg_moves.append(move)
    
    # Merge with new egg moves, avoiding duplicates
    for move in new_egg_moves:
        if move not in existing_egg_moves:
            existing_egg_moves.append(move)
    
    # Build new block
    new_lines = []
    for move in existing_egg_moves:
        new_lines.append(f"    {move},")
    new_lines.append("    MOVE_UNAVAILABLE,")
    new_lines.append("};")
    
    new_block = old_block.split('{')[0] + "{\n" + "\n".join(new_lines) + "\n"
    
    return egg_moves_content[:start] + new_block + egg_moves_content[end:]


def add_teachable_move(teachable_content: str, species_macro: str, new_moves: list) -> str:
    """
    Add new teachable moves to the teachable learnset.
    new_moves: list of MOVE_* macros
    Returns modified content.
    """
    # Find the array: static const u16 s<Species>TeachableLearnset[]
    species_camel = re.sub(r'_(.)', lambda m: m.group(1).upper(), species_macro.lower())
    species_camel = species_camel[0].upper() + species_camel[1:]
    
    pat = re.compile(r"static const u16\s+s%sTeachableLearnset\s*\[\s*\]\s*=\s*\{" % re.escape(species_camel), re.IGNORECASE)
    m = pat.search(teachable_content)
    if not m:
        return teachable_content
    
    start = m.start()
    brace_pos = teachable_content.find('{', m.end() - 1)
    i = brace_pos
    depth = 0
    end = None
    while i < len(teachable_content):
        if teachable_content[i] == '{':
            depth += 1
        elif teachable_content[i] == '}':
            depth -= 1
            if depth == 0:
                j = i + 1
                while j < len(teachable_content) and teachable_content[j].isspace():
                    j += 1
                if j < len(teachable_content) and teachable_content[j] == ';':
                    end = j + 1
                else:
                    end = i + 1
                break
        i += 1
    
    if end is None:
        return teachable_content
    
    old_block = teachable_content[start:end]
    
    # Parse existing teachable moves (excluding MOVE_UNAVAILABLE)
    existing_moves = []
    for match in re.finditer(r"\b(MOVE_[A-Z0-9_]+)\b", old_block):
        move = match.group(1)
        if move != "MOVE_UNAVAILABLE":
            existing_moves.append(move)
    
    # Merge with new moves, avoiding duplicates
    for move in new_moves:
        if move not in existing_moves:
            existing_moves.append(move)
    
    # Build new block
    new_lines = []
    for move in existing_moves:
        new_lines.append(f"    {move},")
    new_lines.append("    MOVE_UNAVAILABLE,")
    new_lines.append("};")
    
    new_block = old_block.split('{')[0] + "{\n" + "\n".join(new_lines) + "\n"
    
    return teachable_content[:start] + new_block + teachable_content[end:]


def replace_move_in_all_learnsets(learnset_content: str, species_macro: str, old_move: str, new_move: str) -> str:
    """
    Replace old_move with new_move in all learnsets (level-up) for the species.
    Returns modified content.
    """
    species_camel = re.sub(r'_(.)', lambda m: m.group(1).upper(), species_macro.lower())
    species_camel = species_camel[0].upper() + species_camel[1:]
    
    pat = re.compile(r"static const struct LevelUpMove\s+s%sLevelUpLearnset\s*\[\s*\]\s*=\s*\{" % re.escape(species_camel), re.IGNORECASE)
    m = pat.search(learnset_content)
    if not m:
        return learnset_content
    
    start = m.start()
    brace_pos = learnset_content.find('{', m.end() - 1)
    i = brace_pos
    depth = 0
    end = None
    while i < len(learnset_content):
        if learnset_content[i] == '{':
            depth += 1
        elif learnset_content[i] == '}':
            depth -= 1
            if depth == 0:
                j = i + 1
                while j < len(learnset_content) and learnset_content[j].isspace():
                    j += 1
                if j < len(learnset_content) and learnset_content[j] == ';':
                    end = j + 1
                else:
                    end = i + 1
                break
        i += 1
    
    if end is None:
        return learnset_content
    
    old_block = learnset_content[start:end]
    new_block = old_block.replace(old_move, new_move)
    
    return learnset_content[:start] + new_block + learnset_content[end:]


def replace_move_in_egg_moves(egg_moves_content: str, species_macro: str, old_move: str, new_move: str) -> str:
    """Replace old_move with new_move in egg moves for the species."""
    species_camel = re.sub(r'_(.)', lambda m: m.group(1).upper(), species_macro.lower())
    species_camel = species_camel[0].upper() + species_camel[1:]
    
    pat = re.compile(r"static const u16\s+s%sEggMoveLearnset\s*\[\s*\]\s*=\s*\{" % re.escape(species_camel), re.IGNORECASE)
    m = pat.search(egg_moves_content)
    if not m:
        return egg_moves_content
    
    start = m.start()
    brace_pos = egg_moves_content.find('{', m.end() - 1)
    i = brace_pos
    depth = 0
    end = None
    while i < len(egg_moves_content):
        if egg_moves_content[i] == '{':
            depth += 1
        elif egg_moves_content[i] == '}':
            depth -= 1
            if depth == 0:
                j = i + 1
                while j < len(egg_moves_content) and egg_moves_content[j].isspace():
                    j += 1
                if j < len(egg_moves_content) and egg_moves_content[j] == ';':
                    end = j + 1
                else:
                    end = i + 1
                break
        i += 1
    
    if end is None:
        return egg_moves_content
    
    old_block = egg_moves_content[start:end]
    new_block = old_block.replace(old_move, new_move)
    
    return egg_moves_content[:start] + new_block + egg_moves_content[end:]


def replace_move_in_teachable_moves(teachable_content: str, species_macro: str, old_move: str, new_move: str) -> str:
    """Replace old_move with new_move in teachable moves for the species."""
    species_camel = re.sub(r'_(.)', lambda m: m.group(1).upper(), species_macro.lower())
    species_camel = species_camel[0].upper() + species_camel[1:]
    
    pat = re.compile(r"static const u16\s+s%sTeachableLearnset\s*\[\s*\]\s*=\s*\{" % re.escape(species_camel), re.IGNORECASE)
    m = pat.search(teachable_content)
    if not m:
        return teachable_content
    
    start = m.start()
    brace_pos = teachable_content.find('{', m.end() - 1)
    i = brace_pos
    depth = 0
    end = None
    while i < len(teachable_content):
        if teachable_content[i] == '{':
            depth += 1
        elif teachable_content[i] == '}':
            depth -= 1
            if depth == 0:
                j = i + 1
                while j < len(teachable_content) and teachable_content[j].isspace():
                    j += 1
                if j < len(teachable_content) and teachable_content[j] == ';':
                    end = j + 1
                else:
                    end = i + 1
                break
        i += 1
    
    if end is None:
        return teachable_content
    
    old_block = teachable_content[start:end]
    new_block = old_block.replace(old_move, new_move)
    
    return teachable_content[:start] + new_block + teachable_content[end:]


def process_csv(csv_path, species_dir, hoenn_src_path, abilities_header_path, types_header_path, learnset_dir=None, egg_moves_path=None, teachable_moves_path=None, moves_header_path=None, dry_run=False):
    family_files = find_family_files(species_dir)
    family_contents = {p: load_file(p) for p in family_files}

    abilities_set = load_abilities_set(abilities_header_path)
    types_set = load_abilities_set(types_header_path)
    moves_set = load_moves_set(moves_header_path) if moves_header_path else set()
    
    # Always load learnset files - they are core to the operation
    learnset_contents = {}
    if learnset_dir:
        for path in find_learnset_files(learnset_dir):
            learnset_contents[path] = load_file(path)
    
    egg_moves_content = None
    if egg_moves_path and os.path.isfile(egg_moves_path):
        egg_moves_content = load_file(egg_moves_path)
    
    teachable_content = None
    if teachable_moves_path and os.path.isfile(teachable_moves_path):
        teachable_content = load_file(teachable_moves_path)

    not_found = []
    hoenn_list = []
    modified_files = {}

    with open(csv_path, newline='', encoding='utf-8') as csvfile:
        reader = csv.reader(csvfile)
        # Read headers separately
        headers_raw = next(reader)
        headers_lower = [h.lower() for h in headers_raw]
        
        # find name column
        name_idx = None
        for candidate in ('pokemon', 'species', 'name'):
            if candidate in headers_lower:
                name_idx = headers_lower.index(candidate)
                break
        if name_idx is None:
            print('CSV does not contain a species/pokemon/name header')
            return 1

        # find "Attack Changes" column
        attack_changes_idx = None
        for idx, header in enumerate(headers_raw):
            if header.lower().replace(' ', '').replace('_', '') == 'attackchanges':
                attack_changes_idx = idx
                break

        for row in reader:
            if not row or len(row) <= name_idx:
                continue
            raw_name = row[name_idx].strip()
            if not raw_name:
                continue
            # match ignoring case but exact spelling
            species_name = normalize_name(raw_name)
            macro_species = macro_name_for_species(species_name)
            
            # Helper function to get values from row by header name (normalized matching)
            def get_row_value(header_key_pattern):
                """Get row value by fuzzy header matching. header_key_pattern should be normalized."""
                for idx, header in enumerate(headers_raw):
                    normalized = header.lower().replace(' ', '').replace('_', '').replace('-', '')
                    if normalized == header_key_pattern.lower().replace(' ', '').replace('_', '').replace('-', ''):
                        if idx < len(row):
                            return row[idx].strip()
                return ''
            
            found_file = None
            found_block = None
            found_start = found_end = None

            for path, content in family_contents.items():
                start, end, block = find_species_block(content, macro_species)
                if block is not None:
                    found_file = path
                    found_block = block
                    found_start = start
                    found_end = end
                    break

            if not found_file:
                print(f"Not found: {species_name}")
                not_found.append(species_name)
                continue

            new_block = found_block

            # Abilities: detect common headers and get values by index
            ability_macros = []
            for ability_candidate in ('ability1', 'ability2', 'hiddenability'):
                val = get_row_value(ability_candidate)
                ability_macros.append(ability_macro(val))

            # Verify abilities exist in include/abilities.h (unless ABILITY_NONE)
            bad_ability = None
            for am in ability_macros:
                if am == 'ABILITY_NONE':
                    continue
                if abilities_set and am not in abilities_set:
                    bad_ability = am
                    break

            if bad_ability:
                print(f"Error: ability {bad_ability} not found in {abilities_header_path}; skipping {species_name}")
                not_found.append(species_name)
                continue

            if ability_macros:
                new_block = replace_abilities_in_block(new_block, ability_macros)

            # Types: detect "Type 1" / "Type 2" (case-insensitive)
            type_macros = []
            for type_candidate in ('type1', 'type2'):
                val = get_row_value(type_candidate)
                if val:
                    type_macros.append(type_macro(val))

            # Verify types exist in header (if provided)
            bad_type = None
            for tm in type_macros:
                if tm == 'TYPE_NONE':
                    continue
                if types_set and tm not in types_set:
                    bad_type = tm
                    break

            if bad_type:
                print(f"Error: type {bad_type} not found in {types_header_path}; skipping {species_name}")
                not_found.append(species_name)
                continue

            if type_macros:
                new_block = replace_types_in_block(new_block, type_macros)

            # Stats
            stats_map = {}
            # Robust mapping from normalized CSV header -> internal stat key
            header_to_stat = {
                'hp': 'hp',
                'hpmax': 'hp',
                'atk': 'atk', 'attack': 'atk',
                'def': 'def', 'defense': 'def',
                'spatk': 'spatk', 'spattack': 'spatk', 'sp_atk': 'spatk',
                'spdef': 'spdef', 'spdefense': 'spdef', 'sp_def': 'spdef',
                'speed': 'speed', 'spd': 'speed'
            }

            for idx, header in enumerate(headers_raw):
                nk = header.lower().replace(' ', '').replace('_', '').replace('-', '')
                if nk in header_to_stat and idx < len(row):
                    try:
                        val = int(row[idx])
                    except Exception:
                        val = None
                    if val is not None:
                        stats_map[header_to_stat[nk]] = val

            if stats_map:
                new_block = replace_base_stats_in_block(new_block, stats_map)

            # Process moves: Parse move changes from columns starting at attack_changes_idx onwards
            # Process each move change column by INDEX (not name) since columns after "Attack Changes" have empty headers
            levelup_moves = {}  # level -> MOVE_*
            evo_moves = []  # list of MOVE_*
            learnable_moves = []  # list of MOVE_*
            egg_moves_to_add = []  # list of MOVE_*
            move_swaps = []  # list of (old_move, new_move) tuples
            
            if attack_changes_idx is not None:
                # Process columns from attack_changes_idx onwards
                for col_idx in range(attack_changes_idx, len(row)):
                    change_value = row[col_idx].strip()
                    if not change_value:
                        continue
                    
                    # Parse the change value
                    if re.match(r'^\d+:', change_value):
                        # Level-up move: "50: MOVE_NAME"
                        match = re.match(r'^(\d+):\s*(.+)$', change_value)
                        if match:
                            level = int(match.group(1))
                            move_name = match.group(2).strip()
                            move_macro_str = move_macro(move_name)
                            if species_name == 'Ledian':
                                print(f"DEBUG {species_name}: Parsed levelup move: level {level}, {move_name!r} -> {move_macro_str!r}")
                            if move_macro_str:
                                # Validate move exists (if moves_set is populated)
                                if moves_set and move_macro_str not in moves_set:
                                    print(f"Warning: {species_name}: Move {move_macro_str} not found in {moves_header_path}; skipping")
                                    continue
                                levelup_moves[level] = move_macro_str
                    
                    elif change_value.startswith('Evo:'):
                        # Evolution move
                        move_name = change_value[4:].strip()
                        move_macro_str = move_macro(move_name)
                        if species_name == 'Ledian':
                            print(f"DEBUG {species_name}: Parsed Evo move: {move_name!r} -> {move_macro_str!r}")
                        if move_macro_str:
                            if moves_set and move_macro_str not in moves_set:
                                print(f"Warning: {species_name}: Move {move_macro_str} not found in {moves_header_path}; skipping")
                                continue
                            evo_moves.append(move_macro_str)
                            if species_name == 'Ledian':
                                print(f"DEBUG {species_name}: Added evo move {move_macro_str}")
                    
                    elif change_value.startswith('Learnable:'):
                        # Teachable/TM/Tutor move
                        move_name = change_value[10:].strip()
                        move_macro_str = move_macro(move_name)
                        if move_macro_str:
                            if moves_set and move_macro_str not in moves_set:
                                print(f"Warning: {species_name}: Move {move_macro_str} not found in {moves_header_path}; skipping")
                                continue
                            learnable_moves.append(move_macro_str)
                    
                    elif change_value.startswith('Egg:'):
                        # Egg move
                        move_name = change_value[4:].strip()
                        move_macro_str = move_macro(move_name)
                        if move_macro_str:
                            if moves_set and move_macro_str not in moves_set:
                                print(f"Warning: {species_name}: Move {move_macro_str} not found in {moves_header_path}; skipping")
                                continue
                            egg_moves_to_add.append(move_macro_str)
                    
                    elif '->' in change_value:
                        # Move swap: "OLD_MOVE -> NEW_MOVE"
                        parts = change_value.split('->')
                        if len(parts) == 2:
                            old_name = parts[0].strip()
                            new_name = parts[1].strip()
                            old_macro_str = move_macro(old_name)
                            new_macro_str = move_macro(new_name)
                            if old_macro_str and new_macro_str:
                                if moves_set and (old_macro_str not in moves_set or new_macro_str not in moves_set):
                                    print(f"Warning: {species_name}: Move swap {old_macro_str} -> {new_macro_str}: one or both not found; skipping")
                                    continue
                                move_swaps.append((old_macro_str, new_macro_str))
            
            # Track move changes for logging
            move_changes_applied = []
            
            # Apply move changes to learnsets
            if levelup_moves and learnset_contents:
                # Find the appropriate learnset file for this species
                for path, content in learnset_contents.items():
                    updated = update_levelup_moves(content, macro_species, levelup_moves)
                    if updated != content:
                        learnset_contents[path] = updated
                        if path not in modified_files:
                            modified_files[path] = updated
                        else:
                            modified_files[path] = updated
                        break
                move_changes_applied.append(f"added {len(levelup_moves)} level-up move(s)")
            
            if evo_moves and learnset_contents:
                # Evolution moves are also stored in learnsets
                for path, content in learnset_contents.items():
                    updated = add_evo_moves(content, macro_species, evo_moves)
                    if updated != content:
                        learnset_contents[path] = updated
                        modified_files[path] = updated
                        break
                move_changes_applied.append(f"added {len(evo_moves)} evolution move(s)")
            
            if egg_moves_to_add and egg_moves_content is not None:
                updated = find_and_update_egg_moves(egg_moves_content, macro_species, egg_moves_to_add)
                if updated != egg_moves_content:
                    egg_moves_content = updated
                move_changes_applied.append(f"added {len(egg_moves_to_add)} egg move(s)")
            
            if learnable_moves and teachable_content is not None:
                updated = add_teachable_move(teachable_content, macro_species, learnable_moves)
                if updated != teachable_content:
                    teachable_content = updated
                move_changes_applied.append(f"added {len(learnable_moves)} learnable move(s)")
            
            # Apply move swaps to all learnsets
            for old_move, new_move in move_swaps:
                swap_found = False
                if learnset_contents:
                    for path, content in learnset_contents.items():
                        updated = replace_move_in_all_learnsets(content, macro_species, old_move, new_move)
                        if updated != content:
                            learnset_contents[path] = updated
                            modified_files[path] = updated
                            swap_found = True
                
                if egg_moves_content is not None:
                    updated = replace_move_in_egg_moves(egg_moves_content, macro_species, old_move, new_move)
                    if updated != egg_moves_content:
                        egg_moves_content = updated
                        swap_found = True
                
                if teachable_content is not None:
                    updated = replace_move_in_teachable_moves(teachable_content, macro_species, old_move, new_move)
                    if updated != teachable_content:
                        teachable_content = updated
                        swap_found = True
                
                if swap_found:
                    move_changes_applied.append(f"swapped {old_move} -> {new_move}")

            # Collect all changes for summary output
            changed = []
            
            # Only check family block changes if the final block differs from the original
            if new_block != found_block:
                # Abilities diff
                m_old = re.search(r"\.abilities\s*=\s*\{([^}]*)\},", found_block, re.S)
                old_txt = m_old.group(0).strip() if m_old else None
                m_new = re.search(r"\.abilities\s*=\s*\{([^}]*)\},", new_block, re.S)
                new_txt = m_new.group(0).strip() if m_new else None
                if old_txt != new_txt:
                    changed.append('abilities')
                    print(f"{species_name}: Abilities change -> old: {old_txt!r} new: {new_txt!r}")

                # Types diff
                m_old_types = re.search(r"\.types\s*=\s*(?:MON_TYPES\([^)]*\)|\{[^}]*\})\s*,", found_block, re.S)
                old_types_txt = m_old_types.group(0).strip() if m_old_types else None
                m_new_types = re.search(r"\.types\s*=\s*(?:MON_TYPES\([^)]*\)|\{[^}]*\})\s*,", new_block, re.S)
                new_types_txt = m_new_types.group(0).strip() if m_new_types else None
                if old_types_txt != new_types_txt:
                    changed.append('types')
                    print(f"{species_name}: Types change -> old: {old_types_txt!r} new: {new_types_txt!r}")

                # base stat diffs for individual fields
                stat_fields = [('.baseHP','hp'), ('.baseAttack','atk'), ('.baseDefense','def'), ('.baseSpAttack','spatk'), ('.baseSpDefense','spdef'), ('.baseSpeed','speed')]
                for field_name, key in stat_fields:
                    pat = re.compile(r"\.%s\s*=\s*(\d+)\s*," % re.escape(field_name[1:]))
                    old_m = pat.search(found_block)
                    new_m = pat.search(new_block)
                    old_val = old_m.group(1) if old_m else None
                    new_val = new_m.group(1) if new_m else None
                    if old_val != new_val:
                        changed.append(field_name)
                        print(f"{species_name}: {field_name} change -> old: {old_val!r} new: {new_val!r}")

            # Combine all changes (family block + movesets) for summary
            if changed or move_changes_applied:
                all_changes = changed + move_changes_applied
                print(f"{species_name}: Updated -> {', '.join(all_changes)}")

            # write back to content buffer
            content = family_contents[found_file]
            content = content[:found_start] + new_block + content[found_end:]
            family_contents[found_file] = content
            modified_files[found_file] = content

            # Add to hoenn list (macro form without SPECIES_ prefix)
            hoenn_list.append(macro_species)

    # Write modified family files
    if not dry_run:
        for path, content in modified_files.items():
            write_file(path, content)
    
    # Write modified learnset files
    if not dry_run:
        for path, content in learnset_contents.items():
            write_file(path, content)
    
    # Write egg moves file
    if not dry_run and egg_moves_content is not None and egg_moves_path:
        write_file(egg_moves_path, egg_moves_content)
    
    # Write teachable moves file
    if not dry_run and teachable_content is not None and teachable_moves_path:
        write_file(teachable_moves_path, teachable_content)

    # Update Hoenn order in src/pokemon.c
    if hoenn_list:
        hoenn_content = load_file(hoenn_src_path)
        arr_pat = re.compile(r"static const enum NationalDexOrder sHoennToNationalOrder\[HOENN_DEX_COUNT - 1\]\s*=\s*\{", re.M)
        m = arr_pat.search(hoenn_content)
        if not m:
            print('Could not find sHoennToNationalOrder array in', hoenn_src_path)
            return 1
        start = m.end()
        # find closing }; for the array
        brace_i = hoenn_content.find('{', m.start())
        i = brace_i
        depth = 0
        end = None
        while i < len(hoenn_content):
            if hoenn_content[i] == '{':
                depth += 1
            elif hoenn_content[i] == '}':
                depth -= 1
                if depth == 0:
                    # find following semicolon or closing ;
                    j = i + 1
                    while j < len(hoenn_content) and hoenn_content[j].isspace():
                        j += 1
                    end = i
                    break
            i += 1
        if end is None:
            print('Could not parse Hoenn array braces in', hoenn_src_path)
            return 1

        # Build replacement body
        body_lines = []
        for name in hoenn_list:
            body_lines.append(f"    HOENN_TO_NATIONAL({name}),")
        body_text = "\n".join(body_lines) + "\n"

        new_hoenn = hoenn_content[:brace_i+1] + "\n" + body_text + hoenn_content[end:]

        if not dry_run:
            write_file(hoenn_src_path, new_hoenn)

    print('Done. Not found count:', len(not_found))
    return 0


def main():
    p = argparse.ArgumentParser(description='Apply Pokémon changes from CSV to family files and movesets.')
    p.add_argument('--csv', default='PokemonFossilizedHoennDex.csv', help='CSV file with changes')
    p.add_argument('--dry-run', action='store_true', help='Preview changes without modifying files')
    p.add_argument('--validate-moves', action='store_true', help='Validate moves exist in moves header')
    args = p.parse_args()

    csv_path = args.csv
    if not os.path.isfile(csv_path):
        print('CSV file not found:', csv_path)
        sys.exit(2)

    # Use standard paths for all required files
    species_dir = os.path.join('src', 'data', 'pokemon', 'species_info')
    hoenn_src = os.path.join('src', 'pokemon.c')
    abilities_header = os.path.join('include', 'abilities.h')
    types_header = os.path.join('include', 'types.h')
    learnset_dir = os.path.join('src', 'data', 'pokemon', 'level_up_learnsets')
    egg_moves_path = os.path.join('src', 'data', 'pokemon', 'egg_moves.h')
    teachable_moves_path = os.path.join('src', 'data', 'pokemon', 'teachable_learnsets.h')
    moves_header = os.path.join('include', 'constants', 'moves.h') if args.validate_moves else None

    if not os.path.isdir(species_dir):
        print('Species directory not found:', species_dir)
        sys.exit(2)

    if not os.path.isfile(hoenn_src):
        print('Hoenn source file not found:', hoenn_src)
        sys.exit(2)

    sys.exit(process_csv(csv_path, species_dir, hoenn_src, abilities_header, types_header,
                        learnset_dir=learnset_dir, egg_moves_path=egg_moves_path,
                        teachable_moves_path=teachable_moves_path, moves_header_path=moves_header,
                        dry_run=args.dry_run))


if __name__ == '__main__':
    main()
