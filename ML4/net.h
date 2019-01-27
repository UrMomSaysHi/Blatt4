#ifndef NET_H
#define NET_H
#include <vector>
#include "neuron.h"
#include "utilities.h"

using namespace std;

class Net
{
public:

    vector<vector<vector<double>>> delta_w;

    bool init_delta_w = true;

    vector<int> topology;

    Net(vector<int> topology, double (*f)(double), double (*df)(double));

    vector<vector<Neuron>> neuro_net;

    vector<vector<vector<double>>> dE_in_w(vector<double> x, vector<double> target);

    vector<double> predict(vector<double> x);

    vector<double> apply_activation(vector<double> x, vector<Neuron> layer);

    vector<double> apply_weights(vector<double> x, vector<Neuron> layer);

    vector<vector<double>> get_layer_result(vector<double> x);

    vector<double> apply_derivates(vector<double> x, vector<Neuron> layer);

    vector<double> calc_sigma(vector<double> sigma, vector<Neuron> layer, vector<double> layer_results);

    vector<vector<double>> calc_grad_layer(vector<double> sigma, vector<Neuron> layer, vector<double> layer_results);

    void update_weights(vector<vector<vector<double>>> delta_w);

    void train(vector<double> X, vector<double> y_target, double alpha, double learning_rate);

    vector<vector<vector<double>>> weights_to_vec();

    void vec_to_weights(vector<vector<vector<double>>> weights);

};

#endif // NET_H
