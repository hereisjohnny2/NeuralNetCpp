#include <cassert>
#include <cmath>
#include <random>
#include <iomanip>
#include "headers/Vetor.hpp"

//Construtor vazio. Inicializa um vetor padrão colcando 3 posições de memória.
Vetor::Vetor() {
    mElementos = 3;
    mData = new double[mElementos];
}

//Construtor que cria um novo vetor a partir de outro.
Vetor::Vetor(const Vetor& outroVetor) {
    mElementos = outroVetor.GetNumElementos();
    mData = new double[mElementos];
    for (int i = 0; i < mElementos; i++)
    {
        mData[i] = outroVetor.mData[i];
    }    
}

//Construtor que aloca n_elementos para um vetor.
Vetor::Vetor(int n_elementos) {
    assert(n_elementos > 0);
    mElementos = n_elementos;
    mData = new double[mElementos];
}

//Construtor que cria um vetor com n_elementos, linearmente separados, entre dois numeros do tipo double.
Vetor::Vetor(double inicio, double fim, int n_elementos) {
    assert(inicio < fim);
    mElementos = n_elementos;
    mData = new double[mElementos];
    double passo = (fim - inicio) / (mElementos - 1);
    double num = inicio;
    for (int i = 0; i < mElementos; i++)
    {
        mData[i] = num;
        num += passo;
    }
}

//Sobrescreve o método destrutor para desalocar a memória de maneira apropriada.
Vetor::~Vetor() {
    delete[] mData;
}

//Retorna o numero de elementos em um vetor.
int Vetor::GetNumElementos() const {
    return mElementos;
}

void Vetor::SetNumElementos(int numElementos) {
    delete[] mData;
    mElementos = numElementos;
    mData = new double[mElementos];
}

//Calcula a norma euclidiana de um vetor. Utilizada para calcular o comprimento de um vetor. Ver mais em https://pt.wikipedia.org/wiki/Vetor_(matemática).
double Vetor::CalculaNorma(int p) const {
    double valorNorma, soma {0.0};
    for (int i = 0; i < mElementos; i++)
    {
        soma += pow(fabs(mData[i]), p);
    }
    valorNorma = pow(soma, 1.0/((double) p ));
    return valorNorma;
}

//Calcula o angulo entre dois vetores, utilizando a norma euclidiana para p=2;
double Vetor::CalculaAngulo(const Vetor& outroVetor) {
    double angulo;
    angulo = acos((*this * outroVetor)/(CalculaNorma()*outroVetor.CalculaNorma()));
    return angulo;
}

//Atribui o valor 0.0 à todos os elementos do vetor.
void Vetor::Zeros() {
    for (int i = 0; i < mElementos; i++)
    {
        mData[i] = 0.0;
    }
}

Vetor Vetor::Shuffle(int seed) {
    std::default_random_engine gerador(seed);
    std::uniform_int_distribution<int> numRand(0, mElementos-1);
    Vetor saida(*this);
    for (int i = 0; i < mElementos; i++)
    {
        double aux = saida[i];
        int num = numRand(gerador);
        saida[i] = saida[num];
        saida[num] = aux;
    }
    return saida;
}

//Atribui um valor randômico de um distribuição uniforme entre um limite superior (limiteSup) e inferior (limiteInf) à todos os elementos da matriz. Os valores padrão para os limites inferior e superior são, respectivamente -1.0 e 1.0.
void Vetor::RandUniforme(double limiteInf, double limiteSup) {
    std::default_random_engine gerador;
    std::uniform_real_distribution<double> numRand(limiteInf, limiteSup);
    for (int i = 0; i < mElementos; i++)
    {
        double num = numRand(gerador);
        mData[i] = num;
    }
}
//Atribui um valor randômico de um distribuição normal com média 0.0 e desvio padrão 1.0 à todos os elementos da matriz. Os valores da média e dos desvio padrão podem ser alterados passando-se esse elemento como parâmetros do método.
void Vetor::RandNormal(double media, double desvioPadrao) {
    std::default_random_engine gerador;
    std::normal_distribution<double> numRand(media, desvioPadrao);
    for (int i = 0; i < mElementos; i++)
    {
        double num = numRand(gerador);
        mData[i] = num;
    }
}

//Sobrescreve o operador [] para retornar o indice de um vetor, de modo que o primeiro elemento será igual terá indice zero.
double& Vetor::operator[](int index_elemento) {
    assert(index_elemento > -1);
    assert(index_elemento < mElementos);
    return mData[index_elemento];
}

//Sobrescreve o operador [] para retornar o indice de um vetor, de modo que o primeiro elemento será igual terá indice 1.
double& Vetor::operator()(int index_elemento) {
    assert(index_elemento > 0);
    assert(index_elemento < mElementos + 1);
    return mData[index_elemento];
} 

//Sobrescreve o operador de atribuição. Dessa forma uma variável do tipo Vetor pode ser atribuida a outra desde que possuam o mesmo tamanho de espaço alocado.
Vetor& Vetor::operator=(const Vetor& outraVetor) {
    assert(mElementos == outraVetor.mElementos);
    for (int i = 0; i < mElementos; i++)
    {
        mData[i] = outraVetor.mData[i];
    }
    return *this;
}

