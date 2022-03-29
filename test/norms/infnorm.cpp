#include "../../src/common/helpers.h"
#include "../../src/norms/infnorm.h"
#include "mpi.h"

#define MCW MPI_COMM_WORLD

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, commSize = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double testVec[5];
    for (int i = 0; i < 5; i++)
    {
        testVec[i] = (double) i;
    }

    double result = infNorm(testVec, 5, MCW);
    if (!rank)
    {
        std::cout << "Test Vector ";

        printVector(testVec, 5);

        std::cout << "Inf norm result: infNorm(testVec) = " << result << std::endl;
    }

    MPI_Finalize();

    return 0;
}
