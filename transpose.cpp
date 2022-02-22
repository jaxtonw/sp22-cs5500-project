



#include <iostream>
#include <mpi.h>
#include <cmath>
#include <random>
#include <time.h>
#include <stdlib.h>




#define MCW MPI_COMM_WORLD
#define nmax 10
#define mmax 20




void delay(int num);


using namespace std;
void transpose(int rank, int size, int a[nmax][mmax], int at[mmax][nmax]);



int main(int argc, char** argv) {

    int orders = 0;
    int allOrders = 0;
    int shout;
    int rank = 0, size = 0;
    MPI_Request request;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);



    int a[nmax][mmax] = {};

    int num = 0;
    for (int i = 0; i < nmax; i++) {
        for (int k = 0; k < mmax; k++) {
            a[i][k]=num;
            num++;

        }

    }


    delay(10);
    
    int at[mmax][nmax] = {};

    for (int i = 0; i < mmax; i++) {
        for (int k = 0; k < nmax; k++) {
            at[i][k] = 0;
        }

    }

    transpose(rank, size, a, at);

    //MPI_Barrier(MCW);
    delay(10);
    //print matrix
    if (rank == 0) {
        
        for (int i = 0; i < nmax; i++) {
            for (int k = 0; k < mmax; k++) {
                cout << a[i][k] << "  ";

            }
            cout << endl;

        }

        cout << "\n  transpose " << endl;
        for (int i = 0; i < mmax; i++) {
            for (int k = 0; k < nmax; k++) {
                cout << at[i][k] << "  ";

            }
            cout << endl;

        }


    }

    MPI_Finalize();

    return 0;
}



void delay(int num) {
    num = num * num;
    bool stuff = false;
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            stuff = !stuff;
        }
    }
    //return (int)stuff;

}







void transpose(int rank, int size, int a[nmax][mmax], int at[mmax][nmax]) {
    MPI_Status status;
    //set variable to processor
    int j = rank;
    int index = 1;
//force start at same place
    MPI_Barrier(MCW);
    while (j < mmax) {
        //transpose paralliezed 
        for (int i = 0; i < size; i++) {
            if (rank == i) {
                for (int k = 0; k < nmax; k++) {
                    at[j][k] = a[k][j];

                }

            }

        }
        //merge processors
        if (!rank) {
            while (1) {//root proccessor
                // see if we have any messages
                int flag = 0;
                int indexflag = 0;
                int i = 1;

                MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MCW, &flag, &status);
                while (flag) {
                    //recive row from each processor
                    MPI_Recv(&at[index], nmax, MPI_INT, i, 0, MCW, &status);
                    delay(10);
                   // cout << index << endl;
                    i++;
                    if (i == size)
                        i = 1;

                    index++;

                    MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MCW, &flag, &status);
                }

                if (index == mmax) {
                    //cout << "if entered" << endl;
                    indexflag = 1;
                }
                //send sum back to other processors
                if (!flag && indexflag) {

                    break;
                }
            }
        }
        else {//all other processors
            //send one random number from each processor to root
            delay(10);
            //cout << rank << endl;
            //send row to root processor
            MPI_Send(&at[j], nmax, MPI_INT, 0, 0, MCW);

        }
        //if there are more columns then there are processors increment
        j = j + size - 1;

    }
    MPI_Barrier(MCW);

}

    