//Sobrescreve a operação de atribição e soma. Sejam dois vetor A e B, com a mesma quantidade de elementos. Em A+=B, os valores de ambos são somados e o resultado é colocado de volta em A.
Vetor& Vetor::operator+=(const Vetor& outraVetor) {
    assert(mElementos == outraVetor.mElementos);
    for (int i = 0; i < mElementos; i++)
    {
        mData[i] += outraVetor.mData[i];
    }
    return *this;
}

//Sobrescreve a operação de atribição e subtração. Sejam dois vetor A e B, com a mesma quantidade de elementos. Em A-=B, os valores de ambos são subtratidos A-B, e o resultado é colocado de volta em A.
Vetor& Vetor::operator-=(const Vetor& outraVetor) {
    assert(mElementos == outraVetor.mElementos);
    for (int i = 0; i < mElementos; i++)
    {
        mData[i] -= outraVetor.mData[i];
    }
    return *this;
}

//Sobrescreve a operação de soma. Dois vetores A e B, de mesmo tamanho são somados e o resultado é colocado em um terceiro vetor de Saida.
Vetor Vetor::operator+(const Vetor& outroVetor) const {
    assert(mElementos == outroVetor.mElementos);
    Vetor Saida(mElementos);
    for (int i = 0; i < mElementos; i++)
    {
        Saida.mData[i] = mData[i] + outroVetor.mData[i];
    }
    return Saida;
}



//Sobrescreve a operação de soma. Os elementos de um vetor A é somado à cada linha de uma matriz B com o número de colunas igual ao número de elemento do vetor. A saida é portanto uma segunda matriz C.
Matriz Vetor::operator+(const Matriz& outraMatriz) const {
    assert(mElementos == outraMatriz.GetNumColunas());
    Matriz entrada = outraMatriz;
    Matriz saida(outraMatriz.GetNumLinhas(), mElementos);
    for (int i = 0; i < outraMatriz.GetNumLinhas(); i++)
    {
        for (int j = 0; j < outraMatriz.GetNumColunas(); j++)
        {
            saida[i][j] = entrada[i][j] + mData[j];
        }
    } 
    return saida;
}

//Sobrescreve a operação de soma. Dois vetores A e B, de mesmo tamanho são subtraidos e o resultado é colocado em um terceiro vetor de Saida.
Vetor Vetor::operator-(const Vetor& outroVetor) const {
    assert(mElementos == outroVetor.mElementos);
    Vetor Saida(mElementos);
    for (int i = 0; i < mElementos; i++)
    {
        Saida.mData[i] = mData[i] - outroVetor.mData[i];
    }
    return Saida;
}

//Sobrescreve o operador unário de subtração de modo que são atribuidos à vetor de saida os valores de um outro vetor multiplicados por -1.
Vetor Vetor::operator-() const {
    Vetor Saida(mElementos);
    for (int i = 0; i < mElementos; i++)
    {
        Saida.mData[i] = -mData[i];
    }
    return Saida;
}

//Sobrescreve a operação de multiplicação. Um vetor A tem cada um dos seus elementos multiplicados por um escalar n, e o resultado é colocado dentro de um terceiro vetor de Saida.
Vetor Vetor::operator*(double n) {
    Vetor Saida(mElementos);
    for (int i = 0; i < mElementos; i++)
    {
        Saida.mData[i] = mData[i] * n;
    }
    return Saida;
}

//Sobrescreve a operação de multiplicação. Os elementos de um vetor A sãp multiplicados aos de uma matriz B com o número de linhas igual ao número de elemento do vetor. A saida é portanto um segundo vetor C.
Vetor Vetor::operator*(Matriz A) {
    assert(mElementos == A.GetNumLinhas());
    double soma;
    Vetor C(A.GetNumColunas());
    for (int i = 0; i < A.GetNumColunas(); i++)
    {
        soma = 0;
        for (int j = 0; j < A.GetNumLinhas(); j++)
        {
            soma += A[j][i] * mData[j]; 
        }
        C[i] = soma;
    }
    return C;
}

//Sobrescreve a operação de multiplicação retornando o produto escalar de dois vetores, de modo que ambos possuam o mesmo tamanho.
double Vetor::operator*(const Vetor& outroVetor) const {
    assert(mElementos == outroVetor.mElementos);
    double soma {0.0};
    for (int i = 0; i < mElementos; i++)
    {
        soma += mData[i] * outroVetor.mData[i];
    }
    return soma;
}

//Sobrescreve a operação <<, retornando na tela os elementos de um vetor A.
std::ostream& operator<<(std::ostream& saida, const Vetor& A) {
    for (int i = 0; i < A.mElementos; i++)
    {
        saida << A.mData[i] << std::setw(20);
    }
    return saida;
}

//Retorna o tamanho de um vetor A recebendo como argumento o vetor. Semelhante a sintaxe do python.
int len(const Vetor& A) {
    return A.GetNumElementos();
}
