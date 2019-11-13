/**********************************************************
* UNIVERSIDADE FEDERAL DE PERNAMBUCO - UFPE
* CENTRO DE INFORMARICA - CIN
* GRUPO DE ENGENHARIA DA COMPUTACAO - GRECO
* INTRODUCAO A PROGRAMACAO COM GALILEO - IF669ECF
* CODIGO PARA TESTE DO SHIELD SENSOR OPTICO
***********************************************************
* DESCRICAO: ATIVACAO DO SENSOR E LEITURA DOS DADOS OBTIDOS
* ATRAVES DO MONITOR SERIAL DO GALILEO
********************************************************/

int inPin = 11; //pino de entrada no sensor
int valor = 0; //Inteiro que armazena o valor lido
 
void setup()
{
   Serial.begin(9600); //inicializando a porta serial
   pinMode(inPin, INPUT); //colocando a porta 11 como entrada
}
 
void loop()
{
    valor = digitalRead(inPin);//realizando a leitura no sensor optico
 
    if (valor == HIGH)
    {
       Serial.write("Preto"); //caso o valor seja alto - cor preta
    } 
	else
    {
       Serial.write("Branco"); //caso o valor lido seja baixo - cor branca
    }
}
