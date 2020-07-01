#include "headers/CMNIST.hpp"
#include "headers/CRedeNeural.hpp"

using std::vector;

int main()
{

    int epocas = 30, tamMiniBatch = 10;
    double eta = 0.1;


    CMNIST mnistData("MNIST/train.csv", "MNIST/test.csv");
    
    int tamCamadas[] {784, 30, 10};
    int numCamadas = sizeof(tamCamadas)/sizeof(tamCamadas[0]);
    
    CRedeNeural Net(epocas, tamMiniBatch, eta, numCamadas, tamCamadas);

    Net.SGD(mnistData.GetTreinoX(), mnistData.GetTreinoY(), mnistData.GetTesteX(), mnistData.GetTesteY());
    
    
    return 0;
}