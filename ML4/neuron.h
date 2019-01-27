#ifndef NEURON_H
#define NEURON_H
#include <vector>
#include <random>
#include <stdlib.h>
#include "utilities.h"
#include <random>


using namespace std;

class Neuron
{
public:
    Neuron(int n_weights);
    Neuron(double (*f)(double), double (*df)(double), int n_weights);
    double (*f)(double);
    double (*df)(double);

    vector<double> weights;
    vector<double> calc(int x);
};

#endif // NEURON_H
