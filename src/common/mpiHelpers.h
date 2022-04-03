/**
 * @file
 * 
 * Helper functions for creating custom MPI data types.
 *
 */
#ifndef MPI_HELPERS_H
#define MPI_HELPERS_H

#include "mpi.h"
#include <iostream>

struct indexDoubleStruct
{
    uint64_t idx;
    double value;
};

struct indexDoubleSliceStruct
{
    uint64_t idx;
    uint64_t len;
    double* value;
};

/**
 * Creates a custom datatype representing an index (uint64_t),
 * and double value (double) and commits it to MPI.
 *
 * @return MPI_Datatype
 */
MPI_Datatype createIndexDoubleDatatype();

/**
 * Creates a custom datatype representing an index (uint64_t),
 * slice length (uint64_t) and array of double values (*double)
 * and commits it to MPI.
 *
 * @param length 
 * @return MPI_Datatype
 */
MPI_Datatype createIndexDoubleSliceDatatype(int length);

#endif