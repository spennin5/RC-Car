#include "Motor.h"
#include <SPI.h>
#include "RF24.h"
#include <Servo.h>
Servo servo;
RF24 radio(7,8);
const int PACKETSIZE = 8;
byte packet[PACKETSIZE]; //holds the data
int radioChannel = 25; //Must match receiver channel
byte address[8] = {"30281"}; //Must match receiver address
int buttonState;

int piezoPin = A0;
int ledPin = A1;
int laserPin = A3;
int buttonPin = A5;
bool pressed;
Motor motor(2,4,3);
Motor motor2(5,9,6);
int Power;
int Differential;
int leftPower;
int rightPower;

void setup(){
  Serial.begin(115200);
  servo.attach(10);
  radio.begin();
  pinMode(A1,OUTPUT);
  pinMode(A5,INPUT_PULLUP);
  pinMode(A2,OUTPUT);
  pinMode(laserPin,OUTPUT);
  radio.setChannel(radioChannel);
  radio.setPALevel(RF24_PA_HIGH);
  radio.openReadingPipe(1,address);
  radio.startListening();
  buttonState=analogRead(buttonPin);
  }
  
void loop(){
  int piezoReading=analogRead(piezoPin);
  if(radio.available()){
    int *intPacket= (int *)packet;
    radio.read(packet,8);
    if(intPacket[2]==0){
      servo.write(180);
    }
    if(intPacket[2]==1){
      servo.write(0);
  }
  int laserPower = map(intPacket[3],0,1023,0,255);
  Serial.println("Braking power:"+brakingPower);
  Power= map(intPacket[0],0,1023,-255,255);
  Differential=map(intPacket[1],0,1023,-255,255);
  leftPower=map((Power+Differential),-510,510,-255,255);
  rightPower=map((Power-Differential),-510,510,-255,255);
  int newButtonState=digitalRead(buttonPin);
  if(buttonState==1&&newButtonState==0){
    pressed=!pressed;
  }
  buttonState=newButtonState;
  
  if(leftPower<-10 && rightPower<-10){
    digitalWrite(A2,HIGH);
    analogWrite(laserPin,laserPower);
  }
  else{
    digitalWrite(A2,LOW);
    analogWrite(laserPin,laserPower);
  }
  delay(10);
  goCar();
  Serial.flush();
  }
  //Turns on yellow LED if car collides with something
  if(piezoReading>=250){
    digitalWrite(ledPin,HIGH);
  }
  if(piezoReading<250){
    digitalWrite(ledPin,LOW);
  }
}
void goCar(){
  if(pressed){
    motor.run(-(2*leftPower-1));
    motor2.run(-(2*rightPower-1));
  }
  else if(!pressed){
    motor2.brake(255);
    motor.brake(255);
  }
}
//#include "Motor.h"
//Motor motor(2,4,3);
//Motor motor2(5,7,6);
//void setup() {
//  // put your setup code here, to run once:
//
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//      motor.run(255);
//      motor2.run(255);
//}
//#include "Motor.h"
//Motor mL(2,4,3,A0,700,900);
//Motor mR(5,7,6,A1,700,900);
//int numPresses = 0;
//int currentButtonState;
//static boolean paused=true;
//boolean pingSent=false;
//boolean pulseStarted=false;
//int trigPin=10;
//int echoPin=11;
//unsigned long pulseStartTime=0;
//unsigned long lastPingTime=0;
//unsigned long lastTime=0;
//void setup(){
//  mL.run(0); mR.run(0);
//  Serial.begin(9600);
//  pinMode(9, INPUT_PULLUP);
//  pinMode(trigPin,OUTPUT);
//  pinMode(echoPin,INPUT);
//  currentButtonState = digitalRead(9);
//}
//void loop(){
//  pinMode(trigPin,OUTPUT);
//  pinMode(echoPin,INPUT);
//  int newButtonState = digitalRead(9);
//  if(currentButtonState == 1 && newButtonState == 0){
//    paused=!paused;
//  }
//  currentButtonState=newButtonState;
//  WaitMove(100,100,255,255);
//  WaitMove(15,15,255,-255);
//  delay(10);
// 
//}
//
//
//float checkUltrasonic(){
//  unsigned long currentTime = micros();
//  int echoReading = digitalRead(echoPin);
//  if(currentTime-lastPingTime>60000){
//    digitalWrite(trigPin,LOW);
//    delayMicroseconds(2);
//    digitalWrite(trigPin,HIGH);
//    delayMicroseconds(10);
//    digitalWrite(trigPin, LOW);
//    lastPingTime=currentTime;
//    pingSent=true;
//    pulseStarted=false;
//    return -1;
//  }
//  else if(echoReading==HIGH&&!pulseStarted&&pingSent){
//    pulseStartTime=micros();
//    pulseStarted=true;
//    return -1;
//  }else if(echoReading==LOW&&pulseStarted&&pingSent){
//    pingSent=false;
//    return(micros()-pulseStartTime)/2.0*.000340;
//  }
//}
//
//void WaitMove(int numL, int numR, int lPower, int rPower){
//  mL.resetCount(); mR.resetCount();
//  //mL.run(lPower); mR.run(rPower);
//  while(!paused){
//    while(true){
//      double distance=checkUltrasonic();
//      while(!paused&&(distance>=.3)){
//        int newButtonState=digitalRead(9);
//        distance=checkUltrasonic();
//        mL.updateCount();
//        mR.updateCount();
//        int lCount=mL.getCount(); int rCount=mR.getCount(); 
//        lCount=mL.getCount(); rCount=mR.getCount();
//        if(rCount>=numL){
//          lPower=0;
//        }
//        if (rCount>=numR){
//          rPower=0;
//        }
//        Serial.println(lCount);
//        Serial.println(rCount);
//        Serial.println(numL);
//        Serial.println(numR);
//        if(lCount>=numL&&rCount>=numR){
//          Serial.print("Aqui");
//          break;
//        }
//        if(currentButtonState!=newButtonState){
//          if(paused){  
//            paused=false;
//          }
//          else{
//            paused=true;
//          }
//          delay(50);
//          
//        }
//        if(paused){
//          mR.run(0);
//          mL.run(0);
//        }
//        else{
//          mR.run(rPower);
//          mL.run(lPower);
//  
//        }
//        currentButtonState=newButtonState;
//      }
//    }
//  }
//}


