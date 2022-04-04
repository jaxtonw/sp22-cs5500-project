#include "../../src/common/helpers.h"
#include "../../src/norms/pnorm.h"
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


    double result1p1 = pNorm(1, testVecS5, 5, MCW);
    double result1p2 = pNorm(2, testVecS5, 5, MCW);
    double result1p3 = pNorm(3, testVecS5, 5, MCW);
    double result1p4 = pNorm(4, testVecS5, 5, MCW);
    double result1p5 = pNorm(5, testVecS5, 5, MCW);

    double result2p1 = pNorm(1, testVecS50, 50, MCW);
    double result2p2 = pNorm(2, testVecS50, 50, MCW);
    double result2p3 = pNorm(3, testVecS50, 50, MCW);
    double result2p4 = pNorm(4, testVecS50, 50, MCW);
    double result2p5 = pNorm(5, testVecS50, 50, MCW);
    
    double result3p1 = pNorm(1, testVecS500, 500, MCW);
    double result3p2 = pNorm(2, testVecS500, 500, MCW);
    double result3p3 = pNorm(3, testVecS500, 500, MCW);
    double result3p4 = pNorm(4, testVecS500, 500, MCW);
    double result3p5 = pNorm(5, testVecS500, 500, MCW);

    if (!rank)
    {
        std::cout << "Test Vector Of Size 5: ";

        printVector(testVecS5, 5);

        std::cout << "P norm result (p=1): pNorm(1, testVecS5)   = " << result1p1 << std::endl;
        std::cout << "P norm result (p=2): pNorm(2, testVecS5)   = " << result1p2 << std::endl;
        std::cout << "P norm result (p=3): pNorm(3, testVecS5)   = " << result1p3 << std::endl;
        std::cout << "P norm result (p=4): pNorm(4, testVecS5)   = " << result1p4 << std::endl;
        std::cout << "P norm result (p=5): pNorm(5, testVecS5)   = " << result1p5 << std::endl;

        std::cout << "Test Vector Of Size 50 created, containing only 1s." << std::endl;

        std::cout << "P norm result (p=1): pNorm(1, testVecS50)  = " << result2p1 << std::endl;
        std::cout << "P norm result (p=2): pNorm(2, testVecS50)  = " << result2p2 << std::endl;
        std::cout << "P norm result (p=3): pNorm(3, testVecS50)  = " << result2p3 << std::endl;
        std::cout << "P norm result (p=4): pNorm(4, testVecS50)  = " << result2p4 << std::endl;
        std::cout << "P norm result (p=5): pNorm(5, testVecS50)  = " << result2p5 << std::endl;

        std::cout << "Test Vector Of Size 500 created, containing only." << std::endl;

        std::cout << "P norm result (p=1): pNorm(1, testVecS500) = " << result3p1 << std::endl;
        std::cout << "P norm result (p=2): pNorm(2, testVecS500) = " << result3p2 << std::endl;
        std::cout << "P norm result (p=3): pNorm(3, testVecS500) = " << result3p3 << std::endl;
        std::cout << "P norm result (p=4): pNorm(4, testVecS500) = " << result3p4 << std::endl;
        std::cout << "P norm result (p=5): pNorm(5, testVecS500) = " << result3p5 << std::endl;
    }

    MPI_Finalize();

    return 0;
}
