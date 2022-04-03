#include "../../src/arithmetic/arithmetic.h"
#include "../../src/common/helpers.h"
#include <mpi.h>

#define MCW MPI_COMM_WORLD

#define LENGTH 10

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, commSize = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Barrier(MPI_COMM_WORLD);

    double *a = new double[LENGTH];
    double *b = new double[LENGTH];

    int m = LENGTH;

    for (size_t i = 0; i < LENGTH; i++)
    {
        a[i] = 2 * i;
        b[i] = i;
    }

    double *result = addVectors(a, b, m, MCW);

    if (rank == 0)
    {
        printVector(result, m);
    }

    MPI_Finalize();
}