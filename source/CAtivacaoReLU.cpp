#include "headers/CAtivacaoReLU.hpp"

/* 
Aplica a função ReLU, que é a unidade linear retificada, em uma matriz de entrada _inputs. O atributo saida tem seu numero de linhas e colunas modificado para se adequar às dimensões da matriz de entrada. Em seguida os valores da matriz de entrda são atribuidos a matriz de saida, uma vez que a matriz de entrada é uma constante portando não deve ser modificada. Dois laços percorrem a matriz de modo que se o valor de uma determinada posição i,j for menor ou igual a zero, ao valor desta é atribuido 0.0. Se não, o valor original é preservado.  

Entradas: _inputs

f(x) = max(0,x)
*/

double CAtivacaoReLU::f(double _x) {
    return (_x <= 0) ? 0.0 : _x; 
}

double CAtivacaoReLU::df(double _x) {
    return (_x < 0) ? 0.0 : 1.0; 
}