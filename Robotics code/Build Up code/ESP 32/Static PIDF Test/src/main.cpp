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

//Setting up motors
#define enA 1
#define enB 2
#define in1 3
#define in2 4
#define in3 5
#define in4 6

//Set up PIDF

float Kp = 0;
float Ki = 0;
float Kd = 0;
float Kf = 0;

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

  //Setup Motor intial direction
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void PIDF(int target, int current){
  double error = target - current;
  double dt;
}

void loop() {
  Platform(45); // TODO: Test which angles work best
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