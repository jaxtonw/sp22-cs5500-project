#include "../../src/arithmetic/addition.h"
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

    double a[] = {
        12.0, 8.0, 4.0};

    double b[] = {
        5.0, 19.0, 3.0};

    int m = 3;

    double *result = addVectors(a, b, m, MCW);

    MPI_Barrier(MCW);
    if (rank == 0)
    {
        printVector(result, m);
    }

    MPI_Finalize();
}