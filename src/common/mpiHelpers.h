#ifndef MPI_HELPERS_H
#define MPI_HELPERS_H

#include "mpi.h"
#include <iostream>

struct indexDoubleStruct
{
    uint64_t idx;
    double value;
};

void printStruct(indexDoubleStruct s);

MPI_Datatype createIndexDoubleDatatype();

#endif