#pragma once

#include "CActivation.hpp"

class CActReLU : public CActivation
{
public:
    CActReLU() = default;
    ~CActReLU() = default;

    virtual double F(double value) { return (value > 0.0) ? value : 0.0; }
    virtual double dF(double value) { return (value > 0.0) ? 1.0 : 0.0; }
};