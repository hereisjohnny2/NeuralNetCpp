#pragma once
#include <vector>

class CLayer
{
private:
    std::vector<std::vector<double>> weights;
    std::vector<std::vector<double>> biases;
    std::vector<std::vector<double>> output;

    std::vector<std::vector<double>> delta;

public:
    CLayer(int inputs, int neurons);
    ~CLayer() = default;

    std::vector<std::vector<double>> Forward(std::vector<std::vector<double>> X);

    std::vector<std::vector<double>> operator()(std::vector<std::vector<double>> X) { return Forward(X); }
    void operator()(std::vector<std::vector<double>> _weights, std::vector<std::vector<double>> _biases)
    {
        weights = _weights;
        biases = _biases;
    }

    friend std::ostream &operator<<(std::ostream &os, const CLayer &layer);
    friend class CNetwork;
};
