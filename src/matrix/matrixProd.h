/**
 * @file
 * 
 * Interface for parallel matrix multiplication.
 */
#ifndef MATRIX_PROD_H
#define MATRIX_PROD_H

#include "mpi.h"
#include "../common/constants.h"
#include "../common/mpiHelpers.h"
#include <iostream>

/**
 * 2D Matrix - 2D Matrix product. It is assumed that matrix A is m x n and
 * matrix B is n x p. Result is a m x p matrix stored in array form.
 *
 * @param A The left matrix
 * @param m The row count of the left matrix
 * @param n The column count of the left matrix
 * @param B The right matrix
 * @param p The column count of the right matrix
 * @param comm The current MPI_Comm
 * @return The pointer to the result
 */
double *matrixProduct(double *A, uint64_t m, uint64_t n, double *B, uint64_t p, MPI_Comm comm);

/**
 * 2D Matrix dot product with 2D Matrix.
 *
 * @param A The left matrix
 * @param m The row count of the left matrix
 * @param n The column count of the left matrix
 * @param B The right matrix
 * @param p The column count of the right matrix
 * @param comm The current MPI_Comm
 * @return The pointer to the result
 */
double *matrixProductRowByRow(double *A, uint64_t m, uint64_t n, double *B, uint64_t p, MPI_Comm comm);

#endif