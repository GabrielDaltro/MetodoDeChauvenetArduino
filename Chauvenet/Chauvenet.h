/******************************************************************************************
Chauvenet.h
Autor: Gabriel Daltro Duarte
Data: 14 de junho de 2017

Descrição: Os objetos dessa classe recebem um vetor de leituras, avalia estatísticamente
cada elemento do vetor de leituras utlilizando o método de Chauvenet, para determinar se
a leitura deve ser descartada ou não, por fim, calcula a média das leituras que não foram
rejeitadas.
*******************************************************************************************/


#define TAM_MAX 30
#define ARDUINO // Descomente quando compilar no Arduino
//#define PC // Descomente quando compilar em um PC
//#define DEBUG_ON_PC // Descomente para visualizar o calculo etapa a etapa - só funciona no PC


#ifdef ARDUINO
    #include <math.h>
#endif // ADUINO

#ifdef PC
    #include <cmath>
#endif


class Chauvenet {
    public:
        Chauvenet( double* const ptrAmostras, int qtdAmostras); // Construtores da classe
        Chauvenet();

        bool setAmostras( double* const ptrAmostras, int qtdAmostras); // Passa para o objeto Chauvenet o vetor das amostras a serem avaliadas e o tamanho desse vetor
        void verificaAmostras(void); // Verifica cada amostra e determina quais serão descartadas
        double getMediaAposDescarte(void); // retorna a média das amostras não descartadas

    private:
        int quantidadeDeAmostras;
        static float DS_CRITICO[27];
        double amostras[TAM_MAX];
        bool flagDeDescarte [TAM_MAX];
        double desvioPadrao;
        double mediaInicial;
        double mediaAposDescarte;

        void calculaMediaInicial(void);
        void calculaDesvioPadrao(void);
        void calculaMediaAposDescarte(void);
        double modulo (double);
};

