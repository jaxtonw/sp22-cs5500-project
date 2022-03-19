
#include "arithmetic.h"



#define MCW MPI_COMM_WORLD
#define nmax 10
#define mmax 20
using namespace std;


vector<vector<double>> addition(int rank, int size,
    vector<vector<double>> a, vector<vector<double>>  b) {
    MPI_Status status;

    vector<vector<double> > c(a.size());
    for (int i = 0; i < a.size(); i++)
        c[i].resize(a[1].size());


    int j = rank;
    int index = 1;
    //force start at same place
    MPI_Barrier(MCW);

    while (j < a.size()) {
        //addition paralliezed 
        for (int i = 0; i < size; i++) {
            if (rank == i) {
                for (int k = 0; k < a[1].size(); k++) {
                    c[j][k] = a[j][k] + b[j][k];

                }

            }

        }

        //merge processors
        if (!rank) {

            while (1) {//root proccessor
                //cout<< rank<<endl;
                delay(10);
                // see if we have any messages
                int flag = 0;
                int indexflag = 0;
                int i = 1;
                
                MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MCW, &flag, &status);
                while (flag) {
                    //recive row from each processor

                    c[index]=recv_vector(i);

                    //for (int l = 0; l < nmax; l++) {
                    //   cout << "c array: " << c[index][l] << endl;
                    //}
                    delay(15);
                    //cout<< endl;
                    i++;
                    if (i == size)
                        i = 1;
                    delay(15);
                    index++;

                    MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MCW, &flag, &status);
                }
                if (index == a.size()) {
                    // cout << "if entered" << endl;
                    indexflag = 1;
                    //cout << "if exited" << c[3][3] << endl;

                }
                //send sum back to other processors
                if (!flag && indexflag) {
                    //cout<<"indexed: "<< c[4][8] << endl;

                    break;
                }
            }
            delay(10);

            //cout << rank << " break out" << endl;
            break;

        }
        else {//all other processors
              //send one random number from each processor to root
            delay(10);
            //cout << rank << endl;
            //send row to root processor
           // for (int l = 0; l < nmax; l++) {
            //    cout << "c array: " << c[j][l]<<"  ";
            //}
            send_vector(0, c[j]);
            

        }
        //if there are more columns then there are processors increment

        delay(10);


        j = j + size - 1;
    }


    MPI_Barrier(MCW);
    //  if (!rank) cout << rank << endl;
      //cout << "end of fun for : " << rank << endl;



    return c;
}

vector<vector<double>> subtraction(int rank, int size,
    vector<vector<double>> a, vector<vector<double>>  b) {
    MPI_Status status;

    vector<vector<double> > c(a.size());
    for (int i = 0; i < a.size(); i++)
        c[i].resize(a[1].size());


    int j = rank;
    int index = 1;
    //force start at same place
    MPI_Barrier(MCW);

    while (j < a.size()) {
        //addition paralliezed 
        for (int i = 0; i < size; i++) {
            if (rank == i) {
                for (int k = 0; k < a[1].size(); k++) {
                    c[j][k] = a[j][k] - b[j][k];

                }

            }

        }

        //merge processors
        if (!rank) {

            while (1) {//root proccessor
                //cout<< rank<<endl;
                delay(10);
                // see if we have any messages
                int flag = 0;
                int indexflag = 0;
                int i = 1;

                MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MCW, &flag, &status);
                while (flag) {
                    //recive row from each processor

                    c[index] = recv_vector(i);

                    //for (int l = 0; l < nmax; l++) {
                    //   cout << "c array: " << c[index][l] << endl;
                    //}
                    delay(15);
                    //cout<< endl;
                    i++;
                    if (i == size)
                        i = 1;
                    delay(15);
                    index++;

                    MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MCW, &flag, &status);
                }
                if (index == a.size()) {
                    // cout << "if entered" << endl;
                    indexflag = 1;
                    //cout << "if exited" << c[3][3] << endl;

                }
                //send sum back to other processors
                if (!flag && indexflag) {
                    //cout<<"indexed: "<< c[4][8] << endl;

                    break;
                }
            }
            delay(10);

            //cout << rank << " break out" << endl;
            break;

        }
        else {//all other processors
              //send one random number from each processor to root
            delay(10);
            //cout << rank << endl;
            //send row to root processor
           // for (int l = 0; l < nmax; l++) {
            //    cout << "c array: " << c[j][l]<<"  ";
            //}
            send_vector(0, c[j]);


        }
        //if there are more columns then there are processors increment

        delay(10);


        j = j + size - 1;
    }


    MPI_Barrier(MCW);
    //  if (!rank) cout << rank << endl;
      //cout << "end of fun for : " << rank << endl;



    return c;
}
vector<vector<double>> element_multiply(int rank, int size,
    vector<vector<double>> a, double b) {
    MPI_Status status;

    vector<vector<double> > c(a.size());
    for (int i = 0; i < a.size(); i++)
        c[i].resize(a[1].size());


    int j = rank;
    int index = 1;
    //force start at same place
    MPI_Barrier(MCW);

    while (j < a.size()) {
        //addition paralliezed 
        for (int i = 0; i < size; i++) {
            if (rank == i) {
                for (int k = 0; k < a[1].size(); k++) {
                    c[j][k] = a[j][k] *b;

                }

            }

        }

        //merge processors
        if (!rank) {

            while (1) {//root proccessor
                //cout<< rank<<endl;
                delay(10);
                // see if we have any messages
                int flag = 0;
                int indexflag = 0;
                int i = 1;

                MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MCW, &flag, &status);
                while (flag) {
                    //recive row from each processor

                    c[index] = recv_vector(i);

                    //for (int l = 0; l < nmax; l++) {
                    //   cout << "c array: " << c[index][l] << endl;
                    //}
                    delay(15);
                    //cout<< endl;
                    i++;
                    if (i == size)
                        i = 1;
                    delay(15);
                    index++;

                    MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MCW, &flag, &status);
                }
                if (index == a.size()) {
                    // cout << "if entered" << endl;
                    indexflag = 1;
                    //cout << "if exited" << c[3][3] << endl;

                }
                //send sum back to other processors
                if (!flag && indexflag) {
                    //cout<<"indexed: "<< c[4][8] << endl;

                    break;
                }
            }
            delay(10);

            //cout << rank << " break out" << endl;
            break;

        }
        else {//all other processors
              //send one random number from each processor to root
            delay(10);
            //cout << rank << endl;
            //send row to root processor
           // for (int l = 0; l < nmax; l++) {
            //    cout << "c array: " << c[j][l]<<"  ";
            //}
            send_vector(0, c[j]);


        }
        //if there are more columns then there are processors increment

        delay(10);


        j = j + size - 1;
    }


    MPI_Barrier(MCW);
    //  if (!rank) cout << rank << endl;
      //cout << "end of fun for : " << rank << endl;



    return c;
}

