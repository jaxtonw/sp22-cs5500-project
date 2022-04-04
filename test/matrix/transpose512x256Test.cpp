#include "../../src/matrix/transpose.h"
#include "../../src/common/helpers.h"
#include <mpi.h>

#define MCW MPI_COMM_WORLD

#define ROWS 256
#define COLS 512
#define TOTAL ROWS*COLS

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, commSize = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Barrier(MPI_COMM_WORLD);

    double *A = new double[TOTAL];

    for (size_t i = 0; i < TOTAL; i++)
    {
        A[i] = i;
    }
    
    int m = COLS;
    int n = ROWS;

    double *result = transpose(A, m, n, MCW);

    if (rank == 0)
    {
        printMatrix2D(result, n, m);
    }

    MPI_Finalize();
}