#include "./helpers.h"

void printVector(double *vec, int size)
{
    std::cout << "[" << std::endl;
    for (int i = 0; i < size; i++)
    {
        std::cout << " " << vec[i] << std::endl;
    }
    std::cout << "]" << std::endl;
}

void printVector(std::vector<double> vec)
{
    std::cout << "[\n";
    for (double item : vec)
    {
        std::cout << "  " << item << std::endl;
    }
    std::cout << "]" << std::endl;
}

void printVectorHorizontal(double *vec, int size)
{
    std::cout << "[";
    for (int i = 0; i < size; i++)
    {
        std::cout << " " << vec[i];
    }
    std::cout << " ]" << std::endl;
}

void printMatrix2D(double *A, int m, int n)
{
    for (size_t i = 0; i < m; i++)
    {
        std::cout << "| ";
        for (size_t j = 0; j < n; j++)
        {
            std::cout << A[i * n + j] << " ";
        }

        std::cout << "|" << std::endl;
    }
}

void printDblUnion(dblUnion u)
{
    std::cout << "unioned to double is " << u.dbl << std::endl;
    std::cout << "unioned to uint64 is " << u.uint64 << std::endl;
    std::cout << "unioned to int64 is " << u.int64 << std::endl;
    std::cout << "unioned to uint8* is [";
    for (size_t i = 0; i < 8; i++)
    {
        if (i)
        {
            std::cout << ", ";
        }
        std::cout << (int)u.uint8[i];
    }
    std::cout << "]" << std::endl;
}

/**
 * @brief Returns whether a positive value is a power of two
 *
 * @param value The value to check
 * @return true If the value is a power of 2
 * @return false If the value is not a power of 2
 */
bool isPowerOfTwo(int value)
{
    if (value <= 0)
    {
        return false;
    }

    // Only a number that is a power of two will, when subtracted
    // by one and ORed together, equal zero.
    // Example (power of 2):
    // val = 8       = 1000
    // val - 1 = 7   = 0111
    // 8 & 7         = 0000
    // Failure (not power of 2):
    // val = 10      = 1010
    // val - 1 = 9   = 1001
    // 10 & 9        = 1000
    return value & (value - 1) == 0;
}
