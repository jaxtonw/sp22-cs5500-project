#include "pnorm.h"
#include "mpi.h"

double pNorm(double p, double *vec, size_t length, MPI_Comm comm) {
    double result = 0;
    
    int rank, commSize;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &commSize);

    int startIdx, endIdx;
    startIdx = (length / commSize) * rank;
    endIdx = (length / commSize) * (rank + 1);

    int remainder = length % commSize; 
    if (remainder != 0) {
        if (rank < remainder) {
            startIdx += rank;
            endIdx += rank + 1;
        }
        else if (length > commSize) {
            startIdx += remainder;
            endIdx += remainder;
        }
    }

    if (endIdx != 0) {
        for (int i = startIdx; i < endIdx; i++) {
            result += pow(abs(vec[i]), p);
        }
    }

    if (rank != 0) {
        MPI_Send(&result, 1, MPI_DOUBLE, 0, 0, comm);
    }
    else {
        double receivedVal = 0;
        for (int proc = 1; proc < commSize; proc++) {
            MPI_Recv(&receivedVal, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, comm, MPI_STATUS_IGNORE);
            result += receivedVal;
        }
    }
    MPI_Barrier(comm);

    return pow(result, 1/p);
}
