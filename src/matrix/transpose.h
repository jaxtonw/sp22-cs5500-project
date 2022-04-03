/**
 * @file
 *
 * File containing transposing of a matrix.
 */

#ifndef VECTOR_PROD_H
#define VECTOR_PROD_H

#include "mpi.h"
#include "../common/constants.h"
#include "../common/helpers.h"
#include "../common/mpiHelpers.h"
#include <iostream>
#include <cmath>

/**
 * Transpose matrix.
 *
 * @param A The matrix
 * @param m The row count of the matrix
 * @param n The column count of the matrix
 * @param comm The current MPI_Comm
 * @return The pointer to the result
 */
double *transpose(double *A, int m, int n, MPI_Comm comm);

#endif