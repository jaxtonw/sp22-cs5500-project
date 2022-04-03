#include "./transpose.h"

double *transposePreDetermined(double *A, int m, int n, MPI_Comm comm)
{
    int rank, commSize = 0;
    size_t total = m * n;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &commSize);

    // bufSize could be the total values / working processesors
    // but that misses the leftover (modulo) values and starting
    // index. By padding for the modulo values, we have to also
    // add a length value. The final total is:
    // (values / working processors) + modulo + length (1) + starting idx (1)
    int bufSize = (total / (commSize - 1)) + (total % (commSize - 1)) + 2;

    // The first byte will contain the current index
    double buf[bufSize];

    double *c = NULL;
    // Converts doubles to uint64
    dblUnion dblU;

    if (rank == 0)
    {
        MPI_Request request;
        MPI_Status status;

        c = new double[total];

        for (size_t i = 0; i < commSize - 1; i++)
        {
            MPI_Recv(buf, bufSize, MPI_DOUBLE, MPI_ANY_SOURCE, 0, comm, MPI_STATUS_IGNORE);

            // Convert the nth as uint64 for index
            dblU.dbl = buf[bufSize - 1];
            uint64_t index = dblU.uint64;

            // Convert the nth - 1 as uint64 for length
            dblU.dbl = buf[bufSize - 2];
            uint64_t length = dblU.uint64;

            for (size_t i = 0; i < length; i++)
            {
                c[i + index] = buf[i];
            }
        }
    }
    else
    {
        // Find slice length
        int length = (total / (commSize - 1));
        // The start of slice
        int startIdx = (rank - 1) * length;

        // If at the end, take care of the remainder
        if (rank == commSize - 1)
        {
            length += total % (commSize - 1);
        }

        // Bytewise convert row to double, save it in nth spot
        dblU.uint64 = startIdx;
        buf[bufSize - 1] = dblU.dbl;

        // Bytewise convert length to double, save it in n-1 spot
        dblU.uint64 = length;
        buf[bufSize - 2] = dblU.dbl;

        for (size_t i = 0; i < length; i++)
        {
            buf[i] = A[(((startIdx + i) % m) * n) + (startIdx + i) / m];
        }

        // for (size_t i = 1; i < commSize; i++)
        // {
        //     if (rank == i)
        //     {
        //         std::cout << "rank " << rank << " got: ";
        //         for (size_t j = 0; j < length; j++)
        //         {
        //             if(j)
        //             {
        //                 std::cout << ", ";
        //             }
        //             std::cout << buf[j];
        //         }
        //         std::cout << std::endl;
        //     }
        // }
        

        MPI_Send(buf, bufSize, MPI_DOUBLE, 0, 0, comm);
    }

    // cout << "rank: " << rank << " exiting" << endl;

    return c;
}

double *transpose(double *A, int m, int n, MPI_Comm comm)
{
    return transposePreDetermined(A, m, n, comm);
}