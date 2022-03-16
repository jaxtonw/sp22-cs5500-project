#include "./vectorProd.h"
#include <mpi.h>
#include <algorithm>
#include <chrono>
#include <iostream>

#define MCW MPI_COMM_WORLD
#define COLUMNS 512
#define ROWS COLUMNS

using namespace std::chrono;
using namespace std;

void printVector(double* vec, int size) {
    cout << "[\n";
    for (int i = 0; i < size; i++) {
        cout << " " << vec[i] << endl;
    }
    cout << "]" << endl;
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, commSize = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Barrier(MPI_COMM_WORLD);

    double B[ROWS * COLUMNS];
    double y[COLUMNS];

    for (size_t i = 0; i < ROWS * COLUMNS; i++)
    {
        B[i] = (double)i;
        if (i < COLUMNS)
        {
            y[i] = (double)i;
        }
    }

    random_shuffle(B, B + ROWS * COLUMNS);
    random_shuffle(y, y + COLUMNS);

    auto start = high_resolution_clock::now();

    auto result = vectorProduct(B, ROWS, COLUMNS, y, MCW);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);



    if (rank == 0)
    {
        // cout << "Result is ";
        // printVector(result, COLUMNS);
        cout << "time (microseconds): " << duration.count() << endl;
    }

    MPI_Finalize();
}