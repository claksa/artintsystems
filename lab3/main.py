import math
import random
import numpy as np

def print_dict(dict):
    for key in dict:
        print(key, '->', dict[key])

def freq(T, p):
    return T.count(p)


data = []
with open("DATA.csv", newline='') as file:
    for line in file:
        row = line.split(';')
        for i in range(1,len(row)):
            row[i] = int(row[i])
        row.pop(0)
        data.append(row)
attr_amount = round(math.sqrt(len(row)+1)) 
attr_nums = random.sample(range(len(row)), attr_amount)
print('indexes of random attributes: ', attr_nums)
dataset = [([data[k][j] for j in attr_nums], data[k][-1]) for k in range(len(data))]
dict_attr = dict(zip(attr_nums, [None]*len(attr_nums)))

attributes = []
for row in dataset:
    attributes.append(row[0])
attributes = np.array(attributes).transpose()
for attr, key in zip(attributes, dict_attr):
    dict_attr[key] = np.unique(attr, return_counts=True)
print(dict_attr)

grades = set()
for row in dataset:
    grades.add(row[1])
grades = list(grades)

dict_T = dict(zip(grades, []*len(grades)))
for key in grades:
    attributes = []
    for row in dataset:
        if row[1] == key:
            attributes.append(row[0])
    dict_T[key] = (np.array(attributes), len(attributes))


info_ent = 0
s = 0
dataset_size = len(dataset)
for key in dict_T:
    freq = dict_T[key][1]
    p = freq/dataset_size
    s += p*math.log2(p)
info_ent = -s

# example dataset
sample_arr = np.array([
    [1, 1, 1, 0, 0],
    [1, 1, 1, 1, 0],
    [2, 1, 1, 0, 1]
    ])
transposed_sample_arr = sample_arr.transpose()
classes = transposed_sample_arr[-1]
print(classes)
transposed_sample_arr = transposed_sample_arr[:-1, :]



def info_x(labels):
    s = 0
    for label in labels:
        label = np.array(label)
        label = label.transpose()
        print(label)
        #info(label)

labels = []
for a in transposed_sample_arr:
    labels.append(
        [list(a), list(classes)]
        )
info_x(labels)


