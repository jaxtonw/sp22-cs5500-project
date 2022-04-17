import numpy as np
import random
import time

SIZE = 2000

totalTime_ns = 0

for testLoops in range(10):
    A = np.array([[random.random() * 8 + 2 for _ in range(SIZE)] for _ in range(SIZE)])
    B = np.array([[random.random() * 8 + 2 for _ in range(SIZE)] for _ in range(SIZE)])
    start = time.perf_counter_ns()
    np.matmul(A, B)
    end = time.perf_counter_ns() 
    totalTime_ns += time.perf_counter_ns() - start
    # print(f"loop {testLoops} done, accumulated test time: {totalTime_ns / 1000000}ms")
    print(f"{(end - start) / 1000000}")



