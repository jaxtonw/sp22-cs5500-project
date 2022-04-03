#pragma once
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;



vector<vector<double>> addition(int rank, int size,
    vector<vector<double>> a, vector<vector<double>> b);
vector<vector<double>> subtraction(int rank, int size,
    vector<vector<double>> a, vector<vector<double>> b);
vector<vector<double>> element_multiply(int rank, int size,
    vector<vector<double>> a, double b);
vector<vector<double>> transpose(int rank, int size,
    vector<vector<double>> a);
pair<vector<vector<double>>, vector<vector<double>>> ludecomp(int rank, int size,
    vector<vector<double>> a)
void delay(int num);
//this code was found on http://skinderowicz.pl/static/pw2/MPI-tutorial.html
vector<double> recv_vector(int sender);
//this code was found on http://skinderowicz.pl/static/pw2/MPI-tutorial.html
void send_vector(int dest, const vector<double>& vec);


