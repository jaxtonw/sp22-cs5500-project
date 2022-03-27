#include "./vectorProd.h"

void checkSendNext(uint64_t *currentIdx, uint64_t m, uint16_t rank, MPI_Comm comm)
{
    // don't overrun work if m < size
    if (*currentIdx < m)
    {
        // cout << "sending row: " << curIdx << ", to rank: " << i << endl;
        MPI_Send(currentIdx, 1, MPI_UINT64_T, rank, 0, comm);
        *currentIdx += 1;
    }
}

/**
 * @brief 2D Matrix dot product with vector, fastest
 *
 * @param A The main matrix
 * @param m The row count of the matrix
 * @param n The column count of the matrix
 * @param x The product vector
 * @param y The result vector
 * @param comm The current MPI_Comm
 * @return The shared_ptr pointer to the result
 */
double *vectorProductRowByRow(double *A, uint64_t m, uint64_t n, double *x, MPI_Comm comm)
{
    int rank, commSize, sendBuf, flag = 0;

    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &commSize);
    MPI_Datatype vectorCalcType = mpiDatatypeVectorCalcType();

    double *y = NULL;
    vectorCalcStruct vecBuf;

    if (rank == 0)
    {
        MPI_Request request;
        MPI_Status status;
        uint64_t returnCounter = 0;
        uint64_t curIdx = 0;
        y = new double[m]{0};

        while (1)
        {
            MPI_Irecv(&vecBuf, 1, vectorCalcType, MPI_ANY_SOURCE, 0, comm, &request);

            // On initial send, start workers
            if (!curIdx)
            {
                for (size_t i = 1; i < commSize; i++)
                {
                    checkSendNext(&curIdx, m, i, comm);
                }
            }

            // Kill process when calculated
            if (returnCounter >= m)
            {
                // cout << "returnCounter: " << returnCounter << endl;
                // cout << "sending poison pill" << endl;
                sendBuf = POISON_PILL;
                for (size_t i = 1; i < commSize; i++)
                {
                    MPI_Send(&sendBuf, 1, MPI_UINT64_T, i, 0, comm);
                }
                break;
            }

            while (1)
            {
                MPI_Test(&request, &flag, &status);

                if (flag)
                {
                    returnCounter++;
                    // cout << "returnCounter: " << returnCounter << endl;

                    uint64_t idx = vecBuf.idx;
                    uint16_t recRank = status.MPI_SOURCE;
                    double recValue = vecBuf.value;

                    y[idx] = recValue;

                    // cout << "value: " << recValue << ", from rank: " << recRank << ", idx: " << idx << endl;

                    checkSendNext(&curIdx, m, recRank, comm);
                    break;
                };
            }
        }
    }
    else
    {
        int recBuf;

        while (1)
        {
            MPI_Recv(&recBuf, 1, MPI_UINT64_T, MPI_ANY_SOURCE, 0, comm, MPI_STATUS_IGNORE);

            if (recBuf == POISON_PILL)
            {
                break;
            }

            vecBuf.idx = recBuf;
            vecBuf.value = 0;

            for (size_t i = 0; i < n; i++)
            {
                vecBuf.value += x[i] * A[recBuf * n + i];
            }

            MPI_Send(&vecBuf, 1, vectorCalcType, 0, 0, comm);
        }
    }

    // cout << "rank: " << rank << " exiting" << endl;

    return y;
}

/**
 * @brief 2D Matrix dot product with vector
 *
 * @param A The main matrix
 * @param m The row count of the matrix
 * @param n The column count of the matrix
 * @param x The product vector
 * @param y The result vector
 * @param comm The current MPI_Comm
 * @return The shared_ptr pointer to the result
 */
double *vectorProductPreDetermined(double *A, uint64_t m, uint64_t n, double *x, MPI_Comm comm)
{
    int rank, commSize, sendBuf, flag = 0;

    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &commSize);
    MPI_Datatype vectorCalcType = mpiDatatypeVectorCalcType();

    double *y = NULL;
    vectorCalcStruct vecBuf;

    if (rank == 0)
    {
        MPI_Request request;
        MPI_Status status;
        uint64_t returnCounter = 0;
        uint64_t curIdx = 0;
        y = new double[m]{0};

        while (1)
        {
            MPI_Recv(&vecBuf, 1, vectorCalcType, MPI_ANY_SOURCE, 0, comm, MPI_STATUS_IGNORE);

            returnCounter++;
            y[vecBuf.idx] = vecBuf.value;

            // Kill process when calculated
            if (returnCounter >= m)
            {
                // cout << "returnCounter: " << returnCounter << endl;
                // cout << "sending poison pill" << endl;
                sendBuf = POISON_PILL;
                for (size_t i = 1; i < commSize; i++)
                {
                    MPI_Send(&sendBuf, 1, MPI_UINT64_T, i, 0, comm);
                }
                break;
            }
        }
    }
    else
    {
        int recBuf;
        // np 2, m = 1000
        // curIdx rank 1 = 0
        // nextIdx rank 1 = 1000

        // np 4, m = 1000
        // curIdx rank 2 = 333
        int startIdx = (rank - 1) * (m / (commSize - 1));
        int endIdx = rank * (m / (commSize - 1));

        if (rank == commSize - 1)
        {
            endIdx = m;
        }

        // #ifndef MAKE_TEST
        //         cout << "rank: " << rank << ", startIdx: " << startIdx << ", endIdx: " << endIdx << endl;
        // #endif

        for (size_t j = startIdx; j < endIdx; j++)
        {
            vecBuf.idx = j;
            vecBuf.value = 0;

            for (size_t i = 0; i < n; i++)
            {
                vecBuf.value += x[i] * A[j * n + i];
            }

            MPI_Send(&vecBuf, 1, vectorCalcType, 0, 0, comm);
        }

        while (1)
        {
            MPI_Recv(&recBuf, 1, MPI_UINT64_T, MPI_ANY_SOURCE, 0, comm, MPI_STATUS_IGNORE);

            if (recBuf == POISON_PILL)
            {
                break;
            }
        }
    }

    // cout << "rank: " << rank << " exiting" << endl;

    return y;
}

/**
 * @brief 2D Matrix dot product with vector
 *
 * @param A The main matrix
 * @param m The row count of the matrix
 * @param n The column count of the matrix
 * @param x The product vector
 * @param y The result vector
 * @param comm The current MPI_Comm
 * @return The shared_ptr pointer to the result
 */
double *vectorProduct(double *A, uint64_t m, uint64_t n, double *x, MPI_Comm comm)
{
    // The fastest in benchmark so far
    return vectorProductRowByRow(A, m, n, x, comm);
}
