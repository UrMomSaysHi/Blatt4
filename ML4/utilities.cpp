#include "utilities.h"
#include "assert.h"
#include <cmath>

using namespace std;

/*!
 * @brief scales the vector
 *
 * @param v vector
 *
 * @param c scaler
 *
 * @return scaled vector
 */
vector<double> scale(vector<double> v, double c){
    vector<double> result_vec;
    for(int i = 0; i < v.size(); i++){
        result_vec.push_back(v[i]*c);
    }
    return(result_vec);
}

/*!
 * @brief vector multiplication
 *
 * @param v1 vector
 *
 * @param v1 vector
 *
 * @return result
 */
double v_mult(vector<double> v1, vector<double> v2){
    double sum = 0;
    assert(v1.size() == v2.size());

    for(int i = 0; i < v1.size(); i++){
        sum = sum + v1[i]*v2[i];
    }

    return(sum);
}

/*!
 * @brief add two vectors
 *
 * @param v1 vector
 *
 * @param v1 vector
 *
 * @return result
 */
vector<double> v_add(vector<double> v1, vector<double> v2){
    vector<double> result_vec;
    assert(v1.size() == v2.size());

    for(int i = 0; i < v1.size(); i++){
        result_vec.push_back(v1[i] + v2[i]);
    }
    return(result_vec);

}


/*!
 * @brief elementwise multiplication
 *
 * @param v1 vector
 *
 * @param v1 vector
 *
 * @return result
 */
vector<double> elem_wise_mul(vector<double> v1, vector<double> v2){
    vector<double> result_vec;
    assert(v1.size() == v2.size());

    for(int i = 0; i < v1.size(); i++){
        result_vec.push_back(v1[i] * v2[i]);
    }
    return(result_vec);
}

/*!
 * @brief scales the vector
 *
 * @param v vector
 *
 * @param c scaler
 *
 * @return scaled vector
 */
vector<vector<vector<double>>> scale(vector<vector<vector<double>>> v, double c){
    for(auto v1=v.begin(); v1!=v.end(); ++v1){
        for(auto v2=v1->begin(); v2!=v1->end(); ++v2){
            for(auto v3=v2->begin(); v3!=v2->end(); ++v3){
                *v3 = *v3 * c;
            }
        }
    }

    return(v);
}

/*!
 * @brief add two vectors
 *
 * @param v1 vector
 *
 * @param v1 vector
 *
 * @return result
 */
vector<vector<vector<double>>>  v_add(vector<vector<vector<double>>>  v1, vector<vector<vector<double>>>  v2){
    for(unsigned i_1 = 0; i_1 < v1.size(); i_1 ++){
        for(unsigned i_2 = 0; i_2 < v1[i_1].size(); i_2 ++){
            for(unsigned i_3 = 0; i_3 < v1[i_1][i_2].size(); i_3 ++){
                v1[i_1][i_2][i_3] = v1[i_1][i_2][i_3] + v2[i_1][i_2][i_3];
            }
        }
    }
    return(v1);
}

/*!
 * @brief sigmoid
 *
 * @param x in
 *
 * @return result
 */
double sigmoid0(double x){
    double e = 2.71828;
    return(pow(1 + pow(e,-x), -1));
}

/*!
 * @brief derivate of sigmoid (dont ask me about the zero)
 *
 * @param x in
 *
 * @return result
 */
double dsigmoid0(double x){
    return(sigmoid0(x)*(1- sigmoid0(x)));
}
