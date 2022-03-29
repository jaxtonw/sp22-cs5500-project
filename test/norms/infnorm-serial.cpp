#include "../../src/common/helpers.h"
#include "../../src/norms/infnorm-serial.h"
#include "mpi.h"

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, commSize = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (!rank)
    {
        std::vector<double> testVec;
        for (int i = 0; i < 5; i++)
        {
            testVec.push_back((double)i);
        }

        std::cout << "Test Vector ";

        printVector(testVec);

        std::cout << "Inf norm result: infNorm(testVec) = " << infNorm(testVec) << std::endl;
    }

    MPI_Finalize();

    return 0;
}
