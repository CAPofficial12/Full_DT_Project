#include <Arduino.h>
#include <Servo.h>

Servo TopLeft;
Servo TopRight;
Servo BottomLeft;
Servo BottomRight;

int brightness = 0;
int multiplier = 1;
void Lock_Servo(int);                                                                                       

void setup() {
  TopRight.attach(6);
  BottomLeft.attach(9);
  BottomRight.attach(10);
  pinMode(5, OUTPUT);
}

void loop() {

  analogWrite(5, 100);
  delay(1000);
}

void Lock_Servo(int angle){
  long long milli = map(angle, 0, 180, 0, 255);
  TopLeft.write(angle);
}