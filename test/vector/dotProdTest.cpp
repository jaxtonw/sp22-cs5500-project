#include "../../src/vector/dotProd.h"
#include "../../src/common/helpers.h"
#include <mpi.h>
#include <iostream>
#define MCW MPI_COMM_WORLD
using namespace std;

bool assert(double actual, double expected) {
    if (actual != expected) {
        cout << "FAIL: actual (" << actual << ") != expected (" << expected << ")" << endl;
        return false;
    } else {
        cout << "PASS: result is " << actual << endl;
        return true;
    }
}

void testDotProd(double *x, double *y, size_t length, double expected, int rank) {
    if (rank == 0) {
		cout << "Computing dot product of " << endl;
        printVectorHorizontal(x, length);
		cout << "and" << endl;
		printVectorHorizontal(y, length);
    }

    double result = dotProduct(x, y, length, MCW);

    if (rank == 0) {
        assert(result, expected);
    }
    MPI_Barrier(MCW);
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
    testDotProd(x, y, length, 30.0, rank);

    double a[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    double b[] = {1.0, 2.0, 3.0, 4.0, 5.0, 1.0, 2.0, 3.0, 4.0, 5.0, 1.0, 2.0, 3.0, 4.0, 5.0};
	length = 15;
    testDotProd(a, b, length, 45.0, rank);

    double c[] = {2.0, 2.0, 2.0, 2.0, 4.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0};
    double d[] = {1.0, 2.0, 3.0, 4.0, 5.0, 1.0, 2.0, 3.0, 4.0, 5.0, 1.0, 2.0, 3.0, 4.0, 5.0};
	length = 15;
    testDotProd(c, d, length,100.0, rank);

    double e[] = {};
    double f[] = {};
	length = 0;
    testDotProd(c, d, length, 0, rank);

    length = 100000;
    double g[length];
    double h[length];
    for (unsigned int i = 0; i < length; i++) {
        g[i] = (i + 31) * i % 37 + 1; // Kind of random test values (more like hashed values)
        h[i] = ((i + 1) * i / 2) % 37;
    }
    
    double start = MPI_Wtime();
	double result = dotProduct(g, h, length, MCW);
    if (!rank) {
        cout << "Computed dot product with " << length << " values in each vector in " << MPI_Wtime() - start << " seconds!" << endl;
    }

    MPI_Finalize();
}