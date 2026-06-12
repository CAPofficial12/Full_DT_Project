#include <Arduino.h>
#include <ESP32Servo.h>

const int ServoPin = 23;
Servo testServo;

void setup() {
  ESP32PWM::allocateTimer(0);
  testServo.setPeriodHertz(50); //Test at 333Hz
  testServo.attach(ServoPin, 500, 2500);
}

void loop() {
  testServo.write(0);
  delay(1000);
  testServo.write(90);
  delay(1000);
  testServo.write(180);
  delay(1000);
  testServo.write(90);
  delay(1000);
}
