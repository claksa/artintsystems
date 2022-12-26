import math
import random

def freq(T, p):
    return T.count(p)

data = []
row = []
with open("DATA.csv", newline='') as file:
    for line in file:
        row = line.split(';')
        for i in range(1,len(row)):
            row[i] = int(row[i])
        row.pop(0)
        data.append(row)

attr_num = math.sqrt(len(row)+1)
random_attr = list(range(round(attr_num)))
random.shuffle(random_attr)
dataset = [([data[k][j] for j in random_attr], data[k][-1]) for k in range(len(data))]

dict = dict()
for i in random_attr:
    attr = []
    for row in dataset:
        params = row[0]
        attr.append(params[i])
    dict[i] = attr
print(dict.keys())

# classes = []
# for i in range(len(random_attr)):
#     c = set()
#     for row in dataset:
#         params = row[1]
#         c.add(params)
#     classes.append(list(c))
# print(classes)

metrics = set()
for row in dataset:
    metrics.add(row[1])
metrics = list(metrics)
values = list(dict.values())
all_freqs = []
for m in metrics:
    freqs = []
    for v in values:
        freqs.append(v.count(m))
    all_freqs.append(freqs)
print(all_freqs)
