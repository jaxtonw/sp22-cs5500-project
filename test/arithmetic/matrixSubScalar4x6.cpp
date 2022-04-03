#include "../../src/arithmetic/arithmetic.h"
#include "../../src/common/helpers.h"
#include <mpi.h>

#define MCW MPI_COMM_WORLD

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, commSize = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Barrier(MPI_COMM_WORLD);

    double A[] = {
        12.0, 8.0, 4.0, 12.0, 8.0, 4.0,
        3.0, 17.0, 14.0, 1.0, 3.0, 27.0,
        9.0, 8.0, 10.0, 17.0, 14.0, 1.0,
        7.0, 2.0, 11.0, 23.0, 38.0, 8.0};

    double x = 1;

    int m = 4;
    int n = 6;

    double *result = subScalarFromMatrix(A, x, m, n, MCW);

    MPI_Barrier(MCW);
    if (rank == 0)
    {
        printMatrix2D(result, m, n);
    }

    MPI_Finalize();
}