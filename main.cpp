#include <iostream>
#include <algorithm>
#include <cmath>
#include <memory>

#include "CNetwork.hpp"
#include "CLayer.hpp"

#include "CActReLU.hpp"
#include "CLoss.hpp"

#include "CircleData.hpp"
#include "SpiralData.hpp"

int main()
{
    std::vector<CLayer> layers{
        CLayer(2, 16),
        CLayer(16, 16),
        CLayer(16, 16),
        CLayer(16, 16),
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
