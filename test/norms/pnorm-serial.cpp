#include "../../src/common/helpers.h"
#include "../../src/norms/pnorm-serial.h"
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

        std::cout << "p norm result (p=1): pNorm(testVec, 1) = " << pNorm(testVec, 1) << std::endl;
        std::cout << "p norm result (p=2): pNorm(testVec, 2) = " << pNorm(testVec, 2) << std::endl;
        std::cout << "p norm result (p=3): pNorm(testVec, 3) = " << pNorm(testVec, 3) << std::endl;
        std::cout << "p norm result (p=4): pNorm(testVec, 4) = " << pNorm(testVec, 4) << std::endl;
        std::cout << "p norm result (p=5): pNorm(testVec, 5) = " << pNorm(testVec, 5) << std::endl;
    }

    MPI_Finalize();

    return 0;
}
