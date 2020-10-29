#pragma once

#include "CDataset.hpp"

class SpiralData : public CDataset
{
public:
    SpiralData() = default;
    ~SpiralData() = default;

    virtual void CreateData(int points, int classes);
};