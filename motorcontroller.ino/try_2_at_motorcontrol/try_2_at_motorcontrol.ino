#include <Servo.h>
int motor[3];
Servo motorA;
Servo motorB;
Servo motorC;
String readString, servo1, servo2, servo3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Start");
  motor[0] = 90;
  motor[1] = 90;
  motor[2] = 90;
  motorA.attach(6);
  motorB.attach(7);
  motorC.attach(8); 
  Serial.println("setup done");
}

void loop() {
  while (Serial.available()) {
    delay(3);  //delay to allow buffer to fill 
    readString = Serial.readStringUntil('\n');
  }
  if (readString.length() == 12) {
      //Serial.println(readString); //see what was received
      
      // expect a string like 090;090;090; containing the two servo positions      
      servo1 = readString.substring(0, 3);
      servo2 = readString.substring(4, 7);
      servo3 = readString.substring(8, 11);

      motor[0] = servo1.toInt();
      motor[1] = servo2.toInt();
      motor[2] = servo3.toInt();
            
      motorA.write(motor[0]);
      motorB.write(motor[1]);
      motorC.write(motor[2]);
      
    readString="";
  } 

}
