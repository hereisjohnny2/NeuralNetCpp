#include "headers/CMNIST.hpp"

std::vector<std::vector<std::string>> read_csv(std::string filename) {
    std::ifstream file(filename);

    std::string line;
    std::vector<std::vector<std::string>> values;

    while (std::getline(file, line))
    {
        std::string lineValue;
        std::vector<std::string> lineValuesVector;
        std::stringstream ss(line);
        while (std::getline(ss, lineValue, ','))
        {
            lineValuesVector.push_back(lineValue);
        }
        values.push_back(lineValuesVector);        
    }    

    file.close();

    std::cout << "Leitura do Arquivo \"" << filename << "\" encerrada!" << std::endl;
    return values;
}

CMNIST::CMNIST(std::string arqTreino, std::string arqTeste) {
    std::vector<std::vector<std::string>> treino = read_csv(arqTreino);
    std::vector<std::vector<std::string>> teste = read_csv(arqTeste);

    for (int i = 0; i < treinoX.GetNumLinhas(); i++)
    {
        for (int j = 0; j < treinoX.GetNumColunas(); j++)
        {
            treinoX[i][j] = std::stof(treino[i+1][j+1]);
        }
        for (int j = 0; j < treinoY.GetNumColunas(); j++)
        {
            treinoY[i][j] = std::stof(treino[i+1][0]) == j ? 1.0 : 0.0;
        }
        
        
    }

    for (int i = 0; i < testeX.GetNumLinhas(); i++)
    {
        for (int j = 0; j < testeX.GetNumColunas(); j++)
        {
            testeX[i][j] = std::stof(teste[i+1][j+1]);
        }
        testeY[0][i] = std::stof(teste[i+1][0]);
    }    
}

Matriz CMNIST::GetTreinoX() const{
    return treinoX;
}

Matriz CMNIST::GetTreinoY() const{
    return treinoY;
}

Matriz CMNIST::GetTesteX() const{
    return testeX;
}

Matriz CMNIST::GetTesteY() const{
    return testeY;
}


