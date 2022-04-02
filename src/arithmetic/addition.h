#ifndef ADDITION_H
#define ADDITION_H

#include <mpi.h>
#include <iostream>
#include "../common/helpers.h"
#include "../common/constants.h"

double *addMatrices(double *A, double *B, int n, int m);
double *addVectors(double *a, double *b, int m);
double *addScarlarMatrix(double *A, double x, int n, int m);
double *addScarlarVector(double *a, double x, int m);

#endif