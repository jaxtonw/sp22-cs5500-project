#include "./matrixProd.h"

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

double *matrixProductPreDetermined(double *A, uint64_t m, uint64_t n, double *B, uint64_t p, MPI_Comm comm)
{
    int rank, commSize;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &commSize);

    // Work + overflow
    const uint64_t sizeC = p * m;
    const uint64_t workSize = (sizeC / commSize);
    const uint64_t workRemainder = (sizeC % commSize);
    const uint64_t bufferSize = workSize + (sizeC % commSize);
    const uint64_t startIndex = workSize * rank;
    double *buf = new double[bufferSize];
    double *C = new double[sizeC];
    double calcValue;

    int displacements[commSize];
    displacements[0] = 0;
    for (size_t i = 1; i < commSize; i++)
    {
        displacements[i] = displacements[i - 1] + workSize;
    }

    // std::cout << "displacements rank " << rank << ": {";
    // for (size_t i = 0; i < commSize; i++)
    // {
    //     std::cout << displacements[i];
    //     if (i < commSize - 1)
    //     {
    //         std::cout << ", ";
    //     }
    //     else
    //     {
    //         std::cout << "}" << std::endl;
    //     }
    // }

    int lengths[commSize];
    for (size_t i = 0; i < commSize; i++)
    {
        lengths[i] = workSize;
    }
    lengths[commSize - 1] += workRemainder;

    // std::cout << "lengths rank " << rank << ": {";
    // for (size_t i = 0; i < commSize; i++)
    // {
    //     std::cout << lengths[i];
    //     if (i < commSize - 1)
    //     {
    //         std::cout << ", ";
    //     }
    //     else
    //     {
    //         std::cout << "}" << std::endl;
    //     }
    // }

    uint64_t newStartIdx;
    for (uint64_t idx = 0; idx < lengths[rank]; idx++)
    {
        buf[idx] = 0;
        newStartIdx = (idx + startIndex);
        for (uint64_t i = 0; i < n; i++)
        {
            // The first values of A are on the first row (e.g., idx/p == 0), indexed by i % n.
            // Use the columns of B (i * b) and incrememt by the idx % p.

            buf[idx] += A[(newStartIdx / p) * n + i] * B[i * p + newStartIdx % p];
            // buf[idx] += A[(idx + startIndex) + i] * B[i * p + (idx + startIndex)];
        }
    }

    MPI_Allgatherv(buf, lengths[rank], MPI_DOUBLE, C, lengths, displacements, MPI_DOUBLE, comm);

    return C;
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
    // return matrixProductRowByRow(A, m, n, B, p, comm);

    return matrixProductPreDetermined(A, m, n, B, p, comm);
}
