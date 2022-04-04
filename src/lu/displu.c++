#include "ludecomp.h"

#define MCW MPI_COMM_WORLD
#define nmax 10

int main(int argc, char **argv)
{
    int rank;
    int size;

    // 
    // delay(10);
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);

    //*/

    std::vector<std::vector<double>> m(nmax);
    for (int i = 0; i < nmax; i++)
        m[i].resize(nmax);

    int i;
    int j;
    int num = 0;
    for (i = 0; i < m.size(); i++)
    {
        for (j = 0; j < m.at(0).size(); j++)
        {
            m[i][j] = (rand() % 10); // mat[i][j];
            // std::cout << m[i][j] ;
        }
    }

    if (!rank)
    {
        std::cout << " matrix: " << std::endl;

        for (i = 0; i < m.size(); i++)
        {
            for (j = 0; j < m.at(0).size(); j++)
            {
                std::cout << m[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> matrix;
    // matrix = Ldecomposition(m, l, u);
    // matrix = lu_decomposition_sequential(m, l, u);
    matrix = ludecomp(rank, size, m);

    if (!rank)
    {
        std::cout << "L Decomposition is as follows..." << std::endl;
        for (i = 0; i < m.size(); i++)
        {
            for (j = 0; j < m.at(0).size(); j++)
            {
                // std::cout << l[i][j] << " ";
                std::cout << matrix.first[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "U Decomposition is as follows..." << std::endl;
        for (i = 0; i < m.size(); i++)
        {
            for (j = 0; j < m.at(0).size(); j++)
            {
                std::cout << matrix.second[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}
