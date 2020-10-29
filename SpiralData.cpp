// def spiral_data(points, classes):
//     X = np.zeros((points*classes, 2))
//     y = np.zeros(points*classes, dtype='uint8')
//     for class_number in range(classes):
//         ix = range(points*class_number, points*(class_number+1))
//         r = np.linspace(0.0, 1, points)  # radius
//         t = np.linspace(class_number*4, (class_number+1)*4, points) + np.random.randn(points)*0.2
//         X[ix] = np.c_[r*np.sin(t*2.5), r*np.cos(t*2.5)]
//         y[ix] = class_number
//     return X, y

#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>

#include "SpiralData.hpp"
#include "LinAlg.hpp"

using namespace std;

void SpiralData::CreateData(int points, int classes)
{
    CDataset::plotName = "SpiralData";

    X = vector<vector<double>>(points * classes, vector<double>(2, 0.0));
    y = vector<vector<double>>(points * classes, vector<double>(classes, 0.0));

    for (int class_number = 0; class_number < classes; class_number++)
    {
        // range function on python
        vector<double> ix(points * (class_number + 1) - points * class_number, 0);
        for (int i = 0; i < ix.size(); i++)
            ix[i] = double(points * class_number + i);

        vector<double> ixTest(points * (class_number + 1) - points * class_number, 0);
        for (int i = 0; i < ix.size(); i++)
            ix[i] = double(points * class_number + i);

        // np.linspace on python
        vector<double> r(points, 0.0);
        for (int i = 1; i < r.size(); i++)
            r[i] = r[i - 1] + (1.0 / double(points - 1));

        // np.linspace on python
        vector<double> t(points, class_number * 4);
        for (int i = 1; i < t.size(); i++)
            t[i] = (t[i - 1] + (4.0 / double(points - 1))) + 0.2 * LinAlg::GetRandomDouble();

        for (auto i : ix)
        {
            X[i][0] = r[i - class_number * points] * sin(t[i - class_number * points] * 2.5);
            X[i][1] = r[i - class_number * points] * cos(t[i - class_number * points] * 2.5);
            y[i][class_number] = 1.0;
        }
    }
}
