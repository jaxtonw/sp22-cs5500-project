#include "./vectorProd.h"
#include "../common/constants.h"
#include <iostream>
#include <cmath>

using namespace std;

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
double *vectorProduct(double *A, size_t m, size_t n, double *x, MPI_Comm comm)
{
    int rank, commSize, sendBuf, flag = 0;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &commSize);
    double *y = NULL;
    double vecBuf[3] = {0,0,0};

    if (rank == 0)
    {
        MPI_Request request;
        MPI_Status status;
        size_t returnCounter = 0;
        size_t curIdx = 0;
        y = new double[m];

        while (1)
        {
            MPI_Irecv(&vecBuf, 3, MPI_DOUBLE, MPI_ANY_SOURCE, 0, comm, &request);

            // On initial send, start workers
            if (!curIdx)
            {
                for (size_t i = 1; i < commSize; i++)
                {
                    if (curIdx < m)
                    {
                        MPI_Send(&curIdx, 1, MPI_INT32_T, i, 0, comm);
                        curIdx++;
                    }
                }
            }

            // Kill process when calculated
            if (returnCounter >= m)
            {
                //cout << "sending poison pill" << endl;
                sendBuf = POISON_PILL;
                for (size_t i = 1; i < commSize; i++)
                {
                    MPI_Send(&sendBuf, 1, MPI_INT32_T, i, 0, comm);
                }
                break;
            }

            while (1)
            {
                MPI_Test(&request, &flag, &status);

                if (flag)
                {
                    returnCounter++;
                    //cout << "returnCounter: " << returnCounter << endl;

                    int idx = round(vecBuf[0]);
                    int recRank = round(vecBuf[1]);
                    double recValue = vecBuf[2];

                    y[idx] = recValue;
                
                    //cout << "value: " << recValue << ", from rank: " << recRank << ", idx: " << idx << endl;

                    if (curIdx < m)
                    {
                        MPI_Send(&curIdx, 1, MPI_INT32_T, recRank, 0, comm);
                        curIdx++;
                    }
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
            MPI_Recv(&recBuf, 1, MPI_INT32_T, MPI_ANY_SOURCE, 0, comm, MPI_STATUS_IGNORE);

            if (recBuf == POISON_PILL)
            {
                break;
            }

            vecBuf[0] = recBuf;
            vecBuf[1] = rank;
            vecBuf[2] = 0;
            for (size_t i = 0; i < m; i++) // should be column count (n) instead of row count (m), I think?
            {
                vecBuf[2] += x[i] * A[recBuf * m + i];
            }

            MPI_Send(&vecBuf, 3, MPI_DOUBLE, 0, 0, comm);
        }
    }

    // if (rank == 0)
    // {
    //     cout << "Result: " << endl;

    //     for (size_t i = 0; i < m; i++)
    //     {
    //         cout << y[i] << endl;
    //     }
    // }

    //cout << "rank: " << rank << " exiting" << endl;

    return y;
}
