#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <stdexcept>
#include <sstream>
#include <tuple>
#include <vector>

#include "Matriz.hpp"

class CMNIST
{
private:
    Matriz treinoX = Matriz(60000, 784);
    Matriz treinoY = Matriz(60000, 10);

    Matriz testeX = Matriz(10000, 784);
    Matriz testeY = Matriz(1, 10000);
public:
    CMNIST(std::string arqTreino, std::string arqTeste);

    Matriz GetTreinoX() const;
    Matriz GetTreinoY() const;
    Matriz GetTesteX() const;
    Matriz GetTesteY() const;
    
    friend std::vector<std::vector<std::string>> read_csv(std::string filename);
};