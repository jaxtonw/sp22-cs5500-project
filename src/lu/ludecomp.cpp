#include "./ludecomp.h"

std::pair<std::vector<std::vector<double>>,
          std::vector<std::vector<double>>>
ludecomp(int rank, int size,
         std::vector<std::vector<double>> a)
{
    // temps
    double ltemp = 0;
    double utemp = 0;

    int indexflag = 0;
    int sizeoffset = size;

    std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> matrix;
    std::vector<std::vector<double>> l(a.size());
    for (int i = 0; i < a.at(0).size(); i++)
        l[i].resize(a.at(0).size());

    std::vector<std::vector<double>> u(a.size());
    for (int i = 0; i < a.size(); i++)
        u[i].resize(a.at(0).size());

    int index = rank;
    MPI_Barrier(MCW);

    for (int i = 0; i < a.size(); i++)
    {
        if (i - sizeoffset == size)
        {
            indexflag = 0;
            sizeoffset = sizeoffset + size;
        }
        if (i >= sizeoffset && !indexflag)
        {
            indexflag = 1;
            index = index + size;
        }

        for (int j = 0; j < a.size(); j++) {
            if (index == i) {
                //set zeros
                if (j < i)
                    u[i][j] = 0;
                //evaluate upper
                else {

                    u[i][j] = a[i][j];
                    for (int k = 0; k < i; k++) {

                        u[i][j] = u[i][j] - ((u[k][j] * l[i][k]));
                      //cout << "u: " << u[i][j] << " u[k][j] " << u[k][i] << " l[i][k]: " << l[j][k] << endl;

                    }
                }

            }
            if (i >= sizeoffset) {
                MPI_Barrier(MCW);
                MPI_Bcast(&u[i][j], 1, MPI_LONG_DOUBLE, i - sizeoffset, MCW);
                MPI_Barrier(MCW);
                //cout << "rank: " << rank << " sizeoff " << sizeoffset << " i-size: " << i - sizeoffset << " i : " << i << " index: " << index << endl;

            }
            else {
                MPI_Barrier(MCW);
                MPI_Bcast(&u[i][j], 1, MPI_LONG_DOUBLE, i, MCW);
                MPI_Barrier(MCW);
                //cout << "rank: " << rank << " i-size: " << i - sizeoffset << " i : " << i << " index: " << index << endl;


            }


        }



        for (int j = 0; j < a.size(); j++) {
            if (index == i) {
                //set zeros
                if (j < i) {
                    l[j][i] = 0;
                }
                //set diagonal
                else if (j == i) {
                    l[j][i] = 1;
                    if (a[j][i] == 0) {
                        cout<< "not Decomposable" << endl;
                        break;
                    }
                }
                //evaluate lower
                else {

                    l[j][i] = a[j][i]/u[i][i];

                    for (int k = 0; k < i; k++) {
                        l[j][i] = l[j][i] - ((u[k][i] * l[j][k])/u[i][i]);
                      //cout << "l: " << l[j][i]  << " u[k][i] " << u[k][i] << " l[j][k]: " << l[j][k] << endl;

                    }
                }
            }
            if (i >= sizeoffset) {

                MPI_Barrier(MCW);
                MPI_Bcast(&l[j][i], 1, MPI_LONG_DOUBLE, (i - sizeoffset), MCW);
                MPI_Barrier(MCW);
                //cout << "rank: " << rank << " sizeoff " << sizeoffset << " i-size: " << i - sizeoffset << " i : " << i << " index: " << index << endl;

            }
            else {
                MPI_Barrier(MCW);
                MPI_Bcast(&l[j][i], 1, MPI_LONG_DOUBLE, i, MCW);
                MPI_Barrier(MCW);
                //cout << "rank: " << rank << " sizeoff " << sizeoffset << " i-size: " << i - sizeoffset << " i : " << i << " index: " << index << endl;

            }
            //l[j][i] = ltemp;

        }
    }
    MPI_Barrier(MCW);

    matrix.first = l;
    matrix.second = u;

    return matrix;
}
