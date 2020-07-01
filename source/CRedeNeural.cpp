#include "headers/CRedeNeural.hpp"
#include <cmath>

// Construtores

CRedeNeural::CRedeNeural(int epocas, int tamMiniBatch, double eta, int numCamadas, int* tamCamadas)
    : mEpocas(epocas), mTamMiniBatch(tamMiniBatch), mEta(eta), mNumCamadas(numCamadas)
{
    std::cout << "Número de Camadas: " << mNumCamadas << "\n" << std::endl;
    for (int i = 0; i < mNumCamadas - 1; i++)
    {
        // A icialização dos pesos se da lihando o j-ésimo neuronio da camada i + 1
        // como k-ésimo neurônio da camada i. Isso resulta em um set de mNumCamadas - 1 
        // de pesos para a matriz. A notação adota é W(j,k).
        Matriz pesosCamada(tamCamadas[i+1], tamCamadas[i]);
        pesosCamada.RandNormal();
        mPesos.push_back(pesosCamada);

        // Como convensão, a primeira camada representa o input de dados,
        // logo esta não possui biases
        Matriz biasesCamada(tamCamadas[i + 1], 1);
        biasesCamada.RandNormal();
        mBiases.push_back(biasesCamada);
    }
}

//Getters

int CRedeNeural::GetEpocas() {
    return mEpocas;
}

int CRedeNeural::GetTamMiniBatch() {
    return mTamMiniBatch;
}

int CRedeNeural::GetEta() {
    return mEta;
}

std::vector<Matriz> CRedeNeural::GetPesos() const {
    return mPesos;
}

std::vector<Matriz> CRedeNeural::GetBiases() const {
    return mBiases;
}

// Setters

void CRedeNeural::SetEpocas(int epocas){
    mEpocas = epocas;
}

void CRedeNeural::SetTamanhoMiniBatch(int tamMiniBatch){
    mTamMiniBatch = tamMiniBatch;    
}

void CRedeNeural::SetEta(double eta){
    mEta = eta;    
}

// Funções de Atulização da Rede

Matriz CRedeNeural::Feedforward(Matriz input) {
    std::vector<Matriz> saidas;

    Matriz saida = Matriz(mBiases[0]);
    saida = mPesos[0] * input + mBiases[0];
    saida = Sigmoid(saida);
    saidas.push_back(saida);

    for (int i = 1; i < mNumCamadas - 1; i++)
    {
        Matriz saida = Matriz(mBiases[i]);
        saida = mPesos[i] * saidas.back() + mBiases[i];
        saida = Sigmoid(saida);
        saidas.push_back(saida);
    }
    return saidas.back();   
}

void CRedeNeural::SGD(Matriz X, Matriz y, Matriz XTest, Matriz yTest) {
    
    int n = X.GetNumLinhas();
    
    for (int epoca = 0; epoca < mEpocas; epoca++)
    {

        std::vector<Matriz> miniBatchX;
        std::vector<Matriz> miniBatchY;

        for (int i = 0; i < n; i+=mTamMiniBatch)
        {
            Matriz XTemp = Matriz(mTamMiniBatch, X.GetNumColunas());
            Matriz YTemp = Matriz(mTamMiniBatch, y.GetNumColunas());
            int linhaTemp = 0;
            for (int k = i; k < i + mTamMiniBatch; k++)
            {
                for (int j = 0; j < X.GetNumColunas(); j++)
                {
                    XTemp[linhaTemp][j] = X[k][j];
                }
                for (int j = 0; j < y.GetNumColunas(); j++)
                {
                    YTemp[linhaTemp][j] = y[k][j];
                }
                linhaTemp++;
            }
            miniBatchX.push_back(XTemp);
            miniBatchY.push_back(YTemp);
        }

        int numMiniBatchs = miniBatchX.size();
        for (int i = 0; i < numMiniBatchs; i++)
        {
            AtualizaMiniBatch(miniBatchX[i], miniBatchY[i]);
        }

        //std::cout << "Epoca " << epoca + 1 << ": " << AvaliarDesempenho(XTest, yTest) << "/" << XTest.GetNumLinhas() << std::endl;   
        std::cout << "Época " << epoca + 1 << "/" << mEpocas << " completa!" << std::endl;      
    }
    std::cout << "Resultado: " << AvaliarDesempenho(XTest, yTest) << "/" << XTest.GetNumLinhas() << std::endl;
}

