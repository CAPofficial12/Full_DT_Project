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
  TopLeft.attach(5);
  TopRight.attach(6);
  BottomLeft.attach(9);
  BottomRight.attach(10);
}

void loop() {
  /*
  if (brightness == 0){
    multiplier = 40;
  } else if(brightness == 255){
    multiplier = -40;
  }
  digitalWrite(5, HIGH);
  brightness += multiplier;
  */

  analogWrite(5, 128);
}

void Lock_Servo(int angle){
  long long milli = map(angle, 0, 180, 0, 255);
  TopLeft.write(angle);
}