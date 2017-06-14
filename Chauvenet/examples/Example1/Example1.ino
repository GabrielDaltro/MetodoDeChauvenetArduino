#include <Chauvenet.h>


void setup()
{
    double medidas[] = {1.0, 2.0, 3.0, 4.0, 100.0}; // Vetor com as medidas a serem avaliadas
    Serial.begin (9600);
   
    Chauvenet chauvenet; // Cria um objeto Chauvenet

    if (!chauvenet.setAmostras(medidas,4)) // Passa para o objeto o vetor com as medidas e seu tamanho
    {
        Serial.println ("ERRO! A QUANTIDADE DE MEDIDAS DEVE SER ENTRE 4 E 30"); // O tamanho do vetor deve ser maior que 4 e menor que 30. 
    }
    else
    {
    	chauvenet.verificaAmostras();
    	Serial.println ( "Media das amostras apos o descarte: ");
    	Serial.println ( chauvenet.getMediaAposDescarte() ); // Observe que a medida 100 foi descartada. 2.5 é a média dos 4 primeiros elementos do vetor que não foram descartados
    }
  
}
void loop()
{
  
}
