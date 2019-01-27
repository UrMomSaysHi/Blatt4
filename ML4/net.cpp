#include "net.h"
#include <iostream>
#include <fstream>
#include <assert.h>


Net::Net(vector<int> topology, double (*f)(double), double (*df)(double))
{
    Net::topology = topology;
    unsigned n_layers = topology.size();


    for(unsigned i_layer = 0; i_layer < n_layers; i_layer++)
    {
        neuro_net.push_back(vector<Neuron>());

        for(int i_neurons = 0; i_neurons < topology[i_layer]; i_neurons ++)
        {
            if (i_layer == n_layers){
                neuro_net.back().push_back(Neuron(*f,*df,0));
            } else {
                neuro_net.back().push_back(Neuron(*f,*df,topology[i_layer+1]));
            }
        }

        if (i_layer != n_layers-1){
            neuro_net.back().push_back(topology[i_layer+1]);
        }
    }
}

/*!
 * @brief calculates the resulting output given the input x
 *
 * @param x inmput
 *
 * @return output
 */
vector<double> Net::predict(vector<double> x)
{
    vector<double> result_vector;

    result_vector = get_layer_result(x).back();
    result_vector = apply_activation(result_vector, neuro_net.back());
    return(result_vector);

}


/*!
 * @brief calc the interim results for input x
 *
 * @param x input
 *
 * @return interim results
 */
vector<vector<double>> Net::get_layer_result(vector<double> x)
{
    assert(x.size()+1 == neuro_net[0].size());

    vector<vector<double>> result_layers;
    vector<double> result_vector = x;

    result_layers.push_back(result_vector);
    for(unsigned i = 0; i < neuro_net.size() - 1; i ++){
        result_vector.push_back(1);
        result_vector = apply_activation(result_vector, neuro_net[i]);
        result_vector = apply_weights(result_vector, neuro_net[i]);
        result_layers.push_back(result_vector);
    }


    return(result_layers);
}

/*!
 * @brief applys the activation function on input x
 *
 * @param x input
 *
 * @param layer neuron layer
 *
 * @return result
 */
vector<double> Net::apply_activation(vector<double> x, vector<Neuron> layer){
    assert(x.size() == layer.size());

    vector<double> result_vec;
    for(unsigned i = 0; i < x.size(); i ++){
        result_vec.push_back(layer[i].f(x[i]));
    }
    return(result_vec);
}

/*!
 * @brief applys weights on input x
 *
 * @param x input
 *
 * @param layer neuron layer
 *
 * @return result
 */
vector<double> Net::apply_weights(vector<double> x, vector<Neuron> layer){
    assert(x.size() == layer.size());

    vector<double> result_vec;
    for(unsigned i = 0; i < x.size(); i ++){
        if(i == 0){
            result_vec = scale(layer[i].weights, x[i]);
        } else {
            result_vec = v_add(scale(layer[i].weights, x[i]), result_vec);
        }
    }
    return(result_vec);
}

/*!
 * @brief applys derivates on input x
 *
 * @param x input
 *
 * @param layer neuron layer
 *
 * @return result
 */
vector<double> Net::apply_derivates(vector<double> x, vector<Neuron> layer){
    assert(x.size() == layer.size());

    vector<double> result_vec;
    for(unsigned i = 0; i < x.size(); i ++){
        result_vec.push_back(layer[i].df(x[i]));
    }
    return(result_vec);
}

/*!
 * @brief calculates the Gradient (kinda)
 *
 * @param x input
 *
 * @param target -value
 *
 * @return gradient
 */
vector<vector<vector<double>>> Net::dE_in_w(vector<double> x, vector<double> target){
    vector<vector<vector<double>>> jacobi_matrix;

    assert(target.size() == neuro_net.back().size());
    vector<double> y_pred = predict(x);
    vector<vector<double>> layer_values = get_layer_result(x);

    vector<double> delta = v_add(target, scale(y_pred, -1));
    vector<double> sigma;
    sigma = elem_wise_mul(delta, apply_derivates(layer_values.back(), neuro_net.back()));


    vector<vector<double>> layer_grad;
    for(int i_layer = neuro_net.size() - 2; i_layer >= 0; i_layer = i_layer - 1){
        layer_grad = calc_grad_layer(sigma, neuro_net[i_layer], layer_values[i_layer]);

        jacobi_matrix.insert(jacobi_matrix.begin(), layer_grad);
        sigma = calc_sigma(sigma, neuro_net[i_layer], layer_values[i_layer]);
    }

    return(jacobi_matrix);
}

