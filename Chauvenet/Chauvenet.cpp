/*************************************************************************************
Chauvenet.cpp
Autor: Gabriel Daltro Duarte
Data: 14 de junho de 2017

Descrição: Implementação das funções-membro da classe Chauvenet
*************************************************************************************/



#include "Chauvenet.h"

#ifdef DEBUG_ON_PC
    #include <iostream>
#endif

float Chauvenet::DS_CRITICO[27] = {1.54, 1.65, 1.73, 1.80, 1.85, 1.91, 1.96,
                                  1.99, 2.03, 2.06, 2.10, 2.13, 2.16, 2.18,
                                  2.20, 2.22, 2.24, 2.26, 2.28, 2.30, 2.31,
                                  2.33, 2.35, 2.36, 2.37, 2.38, 2.37 };

Chauvenet::Chauvenet(double* const ptrAmostras, int qtdAmostras)
{
    setAmostras(ptrAmostras, qtdAmostras);
}

Chauvenet::Chauvenet() // construtor vazio
{

}

bool Chauvenet::setAmostras( double* const ptrAmostras, int qtdAmostras)
{
    int i = 0;

    quantidadeDeAmostras = qtdAmostras;
    if( (qtdAmostras < 4) || (qtdAmostras > 30) )
    {
        return false;
    }
    else
    {
        for (i = 0; i < quantidadeDeAmostras; i++)
        {
            amostras[i] = ptrAmostras[i];
        }
        calculaMediaInicial();
        calculaDesvioPadrao ();
        #ifdef DEBUG_ON_PC
         std::cout << "Media Inicial: " << mediaInicial << "\n" << "Desvio Padrao: " << desvioPadrao << "\n";
        #endif

        return true;
    }
}

double Chauvenet::getMediaAposDescarte()
{
     return mediaAposDescarte;
}

void Chauvenet::calculaMediaInicial()
{
    int i = 0;
    double somaDasAmostras = 0;
    for (i = 0; i < quantidadeDeAmostras; i++)
    {
        somaDasAmostras = somaDasAmostras + amostras[i];
    }
    mediaInicial = (double)somaDasAmostras/quantidadeDeAmostras;
}


 void Chauvenet::calculaDesvioPadrao()
 {
    int i = 0;
    double desvioPadraoNUM = 0;
    double desvioPadraoDEM = 1;
    for (i = 0; i < quantidadeDeAmostras; i++)
    {
        desvioPadraoNUM = desvioPadraoNUM + (amostras[i] - mediaInicial)*(amostras[i] - mediaInicial);
    }
    desvioPadraoDEM = quantidadeDeAmostras - 1;
    desvioPadrao = sqrt(desvioPadraoNUM/desvioPadraoDEM);
 }


void Chauvenet::verificaAmostras(void)
{
    int i;
    double r;
    if ( desvioPadrao == 0 )
    {
        for (i = 0; i < quantidadeDeAmostras; i++ )
        {
            flagDeDescarte[i] = false;
        }
        mediaAposDescarte = mediaInicial;
        qtdAmostrasNaoRejeitadas = quantidadeDeAmostras;
        qtdAmostrasRejeitadas = 0;

        #ifdef DEBUG_ON_PC
            std::cout << "\nDesvio Padrao zero!\n";
        #endif

    }
    else
    {
        for (i = 0; i < quantidadeDeAmostras; i++ )
        {
            r = modulo ( amostras[i] - mediaInicial )/desvioPadrao;
             #ifdef DEBUG_ON_PC
                std::cout << "\nr recebeu = " << r << "\n";
             #endif

            if (r < DS_CRITICO[quantidadeDeAmostras - 4])
                flagDeDescarte[i] = false;
            else
                flagDeDescarte[i] = true;
            #ifdef DEBUG_ON_PC
                std::cout << "flagDeDescarte[" << i << "] = " << flagDeDescarte[i] << "\n";
            #endif

        }
        calculaMediaAposDescarte();
        setAmostrasRejeitadas();
        setAmostrasNaoRejeitadas();
        #ifdef DEBUG_ON_PC
            std::cout << "Media apos decarte: " << mediaAposDescarte << "\n";
        #endif
    }
}


void Chauvenet::calculaMediaAposDescarte(void)
{
    double somaParcial = 0.0;
    int contadorDeAmostrasValidas = 0.0;
    int i;

    for (i = 0; i < quantidadeDeAmostras; i++)
    {
        if (flagDeDescarte[i] == false)
        {
            somaParcial = somaParcial + amostras[i];
            contadorDeAmostrasValidas++;
        }
    }
    mediaAposDescarte = somaParcial/contadorDeAmostrasValidas;

}

 double Chauvenet::modulo (double num)
 {
     if (num >= 0)
        return num;
     else
        return (-1*num);
 }

double Chauvenet::getMediaInicial ()
{
    return mediaInicial;
}
double Chauvenet::getDesvioPadrao ()
{
    return desvioPadrao;
}

void Chauvenet::getFlagDeDescarte( bool* vet)
{
    int i = 0;
    for (i = 0; i < quantidadeDeAmostras; i++)
    {
        vet[i] = flagDeDescarte[i];
    }
}

 void Chauvenet::setAmostrasRejeitadas(void)
 {
     int i = 0;
     int j = 0;
     for (i = 0; i < quantidadeDeAmostras; i++)
     {
         if ( flagDeDescarte[i] == true)
         {
             amostrasRejeitadas[j] = amostras[i];
             j++;
         }
     }
     qtdAmostrasRejeitadas = j;

 }

void Chauvenet::setAmostrasNaoRejeitadas(void)
{
     int i = 0;
     int j = 0;
     for (i = 0; i < quantidadeDeAmostras; i++)
     {
         if ( flagDeDescarte[i] == false)
         {
             amostrasNaoRejeitadas[j] = amostras[i];
             j++;
         }
     }
     qtdAmostrasNaoRejeitadas = j;

}

 int Chauvenet::getQtdAmostrasRejeitadas (void)
 {
    return qtdAmostrasRejeitadas;
 }
int Chauvenet::getQtdAmostrasNaoRejeitadas (void)
{
    return qtdAmostrasNaoRejeitadas;
}

const double* const Chauvenet::getAmostrasRejeitadas(void)
{
    return (const double* const)(amostrasRejeitadas);

}
const double* const Chauvenet::getAmostrasNaoRejeitadas(void)
{
    return (const double* const)(amostrasNaoRejeitadas);
}


