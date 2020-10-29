#include "CActivation.hpp"

using namespace std;

std::vector<std::vector<double>> CActivation::Forward(std::vector<std::vector<double>> X)
{
    output = X;
    for (int i = 0; i < X.size(); i++)
        for (int j = 0; j < X[0].size(); j++)
            output[i][j] = F(X[i][j]);
    return output;
}

std::vector<std::vector<double>> CActivation::ForwardPrime(std::vector<std::vector<double>> X)
{
    outputPrime = X;
    for (int i = 0; i < X.size(); i++)
        for (int j = 0; j < X[0].size(); j++)
            outputPrime[i][j] = dF(X[i][j]);
    return outputPrime;
}

std::ostream &operator<<(std::ostream &os, const CActivation &act)
{
    for (int i = 0; i < act.output.size(); i++)
    {
        for (int j = 0; j < act.output[0].size(); j++)
            os << act.output[i][j] << " ";
        os << std::endl;
    }
    return os;
}
