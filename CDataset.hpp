#pragma once
#include <vector>
#include "CGnuplot.h"

class CDataset
{
protected:
    std::vector<std::vector<double>> X;
    std::vector<std::vector<double>> y;
    Gnuplot plot;

    std::string plotName;

public:
    CDataset() = default;
    ~CDataset() = default;

    std::vector<std::vector<double>> GetX() { return X; }
    std::vector<std::vector<double>> GetY() { return y; }

    virtual void CreateData(int points, int classes) = 0;
    void Plot();

    void ShuffleData();
};
