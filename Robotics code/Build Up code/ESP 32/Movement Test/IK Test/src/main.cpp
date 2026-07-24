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
vector<double> Polar();

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
  vector<double> angles = Polar(5,5);
  vector<double> offset = {0,0};
  double PWM_conversion = 2000/180;
  int Signal1 = (offset[0] + angles[0]) * PWM_conversion + 500;
  int Signal2 = (offset[1] + angles[1]) * PWM_conversion + 500;

  BottomLeft.writeMicroseconds(Signal1);
  TopLeft.writeMicroseconds(Signal2);
}

vector<double> Polar(double x, double y){
    double r = 0, theta = 0;
    double ABC = 0, BAC = 0;
    double a1 = 0, a2 = 0;
    double num = 0, denom;

    r = sqrt(pow(x, 2) + pow(y,2));
    theta = atan(y/x);

    num = Sum(l1, l2) - pow(r,2);
    denom = (2*l1*l2);
    ABC = PI - acos(num/denom);

    num  = Sum(l1, r) - pow(l2, 2);
    denom = 2 * l1 * r;
    BAC = -acos(num/denom);

    a1 = BAC + theta;
    a2 = ABC - (PI - a2) + PI;

    vector<double> angles = {a1,a2};
    return angles;
}

double Sum(double a, double b){
    return pow(a,2) + pow(b,2);
}

void print(vector<double> rec){
    for (double i:rec){
        cout << i*180/PI << endl;
    }
}
