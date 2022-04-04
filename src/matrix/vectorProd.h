/**
 * @file
 * 
 * Interface for parallel matrix vector product.
 */
#ifndef VECTOR_PROD_H
#define VECTOR_PROD_H

#include "mpi.h"
#include "../common/constants.h"
#include "../common/mpiHelpers.h"
#include <iostream>
#include <cmath>

/**
 * 2D Matrix product with vector
 *
 * @param A The matrix
 * @param m The row count of the matrix
 * @param n The column count of the matrix
 * @param x The product vector
 * @param comm The current MPI_Comm
 * @return The pointer to the result
 */
double *vectorProduct(double *A, size_t m, size_t n, double *x, MPI_Comm comm);

/**
 * 2D Matrix product with vector. Rank 0 delivers work and receives calculations
 * asynchronously
 *
 * @param A The matrix
 * @param m The row count of the matrix
 * @param n The column count of the matrix
 * @param x The product vector
 * @param comm The current MPI_Comm
 * @return The pointer to the result
 */
double *vectorProductRowByRow(double *A, uint64_t m, uint64_t n, double *x, MPI_Comm comm);

#endif