#pragma once
#include "CAtivacao.hpp"

/*
Camada densa de uma rede neural que recebe como construtor o numero de inputs da camada anterior ou dos dados de entrada, e o numero de neurônios.

Atributos:
    - numInputs: numero de entradas da camada anterior ou dos dados de entrada.
    - numNeuronios: numero de neuronios da camada.
    - biases: Vetor que armazena os vieses (biases) de cada neuronio da camada.
    - pesos: Matriz que armanas os pesos (weights) de cada neuronio da camada. 
    - saida: Matriz que armazena as saidas de cada neurônio da camada.

Métodos:
    CCamadaDensa(int _numInputs, int _numNeuronios): Constroi uma nava camada com base no numero de entradas e saidas.
    ~CCamadaDensa(): Invoca o destrutor padrão.
    GetSaida(): Retorna as saidas da camada.
    Forward(const Matriz& _inputs): Realiza o processo de multiplicação das entradas pelos pesos e soma o resultado aos vieses. f(x) = X.W + b
*/

class CCamadaDensa
{
private:
    int numInputs {1}, numNeuronios {1};
    Matriz biases = Matriz(1, numNeuronios);
    Matriz z = Matriz(1, numNeuronios);
    Matriz saida = Matriz(1, numNeuronios);
    Matriz pesos = Matriz(numInputs, numNeuronios);
    CAtivacao* ativacao;

public:
    //Construtor
    CCamadaDensa(int _numInputs, int _numNeuronios, CAtivacao* _ativacao);
    //Destrutor
    ~CCamadaDensa() = default;

    //Getters
    Matriz GetZ();
    Matriz GetSaida();
    Matriz GetPesos();
    Matriz GetBiases();
    Matriz DSigmaZ();
    
    //Setters
    void UpdatePesos(const Matriz& _pesos);
    void UpdateBiases(const Matriz& _biases);

    //Funçao FeedForard
    void Forward(const Matriz& _inputs);
};
