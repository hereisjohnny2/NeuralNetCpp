#include <iostream>
#include <cassert>
#include <cmath>
#include <random>
#include <iomanip>
#include <algorithm>

#include "headers/Matriz.hpp"

//Construtor para uma matriz que não rebece nenhum parametro de entrada. Dessa forma ela aloca memória para uma matriz 3x3, com todos os elementos iguais a zero.
Matriz::Matriz() {
    mColunas = 3;
    mLinhas = 3;
    mData = new double* [mLinhas];
    for (int i = 0; i < mLinhas; i++)
    {
        mData[i] = new double [mColunas];
    }    
}

//Construtor de Cópia que recebe um segunda matriz e aloca memória de acordo com o numero de linhas e colunas dessa matriz.
Matriz::Matriz(const Matriz& outraMatriz) {
    mLinhas = outraMatriz.GetNumLinhas();
    mColunas = outraMatriz.GetNumColunas();
    mData = new double* [mLinhas];
    for (int i = 0; i < mLinhas; i++)
    {
        mData[i] = new double[mColunas];
    }
    for (int i = 0; i < mLinhas; i++)
    {
        for (int j = 0; j < mColunas; j++)
        {
            mData[i][j] = outraMatriz.mData[i][j];
        }
    }
}

//Construtor para uma matriz quadrada (NxN), alocando memória para uma matriz de ordem N, tal que N é o número de elementos (n_elementos).
Matriz::Matriz(int n_elementos) {
    assert(n_elementos > 0);
    mColunas = n_elementos;
    mLinhas = n_elementos;
    mData = new double* [mLinhas];
    for (int i = 0; i < mLinhas; i++)
    {
        mData[i] = new double [mColunas];
    }
}

//Construtor que recebe o número de colunas (n_colunas) e o número de linhas (n_linhas) da matriz e aloca memória com base nesses valores.
Matriz::Matriz(int n_linhas, int n_colunas) {
    assert(n_linhas > 0 && n_colunas > 0);
    mColunas = n_colunas;
    mLinhas = n_linhas;
    mData = new double* [mLinhas];
    for (int i = 0; i < mLinhas; i++)
    {
        mData[i] = new double [mColunas];
    }
}

//Sobrescreve o destrutor do objeto, de modo que a memória seja devidamente desalocada;
Matriz::~Matriz() {
    for (int i = 0; i < mLinhas; i++)
    {
        delete[] mData[i];
    }
    delete[] mData;
}

//Retorna o numero de linhas da matriz
int Matriz::GetNumLinhas() const {
    return mLinhas;
}

//Retorna o numero de colunas da matriz
int Matriz::GetNumColunas() const {
    return mColunas;
}

//Define o numero de linhas para a matriz, deletando a informação anterior e realocando memória com os novos parâmetros.
void Matriz::SetNumLinhas(int _Linhas) {
    for (int i = 0; i < mLinhas; i++)
    {
        delete[] mData[i];
    }
    delete[] mData;
    mLinhas = _Linhas;
    mData = new double* [mLinhas];
    for (int i = 0; i < mLinhas; i++)
    {
        mData[i] = new double [mColunas];
    }
    
}

//Define o numero de colunas para a matriz, deletando a informação anterior e realocando memória com os novos parâmetros.
void Matriz::SetNumColunas(int _Colunas) {
    for (int i = 0; i < mLinhas; i++)
    {
        delete[] mData[i];
    }
    delete[] mData;
    mColunas = _Colunas;
    mData = new double* [mLinhas];
    for (int i = 0; i < mLinhas; i++)
    {
        mData[i] = new double [mColunas];
    }
    
}

//Retorna o determinante de uma determinada matriz quadrada A usando o método de Laplace. Se as a matriz for de ordem 1, o valore retornado será o unico elemento que ela possui. 
double Matriz::CalculaDeterminante() {
    assert(mLinhas == mColunas);
    double determinante, soma;
    if (mLinhas == 1) {
        determinante = mData[0][0];
    } 
    else {
        Matriz MatAux(mLinhas-1, mColunas-1);
        soma = 0.0;
        for (int coluna = 0; coluna < mColunas; coluna++) {
            int iAux = 0;
            for (int i = 0; i < mLinhas; i++) {
                if (i != 0) {
                    int jAux = 0;
                    for (int j = 0; j < mColunas; j++) {
                        if (j != coluna) {
                            MatAux.mData[iAux][jAux] = mData[i][j];
                            jAux++;
                        }
                    }
                    iAux++;    
                }
            }         
            soma += (-1.0)*pow(-1.0, coluna)*mData[0][coluna]*MatAux.CalculaDeterminante();    
        }
        determinante = soma;
    }    
    return determinante;  
}

