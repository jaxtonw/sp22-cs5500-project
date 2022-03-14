#include "./vectorProd.h"

double *vectorProduct(double *A, int n, int m, double *x, double *y, MPI_Comm comm)
{
    int rank, commSize, data, flag;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &commSize);

    if (rank == 0)
    {
        MPI_Request request;
        MPI_Status status;
        int returnCounter = 0;
        int curIdx = 0;
        while (1)
        {
            MPI_Irecv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 0, comm, &request);

            if (!returnCounter)
            {
                // TODO: do logic for if n < size
                for (size_t i = 1; i < commSize; i++)
                {

                    MPI_Send(&curIdx, 1, MPI_INT, i, 0, comm);
                    curIdx++;
                }
            }

            while (1)
            {
                MPI_Test(&request, &flag, &status);

                if (flag)
                {
                    // TODO: load
                };

                // Perform 1 calculation
            }
        }
    }
    else
    {
        MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 0, comm, MPI_STATUS_IGNORE);

        // TODO: check poison pill

        // TODO: Perform calc
    }

    MPI_Finalize();
    return 0;
}
