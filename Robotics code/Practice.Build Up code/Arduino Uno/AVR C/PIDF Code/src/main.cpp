#include <Arduino.h>
#include <Servo.h>
#include <MPU6050.h>
#include <Wire.h>

// All 4 servos
Servo servoTL;
Servo servoTR;
Servo servoBL;
Servo servoBR;

MPU6050 imu;

//Time Points
int t1;
int t2;

// Angles
int target;
int tilt;
int lastTilt;

//Proportional
double Kp;
double error;
double P;

//Derivative
double Kd;
double dt;
double derivative;
double D;

//Integral
double Ki;
double integral;
double I;

//Feedorward
double Kf;

//Fuction forward declaration
void fix_pos(int x);
void set_power(int x);

void setup() {

  //Set Imu caribration and orientation
  imu.CalibrateAccel();
  imu.CalibrateGyro();
  target = imu.getRotationY();    //Subject to change DOF

  //Connects servos to Pins
  servoTL.attach(0);
  servoTR.attach(1);
  servoBL.attach(2);
  servoBR.attach(3);

  // Set Motor to Pins
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  //Checks Tilt from 
  lastTilt = imu.getRotationY() - target;
}

void loop() {
  // Check time at start of loop
  t1 = micros();
  fix_pos(90);

  tilt = angl();
  error = tilt - target;

  t2 = micros();
  dt = t2 - t1;
  if (dt == 0){
    dt = 1;
  }
  derivative  = (tilt - lastTilt)/dt;
  /*
  integral = max(error * dt, 50);
  I = Ki * integral;
  */
  double out = Kp*error + Kd*derivative;
  Serial.println(out);

  set_power(out);
  lastTilt = tilt;
}



void fix_pos(int x) {
  servoTL.write(x);
  servoTR.write(x);
  servoBL.write(x);
  servoBR.write(x);
}

void set_power(int x){
  analogWrite(4,x);
  analogWrite(5,x);
}

double angl(){
  double angle = 0;
  float alpha = 0.98;

  float accelAngle = atan2(imu.getAccelerationX(), imu.getAccelerationZ()) * 180/PI;
  float gyroRate = imu.getRotationY() / 131.0; // 131 LSB/(°/s) at ±250°/s
  angle = alpha * (angle + gyroRate * dt/1000.0) + (1 - alpha) * accelAngle;
  return angle;
}