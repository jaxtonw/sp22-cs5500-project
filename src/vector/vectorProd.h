/**
 * @file
 *
 * Interface for parallel dot product.
 *
 * This header file describes the public interface for our implementation of the dot product in parallel.
 * It uses a partition approach to evenly divide the work between any given number of processors.
 */
#ifndef DOT_PROD_H
#define DOT_PROD_H

#include "mpi.h"
#include "../common/constants.h"
#include "../common/helpers.h"
#include <iostream>
#include <cmath>
#define MCW MPI_COMM_WORLD

/**
 * Vector * Vector Dot product
 *
 * @param x Input Vector 1
 * @param y Input Vector 2
 * @param comm The current MPI_Comm
 * @return a double representing the result (a scalar)
 */
double dotProduct(double *x, double *y, size_t length, MPI_Comm comm);

/**
 * Elementwise product of two equally sized vectors.
 *
 * @param x Input Vector 1
 * @param y Input Vector 2
 * @param comm The current MPI_Comm
 * @return An array consisting of the elementwise products
 */
double *vectorElementwiseProduct(double *a, double *b, int m, MPI_Comm comm);

#endif