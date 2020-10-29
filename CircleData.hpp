#pragma once

#include "CDataset.hpp"

class CircleData : public CDataset
{
protected:
    double xDist = 5;
    double yDist = 1;

public:
    double CreateXPoint(double x1, double rc);
    double CreateYPoint(double y1, double rc);

    void SetXDist(double _xDist) { xDist = _xDist; }
    void SetyDist(double _yDist) { yDist = _yDist; }

    virtual void CreateData(int points, int classes);
};