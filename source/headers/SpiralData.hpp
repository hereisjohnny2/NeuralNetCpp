#pragma once
#include <cmath>
#include "Vetor.hpp"
#include "Matriz.hpp"

/*
Classe desenvolvida para gerar um dataset na forma de um espirnal. Recebe como construtor o numero de pontos para cada classe e o numero de classes que serão criadas.
Ex: Um dataset que recebe como entrada _pontos = 100 e _classes = 3 possuirá 3 classes com 100 pares (x,y) cada uma. A matriz X possuirá portanto uma forma (300,2). 

Atributos Membros:
    - pontos: números de pontos que cada classe deve possuir.
    - classes: número de classes que serão geradas no dataset.
    - X: Matriz de pares ordenados (x,y) que representam os pontos do dataset;
    - y: Vetor que armazena as classes de cada ponto.

Métodos Membros:
    SpiralData(int _pontos, int _classes): Constroi uma nova camada com base no numero de pontos e classes.
    GetX(): Retorna os valorem em X.
    GetY(): Retorna os valores em y.
*/
class SpiralData
{
private:
    int pontos {1};
    int classes {2};
    Matriz X = Matriz(pontos*classes,2); //Dados que forma a espiral
    Matriz yVec = Matriz(pontos*classes, classes);
    Matriz y = Matriz(1, pontos*classes); //Labels referantes aos dados
public:
    //Construtor
    SpiralData(int _pontos, int _classes);
    //Destrutor
    ~SpiralData() = default;

    //Getters
    Matriz GetX() const {return X;};
    Matriz GetYVec() const {return yVec;};
    Matriz GetY() const {return y;};
    
    //Funcao para gerar os dados
    void CriarDados();
};