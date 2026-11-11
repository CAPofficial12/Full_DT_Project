#include <Arduino.h>
#include <ESP32Servo.h>

const int BottomLeftPin = 17;
const int BottomRightPin = 5;

Servo BottomLeft;
Servo BottomRight;

void setup() {
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);

  BottomLeft.setPeriodHertz(50);
  BottomRight.setPeriodHertz(50);

  BottomLeft.attach(BottomLeftPin, 500, 2500);
  BottomRight.attach(BottomRightPin, 500, 2500); 
}

void loop() {
  BottomLeft.write(0);
  delay(1000);
  BottomLeft.write(90);
  delay(1000);
  BottomLeft.write(180);
  delay(1000);
  BottomLeft.write(90);
  delay(1000);
}
