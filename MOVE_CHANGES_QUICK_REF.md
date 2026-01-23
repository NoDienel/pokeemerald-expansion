# Quick Reference: Move Change Syntax

## CSV Column Format

Place all move changes in columns after "Attack Changes" column.

## Supported Formats

| Format | Example | Effect |
|--------|---------|--------|
| `<level>: <move>` | `25: Power-Up Punch` | Add level-up move at level |
| `Evo: <move>` | `Evo: Leaf Storm` | Evolution move |
| `Learnable: <move>` | `Learnable: Swords Dance` | Add to teachable/TM moves |
| `Egg: <move>` | `Egg: Grassy Terrain` | Add to egg moves |
| `<old> -> <new>` | `Hidden Power -> Tri Attack` | Replace move in all learnsets |

## Examples in CSV

```csv
Name,HP,Attack,Defense,...,Attack Changes,,,,
Treecko,40,45,35,...,,25: Synthesis,Learnable: Close Combat,Egg: Grass Whistle,Hidden Power -> Tri Attack
Grovyle,50,65,45,...,Leaf Storm -> Solar Beam,30: Synthesis,Evo: Close Combat,,
Sceptile,70,85,65,...,,40: Synthesis,Learnable: Swords Dance,Egg: Magical Leaf,
```

## Running the Script

```bash
# From repository root with all defaults
python scripts/apply_fossilized_hoenn_changes.py

# With custom CSV file
python scripts/apply_fossilized_hoenn_changes.py --csv MyChanges.csv

# Preview changes without modifying files
python scripts/apply_fossilized_hoenn_changes.py --dry-run
```

## Move Name Rules

- Spaces become underscores: `Power Up Punch` → `MOVE_POWER_UP_PUNCH`
- Hyphens become underscores: `Close-Combat` → `MOVE_CLOSE_COMBAT`
- All text becomes uppercase automatically
- Use standard Pokémon move names from the game

## Output

The script prints:
- Each Pokémon processed
- Any species not found
- Summary of changes made per Pokémon
- Total count of species not found

Example output:
```
Treecko: Added 1 level-up move(s)
Treecko: Added 1 learnable move(s)
Treecko: Swapped MOVE_HIDDEN_POWER -> MOVE_TRI_ATTACK in all movesets
Done. Not found count: 0
```

## Notes

- Empty cells are ignored
- Move names are case-insensitive in CSV
- All output moves use MOVE_* macro format
- Invalid moves are skipped with warnings if move header is provided
- Changes are applied to level-up, egg, and teachable movesets as appropriate
