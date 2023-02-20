import math
import random
import numpy as np


def print_dict(dict):
    for key in dict:
        print(key, '->', dict[key])
        print()

def freq(T, p):
    return list(T).count(p)

def transpose_dict(dict):
    for key in dict:
        up_dict = {key: 
                   dict[key][0].transpose()
                   }
        dict.update(up_dict)


# dict_T not transposed grade --> [row0, row1, row2]
def info_T(dict_T):
    size = 0
    for key in dict_T:
        size += dict_T[key][1]
    s = 0
    for key in dict_T:
        p = dict_T[key][1]/size
        if (p > 0):
            p *= math.log2(p)
        s += p
    return -s

# i -- индекс атрибута
def info_x(T_i, i, labels_by_grade):
    info_x = 0
    cnt = 1
    T_size = sum(T_i[1])
    for j in range(len(T_i[0])):
        s = 0
        for grade_key in labels_by_grade:
            f = freq(labels_by_grade[grade_key][i], T_i[0][j])/T_i[1][j]
            if (f!=0):
                cnt = -(f*math.log2(f))
                s += cnt
        info_x += ((T_i[1][j]/T_size)*s)
    return info_x

def split_info_x(T_i):
    T_size = sum(T_i[1])
    s_split = 0
    for j in range(len(T_i[0])):
        p = T_i[1][j]/T_size
        if (p > 0):
            p *= math.log2(p)
        s_split += p
    return -s_split

def find_max_gain_attr(dict_T, dict_attr):
    info = info_T(dict_T)
    transposed_dict_T = dict_T
    for key in dict_T:
        up_dict = {key: 
                   dict_T[key][0].transpose()
                   }
        transposed_dict_T.update(up_dict)
   
    attr_max_gain = -1
    max_gain_ratio = -1
    attr_ind = -1
    for i, key_attr in enumerate(dict_attr):
        infox = info_x(dict_attr[key_attr], i, transposed_dict_T)
        split_infox = split_info_x(dict_attr[key_attr])
        gain = info - infox
        #gain_ratio = gain/split_info_x
        gain_ratio = gain
        if (gain_ratio > max_gain_ratio):
            max_gain_ratio = gain_ratio
            attr_max_gain = key_attr
            attr_ind = i
    return attr_max_gain, max_gain_ratio, attr_ind

def rec_des_tree(dict_T, dict_attr, attr_num, attr_ind):
    labels = dict_attr.pop(attr_num)[0]
    pass
    for l in range(len(labels)):
        print("node: ", attr_num)
        print("considered node label: ", labels[l])
        print()
        ndict_T = dict_T.copy() # dict_T: grade --> [attr0, attr1, ..., attrN]
        ndict_attr = dict_attr.copy()
        leaf_node = -1
        for key in list(ndict_T.keys()):
            indexes = []
            for i, v in enumerate(ndict_T[key][attr_ind]):
                if (labels[l] == v):
                    indexes.append(i)
            if not indexes:
                del ndict_T[key]
                continue
            new_arr = np.array(ndict_T[key]).transpose()
            rows = []
            for i in indexes:
                rows.append(new_arr[i])
            rows = np.delete(rows, attr_ind, axis=1)
            ndict_T[key] = (rows, len(rows))
        values = ndict_T.copy()
        pass
        for i, key in enumerate(dict_attr):
            attributes = np.array([])
            for k in ndict_T:
                arr = ndict_T[k][0].transpose()
                if i >= len(arr): # нет нужных значений 
                    break
                attributes = np.append(attributes, arr[i]) # grade --> [attr0, attr1,..., attrN]
            ndict_attr[key] = np.unique(attributes, return_counts=True)
        attr_num1, gain_ratio, attr_ind1 = find_max_gain_attr(ndict_T, ndict_attr)
        pass
        if gain_ratio <= 0:
            pass
            if best_key in values.keys():
                TP_arr.append(values[best_key][1])
            for k in bad_keys:
                if k in values.keys():
                    TN_arr.append(values[k][1])
            print("leaf: ", labels[l])
            if l != (len(labels)-1):
                continue
            else:
                print("-----")
                print()
                return
        else:
            rec_des_tree(ndict_T, ndict_attr, attr_num1, attr_ind1)

def init_DT(dict_T, dict_attr):
    attr_num, gain_ratio, attr_ind = find_max_gain_attr(dict_T, dict_attr)
    rec_des_tree(dict_T, dict_attr, attr_num, attr_ind)

data = []
with open("DATA.csv", newline='') as file:
    for line in file:
        row = line.split(';')
        for i in range(1,len(row)):
            row[i] = int(row[i])
        row.pop(0)
        data.append(row)
attr_amount = round(math.sqrt(len(row)+1)) 
TP = 0
TN = 0
TP_arr = []
TN_arr = []
ROC_arr = []

#attr_amount = 4
attr_nums = random.sample(range(len(row)), attr_amount)
#attr_nums = [0, 1, 2, 3]

best_key = 7
bad_keys = [0, 1, 2, 3, 4, 5, 6]

print('indexes of random attributes: ', attr_nums)
dataset = [([data[k][j] for j in attr_nums], data[k][-1]) for k in range(len(data))]
#dataset = [
#    ([1, 1, 1, 0], 0),
#    ([1, 1, 1, 1], 0),
#   ([2, 1, 1, 0], 1),
#    ([3, 2, 1, 0], 1),
#    ([3, 3, 0, 0], 1),
#    ([3, 3, 0, 1], 0),
#    ([2, 3, 0, 1], 1),
#    ([1, 2, 1, 0], 0),
#    ([1, 3, 0, 0], 1),
#    ([3, 2, 0, 0], 1),
#    ([1, 2, 0, 1], 1),
#    ([2, 2, 1, 1], 1),
#    ([2, 1, 0, 0], 1),
#    ([3, 2, 1, 1], 0)
#    ]
dict_attr = dict(zip(attr_nums, [None]*len(attr_nums)))

attributes = []
for row in dataset:
    attributes.append(row[0])
attributes = np.array(attributes).transpose()

for attr, key in zip(attributes, dict_attr):
    dict_attr[key] = np.unique(attr, return_counts=True)

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

init_DT(dict_T, dict_attr)
TP = sum(TP_arr)
TN = sum(TN_arr)

print("TP: ", TP)
print("TN: ", TN)
print("Accuracy: ", (TP+TN)/len(dataset))