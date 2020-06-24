#include "headers/CRedeNeural.hpp"

using std::vector;

CRedeNeural::CRedeNeural(vector<CCamadaDensa> _camadas, int _epocas, int _tamMiniBatch, double _eta) 
    : mNumCamadas(_camadas.size()), mCamadas(_camadas), mEpocas(_epocas), mTamMiniBatch(_tamMiniBatch), mEta(_eta) {}

void CRedeNeural::SetEpocas(int _epocas) {
    mEpocas = _epocas;
}

void CRedeNeural::SetTamMiniBatch(int _tamMiniBatch) {
    mTamMiniBatch = _tamMiniBatch;
}

void CRedeNeural::SetEta(int _eta) {
    mEta = _eta;
}

void CRedeNeural::AdicionarCamada(const CCamadaDensa& _novaCamada) {
    mCamadas.push_back(_novaCamada);
    mNumCamadas++;
}

Matriz CRedeNeural::FeedForward(const Matriz& input) {
    mCamadas[0].Forward(input);
    for (int i = 1; i < mNumCamadas; i++)
    {
        mCamadas[i].Forward(mCamadas[i-1].GetSaida());
    }
    return mCamadas[mNumCamadas - 1].GetSaida();
}

void CRedeNeural::SGD(const Matriz& X, const Matriz& y) 
{
    Matriz XShuffle(X);
    Matriz yShuffle(y);

    int n = y.GetNumLinhas();
    int numMiniBatches = n/mTamMiniBatch;

    std::cout << "Número de épocas: " << mEpocas << std::endl;
    std::cout << "Tamanho de cada mini-batch: " << mTamMiniBatch << std::endl;
    std::cout << "Número de mini-batches: " << numMiniBatches << std::endl;
    std::cout << "Taxa de aprendizagem: " << mEta << std::endl;
    std::cout << std::endl;

    for (int j = 1; j <= mEpocas; j++)
    {
        XShuffle = XShuffle.Shuffle();
        yShuffle = yShuffle.Shuffle();

        std::vector<Matriz> mini_batchX;
        std::vector<Matriz> mini_batchY;

        for (int k = 0; k < n; k+=mTamMiniBatch)
        {
            Matriz x_temp(mTamMiniBatch, X.GetNumColunas());
            Matriz y_temp(mTamMiniBatch, y.GetNumColunas());

            for (int i = 0; i < mTamMiniBatch; i++)
            {
                for (int a = 0; a < X.GetNumColunas(); a++)
                {
                    x_temp[i][a] = XShuffle[i+k][a];
                }
                for (int a = 0; a < y.GetNumColunas(); a++)
                {
                    y_temp[i][a] = yShuffle[i+k][a];
                }                              
            }  
            mini_batchX.push_back(x_temp);
            mini_batchY.push_back(y_temp);
        }

        Matriz Erro(mTamMiniBatch, y.GetNumColunas());
        for (int i = 0; i < numMiniBatches; i++)
        {
            for (int l = mNumCamadas; l > 0; l--)
            {
                Erro = (FeedForward(mini_batchX[i]) - mini_batchY[i]);
                Erro = Erro.Hardmard(mCamadas[l - 1].DSigmaZ());
            }
        }

       std::cout << "Epoca " << j << "/" << mEpocas << " concluída." << std::endl;
    }
}



