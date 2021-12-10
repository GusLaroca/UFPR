#include <LiquidCrystal.h>// inclusão da biblioteca auxiliar do display LCD
#include <Servo.h>// inclusão da biblioteca auxiliar do mini servo motor

// abaixo as atribuições de número do pino a cada componete ligado a placa
const int LEDativar = 13;// pino 13, LED indicando acionamento do servo motor
const int USTRIG = 11, USECHO = 10;// pinos 10 e 11, cominicação com sensor de distancia
const int btativar = 9, btporcao = 8, bthora = 7;/* pinos 7, 8 e 9, respectivamente botão de
ajuste de hora, botão de ajuste de porções e botão de ativação instantânea*/
const int servomotor = 6;// pino 6, corresponde com o mini servo motor
const int LED100 = 1, LED80 = 2, LED60 = 3, LED40 = 4, LED20 = 5;/* os pinos de 1 a 5 
correspondem com os leds que indicam o nível de alimento ainda dissponível no reservatório*/
const int RS = A0, EN = A1, D4 = A2, D5 = A3, D6 = A4, D7 = A5;/* os pinos analógicos da placa
se correspondem ao display LCD*/
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);// informa os pinos responsáveis pelo display LCD

Servo servo;// nomeia um servo motor como "servo"

long time = 0; // variável que armazena tempo de operação decorrido

//abaixo estão declaradas as variáveis responsáveis pelos ajustes de porção e hora
int fatortime = 4;
int porcao = 01, maxporcao = 9, incporcao = 1, minporcao = 1;
int hora = 4, maxhora = 8, inchora = 2, minhora = 4;

void setup()
{
  pinMode(LEDativar, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(btativar, INPUT_PULLUP);
  pinMode(btporcao, INPUT_PULLUP);
  pinMode(bthora, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(USTRIG, OUTPUT);
  pinMode(USECHO, INPUT);
  pinMode(LED100, OUTPUT);
  pinMode(LED80, OUTPUT);
  pinMode(LED60, OUTPUT);
  pinMode(LED40, OUTPUT);
  pinMode(LED20, OUTPUT);
  
  servo.attach(servomotor);// inicia o servo motor
  servo.write(40);// posiciona o servo motor em 40º
  
  lcd.begin(16,2);// informa o tamanho do display LCD utilizado
  lcd.clear();// limpa o visor do display LCD
}

void loop()
{
  ativarservo(porcao);// chama a função que ativa o servo motor
  time = millis();
  delay(10);
  
  while(millis() < fatortime * 15000 + time){

  int armazenamento = medirarmazenamento(USTRIG, USECHO);
  nivelarmazenamento(armazenamento);
  porcao = ajusteporcaohora(btporcao, porcao, incporcao, minporcao, maxporcao);
  hora = ajusteporcaohora(bthora, hora, inchora, minhora, maxhora);
 
  if(digitalRead(btativar) == LOW){
    delay(80);
    ativarservo(porcao);  
    }
  
  lcd.setCursor(3, 0);
  lcd.print(porcao);
  lcd.print(" porcoes");
  lcd.setCursor(1, 2);
  lcd.print("a cada ");
  lcd.print(hora);
  lcd.print(" horas");
  
  }
  fatortime = hora;
}

int ajusteporcaohora(int botao, int var, int varinc, int minvar, int maxvar)
{
 delay(80); 
  if(digitalRead(botao) == LOW){
    var = var + varinc;
    if(var > maxvar)
      var = minvar;
    }
  return var;
 }
 
void ativarservo(int porcao)
{
  int tempo;
  tempo = 2000*porcao;

  digitalWrite(LEDativar, HIGH);
  tone(buzzer, 400);
  delay(700);
  noTone(buzzer);
  servo.write(130);
  delay(tempo);
  servo.write(40);
  digitalWrite(LEDativar, LOW);
}

int medirarmazenamento(int TRIG,int ECHO){
  digitalWrite(TRIG,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG,LOW);
  
  return pulseIn(ECHO,HIGH)/58;
}

void nivelarmazenamento(int distancia){
  if(distancia <= 5){
    digitalWrite(LED100, HIGH);
    digitalWrite(LED80, HIGH);
    digitalWrite(LED60, HIGH);
    digitalWrite(LED40, HIGH);
    digitalWrite(LED20, HIGH);
  }
  else if(distancia <= 8 && distancia > 5){
    digitalWrite(LED100, LOW);
    digitalWrite(LED80, HIGH);
    digitalWrite(LED60, HIGH);
    digitalWrite(LED40, HIGH);
    digitalWrite(LED20, HIGH);
  }
  else if(distancia <= 11 && distancia > 8){
    digitalWrite(LED100, LOW);
    digitalWrite(LED80, LOW);
    digitalWrite(LED60, HIGH);
    digitalWrite(LED40, HIGH);
    digitalWrite(LED20, HIGH);
  }
  else if(distancia <= 14 && distancia > 11){
    digitalWrite(LED100, LOW);
    digitalWrite(LED80, LOW);
    digitalWrite(LED60, LOW);
    digitalWrite(LED40, HIGH);
    digitalWrite(LED20, HIGH);
  }
  else{
    digitalWrite(LED100, LOW);
    digitalWrite(LED80, LOW);
    digitalWrite(LED60, LOW);
    digitalWrite(LED40, LOW);
    digitalWrite(LED20, HIGH);
  }
}
