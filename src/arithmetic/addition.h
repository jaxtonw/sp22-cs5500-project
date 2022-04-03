/**
 * @file
 * 
 * Basic arithmetic functions for vectors and matrices, including addition,
 * subtraction, and scalar multiplication
 */

#ifndef ADDITION_H
#define ADDITION_H

#include <mpi.h>
#include <iostream>
#include <cstring>
#include "../common/helpers.h"
#include "../common/mpiHelpers.h"
#include "../common/constants.h"

/**
 * @brief Sum two matrices together. Return summed matrix on Rank 0.
 *
 * @param A Matrix A
 * @param B Matrix B
 * @param m The row count of the matrices
 * @param n The column count of the matrices
 * @param comm The current MPI_Comm
 * @return The pointer to the result
 */
double *addMatrices(double *A, double *B, int m, int n, MPI_Comm comm);

/**
 * @brief Sum two vectors together. Return summed vector on Rank 0.
 *
 * @param a Vector a
 * @param b Vector b
 * @param n The length of vector a and b
 * @param comm The current MPI_Comm
 * @return The pointer to the result
 */
double *addVectors(double *a, double *b, int m, MPI_Comm comm);


/**
 * @brief Sum a matrix with a scalar value.
 *
 * @param A Matrix A
 * @param x Scalar x
 * @param m The row count of the matrix
 * @param n The column count of the matrix
 * @param comm The current MPI_Comm
 * @return The pointer to the result
 */
double *addScalarToMatrix(double *A, double x, int n, int m, MPI_Comm comm);

/**
 * @brief Sum a vector with a scalar value.
 *
 * @param a Vector a
 * @param x Scalar x
 * @param m The length of the vector
 * @param comm The current MPI_Comm
 * @return The pointer to the result
 */
double *addScalarToVector(double *a, double x, int m, MPI_Comm comm);


/**
 * @brief Sub matrix B from matrix A. Return result matrix on Rank 0.
 *
 * @param A Matrix A
 * @param B Matrix B
 * @param m The row count of the matrices
 * @param n The column count of the matrices
 * @param comm The current MPI_Comm
 * @return The pointer to the result
 */
double *subMatrices(double *A, double *B, int m, int n, MPI_Comm comm);

/**
 * @brief Sub vector b from vector a. Return result vector on Rank 0.
 *
 * @param a Vector a
 * @param b Vector b
 * @param n The length of vector a and b
 * @param comm The current MPI_Comm
 * @return The pointer to the result
 */
double *subVectors(double *a, double *b, int m, MPI_Comm comm);

#endif