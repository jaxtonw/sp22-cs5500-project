#include "./vectorProd.h"
#include "../common/constants.h"


double *vectorProduct(double *A, int32_t n, int32_t m, double *x, double *y, MPI_Comm comm)
{
    int rank, commSize, recBuf, sendBuf, flag;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &commSize);

    if (rank == 0)
    {
        MPI_Request request;
        MPI_Status status;
        int32_t returnCounter = 0;
        int32_t curIdx = 0;

        while (1)
        {
            MPI_Irecv(&recBuf, 1, MPI_INT32_T, MPI_ANY_SOURCE, 0, comm, &request);

            if (!returnCounter)
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

            if (returnCounter >= m)
            {
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

                if (flag && curIdx < m)
                {
                    MPI_Send(&curIdx, 1, MPI_INT32_T, recBuf, 0, comm);
                };

                // TODO: Perform calc
            }
        }
    }
    else
    {
        while (1)
        {

            MPI_Recv(&recBuf, 1, MPI_INT32_T, MPI_ANY_SOURCE, 0, comm, MPI_STATUS_IGNORE);

            if (recBuf == POISON_PILL)
            {
                break;
            }

            // TODO: Perform calc
        }

        MPI_Finalize();
        return 0;
    }
