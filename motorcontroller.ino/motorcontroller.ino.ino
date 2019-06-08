#include <Servo.h>
int motor[3];
Servo motorA;
Servo motorB;
Servo motorC;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("start");
  motor[0] = 110;
  motor[1] = 110;
  motor[2] = 110;
  motorA.attach(6);
  motorB.attach(7);
  motorC.attach(8);
  
  Serial.println("setup done");
}

void getAngles(){
  String received = Serial.readStringUntil('\n');
  String temp = "";
  int counter = 0;
  
  for(int i = 0; i < received.length(); i++){
    if(received[i] == ';'){
      motor[counter] = temp.toInt();
      //Serial.println(motor[counter]);
      counter ++;
      temp = "";
    }else if(received[i] == '\n'){
      
      return;
    } else{
      temp += received[i];
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
  if(Serial.available()){  
    
    getAngles(); 
  
    
  }
  setMotor();
  
  
}
