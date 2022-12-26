import math
import random

# T - data, i - column, c - param
def freq(T, column, p):
    return T[column].count(p)

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

classes = []
for i in range(len(random_attr)):
    c = set()
    for row in dataset:
        params = row[0]
        c.add(params[i])
    classes.append(c)

dict = dict()
for i in random_attr:
    attr = []
    for row in dataset:
        params = row[0]
        attr.append(params[i])
    dict[i] = attr

freqs = []
for k, v in dict.items():
    print(v.count(1))