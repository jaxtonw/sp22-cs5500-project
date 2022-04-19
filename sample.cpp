/**
 * @file sample.cpp
 * @brief This is a sample of what can be performed with our library.
 *        This file creates two small matrices and multiplies them.
 *        The library can handle much larger matrices, so experiment!
 * @date 2022-04-18
 *
 */

#include "src/matrix/matrixProd.h"
#include "src/common/helpers.h"
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

    // Create some small matrices that will print nicely
    // Large matrices (2000x2000) are also good!
    double A[] = {
        12.0, 8.0, 4.0, 3.0,
        3.0, 17.0, 14.0, 7.0,
        9.0, 8.0, 10.0, 6.0,
        4.0, 9.0, 5.0, 11.0,
        7.0, 3.0, 13.0, 4.0,
        3.0, 9.0, 5.0, 14.0};

    double B[] = {
        5.0, 19.0,
        6.0, 15.0,
        7.0, 8.0,
        3.0, 9.0};

    int m = 6;
    int n = 4;
    int p = 2;

    if (rank == 0)
    {
        std::cout << "Matrix A is: " << std::endl;
        printMatrix2D(A, m, n);

        std::cout << "Matrix B is: " << std::endl;
        printMatrix2D(B, n, p);
    }

    // Perform a multi-threaded matrix product with MPI
    double *result = matrixProduct(A, m, n, B, p, MCW);

    if (rank == 0)
    {
        std::cout << "Matrix product is: " << std::endl;
        printMatrix2D(result, m, p);
    }

    MPI_Finalize();
}