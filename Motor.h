class Motor {
  int modePin1;
  int modePin2;
  int enablePin;

  public:
  Motor(int m1, int m2, int en){
    modePin1=m1;
    modePin2=m2;
    enablePin=en;
    pinMode(modePin1, OUTPUT);
    pinMode(modePin2, OUTPUT);
    pinMode(enablePin, OUTPUT);
  }
  void run(int speed){
    if (speed>=0){
      digitalWrite(modePin1, HIGH);
      digitalWrite(modePin2, LOW);
      analogWrite(enablePin, speed);
    }
    else{
      digitalWrite(modePin2, HIGH);
      digitalWrite(modePin1, LOW);
      analogWrite(enablePin, -speed);
    }
  }
  void brake(int speed){
    digitalWrite(modePin1, LOW);
      digitalWrite(modePin2, LOW);
      analogWrite(enablePin, speed);
  }
};
//class Motor{
//  int modePin1; int modePin2;
//  int enablePin;
//  int encoderPin;
//  int edgeCount;
//  int lowThresh;
//  int highThresh;
//  int countState;
//  public:
//     Motor(int m1, int m2, int en, int encoder, int lThresh, int hThresh)
//     {
//      modePin1=m1;
//      modePin2=m2;
//      enablePin=en;
//      encoderPin=encoder;
//      lowThresh=lThresh;
//      highThresh=hThresh;
//      pinMode(modePin1, OUTPUT);
//      pinMode(modePin2,OUTPUT);
//      pinMode(enablePin,OUTPUT);
//      edgeCount=0;
//      countState=LOW;
//     }
//     void run(int power){
//      if(power>0){
//        digitalWrite(modePin1,HIGH);
//        digitalWrite(modePin2, LOW);
//        analogWrite(enablePin,power);
//      }
//      else
//        {
//        digitalWrite(modePin2,HIGH);
//        digitalWrite(modePin1,LOW);
//        analogWrite(enablePin,-power);
//        }
//     }
//     void brake(int power){
//      digitalWrite(modePin1,LOW);
//      digitalWrite(modePin2, LOW);
//      analogWrite(enablePin,power);
//     }
//     void updateCount(){
//      int reading=analogRead(encoderPin);
//      if(countState==HIGH &&reading<lowThresh){
//        edgeCount++;
//        countState=LOW;
//      }
//      else if(countState==LOW&&reading>highThresh){
//        edgeCount++;
//        countState=HIGH;
//      }
//     }
//     void resetCount(){
//      edgeCount=0;
//     }
//     int getCount(){
//      return edgeCount;
//     }
//};
//

