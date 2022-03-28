const int L0 = 5;
const int L1 = 6;
const int L2 = 7;
const int L3 = 8;
const int L4 = 9;
const int L5 = 10;
const int L6 = 11;
const int L7 = 12;
const int LM0 = 0;
const int LM1 = 1;
const int LM2 = 2;
const int LEDS[] = {L0, L1, L2, L3, L4, L5, L6, L7};

const int BT = 13;

const int vals[] = {1, 2, 4, 8, 16, 32, 64, 128};

int PTC[] = {A0, A1, A2};  //vetor que declara as entradas analógicas

void setup() 
{
  pinMode(BT,INPUT_PULLUP);
  //Declarando as portas digitais dos leds dos bits:
 for(int k = 5; k <= 12; k++) 
 {
  pinMode(k,OUTPUT);
  }

  //Declarando os pinos dos leds que representam cada resistor:
  pinMode(LM0,OUTPUT); //amarelo = A0
  pinMode(LM1,OUTPUT); //vermelho = A1
  pinMode(LM2,OUTPUT); //verde = A2

  //Declarando as portas analogicas dos resistores:
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);

  Serial.begin(9600);
}
 
void loop()
{
  int ATIVO = 0;  //variável para definir o potenciôemtro lido
  int LEITURA = 0;  //variável para leitura do potenciôemtro
  
  if (ATIVO <= 2)
  {
      //armazena o valor do potenciômetro respectivo
      if (digitalRead(BT) == 0)
      {
         ATIVO++;
         delay(500);
      }
      
      LEITURA = analogRead(PTC[ATIVO]) / 4;     
      
      //chamada da função ligarLeds, com entrada sendo o valor oitobits
      ligarLeds_bits(LEITURA);
      maiorvalor();
      
      //imprimir os dados 
      Serial.print("Resistor 0: ");
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
      Serial.println(ATIVO);
      delay(3000);
  }
  else
  {
    ATIVO = 0;
  }
}

void maiorvalor()
{
  if(analogRead(A0)>analogRead(A1) and analogRead(A0)>analogRead(A2))
  {
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(11, LOW);
    }
  else if(analogRead(A1)>analogRead(A0) and analogRead(A1)>analogRead(A2))
  {
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(11, LOW);
    }
  else if(analogRead(A2)>analogRead(A1) and analogRead(A2)>analogRead(A0))
  {
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(11, HIGH);
    }
  else if(analogRead(A0)==analogRead(A1) and analogRead(A0)>analogRead(A2))
  {
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(11, LOW);
    }
   else if(analogRead(A0)==analogRead(A2) and analogRead(A2)>analogRead(A1))
   {
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(11, HIGH);
    }
   else if(analogRead(A1)==analogRead(A2) and analogRead(A2)>analogRead(A0))
   {
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(11, HIGH);
    }
   else
   {
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(11, HIGH);
    }
}

void ligarLeds_bits(int valor)
{
    for(int k = 7; k >= 0; k--)
    {
        if(valor >= vals[k])
        {
            valor -= vals[k];
            digitalWrite(LEDS[k], HIGH);
        }
        else
          digitalWrite(LEDS[k], LOW);
    }
}
