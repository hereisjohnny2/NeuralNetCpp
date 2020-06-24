#include <cmath>
#include "headers/SpiralData.hpp"

/*
Aplica ao atributo X dados na forma de um espiral ao longo dos eixos x e y, e ao atributo y o numero da classe de um determinado ponto. 
Mais informações em: https://cs231n.github.io/neural-networks-case-study/.

*/

SpiralData::SpiralData(int _pontos, int _classes) 
    : pontos(_pontos), classes(_classes) 
{
    X.Zeros();
    yVec.Zeros();
    y.Zeros();
}

void SpiralData::CriarDados() {
    
    for (int num_classe = 0; num_classe < classes; num_classe++)
    {
        Vetor r(0,1,pontos);
        Vetor t(num_classe*4, (num_classe + 1)*4, pontos);
        Vetor randVet(pontos);
        randVet.RandNormal();
        t += randVet * 0.2;
        
        for (int i = 0; i < pontos; i++)
        {
            X[i + pontos*num_classe][0] = r[i]*sin(t[i] * 2.5);
            X[i + pontos*num_classe][1] = r[i]*cos(t[i] * 2.5);
            y[0][i + pontos*num_classe] = num_classe;
            for (int j = 0; j < classes; j++)
            {
                yVec[i + pontos*num_classe][j] = num_classe == j ? 1.0 : 0.0;
            }   
        }
    }
} 