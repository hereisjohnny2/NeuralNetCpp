#include <cassert>
#include <random>
#include <iostream>

#include "CLayer.hpp"

using namespace std;

CLayer::CLayer(int inputs, int neurons)
{
    weights = vector<vector<double>>(inputs, std::vector<double>(neurons, 0.0));
    biases = vector<vector<double>>(neurons, std::vector<double>(1, 0.0));

    // Creating a random device to generate normal distribuded randon numbers
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> dis(0.0, 1.0);

    for (int i = 0; i < weights.size(); i++)
        for (int j = 0; j < weights[0].size(); j++)
            weights[i][j] = dis(gen) * 0.1;
}

vector<vector<double>> CLayer::Forward(vector<vector<double>> X)
{
    assert(weights.size() == X[0].size());

    output = vector<vector<double>>(X.size(), vector<double>(weights[0].size()));

    for (int i = 0; i < X.size(); i++)
        for (int j = 0; j < weights[0].size(); j++)
        {
            double sum{0.0};
            for (int k = 0; k < weights.size(); k++)
                sum += X[i][k] * weights[k][j];
            output[i][j] = sum + biases[j][0];
        }

    return output;
}

std::ostream &operator<<(std::ostream &os, const CLayer &layer)
{
    os << "\nWeights: " << endl;
    for (int i = 0; i < layer.weights.size(); i++)
    {
        for (int j = 0; j < layer.weights[0].size(); j++)
            os << layer.weights[i][j] << " ";
        os << endl;
    }

    os << "\nBiases: " << endl;
    for (int i = 0; i < layer.biases.size(); i++)
        os << layer.biases[i][0] << endl;

    os << "\nOutput: " << endl;
    for (int i = 0; i < layer.output.size(); i++)
    {
        for (int j = 0; j < layer.output[0].size(); j++)
            os << layer.output[i][j] << " ";
        os << endl;
    }

    os << "\nDelta: " << endl;
    for (int i = 0; i < layer.delta.size(); i++)
    {
        for (int j = 0; j < layer.delta[0].size(); j++)
            os << layer.delta[i][j] << " ";
        os << endl;
    }

    return os;
}