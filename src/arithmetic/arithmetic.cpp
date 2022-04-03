/*
#include "arithmetic.h"



#define MCW MPI_COMM_WORLD
#define nmax 10
#define mmax 20





pair<vector<vector<double>>, vector<vector<double>>> ludecomp(int rank, int size,
    vector<vector<double>> a) {
    //temps
    double  ltemp = 0;
    double  utemp = 0;

    int indexflag = 0;
    int sizeoffset = size;

    pair<vector<vector<double>>, vector<vector<double>>> matrix;
    vector<vector<double>> l(a.size());
    for (int i = 0; i < a.at(0).size(); i++)
        l[i].resize(a.at(0).size());

    vector<vector<double>> u(a.size());
    for (int i = 0; i < a.size(); i++)
        u[i].resize(a.at(0).size());


    int index = rank;
    MPI_Barrier(MCW);


    for (int i = 0; i < a.size(); i++) {

        if (i - sizeoffset == size) {
            indexflag = 0;
            sizeoffset = sizeoffset + size;
        }
        if (i >= sizeoffset && !indexflag) {
            indexflag = 1;
            index = index + size;

        }

        for (int j = 0; j < a.size(); j++) {
            if (index == i) {
                //set zeros
                if (j < i) {
                    ltemp = 0;
                }
                //set diagonal
                else if (j == i)
                    ltemp = 1;
                //evaluate lower
                else {

                    ltemp = a[j][i];

                    for (int k = 0; k < i; k++) {
                        ltemp = ltemp - l[j][k] * u[k][i];

                    }
                }
            }
            if (i >= sizeoffset) {

                // MPI_Barrier(MCW);
                MPI_Bcast(&ltemp, 1, MPI_LONG_DOUBLE, (i - sizeoffset), MCW);
                //MPI_Barrier(MCW); 
                //cout << "rank: " << rank << " sizeoff " << sizeoffset << " i-size: " << i - sizeoffset << " i : " << i << " index: " << index << endl;

            }
            else {
                //MPI_Barrier(MCW);
                MPI_Bcast(&ltemp, 1, MPI_LONG_DOUBLE, i, MCW);
                //MPI_Barrier(MCW);
                //cout << "rank: " << rank << " sizeoff " << sizeoffset << " i-size: " << i - sizeoffset << " i : " << i << " index: " << index << endl;

            }
            l[j][i] = ltemp;
        }

        for (int j = 0; j < a.size(); j++) {
            if (index == i) {
                //set zeros
                if (j < i)
                    utemp = 0;
                //evaluate upper
                else {

                    utemp = a[i][j] / l[i][i];
                    for (int k = 0; k < i; k++) {

                        utemp = utemp - ((l[i][k] * u[k][j]) / l[i][i]);
                    }
                }

            }
            if (i >= sizeoffset) {
                //MPI_Barrier(MCW);
                MPI_Bcast(&utemp, 1, MPI_LONG_DOUBLE, i - sizeoffset, MCW);
                //MPI_Barrier(MCW);
                //cout << "rank: " << rank << " sizeoff " << sizeoffset << " i-size: " << i - sizeoffset << " i : " << i << " index: " << index << endl;

            }
            else {
                //MPI_Barrier(MCW);
                MPI_Bcast(&utemp, 1, MPI_LONG_DOUBLE, i, MCW);
                //MPI_Barrier(MCW);
                //cout << "rank: " << rank << " i-size: " << i - sizeoffset << " i : " << i << " index: " << index << endl;


            }

            u[i][j] = utemp;

        }


    }
    MPI_Barrier(MCW);

    matrix.first = l;
    matrix.second = u;

    return matrix;
}


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
                //std::cout << rank<<endl;
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
                    //   std::cout << "c array: " << c[index][l] << endl;
                    //}
                    delay(15);
                    //std::cout<< endl;
                    i++;
                    if (i == size)
                        i = 1;
                    delay(15);
                    index++;

                    MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MCW, &flag, &status);
                }
                if (index == a.size()) {
                    // std::cout << "if entered" << endl;
                    indexflag = 1;
                    //std::cout << "if exited" << c[3][3] << endl;

                }
                //send sum back to other processors
                if (!flag && indexflag) {
                    //std::cout<<"indexed: "<< c[4][8] << endl;

                    break;
                }
            }
            delay(10);

            //std::cout << rank << " break out" << endl;
            break;

        }
        else {//all other processors
              //send one random number from each processor to root
            delay(10);
            //std::cout << rank << endl;
            //send row to root processor
           // for (int l = 0; l < nmax; l++) {
            //    std::cout << "c array: " << c[j][l]<<"  ";
            //}
            send_vector(0, c[j]);
            

        }
        //if there are more columns then there are processors increment

        delay(10);


        j = j + size - 1;
    }


    MPI_Barrier(MCW);
    //  if (!rank) std::cout << rank << endl;
      //std::cout << "end of fun for : " << rank << endl;



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
                //std::cout<< rank<<endl;
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
                    //   std::cout << "c array: " << c[index][l] << endl;
                    //}
                    delay(15);
                    //std::cout<< endl;
                    i++;
                    if (i == size)
                        i = 1;
                    delay(15);
                    index++;

                    MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MCW, &flag, &status);
                }
                if (index == a.size()) {
                    // std::cout << "if entered" << endl;
                    indexflag = 1;
                    //std::cout << "if exited" << c[3][3] << endl;

                }
                //send sum back to other processors
                if (!flag && indexflag) {
                    //std::cout<<"indexed: "<< c[4][8] << endl;

                    break;
                }
            }
            delay(10);

            //std::cout << rank << " break out" << endl;
            break;

        }
        else {//all other processors
              //send one random number from each processor to root
            delay(10);
            //std::cout << rank << endl;
            //send row to root processor
           // for (int l = 0; l < nmax; l++) {
            //    std::cout << "c array: " << c[j][l]<<"  ";
            //}
            send_vector(0, c[j]);


        }
        //if there are more columns then there are processors increment

        delay(10);


        j = j + size - 1;
    }


    MPI_Barrier(MCW);
    //  if (!rank) std::cout << rank << endl;
      //std::cout << "end of fun for : " << rank << endl;



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
                //std::cout<< rank<<endl;
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
                    //   std::cout << "c array: " << c[index][l] << endl;
                    //}
                    delay(15);
                    //std::cout<< endl;
                    i++;
                    if (i == size)
                        i = 1;
                    delay(15);
                    index++;

                    MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MCW, &flag, &status);
                }
                if (index == a.size()) {
                    // std::cout << "if entered" << endl;
                    indexflag = 1;
                    //std::cout << "if exited" << c[3][3] << endl;

                }
                //send sum back to other processors
                if (!flag && indexflag) {
                    //std::cout<<"indexed: "<< c[4][8] << endl;

                    break;
                }
            }
            delay(10);

            //std::cout << rank << " break out" << endl;
            break;

        }
        else {//all other processors
              //send one random number from each processor to root
            delay(10);
            //std::cout << rank << endl;
            //send row to root processor
           // for (int l = 0; l < nmax; l++) {
            //    std::cout << "c array: " << c[j][l]<<"  ";
            //}
            send_vector(0, c[j]);


        }
        //if there are more columns then there are processors increment

        delay(10);


        j = j + size - 1;
    }


    MPI_Barrier(MCW);
    //  if (!rank) std::cout << rank << endl;
      //std::cout << "end of fun for : " << rank << endl;



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
                //std::cout<< rank<<endl;
                delay(10);
                // see if we have any messages
                int flag = 0;
                int indexflag = 0;
                int i = 1;
                std::cout << stuck << endl;

                MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MCW, &flag, &status);
                while (flag) {
                    //recive row from each processor

                    c[index] = recv_vector(i);

                    //for (int l = 0; l < c[1].size(); l++) {
                    //   std::cout << "c array: " << c[index][l] << endl;
                    //}
                    delay(15);
                    //std::cout<< endl;
                    i++;
                    if (i == size)
                        i = 1;
                    delay(15);
                    index++;

                    MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MCW, &flag, &status);
                }
                if (index == a[1].size()) {
                    // std::cout << "if entered" << endl;
                    indexflag = 1;
                    //std::cout << "if exited" << c[3][3] << endl;

                }
                //send sum back to other processors
                if (!flag && indexflag) {
//                    std::cout<<"indexed: "<< c[4][8] << endl;

                    break;
                }
            }
            delay(10);

            //std::cout << rank << " break out" << endl;
            break;

        }
        else {//all other processors
              //send one random number from each processor to root
            delay(10);
            //std::cout << rank << endl;
            //send row to root processor
           // for (int l = 0; l < nmax; l++) {
            //    std::cout << "c array: " << c[j][l]<<"  ";
            //}
            send_vector(0, c[j]);


        }
        //if there are more columns then there are processors increment

        delay(10);


        j = j + size - 1;
    }


    MPI_Barrier(MCW);
    //  if (!rank) std::cout << rank << endl;
      //std::cout << "end of fun for : " << rank << endl;



    return c;
}


//this function was found on http://skinderowicz.pl/static/pw2/MPI-tutorial.html
void send_vector(int dest, const vector<double>& vec) {
//send vector size
    int size = vec.size();
    MPI_Send(&size, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);

    // send vector element
    const double* elements = vec.data();
    MPI_Send(elements, size, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
}

//this function was found on http://skinderowicz.pl/static/pw2/MPI-tutorial.html
vector<double> recv_vector(int sender) {
    MPI_Status status;

    // Receive a message with vector size
    int size = 0;
    MPI_Recv(&size, 1, MPI_INT, sender, 0, MPI_COMM_WORLD, &status);
    

    vector<double> numbers(size);  //  allocate memory to the received items
    double* elements = numbers.data();  // convert to sendable data type
    MPI_Recv(elements, size, MPI_DOUBLE, sender, 0, MPI_COMM_WORLD, &status);

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






*/