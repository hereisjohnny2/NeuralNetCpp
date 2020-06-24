#include <iostream>

#include "headers/CCamadaDensa.hpp"
#include "headers/SpiralData.hpp"
#include "headers/CAtivacaoReLU.hpp"
#include "headers/CRedeNeural.hpp"

using std::vector;

int main()
{

    const int pontos {20}, classes {3};

    SpiralData Data = SpiralData(pontos, classes);
    Data.CriarDados();

    CAtivacaoReLU ativacao;
    CCamadaDensa camada1(2,4, &ativacao);
    CCamadaDensa camada2(4,3, &ativacao);

    vector<CCamadaDensa> camadas {
        camada1,
        camada2
    };

    CRedeNeural redeNeural(camadas, 1, 10, 0.25);
    redeNeural.SGD(Data.GetX(), Data.GetYVec());
    
    return 0;
}