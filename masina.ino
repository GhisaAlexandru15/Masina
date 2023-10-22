#include "senzorDistanta.h"
int motorStanga1 = 12;
int motorStanga2 = 13;
int vitezaStanga = 11; 
int motorDreapta1 = 9;
int motorDreapta2 = 8;
int vitezaDreapta = 10; 
int cod[2]={0,0}, semnalB;
int bec = 2, difuzor = 3;
bool stareBec=false, stareDifuzor=false;
int numar=0;

void setup() {
  pinMode(bec, OUTPUT);
  pinMode(difuzor, OUTPUT);
  digitalWrite(bec,LOW);
  analogWrite(difuzor, 255);
  pinMode(motorStanga1, OUTPUT);
  pinMode(motorStanga2, OUTPUT);
  pinMode(motorDreapta1, OUTPUT);
  pinMode(motorDreapta2, OUTPUT);
  digitalWrite(motorStanga1, LOW);
  digitalWrite(motorStanga2, LOW);
  digitalWrite(motorDreapta1, LOW);
  digitalWrite(motorDreapta2, LOW);
  analogWrite(vitezaStanga, 150);
  analogWrite(vitezaDreapta, 150);
  setupD();
  Serial.begin(9600);
}

int semnalBluetooth(){
  int semnal=0;
  if(Serial.available()>0)
  {
    semnal=Serial.read();
    if(semnal>60)
    { 
      cod[0]=0; cod[1]=0;
      return semnal;
    }
    else if(!cod[0]) cod[0]=semnal-48;
    else if(!cod[1])
    {
      cod[1]=semnal-48;
      semnal=(cod[0]*10+cod[1])*2+100; //merge de la 20 la 100
      cod[0]=0; cod[1]=0;
      return semnal;
    }
  }
  return semnal;
}

void viteza(int viteza){
  
  analogWrite(vitezaStanga, viteza/100.0*255);
  analogWrite(vitezaDreapta, viteza/100.0*255);
}

void bec_(){
  stareBec=!stareBec;
  if (stareBec) digitalWrite(bec, HIGH);
  else digitalWrite(bec,LOW);
}

void difuzor_(){
  stareDifuzor=!stareDifuzor;
  if (stareDifuzor) analogWrite(difuzor, 127);
  else analogWrite(difuzor, 255);
}

void fata(){
  digitalWrite(motorStanga1, LOW);
  digitalWrite(motorStanga2, HIGH);
  digitalWrite(motorDreapta1, LOW);
  digitalWrite(motorDreapta2, HIGH);
}

void spate(){
  digitalWrite(motorStanga1, HIGH);
  digitalWrite(motorStanga2, LOW);
  digitalWrite(motorDreapta1, HIGH);
  digitalWrite(motorDreapta2, LOW);
}

void fataD(){
  digitalWrite(motorStanga1, LOW);
  digitalWrite(motorStanga2, HIGH);
  digitalWrite(motorDreapta1, HIGH);
  digitalWrite(motorDreapta2, LOW);
}

void fataS(){
  digitalWrite(motorStanga1, HIGH);
  digitalWrite(motorStanga2, LOW);
  digitalWrite(motorDreapta1, LOW);
  digitalWrite(motorDreapta2, HIGH);
}

void spateD(){
  digitalWrite(motorStanga1, HIGH);
  digitalWrite(motorStanga2, LOW);
  digitalWrite(motorDreapta1, LOW);
  digitalWrite(motorDreapta2, HIGH);
}

void spateS(){
  digitalWrite(motorStanga1, LOW);
  digitalWrite(motorStanga2, HIGH);
  digitalWrite(motorDreapta1,HIGH);
  digitalWrite(motorDreapta2, LOW);
}

void oprireMotoare(){
  digitalWrite(motorStanga1, LOW);
  digitalWrite(motorStanga2, LOW);
  digitalWrite(motorDreapta1, LOW);
  digitalWrite(motorDreapta2, LOW);
}
void control(){
 semnalB=semnalBluetooth();
  if (semnalB==65 || semnalB==67 || semnalB==69)
    if(distance2_()<=7)
      semnalB=0;
  if(semnalB > 100) viteza(semnalB-100);
  else
  switch(semnalB){
    case 76:  bec_();      break;
    case 83:  difuzor_();  break;
    case 65:  fata();     break;
    case 67:  fataD();    break;
    case 69:  fataS();    break;
    case 66:  spate();    break;
    case 68:  spateD();   break;
    case 70:  spateS();    break;
    default:  oprireMotoare(); break;
  }
  semnalB=0;
  delay(100);
}
void autonom(){
  delay(3000);
  fata();
  delay(1500);
  spateS();
  delay(1350);
  oprireMotoare();
  bec_();
  fata();
  delay(1000);
  oprireMotoare();
  bec_();
  delay(200);
  bec_();
  delay(200);
  bec_();
  delay(200);
  bec_();
  delay(200);
  bec_();
  delay(200);
  bec_();
  delay(200);
  bec_();
}
void loop() {
  control();
}
