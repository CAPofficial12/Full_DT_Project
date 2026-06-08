#include <Arduino.h>
#include <Servo.h>

Servo TopLeft;
Servo TopRight;
Servo BottomLeft;
Servo BottomRight;

void PlatforM(int);                                                                            
void Bottom(int);

void setup() {
  TopLeft.attach(9);
  TopRight.attach(6);
  BottomLeft.attach(3);
  BottomRight.attach(5);
}

void loop() {
  PlatforM(60);
  Bottom(45);
}

void PlatforM(int angle){
  TopRight.write(angle);
  TopLeft.write(180-angle);
}

void Bottom(int angle){
  BottomLeft.write(angle);
  BottomRight.write(180-angle);
}