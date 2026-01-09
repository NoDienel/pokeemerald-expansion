#!/usr/bin/env python3
"""
Script to apply changes from PokemonFossilizedHoennDex.csv to gen_X family files
and rewrite the Hoenn dex order in src/pokemon.c.

Behavior:
- Read CSV (case-insensitive headers). The Pokémon name header can be "pokemon", "species" or "name".
- For each row, locate the species in any gen_*_families.h file by matching "[SPECIES_<NAME>]" (case-insensitive name match but exact spelling required).
- If ability columns are present (ability1, ability2, hidden_ability, ability_1, etc.), replace the `.abilities = { ... },` line in that species block with ABILITY_... names. Empty values become `ABILITY_NONE`.
- If stat columns are present (hp, atk, def, spatk, spdef, speed), overwrite a `.baseStats = { ... },` block (best-effort).
- Build a Hoenn order list from the CSV rows (in CSV order) for species that were found, and replace the sHoennToNationalOrder array in `src/pokemon.c` with `HOENN_TO_NATIONAL(NAME),` entries.
- Print species that were not found and continue.

Ignored CSV fields: "aquire method", "attack changes", "fossil" (these are skipped).

Usage: run from repo root. Defaults to the attached CSV and repository paths.
"""

import argparse
import csv
import os
import re
import sys
from collections import OrderedDict


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


def type_macro(name: str) -> str:
    if not name or name.strip() == "":
        return "TYPE_NONE"
    s = name.strip().upper()
    s = re.sub(r"[^A-Z0-9_]+", "_", s)
    return "TYPE_" + s


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


def process_csv(csv_path, species_dir, hoenn_src_path, abilities_header_path, types_header_path, dry_run=False):
    family_files = find_family_files(species_dir)
    family_contents = {p: load_file(p) for p in family_files}

    abilities_set = load_abilities_set(abilities_header_path)
    types_set = load_abilities_set(types_header_path)

    not_found = []
    hoenn_list = []
    modified_files = {}

    with open(csv_path, newline='', encoding='utf-8') as csvfile:
        reader = csv.DictReader(csvfile)
        headers = [h.lower() for h in reader.fieldnames]
        # find name column
        name_key = None
        for candidate in ('pokemon', 'species', 'name'):
            if candidate in headers:
                name_key = reader.fieldnames[headers.index(candidate)]
                break
        if not name_key:
            print('CSV does not contain a species/pokemon/name header')
            return 1

        for row in reader:
            raw_name = row.get(name_key, '').strip()
            if not raw_name:
                continue
            # match ignoring case but exact spelling
            species_name = normalize_name(raw_name)
            macro_species = macro_name_for_species(species_name)
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

            # Abilities: detect common headers
            ability_keys = []
            for key in row.keys():
                kl = key.lower().replace(' ', '').replace('-', '').replace('_', '')
                if kl in ('ability1','abilityone','ability_1'):
                    ability_keys.insert(0, key)
                elif kl in ('ability2','abilitytwo','ability_2'):
                    ability_keys.insert(1, key)
                elif kl in ('hiddenability','hidden','ability3','abilityhidden'):
                    ability_keys.append(key)

            ability_macros = []
            for ak in ability_keys:
                if ak in row:
                    ability_macros.append(ability_macro(row.get(ak, '')))

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
            type_keys = [None, None]
            for key in row.keys():
                nk = key.lower().replace(' ', '').replace('_','').replace('-', '')
                if nk in ('type1','typeone','primarytype'):
                    type_keys[0] = key
                elif nk in ('type2','typetwo','secondarytype'):
                    type_keys[1] = key

            type_macros = []
            if type_keys[0] or type_keys[1]:
                # build two-entry list
                for i in range(2):
                    k = type_keys[i]
                    if k and k in row:
                        type_macros.append(type_macro(row.get(k, '')))
                    else:
                        type_macros.append('TYPE_NONE')

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

            for h in row.keys():
                nk = h.lower().replace(' ', '').replace('_', '').replace('-', '')
                if nk in header_to_stat:
                    try:
                        val = int(row[h])
                    except Exception:
                        val = None
                    if val is not None:
                        stats_map[header_to_stat[nk]] = val

            if stats_map:
                new_block = replace_base_stats_in_block(new_block, stats_map)

            # Only print changes if the final block differs from the original
            if new_block != found_block:
                changed = []
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

                # If any change detected, print a summary line
                if changed:
                    print(f"{species_name}: Updated fields -> {', '.join(changed)}")

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
    p = argparse.ArgumentParser()
    p.add_argument('--csv', default='PokemonFossilizedHoennDex.csv')
    p.add_argument('--species-dir', default=os.path.join('src','data','pokemon','species_info'))
    p.add_argument('--hoenn-src', default=os.path.join('src','pokemon.c'))
    p.add_argument('--abilities-header', default=os.path.join('include','abilities.h'))
    p.add_argument('--types-header', default=os.path.join('include','types.h'))
    p.add_argument('--dry-run', action='store_true')
    args = p.parse_args()

    csv_path = args.csv
    if not os.path.isfile(csv_path):
        print('CSV file not found:', csv_path)
        sys.exit(2)

    species_dir = args.species_dir
    if not os.path.isdir(species_dir):
        print('Species directory not found:', species_dir)
        sys.exit(2)

    hoenn_src = args.hoenn_src
    if not os.path.isfile(hoenn_src):
        print('Hoenn source file not found:', hoenn_src)
        sys.exit(2)

    sys.exit(process_csv(csv_path, species_dir, hoenn_src, args.abilities_header, args.types_header, dry_run=args.dry_run))


if __name__ == '__main__':
    main()
