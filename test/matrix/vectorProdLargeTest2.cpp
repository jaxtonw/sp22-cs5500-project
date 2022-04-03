#include "../../src/matrix/vectorProd.h"
#include "../../src/common/helpers.h"
#include <mpi.h>
#include <algorithm>
#include <chrono>
#include <iostream>

#define MCW MPI_COMM_WORLD

int main(int argc, char **argv)
{

    const size_t COLUMNS = 2400;
    const size_t ROWS = COLUMNS;
    const size_t TOTAL = COLUMNS * ROWS;

    double *B = new double[TOTAL];
    double *y = new double[COLUMNS];

    for (size_t i = 0; i < TOTAL; i++)
    {
        B[i] = (double)i;
        if (i < COLUMNS)
        {
            y[i] = (double)i;
        }
    }

    // random_shuffle(B, B + TOTAL);
    // random_shuffle(y, y + COLUMNS);

    MPI_Init(&argc, &argv);
    int rank, commSize = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Barrier(MPI_COMM_WORLD);

    auto start = std::chrono::high_resolution_clock::now();

    auto result = vectorProductRowByRow(B, ROWS, COLUMNS, y, MCW);

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now() - start);

    if (rank == 0)
    {
#ifdef MAKE_TEST
        // std::cout << "Result is ";
        printVector(result, COLUMNS);
#else
        std::cout << duration.count() << std::endl;
#endif
    }

    MPI_Finalize();
}