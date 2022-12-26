import math
import random

data = []
all_data = []
row = []
next_list = list(range(6))
random.shuffle(next_list)
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
print(dataset)





