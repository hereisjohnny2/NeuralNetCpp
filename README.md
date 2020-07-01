# NeuralNetCpp

Como forma de iniciar meus estudos em desenvolvimento C++ e em inteligência artificial, crie este projeto baseado no livro "Neural Networks and Deep Learning", de Michael Nielsen.

Nele são mostrados os princípios básicos do desenvolvimento de uma rede neural utilizando a linguagem python. Todavia, no meu caso resolvi utilizar C++.

Na versão atual ele já executa os algoritimos de Feedforward, Backpropagation e Gradiente Descendente Estocástico. Também conta com duas funções de ativação: ReLU e Sigmoid, todavia, mudar de uma para outra ainda envolve modificar diretamente o código do algoritimo de SGD.

Como estrutura de dados para armazenar as informações que são processadas ao longo da rede, resolvi criar uma pequena biblioteca para a manipulação de matrizes.

O compilador utilizado é o g++, a a versão da liguagem C++ é a 17, entretanto, essa configurações podem ser modificadas no makefile. 

Como teste, estou utiliando o banco de dados de imagens MNIST. Nele estão contidas imagens algarismos numéricos escritos à mão. Para conseguir utilizar a imagens com o algoritimo basta incluí-las no formato CSV na pasta ```MNIST```. Para baixa, basta clicar [neste link](https://www.kaggle.com/oddrationale/mnist-in-csv?select=mnist_train.csv).

Para compilar o código é necessário executar no terminar, no mesmo diretório do projeto, o comando ```make all```.
