#ifndef MATRIX_PROD_H
#define MATRIX_PROD_H

#include "mpi.h"
#include "../common/constants.h"
#include "../common/mpiHelpers.h"
#include <iostream>

double *matrixProduct(double *A, uint64_t m, uint64_t n, double *B, uint64_t p, MPI_Comm comm);
double *matrixProductRowByRow(double *A, uint64_t m, uint64_t n, double *B, uint64_t p, MPI_Comm comm);

#endif