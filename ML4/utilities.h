#ifndef UTILITIES_H
#define UTILITIES_H

#include<vector>
#include<iostream>

using namespace std;



vector<double> scale(vector<double> v, double c);

vector<vector<vector<double>>> scale(vector<vector<vector<double>>> v, double c);

double v_mult(vector<double> v1, vector<double> v2);

vector<double> v_add(vector<double> v1, vector<double> v2);

vector<vector<vector<double>>>  v_add(vector<vector<vector<double>>>  v1, vector<vector<vector<double>>>  v2);

vector<double> elem_wise_mul(vector<double> v1, vector<double> v2);

double sigmoid0(double x);

double dsigmoid0(double x);

#endif // UTILITIES_H
