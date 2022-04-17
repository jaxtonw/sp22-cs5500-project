#include "../src/common/helpers.h"
#include <chrono>
#include <random>
#include <algorithm>

#define MCW MPI_COMM_WORLD

#define MATRIX_A_M 2000
#define MATRIX_A_B_N 2000
#define MATRIX_B_P 2000
#define TEST_RUNS 10

int main(int argc, char **argv)
{

    std::chrono::milliseconds totalTime(0);
    std::default_random_engine rEng(33);
    std::uniform_real_distribution<double> distTwoThruTen(2, 10);

    const uint64_t matrixASize = MATRIX_A_M * MATRIX_A_B_N;
    const uint64_t matrixBSize = MATRIX_A_B_N * MATRIX_B_P;
    const uint64_t matrixCSize = MATRIX_A_M * MATRIX_B_P;

    for (size_t testLoop = 0; testLoop < TEST_RUNS; testLoop++)
    {
        // First Matrix: MxN
        // Second Matrix: NxP
        // Result : MxP

        double *A = new double[matrixASize];
        double *B = new double[matrixBSize];
        double *C = new double[matrixCSize];

        int m = MATRIX_A_M;
        int n = MATRIX_A_B_N;
        int p = MATRIX_B_P;

        for (size_t i = 0; i < matrixASize; i++)
        {
            A[i] = distTwoThruTen(rEng);
        }

        for (size_t i = 0; i < matrixBSize; i++)
        {
            B[i] = distTwoThruTen(rEng);
        }

        // std::cout << "loops initialized, starting product" << std::endl;

        std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

        for (uint64_t idx = 0; idx < matrixCSize; idx++)
        {
            C[idx] = 0;
            for (uint64_t i = 0; i < n; i++)
            {
                // The first values of A are on the first row (e.g., idx/p == 0), indexed by i % n.
                // Use the columns of B (i * b) and incrememt by the idx % p.

                C[idx] += A[(idx / p) * n + i] * B[i * p + idx % p];
                // buf[idx] += A[(idx + startIndex) + i] * B[i * p + (idx + startIndex)];
            }
        }
        std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
        totalTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
        // std::cout << "loop " << testLoop << " done, total processing time: " << totalTime.count() << "ms" << std::endl;
        // printMatrix2D(result, m, p);

        delete A;
        delete B;
    }

    std::cout << "Matrix A: " << MATRIX_A_M << " x " << MATRIX_A_B_N << ", "
              << "matrix B: " << MATRIX_A_B_N << " x " << MATRIX_B_P << ", "
              << "random multiply " << TEST_RUNS << " times, "
              << "total time was: " << totalTime.count() << "ms" << std::endl;

}