/*!
 * @brief calculates sigma
 *
 * @param x input
 *
 * @param layer_result interim results for the layer
 *
 * @return sigma
 */
vector<double> Net::calc_sigma(vector<double> sigma, vector<Neuron> layer, vector<double> layer_results){
    assert(layer.size() == layer_results.size()+1);
    assert(layer[0].weights.size() == sigma.size());

    vector<double> new_sigma;

    double dfx_n;
    for(unsigned i_neuron = 0; i_neuron < layer.size()-1; i_neuron ++){
        dfx_n = layer[i_neuron].df(layer_results[i_neuron]);
        new_sigma.push_back(v_mult(layer[i_neuron].weights, sigma)*dfx_n);
    }

    return(new_sigma);
}

/*!
 * @brief calculates the Gradient for each layer
 *
 * @param sigma
 *
 * @param layer of Neurons
 *
 * @param layer_result interim results for the layer
 *
 * @return gradient
 */

vector<vector<double>> Net::calc_grad_layer(vector<double> sigma, vector<Neuron> layer, vector<double> layer_results){
    assert(layer.size() == layer_results.size()+1);
    assert(layer[0].weights.size() == sigma.size());

    vector<vector<double>> grad_vec_layer;

    double a_j;
    for(unsigned i_neuron = 0; i_neuron < layer.size(); i_neuron ++){
        a_j = layer[i_neuron].f(layer_results[i_neuron]) * 2;
        grad_vec_layer.push_back(scale(sigma, a_j));
    }
    return(grad_vec_layer);
}


/*!
 * @brief adds changes_w on the weights
 *
 * @param change_w
 *
 */
void Net::update_weights(vector<vector<vector<double>>> change_w){
    assert(neuro_net.size()-1 == change_w.size());
    for (unsigned i_layer = 0; i_layer < change_w.size(); i_layer++){
        assert(change_w[i_layer].size() == neuro_net[i_layer].size());
        for(unsigned i_neuron = 0; i_neuron < change_w[i_layer].size(); i_neuron++){
            for(unsigned i_weight = 0; i_weight < change_w[i_layer][i_neuron].size(); i_weight++){
                neuro_net[i_layer][i_neuron].weights[i_weight] = neuro_net[i_layer][i_neuron].weights[i_weight]
                        + change_w[i_layer][i_neuron][i_weight];
            }
        }
    }
}

/*!
 * @brief trains the Network
 *
 * @param x input
 *
 * @param y_target target
 *
 * @param alpha trägheit
 *
 * @param learning_rate
 *
 */

void Net::train(vector<double> x, vector<double> y_target, double alpha, double learning_rate){
    vector<vector<vector<double>>> w_gradient = scale(dE_in_w(x, y_target), learning_rate);

    if(init_delta_w){
        delta_w = scale(w_gradient, alpha);
        init_delta_w = false;
    } else {
        delta_w = v_add(scale(w_gradient, alpha),  scale(delta_w, 1 - alpha));
    }

    update_weights(delta_w);
}

/*!
 * @brief returns the weights as a vector
 *
 * @return weights
 */

vector<vector<vector<double>>> Net::weights_to_vec(){
    vector<vector<vector<double>>> result_vec;
    for(int e1 = 0; e1 < topology.size()-1; e1 ++){
        result_vec.push_back(vector<vector<double>>());
        for(int e2 = 0; e2 < topology[e1] + 1; e2++){
            result_vec.back().push_back(vector<double>());
            for(int e3 = 0; e3 < topology[e1 + 1]; e3 ++){
                result_vec.back().back().push_back(neuro_net[e1][e2].weights[e3]);
            }
        }
    }
    return(result_vec);
}

/*!
 * @brief changes all the weights to the given weights
 *
 */
void Net::vec_to_weights(vector<vector<vector<double>>> weights){

    for(int e1 = 0; e1 < weights.size(); e1 ++){

        for(int e2 = 0; e2 < weights[e1].size(); e2 ++){
            for(int e3 = 0; e3 < weights[e1][e2].size(); e3 ++){
                neuro_net[e1][e2].weights[e3] = weights[e1][e2][e3];
            }
        }
    }

}





