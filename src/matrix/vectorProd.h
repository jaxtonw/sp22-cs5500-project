#ifndef VECTOR_PROD_H
#define VECTOR_PROD_H

#include "mpi.h"
#include "../common/constants.h"
#include "../common/mpiHelpers.h"
#include <iostream>
#include <cmath>

using namespace std;

double *vectorProduct(double *A, size_t m, size_t n, double *x, MPI_Comm comm);
double *vectorProductRowByRow(double *A, uint64_t m, uint64_t n, double *x, MPI_Comm comm);

#endif