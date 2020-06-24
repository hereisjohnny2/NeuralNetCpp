# NeuralNetsCpp

Como forma de iniciar meus estudos em desenvolvimento C++ e em inteligência artificial, crie este projeto baseado no livro "Neural Networks and Deep Learning", de Michael Nielsen. <br>

Nele são mostrados os princípios básicos do desenvolvimento de uma rede neural utilizando a linguagem python. Todavia, no meu caso resolvi utilizar C++. <br>

Atualmente o projeto é capaz apenas de realizar o movimento de FeedForward, que significa alimentar as cada camada da rede com a saida da anterior. Ele também já conta com duas funções de ativação, ReLU e Sigmoid. <br>

Como estrutura de dados para armazenar as informações que são processadas ao longo da rede, resolvi criar uma pequena biblioteca para a manipulação de matrizes. <br>

O compilador utilizado é o g++, a a versão da liguagem C++ é a 14, entretanto, essa configurações podem ser modificadas no `makefile`. <br>