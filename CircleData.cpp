#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>

#include "CircleData.hpp"
#include "LinAlg.hpp"

using namespace std;

double CircleData::CreateXPoint(double x1, double rc)
{
    double a = 2 * M_PI * LinAlg::GetRandomDouble();
    double r = LinAlg::GetRandomDouble();
    return r * rc * cos(a) + x1;
}

double CircleData::CreateYPoint(double y1, double rc)
{
    double a = 2 * M_PI * LinAlg::GetRandomDouble();
    double r = LinAlg::GetRandomDouble();
    return r * rc * sin(a) + y1;
}

void CircleData::CreateData(int points, int classes)
{
    CDataset::plotName = "CircleData";

    X = vector<vector<double>>(points * classes, vector<double>(2, 0.0));
    y = vector<vector<double>>(points * classes, vector<double>(classes, 0.0));

    for (int class_number = 0; class_number < classes; class_number++)
    {
        // range function on python
        vector<double> ix(points * (class_number + 1) - points * class_number, 0);
        for (int i = 0; i < ix.size(); i++)
            ix[i] = double(points * class_number + i);

        for (auto i : ix)
        {
            X[i][0] = CreateXPoint(1 + xDist * class_number, 1);
            X[i][1] = CreateYPoint(1 - yDist * class_number, 1);
            y[i][class_number] = 1.0;
        }
    }
}