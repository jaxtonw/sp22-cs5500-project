#include "../src/common/helpers.h"
#include "../src/matrix/matrixProd.h"
#include <mpi.h>
#include <chrono>
#include <random>
#include <algorithm>

#define MCW MPI_COMM_WORLD

#define MATRIX_A_M 1000
#define MATRIX_A_B_N 1000
#define MATRIX_B_P 1000
#define TEST_RUNS 10

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, commSize = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Barrier(MPI_COMM_WORLD);

    // First Matrix: MxN
    // Second Matrix: NxP
    // Result : MxP

    uint64_t matrixASize = MATRIX_A_M * MATRIX_A_B_N;
    uint64_t matrixBSize = MATRIX_A_B_N * MATRIX_B_P;

    double *A = new double[matrixASize];
    double *B = new double[matrixBSize];

    int m = MATRIX_A_M;
    int n = MATRIX_A_B_N;
    int p = MATRIX_B_P;

    std::chrono::milliseconds totalTime;
    std::default_random_engine rEng(MPI_Wtime());
    std::uniform_real_distribution<double> distTwoThruTen(2, 10);

    for (size_t testLoop = 0; testLoop < TEST_RUNS; testLoop++)
    {

        for (size_t i = 0; i < matrixASize; i++)
        {
            A[i] = distTwoThruTen(rEng);
        }

        for (size_t i = 0; i < matrixBSize; i++)
        {
            B[i] = distTwoThruTen(rEng);
        }

        std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

        double *result = matrixProduct(A, m, n, B, p, MCW);

        totalTime += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);

        delete result;

        if (rank == 0)
        {
            printMatrix2D(result, m, p);
        }
        /* code */
    }

    if (rank == 0)
    {
        std::cout << "Matrix A: " << MATRIX_A_M << " x " << MATRIX_A_B_N << ", "
                  << "matrix B: " << MATRIX_A_B_N << " x " << MATRIX_B_P << ", "
                  << "random multiply " << TEST_RUNS << " times, "
                  << "total time was: " << totalTime.count() << "ms" << std::endl;
    }

    MPI_Finalize();
}