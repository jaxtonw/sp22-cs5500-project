#include "./vectorProd.h"

void checkSizeCSendNext(uint64_t *currentIdx, uint64_t sizeC, uint16_t rank, MPI_Comm comm)
{
    // don't overrun work if m < size
    if (*currentIdx < sizeC)
    {
        // std::cout << "sending row: " << curIdx << ", to rank: " << i << std::endl;
        MPI_Send(currentIdx, 1, MPI_UINT64_T, rank, 0, comm);
        *currentIdx += 1;
    }
}

double *matrixProductRowByRow(double *A, uint64_t m, uint64_t n, double *B, uint64_t p, MPI_Comm comm)
{
    int rank, commSize, sendBuf, flag = 0;
    const uint64_t sizeC = p * m;

    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &commSize);
    MPI_Datatype indexDoubleType = createIndexDoubleDatatype();

    double *C = NULL;
    indexDoubleStruct vecBuf;

    if (rank == 0)
    {
        MPI_Request request;
        MPI_Status status;
        uint64_t returnCounter = 0;
        uint64_t curIdx = 0;
        C = new double[sizeC];

        while (1)
        {
            MPI_Irecv(&vecBuf, 1, indexDoubleType, MPI_ANY_SOURCE, 0, comm, &request);

            // On initial send, start workers
            if (!curIdx)
            {
                for (size_t i = 1; i < commSize; i++)
                {
                    checkSizeCSendNext(&curIdx, sizeC, i, comm);
                }
            }

            // Kill process when calculated
            if (returnCounter >= sizeC)
            {
                // std::cout << "returnCounter: " << returnCounter << std::endl;
                // std::cout << "sending poison pill" << std::endl;
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
                    // std::cout << "returnCounter: " << returnCounter << std::endl;

                    uint64_t idx = vecBuf.idx;
                    uint16_t recRank = status.MPI_SOURCE;
                    double recValue = vecBuf.value;

                    C[idx] = recValue;

                    // std::cout << "value: " << recValue << ", from rank: " << recRank << ", idx: " << idx << std::endl;

                    checkSizeCSendNext(&curIdx, sizeC, recRank, comm);
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

#ifndef MAKE_TEST
            if (vecBuf.idx == 3)
            {
                std::cout << "rank: " << rank << ", idx: " << vecBuf.idx << std::endl;
            }
#endif

            // First Matrix: MxN
            // Second Matrix: NxP
            // Result : MxP
            for (size_t i = 0; i < n; i++)
            {
                // The first values of A are on the first row (e.g., idx/p == 0), indexed by i % n.
                // Use the columns of B (i * b) and incrememt by the idx % p.
                vecBuf.value += A[(vecBuf.idx / p) * n + i % n] * B[i * p + vecBuf.idx % p];
            }

            MPI_Send(&vecBuf, 1, indexDoubleType, 0, 0, comm);
        }
    }

    // std::cout << "rank: " << rank << " exiting" << std::endl;

    return C;
}


double *matrixProduct(double *A, uint64_t m, uint64_t n, double *B, uint64_t p, MPI_Comm comm)
{
    // The fastest in benchmark so far
    return matrixProductRowByRow(A, m, n, B, p, comm);
}
