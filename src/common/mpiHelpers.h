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

/**
 * @brief A struct holding holds a uint64 index and
 *        double value.
 */
struct indexDoubleStruct
{
    uint64_t idx;
    double value;
};

/**
 * @brief Prints an indexDoubleStruct to standard out.
 * 
 * @param s The indexDoubleStruct to print.
 */
void printStruct(indexDoubleStruct s);

/**
 * Creates a custom datatype representing an index (uint64_t),
 * and double value (double) and commits it to MPI.
 *
 * @return MPI_Datatype
 */
MPI_Datatype createIndexDoubleDatatype();

#endif