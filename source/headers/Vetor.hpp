#pragma once
#include <iostream>
#include "Matriz.hpp"

class Vetor {

private:
    double* mData;
    int mElementos;

public:
    Vetor();
    Vetor(const Vetor& outroVetor);
    Vetor(int n_elementos);
    Vetor(double inicio, double fim, int n_elementos);
    ~Vetor();

    int GetNumElementos() const;
    void SetNumElementos(int numElementos);

    double CalculaNorma(int p=2) const;
    double CalculaAngulo(const Vetor& outroVetor);
    void Zeros();
    Vetor Shuffle(int seed=0);
    void RandUniforme(double limiteInf = -1.0, double limiteSup = 1.0);
    void RandNormal(double media = 0.0, double desvioPadrao = 1.0);

    double& operator[](int index_elemento);
    double& operator()(int index_elemento);

    Vetor& operator=(const Vetor& outraVetor);
    Vetor& operator+=(const Vetor& outraVetor);
    Vetor& operator-=(const Vetor& outraVetor);

    Vetor operator+(const Vetor& outraVetor) const;
    Matriz operator+(const Matriz& outraMatriz) const;
    Vetor operator-(const Vetor& outraVetor) const;
    Vetor operator-() const;

    Vetor operator*(double n);
    Vetor operator*(Matriz A);
    double operator*(const Vetor& outraVetor) const;

    friend std::ostream& operator<<(std::ostream& saida, const Vetor& A);
};

int len(const Vetor& A);