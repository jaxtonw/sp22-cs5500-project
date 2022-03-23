#ifndef DOT_PROD_H
#define DOT_PROD_H

#include "mpi.h"

double dotProduct(double *x, double *y, size_t length, MPI_Comm comm);

#endif