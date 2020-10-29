#pragma once

#include <iostream>
#include <vector>

class CLoss
{
private:
    double loss{0.0};
    std::vector<std::vector<double>> output;

public:
    CLoss() = default;
    ~CLoss() = default;

    double CostFunction(double a, double y);
    double CostPrime(double a, double y);

    double GetLoss() { return loss; }

    std::vector<std::vector<double>> CalculateCost(std::vector<std::vector<double>> X, std::vector<std::vector<double>> y);
    std::vector<std::vector<double>> operator()(std::vector<std::vector<double>> X, std::vector<std::vector<double>> y) { return CalculateCost(X, y); };

    friend std::ostream &operator<<(std::ostream &os, const CLoss &loss);
};
