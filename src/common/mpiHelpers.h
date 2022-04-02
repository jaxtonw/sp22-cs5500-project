#ifndef MPI_HELPERS_H
#define MPI_HELPERS_H

#include "mpi.h"
#include <iostream>

struct indexDoubleStruct
{
    uint64_t idx;
    double value;
};

struct indexLenSliceStruct
{
    uint64_t idx;
    uint64_t len;
    double* value;
};

MPI_Datatype createIndexDoubleDatatype();
MPI_Datatype createIndexDoubleSliceDatatype(int length);

#endif