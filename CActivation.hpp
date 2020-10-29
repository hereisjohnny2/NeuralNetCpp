#pragma once

#include <vector>
#include <iostream>

class CActivation
{
protected:
    std::vector<std::vector<double>> output;
    std::vector<std::vector<double>> outputPrime;

public:
    CActivation() = default;
    ~CActivation() = default;

    virtual double F(double value) = 0;
    virtual double dF(double value) = 0;

    std::vector<std::vector<double>> Forward(std::vector<std::vector<double>> X);
    std::vector<std::vector<double>> ForwardPrime(std::vector<std::vector<double>> X);

    std::vector<std::vector<double>> operator()(std::vector<std::vector<double>> X) { return Forward(X); };
    friend std::ostream &operator<<(std::ostream &os, const CActivation &act);

    friend class CNetwork;
};
