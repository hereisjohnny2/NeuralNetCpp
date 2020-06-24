#include "headers/CAtivacao.hpp"

void CAtivacao::Forward(const Matriz& _inputs) {
    saida.SetNumLinhas(_inputs.GetNumLinhas());
    saida.SetNumColunas(_inputs.GetNumColunas());
    saida = _inputs;
    for (int i = 0; i < saida.GetNumLinhas(); i++)
    {   
        for (int j = 0; j < saida.GetNumColunas(); j++)
        {
            saida[i][j] = f(saida[i][j]);
        } 
    }
}

Matriz CAtivacao::DF(const Matriz& _input) {
    Matriz saidaDf(_input);
    for (int i = 0; i < saida.GetNumLinhas(); i++)
    {   
        for (int j = 0; j < saida.GetNumColunas(); j++)
        {
            saidaDf[i][j] = df(saidaDf[i][j]);       
        } 
    }
    return saidaDf;
}