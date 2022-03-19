#ifndef VECTOR_PROD_H
#define VECTOR_PROD_H

#include "mpi.h"

double* vectorProduct(double *A, size_t m, size_t n, double *x, MPI_Comm comm);

#endif