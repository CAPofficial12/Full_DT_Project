#include <Arduino.h>


#define in1 4
#define in2 5
#define enA 9

#define in3 6
#define in4 7
#define enB 10

//Speeds
float motorSpeedA = 0;
float motorSpeedB = 0;

//Inputs
int Tx = 0;
int Ty = 0;
float x = 0;
float y = 0;

void setup() {
  //Setup Pins
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  //Get Joystick reading
  Tx = analogRead(A0);
  Ty = analogRead(A1);

  //Normailise and scale xAxis reading
  if (Tx > 550 || Tx < 470){
    x = (x-512)/512;
  } else{
    x = 0;
  }

  //Normalise and scale uAxis reading
  if (Ty < 470 || Ty > 550){
    y = (y-512)/512;
  } else{
    y = 0;
  }

  //Caluclates motor speed and scale them
  motorSpeedA = (y + x);
  motorSpeedB = (y - x);

  float maxMagnitude = max(abs(motorSpeedA), abs(motorSpeedB));

  if (maxMagnitude > 1.0) {
      motorSpeedA /= maxMagnitude;
      motorSpeedB /= maxMagnitude;
  }

  //Sets Left motor direction
  if (motorSpeedA < 0){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }

  //Sets right motor direction
  if(motorSpeedB < 0){
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  } else{
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }

  //Scales motor speed to PWM
  motorSpeedA *= 255;
  motorSpeedB *= 255;

  //Signal Motor Speed to LN298
  analogWrite(enA, abs(motorSpeedA)); 
  analogWrite(enB, abs(motorSpeedB)); 
}