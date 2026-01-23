# Moveset Extension for apply_fossilized_hoenn_changes.py

## Overview

The `apply_fossilized_hoenn_changes.py` script reads Pokémon data changes from a CSV file and applies them to the game data. **Moveset processing is now a core feature** that is automatically applied whenever move changes are detected in the CSV.

## Core Features

The script processes the following changes from the CSV:

1. **Abilities** - Updates `.abilities` in species family files
2. **Types** - Updates `.types` in species family files  
3. **Base Stats** - Updates `.baseHP`, `.baseAttack`, etc. in species family files
4. **Movesets** - Automatically updates level-up, egg, and teachable movesets *(no special options needed)*
5. **Hoenn Dex Order** - Updates species order in `src/pokemon.c`

## Move Change Support

All columns after the "Attack Changes" column are processed as move change directives. The script supports five types of move changes:

#### 1. **Level-Up Moves**
Format: `<level>: <move_name>`

Example: `50: Power-Up Punch`

These moves are added to or replace entries in the level-up learnset at the specified level.

#### 2. **Evolution Moves**
Format: `Evo: <move_name>`

Example: `Evo: Leaf Storm`

These moves are moves the Pokémon learns upon evolution.

#### 3. **Learnable Moves** (TM/Tutor/Teachable)
Format: `Learnable: <move_name>`

Example: `Learnable: Swords Dance`

These moves are added to the teachable learnsets (TM/Tutor moves).

#### 4. **Egg Moves**
Format: `Egg: <move_name>`

Example: `Egg: Earth Power`

These moves are added to the egg move learnsets.

#### 5. **Move Swaps**
Format: `<old_move> -> <new_move>`

Example: `Hidden Power -> Tri Attack`

Move swaps replace all occurrences of the old move with the new move across **all learnset types** (level-up, egg, and teachable) for the Pokémon.

## Command-Line Arguments

The script now has a simplified argument structure focused on core functionality:

```bash
--csv PATH
    Path to the CSV file with changes (default: PokemonFossilizedHoennDex.csv)

--dry-run
    Preview all changes without modifying any files
    All changes are printed to console for verification

--validate-moves
    Optional: Validate that move names exist in include/constants/moves.h
    Moves that don't exist will trigger warnings and be skipped
```

All other paths are automatically determined from the standard repository structure.

## Usage Examples

```bash
# Run with default CSV in current directory
python scripts/apply_fossilized_hoenn_changes.py

# Run with custom CSV file
python scripts/apply_fossilized_hoenn_changes.py --csv MyChanges.csv

# Preview changes without modifying files (dry-run)
python scripts/apply_fossilized_hoenn_changes.py --dry-run

# Enable move validation (checks moves exist)
python scripts/apply_fossilized_hoenn_changes.py --validate-moves

# Combine options
python scripts/apply_fossilized_hoenn_changes.py --csv MyChanges.csv --dry-run --validate-moves
```

## CSV Format Example

| Name | Type 1 | HP | Attack | ... | Attack Changes | | | | |
|------|--------|----|---------|----|---|---|---|---|---|
| Treecko | Grass | 40 | 45 | ... | | 25: Synthesis | 50: Giga Drain | Learnable: Close Combat | Egg: Grassy Terrain |
| Grovyle | Grass | 50 | 65 | ... | Leaf Storm -> Solar Beam | 30: Synthesis | Evo: Close Combat | Learnable: Swords Dance | |

The "Attack Changes" column marks where move changes begin. All columns after it are processed as move directives.

## File Modifications

The script updates the following files automatically when changes are detected:

1. **Species family files**: `src/data/pokemon/species_info/gen_*.h`
   - Updates abilities, types, and base stats

2. **Level-up learnsets**: `src/data/pokemon/level_up_learnsets/gen_*.h`
   - Adds or modifies `s<Species>LevelUpLearnset[]` arrays

3. **Egg moves**: `src/data/pokemon/egg_moves.h`
   - Modifies `s<Species>EggMoveLearnset[]` arrays

4. **Teachable moves**: `src/data/pokemon/teachable_learnsets.h`
   - Modifies `s<Species>TeachableLearnset[]` arrays

5. **Hoenn Dex order**: `src/pokemon.c`
   - Updates `sHoennToNationalOrder` array

## Output

The script prints detailed information about all changes:

```
Treecko: Abilities change -> old: '.abilities = { ABILITY_OVERGROW, ABILITY_UNBURDEN },' new: '.abilities = { ABILITY_OVERGROW, ABILITY_SOLAR_POWER }'
Treecko: Updated -> abilities, added 2 level-up move(s), added 1 egg move(s), swapped MOVE_HIDDEN_POWER -> MOVE_TRI_ATTACK
```

In dry-run mode, all changes are printed without modifying files.

## Move Name Normalization

Move names are automatically normalized to MOVE_* macro format:
- Spaces and hyphens are converted to underscores
- All text is converted to uppercase
- Examples:
  - "Power-Up Punch" → `MOVE_POWER_UP_PUNCH`
  - "Close Combat" → `MOVE_CLOSE_COMBAT`
  - "Tri Attack" → `MOVE_TRI_ATTACK`

## Standard File Paths

The script uses these default paths (no customization needed):

```
src/data/pokemon/species_info/          - Species definitions
src/data/pokemon/level_up_learnsets/    - Level-up movesets
src/data/pokemon/egg_moves.h            - Egg movesets
src/data/pokemon/teachable_learnsets.h  - TM/Tutor movesets
include/abilities.h                      - Ability definitions
include/types.h                          - Type definitions
include/constants/moves.h                - Move definitions (optional)
src/pokemon.c                            - Hoenn dex order
```

## Notes

1. **Moveset changes are always applied** - If move columns are present in the CSV, they will be processed automatically as part of the core operation.

2. **Duplicate prevention** - The script automatically prevents duplicate moves when adding to learnsets.

3. **Move validation is optional** - Use `--validate-moves` if you want to ensure all moves exist before applying changes.

4. **Dry-run for safety** - Always use `--dry-run` first to preview changes before actually modifying files.

5. **Move swaps are comprehensive** - Swaps affect all learnset types for the Pokémon, ensuring consistency.

