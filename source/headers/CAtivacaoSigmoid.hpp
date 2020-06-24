#pragma once

#include "CAtivacao.hpp"
#include "Matriz.hpp"

#include <cmath>

class CAtivacaoSigmoid : public CAtivacao
{
public:
    //Construtor
    CAtivacaoSigmoid() = default;
    //Destrutor
    ~CAtivacaoSigmoid() = default;
    //Funcao Sigmoid
    virtual double f(double _x) override;
    //Derivada da Funcao Sigmoid
    virtual double df(double _x) override;
};