//Atribui o valor 0.0 à todos os elementos da matriz.
void Matriz::Zeros() {
    for (int i = 0; i < mLinhas; i++)
    {
        for (int j = 0; j < mColunas; j++)
        {
            mData[i][j] = 0.0;
        }
    }
}

Matriz Matriz::Shuffle(int seed) {
    std::default_random_engine gerador(seed);
    std::uniform_int_distribution<int> NumRand(0, mLinhas-1);
    Matriz saida(*this);
    for (int i = 0; i < mLinhas; i++)
    {   
        double* vAux = saida.mData[i];
        int num = NumRand(gerador);
        saida.mData[i] = saida.mData[num];
        saida.mData[num] = vAux;
    }
    return saida; 
}

//Atribui um valor randômico de um distribuição uniforme entre um limite superior (limiteSup) e inferior (limiteInf) à todos os elementos da matriz. Os valores padrão para os limites inferior e superior são, respectivamente -1.0 e 1.0.
void Matriz::RandUniforme(double limiteInf, double limiteSup) {
    std::default_random_engine gerador;
    std::uniform_real_distribution<double> NumRand(limiteInf, limiteSup);
    for (int i = 0; i < mLinhas; i++)
    {
        for (int j = 0; j < mColunas; j++)
        {
            mData[i][j] = NumRand(gerador);
        } 
    }
}

//Atribui um valor randômico de um distribuição normal com média 0.0 e desvio padrão 1.0 à todos os elementos da matriz. Os valores da média e dos desvio padrão podem ser alterados passando-se esse elemento como parâmetros do método.
void Matriz::RandNormal(double media, double desvioPadrao) {
    std::default_random_engine gerador;
    std::normal_distribution<double> NumRand(media, desvioPadrao);
    for (int i = 0; i < mLinhas; i++)
    {
        for (int j = 0; j < mColunas; j++)
        {
            mData[i][j] = NumRand(gerador);
        } 
    }
}

//Retorna a transposta de uma matriz.
Matriz Matriz::CalculaTransposta() {
    Matriz Saida(mColunas, mLinhas);
    for (int i = 0; i < mLinhas; i++)
    {
        for (int j = 0; j < mColunas; j++)
        {
            Saida[j][i] = mData[i][j];
        }
    }
    return Saida;
}

//Sobrescreve o método de colchetes. Desse forma é possível acessar o ponteiro que armazena a linha no índice dado (index_linha). Como ponteiros já suportam nativamente o operador de conchetes, para acessar um determinado elemento na possivel i,j, sendo i o numero da linha e j o número da coluna, basta escrever A[i][j]. Note que o acesso ao elemento é baseado no 0, ou seja, o index do primeiro elemento será 0, e o índice do ultimo será N-1, tal que N é o número de linhas.
double* Matriz::operator[](int index_linha) {
    assert(index_linha > -1);
    assert(index_linha < mLinhas);
    return mData[index_linha];
}

//Sobrescreve o operador parenteses. Funciona de maneira semelhante ao operador colchetes, mas nesse caso, o indice do primeiro elemento é 1, e do último elemento é N, tal que N é o numero de colunas ou linhas. É utilizado de maneira semelhante a de um função, de forma que o elemento na posição i,j de uma matriz M é dado por M(i,j).
double& Matriz::operator()(int index_linha, int index_coluna) {
    assert(index_coluna > 0);
    assert(index_coluna < mColunas+1);
    return mData[index_linha][index_coluna];
}

//Sobrescreve o operador de atribuição. As informações de uma matriz é passado para outra desde que elas possuam o memso tamanho.
Matriz& Matriz::operator=(const Matriz& outraMatriz) {
    assert(mLinhas == outraMatriz.mLinhas);
    assert(mColunas == outraMatriz.mColunas);
    for (int i = 0; i < mLinhas; i++)
    {
        for (int j = 0; j < mColunas; j++)
        {
            mData[i][j] = outraMatriz.mData[i][j];
        }
    }
    return *this;
}

//Sobrescreve o operador de atribuição junto adição (+=). As informações de duas matrizes A e B são somadas e atribuidas a matriz A, desde que possuam o mesmo tamanho.
Matriz& Matriz::operator+=(const Matriz& outraMatriz) {
    assert(mLinhas == outraMatriz.mLinhas);
    assert(mColunas == outraMatriz.mColunas);
    for (int i = 0; i < mLinhas; i++)
    {
        for (int j = 0; j < mColunas; j++)
        {
            mData[i][j] += outraMatriz.mData[i][j];
        }            
    }
    return *this;
}

