#pragma once
#include "Matriz.hpp"

/*
Cria uma função de ativação ReLU (unidade linear retificada).

Atributos:
    - saida: Matriz que armazena os arquivos de saida da função.

Métodos:
    - GetSaida(): Retorna a saida da função.
    - Forward(): Recebe uma matriz de entrada e aplica nela a função retificadora.
*/

class CAtivacao
{
protected:
    Matriz saida;
public:
    //Construtor
    CAtivacao() = default;
    //Destrutor
    ~CAtivacao() = default;

    //Getters
    Matriz GetSaida() const {return saida;};

    //Funcao
    virtual double f(double _x) = 0;
    //Derivada da Funcao
    virtual double df(double _x) = 0;
    //Executa FeedForward
    virtual void Forward(const Matriz& _input);
    //Executa a derivada da função para todos os elementos de uma matriz de entrada
    virtual Matriz DF(const Matriz& _input);
};