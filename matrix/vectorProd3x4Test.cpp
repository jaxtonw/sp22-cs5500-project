#include "./vectorProd.h"
#include "../common/helpers.h"
#include <mpi.h>

#define MCW MPI_COMM_WORLD

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    double A[] = {
        1.0, 2.0, 3.0, 4.0, 
        5.0, 6.0, 7.0, 8.0, 
        9.0, 10.0, 11.0, 12.0};

    int m = 3;
    int n = 4;
    double x[] = {
        1.0, 2.0, 3.0, 4.0};

    double *result = vectorProduct(A, m, n, x, MCW);

    printVector(result, n);

    MPI_Finalize();
}