//Sobrescreve o operador de atribuição junto subtração (-=). As informações de duas matrizes A e B são somadas e atribuidas a matriz A, desde que possuam o mesmo tamanho.
Matriz& Matriz::operator-=(const Matriz& outraMatriz) {
    assert(mLinhas == outraMatriz.mLinhas);
    assert(mColunas == outraMatriz.mColunas);
    for (int i = 0; i < mLinhas; i++)
    {
        for (int j = 0; j < mColunas; j++)
        {
            mData[i][j] -= outraMatriz.mData[i][j];
        }            
    }
    return *this;
}

//Sobrescreve o operador de atribuição junto multiplicação (-=). As informações de duas matrizes A e B são multiplicadas e atribuidas a matriz A, desde que possuam o mesmo tamanho.
Matriz& Matriz::operator*=(const Matriz& outraMatriz) {
    assert(mColunas == outraMatriz.mLinhas);
    double soma;
    for (int k = 0; k < outraMatriz.mColunas; k++) {
        for (int i = 0; i < mLinhas; i++) {
            soma = 0.0;
            for (int j = 0; j < mColunas; j++) {
                soma += mData[i][j] * outraMatriz.mData[j][k];
            }
            mData[i][k] = soma;
        }        
    }
    return *this;
}

//Realiza a soma de duas matrizes de mesmo tamanho e retorna uma matriz com mesmo tamanho das anteriores.
Matriz Matriz::operator+(const Matriz& outraMatriz) {
    assert(mLinhas == outraMatriz.mLinhas);
    assert(mColunas == outraMatriz.mColunas);
    Matriz Saida(mLinhas, mColunas);
    for (int i = 0; i < mLinhas; i++)
    {
        for (int j = 0; j < mColunas; j++)
        {
            Saida[i][j] = mData[i][j] + outraMatriz.mData[i][j];
        }            
    }
    return Saida;
}

//Realiza a subtração de duas matrizes de mesmo tamanho e retorna uma matriz com mesmo tamanho das anteriores.
Matriz Matriz::operator-(const Matriz& outraMatriz) {
    assert(mLinhas == outraMatriz.mLinhas);
    assert(mColunas == outraMatriz.mColunas);
    Matriz Saida(mLinhas, mColunas);
    for (int i = 0; i < mLinhas; i++)
    {
        for (int j = 0; j < mColunas; j++)
        {
            Saida[i][j] = mData[i][j] - outraMatriz.mData[i][j];
        }            
    }
    return Saida;
}

//Realiza a multiplicação de um escalar n por uma matrix A e retorna uma matriz de saida com as mesma dimensões da matriz A.
Matriz Matriz::operator*(double n) {
    Matriz Saida(mLinhas, mColunas);
    for (int i = 0; i < mLinhas; i++)
    {
        for (int j = 0; j < mColunas; j++)
        {
            Saida[i][j] = mData[i][j] * n;
        }
    }
    return Saida;
}

//Realiza a multiplição de uma matriz A por uma outra matriz B e retorna uma matriz de saida com o número de linhas da matriz A e de colunas da matriz B. A operação só é realizada se o número de colunas de A for igual ao número de colunas de B.
Matriz Matriz::operator*(const Matriz& outraMatriz) {
    assert(mColunas == outraMatriz.mLinhas);
    Matriz Saida(mLinhas, outraMatriz.mColunas);
    double soma;
    for (int k = 0; k < outraMatriz.mColunas; k++) {
        for (int i = 0; i < mLinhas; i++) {
            soma = 0.0;
            for (int j = 0; j < mColunas; j++) {
                soma += mData[i][j] * outraMatriz.mData[j][k];
            }
            Saida[i][k] = soma;
        }        
    }
    return Saida;
}

//O produto de Hardmard realiza a multiplicação de um elemento da matriz pelo de uma segunda matriz na mesma linha e coluna.
Matriz Matriz::Hardmard(const Matriz& outraMatriz) {
    assert(mLinhas == outraMatriz.mLinhas);
    assert(mColunas == outraMatriz.mColunas);
    Matriz Saida(mLinhas, mColunas);
    for (int i = 0; i < mLinhas; i++)
    {
        for (int j = 0; j < mColunas; j++)
        {
            Saida[i][j] = mData[i][j] * outraMatriz.mData[i][j];
        }            
    }
    return Saida;
}

//Sobrescreve o operador << para retornar na tela as informações contidas e, uma matriz A.
std::ostream& operator<<(std::ostream& saida, const Matriz& A) {
    saida << std::setw(20);
    for (int i = 0; i < A.mLinhas; i++)
    {
        for (int j = 0; j < A.mColunas; j++)
        {
            saida << A.mData[i][j] << std::setw(20);
        }
        saida << std::endl;
    }
    return saida;
}