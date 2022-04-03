#include "./addition.h"

/**
 * @brief Sum two matrices together. Return summed matrix on Rank 0.
 *
 * @param A Matrix A
 * @param B Matrix B
 * @param m The row count of the matrices
 * @param n The column count of the matrices
 * @param comm The current MPI_Comm
 * @return The pointer to the result
 */
double *matricesSumPreDetermined(double *A, double *B, int m, int n, MPI_Comm comm)
{
    int rank, commSize = 0;

    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &commSize);

    double *C = NULL;
    // The first byte will contain the current index
    double buf[n + 1];
    // Converts doubles to uint64
    dblUnion dblU;

    if (rank == 0)
    {
        MPI_Request request;
        MPI_Status status;

        C = new double[m * n];

        for (size_t i = 0; i < m; i++)
        {
            MPI_Recv(buf, n + 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, comm, MPI_STATUS_IGNORE);

            // Convert the first double as uint64 for index
            dblU.dbl = buf[n];
            uint64_t index = dblU.uint64;

            for (size_t c = 0; c < n; c++)
            {
                C[index * n + c] = buf[c];
            }
        }
    }
    else
    {
        // Calculate values to calculate
        // 1. Divide m by PE count - 1
        // 2. Start is (rank - 1) * #1
        // 3. End is rank * #1
        // 3.1 If last rank, end is m
        int startIdx = (rank - 1) * (m / (commSize - 1));
        int endIdx = rank * (m / (commSize - 1));

        if (rank == commSize - 1)
        {
            endIdx = m;
        }


        for (size_t curRow = startIdx; curRow < endIdx; curRow++)
        {

            // Bytewise convert row to double, save it in 0th spot
            dblU.uint64 = curRow;
            buf[n] = dblU.dbl;

            // Add row of A & B
            for (size_t c = 0; c < n; c++)
            {
                // Offset the buff by 1 for index
                buf[c] = A[curRow * n + c] + B[curRow * n + c];
            }

            MPI_Send(buf, n + 1, MPI_DOUBLE, 0, 0, comm);
        }
    }

    // cout << "rank: " << rank << " exiting" << endl;

    return C;
}

double *addMatrices(double *A, double *B, int m, int n, MPI_Comm comm)
{
    return matricesSumPreDetermined(A, B, m, n, comm);
}