#include "mpiHelpers.h"

/**
 * @brief Creates a custom datatype representing an index (uint64_t),
 *        and double value (double) and commits it to MPI.
 *
 * @return MPI_Datatype
 */
MPI_Datatype createIndexDoubleDatatype(){
    const int objs = 2;
    const int lengths[objs] = {1, 1};
    MPI_Datatype types[objs] = {MPI_UINT64_T, MPI_DOUBLE};
    MPI_Datatype indexDoubleDatatype;

    // The displacement is the size of the last variables
    // e.g., start @ 0, uint64_t is 8 bytes
    MPI_Aint displacements[objs] = {0, 8}; 

    // Generate the MPI Type struct with the following info:
    // - The number of objects
    // - An array containing the number of each primitive
    // - The displacements (byte size) of each primitive
    // - An array containing the MPI primitive types
    // - The pointer to the to-be-created type
    MPI_Type_create_struct(objs, lengths, displacements, types, &indexDoubleDatatype);

    // Commit the new type to MPI
    MPI_Type_commit(&indexDoubleDatatype);

    return indexDoubleDatatype;
}

/**
 * @brief Creates a custom datatype representing an index (uint64_t),
 *        slice length (uint64_t) and array of double values (*double)
 *        and commits it to MPI.
 *
 * @return MPI_Datatype
 */
MPI_Datatype createIndexDoubleSliceDatatype(int length)
{
    const int objs = 3;
    const int lengths[objs] = {1, 1, length};
    MPI_Datatype types[objs] = {MPI_UINT64_T, MPI_UINT64_T, MPI_DOUBLE};
    MPI_Datatype indexDoubleSliceDatatype;

    // The displacement is the size of the last variables
    // e.g., start @ 0, uint64_t is 8 bytes, uint64_t is 8 bytes + 8 prev bytes
    MPI_Aint displacements[objs] = {0, 8, 16};

    // Generate the MPI Type struct with the following info:
    // - The number of objects
    // - An array containing the number of each primitive
    // - The displacements (byte size) of each primitive
    // - An array containing the MPI primitive types
    // - The pointer to the to-be-created type
    MPI_Type_create_struct(objs, lengths, displacements, types, &indexDoubleSliceDatatype);

    // Commit the new type to MPI
    MPI_Type_commit(&indexDoubleSliceDatatype);

    return indexDoubleSliceDatatype;
}

#ifdef CUSTOM_DATATYPE_TEST
int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, commSize = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Barrier(MPI_COMM_WORLD);

    createIndexDoubleSliceDatatype(10);

    MPI_Finalize();
}
#endif
