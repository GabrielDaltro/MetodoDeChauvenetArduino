#include <Chauvenet.h>


void setup()
{
    Serial.begin(9600);
    
    // vetor que armazena as amostras a serem avaliadas
    double medidas[] = {1.0, 2.0, 3.0, 4.0, 100.0};

    // cria o objeto chauvenet
    Chauvenet chauvenet;

    // Imprime o vetor de amostras
   Serial.print ( "\n\nLista de amostras: ");
     for (int i = 0; i < 5; i++)
      {
         Serial.print ( medidas[i]);
         Serial.print (" ");
      }
     // passa o vetor de amostras e seu tamano para o objeto chauvenet
    if (!chauvenet.setAmostras(medidas,5)) 
    {
        Serial.println ("ERRO! A QUANTIDADE DE MEDIDAS DEVE SER ENTRE 4 E 30"); // O tamanho do vetor deve ser maior que 4 e menor que 30. 
    }
    else
    {
        //verifica quais amostras serão mantidas e quais serão descartadas
        chauvenet.verificaAmostras();
  
       // Observe que a medida 100 foi descartada. 2.5 é a média dos 4 primeiros elementos do vetor que não foram descartados
  
       // Imprime a média das amostras que não foram descartadas
        Serial.print ( "\n\nMedia das amostras apos o descarte: ");
        Serial.println ( chauvenet.getMediaAposDescarte() ); 
  
       // Declara um ponteiros constante para dados constantes que aponta para o vetor de amostras descartadas
        const double* const amostrasDescartadas = chauvenet.getAmostrasRejeitadas();
  
      // imprime o vetor que armazena as amostras descartadas
       Serial.print ( "\n\nLista de amostras descartadas: ");
        for (int i = 0; i < chauvenet.getQtdAmostrasRejeitadas(); i++)
        {
           Serial.print ( amostrasDescartadas[i]);
           Serial.print (" ");
        }
  
      // Declara um ponteiros constante para dados constantes que aponta para o vetor de amostras NAO descartadas
       const double* const amostrasNaoDescartadas = chauvenet.getAmostrasNaoRejeitadas();
  
      // imprime o vetor que armazena as amostras descartadas
        Serial.print ("\n\nLista de amostras NAO descartadas: ");
  
        for (int i = 0; i < chauvenet.getQtdAmostrasNaoRejeitadas(); i++)
        {
          Serial.print (amostrasNaoDescartadas[i]);
          Serial.print (" ");
        }

     
    }
  
}
void loop()
{
  
}

  

   
