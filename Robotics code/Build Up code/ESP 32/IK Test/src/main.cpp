#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include <Arduino.h>
#include <ESP32Servo.h>
using namespace std;

// Arm Lengths
double l1 = 1;
double l2 = 2;

// Functions
double Sum(double a, double b);
void print(vector<double> rec);
vector<double> Polar();

void setup(){

}

void loop(){

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
