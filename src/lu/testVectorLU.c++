#include "vectorLU.h"

#define nmax 4

void printVector(std::vector<double> vec)
{
    std::cout << "[";
    for (double item : vec)
    {
        std::cout << "  " << item;
    }
    std::cout << "]" << std::endl;
}

void printMatrix(Matrix a) {
    for (auto v : a) {
        printVector(v);
    }
}

int main(int argc, char **argv)
{

    Matrix m(nmax);
    for (int i = 0; i < nmax; i++)
        m[i].resize(nmax);

    int num = 0;
    m[0] = std::vector<double>{2, 6, 7, -3};
    m[1] = std::vector<double>{4, 13, 11, 1};
    m[2] = std::vector<double>{-2, -2, -21, 41};
    m[3] = std::vector<double>{-8, -21, -51, 53};

    std::cout << " matrix: " << std::endl;

    printMatrix(m);

    LUPair luResult;
    luResult = vectorLU(m);

    std::cout << "L Decomposition is as follows..." << std::endl;
    printMatrix(luResult.first);

    std::cout << "U Decomposition is as follows..." << std::endl;
    printMatrix(luResult.second);

    return 0;
}
