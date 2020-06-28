#include "headers/CCamadaDensa.hpp"

CCamadaDensa::CCamadaDensa(int _numInputs, int _numNeuronios, CAtivacao* _ativacao) 
    : numInputs(_numInputs), numNeuronios(_numNeuronios), ativacao(_ativacao)
{
    biases.Zeros(); 
    pesos.RandNormal(); 
    pesos = pesos*0.01;
}

int CCamadaDensa::GetNumInputs() {
    return numInputs;
}

int CCamadaDensa::GetNumNeuronios() {
    return numNeuronios;
}

Matriz CCamadaDensa::GetZ() {
    return saida;
}

Matriz CCamadaDensa::GetSaida() {
    return saida;
}

Matriz CCamadaDensa::GetPesos() {
    return pesos;
}

Matriz CCamadaDensa::GetBiases() {
    return biases;
}

Matriz CCamadaDensa::DSigmaZ() {
    return ativacao->DF(z);
}

void CCamadaDensa::UpdatePesos(const Matriz& _pesos) {
    pesos = _pesos;
}

void CCamadaDensa::UpdateBiases(const Matriz& _biases) {
    biases = _biases;
}
    
void CCamadaDensa::Forward(const Matriz& _inputs) {
    z.SetNumLinhas(_inputs.GetNumLinhas());
    saida.SetNumLinhas(_inputs.GetNumLinhas());
    
    Matriz inputs(_inputs);

    z = inputs*pesos;
    
    for (int i = 0; i < saida.GetNumLinhas(); i++)
    {
        for (int  j = 0; j < saida.GetNumColunas(); j++)
        {
            z[i][j] += biases[0][j];
        }        
    }    
    ativacao->Forward(z);
    saida = ativacao->GetSaida();
}