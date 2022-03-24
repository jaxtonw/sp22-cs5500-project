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
    struct vectorCalcStruct dummy_person;
    MPI_Aint base_address;
    MPI_Get_address(&dummy_person, &base_address);
    MPI_Get_address(&dummy_person.idx, &displacements[0]);
    MPI_Get_address(&dummy_person.value, &displacements[1]);
    displacements[0] = MPI_Aint_diff(displacements[0], base_address);
    displacements[1] = MPI_Aint_diff(displacements[1], base_address);

    MPI_Datatype types[numObjs] = {MPI_UINT64_T, MPI_DOUBLE};
    MPI_Type_create_struct(numObjs, lengths, displacements, types, &vectorCalcType);
    MPI_Type_commit(&vectorCalcType);
    return vectorCalcType;
}
