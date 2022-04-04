#include "../../src/matrix/matrixProd.h"
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


    // First Matrix: MxN
    // Second Matrix: NxP
    // Result : MxP

    double A[] = {
        12.0, 8.0, 4.0,
        3.0, 17.0, 14.0,
        9.0, 8.0, 10.0,
        4.0, 9.0, 5.0};

    double B[] = {
        5.0, 19.0, 3.0, 6.0, 15.0, 9.0,
        6.0, 15.0, 9.0, 5.0, 19.0, 3.0, 
        7.0, 8.0, 16.0, 8.0, 2.0, 4.0};

    int m = 4;
    int n = 3;
    int p = 6;

    // if (rank == 0)
    // {
    //     printMatrix2D(A, m, n);
    // }

    double *result = matrixProduct(A, m, n, B, p, MCW);

    if (rank == 0)
    {
        printMatrix2D(result, m, p);
    }

    MPI_Finalize();
}