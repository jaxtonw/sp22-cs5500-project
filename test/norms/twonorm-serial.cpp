#include "../../src/common/helpers.h"
#include "../../src/norms/twonorm-serial.h"
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
            testVec.push_back(1.0);
        }

        std::cout << "Test Vector ";

        printVector(testVec);

        std::cout << "Two norm result: twoNorm(testVec) = " << twoNormSerial(testVec) << std::endl;
    }

    MPI_Finalize();

    return 0;
}
