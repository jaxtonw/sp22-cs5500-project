#include "./vectorProd.h"
#include "../common/helpers.h"
#include <iostream>
#include <mpi.h>

#define MCW MPI_COMM_WORLD

int main(int argc, char **argv)
{
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);

    int m = 4; // rows
    int n = 3; // columns
    double A[] = { // 4x3 matrix
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0,
        10.0, 11.0, 12.0
    };

    int m = 4;
    int n = 3;
    double x[] = {
        1.0, 2.0, 3.0};

    double *result = vectorProduct(A, m, n, x, MCW);

    printVector(result, n);

    MPI_Finalize();
}