#pragma once
#include <iostream>

class Matriz {

private:
    double** mData;
    int mColunas;
    int mLinhas;

public:
    Matriz();
    Matriz(const Matriz& outraMatriz);
    Matriz(int n_elementos);
    Matriz(int n_linhas, int n_colunas);
    ~Matriz();

    int GetNumLinhas() const;
    int GetNumColunas() const;

    void SetNumLinhas(int _Linhas);
    void SetNumColunas(int _Colunas);

    double CalculaDeterminante();
    void Zeros();
    Matriz Shuffle(int seed=0);
    void RandUniforme(double limiteInf = -1.0, double limiteSup = 1.0);
    void RandNormal(double media = 0.0, double desvioPadrao = 1.0);
    Matriz CalculaTransposta();

    double* operator[](int index_linha);
    double& operator()(int index_linha, int index_coluna);

    Matriz& operator=(const Matriz& outraMatriz);
    Matriz& operator+=(const Matriz& outraMatriz);
    Matriz& operator-=(const Matriz& outraMatriz);
    Matriz& operator*=(const Matriz& outraMatriz);

    Matriz operator+(const Matriz& outraMatriz);
    Matriz operator-(const Matriz& outraMatriz);

    Matriz operator*(double n);
    Matriz operator*(const Matriz& outraMatriz);

    Matriz Hardmard(const Matriz& outraMatriz);

    friend std::ostream& operator<<(std::ostream& saida, const Matriz& A);
};