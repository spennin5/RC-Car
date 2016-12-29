#include <SPI.h>
#include "RF24.h"
RF24 radio(7, 8);
const int PACKETSIZE = 8;
byte packet[PACKETSIZE]; //holds the data
int joySelPin = 9;
int joyXPin = A0;
int joyYPin = A1;
int piezoReadPin = A2;
int radioChannel = 25;//match this with receiver code
byte address[8] = {"30281"};//match this with receiver code
void setup() {
  Serial.begin(9600);
  pinMode(joySelPin, INPUT_PULLUP);
  pinMode(piezoReadPin, INPUT);
  radio.begin();
  radio.setChannel(radioChannel);
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening();
  radio.openWritingPipe(address);
}

void loop() {
  // put your main code here, to run repeatedly:
  int *intPacket = (int *) packet;
  intPacket[0] = analogRead(joyXPin);
  intPacket[1] = analogRead(joyYPin);
  intPacket[2] = digitalRead(joySelPin);
  intPacket[3] = analogRead(piezoReadPin);
  radio.write((void*)packet, PACKETSIZE, false);
}
