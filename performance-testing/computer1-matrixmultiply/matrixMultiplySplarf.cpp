#include "../src/common/helpers.h"
#include "../src/matrix/matrixProd.h"
#include <mpi.h>
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
    MPI_Init(&argc, &argv);
    int rank, commSize = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Barrier(MPI_COMM_WORLD);

    std::chrono::milliseconds totalTime(0);
    std::default_random_engine rEng(rank);
    std::uniform_real_distribution<double> distTwoThruTen(2, 10);

    const uint64_t matrixASize = MATRIX_A_M * MATRIX_A_B_N;
    const uint64_t matrixBSize = MATRIX_A_B_N * MATRIX_B_P;

    for (size_t testLoop = 0; testLoop < TEST_RUNS; testLoop++)
    {
        // First Matrix: MxN
        // Second Matrix: NxP
        // Result : MxP

        double *A = new double[matrixASize];
        double *B = new double[matrixBSize];

        int m = MATRIX_A_M;
        int n = MATRIX_A_B_N;
        int p = MATRIX_B_P;

        if (rank == 0)
        {
            for (size_t i = 0; i < matrixASize; i++)
            {
                A[i] = distTwoThruTen(rEng);
            }

            for (size_t i = 0; i < matrixBSize; i++)
            {
                B[i] = distTwoThruTen(rEng);
            }
        }

        MPI_Bcast(A, matrixASize, MPI_DOUBLE, 0, MCW);
        MPI_Bcast(B, matrixBSize, MPI_DOUBLE, 0, MCW);

        // if (rank == 0)
        // {
        //     std::cout << "loops initialized, starting product" << std::endl;
        // }

        std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

        double *result = matrixProduct(A, m, n, B, p, MCW);

        std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
        totalTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        if (rank == 0)
        {
            std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
        }

        // if (rank == 0)
        // {
        //     std::cout << "loop " << testLoop << " done, total processing time: " << totalTime.count() << "ms" << std::endl;
        //     // printMatrix2D(result, m, p);
        // }

        MPI_Barrier(MCW);

        delete A;
        delete B;
        delete result;
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