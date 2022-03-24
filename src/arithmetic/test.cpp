


#include <iostream>
#include <mpi.h>
#include <cmath>
#include <random>
#include <time.h>
#include <stdlib.h>
#include <cstdio>
#include "arithmetic.h"

#define MCW MPI_COMM_WORLD
#define nmax 10
#define mmax 20







using namespace std;


int main(int argc, char** argv) {

    int orders = 0;
    int allOrders = 0;
    int shout;
    int rank = 0, size = 0;
    MPI_Request request;
    int experession = 4;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);


    vector<vector<double>> a(mmax);
    for (int i = 0; i < mmax; i++)
        a[i].resize(nmax);

    int num = 0;
    for (int i = 0; i < mmax; i++) {
        for (int k = 0; k < nmax; k++) {
            a[i][k] = num;
            num++;
            //cout<<a[i][k] <<" ";
        }
        //cout << endl;
    }


    delay(10);
    vector<vector<double> > b(mmax);
    for (int i = 0; i < mmax; i++)
        b[i].resize(nmax);


    for (int i = 0; i < mmax; i++) {
        for (int k = 0; k < nmax; k++) {
            b[i][k] = 1+k;
        }

    }
    MPI_Barrier(MCW);
    delay(15);
    //cout<<rank<<" is the rank "<<endl;
    


    if (!rank) {
        cout << "\n  matrix a " << endl;
        for (int i = 0; i < mmax; i++) {
            for (int k = 0; k < nmax; k++) {
                cout << a[i][k] << "  ";

            }
            cout << endl;

        }

        cout << "\n  matrix b " << endl;
        for (int i = 0; i < mmax; i++) {
            for (int k = 0; k < nmax; k++) {
                cout << b[i][k] << "  ";

            }
            cout << endl;

        }



    }
    vector<vector<double> > c(mmax);
    for (int i = 0; i < mmax; i++)
        c[i].resize(nmax);

    
        for (int i = 0; i < experession; i++) {
            switch (i) {
            case 0:

                c = addition(rank, size, a, b);


                break;
            case 1:
                c = subtraction(rank, size, a, b);
                break;
            case 2: {
                double constant = 1.234;
                c = element_multiply(rank, size, a, constant);
                break; }
            case 3:
                c.resize(nmax);
                    for (int i = 0; i < nmax; i++)
                    c[i].resize(mmax);
                c = transpose(rank, size, a);
                break;
            }
            if (!rank && i<3 ) {
                cout << "\n  output matrix " << endl;
                for (int i = 0; i < mmax; i++) {
                    for (int k = 0; k < nmax; k++) {
                        cout << c[i][k] << "  ";

                    }
                    cout << endl;

                }
            }
            else if (!rank && experession==4) {
                cout << "\n  output matrix " << endl;
                for (int i = 0; i < nmax; i++) {
                    for (int k = 0; k < mmax; k++) {
                        cout << c[i][k] << "  ";

                    }
                    cout << endl;

                }
                }
            }
    
    MPI_Barrier(MCW);
    delay(10);
   

    MPI_Finalize();

    return 0;
}











