#include <SoftwareSerial.h>         // Include the SoftwareSerial Library 

SoftwareSerial mySerial(4, 5);
#define DistanceEn_Pin 5
const int trigPin = 6;
const int echoPin = 7;
float duration, distance2; 
int i = 0;
long unsigned distance = 0;
uint8_t distanceValue[4] = {0,0,0,0};

void setupD() 
{
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(DistanceEn_Pin,OUTPUT);
  digitalWrite(DistanceEn_Pin,1);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
float distance_()
{
  while(mySerial.read() >= 0 );         //Empty the serial buffer
  digitalWrite(DistanceEn_Pin,0);      //Ultrasound can open
  while(mySerial.available() <= 4)  ;     //Waiting for the ultrasonic data window
  
  distanceValue[0] = mySerial.read();    //Extract the data
  if( distanceValue[0] == 0xff )       //Determine if data for ultrasonic module
  {
    for(i = 1;i <= 3;i ++)
    {
      distanceValue[i] = mySerial.read();
    }
   }
 
  digitalWrite(DistanceEn_Pin,1);       //Ultrasound can make
 
  distance = distanceValue[1] * 256 + distanceValue[2];                   //Data processing, calculating distance
  if((distanceValue[3] == distanceValue[1] + distanceValue[2] - 1))       //Data and check, can be removed
  {
    return distance/10;
  }
  else return 100;
}
 
float distance2_(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance2 = (duration*.0343)/2;
  return distance2;
}

