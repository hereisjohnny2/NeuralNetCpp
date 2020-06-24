#pragma once

#include "CCamadaDensa.hpp"
#include <vector>

class CRedeNeural
{
private:
    int mNumCamadas;
    std::vector<CCamadaDensa> mCamadas;

    int mEpocas {10};
    int mTamMiniBatch {10};
    double mEta {1.0};


public:
    //Construtores
    CRedeNeural();
    CRedeNeural(std::vector<CCamadaDensa> _camadas, int _epocas, int _tamMiniBatch, double _eta);
    //Destrutores
    ~CRedeNeural() = default;

    //Setters
    void SetEpocas(int _epocas);
    void SetTamMiniBatch(int _tamMiniBatch);
    void SetEta(int _eta);

    void AdicionarCamada(const CCamadaDensa& _novaCamada);

    //Aplica o algoritimo de feedforward em cada uma das camadas da rede
    Matriz FeedForward(const Matriz& input);

    //Aplica o algoritimo do Gradiente Estocástico Descendente (Stocastic Gradient Descendent)
    void SGD(const Matriz& X, const Matriz& y);
};

