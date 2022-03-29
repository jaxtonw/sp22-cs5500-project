#include "mpiHelpers.h"

#include <iostream>
/**
 * @brief Creates a custom MPI datatype with a UInt64, Uint64, and double.
 *        Source code from https://www.rookiehpc.com/mpi/docs/mpi_type_create_struct.php
 * 
 * @return MPI_Datatype 
 */
MPI_Datatype mpiDatatypeVectorCalcType()
{
    //https://www.rookiehpc.com/mpi/docs/mpi_type_create_struct.php

    const int numObjs = 2;
    MPI_Datatype vectorCalcType;
    int lengths[numObjs] = {1, 1};

    MPI_Aint displacements[numObjs];
    struct vectorCalcStruct dummyVectorCalcStruct;
    MPI_Aint base_address;
    MPI_Get_address(&dummyVectorCalcStruct, &base_address);
    MPI_Get_address(&dummyVectorCalcStruct.idx, &displacements[0]);
    MPI_Get_address(&dummyVectorCalcStruct.value, &displacements[1]);
    displacements[0] = MPI_Aint_diff(displacements[0], base_address);
    displacements[1] = MPI_Aint_diff(displacements[1], base_address);

    MPI_Datatype types[numObjs] = {MPI_UINT64_T, MPI_DOUBLE};

    // Generate the MPI Type struct with the following info:
    // - The number of objects
    // - An array containing the number of each primitive
    // - The displacements (byte size?) of each primitive
    // - An array containing the MPI primitive types
    // - The pointer to the to-be-created type
    MPI_Type_create_struct(numObjs, lengths, displacements, types, &vectorCalcType);

    // Register the type with mpi
    MPI_Type_commit(&vectorCalcType);

    return vectorCalcType;
}
