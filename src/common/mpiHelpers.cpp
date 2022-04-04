#include "mpiHelpers.h"

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

void printStruct(indexDoubleStruct indexDouble)
{
    std::cout << "idx: " << indexDouble.idx << ", value: " << indexDouble.value << ", val";
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
