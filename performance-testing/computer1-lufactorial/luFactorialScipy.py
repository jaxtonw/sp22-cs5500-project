import random
import scipy
import scipy.linalg   # SciPy Linear Algebra Library
import numpy
import time


def lowerTriangularGenerator(size : int, maxMagnitude : float = 1.0):

    matrixA : list[list[float]] = [None] * size

    for i in range(size):
        matrixA[i] = [0] * size
        for j in range(i+1):
            matrixA[i][j] = random.uniform(-1 * maxMagnitude, maxMagnitude)
        if matrixA[i][i] == 0: matrixA[i][j] = maxMagnitude

    return matrixA


def unitLowerTriangularGenerator(size : int, maxMagnitude : float = 1.0):

    matrixA : list[list[float]] = [None] * size

    for i in range(size):
        matrixA[i] = [0] * size
        matrixA[i][i] = 1
        for j in range(i):
            matrixA[i][j] = random.uniform(-1 * maxMagnitude, maxMagnitude)

    return matrixA


def upperTriangularGenerator(size : int, maxMagnitude : float = 1.0):

    matrixA : list[list[float]] = [None] * size

    for i in range(size):
        matrixA[i] = [0] * size
        for j in range(i, size):
            matrixA[i][j] = random.uniform(-1 * maxMagnitude, maxMagnitude)
        if matrixA[i][i] == 0: matrixA[i][j] = maxMagnitude

    return matrixA


def matrixMultiply(matrixA : list[list[float]], matrixB : list[list[float]]):

    M = len(matrixA)
    N = len(matrixB)
    K = len(matrixB[0])
    matrixResult : list[list[float]] = [None] * M

    for row in range(M):
        matrixResult[row] = [0] * K
        for col in range(K):
            result = 0
            for n in range(N):
                result += matrixA[row][n] * matrixB[n][col]
            matrixResult[row][col] = result

    return matrixResult


if __name__ == "__main__":
    totalTime_ns = 0
    TEST_RUNS = 10
    SIZE = 2000

    L = lowerTriangularGenerator(SIZE)
    U = upperTriangularGenerator(SIZE)
    A = numpy.matmul(L, U)

    print(f"starting lu factorization for {SIZE}x{SIZE} matrix")

    for i in range(TEST_RUNS):

        start = time.perf_counter_ns()
        P, L, U = scipy.linalg.lu(A)
        end = time.perf_counter_ns() 

        totalTime_ns += time.perf_counter_ns() - start

        print(f"{(end - start) / 1000000}")

