#define MOTA1 3
#define MOTA2 5
#define MOTB1 6
#define MOTB2 9  


/*o b ta girando mais rapido*/

void acelerar(int velocidade)
{
  //Gira o Motor A no sentido horario
  analogWrite(MOTA1, velocidade);
  analogWrite(MOTA2, 0);

  //Gira o Motor B no sentido horario
  analogWrite(MOTB1, velocidade-10);
  analogWrite(MOTB2, 0);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(MOTA1, INPUT);
  pinMode(MOTA2, INPUT);
  pinMode(MOTB1, INPUT);
  pinMode(MOTB2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  acelerar(50);
  
}
