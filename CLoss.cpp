#include <cassert>

#include "CLoss.hpp"

using namespace std;

vector<vector<double>> CLoss::CalculateCost(vector<vector<double>> yPred, vector<vector<double>> y)
{
    output = yPred;
    loss = 0.0;
    for (int i = 0; i < yPred.size(); i++)
    {
        double cxLoss = 0.0; // Single training element cost
        for (int j = 0; j < yPred[0].size(); j++)
        {
            output[i][j] = CostPrime(yPred[i][j], y[i][j]);
            cxLoss += CostFunction(yPred[i][j], y[j][j]);
        }
        loss += (cxLoss / 2.0);
    }

    loss /= yPred.size();

    return output;
}

double CLoss::CostFunction(double a, double y)
{
    return ((y - a) * (y - a));
}

double CLoss::CostPrime(double a, double y)
{
    return (a - y);
}

std::ostream &operator<<(std::ostream &os, const CLoss &loss)
{
    for (int i = 0; i < loss.output.size(); i++)
    {
        for (int j = 0; j < loss.output[0].size(); j++)
            os << loss.output[i][j] << " ";
        os << std::endl;
    }
    return os;
}
