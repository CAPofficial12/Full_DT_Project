#include <Arduino.h>
#include <ESP32Servo.h>

// Setting Up Servos
Servo BottomLeft;
const int BottomLeftPin = 23;

Servo BottomRight;
const int BottomRightPin = 22;

Servo TopLeft;
const int TopLeftPin = 21;

Servo TopRight;
const int TopRightPin = 20;


void setup() {
  // Sets up timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  //Sets up Servo frequency
  BottomLeft.setPeriodHertz(50);
  BottomRight.setPeriodHertz(50);
  TopLeft.setPeriodHertz(50);
  TopRight.setPeriodHertz(50);

  //Attaches Servos to their repective mins and configures frequency
  BottomLeft.attach(BottomLeftPin, 500, 2500);
  BottomRight.attach(BottomRightPin, 500, 2500); 
  TopLeft.attach(TopLeftPin, 500, 2500);
  TopRight.attach(TopRightPin, 500, 2500); 
}

void loop() {
  Platform(45);
  Top(90);


}

void Platform(int angle){
  BottomLeft.write(angle);
  BottomRight.write(180 - angle);
}

void Top(int angle){
  TopLeft.write(angle);
  TopRight.write(180 - angle);
}