#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>

#include <Arduino.h>
#include <ESP32Servo.h>
using namespace std;


//Servos
Servo BottomLeft;
const int BottomLeftPin = 23;

Servo BottomRight;
const int BottomRightPin = 22;

Servo TopLeft;
const int TopLeftPin = 21;

Servo TopRight;
const int TopRightPin = 20;

// Arm Lengths
double l1 = 1;
double l2 = 2;

// Functions
double Sum(double a, double b);
void print(vector<double> rec);
vector<double> Polar(double x, double y);

void setup(){
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

void loop(){
  vector<double> angles = Polar(1,1);
  vector<double> offset = {0,0};
  double PWM_conversion = 2000.0/PI*180.0;
  int Signal1 = (offset[0] + angles[0]) * PWM_conversion + 500;
  int Signal2 = (offset[1] + angles[1]) * PWM_conversion + 500;

  BottomLeft.writeMicroseconds(Signal1);
  TopLeft.writeMicroseconds(Signal2);
}

vector<double> Polar(double x, double y){
    double r = sqrt(Sum(x, y));

    if (r > l1 + l2 || r < abs(l1 - l2)) {
        return {};
    }

    double theta = atan2(y,x);

    
    double theta2 = acos(
        (Sum(x, y) - l1*l1 - l2*l2)
        / (2*l1*l2)
    );

    double theta1 =
        atan2(y, x)
        - atan2(
            l2 * sin(theta2),
            l1 + l2 * cos(theta2)
        );

    return {theta1, theta2};
}

double Sum(double a, double b){
    return a*a + b*b;
}

void print(vector<double> rec){
    for (double i:rec){
        cout << i*180/PI << endl;
    }
}