#include<SoftwareSerial.h>

int irvalue;
int motorIn11=6, motorIn12=5, motorIn21=11, motorIn22=10;
const int trigPin = 2;
const int echoPin = 3;
const int recho = 10;
const int lecho=11;
int ir=A0,mq135=A1,mq9=A2;
long duration;
int distanceCm;
int rdist, ldist;
int mq135sensorValue;
String state;
int velo=200;
int buzz=9;

void setup() {

  pinMode(ir, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
  pinMode(motorIn11, OUTPUT);
  pinMode(motorIn12, OUTPUT);
  pinMode(motorIn21, OUTPUT);
  pinMode(motorIn22, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(recho, INPUT);
  pinMode(lecho, INPUT);
  pinMode(buzz, OUTPUT);

  

}

void Forward(){
  analogWrite(motorIn11, 0);
  analogWrite(motorIn12, velo);
  analogWrite(motorIn21, 0);
  analogWrite(motorIn22, velo);
}

void Stop(){
  analogWrite(motorIn11, 0);
  analogWrite(motorIn12, 0);
  analogWrite(motorIn21, 0);
  analogWrite(motorIn22, 0);
}

void Left(){
  analogWrite(motorIn11, 0);
  analogWrite(motorIn12, velo);
  analogWrite(motorIn21, velo);
  analogWrite(motorIn22, 0);
}

void Right(){
  analogWrite(motorIn11, velo);
  analogWrite(motorIn12, 0);
  analogWrite(motorIn21, 0);
  analogWrite(motorIn22, velo);
}


void beep(int buzzer){
  analogWrite(buzz, buzzer);      // Almost any value can be used except 0 and 255
                           // experiment to get the best tone
  //delay(delayms);          // wait for a delayms ms
  //analogWrite(buzz, 0);       // 0 turns it off
  //delay(delayms);          // wait for a delayms ms   
}

void loop() {

  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm= duration*0.034/2;
  
  irvalue=analogRead(A0);
  if(irvalue<105){
    Serial.println("Fire detected!");
    beep(20);
  }
  else{ beep(0);
  
  mq135sensorValue = analogRead(mq135);
  if(mq135sensorValue>400){
    Serial.println("Air quality alert");
    beep(20);
  }
  else if(mq135sensorValue>700){
    Serial.println("Severe air quality alert");
    beep(30);
  }
  else beep(0);
  }
  if(distanceCm>25)
      Forward();
  else{
      //obstacle avoiding
      Right();
      delay(800);
      Forward();
      delay(1600);
      Left();
      delay(800);
      Forward();
  }
  


  Serial.println("mq135");
  Serial.println(mq135sensorValue);
  Serial.println("dist");
  Serial.println(distanceCm);
  Serial.println("ir");
  Serial.println(irvalue);
  

}
