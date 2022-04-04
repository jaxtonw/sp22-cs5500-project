#include "../../src/common/helpers.h"
#include "../../src/norms/infnorm.h"
#include "mpi.h"
#include <algorithm>

#define MCW MPI_COMM_WORLD

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, commSize = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double testVecS5[5];
    double testVecS5Shuffled[5];
    double testVecS5Reversed[5];

    double testVecS50[50];
    double testVecS50Shuffled[50];
    double testVecS50Reversed[50];

    double testVecS500[500];
    double testVecS500Shuffled[500];
    double testVecS500Reversed[500];

    for (int i = 0; i < 5; i++)
    {
        testVecS5[i] = (double) i;
    }

    for (int i = 0; i < 50; i++)
    {
        testVecS50[i] = (double) i;
    }

    for (int i = 0; i < 500; i++)
    {
        testVecS500[i] = (double) i;
    }


    std::copy(std::begin(testVecS5), std::end(testVecS5), std::begin(testVecS5Shuffled));
    std::random_shuffle(std::begin(testVecS5Shuffled), std::end(testVecS5Shuffled));

    std::copy(std::begin(testVecS5), std::end(testVecS5), std::begin(testVecS5Reversed));
    std::reverse(std::begin(testVecS5Reversed), std::end(testVecS5Reversed));

    std::copy(std::begin(testVecS50), std::end(testVecS50), std::begin(testVecS50Shuffled));
    std::random_shuffle(std::begin(testVecS50Shuffled), std::end(testVecS50Shuffled));

    std::copy(std::begin(testVecS50), std::end(testVecS50), std::begin(testVecS50Reversed));
    std::reverse(std::begin(testVecS50Reversed), std::end(testVecS50Reversed));

    std::copy(std::begin(testVecS500), std::end(testVecS500), std::begin(testVecS500Shuffled));
    std::random_shuffle(std::begin(testVecS500Shuffled), std::end(testVecS500Shuffled));

    std::copy(std::begin(testVecS500), std::end(testVecS500), std::begin(testVecS500Reversed));
    std::reverse(std::begin(testVecS500Reversed), std::end(testVecS500Reversed));


    double result1 = infNorm(testVecS5, 5, MCW);
    double result2 = infNorm(testVecS5Shuffled, 5, MCW);
    double result3 = infNorm(testVecS5Reversed, 5, MCW);

    double result4 = infNorm(testVecS50, 50, MCW);
    double result5 = infNorm(testVecS50Shuffled, 50, MCW);
    double result6 = infNorm(testVecS50Reversed, 50, MCW);

    double result7 = infNorm(testVecS500, 500, MCW);
    double result8 = infNorm(testVecS500Shuffled, 500, MCW);
    double result9 = infNorm(testVecS500Reversed, 500, MCW);


    if (!rank)
    {
        std::cout << "Test Vector Of Size 5: ";

        printVector(testVecS5, 5);

        std::cout << "Inf norm result: infNorm(testVecS5) = " << result1 << std::endl;

        std::cout << "Inf norm result: infNorm(testVecS5Shuffled) = " << result2 << std::endl;

        std::cout << "Inf norm result: infNorm(testVecS5Reversed) = " << result3 << std::endl;

        std::cout << "Test Vector Of Size 50 created, like the above test vector, with max of 49." << std::endl;

        std::cout << "Inf norm result: infNorm(testVecS50) = " << result4 << std::endl;

        std::cout << "Inf norm result: infNorm(testVecS50Shuffled) = " << result5 << std::endl;

        std::cout << "Inf norm result: infNorm(testVecS50Reversed) = " << result6 << std::endl;

        std::cout << "Test Vector Of Size 500 created, like the above test vector, with max of 499." << std::endl;

        std::cout << "Inf norm result: infNorm(testVecS50) = " << result7 << std::endl;

        std::cout << "Inf norm result: infNorm(testVecS50Shuffled) = " << result8 << std::endl;

        std::cout << "Inf norm result: infNorm(testVecS50Reversed) = " << result9 << std::endl;
    }

    MPI_Finalize();

    return 0;
}
