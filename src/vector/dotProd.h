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

/**
 * Vector * Vector Dot product
 *
 * @param x Input Vector 1
 * @param y Input Vector 2
 * @param comm The current MPI_Comm
 * @return a double representing the result (a scalar)
 */
double dotProduct(double *x, double *y, size_t length, MPI_Comm comm);

#endif