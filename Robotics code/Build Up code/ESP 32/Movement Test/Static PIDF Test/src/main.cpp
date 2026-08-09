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
unsigned long start = 0;
float lastError = 0;

float Kp = 0;
float Ki = 0;
float Kd = 0;
float Kf = 0;

//Forward decalertion of functions
void Platform(int angle);
void Top(int angle);
double PIDF(int target, int current);
int IMU_TILT();
void motors(int PWM);

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
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  ledcAttach(enA, 20000, 8);
  ledcAttach(enB, 20000, 8);
}

void loop() {
  Platform(45); // TODO: Test which angles work best
  Top(90);

  int tilt = IMU_TILT();
  float power = PIDF(0, tilt);
  motors(power);
}

void Platform(int angle){
  BottomLeft.write(angle);
  BottomRight.write(180 - angle);
}

void Top(int angle){
  TopLeft.write(angle);
  TopRight.write(180 - angle);
}

double PIDF(int target, int current){
  double error = target - current;

  double dt = (micros() - start)/1000000.0;
  double derivative = (error - lastError) / dt;

  double output = Kp * error + Kd* derivative +  * Kf;
  lastError = error;
  start = micros();

  return output;
}

int IMU_TILT(){
  return 0;
}

void motors(float PWM){

  //Caps PWM at 1
  PWM = constrain(PWM, -1.0f, 1.0f);
  PWM =* 255;

  //Control Motor Direction
  if(PWM > 0){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  } else if (PWM < 0){
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
  }

  //Sets motor speed to TT motors
  ledcWrite(enA, PWM);
  ledcWrite(enB, PWM);
}