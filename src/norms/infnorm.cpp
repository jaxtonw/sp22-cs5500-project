#include "infnorm-serial.h"
#include "mpi.h"

double infNorm(double *vec, size_t length, MPI_Comm comm) {
    double result = 0;
    
    int rank, commSize;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &commSize);

    int startIdx, endIdx;
    startIdx = (length / commSize) * rank;
    endIdx = (length / commSize) * (rank + 1);

    if (endIdx != 0) {
        for (int i = startIdx; i < endIdx; i++) {
            if (abs(vec[i]) > result) {
                result = abs(vec[i]);
            }
        }
    }

    if (!rank) {
        double receivedVal = 0;
        for (int proc = 1; proc < commSize; proc++) {
            MPI_Recv(&receivedVal, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, comm, MPI_STATUS_IGNORE);
            if (abs(receivedVal) > result)
                result = abs(receivedVal);
        }
    }
    else {
        MPI_Send(&result, 1, MPI_DOUBLE, 0, 0, comm);
    }

    return result;
}
