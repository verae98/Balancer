#include <Servo.h>
int motor[3];
Servo motorA;
Servo motorB;
Servo motorC;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("start");
  motor[0] = 90;
  motor[1] = 90;
  motor[2] = 90;
  motorA.attach(6);
  motorB.attach(7);
  motorC.attach(8);
  Serial.println("setup done");
}

void getAngles(){
  if(Serial.available()>0){
    String received = Serial.readString();
    Serial.println(received);
    String temp = "";
    int counter = 0;
    for(int i = 0; i < received.length(); i++){
      if(received[i] == ';'){
        motor[counter] = temp.toInt();
        Serial.println(motor[counter]);
        counter ++;
        temp = "";
      } else{
        temp += received[i];
      }
    }
  }
}

void setMotor(){
  motorA.write(motor[0]);
  motorB.write(motor[1]);
  motorC.write(motor[2]);
}

void loop() {
  // put your main code here, to run repeatedly:
  getAngles();
  setMotor();
  delay(100);
}
