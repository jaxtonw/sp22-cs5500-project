#include <mpi.h>
#include <iostream>
#include "../src/vector/vectorProd.h"
#define MCW MPI_COMM_WORLD
using namespace std;

// single thread - run with 1 processor
// multi-thread run with any number (probably 8) processors
// run the .py file to compare the same vector dot products to numpy

double benchMark(double *x, double *y, size_t length, int rank) {
  if (rank == 0) {
    cout << "Computing dot product between vectors of size " << length << endl;
  }

  double start = MPI_Wtime();
  double result = dotProduct(x, y, length, MCW);
  double totalTime = MPI_Wtime() - start;

  if (rank == 0) {
    cout << "Done in " << totalTime << " seconds." << std::endl;
  }
  MPI_Barrier(MCW);
  return totalTime;
}

int main(int argc, char **argv)
{
    int rank, commSize;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &commSize);

    double x[] = {1.0, 2.0, 3.0, 4.0};
    double y[] = {1.0, 2.0, 3.0, 4.0};
	size_t length = 4;
    benchMark(x, y, length, rank);

    double a[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    double b[] = {1.0, 2.0, 3.0, 4.0, 5.0, 1.0, 2.0, 3.0, 4.0, 5.0, 1.0, 2.0, 3.0, 4.0, 5.0};
	length = 15;
    benchMark(a, b, length, rank);

    double e[] = {};
    double f[] = {};
	length = 0;
    benchMark(e, f, length, rank);

    length = 100000;
    double g[length];
    double h[length];
    for (unsigned int i = 0; i < length; i++) {
        g[i] = (i + 31) * i % 37 + 1; // Kind of random test values (more like hashed values)
        h[i] = ((i + 1) * i / 2) % 37;
    }
    
	benchMark(g, h, length, rank);

    // leads to seg fault
    // length = 1000000;
    // double c[length];
    // double d[length];
    // for (unsigned int i = 0; i < length; i++) {
    //     c[i] = (i + 31) * i % 37 + 1; // Kind of random test values (more like hashed values)
    //     d[i] = ((i + 1) * i / 2) % 37;
    // }
    
	// benchMark(c, d, length, rank);

    MPI_Finalize();
}
