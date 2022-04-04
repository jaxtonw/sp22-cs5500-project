#ifndef INFNORM_H
#define INFNORM_H

#include <vector>
#include <math.h>
#include "mpi.h"

double oneNorm(double *vec, size_t size, MPI_Comm comm);

#endif