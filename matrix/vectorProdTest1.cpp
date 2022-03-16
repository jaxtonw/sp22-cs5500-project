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
    double A[] = { // 4x3 matrix
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0,
        10.0, 11.0, 12.0
    };

    double x[] = { // 3x1
        1.0,
        2.0,
        3.0
        // 0.0, kind of, because things are called incorrectly
    };

    double* result = vectorProduct(A, n, m, x, MCW);
    // With this call where rows = n = 3, columns = m = 4, things get... weird
    // it kind of treats x as having 4 columns, where x[3] == 0
    
    if (rank == 0) {
        printVector(result, n);
    }

    MPI_Finalize();
}