#include <Arduino.h>
#include <ESP32Servo.h>

const int BottomLeftPin = 23;
const int BottomRightPin = 22;

Servo BottomLeft;
Servo BottomRight;

void setup() {
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);

  BottomLeft.setPeriodHertz(50); //Test at 333Hz
  BottomRight.setPeriodHertz(50);

  BottomLeft.attach(BottomLeftPin, 500, 2500);
  BottomRight.attach(BottomRightPin, 500, 2500); 
}

void loop() {
  BottomLeft.write(90);
  BottomRight.write(90);
}
