#pragma once
#include "Matriz.hpp"
#include "CAtivacao.hpp"

/*
Cria uma função de ativação ReLU (unidade linear retificada).

Atributos:
    - saida: Matriz que armazena os arquivos de saida da função.

Métodos:
    - GetSaida(): Retorna a saida da função.
    - Forward(): Recebe uma matriz de entrada e aplica nela a função retificadora.
*/
class CAtivacaoReLU : public CAtivacao
{
public:
    CAtivacaoReLU() = default;
    ~CAtivacaoReLU() = default;
    //Funcao Sigmoid
    virtual double f(double _x) override;
    //Derivada da Funcao Sigmoid
    virtual double df(double _x) override;
};