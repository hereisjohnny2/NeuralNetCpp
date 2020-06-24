#include "headers/CAtivacaoSigmoid.hpp"

double CAtivacaoSigmoid::f(double _x) {
    return 1.0 / (1.0 + exp(-1.0*_x));
}

double CAtivacaoSigmoid::df(double _x) {
    return f(_x) * (1.0 + f(_x));
}
