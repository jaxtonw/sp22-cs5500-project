#ifndef MPI_HELPERS_H
#define MPI_HELPERS_H

#include "mpi.h"

struct vectorCalcStruct
{
    uint64_t idx;
    double value;
};


MPI_Datatype mpiDatatypeVectorCalcType();

#endif