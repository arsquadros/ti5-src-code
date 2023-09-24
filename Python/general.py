import numpy as np

def sum(values):
    return np.array(values).sum()

def mean(values):
    return np.array(values).mean()

def median(values):
    np_list = np.array(values)
    if len(np_list) % 2 == 0:
        return mean([np_list[int(len(values) / 2) - 1], np_list[int(len(values) / 2)]])
    else:
        return np_list[int(len(values) / 2)]

def std(values):
    return np.array(values).std()
