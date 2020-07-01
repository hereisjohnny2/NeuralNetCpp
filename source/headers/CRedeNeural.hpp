#pragma once
#include <vector>
#include <tuple>
#include "Matriz.hpp"

class CRedeNeural
{
private:
    int mEpocas {10};
    int mTamMiniBatch {10};
    double mEta {1.0};

    int mNumCamadas;

    std::vector<Matriz> mPesos;
    std::vector<Matriz> mBiases;

public:
    //Construtores
    CRedeNeural();
    CRedeNeural(int epocas, int tamMiniBatch, double eta, int numCamadas, int* tamCamadas);

    //Destrutores
    ~CRedeNeural() = default;

    //Getters
    int GetEpocas();
    int GetTamMiniBatch();
    int GetEta();
    std::vector<Matriz> GetPesos() const;
    std::vector<Matriz> GetBiases() const;

    //Setters
    void SetEpocas(int epocas);
    void SetTamanhoMiniBatch(int tamMiniBatch);
    void SetEta(double eta);

    // Funções de Atulização da Rede
    Matriz Feedforward(Matriz input);
    void SGD(Matriz X, Matriz y, Matriz XTest, Matriz yTest);
    void AtualizaMiniBatch(Matriz X, Matriz Y);
    std::tuple<std::vector<Matriz>, std::vector<Matriz>> Backpropagation(Matriz x, Matriz y);

    // Funções de Ativação
    Matriz Sigmoid(Matriz z);
    Matriz SigmoidPrime(Matriz z);
    Matriz ReLU(Matriz z);
    Matriz ReLUPrime(Matriz z);

    // Função de Avalição
    double AvaliarDesempenho(Matriz XTest, Matriz YTest);
};

