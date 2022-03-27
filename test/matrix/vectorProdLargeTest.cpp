#include "../../src/matrix/vectorProd.h"
#include "../../src/common/helpers.h"
#include <mpi.h>
#include <algorithm>
#include <chrono>
#include <iostream>

#define MCW MPI_COMM_WORLD

using namespace std::chrono;
using namespace std;

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, commSize = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);

    const size_t COLUMNS = 800;
    const size_t ROWS = COLUMNS;
    const size_t TOTAL = COLUMNS * ROWS;

    double B[TOTAL];
    double y[COLUMNS];

    for (size_t i = 0; i < TOTAL; i++)
    {
        B[i] = (double)i;
        if (i < COLUMNS)
        {
            y[i] = (double)i;
        }
    }

    random_shuffle(B, B + TOTAL);
    random_shuffle(y, y + COLUMNS);

    MPI_Barrier(MPI_COMM_WORLD);

    auto start = high_resolution_clock::now();

    auto result = vectorProduct(B, ROWS, COLUMNS, y, MCW);

    auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);

    if (rank == 0)
    {
        // cout << "Result is ";
        printVector(result, COLUMNS);
        //cout << duration.count() << endl;
    }

    MPI_Finalize();
}