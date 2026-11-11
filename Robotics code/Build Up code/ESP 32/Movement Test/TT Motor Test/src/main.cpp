#include <Arduino.h>

// Shifted from 34/35 to valid output pins 14/12
const int enA = 23; 
const int enB = 22; 

const int in1 = 32;
const int in2 = 33;
const int in3 = 25;
const int in4 = 26;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void loop() {
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  delay(1000);

  analogWrite(enA, 0);
  analogWrite(enB, 0);
  delay(1000);
}
