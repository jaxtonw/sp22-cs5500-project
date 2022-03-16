#include "./vectorProd.h"
#include <iostream>
#include <mpi.h>

#define MCW MPI_COMM_WORLD

void printVector(double vec[], int size) {
    std::cout << "[\n";
    for (int i = 0; i < size; i++) {
        std::cout << " " << vec[i] << std::endl;
    }
    std::cout << "]" << std::endl;
}

int main(int argc, char **argv)
{
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);

    int m = 4; // rows
    int n = 3; // columns
    double A[] = { // 3x4 matrix
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0,
        10.0, 11.0, 12.0
    };

    double x[] = { // 3x1
        1.0,
        2.0,
        3.0
    };

    // TODO: Make n,m dimension usage consistent in vectorProd
    double* result = vectorProduct(A, n, m, x, MCW);

    if (rank == 0) {
        printVector(result, m);
    }

    MPI_Finalize();
}