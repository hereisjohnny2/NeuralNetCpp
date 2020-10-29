#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "CActivation.hpp"

class CLayer;

class CNetwork
{
private:
    std::vector<std::vector<double>> output;
    std::vector<CLayer> layers;
    std::vector<CActivation *> activations;

public:
    CNetwork(std::vector<CLayer> &_layers, std::vector<CActivation *> _activations) : layers(_layers), activations(_activations) {}
    ~CNetwork() = default;

    std::vector<std::vector<double>> Forward(std::vector<std::vector<double>> X);
    std::vector<std::vector<double>> operator()(std::vector<std::vector<double>> X) { return Forward(X); }

    void Backpropagate(std::vector<std::vector<double>> loss);
    void UpdateParams(double lr, const std::vector<std::vector<double>> &X);

    friend std::ostream &operator<<(std::ostream &os, const CNetwork &net);
};
