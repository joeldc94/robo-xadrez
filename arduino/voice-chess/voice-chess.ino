#include <Arduino.h>
//#include "io.h"


String comando = "";
bool comandoRecebido = false;
bool comandoValidado = false;
char origemLetra;
char destinoLetra;
int origemNumero;
int destinoNumero;

int tabuleiro[8][8][3];


//////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  Serial.println("Inicializando Comunicação...");
  Serial1.begin(9600); //utilizar BaudRate 9600 para serialBT
  Serial.println("Inicializando Comunicação com Módulo Bluetooth...");
  Serial.println("Representação do tabuleiro...");

  for(int i=0; i<8; i++){
    tabuleiro[i][0][0] = i+1;
    tabuleiro[i][1][0] = i+8+1;
    tabuleiro[i][2][0] = 0;
    tabuleiro[i][3][0] = 0;
    tabuleiro[i][4][0] = 0;
    tabuleiro[i][5][0] = 0;
    tabuleiro[i][6][0] = i+16+1;
    tabuleiro[i][7][0] = i+24+1;
  }
  imprimeTabuleiro();
}

//////////////////////////////////////////////////////////////////////////
void loop()
{
  if(comandoRecebido && !comandoValidado){
    comandoRecebido = false;
    Serial.println("Iniciando Validaçao");
    validacaoComando();
    if(comandoValidado){
      realizaMovimento();
      imprimeTabuleiro();
    }
    
  }
}

//////////////////////////////////////////////////////////////////////////
void serialEvent1() {
   if(Serial1.available()) { // Verificar se há caracteres disponíveis
    comando = Serial1.readString(); // Armazena string de comando disponivel
    comandoRecebido = true; 
    comandoValidado = false;   
  }
}

//////////////////////////////////////////////////////////////////////////
//valida o comando recebido via serial
void validacaoComando(){
  Serial.print("Iniciando veriicação do comando: ");
  Serial.println(comando);
  if(verificaComprimentoComando()){
    Serial.println("1) Comprimento OK");
    if(verificaOrigemValida()){
      Serial.print("2) Origem: ");Serial.print(origemLetra);Serial.println(origemNumero);
      //verifica destino:
      if(verificaDestinoValido()){
        Serial.print("3) Destino: ");Serial.print(destinoLetra);Serial.println(destinoNumero);
        if(verificaMesmaOrigemDestino()){
          Serial.println("4) Comando Validado!!!");
          comandoValidado = true;
        }
        else
          Serial.println("4) Comando Inválido: Origem igual ao Destino");
      }     
      else
        Serial.println("3) Destino Inválido!"); 
    }
    else
      Serial.println("2) Origem Inválida!");
  }
  else
    Serial.println("1) Comprimento do comando inválido!");
}


//////////////////////////////////////////////////////////////////////////
// verifica comprimento da string recebida. 
// Passa a string do comando para letras maiusculas
// retorna TRUE se for valida, senao FALSE
bool verificaComprimentoComando(){
    if(comando.length() > 3){
      comando.toUpperCase();
      return true;
    }
    return false;
}


//////////////////////////////////////////////////////////////////////////
//verifica se o comando de origem está dentro dos limites do tabuleiro
//retorna true se estiver OK ou false se não estiver
bool verificaOrigemValida(){
  String auxStr;
  int auxInt;
  //verifica se o primeiro char está entre A(65) e H(72)
  if(comando.charAt(0)>=65 && comando.charAt(0) <= 72){
     auxStr = comando.charAt(1); //copia segundo char para auxiliar
     auxInt = auxStr.toInt(); //transforma aux para Int
     if(auxInt >= 1 && auxInt <= 8){   // verifica se o segundo char está entre 1 e 8     
       origemLetra = comando.charAt(0);
       origemNumero = auxInt;
       return true;
     }
  }
  return false;
}


//////////////////////////////////////////////////////////////////////////
//verifica se o comando de destino está dentro dos limites do tabuleiro
//retorna true se estiver OK ou false se não estiver
bool verificaDestinoValido(){
  String auxStr;
  int auxInt;
  //verifica se o orimeiro char está entre A(65) e H(72)
  if(comando.charAt(3)>=65 && comando.charAt(3) <= 72){
     auxStr = comando.charAt(4); //copia segundo char para auxiliar
     auxInt = auxStr.toInt(); //transforma aux para Int
     if(auxInt >= 1 && auxInt <= 8){   // verifica se o segundo char está entre 1 e 8     
       destinoLetra = comando.charAt(3);
       destinoNumero = auxInt;
       return true;
     }
  }
  return false;
}


//////////////////////////////////////////////////////////////////////////
//verifica se a origem é igual ao desino
//retorna true se estiver OK ou false se não estiver
bool verificaMesmaOrigemDestino(){
  if(origemLetra == destinoLetra)
    if(origemNumero == destinoNumero)
      return false;
   return true;
}

void imprimeTabuleiro(){
  Serial.println();
  Serial.println("Tabuleiro de jogo!");
  Serial.println();
  Serial.println("    -------------------------------------------------");
  for(int j=7; j>=0; j--){
    Serial.print(j+1);
    Serial.print(": |");
    for(int i=0;i<8;i++){
      if(tabuleiro[i][j][0]<=9)
        Serial.print(" ");
      Serial.print("  ");
      Serial.print(tabuleiro[i][j][0]);
      Serial.print("  ");
      if(i==7){
        Serial.println(" |");
        if(j!=0)
        Serial.println("   |                                                 |");
      }
    } 
  } 
  Serial.println("    -------------------------------------------------");
  Serial.println("       A  |  B  |  C  |  D  |  E  |  F  |  G  |  H");
  Serial.println();
}

bool validaJogada(){
  
}

void realizaMovimento(){
  int auxPeca;
  Serial.println(tabuleiro[origemLetra-65][origemNumero-1][0]);
  Serial.println(tabuleiro[destinoLetra-65][destinoNumero-1][0]);
  auxPeca=tabuleiro[origemLetra-65][origemNumero-1][0];
  tabuleiro[origemLetra-65][origemNumero-1][0]=0;
  tabuleiro[destinoLetra-65][destinoNumero-1][0]=auxPeca;
  comandoValidado = false;
}
