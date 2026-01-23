import csv

with open('PokemonFossilizedHoennDex.csv', 'r') as f:
    reader = csv.DictReader(f)
    for i, row in enumerate(reader):
        if i == 10:  # Ledian is row 11 (0-indexed = 10)
            print(f"Fieldnames: {reader.fieldnames}")
            print(f"Fieldnames count: {len(reader.fieldnames)}")
            print()
            print("Type of row:", type(row))
            print("Dir of row:", [x for x in dir(row) if not x.startswith('_')])
            print()
            # Try accessing as dict
            print("As dict.values():")
            print(list(row.values()))
            print()
            # Check if there's an internal list
            if hasattr(row, '__iter__'):
                print("Row appears iterable")
            break
