#include "../../src/arithmetic/addition.h"
#include "../../src/common/helpers.h"
#include <mpi.h>

#define MCW MPI_COMM_WORLD

#define BIG_VALUE 1024

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, commSize = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Barrier(MPI_COMM_WORLD);

    double *a = new double[BIG_VALUE];
    double *b = new double[BIG_VALUE];

    int m = BIG_VALUE;

    for (size_t i = 0; i < BIG_VALUE; i++)
    {
        a[i] = i;
        b[i] = i;
    }

    double *result = addVectors(a, b, m, MCW);

    if (rank == 0)
    {
        printVector(result, m);
    }

    MPI_Finalize();
}