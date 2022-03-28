/*Objetivo 1: Estude o datasheet do arduíno uno para determinar quais os valores são escritos nas portas Analógicas para cada um dos valores de tensão possíveis - de 0 a 5V.

Objetivo 2: Implemente um circuito, com 3 divisores de tensão, conectados às portas A0, A1 e A2.

Objetivo 3: Implemente um programa que faça a leitura das tensões em A0, A1 e A2 e exiba os valores em binários nos pinos digitais. Escolha a resolução desejada, fazendo uma regra de 3 para garantir que os valores máximos conforme os valores escritos nem A0, A1 e A2. Alterne os valores exibidos na saida com base no click de um push button. Demonstre o funcionamento do circuito real, através de um múltimitro contectado à porta e faça as conversões manualmente que o programa desenvolvido também o faz. Apresente esses resultados no relatório.

Objetivo 4: Reserve um conjunto de bits de saída para demonstrar qual dos valores tem maior módulo. Exemplo: Se o valor de A0 for maior que A1 e A2, o pino de saida indicativo do A0 estará High e os demais Low, se A0 e A1 forem iguais e > que A2, os pinos de A0 e A1 estarão High e A2 Low.

Objetivo 5: Exiba os dados lidos no console, utilizando a classe Serial.*/



#include <Arduino.h>	// inclusao da biblioteca arduino.h

// Ln é o LED correspondente a saida binaria (amarelos e vermelhos)
const int L0 = 5;
const int L1 = 6;
const int L2 = 7;
const int L3 = 8;
const int L4 = 9;
const int L5 = 10;
const int L6 = 11;
const int L7 = 12;
// LMn é o LED correspondente a indicacao da maior leitura analogica (verde)
const int LM0 = 0;
const int LM1 = 1;
const int LM2 = 2;
// incluindo LEDs em vetor de escopo global p/ utilizacao em funcoes
const int LEDS[] = {L0, L1, L2, L3, L4, L5, L6, L7};

const int BT = 13;	// variavel representa botao

int PTC[] = {A0, A1, A2};  //vetor que declara as entradas analógicas

void setup() 
{
// inicializando botao
  pinMode(BT,INPUT_PULLUP);
  //inicializando as portas digitais dos LEDs dos bits:
 for(int k = 5; k <= 12; k++)	
 {
  pinMode(k,OUTPUT);
  }

  //Inicializando os pinos dos LEDs que apresentam a maior leitura analogica
  pinMode(LM0,OUTPUT);
  pinMode(LM1,OUTPUT);
  pinMode(LM2,OUTPUT);

  //Inicializando os pinos que realizam cada leitura analogica
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);

// inicializa o monitor serial
  Serial.begin(9600);
}

//apresentando cabecalho das funcoes utilizadas no codigo
void BITS_LEDS(int OPERANDO);
void INDICA_MAIOR();
 
void loop()
{
  int LEITURA = 0;  //variável para leitura da entrada analogica
  int ATIVO = 0;  //variável para definir a entrada analogica
  
  if (ATIVO <= 2)	// a var ATIVO define a posicao dentro do ponteiro PTC[]
  {
      if (digitalRead(BT) == 0)
      {
         ATIVO++;
         delay(500);
      }
      //grava a leitura do pino analogico na var LEITURA. Adivisao por 4 ocorre para reduzir a resolucao de 10 bits para 8 bits
      LEITURA = analogRead(PTC[ATIVO]) / 4;     
      
      // chamada das funcoes que comandam os LEDs
      BITS_LEDS(LEITURA);
      INDICA_MAIOR();
      
      //comandos que imprimem os dados no console 
      Serial.println("Resistor 0: ");
      Serial.print(analogRead(A0));
      Serial.print("  Resistor 1:");
      Serial.print(analogRead(A1)); 
      Serial.print("  Resistor 2: ");
      Serial.print(analogRead(A2)); 
      Serial.println("Tensão em R0: ");
      Serial.print((5 * analogRead(A0)) / 1024.0);
      Serial.print("  Tensão em R1: ");
      Serial.print((5 * analogRead(A1)) / 1024.0);
      Serial.print("  Tensão em R2: ");
      Serial.print((5 * analogRead(A2)) / 1024.0);
      Serial.println("Leitura ativa: R");
      Serial.print(ATIVO);
      delay(2300);
  }
  else
  {
    ATIVO = 0;
  }
}

void BITS_LEDS(int OPERANDO) //funcao responsavel por converter o valor lido na porta analogica para base binaria enquanto comanda os LEDs
{
    for(int k = 7; k >= 0; k--)
    {
        int DIVISORES[] = {1, 2, 4, 8, 16, 32, 64, 128};
        if(OPERANDO >= DIVISORES[k])
        {
            OPERANDO -= DIVISORES[k];
            digitalWrite(LEDS[k], HIGH);
        }
        else
            digitalWrite(LEDS[k], LOW);
    }
}

void INDICA_MAIOR()	// funcao responsavel por acender o LED que indica a maior entrada analogica
{
  int R0, R1, R2;
  R0 = analogRead(A0);
  R1 = analogRead(A1);
  R2 = analogRead(A2);
 
  if(R0 > R1 && R0 > R2)
  {
    digitalWrite(LM0, HIGH);
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    }
  else if(R1 > R0 && R1 > R2)
  {
    digitalWrite(LM0, LOW);
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    }
  else if(R2 > R0 && R2 > R1)
  {
    digitalWrite(LM0, LOW);
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    }
  else if(R0 == R1 && R0 > R2)
  {
    digitalWrite(LM0, HIGH);
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    }
   else if(R0 == R2 && R2 > R1)
   {
    digitalWrite(LM0, HIGH);
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    }
   else if(R1 == R2 && R2 > R0)
   {
    digitalWrite(LM0, LOW);
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    }
   else
   {
    digitalWrite(LM0, HIGH);
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    }
}
