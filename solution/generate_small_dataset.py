# Generate a smaller 500 line csv from the dataset

# This can be converted to a sqlite database using csv-to-sqlite
# $ pip install csv-to-sqlite
# $ csv-to-sqlite -f water_samples.csv -t quick
# https://github.com/zblesk/csv-to-sqlite

import csv
import random

NUM_OF_ROWS = 5000

rows = []
with open("data/2024.csv", "r") as f:
    reader = csv.reader(f)
    all_rows = list(reader)

row_count = len(all_rows)
rows_to_select = random.sample(range(1, row_count-1), NUM_OF_ROWS)
rows.append(all_rows[0]) # Header
for i in rows_to_select:
    rows.append(all_rows[i])

with open("data/2024_small.csv", "w") as f:
    writer = csv.writer(f, lineterminator="\n")
    for r in rows:
        writer.writerow(r)
