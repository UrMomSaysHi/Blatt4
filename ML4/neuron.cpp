#include "neuron.h"

double const_zero(double x){
    return(0);
}

double const_one(double x){
    return(1);
}

default_random_engine generator;
normal_distribution<double> distribution(0,0.5);

Neuron::Neuron(int n_weights){
    Neuron::f = const_one;
    Neuron::df = const_zero;

    for(int i = 0; i < n_weights; i++){
        weights.push_back(distribution(generator)); //needs to be another value
    }
}

Neuron::Neuron(double (*f)(double), double (*df)(double), int n_weights)
{
    Neuron::f = f;
    Neuron::df = df;

    for(int i = 0; i < n_weights; i++){
        weights.push_back(distribution(generator)); //needs to be another value
    }

}

/*!
 * @brief returns all the outsputs for the input x
 *
 * @param x input
 *
 * @result output
 */

vector<double> Neuron::calc(int x)
{
    return(scale(weights, f(x)));
}
