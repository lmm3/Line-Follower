/**********************************************************
* UNIVERSIDADE FEDERAL DE PERNAMBUCO - UFPE
* CENTRO DE INFORMARICA - CIN
* GRUPO DE ENGENHARIA DA COMPUTACAO - GRECO
* INTRODUCAO A PROGRAMACAO COM GALILEO - IF669ECF
* CODIGO PARA TESTE DO SHIELD SENSOR ULTRASSONICO
***********************************************************
* DESCRICAO: ATIVACAO DO SENSOR E LEITURA DOS DADOS OBTIDOS
* ATRAVES DO MONITOR SERIAL DO GALILEO
********************************************************/

#include "Ultrasonic.h"
#define echoPin 13 //Pino 13 recebe o pulso do echo
#define trigPin 12 //Pino 12 envia o pulso para gerar o echo

//iniciando a função e passando os pinos
Ultrasonic ultrasonic(12,13);

int parou = 0;
 
void setup()
{
   pinMode(echoPin, INPUT); // define o pino 13 como entrada (recebe)
   pinMode(trigPin, OUTPUT); // define o pino 12 como saida (envia)
   Serial.begin(9600);
}
 
void loop()
{
//seta o pino 12 com um pulso baixo "LOW" ou desligado ou ainda 0
digitalWrite(trigPin, LOW);
// delay de 2 microssegundos
delayMicroseconds(2);
//seta o pino 12 com pulso alto "HIGH" ou ligado ou ainda 1
digitalWrite(trigPin, HIGH);
//delay de 10 microssegundos
delayMicroseconds(10);
//seta o pino 12 com pulso baixo novamente
digitalWrite(trigPin, LOW);
// função Ranging, faz a conversão do tempo de
//resposta do echo em centimetros, e armazena
//na variavel distancia
int distancia = (ultrasonic.Ranging(CM));
Serial.print("Distancia em CM: ");
Serial.println(distancia);
delay(1000); //espera 1 segundo para fazer a leitura
}
