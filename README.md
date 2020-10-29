# NeuralNetsCpp

Esse projeto tem como objetivo desenvolver uma biblioteca simples para a construção de redes neurais para a linguagem C++. Ela é baseada principalmente na série de videos do canal Sentdex, [Neural Networks from Scratch](https://www.youtube.com/playlist?list=PLQVvvaa0QuDcjD5BAw2DxE6OF2tius3V3) e o livro [Neural Networks and Deep Learning](http://neuralnetworksanddeeplearning.com/index.html), do Michael Nielsen. Em ambas as fontes os códigos utilizados pelos autores são escritos em python e portanto foram necessárias adptações para a linguagem C++.

Atualmente a biblioteca é dividida em 4 classes principais:

- CNetwork: Classe principal responsável para construção da rede neural em si.
- CActivation: Classe relacionada às funções de ativação de cada neurônio.
- CLayer: Classe de construção da camada da rede neural.
- CLoss: Classe relacionadas às funções de perda da rede neural.

Além disso existem outras classes de suporte para a execução das operações matemáticas e geração de datasets de teste:

- CDataset: Classe relacionada à gerações de conjuntos de dados para realização de testes no código.Atualmente a biblioteca conta com duas classes de conjuntos de dados que herdam dessa classe mãe:
  - CircleData: Conjunto de clusters circulares separados uns dos outros por um offset em x e em y.
    -SpiralData: Conjunto de dados que forma espirais em torno de um centro comum. Baseado no código de um estudo de caso da disciplina CS231n - ["Convolutial Neural Networks for Image Recognition"](https://cs231n.github.io/neural-networks-case-study/), do curso de Ciência da Computação da Universidade de Stanford.
- LinAlg: Conjunto de funções para a realização de operações de algebra linear na rede neural.
- CGnuplot: Classe externa utilizada para a plotagem de gráficos dos conjuntos de dados.

O diagrama de classes do projeto pode ser encontrado no arquivo neuralNetDia, que abre com o sofware Umbrello.

## Compilação e Execução

Atualmente o projeto é compilado com o gcc com o seguinte comando:

```
g++ *.cpp -o main
```

## Exemplo de criação de rede neural

Para que se possa utilizar a biblioteca _NeuralNetsCpp_, pode-se seguir o exemplo a baixo.

```c++
#include <iostream>
#include <algorithm>
#include <cmath>
#include <memory>

#include "CNetwork.hpp"
#include "CLayer.hpp"

#include "CActReLU.hpp"
#include "CLoss.hpp"

#include "CircleData.hpp"

int main()
{
    std::vector<CLayer> layers{
        CLayer(2, 16),
        CLayer(16, 3),
    };

    std::vector<CActivation *> activations;
    for (int i = 0; i < layers.size() - 1; i++)
    {
        auto p = new CActReLU();
        activations.push_back(p);
    }

    CNetwork net(layers, activations);
    CLoss Loss;

    std::unique_ptr<CDataset> dataset = std::make_unique<CircleData>();
    dataset->CreateData(300, 3);

    std::unique_ptr<CDataset> test = std::make_unique<CircleData>();
    test->CreateData(10, 3);

    int miniBatchSize{15};
    int numMiniBatches = dataset->GetX().size() / miniBatchSize;

    for (int e = 0; e < 300; e++)
    {
        dataset->ShuffleData();
        auto X = dataset->GetX();
        auto y = dataset->GetY();

        for (int m = 0; m < numMiniBatches; m++)
        {
            std::vector<std::vector<double>> miniBatchX(X.begin() + m * miniBatchSize, X.begin() + m * miniBatchSize + miniBatchSize);
            std::vector<std::vector<double>> miniBatchY(y.begin() + m * miniBatchSize, y.begin() + m * miniBatchSize + miniBatchSize);

            auto out = net(miniBatchX);

            auto loss = Loss(out, miniBatchY);

            net.Backpropagate(loss);
            net.UpdateParams(0.01, miniBatchX);
        }

        std::cout << "Loss: " << std::sqrt(Loss.GetLoss()) << " Epoch: " << e + 1 << std::endl;

        auto yPred = net(test->GetX());

        int res{0};
        for (int m = 0; m < yPred.size(); m++)
        {
            std::vector<double> o = yPred[m];
            std::vector<double> l = test->GetY()[m];
            auto maxElementIndexOutput = std::max_element(o.begin(), o.end()) - o.begin();
            auto maxElementIndexLabels = std::max_element(l.begin(), l.end()) - l.begin();

            res += (maxElementIndexOutput == maxElementIndexLabels) ? 1 : 0;
        }
        std::cout << "Accuracy: " << double(res) / test->GetY().size() << std::endl;
    }

    for (int i = 0; i < activations.size(); i++)
    {
        delete activations[i];
    }

    return 0;
}
```

Nele é criado uma rede com dois "sensores" de entrada, uma camada profunda com 16 neurônios e uma de saida com 3.

```c++
std::vector<CLayer> layers{
    CLayer(2, 16),
    CLayer(16, 3),
};
```

Para cada camada interna são criadas às funções de ativação.

```c++
std::vector<CActivation *> activations;
for (int i = 0; i < layers.size() - 1; i++)
{
    auto p = new CActReLU();
    activations.push_back(p);
}
```

Com isso cria-se o objeto da rede neural _CNetwork_ e o de função de custo _CLoss_. Cria-se também, nesse caso uma dataset para o treino e outro para o teste e define-se o também do _batch_ utilizado em cada etapa do treinamento.

```c++
CNetwork net(layers, activations);
CLoss Loss;

std::unique_ptr<CDataset> dataset = std::make_unique<CircleData>();
dataset->CreateData(300, 3);

std::unique_ptr<CDataset> test = std::make_unique<CircleData>();test->CreateData(10, 3);
```

A execução do treino é feita dentro de um laço que executa os calculos dentro de um número _e_ de _épocas_.

Primeiro a ordem dos componentes do dataset é randomicamente alterada:

```c++
dataset->ShuffleData();
auto X = dataset->GetX();
auto y = dataset->GetY();
```

Em seguida cada _mini batch_ é passado através da rede neural e o erro é retropropagado, os pesos e biases da rede são atualizados no processo:

```c++
for (int m = 0; m < numMiniBatches; m++)
{
    std::vector<std::vector<double>> miniBatchX(X.begin() + m * miniBatchSize, X.begin() + m * miniBatchSize + miniBatchSize);
    std::vector<std::vector<double>> miniBatchY(y.begin() + m * miniBatchSize, y.begin() + m * miniBatchSize + miniBatchSize);

    auto out = net(miniBatchX);

    auto loss = Loss(out, miniBatchY);

    net.Backpropagate(loss);
    net.UpdateParams(0.01, miniBatchX);
}
```

Calcula-se perda nessa época do treinamento e mostra-se o resultado na tela.

```c++
std::cout << "Loss: " << std::sqrt(Loss.GetLoss()) << " Epoch: " << e + 1 << std::endl;
```

Por fim, são feitas previsões com o modelo treinado e calcula-se sua acurácia:

```c++
auto yPred = net(test->GetX());
int res{0};
for (int m = 0; m < yPred.size(); m++)
{
    std::vector<double> o = yPred[m];
    std::vector<double> l = test->GetY()[m];
    auto maxElementIndexOutput = std::max_element(o.begin(), o.end()) - o.begin();
    auto maxElementIndexLabels = std::max_element(l.begin(), l.end()) - l.begin();

    res += (maxElementIndexOutput == maxElementIndexLabels) ? 1 : 0;
}
std::cout << "Accuracy: " << double(res) / test->GetY().size() << std::endl;
```