void CRedeNeural::AtualizaMiniBatch(Matriz X, Matriz Y) {
    
    std::vector<Matriz> nablaBiases;
    std::vector<Matriz> nablaPesos;

    for (auto biases : mBiases) {
        Matriz temp = Matriz(biases);
        temp.Zeros();
        nablaBiases.push_back(temp);
    }

    for (auto peso : mPesos) {
        Matriz temp = Matriz(peso);
        temp.Zeros();
        nablaPesos.push_back(temp);
    }

    std::vector<Matriz> deltaNablaBiases;
    std::vector<Matriz> deltaNablaPesos;
    for (int i = 0; i < mTamMiniBatch; i++)
    {
        Matriz x = Matriz(X.GetNumColunas(), 1);
        Matriz y = Matriz(Y.GetNumColunas(), 1);

        for (int j = 0; j < X.GetNumColunas(); j++)
        {
            x[j][0] = X[i][j];
        }
        for (int j = 0; j < Y.GetNumColunas(); j++)
        {
            y[j][0] = Y[i][j];
        }  
        
        std::tie(deltaNablaBiases, deltaNablaPesos) = Backpropagation(x,y);

        for (int k = 0; k < mNumCamadas - 1; k++)
        {
            nablaPesos[k] += deltaNablaPesos[k];
            nablaBiases[k] += deltaNablaBiases[k];
        }  
    }
    
    for (int i = 0; i < mNumCamadas - 1; i++)
    {
        mPesos[i] -= nablaPesos[i] * (mEta/mTamMiniBatch);
        mBiases[i] -= nablaBiases[i] * (mEta/mTamMiniBatch);
    }   
}

std::tuple<std::vector<Matriz>, std::vector<Matriz>> CRedeNeural::Backpropagation(Matriz x, Matriz y) {
    
    std::vector<Matriz> nablaBiases;
    std::vector<Matriz> nablaPesos;

    for (auto biases : mBiases) {
        Matriz temp = Matriz(biases);
        temp.Zeros();
        nablaBiases.push_back(temp);
    }

    for (auto peso : mPesos) {
        Matriz temp = Matriz(peso);
        temp.Zeros();
        nablaPesos.push_back(temp);
    }

    std::vector<Matriz> activacoes;
    std::vector<Matriz> zs;

    activacoes.push_back(x);

    Matriz saida = Matriz(mBiases[0]);
    saida = mPesos[0] * activacoes.back() + mBiases[0];
    zs.push_back(saida);
    activacoes.push_back(Sigmoid(saida));

    for (int i = 1; i < mNumCamadas - 1; i++)
    {
        Matriz saida = Matriz(mBiases[i]);
        saida = mPesos[i] * activacoes.back() + mBiases[i];
        zs.push_back(saida);
        activacoes.push_back(Sigmoid(saida));
    }    

    Matriz delta = Matriz(nablaBiases.back());
    delta = (activacoes.back() - y);
    delta = delta.Hardmard(SigmoidPrime(zs.back()));

    nablaBiases.back() = delta;
    nablaPesos.back() = delta * activacoes[mNumCamadas - 2].CalculaTransposta();

    for (int i = mNumCamadas - 2; i > 0; i--)
    {

        Matriz z = Matriz(zs[i-1]);
        Matriz delta = Matriz(nablaBiases[i-1]);

        delta = mPesos[i].CalculaTransposta() * nablaBiases[i];
        delta.Hardmard(SigmoidPrime(z));

        nablaBiases[i-1] = delta;
        nablaPesos[i-1] = delta * activacoes[i-1].CalculaTransposta();
        
    }
    
    return std::make_tuple(nablaBiases, nablaPesos);
}

//Funcções de Ativação

Matriz CRedeNeural::Sigmoid(Matriz z) {
    Matriz saida(z);
    for (int i = 0; i < saida.GetNumLinhas(); i++)
    {
        for (int j = 0; j < saida.GetNumColunas(); j++)
        {
            saida[i][j] = 1.0/(1.0 + exp(-saida[i][j]));
        }
    }
    return saida;
}

Matriz CRedeNeural::SigmoidPrime(Matriz z) {
    Matriz saida(z);
    for (int i = 0; i < saida.GetNumLinhas(); i++)
    {
        for (int j = 0; j < saida.GetNumColunas(); j++)
        {
            saida[i][j] = exp(-saida[i][j]) / pow((1.0 + exp(-saida[i][j])), 2);
        }
    }
    return saida;
}

Matriz CRedeNeural::ReLU(Matriz z) {
    Matriz saida(z);
    for (int i = 0; i < saida.GetNumLinhas(); i++)
    {
        for (int j = 0; j < saida.GetNumColunas(); j++)
        {
            saida[i][j] = (saida[i][j] > 0) ? saida[i][j] : 0.0;
        }
    }
    return saida;
}

Matriz CRedeNeural::ReLUPrime(Matriz z) {
    Matriz saida(z);
    for (int i = 0; i < saida.GetNumLinhas(); i++)
    {
        for (int j = 0; j < saida.GetNumColunas(); j++)
        {
            saida[i][j] = (saida[i][j] > 0) ? 1.0 : 0.0;
        }
    }
    return saida;
}


double CRedeNeural::AvaliarDesempenho(Matriz XTest, Matriz YTest) {
    int soma = 0;

    for (int i = 0; i < XTest.GetNumLinhas(); i++)
    {
        Matriz input = Matriz(XTest.GetNumColunas(), 1);
        for (int j = 0; j < XTest.GetNumColunas(); j++)
        {
            input[j][0] = XTest[i][j];
        }  

        Matriz saida = Matriz(Feedforward(input));
        int MaiorIndice = saida.GetLinhaMaiorElemento();

        // std::cout << saida.CalculaTransposta() << std::endl;
        // std::cout << MaiorIndice << " -> " << YTest[0][i] << std::endl;

        if (MaiorIndice == YTest[0][i])
        {
            soma++;
        }
    }
    return soma;
}