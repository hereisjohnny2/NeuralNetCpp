#include "CNetwork.hpp"
#include "CLayer.hpp"
#include "CActivation.hpp"

using namespace std;

vector<vector<double>> CNetwork::Forward(vector<vector<double>> X)
{
    output = X;
    for (int i = 0; i < layers.size() - 1; i++)
        output = (*activations[i])(layers[i](output));

    output = layers.back()(output);

    // for (int i = 0; i < output.size(); i++)
    // {
    //     double soma = 0.0;
    //     for (int j = 0; j < output[0].size(); j++)
    //         soma += output[i][j];
    //     for (int j = 0; j < output[0].size(); j++)
    //         output[i][j] /= soma;
    // }

    return output;
}

void CNetwork::Backpropagate(vector<vector<double>> loss)
{
    layers.back().delta = activations.back()->ForwardPrime(layers.back().output);
    for (int i = 0; i < layers.back().delta.size(); i++)
        for (int j = 0; j < layers.back().delta[0].size(); j++)
            layers.back().delta[i][j] *= loss[i][j];

    for (int l = layers.size() - 2; l >= 0; l--)
    {
        layers[l].delta = activations[l]->ForwardPrime(layers[l].output);
        for (int i = 0; i < layers[l + 1].delta.size(); i++)
        {
            for (int j = 0; j < layers[l + 1].weights.size(); j++)
            {
                double sum{0.0};
                for (int k = 0; k < layers[l + 1].weights[0].size(); k++)
                    sum += layers[l + 1].delta[i][k] * layers[l + 1].weights[j][k];
                layers[l].delta[i][j] *= sum;
            }
        }
    }
}

void CNetwork::UpdateParams(double lr, const vector<vector<double>> &X)
{
    for (int l = 0; l < layers.size(); l++)
    {
        auto deltaBiases = layers[l].biases;
        for (int i = 0; i < layers[l].delta.size(); i++)
            for (int j = 0; j < layers[l].delta[0].size(); j++)
                deltaBiases[j][0] += layers[l].delta[i][j];

        for (int i = 0; i < layers[l].biases.size(); i++)
            layers[l].biases[i][0] -= (lr / X.size()) * deltaBiases[i][0];
    }

    for (int i = 0; i < X[0].size(); i++)
    {
        for (int j = 0; j < layers[0].delta[0].size(); j++)
        {
            double sum{0.0};
            for (int k = 0; k < layers[0].delta.size(); k++)
                sum += X[k][i] * layers[0].delta[k][j];

            layers[0].weights[i][j] -= (lr / X.size()) * sum;
        }
    }

    for (int l = 1; l < layers.size(); l++)
    {
        for (int i = 0; i < layers[l - 1].output[0].size(); i++)
        {
            for (int j = 0; j < layers[l].delta[0].size(); j++)
            {
                double sum{0.0};
                for (int k = 0; k < layers[l].delta.size(); k++)
                    sum += layers[l - 1].output[k][i] * layers[l].delta[k][j];
                layers[l].weights[i][j] -= (lr / X.size()) * sum;
            }
        }
    }
}

std::ostream &operator<<(std::ostream &os, const CNetwork &net)
{
    for (int i = 0; i < net.output.size(); i++)
    {
        for (int j = 0; j < net.output[0].size(); j++)
            os << net.output[i][j] << " ";
        os << std::endl;
    }
    return os;
}
