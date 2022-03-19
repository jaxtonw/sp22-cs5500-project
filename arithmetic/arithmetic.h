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
void delay(int num);

vector<double> recv_vector(int sender);

void send_vector(int dest, const vector<double>& vec);


