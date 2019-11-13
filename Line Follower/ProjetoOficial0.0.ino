/*
  ultima atualização dia 05/06/17 - VSSM -
  Metas para 06/06/17:
  .Corrigir defeitos no optico
  .Corrigir defeitos no desvio
  .Optimizar tempo de percurso
  .Corrigir possiveis bugs
*/

/*
Teoricamente o codigo ja ta pronto.
Falta só funcionar na pratica (ou seja, tudo).
*/

#include "Ultrasonic.h"
#define MOTA1 3
#define MOTA2 5
#define MOTB1 6
#define MOTB2 9  
#define trig 11
#define echo 12
#define led 2
#define optico 7

/*o b ta girando mais rapido*/
Ultrasonic ultrasonic(11,12);

void setup() {
  // put your setup code here, to run once:
  pinMode(MOTA1, INPUT);
  pinMode(MOTA2, INPUT);
  pinMode(MOTB1, INPUT);
  pinMode(MOTB2, INPUT);
  //referentes ao ultrasson
  pinMode(echo, INPUT); // define o pino 12 como entrada (recebe)
  pinMode(trig, OUTPUT); // define o pino 11 como saida (envia)
  pinMode(led, OUTPUT);
  pinMode(optico, INPUT);
}

int distanciaUltra();
void acelerar(int velocidadeA, int velocidadeB);
void curva(int lado);
void parar();
void desvio(int distInicial, int lado);
void segueLinha();
int velo[2][2] = {{85, 70}, {70, 80}};
int modo = 0;

void loop() {

 // acelerar(velo[modo][0], velo[modo][1]);
  int linha = digitalRead(optico);
  if(linha == 1) //mudei o valor para 1, estava  0
  {
    //segueLinha();
    /*modo = (modo+1)%2;
    digitalWrite(led, HIGH);*/
    acelerar(0, 150);
  }
  else if(linha == 0)
  {
    acelerar(150,0);
  }
  /*int dist = distanciaUltra();
    
  if(dist <= 15)
  {
    parar();
    desvio(dist, 0);
  }*/
}

int distanciaUltra()
{
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    int distancia = (ultrasonic.Ranging(CM));
    Serial.print("Distancia em CM: ");
    Serial.println(distancia);
    return distancia;
}

void acelerar(int velocidadeA, int velocidadeB)
{
  //Gira o Motor A no sentido horario
  analogWrite(MOTA1, velocidadeA);
  analogWrite(MOTA2, 0);

  //Gira o Motor B no sentido horario
  analogWrite(MOTB1, velocidadeB);
  analogWrite(MOTB2, 0);
}

void curva(int lado)
{
  //direita
  if(lado == 0)
  {
    analogWrite(MOTA1, 50);
    analogWrite(MOTA2, 0);

    analogWrite(MOTB1, 0);
    analogWrite(MOTB2, 50);
  } //Esquerda
  else if(lado == 1)
  {
    analogWrite(MOTA1, 0);
    analogWrite(MOTA2, 50);

    analogWrite(MOTB1, 50);
    analogWrite(MOTB2, 0);
  }
}

void parar()
{
  analogWrite(MOTA1, 255);
  analogWrite(MOTA2, 255);
  analogWrite(MOTB1, 255);
  analogWrite(MOTB2, 255);
}

/*direita 0 esquerda 1*/
void desvio(int distInicial, int lado)
{
  int dist = distInicial;
  int x = dist;
  int linha = 0;
  while(x/dist <= 3)
  {
    curva(0);
    x = distanciaUltra();
    delay(100);
  }

  delay(100);
  acelerar(85,65);
  delay(500);
  
  parar();
  delay(100);
  
  //Adicionado por Ramon 
  curva(1);
  delay(700);
  parar();
  delay(100);
  //-----------
  
  
  linha = digitalRead(optico);
  
  if(lado == 0)
  {    
    //linha = digitalRead(optico);
   /*lembrar de mudar condição de parada para quando encontrar linha*/
    while(linha != HIGH){
    digitalWrite(led, HIGH);
    acelerar(60, 70);
    x = distanciaUltra();
    if(x <= 10)
      desvio(x, 0);
    linha = digitalRead(optico);
    }
  }
  else if(lado == 1)
  {
    /*lembrar de mudar condição de parada para quando econtrar linha*/
    while(linha != HIGH)
    {
      digitalWrite(led, HIGH);
      acelerar(40, 20);
      x = distanciaUltra();
      if(x <= 10)
        desvio(x, 1);

      linha = digitalRead(optico);
    }
  }

  digitalWrite(led, LOW);
}

void segueLinha()
{
  //falta especificar oq e X!(Luiz Albuquerque)
  //TODO: renomear variavel x para achouOptico
  int x = 0, t = 1, i, lado = 0;
  while(1)
  {
  
    digitalWrite(led, HIGH);
    //0 = direita e 1 = esquerda
    curva(lado);
    //não entendi esse for(Luiz Albuquerque)
    for(i = 0; i < 10; i++)
    {
      x = digitalRead(optico);
      if(x == LOW)
      { 
        return;
      }
      //Pra que esse delay? 
      delay(t);
    } 
    lado = (lado+1)%2;
    t = t*2;
  }
}