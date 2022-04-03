#ifndef ADDITION_H
#define ADDITION_H

#include <mpi.h>
#include <iostream>
#include <cstring>
#include "../common/helpers.h"
#include "../common/mpiHelpers.h"
#include "../common/constants.h"

double *addMatrices(double *A, double *B, int m, int n, MPI_Comm comm);
double *addVectors(double *a, double *b, int m, MPI_Comm comm);
double *addScarlarMatrix(double *A, double x, int n, int m, MPI_Comm comm);
double *addScarlarVector(double *a, double x, int m, MPI_Comm comm);

#endif