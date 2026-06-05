#include <Arduino.h>
#include <Servo.h>

Servo TopLeft;
Servo TopRight;
Servo BottomLeft;
Servo BottomRight;

void Lock_Servo(int);                                                                                       

void setup() {
  TopLeft.attach(5);
  TopRight.attach(6);
}

void loop() {
  TopRight.write(0);
  TopLeft.write(180);
}

void Lock_Servo(int angle){
  long milli = map(angle, 0, 180, 0, 255);
  analogWrite(5, milli);
  analogWrite(6, milli);
}