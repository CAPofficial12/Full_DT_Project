#include <Arduino.h>
#include <Servo.h>

Servo TopLeft;
Servo TopRight;
Servo BottomLeft;
Servo BottomRight;

void setup() {
  // put your setup code here, to run once:
  TopLeft.attach(5);
  TopRight.attach(6);
  BottomLeft.attach(9);
  BottomRight.attach(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  Lock_Servo(90);
}

void Lock_Servo(int angle){
  TopLeft.write(angle);
  TopRight.write(angle);
  BottomLeft.write(angle);
  BottomRight.write(angle);
}