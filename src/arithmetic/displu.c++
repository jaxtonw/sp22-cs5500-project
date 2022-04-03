#include<iostream>

#include "arithmetic.h"

#define MCW MPI_COMM_WORLD
#define nmax 10

using namespace std;






int main(int argc, char** argv) {
    int rank;
    int size;

    delay(10);
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);

    //*/

    vector<vector<double>> m(nmax);
    for (int i = 0; i < nmax; i++)
        m[i].resize(nmax);



    int i;
    int j;
    int num = 0;
    for (i = 0; i < m.size(); i++) {
        for (j = 0; j < m.at(0).size(); j++){
            m[i][j] = (rand()%10);//mat[i][j];
            //cout << m[i][j] ;

        }
    }
    
   if (!rank) {
        cout << " matrix: " << endl;

        for (i = 0; i < m.size(); i++) {
            for (j = 0; j < m.at(0).size(); j++) {
                cout << m[i][j] << " ";
            }
            cout << endl;
        }
   }
    pair<vector<vector<double>>, vector<vector<double>>> matrix;
   //matrix = Ldecomposition(m, l, u);
  //matrix = lu_decomposition_sequential(m, l, u);
   matrix = ludecomp(rank, size, m);


   if (!rank) {
       cout << "L Decomposition is as follows..." << endl;
       for (i = 0; i < m.size(); i++) {
           for (j = 0; j < m.at(0).size(); j++) {
               //cout << l[i][j] << " ";
               cout << matrix.first[i][j] << " ";
           }
           cout << endl;
       }
       cout << "U Decomposition is as follows..." << endl;
       for (i = 0; i < m.size(); i++) {
           for (j = 0; j < m.at(0).size(); j++) {
               cout << matrix.second[i][j] << " ";
           }
           cout << endl;
       }
   }

   MPI_Finalize();
    return 0;
}






 