vector<vector<double>> transpose(int rank, int size,
    vector<vector<double>> a) {
    MPI_Status status;
    string stuck = "stuck";
    vector<vector<double> > c(a[1].size());
    for (int i = 0; i < a[1].size(); i++)
        c[i].resize(a.size());



    int j = rank;
    int index = 1;
    //force start at same place
    MPI_Barrier(MCW);

    while (j < a[1].size()) {
        //addition paralliezed 
        for (int i = 0; i < size; i++) {
            if (rank == i) {
                for (int k = 0; k < a.size(); k++) {
                    c[j][k] = a[k][j];

                }

            }

        }

        //merge processors
        if (!rank) {

            while (1) {//root proccessor
                //cout<< rank<<endl;
                delay(10);
                // see if we have any messages
                int flag = 0;
                int indexflag = 0;
                int i = 1;
                cout << stuck << endl;

                MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MCW, &flag, &status);
                while (flag) {
                    //recive row from each processor

                    c[index] = recv_vector(i);

                    //for (int l = 0; l < c[1].size(); l++) {
                    //   cout << "c array: " << c[index][l] << endl;
                    //}
                    delay(15);
                    //cout<< endl;
                    i++;
                    if (i == size)
                        i = 1;
                    delay(15);
                    index++;

                    MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MCW, &flag, &status);
                }
                if (index == a[1].size()) {
                    // cout << "if entered" << endl;
                    indexflag = 1;
                    //cout << "if exited" << c[3][3] << endl;

                }
                //send sum back to other processors
                if (!flag && indexflag) {
//                    cout<<"indexed: "<< c[4][8] << endl;

                    break;
                }
            }
            delay(10);

            //cout << rank << " break out" << endl;
            break;

        }
        else {//all other processors
              //send one random number from each processor to root
            delay(10);
            //cout << rank << endl;
            //send row to root processor
           // for (int l = 0; l < nmax; l++) {
            //    cout << "c array: " << c[j][l]<<"  ";
            //}
            send_vector(0, c[j]);


        }
        //if there are more columns then there are processors increment

        delay(10);


        j = j + size - 1;
    }


    MPI_Barrier(MCW);
    //  if (!rank) cout << rank << endl;
      //cout << "end of fun for : " << rank << endl;



    return c;
}



void send_vector(int dest, const vector<double>& vec) {
    // Pobierz i wyślij rozmiar wektora
    uint32_t size = static_cast<uint32_t>(vec.size());
    MPI_Send(&size, 1, MPI_UNSIGNED, dest, 0, MPI_COMM_WORLD);

    // Teraz elementy
    const double* elements = vec.data();
    MPI_Send(elements, size, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
}


vector<double> recv_vector(int sender) {
    MPI_Status status;

    // Odbierz wiad. z rozmiarem wektora
    uint32_t size = 0;
    auto code = MPI_Recv(&size, 1, MPI_UNSIGNED, sender, 0, MPI_COMM_WORLD, &status);
    if (code != MPI_SUCCESS) {
        MPI_Abort(MPI_COMM_WORLD, code);
    }

    vector<double> numbers(size);  // Alokujemy pamięć na otrzymane elementy
    double* elements = numbers.data();  // Wskaźnik bufora docelowego
    code = MPI_Recv(elements, size, MPI_DOUBLE, sender, 0, MPI_COMM_WORLD, &status);
    if (code != MPI_SUCCESS) {
        MPI_Abort(MPI_COMM_WORLD, code);
    }
    return numbers;
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






