import os
os.environ["MKL_NUM_THREADS"] = "1" 
os.environ["NUMEXPR_NUM_THREADS"] = "1" 
os.environ["OMP_NUM_THREADS"] = "1" 

import time
import numpy
import random

TEST_RUNS = 10

def benchMark(x, y):
    print(f"Computing dot product between vectors of size {len(x)}")
    start = time.time()
    result = numpy.dot(x, y)
    totalTime = (time.time() - start) / 1000

    print(f"Done in {totalTime:.9f} seconds")

    return totalTime

x = [1.0, 2.0, 3.0, 4.0]
y = [1.0, 2.0, 3.0, 4.0]
benchMark(x, y)

a = [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0]
b = [1.0, 2.0, 3.0, 4.0, 5.0, 1.0, 2.0, 3.0, 4.0, 5.0, 1.0, 2.0, 3.0, 4.0, 5.0]
benchMark(a, b)

e = []
f = []
benchMark(e, f)

for i in range(TEST_RUNS):
    length = 50000000
    g = [0] * length
    h = [0] * length
    for i in range(length):
        g[i] = (i + 31) * i % 37 + 1 # Kind of random test values (more like hashed values)
        h[i] = ((i + 1) * i / 2) % 37

    benchMark(g, h)
