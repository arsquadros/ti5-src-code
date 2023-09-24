from datetime import datetime

import general

if __name__ == '__main__':

    values = []

    for i in range(2):
        counter = 0
        start = datetime.now()
        for j in range(1000000000):
            counter += 1
        end = datetime.now()

        seconds = (end - start).seconds
        values.append(seconds)

    mean = general.mean(values)
    median = general.median(values)
    total = general.sum(values)

    print("mean:", mean)
    print("median:", median)
    print("total:", total)