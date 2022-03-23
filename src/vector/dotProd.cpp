#include "./dotProd.h"
#include "../common/constants.h"
#include <iostream>
#include <cmath>
#define MCW MPI_COMM_WORLD

using namespace std;

/**
 * @brief helper function - computes the dot product within a certain range
 *
 * @param x Input Vector 1
 * @param y Input Vector 2
 * @param range sub-range (inclusive) of original vectors to compute dot product for - [start, end]
 * @return The shared_ptr pointer to the result
 */
double partialDotProduct(double *x, double *y, int *range) {
    int sum = 0;
    for (unsigned int i = range[0]; i <= range[1]; i++) {
        sum += x[i] * y[i];
    }
    return sum;
}

/**
 * @brief Vector * Vector Dot product
 *
 * @param x Input Vector 1
 * @param y Input Vector 2
 * @param comm The current MPI_Comm
 * @return The shared_ptr pointer to the result
 */
double dotProduct(double *x, double *y, size_t length, MPI_Comm comm)
{
    int rank, commSize;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &commSize);
    double result = 0;
    int subRange[2];

    if (length < 1) {
        return 0;
    }

	if (rank == 0) {
        // partition the indices for each processor as evenly as possible, leave the first partition for p0 to do itself
		size_t partitionSize = length / commSize;
        size_t remainder = length % commSize;
        unsigned int partitionStart = 0;
        unsigned int partitionEnd;
        int partition[2]; // Array of 2 elements which represents a range for a single processor to compute

        for (unsigned int i = 0; i < commSize; i++) {
            partition[0] = partitionStart;
            partitionEnd = partitionStart + partitionSize - 1; // Offset by 1 because here we are working with indices
            if (remainder > 0) {
                partitionEnd += 1;
                remainder--;
            }
            partition[1] = partitionEnd;
            // cout << i << ": partition start: "<< partitionStart << ", partition end: " << partitionEnd << endl;
            if (i == 0) {
                subRange[0] = partitionStart;
                subRange[1] = partitionEnd;
            } else {
                MPI_Send(partition,2,MPI_INT,i,0,MCW);
            }
            partitionStart = partitionEnd + 1;
        }
	} else {
        MPI_Recv(subRange,2,MPI_INT,MPI_ANY_SOURCE,0,MCW,MPI_STATUS_IGNORE);
    }

    double subRangeSum = partialDotProduct(x, y, subRange);
    // cout << rank << ": subrange sum is " << subRangeSum << endl;
    MPI_Allreduce(&subRangeSum,&result,1,MPI_DOUBLE,MPI_SUM,MCW);

    return result;
}
