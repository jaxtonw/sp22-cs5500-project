#include "../../src/common/helpers.h"
#include "../../src/norms/twonorm.h"
#include "mpi.h"

#define MCW MPI_COMM_WORLD

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, commSize = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double testVecS5[5];
    double testVecS50[50];
    double testVecS500[500];

    for (int i = 0; i < 5; i++)
    {
        testVecS5[i] = (double) 1;
    }

    for (int i = 0; i < 50; i++)
    {
        testVecS50[i] = (double) 1;
    }

    for (int i = 0; i < 500; i++)
    {
        testVecS500[i] = (double) 1;
    }

    double result1 = twoNorm(testVecS5, 5, MCW);
    double result2 = twoNorm(testVecS50, 50, MCW);
    double result3 = twoNorm(testVecS500, 500, MCW);

    if (!rank)
    {
        std::cout << "Test Vector Of Size 5: ";

        printVector(testVecS5, 5);

        std::cout << "Two norm result: twoNorm(testVecS5) = " << result1 << std::endl;

        std::cout << "Test Vector Of Size 50 created, containing only 1s." << std::endl;

        std::cout << "Two norm result: twoNorm(testVecS50) = " << result2 << std::endl;

        std::cout << "Test Vector Of Size 500 created, containing only 1s." << std::endl;

        std::cout << "Two norm result: twoNorm(testVecS500) = " << result3 << std::endl;
    }

    MPI_Finalize();

    return 0;
}
