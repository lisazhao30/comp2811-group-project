# Generate a smaller 500 line csv from the dataset

# This can be converted to a sqlite database using csv-to-sqlite
# $ pip install csv-to-sqlite
# $ csv-to-sqlite -f water_samples.csv -t quick
# https://github.com/zblesk/csv-to-sqlite

import csv

rows = []
with open("data/2024.csv", "r") as f:
    reader = csv.reader(f)
    for _ in range(500):
        rows.append(next(reader))

with open("data/2024_small.csv", "w") as f:
    writer = csv.writer(f, lineterminator="\n")
    for r in rows:
        writer.writerow(r)
