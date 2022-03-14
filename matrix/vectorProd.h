#ifndef VECTOR_PROD_H
#define VECTOR_PROD_H

#include "mpi.h"

double *vectorProduct(double *A, int32_t n, int32_t m, double *x, double *y, MPI_Comm comm);

#endif